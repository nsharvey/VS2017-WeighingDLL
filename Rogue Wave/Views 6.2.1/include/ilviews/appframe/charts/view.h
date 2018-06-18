// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/charts/view.h
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
#if !defined(__Ilv_Appframe_Charts_View_H)
#define __Ilv_Appframe_Charts_View_H

#if !defined(__Ilv_Charts_Graphic_H)
#include <ilviews/charts/graphic.h>
#endif

#if !defined(__Ilv_Appframe_View_H)
#include <ilviews/appframe/view.h>
#endif

#include <ilviews/charts/chartinc.h>

class IlvDvChartView : public IlvChartGraphic, public IlvDvDocViewInterface
{
public:
    IlvDvChartView(IlvDisplay* display);
    ~IlvDvChartView();

    IlvDvDeclareGadgetViewCreate();

protected:
    IlvDvDocViewContext*		_context;
    virtual IlvDvDocViewContext*	createViewContext();
    virtual IlvDvDocViewContext*	getViewContext() const;
};

IL_MODULEINIT(dvchartview, IL_EMPTYMACRO);

#endif
