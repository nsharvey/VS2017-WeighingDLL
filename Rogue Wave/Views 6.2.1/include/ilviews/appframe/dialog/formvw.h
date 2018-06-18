// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/formvw.h
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
// Declaration of the IlvDvFormView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Dialog_Formvw_H)
#define __Ilv_Appframe_Dialog_Formvw_H

#if !defined(__Ilv_Gadgets_Rectgadc_H)
#include <ilviews/gadgets/rectgadc.h>
#endif
#if !defined(__Ilv_Appframe_Dialog_Inspect_H)
#include <ilviews/appframe/dialog/inspect.h>
#endif
#if !defined(__Ilv_Appframe_View_H)
#include <ilviews/appframe/view.h>
#endif
#if !defined(__Ilv_Appframe_Gadgets_Events_H)
#include <ilviews/appframe/gadgets/events.h>
#endif

// --------------------------------------------------------------------------
// IlvDvFormView class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvFormView
: public IlvGadgetContainerRectangle,
  public IlvDvInspector,
  public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();

public:
    IlvAbstractView*	getDvView();
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvFormView(IlvDisplay*, const IlSymbol* inspectorName = 0);
    virtual ~IlvDvFormView();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void	initializeView();
    virtual IlvGraphic* getGraphic();
    virtual ApplyMode	getApplyMode() const;
    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

protected:
    IlvDvDocViewContext*	_context;
    ApplyMode			_mode;

    virtual IlvDvDocViewContext*	createViewContext();
    virtual IlvDvDocViewContext*	getViewContext() const;

    virtual void	doUpdateModified();
    void		undoUI(IlvDvActionDescriptor*) const;
    void		redoUI(IlvDvActionDescriptor*) const;

protected:
    // Callback management
    void		foreachGraphic(IlvGraphicCallback cb, IlAny param = 0);
    void		foreachGraphicInHolder(IlvGraphicHolder* holder,
					       IlvGraphicCallback cb,
					       IlAny param = 0);

public:
    static void		GraphicCallback(IlvGraphic* g, IlAny param);
    static void		RegisterGraphicCallbacks(IlvGraphic* g, IlAny param);
    static void		InitializeGraphic(IlvGraphic* g, IlAny param);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(formvw);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Formvw_H */
