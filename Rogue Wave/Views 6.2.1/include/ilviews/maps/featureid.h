// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/featureid.h
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
// Definition of the IlvMapFeatureId
// Definition of the IlvMapFeatureIntegerId
// Definition of the IlvMapFeatureStringId
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Featureid_H
#define __Ilv_Maps_Featureid_H

#if !defined(__Ilv_Maps_Macros_H)
#  include <ilviews/maps/macros.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif

ILVMAPSMODULEINIT(IlvMapFeatureId);

class ILVMAPSEXPORTED IlvMapFeatureId
{
public:
    virtual ~IlvMapFeatureId();
    virtual IlBoolean equals(const IlvMapFeatureId& featureId) const = 0;
    virtual IlUInt hashCode() const = 0;
    virtual IlvClassInfo* getClassInfo() const = 0;
    virtual IlvMapFeatureId* copy() const = 0;

    inline int operator==(const IlvMapFeatureId& a) const
	{ return equals(a);  }
    inline int operator!=(const IlvMapFeatureId& a) const
	{ return !equals(a); }

    inline static IlvClassInfo* ClassInfo()     { return _classinfo;  }
    inline static IlvClassInfo** ClassInfoRef() { return &_classinfo; }
    IlvMapsIcFriend(IlvMapFeatureId, ILVMAPSEXPORTED);
private:
    static void Init();

    static IlvClassInfo* _classinfo;    
};

class ILVMAPSEXPORTED IlvMapFeatureIntegerId
: public IlvMapFeatureId
{
public:
    IlvMapFeatureIntegerId(IlInt value)
    : _value(value)
    {}
    virtual ~IlvMapFeatureIntegerId();

    virtual IlBoolean equals(const IlvMapFeatureId&) const;
    virtual IlUInt hashCode() const;
    virtual IlvClassInfo* getClassInfo() const;
    virtual IlvMapFeatureId* copy() const;

    inline IlInt getValue() const { return _value; }
    inline void setValue(IlInt val) { _value = val; }

    inline static IlvClassInfo* ClassInfo()     { return _classinfo;  }
    inline static IlvClassInfo** ClassInfoRef() { return &_classinfo; }
    IlvMapsIcFriend(IlvMapFeatureId, ILVMAPSEXPORTED);
private:
    IlInt _value;

    static void Init();

    static IlvClassInfo* _classinfo;
};

class ILVMAPSEXPORTED IlvMapFeatureDoubleId
: public IlvMapFeatureId
{
public:
    IlvMapFeatureDoubleId(IlDouble value)
    : _value(value)
    {}    
    virtual ~IlvMapFeatureDoubleId();

    virtual IlBoolean equals(const IlvMapFeatureId&) const;
    virtual IlUInt hashCode() const;
    virtual IlvClassInfo* getClassInfo() const;
    virtual IlvMapFeatureId* copy() const;

    inline IlDouble getValue() const { return _value; }
    inline void setValue(IlDouble val) { _value = val; }

    inline static IlvClassInfo* ClassInfo()     { return _classinfo;  }
    inline static IlvClassInfo** ClassInfoRef() { return &_classinfo; }
    IlvMapsIcFriend(IlvMapFeatureId, ILVMAPSEXPORTED);
private:
    IlDouble _value;

    static void Init();

    static IlvClassInfo* _classinfo;
};

class ILVMAPSEXPORTED IlvMapFeatureStringId
: public IlvMapFeatureId
{
public:
    IlvMapFeatureStringId(const char* value);
    virtual ~IlvMapFeatureStringId();

    virtual IlBoolean equals(const IlvMapFeatureId&) const;
    virtual IlUInt hashCode() const;
    virtual IlvClassInfo* getClassInfo() const;
    virtual IlvMapFeatureId* copy() const;

    inline const char* getValue() const { return _value; }
    void setValue(const char* val);

    static IlvClassInfo* ClassInfo() {return _classinfo;}
    static IlvClassInfo** ClassInfoRef() {return &_classinfo;}
    IlvMapsIcFriend(IlvMapFeatureId, ILVMAPSEXPORTED);
private:
    char* _value;

    static void Init();

    static IlvClassInfo* _classinfo;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvMapFeatureIdHashTable
: public IlvHashTable
{
public:
    IlvMapFeatureIdHashTable(IlUInt size)
    : IlvHashTable(size)
    {}
    virtual ~IlvMapFeatureIdHashTable();
protected:
    virtual IlBoolean match(const IlAny, const IlAny) const;
    virtual IlUInt    hash(const IlAny) const;
};

#endif /* !__Ilv_Maps_Featureid_H */
