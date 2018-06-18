// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/scale.h
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
// Declaration of the IlvScale class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Scale_H
#define __Ilv_Graphics_Scale_H

#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif

#define IlvScaleTextOffset 4
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScale : public IlvSimpleGraphic
{
public:
    IlvScale(IlvDisplay*	display,
	     const IlvRect&	drawrect,
	     const char*	format		=   0,
	     IlFloat		min		=   0,
	     IlFloat		max		= 100,
	     IlUShort		steps		=   0,
	     IlUShort		substeps	=   0,
	     IlUShort		stepsize	=  10,
	     IlUShort		substepsize	=   5,
	     IlvPalette*	palette		=   0);
    IlvScale(IlvDisplay*	display,
	     const IlvRect&	drawrect,
	     char*		labels[],
	     IlUShort		steps		=  2,
	     IlUShort		substeps	=  0,
	     IlUShort		stepsize	= 10,
	     IlUShort		substepsize	=  5,
	     IlvPalette*	palette		=  0);
    ~IlvScale();

    void		setSteps(IlUShort steps);
    inline IlUShort	getSteps() const { return _steps; }
    inline IlUShort	getSubSteps() const { return _substeps; }
    inline void		setSubSteps(IlUShort substeps) 
			{
			    _substeps = substeps;
			}
    inline IlUShort	getStepSize() const { return _stepsize; }
    inline void		setStepSize(IlUShort stepsize) 
			{
			    _stepsize = stepsize;
			}
    inline IlUShort	getSubStepSize() const { return _substepsize; }
    inline void		setSubStepSize(IlUShort substepsize)
			{
			    _substepsize = substepsize;
			}
    inline IlFloat	getMin() const { return _min; }
    void		setMin(IlFloat min);
    inline IlFloat	getMax() const { return _max; }
    void		setMax(IlFloat max);
    inline const char*	getFormat() const { return(_format); }
    void		setFormat(const char* format);
    inline char* const*	getLabels() const { return _labels; }
    inline const char*	getLabel(IlUShort idx) const
			{
			    return _labels ? _labels[idx] : 0;
			}
    void		getLabelSizes(IlUShort idx,
				      IlvDim&  w,
				      IlvDim&  h,
				      IlvDim&  d) const;
    void		setLabels(IlUShort		count,
				  const char* const*	labels = 0);
    void		setLabel(IlUShort idx, const char* label);
    void		setLabels(IlUShort	count,
				  IlFloat	min,
				  IlFloat	max,
				  const char*	format);
    inline void		setModified(IlBoolean modified)
			{
			    _modified = modified;
			}
    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const = 0;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const = 0;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	setFont(IlvFont*);
    virtual void	setPalette(IlvPalette*);
    inline IlBoolean	usedRange() const { return _usedRange; }
    inline void		useRange(IlBoolean v) { _usedRange = v; }

    DeclareGraphicAccessors();

    static IlSymbol*	_stepsValue;
    static IlSymbol*	_subStepsValue;
    static IlSymbol*	_stepSizeValue;
    static IlSymbol*	_subStepSizeValue;
    static IlSymbol*	_minValue;
    static IlSymbol*	_maxValue;
    static IlSymbol*	_formatValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvScale);

protected:
    IlvRect		_drawrect;
    IlUShort		_steps;
    IlUShort		_substeps;
    IlUShort		_stepsize;
    IlUShort		_substepsize;
    char**		_labels;
    IlvDim*		_labelWs;
    IlvDim*		_labelHs;
    IlvDim*		_labelDs;
    IlBoolean		_modified;
    IlFloat		_min;
    IlFloat		_max;
    char*		_format;
    IlBoolean		_usedRange;

    virtual void	computeLabels(IlFloat, IlFloat, const char*);
    virtual void	computeLabelSizes();
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvRectangularScale : public IlvScale
{
public:
    IlvRectangularScale(IlvDisplay*	display,
			const IlvPoint&	orig,
			IlvDim		size,
			const char*	format,
			IlFloat		min,
			IlFloat		max,
			IlvDirection	direction	= IlvVertical,
			IlvPosition	position	= IlvLeft,
			IlUShort	steps		=  0,
			IlUShort	substeps	=  0,
			IlUShort	stepsize	= 10,
			IlUShort	substepsize	=  5,
			IlvPalette*	palette		=  0);
    IlvRectangularScale(IlvDisplay*	display,
			const IlvPoint&	orig,
			IlvDim		size,
			char*		labels[],
			IlvDirection	direction	= IlvVertical,
			IlvPosition	position	= IlvLeft,
			IlUShort	steps		=  2,
			IlUShort	substeps	=  0,
			IlUShort	stepsize	= 10,
			IlUShort	substepsize	=  5,
			IlvPalette*	palette		=  0);

    void		getOrigin(IlvPoint& p) const;
    void		setOrigin(const IlvPoint& origin);
    IlvDim		getSize() const;
    void		setSize(IlvDim size);
    inline IlvDirection	getDirection() const { return _direction; }
    void		setDirection(IlvDirection direction);
    inline IlvPosition	getPosition() const { return _position; }
    void		setPosition(IlvPosition position);
    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawBaseLine(IlvPort*		   dst,
				     const IlvTransformer* t    = 0,
				     const IlvRegion*	   clip = 0) const;
    virtual void	drawLabel(IlvPort*		dst, 
				  IlUShort		idx,
				  const IlvPoint&	orig,
				  const IlvFloatPoint&	offset,
				  const IlvPoint&	tickoffset,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	drawLabels(IlvPort*		 dst,
				   const IlvTransformer* t    = 0,
				   const IlvRegion*	 clip = 0) const;
    virtual void	drawTick(IlvPort*		dst,
				 IlUShort		idx,
				 const IlvPoint&	orig,
				 const IlvFloatPoint&	offset,
				 const IlvFloatPoint&	suboffset,
				 const IlvPoint&	tickoffset,
				 const IlvPoint&	subtickoffset,
				 const IlvTransformer*	t    = 0,
				 const IlvRegion*	clip = 0) const;
    virtual void	drawTicks(IlvPort*		dst,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual void	labelBBox(IlvRect&		rect,
				  IlUShort		idx,
				  const IlvPoint&	orig,
				  const IlvFloatPoint&	offset,
				  const IlvPoint&	tickoffset,
				  const IlvTransformer*	t = 0) const;
    virtual void	labelsBBox(IlvRect&		 rect,
				   const IlvFloatPoint&	 offset,
				   const IlvPoint&	 tickoffset,
				   const IlvTransformer* t = 0) const;
    virtual void	ticksBBox(IlvRect&		rect,
				  const IlvFloatPoint&	offset,
				  const IlvPoint&	tickoffset,
				  const IlvTransformer*	t = 0) const;
    IlBoolean		liesIn(IlvPort*		dst,
			       const IlvPoint&	p,
			       const IlvRegion*	clip = 0) const;
    virtual IlUShort	getNumberOfSkippedSteps(const IlvPoint& orig,
						IlvDim size,
						IlUShort steps,
						const IlvFloatPoint& offset,
						const IlvPoint& tickoffset,
						const IlvTransformer* t = 0)
						const;
    inline IlBoolean	isStepSizeFixed() const { return _isStepSizeFixed; }
    inline void		setStepSizeFixed(IlBoolean flag)
			{
			    _isStepSizeFixed = flag;
			    _modified = IlTrue;
			}
    inline IlBoolean	hasVerticalLabels() const
			{
			    return _hasVerticalLabels;
			}
    inline void		useVerticalLabels(IlBoolean flag)
			{
			    _hasVerticalLabels = flag;
			    _modified = IlTrue;
			}
    inline IlBoolean	areLabelsCentered() const
			{
			    return _areLabelsCentered;
			}
    inline void		centerLabels(IlBoolean flag)
			{
			    _areLabelsCentered = flag;
			    _modified = IlTrue;
			}
    inline IlBoolean	doesDrawOverlappingLabels() const
			{
			    return _doesDrawOverlappingLabels;
			}
    inline void		drawOverlappingLabels(IlBoolean val)
			{
			    _doesDrawOverlappingLabels = val;
			    _modified = IlTrue;
			}
    virtual void	applyTransform(const IlvTransformer* t);

    DeclareGraphicAccessors();

    static IlSymbol*	_originXValue;
    static IlSymbol*	_originYValue;
    static IlSymbol*	_sizeValue;
    static IlSymbol*	_directionValue;
    static IlSymbol*	_positionValue;
    static IlSymbol*	_stepSizeFixedValue;
    static IlSymbol*	_verticalLabelsValue;
    static IlSymbol*	_centerLabelsValue;
    static IlSymbol*	_drawOverlappingLabelsValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvRectangularScale);

protected:
    IlvDirection	_direction; // Scale orientation
    IlvPosition		_position;  // Text position relative to Scale
    IlUShort		_skippedSteps;
    IlBoolean		_isStepSizeFixed;
    IlBoolean		_hasVerticalLabels;
    IlBoolean		_areLabelsCentered;
    IlBoolean		_doesDrawOverlappingLabels;

    void		computeRect(const IlvPoint& orig, IlvDim size);
    IlvDim		computeSize(IlvPoint& orig) const;
};

ILVVWSMODULEINIT(g0scale);
#endif /* !__Ilv_Graphics_Scale_H */
