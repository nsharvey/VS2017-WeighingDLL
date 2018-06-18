// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/studio.h
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
// Declaration of IlvStudio class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Studio_H
#define __IlvSt_Studio_H

#if !defined(__IlvSt_Util_H)
#  include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#  include <ilviews/gadgets/stdialog.h>
#endif
#if !defined(__Ilv_Gadgets_Iprompt_H)
#  include <ilviews/gadgets/iprompt.h>
#endif
#if !defined(__IlvSt_Object_H)
#  include <ivstudio/object.h>
#endif
#if !defined(__IlvSt_Studapp_H)
#  include <ivstudio/studapp.h>
#endif
#if !defined(__IlvSt_Stprop_H)
#  include <ivstudio/stprop.h>
#endif
#if !defined(__Ilv_Base_PathName_H)
#  include <ilviews/base/pathname.h>
#endif

class IlvManager;
class IlvEventPlayer;
class IlvIFileSelector;
class IlvParser;
class IlvFileBrowser;

class IlvStSubscription;
class IlvStAppCode;
class IlvStStates;
class IlvStMessages;
class IlvStModes;
class IlvStInspector;
class IlvStOptions;
class IlvStSession;
class IlvStPanelHandler;
class IlvStBuffers;
class IlvStContainerInfo;
class IlvStContainerInfoSet;
class IlvStCommandDescriptor;
class IlvStApplication;
class IlvStEventSequencer;
class IlvStToolTipHandler;
class IlvStDragDrop;
class IlvStPanelDescriptor;
class IlvStSelectionHook;
class IlvStCommandBuilder;
class IlvStExtensions;
class IlvStExtension;
class IlvStHelpTool;
class IlvStHelpItem;

extern ILVSTEXPORTEDVAR(const char*) IlvNmSetUpTestApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeDeletingTestApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmNewTestApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmTestApplicationRealized;
extern ILVSTEXPORTEDVAR(const char*) IlvNmInspectObject;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPlayerStop;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSetApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeExitingStudio;

// ==========================================================================
// IlvStConfiguration class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStConfiguration : public IlvStTopPropertySet
{
public:
    IlvStConfiguration(const IlSymbol* name) : IlvStTopPropertySet(name) {}
};

class ILVSTUDIOCLASS IlvStudio : public IlvValueInterface
{
public:
    IlvStudio(IlvDisplay* display, int argc = 0, char** argv = 0);

    virtual ~IlvStudio();
    // ____________________________________________________________

    virtual void	initialize();
    virtual void	parseArguments();
    virtual void	finalizeInit();
    virtual void	mainLoop();
    IlvDisplay*		getDisplay() const;
    IlBoolean		isBad() const;
    void		addOptionFile(const char* str,
				      IlUInt ndx = (IlUInt)-1);
    inline
    IlBoolean		isInitialized() const { return _initialized; }
    IlBoolean		readProperties(ILVSTDPREF istream&);
    IlBoolean		readProperties(const char* = 0);

public:
    IlvManager*		getManager() const;

    virtual IlBoolean	readPropertyFiles();
    virtual IlBoolean	writeOptionFile(IlvStOptions* = NULL);
    virtual IlBoolean	writeOptionFile(ILVSTDPREF ostream&,
					const char* szFile,
					IlvStOptions* = NULL);
    virtual IlBoolean	writeCommandFile(IlvStPropertySet* = NULL);
    virtual IlBoolean	writeCommandFile(ILVSTDPREF ostream&,
					 const char* szFile,
					 IlvStPropertySet* = NULL);
    // --- Application ---
    inline
    IlvStApplication*	getApplicationDescriptor() const { return _appDesc; }
    inline
    IlvStApplication*	getApplication() const
			{
			    return getApplicationDescriptor();
			}
    void		setApplicationDescriptor(IlvStApplication* appliDesc);
    inline
    void		setApplication(IlvStApplication* appliDesc)
			{
			    setApplicationDescriptor(appliDesc);
			}
    // --- Objects ---
    virtual void	setSelection(IlvGraphic* obj, IlAny caller = 0);

    IlvGraphic*		getSelection() const;

    virtual void	objectSelected(IlvGraphic* obj, IlAny caller = 0);
    virtual void	addedToSelection(IlvGraphic*, IlAny caller = 0);
    virtual void	removedFromSelection(IlvGraphic*, IlAny caller = 0);
    inline
    IlvGraphic*		getInspectedObject() const
			{
			    return _inspected ? _inspected : _selection;
			}
    void		inspect(IlvGraphic* obj, IlAny caller = 0);
    virtual void	addObject(IlvGraphic* obj, IlBoolean redraw = IlFalse);
    virtual void	removeObject(IlvGraphic* obj,
				     IlBoolean redraw = IlFalse);
    virtual void	objectReshaped(IlvGraphic* ob, IlAny caller = 0);
    // --- Panels ---
    virtual void	initializePanels();
    virtual void	createPanels();
    virtual void	add(IlvStPanelHandler*);
    virtual void	remove(IlvStPanelHandler*);

    IlvStPanelHandler*	getPanel(const char* name) const;

    IlvGadgetContainer*	getMainContainer() const;

    IlvStPanelDescriptor* getPanelDescriptor(const char* name) const;
    void		addPanelDescriptor(IlvStPanelDescriptor* pdesc,
					   IlUInt rank = (IlUShort)-1);
    IlBoolean		readPanelProperties(ILVSTDPREF istream& istrm,
					    IlBoolean apply = IlTrue);
    IlBoolean		readPanelProperties(const char* fileName = 0,
					    IlBoolean apply = IlTrue);
    IlUInt		applyPanelProperties();
    inline
    IlvStToolTipHandler* getToolTipHandler() const { return _toolTipHandler; }
    inline
    IlvSystemView	getTransientFor() const { return _transientFor; }
    inline void		setTransientFor(IlvSystemView tfor)
			{
			    _transientFor = tfor;
			}
    // --- Files ---
    inline
    IlvFileBrowser*	getFileBrowser() const { return _fbrowser; }
    IlvStError*		askInputFile(const char* filter, const char*& result);
    IlvStError*		askOutputFile(const char* filter, const char*& result);
    IlvIFileSelector*	queryBitmapSelector();
    inline
    IlPathName&		getCurrentDirectory() { return _curDir; }
    inline void		setCurrentDirectory(const char* dir) { _curDir = dir; }
    inline const char*	getViewsHome() const { return _viewsHome; }
    inline void		setViewsHome(const char* str) { _viewsHome = str; }
    inline const char*	getStudioHome() const { return _studioHome; }
    inline void		setStudioHome(const char* str) { _studioHome = str; }
    virtual const char*	getStudioUserHome() const;
    inline void		setStudioUserHome(const char* str)
			{
			    _studioUserHome = str;
			}
    ILVSTDPREF ostream*	getUserHomeOStream(const char* filename,
					   IlvStString& path,
					   IlBoolean warnUser = IlTrue)const;
    virtual
    ILVSTDPREF istream*	createInputStream(const char* fname,
					  IlBoolean = IlFalse,
					  IlBoolean = IlFalse) const;
    virtual const char*	getFilePath(const char* filename,
				    IlBoolean findInPath = IlTrue) const;
    // --- Commands ---
    virtual void	initializeCommandDescriptors();
    IlvStCommandDescriptor* getCommandDescriptor(const char* name) const;
    void		addDescriptor(IlvStCommandDescriptor*);
    void		removeDescriptor(IlvStCommandDescriptor*);
    void		registerCommand(const char*, IlvStCommandBuilder*);
    void		registerCommand(const char*, IlvStCommandFunction);

    void		registerCommand(const char* name,
					IlvStCommandConstructor cmd);
    void		setCommandState(IlvStCommandDescriptor*,
					IlBoolean,
					IlAny = 0);
    void		setCommandState(const char*, IlBoolean, IlAny = 0);
    void		inhibitCommand(IlvStCommandDescriptor*,
				       IlBoolean,
				       IlAny = 0);
    void		inhibitCommand(const char*, IlBoolean, IlAny = 0);

    // --- Messages ---
    void		subscribe(const char*, IlvStSubscription*);
    void		subscribe(const char* messageName,
				  IlAny receiver,
				  IlvStMessageCallbackType);
    void		broadcast(const char* msgname,
				  IlAny caller = 0,
				  IlAny arg = 0);

    // --- Errors, warning and information messages ---
    virtual void	initializeErrors();
    virtual void	manageError(IlvStError*);
    IlvStError*		getError(const char* name);
    IlvStError*		getLastError();
    inline
    IlvStErrorHistory*	getErrorHistory() { return _errorHistory; }
    virtual void	putMessage(const char*, IlAny caller = 0);
    virtual void	popupInformation(const char*, IlvView* papa = 0) const;
    virtual void	popupWarning(const char*, IlvView* papa = 0) const;
    virtual void	popupError(const char*, IlvView* papa = 0) const;
    virtual IlBoolean	confirm(const char*, IlvView* papa = 0) const;
    inline const char*	getLastMessage() const { return _messageString; }
    virtual void	putStatusLabel(const char*, IlAny caller = 0);
    // --- Commands ---
    IlvStCommandDescriptor** getCommandDescriptors(IlUShort& count);

    IlvStError*		execute(const char* commandName,
				IlAny caller = 0,
				IlvStCommand* command = 0,
				IlAny data = 0);

    IlvStError*		execute(IlvStCommandDescriptor* codesc,
				IlAny caller = 0,
				IlvStCommand* = 0,
				IlAny arg = 0);

    IlvStCommand*	getLastCommand();
    IlvStCommandHistory* getCommandHistory() { return _commandHistory; }
    IlBoolean		readCommandDescriptors(ILVSTDPREF istream& istrm,
					       IlvStPropertySet* = NULL);
    IlBoolean		readCommandDescriptors(const char* fileName = 0,
					       IlvStPropertySet* = NULL);
    virtual IlBoolean	stringToKeyEvent(const char*,
					 IlUShort& key,
					 IlUShort& mods);
    virtual const char*	keyEventToString(IlvStString& result,
					 IlUShort key,
					 IlUShort mods);
    virtual void	initializeBitmaps();
    IlvBitmap*		getBitmap(const char* name);
    void		add(IlvBitmap* bitmap);
    inline
    IlvEventPlayer*	getPlayer() const { return _player; }

    // --- delegates ---
    IlvStOptions&	options();
    IlvStSession&	session();

    IlvStBuffers&	buffers();

    IlvStInspector&	inspector();

    IlvStModes&		modes();

    IlvStAppCode&	code();
    IlvStStates&	states();
    inline
    IlvStMessages&	messages() { return *_messages;   }
    inline
    IlvStEventSequencer& eventSequencer() { return *_eventSequencer;  }
    inline
    IlvStDragDrop&	dragDrop() { return *_dragDrop; }
    IlvStContainerInfoSet& containerInfoSet();
    inline
    IlvStContainerInfoSet* getContainerInfoSet() const
			{
			    return _containerInfoSet;
			}
    void		setContainerInfoSet(IlvStContainerInfoSet*,
					    IlBoolean owner);

    // --- test ---
    void		addContainerInfo(IlvStContainerInfo* info);

    IlvStudioApplication* makeTestApplication(IlvDisplay*,
					      const char* name,
					      IlBoolean displayOwner,
					      IlvStAppDescriptor*,
					      IlBoolean descOwner);
    void		realizeTestApplication(IlvStudioApplication* appli);
    virtual
    IlvStudioApplication* createTestApplication(IlvDisplay*,
						const char* name,
						IlBoolean displayOwner,
						IlvStAppDescriptor*,
						IlBoolean descOwner);
    void		iSetUpTestApplication(IlvStudioApplication*);
    virtual void	setUpTestApplication(IlvStudioApplication*);
    virtual void	testApplicationRealized(IlvStudioApplication*);
    inline
    IlvStudioApplication* getTestApplication() const { return _testAppli; }
    void		setTestApplication(IlvStudioApplication* tapp);
    virtual
    IlvGraphicCallback	getTestCallback(const char*) const;

    void		registerCallback(const char* name,
					 IlvGraphicCallback callback);

    void		unregisterCallback(const char* name);

    IlvGraphicCallback	getRegisteredCallback(const char* name) const;

    inline
    IlvGraphicCallback	getDefaultCallback() const { return _defaultCallback; }
    inline void		setDefaultCallback(IlvGraphicCallback cback)
			{
			    _defaultCallback = cback;
			}

    // --- internal use ---
    IlAny*		tmpPointerArray(IlUShort count);
    char*		tmpCharArray(IlUShort count);
    inline IlArray&	getDeletedObjects() { return _deletedObjects; }
    inline
    IlvStStringArray&	args() { return _args; }
    IlUInt		getArgIndex(const char*) const;
    inline IlBoolean	isInteractive() const { return _interactive; }
    void		addObjectToDelete(IlvStObject*);
    inline IlBoolean	JvScript() const { return _JvScript; }
    inline void		JvScript(IlBoolean val) { _JvScript = val; }
    inline
    IlvStConfiguration*	getConfiguration() const { return _configuration; }
    static IlSymbol*	StudioSymbol() { return _S_studio; }
    inline
    IlvStSelectionHook*	getSelectionHook() const { return _selectionHook; }

    void		executeTestFile(const char* szFileName);

    // --- Misc ---
    virtual IlBoolean	checkCIdentifier(const char* identifier,
					 IlBoolean printErr = IlTrue) const;
    virtual IlBoolean	checkCPPIdentifier(const char* identifier,
					   IlBoolean printErr = IlTrue) const;
    virtual IlBoolean	checkCallbackName(const char* identifier,
					  IlBoolean printErr = IlTrue) const;
    // value interface
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual const IlvValueTypeClass* getValueType(const IlSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_selectionValue;
    static IlSymbol*	_S_studio;

    IlvDeclareClassInfo();

protected:
    inline
    const IlvStHash&	getPanels() const { return _panels; }
    inline
    const IlHashTable&	getCommandDescriptors() const
			{
			    return _commandDescriptors;
			}
    inline
    const IlvStHash&	getCommandBuilders() const { return _commandBuilders; }
    inline IlInt	numberOfPanels() { return _panels.getLength(); }
    IlAny*		hashToArray(const IlHashTable& htbl, IlUShort& count);
    void		readMessageDatabase(IlvDisplay*);
    virtual void	writeOptionHeader(ILVSTDPREF ostream&,
					  const char* filename,
					  const char* desc,
					  IlvStOptions* = NULL);
    IlvStError*		doExecute(IlvStCommandDescriptor* codesc,
				  IlAny caller = 0,
				  IlvStCommand* = 0,
				  IlAny arg    = 0);

    IlvStConfiguration*		_configuration;
    IlvStApplication*		_appDesc;
    IlvStudioApplication*	_testAppli;
    IlvStOptions*		_options;
    IlvStSession*		_session;
    IlvStExtensions*		_extensions;
    IlvStBuffers*		_buffers;
    IlvStInspector*		_inspector;
    IlvStModes*			_modes;
    IlvStAppCode*		_code;
    IlvStStates*		_states;
    IlvStMessages*		_messages;
    IlvStToolTipHandler*	_toolTipHandler;
    IlvStSelectionHook*		_selectionHook;
    IlvStDragDrop*		_dragDrop;
    IlvStContainerInfoSet*	_containerInfoSet;
    IlBoolean			_containerInfoSetOwner;
    IlvStEventSequencer*	_eventSequencer;
    IlvStStringArray		_args;
    IlArray			_deletedObjects;
    IlHashTable			_callbacks;
    IlvGraphicCallback		_defaultCallback;
    IlvStStringArray		_optionFiles;
    IlBoolean			_initialized	ILVSTBF;
    IlBoolean			_isBad		ILVSTBF;
    IlBoolean			_interactive	ILVSTBF;
    IlBoolean			_JvScript	ILVSTBF;

private:
    IlvStHash			_panels;
    IlArray			_panelDescriptors;
    IlArray			_deferredPanelDescriptors;
    IlvStHash			_commandDescriptors;
    IlvStHash			_commandBuilders;
    IlvStHash			_bitmaps;
    IlvStCommandHistory*	_commandHistory;
    IlvStErrorHistory*		_errorHistory;
    IlUShort			_historySize;
    IlvGraphic*			_selection;
    IlvGraphic*			_inspected;
    IlUShort			_memSize;
    char*			_memBloc;
    char*			_messageString;
    IlUShort			_messageSize;
    IlvDisplay*			_display;
    IlvFileBrowser*		_fbrowser;
    IlvIFileSelector*		_bitmapsel;
    IlvEventPlayer*		_player;
    IlPathName			_curDir;
    IlvSystemView		_transientFor;
    IlvStString			_viewsHome;
    IlvStString			_studioHome;
    IlvStString			_studioUserHome;
    IlvStHelpTool*		_helpTool;

    void		registerInteractors();

    friend class IlvStModes;
    friend class IlvStBuffers;
    friend class IlvStInspector;
    friend class IlvStOptions;
    friend class IlvStCommandDescriptor;

public:
    virtual void	warn(const char* msg, IlvView* papa = 0) const
			{
			    popupWarning(msg, papa);
			}
    // --- extensions ---
    inline
    IlvStExtensions&	extensions() { return *_extensions; }
    IlvStExtension*	getExtension(const char* name) const;
    // --- Help tool ---
    inline
    IlvStHelpTool*	getHelpTool() const { return _helpTool; }
    void		setHelpTool(IlvStHelpTool*);
    IlBoolean		showHelp(IlvStHelpItem*);

    // --- Misc. Internal functions ---
    inline void		appCode(IlvStAppCode* appcode) { _code = appcode; }
    inline void		states(IlvStStates* istates) { _states = istates; }
    inline
    IlvStCallbackChecker getCallbackChecker() const
			{
			    return _callbackChecker;
			}
    inline void		setCallbackChecker(IlvStCallbackChecker func)
			{
			    _callbackChecker = func;
			}

    static IlvView*	GetSplashScreen(IlvDisplay*);

protected:

    IlvStCallbackChecker	_callbackChecker;

}; // class IlvStudio

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCommandHistory
{
public:
    IlvStCommandHistory(IlUShort max);
    virtual ~IlvStCommandHistory();
    // ____________________________________________________________
    void		empty();
    void		add(IlvStCommand* command);
    IlvStCommand*	getLastCommand();
    void		apply(IlvStCommandHistoryFunction, IlAny arg);
private:
    IlvStCommand**	_commands;
    IlUShort		_max;
    IlUShort		_currentIndex;
};

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_studio)
#endif /* IlvDECLAREINITCLASS */

#endif /* ! __IlvSt_Studio_H */
