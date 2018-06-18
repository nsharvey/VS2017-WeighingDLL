// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/attrinfo.h
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
// Rogue Wave Views - Maps add-on.
// Definition of the IlvMapAttributeInfo class
// Definition of the IlvMapAttribute class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Attrinfo_H
#define __Ilv_Maps_Attrinfo_H

#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Maps_Proplist_H)
#  include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Maps_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif

ILVMAPSMODULEINIT(attrinfo);

class ILVDSPEXPORTED IlvValueTypeClass;
class ILVDSPEXPORTED IlvValue;
class ILVDSPEXPORTED IlvStringHashTable;

//-----------------------------------------------------------------------------
// This named property points to a description of the attributes
// associated with an object.
//
class ILVMAPSEXPORTED IlvMapAttributeInfo
{
public:
    void	write(IlvOutputFile&) const;
    IlvMapAttributeInfo(IlvInputFile&);
    IlvMapAttributeInfo(const IlvMapAttributeInfo&);
    inline IlvMapAttributeInfo* copy() const {
	return new IlvMapAttributeInfo(*this);
    }
protected:
    IlUInt			_count;
    IlStringHashTable* 		_nameTable;
    char**			_names;
    const IlvValueTypeClass**	_types;		
    IlUChar*			_nullables;
    IlBoolean			_owned;
    IlUInt			_lockCount;
    IlBoolean			_persistent;

    void init(IlUInt,
	      IlBoolean,
	      IlBoolean,
	      IlBoolean);

    inline IlBoolean hasNullableAttributes() const {
	return !!_nullables;
    }
    void store(IlUInt,
	       const char*,
	       const IlvValueTypeClass*,
	       IlBoolean);

    friend class IlvMapAttributeProperty;
public:
    IlvMapAttributeInfo(IlUInt				count,
			const char**			names,
			const IlvValueTypeClass**	types,
			const IlBoolean*		nullables = 0,
			IlBoolean			owned = IlFalse);
protected:
    // use lock / unLock to manage object destruction
    virtual ~IlvMapAttributeInfo();
public:
    void setPersistent(IlBoolean flag) {
	_persistent = flag;
    }

    IlUInt getAttributeCount() const {
	return _count;
    }
    const char*	getAttributeName(IlUInt index) const;
    const IlvValueTypeClass* getAttributeType(IlUInt index) const;
    IlBoolean isNullable(IlUInt index) const;
    void getAttributeInfos(IlUInt index,
			   const char*& name,
			   const IlvValueTypeClass*& type,
			   IlBoolean& nullable) const;
    IlInt getAttributeIndex(const char* name,
			     IlvMapsError* error = 0) const;

    IlBoolean isBad() const;
    inline void setOwned(IlBoolean owned) { _owned = owned; }
    inline IlBoolean isOwned() const      { return _owned; }
    inline IlBoolean isLocked() const { return !!_lockCount; }
    void lock();
    void unLock();

    inline static IlvMapsError AttributeNotFoundError() { return _AttributeNotFoundError; }

    static void	InitClass();
private:
    static IlvMapsError		_AttributeNotFoundError;
};

//-----------------------------------------------------------------------------
// This named property contains the attribute values
// associated to an object.
//
class ILVMAPSEXPORTED IlvMapAttributeProperty
: public IlvNamedProperty
{
public:
    IlvMapAttributeProperty(IlvMapAttributeInfo* info,
			    IlBoolean persistent = IlTrue);
    virtual ~IlvMapAttributeProperty();

    static const IlvSymbol* GetName() { return _name; }
    inline IlvMapAttributeInfo* getInfo() const { return _info; }
    virtual IlBoolean	isPersistent() const;
    inline void setPersistent(IlBoolean value) { _persistent = value; }
    IlvMapsError getValue(const char* name, IlvValue& x) const;

    IlvMapsError getValue(IlUInt index, IlvValue& x) const;
    IlBoolean isSet(const char* name) const;
    IlBoolean			isSet(IlUInt index) const;
    // Setters which use the attribute name
    IlvMapsError		setValue(const char* name, IlInt value);
    IlvMapsError		setValue(const char* name, IlUInt value);
    IlvMapsError		setValue(const char* name, IlFloat value);
    IlvMapsError		setValue(const char* name, IlDouble value);
    IlvMapsError		setValue(const char* name, const char* value);
    IlvMapsError		setValue(const char* name, IlBoolean value);
    // Setters which use the attribute index.
    IlvMapsError		setValue(IlUInt index, IlInt value);
    IlvMapsError		setValue(IlUInt index, IlUInt value);
    IlvMapsError		setValue(IlUInt index, IlFloat value);
    IlvMapsError		setValue(IlUInt index, IlDouble value);
    IlvMapsError		setValue(IlUInt index, const char * value);
    IlvMapsError		setValue(IlUInt index, IlBoolean value);

    IlBoolean isBad() const;
    inline static IlvMapsError	AttributeTypeMismatchError()
	{ return _AttributeTypeMismatchError; }

    inline static IlvMapsError UnsetAttributeError() { return _UnsetAttributeError; }

    static void	InitClass();
protected:
    void init(IlvMapAttributeInfo*,
	      IlBoolean,
	      const IlvMapAttributeProperty*);
    IlvMapsError setValueInternal(IlUInt,
				  const IlvValue&);
    IlUChar*	 getValueMarks() const;
    void	 deleteValueIfNeeded(IlUInt);
private:
    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvMapAttributeProperty);

private:
    IlvMapAttributeInfo*	_info;
    IlAny			_values;
    IlBoolean			_persistent;

    static const  IlvSymbol*    _name;
    static IlvMapsError		_AttributeTypeMismatchError;
    static IlvMapsError		_UnsetAttributeError;
    static IlvMapsError		_BadStringValueError;
    IlvMapsError		setValueFromString(IlUInt, const char*);

};
#endif /* !Ilv_Maps_Attrinfo_H*/
