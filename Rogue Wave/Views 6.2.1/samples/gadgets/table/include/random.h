// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/include/random.h
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
// Definition of a subclass of IlvAstractMatrix.
// The IlvSampleMatrix is a matrix with three columns,
// first row is the index, second row a random value
// third row is a gauge
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Random_H
#define __Ilv_Samples_Random_H

#include <ilviews/graphics/io.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/gauge.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/amatrix.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/base/timer.h>
#include <ilviews/graphics/attach.h>

#if defined(IL_STD)
IL_STDUSE
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>
#else  /* !IL_STD */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#endif /* IL_STD */

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Random
// --------------------------------------------------------------------------
class Random : public PageNoteBook 
{
public:
    Random(IlvAbstractView* view, const char* filename)
        : PageNoteBook(view, filename) 
    {
	initRandom();
    }

    ~Random() {}

 protected:
    void		initRandom();
};

#endif /* !__Ilv_Samples_Random_H*/
