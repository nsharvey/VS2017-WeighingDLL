// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/scaledis.h
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
// Declaration of the classes that allow to display the scales.
// The scales are displayed by the mean of "scale displayers".
// Contains:
//  - IlvAbstractScaleDisplayer: the root class.
//  - IlvSingleScaleDisplayer: a subclass of IlvAbstractScaleDisplayer
//    which allows you to display a standard scale.
//  - IlvMultiScaleDisplayer: a subclass of IlvAbstractScaleDisplayer
//    which allows you to display a multi-scale which is composed of several
//    single scales.
//  - IlvRectangularScaleDisplayer: a subclass of IlvSingleScaleDisplayer
//    which allows you to display a rectangular scale.
//  - IlvCircularScaleDisplayer: a subclass of IlvSingleScaleDisplayer
//    which allows you to display a circular scale.
//  - IlvScaleStepsUpdater: the base class that allows you to compute the 
//    steps and substeps for a scale.
//  - IlvConstantScaleStepsUpdater: a subclass of IlvScaleStepsUpdater
//    which allows you to compute steps and substeps with a constant spacing.
//  - IlvAutoScaleStepsUpdater: a subclass of IlvConstantScaleStepsUpdater
//    that performs an automatic computation of the steps and the substeps.
//  - IlvLogScaleStepsUpdater: a subclass of IlvScaleStepsUpdater that 
//    computes logarithmic graduations.
//  - IlvZoomScaleScaleStepsUpdater: a subclass of IlvScaleStepsUpdater
//    which allows you to display graduations that are zoomed locally on a
//    part of the scale, whereas the graduations are displayed normally
//    on the rest of the scale.
//  - IlvZoomCoordinateTransformer: a subclass of IlvCoordinateTransformer
//    which allows you to define a transformation that is applied locally on
//    a part of the data. This allows you to display this data as zoomed.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Scaledis_H
#define __Ilv_Charts_Scaledis_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Util_Proplist_h)
#include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Common_H)
#include <ilviews/charts/common.h>
#endif


class IlvCircularScaleDisplayer;
class IlvAbstractChartCursor;
class IlvAxisElement;
class IlvScaleStepsUpdater;

// --------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------
#define IlvDefaultScaleMajorTickSize 4

#define IlvDefaultScaleMinorTickSize 2

#define IlvDefaultScaleOffset 4

#define IlvDefaultScaleArrowWidth 8

#define IlvDefaultScaleArrowLength 8

#define IlvDefaultStepLabelFormat "%g"

// --------------------------------------------------------------------------
// Callbacks type
// --------------------------------------------------------------------------
typedef char* (*IlvValueToLabelCB)(IlDouble, IlAny);

class ILVCHTEXPORTED IlvAbstractGridDisplayer;

// --------------------------------------------------------------------------
// IlvAbstractScaleDisplayer persistence
// --------------------------------------------------------------------------
class IlvAbstractScaleDisplayer;
typedef IlvAbstractScaleDisplayer* 
    (*IlvScaleDisplayerConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvScaleDisplayerClassInfo : public IlvValuedClassInfo
{
public:
    inline
    IlvScaleDisplayerClassInfo*	getScaleDisplayerSuperClass() const
			{
			    return ILVDYNAMICCAST(IlvScaleDisplayerClassInfo*,
						  getSuperClass());
			}
    inline
    IlvScaleDisplayerConstructor getConstructor() const
			{
			    return _constructor;
			}
    static IlvScaleDisplayerClassInfo* Create(const char*,
					      IlvClassInfo**,
					      IlvScaleDisplayerConstructor);

protected:
    IlvScaleDisplayerClassInfo(const char*    className,
			       IlvClassInfo** superClass,
			       IlvScaleDisplayerConstructor c)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(c) {}
    IlvScaleDisplayerConstructor     _constructor;
};


#define IlvRegisterScaleDisplayerClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
		  IlvScaleDisplayerClassInfo::Create(#classname,	\
			    ILVSUPERCLASSINFO(superclass),		\
			    (IlvScaleDisplayerConstructor)		\
			    classname::Read))
#define IlvPreRegisterScaleDisplayerClass(classname)			\
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterScaleDisplayerClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
		IlvScaleDisplayerClassInfo::Create(#classname,		\
			   ILVSUPERCLASSINFO(superclass),		\
			   (IlvScaleDisplayerConstructor)		\
			   classname::Read))

//== Compat
#define IlvRegisterAbstractScaleDisplayerClass(classname, superclass)	    \
IlvRegisterScaleDisplayerClass(classname, superclass)
#define IlvPreRegisterAbstractScaleDisplayerClass(classname)		    \
IlvPreRegisterScaleDisplayerClass(classname)
#define IlvPostRegisterAbstractScaleDisplayerClass(classname, superclass)   \
IlvPostRegisterScaleDisplayerClass(classname, superclass)

// --------------------------------------------------------------------------
// Class IlvAbstractScaleDisplayer
// --------------------------------------------------------------------------
//- Flags
// --------------------------------------------------------------------------
#define IlvCHTScale40FileFormat  0x00000001
#define IlvCHTScale40TextLabels  0x00000002
#define IlvCHTScale50FileFormat  0x00000004

// --------------------------------------------------------------------------
class IlvConstantScaleStepsUpdater;
class ILVCHTEXPORTED IlvSingleScaleDisplayer;
class ILVCHTEXPORTED IlvAbstractScaleDisplayer : public IlvValueInterface
{
public:    
    friend class IlvAxisElement;
    friend class IlvAbscissaAxisElement;

    typedef IlvProjectorArea DataArea;

    enum StepMode {
	OtherMode		    = 0x0000,
	AutomaticMode		    = 0x0001,
	StepNumberMode		    = 0x0002,
	StepUnitMode		    = 0x0004,
	StepLabelsMode		    = 0x0008,
	TextLabelsMode		    = StepLabelsMode
    };

    enum TickLayout {
	TickInside  = 0x0001,
	TickOutside = 0x0002,
	TickCross   = 0x0003
    };

     enum LabelLayout {
	 LabelInside  = 0x0001,
	 LabelOutside = 0x0002	
    };

    virtual ~IlvAbstractScaleDisplayer();

    //== Coordinate information
    virtual IlBoolean	isOnAbscissa() const = 0;

    virtual IlBoolean	isOnOrdinate() const = 0;

    virtual
    IlvCoordinateType	getCoordinateType() const = 0;

    virtual
    IlvCoordinateInfo*	getCoordinateInfo(IlUInt index = 0) const = 0;

    //== Misc
    inline const char*	getName() const 
			{
			    return _name.isEmpty()
				? (const char*) 0
				: (const char*)_name;
			}

    inline void		setName(const char* name) { _name = name; }

    //== Positioning ========
    inline IlBoolean	isFixedToPosition() const 
			{
			    return _positioning._fixedToPosition;
			}

    virtual void	setRelativePosition(IlvAxisPosition relPos,
					    IlvPos offset = 0);

    virtual IlBoolean	setCrossingValue(IlDouble dataValue,
					 const IlvSingleScaleDisplayer* ref);

    // This method can be used only if _infoForCrossingValue is defined.
    virtual IlBoolean	setCrossingValue(IlDouble dataValue);

    inline IlBoolean	getRelativePosition(IlvAxisPosition& relPos,
					    IlvPos& offset) const
			{
			    if (_positioning._fixedToPosition) {
				relPos = _positioning._relativePosition;
				offset = _positioning._relativeOffset;
				return IlTrue;
			    }
			    else return IlFalse;
			}

#if DOCUMENTED_LATER
#endif
    IlBoolean		getGlobalPosition(const IlvRect& dataArea,
					  IlvPos& globalPosition) const;

    inline IlBoolean	getCrossingValue(IlDouble& dataValue) const
			{
			    return _positioning.getCrossingValue(dataValue);
			}

    inline IlDouble	getStoredCrossingValue() const 
			{
			    return _positioning._crossingValue;
			}

    inline
    IlvCoordinateInfo*	getInfoForCrossingValue() const
			{
			    return _positioning._infoForCrossingValue;
			}

    inline IlBoolean	isAlwaysVisible() const
			{
			    return _positioning._alwaysVisible;
			}

    virtual void	setAlwaysVisible(IlBoolean b);

    IlvDrawOrder	getDrawOrder() const { return _drawOrder; }

    virtual void	setDrawOrder(IlvDrawOrder drawOrder);

    virtual void	setGridDrawOrder(IlvDrawOrder drawOrder) = 0;

    //== Steps, subSteps definition    
    //== Obsolete. Now handled by the IlvScaleStepsUpdater class.
    virtual void	fixStepsCount(IlUInt stepsCount,
				      IlUInt subStepsCount) = 0;
    virtual void	fixStepUnit(IlDouble stepUnit,
				    IlDouble subStepUnit) = 0;
    void		fixDeltaStep(IlDouble deltaStep,
				     IlDouble deltaSubStep) 
			{
			    fixStepUnit(deltaStep, deltaSubStep);
			}
    virtual void	setAutoStepsCount(IlBoolean	b,
					  IlvDim	stepsSpacing  = 10,
					  IlUInt	subStepsCount = 0) = 0;

    //== Layout ============
    virtual void	setLabelLayout(LabelLayout layout) = 0;

    virtual void	setTickLayout(TickLayout layout) = 0;

    virtual void	setMajorTickSize(IlvDim size) = 0;

    // Obsolete.
    // Keep for compatibility.
    inline void		setStepSize(IlvDim size) { setMajorTickSize(size); }

    virtual void	setMinorTickSize(IlvDim size) = 0;

    // Obsolete.
    // Keep for compatibility.
    inline void		setSubStepSize(IlvDim size) { setMinorTickSize(size); }

    virtual void	setOffset(IlvDim dim) = 0;

    virtual void	setStepLabelAngle(IlDouble angle) = 0;

    virtual void	setAxisOriented(IlBoolean oriented) = 0;

    virtual void	setArrowWidth(IlvDim width) = 0;

    virtual void	setArrowLength(IlvDim length) = 0;

    virtual void	drawLabelOnCrossings(IlBoolean b) = 0;

    virtual void	drawOverlappingLabels(IlBoolean b) = 0;

    virtual void	setAxisLabelOffset(IlvDim offset) = 0;

    //== Labels
    virtual void	setStepLabelFormat(const char* format,
					   IlBoolean invalidate = IlTrue) = 0;

    virtual void	setValueToLabelCB(IlvValueToLabelCB cb,
					  IlAny cbData = 0) = 0;

    virtual void	setStepLabels(IlUInt count,
				      const char* const* labels = 0) = 0;

    virtual void	setStepLabel(IlUInt labelIndex,
				     const char* label) = 0;

    virtual void	setLabelZoomFactor(IlDouble scale) = 0;

    //== Palettes
    virtual void	setStepLabelsPalette(IlvPalette* pal) = 0;

    virtual void	setAxisPalette(IlvPalette* pal) = 0;

    virtual void	setAxisLabelPalette(IlvPalette* pal) = 0;

    //== Visibility ==============
    inline IlBoolean	isVisible() const 
			{
			    return (_visibilityMask & Visible)
				? IlTrue
				: IlFalse;
			}

    inline void		setVisible(IlBoolean visible)
			{
			    if (visible) 
				_visibilityMask |= Visible;
			    else
				_visibilityMask &= ~Visible;
			}

    //== Updating =============

#if DOCUMENTED_LATER
#endif
    virtual IlBoolean	layoutToUpdate() const;    

    virtual void	setCoordinateType(IlvCoordinateType type) = 0;
    virtual IlBoolean	setCoordinateInfo(IlvCoordinateInfo* coordInfo,
					  IlUInt index = 0) = 0;
    void		setInfoForCrossingValue(IlvCoordinateInfo* coordInfo);

    inline void		invalidateLayout() { _layoutModified = IlTrue; }
    inline IlBoolean	isLayoutModified() const { return _layoutModified; } 
    virtual void	setLayoutModified(IlBoolean flag);

    virtual void	setProjector(const IlvAbstractProjector* prj);
    const IlvAbstractProjector* getProjector() const { return _projector; }


    // API
    void		setCrossingPoints(IlUInt count, const IlvPoint* pts);
    inline
    const IlvPoint*	getCrossingPoints(IlUInt& count) const
			{
			    count = _crossingCount;
			    return _crossingPoints;
			}

    virtual IlBoolean	isDrawingNeeded(IlvDrawOrder order);
#if DOCUMENTED_LATER
#endif
    virtual void	draw(const IlvProjectorArea& scaleArea,
			     IlvDrawOrder	      drawOrder,
			     IlvPort*		      dst,
			     const IlvTransformer*   t = 0,
			     const IlvRegion*	      clip = 0) const = 0;
#if DOCUMENTED_LATER
#endif
    virtual IlBoolean	boundingBox(const IlvProjectorArea& scaleArea,
				    IlvRect& bbox,
				    const IlvTransformer* t = 0) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual void	update(const IlvProjectorArea& dataArea) = 0;

    inline IlBoolean	isInVisibleDataArea() const
			{
			    return _positioning.isInVisibleRange();
			}


    // Assignment.
    IlvAbstractScaleDisplayer& operator=(const IlvAbstractScaleDisplayer&);

    // Drawing modes.
    virtual void	setOverwrite(IlBoolean o) = 0;
    virtual void	setMode(IlvDrawMode mode) = 0;

    virtual IlvAbstractScaleDisplayer* copy() const = 0;

    //== Persistence ========
    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvAbstractScaleDisplayer* Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    inline void		invalidateSteps() { _stepsValid = IlFalse; }

    IlUInt		getFlags() const { return _flags; }
    void		setFlags(IlUInt flags) { _flags = flags; }

    static
    const IlSymbol*	NPSymbol();

    IlvDeclarePropertyListOwnerWithNotify(NPSymbol());
    IlvDeclarePropRootClassInfo();

    void		copyProperties(const IlvAbstractScaleDisplayer&);

public: // Due to a bug in some compilers, the structure must be public
    struct ILVCHTEXPORTED Positioning
    {
	Positioning();
	Positioning(const Positioning&);
	~Positioning();

	Positioning& operator=(const Positioning&);
	void		read(IlvInputFile& file);
	void		write(IlvOutputFile& file) const;
	void		setInfo(IlvCoordinateInfo*);
	IlBoolean	isInVisibleRange() const;
	void		update();

	void		setRelativePosition(IlvAxisPosition, IlvPos);
	IlBoolean	setCrossingValue(IlDouble value);
	IlBoolean	getCrossingValue(IlDouble& dataValue,
					 IlBoolean applyT = IlFalse) const;

	IlBoolean			_fixedToPosition;
	IlvAxisPosition			_relativePosition;
	IlvPos				_relativeOffset;
	IlDouble			_crossingValue;
	IlvCoordinateInfo*		_infoForCrossingValue;
	IlBoolean			_alwaysVisible;
    };

protected:
    //== Class constants
    enum {
	Visible		  = 0x0001,
	EverythingVisible = 0xffff
    };

    //== General information
    IlString			_name;
    IlUInt			_flags;

    //== Positioning
    Positioning			_positioning;

    //== DrawOrder
    IlvDrawOrder		_drawOrder;    

    //== Visibility
    int				_visibilityMask;

    //== Internal use
    IlBoolean			_layoutModified;
    IlBoolean			_stepsValid;

    //== Projector
    const IlvAbstractProjector* _projector;

    //== Crossing points
    IlUInt			_crossingCount;
    IlvPoint*			_crossingPoints;

    IlvAxisElement*		_axisElement;

    // Constructors
    IlvAbstractScaleDisplayer();

    IlvAbstractScaleDisplayer(const IlvAbstractScaleDisplayer& scaleDisplayer);

    IlvAbstractScaleDisplayer(IlvInputFile& file);

    virtual void	readCompat(IlvInputFile& file);

    virtual void	setAxisElement(IlvAxisElement *el);
    virtual
    IlvAxisElement*	getAxisElement() const;

};

class IlvAxisElement;

// --------------------------------------------------------------------------
// Class IlvSingleScaleDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvSingleScaleDisplayer : public IlvAbstractScaleDisplayer
{
    friend class IlvAbstractChartCursor;
    friend class IlvScaleStepsUpdater;
    friend class IlvConstantScaleStepsUpdater;

protected:
    //== Class constants
    enum {
	MajorTicksVisible = 0x0010,
	MinorTicksVisible = 0x0020,
	StepLabelsVisible = 0x0040,
	AxisVisible	  = 0x0080	
    };

    enum {
	DrawMajor	= 0x0001,
	DrawMinor	= 0x0002,
	DrawTick	= 0x0004,
	DrawGrid	= 0x0008
    };

public:

    virtual ~IlvSingleScaleDisplayer();

    //== Coordinate
    virtual IlBoolean	isOnAbscissa() const;
    virtual IlBoolean	isOnOrdinate() const;
    virtual
    IlvCoordinateType	getCoordinateType() const;

    virtual
    IlvCoordinateInfo*	getCoordinateInfo(IlUInt index = 0) const;

    //== First and last steps positioning
    //== Kept for compatibility. See IlvConstantScaleStepsUpdater.
    virtual void	setFirstStepData(IlDouble dataValue);
    IlDouble		getFirstStepData() const;
    IlBoolean		isFirstStepDataDefined() const;
    void		unsetFirstStepData(); 
    virtual void	setLastStepData(IlDouble dataValue);
    IlDouble		getLastStepData() const;
    IlBoolean		isLastStepDataDefined() const;
    void		unsetLastStepData();

    virtual void	setGridDrawOrder(IlvDrawOrder drawOrder);

    //== Steps, subSteps
    IlUInt		getStepsCount() const;

    IlUInt		getSubStepsCount() const;

    IlUInt		getTotalSubStepsCount() const;

    inline
    IlvConstantScaleStepsUpdater* getConstantStepsUpdater() const
			{
			    return _constStepsUpdater;
			}

    IlvScaleStepsUpdater* getStepsUpdater() const;

    virtual void	fixStepsCount(IlUInt stepsCount, IlUInt subStepsCount);

    IlDouble		getStepUnit() const;

    IlDouble		getSubStepUnit() const;


    // Compat
    inline IlDouble	getDeltaStep()    const { return getStepUnit(); }
    inline IlDouble	getDeltaSubStep() const { return getSubStepUnit(); }

    virtual void	fixStepUnit(IlDouble stepUnit,IlDouble subStepUnit);

    StepMode		getStepMode() const;
    inline IlBoolean	isStepUnitSpecified() const
			{
			    return (getStepMode() == StepUnitMode); 
			}
    inline IlBoolean	isUsingTextLabels() const
			{
			    return (_flags & IlvCHTScale40TextLabels)
				? IlTrue
				: IlFalse;
			}
    inline void		useTextLabels(IlBoolean b)
			{
			    if (b)
				_flags |= IlvCHTScale40TextLabels;
			    else
				_flags &= ~IlvCHTScale40TextLabels;
			}

    virtual IlBoolean	coordRangeChanged(const IlvCoordInterval& oldRange);
    virtual void	coordTransformerChanged(const IlvCoordinateTransformer* oldT);

    IlBoolean		checkRange(IlvCoordInterval& range) const;

    void		getStepSubStepValues(IlUInt& stepsCount,
					     const IlDouble*& stepValues,
					     const char* const*& stepLabels,
					     IlUInt& subStepsCount,
					     const IlDouble*& subStepValues) const;

    inline
    const IlDouble*	getStepValues(IlUInt& count) const 
			{
			    count = getStepsCount();
			    return _stepValues;
			}

    inline
    const IlDouble*	getSubStepValues(IlUInt& count) const 
			{
			    count = getTotalSubStepsCount();
			    return _subStepValues;
			}

    IlDouble		getStepValue(IlUInt iStep) const;

    IlDouble		getSubStepValue(IlUInt iSubStep) const;

    IlDouble		getSubStepValue(IlUInt iStep, IlUInt iSubStep) const;

    virtual void	setAutoStepsCount(IlBoolean	b,
					  IlvDim	stepsSpacing  = 10,
					  IlUInt	subStepsCount = 0);

    //== Used for automatic step computation.
    virtual IlUInt	getMaxStepsCount(const IlvProjectorArea&,
					 IlvDim stepsSpacing) const = 0;

    //== Layout ============

    inline LabelLayout	getLabelLayout() const {return _labelLayout;}
    virtual void	setLabelLayout(LabelLayout layout);

    inline TickLayout	getTickLayout() const {return _tickLayout;}
    virtual void	setTickLayout(TickLayout layout);

    inline IlvDim	getMajorTickSize() const { return _majorTickSize; }

    // Obsolete.
    // Keep for compatibility.
    inline IlvDim	getStepSize() const { return getMajorTickSize(); }

    virtual void	setMajorTickSize( IlvDim val );

    inline IlvDim	getMinorTickSize() const { return _minorTickSize; }

    // Obsolete.
    // Keep for compatibility.
    inline IlvDim	getSubStepSize() const { return getMinorTickSize(); }

    virtual void	setMinorTickSize(IlvDim val);

    inline IlvDim	getOffset() const { return _offset; }

    virtual void	setOffset(IlvDim dim);

    inline IlDouble	getStepLabelAngle() const { return _stepLabelAngle; }

    virtual void	setStepLabelAngle(IlDouble angle);

    inline IlBoolean	isAxisOriented() const { return _axisOriented; }

    virtual void	setAxisOriented(IlBoolean o);

    inline IlvDim	getArrowWidth() const { return _arrowWidth; }

    virtual void	setArrowWidth(IlvDim width);

    inline IlvDim	getArrowLength() const { return _arrowLength; }

    virtual void	setArrowLength(IlvDim length);

    inline IlBoolean	isDrawingLabelOnCrossings() const
			{
			    return _drawLabelOnCrossings;
			}

    virtual void	drawLabelOnCrossings(IlBoolean b);

    inline IlBoolean	isDrawingOverlappingLabels() const
			{
			    return _drawOverlappingLabels;
			}

    virtual void	drawOverlappingLabels(IlBoolean b);

    inline IlvDim	getAxisLabelOffset() const { return _axisLabelOffset; }

    virtual void	setAxisLabelOffset(IlvDim offset);

    //== Labels ========

    inline const char*	getStepLabelFormat() const 
			{
			    return _stepLabelFormat.isEmpty()
				? (const char*)0
				: (const char*)_stepLabelFormat;
			}

    virtual void	setStepLabelFormat(const char* format, 
					   IlBoolean invalidate = IlTrue);

    inline
    IlvValueToLabelCB	getValueToLabelCB() const { return  _valueToLabelCB; }

    inline IlAny	getValueToLabelCBData() const
			{
			    return _valueToLabelCBData;
			}

    virtual void	setValueToLabelCB(IlvValueToLabelCB cb,
					  IlAny cbData = 0);

    inline
    const char* const*	getStepLabels(IlUInt& labelsCount) const
			{
			    labelsCount = _stepLabelsCount;
			    return IL_CONSTCAST(const char* const*,
						_stepLabels);
			}

    inline IlUInt	getStepLabelsCount() const { return _stepLabelsCount; }

    virtual void	setStepLabels(IlUInt count, 
				      const char* const* labels = 0);

    inline const char*	getStepLabel(IlUInt iStep) const
			{
			    return _stepLabels[iStep];
			}

    virtual void	setStepLabel(IlUInt labelIndex, const char* label);

    void		getStepLabelSizes(IlUInt iStep, 
					  IlvDim& width, 
					  IlvDim& height, 
					  IlvDim& descent) const;

#if DOCUMENTED_LATER
#endif
    inline IlvDim	getMaxStepLabelWidth() const
			{
			    return _maxStepLabelWidth;
			}
#if DOCUMENTED_LATER
#endif
    inline IlvDim	getMaxStepLabelHeight() const
			{
			    return _maxStepLabelHeight;
			}

#if DOCUMENTED_LATER
#endif
    inline IlvDim	getMaxStepLabelDescent() const
			{
			    return _maxStepLabelDescent;
			}

    virtual char*	computeStepLabel(IlDouble value) const;

    char*		translateToLabel(IlDouble value) const;

    inline void		setAxisLabel(const char* label) { _axisLabel = label; }

    inline const char*	getAxisLabel() const 
			{
			    return _axisLabel.isEmpty()
				? (const char*)0
				: (const char*)_axisLabel;
			}

    void		getAxisLabelSizes(IlvDim& width,
					  IlvDim& height,
					  IlvDim& descent) const;

    //== Visibility ========
    inline IlBoolean	isAxisVisible() const
			{
			    return (_visibilityMask & AxisVisible)
				? IlTrue
				: IlFalse;
			}

    inline void		setAxisVisible(IlBoolean visible) 
			{
			    if (visible)
				_visibilityMask |= AxisVisible; 
			    else
				_visibilityMask &= ~AxisVisible; 
			}

    inline IlBoolean	areMajorTicksVisible() const 
			{
			    return (_visibilityMask & MajorTicksVisible)
				? IlTrue
				: IlFalse;
			}

    // Obsolete.
    // Keep for compatibility.
    inline IlBoolean	areStepsVisible() const
			{
			    return areMajorTicksVisible();
			}

    inline void		setMajorTicksVisible(IlBoolean visible) 
			{
			    if (visible)
				_visibilityMask |= MajorTicksVisible; 
			    else
				_visibilityMask &= ~MajorTicksVisible; 
			}

    // Obsolete.
    // Keep for compatibility.
    inline void		setStepsVisible(IlBoolean visible)
			{
			    setMajorTicksVisible(visible);
			}

    inline IlBoolean	areStepLabelsVisible() const 
			{
			    return (_visibilityMask & StepLabelsVisible)
				? IlTrue
				: IlFalse;
			}

    inline void		setStepLabelsVisible(IlBoolean visible) 
			{
			    if (visible)
				_visibilityMask |= StepLabelsVisible; 
			    else
				_visibilityMask &= ~StepLabelsVisible; 
			}

    inline IlBoolean	areMinorTicksVisible() const 
			{
			    return (_visibilityMask & MinorTicksVisible)
				? IlTrue
				: IlFalse;
			}

    // Obsolete.
    // Keep for compatibility.
    inline IlBoolean	areSubStepsVisible() const
			{
			    return areMinorTicksVisible();
			}

    inline void		setMinorTicksVisible(IlBoolean visible) 
			{
			    if (visible)
				_visibilityMask |= MinorTicksVisible; 
			    else
				_visibilityMask &= ~MinorTicksVisible; 
			}

    // Obsolete.
    // Keep for compatibility.
    inline void		setSubStepsVisible(IlBoolean b)
			{
			    setMinorTicksVisible(b);
			}

    //== Palettes =========
    inline IlvPalette*	getStepLabelsPalette() const
			{
			    return _stepLabelsPalette;
			}

    virtual void	setStepLabelsPalette(IlvPalette* pal);

    inline IlvPalette*	getAxisPalette() const { return _axisPalette; }

    virtual void	setAxisPalette(IlvPalette* pal);

    inline IlvPalette*	getAxisLabelPalette() const
			{
			    return _axisLabelPalette;
			}

    virtual void	setAxisLabelPalette(IlvPalette* pal);

    //== Associated Grid ==========
    IlvAbstractGridDisplayer* getGridDisplayer() const;

    void		setGridDisplayer(IlvAbstractGridDisplayer* grid);

    virtual
    IlvAbstractGridDisplayer* createGridDisplayer(const IlvSingleScaleDisplayer* scaleRef=0) const = 0;


    // Misc : Should not be directly used by the user.
    virtual void	setCoordinateType(IlvCoordinateType type);
    virtual IlBoolean	setCoordinateInfo(IlvCoordinateInfo* coordInfo,
					  IlUInt index = 0);

    virtual IlBoolean	isDrawingNeeded(IlvDrawOrder order);
    virtual void	draw(const IlvProjectorArea& scaleArea,
			     IlvDrawOrder drawOrder,
			     IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    virtual IlBoolean	boundingBox(const IlvProjectorArea& scaleArea,
				    IlvRect& bbox,
				    const IlvTransformer* t = 0) const;

    virtual void	update(const IlvProjectorArea& dataArea);

    inline
    const IlvProjectorArea& getScaleArea() const
			{
			    return _axisPoints._prjArea;
			}

    // Specific methods for points computing.
#if DOCUMENTED_LATER
#endif
    void		getMinPointOnAxis(const IlvProjectorArea& dataArea,
					  IlvPoint& minPoint) const;
#if DOCUMENTED_LATER
#endif
    void		getMaxPointOnAxis(const IlvProjectorArea& dataArea,
					  IlvPoint& minPoint) const;
#if DOCUMENTED_LATER
#endif
    void		getPointOnAxis(const IlvProjectorArea& dataArea,
				       IlDouble valueOnAxis,
				       IlvPoint& pointOnAxis) const;

    void		computePoints(const IlvProjectorArea& dataArea,
				      IlUInt& nbSteps,
				      IlvPoint*& stepPoints,
				      IlUInt& nbSubSteps,
				      IlvPoint*& subStepPoints,
				      IlvPoint& minPointOnAxis,
				      IlvPoint& maxPointOnAxis) const;

    void		computeAxisPoints(const IlvProjectorArea&) const;
    // Specific methods for drawing.
#if DOCUMENTED_LATER
#endif
    virtual void	drawAxis(const IlvProjectorArea& scaleArea,
				 IlvPort* dst,
				 const IlvRegion* clip = 0) const = 0;
#if DOCUMENTED_LATER
#endif
    virtual void	drawTicks(const IlvProjectorArea&  dataArea,
				  IlBoolean	   majorTicks,
				  IlUInt	   iMin,
				  IlUInt	   iMax,
				  IlvDrawOrder	   drawOrder,
				  IlvPort*	   dst,
				  const IlvRegion* clip) const;
#if DOCUMENTED_LATER
#endif
    virtual void	drawLabels(const IlvProjectorArea& dataArea,
				   IlvPort* dst,
				   const IlvRegion* clip) const;
#if DOCUMENTED_LATER
#endif
    virtual void	drawTick(IlUInt idx,
				 const IlvPoint& tickPoint,
				 IlDouble tickAngle,
				 IlvPos ticksOffset,
				 int drawMode,
				 IlvPort* dst,
				 const IlvRegion* clip = 0) const;
#if DOCUMENTED_LATER
#endif
    virtual void	drawLabel(const IlvPoint& tickPoint,
				  IlDouble tickAngle,
				  IlDouble labelAngle,
				  const char* label,
				  IlvDim labelWidth,
				  IlvDim labelHeight,
				  IlvDim labelDescent,
				  IlvPos offset,
				  IlvPalette* labelPalette,
				  IlvPort* dst,
				  const IlvRegion* clip = 0) const;
#if DOCUMENTED_LATER
#endif
    virtual void	drawArrow(const IlvProjectorArea& dataArea,
				  IlvPort* dst,
				  const IlvRegion* clip = 0) const;
#if DOCUMENTED_LATER
#endif
    virtual void	drawAxisLabel(const IlvProjectorArea& scaleArea,
				      IlvPort* dst,
				      const IlvRegion* clip) const;

    // Specific methods for bounding box computing.

    void		getLabelBBox(const IlvPoint& tickPoint,
				     IlDouble tickAngle,
				     IlDouble labelAngle,
				     IlvDim labelWidth,
				     IlvDim labelHeight,
				     IlvDim labelDescent,
				     IlvPos offset,
				     IlvRect& labelBBox) const;

    void		getStepLabelBBox(const IlvProjectorArea& dataArea,
					 IlUInt iStep,
					 IlvRect& bbox) const;

#if DOCUMENTED_LATER
#endif
    virtual void	getAxisBBox(const IlvProjectorArea& scaleArea,
				    const IlvPoint& minPointOnAxis,
				    const IlvPoint& maxPointOnAxis,
				    IlvRect& axisBBox) const = 0;


    //== Cursors ============
    void		drawCursors(const IlvProjectorArea& dataArea,
				    IlvDrawOrder drawOrder,
				    IlvPort* dst,
				    const IlvRegion* clip=0) const;

    void		drawCursor(const IlvAbstractChartCursor* cursor,
				   const IlvProjectorArea& dataArea,
				   IlvPort* dst,
				   const IlvRegion* clip=0) const;

    void		cursorBBox(const IlvAbstractChartCursor* cursor,
				   const IlvProjectorArea& dataArea,
				   IlvRect& bbox) const;

    virtual
    IlvAbstractChartCursor* createCursor(const IlvSingleScaleDisplayer* scaleRef=0) const = 0;

    IlUInt		getCursorsCount() const; 

    IlvAbstractChartCursor* getCursor(IlUInt index) const;   


    IlvAbstractChartCursor* getCursorByName(const char* name) const; 

    IlvAbstractChartCursor* removeCursor(IlvAbstractChartCursor* cursor);   

    void		addCursor(IlvAbstractChartCursor* cursor,
				  IlUInt position = IlvLastPositionIndex);

    void		removeCursors();

    IlBoolean		hasCursor(const IlvAbstractChartCursor* cursor) const;

    // Drawing mode
    virtual void	setOverwrite(IlBoolean o);    
    virtual void	setMode(IlvDrawMode mode);

    virtual void	setLabelZoomFactor(IlDouble scale);

    // Assignment.
    IlvSingleScaleDisplayer& operator=(const IlvSingleScaleDisplayer&);

    // Persistence
    virtual void	write(IlvOutputFile&) const;

    IlvDeclarePropClassInfo();

protected:
    struct ILVCHTEXPORTED AxisPoints
    {
	AxisPoints();
	~AxisPoints() {reset();};

	IlBoolean	mustCompute(const IlvProjectorArea& dataArea) const;
	void		update(const IlvProjectorArea& dataArea);

	void		reset();

	IlvProjectorArea	_prjArea;
	IlvPoint*		_stepPoints;
	IlUInt			_stepsCount;
	IlvPoint*		_subStepPoints;
	IlUInt			_subStepsCount;
	IlvPoint		_minPoint;
	IlvPoint		_maxPoint;
    };

    inline
    const IlvPoint*	getStepPoints(IlUInt& count) const 
			{
			    count = _axisPoints._stepsCount;
			    return _axisPoints._stepPoints;
			}

    inline
    const IlvPoint*	getSubStepPoints(IlUInt& count) const 
			{
			    count = _axisPoints._subStepsCount;
			    return _axisPoints._subStepPoints;
			}

    inline
    const IlvPoint&	getMinPointOnAxis() const 
			{
			    return _axisPoints._minPoint;
			}

    inline
    const IlvPoint&	getMaxPointOnAxis() const 
			{
			    return _axisPoints._maxPoint;
			}

    //== Coordinate information
    // (used only until the object is referenced by an axis element)
    IlvCoordinateInfo*		_coordinateInfo;
    IlvCoordinateInfoListener*	_coordLst;

    //== Fixed steps updater
    IlvConstantScaleStepsUpdater* _constStepsUpdater;

    //== Step, subStep values
    IlUInt			_stepsCount;
    IlDouble*			_stepValues;
    IlUInt			_totalSubStepsCount;
    IlDouble*			_subStepValues;

    //== Step Labels
    IlString			_stepLabelFormat;
    IlvValueToLabelCB		_valueToLabelCB;
    IlAny			_valueToLabelCBData;
    char**			_stepLabels;
    IlUInt			_stepLabelsCount;
    IlvDim*			_stepLabelsWidths;
    IlvDim*			_stepLabelsHeights;
    IlvDim*			_stepLabelsDescents;
    IlvDim			_maxStepLabelWidth;
    IlvDim			_maxStepLabelHeight;
    IlvDim			_maxStepLabelDescent;
    IlBoolean			_drawOverlappingLabels;
    IlString			_axisLabel;

    //== Layout
    LabelLayout			_labelLayout;
    TickLayout			_tickLayout;
    IlvDim			_majorTickSize;
    IlvDim			_minorTickSize;
    IlvDim			_offset;
    IlDouble			_stepLabelAngle;
    IlBoolean			_axisOriented;
    IlvDim			_arrowWidth;
    IlvDim			_arrowLength;
    IlBoolean			_drawLabelOnCrossings;
    IlvDim			_axisLabelOffset;

    //== Palettes
    IlvPalette*			_stepLabelsPalette;
    IlvPalette*			_axisPalette;
    IlvPalette*			_axisLabelPalette;

    //== Associated Grid (owned by the scale) - used only until the
    // object is referenced by an axis element
    IlvAbstractGridDisplayer*	_gridDisplayer;
    IlArray			_cursors;

    IlDouble			_labelZoomFactor;

private:
    IL_MUTABLE AxisPoints	_axisPoints;

protected:
    // Constructors
    IlvSingleScaleDisplayer(IlvCoordinateInfo* coordInfo,
			    IlvPalette* defaultPalette);

    IlvSingleScaleDisplayer(IlvCoordinateInfo* coordInfo,
			    IlUInt nbSteps,
			    const char* const* stepLabels,
			    IlUInt nbSubStepsBetween,
			    IlvPalette* defaultPalette);

    IlvSingleScaleDisplayer(const IlvSingleScaleDisplayer& src);

    IlvSingleScaleDisplayer(IlvInputFile& file);

    virtual void	readCompat(IlvInputFile& file);

    inline void		setMaxStepLabelWidth(IlvDim dim)
			{
			    _maxStepLabelWidth = dim;
			}
    inline void		setMaxStepLabelHeight(IlvDim dim)
			{
			    _maxStepLabelHeight = dim;
			}
    inline void		setMaxStepLabelDescent(IlvDim dim)
			{
			    _maxStepLabelDescent = dim;
			}

    // Internal methods
    virtual IlBoolean	updateSteps(const IlvProjectorArea* area);
    void		createFixedStepsUpdater(const IlvConstantScaleStepsUpdater* src = 0);

#if DOCUMENTED_LATER
#endif
    void		computeStepLabels();
    char*		iComputeStepLabel(IlDouble value) const;

    void		removeStepLabels();   
    void		computeStepLabelsSizes();
    void		computeMaxStepLabelSizes(); 
    void		computeMaxStepLabelWHD(IlvDim& maxWidth,
					       IlvDim& maxHeigth,
					       IlvDim& maxDescent) const;

    IlvPos		getStepLabelsOffset() const;

#if DOCUMENTED_LATER
#endif
    virtual void	getRealOffset(IlvPos& offset) const; 

    // Methods to get the min and max values.

    IlDouble		getStepDataMin() const;

    IlDouble		getStepDataMax() const;

    // Methods for drawing.
    // Specific methods for points computing.
    IlvPoint*		getPointsOnAxis(const IlvProjectorArea& dataArea,
					IlUInt valuesCount,
					const IlDouble* valuesOnAxis) const;

    // Methods to test if the drawing can be performed.
    virtual IlBoolean	tickPointOnCrossing(const IlvProjectorArea& dataArea,
					    const IlvPoint& tickPoint) const;

    virtual IlBoolean	canDrawLabel(const IlvProjectorArea& dataArea,
				     const IlvPoint& tickPoint,
				     IlvDim stepLabelWidth,
				     IlvDim stepLabelHeight) const;

    virtual IlBoolean	canDrawTick(IlDouble minPointTickAngle,
				    IlDouble tickAngle,
				    IlDouble tickValue) const;

    // Specific computings for the labels.
    void		computeLabelPosition(const IlvPoint& tickPoint,
					     IlDouble tickAngle,
					     IlDouble labelAngle,
					     IlvDim stepLabelWidth,
					     IlvDim stepLabelHeight,
					     IlvDim stepLabelDescent,
					     IlvPos offset,
					     IlvPoint& centerOfBaseline) const;

    virtual void	getAxisLabelLocation(const IlvProjectorArea& dataArea,
					     IlvPoint& point,
					     IlDouble& tickAngle) const = 0;

    //== Specific computings for the arrow.
    virtual void	getArrowLocation(const IlvProjectorArea& dataArea,
					 IlvPoint& from,
					 IlDouble& direction) const = 0;


    IlvPoint*		computeArrowPoints(const IlvPoint& from,
					   IlDouble direction,
					   IlUInt& pointCount) const;

    virtual void	getTickAngle(const IlvPoint& minPointOnAxis,
				     const IlvPoint& maxPointOnAxis,
				     IlDouble tickValue,
				     IlDouble& tickAngle) const = 0;

    void		getTickExtremities(const IlvPoint& tickPoint,
					   IlDouble tickAngle,
					   IlvPos offset,
					   IlvPoint& from,
					   IlvPoint& to) const;

    // Drawing methods.
    virtual void	internalDraw(const IlvProjectorArea& scaleArea,
				     IlvDrawOrder	      drawOrder,
				     IlvPort*		      dst,
				     const IlvRegion*	      clip = 0) const;

    virtual void	internalDrawArrow(const IlvPoint& from,
					  IlDouble direction,
					  IlvPort* dst,
					  const IlvRegion* clip = 0) const;

    // Bounding box computing.
    virtual void	internalBBox(const IlvProjectorArea& dataArea,
				     IlvRect& bbox) const;

    virtual IlUInt	getNumberOfSkippedSteps(IlUInt ticksCount,
						const IlDouble* tickValues,
						const IlvPoint* tickPoints,
						const IlvPoint& minPointOnAxis,
						const IlvPoint& maxPointOnAxis,
						IlvPos offset) const;
    // Check grid type against projector type 
    IlBoolean		checkGridType(const IlvAbstractGridDisplayer* grid);
    void		checkLogTransfo();

    virtual void	setAxisElement(IlvAxisElement *el);
    virtual
    IlvAxisElement*	getAxisElement() const;
};

// --------------------------------------------------------------------------
// Class IlvRectangularScaleDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvRectangularScaleDisplayer
    : public IlvSingleScaleDisplayer
{
public:
    // Constructors & destructor

    IlvRectangularScaleDisplayer(IlvCoordinateInfo* coordInfo,
				 IlvPalette* defaultPalette);
    IlvRectangularScaleDisplayer(IlvCoordinateInfo* coordInfo,
				 IlUInt nbSteps,
				 const char* const* stepLabels,
				 IlUInt nbSubStepsBetween,
				 IlvPalette* defaultPalette);

    virtual ~IlvRectangularScaleDisplayer();

    //== Axis drawing
    virtual void	drawAxis(const IlvProjectorArea& scaleArea,
				 IlvPort* dst,
				 const IlvRegion* clip = 0) const;

    virtual void	getAxisBBox(const IlvProjectorArea& scaleArea,
				    const IlvPoint& minPointOnAxis,
				    const IlvPoint& maxPointOnAxis,
				    IlvRect& axisBBox) const;


    virtual IlvCircularScaleDisplayer* 
	createCircularScale(IlvAbstractGridDisplayer* gridDisplayer) const;

    virtual IlUInt	getMaxStepsCount(const IlvProjectorArea& scaleArea,
					 IlvDim stepsSpacing) const;

    virtual IlvAbstractGridDisplayer* 
	createGridDisplayer(const IlvSingleScaleDisplayer* scaleRef=0) const;

    virtual IlvAbstractChartCursor* 
	createCursor(const IlvSingleScaleDisplayer* scaleRef=0) const;


    DeclareScaleDisplayerTypeInfoRO(IlvRectangularScaleDisplayer);

protected:

    // Internal methods

    virtual void	getRealOffset(IlvPos& offset) const;

    // Methods for drawing.
    // Methods to test if the drawing can be performed.
    virtual IlBoolean	canDrawTick(IlDouble minPointTickAngle,
				    IlDouble tickAngle,
				    IlDouble tickValue) const;

    // Specific computings for the labels.
    virtual void	getAxisLabelLocation(const IlvProjectorArea& dataArea,
					     IlvPoint& point,
					     IlDouble& tickAngle) const;

    // Specific computings for the arrow.
    virtual void	getArrowLocation(const IlvProjectorArea& dataArea,
					 IlvPoint& from,
					 IlDouble& direction) const;

    // Specific methods for the steps and subSteps.

    virtual void	getTickAngle(const IlvPoint& minPointOnAxis,
				     const IlvPoint& maxPointOnAxis,
				     IlDouble tickValue,
				     IlDouble& tickAngle) const;

    // Specific methods for the axis.
    IlDouble		getAxisAngle(const IlvPoint& minPointOnAxis,
				     const IlvPoint& maxPointOnAxis) const;

    virtual void	getAxisExtremities(const IlvProjectorArea& scaleArea,
					   IlDouble& axisAngle,
					   IlvPoint& axisBeginning,
					   IlvPoint& axisEnd) const;
};


// --------------------------------------------------------------------------
// Class IlvCircularScaleDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCircularScaleDisplayer : public IlvSingleScaleDisplayer
{
public:
    IlvCircularScaleDisplayer(IlvCoordinateInfo* coordInfo,
			      IlvPalette* defaultPalette);

    IlvCircularScaleDisplayer(IlvCoordinateInfo* coordInfo,
			      IlUInt stepsCount,
			      const char* const* stepLabels,
			      IlUInt subStepsCount,
			      IlvPalette* defaultPalette);

    virtual ~IlvCircularScaleDisplayer();

    // Specific methods for drawing.
    virtual void	drawAxis(const IlvProjectorArea& scaleArea,
				 IlvPort* dst,
				 const IlvRegion* clip = 0) const;

    // Specific methods for bounding box computing.
    virtual void	getAxisBBox(const IlvProjectorArea& scaleArea,
				    const IlvPoint& minPointOnAxis,
				    const IlvPoint& maxPointOnAxis,
				    IlvRect& axisBBox) const;

    virtual void	getAxisDrawingRect(const IlvProjectorArea& dataArea,
					   const IlvPoint& minPointOnAxis,
					   IlvRect& axisDrawingRect) const;

    virtual void	getAxisExtremitiesAngles(const IlvRect& axisRect,
						 IlDouble& startingAngle,
						 IlDouble& endingAngle) const;

    virtual void	setProjector(const IlvAbstractProjector* prj);

    virtual IlvRectangularScaleDisplayer* 
	createRectangularScale(IlvAbstractGridDisplayer* gridDisplayer) const;

    virtual IlUInt	getMaxStepsCount(const IlvProjectorArea& scaleArea,
					 IlvDim stepsSpacing) const;



    virtual IlvAbstractGridDisplayer* 
	createGridDisplayer(const IlvSingleScaleDisplayer* scaleRef=0) const;

    virtual IlvAbstractChartCursor* 
	createCursor(const IlvSingleScaleDisplayer* scaleRef=0) const;

    DeclareAbstractScaleDisplayerTypeInfoRO(IlvCircularScaleDisplayer);

protected:

    // Internal methods
    // Methods for drawing.
    // Methods to test if the drawing can be performed.
    virtual IlBoolean	canDrawTick(IlDouble minPointTickAngle,
				    IlDouble tickAngle,
				    IlDouble tickValue) const;

    // Specific computings for the labels.
    virtual void	getAxisLabelLocation(const IlvProjectorArea& dataArea,
					     IlvPoint& point,
					     IlDouble& tickAngle) const;

    void		computeLabelBoundingAngle(IlDouble scaleRadius,
						  IlDouble tickAngle,
						  IlvDim labelWidth,
						  IlvDim labelHeight,
						  IlvPos offset,
						  IlDouble& boundAngle) const;

    // Specific computings for the arrow.
    virtual void	getArrowLocation(const IlvProjectorArea& dataArea,
					 IlvPoint&  from,
					 IlDouble& direction) const;

    // Specific methods for the steps and subSteps.
    virtual void	getTickAngle(const IlvPoint& minPointOnAxis,
				     const IlvPoint& maxPointOnAxis,
				     IlDouble tickValue,
				     IlDouble& tickAngle) const;

    // Specific methods for the axis.
    virtual IlvDim	getAxisLength(const IlvProjectorArea& dataArea) const;

    void		computeAxisBBox(const IlvRect& axisDrawingRect,
					IlDouble startingAngle,
					IlDouble endingAngle,
					IlvRect& axisBBox) const;
};

// --------------------------------------------------------------------------
// Class IlvMultiScaleDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvMultiScaleDisplayer : public IlvAbstractScaleDisplayer
{
public:

    virtual ~IlvMultiScaleDisplayer();

    // Accessors
    virtual IlBoolean	isOnAbscissa() const;
    virtual IlBoolean	isOnOrdinate() const;
    virtual
    IlvCoordinateType	getCoordinateType() const;

    virtual
    IlvCoordinateInfo*	getCoordinateInfo(IlUInt index = 0) const;

    IlUInt		getSubScalesCount() const;

    IlvSingleScaleDisplayer* getSubScale(IlUInt index) const;

    void		addSubScale(IlvCoordinateInfo* coordInfo);

    void		addSubScales(IlUInt count,
				     IlvCoordinateInfo* const* coordInfo);

    IlvSingleScaleDisplayer* removeSubScale(IlUInt index);

    void removeSubScales();

    IlvDim		getSubScaleOffset() const { return _subScaleOffset; }

    void		setSubScaleOffset(IlvDim offset) 
			{
			    _subScaleOffset = offset; invalidateLayout();
			}

    IlUInt		findSubScaleIndex(const IlvCoordinateInfo* cInfo)const;

    // Returns the associated subscale index or IlvBadIndex if no associated 
    // subscale is found.
    IlUInt findSubScaleIndex(const IlvSingleScaleDisplayer* subScale) const;


    // Positioning
    virtual void	setRelativePosition(IlvAxisPosition relPos,
					    IlvPos offset = 0);
    virtual IlBoolean	setCrossingValue(IlDouble dataValue,
					 const IlvSingleScaleDisplayer* ref);


    // This method can be used only if _infoForCrossingValue is defined.
    virtual IlBoolean	setCrossingValue(IlDouble dataValue); 

    virtual void	setAlwaysVisible(IlBoolean b);
    virtual void	setDrawOrder(IlvDrawOrder drawOrder);
    virtual void	setGridDrawOrder(IlvDrawOrder drawOrder);

    // Steps, subSteps 
    virtual void	fixStepsCount(IlUInt stepsCount,
				      IlUInt subStepsBetweenCount);
    virtual void	fixStepUnit(IlDouble stepUnit, IlDouble subStepUnit);

    // Automatic step, substep count computing

    virtual void	setAutoStepsCount(IlBoolean	b,
					  IlvDim	stepsSpacing  = 10,
					  IlUInt	subStepsCount = 0);


    //== Layout ============
    virtual void	setLabelLayout(LabelLayout layout);
    virtual void	setTickLayout(TickLayout layout);
    virtual void	setMajorTickSize( IlvDim val );
    virtual void	setMinorTickSize(IlvDim val);
    virtual void	setOffset(IlvDim dim);
    virtual void	setStepLabelAngle(IlDouble angle);
    virtual void	setAxisOriented(IlBoolean o);
    virtual void	setArrowWidth(IlvDim width);
    virtual void	setArrowLength(IlvDim length);
    virtual void	drawLabelOnCrossings(IlBoolean b);
    virtual void	drawOverlappingLabels(IlBoolean b);
    virtual void	setAxisLabelOffset(IlvDim offset);

    //== Labels ========
    virtual void	setStepLabelFormat(const char* format,
					   IlBoolean invalidate = IlTrue);
    virtual void	setValueToLabelCB(IlvValueToLabelCB cb,
					  IlAny cbData = 0); 
    virtual void	setStepLabels(IlUInt count, 
				      const char* const* labels = 0);
    virtual void	setStepLabel(IlUInt labelIndex, const char* label); 


    //== Palettes ========
    inline IlvPalette*	getDefaultPalette() const { return _defaultPalette; }
    void		setDefaultPalette(IlvPalette* pal);

    virtual void	setStepLabelsPalette(IlvPalette* pal);
    virtual void	setAxisPalette(IlvPalette* pal);
    virtual void	setAxisLabelPalette(IlvPalette* pal);

    // Updating
    virtual IlBoolean	layoutToUpdate() const;

    virtual void	setProjector(const IlvAbstractProjector* prj);
    virtual void	setCoordinateType(IlvCoordinateType type);

    virtual IlBoolean	setCoordinateInfo(IlvCoordinateInfo* coordInfo,
					  IlUInt index = 0);

    virtual void	setLayoutModified(IlBoolean flag);

    virtual IlBoolean	isDrawingNeeded(IlvDrawOrder order);

    virtual void	draw(const IlvProjectorArea& scaleArea,
			     IlvDrawOrder	     drawOrder,
			     IlvPort*		     dst,
			     const IlvTransformer*   t = 0,
			     const IlvRegion*	     clip = 0) const;

    virtual IlBoolean	boundingBox(const IlvProjectorArea& scaleArea,
				    IlvRect&		    bbox,
				    const IlvTransformer*   t = 0) const;

    virtual void	update(const IlvProjectorArea& dataArea);

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode mode);

    virtual void	write(IlvOutputFile&) const;

    IlvDeclarePropClassInfo();

protected:
    IlvDim		_subScaleOffset;
    IlArray		_subScales;
    IlvPalette*		_defaultPalette;

    // Constructors
    IlvMultiScaleDisplayer(IlvDim subScaleOffset,
			   IlvPalette* defaultPalette);

    IlvMultiScaleDisplayer(const IlvMultiScaleDisplayer& scaleDisplayer);

    IlvMultiScaleDisplayer(IlvInputFile& file);

    virtual IlvSingleScaleDisplayer* 
	createSubScale(IlvCoordinateInfo* coordInfo) = 0;

};


// --------------------------------------------------------------------------
// IlvScaleStepsUpdater
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvScaleStepsUpdater : public IlvNamedProperty
{
    friend class IlvSingleScaleDisplayer;

public:
    virtual ~IlvScaleStepsUpdater();
    static IlSymbol*	GetSymbol();

    static
    IlvScaleStepsUpdater*	Set(IlvSingleScaleDisplayer* scale,
				    IlvScaleStepsUpdater*    updater);

    static
    IlvScaleStepsUpdater*	Get(const IlvSingleScaleDisplayer* scale);

    static
    IlvScaleStepsUpdater*	Remove(IlvSingleScaleDisplayer* scale);

    inline
    IlvSingleScaleDisplayer*	getScale() const { return _scale; }

    virtual IlBoolean	mustUpdate(const IlvProjectorArea& area);

    virtual void	getStepSubStepValues(const IlvProjectorArea& area,
					     IlUInt& stepsCount,
					     IlDouble*&	stepValues,
					     IlUInt& subStepsCount,
					     IlDouble*&	subStepValues) const = 0;

    virtual char*	computeStepLabel(IlDouble value) const;
    //virtual IlBoolean isPersistent() const;

    inline
    IlvCoordinateInfo*	getCoordinateInfo() const 
			{
			    return _scale ? _scale->getCoordinateInfo() : 0;
			}

    virtual IlBoolean	checkRange(IlvCoordInterval& range) const;

    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    DeclareLazyPropertyInfoRO();
    DeclarePropertyIOConstructors(IlvScaleStepsUpdater);

protected:
    IlvSingleScaleDisplayer*	_scale;
    IlBoolean			_valid;

    IlvScaleStepsUpdater(IlvSingleScaleDisplayer* scale);

    inline void		setValid(IlBoolean b) { _valid = b;}
    inline IlBoolean	isValid() const { return _valid; }

    virtual IlBoolean	coordRangeChanged(const IlvCoordInterval& oldRange);
    virtual void	coordTransformerChanged(const IlvCoordinateTransformer* oldT);
};

// --------------------------------------------------------------------------
// IlvConstantScaleStepsUpdater
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvConstantScaleStepsUpdater : public IlvScaleStepsUpdater
{
protected:
    enum {
	FirstStepData  = 0x0001,
	LastStepData   = 0x0002,
	StepUnit       = 0x0004,
	StepNumber     = 0x0008,
	Invalidated    = 0x0010,
	NoTransformer  = 0x0020
    };

public:
    IlvConstantScaleStepsUpdater(IlvSingleScaleDisplayer* scale);

    IlvConstantScaleStepsUpdater(IlvSingleScaleDisplayer* scale,
				 IlUInt stepsCount,
				 IlUInt subStepsCount = 0);

    IlvConstantScaleStepsUpdater(IlvSingleScaleDisplayer* scale,
				 IlDouble stepUnit,
				 IlDouble subStepUnit = 0.);

    virtual ~IlvConstantScaleStepsUpdater();

    inline IlBoolean	isStepUnitFixed() const 
			{
			    return (_flags & StepUnit) ? IlTrue : IlFalse;
			}

    virtual void	getStepSubStepValues(const IlvProjectorArea& area,
					     IlUInt& stepsCount,
					     IlDouble*&	stepValues,
					     IlUInt& subStepsCount,
					     IlDouble*& subStepValues) const;
    inline IlDouble	getStepUnit() const { return _stepUnit; }

    inline IlDouble	getSubStepUnit() const { return _subStepUnit; }

    inline IlUInt	getStepsCount() const { return _stepsCount; } 

    inline IlUInt	getSubStepsCount() const { return _subStepsCount; } 

    void		fixStepsCount(IlUInt stepsCount,
				      IlUInt subStepsCount);

    void		fixStepUnit(IlDouble stepUnit,
				    IlDouble subStepUnit);

    //== First and last steps values
    void		setFirstStepData(IlDouble value);

    inline IlDouble	getFirstStepData() const { return _firstStepData; }

    inline IlBoolean	isFirstStepDataDefined() const 
			{
			    return (_flags & FirstStepData)
				? IlTrue
				: IlFalse;
			}
    inline void		unsetFirstStepData() { _flags &= ~FirstStepData; }
    IlDouble		getStepDataMin() const;

    void		setLastStepData(IlDouble value);

    inline IlDouble	getLastStepData() const { return _lastStepData; }   

    inline IlBoolean	isLastStepDataDefined() const  
			{
			    return (_flags & LastStepData) ? IlTrue : IlFalse;
			}
    inline void		unsetLastStepData() { _flags &= ~LastStepData; }
    IlDouble		getStepDataMax() const;

    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    void		getExtraSubStepsCount(IlUInt& extraSubStepBefore,
					      IlUInt& extraSubStepAfter) const;
    IlUInt		getTotalSubStepsCount() const;

    virtual IlBoolean	checkRange(IlvCoordInterval& range) const;


    inline IlBoolean	isUsingTransformer() const
			{
			    return (_flags & NoTransformer)
				? IlFalse
				: IlTrue; 
			}
    inline void		useTransformer(IlBoolean b)
			{
			    if (b) 
				_flags &= ~NoTransformer;
			    else
				_flags |= NoTransformer;
			}

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvConstantScaleStepsUpdater);

protected:
    int			_flags;
    IlUInt		_stepsCount;
    IlUInt		_subStepsCount;
    IlDouble		_stepUnit;
    IlDouble		_subStepUnit;

    //== First and last steps values
    IlDouble		_firstStepData;
    IlDouble		_lastStepData;

    void		iFixStepUnit(IlDouble stepUnit, IlDouble subStepUnit);
    void		computeFixedStepUnit();

    void		iFixStepsCount(IlUInt stepsCount,
				       IlUInt subStepsCount);
    void		computeFixedStepsCount();

    virtual IlBoolean	coordRangeChanged(const IlvCoordInterval& oldRange);
};

// --------------------------------------------------------------------------
// IlvAutoScaleStepsUpdater
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAutoScaleStepsUpdater
    : public IlvConstantScaleStepsUpdater
{
protected:
    enum {
	AutoLabelFormat    = 0x0001,
	AutoPrecision	   = 0x0002,
	AutoSubSteps	   = 0x0004,
	AutoDisabled	   = 0x0008
    };

public:

    IlvAutoScaleStepsUpdater(IlvSingleScaleDisplayer* scale,
			     IlDouble	precision,
			     IlvDim	stepsSpacing	= 10,
			     IlDouble	precisionBase	= 10.,
			     IlBoolean	autoSubSteps	= IlTrue);

    IlvAutoScaleStepsUpdater(IlvSingleScaleDisplayer* scale,
			     IlvDim	stepsSpacing	= 10,
			     IlBoolean	autoSubSteps	= IlTrue,
			     IlBoolean  autoLabelFormat = IlTrue);

    virtual IlBoolean	mustUpdate(const IlvProjectorArea& area);

    virtual void	getStepSubStepValues(const IlvProjectorArea& area,
					     IlUInt& stepsCount,
					     IlDouble*&	stepValues,
					     IlUInt& subStepsCount,
					     IlDouble*&	subStepValues) const;

    void		setPrecision(IlDouble	precision, 
				     IlDouble	precisionBase = 10.);

    inline IlDouble	getPrecision() const { return _precision; }

    inline IlDouble	getPrecisionBase() const { return _precisionBase; }

    inline IlBoolean	getAutoLabelFormat() const 
			{
			    return (_autoMode & AutoLabelFormat)
				? IlTrue
				: IlFalse;
			}

    void		setAutoLabelFormat(IlBoolean autoLabelFormat);

    inline IlBoolean	getAutoPrecision() const 
			{
			    return (_autoMode & AutoPrecision)
				? IlTrue
				: IlFalse;
			}

    void		setAutoPrecision(IlBoolean autoPrecision);

    inline IlBoolean	getAutoSubSteps() const 
			{
			    return (_autoMode & AutoSubSteps)
				? IlTrue
				: IlFalse;
			}

    void		setAutoSubSteps(IlBoolean autoSubSteps,
					IlUInt subStepsCount = 0);

    inline IlvDim	getStepsSpacing() const { return _stepsSpacing; }

    inline void		setStepsSpacing(IlvDim stepsSpacing)
			{
			    _stepsSpacing = stepsSpacing;
			}

    static
    IlvAutoScaleStepsUpdater* Get(const IlvSingleScaleDisplayer* scale);

    virtual void	propertyAdded(IlAny);

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvAutoScaleStepsUpdater);

    void		disable(IlBoolean);
    inline IlBoolean	isDisabled() const 
			{
			    return (_autoMode & AutoDisabled)
				? IlTrue
				: IlFalse;
			}
protected:
    int			_autoMode;
    IlDouble		_precision;
    IlDouble		_precisionBase;
    IlvDim		_stepsSpacing;

    virtual void	autoComputeSteps(const IlvProjectorArea& area);
    virtual void	updateLabelFormat(IlDouble	precision,
					  IlBoolean	invalidate = IlTrue);
    virtual void	updatePrecision(const IlvProjectorArea& area,
					const IlvCoordInterval& range,
					IlUInt realSteps);
    void		updatePrecision10(const IlvCoordInterval& range,
					  IlUInt realSteps);
};

// --------------------------------------------------------------------------
// IlvLogScaleStepsUpdater
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvLogScaleStepsUpdater : public IlvScaleStepsUpdater
{
public :
    IlvLogScaleStepsUpdater(IlvSingleScaleDisplayer* scale);

    virtual void	getStepSubStepValues(const IlvProjectorArea& area,
					     IlUInt& stepsCount,
					     IlDouble*&	stepValues,
					     IlUInt& subStepsCount,
					     IlDouble*&	subStepValues) const;

    virtual char*	computeStepLabel(IlDouble value) const;

    virtual IlBoolean	checkRange(IlvCoordInterval& range) const;

    DeclareLazyPropertyInfoRO();
    DeclarePropertyIOConstructors(IlvLogScaleStepsUpdater);

protected :    
    inline
    IlvChartCoordinateTransformer* getTransformer() const
			{
			    return _scale 
				? IL_CAST(IlvChartCoordinateTransformer*,
					  getCoordinateInfo()
					  ->getTransformer())
				: 0;
    }
};

// --------------------------------------------------------------------------
// IlvZoomCoordinateTransformer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvZoomCoordinateTransformer
    : public IlvCoordinateTransformer
{
public:
    IlvZoomCoordinateTransformer(const IlvCoordInterval& zoomWindow,
				 IlDouble		 zoomFactor,
				 IlBoolean		 continuous = IlTrue);

    //== General Accessors
    inline
    const IlvCoordInterval&	getZoomWindow() const
				{
				    return _zoomWindow; 
				}

    IlBoolean		setZoomWindow(const IlvCoordInterval& window);

    inline IlBoolean	setZoomWindow(IlDouble start, IlDouble end)
			{
			    return setZoomWindow(IlvCoordInterval(start, end));
			}

    inline IlDouble	getZoomFactor() const { return _zoomFactor; }

    IlBoolean		setZoomFactor(IlDouble zoomFactor);

    inline IlBoolean	isContinuous() const { return _continuous; }

    void		setContinuous(IlBoolean continuous);

    inline void		getTransformedWindow(IlvCoordInterval& itv) const
			{
			    IlDouble mid = getZoomWindow().getMiddle();
			    IlDouble width = getZoomFactor() *
				getZoomWindow().getLength()/2;
			    itv.set(mid - width, mid + width);
			    if (getOwner())
				itv.intersection(getOwner()->getDataRange());
			}

    //== Transformation
    virtual IlBoolean	transformPoints(IlUInt pointsCount,
					IlvDoublePoint* points) const;
    virtual IlBoolean	transformValue(IlDouble& value) const;
    virtual IlBoolean	inverseTransformPoints(IlUInt pointsCount,
					       IlvDoublePoint* points) const;
    virtual IlBoolean	inverseTransformValue(IlDouble& value) const;


    virtual IlBoolean	validateInterval(IlvCoordInterval& interval) const;

    DeclareCoordinateTransformerTypeInfo(IlvZoomCoordinateTransformer);

protected:
    IlvCoordInterval	_zoomWindow;
    IlDouble		_zoomFactor;
    IlBoolean		_continuous;
};

// --------------------------------------------------------------------------
// IlvZoomScaleStepsUpdater
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvZoomScaleStepsUpdater : public IlvScaleStepsUpdater
{
public :
    IlvZoomScaleStepsUpdater(IlvSingleScaleDisplayer* scale);
    virtual ~IlvZoomScaleStepsUpdater();

    virtual IlBoolean	mustUpdate(const IlvProjectorArea& area);

    virtual void	getStepSubStepValues(const IlvProjectorArea& area,
					     IlUInt& stepsCount,
					     IlDouble*&	stepValues,
					     IlUInt& subStepsCount,
					     IlDouble*&	subStepValues) const;

    virtual char*	computeStepLabel(IlDouble value) const;

    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    DeclareLazyPropertyInfoRO();
    DeclarePropertyIOConstructors(IlvZoomScaleStepsUpdater);

protected :
    IlvAutoScaleStepsUpdater*	_subUpdater;

    inline
    IlvZoomCoordinateTransformer* getTransformer() const
			{
			    return _scale 
				? IL_CAST(IlvZoomCoordinateTransformer*,
					  getCoordinateInfo()
					  ->getTransformer())
				: 0;
			}
    void		createSubUpdater(IlvSingleScaleDisplayer*);
};
ILVCHTMODULEINIT(scaledis);

#endif /* __Ilv_Charts_Scaledis_H */
