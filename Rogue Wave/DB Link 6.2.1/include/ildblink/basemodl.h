// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/basemodl.h
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
// Model for inheritance of DBLink base classes IldDbms & IldRequest.
// ----------------------------------------------------------------------------

#ifndef __ILD_BASEMODL_H
#define __ILD_BASEMODL_H

#ifndef __ILD_ILDBASE_H
#include <ildblink/ildbase.h>
#endif
#ifndef __Il_Hash_H
# include <ilog/hash.h>
#endif

class IldDiagnostic;
class IldErrorReporter;

// ============================================================================
// IldBaseModel class.
// ============================================================================
class ILD_EXPORTED IldBaseModel : public virtual IldIldBase {

 private:  
    static IlHashTable& GetHashTable();

 protected:
    IldIldBase&		_base;
			IldBaseModel		(IldIldBase& ptr); 
    virtual
			~IldBaseModel		();

 public:
    virtual
    IlBoolean		isDbms			() const = 0;
    virtual
    void		initializeError		();
    void		fillError		(IlInt code,
						 IldFuncId fCode,
						 IldErrorOrigin origin,
						 const char* message,
						 const char* sqlstate,
						 const char* name = 0,
						 const char* connection = 0);
    void		fillError		(const IldDiagnostic*);
    void		fillInformation		(IlInt code,
						 IldFuncId fCode,
						 const char* msg);

    int			operator!		() const;

    IlBoolean		isErrorRaised		() const;

    IlBoolean		isInformationRaised	() const;

    void		setError              (IldDiagnostic*);

    void		setInformation        (IldDiagnostic*);

    const IldDiagnostic* getError		() const;

    const IldDiagnostic* getInformation		() const;

    IlInt		getInformationCode	() const;

    const char*		getInformationMessage	() const;

    IlInt		getErrorCode		() const;

    IldErrorOrigin	getErrorOrigin		() const;

    const char*		getErrorSqlstate	() const;

    const char*		getErrorMessage		() const;

    const char*		getErrorConnection	() const;

    const char*		getErrorName		() const;

    virtual
    IldErrorReporter*	getErrorReporter	() const = 0;

    virtual
    IlBoolean		useStringDate		() const;

    virtual
    void		setStringDateUse	(IlBoolean flag = IlTrue);

    virtual
    IlBoolean		useStringNumeric	() const;

    virtual
    void		setStringNumericUse	(IlBoolean flag = IlTrue);

    virtual
    IlBoolean		useNumeric		() const;

    virtual
    void		setNumericUse		(IlBoolean flag);

    static
    IldBaseModel*	getModel		(const IldIldBase* const base);
};

#endif // __ILD_BASEMODL_H
