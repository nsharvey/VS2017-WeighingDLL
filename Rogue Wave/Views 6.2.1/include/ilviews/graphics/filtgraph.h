// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/filtgraph.h
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
// Declaration of the IlvFilteredGraphic class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Filtgraph_H
#define __Ilv_Graphics_Filtgraph_H

#if !defined(__Ilv_Graphics_Handle_H)
#include <ilviews/graphics/handle.h>
#endif
#if !defined(__Il_String_H)
#include <ilog/string.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Bitmaps_Flow_H)
#include <ilviews/bitmaps/flow.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilteredGraphic : public IlvGraphicHandle
{
public:
    IlvFilteredGraphic(IlvDisplay*,
		       IlvGraphic*, 
		       const IlString& = IlString(),
		       IlBoolean       = IlFalse);

    virtual ~IlvFilteredGraphic();
    void		computeBitmapData(const IlvTransformer* t = 0);
    enum RefreshMode {
	RefreshOnDemand,
	RefreshAlways
    };
    enum DisplayMode {
	DisplayFiltered,
	DisplayShowThrough
    };
    void		setRefreshMode(RefreshMode mode);
    inline RefreshMode	getRefreshMode() const { return _refreshMode; }
    void		setDisplayMode(DisplayMode mode);
    inline DisplayMode	getDisplayMode() const { return _displayMode; }
    void		invalidate();
    IlBoolean		isInvalid() const;
    void		setInternalColor(IlvColor* color);
    inline IlvColor*	getInternalColor() const 
	{ return _ipalette->getForeground(); }
    inline void		setMaximumSize(IlUInt size)
	{ _maxsize = size; }
    inline IlUInt	getMaximumSize() const
	{ return _maxsize; }
    const IlvBitmapData* getInternalBitmapData() const { return _bdata; }
    void		setFilterName(const IlString& filter);
    inline
    const IlString&	getFilterName() const { return _filterName; }
    inline
    IlvFilterFlow*	getFilterFlow() const { return _filter; }
    void		setFilterFlow(IlvFilterFlow* flow);
    virtual IlBoolean	zoomable() const;
    void		draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    void		boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* = 0) const;
    virtual IlBoolean	intersects(const IlvRegion&,
				   const IlvTransformer* = 0) const;
    virtual IlBoolean	inside(const IlvRegion&,
			       const IlvTransformer* = 0) const;
    void		applyTransform(const IlvTransformer*);
    virtual IlvDisplay* getDisplay() const;
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setPattern(IlvPattern*);
    virtual void	setGradientPattern(IlvGradientPattern*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void	setPalette(IlvPalette*);
    virtual void	invert(IlBoolean = IlFalse);
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    DeclareGraphicAccessors();

    static IlSymbol*	_maxsizeValue;
    static IlSymbol*	_internalColorValue;
    static IlSymbol*	_filterNameValue;
    static IlSymbol*	_refreshModeValue;
    static IlSymbol*	_displayModeValue;

    DeclareIOConstructors(IlvFilteredGraphic);
    DeclareLazyTypeInfo();

protected:
    IlString		_filterName;
    IlvFilterFlow*	_filter;
    IlvBitmapData*	_bdata;
    RefreshMode		_refreshMode;
    DisplayMode		_displayMode;
    IlUInt		_maxsize;
    IlvPalette*		_ipalette;
    IlvTransformer*	_cachedTransform;
};

IlvDeclareEnumTypeClass(ILVVWSEXPORTED,RefreshMode);
IlvDeclareEnumTypeClass(ILVVWSEXPORTED,DisplayMode);

extern ILVVWSEXPORTEDVAR(IlvValueRefreshModeTypeClass*)
IlvValueRefreshModeType;
extern ILVVWSEXPORTEDVAR(IlvValueDisplayModeTypeClass*)
IlvValueDisplayModeType;

ILVVWSMODULETERM(g0filter);
#endif /* __Ilv_Graphics_Filtgraph_H */
