// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/inspect.h
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
// Declaration of the IlvDvInspector class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Dialog_Inspect_H)
#define __Ilv_Appframe_Dialog_Inspect_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif
#if !defined(__Ilv_Appframe_Dialog_Dlgassoc_H)
#include <ilviews/appframe/dialog/dlgassoc.h>
#endif

class IlvDvOptions;
class IlvDvNodeValue;
class IlvDvClass;
class IlvDvDialogCommand;
class IlvGadget;
class IlvDvListGadgetAssoc;
class IlvDvGenericGadget;
class IlvTreeGadgetItem;
class IlvDvTreeGadgetAssoc;
class IlvDvAbstractListAssoc;
class IlvDvDialogAssocCommand;

// --------------------------------------------------------------------------
// IlvDvGraphicHolderFilter class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvGraphicHolderFilter
{
public:
    virtual IlvGraphicHolder* getGraphicHolder(IlvGraphicHolder*) const = 0;
};

// --------------------------------------------------------------------------
// IlvDvInspector class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvInspector
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvInspector(const IlSymbol* = 0);
    virtual ~IlvDvInspector();

    // ----------------------------------------------------------------------
    // Main operation
    void		reset(const IlSymbol* = 0);
    void		apply(const IlSymbol* = 0);
    void		initializeAll(IlvGraphicHolder* holder);
    virtual void	additionalInitialization();
    void		updateModified();

    // ----------------------------------------------------------------------
    // Commands management
    void		addCmd(IlvDvDialogCommand* cmd, IlBoolean isDone);
    void		undo();
    IlBoolean		canUndo() const;

    void		redo();
    IlBoolean		canRedo() const;

    IlvDvDialogCommand*	findCommand(const IlSymbol*, IlBoolean& isDone) const;
    void		removeCommand(IlvDvDialogCommand*,
				      IlBoolean,
				      IlBoolean);

    // ----------------------------------------------------------------------
    // ApplyMode
    enum ApplyMode {
	None,
	Direct,
	OnApplyPressed };

    virtual ApplyMode	getApplyMode() const;

    // ----------------------------------------------------------------------
    // Inspectors management
    const IlvDvInspector*	getTopInspector() const;
    IlvDvInspector*	getTopInspector();
    IlvDvInspector*	findInspector(const IlSymbol*);
    IlvDvInspector*	findInspectorInAllPath(const IlSymbol*);
    void		addInspector(IlvDvInspector*);

    // ----------------------------------------------------------------------
    // Making assocs

    IlvDvGadgetAssoc*	assocGadget(const IlSymbol* dataKey,
				    const char* gadgetName,
				    IlvDvDialogAssoc* parent = 0,
				    const IlSymbol* varName = 0,
				    int mode = 0);
    IlvDvGadgetAssoc*	assocGadget(const IlSymbol* dataKey,
				    const char* gadgetName,
				    const IlvDvValue&,
				    IlAny clientData = 0,
				    int mode = 0);
    IlvDvGadgetAssoc*	assocGadget(const IlSymbol* dataKey,
				    const char* gadgetName,
				    IlvDvNodeValue* dataVariable,
				    int mode = 0);
    IlvDvGadgetAssoc*	assocTextField(const IlSymbol* dataKey,
				       const char* gadgetName,
				       IlvDvDialogAssoc* parent = 0,
				       const IlSymbol* varName = 0,
				       IlBoolean modifOnChanged = IlFalse);
    IlvDvGadgetAssoc*	assocTextField(const IlSymbol* dataKey,
				       const char* gadgetName,
				       const IlvDvValue&,
				       IlAny clientData,
				       IlBoolean modifOnChanged = IlFalse);
    IlvDvListGadgetAssoc*	assocList(const IlSymbol* dataKey,
					  const char* gadgetName,
					  const IlvDvClass* itemsClass,
					  IlBoolean fillAlways = IlFalse,
					  IlvDvDialogAssoc* parent = 0,
					  const IlSymbol* varName = 0);
    IlvDvTreeGadgetAssoc*	assocTree(const IlSymbol* dataKey,
					  const char* gadgetName,
					  const IlvDvClass* itemsClass,
					  IlBoolean fillAlways = IlFalse,
					  IlvDvDialogAssoc* parent = 0,
					  const IlSymbol* varName = 0,
					  IlShort nAction =
					  IlvDvTreeGadgetAssoc::_TreeActionsCount);

    // ----------------------------------------------------------------------
    // Assocs management
    IlvDvDialogAssoc*		findAssoc(const IlSymbol*) const;
    IlvDvDialogAssoc*		findAssocInAllPath(const IlSymbol*) const;
    IlvDvNodeValue*		findValueInAllPath(const IlSymbol*) const;
    IlvDvNodeValue*		findVariable(const IlSymbol*) const;
    inline IlvDvAssocsArray&	getAssocs() { return _assocs; }

    // ----------------------------------------------------------------------
    // Basic properties
    IlvDisplay*		getHolderDisplay() const;
    IlvDvNodeValue*	getItemVariable(const IlvGadgetItem*) const;
    void		setItemVariable(IlvGadgetItem*, IlvDvNodeValue*) const;
    IlvDvNodeValue*	getItemDataVariable(IlvGadgetItem*) const;
    void		setItemDataVariable(IlvGadgetItem*,
					    IlvDvNodeValue*) const;

    void		setGraphicHolderFilter(IlvDvGraphicHolderFilter*);
    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_GadItemVariableProperty;
    static IlSymbol*	_GadItemDataVariableProperty;
    static IlSymbol*	_PrivateDataPropertyName;

protected:
    // ----------------------------------------------------------------------
    // Fields
    // ----------------------------------------------------------------------
    IlvDvGraphicHolderFilter*	_grHolderFilter;
    IlvGraphicHolder*		_holder;
    IlvDvInspector*		_parent;
    IlArray			_inspectors;
    const IlSymbol*		_name;
    IlvDvCommandHistory		_commands;
    IlvDvAssocsArray		_assocs;

    virtual IlvGraphicHolder*	filterGraphicHolder(IlvGraphicHolder*);

    // Assocs
    inline IlvDvDialogAssoc*	getAssoc(IlUInt iAssoc)
				{
				    return _assocs.getAssoc(iAssoc);
				}
    void			removeAssocs();
    void			addAssoc(IlvDvDialogAssoc*);
    void			createAllAssocs();
    void			allAdditionalInitialization();
    void			linkAllGadgets(IlvGraphicHolder* holder);
    void			initializeAllAssocs();
    void			updateAllModified();
    virtual void		doUpdateModified();

    // ----------------------------------------------------------------------
    // Friends
    // ----------------------------------------------------------------------
    friend class ILVDVCLASS IlvDvDialogAssocCommand;
    friend class ILVDVCLASS IlvDvGadgetModifCommand;
    friend class ILVDVCLASS IlvDvDialogAssoc;
    friend class ILVDVCLASS IlvDvGadgetAssoc;
    friend class ILVDVCLASS IlvDvAbstractListAssoc;
    friend class ILVDVCLASS IlvDvListGadgetAssoc;
    friend class ILVDVCLASS IlvDvTreeGadgetAssoc;
    friend class ILVDVCLASS IlvDvListMoveCommand;
    friend class ILVDVCLASS IlvDvListInsertRemoveCommand;
    friend class ILVDVCLASS IlvDvListCleanCommand;
    friend class ILVDVCLASS IlvDvPageSelectorAssoc;
    friend class ILVDVCLASS IlvDvListCheckCommand;
    friend class ILVDVCLASS IlvDvListModifCommand;
    friend class ILVDVCLASS IlvDvListEndEditCommand;
    friend class ILVDVCLASS IlvDvTreeModifCommand;
    friend class ILVDVCLASS IlvDvTreeMoveCommand;
    friend class ILVDVCLASS IlvDvTreeInsertRemoveCommand;
    friend class ILVDVCLASS IlvDvTreeCleanCommand;
    friend class ILVDVCLASS IlvDvTreeCheckCommand;
    friend class ILVDVCLASS IlvDvTreeEndEditCommand;

    // ----------------------------------------------------------------------
    // Overridables
    // ----------------------------------------------------------------------
    virtual void		connectHolder(IlvGraphicHolder* holder);
    virtual void		createAssocs();
    virtual IlvDvNodeValue*	getAssocValue(const IlSymbol* dataKey,
					      const IlvDvDialogAssoc&,
					      IlBoolean dataVar=IlFalse) const;
    virtual void		modified(const IlSymbol*,
					 const IlvDvDialogAssoc&);
    virtual void		dataModified(const IlSymbol*,
					     const IlvDvDialogAssoc&);
    virtual IlvDvOptions*	getOptions() const;

    // ----------------------------------------------------------------------
    // Gadget overridables
    virtual void	initializeGadget(const IlSymbol*,
					 IlvDvGenericGadget&,
					 const IlvDvNodeValue*,
					 const IlvDvGadgetAssoc&);
    virtual void	setGadgetValue(const IlSymbol*,
				       IlvDvGenericGadget&,
				       const IlvValue*,
				       const IlvDvGadgetAssoc&);
    virtual void	setValueFromGadget(const IlSymbol*,
					   IlvDvNodeValue*,
					   IlvDvGenericGadget&);
    virtual void	applyValue(const IlSymbol*,
				   const IlvDvNodeValue*,
				   IlAny clientData);
    virtual void	setNodeValue(const IlSymbol*,
				     IlvDvNodeValue* var,
				     const IlvDvNodeValue*,
				     const IlvDvDialogAssoc&);
    virtual void	setDataVariableValue(const IlSymbol*,
					     IlvDvNodeValue* var,
					     const IlvDvNodeValue*,
					     const IlvDvDialogAssoc&);
    virtual IlBoolean	getGadgetSensitivity(const IlSymbol*,
					     const IlvDvGadgetAssoc&) const;

    // ----------------------------------------------------------------------
    // Specific list managment overridables
    virtual void	fill(const IlSymbol*,
			     IlvDvGenericGadget&,
			     IlAny clientData,
			     IlvDvListGadgetAssoc&);
    virtual void	addListItems(const IlSymbol*,
				     IlvDvGenericGadget&,
				     IlAny clientData,
				     IlvDvListGadgetAssoc&) const;
    virtual IlUShort	getInitialSelectedItem(const IlSymbol*,
					       const IlvDvNodeValue* var,
					       IlUShort selection,
					       IlvDvListGadgetAssoc&) const;
    virtual IlvGadgetItem*
			createListItem(const IlvDvListGadgetAssoc&,
				       IlUInt,
				       IlAny clientData = 0,
				       const IlvDvNodeValue* = 0) const;
    virtual void	initGadgetItem(const IlSymbol*,
				       IlvGadgetItem*,
				       const IlvDvAbstractListAssoc&) const;

    virtual IlvDvNodeValue*
			createFieldVariable(const IlSymbol*,
					    const IlvDvNodeValue* parent,
					    IlUInt index,
					    const IlvDvClass* itemClass,
					    IlAny param = 0);
    virtual IlvDvNodeValue*
			createDataVariable(const IlSymbol*,
					   const IlvDvNodeValue* parent,
					   IlUInt index,
					   const IlvDvClass* itemClass,
					   IlAny param = 0);
    virtual IlBoolean	isListActionEnabled(const IlSymbol*,
					    IlUInt iItem,
					    IlShort nAction,
					    const IlvDvListGadgetAssoc&,
					    IlAny param = 0) const;
    virtual IlvDvNodeValue*
			getListItemVariable(const IlSymbol*,
					    IlvDvNodeValue*,
					    IlUInt,
					    IlvGadgetItem*,
					    const IlvDvListGadgetAssoc&) const;
    virtual IlvDvNodeValue*
			getListItemDataVariable(const IlSymbol*,
						IlvDvNodeValue*,
						IlUInt,
						IlvGadgetItem*,
						const IlvDvListGadgetAssoc&)
						const;
    virtual void	moveVarInList(const IlSymbol*,
				      IlUInt,
				      IlUInt,
				      IlvDvNodeValue*,
				      IlvDvNodeValue*);
    virtual void	moveInList(const IlSymbol*,
				   IlUInt,
				   IlUInt,
				   IlvDvNodeValue*,
				   IlvDvNodeValue*);
    virtual IlUInt	insertInVarList(const IlSymbol*,
					IlvDvNodeValue* varList,
					IlvDvNodeValue*,
					IlUInt);
    virtual IlUInt	insertInDataVarList(const IlSymbol*,
					    IlvDvNodeValue* varList,
					    IlvDvNodeValue*,
					    IlUInt,
					    const IlvDvListGadgetAssoc&);
    virtual IlUInt	addItem(const IlSymbol*,
				IlvDvNodeValue*,
				IlvDvListGadgetAssoc&,
				IlUInt = (IlUInt)-1,
				IlAny clientData = 0,
				IlBoolean selectIt = IlTrue);
    virtual void	detachFromVarList(const IlSymbol*,
					  IlvDvNodeValue* varList,
					  IlvDvNodeValue*,
					  IlUInt);
    virtual void	detachListItem(const IlSymbol*,
				       IlUInt,
				       const IlvDvListGadgetAssoc& listAssoc);
    virtual void	detachFromDataVarList(
					      const IlSymbol*,
					      IlvDvNodeValue* varList,
					      IlvDvNodeValue*,
					      IlUInt,
					      const IlvDvListGadgetAssoc&);
    virtual void	removeItem(const IlSymbol*,
				   IlUInt index,
				   IlvDvNodeValue* varField,
				   IlvDvListGadgetAssoc&);
    virtual void	insertedInList(const IlSymbol*,
				       IlvDvNodeValue* varList,
				       IlvDvNodeValue*,
				       IlUInt);
    virtual void	removedFromList(const IlSymbol*,
					IlvDvNodeValue* varList,
					const IlvDvNodeValue* varRemoved,
					IlUInt);
    virtual void	cleanVarList(const IlSymbol*, IlvDvNodeValue* varList);
    virtual void	listAction(const IlSymbol*,
				   IlShort nAction,
				   IlUShort selection,
				   IlvDvNodeValue* varField,
				   IlvDvListGadgetAssoc*,
				   IlAny param);
    virtual IlvDvDialogAssocCommand*
			makeEndEditCmd(IlvDvAbstractListAssoc&,
				       IlvGadgetItem*,
				       const char* origLabel,
				       IlAny param = 0);
    virtual void	setVarListItemLabel(const IlSymbol*,
					    IlvGadgetItem*,
					    const char* label,
					    const char* previousLabel,
					    IlvDvNodeValue* = 0);
    virtual void	setListItemLabel(const IlSymbol*,
					 IlvGadgetItem*,
					 const char* label,
					 const char* previousLabel,
					 const IlvDvListGadgetAssoc&);
    void		setVarLabel(IlvDvNodeValue* var, const char* label);

    virtual IlvGadgetItem*
			getDragDropItem(const IlvPoint&,
					IlUShort modifiers,
					const IlvDvAbstractListAssoc&,
					IlBoolean* insertBefore = 0,
					IlBoolean* insertAsChild = 0) const;

    // Check list management
    virtual void	checkListItem(const IlSymbol*,
				      IlUInt,
				      IlBoolean,
				      const IlvDvListGadgetAssoc&);
    virtual void	listItemChecked(const IlSymbol*,
					IlvDvNodeValue* varList,
					IlvDvNodeValue* varItem,
					IlUInt index,
					IlBoolean state);
    virtual IlBoolean	getCheckValue(const IlSymbol*,
				      const IlvGadgetItem*,
				      const IlvDvNodeValue* varItem,
				      const IlvDvAbstractListAssoc& assoc) const;

    virtual IlBoolean	reinitializeFromChildModif(const IlSymbol*,
						 const IlvDvAbstractListAssoc&,
						 const IlvDvDialogAssoc&)const;

    // ----------------------------------------------------------------------
    // Tree gadget management
    virtual IlvTreeGadgetItem* 
			createTreeItem(const IlvDvTreeGadgetAssoc&,
				       IlvTreeGadgetItem* parent,
				       IlUInt index,
				       IlAny clientData = 0,
				       const IlvDvNodeValue* = 0) const;
    void		fillTree(const IlSymbol*,
				 IlvDvGenericGadget&,
				 IlAny clientData,
				 IlvDvTreeGadgetAssoc&);
    virtual IlvTreeGadgetItem*	getTreeItem(const IlvDvNodeValue*,
					    IlvTreeGadgetItem* parent) const;
    virtual IlvTreeGadgetItem*
			getInitialSelectedTreeItem(const IlSymbol* dataKey,
						   IlvDvNodeValue* varTree,
						   IlvTreeGadgetItem* itemSel,
						   IlvDvGenericGadget&) const;
    virtual IlvDvNodeValue* 
			getTreeItemVariable(const IlSymbol* dataKey,
					    IlvDvNodeValue* varTree,
					    IlvTreeGadgetItem* itemSel,
					    const IlvDvTreeGadgetAssoc&) const;
    virtual IlvDvNodeValue* 
			getTreeItemDataVariable(const IlSymbol* dataKey,
						IlvDvNodeValue* varTree,
						IlvTreeGadgetItem* itemSel,
						const IlvDvTreeGadgetAssoc&)
						const;
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
    virtual void	moveVarInTree(const IlSymbol*,
				      IlvDvNodeValue* varMoved,
				      IlvTreeGadgetItem* itemFromParent,
				      IlvDvNodeValue* varParent,
				      IlUInt fromIndex,
				      IlvTreeGadgetItem* itemToParent,
				      IlvDvNodeValue* varToParent,
				      IlUInt toIndex) const;
    virtual void	movedInTree(const IlSymbol*,
				    IlvTreeGadgetItem* movedItem,
				    IlvTreeGadgetItem* itemFromParent,
				    IlUInt fromIndex,
				    const IlvDvTreeGadgetAssoc&) const;
    virtual IlUInt	insertInDataVarTree(const IlSymbol*,
					    IlvTreeGadgetItem* insertedItem,
					    IlvDvNodeValue* varParent,
					    IlvDvNodeValue*,
					    IlUInt,
					    const IlvDvTreeGadgetAssoc&);
    virtual void	insertedInTree(const IlSymbol*,
				       IlvTreeGadgetItem* newItem,
				       IlvTreeGadgetItem* parentItem,
				       IlUInt index,
				       const IlvDvTreeGadgetAssoc&) const;
    virtual void	detachTreeItem(const IlSymbol*,
				       IlvTreeGadgetItem*,
				       const IlvDvTreeGadgetAssoc& treeAssoc);
    virtual void	detachFromDataVarTree(const IlSymbol*,
					      IlvDvNodeValue*,
					      IlvDvNodeValue*,
					      IlUInt,
					      const IlvDvTreeGadgetAssoc&);
    virtual void	removedFromTree(const IlSymbol*,
					IlvTreeGadgetItem* removedItem,
					IlvTreeGadgetItem* parentItem,
					IlUInt index,
					const IlvDvTreeGadgetAssoc&) const;
    virtual IlvDvNodeValue*
			createTreeFieldVariable(const IlSymbol*,
						IlvTreeGadgetItem*,
						IlvDvNodeValue*,
						IlUInt index,
						IlAny param,
						const IlvDvTreeGadgetAssoc&);
    virtual void	setVarTreeItemLabel(const IlSymbol*,
					    IlvTreeGadgetItem*,
					    IlvDvNodeValue*,
					    const char* label,
					    IlvDvTreeGadgetAssoc*,
					    IlAny);
    virtual void	setTreeItemLabel(const IlSymbol*,
					 IlvTreeGadgetItem*,
					 const char* label,
					 const char* previousLabel,
					 const IlvDvTreeGadgetAssoc&);
    virtual void	checkTreeItem(const IlSymbol*,
				      IlvTreeGadgetItem*,
				      IlBoolean,
				      const IlvDvTreeGadgetAssoc&);

    // ----------------------------------------------------------------------
    // Utilities
    IlvBitmap*		getBitmap(const IlvDvNodeValue*) const;
    const char*		getVariableName(const IlvDvNodeValue*) const;
    virtual IlvDvNodeValue*
			createNodeValue(const char* name, 
					const IlvDvClass* itemClass) const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(inspect);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Inspect_H */
