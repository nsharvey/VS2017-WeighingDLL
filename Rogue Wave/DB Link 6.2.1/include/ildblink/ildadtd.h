// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildadtd.h
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

#ifndef __ILD_ILDADTD_H
#define __ILD_ILDADTD_H

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
#ifndef _VECTOR_
# include <vector>
#endif

class IldDescriptor;
class IldSchemaEntity;

// ============================================================================
// User defined datatypes: Abstract Data Type descriptor
// ============================================================================
class ILD_EXPORTED IldADTDescriptor : public IldSchemaEntity {

protected:
    int                 _refCount;
    IldADTType		_type;
    char*               _litteralTypeName;
    IlUInt		_nAttr;
    IldDescriptor**	_attributes;
    IlUInt		_nMethods;
    IldCallable**	_methods;
    IlUInt		_nElts;

    char*			buildLitteralTypeName  () const;
    virtual
    void			setDbms			(IldDbms* db);

public:
    IldADTDescriptor					();
    IldADTDescriptor					(const char* name,
							 const char* owner,
							 IlInt id,
							 IldADTType type,
							 IldDescriptor** attrs,
							 IlUInt nAttr,
							 IldCallable** m = 0,
							 IlUInt nMeths = 0);

    virtual
    ~IldADTDescriptor					();

    void			lock			();

    int				unLock			();

    IlBoolean			setObject		(IldDescriptor** attrs,
							 IlUInt nAttr,
							 IldCallable** meths,
							 IlUInt nMeths);
    IlBoolean			setTable		(IldDescriptor** cols,
							 IlUInt nCols);
    IlBoolean			setArray		(IlUInt nElts,
							 IldDescriptor* eDesc);

    IldADTType			getType                () const;

    const IldDescriptor* const* getAttributes  () const;

    const IldCallable* const*   getMethods		() const;

    const IldDescriptor*	getCollectionAttribute	() const;

    IlBoolean			isCollectionType	() const;

    IlBoolean			isObjectType		() const;

    IlUInt			getAttributesCount	() const;

    IlUInt			getMethodsCount		() const;

    IlUInt			getCollMaxSize		() const;

    IlBoolean			isNamedType		() const;
    const char*			getLitteralTypeName	() const;
    void			setLitteralTypeName	(const char* tName);

};

#endif // __ILD_ILDADTD_H
