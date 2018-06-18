// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/mainwin.h
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
// Declaration of the IlvDvDockableMainWindow class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Mainwin_H)
#define __Ilv_Appframe_Mainwin_H

#if !defined(__Ilv_Gadgets_Desktop_H)
#include <ilviews/gadgets/desktop.h>
#endif
#if !defined(__Ilv_Gadgets_Dockutil_H)
#include <ilviews/gadgets/dockutil.h>
#endif
#if !defined(__Ilv_Appframe_Mainwitf_H)
#include <ilviews/appframe/mainwitf.h>
#endif

class IlvDvViewFrame;
class IlvDvDockableMainWindow;
class IlvDvDocTemplate;
class IlvDvActionDescriptor;
class IlvDvStringArray;
class IlvDvDockingConfiguration;

#define __PATCH_FRAME_SELECTION_ON_DESTROY
#define __PATCH_MAXBUTTON_VISIBILITY 
// --------------------------------------------------------------------------
// IlvDvDesktopManager class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDesktopManager : public IlvDesktopManager
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDesktopManager(IlvView* view,
			IlvDvDockableMainWindow* mviewContainer);

    virtual void	frameSelectionChanged(IlvViewFrame* newFrame,
					      IlvViewFrame* oldFrame);

    // ----------------------------------------------------------------------
    // Virtuals inherited from IlvDvContainerHandler
    IlvDvViewFrame*	createViewFrame(IlBoolean forceMaximization = IlFalse);

    void		deleteViewFrame(IlvDvViewFrame* viewFrame);
    virtual IlBoolean	isMaximizingFrames() const;
    virtual void	setMaximizingFrames(IlBoolean = IlTrue);
    virtual void	setCurrentFrame(IlvViewFrame* frame,
					IlBoolean raise = IlTrue);
#ifdef __PATCH_MAXBUTTON_VISIBILITY
    virtual void	makeMaximizedStateButtons(IlvToolBar*);
    virtual void	makeMaximizedStateButtons(IlvGraphicHolder*,
						  IlvPos vOffset = -1,
						  IlvPos hOffset = -1);
#endif
    inline void		_setMaxButtonsVisibility(IlBoolean b)
			{
			    setMaxButtonsVisibility(b);
			}

    // ----------------------------------------------------------------------
    // Basic properties
    virtual
    IlvDvApplication*	getDvApplication() const;
    void		setFirstFramePosition(const IlvPoint&);
    void		setDeltaFramePosition(const IlvPoint&);

#ifdef __PATCH_FRAME_SELECTION_ON_DESTROY
    IlBoolean			_destroying;
#endif

protected:
    IlvPoint		_firstFramePosition;
    IlvPoint		_deltaFramePosition;
    IlvDvDockableMainWindow* _mainWindow;

    virtual IlvPoint&	getNewFramePosition(IlvPoint&);
};

// --------------------------------------------------------------------------
// IlvDvDockableMainWindow class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvDockableMainWindow
    : public IlvDockableMainWindow, public IlvDvMainWindowInterface
{
    IlvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDockableMainWindow(IlvDisplay*		display,
			    const char*		name,
			    const char*		title,
			    const IlvRect&	dims,
			    IlUInt		properties = 0,
			    IlBoolean		visible = IlTrue,
			    IlvSystemView	transientFor = 0);

    IlvDvDockableMainWindow(IlvAbstractView*	parent,
			    const IlvRect&	rect,
			    IlBoolean		visible = IlTrue);

    IlvDvDockableMainWindow(IlvDisplay*		display,
			    IlvSystemView	parent,
			    const IlvRect&	rect,
			    IlBoolean		visible = IlTrue);

    IlvDvDockableMainWindow(IlvDisplay*      display,
			    IlvSystemView    window);

    virtual ~IlvDvDockableMainWindow();

    // ----------------------------------------------------------------------
    // Multiview behavior
    void		newWindow();
    void		newWindowUI(IlvDvActionDescriptor*);
    IlBoolean		closeFrame(IlvViewFrame*);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initialize();
    virtual void	updateTitle();
    virtual void	readOptions(const IlvDvOptions*);
    virtual void	updateOptions(IlvDvOptions*);

    // ----------------------------------------------------------------------
    // Docking panes

    virtual void	dockBar(const char* name,
				IlvToolBar* bar,
				IlBoolean update = IlTrue);
    virtual void	addBar(const char* name, IlvToolBar* bar);
    virtual void	deleteBar(IlvToolBar* bar, IlBoolean update = IlTrue);

    virtual void	dockBarSet(IlvDvBarSet* barSet,
				   IlBoolean update = IlTrue);
    virtual void	addBarSet(const IlvDvBarSet* barSet);
    virtual void	removeBarSet(const IlvDvBarSet* barSet,
				     IlBoolean update = IlTrue);
    void		ensurePaneVisible(IlvPane*);
    virtual IlvToolBar*	getToolBar(const IlSymbol* name) const;
    virtual IlUInt	getToolBarsCount(const IlSymbol* barName) const;
    virtual IlBoolean	canShowInCustomizDialog(const IlSymbol* name) const;
    void		setCanShowInCustomizeDialog(const IlSymbol* name,
						    IlBoolean show= IlTrue);
    void		changePaneName(const IlSymbol* oldName,
				       const IlSymbol* newName);
    void		getPaneNames(IlvDvStringArray& names) const;
    IlBoolean		isBarVisible(IlvToolBar* bar) const;
    virtual IlBoolean	showPane(const IlSymbol* name,
				 IlBoolean visible = IlTrue);
    virtual IlBoolean	isPaneVisible(const IlSymbol* name) const;
    virtual IlBoolean	containPane(const IlSymbol* name) const;
    IlvPane*		createPaneWithFile(const char* name,
					   const char* filename,
					   const IlvDockingPaneLocation& loc,
					   const IlSymbol* showHideAction = 0);
    void		unLinkShowHideAction(IlvPane*);

    // ----------------------------------------------------------------------
    // External windows interfaces
    virtual
    IlvDvInterface*	getExternalWindow(IlUInt nWindow) const;
    virtual IlUInt	getExternalWindowsCount() const;
    void		addExternalWindow(IlvDvInterface* extWindow);
    void		removeExternalWindow(IlvDvInterface* extWindow);

    // ----------------------------------------------------------------------
    // Specific window processing
    virtual void	showWindow(IlBoolean bShow = IlTrue);

    // ----------------------------------------------------------------------
    // Status bar management
    IlvToolBar*		getStatusBar() const;
    virtual void	setStatusLabel(const char*);
    virtual IlBoolean	acceptDocking(const IlvPane*, IlUInt) const;
    void		showStatusBar(IlBoolean show);

    // Menu management
    virtual IlvToolBar*	getMenuBar() const;
    virtual IlvToolBar*	getMainToolBar() const;
    IlvMenuItem*	insertMenuSeparator(IlvAbstractMenu* parent,
					    IlUShort index);
    IlvMenuItem*	findMenuItemByAction(const IlSymbol* actionName,
					     IlvAbstractMenu** foundParent=0);

    // ----------------------------------------------------------------------
    // Basic properties
    inline
    const IlvString&	getRootTitle() const { return _rootTitle; }
    void		setRootTitle(const IlvString&,
				     IlBoolean bUpdateTitle = IlTrue);
    inline
    IlvDvDesktopManager* getDesktop() const { return _desktop; }
    virtual IlvDvContainerHandler*
		createContainerHandler(IlvDvDocTemplate* docTpl,
				       IlUInt viewTemplateIndex = 0) const;
    IlvDvViewContainerInterface* getActiveViewContainer() const;
    virtual
    IlvGadgetContainer*	getGadgetContainer();
    virtual
    const IlvGadgetContainer* getGadgetContainer() const;
    virtual
    IlvDvApplication*	getDvApplication() const;
    virtual void	setDvApplication(IlvDvApplication* app);

    IlBoolean		sortOpenedWindows() const;
    void		setSortOpenedWindows(IlBoolean sort = IlTrue);

    // ----------------------------------------------------------------------
    // Configurations
    void		setDefaultConfiguration(const IlSymbol* configName);
    void		saveCurrentConfiguration();
    virtual void	saveConfiguration(const IlvDvBarSet& barSet);
    void		addConfiguration(const IlSymbol* configName,
					 const IlSymbol* copyConfigOf = 0);
    void		ensurePaneLocation(const char* paneName,
					   const IlvDockingPaneLocation& def);

    // ----------------------------------------------------------------------
    // Big icons
    virtual IlBoolean	isUsingBigIcons() const;
    void		setBigIcons(IlBoolean = IlTrue, IlBoolean = IlTrue);
    virtual IlBoolean	isShowingTooltips() const;
    void		setShowingTooltips(IlBoolean);
    virtual IlBoolean	withShortcuts() const;
    void		setWithShortcuts(IlBoolean);

    // ----------------------------------------------------------------------
    // Exporting API
    virtual IlBoolean	processAction(const IlSymbol* actionName);

    IlvDvDeclareInterface();

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_ClientSymbol;
    static IlSymbol*	_ContainerSymbol;
    static IlSymbol*	_StatusBarSymbol;
    static IlSymbol*	_MainWindowSymbol;
    static IlSymbol*	_DefaultConfigNameSymbol;
    static IlSymbol*	_OptionDefaultMenuNameSymbol;
    static IlSymbol*	_BarRemovedSymbol;
    static IlSymbol*	_ConfigMainPanelSymbol;
    static IlSymbol*	_BarCommandsAddedSymbol;
    static IlSymbol*	_CanShowInCustomizeDlgSymbol;
    static IlSymbol*	_ContainerConfigurationClass;
    static IlSymbol*	_PaneViewerSymbol;

    static const char*	GetStatusBarSeparatorName();

protected:
    IlvDvDesktopManager* _desktop;
    IlvString		_rootTitle;
    IlvDvApplication*	_application;
    IlBoolean		_bigIcons;
    IlBoolean		_showTooltips;
    IlBoolean		_withShortcuts;

    void		updateBigIcons(IlBoolean bigIcons);
    void		refreshToolBarIcons(IlvToolBar* toolBar,
					    IlBoolean bigIcons);

    // Tiling
    void		tileHorizontaly();
    void		tileVerticaly();
    void		tile(IlvDirection);

    void		tileHorizontalyUI(IlvDvActionDescriptor* desc);
    void		tileVerticalyUI(IlvDvActionDescriptor* desc);
    void		tileUI(IlvDvActionDescriptor* desc, IlvDirection);

    // Configurations data
    IlvArray		_configurations;
    const IlSymbol*	_currentConfigName;

    IlvDvDockingConfiguration*	getCurrentConfiguration() const;
    IlvDvDockingConfiguration*	findConfiguration(const IlSymbol* cName) const;
    IlvDvDockingConfiguration*	getConfiguration(IlUInt index) const;
    void		applyConfiguration(const IlvDvDockingConfiguration&);
    virtual
    const IlSymbol*	getInitialConfigurationName() const;

    // Working with bars
    virtual IlvToolBar*	createToolBar(const IlSymbol* name) const;
    virtual void	initializeBar(const char* name, IlvToolBar* bar) const;
    virtual void	initializeBarCommandsUI(IlvToolBar*) const;
    virtual void	removeBarCommandsUI(IlvToolBar*) const;
    IlvPane*		getToolBarPane(const IlvToolBar* bar,
				       IlvDvBarSet** pBarSet = 0) const;
    IlvPane*		createPane(const IlvDvBarSet& barSet,
				   IlInt nBar) const;
    void		prepareBarsForDocking(IlvDvBarSet& barSet) const;

    // Bars
    IlvToolBar*		_statusBar;
    IlBoolean		_showStatus;
    IlvToolBar*		_menuBar;
    IlvDvBarSet*	_mainBarSet;
    IlvArray		_attachedBarSets;
    IlvArray		_externalWindows;

    void		mergeAllBarSets(IlvDvBarSet&) const;

private:
    void		internalInitialize();

public:
    // ----------------------------------------------------------------------
    // Managing windows
    virtual void	cascade();
    virtual void	cascadeUI(IlvDvActionDescriptor*);
    virtual void	nextWindow();
    virtual void	nextWindowUI(IlvDvActionDescriptor*);
    virtual void	previousWindow();
    virtual void	previousWindowUI(IlvDvActionDescriptor*);
    virtual void	manageWindows();
    virtual void	manageWindowsUI(IlvDvActionDescriptor*);
    const char*		makeWindowTitle(IlvString&, IlUInt n,
					const char* title);
    virtual void	customize();
    // callbacks
    static void		UpdateWindowsCB(IlvGraphic* g, IlAny arg);
    static void		HighlightCB(IlvGraphic* g, IlAny arg);
    static void		SetMainWindow(IlvAbstractMenu* bar,
				      IlvDvDockableMainWindow* mainWindow);
    static
    IlvDvDockableMainWindow*	GetMainWindow(IlvAbstractMenu* bar);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(mainwin);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Mainwin_H */
