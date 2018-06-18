// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/menupnl.h
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
// Declaration of the IlvStIMenuBarPanel class
// Declaration of the IlvStIPopupMenuPanel class
// Declaration of the IlvStIToolBarPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Menupnl_H)
#define __IlvSt_Gadgets_Menupnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif
#if !defined(__IlvSt_Inspectors_Listedt_H)
#  include <ivstudio/inspectors/listedt.h>
#endif

class IlvStringList;
class IlvMenuBar;
class IlvToolBar;
class IlvAbstractMenu;
class IlvMenuItem;
class IlvPopupMenu;
class IlvStIPropertyTextEditor;
class IlvStICallbackInfos;

// --------------------------------------------------------------------------
// IlvStIMenuItemValue
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuItemValue
    : public IlvStIProperty
{
    IlvDeclareInspClassInfo();

public:
    IlvStIMenuItemValue(IlvMenuItem* = 0,
			const IlvAbstractMenu* = 0);
    IlvStIMenuItemValue(IlvAbstractMenu*);
    IlvStIMenuItemValue(IlvPopupMenu*, const IlvMenuItem*);
    IlvStIMenuItemValue(const IlvStIMenuItemValue&);
    virtual ~IlvStIMenuItemValue();

    // ____________________________________________________________
    virtual IlvStIProperty*	copy() const;
    virtual void		clean();

    virtual void		set(const IlvStIProperty&);
    virtual IlvValue&		getValue(IlvValue&) const;
    virtual void		setValue(const IlvValue&);

    virtual const char*		getString() const;
    virtual void		setString(const char*);

    virtual IlAny		getPointer() const;

    // ----------------------------------------------------------------------
    // Specific gadget item methods
    IlvMenuItem*		getMenuItem() const;
    void			setMenuItem(IlvMenuItem*,
					    const IlvAbstractMenu*);
    IlvAbstractMenu*		getAbstractMenu() const;
    void			setAbstractMenu(IlvAbstractMenu*);
    IlvMenuBar*			getMenuBar() const;
    IlvPopupMenu*		getPopupMenu() const;
    IlvToolBar*			getToolBar() const;

    typedef enum
    {
	NONE = -1,
	MENUBAR = 1,
	POPUP_MENU = 2,
	SEPARATOR = 3,
	TEAROFF = 4,
	MENUITEM = 0,
	TOOLBAR = 5,
	TOOLBAR_ITEM = 6,
	POPUP_ITEM = 7,
	SUBPOPUP_MENU = 8
    } Type;

    Type			getType() const { return _valueType; }
    static Type			GetMenuItemIType(const IlvMenuItem*,
						 const IlvAbstractMenu*);
    static Type			GetMenuIType(const IlvAbstractMenu*);

protected:
    union {
	IlvMenuItem*		_menuItem;
	IlvAbstractMenu*	_menu;
    } _value;
    Type			_valueType;
};

// --------------------------------------------------------------------------
// IlvStIMenuItemAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuItemAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIMenuItemAccessor(IlvStIPropertyAccessor* = 0,
			   IlvStIAccessor::UpdateMode = Inherited,
			   const char* = 0);
protected:
    IlvMenuItem*		getMenuItem() const;
};

// --------------------------------------------------------------------------
// IlvStIMenuAcceleratorAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuAcceleratorAccessor
    : public IlvStIMenuItemAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuAcceleratorAccessor(IlvStIPropertyAccessor* = 0,
				  IlvStIPropertyAccessor* = 0,
				  IlvStIAccessor::UpdateMode = Inherited,
			          const char* = 0);
    virtual ~IlvStIMenuAcceleratorAccessor();

    virtual void set(const IlvStIProperty*, IlvStIEditor*);

protected:
    IlvStIPropertyAccessor*	_accTextAcc;

    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMenuAcceleratorTextAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuAcceleratorTextAccessor
    : public IlvStIMenuItemAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuAcceleratorTextAccessor(IlvStIPropertyAccessor* = 0,
				      IlvStIAccessor::UpdateMode = Inherited,
				      const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMenuItemStateAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuItemStateAccessor
    : public IlvStIMenuItemAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuItemStateAccessor(IlvStIPropertyAccessor* = 0,
			        IlvStIAccessor::UpdateMode = Inherited,
			        const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMenuItemCallbackAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuItemCallbackAccessor
    : public IlvStIMenuItemAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuItemCallbackAccessor(IlvStIPropertyAccessor* = 0,
			           IlvStIAccessor::UpdateMode = Inherited,
			           const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIMenuItemCallbackEditor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuItemCallbackEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuItemCallbackEditor(IlvStIPropertyAccessor* = 0,
				 IlvStICallbackInfos* = 0,
				 IlvStIEditor::NotificationMode =
						       IlvStIEditor::AsOwner,
				 const char* = 0);
    virtual ~IlvStIMenuItemCallbackEditor();

    // ----------------------------------------------------------------------
    // Main overridable
    virtual IlBoolean		initialize();
    virtual IlBoolean		connectHolder(IlvGraphicHolder*);

    IlBoolean			isUsingJScript() const;

protected:
    IlvStICallbackInfos*	_callbackInfos;
    IlvStIPropertyTextEditor*	_cbEditor;
    IlvStIPropertyTextEditor*	_jsCbEditor;
    IlvStIPropertyToggleEditor*	_scriptToggle;
    IlvButton*			_btnEditScript;
    IlvGraphicHolder*		_btnHolder;

    IlvMenuItem*		getMenuItem();

public:
    // callbacks have to be public because of sun compiler
    static void			ButtonScriptCallback(IlvGraphic*, IlAny);
    static void			CheckScriptCallback(IlvGraphic*, IlAny);
    static void			NameChangedCallback(IlvGraphic*, IlAny);

protected:
    virtual void		onButtonScriptPushed();
    virtual void		onScriptChecked();
    virtual void		onNameChanged();
    void			setCallbackName(IlSymbol*);
};

// --------------------------------------------------------------------------
// class IlvStIMenuItemEditor
// --------------------------------------------------------------------------
class IlvStIMenuItemEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuItemEditor(IlvStIPropertyAccessor* = 0,
			 IlvStICallbackInfos* = 0,
			 const char* = 0,
			 NotificationMode = AsOwner);
    virtual ~IlvStIMenuItemEditor();

    // ----------------------------------------------------------------------
    // Overridable
    virtual IlBoolean		connectHolder(IlvGraphicHolder*);
};

// --------------------------------------------------------------------------
// IlvStIGadgetItemMenuAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIGadgetItemMenuAccessor
    : public IlvStIPropertyTreeAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGadgetItemMenuAccessor(IlvStIPropertyAccessor* = 0,
			         IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			         const char* = 0);
    virtual ~IlvStIGadgetItemMenuAccessor();

    // ----------------------------------------------------------------------
    // Editors managment
    virtual IlvStIEditor*	findFirstEditor() const;

    // ----------------------------------------------------------------------
    IlvAbstractMenu*	getAbstractMenu() const;

protected:

    IlvMenuItem*	getMenuItem(const IlvStIProperty*) const;
    IlvAbstractMenu*	getAbstractMenu(const IlvStIProperty*) const;
    IlvMenuItem*	getParentGadgetItem(const IlvStIProperty*) const;
    // ----------------------------------------------------------------------
    // Application

    virtual IlUInt	getChildPosition(const IlvStIProperty*,
					 const IlvStIProperty*) const;
    virtual void	addProperty(IlvStIProperty*,
				    const IlvStIProperty*,
				    IlUInt);
    virtual void	replaceProperty(IlvStIProperty*,
					IlvStIProperty*,
					const IlvStIProperty*,
					IlUInt);
    virtual void	doApply();

    // ----------------------------------------------------------------------
    // Array of properties
    virtual IlvStIProperty**
	       getInitialChildrenProperties(IlUInt&,
					    const IlvStIProperty* = 0) const;
    // ----------------------------------------------------------------------
    // Insertion of properties
    virtual
    IlvStIProperty*	createProperty(const IlvStIProperty*,
				       IlUInt,
				       IlAny = 0) const;

    // ----------------------------------------------------------------------
    // Destruction of properties
    virtual void	deleteNewProperty(IlvStIProperty*);
    virtual void	deleteChildrenProperty(IlvStIProperty*,
					       IlvStIProperty*);
    virtual void	cleanNodes();
};


// --------------------------------------------------------------------------
// IlvStIPopupMenuAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIPopupMenuAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPopupMenuAccessor(IlvStIPropertyAccessor* = 0,
			    IlvStIAccessor::UpdateMode = Inherited,
			    const char* = 0);
protected:
    IlvPopupMenu*		getPopupMenu() const;
};

// --------------------------------------------------------------------------
// IlvStITearOffAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITearOffAccessor
    : public IlvStIPopupMenuAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStITearOffAccessor(IlvStIPropertyAccessor* = 0,
			  IlvStIAccessor::UpdateMode = Inherited,
			  const char* = 0);

    static IlBoolean		IsPopupTearOff(const IlvPopupMenu*);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIPopupMenuEditor
// --------------------------------------------------------------------------
class IlvStIPopupMenuEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPopupMenuEditor(IlvStIPropertyAccessor* = 0,
			  IlBoolean = IlFalse,
			  const char* = 0,
			  NotificationMode = AsOwner);
    virtual ~IlvStIPopupMenuEditor();

    // ----------------------------------------------------------------------
protected:
    const char*			getGadgetName(const char*,
					      IlString&,
					      IlBoolean) const;
};

// --------------------------------------------------------------------------
// class IlvStIMenuItemsTreeEditor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuItemsTreeEditor
    : public IlvStIPropertyTreeEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMenuItemsTreeEditor(IlvStIPropertyAccessor* = 0,
			      const char* = 0,
		              IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIMenuItemsTreeEditor();

    // ----------------------------------------------------------------------
    virtual IlBoolean		connectHolder(IlvGraphicHolder*);
    virtual void		setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    virtual IlvGadgetItem*     createGadgetItem(const IlvStIProperty*) const;

    // ----------------------------------------------------------------------
    // Specific accessors
    IlvStIPropertyAccessor*	getSelectionAccessor() const;

protected:
    IlString			_addPopup;
    IlString			_addSeparator;

public:
    static void			AddPopupCallback(IlvGraphic*, IlAny);
    static void			AddSeparatorCallback(IlvGraphic*, IlAny);

protected:
    virtual void		addPopupCallback();
    virtual void		addSeparatorCallback();
    virtual void		treeItemSelected(IlvTreeGadgetItem*,
						 const IlvStIProperty*,
						 const IlvStIProperty*);
    const IlvStIMenuItemValue*	getMenuValue(IlAny) const;
    virtual void		addTreeItem(IlBoolean, IlAny = 0);
};

// --------------------------------------------------------------------------
// class IlvStIAbstractMenuEditor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIAbstractMenuEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();

public:
    IlvStIAbstractMenuEditor(IlvStIPropertyAccessor* = 0,
			     IlvStICallbackInfos* = 0,
			     const char* = 0,
			     IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIAbstractMenuEditor();

    IlvStIPropertyAccessor*	getMenuItemAccessor() const;
    void		      linkAbstractBarEditor(IlvStIPropertyAccessor*);
    IlvStIPropertyAccessor*	makeMenuSelectionAccessor(IlUShort) const;

protected:
    IlvStIMenuItemsTreeEditor*	_menuItemsEditor;
};

// --------------------------------------------------------------------------
// Inspector panel of Menubar
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMenuBarPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIMenuBarPanel(IlvDisplay*,
		       const char*,
		       const char* = 0,
		       IlvSystemView = 0,
		       IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridable
    virtual void		initializeEditors();
    virtual void		applyChange(IlvGraphic*);
    virtual void		initFrom(IlvGraphic*);

protected:
    void			initializeMenuPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIMenuBarPanel,
				    IlvStIMenuBarPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// Inspector panel of Popup menu
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIPopupMenuPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIPopupMenuPanel(IlvDisplay*,
		         const char*,
		         const char* = 0,
		         IlvSystemView = 0,
		         IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridable
    virtual void		initializeEditors();
    virtual void		applyChange(IlvGraphic*);
    virtual void		initFrom(IlvGraphic*);

protected:
    void			initializeMenuPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIPopupMenuPanel,
				    IlvStIPopupMenuPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// Inspector panel of Toolbar
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIToolBarPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIToolBarPanel(IlvDisplay*,
		       const char*,
		       const char* = 0,
		       IlvSystemView = 0,
		       IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridable
    virtual void		initializeEditors();
    virtual void		applyChange(IlvGraphic*);
    virtual void		initFrom(IlvGraphic*);

protected:
    void			initializeToolBarPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIToolBarPanel,
				    IlvStIToolBarPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// Exported functions
ILVSTGADGETEXPORTEDFUNC(void)
IlvStIOrientationFiller(IlvStIProxyListGadget&, IlAny);

ILVSTGADGETEXPORTEDFUNC(IlBoolean)
IlvStIOrientationTranslator(IlvStIProperty*, IlvStIProxyListGadget*,
			    IlBoolean, IlAny);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_menupnl)
#endif /* !__IlvSt_Gadgets_Menupnl_H */
