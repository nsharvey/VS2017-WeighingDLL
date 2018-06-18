// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/app.h
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
// Declaration of the IlvDvApplication class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_App_H)
#define __Ilv_Appframe_App_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Gadgets_Appli_H)
#include <ilviews/gadgets/appli.h>
#endif
#if !defined(__Ilv_Appframe_Registry_H)
#include <ilviews/appframe/registry.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif
#if !defined(__Ilv_Base_Evloop_H)
#include <ilviews/base/evloop.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#include <ilviews/util/proplist.h>
#endif

class IlvDvDocManager;
class IlvDvMainWindowInterface;
class IlvDvDocument;
class IlvDvDocTemplate;
class IlvDvContainerHandler;
class IlvDvStringArray;
class IlvDvOptions;
class IlvDvNodeValue;
class IlvDvDocViewInterface;
class IlvDvViewContainerInterface;
class IlvDvActionDescriptor;
class IlvDvModuleInfos;
class IlvDvModuleInfosArray;
class IlvDvModule;
class IlvDvActionProcessor;
class IlvDvActionManager;
class ILVDVCLASS IlvDvMenuOptionsReader;
class IlvDvDockableMainWindow;
class ILVDVCLASS IlvDvPrintManager;
class ILVDVCLASS IlvDvAction;

class IlvAbstractMenu;
class IlvPopupMenu;
class IlvToolBar;

typedef IlBoolean (*IlvDvCommandTargetCallback)(IlvDvInterface*, IlAny, IlAny);
#define _PATCH_GCONTEXT_GIVENOT_USERHOME

#ifndef COMMAND_STATE_DEFINED
#define COMMAND_STATE_DEFINED
enum IlvDvCommandState {
    Sensitive   = 0,
    Selected    = 1,
    Unsensitive = 2,
    Highlighted = 3 };
#endif /* COMMAND_STATE_DEFINED */

// --------------------------------------------------------------------------
// IlvDvApplicationStarter class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvApplicationStarter
{
public:

    IlvDvApplicationStarter(IlvDvApplication* app,
			    IlBoolean         createDoc = IlFalse,
			    const char*       ndocTemplateName = 0);
    virtual ~IlvDvApplicationStarter();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	execute();

    // ----------------------------------------------------------------------
    // Main methods
    IlUInt		getCmdLineArgumentsCount() const;
    const char*		getCmdLineArgument(IlUInt) const;
    inline
    IlvDvApplication*	getDvApplication() const { return _app; }

    // ----------------------------------------------------------------------
    // Accessors
    void		setCreateNewDocument(IlBoolean create = IlTrue,
					     const char* docTemplateName = 0);
    inline IlBoolean	canCreateNewDocument() const
			{
			    return _createNewDocument;
			}
    // ----------------------------------------------------------------------
    // Options
    void		readOptions(IlvDvOptions*);
    void		updateOptions(IlvDvOptions*);

protected:
    IlvDvApplication*	_app;
    IlBoolean		_createNewDocument;
    IlString		_newDocTemplateName;

    IlBoolean		parseCommandLine();
    IlvDvDocument*	createNewDocument();
};

// --------------------------------------------------------------------------
// IlvDvApplication class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvApplication
    : public IlvApplication, public IlvDvInterface
{
    IlvDeclareClassInfo();

public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvApplication(const char* name,
		     const char* displayName,
		     int         argc = 0,
		     char**      argv = 0);
    IlvDvApplication(IlvDisplay* display,
		     const char* name,
		     IlBoolean   owner = IlFalse);
    virtual ~IlvDvApplication();

    void		hideApplication();

    // ----------------------------------------------------------------------
    // Document management
    virtual IlBoolean	saveAllModifiedDocs(); // save before exit

    // close documents before exiting
    virtual IlBoolean	closeAllDocuments(IlBoolean endSession = IlFalse);
    virtual IlBoolean	closeCurrentDocument();

    // ----------------------------------------------------------------------
    // Document template management
    virtual void	addDocTemplate(IlvDvDocTemplate* tpl);

    IlUInt		getDocTemplatesCount() const;

    IlvDvDocTemplate*	getDocTemplate(IlUInt index) const;

    IlvDvDocTemplate*	findDocTemplate(const char* name) const;
    IlBoolean		removeTemplates(IlvDvModule* = 0);

    // ----------------------------------------------------------------------
    // Dealing with files
    virtual
    IlvDvDocument*	openDocument();

    virtual
    IlvDvDocument*	openDocumentFile(const char* filename,
					 IlBoolean createWindow = IlTrue,
					 IlBoolean addToROL = IlTrue);
    virtual
    IlvDvDocument*	newDocument();
    virtual
    IlvDvDocument*	newDocument(const char* templateName, IlAny data = 0);
    virtual
    IlvDvDocument*	newDocument(IlvDvDocTemplate* tpl, IlAny data = 0);
    virtual IlBoolean	saveCurrentDocument();
    virtual IlBoolean	saveDocument(const char* filename);
    virtual IlBoolean	saveAsCurrentDocument();
    virtual const char*	getFullPathName(const char* pathname) const;
    IlvDvDocument*	findDocument(const char* filename) const;
    virtual IlUInt	getOpenedDocumentCount() const;
    void		openRecentOpenedFile(IlUInt nFile);
    const char*		getRecentOpenedFile(IlUInt nFile) const;
    const char*		getRecentOpenedFileMenuString(IlUInt,
						      IlString&) const;
    IlUInt		getRecentOpenedFilesCount() const;
    virtual void	addToRecentFileList(const IlPathName&);  // add to MRU

    // ----------------------------------------------------------------------
    // Active document
    inline
    IlvDvDocument*	getActiveDocument() const
			{
			    return _activeDocument;
			}
    void		setActiveDocument(IlvDvDocument*,
					  IlBoolean activateView = IlFalse);
    void		activeViewChanged(IlvDvDocViewInterface*);

    IlvDvDocViewInterface*	getActiveView() const;
    IlvDvViewContainerInterface*	getActiveViewContainer() const;

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void	run();
    virtual void	makePanels();
    virtual void	beforeRunning();

    virtual void	initialize();
    virtual void	quit();

    // ----------------------------------------------------------------------
    // Registry management
    inline IlBoolean	writeRegistry(const IlvDvRegistryKey& k,
				      const char* subk,
				      const IlvDvValue& val) const
			{
			    return _registryProcessor.writeRegistry(k,
								    subk,
								    val);
			}

    inline IlBoolean	readRegistryInt(const IlvDvRegistryKey& k,
					const char* subk,
					int& n,
					int defVal = 0) const
			{
			    return _registryProcessor.readRegistryInt(k,
								      subk,
								      n,
								      defVal);
			}

    inline IlBoolean	readRegistryString(const IlvDvRegistryKey& k,
					   const char* subk,
					   IlString& s,
					   const char* defVal = 0) const
			{
			    return
				_registryProcessor.readRegistryString(k,
								      subk,
								      s,
								      defVal);
			}

    inline IlBoolean	getRegistryKeys(const IlvDvRegistryKey& k,
					const char* subk,
					IlvDvStringArray& subks) const
			{
			    return _registryProcessor.getRegistryKeys(k,
								      subk,
								      subks);
			}
    inline IlBoolean	writeRegistryKeys(const IlvDvRegistryKey& k,
					  const char* subk,
					  const IlvDvStringArray& subks) const

			{
			    return
				_registryProcessor.writeRegistryKeys(k,
								     subk,
								     subks);
			}
    inline IlBoolean	delRegistryTree(const IlvDvRegistryKey& key,
					const char* subKey)
			{
			    return _registryProcessor.delRegistryTree(key,
								      subKey);
			}
    inline void		unregisterAll() { _registryProcessor.unregisterAll(); }
    inline void		setAppRegistryRootName(const char* name)
			{
			    _registryProcessor.setRootName(name);
			}
    inline void		setProfileName(const char* name)
			{
			    _registryProcessor.setProfileName(name);
			}
    inline
    const IlString&	getProfileName() const
			{
			    return _registryProcessor.getProfileName();
			}

    inline
    const IlvDvRegistryProcessor& getRegistryProcessor() const
			{
			    return _registryProcessor;
			}

    // ----------------------------------------------------------------------
    virtual void	updateOptions();
    void		writeOptions();
    IlBoolean		readOptions(const char* filename);
    IlvDvNodeValue*	getOptionNode(const IlSymbol* type,
				      const IlSymbol* name) const;
    IlvDvNodeValue*	getOptionNode(const char* type,
				      const char* name) const;
    IlvDvOptions*	readOptionFile(const char* filename,
				       IlBoolean bMerge = IlTrue);
    virtual void	initializeFromOptions();
    virtual void	writeRegistries();

    inline
    const IlString&	getHomePath() const { return _homePath; }
    void		setHomePath(const IlString&);
    inline
    const IlString&	getUserOptionsFilename() const
			{
			    return _userOptionsFilename;
			}
    inline void		setUserOptionsFilename(const char* filename)
			{
			    _userOptionsFilename = filename;
			}
    inline
    const IlString&	getAppOptionsFilename() const
			{
			    return _appOptionsFilename;
			}
    inline void		setAppOptionsFilename(const char* filename)
			{
			    _appOptionsFilename = filename;
			}
    inline void		setDataBaseFilename(const char* filename)
			{
			    _dataBaseFilename = filename;
			}
    IlBoolean		readDataBase(const char* filename,
				     IlBoolean notifyError = IlTrue);
    virtual IlBoolean	readDocTemplates(IlvDvOptions*,
					 IlvDvModule* = 0,
					 IlBoolean bUpdate = IlFalse);
    IlBoolean		deleteUserOptionsFile();

    // ----------------------------------------------------------------------
    // Loading ressources
    IlBoolean		readBar(const char* menuName,
				IlvAbstractMenu* menu) const;
    IlBoolean		readMenu(const IlvDvNodeValue*,
				 IlvAbstractMenu* bar) const;

    IlvPopupMenu*	readPopup(const IlSymbol* popupName);

    void		connectMenuActions(IlvAbstractMenu* menu,
					   IlBoolean connect = IlTrue) const;

    void		refreshMenuActions(IlvAbstractMenu* menu);


    IlvGadgetItem*	loadGraphicInBar(IlvToolBar* bar,
					 const char* itemLabel,
					 const char* pathname,
					 const char* graphicName,
					 IlBoolean defaultCallbacks = IlTrue);
    IlvGadgetItem*	setGraphicInBar(IlvToolBar* bar,
					const char* itemLabel,
					IlvGraphic* graphic,
					IlBoolean defaultCallbacks = IlTrue);

    IlvGadgetItem*	findMenuItemByPath(IlvAbstractMenu* menu,
					   const char* path,
					   IlvAbstractMenu** foundParent = 0)
					   const;

    IlUShort		findMenuItemIndexByPath(IlvAbstractMenu* menu,
						const char* path,
						IlvAbstractMenu** foundParent)
						const;

    virtual IlBoolean	initializeGraphic(IlvGraphic* g);
    virtual IlBoolean	graphicNotification(IlvGraphic*     g,
					    const IlSymbol* cbName);

    // ----------------------------------------------------------------------
    // Actions managment
    virtual IlBoolean	processAction(const IlSymbol* actionName);
    virtual const char*	getActionDescription(const IlSymbol* actionName) const;
    virtual void	setActionItemBitmaps(IlvGadgetItem* gadgetItem,
					     const IlSymbol* actionName,
					     IlBoolean bigIcon=IlFalse) const;
    void		getActionCategories(const IlSymbol* actionName,
					    IlvDvStringArray&) const;
    virtual IlBoolean	refreshAction(const IlSymbol* actionName,
				      IlvDvActionDescriptor* actionDesc) const;
    virtual IlBoolean	refreshAction(const IlSymbol* actionName);
    virtual IlBoolean	refreshAction(const char* actionName);

    virtual void	refreshActions();
    virtual void	refreshActionsByCategory(const char*);
    virtual void	refreshActionsByCategory(const IlSymbol*);
    virtual IlBoolean	isActionChecked(const char*) const;
    virtual IlBoolean	isActionChecked(const IlSymbol*) const;
    virtual void	setActionChecked(const char*, IlBoolean = IlTrue);
    virtual void	setActionChecked(const IlSymbol*, IlBoolean = IlTrue);
    virtual IlBoolean	isActionValid(const char*) const;
    virtual IlBoolean	isActionValid(const IlSymbol*) const;
    virtual void	setActionValid(const char* actionName,
				       IlBoolean   valid = IlTrue);
    virtual void	setActionValid(const IlSymbol* actionName,
				       IlBoolean       valid = IlTrue);
    void		addActionProcessor(IlvDvActionProcessor* actProcess);

    void		removeActionProcessor(IlvDvActionProcessor* actProcess,
					      IlBoolean deleteIt = IlTrue);

    IlBoolean		addActionItem(const char* menuPath,
				      const IlSymbol* actionName,
				      IlBoolean after = IlTrue);
    IlBoolean		addActionItem(IlvAbstractMenu* menu,
				      IlUShort index,
				      const IlSymbol* actionName);
    IlBoolean		removeActionItem(const char* menuPath);
    void		addAction(IlvDvAction*);
    IlBoolean		removeAction(IlvDvAction*,
				     IlBoolean deleteIt = IlTrue);

    // ----------------------------------------------------------------------
    // Menu management
    void		updateRecentFileListMenu();

    // ----------------------------------------------------------------------
    // Modules management
    inline
    IlvDvModuleInfosArray*	getModuleInfosArray()
				{
				    return _modules;
				}
    void		setModuleInfosArray(IlvDvModuleInfosArray*);
    IlvDvModule*	findOptionsModule(IlvDvOptions*) const;
    void		editModules();

    // ----------------------------------------------------------------------
    // Basic properties
    inline
    IlvDvDocManager*	getDocManager() const { return _docManager; }
    inline
    IlvDvMainWindowInterface*	getMainWindow() const
				{
				    return _mainWindow;
				}
    IlvDvDockableMainWindow*	getDockableMainWindow() const;
    virtual
    const IlvGadgetContainer*	getMainContainer() const;
    IlvSystemView	getMainSystemView() const;
    inline
    IlvDvActionManager*	getActionManager() const
			{
			    return _actionManager;
			}

    virtual IlvDvContainerHandler*
			createContainerHandler(IlvDvDocTemplate* docTpl,
					       IlUInt tmplIndex = 0) const;
    inline
    IlvDvOptions*	getOptions() const { return _options; }
    inline
    IlvDvApplicationStarter*	getApplicationStarter() const
				{
				    return _starter;
				}
    void		setApplicationStarter(IlvDvApplicationStarter* st);

    void		startWithNewDocument(IlBoolean create = IlTrue,
					     const char* docTemplateName = 0);

    inline
    IlvDvMenuOptionsReader*	getMenuOptionsReader() const
				{
				    return  _menuOptionsReader;
				}
    void		setMenuOptionsReader(IlvDvMenuOptionsReader* reader);

    void		setRefreshActionIdleDelay(IlUInt delay);
    inline IlUInt	getRefreshActionIdleDelay() const
			{
			    return _refreshActionsIdleDelay;
			}
    virtual void	idle();

    static const char*	_RegistryCommandName;
    static const char*	_RegistryOptionName;
    static const char*	_RegistryOptionFileName;
    static const char*	_RegistryAppOptionFileName;
    static const char*	_RegistryUserOptionFileName;
    static const char*	_MainOptionFileName;
    static const char*	_DefaultUserOptionFileName;
    static const char*	_OptionFileNameExtention;
    static IlSymbol*	_OptionAppModulesSymbol;

    IlvDvDeclareInterface();

    static void		UseXmlOptions(IlBoolean);
    static IlBoolean	_UseXmlOptions;

    // ----------------------------------------------------------------------
    IlvDeclareBasePropertyListOwner();

protected:
    IlvDvDocManager*		_docManager;
    IlvDvMainWindowInterface*	_mainWindow;
    IlvDvDocument*		_activeDocument;
    IlvDvDocTemplate*		_activeTemplate;
    IlArray			_actionProcessors;
    IlvDvActionManager*		_actionManager;
    IlUInt			_refreshActionsIdleDelay;
    IlUInt			_idleCount;
    IlvIdleProcId		_idleProcId;

    friend class		IlvDvApplicationStarter;
    IlvDvApplicationStarter*	_starter;
    IlvDvStringArray		_cmdLineArgs;

    IlvDvOptions*		_options;
    IlvDvOptions*		_appOptions;
    IlvDvOptions*		_userOptions;
    IlString			_appOptionsFilename;
    IlString			_userOptionsFilename;
    IlString			_dataBaseFilename;
    IlvDvMenuOptionsReader*	_menuOptionsReader;
#ifdef _PATCH_GCONTEXT_GIVENOT_USERHOME
    IlString			_homePath;
#endif

    IlvDvRegistryProcessor	_registryProcessor;

    virtual void	readRegistryOptions();
    virtual void	readDocViewOptions();
    virtual void	readAppOptions();
    virtual void	readUserOptions();

    virtual IlPathName	getUserOptionsPathName() const;

    // Modules
    IlvDvModuleInfosArray*	_modules;

    // Options
    virtual
    IlvDvMainWindowInterface*	createMainWindow();

    virtual
    IlvDvDocTemplate*	createDocTemplate(const IlSymbol* app);
    virtual IlBoolean	forEachCommandTarget(IlvDvCommandTargetCallback,
					     IlAny = 0,
					     IlAny = 0) const;
    void		saveAllModifiedDocsUI(IlvDvActionDescriptor*) const;
    void		saveDocumentUI(IlvDvActionDescriptor*) const;
    virtual IlBoolean	forceHomeOptions() const;
    virtual IlBoolean	useRegistries() const;
    virtual IlBoolean	closeAll();
    void		closeDocumentUI(IlvDvActionDescriptor* desc) const;

    // Printing members
    IlvDvPrintManager*	_printerManager;
    void		print();
    void		printUI(IlvDvActionDescriptor*);
    void		pageSetup();
    void		pageSetupUI(IlvDvActionDescriptor*);
    void		printerSetup();
    void		dumpPostScript();

private:
    void		internalInitialize();
    void		initializeHomePath();

public:
    static IlBoolean	IdleProc(IlAny userArg);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(app);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_App_H */
