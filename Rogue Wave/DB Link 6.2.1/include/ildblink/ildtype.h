// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildtype.h
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
// SQL column data type descriptors
// --------------------------------------------------------------------------
#ifndef __ILD_ILDTYPE_H
#define __ILD_ILDTYPE_H

#if !defined(__ILD_DBUTIL_H)
#  include <ildblink/dbutil.h>
#endif
#if !defined(__Il_Memory_H)
#  include <ilog/memory.h>
#endif

// ==========================================================================
// IldSQLType class.
// ==========================================================================
class ILD_EXPORTED IldSQLType {
public:
    IldSQLType           ()
    : _name(0),
      _prefix(0),
      _suffix(0),
      _params(0),
      _nullable(1),
      _localName(0)
    {}
    IldSQLType           (const char*,
			  short,
			  IlUInt,
			  const char*,
			  const char*,
			  const char*,
			  short,
			  IlBoolean,
			  short,
			  short,
			  IlBoolean,
			  const char* = 0,
			  IlInt = 0,
			  IlInt = 0);
    virtual
    ~IldSQLType          ();

    inline
    void        setName              (const char* name)
	{
	    if (name) {
		_name = IlCopyString(name, IlFalse);
	    }
	}
    inline
    const char* getName              () const
	{ return _name; }

    inline
    void        setType              (short type)
	{ _type = type; }
    inline
    short       getType              () const
	{ return _type; }

    inline
    void        setSize              (IlUInt size)
	{ _size = size; }
    inline
    IlUInt      getSize              () const
	{ return _size; }

    inline
    void        setPrefix            (const char* prefix)
	{
	    if (prefix) {
		_prefix = IlCopyString(prefix, IlFalse);
	    }
	}
    inline
    const char* getPrefix            () const
	{ return _prefix; }

    inline
    void        setSuffix            (const char* suffix)
	{
	    if (suffix) {
		_suffix = IlCopyString(suffix, IlFalse);
	    }
	}
    inline
    const char* getSuffix            () const;

    inline
    void        setParams            (const char* params)
	{
	    if (params) {
		_params = IlCopyString(params, IlFalse);
	    }
	}
    inline
    const char* getParams            () const
	{ return _params; }

    inline
    void        setNullable          (short nullable)
	{ _nullable = nullable; }
    inline
    short       getNullable          () const
	{ return _nullable; }

    inline
    void        setCaseSensitive     (IlBoolean caseSensitive)
	{ _caseSensitive = caseSensitive; }
    inline
    IlBoolean   getCaseSensitive     () const
	{ return _caseSensitive; }

    inline
    void        setSearchable        (short searchable)
	{ _searchable = searchable; }
    inline
    short       getSearchable        () const
	{ return _searchable; }

    inline
    void        setUnsignedAttribute (short unsignedAttr)
	{ _unsignedAttribute = unsignedAttr; }
    inline
    short       getUnsignedAttribute () const
	{ return _unsignedAttribute; }

    inline
    void        setAutoUnique        (IlBoolean autoUnique)
	{ _autoUnique = autoUnique; }
    inline
    IlBoolean   getAutoUniqueValue   () const
	{ return _autoUnique; }

    inline
    void        setLocalName         (const char* local)
	{
	    if (local) {
		_localName = IlCopyString(local, IlFalse);
	    }
	}
    inline
    const char* getLocalName         () const
	{ return _localName; }

    inline
    void        setMinScale          (IlInt min)
	{ _minScale = min; }
    inline
    IlInt       getMinScale          () const
	{ return _minScale; }

    inline
    void        setMaxScale          (IlInt max)
	{ _maxScale = max; }
    inline
    IlInt       getMaxScale          () const
	{ return _maxScale; }
protected:
    char*		_name;
    IlUInt		_size;
    char*		_prefix;
    char*		_suffix;
    char*		_params;
    short		_type;
    short		_nullable;
    IlBoolean		_caseSensitive;
    short		_searchable;
    short		_unsignedAttribute;
    IlBoolean		_autoUnique;
    char*		_localName;
    IlInt		_minScale;
    IlInt		_maxScale;
};

#endif /* !__ILD_ILDTYPE_H */
