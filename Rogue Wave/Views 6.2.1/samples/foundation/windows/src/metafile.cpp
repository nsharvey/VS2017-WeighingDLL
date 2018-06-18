// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/windows/src/metafile.cpp
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Reading a Rogue Wave Views file in a container and dump in a metafile.
// --------------------------------------------------------------------------

#include <ilviews/graphics/all.h>
#include <ilviews/contain/contain.h>
#include <ilviews/windows/dump.h>

#include <windows.h>
#if defined(IL_STD)
#include <fstream>
IL_STDUSE
#else  /* !IL_STD */
#include <fstream.h>
#endif /* !IL_STD */

static char* DefaultFileName    = "elefante.ilv";
static char* DefaultEMFDumpName = "dump.emf";
static char* DefaultWMFDumpName = "dump.wmf";
static char* DumpName = 0;

#if defined(_MSC_VER)
#pragma pack(push, 1)
#endif /* _MSC_VER */
typedef struct PlaceableHeader {
    DWORD key;
    WORD  hmf;
    WORD  left;
    WORD  top;
    WORD  right;
    WORD  bottom;
    WORD  inch;
    DWORD reserved;
    WORD  cheksum;
} _PlaceableHeader;

#if defined(_MSC_VER)
#pragma pack(pop)
#endif /* _MSC_VER */

static void ILVCALLBACK DumpInMetafile(IlvContainer*, IlvEvent&, IlAny);

enum MFType {
    WMFType = 1,
    PMFType,
    EMFType
} _MFType;

// --------------------------------------------------------------------------
class MetaFileDump
    : public IlvWindowsVirtualDevice
{
public:
    // ____________________________________________________________
    MetaFileDump(IlvDisplay* display,
		 MFType type = PMFType)
        : IlvWindowsVirtualDevice(display), _type(type), _filename(0)
    {
    }

    // ____________________________________________________________
    virtual IlBoolean init(const char* filename,
			   IlvRect* bbox = 0);
    IlBoolean init(const char*	filename,
		   const char*	description,
		   IlvRect*	bbox = 0);
    MFType getType() const	{ return _type; }
    virtual void send(const char*) const {} // Nothing to do.
    void   setType(MFType);
    virtual void end();

private:
    MFType _type;
    char*  _filename;
};

// --------------------------------------------------------------------------
IlBoolean
MetaFileDump::init(const char* filename,
		   IlvRect* bbox)
{
    if (_type == EMFType)
	return init(filename, 0, bbox);
    HDC hdc
#if !defined(__BORLANDC__)
	    = 0
#endif /* !Borland C++ */
	   ;
    if (_filename)
	delete [] _filename;
    const char* f = 0;
    if (_type == PMFType) {
	if (!bbox) {
	    IlvFatalError("Placeable Metafiles need a bbox.");
	    return IlFalse;
	}
	_filename = strcpy(new char [strlen(filename) + 1], filename);
	PlaceableHeader* header = new PlaceableHeader;
	header->key    = (DWORD)0x9AC6CDD7L;
	header->hmf    = 0;
	header->left   = (WORD)bbox->x();
	header->top    = (WORD)bbox->y();
	header->right  = (WORD)bbox->right();
	header->bottom = (WORD)bbox->bottom();
	header->inch   = (WORD)1000;
	WORD* p = (WORD*)header;
	header->cheksum = *p;
	for (int loop = 1; loop < 10; ++loop)
	    header->cheksum ^= *(++p);
	ofstream str(_filename, ios::binary);
	str.write((const char*)header, sizeof(PlaceableHeader));
	delete header;
    } else
	f = filename;
    // Create a Windows Metafile.
    hdc = CreateMetaFile(f);
    // Test if ok.
    if (!hdc)
	return IlFalse;
    setHDC(hdc);
    return IlvWindowsVirtualDevice::init(filename, bbox);
}

// --------------------------------------------------------------------------
void
MetaFileDump::setType(MFType type)
{
    _type = type;
}

// --------------------------------------------------------------------------
IlBoolean
MetaFileDump::init(const char* filename,
		   const char* descr,
		   IlvRect* bbox)
{
    HDC hdc
#if !defined(__BORLANDC__)
	    = 0
#endif /* !Borland C++ */
	   ;
    // Compute the size in .01-mm
    LPRECT lpRect = 0;
    RECT rect;
    if (bbox) {
	HDC hdcRef = GetDC(NULL);
	int iMMPerPelX = (GetDeviceCaps(hdcRef, HORZSIZE) * 100) /
			  GetDeviceCaps(hdcRef, HORZRES);
	int iMMPerPelY = (GetDeviceCaps(hdcRef, VERTSIZE) * 100) /
			  GetDeviceCaps(hdcRef, VERTRES);
	ReleaseDC(NULL, hdcRef);
	rect.left   = (LONG)(bbox->x() * iMMPerPelX);
	rect.top    = (LONG)(bbox->y() * iMMPerPelY);
	rect.right  = (LONG)((bbox->x() + bbox->w()) * iMMPerPelX);
	rect.bottom = (LONG)((bbox->y() + bbox->h()) * iMMPerPelY);
	lpRect = &rect;
    }
    // Create an enhanced metafile.
    hdc = CreateEnhMetaFile(NULL, filename, lpRect, descr);
    if (!hdc)
	return IlFalse;
    setHDC(hdc);
    return IlvWindowsVirtualDevice::init(filename, bbox);
}

// --------------------------------------------------------------------------
void
MetaFileDump::end()
{
    IlvWindowsVirtualDevice::end();
    if (_type == EMFType) {
	HENHMETAFILE hEmf = CloseEnhMetaFile((HDC)getHDC());
	if (hEmf)
	    DeleteEnhMetaFile(hEmf);
	return;
    }
    HMETAFILE hWmf = CloseMetaFile((HDC)getHDC());
    if (_filename) {
	UINT size;
	char* buffer = 0;
	if (((size = GetMetaFileBitsEx(hWmf, 0, 0)) == 0) ||
	    ((buffer = new char [size]) == 0) ||
	    (size != GetMetaFileBitsEx(hWmf, size, buffer)))
	    IlvFatalError("Can't write the placeable metafile.");
	else {
	    ofstream str(_filename, ios::binary|ios::app);
	    str.write(buffer, size);
	}
	if (buffer)
	    delete [] buffer;
	delete [] _filename;
    }
    if (hWmf)
	DeleteMetaFile(hWmf);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
Quit(IlvTopView* top,
     IlAny)
{
    IlvDisplay* d = top->getDisplay();
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    char* filename = DefaultFileName;
    for (int loop = 1; loop < argc; ++loop) {
	if (argv[loop]) {
	    if (!strcmp(argv[loop], "-d")) {
		if ((argc == loop + 1) || !argv[loop + 1])
		    IlvWarning("Usage: %s [file] [-d dumpfile]", argv[0]);
		else
		    DumpName = argv[++loop];
		continue;
	    }
	    filename = argv[loop];
	}
    }
    IlvDisplay* display = new IlvDisplay("Metafile", "", argc, argv);
    if (!display || display->isBad()) {
	if (display)
	    delete display;
	IlvFatalError("Can't open display...");
	return 1;
    }
    IlvRect dims(0, 0, 360, 460);
    char* title = "Metafile";
    IlvTopView* topwindow =
	new IlvTopView(display, title, title, dims, IlFalse);
    topwindow->setDestroyCallback(Quit);
    IlvContainer* container = new IlvContainer(topwindow, dims, IlTrue);
    container->readFile(filename);
    container->addAccelerator(DumpInMetafile, IlvKeyUp, 'D');
    container->addAccelerator(DumpInMetafile,
			      IlvKeyUp,
			      'E',
			      0,
			      (IlAny)EMFType);
    container->addAccelerator(DumpInMetafile,
			      IlvKeyUp,
			      'W',
			      0,
			      (IlAny)WMFType);
    container->addAccelerator(DumpInMetafile,
			      IlvKeyUp,
			      'P',
			      0,
			      (IlAny)PMFType);
    topwindow->show();
    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
DumpInMetafile(IlvContainer* cont,
	       IlvEvent&,
	       IlAny arg)
{
    MFType type = IL_CAST(MFType, IlCastIlAnyToInt(arg));
    if (!type)
	type = EMFType;
    if (!DumpName)
	DumpName = (type == EMFType) ? DefaultEMFDumpName : DefaultWMFDumpName;
    IlvDisplay* display = cont->getDisplay();
    MetaFileDump device(display, type);
    IlvRect size;
    cont->boundingBox(size);
    if (device.init(DumpName, &size)) {
	display->initDump(&device);
	cont->draw();
	display->endDump();
    } else
	IlvFatalError("DumpMetaFile : Can't init the metafile device.");
    return;
}
