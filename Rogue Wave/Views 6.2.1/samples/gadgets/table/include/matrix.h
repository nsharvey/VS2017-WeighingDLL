// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/include/matrix.h
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
// Definition of a IlvSampleMatrix subclass.
// Sub class of IlvAstractMatrix, the IlvSampleMatrix is a matrix
// with two column, and the number of rows is not limited.
// Each row shows the number of the row
// an icon is drawn on the second column every 10 item.
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Matrix_H
#define __Ilv_Samples_Matrix_H

#include <ilviews/graphics/io.h>
#include <ilviews/gadgets/amatrix.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/bitmaps/png.h>

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
// Panel class for sample Matrix
// --------------------------------------------------------------------------
class Matrix : public PageNoteBook 
{
public:
    Matrix(IlvAbstractView* view, const char* filename)
	: PageNoteBook(view, filename) 
    {
	initMatrix();
    }

    ~Matrix() {}

 protected:
    void		initMatrix();
};

#endif /* !__Ilv_Samples_Matrix_H*/
