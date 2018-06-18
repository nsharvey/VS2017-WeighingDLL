// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vrgcnbpg.h
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
// Declaration of the IlvVariableGadgetContainerNotebookPage class
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vrgcnbpg_H
#define __Ilv31_Vrgcnbpg_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Vrgadcon_H)
#include <ilviews/vrgadcon.h>
#endif
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableGadgetContainerNotebookPage
: public IlvNotebookPage
{
public:
    IlvVariableGadgetContainerNotebookPage(IlvNotebook* notebook,
					   const char*  label,
					   IlvBitmap*   bitmap,
					   IlBoolean    transparent,
					   const char*  filename);
    virtual ~IlvVariableGadgetContainerNotebookPage();
    // ____________________________________________________________
    IlvParser* getParser() const { return _parser; }
    virtual IlvView* createView(IlvAbstractView* parent,
				const IlvRect&   size);
    DeclareLazyNotebookPageInfoRO();
    DeclareNotebookPageIOConstructors(IlvVariableGadgetContainerNotebookPage);
protected:
    IlvParser* _parser;
};

ILV31VARMODULEINIT(vrgcnbpg);
#endif /* !__Ilv31_Vrgcnbpg_H */
