// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/dlgassoc.h
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
// Declaration of the IlvDvDialogAssoc classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Dialog_Dlgassoc_H)
#define __Ilv_Appframe_Dialog_Dlgassoc_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Appframe_Gadgets_Gengadg_H)
#include <ilviews/appframe/gadgets/gengadg.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif

class IlvDvOptions;
class IlvListGadgetItemHolder;
class IlvGadgetItem;
class IlvButton;
class IlvTreeGadget;
class IlvTreeGadgetItem;
class IlvDvNodeValue;
class IlvDvClass;
class IlvGraphic;
class IlvDvInspector;
class IlvDvDialogCommand;
class IlvDvDialogAssoc;
class IlvGadgetItemHolder;
class IlvDvValue;
class IlvGraphicHolder;
class IlvCursor;
class IlvDvNodeValueArray;
// --------------------------------------------------------------------------
// IlvDvAssocsArray class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvAssocsArray : public IlArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvAssocsArray();
    ~IlvDvAssocsArray();

    // ----------------------------------------------------------------------
    // Overriadables
    void			initializeAssocs();
    void			addAssoc(IlvDvDialogAssoc*);
    void			setInspector(IlvDvInspector* dialog);
    void			reset(IlBoolean bApply);
    void			initialize();
    void			linkGadgets(IlvGraphicHolder* holder);
    IlvDvDialogAssoc*		getAssoc(const IlSymbol*) const;
    IlvDvNodeValue*		getNodeValue(const IlSymbol*) const;
    inline IlvDvDialogAssoc*	getAssoc(IlUInt iAssoc) const
				{
				    return (IlvDvDialogAssoc*)(*this)[iAssoc];
				}
};

// --------------------------------------------------------------------------
// IlvDvDialogAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDialogAssoc
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDialogAssoc(const IlSymbol*   dataKey,
		     IlvDvDialogAssoc* parent = 0,
		     const IlSymbol*   variableName = 0);
    virtual ~IlvDvDialogAssoc();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		initialize();
    virtual void		reset(IlBoolean bApply);
    virtual IlBoolean		linkGadgets(IlvGraphicHolder* holder);
    virtual void		initializeSubAssocs();
    void			addSubAssoc(IlvDvDialogAssoc*);
    inline const IlvDvAssocsArray&	getAssocs() const { return _assocs; }
    virtual void		subAssocModified(const IlvDvDialogAssoc&);
    void			removeAssoc(IlvDvDialogAssoc*,
					    IlBoolean deleteIt = IlTrue);

    // ----------------------------------------------------------------------
    // Focus
    virtual IlBoolean		setFocus();
    IlBoolean			setFocusOnFirstChild();
    // ----------------------------------------------------------------------
    void			setInspector(IlvDvInspector* dialog);
    inline IlvDvInspector*	getInspector() const { return _inspector; }
    virtual IlvGraphicHolder*	getGraphicHolder() const;
    virtual const IlvDvGenericGadget*	getGenericGadget() const;

    inline IlvDvNodeValue*	getNodeValue() const { return _var; }
    virtual void		updateVariable();
    inline const IlSymbol*	getDataKey() const { return _dataKey; }

    inline const IlSymbol*	getVariableName() const
				{
				    return _variableName;
				}
    inline void			setVariableName(const IlSymbol* variableName)
				{
				    _variableName = variableName;
				}

    inline IlvDvDialogAssoc*	getParent() const { return _parent; }
    void			setParent(IlvDvDialogAssoc* parent);
    virtual IlvDvNodeValue*	getChildVariable() const;

    virtual IlvDvNodeValue*	getDataVariable() const;
    virtual IlvDvNodeValue*	getChildDataVariable() const;

    // Mode management
    inline IlUShort		getMode() const { return _mode; }
    void			setMode(IlUShort mode, IlBoolean set = IlTrue);

    // Statics
    static void			ClearVar(IlvDvNodeValue*);

    static IlSymbol*		_VariableNameKeySymbol;
    static IlSymbol*		_VariableParentKeySymbol;

    // Static modes
    static IlUShort		_ModeDoNotGetParentValue;

protected:
    IlvDvInspector*		_inspector;
    const IlSymbol*		_dataKey;
    const IlSymbol*		_variableName;
    IlvDvNodeValue*		_var;
    IlUShort			_mode;
    IlvDvAssocsArray		_assocs;
    IlvDvDialogAssoc*		_parent;

    IlvDvDialogCommand*		ensureCommand(IlBoolean& created);
    virtual IlvDvDialogCommand*	createCommand();
};

// --------------------------------------------------------------------------
// IlvDvGlobalVarAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvGlobalVarAssoc : public IlvDvDialogAssoc
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvGlobalVarAssoc(const IlSymbol* dataKey,
			IlvDvOptions*   options,
			const IlSymbol* typeName,
			const IlSymbol* variableName);

    IlvDvGlobalVarAssoc(const IlSymbol*   dataKey,
			IlvDvDialogAssoc* optAssoc,
			const IlSymbol*   typeName,
			const IlSymbol*   variableName);
    virtual ~IlvDvGlobalVarAssoc();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		initialize();
    virtual IlvDvNodeValue*	getDataVariable() const;

    // ----------------------------------------------------------------------

protected:
    IlvDvOptions*		_options;
    const IlSymbol*		_typeName;
    IlvDvNodeValue*		_dataVariable;
};

// --------------------------------------------------------------------------
// IlvDvGadgetAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvGadgetAssoc : public IlvDvDialogAssoc
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvGadgetAssoc(const IlSymbol* dataKey,
		     const char*     gadgetName,
		     const IlvDvValue&,
		     IlAny           clientData = 0,
		     int             mode = 0);

    IlvDvGadgetAssoc(const IlSymbol*   dataKey,
		     const char*       gadgetName,
		     IlvDvDialogAssoc* parent,
		     const IlSymbol*   variableName = 0,
		     int               mode = 0);

    IlvDvGadgetAssoc(const IlSymbol* dataKey,
		     const char*     gadgetName,
		     IlvDvNodeValue* dataVariable,
		     int             mode = 0);

    ~IlvDvGadgetAssoc();

    // ----------------------------------------------------------------------
    // Overriadables
    virtual void		initialize();
    virtual void		reset(IlBoolean bApply);
    virtual IlBoolean		linkGadgets(IlvGraphicHolder* holder);
    virtual void		updateVariable();

    // ----------------------------------------------------------------------
    // Focus
    virtual IlBoolean		setFocus();

    // ----------------------------------------------------------------------
    // Basic properties
    inline IlvDvGenericGadget&	getGadget() { return _gadget; }
    inline const IlvDvGenericGadget&	getGadget() const { return _gadget; }
    virtual const IlvDvGenericGadget*	getGenericGadget() const;

    void			modified();

    void			setOriginalValue(IlvDvNodeValue* var);
    void			setDataVariable(IlvDvNodeValue* var);
    void			setDataVariable(IlvDvOptions*,
						const IlSymbol* type,
						const IlSymbol* name);
    virtual IlvDvNodeValue*	getDataVariable() const;

    void			setVariable(IlvDvNodeValue* var,
					    IlBoolean saveAnOrig = IlTrue);

    inline IlAny		getClientData() const { return _clientData; }
    inline void			setClientData(IlAny clientData)
				{
				    _clientData = clientData;
				}
    IlBoolean			alreadyLinkedTo(IlvGraphicHolder* holder,
						IlvGraphic** g = 0) const;

    static IlUShort		_ModeEditModifOnChange;

protected:
    IlvDvNodeValue*		_originalValue;
    IlvDvNodeValue*		_dataVariable;
    IlAny			_clientData;
    IlString			_gadgetName;
    IlvDvGenericGadget		_gadget;
    IlArray			_commands;

    virtual void		setCallback();
    virtual const IlSymbol*	getCallbackType() const;
    virtual void		gadgetNotification();
    virtual IlvDvDialogCommand*	createCommand();
    void			addCmd(IlvDvDialogCommand* cmd,
				       IlBoolean isDone = IlFalse);
public:
    static void			GadgetCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
// IlvDvAbstractListAssoc class
// --------------------------------------------------------------------------
class IlvDvListGadgetAssoc;
class IlvDvTreeGadgetAssoc;

class ILVDVCLASS IlvDvAbstractListAssoc : public IlvDvGadgetAssoc
{
public:
    static IlShort	_ActionInsert;
    static IlShort	_ActionAdd;
    static IlShort	_ActionRemove;
    static IlShort	_ActionClean;
    static IlShort	_ActionUp;
    static IlShort	_ActionDown;
    static IlShort	_ActionEndEditItem;
    static IlShort	_ActionDragItem;
    static IlShort	_CombinedButtonsCount;
    static IlShort	_DragDropBeforeBrother;
    static IlShort	_DragDropAfterBrother;
    static IlShort	_DragDropAsChild;
    static IlSymbol*	_ActionType;

    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvAbstractListAssoc(const IlSymbol* dataKey,
			   const char* gadgetName,
			   IlvDvNodeValue* varList,
			   const IlvDvClass* itemsClass,
			   IlBoolean fillAlways = IlFalse,
			   IlAny clientData = 0,
			   IlShort actionsCount = _CombinedButtonsCount);

    IlvDvAbstractListAssoc(const IlSymbol* dataKey,
			   const char* gadgetName,
			   const IlvDvClass* itemsClass,
			   IlBoolean fillAlways = IlFalse,
			   IlvDvDialogAssoc* parent = 0,
			   const IlSymbol* varName = 0,
			   IlShort actionsCount = _CombinedButtonsCount);
    ~IlvDvAbstractListAssoc();

    // ----------------------------------------------------------------------
    // Overriadables
    virtual void	initialize();
    virtual IlBoolean	linkGadgets(IlvGraphicHolder* holder);
    // ----------------------------------------------------------------------
    // Basic properties
    void		setEditionGadgets(const char* insertName,
					  const char* addName = 0,
					  const char* removeName = 0,
					  const char* cleanName = 0,
					  const char* upName = 0,
					  const char* downName = 0);
    void		setEditionGadgetName(IlShort, const char*);
    IlvGadgetItem*	getSelectedItem(IlUInt* = 0) const;

    void		setDataVariables(IlvDvOptions* options,
					 const IlSymbol* type,
					 IlBoolean initOrigAndCurrent=IlTrue);
    IlvDvNodeValueArray*	getDataVariables() const;
    inline IlBoolean	isVarListOptions() const
			{
			    return _deleteDataVariable;
			}
    const IlSymbol*	getOptionsVarListType() const;
    inline const IlvDvClass*	getItemsClass() const { return _itemsClass; }
    IlAny		getActionParam(IlShort) const;
    void		setActionParam(IlShort, IlAny);

    IlvDvNodeValue*	getListVariable() const; // Returns _listVar or _var
    inline IlvDvNodeValue*	getDefinedListVariable() const
				{
				    return _listVar;
				}
    void		setListVariable(IlvDvNodeValue*);

    IlBoolean		selectOnParentVar() const;
    inline void		setSelectOnParentVar(IlBoolean b)
			{
			    _selectOnParentValue = b;
			}

    virtual IlvDvListGadgetAssoc*	getListGadgetAssoc();
    virtual IlvDvTreeGadgetAssoc*	getTreeGadgetAssoc();

protected:
    IlvDvNodeValue*	_listVar;
    IlvDvNodeValue*	_listVarOrig;
    IlBoolean		_deleteDataVariable;
    IlShort		_actionsCount;
    const IlvDvClass*	_itemsClass;
    IlString*		_buttonNames;
    IlvButton**		_buttons;
    IlBoolean		_fillAlways;
    IlBoolean		_selectOnParentValue;
    IlArray		_actionParams;
    IlString		_origEditedLabel;
    IlvGadgetItem*	_initialDragItem;
    IlvCursor*		_cannotCursor;
    IlvCursor*		_insChildCursor;
    IlvCursor*		_insBrotherCursor;
    IlvCursor*		_insBeforeCursor;
    IlBoolean		_insertBefore;
    IlBoolean		_insertAsChild;
    IlvBitmap*		_cannotBmp;
    IlvBitmap*		_insertChildBmp;
    IlvBitmap*		_insertAfterBmp;
    IlvBitmap*		_insertBeforeBmp;

    void		ensureCursors();
    void		ensureBitmaps();
    void		setCursor(IlvCursor*);
    IlvGadgetItem*	getDragDropItem(const IlvPoint&,
					IlUShort modifier,
					IlBoolean* insertBefore = 0,
					IlBoolean* insertAsChild = 0) const;

    virtual void	selectionChanged();
    virtual void	gadgetNotification();
    virtual void	startEdit();
    virtual void	endEdit();
    virtual void	startDrag();
    virtual void	drag();
    virtual void	endDrag();
    virtual void	draggCanceled();

    virtual void	action(IlShort) = 0;

public:
    static void		ButtonCallback(IlvGraphic*, IlAny);
    static void		InsertCallback(IlvGraphic*, IlAny);
    static void		DeleteCallback(IlvGraphic*, IlAny);
    static void		StartEditCallback(IlvGraphic*, IlAny);
    static void		EndEditCallback(IlvGraphic*, IlAny);
    static void		StartDragCallback(IlvGraphic*, IlAny);
    static void		DragCallback(IlvGraphic*, IlAny);
    static void		EndDragCallback(IlvGraphic*, IlAny);
    static void		AbortDragItemCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
// IlvDvListAssocs class
// --------------------------------------------------------------------------
class IlvDvListGadgetAssoc;

class ILVDVCLASS IlvDvListAssocs : public IlArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListAssocs(IlUInt len = 3) : IlArray(len) {}

    inline IlvDvListGadgetAssoc* getAssoc(IlUInt nAssoc) const
					{ return (IlvDvListGadgetAssoc*)
					      (*this)[nAssoc];
					}
};

// --------------------------------------------------------------------------
// IlvDvListGadgetAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListGadgetAssoc : public IlvDvAbstractListAssoc
{
public:
    static IlShort	_ListActionsCount;

    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListGadgetAssoc(const IlSymbol* dataKey,
			 const char* gadgetName,
			 const IlvDvClass* itemsClass,
			 IlBoolean fillAlways = IlFalse,
			 IlvDvDialogAssoc* parent = 0,
			 const IlSymbol* varName = 0,
			 IlShort actionsCount = _ListActionsCount);
    ~IlvDvListGadgetAssoc();

    // ----------------------------------------------------------------------
    // Overriadables
    virtual void		initialize();
    virtual IlBoolean		linkGadgets(IlvGraphicHolder* holder);
    virtual void		subAssocModified(const IlvDvDialogAssoc&);
    virtual IlvDvNodeValue*	getChildVariable() const;
    virtual IlvDvNodeValue*	getChildDataVariable() const;
    virtual IlvDvListGadgetAssoc*	getListGadgetAssoc();

    // ----------------------------------------------------------------------
    // Main operations
    void		fill();
    IlUInt		addItem(IlvDvNodeValue*,
				IlUInt = (IlUInt)-1,
				IlAny clientData = 0,
				IlBoolean selectIt = IlTrue);
    void		removeItem(IlUInt, IlvDvNodeValue*);

    // ----------------------------------------------------------------------
    // Basic properties
    inline void		setApplyOnDblClick(IlBoolean b)
			{
			    _applyOnDblClick = b;
			}
    inline IlvListGadgetItemHolder*	getListHolder() const
					{
					    return _listHolder;
					}
    void		setSelected(IlUShort,
				    IlBoolean reinitChildren = IlTrue);
    IlUShort		getSelection(IlvDvNodeValue** = 0) const;
    IlUShort		getIndex(const IlvDvNodeValue*) const;
    IlvDvNodeValue*	getItemVariable(IlUInt) const;

    inline IlBoolean	isSorted() const { return _sorted; }
    inline void		setSorted(IlBoolean sorted = IlTrue)
			{
			    _sorted = sorted;
			}

    void		addLinkedAssoc(IlvDvListGadgetAssoc*);
    void		removeLinkedAssoc(IlvDvListGadgetAssoc*);
    void		removeLinkedToAssoc();
    IlUInt		getLinkedAssocCount() const;
    IlvDvListGadgetAssoc*		getLinkedAssoc(IlUInt) const;
    inline IlvDvListGadgetAssoc*	getLinkedToAssoc() const
					{
					    return _linkedToAssoc;
					}
    void getAllListAssocs(IlvDvListAssocs&);

    // ----------------------------------------------------------------------
protected:
    IlBoolean			_applyOnDblClick;
    IlBoolean			_sorted;
    IlBoolean			_cbTextModified;
    IlvListGadgetItemHolder*	_listHolder;
    IlvDvListAssocs		_linkedListAssocs;
    IlvDvListGadgetAssoc*	_linkedToAssoc;

    void			selectionChanged();
    virtual void		listItemChecked(IlUShort, IlBoolean);
    virtual void		focusOut();
    virtual void		labelChanged();

    virtual void		action(IlShort);

public:
    static void			ApplyCallback(IlvGraphic*, IlAny);
    static void			ListItemCheckedCallback(IlvGadgetItemHolder*,
							IlvGadgetItem*,
							IlBoolean,
							IlBoolean,
							IlAny);
    static void			FocusOutCallback(IlvGraphic*, IlAny);
    static void			LabelChangedCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
// IlvDvTreeGadgetAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeGadgetAssoc : public IlvDvAbstractListAssoc
{
public:
    static IlShort	_ActionAddChild;
    static IlShort	_TreeActionsCount;

    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeGadgetAssoc(const IlSymbol* dataKey,
			 const char* gadgetName,
			 const IlvDvClass* itemsClass,
			 IlBoolean fillAlways = IlFalse,
			 IlvDvDialogAssoc* parent = 0,
			 const IlSymbol* varName = 0,
			 IlShort actionsCount = _TreeActionsCount);
    ~IlvDvTreeGadgetAssoc();

    // ----------------------------------------------------------------------
    // Overriadables
    virtual void		initialize();
    virtual IlBoolean		linkGadgets(IlvGraphicHolder* holder);
    virtual void		subAssocModified(const IlvDvDialogAssoc&);
    virtual IlvDvNodeValue*	getChildVariable() const;
    virtual IlvDvNodeValue*	getChildDataVariable() const;
    virtual IlvDvTreeGadgetAssoc*	getTreeGadgetAssoc();
    // ----------------------------------------------------------------------
    // Basic properties
    void		setTreeEditionGadgets(const char* insertName,
					      const char* addName = 0,
					      const char* insertChild = 0,
					      const char* removeName = 0,
					      const char* cleanName = 0,
					      const char* upName = 0,
					      const char* downName = 0);
    IlvTreeGadget*	getTreeGadget() const;
    void		setSelected(IlvTreeGadgetItem*,
				    IlBoolean reinitializeChilds = IlTrue);
    IlvTreeGadgetItem*	getSelection(IlvDvNodeValue** = 0) const;

    inline IlBoolean	isDragDropOnlyInRoots() const
			{
			    return _dragDropOnlyInRoots;
			}
    inline void		setDragDropOnlyInRoots(IlBoolean b)
			{
			    _dragDropOnlyInRoots = b;
			}

protected:
    IlBoolean		_dragDropOnlyInRoots;

    void		selectionChanged();
    virtual void	treeItemChecked(IlvTreeGadgetItem*, IlBoolean);

    virtual void	action(IlShort);
    virtual void	gadgetNotification();

public:
    static void		TreeItemCheckedCallback(IlvGadgetItemHolder*,
						IlvGadgetItem*,
						IlBoolean,
						IlBoolean,
						IlAny);
};

// --------------------------------------------------------------------------
// IlvDvPageSelectorAssoc class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvPageSelectorAssoc : public IlvDvDialogAssoc
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvPageSelectorAssoc(const IlSymbol*   dataKey,
			   IlvDvDialogAssoc* parent = 0,
			   const IlSymbol*   varName = 0);
    ~IlvDvPageSelectorAssoc();

    // ----------------------------------------------------------------------
    // Overriadables
    virtual void	initialize();
    virtual IlBoolean	linkGadgets(IlvGraphicHolder* holder);

    // ----------------------------------------------------------------------
    // Basic properties
    void		addPage(IlUInt pageIndex, ...);
    void		addPage(const char* pageValueID, ...);
    void		removePages();

public: // Some Unix compilers need public declarations for nested classes
    IlArray		_pages;
    class PageID {
    public:
	IlBoolean _isIndex;
	union {
	    IlUInt _index;
	    IlString* _name;
	} _val;
	PageID(IlUInt index) { _val._index = index; _isIndex = IlTrue; }
	PageID(const char* name)
	{
	    _val._name = new IlString(name); _isIndex = IlFalse;
	}
	~PageID() { if (!_isIndex && _val._name) delete _val._name; }
    };

    class PageInfos
    {
    public:
	PageID			_id;
	IlvDvStringArray	_names;
	IlArray			_holders;
	/* Do Not store gadgets because they can be replaced
	 * later by AppFrame gadgets
	 */

	PageInfos(IlUInt id) : _id(id) {}
	PageInfos(const char* id) : _id(id) {}
    };

protected:
    PageInfos*		getPage(IlUInt nPage) const;
    virtual IlUInt	findPage(IlUInt, const char*) const;
    void		showPage(IlUInt nPage,
				 IlBoolean show = IlTrue,
				 IlArray* holders = 0);

    IlUInt		_selectedPage;
    IlBoolean		_fillAlways;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(dlgassoc);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Dlgassoc_H */
