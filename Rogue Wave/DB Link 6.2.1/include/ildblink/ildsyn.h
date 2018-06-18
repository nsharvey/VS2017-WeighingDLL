// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildsyn.h
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
// Schema entities common description
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDSYN_H
#define __ILD_ILDSYN_H

#ifdef IL_STD
# ifndef _STRING_
#  include <string>
# endif
#else
# ifndef _STRING_H
#  include <string.h>
# endif
#endif

#ifndef __ILD_DBUTIL_H
#include <ildblink/dbutil.h>
#endif

class IldDbms;
class IldDbmsImp;
class IldDescriptor;
class IldArgument;
class IldSchemaEntity;

// ============================================================================
//    Oracle: Synonym, Sequence, Package
// ============================================================================
class ILD_EXPORTED IldSynonym : public IldSchemaEntity {

protected:
    char*		_target;
    char*		_targetOwner;
    char*		_link;

public:
    IldSynonym     ();
    IldSynonym     (const char* name,
		    const char* owner,
		    IlInt id,
		    const char* target,
		    const char* targetOwner,
		    const char* link);

    virtual
    ~IldSynonym    ();

    inline
    const char*		getLink        () const;

    inline
    const char*		getTarget      () const;

    inline
    const char*		getTargetOwner () const;
};

// ----------------------------------------------------------------------------
// Inlines for IldSynonym class
// ----------------------------------------------------------------------------
inline const char*
IldSynonym::getLink () const
{
    return _link;
}

inline const char*
IldSynonym::getTarget () const
{
    return _target;
}

inline const char*
IldSynonym::getTargetOwner() const
{
    return _targetOwner;
}

#endif // __ILD_ILDSYN_H
