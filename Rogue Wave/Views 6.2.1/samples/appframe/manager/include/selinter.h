// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/include/selinter.h
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
// Declaration of the SelectInteractor class
// --------------------------------------------------------------------------
#if !defined(__Selinter_H)
#define __Selinter_H

#if !defined(__Ilv_Manager_Selinter_H)
#  include <ilviews/manager/selinter.h>
#endif
#if !defined(__Ilv_Appframe_Macros_H)
#  include <ilviews/appframe/macros.h>
#endif

class ManagerView;
// --------------------------------------------------------------------------
// SelectInteractor class
// --------------------------------------------------------------------------
class DVAPPCLASS SelectInteractor
: public IlvSelectInteractor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SelectInteractor(IlvManager*         manager,
			  ManagerView*   view,
			  unsigned short button     = IlvLeftButton,
			  IlBoolean      showCursor = IlFalse);
    virtual ~SelectInteractor();

    // ----------------------------------------------------------------------
    virtual void   addedToSelection(IlvGraphic*);
    virtual void   removedFromSelection(IlvGraphic*);
    virtual void   doTranslate(const IlvPoint&);
    virtual void   doReshape(IlvGraphic*, const IlvRect&);
    virtual void   objectReSelected(IlvGraphic*);
    virtual IlBoolean handleEvent(IlvEvent&);

    inline void setTranslationStep(const IlvPoint& pt)
	{ _translationStep = pt; }

protected:
    ManagerView* _view;
    IlvPoint              _translationStep;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(selinter, IL_EMPTYMACRO);
#endif /* !__Selinter_H */
