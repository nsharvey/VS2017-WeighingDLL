// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vtfinter.h
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
// Declaration of the IlvViewTextFieldInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vtfinter_H
#define __Ilv31_Vtfinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Contain_Holder)
#include <ilviews/contain/holder.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvViewTextFieldInteractor
: public IlvViewGadgetInteractor {
public:
    IlvViewTextFieldInteractor();
    // ____________________________________________________________
    virtual const char* check(IlvContainer*, IlvTextField*, IlUShort);
    virtual const char* mbCheck(IlvContainer*, IlvTextField*, const char*);
    virtual void validate(IlvContainer*, IlvTextField*);
    virtual IlBoolean handleControl(IlvContainer*, IlvTextField*, IlUShort);
    virtual const char* className() const;
    virtual IlBoolean accept(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvVHTextFieldInteractor
: public IlvHTextFieldInteractor {
public:
    IlvVHTextFieldInteractor(IlvViewTextFieldInteractor* inter)
    : IlvHTextFieldInteractor(),
      _textFieldInteractor(inter)
    {}
    // ____________________________________________________________
    virtual const char* check(IlvTextField*, IlUShort);
    virtual const char* mbCheck(IlvTextField*, const char*);
    virtual void validate(IlvTextField*);
    virtual IlBoolean handleControl(IlvTextField*, IlUShort);
protected:
    IlvViewTextFieldInteractor* _textFieldInteractor;
};

// --------------------------------------------------------------------------
ILV31GDTMODULEINIT(vtfinter);

#endif /* !__Ilv31_Vtfinter_H */
