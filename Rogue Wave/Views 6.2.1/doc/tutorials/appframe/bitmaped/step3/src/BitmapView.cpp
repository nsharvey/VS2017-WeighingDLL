// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapView.cpp
// IlogViews 4 generated source file
// File generated Tue Jun 13 18:32:05 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <BitmapView.h>
#include <BitmapDocument.h>
#include <drawinter.h>
#include <ilviews/appframe/command.h>

#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/rectscgc.h>
#include <ilviews/gadgets/scview.h>

// --------------------------------------------------------------------------
// BitmapView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(BitmapView)
  Method1(BitmapHasChanged, bitmapHasChanged, IlAny, region)
IlvDvEndInterface1(IlvDvFormView)

// --------------------------------------------------------------------------
// Constructor / destructor
BitmapView::BitmapView(IlvDisplay* display)
: IlvDvFormView(display),
  _icon(0)
{
}

// --------------------------------------------------------------------------
BitmapView::~BitmapView()
{
}

// --------------------------------------------------------------------------
// Overridables
void
BitmapView::initializeView()
{
    IlvDvFormView::initializeView();
    BitmapDocument* document = getBitmapDocument();
    if (document->getBitmap()) {
	// Load the file
	setFilename("bitmapview.ilv");
	// Retrieve the IlvSCGadgetContainerRectangle
	IlvSCGadgetContainerRectangle* rectangle = 
	    (IlvSCGadgetContainerRectangle*)getContainer()->
	    getObject((IlvUInt)0);
	// Change the color of the clip view to 'black'
	IlvColor* color = getDisplay()->getColor("black");
	rectangle->getScrolledView()->getClipView()->setBackground(color);
	// Add the zoommable icon
	IlvContainer* container = rectangle->getContainer();
	_icon = new IlvZoomableIcon(getDisplay(),
				    IlvPoint(0, 0),
				    document->getBitmap(),
				    document->getPalette());
	container->addObject("Icon", _icon);
	container->fitToContents();
	_icon->setInteractor(new DrawBitmapInteractor(document));
    }
}

// --------------------------------------------------------------------------
// Basic properties
BitmapDocument*
BitmapView::getBitmapDocument() const
{
    return (BitmapDocument*)getDocument();
}

// --------------------------------------------------------------------------
void
BitmapView::bitmapHasChanged(IlAny region)
{
    IlvRegion redrawRegion(*(IlvRegion*)region);
    IlvContainer* container = IlvContainer::GetContainer(_icon);
    // Deal with the container transformer
    if (container->getTransformer())
	redrawRegion.apply(container->getTransformer());
    // Optimization : Clip using the visible size of the container
    IlvRect rect;
    container->sizeVisible(rect);
    redrawRegion.intersection(rect);
    // Then redraw the region
    container->bufferedDraw(redrawRegion);
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterGadgetViewClass(BitmapView, IlvDvFormView);

IL_BEGINMODULEINITDEF(BitmapView)
    IlvDvPostRegisterGadgetViewClass(BitmapView, IlvDvFormView);
IL_ENDMODULEINITDEF(BitmapView)

#if !defined(ILVBUILDLIBS)
static int BitmapView_ini = (IL_MODINIT(BitmapView)(), 0);
#endif

