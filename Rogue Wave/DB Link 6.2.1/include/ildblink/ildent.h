// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildent.h
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

#ifndef __ILD_ILDENT_H
#define __ILD_ILDENT_H

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

// ============================================================================
// Basic properties common to all types of autonomous schema entities
// ============================================================================
class ILD_EXPORTED IldSchemaEntity {

protected:
    IldDbms*		_dbms;
    char*		_name;
    char*		_owner;
    IlInt		_id;
    IldEntityType	_kind;

    IldSchemaEntity		()
	: _dbms(0),
	  _name(0),
	  _owner(0),
	  _id(0),
	  _kind(IldUnknownEntity)
    {};
    IldSchemaEntity		(IldSchemaEntity&);
    IldSchemaEntity&	operator=		(IldSchemaEntity&)
    { return *this; }

public:
    IldSchemaEntity		(const char* name,
				 const char* owner,
				 IldEntityType kind,
				 IlInt id = 0);

    virtual
    ~IldSchemaEntity	();

    virtual
    void		setDbms			(IldDbms* db);
    IldDbms*		getDbms			() const;

    inline
    const char*		getName			() const;

    inline
    const char*		getOwner		() const;

    inline
    IlInt		getId			() const;

    inline
    IldEntityType	getEntityType		() const;
};

// ----------------------------------------------------------------------------
// Inlines for IldSchemaEntity class
// ----------------------------------------------------------------------------
inline const char*
IldSchemaEntity::getName () const
{
    return _name;
}

inline const char*
IldSchemaEntity::getOwner () const
{
    return _owner;
}

inline IlInt
IldSchemaEntity::getId () const
{
    return _id;
}

inline IldEntityType
IldSchemaEntity::getEntityType () const
{
    return _kind;
}

#ifndef __ILD_ILDSYN_H
# include <ildblink/ildsyn.h>
#endif
#ifndef __ILD_ILDCALL_H
# include <ildblink/ildcall.h>
#endif
#ifndef __ILD_ILDADTD_H
# include <ildblink/ildadtd.h>
#endif
#ifndef __ILD_ILDDESC_H
# include <ildblink/ilddesc.h>
#endif
#ifndef __ILD_ILDARG_H
# include <ildblink/ildarg.h>
#endif

#endif // __ILD_ILDENT_H
