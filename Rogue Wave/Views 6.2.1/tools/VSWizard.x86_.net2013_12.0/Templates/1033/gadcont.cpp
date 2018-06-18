#include <ilviews/gadgets/gadcont.h>
#include <ilviews/base/error.h>
[!if GADCONTBUTTON]
#include <ilviews/gadgets/button.h>
[!endif]
[!if GADCONTRECT]
#include <ilviews/gadmgr/rectscmg.h>
[!endif]

static char const ApplyName[]   = "[!output PROJECT_NAME]";
static char const ViewName[]    = "MyGadgetContainer";
[!if GADCONTBUTTON]
static char const ButtonLabel[] = "Click me!";
[!endif]
static IlvRect const ViewSize(10, 10, 800, 600);
[!if GADCONTBUTTON]
static IlvRect const ButtonSize(10, 10, 100, 25);
[!endif]
[!if GADCONTRECT]
static IlvRect const ManagerRectangleSize(10, 50, 500, 400);
[!endif]

[!if GADCONTBUTTON]
// ------------------------------------------------------------------------
// The button callback.
static void
ButtonCallback(IlvGraphic* /* theButton */, IlvAny /* userArg */)
{
    // Add your code here.
    IlvCOut << "click me callback.\n";
}
[!endif]

[!if MYCLASS]
// ------------------------------------------------------------------------
// An IlvGadgetContainer subclass.
class MyIlvGadgetContainer : public IlvGadgetContainer
{
public:
    MyIlvGadgetContainer(IlvAbstractView* parent,
                         const IlvRect&   size,
                         IlvBoolean       useacc  = IlvFalse,
                         IlvBoolean       visible = IlvTrue);
    MyIlvGadgetContainer(IlvDisplay*    display,
                         IlvSystemView  parent,
                         const IlvRect& size,
                         IlvBoolean     useacc  = IlvFalse,
                         IlvBoolean     visible = IlvTrue);
    MyIlvGadgetContainer(IlvDisplay*    d,
                         IlvSystemView  available,
                         IlvBoolean     useacc = IlvFalse);
    MyIlvGadgetContainer(IlvDisplay*    d,
                         const char*    name,
                         const char*    title,
                         const IlvRect& size,
                         IlvBoolean     useacc = IlvTrue,
                         IlvBoolean     visible = IlvTrue);
    MyIlvGadgetContainer(IlvDisplay*    d,
                         const char*    name,
                         const char*    title,
                         const IlvRect& size,
                         IlvUInt        properties,
                         IlvBoolean     useacc  = IlvTrue,
                         IlvBoolean     visible = IlvTrue,
                         IlvSystemView  transientFor = 0);

    virtual IlvBoolean dispatchToObjects(IlvEvent& event);
    virtual void handleInput(IlvEvent& event);
    virtual void handleResize(IlvRect& rect);
};

// ------------------------------------------------------------------------
inline
MyIlvGadgetContainer::MyIlvGadgetContainer(IlvAbstractView* parent,
					   const IlvRect&   size,
					   IlvBoolean       useacc,
					   IlvBoolean       visible)
: IlvGadgetContainer(parent, size, useacc, visible)
{
}

// ------------------------------------------------------------------------
inline
MyIlvGadgetContainer::MyIlvGadgetContainer(IlvDisplay*    display,
					   IlvSystemView  parent,
					   const IlvRect& size,
					   IlvBoolean     useacc,
					   IlvBoolean     visible)
: IlvGadgetContainer(display, parent, size, useacc, visible)
{
}

// ------------------------------------------------------------------------
inline
MyIlvGadgetContainer::MyIlvGadgetContainer(IlvDisplay*    d,
					   IlvSystemView  available,
					   IlvBoolean     useacc)
: IlvGadgetContainer(d, available, useacc)
{
}

// ------------------------------------------------------------------------
inline
MyIlvGadgetContainer::MyIlvGadgetContainer(IlvDisplay*    d,
					   const char*    name,
					   const char*    title,
					   const IlvRect& size,
					   IlvBoolean     useacc,
					   IlvBoolean     visible)
: IlvGadgetContainer(d, name, title, size, useacc, visible)
{
}

// ------------------------------------------------------------------------
inline
MyIlvGadgetContainer::MyIlvGadgetContainer(IlvDisplay*    d,
					   const char*    name,
					   const char*    title,
					   const IlvRect& size,
					   IlvUInt        properties,
					   IlvBoolean     useacc,
					   IlvBoolean     visible,
					   IlvSystemView  transientFor)
: IlvGadgetContainer(d, name, title, size, properties, useacc, visible)
{
}

// ------------------------------------------------------------------------
IlvBoolean
MyIlvGadgetContainer::dispatchToObjects(IlvEvent& event)
{
    return IlvGadgetContainer::dispatchToObjects(event);
}

// ------------------------------------------------------------------------
void
MyIlvGadgetContainer::handleInput(IlvEvent& event)
{
    IlvGadgetContainer::handleInput(event);
}

// ------------------------------------------------------------------------
void
MyIlvGadgetContainer::handleResize(IlvRect& rect)
{
    IlvGadgetContainer::handleResize(rect);
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
    MyIlvGadgetContainer*	getContainer() const;
[!else]
    IlvGadgetContainer*		getContainer() const;
[!endif]

private:
    Context(int argc, char* argv[]);
    // Intentionally not defined.
    Context(Context const&);
    // Intentionally not defined.
    Context& operator=(Context const&);
    void			clean();
    static void			DestroyCB(IlvView* view, IlAny userArg);

[!if MYCLASS]
    MyIlvGadgetContainer*	_container;
[!else]
    IlvGadgetContainer*		_container;
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
    return _container ? IlFalse : IlTrue;
}

// -------------------------------------------------------------------------
IlvDisplay*
Context::getDisplay() const
{
    return _container->getDisplay();
}

// -------------------------------------------------------------------------
[!if MYCLASS]
MyIlvGadgetContainer*
[!else]
IlvGadgetContainer*
[!endif]
Context::getContainer() const
{
    return _container;
}

// -------------------------------------------------------------------------
Context::~Context()
{
    clean();
}

// -------------------------------------------------------------------------
Context::Context(int argc, char* argv[])
: _container(0)
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
[!if MYCLASS]
    _container =
	new MyIlvGadgetContainer(display, ViewName, ApplyName, ViewSize);
[!else]
    _container =
	new IlvGadgetContainer(display, ViewName, ApplyName, ViewSize);
[!endif]
    if (!_container) {
	IlvCErr << "Can't build the container.\n";
	delete display;
	return;
    }
    _container->setDestroyCallback(DestroyCB, this);
}

// -------------------------------------------------------------------------
void
Context::clean()
{
    if (_container) {
	// The display deletes all the views.
	delete _container->getDisplay();
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
[!if GADCONTBUTTON]
	IlvDisplay* display = theContext.getDisplay();
	IlvGadgetContainer* container = theContext.getContainer();
	// Adds a button and its callback.
	IlvButton* button = new IlvButton(display, ButtonLabel, ButtonSize);
	container->addObject(button);
	button->setCallback(ButtonCallback);
[!endif]

[!if GADCONTRECT]
	IlvSCManagerRectangle* rect =
	    new IlvSCManagerRectangle(display, ManagerRectangleSize);
	container->addObject(rect);
	//IlvManager* manager = rect->getManager();
	//IlvView* view = rect->getView();
[!endif]

	// Add your specific code here.
    
	// Runs the event loop.
	IlvMainLoop();
    }

    return exitCode;
}
