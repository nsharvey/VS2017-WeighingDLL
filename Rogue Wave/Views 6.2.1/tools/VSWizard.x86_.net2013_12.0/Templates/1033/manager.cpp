#include <ilviews/manager/manager.h>
#include <ilviews/base/error.h>
[!if INTERMANAGER]
#include <ilviews/manager/selinter.h>
[!endif]
[!if OBSERVER]
#include <ilviews/manager/observer.h>
#include <ilviews/manager/layer.h>
[!endif]
[!if ADDOBJS]
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/ellipse.h>
[!endif]

// -------------------------------------------------------------------------
static char const ApplyName[]	= "[!output PROJECT_NAME]";
static char const ViewName[]	= "MyManager";
static IlvRect const ViewSize(10, 10, 800, 600);
[!if ADDOBJS]
static IlvRect const FilledRectangleSize(10, 10, 100, 25);
static IlvRect const FilledEllipseSize(200, 200, 100, 25);
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
    // Notification on the manager itself.
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
    // Notification on manager view.
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
    // Notification on manager contents.
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
    // Notification on manager layer.
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
    // Notification on object geometry
    case IlvMgrMsgObjectGeometry: {
	IlvCOut << "Object geometry notification.\n";
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
// IlvManager subclass
class MyIlvManager : public IlvManager
{
public:
    MyIlvManager(IlvDisplay*	display,
		 int		layers		= 2,
		 IlBoolean	useAccelerators	= IlTrue,
		 IlUShort	maxInList	= IlvMaxObjectsInList,
		 IlUShort	maxInNode	= IlvMaxObjectsInList);
};

// -------------------------------------------------------------------------
inline
MyIlvManager::MyIlvManager(IlvDisplay*	display,
			   int		layers,
			   IlBoolean	useAccelerators,
			   IlUShort	maxInList,
			   IlUShort	maxInNode)
: IlvManager(display, layers, useAccelerators, maxInList, maxInNode)
{
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
    MyIlvManager*		getManager() const;
[!else]
    IlvManager*			getManager() const;
[!endif]
    IlvView*			getView() const;
[!if INTERMANAGER]
    IlvSelectInteractor*	getSelectInteractor() const;
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
    MyManagerObserver*		_observer;
[!endif]
[!if INTERMANAGER]
    IlvSelectInteractor*	_selectInteractor;
[!endif]
[!if MYCLASS]
    MyIlvManager*		_manager;
[!else]
    IlvManager*			_manager;
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
MyIlvManager*
[!else]
IlvManager*
[!endif]
Context::getManager() const
{
    return _manager;
}

// -------------------------------------------------------------------------
IlvView*
Context::getView() const
{
    return _view;
}

[!if INTERMANAGER]
// -------------------------------------------------------------------------
IlvSelectInteractor*
Context::getSelectInteractor() const
{
    return _selectInteractor;
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
[!if INTERMANAGER]
  _selectInteractor(0),
[!endif]
  _manager(0)
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
    _manager = new MyIlvManager(display);
[!else]
    _manager = new IlvManager(display);
[!endif]
    if (!_manager) {
	IlvCErr << "Can't build the manager.\n";
	clean();
	return;
    }
    _manager->addView(_view);

[!if OBSERVER]
    // Adds an an IlvManagerObserver to the manager.
    _observer = new MyManagerObserver(_manager);
    if ( !_observer) {
	IlvCErr << "Can't build the observer.\n";
	clean();
	return;
    }
[!endif]

[!if INTERMANAGER]
    // Adds a select interactor.
    _selectInteractor = new IlvSelectInteractor(_manager, _view); 
    if (!_selectInteractor) {
	IlvCErr << "Can't build the interactor.\n";
    } else {
        _manager->setInteractor(_selectInteractor, _view);
    }
[!endif]
}

// -------------------------------------------------------------------------
void
Context::clean()
{
    if (_manager) {
	delete _manager;
    }

[!if INTERMANAGER]
    if (_selectInteractor) {
	delete _selectInteractor;
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

// -------------------------------------------------------------------------
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
	IlvManager* manager = theContext.getManager();
	// Adds some objects in the manager.
	IlvGraphic* obj =
    	    new IlvFilledRectangle(display, FilledRectangleSize);
	if (!obj) {
	    IlvCErr << "Can't build the filled rectangle.\n";
	} else {
	    manager->addObject(obj);
	}
	obj = new IlvFilledEllipse(display, FilledEllipseSize);
	if (!obj) {
	    IlvCErr << "Can't build the filled ellipse.\n";
	} else {
	    manager->addObject(obj);
	}
[!endif]

	// Add your specific code here.
    
	// Runs the event loop.
	IlvMainLoop();
    }

    return exitCode;
}
