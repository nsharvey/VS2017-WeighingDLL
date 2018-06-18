// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/reset.h
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
// Declaration of the IlvStateProcedure and IlvStateRequirement classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Reset_H
#define __Ilv_States_Reset_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#ifndef __Ilv_States_Stateass_H
#  include <ilviews/states/stateass.h>
#endif
#ifndef __Ilv_States_Gendefs_H
#  include <ilviews/states/gendefs.h>
#endif

// dynamic type info :
// this function and macros are used by the type mechanism for state requirements
// other (may be trickier) possibilities could have existed,
// such as taking the address of a virtual function as its type
// the explicit numbering below has the advantage of being
// totally under control
#define ILVSTATES_TYPE_INFO \
    static IlInt _dont_forget_REGISTER_TYPE_in_cc_file; \
virtual IlAny getType() { return &_dont_forget_REGISTER_TYPE_in_cc_file; }

#define ILVSTATES_REGISTER_TYPE(c) IlInt c::_dont_forget_REGISTER_TYPE_in_cc_file = 0;

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStateProcedure
{
public:
    virtual ~IlvStateProcedure() {}
    virtual void onEntry() = 0;   // called upon entry
    virtual void onExit() = 0;    // called upon exit
};

// --------------------------------------------------------------------------
// IlvStateRequirement is an interface definition class
// the protocol declares methods to
//	- read a value from an object (store)
// - write that value again      (restore)
// - write a requested value     (apply)
// - copy the Stored value from an other IlvStateRequirement object (algo feature)
// - copy the requested value from an other IlvStateRequirement object (id.)
class ILVSTATESEXPORTED IlvStateRequirement
{
    // this class is a pure interface
public:
    virtual ~IlvStateRequirement() {}
    // for the hash tables :
    virtual IlAny getType() = 0;
    virtual IlInt getInt() = 0; // for indexing in the hash tables
    // to compare "resource" requirements
    virtual IlInt isDifferentOf(IlvStateRequirement*) = 0;
    // for the algorithms
    virtual void apply() = 0;
    virtual void restore() = 0;
    virtual void copyStoredFrom(IlvStateRequirement*) = 0;
    virtual void copyRequiredFrom(IlvStateRequirement*) = 0;
    virtual void storeObjectData() = 0;
};

// --------------------------------------------------------------------------
//the hash table bucket type
class ILVSTATESEXPORTED IlvSuApplyList
: public IlvSuKeyList
{
    typedef IlvSuApplyList* self;
    typedef IlvSuKeyList    inherited;
    IlvStateRequirement*    _ToRestore;
    IlvStateRequirement*    _ToApply;
public:
    IlvSuApplyList(IlAny k,
		   IlvSuApplyList* n = 0)
	: IlvSuKeyList(k, n),
	_ToRestore(0),
	_ToApply(0) {}
    ~IlvSuApplyList() {}
    ILVSTATES_READWRITE(IlvStateRequirement*, ToRestore);
    ILVSTATES_READWRITE(IlvStateRequirement*, ToApply);
    // accessors
    selffield(Next);
};

// --------------------------------------------------------------------------
class IlvSuApplyAssocTable: public IlvSuKeyTable
{
public:
    IlvSuApplyAssocTable(IlInt = 5);
    ~IlvSuApplyAssocTable() {};
};
#endif /* !__Ilv_States_Reset_H */
