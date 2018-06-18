// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/mgrvect.cpp
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
// Using vectorial fonts in an IlvManager
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gadmgr/mviselect.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/manager/geointer.h>
#include <ilviews/manager/rotinter.h>
#include <ilviews/manager/mkrectin.h>
#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/gadmgr/strinter.h>
#include <ilviews/base/sstream.h>
#include <ilviews/bitmaps/png.h>

ILVSTDUSE

#if defined(WINDOWS)
#include <vfincl/truetype.h>
#else  /* !WINDOWS */
#include <vfincl/vect.h>
#endif /* !WINDOWS */
#include <vfincl/vectlab.h>
#if !defined(WINDOWS)
extern "C" IlvVirtualVectFont* IlvVirtualVectFont_romans();
extern "C" IlvVirtualVectFont* IlvVirtualVectFont_romand();
#endif /* !WINDOWS */

// --------------------------------------------------------------------------
// Class IlvManagerMakeVectLabelInteractor
// --------------------------------------------------------------------------
class IlvManagerMakeRectPolygonInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvManagerMakeRectPolygonInteractor(IlvManager* manager, IlvView* view)
	: IlvDragRectangleInteractor(manager, view) {}
    // ____________________________________________________________
    virtual void doIt(IlvRect&);
};

// --------------------------------------------------------------------------
void
IlvManagerMakeRectPolygonInteractor::doIt(IlvRect& rect)
{
    IlvGraphic* obj;
    IlvPoint p1(rect.orig());
    IlvPoint p2(p1.x(), p1.y()+rect.h());
    IlvPoint p3(p2.x()+rect.w(),p2.y());
    IlvPoint p4(p3.x(), p1.y());
    obj = new IlvPolyline(getManager()->getDisplay(), p1, p2, p3, p4);
    getManager()->deSelect();
    getManager()->addObject(obj);
    getManager()->makeSelected(obj);
}

// --------------------------------------------------------------------------
// Class IlvManagerMakeVectLabelInteractor
// --------------------------------------------------------------------------
class IlvManagerMakeVectLabelInteractor
: public IlvManagerMakeLabelInteractor
{
public:
    IlvManagerMakeVectLabelInteractor(IlvManager* manager,
				      IlvView* eview,
				      IlvVectFont* font)
	: IlvManagerMakeLabelInteractor(manager,eview), _font(font)
    { _font->lock(); }
    ~IlvManagerMakeVectLabelInteractor() { _font->unLock(); }
    // ____________________________________________________________
    virtual IlBoolean accept(IlvPoint& p);
    virtual void doIt(const char*);
protected:
    IlvVectFont* _font;
};

// --------------------------------------------------------------------------
IlBoolean
IlvManagerMakeVectLabelInteractor::accept(IlvPoint& p)
{
    IlvManagerMakeLabelInteractor::accept(p);
    _label = 0;
    return IlTrue;
}

// --------------------------------------------------------------------------
void
IlvManagerMakeVectLabelInteractor::doIt(const char* buffer)
{
    IlvGraphic* obj = new IlvVectLabel(getManager()->getDisplay(),
				       _font,
				       _position,
				       buffer);
    getManager()->deSelect();
    getManager()->addObject(obj);
    getManager()->makeSelected(obj);
}

// --------------------------------------------------------------------------
// Class MgrVect
// --------------------------------------------------------------------------
class MgrVect
: public IlvGadgetContainer
{
public:
    MgrVect(IlvDisplay*, IlvRect* size = 0);
    ~MgrVect();
    // ___________________________________
    IlvSCManagerRectangle* getSCManagerRectangle() const
    {
	return (IlvSCManagerRectangle*)getObject("SCM");
    }
    IlvToolBar* getToolBar() const
    {
	return (IlvToolBar*)getObject("toolbar");
    }
    IlvManagerViewInteractorSelector* getHook() const
    {
	return _hook;
    }
    IlvManager* getManager() const
    {
	return _manager;
    }
    IlvView* getView() const
    {
	return _view;
    }
    IlvVirtualVectFont* getDefaultVirtualVectFont() const {
	return _defaultvirtualvectfont;
    }
protected:
    IlvManagerViewInteractorSelector*	 _hook;
    IlvManager*				 _manager;
    IlvView*				 _view;
    IlvSelectInteractor*		 _select;
    IlvMakeZoomInteractor*		 _zoom;
    IlvMakeUnZoomInteractor*		 _unzoom;
    IlvRotateInteractor*		 _rotate;
    IlvManagerMakeRectPolygonInteractor* _mkrectpoly;
    IlvManagerMakeVectLabelInteractor*	 _mkvectlab;
#if !defined(WINDOWS)
    IlvVirtualVectFont*
#else /* WINDOWS */
    IlvVirtualTrueTypeFont*
#endif /* WINDOWS */
					 _defaultvirtualvectfont;
    void init();
};

// --------------------------------------------------------------------------
MgrVect::MgrVect(IlvDisplay* display, IlvRect* rect)
: IlvGadgetContainer(display,
		     "MgrVect",
		     "MgrVect",
		     rect ? *rect : IlvRect(0, 0, 600, 400),
		     IlFalse,
		     IlFalse),
  _hook(0),
  _manager(0),
  _view(0),
  _select(0),
  _zoom(0),
  _unzoom(0),
  _rotate(0),
  _mkrectpoly(0),
  _mkvectlab(0),
  _defaultvirtualvectfont(0)
{
    readFile("../data/mgrvect.ilv");
    init();
}

// --------------------------------------------------------------------------
MgrVect::~MgrVect()
{
    _manager->removeInteractor(_view);
    delete _hook;
    delete _select;
    delete _zoom;
    delete _unzoom;
    delete _rotate;
    delete _mkrectpoly;
    delete _mkvectlab;
}

// --------------------------------------------------------------------------
void
MgrVect::init()
{
    // Creates the manager
    _manager = new IlvManager(getDisplay(), 3);
    // Retrieve the sc manager
    IlvSCManagerRectangle* viewRect = getSCManagerRectangle();
    viewRect->setManager(_manager);
    _view = viewRect->getView();
    // Retrieve the toolbar
    IlvToolBar* toolbar = getToolBar();
    // Create the selector
    IlvMenuItemSelector* selector =
	new IlvMenuItemSelector(IlvGetSymbol("Interactors"));
    // Connect it to the toolbar
    selector->addTo(toolbar);
    // Create the Interactor selector and connect it to the manager
    _hook = new IlvManagerViewInteractorSelector(_manager, _view, selector);
    _manager->installViewHook(_hook);

#define TOOL(i, inter) \
selector->addItem(toolbar->getItem(i)); \
_hook->link(toolbar->getItem(i)->getSName(), inter);

    // Selection tool
    _select = new IlvSelectInteractor(_manager, _view);
    TOOL(0, _select);
    _manager->setInteractor(_select);
    // Zoom tool
    _zoom = new IlvMakeZoomInteractor(_manager, _view);
    TOOL(1, _zoom);
    // Unzoom tool
    _unzoom = new IlvMakeUnZoomInteractor(_manager, _view);
    TOOL(2, _unzoom);
    // Rotate tool
    _rotate = new IlvRotateInteractor(_manager, _view);
    TOOL(3, _rotate);
    // Closed polygons construction tool
    _mkrectpoly = new IlvManagerMakeRectPolygonInteractor(_manager, _view);
    TOOL(4, _mkrectpoly);
    // Label construction tool
#if !defined(WINDOWS)
    _defaultvirtualvectfont = IlvVirtualVectFont_romans();
    IlvVectFont* font = new IlvVectFont(_defaultvirtualvectfont, 40, 40, 0, 0);
#else /* WINDOWS */
    _defaultvirtualvectfont = new IlvVirtualTrueTypeFont("Arial");
    IlvVectFont* font =
	new IlvTrueTypeFont(_defaultvirtualvectfont, 0, 9, (IlFloat)0);
#endif /* WINDOWS */
    _mkvectlab = new IlvManagerMakeVectLabelInteractor(_manager, _view, font);
    TOOL(5, _mkvectlab);
}

// --------------------------------------------------------------------------
// Callbacks as methods
// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("MgrVect", 0, argc, argv);
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        delete display;
        return -1;
    }
    IlvRect size(0, 0, 600, 400);
    MgrVect* cont = new MgrVect(display, &size);
    IlvManager* man = cont->getManager();
#if !defined(WINDOWS)
    IlvVirtualVectFont* vfont = cont->getDefaultVirtualVectFont();
    man->addObject(new IlvVectLabel(display,
				    new IlvVectFont(vfont, 40,40,0,0),
				    IlvPoint(10,  50), "Font Romans"));
    IlvVirtualVectFont* vfontr = IlvVirtualVectFont_romand();
    man->addObject(new IlvVectLabel(display,
				    new IlvVectFont(vfontr, 40,40,0,0),
				    IlvPoint(10,  150),
				    "Rogue Wave Views Font Romand"));
#else  /* WINDOWS */
    IlvVirtualTrueTypeFont* vfont =
	(IlvVirtualTrueTypeFont*)cont->getDefaultVirtualVectFont();
    man->addObject(new IlvVectLabel(display,
				    new IlvTrueTypeFont(vfont,
				    			0, 9, (IlFloat)0),
				    IlvPoint(10, 100), "True Type Font"));
    man->addObject(new IlvVectLabel(display,
				    new IlvTrueTypeFont(vfont,
							0, 9, (IlFloat)0,
							(IlvFontStyle)
							(IlvBoldFontStyle|
							 IlvUnderlinedFontStyle|
							 IlvItalicFontStyle)),
				    IlvPoint(10, 150), "True Type Font"));
    man->addObject(new IlvVectLabel(display,
				    new IlvTrueTypeFont(vfont,
							0, 9, (IlFloat)0,
							IlvNormalFontStyle,
							IlvDraftFontQuality),
				    IlvPoint(10, 200), "True Type Font"));
#endif /* WINDOWS */
    cont->setDestroyCallback(Quit);
    cont->show();
    IlvMainLoop();
    return 0;
}
