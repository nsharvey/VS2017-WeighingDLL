// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/optmint.h
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
// Declaration of the IlvManagerOptionMenuInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------

#ifndef __Ilv31_Optmint_H
#define __Ilv31_Optmint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Manager_Holder_H)
#include <ilviews/manager/holder.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvManagerOptionMenuInteractor
    : public IlvManagerGadgetInteractor
{
 public:
    IlvManagerOptionMenuInteractor();
    // ____________________________________________________________
    virtual void        doIt(IlvManager*, IlvView*, IlvOptionMenu*);
    virtual const char* className() const;
    virtual IlBoolean   accept(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvMHOptionMenuInteractor
    : public IlvHOptionMenuInteractor
{
 public:
    IlvMHOptionMenuInteractor(IlvManagerOptionMenuInteractor* inter)
	: IlvHOptionMenuInteractor(),
	_optionMenuInteractor(inter)
	{}
    // ____________________________________________________________
    virtual void doIt(IlvOptionMenu*);
 protected:
    IlvManagerOptionMenuInteractor* _optionMenuInteractor;
};

// --------------------------------------------------------------------------
ILV31GDTMODULEINIT(optmint);

#endif /* !__Ilv31_Optmint_H */
