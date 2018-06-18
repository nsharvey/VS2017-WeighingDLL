#include <ilviews/grapher/grapher.h>
#include <ilviews/base/error.h>
[!if INTERGRAPHSEL]
#include <ilviews/grapher/selinter.h>
[!endif]
[!if INTERGRAPHIMG]
#include <ilviews/grapher/inters.h>
[!endif]
[!if OBSERVER]
#include <ilviews/grapher/observer.h>
#include <ilviews/manager/layer.h>
[!endif]
[!if ADDOBJS]
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/ellipse.h>
[!endif]
[!if ADDLINKS]
#include <ilviews/grapher/links.h>
[!endif]

// -------------------------------------------------------------------------
static char const ApplyName[]	= "[!output PROJECT_NAME]";
static char const ViewName[]	= "MyGrapher";
static IlvRect const ViewSize(10, 10, 800, 600);
[!if ADDOBJS]
static IlvRect const FilledRectangle1Size( 10,  10, 100, 25);
static IlvRect const FilledRectangle2Size(300, 300, 100, 25);
static IlvRect const FilledEllipse1Size(  300,  10, 100, 25);
static IlvRect const FilledEllipse2Size(   10, 300, 100, 25);
[!endif]

[!if OBSERVER]
// -------------------------------------------------------------------------
class MyManagerObserver
: public IlvManagerObserver
{
public:
    MyManagerObserver(IlvManager* manager);
    virtual void update(IlvObservable* observable, IlvAny userArg);
};

// -------------------------------------------------------------------------
inline
MyManagerObserver::MyManagerObserver(IlvManager* manager)
: IlvManagerObserver(manager)
{
}

// -------------------------------------------------------------------------
void
MyManagerObserver::update(IlvObservable* observable, IlvAny userArg)
{
    IlvManager* manager =
	IL_CAST(IlvManagerObservable*, observable)->getManager();
    IlvManagerMessage* message = IL_CAST(IlvManagerMessage*, userArg);
    switch (message->_reason) {
    // __ Notification on the manager itself.
    case IlvMgrMsgDelete: {
	IlvCOut << "Delete manager notification.\n";
	break;
    }
    case IlvMgrMsgUndo: {
	IlvCOut << "Undo notification.\n";
	break;
    }
    case IlvMgrMsgGrid: {
	IlvCOut << "Grid notification.\n";
	break;
    }
    // __ Notification on manager view.
    case IlvMgrMsgAddView: {
	IlvCOut << "Add view notification.\n";
	break;
    }
    case IlvMgrMsgRemoveView: {
	IlvCOut << "Remove view notification.\n";
	break;
    }
    case IlvMgrMsgSetInteractor: {
	IlvCOut << "Set interactor notification.\n";
	break;
    }
    case IlvMgrMsgSetTransformer: {
	IlvCOut << "Set transformer notification.\n";
	break;
    }
    // __ Notification on manager contents.
    case IlvMgrMsgAddObject: {
	IlvManagerContentsMessage* msg =
	    IL_CAST(IlvManagerContentsMessage*, userArg);
	IlvCOut << "Add object " << msg->getObject()
		<< ", layer " << msg->_layer
		<< ".\n";
	break;
    }
    case IlvMgrMsgRemoveObject: {
	IlvManagerContentsMessage* msg =
	    IL_CAST(IlvManagerContentsMessage*, userArg);
	IlvCOut << "Remove object " << msg->getObject()
		<< ", layer " << msg->_layer
		<< ".\n";
	break;
    }
    case IlvMgrMsgObjectLayer: {
	IlvManagerObjectLayerMessage* msg =
	    IL_CAST(IlvManagerObjectLayerMessage*, userArg);
	IlvCOut << "Object " << msg->getObject()
		<< " moved from layer " << msg->_layer
		<< " to layer " << msg->_oldLayer
		<< ".\n";
	break;
    }
    // __ Notification on manager layer.
    case IlvMgrMsgAddLayer: {
	IlvManagerLayerMessage* msg =
	    IL_CAST(IlvManagerLayerMessage*, userArg);
	IlvCOut << "Add layer notification: " << msg->getLayer() << ".\n";
	break;
    }
    case IlvMgrMsgRemoveLayer: {
	IlvManagerLayerMessage* msg =
	    IL_CAST(IlvManagerLayerMessage*, userArg);
	IlvCOut << "Remove layer notification: " << msg->getLayer() << ".\n";
	break;
    }
    case IlvMgrMsgMoveLayer: {
	IlvManagerMoveLayerMessage* msg =
	    IL_CAST(IlvManagerMoveLayerMessage*, userArg);
	IlvCOut << "Move layer notification: "
		<< msg->_oldIndex
		<< " moved to "
		<< msg->getLayer()
		<< ".\n";
	break;
    }
    case IlvMgrMsgSwapLayer: {
	IlvManagerSwapLayerMessage* msg =
	    IL_CAST(IlvManagerSwapLayerMessage*, userArg);
	IlvCOut << "Swap layer notification: "
		<< msg->getLayer()
		<< " and "
		<< msg->_layer2
		<< ".\n";
	break;
    }
    case IlvMgrMsgLayerName: {
	IlvManagerLayerNameMessage* msg =
	    IL_CAST(IlvManagerLayerNameMessage*, userArg);
	IlvCOut << "Layer name notification: "
		<< msg->_oldName
		<< " changed to "
		<< manager->getManagerLayer(msg->getLayer())->getName()
		<< ".\n";
	break;
    }
    case IlvMgrMsgLayerVisibility: {
	IlvManagerLayerMessage* msg =
	    IL_CAST(IlvManagerLayerMessage*, userArg);
	IlvCOut << "Layer visibility notification: "
		<< msg->getLayer()
		<< ".\n";
	break;
    }
    case IlvMgrMsgLayerSelectability: {
	IlvManagerLayerMessage* msg =
	    IL_CAST(IlvManagerLayerMessage*, userArg);
	IlvCOut << "Layer selectability notification: "
		<< msg->getLayer()
		<< ".\n";
	break;
    }
    // __ Notification on object geometry
    case IlvMgrMsgObjectGeometry: {
	IlvCOut << "Object geometry notification.\n";
	break;
    }
    // __ Notification on the grapher (link connection)
    case IlvGrapherMsgLinkConnection: {
	IlvCOut << "Link connection notification.\n";
	break;
    }
    default: {
	IlvCOut << "Unhandled notification.\n";
	break;
    }
    }
}
[!endif]

[!if MYCLASS]
// -------------------------------------------------------------------------
// IlvGrapher subclass
class MyIlvGrapher : public IlvGrapher
{
public:
    MyIlvGrapher(IlvDisplay*		display,
		 int			layers		= 2,
		 IlBoolean		useAccelerators	= IlTrue,
		 IlUShort		maxInList	= IlvMaxObjectsInList,
		 IlUShort		maxInNode	= IlvMaxObjectsInList);

    void addNode(IlvGraphic*		obj,
		 IlBoolean		redraw		= IlTrue,
		 int			layer		= -1);
    void addLink(IlvLinkImage*		link,
		 IlBoolean		redraw		= IlTrue,
		 int			layer		= -1,
		 IlvLinkImage*		afterFrom	= 0,
		 IlvLinkImage*		afterTo		= 0);
    void removeNode(IlvGraphic*		obj,
		    IlBoolean		redraw		= IlTrue,
		    IlBoolean		destroyIt	= IlTrue);
    void removeLink(IlvLinkImage*	link,
		    IlBoolean		redraw		= IlTrue,
		    IlBoolean		destroyIt	= IlTrue);
    void nodeXPretty(IlvGraphic*	node,
		     IlvPos		xspacing,
		     IlvPos		yspacing,
		     IlBoolean		redraw		= IlTrue,
		     IlvOrientation	orientation	= IlvCenter);
    void nodeYPretty(IlvGraphic*	node,
		     IlvPos		xspacing,
		     IlvPos		yspacing,
		     IlBoolean		redraw		= IlTrue,
		     IlvOrientation	orientation	= IlvCenter);
    void changeNode(IlvGraphic*		node,
		    IlvGraphic*		newNode,
		    IlBoolean		redraw		= IlFalse);
    void changeLink(IlvLinkImage*	link,
		    IlvLinkImage*	newLink,
		    IlBoolean		redraw		= IlFalse);
    IlvGrapher* makeNode(IlvGraphic*	obj);
    IlvGrapher* makeLink(IlvGraphic*	obj);
};

// -------------------------------------------------------------------------
inline
MyIlvGrapher::MyIlvGrapher(IlvDisplay*	display,
			   int		layers,
			   IlBoolean	useAccelerators,
			   IlUShort	maxInList,
			   IlUShort	maxInNode)
: IlvGrapher(display, layers, useAccelerators, maxInList, maxInNode)
{
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::addNode(IlvGraphic* obj, IlBoolean redraw, int layer)
{
    IlvGrapher::addNode(obj, redraw, layer);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::addLink(IlvLinkImage*	link,
		      IlBoolean		redraw,
		      int		layer,
		      IlvLinkImage*	afterFrom,
		      IlvLinkImage*	afterTo)
{
    IlvGrapher::addLink(link, redraw, layer, afterFrom, afterTo);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::removeNode(IlvGraphic*	obj,
			 IlBoolean	redraw,
			 IlBoolean	destroyIt)
{
    IlvGrapher::removeNode(obj, redraw, destroyIt);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::removeLink(IlvLinkImage*	link,
			 IlBoolean	redraw,
			 IlBoolean	destroyIt)
{
    IlvGrapher::removeLink(link, redraw, destroyIt);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::nodeXPretty(IlvGraphic*		node,
			  IlvPos		xspacing,
			  IlvPos		yspacing,
			  IlBoolean		redraw,
			  IlvOrientation	orientation)
{
    IlvGrapher::nodeXPretty(node, xspacing, yspacing, redraw, orientation);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::nodeYPretty(IlvGraphic*		node,
			  IlvPos		xspacing,
			  IlvPos		yspacing,
			  IlBoolean		redraw,
			  IlvOrientation	orientation)
{
    IlvGrapher::nodeYPretty(node, xspacing, yspacing, redraw, orientation);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::changeNode(IlvGraphic*	node,
			 IlvGraphic*	newNode,
			 IlBoolean	redraw)
{
    IlvGrapher::changeNode(node, newNode, redraw);
}

// -------------------------------------------------------------------------
inline void
MyIlvGrapher::changeLink(IlvLinkImage*	link,
			 IlvLinkImage*	newLink,
			 IlBoolean	redraw)
{
    IlvGrapher::changeLink(link, newLink, redraw);
}

// -------------------------------------------------------------------------
inline IlvGrapher*
MyIlvGrapher::makeNode(IlvGraphic* obj)
{
    IlvGrapher::makeNode(obj);
}

// -------------------------------------------------------------------------
inline IlvGrapher*
MyIlvGrapher::makeLink(IlvGraphic* obj)
{
    IlvGrapher::makeLink(obj);
}
[!endif]

// -------------------------------------------------------------------------
class Context {
public:
    static Context&		GetContext(int argc, char* argv[]);
    ~Context();
    IlBoolean			operator!() const;
    IlvDisplay*			getDisplay() const;
[!if MYCLASS]
    MyIlvGrapher*		getGrapher() const;
[!else]
    IlvGrapher*			getGrapher() const;
[!endif]
    IlvView*			getView() const;
[!if INTERGRAPHSEL]
    IlvSelectInteractor*	getSelectInteractor() const;
[!endif]
[!if INTERGRAPHIMG]
    IlvMakeLinkInteractor*	getMakeLinkInteractor() const;
[!endif]
[!if OBSERVER]
    IlvManagerObserver*		getObserver() const;
[!endif]

private:
    Context(int argc, char* argv[]);
    // Intentionally not defined.
    Context(Context const&);
    // Intentionally not defined.
    Context& operator=(Context const&);
    void			clean();
    static void			DestroyCB(IlvView* view, IlAny userArg);

    IlvView*			_view;
[!if OBSERVER]
    IlvManagerObserver*		_observer;
[!endif]
[!if INTERGRAPHSEL]
    IlvSelectInteractor*	_selectInteractor;
[!endif]
[!if INTERGRAPHIMG]
    IlvMakeLinkInteractor*	_makeLinkInteractor;
[!endif]
[!if MYCLASS]
    MyIlvGrapher*		_grapher;
[!else]
    IlvGrapher*			_grapher;
[!endif]
};

// -------------------------------------------------------------------------
Context&
Context::GetContext(int argc, char* argv[])
{
    static Context* Singleton = new Context(argc, argv);
    return *Singleton;
}

// -------------------------------------------------------------------------
IlBoolean
Context::operator!() const
{
    return _view ? IlFalse : IlTrue;
}

// -------------------------------------------------------------------------
IlvDisplay*
Context::getDisplay() const
{
    return _view->getDisplay();
}

// -------------------------------------------------------------------------
[!if MYCLASS]
MyIlvGrapher*
[!else]
IlvGrapher*
[!endif]
Context::getGrapher() const
{
    return _grapher;
}

// -------------------------------------------------------------------------
IlvView*
Context::getView() const
{
    return _view;
}

[!if INTERGRAPHSEL]
// -------------------------------------------------------------------------
IlvSelectInteractor*
Context::getSelectInteractor() const
{
    return _selectInteractor;
}
[!endif]

[!if INTERGRAPHIMG]
// -------------------------------------------------------------------------
IlvMakeLinkInteractor*
Context::getMakeLinkInteractor() const
{
    return _makeLinkInteractor;
}
[!endif]

[!if OBSERVER]
// -------------------------------------------------------------------------
IlvManagerObserver*
Context::getObserver() const
{
    return _observer;
}
[!endif]

// -------------------------------------------------------------------------
Context::~Context()
{
    clean();
}

// -------------------------------------------------------------------------
Context::Context(int argc, char* argv[])
: _view(0),
[!if OBSERVER]
  _observer(0),
[!endif]
[!if INTERGRAPHSEL]
  _selectInteractor(0),
[!endif]
[!if INTERGRAPHIMG]
  _makeLinkInteractor(0),
[!endif]
  _grapher(0)
{
    // Creates the display.
    IlvDisplay* display = new IlvDisplay(ApplyName, "", argc, argv);
    if (!display || display->isBad()) {
	IlvCErr << "Can't initialize the display.\n";
	if (display) {
	    delete display;
	}
	return;
    }

    // Creates the panel.
    _view = new IlvView(display, ViewName, ApplyName, ViewSize);
    if (!_view) {
	IlvCErr << "Can't build the main view.\n";
	delete display;
	return;
    }
    _view->setDestroyCallback(DestroyCB, this);

    // Creates the manager.
[!if MYCLASS]
    _grapher = new MyIlvGrapher(display);
[!else]
    _grapher = new IlvGrapher(display);
[!endif]
    if (!_grapher) {
	IlvCErr << "Can't build the manager.\n";
	clean();
	return;
    }
    _grapher->addView(_view);

[!if OBSERVER]
    // Adds an an IlvManagerObserver to the manager.
    _observer = new MyManagerObserver(_grapher);
    if ( !_observer) {
	IlvCErr << "Can't build the observer.\n";
	clean();
	return;
    }
[!endif]

[!if INTERGRAPHSEL]
    // Adds a select interactor.
    _selectInteractor = new IlvGraphSelectInteractor(_grapher, _view);
    if (!_selectInteractor) {
	IlvCErr << "Can't build the Select interactor.\n";
	clean();
	return;
    }
    _grapher->setInteractor(_selectInteractor, _view);
[!endif]

[!if INTERGRAPHIMG]
    // Set an IlvMakeOneLnkImageInteractor.
    _makeLinkInteractor = new IlvMakeOneLinkImageInteractor(_grapher, _view);
    if (!_makeLinkInteractor) {
	IlvCErr << "Can't build the MakeOneLinkImage interactor.\n";
	clean();
	return;
    }
    _grapher->setInteractor(_makeLinkInteractor, _view);
[!endif]
}

// -------------------------------------------------------------------------
void
Context::clean()
{
    if (_grapher) {
	delete _grapher;
    }

[!if INTERGRAPHSEL]
    if (_selectInteractor) {
	delete _selectInteractor;
    }
[!endif]
[!if INTERGRAPHIMG]
    if (_makeLinkInteractor) {
	delete _makeLinkInteractor;
    }
[!endif]
[!if OBSERVER]
    if (_observer) {
	delete _observer;
    }
[!endif]
    if (_view) {
	// The display deletes all the views.
	delete _view->getDisplay();
    }
}

// -------------------------------------------------------------------------
// Exits the application.
void
Context::DestroyCB(IlvView* view, IlvAny userArg)
{
    Context* context = IL_CAST(Context*, userArg);
    delete context;
    IlvExit(EXIT_SUCCESS);
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    int exitCode = EXIT_SUCCESS;
    Context& theContext = Context::GetContext(argc, argv);

    if (!theContext) {
	delete &theContext;
	exitCode = EXIT_FAILURE;
    } else {
[!if ADDOBJS]
	IlvDisplay* display = theContext.getDisplay();
	IlvGrapher* grapher = theContext.getGrapher();
	// Adds some nodes in the grapher.
	IlvFilledRectangle* rect1 =
	    new IlvFilledRectangle(display, FilledRectangle1Size);
	if (!rect1) {
	    IlvCErr << "Can't build the first node.\n";
	} else {
	    grapher->addNode(rect1);
	}
	IlvFilledRectangle* rect2 =
	    new IlvFilledRectangle(display, FilledRectangle2Size);
	if (!rect2) {
	    IlvCErr << "Can't build the second node.\n";
	} else {
	    grapher->addNode(rect2);
	}
	IlvFilledEllipse* ellipse1 =
	    new IlvFilledEllipse(display, FilledEllipse1Size);
	if (!ellipse1) {
	    IlvCErr << "Can't build the third node.\n";
	} else {
	    grapher->addNode(ellipse1);
	}
	IlvFilledEllipse* ellipse2 =
	    new IlvFilledEllipse(display, FilledEllipse2Size);
	if (!ellipse2) {
	    IlvCErr << "Can't build the fourth node.\n";
	} else {
	    grapher->addNode(ellipse2);
	}

[!if ADDLINKS]
	// Adds some links to connect the nodes.
	if (rect1 && rect2) {
	    IlvOneLinkImage* link =
		new IlvOneLinkImage(display,
				    IlvVerticalLink,
				    IlvTrue,
				    rect1,
				    rect2);
	    if (!link) {
		IlvCErr << "Can't build the first link.\n";
	    } else {
		grapher->addLink(link);
	    }
	}
	if (ellipse1 && ellipse2) {
	    IlvOneLinkImage* link = new IlvOneLinkImage(display,
							IlvVerticalLink,
							IlvTrue,
							ellipse2,
							ellipse1);
	    if (!link) {
		IlvCErr << "Can't build the second link.\n";
	    } else {
		grapher->addLink(link);
	    }
	}
[!endif]
[!endif]

[!if ADDLINKS]
	// Adds some free links in the grapher.
	IlvGraphic* ghost1;
	IlvGraphic* ghost2;
	IlvGraphic* ghost3;
	IlvGraphic* ghost4;
	ghost1 = grapher->addGhostNode(IlvPoint( 10, 400));
	if (!ghost1) {
	    IlvCErr << "Can't build the first ghost node.\n";
	} else {
	    ghost2 = grapher->addGhostNode(IlvPoint(100, 450));
	    if (!ghost2) {
		IlvCErr << "Can't build the second ghost node.\n";
	    } else {
		IlvOneLinkImage* link =
		    new IlvOneLinkImage(display,
					IlvVerticalLink,
					IlTrue,
					ghost1,
					ghost2);
		if (!link) {
		    IlvCErr
			<< "Can't build the first link between ghost nodes.\n";
		} else {
		    grapher->addLink(link);
		}
	    }
	}
	ghost3 = grapher->addGhostNode(IlvPoint(100, 500));
	if (!ghost3) {
	    IlvCErr << "Can't build the third ghost node.\n";
	} else {
	    ghost4 = grapher->addGhostNode(IlvPoint(400, 450));
	    if (!ghost4) {
		IlvCErr << "Can't build the second ghost node.\n";
	    } else {
		IlvOneLinkImage* link =
		    new IlvOneLinkImage(display,
					IlvVerticalLink,
					IlTrue,
					ghost3,
					ghost4);
		if (!link) {
		    IlvCErr
			<< "Can't build the second link between ghost nodes.\n";
		} else {
		    grapher->addLink(link);
		}
	    }
	}
[!endif]

	// Adds your specific code here.
    
	// Runs the event loop.
	IlvMainLoop();
    }

    return exitCode;
}
