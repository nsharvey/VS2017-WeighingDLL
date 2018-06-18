// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapDocument.cpp
// IlogViews 4 generated source file
// File generated Fri Jun  9 16:23:17 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------

#include <BitmapDocument.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/bitmaps/jpg.h>
#include <ilviews/bitmaps/bmp.h>

// --------------------------------------------------------------------------
// BitmapDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(BitmapDocument)
IlvDvEndInterface1(IlvDvDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
BitmapDocument::BitmapDocument()
: IlvDvDocument(),
  _bitmap(0),
  _palette(0)
{
}

// --------------------------------------------------------------------------
BitmapDocument::~BitmapDocument()
{
    setBitmap(0);
    setPalette(0);
}

// --------------------------------------------------------------------------
void
BitmapDocument::setBitmap(IlvBitmap* bitmap)
{
    if (bitmap)
	bitmap->lock();
    if (_bitmap)
	_bitmap->unLock();
    _bitmap = bitmap;
}

// --------------------------------------------------------------------------
void
BitmapDocument::setPalette(IlvPalette* palette)
{
    if (palette)
	palette->lock();
    if (_palette)
	_palette->unLock();
    _palette = palette;
}

// --------------------------------------------------------------------------
// Overridables

IlvBoolean
BitmapDocument::initializeDocument(IlvAny data)
{
    if (!IlvDvDocument::initializeDocument(data))
        return IlvFalse;
    
    IlvDisplay* display = getDisplay();
    // Creates the bitmap with a default size of 128x128
    IlvDim width = 128;
    IlvDim height = 128;
    IlvBitmap* bitmap =
	new IlvBitmap(display, width, height, display->screenDepth());
    setBitmap(bitmap);

    // Initialize it with the display palette
    setPalette(display->defaultPalette());
    getPalette()->invert();
    bitmap->fillRectangle(getPalette(), IlvRect(0, 0, width, height));
    getPalette()->invert();

    return IlvTrue;
}

// --------------------------------------------------------------------------
IlvBoolean
BitmapDocument::readDocument(const IlvPathName& pathname)
{
    IlvDisplay* display = getDisplay();
    // Read the bitmap
    IlvBitmap* bitmap = display->readBitmap(pathname);
    // If the bitmap has not been read correctly
    if (!bitmap || bitmap->isBad()) {
	delete bitmap;
	IlvFatalError("Cannot load %s bitmap !", (const char*)getPathName());
	return IlvFalse;
    } else {
	// The bitmap read by readBitmap is a shared bitmap. 
	// Here you do not want to use a shared bitmap because the editor may
	// modify it. So, the name set by the call to IlvDisplay::readBitmap
	// is removed.
	bitmap->setName(0);
	setBitmap(bitmap);
	setPalette(display->defaultPalette());
	return IlvTrue;
    }
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterDynClass(BitmapDocument, IlvDvDocument);

IL_BEGINMODULEINITDEF(BitmapDocument)
    IlvDvPostRegisterDynClass(BitmapDocument, IlvDvDocument);
IL_ENDMODULEINITDEF(BitmapDocument)
    
#if !defined(ILVBUILDLIBS)
static int BitmapDocument_ini = (IL_MODINIT(BitmapDocument)(), 0);
#endif


