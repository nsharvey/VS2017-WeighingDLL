// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/include/IntroDocument.h
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
// File generated Thu Mar 09 20:08:53 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the IntroDocument class
// --------------------------------------------------------------------------
#if !defined(IntroDocument__header__)
#define IntroDocument__header__

#if !defined(__Ilv_Appframe_Document_H)
#include <ilviews/appframe/document.h>
#endif /* !__Ilv_Appframe_Document_H */

// --------------------------------------------------------------------------
// IntroDocument class
// --------------------------------------------------------------------------

class DVAPPCLASS IntroDocument
: public IlvDvDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IntroDocument();
    virtual ~IntroDocument();

    void refreshValues();
    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean  initializeDocument(IlAny = 0);
    virtual void       clean();

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

    // ----------------------------------------------------------------------
    // Export IntroDocument fields and methods
    IlvDvDeclareInterface();

protected:
    IlvString  _name;
    IlInt     _x;
    IlInt     _y;
    IlBoolean _isScaling;
    IlFloat   _scaleFactor;
    IlDouble  _price;
    void setName(const char*);
    const char* getName();
    void setScaleFactor(IlBoolean = IlTrue,
			IlFloat = (IlFloat)50.);
    IlDouble setPrice(IlDouble);
};

// --------------------------------------------------------------------------
IL_MODULEINIT(IntroDocument, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !IntroDocument__header__ */
