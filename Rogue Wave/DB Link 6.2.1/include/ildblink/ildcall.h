// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildcall.h
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

#ifndef __ILD_ILDCALL_H
#define __ILD_ILDCALL_H

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
// Procedure or function descriptor
// ============================================================================
class ILD_EXPORTED IldCallable : public IldSchemaEntity {

protected:
    IldArgument**	_args;
    IldDescriptor**	_results;
    IlUShort		_nArgs;
    IlUShort            _nRes;
    IlBoolean           _isProc;

public:
    IldCallable       ();
    IldCallable       (const char* name,
		       const char* owner,
		       IlInt id,
		       IlBoolean isProc,
		       IlUShort nArgs,
		       IldArgument** args,
		       IlUShort nRes = 0,
		       IldDescriptor** results = 0);

    virtual
    ~IldCallable      ();

    inline
    IlBoolean		isProcedure       () const;

    inline
    void		setArguments      (IldArgument** args,
					   IlUShort nArgs);
    inline
    IldArgument**	getArguments      () const;

    inline
    IlUShort		getArgumentsCount () const;

    inline
    void		setResults        (IldDescriptor** results,
					   IlUShort nRes);
    inline
    IldDescriptor**	getResults        () const;

    inline
    IlUShort		getResultsCount   () const;
};

// ----------------------------------------------------------------------------
// Inlines for IldCallable class
// ----------------------------------------------------------------------------
inline IlBoolean
IldCallable::isProcedure () const
{
    return _isProc;
}

inline void
IldCallable::setArguments (IldArgument** args,
			   IlUShort nArgs)
{
    _args = args;
    _nArgs = nArgs;
}

inline IldArgument**
IldCallable::getArguments () const
{
    return _args;
}

inline IlUShort
IldCallable::getArgumentsCount () const
{
    return _nArgs;
}

inline void
IldCallable::setResults (IldDescriptor** results,
			 IlUShort nResults)
{
    _results = results;
    _nRes = nResults;
}

inline IldDescriptor**
IldCallable::getResults () const
{
    return _results;
}

inline IlUShort
IldCallable::getResultsCount () const
{
    return _nRes;
}

#endif // __ILD_ILDCALL_H
