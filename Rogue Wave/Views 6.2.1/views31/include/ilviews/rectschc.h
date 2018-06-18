// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/rectschc.h
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
// Definition of the IlvChartContainerRectangle class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Rectschc_H
#define __Ilv31_Rectschc_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Graphics_Rectview_H)
#include <ilviews/graphics/rectview.h>
#endif
#if !defined(__Ilv_Chartcsc_H)
#include <ilviews/chartcsc.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvChartContainerRectangle
: public IlvViewRectangle {
public:
    IlvChartContainerRectangle(IlvDisplay*,
			       const IlvRect&,
			       const IlvRect&,
			       const IlvPoint&,
			       IlvPosition	= IlvVertical,
			       IlvPosition	= IlvBottomLeft,
			       IlBoolean	= IlTrue,
			       IlvPalette*	= 0);
    virtual ~IlvChartContainerRectangle();
    // ____________________________________________________________
    virtual void apply(IlvApplyObject, IlAny);
    virtual void makeView(IlvPort*, const IlvTransformer* = 0);
    virtual IlvSCChartContainer* getChartContainer() const;
    void setChartContainer(IlvSCChartContainer*);
    static IlSymbol* _AxisProperty;
    static IlSymbol* _VisibilityProperty;
    static IlSymbol* _InteractorProperty;
    static IlSymbol* AxisProperty()       { return _AxisProperty; }
    static IlSymbol* VisibilityProperty() { return _VisibilityProperty; }
    static IlSymbol* InteractorProperty() { return _InteractorProperty; }
    DeclareTypeInfo();
    DeclareIOConstructors(IlvChartContainerRectangle);
protected:
    IlList               _charts;
    IlvRect              _handleRect;
    IlvPoint             _legendPosition;
    IlvPosition          _legendAlignment;
    IlvDeltaPos          _legendSpacing;
    int                  _scalesMask;
    IlvPosition          _currentAxis;
    IlFloat              _shownXMin, _shownXMax;
    IlFloat              _shownYMin, _shownYMax;
    IlvGraphicAttachment _origAttach[3];
    IlFloat              _moveOrigin[3];
    IlvPos               _fixOrigin[3];
    char*                _scaleFormat[3];
    IlUShort             _sbFlags;
    IlBoolean            _useacc;
    IlvGraphic*          _handle;
    void update(const IlvSCChartContainer*);
};

ILV31GDTMODULEINIT(rectschc);
#endif /* __Ilv31_Rectschc_H */
