// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/ilvvar.h
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
// Declaration of the IlvAttribute class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Ilvvar_H
#define __Ilv31_Ilvvar_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif

#if !defined(__Ilv_Ilvattr_H)
#include <ilviews/ilvattr.h>
#endif

class IlvVariable;
class IlvvFundamental;

#if !defined(IlvFundamental)
#define IlvFundamental IlvvFundamental
#endif /* !IlvFundamental */

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAttribute
: public IlvAbstractAttribute
{
public:
    IlvAttribute(const char* name = 0);
    IlvAttribute(IlvVariable* variable);
    virtual ~IlvAttribute();
    // ____________________________________________________________
    void setVariable(IlvVariable* variable);
    IlvVariable* getVariable() const { return _variable; }
    const char* getName()      const { return _name; }
    void setName(const char* name);
    virtual IlvAbstractVariable* getAbstractVariable() const;
    //---------------------------------------------------------------------
    // CHANGE
    virtual IlBoolean isaGraphicAttribute();
    virtual void notifySet(const IlvFundamental& value);
    virtual void notifyInCycle();
    virtual void notifyUndefined();

    virtual void setValue(IlInt   value);
    virtual void setValue(IlFloat value);
    virtual void setValue(const char* formula);
    virtual IlFloat getValue()=0;
protected:
    char*        _name;
    IlvVariable* _variable;
};

typedef void (* IlvApplyAttribute)(IlvAttribute* f, IlAny arg);

#endif /* __Ilv31_Ilvvar_H */
