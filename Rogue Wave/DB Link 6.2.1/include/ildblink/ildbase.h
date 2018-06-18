// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildbase.h
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
// Base class for Dbms and Request classes
// ----------------------------------------------------------------------------
#ifndef __ILD_ILDBASE_H
#define __ILD_ILDBASE_H

#ifndef __ILD_ILD_H
#include <ildblink/ild.h>
#endif

class IldDiagnostic;
class IldErrorReporter;

// ============================================================================
// IldIldBase class.
// ============================================================================
class ILD_EXPORTED IldIldBase {

public:
    virtual
    ~IldIldBase           () {};
    virtual
    IlBoolean		isDbms                () const = 0;
    virtual
    void		initializeError       () = 0;
	void		clearDiagnostics		()
	{
		initializeError();
	}
    virtual
    void		fillError             (IlInt code,
					       IldFuncId fCode,
					       IldErrorOrigin origin,
					       const char* message,
					       const char* sqlstate,
					       const char* name = 0,
					       const char* conn = 0) = 0;
    virtual
    void		fillError             (const IldDiagnostic*) = 0;
    virtual
    void		fillInformation       (IlInt code,
					       IldFuncId fCode,
					       const char* msg) = 0;

    virtual
    int			operator!             () const = 0;

    virtual
    IlBoolean		isErrorRaised         () const = 0;

    virtual
    IlBoolean		isInformationRaised   () const = 0;

    virtual
    void		setError              (IldDiagnostic* diag) = 0;

    virtual
    void		setInformation        (IldDiagnostic* diag) = 0;

    virtual
    const IldDiagnostic* getError              () const = 0;

    virtual
    const IldDiagnostic* getInformation        () const = 0;

    virtual
    IlInt		getInformationCode    () const = 0;

    virtual
    const char*		getInformationMessage () const = 0;

    virtual
    IlInt		getErrorCode          () const = 0;

    virtual
    IldErrorOrigin	getErrorOrigin        () const = 0;

    virtual
    const char*		getErrorSqlstate      () const = 0;

    virtual
    const char*		getErrorMessage       () const = 0;

    virtual
    const char*		getErrorConnection    () const = 0;

    virtual
    const char*		getErrorName          () const = 0;

    virtual
    IldErrorReporter*	getErrorReporter      () const = 0;

    virtual
    IlBoolean		useStringDate         () const = 0;

    virtual
    void		setStringDateUse      (IlBoolean flag = IlTrue) = 0;

    virtual
    IlBoolean		useStringNumeric      () const = 0;

    virtual
    void		setStringNumericUse   (IlBoolean flag = IlTrue) = 0;

    virtual
    IlBoolean		useNumeric            () const = 0;

    virtual
    void		setNumericUse         (IlBoolean flag) = 0;
};

#endif // __ILD_ILDBASE_H
