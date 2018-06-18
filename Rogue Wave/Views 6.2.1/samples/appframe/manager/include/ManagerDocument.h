// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/include/ManagerDocument.h
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
// IlogViews 4 generated header file
// File generated Wed Mar 08 20:35:33 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the ManagerDocument class
// --------------------------------------------------------------------------
#if !defined(ManagerDocument__header__)
#define ManagerDocument__header__

#if !defined(__Ilv_Appframe_Managdoc_H)
#include <ilviews/appframe/manager/managdoc.h>
#endif /* !__Ilv_Appframe_Managdoc_H */

// --------------------------------------------------------------------------
// ManagerDocument class
// --------------------------------------------------------------------------

class DVAPPCLASS ManagerDocument
: public IlvDvManagerDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ManagerDocument();
    virtual ~ManagerDocument();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean initializeDocument(IlAny = 0);
    virtual void      clean();

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

    // ----------------------------------------------------------------------
    // Export ManagerDocument fields and methods
    IlvDvDeclareInterface();
};

// --------------------------------------------------------------------------
IL_MODULEINIT(ManagerDocument, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !ManagerDocument__header__ */
