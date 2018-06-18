// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/scrolling/include/cyclic.h
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
// Demonstrating the cyclic mode of charts.
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Cyclic_H
#define __Ilv_Samples_Cyclic_H

#include <ilviews/graphics/attach.h>
#include <ilviews/base/timer.h>

// Include for all charts class headers
#include <ilviews/charts/chartinc.h>

// General purpose functions for the samples
#include <samputil.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Cyclic
// --------------------------------------------------------------------------
class Cyclic : public PageNoteBook
{
public:
    Cyclic(IlvAbstractView* view, const char* filename);
    ~Cyclic();

protected:
    void initCyclic();
};

#endif /* !__Ilv_Samples_Cyclic_H*/