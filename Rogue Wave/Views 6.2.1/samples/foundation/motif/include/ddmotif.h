// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/include/ddmotif.h
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
// Main header file for the Drag&Drop demonstration
// --------------------------------------------------------------------------

#ifndef __Ilv_SampleMotif_Ddmotif_H
#define __Ilv_SampleMotif_Ddmotif_H

#include <X11/Intrinsic.h>
#include <ilviews/contain/contain.h>

// --------------------------------------------------------------------------
class MotifDropSite
{
public:
    MotifDropSite(Widget widget);
    virtual ~MotifDropSite();
    // ------------------------------------------------------------
    Widget getWidget() const { return _widget; }
    virtual void dropRequest(Atom,
			     IlAny,
			     unsigned long,
			     const IlvPoint&) = 0;
    
    static Atom     ILVOBJECT_Atom;
    static Atom     ILVSAVEDOBJECT_Atom;
    static Atom     COMPOUND_TEXT_Atom;
    static MotifDropSite* getSite(Widget widget)
	{ return (MotifDropSite*)_crossRef.get((IlAny)widget); }
private:
    Widget	    _widget;
    static IlAList _crossRef;
};

// --------------------------------------------------------------------------
class ContainerMotifDropSite
: public MotifDropSite
{
public:
    ContainerMotifDropSite(IlvContainer* container)
    : MotifDropSite((Widget)container->getSystemView()),
      _container(container) {}
    // ------------------------------------------------------------
    virtual void dropRequest(Atom,
			     IlAny,
			     unsigned long,
			     const IlvPoint&);
private:
    IlvContainer* _container;
};
#endif /* !__Ilv_SampleMotif_Ddmotif_H */
