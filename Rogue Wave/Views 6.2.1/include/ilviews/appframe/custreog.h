// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/custreog.h
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
// Declaration of the IlvDvCustomizeDialog class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Custreog_H)
#define __Ilv_Appframe_Custreog_H

#if !defined(__Ilv_Appframe_Custcmd_H)
#include <ilviews/appframe/custcmd.h>
#endif

class IlvDvDockableMainWindow;
class IlvAbstractMenu;
class IlvGadgetItem;
class IlvMenuItem;

// --------------------------------------------------------------------------
// IlvDvBarNameListener class
// --------------------------------------------------------------------------
// Used by wizard
class ILVDVCLASS IlvDvBarNameListener
{
public:
    virtual void changeBarName(const char* oldName, const char* newName) = 0;
};

// --------------------------------------------------------------------------
// IlvDvBarReorgInspector class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvBarReorgInspector : public IlvDvSortedCommandsInspector
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvBarReorgInspector(IlvDvDialogAssoc* optionsAssoc,
			   IlvDvOptions* allOptions,
			   IlvDvDialogAssoc* tplAssoc,
			   IlvDvDialogAssoc* mainMenuAssoc,
			   IlvDvCmdCategInterface* cmdInterface,
			   IlvDvDockableMainWindow* mainWindow,
			   IlvPalette* palette,
			   IlvPalette* docItemPalette);
    IlvDvBarReorgInspector(IlvDvDialogAssoc* optionsAssoc,
			   IlvDvOptions* allOptions,
			   IlvDvDialogAssoc* tplAssoc,
			   IlvDvDialogAssoc* mainMenuAssoc,
			   IlvDvCmdCategInterface* cmdInterface,
			   IlvDvApplication* application,
			   IlvPalette*,
			   IlvPalette* docItemPalette,
			   const IlSymbol* name = 0);
    ~IlvDvBarReorgInspector();

    // ----------------------------------------------------------------------
    void		ensureGadgetItemsAppearence(const IlSymbol*) const;
    inline
    IlvDvListGadgetAssoc* getReorgCategsList() const
			{
			    return _barCmdsCategAssoc;
			}
    void		setBarNameListener(IlvDvBarNameListener* listener);
    inline
    IlvDvBarNameListener* getBarNameListener() const
			{
			    return _barNameListener;
			}
    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_BarCmdCategoriesSymbol;
    static IlSymbol*	_CommandsBarSymbol;
    static IlSymbol*	_BarsReorgSymbol;
    static IlSymbol*	_BarTreeSymbol;
    static IlSymbol*	_GadItemProperty;
    static IlShort	_BarTreeInsertAction;
    static IlShort	_BarTreeRemoveAction;
    static IlShort	_BarTreeInsertPopupAction;
    static IlShort	_BarTreeInsertSepAction;
    static IlSymbol*	_NewBarNameSymbol;
    static IlSymbol*	_NewBarSymbol;
    static IlAny	_PopupItem;
    static IlAny	_SeparatorItem;
    static IlAny	_CommandItem;
    static IlAny	_LabelItem;
    static IlAny	_BarItem;

protected:
    IlvDvDockableMainWindow*	_mainWindow;
    IlvDvOptions*		_allOptions;
    IlvDvDialogAssoc*		_tplAssoc;
    IlvDvDialogAssoc*		_mainMenuAssoc;
    IlBoolean			_isWizard;
    IlvDvListGadgetAssoc*	_barCommandsListAssoc;
    IlvDvTreeGadgetAssoc*	_barTreeAssoc;
    IlvDvListGadgetAssoc*	_barCmdsCategAssoc;
    IlvDvCmdCategInterface*	_cmdInterface;
    IlvBitmap*			_barBmp;
    IlvBitmap*			_menuBmp;
    IlvBitmap*			_separatorBmp;
    IlBoolean			_updateRealMenu;
    IlvTreeGadgetItem*		_mainMenuItems;
    IlUInt			_newBarIndex;
    IlvDvBarNameListener*	_barNameListener;
    IlvPalette*			_docItemsPalette;

    IlvPalette*		getNormalItemPalette() const;
    IlvPalette*		getDocItemsPalette() const;
    void		setTreeItemPalette(IlvTreeGadgetItem* item,
					   IlBoolean docItem,
					   IlBoolean recurse = IlFalse) const;

    void		internalInitialize(IlvDisplay* display);
    // Bar methods
    void		addBarsToTree(IlvDvNodeValue* varBarList,
				      IlvTreeGadgetItem* treeParent,
				      IlBoolean asDocItems = IlFalse) const;
    IlvTreeGadgetItem*	initBarTreeItem(IlvDvNodeValue* var,
					IlvTreeGadgetItem*) const;
    void	fillBarItemsVariables(IlvDvNodeValue*,
				      IlvTreeGadgetItem* treeParent,
				      IlUInt insertIndex = 0,
				      IlAny owner = 0,
				      IlBoolean markDocItem = IlFalse) const;
    IlvTreeGadgetItem*	findItemByPath(const char*,
				       IlvTreeGadgetItem* root) const;
    IlBoolean		isUserBar(const IlvDvNodeValue*) const;
    virtual
    IlvDvNodeValue*	getAssocValue(const IlSymbol* dataKey,
				      const IlvDvDialogAssoc&,
				      IlBoolean dataVar=IlFalse) const;
    virtual
    const IlSymbol*	getSelectedCategory() const;
    IlvDvNodeValue*	getSelectedBarCommand() const;
    void		setRealGadgetItems(IlvTreeGadgetItem* item,
					   IlvAbstractMenu* bar) const;

    // Overriden from IlvDvSortedCommandsInspector
    virtual void	addListItems(const IlSymbol*,
				     IlvDvGenericGadget&,
				     IlAny clientData,
				     IlvDvListGadgetAssoc&) const;
    virtual void	fillOtherCmdItems(IlvDvGenericGadget& gadget,
					  IlvDvListGadgetAssoc& assoc,
					  const IlSymbol* category,
					  IlUInt index) const;
    virtual
    IlvDvGadgetAssoc*	getCategoryAssoc() const;
    virtual
    IlvDvListGadgetAssoc* getCmdsListAssoc() const;
    virtual
    const IlvDvCmdCategInterface*	getCmdInterface() const;
    void		addDynMenuToTreeItems(IlvDvNodeValue* tplVar,
					      IlvTreeGadgetItem* root,
					      IlAny owner = 0);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	createAssocs();
    virtual
    IlvGadgetItem*	getDragDropItem(const IlvPoint&,
					IlUShort modifiers,
					const IlvDvAbstractListAssoc&,
					IlBoolean* insertBefore = 0,
					IlBoolean* insertAsChild = 0) const;
    virtual void	addTreeItems(const IlSymbol*,
				     IlvDvGenericGadget&,
				     IlvTreeGadgetItem* parent,
				     IlAny clientData,
				     IlvDvNodeValue* varField,
				     IlvDvTreeGadgetAssoc&);
    virtual void	initTreeItem(const IlSymbol*,
				     IlvTreeGadgetItem* item,
				     const IlvTreeGadgetItem* parent,
				     const IlvDvTreeGadgetAssoc&) const;
    virtual IlvTreeGadgetItem*	createTreeItem(const IlvDvTreeGadgetAssoc&,
					       IlvTreeGadgetItem* parent,
					       IlUInt index,
					       IlAny clientData = 0,
					       const IlvDvNodeValue* = 0)const;
    virtual void	setNodeValue(const IlSymbol*,
				     IlvDvNodeValue* var,
				     const IlvDvNodeValue*,
				     const IlvDvDialogAssoc&);
    virtual void	setGadgetValue(const IlSymbol* dataKey,
				       IlvDvGenericGadget& gadget,
				       const IlvValue* value,
				       const IlvDvGadgetAssoc& assoc);
    virtual void	setValueFromGadget(const IlSymbol* dataKey,
					   IlvDvNodeValue* var,
					   IlvDvGenericGadget& gadget);
    virtual IlBoolean	isTreeActionEnabled(const IlSymbol*,
					    const IlvDvNodeValue*,
					    const IlvDvNodeValue*,
					    IlvTreeGadgetItem*,
					    IlShort nAction,
					    const IlvDvGenericGadget&,
					    IlAny param) const;
    virtual void	treeAction(const IlSymbol*,
				   IlShort nAction,
				   IlvTreeGadgetItem* selection,
				   IlvDvNodeValue* varField,
				   IlvDvTreeGadgetAssoc*,
				   IlAny param);
    virtual void	detachTreeItem(const IlSymbol*,
				       IlvTreeGadgetItem*,
				       const IlvDvTreeGadgetAssoc&);
    virtual void	insertedInTree(const IlSymbol*,
				       IlvTreeGadgetItem* newItem,
				       IlvTreeGadgetItem* parentItem,
				       IlUInt index,
				       const IlvDvTreeGadgetAssoc&) const;
    virtual void	removedFromTree(const IlSymbol*,
					IlvTreeGadgetItem* removedItem,
					IlvTreeGadgetItem* parentItem,
					IlUInt index,
					const IlvDvTreeGadgetAssoc&) const;
    IlvDvNodeValue*	getBarVarByName(IlvDvNodeValue* barsVar,
					const char* name) const;
    void		changeBarVarName(IlvDvNodeValue* barsVar,
					 const char* prevName,
					 const char* newName) const;
    virtual void	setVarListItemLabel(const IlSymbol*,
					    IlvGadgetItem*,
					    const char* label,
					    const char* previousLabel,
					    IlvDvNodeValue* = 0);
    virtual void	setTreeItemLabel(const IlSymbol*,
					 IlvTreeGadgetItem*,
					 const char* label,
					 const char* previousLabel,
					 const IlvDvTreeGadgetAssoc&);
    virtual IlUShort	getInitialSelectedItem(const IlSymbol*,
					       const IlvDvNodeValue*,
					       IlUShort selection,
					       IlvDvListGadgetAssoc&) const;
    virtual void	connectHolder(IlvGraphicHolder* holder);

    // Applying modifs
    virtual void	movedInTree(const IlSymbol*,
				    IlvTreeGadgetItem* movedItem,
				    IlvTreeGadgetItem* itemFromParent,
				    IlUInt fromIndex,
				    const IlvDvTreeGadgetAssoc&) const;
    virtual void	applyValue(const IlSymbol*,
				   const IlvDvNodeValue*,
				   IlAny clientData);
    void	ensureGadgetItemAppearence(IlvTreeGadgetItem*) const;
    void	ensureGadgetItemsAppearence(const IlSymbol*,
					    IlvTreeGadgetItem* parent) const;
    IlvListGadgetItemHolder*	getMenuHolder(const IlvTreeGadgetItem*) const;
    IlvGadgetItem*	getMenuItem(const IlvTreeGadgetItem*) const;
    IlBoolean		isUsingBigIcons() const;
    IlBoolean		isShowingToolips() const;
    IlBoolean		withShortcuts() const;
    IlBoolean		getBarFlag(const IlSymbol*) const;
    IlBoolean		isPrivateItem(const IlvGadgetItem*) const;
    const char*		getActiveDocTemplate() const;
    IlvMenuItem*	createRealItem(IlvTreeGadgetItem*,
				       IlvTreeGadgetItem* parentItem) const;
    IlvDvNodeValue*	createMenuInsertion(const IlvTreeGadgetItem* from,
					    const IlvTreeGadgetItem* upTo,
					    const char* path,
					    IlvString& lastPath,
					    IlBoolean after = IlTrue) const;
    const char*		getTreeItemLabel(IlvString& label,
					 const IlvTreeGadgetItem* item,
					 IlUInt& nSeparator) const;
    void		getDynamicMenu(const IlvTreeGadgetItem* mainMenu,
				       IlvTreeGadgetItem* newMenu,
				       IlvDvNodeValue* dynamicMenu,
				       const IlvString& currentPath,
				       IlBoolean bSetOwner = IlFalse,
				       IlAny owner = 0,
				       IlBoolean isParent = IlFalse) const;
    IlvDvNodeValue*	getToolBarVar(const IlvDvNodeValue* varBars,
				      const IlSymbol* barName) const;
    IlvDvNodeValue*	createMenuVar(const IlvTreeGadgetItem* item,
				      IlBoolean bOnlyNotOwned = IlFalse) const;
    void		setTplOwner(const IlvTreeGadgetItem* treeItem,
				    IlAny owner) const;
    IlvDvNodeValue*	updateBarVariable(IlvTreeGadgetItem*,
					  IlvDvNodeValueArray*,
					  IlvDvNodeValue* barsVar,
					  IlBoolean = IlFalse) const;
    void		updateBarVariables(IlBoolean dataVariables) const;
    virtual void	modified(const IlSymbol*, const IlvDvDialogAssoc&);
    virtual void	dataModified(const IlSymbol*, const IlvDvDialogAssoc&);
};

// --------------------------------------------------------------------------
// IlvDvBarShowHideInspector class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvBarShowHideInspector : public IlvDvInspector
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvBarShowHideInspector(IlvDvDockableMainWindow*, IlvPalette*);
    ~IlvDvBarShowHideInspector();

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_ShowBarsSymbol;

protected:
    IlvDvDockableMainWindow*	_mainWindow;
    IlvDvOptions*		_options;
    IlvDvListGadgetAssoc*	_showBarsListAssoc;
    IlvPalette*			_userDefinedPalette;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	createAssocs();
    virtual void	applyValue(const IlSymbol*,
				   const IlvDvNodeValue*,
				   IlAny clientData);
    virtual void	checkListItem(const IlSymbol*,
				      IlUInt,
				      IlBoolean,
				      const IlvDvListGadgetAssoc&);
    virtual void	listItemChecked(const IlSymbol*,
					IlvDvNodeValue* varList,
					IlvDvNodeValue* varItem,
					IlUInt index,
					IlBoolean state);
    virtual void	connectHolder(IlvGraphicHolder* holder);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(custreog);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Custreog_H */
