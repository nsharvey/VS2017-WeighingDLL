// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/proplist.h
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
// Declaration of the IlvNamedProperty and IlvPropertyList classes, with
// their related macros.
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Proplist_H
#define __Ilv_Util_Proplist_H

#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif

class IlSymbol;
class IlvOutputFile;
class IlvInputFile;

// --------------------------------------------------------------------------
#define DeclarePropertyInfoRO_()				\
    static IlvNamedProperty* read(IlvInputFile&, IlSymbol* s);	\
    virtual IlvNamedProperty* copy() const
#define DeclarePropertyInfoRO() IlvDeclarePropClassInfo();	\
    DeclarePropertyInfoRO_()
#define DeclareLazyPropertyInfoRO() IlvDeclareLazyPropClassInfo();\
    DeclarePropertyInfoRO_()

#define DeclarePropertyInfo() DeclarePropertyInfoRO();	\
    virtual void write(IlvOutputFile&) const
#define DeclareLazyPropertyInfo() DeclareLazyPropertyInfoRO();	\
    virtual void write(IlvOutputFile&) const

#define DeclarePropertyIOConstructors(classname) public:	\
    classname(IlvInputFile& file, IlSymbol* s = 0);		\
    classname(const classname& source)

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvNamedProperty : public IlvValueInterface
{
public:
    IlvNamedProperty(IlSymbol*);
    virtual ~IlvNamedProperty();

    inline const char*	getName() const { return _symbol->name(); }
    inline IlSymbol*	getSymbol() const { return _symbol; }
    virtual
    const IlSymbol*	getValueName() const;
    virtual IlBoolean	isPersistent() const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvNamedProperty);

protected:
    IlSymbol*		_symbol;
};

// --------------------------------------------------------------------------
// - IlvNamedPropertySet: Handles a collection of IlvNamedProperty and 
// - implements the equivalent of some of IlvNamedProperty methods in terms of 
// - a combination of these method calls on the handled properties.
// - For example, a set is persistent if at least one of its handled property
// - is persistent. This class is useful when you want to set several 
// - times the same kind of property on an object (ex: apply listener). 
class ILVVWSEXPORTED IlvNamedPropertySet
{
public:
    IlvNamedPropertySet();
    IlvNamedPropertySet(const IlvNamedPropertySet&);
    IlvNamedPropertySet(IlvInputFile&);
    ~IlvNamedPropertySet();

    inline IlList&	getProperties() { return _properties; }
    inline
    const IlList&	getProperties() const { return _properties; }
    IlBoolean		isPersistent() const;
    void		propertyAdded(IlAny);
    void		propertyRemoved();
    void		write(IlvOutputFile&) const;

    void		add(IlvNamedProperty* np, IlAny holder = 0);
    void		add(const IlvNamedPropertySet& set, IlAny holder = 0);
    IlvNamedProperty*	remove(IlvNamedProperty* np,
			       IlBoolean notif = IlFalse);

    inline
    IlvNamedProperty*	operator[](int idx) 
			{
			    return IL_CAST(IlvNamedProperty*,
					   getProperties()[idx]);
			}
    inline
    const IlvNamedProperty*	operator[](int idx) const 
				{
				    return IL_CAST(IlvNamedProperty*,
						   getProperties()[idx]);
				}
private:
    IlList		_properties;
};

// --------------------------------------------------------------------------
typedef IlvNamedProperty* (* IlvPropertyConstructor)(IlvInputFile&,
						     IlSymbol*);

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPropertyClassInfo : public IlvValuedClassInfo
{
public:
    IlvPropertyClassInfo(const char*		className,
			 IlvPropertyClassInfo*	alias)
    : IlvValuedClassInfo(className, alias->_superClass, alias->_getAccessors),
      _constructor(alias->_constructor)
    {}

    inline
    IlvPropertyConstructor	getConstructor() const { return _constructor; }
    static
    IlvPropertyClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvPropertyConstructor,
				       IlvGetAccessorsFunction = 0);

protected:
    IlvPropertyClassInfo(const char*			className,
			 IlvClassInfo**			superClass,
			 IlvPropertyConstructor		constructor,
			 IlvGetAccessorsFunction	getAccessors = 0)
    : IlvValuedClassInfo(className, superClass, getAccessors),
      _constructor(constructor) {}
    IlvPropertyConstructor _constructor;
};

#define IlvPreRegisterPropertyClass(classname)	\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterPropertyClass(classname, superclass)			\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	    IlvPropertyClassInfo::Create(#classname,			\
					 superclass::ClassPtr(),	\
					 (IlvPropertyConstructor)	\
					 classname::read))
#define IlvRegisterPropertyClassWithAccessors(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	     IlvPropertyClassInfo::Create(#classname,			\
					  superclass::ClassPtr(),	\
					  (IlvPropertyConstructor)	\
					  classname::read,		\
					  classname::GetAccessors))
#define IlvPostRegisterPropertyClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	   IlvPropertyClassInfo::Create(#classname,			\
					superclass::ClassPtr(),		\
					(IlvPropertyConstructor)	\
					classname::read))
#define IlvPostRegisterPropertyClassWithAccessors(classname, superclass)\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	   IlvPropertyClassInfo::Create(#classname,			\
					superclass::ClassPtr(),		\
					(IlvPropertyConstructor)	\
					classname::read,		\
					classname::GetAccessors))
#define IlvPredefinedPropertyIOMembers(classname) \
IlvNamedProperty* classname::copy() const { return new classname(*this); } \
IlvNamedProperty* classname::read(IlvInputFile& i, IlSymbol* s)		\
{ return new classname(i, s); }

#define IlvPostRegisterPropertyClassAlias(classname, a)			\
IlvPropertyClassInfo::Create(#classname, (IlvPropertyClassInfo*)a::ClassPtr())
#define IlvRegisterPropertyClassAlias(classname, alias)			\
static IlvPropertyClassInfo* classname##_info =				\
    IlvPostRegisterPropertyClassAlias(classname, alias)

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvNamedPropertyList : public IlvNamedProperty
{
public:
    IlvNamedPropertyList(IlSymbol*);
    virtual ~IlvNamedPropertyList();

    inline IlList&	getProperties() { return _set.getProperties(); }
    inline
    const IlList&	getProperties() const
			{
			    return _set.getProperties();
			}
    void		add(IlvNamedProperty*, IlAny holder = 0);
    IlvNamedProperty*	remove(IlvNamedProperty*, IlBoolean = IlFalse);
    virtual IlBoolean	isPersistent() const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();
    virtual
    const IlSymbol*	getValueName() const;
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvNamedPropertyList);

protected:
    IlvNamedPropertySet	_set;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvStringProperty : public IlvNamedProperty
{
public:
    IlvStringProperty(IlSymbol* symbol, const char* string = 0);
    ~IlvStringProperty();

    void		setString(const char* str);
    inline const char*	getString() const { return _string; }
    virtual
    const IlSymbol*	getValueName() const;

    static IlSymbol*	StringValue();

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvStringProperty);

private:
    char*		_string;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPropertyList
{
public:
    IlvPropertyList() : _properties(0) {}
    ~IlvPropertyList();

    inline void		addProperty(const IlSymbol* key , IlAny value)
			{
			    if (!_properties)
				_properties = new IlAList();
			    _properties->insert((IlAny)key, value);
			}
    inline void		setProperty(const IlSymbol* key , IlAny value)
			{
			    if (value) {
				if (!replaceProperty(key, value))
				    addProperty(key, value);
			    }
			    else removeProperty(key);
			}
    inline IlBoolean	removeProperty(const IlSymbol* key)
			{
			    return _properties
				? (_properties->remove((IlAny)key), IlTrue)
				: IlFalse;
			}
    inline IlBoolean	replaceProperty(const IlSymbol* key , IlAny value)
			{
			    return _properties
				? _properties->replace((IlAny)key, value)
				: IlFalse;
			}
    inline IlAny	getProperty(const IlSymbol* key) const
			{
			    return _properties
				? _properties->get((IlAny)key)
				: 0;
			}
    inline IlBoolean	hasProperty(const IlSymbol* key, IlAny* value) const
			{
			    return _properties
				? _properties->find((IlAny)key, value)
				: IlFalse;
			}
    inline IlAList*	getProperties() const { return _properties; }
    IlvNamedProperty*	getNamedProperty(const IlSymbol* namedPropSymbol,
					 const IlSymbol*) const;
    IlvNamedProperty*	setNamedProperty(const IlSymbol* namedPropSymbol,
					 IlvNamedProperty*,
					 IlAny = 0);
    IlvNamedProperty*	removeNamedProperty(const IlSymbol* namedPropSymbol,
					    IlSymbol*);
    void		writeNamedProperties(const IlSymbol* namedPropSymbol,
					     IlvOutputFile& stream,
					     const char* marker=0) const;
    void		readNamedProperties(const IlSymbol* namedPropSymbol,
					    IlvInputFile& stream,
					    IlAny = 0);
    void		removeNamedProperties(const IlSymbol* namedPropSymbol);

    static void		WriteNamedProperties(const IlList& nprops,
					     IlvOutputFile& stream,
					     const char* marker=0);
    static IlvNamedProperty* const* 
			ReadNamedProperties(IlUInt& count,
					    IlvInputFile& stream);

protected:
    IlAList*		_properties;
};

// declares a set of method implementing property management
// i.e. IlvGraphic, IlvGadgetItem,  and IlvManager have property management
// done through the IlvPropertyList object.
#define IlvDeclareBasePropertyListOwner()                               \
public:									\
inline const IlvPropertyList& getPropertyList() const { return _pList; }\
inline IlvPropertyList&	getPropertyList()  { return _pList; }		\
inline IlAList* getProperties()const{return _pList.getProperties(); }	\
inline void       addProperty(const IlSymbol* key, IlAny value)		\
	{ _pList.addProperty(key, value); }				\
inline void setProperty(const IlSymbol* key, IlAny value)		\
	{ _pList.setProperty(key, value); }				\
inline IlBoolean removeProperty(const IlSymbol* key)			\
	{ return _pList.removeProperty(key); }				\
inline IlBoolean replaceProperty(const IlSymbol* k, IlAny v)		\
	{ return _pList.replaceProperty(k, v); }			\
inline IlAny   getProperty(const IlSymbol* key) const			\
	{ return _pList.getProperty(key); }				\
inline IlBoolean hasProperty(const IlSymbol* k, IlAny* v = 0) const	\
	{ return _pList.hasProperty(k, v); }				\
protected:								\
IlvPropertyList	_pList

// declares a set of method implementing property and named property 
// management.
#define IlvDeclareDefaultPropertyListOwner(NAMED_PROP_SYMBOL, arg)      \
public:                                                                 \
inline IlvNamedProperty* getNamedProperty(const IlSymbol* symbol) const	\
	{ return _pList.getNamedProperty(NAMED_PROP_SYMBOL, symbol); }	\
inline IlvNamedProperty* setNamedProperty(IlvNamedProperty* property)	\
	{ return _pList.setNamedProperty(NAMED_PROP_SYMBOL, property,   \
					 arg); }                        \
inline IlvNamedProperty* removeNamedProperty(IlSymbol*symbol)		\
	{ return _pList.removeNamedProperty(NAMED_PROP_SYMBOL, symbol);}\
inline void writeNamedProperties(IlvOutputFile& s,			\
				 const char* m = 0) const		\
	{ _pList.writeNamedProperties(NAMED_PROP_SYMBOL, s, m); }	\
inline void readNamedProperties(IlvInputFile& stream)			\
	{ _pList.readNamedProperties(NAMED_PROP_SYMBOL, stream, arg); } \
inline void removeNamedProperties(void)					\
        { _pList.removeNamedProperties(NAMED_PROP_SYMBOL); }		\
IlvDeclareBasePropertyListOwner()                                       

#define IlvDeclarePropertyListOwner(NAMED_PROP_SYMBOL) \
IlvDeclareDefaultPropertyListOwner(NAMED_PROP_SYMBOL, 0)

#define IlvDeclarePropertyListOwnerWithNotify(NAMED_PROP_SYMBOL) \
IlvDeclareDefaultPropertyListOwner(NAMED_PROP_SYMBOL, this)

// implements property methods via specified DELEGATE
// i.e. the manager's delegate for properties management
// is the graphic holder.
#define IlvDeclarePropertyListDelegation() public:			\
IlvPropertyList&  getPropertyList() const;				\
IlAList*	  getProperties() const;				\
void		  addProperty(const IlSymbol*, IlAny) const;		\
void		  setProperty(const IlSymbol*, IlAny) const;		\
IlBoolean	  removeProperty(const IlSymbol*) const;		\
IlBoolean	  replaceProperty(const IlSymbol*, IlAny) const;	\
IlAny		  getProperty(const IlSymbol*) const;			\
IlBoolean	  hasProperty(const IlSymbol*, IlAny* = 0) const;	\
IlvNamedProperty* getNamedProperty(const IlSymbol*) const;		\
IlvNamedProperty* setNamedProperty(IlvNamedProperty*) const;		\
IlvNamedProperty* removeNamedProperty(IlSymbol*) const;			\
void		  writeNamedProperties(IlvOutputFile&,			\
				       const char* =0)const;		\
void		  readNamedProperties(IlvInputFile&) const;		\
void		  removeNamedProperties(void)

// declare inline methods for properties managements via delegation
#define IlvDeclarePropertyListDelegate(DELEGATE)			\
public:									\
inline IlvPropertyList& getPropertyList() const				\
	{ return (DELEGATE).getPropertyList(); }			\
inline IlAList*	 getProperties() const					\
	{ return (DELEGATE).getProperties(); }				\
inline void	 addProperty(const IlSymbol* k, IlAny v) const		\
	{ (DELEGATE).addProperty(k, v); }				\
inline void	 setProperty(const IlSymbol* k, IlAny v) const		\
	{ (DELEGATE).addProperty(k, v); }				\
inline IlBoolean removeProperty(const IlSymbol* k) const		\
	{ return (DELEGATE).removeProperty(k); }			\
inline IlBoolean replaceProperty(const IlSymbol* k, IlAny v) const	\
	{ return (DELEGATE).replaceProperty(k, v); }			\
inline IlAny	 getProperty(const IlSymbol* k) const			\
	{ return (DELEGATE).getProperty(k); }				\
inline IlBoolean hasProperty(const IlSymbol* k, IlAny*  v) const	\
	{ return (DELEGATE).hasProperty(k, v); }			\
inline IlvNamedProperty* getNamedProperty(const IlSymbol* s) const	\
	{ return (DELEGATE).getNamedProperty(s); }			\
inline IlvNamedProperty* setNamedProperty(IlvNamedProperty* p) const 	\
	{ return (DELEGATE).setNamedProperty(p); }			\
inline IlvNamedProperty* removeNamedProperty(IlSymbol*symbol) const	\
	{ return (DELEGATE).removeNamedProperty(symbol); }		\
inline void writeNamedProperties(IlvOutputFile& s, const char* m) const	\
	{ (DELEGATE).writeNamedProperties(s, m); }			\
inline void readNamedProperties(IlvInputFile& s) const			\
	{ (DELEGATE).readNamedProperties(s); }				\
inline void removeNamedProperties(void)					\
        { (DELEGATE).removeNamedProperties(); }

// define out-of-line property methods via delegation
#define IlvDefinePropertyListDelegation(CLASS, DELEGATE)		\
IlvPropertyList& CLASS::getPropertyList() const				\
	{ return (DELEGATE).getPropertyList(); }			\
IlAList*  CLASS::getProperties() const					\
	{ return (DELEGATE).getProperties(); }				\
void	  CLASS::addProperty(const IlSymbol* k, IlAny v) const		\
	{ (DELEGATE).addProperty(k, v); }				\
void	  CLASS::setProperty(const IlSymbol* k, IlAny v) const		\
	{ (DELEGATE).addProperty(k, v); }				\
IlBoolean CLASS::removeProperty(const IlSymbol* k) const		\
	{ return (DELEGATE).removeProperty(k); }			\
IlBoolean CLASS::replaceProperty(const IlSymbol* k, IlAny v) const	\
	{ return (DELEGATE).replaceProperty(k, v); }			\
IlAny	  CLASS::getProperty(const IlSymbol* k) const			\
	{ return (DELEGATE).getProperty(k); }				\
IlBoolean CLASS::hasProperty(const IlSymbol* k, IlAny*  v) const	\
	{ return (DELEGATE).hasProperty(k, v); }			\
IlvNamedProperty* CLASS::getNamedProperty(const IlSymbol* s) const	\
	{ return (DELEGATE).getNamedProperty(s); }			\
IlvNamedProperty* CLASS::setNamedProperty(IlvNamedProperty* p) const	\
	{ return (DELEGATE).setNamedProperty(p); }			\
IlvNamedProperty* CLASS::removeNamedProperty(IlSymbol* s) const		\
	{ return (DELEGATE).removeNamedProperty(s); }			\
void CLASS::writeNamedProperties(IlvOutputFile& s, const char* m) const	\
	{ (DELEGATE).writeNamedProperties(s, m); }			\
void CLASS::readNamedProperties(IlvInputFile& s) const			\
	{ (DELEGATE).readNamedProperties(s); }				\
void CLASS::removeNamedProperties(void)					\
        { (DELEGATE).removeNamedProperties(); }

ILVVWSMODULEINIT(proplist);

#endif  /* !__Ilv_Util_Proplist_H */
