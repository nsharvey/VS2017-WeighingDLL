// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/gui/scale.h
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
// Rogue Wave Views - Maps add-on.
// Declaration of the IlvMapScale class
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __IlvMapsScaleBar_H__
#define __IlvMapsScaleBar_H__

#include <ilviews/manager/manager.h>
#include <ilviews/base/view.h>
#include <ilviews/maps/unitconv.h>

ILVMAPSMODULEINIT(mapscale);
ILVMAPSMODULEINIT(mapdefaultscalebar);

class _IlvScaleInternalHook;


enum IlvMapDefaultScaleBarStyle {
    IlvMapScaleBarEmpty,
    IlvMapScaleBarOdd,
    IlvMapScaleBarEven,
    IlvMapScaleBarDoubleEmpty,
    IlvMapScaleBarDoubleOdd,
    IlvMapScaleBarDoubleEven,
    IlvMapScaleBarBottomLine,
    IlvMapScaleBarCenterLine
};

class ILVMAPSEXPORTED IlvMapDefaultScaleBar : public IlvSimpleGraphic
{
public:
    IlvMapDefaultScaleBar(IlvDisplay* display,
		   const IlvRect& rect,
		   IlUInt divs,
		   IlvMapDefaultScaleBarStyle style,
		   IlvColor* altColor = 0,
		   IlvPalette* palette = 0);

    virtual ~IlvMapDefaultScaleBar();

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    virtual void	boundingBox(IlvRect& r,
				    const IlvTransformer* t) const;

    virtual void	applyTransform(const IlvTransformer* t);

    void		setStyle(IlvMapDefaultScaleBarStyle style);

    IlvMapDefaultScaleBarStyle getStyle() { return _style; }

    void		setAlternateColor(IlvColor* color);

    const IlvColor*	getAlternateColor() { return _alt; }

    inline void		setDivisions(IlInt divs) { _divs = divs; }

    inline IlInt	getDivisions() { return _divs; }

    DeclareTypeInfo();
    DeclareIOConstructors(IlvMapDefaultScaleBar);

private:
    void		drawRect(IlvPort* dst, IlvRect& r) const;
    void		fillRect(IlvPort* dst, IlvRect&) const;

    IlvRect			_box;
    IlvMapDefaultScaleBarStyle	_style;
    IlInt			_divs;
    IlvColor*			_alt;
};


enum IlvMapScaleTextMode {
    IlvMapScaleUniqueLabel,
    IlvMapScaleThreeLabels
};

class ILVMAPSEXPORTED IlvMapScale : public IlvSimpleGraphic
{
  friend class _IlvScaleInternalHook;

public:
    IlvMapScale(IlvDisplay* display,
	      const IlvRect& rect,
	      IlvMapScaleTextMode mode = IlvMapScaleThreeLabels,
	      IlvGraphic* bar = 0,
	      IlvDim margin = 5,
	      IlvPalette* palette = 0);

    virtual ~IlvMapScale();

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    void		setView(IlvView* view);

    virtual void	applyTransform(const IlvTransformer *);
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    virtual void	apply(IlvApplyObject f, IlAny arg);

    void		setScaleTextMode(IlvMapScaleTextMode mode);

    IlvMapScaleTextMode getScaleTextMode() { return _textMode; }

    const IlvGraphic*	getGraphic() { return _scaleBar; }

    void		setGraphic(IlvGraphic* graphic);

    void		setNearUnitConverter(IlvUnitConverter* nearConv);

    const IlvUnitConverter* getNearUnitConverter() const 
			{
			    return _nearUnitConverter;
			}

    void		setFarUnitConverter(IlvUnitConverter* farConv);

    const IlvUnitConverter* getFarUnitConverter() const
			{
			    return _farUnitConverter;
			}

    void		setFarLimit(IlDouble limit);

    IlDouble		getFarLimit() { return _farLimit; }

    void		setSpacing(IlvDim spacing);

    IlvDim		getSpacing() { return _spacing; }

    void		setMargin(IlvDim margin);

    IlvDim		getMargin() { return _margin; }

private:
    void		computeExtent();
    void		computeExtent(IlvDim);
    IlvDim		drawUpperText(IlvPort*,
				      IlvPoint& center,
				      IlvDim offset) const;
    IlvDim		drawScaleText(IlvPort*,
				      IlvPoint& center,
				      IlvDim offset) const;
    IlvDim		drawScaleBar(IlvPort*,
				     IlvPoint& center,
				     const IlvTransformer*,
				     const IlvRegion* clip,
				     IlvDim offset) const;
    IlvDim		usableWidth(IlvRect& r) const;
    void		redraw();
    void		drawRect(IlvPort*, IlvRect&);
    void		fillRect(IlvPort*, IlvRect&);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvMapScale);

protected:
    IlvView*		_view;
    IlvManager*		_manager;
    _IlvScaleInternalHook* _hook;
    IlvRect		_box;
    IlvGraphic*		_scaleBar;
    IlvUnitConverter*	 _nearUnitConverter;
    IlvUnitConverter*	_farUnitConverter;
    IlvUnitConverter*	_currentUnitConverter;
    IlDouble		_farLimit;
    IlDouble		_currentScaleLength;
    const char*		_unitString;
    IlDouble		_pixelFactor;
    IlvMapScaleTextMode _textMode;
    IlvDim		_margin;
    IlInt		_scaleDivs;
    IlvDim		_spacing;
};

#endif /* __IlvMapsScaleBar_H__ */
