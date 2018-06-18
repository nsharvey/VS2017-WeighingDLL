#include <ilviews/contain/contain.h>
#include <ilviews/base/error.h>

static char const ApplyName[] = "[!output PROJECT_NAME]";
static char const ViewName[]  = "MyContainer";
static IlvRect const ViewSize(10, 10, 800, 600);

// -------------------------------------------------------------------------
class Context {
public:
    static Context&		GetContext(int argc, char* argv[]);
    ~Context();
    IlBoolean			operator!() const;
    IlvDisplay*			getDisplay() const;
    IlvContainer*		getContainer() const;

private:
    Context(int argc, char* argv[]);
    // Intentionally not defined.
    Context(Context const&);
    // Intentionally not defined.
    Context& operator=(Context const&);
    void			clean();
    static void			DestroyCB(IlvView* view, IlAny userArg);

    IlvContainer*		_container;
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
IlvContainer*
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
    _container = new IlvContainer(display, ViewName, ApplyName, ViewSize);
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
	// Add your specific code here.
    
	// Runs the event loop.
	IlvMainLoop();
    }

    return exitCode;
}
