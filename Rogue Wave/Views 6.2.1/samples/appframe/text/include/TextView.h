// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/text/include/TextView.h
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
// File generated Thu Mar 09 20:27:35 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the TextView class
// --------------------------------------------------------------------------
#if !defined(TextView__header__)
#define TextView__header__

#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif /* !__Ilv_Appframe_Viewgadg_H */

#if !defined(__Ilv_Base_Resource_H)
#include <ilviews/base/resource.h>
#endif /* !__Ilv_Base_Resource_H */

class DVAPPCLASS TextDocument;
class ILVGDTEXPORTED IlvScrolledComboBox;

// --------------------------------------------------------------------------
// TextView class
// --------------------------------------------------------------------------

class DVAPPCLASS TextView
: public IlvDvTextView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    TextView(IlvDisplay* display);
    virtual ~TextView();

    // -------------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    void toggleBold();
    void toggleItalic();
    void toggleUnderline();
    TextDocument* getTextDocument() const;
    const char* getFontFamily() const;

    // ----------------------------------------------------------------------
    // Export TextView fields and methods
    IlvDvDeclareInterface();

protected:
    void selectFont(IlvScrolledComboBox*);
    void fontChanged(IlvScrolledComboBox*);

    IlString _currentSizesFontName;
    void fillSizes(IlvScrolledComboBox*);
    void sizeChanged(IlvScrolledComboBox*);
    void toggleFontStyle(IlvFontStyle);

    void boldUI(IlvDvActionDescriptor* desc);
    void ItalicUI(IlvDvActionDescriptor* desc);
    void underlineUI(IlvDvActionDescriptor* desc);

    void fontStyleUI(IlvDvActionDescriptor* desc, IlvFontStyle);
};


// --------------------------------------------------------------------------
IL_MODULEINIT(TextView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !TextView__header__ */
