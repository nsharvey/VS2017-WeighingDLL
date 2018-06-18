// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/include/IntroView.h
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
// File generated Thu Mar 09 20:08:54 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the IntroView class
// --------------------------------------------------------------------------
#if !defined(IntroView__header__)
#define IntroView__header__

#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif /* !__Ilv_Appframe_Viewgadg_H */

class DVAPPCLASS IntroDocument;
class ILVDVCLASS IlvDvMethodMember;
class ILVDVCLASS IlvDvFieldMember;
// --------------------------------------------------------------------------
// ValueEditorFactory class
// --------------------------------------------------------------------------

class ValueEditorFactory
{
public:
    static IlvAbstractMatrixItem*
		    CreateMatrixItem(IlvDisplay* display,
				     const IlvValueTypeClass* type);
};

// --------------------------------------------------------------------------
// IntroView class
// --------------------------------------------------------------------------

class DVAPPCLASS IntroView
: public IlvDvHierarchicalSheetView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IntroView(IlvDisplay*);
    virtual ~IntroView();

    // --------------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    IntroDocument* getIntroDocument() const;
    void refreshValues();

    // ----------------------------------------------------------------------
    // Export IntroView fields and methods
    IlvDvDeclareInterface();

protected:
    IlvBitmap* _classBmp;
    IlvBitmap* _fieldBmp;
    IlvBitmap* _methodBmp;

    void memberSelected();
    void memberActivated();
    void executeMethod(IlvDvMethodMember*);
    void changeFieldValue(IlvDvFieldMember*,
			  const char*);
    void fieldToggled(IlvDvFieldMember*,
		      IlBoolean);
    void execSelectedMethod();
    void execSelectedMethodUI(IlvDvActionDescriptor*);
    IlvDvMember* getSelectedMember() const;

public:
    static void ItemSelectedCallback(IlvGraphic*,
				     IlAny);
    static void ItemActivatedCallback(IlvGraphic*,
				      IlAny);
    static void FieldToggled(IlvGraphic*,
			     IlAny);
    static void MatrixItemCallback(IlvMatrix*,
				   IlUShort,
				   IlUShort,
				   IlAny);

};

// --------------------------------------------------------------------------
IL_MODULEINIT(IntroView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !IntroView__header__ */
