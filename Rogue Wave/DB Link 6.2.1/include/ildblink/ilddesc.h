// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ilddesc.h
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

#ifndef __ILD_ILDDESC_H
#define __ILD_ILDDESC_H

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

class IldADTDescriptor;

// ============================================================================
// Descriptor
// Kinda SQL99 IPD & IRD
// ============================================================================
class ILD_EXPORTED IldDescriptor {

protected:
    IldColumnType	_ildType;
    char		_name[ILD_NAME_SIZE];
    IlUInt		_size;
    // SQL type name may be a complex type
    char		_typeName[ILD_FIELD_SIZE];
    char		_typeOwner[ILD_NAME_SIZE];
    char                _tableName[ILD_FIELD_SIZE];
    IlBoolean		_nullable;
    IldADTDescriptor*	_adt;
    short		_precision;
    short		_scale;
    short		_sqlType;

    IldDescriptor&	operator=              (IldDescriptor&)
    { return *this; }

public:
    IldDescriptor          ();
    IldDescriptor          (IldColumnType ildType,
			    const char* name,
			    IlUInt size,
			    short precision,
			    short scale,
			    short sqlType,
			    const char* typeName,
			    IlBoolean nullable,
			    const char* typeOwner = 0);
    virtual
    ~IldDescriptor         ();
    void		setADTDescriptor       (IldADTDescriptor* adt);

    inline
    IldADTDescriptor*	getADTDescriptor       () const;

    void		clear                  ();
    void		set                    (IldColumnType type,
						IlBoolean nullable, 
						IlUInt size,
						short sqlType,
						const char* sqlTypeName,
						short precision,
						short scale,
						const char* typeOwner = 0);
    void		set                    (IldDescriptor*);
    inline
    void		setType                (IldColumnType ildType);

    inline
    IldColumnType	getType                () const;

    void		setName                (const char* name,
						int nLen = 0);
    inline
    const char*		getName                () const;

    inline
    void		setSqlType             (short type);
    inline
    short		getSqlType             () const;

    void		setTypeName            (const char* typeName,
						int nLen = 0);
    inline
    const char*		getSqlTypeName         () const;

    void		setTypeOwner           (const char* owner,
						int nLen = 0);
    void		setTableName           (const char* owner,
						int nLen = 0);
    inline
    const char*		getTypeOwner           () const;
    const char*		getTableName           () const;
    inline
    void		setPrecision           (short prec);

    inline
    short		getPrecision           () const;

    inline
    void		setScale               (short scale);
    inline
    short		getScale               () const;

    inline
    void		setSize                (IlUInt size);
    inline
    IlUInt		getSize                () const;

    inline
    void		setNullable            (IlBoolean flag);
    inline
    IlBoolean		isNullable             () const;
};

// ----------------------------------------------------------------------------
// Inlines for IldDescriptor class
// ----------------------------------------------------------------------------
inline IldADTDescriptor*
IldDescriptor::getADTDescriptor () const
{
    return _adt;
}

inline void
IldDescriptor::setType (IldColumnType ildType)
{
    _ildType = ildType;
}

inline IldColumnType
IldDescriptor::getType () const
{
    return _ildType;
}

inline const char*
IldDescriptor::getName () const
{
    return _name;
}

inline void
IldDescriptor::setSqlType (short type)
{
    _sqlType = type;
}

inline short
IldDescriptor::getSqlType () const
{
    return _sqlType;
}

inline const char*
IldDescriptor::getSqlTypeName () const
{
    return _typeName;
}

inline const char*
IldDescriptor::getTypeOwner () const
{
    return _typeOwner;
}

inline const char*
IldDescriptor::getTableName() const
{
    return _tableName;
}

inline void
IldDescriptor::setPrecision (short prec)
{
    _precision = prec;
}

inline short
IldDescriptor::getPrecision () const
{
    return _precision;
}

inline void
IldDescriptor::setScale (short scale)
{
    _scale = scale;
}

inline short
IldDescriptor::getScale () const
{
    return _scale;
}

inline void
IldDescriptor::setSize (IlUInt size)
{
    _size = size;
}

inline IlUInt
IldDescriptor::getSize () const
{
    return _size;
}

inline void
IldDescriptor::setNullable (IlBoolean flag)
{
    _nullable = flag;
}

inline IlBoolean
IldDescriptor::isNullable () const
{
    return _nullable;
}

#endif // __ILD_ILDDESC_H
