// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/nodeval.h
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
// Declaration of the node value classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Nodeval_H)
#define __Ilv_Appframe_Nodeval_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

#if !defined(__Il_Xml_H)
#include <ilog/xml.h>
#endif

class IlvDvClass;
class IlvDvTextStream;
class IlvDvOptions;
class IlvDvCommand;
class IlvDvApplication;
class IlvDvValue;
class IlvDvStringArray;
class IlvValueTypeClass;
class IlvAbstractMenu;
class IlvMenuItem;
class IlvGadgetItem;
class IlvTransformer;
class IlXmlElementI;
class IlXmlElementI;
extern ILVDVEXPORTEDVAR(IlvValueTypeClass*) IlvValueClassInstanceType;
extern ILVDVEXPORTEDVAR(IlvValueTypeClass*) IlvValueClassInstanceArrayType;

#define GADITEM_BITMAP_COUNT 4
#ifndef COMMAND_STATE_DEFINED
#define COMMAND_STATE_DEFINED
enum IlvDvCommandState {
    Sensitive   = 0,
    Selected    = 1,
    Unsensitive = 2,
    Highlighted = 3 };
#endif /* COMMAND_STATE_DEFINED */

// --------------------------------------------------------------------------
// IlvValueClassInstanceTypeClass class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvValueClassInstanceTypeClass : public IlvValueTypeClass
{
public:
    IlvValueClassInstanceTypeClass();
    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
// IlvValueClassInstanceArrayTypeClass class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvValueClassInstanceArrayTypeClass : public IlvValueTypeClass
{
public:
    IlvValueClassInstanceArrayTypeClass();
    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
// IlvDvNodeValue class
// --------------------------------------------------------------------------
#define NODE_CREATED		    (IlShort)0
#define NODE_FROM_STREAM	    (IlShort)1
#define NODE_MODIFIED		    (IlShort)2
#define NODE_PRESERVE_WHITESPACES   (IlShort)4

class ILVDVCLASS IlvDvNodeValueArray;

class ILVDVCLASS IlvDvNodeValue : public IlvValue, public IlXmlElementI
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvNodeValue();
    IlvDvNodeValue(const IlvDvNodeValue& src);
    IlvDvNodeValue(const IlvValue*);
    IlvDvNodeValue(const char*,
		   const IlvDvClass*,
		   IlBoolean isArray = IlFalse);
    IlvDvNodeValue(const char*,
		   const IlvDvNodeValueArray&,
		   IlBoolean copyAll = IlTrue,
		   IlBoolean canDeleteAll = IlTrue);
    IlvDvNodeValue(const char* name, IlInt n);
    IlvDvNodeValue(const char* name, IlBoolean b);
    IlvDvNodeValue(const char* name, IlFloat f);
    IlvDvNodeValue(const char* name, IlDouble d);
    IlvDvNodeValue(const char* name, const char* s);
    IlvDvNodeValue(const char* name, IlAny p);
    virtual ~IlvDvNodeValue();
    virtual
    IlvDvNodeValue*	copy() const;

    // ----------------------------------------------------------------------
    // Class instances operations
    void		copyValue(const IlvDvNodeValue&);
    void		addChildValue(IlvDvNodeValue* child);
    void		insertChildValue(IlUInt index, IlvDvNodeValue* child);
    void		removeChild(const char* childName,
				    IlBoolean deleteIt = IlTrue);
    void		removeChild(IlUInt index, IlBoolean deleteIt = IlTrue);
    void		removeChild(IlvDvNodeValue* child,
				    IlBoolean deleteIt = IlTrue);
    void		removeChilds();
    IlvDvNodeValue*	getChild(const char* childName) const;
    IlvDvNodeValue*	getChild(const IlSymbol* childName) const;
    IlvDvNodeValue*	getChild(IlUInt index) const;
    IlUInt		getChildsCount() const;
    IlBoolean		getChildRect(const char* name, IlvRect& rect) const;
    void		setChildRect(const char* name, const IlvRect& rect);
    IlBoolean		getChildPoint(const char* name, IlvPoint& pt) const;
    void		setChildPoint(const char* name, const IlvPoint& pt);

    IlBoolean		getChildSize(const char* name, IlvPoint& pt) const;
    void		setChildSize(const char*, const IlvPoint& pt);

    IlvPosition		getChildPosition(const char* name) const;
    void		setChildPosition(const char* name, IlvPosition);

    const IlvDvClass*	getClass() const;
    IlBoolean		isPrimaryType() const;
    IlBoolean		isClassInstance() const;
    IlBoolean		isValueArray() const;
    const char*		getValueClassname() const;
    IlBoolean		isEqualValue(const IlvDvNodeValue*) const;
    const IlvValue&	getChildValue(const char* childName) const;
    const IlvValue&	getChildValue(const IlSymbol* fieldName) const;
    void		setChildValue(const char* name,
				      const IlvDvValue& value);
    void		setChildValue(const IlSymbol* name,
				      const IlvDvValue& value);

    void		setChildTransformer(const char*,
					    const IlvTransformer*);
    IlvTransformer*	getChildTransformer(const char*) const;

    void		setTypeOnOptions(const char* strTypename,
					 const IlvDvOptions*);
    IlvDvNodeValueArray*	getValues() const;
    void		ensureAllFields();
    void		mergeFields(IlvDvNodeValue* node);

    // ----------------------------------------------------------------------
    // Serialization
    void		serialize(IlvDvTextStream&,
				  IlvDvOptions*,
				  IlBoolean bWithType = IlTrue,
				  IlBoolean bWithName = IlTrue,
				  IlBoolean bWithValue = IlTrue);

    // ----------------------------------------------------------------------
    // XML interface implementation

    virtual const char*	getTag() const;
    virtual void	addChild(IlXmlNodeI* node);
    virtual
    IlXmlElementI*	createChildElement(char* tag) const;
    virtual void	storeAttribute(IlXmlDocumentI* document,
				       char* name,
				       char* value);
    // ----------------------------------------------------------------------
    // getState returns one of following values:
    //			NODE_CREATED, NODE_FROM_STREAM, NODE_MODIFIED
    inline IlShort	getState() const { return _state; }
    IlBoolean		isModified(IlBoolean scanFields = IlTrue) const;
    void		setModified(IlBoolean = IlTrue);

protected:
    void		clean();
    IlShort		_state;
    void		setState(IlShort, IlBoolean set = IlTrue);

    // ----------------------------------------------------------------------
    virtual
    IlXmlNodeIteratorI*	createChildrenIterator() const;
    virtual
    IlXmlNodeIteratorI*	createAttributesIterator() const;
    void		storeTag(char* tag);

    // ----------------------------------------------------------------------
public:
    enum NodeValueType { 
	    Declaration,
	    ClassField, /* It is a field of a DvClass */
	    Value, /* It is an attribute, it is weither
				    - an integer value 
				    - a string
				    - a double
				    - a boolean 
				    - a float */
	    AggregateValue /* It is an instance of a DvClass */
    };
    virtual
    NodeValueType	getNodeValueType() const;
};

// --------------------------------------------------------------------------
// IlvDvNodeDeclaration class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvNodeDeclaration : public IlvDvNodeValue
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvNodeDeclaration();
    IlvDvNodeDeclaration(const char* name,
			 const IlvDvClass*,
			 IlBoolean isArray = IlFalse);
    IlvDvNodeDeclaration(const char* name, IlInt);
    IlvDvNodeDeclaration(const char* name, IlBoolean);
    IlvDvNodeDeclaration(const char* name, const char*);
    IlvDvNodeDeclaration(const char* name, IlFloat);
    IlvDvNodeDeclaration(const char* name, IlDouble);
    IlvDvNodeDeclaration(const IlvDvNodeDeclaration&);

    // ----------------------------------------------------------------------
    virtual IlvDvNodeValue*	copy() const;
    virtual const char*		getTag() const;

protected:
    virtual NodeValueType	getNodeValueType() const;
};

// --------------------------------------------------------------------------
// IlvDvClassField class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvClassField : public IlvDvNodeValue
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvClassField();

protected:
    virtual NodeValueType	getNodeValueType() const;
    virtual IlXmlNodeIteratorI*	createAttributesIterator() const;
};

// --------------------------------------------------------------------------
// IlvDvNodeValueArray
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvNodeValueArray : public IlvArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvNodeValueArray(IlBoolean canDelete = IlTrue,
		       IlUInt initialLength = 8);
    IlvDvNodeValueArray(const IlvDvNodeValueArray&);
    IlvDvNodeValueArray(const IlvDvNodeValueArray&,
		       IlBoolean copyAll,
		       IlBoolean canDelete);
    ~IlvDvNodeValueArray();

    // ----------------------------------------------------------------------
    // Main operations
    void		addNodeValue(IlvDvNodeValue* var,
				     IlBoolean check = IlTrue);
    void		mergeNodeValue(IlvDvNodeValue* var);
    void		insertNodeValue(IlUInt index, IlvDvNodeValue* var);
    void		removeNodeValue(IlvDvNodeValue*,
					IlBoolean deleteIt = IlTrue);
    void		removeNodeValue(const char*,
					IlBoolean deleteIt = IlTrue);
    void		removeNodeValue(IlUInt, IlBoolean deleteIt = IlTrue);
    IlvDvNodeValue*	getNodeValue(const char*) const;
    IlvDvNodeValue*	getNodeValue(const IlSymbol*) const;
    IlvDvNodeValue*	getNodeValue(IlUInt) const;
    void		removeVariables();
    IlBoolean		isModified(IlBoolean scanFields = IlTrue) const;

    // ----------------------------------------------------------------------
    // Serialization
    void		serializeInText(IlvDvTextStream&,
					IlvDvOptions*,
					IlBoolean bWithType = IlTrue,
					IlBoolean bWithName = IlTrue,
					IlBoolean bWithValue = IlTrue,
					const IlvDvClass* pClass = 0);

protected:
    IlBoolean		_canDelete;
};

// --------------------------------------------------------------------------
// IlvDvClass class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvClass : public IlXmlElementI, public IlvDvSerializable
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvClass(const IlSymbol* = 0, IlvDvNodeValue* = 0);
    IlvDvClass(ILVSTDPREF istream& is);
    virtual ~IlvDvClass();

    // ----------------------------------------------------------------------
    // Main operations
    void		initializeInstance(IlvDvNodeValue*) const;
    void		ensureAllFields(IlvDvNodeValue*) const; 
			// Same as initializeInstance except that it looks for
			// existing fields before.

    // ----------------------------------------------------------------------
    // Basic properties
    inline
    const IlSymbol*	getSName() const { return _name; }
    IlUInt		getNonDefaultFields(const IlvDvNodeValue* var,
					    IlvDvNodeValueArray&) const;
    IlBoolean		isModified() const;
    inline
    const IlvDvNodeValueArray&	getFields() const { return _fields; }
    IlvDvNodeValue*	getNodeValue(const char* name,
				     IlBoolean findInSuperclasses=IlTrue)const;
    inline
    const IlvArray&	getSuperclasses() const { return _superclasses; }
    // ----------------------------------------------------------------------
    // Serialization
    void		serializeInText(IlvDvTextStream&, IlvDvOptions*);
    void		serializeInstanceValue(IlvDvTextStream&,
					       IlvDvNodeValue*,
					       IlvDvOptions*) const;
    void		endInitializeFromXML(IlvDvOptions* options);
    // ----------------------------------------------------------------------
    // IlXmlElementI overridables
    virtual const char*	getTag() const;
    virtual void	storeTag(char* tag);
    virtual
    IlXmlElementI*	createChildElement(char* tag) const;
    virtual void	addChild(IlXmlNodeI* node);
    virtual void	storeAttribute(IlXmlDocumentI* document,
				       char* name,
				       char* value);

protected:
    const IlSymbol*	_name;
    IlvArray		_superclasses;
    IlvDvNodeValueArray	_fields; // Array of IlvDvNodeValue

    virtual
    IlXmlNodeIteratorI*	createChildrenIterator() const;
    virtual
    IlXmlNodeIteratorI*	createAttributesIterator() const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(nodeval);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Nodeval_H */
