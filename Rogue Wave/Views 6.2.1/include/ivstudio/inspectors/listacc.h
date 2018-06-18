// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/listacc.h
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
// Declaration of IlvStIPropertyListAccessor classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Listacc_H
#define __IlvSt_Inspectors_Listacc_H

#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif

// --------------------------------------------------------------------------
// Type definitions
typedef IlvStIProperty*  (*IlvStIPropertyConstructor)(IlAny);
typedef void           (*IlvStIPropertyCallback)(IlvStIProperty*, IlAny);
class IlvGadgetItem;
class IlvStIProxyListGadget;

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertiesAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertiesAccessor(IlvStIPropertyAccessor* accessor = 0,
			     IlvStIAccessor::UpdateMode updateMode =
						   IlvStIAccessor::Inherited,
			     IlvStIAccessor::BuildMode buildMode =
							IlvStIAccessor::None,
			     const char* name = 0);
    virtual ~IlvStIPropertiesAccessor();

    virtual IlBoolean initialize();
    virtual IlvStIProperty* get();
    virtual void	    set(const IlvStIProperty*, IlvStIEditor*);
    virtual IlvStIEditor* findFirstEditor() const;

    // ----------------------------------------------------------------------
    // Specific list methods
    virtual IlUInt getNumberOfProperties() const = 0;
    IlBoolean      isEmpty() const
	{ return getNumberOfProperties()? IlFalse : IlTrue; }

    virtual void removeProperty(IlUInt, IlBoolean = IlTrue);
    virtual void clean();

    void setSelection(IlUInt, IlvStIEditor* = 0);
    virtual IlUInt getSelection() const { return _selectionIndex; }

    virtual const char* getPropertyString(const IlvStIProperty*) const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;

    // ----------------------------------------------------------------------
    void setPropertyConstructor(IlvStIPropertyConstructor, IlAny = 0);
    void setPropertyDestructor(IlvStIPropertyCallback, IlAny = 0);

protected:

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvStIProperty* getOriginalValue();

    // Also Called by insert method
    virtual IlvStIProperty* createDefaultProperty() const;
    virtual IlBoolean    doInitialize();

    // Called by apply and set in Immediate mode
    virtual void          doApply();


    // Called by doApply
    // returns IlTrue if selection's node was modified, due to an
    // application on it
    virtual IlBoolean    applyNodes(IlUInt) = 0;


    // ----------------------------------------------------------------------
    // Array of properties
    // Methods have to be inlined because of propertect <-> some Unix
    /// compilers

    // Array of private list or tree nodes, represents properties
    // actually shown in list or tree gadgets
    IlArray _properties;

    // To be overriden by list and tree accessors
    virtual void initializeProperties() = 0;

    // ----------------------------------------------------------------------
    // Selection managment
    IlUInt        _selectionIndex;
    virtual IlAny getPropertyNode(IlUInt) const = 0;
    IlAny         getCurrentSelectionNode() const;
    void           selectEditors(IlUInt, IlvStIEditor* = 0);

    // ----------------------------------------------------------------------
    // Destruction of properties
    void cleanProperties();
    virtual void cleanNodes() = 0;
    virtual IlUInt removeSelectedNode(IlUInt) = 0;
    virtual void deleteNewProperties(IlBoolean) = 0;

    virtual void deleteNewProperty(IlvStIProperty* property);

    // Array of initial properties which have to be deleted
    IlArray _deletedNodes;
    virtual void deleteNode(IlAny);
    virtual IlBoolean canDeleteProperty(IlvStIProperty*, IlUInt) const
	{ return IlTrue; }
    IlBoolean canDeletePropertyInNode(IlAny) const;
    IlvStIPropertyCallback _destructor;
    IlAny                 _destructorParam;

    // gadget list accessors
    virtual IlUShort getFirstSelectedIndex() const
	{ return 0; }

    IlvStIPropertyConstructor _constructor;
    IlAny                    _constructorParam;

public:
    class SelectionAccessor
	: public IlvStIPropertyAccessor
    {
	friend class IlvStIPropertiesAccessor;
    protected:
	SelectionAccessor(const char* = 0,
			  IlvStIPropertiesAccessor* = 0,
			  UpdateMode = NoUpdate);
    protected:
	IlvStIPropertiesAccessor* _lstAccessor;

	virtual IlvStIProperty* getOriginalValue();
	virtual void          applyValue(IlvStIProperty*);
	virtual void          modified(IlvStIAccessor*, IlvStIAccessor*);

	// Calls _lstAccessor->copyProperty() by default
	virtual IlvStIProperty* copyProperty(const IlvStIProperty*);
	virtual IlvStIEditor* findFirstEditor() const;
    }* _selectionAccessor;
    friend class SelectionAccessor;

public:
    IlvStIPropertyAccessor* getSelectionAccessor() const
	{ return _selectionAccessor; }
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyListAccessor
    : public IlvStIPropertiesAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertyListAccessor(IlvStIPropertyAccessor* accessor = 0,
			       IlvStIAccessor::UpdateMode updateMode =
						   IlvStIAccessor::Inherited,
			       IlvStIAccessor::BuildMode buildMode =
							IlvStIAccessor::None,
			       const char* name = 0);
    virtual ~IlvStIPropertyListAccessor();

    // ----------------------------------------------------------------------
    // Specific list methods
    virtual IlUInt getNumberOfProperties() const;
    const IlvStIProperty* getProperty(IlUInt = (IlUInt)-1) const;

    virtual void insertProperty(IlUInt, IlAny = 0);
    virtual void move(IlUInt, IlUInt, IlBoolean = IlTrue);

protected:

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean applyNodes(IlUInt); // Called by doApply
    virtual IlUInt getIndex(const IlvStIProperty*) const
	{ return (IlUInt)-1; }

    // ----------------------------------------------------------------------
    // Array of properties
    // Methods have to be inlined because of propertect <-> some Unix
    // compilers

    // Array of private nodes, represents properties actually
    // shown in _lstGadget
    IlArray _properties;
    virtual void initializeProperties();

    virtual IlvStIProperty** getInitialProperties(IlUInt& count);

    // ----------------------------------------------------------------------
    // Selection managment
    virtual IlAny getPropertyNode(IlUInt) const;

    virtual IlvStIProperty* createProperty(IlUInt index,
					   IlAny data = 0) const;

    virtual IlvStIProperty* createPropertyNode(IlUInt, IlAny = 0);

    // ----------------------------------------------------------------------
    // Destruction of properties
    virtual void deleteNode(IlAny);

    virtual void deleteProperty(IlvStIProperty* property, IlUInt index);
    virtual IlUInt removeSelectedNode(IlUInt);
    virtual void deleteNewProperties(IlBoolean);
    virtual void cleanNodes();

    virtual void addProperty(IlvStIProperty* property, IlUInt index);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty,
				 IlUInt index);
    virtual void moveProperty(IlvStIProperty* property,
			      IlUInt previousIndex, IlUInt newIndex);
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyTreeAccessor
    : public IlvStIPropertiesAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertyTreeAccessor(IlvStIPropertyAccessor* accessor = 0,
			       IlvStIAccessor::UpdateMode updateMode =
						   IlvStIAccessor::Inherited,
			       IlvStIAccessor::BuildMode buildMode =
							IlvStIAccessor::None,
			       const char* name = 0);
    virtual ~IlvStIPropertyTreeAccessor();

    // ----------------------------------------------------------------------
    // Specific tree methods called by tree editors
    virtual IlUInt       getNumberOfProperties() const;
    IlUInt               getNumberOfChildrens(IlAny) const;
    IlAny                getChildItem(IlAny, IlUInt) const;
    const IlvStIProperty* getProperty(IlAny) const;
    void                  insertChildItem(IlUInt, IlAny = 0);

    virtual void insertProperty(IlAny, IlUInt, IlAny = 0);

protected:

    virtual IlUInt _getNumberOfProperties(const IlAny) const;
    // ----------------------------------------------------------------------
    // Application
    virtual IlBoolean applyNodes(IlUInt); // Overriden
    virtual IlBoolean _applyNodes(IlUInt, IlAny,
				  IlUInt&); // Called by applyNodes

    virtual IlUInt getChildPosition(const IlvStIProperty* property,
				    const IlvStIProperty* parent) const;

    virtual void addProperty(IlvStIProperty* property,
			     const IlvStIProperty* parent,
			     IlUInt index);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty,
				 const IlvStIProperty* parent,
				 IlUInt index);

    // ----------------------------------------------------------------------
    // Properties tree
    virtual void initializeProperties();
    void initializeChildProperties(IlArray&, const IlvStIProperty* = 0);

    virtual IlvStIProperty**
      getInitialChildrenProperties(IlUInt& count,
				   const IlvStIProperty* property = 0) const;

    virtual IlAny getPropertyNode(IlUInt) const;
    IlAny getPropertyNodeInfo(IlUInt, IlAny&, IlUInt&) const;
    IlAny _getPropertyNodeInfo(IlUInt&, IlAny&, IlUInt&) const;
    IlUInt getPropertyNodeIndex(IlAny, IlAny = 0, IlBoolean* = 0) const;
    IlArray& getChildNodes(IlAny);

    // ----------------------------------------------------------------------
    // Insertion of properties
    virtual IlvStIProperty* createProperty(const IlvStIProperty* parent,
					   IlUInt index,
					   IlAny data = 0) const;
    virtual IlAny createPropertyNode(IlAny, IlUInt, IlAny = 0);

    // ----------------------------------------------------------------------
    // Destruction of properties
    virtual void cleanNodes();
    virtual IlUInt removeSelectedNode(IlUInt); // Stores it as node to delete
    void removeNode(IlAny, IlAny);

    virtual void deleteNode(IlAny);
    void deleteTreeNode(IlAny, IlAny); // Called by deleteNode

    virtual void deleteChildrenProperty(IlvStIProperty* property,
					IlvStIProperty* parent);
    virtual void deleteProperty(IlvStIProperty*);
    virtual void deleteNewProperties(IlBoolean);
    virtual void deleteNewPropertyChilds(IlArray&, IlBoolean);
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_listacc)
#endif /* !__IlvSt_Inspectors_Listacc_H */
