// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/mainwitf.h
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
// Declaration of the IlvDvMainWindowInterface class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Mainwitf_H)
#define __Ilv_Appframe_Mainwitf_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class ILVDVCLASS IlvDvInterface;
class ILVDVCLASS IlvDvDocViewInterface;
class ILVDVCLASS IlvDvContainerHandler;
class ILVDVCLASS IlvDvDocTemplate;
class ILVDVCLASS IlvDvStringArray;
class ILVDVCLASS IlvDvApplication;
class ILVDVCLASS IlvDvOptions;
class ILVDVCLASS IlvDvActionManager;
class ILVDVCLASS IlvDvBarSet;
class ILVDVCLASS IlvDvViewContainerInterface;

class ILVGDTEXPORTED IlvToolBar;
class ILVGDTEXPORTED IlvAbstractMenu;
class ILVGDTEXPORTED IlvMenuItem;
class ILVGDTEXPORTED IlvGadgetContainer;
class ILVGDTEXPORTED IlvGadgetItem;

// --------------------------------------------------------------------------
// IlvDvMainWindowInterface class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvMainWindowInterface : public IlvDvInterface
{
public:
    // ----------------------------------------------------------------------
    // Main overridables
    virtual void	initialize();
    virtual void	showWindow(IlBoolean show = IlTrue);

    // ----------------------------------------------------------------------
    // Bars management

    // Bar set management
    virtual void	dockBarSet(IlvDvBarSet* barSet,
				   IlBoolean update = IlTrue) = 0;
    virtual void	removeBarSet(const IlvDvBarSet* barSet,
				     IlBoolean update = IlTrue) = 0;
    virtual void	saveConfiguration(const IlvDvBarSet& barSet);
    virtual IlvToolBar*	getToolBar(const IlSymbol* barName) const = 0;

    // Menu bar management
    virtual IlvToolBar*	getMenuBar() const = 0;
    virtual void	setStatusLabel(const char* text);
    virtual IlBoolean	isUsingBigIcons() const;
    virtual IlBoolean	isShowingTooltips() const;
    virtual IlBoolean	withShortcuts() const;

    // ----------------------------------------------------------------------
    // Specific Doc / View processing
    virtual
    IlvDvDocViewInterface*	getActiveView() const;
    virtual IlvDvContainerHandler*
		createContainerHandler(IlvDvDocTemplate* docTpl,
				       IlUInt viewTemplateIndex = 0) const = 0;
    virtual IlvDvViewContainerInterface* getActiveViewContainer() const = 0;

    // ----------------------------------------------------------------------
    // Specific window processing
    virtual
    IlvGadgetContainer*	getGadgetContainer() = 0;
    virtual
    const IlvGadgetContainer*	getGadgetContainer() const = 0;

    // ----------------------------------------------------------------------
    // Specific menu item management
    virtual IlUShort	findMenuItemByPath(const char* path,
					   IlvAbstractMenu** = 0) const;
    IlvToolBar*		getToolBarByPath(IlvString&) const;
    virtual void	removeMenuItem(IlvAbstractMenu* parent,
				       IlUShort index,
				       IlBoolean deleteIt = IlTrue);
    virtual
    IlvMenuItem*	insertMenuItem(IlvAbstractMenu* parent,
				       IlUShort index,
				       IlvMenuItem* menuItem,
				       IlAny owner = 0);
    virtual
    IlvMenuItem*	replaceMenuItem(IlvAbstractMenu* parent,
					IlUShort index,
					IlvMenuItem* menuItem,
					IlAny owner = 0);
    virtual void	cleanMenuByOwner(IlvAbstractMenu* menu,
					 IlAny owner,
					 IlBoolean bDelete = IlFalse);
    virtual
    IlvDvActionManager*	getActionManager() const;

    // ----------------------------------------------------------------------
    // Action processing

    IlvDvDeclareInterface();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual
    IlvDvApplication*	getDvApplication() const = 0;
    virtual void	setDvApplication(IlvDvApplication* application) = 0;

    // ----------------------------------------------------------------------
    // External windows interfaces
    virtual
    IlvDvInterface*	getExternalWindow(IlUInt nWindow) const;
    virtual IlUInt	getExternalWindowsCount() const;

    // ----------------------------------------------------------------------
    // IO
    virtual void	readOptions(const IlvDvOptions* options);
    virtual void	updateOptions(IlvDvOptions* options);

    // ----------------------------------------------------------------------
    // Statics
    static IlvMenuItem*	FindMenuItemByAction(IlvAbstractMenu* parent,
					     const IlSymbol* actionName,
					     IlvAbstractMenu** foundParent);
    static IlBoolean	IsBarDocked(const IlvToolBar*);
    static IlBoolean	IsPrivateItem(const IlvGadgetItem*);
    static IlSymbol*	_OwnerProperty;
    static IlSymbol*	_BarNameSymbol;
    static IlSymbol*	_ReplaceMenuItemSymbol;
    static IlSymbol*	_BarPanedSymbol;
    static IlSymbol*	_ActionNameSymbol;

    static void		SetBarName(IlvAbstractMenu*, const char* name);
    static IlSymbol*	GetBarName(IlvAbstractMenu*);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(mainwitf);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Mainwitf_H */
