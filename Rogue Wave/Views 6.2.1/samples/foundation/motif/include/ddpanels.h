// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/include/ddpanels.h
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
// Motif panels that come with the Drag&Drop demonstration
// --------------------------------------------------------------------------

#ifndef __Ilv_SampleMotif_Ddpanels_H
#define __Ilv_SampleMotif_Ddpanels_H

#include <include/ddmotif.h>

// --------------------------------------------------------------------------
class MotifTextDropSite
: public MotifDropSite {
public:
    MotifTextDropSite(Widget widget):
	MotifDropSite(widget) {}
    virtual void dropRequest(Atom,
			     IlAny,
			     unsigned long,
			     const IlvPoint&);
};

extern Widget CreateMotifPanels(IlvDisplay*);
#endif /* !__Ilv_SampleMotif_Ddpanels_H */
