// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/listedt.h
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
// Declaration of properties list and properties tree editors
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Listedt_H)
#define __IlvSt_Inspectors_Listedt_H

#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif

// --------------------------------------------------------------------------
class IlvTreeGadget;
class IlvTreeGadgetItem;
class IlvStIPropertiesAccessor;
class IlvStIPropertyListAccessor;
class IlvStIPropertyTreeAccessor;
class IlvGadget;
class IlvListGadgetItemHolder;

typedef const char* (*IlvStIPropertyNameCallback)(const IlvStIProperty*,
						  IlAny);
typedef IlvGadgetItem* (*IlvStIGadgetItemConstructor)(const IlvStIProperty*,
						      IlAny);

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertiesEditor
    : public IlvStIPropertyEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertiesEditor(IlvStIPropertiesAccessor* accessor = 0,
			   const char* name = 0);
    virtual ~IlvStIPropertiesEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean  connectHolder(IlvGraphicHolder*);
    virtual IlBoolean	initialize();
    virtual void        setState(State = Active, IlBoolean = IlTrue);
    virtual void        setModified(IlBoolean = IlTrue);
    // ----------------------------------------------------------------------
    void setPropertyNamer(IlvStIPropertyNameCallback, IlAny = 0);
    void setGadgetItemConstructor(IlvStIGadgetItemConstructor, IlAny = 0);

    // ----------------------------------------------------------------------
    virtual IlvStIPropertiesAccessor* getAbsListAccessor() const;
    virtual IlvStIPropertyAccessor*   getSelectionAccessor() const;

    // ----------------------------------------------------------------------
    // Methods called by list accessor
    virtual void remove(IlUInt) = 0;
    virtual void setItemSelected(IlUInt) = 0;
    void focusFirstEditor();

    virtual IlvGadget* getListGadget() const = 0;
    virtual IlBoolean isEmpty() const = 0;

protected:
    // Gadgets used to edit list
    IlString            _addAfterName;
    IlString            _removeName;
    IlString            _addBeforeName;
    IlString            _cleanName;

    // gadget list accessors
    virtual IlBoolean  isGadgetItemHolder() const = 0;
    IlUShort getSelectedItem() const;

    virtual void refreshSelection() = 0;

    virtual void addAfter(IlAny = 0) = 0;
    virtual void addBefore(IlAny = 0) = 0;
    void removeCallback();
    void cleanList();

    virtual void fillGadget() = 0;

    virtual const char* getPropertyString(const IlvStIProperty*) const;
    IlvStIPropertyNameCallback _namer;
    IlAny	             _namerParam;

    IlvStIGadgetItemConstructor _gadgetItemConstructor;
    IlAny	                _giConstructorParam;

public: // Due to some Unix compilers
    // ----------------------------------------------------------------------
    //Internal callbacks
    static void SelectItemCallback(IlvGraphic*, IlAny);
    virtual void selectedItemCallback() = 0;
    static void AddAfterCallback(IlvGraphic*, IlAny);
    static void AddBeforeCallback(IlvGraphic*, IlAny);
    static void RemoveCallback(IlvGraphic*, IlAny);
    static void CleanCallback(IlvGraphic*, IlAny);
    static void MoveUpCallback(IlvGraphic*, IlAny);
    static void MoveDownCallback(IlvGraphic*, IlAny);

protected:
    virtual IlvGraphicHolder* getGraphicHolder() const = 0;
    void setGadgetSensitive(const char*, IlBoolean = IlTrue);
    virtual void propertyCountChanged(IlUInt, int) {}
    // flag = 1: adding, flag = 0: initializing, flag = -1: removing
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyListEditor
    : public IlvStIPropertiesEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertyListEditor(IlvStIPropertyListAccessor* accessor = 0,
			     const char* name = 0);
    virtual ~IlvStIPropertyListEditor();

    // ----------------------------------------------------------------------
    void declareGadgets(const char* listName,
			const char* addAfterName = 0,
			const char* removeName = 0,
			const char* addBeforeName = 0,
			const char* cleanName = 0,
			const char* moveUpName = 0,
			const char* moveDownName = 0);

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean  connectHolder(IlvGraphicHolder*);
    virtual void        empty();

    // ----------------------------------------------------------------------
    // Methods called by list accessor
    void insert(IlUInt, const IlvStIProperty*);
    void remove(IlUInt);
    virtual void moveItem(IlUInt, IlUInt);
    virtual void setItemSelected(IlUInt);

    virtual IlvGadget*          getListGadget() const;
    IlvStIProxyListGadget*      getProxyList() const { return _lstGadget; }

    IlvListGadgetItemHolder*    getListGadgetItemHolder() const;


    IlvStIPropertyListAccessor* getListAccessor() const;

    virtual IlBoolean        isEmpty() const;
    virtual IlvDisplay*       getDisplay() const;

protected:

    // Gadgets used to edit list
    IlvStIProxyListGadget* _lstGadget;
    IlString              _listName;
    IlString              _moveUpName;
    IlString              _moveDownName;

    // gadget list accessors
    virtual IlBoolean isGadgetItemHolder() const;
    virtual void       refreshSelection();

    virtual IlvGadgetItem*
		      createGadgetItem(const IlvStIProperty* property) const;

    virtual void itemSelected(IlUInt, const IlvStIProperty*);
    // flag = 1: adding, flag = 0: initializing, flag = -1: removing
    virtual void propertyCountChanged(IlUInt, int);
    virtual void fillGadget();

public: // Due to some Unix compilers
    // ----------------------------------------------------------------------
    //Internal callbacks
    virtual void selectedItemCallback();
    virtual void addAfter(IlAny = 0);
    virtual void addBefore(IlAny = 0);
    virtual void insertNewItem(IlUInt, IlAny = 0);
    virtual void moveUpDownCallback(IlBoolean);
    virtual void moveCallback(IlUInt, IlUInt);
    static void MoveUpCallback(IlvGraphic*, IlAny);
    static void MoveDownCallback(IlvGraphic*, IlAny);

protected:
    virtual IlvGraphicHolder* getGraphicHolder() const;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyTreeEditor
    : public IlvStIPropertiesEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertyTreeEditor(IlvStIPropertyTreeAccessor* accessor = 0,
			     const char* name = 0);
    virtual ~IlvStIPropertyTreeEditor();

    void declareGadgets(const char* treeName,
			const char* addAfterName = 0,
			const char* removeName = 0,
			const char* addChildName = 0,
			const char* addBeforeName = 0,
			const char* cleanName = 0);

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean  connectHolder(IlvGraphicHolder*);
    virtual void        empty();
    virtual void        setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Methods called by list accessor
    void insertTreeItem(IlAny, IlUInt, IlAny, const IlvStIProperty*);
    void remove(IlUInt);
    virtual void setItemSelected(IlUInt);
    virtual IlvGadget* getListGadget() const;

    IlvTreeGadget* getTreeGadget() const;
    IlvStIPropertyTreeAccessor* getTreeAccessor() const;
    virtual IlBoolean isEmpty() const;

    virtual IlvDisplay* getDisplay() const;

    // flag = 1: adding, flag = 0: initializing, flag = -1: removing
    virtual void propertyCountChanged(IlUInt, int);

protected:

    // Gadgets used to edit tree
    IlvTreeGadget*    _treeGadget;
    IlvGraphicHolder* _graphicHolder;
    IlString         _treeName;
    IlString         _addChildName;

    // gadget tree accessors
    virtual IlBoolean isGadgetItemHolder() const;
    virtual void       refreshSelection();

    virtual IlvGadgetItem*
		      createGadgetItem(const IlvStIProperty* property) const;

    virtual void treeItemSelected(IlvTreeGadgetItem*    item,
				  const IlvStIProperty* property,
				  const IlvStIProperty* parent);

    IlvTreeGadgetItem* getGadgetItemAtIndex(IlUInt) const;
    IlvTreeGadgetItem* getGadgetItemAtIndex(IlUInt&,
					    IlvTreeGadgetItem*&) const;
    IlUInt            getGadgetItemIndex(const IlvTreeGadgetItem*) const;
    IlUInt            getGadgetItemIndex(const IlvTreeGadgetItem*,
					 IlvTreeGadgetItem*,
					 IlBoolean&) const;
    IlvTreeGadgetItem* getTreeNodeGadgetItem(IlAny,
					     IlvTreeGadgetItem* = 0) const;

    virtual void fillGadget();

    // Used by IlvTreeGadget
    void fillGadgetItems(IlAny, IlvTreeGadgetItem*);

public: // Due to some Unix compilers
    // ----------------------------------------------------------------------
    //Internal callbacks
    virtual void selectedItemCallback();
    static void AddChildCallback(IlvGraphic*, IlAny);
    virtual void addChildCallback(IlAny = 0);
    void addAfter(IlAny = 0);
    void addBefore(IlAny = 0);
    virtual void addTreeItem(IlBoolean, IlAny = 0);
    virtual void insertNewTreeItem(IlAny, IlUInt, IlAny = 0);

protected:
    virtual IlvGraphicHolder* getGraphicHolder() const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_listedt)
#endif /* !__IlvSt_Inspectors_Listedt_H */
