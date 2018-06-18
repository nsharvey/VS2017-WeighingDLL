// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/include/hugetabl.h
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
// Demonstrates a logical scroll on 100000 rows.
// SIZE is the number of rows of the data array
// ALLOCATEDSIZE is the number of actual rows in the matrix
// the bigger it is, the best results you'll get, but it must be an IlvUShort
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Huge_H
#define __Ilv_Samples_Huge_H

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Huge
// --------------------------------------------------------------------------
class Huge : public PageNoteBook 
{
 public:
    Huge(IlvAbstractView* view, const char* filename)
	: PageNoteBook(view, filename) 
    {
	initHuge();
    }
    ~Huge() {}

 protected:
    void		initHuge();
};

#endif /* !__Ilv_Samples_Huge_H*/
