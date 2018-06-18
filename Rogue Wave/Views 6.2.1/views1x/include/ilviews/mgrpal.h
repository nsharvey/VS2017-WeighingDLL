// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/mgrpal.h
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
// Declaration of the IlvManagerPalette class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Mgrpal_H
#define __Ilv1X_Mgrpal_H

#if !defined(__Ilv_Paledit_H)
#include <ilviews/paledit.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvManagerPalette
: public IlvPaletteSelector {
public:
    IlvManagerPalette(IlvManager*    manager,
		      const IlvRect& size,
		      IlvBoolean     visible=IlvTrue);
    IlvManagerPalette(IlvManager*      manager,
		      IlvSystemView xany);
    IlvManagerPalette(IlvManager*    display,
		      IlvRowColumnView *);
    // ____________________________________________________________
    void setManager(IlvManager* manager) { _manager = manager; }
    IlvManager* getManager()       const { return _manager; }
    virtual void callCallback(IlvPattern*);
    virtual void callCallback(IlvLineStyle*);
    virtual void callCallback(IlvUShort);
    virtual void callCallback(IlvColor*);
    virtual void callCallback(IlvArcMode);
    virtual void callCallback(IlvFillRule);
    virtual void callCallback(IlvFillStyle);
protected:
    IlvManager* _manager;
};

#endif /* !__Ilv1X_Mgrpal_H */
