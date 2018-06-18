// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapDocument.cpp
// IlogViews 4 generated source file
// File generated Fri Jun  9 16:23:17 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------

#include <BitmapDocument.h>
#include <drawcmd.h>
#include <bmpsize.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/bitmaps/jpg.h>
#include <ilviews/bitmaps/bmp.h>

#if defined(IL_STD)
#include <iostream>
IL_STDUSE
#else  /* !IL_STD */
#include <iostream.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
// BitmapDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(BitmapDocument)
  Action(ColorChooser, colorChooser)
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
    // Pops-up a dialog to let the use choose the initial size
    BitmapSizeDialog dialog(display, "New Image", "New Image");
    dialog.moveToMouse(IlvCenter);
    dialog.wait();
    IlvDim width = dialog.getWidth()->getIntValue();
    IlvDim height = dialog.getHeight()->getIntValue();
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
    IlvBitmap* bitmap = display->readBitmap(pathname);
    if (!bitmap || bitmap->isBad()) {
	IlvFatalError("Cannot load %s bitmap !", (const char*)getPathName());
	return IlvFalse;  //Bitmap has not been read correctly 
    } else {
	IlvBitmap* bitmapCopy = new IlvBitmap(display,
					      bitmap->width(),
					      bitmap->height(),
					      bitmap->depth());
	bitmapCopy->drawBitmap(display->defaultPalette(),
			       bitmap,
			       IlvRect(0,
				       0,
				       bitmap->width(),
				       bitmap->height()),
			       IlvPoint(0, 0));
	setBitmap(bitmapCopy);
	setPalette(display->defaultPalette());
	return IlvTrue;
    }
}

// --------------------------------------------------------------------------
IlvBoolean
BitmapDocument::saveDocument(const IlvPathName& pathName)
{
    IlvDvFileStream stream(pathName, IlvTrue, getDisplay());
    if (!stream.getOutStream() || !(*stream.getOutStream()))
        return IlvFalse;
    IlString extension = pathName.getExtension();
    IlvBitmapStreamer* streamer = 0;
    ILVSTDPREF ostream* outstream = stream.getOutStream();
    if (!(!*outstream)) {
	if (extension.equals("png"))
	    streamer = new IlvPNGStreamer;
	else
	    if (extension.equals("jpg"))
		streamer = new IlvJPGStreamer;
	    else
		if (extension.equals("bmp"))
		    streamer = new IlvBMPStreamer;
    }
    if (streamer) {
	IlvBitmapData* bitmapData = IlvSystemPort::GetBitmapData(getBitmap());
	streamer->write(bitmapData, *outstream);
	delete streamer;
	stream.close();
	return IlTrue;
    } else {
	IlvIErrorDialog dialog(getDisplay(), "Unknown format !");
	dialog.moveToMouse();
	dialog.get();
	stream.close();
	return IlFalse;
    }
}

// --------------------------------------------------------------------------
void
BitmapDocument::refreshViews(const IlvRegion& region)
{
    notifyViews(IlvGetSymbol("BitmapHasChanged"), 0, &region);
}

// --------------------------------------------------------------------------
void
BitmapDocument::refreshViews(const IlvRect& rect)
{
    refreshViews(IlvRegion(rect));
}

// --------------------------------------------------------------------------
void
BitmapDocument::drawRectangle(const IlvPoint& point,
			      IlvDim size,
			      IlvPalette* palette)
{
    doCommand(new DrawRectangleCommand(this,
				       point,
				       size,
				       palette,
				       "drawRectangle"));
}

// --------------------------------------------------------------------------
void
BitmapDocument::colorChooser()
{
    IlvColorSelector dialog(getDisplay());
    IlvColor* color = dialog.get(IlTrue);
    if (color) {
	IlvPalette* palette = getPalette();
	setPalette(getDisplay()->getPalette(palette->getBackground(),
					    color,
					    palette->getPattern(),
					    palette->getColorPattern(),
					    palette->getFont(),
					    palette->getLineStyle(),
					    palette->getLineWidth(),
					    palette->getFillStyle(),
					    palette->getArcMode(),
					    palette->getFillRule()));
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


