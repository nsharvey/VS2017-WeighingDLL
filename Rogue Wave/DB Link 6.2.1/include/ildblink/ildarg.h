// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildarg.h
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

#ifndef __ILD_ILDARG_H
#define __ILD_ILDARG_H

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

class IldDescriptor;

// ============================================================================
// Procedure or function argument descriptor
// ============================================================================
class ILD_EXPORTED IldArgument : public IldDescriptor {

protected:
    short		_iomode; // IN: 0, OUT: 1, INOUT: 2
    short		_default; // 0: no default, 1: default specified

public:
    IldArgument     ();
    IldArgument     (IldColumnType ildType,
		     const char* name,
		     IlUInt size,
		     short precision,
		     short scale,
		     short sqlType,
		     const char* typeName,
		     IlBoolean nullable,
		     short iomode,
		     short hasDefault = 0,
		     const char* typeOwner = 0);
    virtual
    ~IldArgument    ();

    inline
    IlBoolean		isInArgument    () const;

    inline
    IlBoolean		isOutArgument   () const;

    inline
    IlBoolean		isInOutArgument () const;

    inline
    IlBoolean		hasDefault      () const;
};

// ----------------------------------------------------------------------------
// Inlines for IldArgument class
// ----------------------------------------------------------------------------
inline IlBoolean
IldArgument::isInArgument () const
{
    return (IlBoolean)(_iomode != 1);
}

inline IlBoolean
IldArgument::isOutArgument () const
{
    return (IlBoolean)(_iomode != 0);
}

inline IlBoolean
IldArgument::isInOutArgument () const
{
    return isInArgument() && isOutArgument();
}

inline IlBoolean
IldArgument::hasDefault () const
{
    return (IlBoolean)(_default == 1);
}

#endif // __ILD_ILDARG_H
