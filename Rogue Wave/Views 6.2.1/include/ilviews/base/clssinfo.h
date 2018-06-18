// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/clssinfo.h
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
// Declaration of the IlvClassInfo class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Clssinfo_H
#define __Ilv_Base_Clssinfo_H

#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif

class IlvClassInfo;
class IlvPropClassInfo;
class IlvValuedClassInfo; // defined in intrface/value.h
typedef void (* IlvClassInfoCreationCallback)(IlvClassInfo*, IlAny);
IL_DEFINEFPTRTOANYCAST(IlvClassInfoCreationCallback);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvClassInfo
{
public:
    virtual ~IlvClassInfo();

    static
    IlvClassInfo*	Get(const IlSymbol*     name,
			    const IlvClassInfo* parent = 0);
    inline static
    IlvClassInfo*	Get(const char* classname,
			    const IlvClassInfo* parent = 0)
			{
			    return Get(IlGetSymbol(classname), parent);
			}
    static IlBoolean	IsKnown(const IlSymbol* classname);
    inline
    static IlBoolean	IsKnown(const char* classname)
			{
			    return IsKnown(IlGetSymbol(classname));
			}
    static
    IlStringHashTable*	GetRegisteredClasses();
    static
    IlvClassInfo* const* GetRegisteredClassInfos(IlUInt&);
    static
    const char* const*	GetRegisteredClassNames(IlUInt&);
    static
    IlvClassInfo*	Create(const char*, IlvClassInfo**);
    static void		AddCreationCallback(IlvClassInfoCreationCallback,
					    IlAny);
    static void		RemoveCreationCallback(IlvClassInfoCreationCallback,
					       IlAny);
    // ____________________________________________________________
    inline
    const IlSymbol*	getSymbol() const { return _className; }
    inline
    const char*		getClassName() const { return _className->name(); }
    inline
    IlvClassInfo*	getSuperClass() const
			{
			    return _superClass ? *_superClass : 0;
			}
    inline IlBoolean	hasSuperClass() const
			{
			    return _superClass ? IlTrue : IlFalse;
			}
    inline IlUInt	getIndex() const { return _index; }
    IlBoolean		isSubtypeOf(const char* className) const;
    IlBoolean		isSubtypeOf(const IlvClassInfo* classInfo) const;
    virtual
    const IlvValuedClassInfo*	getValued() const;

protected:
    IlvClassInfo(const char* className, IlvClassInfo** superClass);

    const IlSymbol*	_className;
    IlvClassInfo**	_superClass;
    IlUInt		_index;

private:
    // No copy constructor
    IlvClassInfo(const IlvClassInfo&);
    // No assignment operator
    IlvClassInfo& operator=(const IlvClassInfo&);
};

// --------------------------------------------------------------------------
typedef void (* IlvPropClassInfoDeleteCallback)(IlvPropClassInfo*, IlAny);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPropClassInfo : public IlvClassInfo
{
public:
    virtual ~IlvPropClassInfo();

    void		addProperty(const IlSymbol* key, IlAny value);
    IlBoolean		removeProperty(const IlSymbol* key);
    IlBoolean		replaceProperty(const IlSymbol* key, IlAny value);
    IlAny		getProperty(const IlSymbol* key,
				    IlBoolean checkParent = IlFalse) const;
    void		addDeleteCallback(IlvPropClassInfoDeleteCallback,
					  IlAny = 0);
    const IlvClassInfo* hasProperty(const IlSymbol* key,
				    IlBoolean checkParent = IlFalse) const;
    static
    IlvPropClassInfo*	Create(const char*, IlvClassInfo**);

protected:
    IlvPropClassInfo(const char*	className,
		     IlvClassInfo**	superClass)
	: IlvClassInfo(className, superClass),
	  _classProperties(0) {}

    IlAList*		_classProperties;
};

// --------------------------------------------------------------------------
inline IlvClassInfo* IlvGetClassInfo(const char* classname)
{
    return IlvClassInfo::Get(classname);
}
inline IlStringHashTable* IlvGetRegisteredClasses()
{
    return IlvClassInfo::GetRegisteredClasses();
}
inline IlvClassInfo* const* IlvGetRegisteredClassInfos(IlUInt& count)
{
    return IlvClassInfo::GetRegisteredClassInfos(count);
}
inline const char* const* IlvGetRegisteredClassNames(IlUInt& count)
{
    return IlvClassInfo::GetRegisteredClassNames(count);
}

// --------------------------------------------------------------------------
#define IlvDeclareClassInfo_() public:					\
    static IlvClassInfo* _classinfo;					\
    inline const char* className() const				\
    { return getClassInfo() ? getClassInfo()->getClassName() : 0; }	\
    inline IlBoolean isSubtypeOf(const char* t) const			\
    { return getClassInfo() && getClassInfo()->isSubtypeOf(t); }	\
    inline IlBoolean isSubtypeOf(const IlvClassInfo* c) const		\
    { return getClassInfo() && getClassInfo()->isSubtypeOf(c); }	\
    virtual IlvClassInfo* getClassInfo() const

#define IlvDeclareClassInfo() IlvDeclareClassInfo_();			\
    static inline IlvClassInfo** ClassPtr() { return &_classinfo; }	\
    static inline IlvClassInfo*  ClassInfo() { return _classinfo; }

#define IlvDeclareLazyClassInfo() IlvDeclareClassInfo_();		\
    static IlvClassInfo** ClassPtr();					\
    static IlvClassInfo* ClassInfo()

#define IlvDeclarePropClassInfo_() public:				\
    inline IlvPropClassInfo* getPropClassInfo() const			\
    { return IL_REINTERPRETCAST(IlvPropClassInfo*, getClassInfo()); }	\
    static inline IlvPropClassInfo* GetPropClassInfo()			\
    { return IL_REINTERPRETCAST(IlvPropClassInfo*, ClassInfo()); }	\
    static inline void AddProperty(const IlSymbol* k, IlAny v)		\
    {									\
	if (GetPropClassInfo())						\
	    GetPropClassInfo()->addProperty(k, v);			\
    }	    								\
    static inline IlBoolean RemoveProperty(const IlSymbol* key)		\
    {									\
	return GetPropClassInfo()					\
	    ? GetPropClassInfo()->removeProperty(key) : IlFalse;	\
    }									\
    static inline IlBoolean ReplaceProperty(const IlSymbol* k, IlAny v)	\
    {									\
	return GetPropClassInfo()					\
	    ? GetPropClassInfo()->replaceProperty(k,v) : IlFalse;	\
    }									\
    static IlAny GetProperty(const IlSymbol* key, IlBoolean p=IlFalse)	\
    {									\
	return GetPropClassInfo()					\
	    ? GetPropClassInfo()->getProperty(key, p) : 0;		\
    }									\
    static inline const IlvClassInfo* HasProperty(const IlSymbol* key,	\
						  IlBoolean p = IlFalse)\
    {									\
	return GetPropClassInfo()					\
	    ? GetPropClassInfo()->hasProperty(key, p) : 0;		\
    }

#define IlvDeclarePropClassInfo() IlvDeclarePropClassInfo_()		\
    IlvDeclareClassInfo()

#define IlvDeclareLazyPropClassInfo() IlvDeclarePropClassInfo_()	\
    IlvDeclareLazyClassInfo()

#define IlvDeclarePropRootClassInfo_() public:				\
    inline void addClassProperty(const IlSymbol* key, IlAny value)	\
    {									\
	if (getPropClassInfo())						\
	    getPropClassInfo()->addProperty(key, value);		\
    }									\
    inline IlBoolean removeClassProperty(const IlSymbol* key)		\
    {									\
	return getPropClassInfo()					\
	? getPropClassInfo()->removeProperty(key) : IlFalse;		\
    }									\
    inline IlBoolean replaceClassProperty(const IlSymbol* key, IlAny v) \
    {									\
	return getPropClassInfo()					\
	? getPropClassInfo()->replaceProperty(key, v) : IlFalse;	\
    }									\
    inline IlAny getClassProperty(const IlSymbol* key, 			\
				  IlBoolean checkParent = IlFalse) const\
    {									\
	return getPropClassInfo()					\
	? getPropClassInfo()->getProperty(key, checkParent) : 0;	\
    }									\
    inline const IlvClassInfo* hasClassProperty(const IlSymbol* key,	\
						IlBoolean p = IlFalse) const\
    {									\
	return getPropClassInfo()					\
	? getPropClassInfo()->hasProperty(key, p) : 0;			\
    }

#define IlvDeclarePropRootClassInfo() IlvDeclarePropRootClassInfo_()	\
    IlvDeclarePropClassInfo()

#define IlvDeclareLazyPropRootClassInfo() IlvDeclarePropRootClassInfo_()\
    IlvDeclareLazyPropClassInfo()

// ClassInfo macros
#define IlvDefineClassInfo(classname, superclass)			\
IlvClassInfo* classname::getClassInfo() const { return ClassInfo(); }	\
IlvClassInfo* classname::_classinfo =					\
    IlvClassInfo::Create(#classname, superclass::ClassPtr())

#define IlvDefineRootClassInfo(classname)				\
IlvClassInfo* classname::getClassInfo() const { return ClassInfo(); }	\
IlvClassInfo* classname::_classinfo = IlvClassInfo::Create(#classname, 0)

#define ILVDEFINECLASSINFOMEMBERS(classname, clinfo)			\
IlvClassInfo* classname::getClassInfo() const { return ClassInfo(); }	\
IlvClassInfo* classname::_classinfo = clinfo

#define ILVPREDEFINECLASSINFOMEMBERS(classname)				\
IlvClassInfo* classname::getClassInfo() const { return ClassInfo(); }	\
IlvClassInfo* classname::_classinfo = 0

#define ILVPOSTDEFINECLASSINFOMEMBERS(classname, clinfo)		\
classname::_classinfo = clinfo

#define IlvLoadClass(classname)						\
IlvClassInfo* _##classname = classname::_classinfo

// PropClassInfo macros
#define IlvDefinePropClassInfo(classname, superclass)			\
IlvPropClassInfo* classname::getClassInfo() const {return ClassInfo();} \
IlvPropClassInfo* classname::_classinfo =				\
    IlvPropClassInfo::Create(#classname, superclass::ClassPtr())

#define IlvDefineLazyClassInfo(classname, symbol)			\
    IlvClassInfo** classname::ClassPtr()				\
    {									\
	if (!_classinfo)						\
	    ClassInfo();						\
	return &_classinfo;						\
    }									\
    IlvClassInfo* classname::ClassInfo()				\
    {									\
	if (!_classinfo) {						\
	    IL_MODINIT(symbol)();					\
	}								\
	return _classinfo;						\
    }
#endif /* !__Ilv_Base_Clssinfo_H */
