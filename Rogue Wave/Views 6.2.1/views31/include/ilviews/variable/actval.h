// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/actval.h
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
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Actval_H
#define __Ilv31_Variable_Actval_H

#if !defined(__Ilv31_Variable_Assert_H)
#include <ilviews/variable/assert.h>
#endif
#if !defined(__Ilv31_Variable_List_H)
#include <ilviews/variable/list.h>
#endif
#if !defined(__Ilv31_Variable_Hash_H)
#include <ilviews/variable/hash.h>
#endif
#if !defined(__Ilv31_Variable_Magic_H)
#include <ilviews/variable/magic.h>
#endif

class IlvvActiveValue;

ILVV_HASH_DEF(IlvvBNullifiedH,IlvvActiveValue*,IlvvActiveValue*)
ILVV_LIST_DEF3(IlvvActValList,IlvvActiveValue*,IlvvActiveValue*)

class ILV31VAREXPORTED IlvvNullifiedH:
public IlvvBNullifiedH
{
 public:
   IlvvNullifiedH();
   // lazy behavior, if the active value is not present, does nothing
   IlvvNullifiedH& operator<<(IlvvActiveValue*);
   // empty destructor, defined just because the virtual destructor of the base class
   // is undefined whenever this header is seen by an object
   ~IlvvNullifiedH();
};

class ILV31VAREXPORTED IlvvNullified
{
 public:
   IlvvNullified();
   operator IlvvNullifiedH&();
   IlvvNullifiedH& getValue();
   // useful for the layers pump
   IlvvNullifiedH* toggle(IlvvNullifiedH*);
   ~IlvvNullified();
 private:
   IlvvNullifiedH* _niaht;
};

class ILV31VAREXPORTED IlvvActiveValue
{
 public:
   enum COMPUTATION{VARIED,UNCHANGED,UNDEFINED,CYCLE};
   enum CYCLE_STATUS{IS_CYCLE,NOT_CYCLE};
   IlvvActiveValue();
   virtual ~IlvvActiveValue();
   IlvvBoolean isImportant() const {return _important?IlvvTrue:IlvvFalse;}
   void incrImportant();
   void decrImportant();
   // can perform several set_used_by with the same argument
   // without harm
   // calls set_uses of the user
   void setUsedBy(IlvvActiveValue* user);
   void unsetUsedBy(IlvvActiveValue* user);
   // can perform several set_uses with the same argument
   // without harm
   void setUses(IlvvActiveValue* used);
   void unsetUses(IlvvActiveValue* used);
   void nullify();
   virtual void reset();
   static void reevaluate(){reevaluate(&nullified().getValue());}
   // nullify + set_to_be_recomputed
   void invalidate(){nullify();setToBeRecomputed();}
   // set_up_to_date + unset_unset
   // set_up_to_date has a side effect on the hash table
   void setInitialized(){setUpToDate();unsetUnset();}
   // these two functions are used by the evaluator
   virtual CYCLE_STATUS stack();
   // the second parameter is used during cycles
   // no need to make it virtual, because of strong typing
   CYCLE_STATUS unstack(IlvvActiveValue* being_evaluated, COMPUTATION, IlvvActiveValue* cycle_door, IlvvBoolean stacked=IlvvFalse);
   int usesCount() const {return _uses_count;}

   static IlvvActiveValue* beingEvaluated(){return _being_evaluated;}
   static COMPUTATION lastComputation(){return _last_computation;}
   static void setLastComputation(COMPUTATION c){_last_computation=c;}
   static void updateLastComputation(COMPUTATION);
   static IlvvActiveValue* cycleDoor(){return _cycle_door;}
#if !defined(__alpha)
protected:
#endif
    static void reevaluate(IlvvNullifiedH*);
#if defined(__alpha)
public:
#endif
    void nullifyUsers();
    IlvvBoolean upToDate() const {return _up_to_date;}
    void setUpToDate();
    // the following function is called by set_up_to_date
    // by default, it does nothing.
    // its specialization can be made at subclassing to be
    // warned when an attribute is set a new value
    virtual void notifyUpToDate();
    virtual void notifyUpdated();
    // tells that this active value is in the cycle
    virtual void notifyInCycle();
    virtual void notifyCycle();
    // call the former functions and reset after
    void tellInCycle();
    // tells that the active value is undefined, because depending
    // on a cycle.
    virtual void notifyUndefined();
    // call the former functions and reset after
    void tellUndefined();
    void unsetUpToDate(){_up_to_date=IlvvFalse;}
    //
    IlvvBoolean toBeRecomputed() const {return _to_be_recomputed;}
    void setToBeRecomputed()
	{ ILVV_ASSERT(!_up_to_date); _to_be_recomputed = IlvvTrue; }
    void unsetToBeRecomputed()
	{ _to_be_recomputed = IlvvFalse; }
    //
    IlvvBoolean isSet() const {return (IlvvBoolean)!_unset;}
    IlvvBoolean isUnset() const {return _unset;}
    void setUnset(){_unset=IlvvTrue;}
    void unsetUnset(){_unset=IlvvFalse;notifyUpdated();}
    void killUses();
    // recomputes all the uses
    COMPUTATION recomputeUses();
    void usersToBeRecomputed();
    virtual COMPUTATION compute()=0;
    int usedByCount() const {return _used_by_count;}
    ILVV_MAGIC_DECL(IlvvNullified,nullified);
private:
    // counter of importance
    unsigned short _important;
    // flags, no bit fields
    IlvvBoolean _up_to_date;
    IlvvBoolean _unset;
    IlvvBoolean _to_be_recomputed;
    IlvvBoolean _stacked;
    unsigned short _used_by_count;
    unsigned short _uses_count;
    // contains no double
    IlvvActiveValue **_used_by;
    // contains no double
    IlvvActiveValue **_uses;
    static IlvvActiveValue *_being_evaluated;
    static IlvvActiveValue *_cycle_door;
    static COMPUTATION _last_computation;
    // forbidden
    IlvvActiveValue(const IlvvActiveValue&);
    void operator=(const IlvvActiveValue&);
};

// MACROS
// mangling
#define ILVV_ATTR(aname) _ILVV_attribute_##aname
#define ILVV_ACTIVE_VALUE_TYPE(aname) IlvvAttributeType##__##aname)
#define ILVV_ACTIVE_ACCESS(aname) _ILVV_access##aname

#define ILVV_ATTR_SET(attr_id) Ilvvset_##son_id
#define ILVV_ATTR_RESET(attr_id) Ilvvreset_##son_id

// evaluate is virtual to be able to overload it.
#define ILVV_RECOMPUTE_IN(owner_type,type,name) \
 public: \
   COMPUTATION compute(); \
   virtual type evaluate(); \
   type getValue() const ; \
   void reset(); \
 private:

#define ILVV_RECOMPUTE_INCR_IN(owner_type,type,name) \
   ILVV_RECOMPUTE_IN(owner_type,type,name) \
 private:

// this precompute compares the values a posteriori
// must define the ILVV_ACTIVE_VALUE_MATCH
// if you want a different one
#define ILVV_ACTIVE_VALUE_MATCH(v1,v2) ((v1)==(v2))
#define ILVV_ACTIVE_VALUE_RESET(v)

// this is meant for attributes whoses values are compared a posteriori
#define ILVV_BASE_ACTIVE_VALUE_BLOCK(type,name) \
{ \
   ILVV_RECOMPUTE_IN(type,name) \
 public: \
   void set(type); \
   void setValue(type); \
   ILVV_ACTIVE_VALUE_TYPE(name)(); \
   ILVV_ACTIVE_VALUE_TYPE(name)(type); \
 private: \
   type _value; \
};

#define ILVV_BASE_ACTIVE_VALUE_DEF(type,name) \
class ILV31VAREXPORTED ILVV_ACTIVE_VALUE_TYPE(name): \
public IlvvActiveValue \
ILVV_BASE_ACTIVE_VALUE_BLOCK(type,name)

#define ILVV_ACTIVE_VALUE_DEF(owner_type,type,name) \
ILVV_BASE_ACTIVE_VALUE_DEF(owner_type,type,name)

#define ILVV_BASE_ACTIVE_VALUE_BODY(type,name) \
void ILVV_ACTIVE_VALUE_TYPE(name)::set(type value){ \
   if (usesCount()){ \
      IlvvUFatalError()<<"Attempt to change the value of an attribute which depends on other attributes."<<IlvvUEOM; \
   } \
   setValue(value); \
   nullifyUsers(); \
   usersToBeRecomputed(); \
   setInitialized(); \
   notifyUpdated(); \
} \
void ILVV_ACTIVE_VALUE_TYPE(name)::setValue(type value){ \
   _value=value; \
} \
ILVV_ACTIVE_VALUE_TYPE(name)::ILVV_ACTIVE_VALUE_TYPE(name)(){} \
ILVV_ACTIVE_VALUE_TYPE(name)::ILVV_ACTIVE_VALUE_TYPE(name)(type value): _value(value){setInitialized();}

#define ILVV_BASE_ACTIVE_DEF(type,name) \
  public: \
    type name(); \
    ILVV_ACTIVE_VALUE_TYPE(name)& ILVV_ACTIVE_ACCESS(name)(); \
  private: \
    ILVV_ACTIVE_VALUE_TYPE(name) ILVV_ATTR(name);

#define ILVV_ACTIVE_DEF(type,name) \
ILVV_BASE_ACTIVE_DEF(type,name)

#define ILVV_BASE_ACTIVE_BODY(owner_type,type,name) \
ILVV_BASE_ACTIVE_VALUE_BODY(owner_type,type,name) \
type owner_type::name(){ \
   ILVV_ATTR(name).compute(); \
   return (ILVV_ATTR(name)).getValue(); \
} \
ILVV_ACTIVE_VALUE_TYPE(owner_type,name)& owner_type::ILVV_ACTIVE_ACCESS(name)(){ \
   return ILVV_ATTR(name); \
} \
type ILVV_ACTIVE_VALUE_TYPE(owner_type,name)::getValue() const { \
   return _value; \
} \
void ILVV_ACTIVE_VALUE_TYPE(owner_type,name)::reset(){ \
   IlvvActiveValue::reset(); \
   ILVV_ACTIVE_VALUE_RESET(_value) \
}

#define ILVV_ACTIVE_BODY(owner_type,type,name) \
ILVV_RECOMPUTE_OUT(owner_type,type,name) \
ILVV_BASE_ACTIVE_BODY(owner_type,type,name)

// to be called in the constructor of the owner
#define ILVV_ACTIVE_BUILD(name) \
ILVV_ATTR(name)(*this)
#define ILVV_ACTIVE_BUILD_VALUED(name,value) \
ILVV_ATTR(name)(*this,value)

/* Generated by <ilguard> */
#endif
