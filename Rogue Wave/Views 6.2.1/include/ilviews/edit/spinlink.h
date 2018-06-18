// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/spinlink.h
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
// Declaration of the IlvMakeSpinLinkInteractor class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Spinlink_H
#define __Ilv_Edit_Spinlink_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class ILVGDTEXPORTED IlvSpinBox;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvMakeSpinLinkInteractor
: public IlvManagerViewInteractor {
public:
    IlvMakeSpinLinkInteractor(IlvManager* mgr, IlvView* v);
    IlvMakeSpinLinkInteractor();
    ~IlvMakeSpinLinkInteractor();
    // ____________________________________________________________
    virtual void attach(IlvManager* manager, IlvView* view);
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void abort() ;
    virtual void init() ;
    virtual void drawGhost();
    virtual void doIt(IlvSpinBox* sb,IlvGraphic*, IlvGraphic*);
protected:
    IlvSpinBox*                   _spin;
    IlvGraphic*                   _graphic;
    IlvGraphic*                   _field;
    IlvPoint                      _prev;
    IlvPoint                      _first;
};

#endif /* !__Ilv_Edit_Spinlink_H */