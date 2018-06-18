// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/error.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliErrorMessage and IliErrorList classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Error_H
#define __Ili_Error_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ili_Common_H)
#  include <ilviews/dataccess/common.h>
#endif
#if !defined(__Ili_Errcodes_H)
#  include <ilviews/dataccess/errcodes.h>
#endif

class ILV_INF_EXPORTED IliErrorSink;
class IliErrorMessageIpl;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorMessage
{
public:
    enum Severity {
	NotAnError,
	Warning,
	Error
    };

    enum Origin {
	UnknownOrigin,
	DbmsServer,
	DbmsClientAPI,
	DbLink,
	DataAccess,
	Application
    };

    IliErrorMessage();
    IliErrorMessage(Severity	severity,
		    Origin	origin,
		    IlInt	code,
		    const char*	message);
    IliErrorMessage(const IliErrorMessage&);
    ~IliErrorMessage() {}

    IliErrorMessage& operator=(const IliErrorMessage& msg);

    void		unset();

    void		set(Severity	severity,
			    Origin	origin,
			    IlInt	code,
			    const char*	message);

    IlBoolean		isDefined() const;

    IlBoolean		isAWarning() const;
    IlBoolean		isAnError() const;

    Severity		getSeverity() const;

    Origin		getOrigin() const;

    IlInt		getCode() const;

    const char*		getMessage() const;
    const char*		getParameter1() const;
    const char*		getParameter2() const;

    void		prettyPrint(IliString& dst) const;
    void		dump(IL_STDPREF ostream&) const;

    void		setDataAccessError(IliErrorCodeTag,
					   const char* = 0,
					   IlInt = 0);
    void		setDataAccessError(IliErrorCodeTag,
					   const char*,
					   const char*);
    void		setApplicationError(const char* msg);

    IlBoolean		hasBeenReported() const;
    void		setAsReported(IlBoolean);
    void		realize() const;
    static void		AddErrorSink(IliErrorSink* sink);
    static void		RemoveErrorSink(IliErrorSink* sink);

    // Error codes to messages
    static const char*	GetErrorText(IliErrorCodeTag);
    static void		SetErrorText(IliErrorCodeTag, const char*);
    static void		ReadMessageDatabase(IlvDisplay* display);
    static void		ConnectToMessageDatabase(IlvDisplay*);

    ILV_MLK_DECL();

    static void		AtInit();
    static void		AtExit();

protected:
    IliErrorMessageIpl* _ipl;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorSink
{
public:
    IliErrorSink() {}
    IliErrorSink(const IliErrorSink&) {}
    virtual ~IliErrorSink();


    IliErrorSink& operator=(const IliErrorSink& sink) { return *this; }
    virtual void	addError(const IliErrorMessage& msg);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorList
: public IliErrorSink
{
public:
    IliErrorList() {}
    IliErrorList(const IliErrorList&);
    virtual ~IliErrorList();

    IliErrorList& operator=(const IliErrorList& list);
    IlInt		getErrorsCount() const;
    const IliErrorMessage& getErrorAt(IlInt pos) const;
    void		append(const IliErrorList& list);
    virtual void	addError(const IliErrorMessage& msg);
    void		removeErrorAt(IlInt pos);
    void		removeAllErrors();

    void		dump(IL_STDPREF ostream&) const;

protected:
    IlvArray		_errors;
    IliErrorMessage	_dummyError;
};

#if !defined(__Ili_Erroritf_H)
#  include <ilviews/dataccess/intrface/erroritf.h>
#endif

IliModuleDECL_exp(ILV_INF_EXPORTED, IliErrorMessage);

#endif /* !__Ili_Error_H */
