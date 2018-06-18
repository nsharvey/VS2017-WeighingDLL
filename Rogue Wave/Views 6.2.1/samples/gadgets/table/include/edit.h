// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/include/edit.h
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
// Shows how to create a subclass of the IlvAbstractMatrixItem class.
// Shows how to use a specific editor on an IlvMatrix object.
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Edit_H
#define __Ilv_Samples_Edit_H

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Edit
// --------------------------------------------------------------------------
class Edit : public PageNoteBook 
{
public:
    Edit(IlvAbstractView* view, const char* filename)
	: PageNoteBook(view, filename) 
    {
	initEdit();
    }
    ~Edit() {}
    
protected:
    void		initEdit();
};

#endif /* !__Ilv_Samples_Edit_H*/
