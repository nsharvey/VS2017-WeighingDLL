// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/dlgcmd.h
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
#if !defined(__Ilv_Appframe_Dialog_Dlgcmd_H)
#define __Ilv_Appframe_Dialog_Dlgcmd_H

#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class IlvDvInspector;
class IlvDvDialogAssoc;
class IlvDvGadgetAssoc;
class IlvDvAbstractListAssoc;
class IlvDvListGadgetAssoc;
class IlvDvTreeGadgetAssoc;
class IlvDvNodeValue;
class IlvDvClass;
class IlvGadgetItem;
class IlvTreeGadget;
class IlvTreeGadgetItem;

// --------------------------------------------------------------------------
// IlvDvDialogCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDialogCommand : public IlvDvCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDialogCommand(IlvDvInspector*, const char* name = 0);
    IlvDvDialogCommand(const IlvDvDialogCommand&);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doIt();
    virtual void		undo();
   // ----------------------------------------------------------------------
    virtual IlvDvNodeValue*	getNodeValue() const;
    virtual IlvDvDialogAssoc*	getDialogAssoc() const;
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

protected:
    IlvDvInspector*		_inspector;
};

// --------------------------------------------------------------------------
// IlvDvDialogAssocCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDialogAssocCommand : public IlvDvDialogCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDialogAssocCommand(IlvDvDialogAssoc*, const char* name = 0);
    IlvDvDialogAssocCommand(const IlvDvDialogAssocCommand&);
    ~IlvDvDialogAssocCommand();

    // ----------------------------------------------------------------------
    virtual IlvDvNodeValue*	getNodeValue() const;
    const IlSymbol*		getDataKey() const;
    virtual IlvDvDialogAssoc*	getDialogAssoc() const = 0;

    virtual void		doIt();
    virtual void		undo();

protected:
    IlvDvNodeValue*		_var;
    void			setNodeValue(const IlvDvNodeValue* src) const;
};

// --------------------------------------------------------------------------
// IlvDvGadgetModifCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvGadgetModifCommand : public IlvDvDialogAssocCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvGadgetModifCommand(IlvDvGadgetAssoc*);
    IlvDvGadgetModifCommand(const IlvDvGadgetModifCommand&);
    ~IlvDvGadgetModifCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

   // ----------------------------------------------------------------------
    void			newState();
    void			applyData(IlvDvNodeValue*);

protected:
    IlvDvNodeValue*		_orig;
    IlvDvNodeValue*		_modified;
    IlvDvGadgetAssoc*		_assoc;
    IlBoolean			_needToUpdateGadget;

    virtual IlvDvDialogAssoc*	getDialogAssoc() const;
};

// --------------------------------------------------------------------------
// IlvDvListModifCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListModifCommand : public IlvDvDialogAssocCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListModifCommand(IlvDvListGadgetAssoc*, IlAny param = 0);
    IlvDvListModifCommand(const IlvDvListModifCommand&);

    // ----------------------------------------------------------------------

protected:
    IlvDvListGadgetAssoc*	_assoc;
    IlAny			_param;

    virtual IlvDvDialogAssoc*	getDialogAssoc() const;
    IlvGadgetItem*		getGadgetItem(IlUInt) const;
    IlvGadgetItem*		createGadgetItem(IlvDvNodeValue*,
						 IlUInt) const;
};

// --------------------------------------------------------------------------
// IlvDvListMoveCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListMoveCommand : public IlvDvListModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListMoveCommand(IlvDvListGadgetAssoc*,
			 IlUShort,
			 IlUShort,
			 IlAny param = 0);
    IlvDvListMoveCommand(const IlvDvListMoveCommand&);
    ~IlvDvListMoveCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();
    void			moveGadget(IlUShort origPos, IlUShort newPos);
    void			moveData(IlUShort origPos, IlUShort newPos);

protected:
    IlUShort			_origPos;
    IlUShort			_newPos;
};

// --------------------------------------------------------------------------
// IlvDvListInsertRemoveCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListInsertRemoveCommand : public IlvDvListModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListInsertRemoveCommand(IlvDvListGadgetAssoc*,
			         IlUShort,
			         const IlvDvClass*,
			         IlAny param);
    IlvDvListInsertRemoveCommand(IlvDvListGadgetAssoc*,
			         IlUShort,
			         IlAny param);
    IlvDvListInsertRemoveCommand(const IlvDvListInsertRemoveCommand&);
    ~IlvDvListInsertRemoveCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

    void			insertGadget();
    void			removeGadget();
    void			insertData();
    void			removeData();

protected:
    IlBoolean			_removeCommand;
    IlUShort			_index;
    IlvDvNodeValue*		_newRemovedVar;
    IlvDvNodeValue*		_newRemovedDataVar;
    IlBoolean			_dataVarInserted;
    IlBoolean			_varInserted;
};

// --------------------------------------------------------------------------
// IlvDvListCleanCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListCleanCommand : public IlvDvListModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListCleanCommand(IlvDvListGadgetAssoc*, IlAny param = 0);
    IlvDvListCleanCommand(const IlvDvListCleanCommand&);
    ~IlvDvListCleanCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

protected:
    IlArray			_deletedVars;
    IlBoolean			_varRemoved;
    IlUShort			_oldSelection;
    IlBoolean			_dataVarRemoved;
    IlArray			_deletedDataVars;

    IlvDvNodeValue*		getDeletedVar(IlUInt) const;
    IlvDvNodeValue*		getDeletedDataVar(IlUInt) const;

};

// --------------------------------------------------------------------------
// IlvDvListCheckCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListCheckCommand : public IlvDvListModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListCheckCommand(IlvDvListGadgetAssoc*,
			  IlUInt index,
			  IlBoolean state,
			  IlAny param = 0);
    IlvDvListCheckCommand(const IlvDvListCheckCommand&);
    ~IlvDvListCheckCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

protected:
    IlUInt			_index;
    IlBoolean			_state;
    IlBoolean			_needToUpdateGadget;
};

// --------------------------------------------------------------------------
// IlvDvListEndEditCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListEndEditCommand : public IlvDvDialogAssocCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListEndEditCommand(IlvDvAbstractListAssoc*,
			    IlvGadgetItem*,
			    const char* previousLabel,
			    const char* newLabel,
			    IlAny param = 0);
    IlvDvListEndEditCommand(const IlvDvListEndEditCommand&);
    ~IlvDvListEndEditCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

    void			setItemLabel(const char*, const char*);
    void			setDataLabel(const char*, const char*);

protected:
    IlvDvAbstractListAssoc*	_listAssoc;
    IlvGadgetItem*		_gadgetItem;
    IlString			_origLabel;
    IlString			_newLabel;

    virtual IlvDvDialogAssoc*	getDialogAssoc() const;
};

// --------------------------------------------------------------------------
// IlvDvTreeModifCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeModifCommand : public IlvDvDialogAssocCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeModifCommand(IlvDvTreeGadgetAssoc*, IlAny param = 0);
    IlvDvTreeModifCommand(const IlvDvTreeModifCommand&);

    // ----------------------------------------------------------------------

protected:
    IlvDvTreeGadgetAssoc*	_assoc;
    IlAny			_param;

    virtual IlvDvDialogAssoc*	getDialogAssoc() const;
    IlvTreeGadget*		getTreeGadget() const;
    IlvDvNodeValue*		getItemVariable(IlvTreeGadgetItem*) const;
    IlvTreeGadgetItem*		createGadgetItem(IlvDvNodeValue*,
						 IlUInt index,
						 IlvTreeGadgetItem* parent)
						 const;
    IlvDvNodeValue*		getItemDataVariable(IlvTreeGadgetItem*) const;
};

// --------------------------------------------------------------------------
// IlvDvTreeMoveCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeMoveCommand : public IlvDvTreeModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeMoveCommand(IlvDvTreeGadgetAssoc*,
			 IlvTreeGadgetItem*,
			 IlvTreeGadgetItem*,
			 IlUShort mode = 1,
			 IlAny param = 0);
    IlvDvTreeMoveCommand(const IlvDvTreeMoveCommand&);
    ~IlvDvTreeMoveCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

    void			moveItem(IlvTreeGadgetItem* fromParent,
					 IlUInt fromPos,
					 IlvTreeGadgetItem* toParent,
					 IlUInt toPos);
    void			moveData(IlvTreeGadgetItem* movedItem,
					 IlvTreeGadgetItem* fromParent,
					 IlUInt fromPos,
					 IlvTreeGadgetItem* toParent,
					 IlUInt toPos);

protected:
    IlvTreeGadgetItem*		_movedItem;
    IlvTreeGadgetItem*		_newParent;
    IlUInt			_newItemPos;
    IlvTreeGadgetItem*		_oldParent;
    IlUInt			_oldItemPos;
};

// --------------------------------------------------------------------------
// IlvDvTreeInsertRemoveCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeInsertRemoveCommand : public IlvDvTreeModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeInsertRemoveCommand(IlvDvTreeGadgetAssoc*,
			         IlvTreeGadgetItem* parentItem,
			         IlUInt index,
			         const IlvDvClass* = 0,
			         IlAny param = 0);
    IlvDvTreeInsertRemoveCommand(IlvDvTreeGadgetAssoc*,
				 IlvTreeGadgetItem* deleteItem,
			         IlAny param = 0);
    IlvDvTreeInsertRemoveCommand(const IlvDvTreeInsertRemoveCommand&);
    ~IlvDvTreeInsertRemoveCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

    void			insertGadget();
    void			removeGadget();
    void			insertData();
    void			removeData();

protected:
    IlBoolean			_removeCommand;
    IlvTreeGadgetItem*		_parentItem;
    IlvTreeGadgetItem*		_insertedItem;
    IlUInt			_index;
    IlvDvNodeValue*		_newRemovedVar;
    IlBoolean			_varInserted;
    IlvDvNodeValue*		_newRemovedDataVar;
    IlBoolean			_dataVarInserted;
};

// --------------------------------------------------------------------------
// IlvDvTreeCleanCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeCleanCommand : public IlvDvTreeModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeCleanCommand(IlvDvTreeGadgetAssoc*,
			  IlvTreeGadgetItem* parent,
			  IlAny param = 0);
    IlvDvTreeCleanCommand(const IlvDvTreeCleanCommand&);
    ~IlvDvTreeCleanCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

protected:
    IlvTreeGadgetItem*		_parentItem;
    IlArray			_insertedItems;
    IlvTreeGadgetItem*		_oldSelection;
    IlArray			_deletedVars;
    IlArray			_deletedDataVars;
    IlBoolean			_varRemoved;
    IlBoolean			_dataVarRemoved;
    IlvDvNodeValue*		getDeletedVar(IlUInt) const;
};

// --------------------------------------------------------------------------
// IlvDvTreeCheckCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeCheckCommand : public IlvDvTreeModifCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeCheckCommand(IlvDvTreeGadgetAssoc*,
			  IlvTreeGadgetItem* treeItem,
			  IlBoolean state,
			  IlAny param = 0);
    IlvDvTreeCheckCommand(const IlvDvTreeCheckCommand&);
    ~IlvDvTreeCheckCommand();
    virtual IlvDvCommand*	copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		doItGadget();
    virtual void		undoGadget();
    virtual void		doItData();
    virtual void		undoData();

protected:
    IlvTreeGadgetItem*		_treeItem;
    IlUInt			_index;
    IlBoolean			_state;
    IlBoolean			_needToUpdateGadget;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(dlgcmd);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Dlgcmd_H */
