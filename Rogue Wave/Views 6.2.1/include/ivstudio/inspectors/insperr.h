// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/insperr.h
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
// Declaration of error classes
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Insperr_H)
#define __IlvSt_Inspectors_Insperr_H

#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif

class IlvStError;
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIError
    : public IlvStObject
{
    IlvDeclareInspClassInfo();
public:
    enum Severity {
	Information,
	Warning,
	Fatal
    };

    IlvStIError(const char* msg = 0, Severity severity = Fatal);

    IlvStIError(const char* msg,
		const char* param1,
		Severity severity = Fatal);
    IlvStIError(const char* msg,
		const char* param1,
		const char* param2,
		Severity severity = Fatal);
    IlvStIError(const char*,
		const char*,
		const char*,
		const char*,
		Severity = Fatal);
    IlvStIError(IlvStError*);
    ~IlvStIError();

    Severity		getSeverity() const;
    void		setSeverity(Severity severity);

    virtual char*	getMessage(IlvDisplay* display) const;

protected:
    IlString*		_strs;
    int			_numStrs;
    Severity		_severity;

    void		empty();
};

// --------------------------------------------------------------------------
// IlvStIErrorManager class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIErrorManager
    : public IlvStObject
{
    IlvDeclareInspClassInfo();
public:
    IlvStIErrorManager(IlvDisplay* display = 0)
    : _display(display)
    {}

    IlvDisplay*		getDisplay() const { return _display; }

    virtual void	displayError(IlvStIError*,
				     IlBoolean = IlTrue);

protected:
    IlvDisplay*		_display;
};

// --------------------------------------------------------------------------
// Useful functions
ILVINSPEXPORTEDFUNC(IlString)
IlvStIFormatString(IlvDisplay*, const char*, ...);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_insperr)
#endif /* !__IlvSt_Inspectors_Insperr_H */
