// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/script/script.h
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
// Declaration of the dialog commands classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Script_Script_H)
#define __Ilv_Appframe_Script_Script_H

#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif

#if !defined(ILVNOSCRIPT)
#if !defined(__ILJSCRIPT_hvalueH)
#include <iljscript/hvalue.h>
#endif

class IlvDvAppScript;
class IlvDvDocTemplate;
class IlvDvApplication;
class IlvDvScriptProjectDocument;
class IlvDvTextScriptDocument;
class IlvDvTextMark;
class ILJEXPORTED_ILJS IljCommandThunk;
class ILJEXPORTED_ILJS IljCallFrame;
// --------------------------------------------------------------------------
// IljDvInterfaceValue class
// --------------------------------------------------------------------------
class ILVDVCLASS IljDvInterfaceValue : public IljHValue
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IljDvInterfaceValue(IljVirtualMachine* vm, IlvDvInterface*);
    ~IljDvInterfaceValue();

    // ----------------------------------------------------------------------
    // Redefinition of virtual methods
    IljStatus		getNamedProperty(const IljHSymbolPtr& name,
					 IljHValuePtr& res);
    IljStatus		setNamedProperty(const IljHSymbolPtr& name,
					 const IljHValuePtr& val);
    IljStatus		putNamedProperty(const IljHSymbolPtr& name,
					 const IljHValuePtr& val);
    IljStatus		deleteNamedProperty(const IljHSymbolPtr& name);
    IljStatus		getPropIterator(IljHPropIteratorPtr& res);
    void		getTypeOf(IljHStringPtr& res);
    IljStatus		toStringDefault(IljHStringPtr& res);
    inline IlvDvInterface*	getInterface() const { return _interf; }

protected:
    IlvDvInterface*	_interf;
    IlArray		_members;

    IlvDvMember*	getMember(IlUInt) const;
    IljStatus		getHValue(IlvDvMember*, IljHValuePtr& res);
    virtual IljStatus	getObjectHValue(const IlSymbol*,
					const IlvValue&,
					IljHValuePtr& res) const;
    IljStatus		setFieldValue(IlvDvFieldMember*,
				      const IljHValuePtr& val) const;
    virtual IljStatus	setObjectHValue(const IlSymbol*,
					const IlvValue&,
					const IljHValuePtr& res) const;
public:
    static IljHStringPtr*	_TypeOfString;
    static void		EnsureTypeOfString(IljVirtualMachine* vm);
    static IlBoolean	IsInterfaceType(IljVirtualMachine* vm,
					const IljHStringPtr&);
};

// --------------------------------------------------------------------------
// class IlvDvSourceDesc
// --------------------------------------------------------------------------
#if !defined(__ILJSCRIPT_cinputH)
#include <iljscript/cinput.h>
#endif
class ILVDVCLASS IljDvSourceDesc : public IljHSourceDesc
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IljDvSourceDesc(IljVirtualMachine* vm,
		    const char* path,
		    IlvDvAppScript* app);

    // ----------------------------------------------------------------------
    // Overridables
    virtual int		getSourceType(); // return ILJ_SRC_FILE
    virtual void	printSourceDesc(ILJ_STD ostream& s);

    inline const char*	getPathName() const { return (const char*)_pathName; }

protected:
    IlString		_pathName;
    IlvDvAppScript*	_app;
};

// --------------------------------------------------------------------------
// IlvDvRunningContext class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvRunningContext : public IlvDvInterface
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvRunningContext(IlvDvAppScript* appScript);
    virtual ~IlvDvRunningContext();

    // ----------------------------------------------------------------------
    // Main operations
    IljCommandThunk*	compile(const char* filename) const;
    IljCommandThunk*	compileBuffer(const char* buffer,
				      const char* filename = 0) const;
    IlBoolean		execute(const char* filename, const char* buffer = 0);
    IlBoolean		execute(IljCommandThunk* thunk,
				IlBoolean canDelete = IlTrue);
    IlBoolean		pause(IlBoolean bPause = IlTrue,
			      IlBoolean updateGUI = IlTrue);
    IlBoolean		continueRunning();

    IlBoolean		stepInto();
    IlBoolean		stepOver();
    IlBoolean		stepOut();
    IlBoolean		stop();

    // ----------------------------------------------------------------------
    // Basic attributes
    IljVirtualMachine*	getVM() const;
    inline IlvDvAppScript*	getAppScript() const { return _appScript; }
    inline void		setAppScript(IlvDvAppScript* script)
			{
			    _appScript = script;
			}
    inline IlBoolean	isRunning() const { return _thunk? IlTrue : IlFalse; }
    inline IlBoolean	isStepByStep() const { return _stepByStep; }
    inline void		setStepByStep(IlBoolean stepByStep)
			{
			    _stepByStep = stepByStep;
			}
    inline IlBoolean	isPaused() const { return _paused; }
    inline IlBoolean	isStopped() const { return _isStopped; }
    IlvDisplay*		getDisplay() const;

    void		removeStopHook();
    void		removeStepIntoHook();
    void		removeStepOverHook();
    void		removeStepOutHook();
    void		doUpdateRunningScriptUI();

    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

protected:
    IlvDvAppScript*	_appScript;
    IljCommandThunk*	_thunk;
    IlBoolean		_paused;
    IlBoolean		_stepByStep;
    IlBoolean		_isStopped;
    class IljDvStopPressedHook*	_stopHook;
    class IljDvStepIntoHook*	_stepIntoHook;
    class IljDvStepOverHook*	_stepOverHook;
    class IljDvStepOutHook*	_stepOutHook;

    void		stepUI(IlvDvActionDescriptor*);
    void		pauseUI(IlvDvActionDescriptor*);
    void		stopUI(IlvDvActionDescriptor*);

    IlvDvApplication*	getDvApplication() const;
    void		doUpdateScriptUI();
};

// --------------------------------------------------------------------------
// class IljGraphicIde
// --------------------------------------------------------------------------
#if !defined(__ILJSCRIPT_ideH)
#include <iljscript/ide.h>
#endif
class IlvGraphic;
class ILVDVCLASS IljDvIde : public IljIde
{
public:
    // ----------------------------------------------------------------------
    // Constructors / destructors
    IljDvIde(IljVirtualMachine* vm, IlvDvApplication* app);
    ~IljDvIde();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	trapRuntimeError(IljRuntimeError* error); 
    virtual IljBoolean	trapInterruption();
    virtual IljStatus	writeStdOut(const char* str);

    // ----------------------------------------------------------------------
    // Basic properties
    inline IljVirtualMachine*	getVM() const { return _vm; }
    IlvDisplay*			getDisplay() const;
    inline IlvDvApplication*	getDvApplication() const { return _app; }
    inline IlBoolean		getDebuggerMode() const
				{
				    return _debuggerMode;
				}
    inline void			setDebuggerMode(IlBoolean bSet)
				{
				    _debuggerMode = bSet;
				}
    inline IlBoolean	isShowingBreakPoints() const
			{
			    return getDebuggerMode();
			}

    void		removeStopMark();
    inline void		setRunningContext(IlvDvRunningContext* runningContext)
			{
			    _runningContext = runningContext;
			}
    void		selectFrame(IljCallFrame* frame);
    // Called by the document when destroying
    void		documentDestroyed(IlvDvTextScriptDocument*);

protected:
    IljVirtualMachine*		_vm;
    IlvDvApplication*		_app;
    IlBoolean			_debuggerMode;
    IlvDvRunningContext*	_runningContext;

    // Mark methods
    IlvDvTextScriptDocument*	_markedDoc;
    IlvDvTextMark*		_mark;

    void		setStopMark(IlvDvTextMark*, IlvDvTextScriptDocument*);

    class IljListenerSourceManager*	_listenerSourceManager;

    IljBoolean		popErrorMessage(IljRuntimeError* error,
					IljBoolean canDebug);

    void		putStopMark(const IljHSourceDescPtr& src, int lineno);
};

// --------------------------------------------------------------------------
// class IlvDvAppScript
// --------------------------------------------------------------------------
class IljCompilerError;
class IljErrorList;
class IljDvIde;
class ILVDVCLASS IlvDvAppScript : public IlvDvInterface
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvAppScript(IlvDvApplication*);
    virtual ~IlvDvAppScript();

    // ----------------------------------------------------------------------
    // Error handling
    void		cleanErrors(); 
    void		printErrors(IljErrorList&);
    // ----------------------------------------------------------------------
    IljVirtualMachine*	getVM() const;
    void		getEnvironment(IljHEnvironmentPtr&);
    inline IlvDvApplication*	getDvApplication() const { return _app; }
    IljDvIde*		getIde() const;
    IlvDvScriptProjectDocument*	getActiveScriptProject() const;
    inline IlvDvRunningContext*	getRunningContext() const
				{
				    return _runningContext;
				}

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_AppScriptSymbol;
    static IlSymbol*		_ScriptTemplateSymbol;
    static IlSymbol*		_ProjectScriptTemplateSymbol;
    static IlSymbol*		_ScriptCategory;

    IlvDvDeclareInterface();

protected:
    IlvDvApplication*		_app;
    IlvDvRunningContext*	_runningContext;

    IlBoolean		initializeScript();
    void		initializeDocTemplate();
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(script);
// --------------------------------------------------------------------------
#endif /* !ILVNOSCRIPT */
#endif /* !__Ilv_Appframe_Script_Script_H */
