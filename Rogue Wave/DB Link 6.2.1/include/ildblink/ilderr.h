// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ilderr.h
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
// Error and information diagnostic class
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDERR_H
#define __ILD_ILDERR_H

#ifndef __ILD_ILD_H
#include <ildblink/ild.h>
#endif
#ifdef IL_STD
# ifndef _CSTRING_
#  include <cstring>
# endif
#else
# ifndef _STRING_H
#  include <string.h>
# endif
#endif

// ----------------------------------------------------------------------------
// IldDiagnostic class.
// ----------------------------------------------------------------------------
class ILD_EXPORTED IldDiagnostic {

 protected:
    IlInt		_code;		// DB Link or RDBMS code
    IlInt		_nativeCode;	// RDBMS code or 0
    IldFuncId		_funcCode;	// DbL function which raised
    IldErrorOrigin	_origin;	// Layer which raised
    char		_message[ILD_ERRMSG_SIZE];
    char		_name[ILD_NAME_SIZE];
    char		_connection[ILD_FIELD_SIZE];
    char		_sqlstate[ILD_SQLS_SIZE];

 public:
			IldDiagnostic   ();
			IldDiagnostic   (IlInt code,
					 IldFuncId fCode,
					 IldErrorOrigin origin,
					 const char* msg,
					 const char* sqlstate,
					 const char* name = 0,
					 const char* connection = 0);
			IldDiagnostic   (const IldDiagnostic* err);
    virtual
			~IldDiagnostic  ();

    inline
    IlInt		getCode         () const;

    inline
    IlInt		getNativeCode   () const;

    inline
    IldFuncId		getFunctionCode () const;

    inline
    IldErrorOrigin	getOrigin       () const;

    inline
    const char*		getSqlstate     () const;

    inline
    const char*		getMessage      () const;

    inline
    const char*		getName         () const;

    inline
    const char*		getConnection   () const;

    inline
    void		fill            (IlInt code,
					 IldFuncId fCode,
					 IldErrorOrigin origin,
					 const char* msg,
					 const char* sqlstate,
					 const char* name = 0,
					 const char* connection = 0);
    inline
    void		fill            (const IldDiagnostic* err);
};

// ----------------------------------------------------------------------------
// Inlines for IldDiagnostic class
// ----------------------------------------------------------------------------
inline IlInt
IldDiagnostic::getCode () const
{
    return _code;
}

inline IlInt
IldDiagnostic::getNativeCode () const
{
    return _nativeCode;
}

inline IldFuncId
IldDiagnostic::getFunctionCode() const
{
    return _funcCode;
}

inline IldErrorOrigin
IldDiagnostic::getOrigin () const
{
    return _origin;
}

inline const char*
IldDiagnostic::getSqlstate () const
{
    return _sqlstate;
}

inline const char*
IldDiagnostic::getMessage () const
{
    return _message;
}

inline const char*
IldDiagnostic::getName () const
{
    return _name;
}

inline const char*
IldDiagnostic::getConnection () const
{
    return _connection;
}

inline void
IldDiagnostic::fill (IlInt code ,
		     IldFuncId fCode,
		     IldErrorOrigin origin,
		     const char* msg,
		     const char* sqlstate,
		     const char* name,
		     const char* connection)
{
    _code = code;
    _nativeCode = (origin == IldRDBMServer) ? _code : 0;
    _funcCode = fCode;
    _origin = origin;
    strcpy(_message, msg);
    if (sqlstate)
	strcpy(_sqlstate, sqlstate);
    else
	_sqlstate[0] = 0;
    if (name)
	strcpy(_name, name);
    else
	_name[0] = 0;
    if (connection)
	strcpy(_connection, connection);
    else 
	_connection[0] = 0;
}

inline void
IldDiagnostic::fill (const IldDiagnostic* err)
{
    _code = err->_code;
    _nativeCode = err->_nativeCode;
    _funcCode = err->_funcCode;
    _origin = err->_origin;
    if (err->_sqlstate[0])
	strcpy(_sqlstate, err->_sqlstate);
    else
	_sqlstate[0] = 0;
    strcpy(_message, err->_message);
    if (err->_name[0])
	strcpy(_name, err->_name);
    else
	_name[0] = 0;
    if (err->_connection[0])
	strcpy(_connection, err->_connection);
    else
	_connection[0] = 0;
}

#endif // __ILD_ILDERR_H
