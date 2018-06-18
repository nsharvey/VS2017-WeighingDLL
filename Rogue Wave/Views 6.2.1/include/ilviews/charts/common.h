// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/common.h
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
// Declaration of the common classes.
// Contains:
//  - IlvCoordInterval: a class that is aimed to represent a values interval.
//  - IlvCoordinateTransformer: an abstract class which allows you to 
//    specify a transformation that will be applied to a given coordinate 
//    of a data point.  
//  - IlvChartCoordinateTransformer: a subclass of 
//    IlvCoordinateTransformer which allows you to define an elementary
//    transformation that will be first applied, possibly followed by a 
//    logarithmic transformation depending on the specified logBase.
//  - IlvSimpleChartTransformer: a subclass of IlvChartCoordinateTransformer
//    with no elementary transformation.
//  - IlvAffineChartTransformer: a subclass of IlvChartCoordinateTransformer
//    with an affine transformation as elementary transformation.
//
//  - IlvCoordinateInfo: a class that stores specific information for each 
//    coordinate (x, y, theta, or rho) that the user would like to represent 
//    with a given scale. It specially stores the minimum and maximum values
//    for this coordinate that will be used to select the data to display. It
//    also stores a transformation that will be applied to this coordinate.
//
//  - IlvAbstractProjector: an abstract class that allows you to project the 
//    data into screen coordinates.
//  - IlvCartesianProjector: a subclass of IlvAbstractProjector that allows
//    to project data expressed in a cartesian system of coordinates.
//  - IlvPolarProjector: a subclass of IlvAbstractProjector that allows you to
//    project data expressed in a polar system of coordinates.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Common_H
#define __Ilv_Charts_Common_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Chart_H)
#include <ilviews/charts/chart.h>
#endif
#if !defined(__Ilv_Util_Pool_H)
#include <ilviews/util/pool.h>
#endif

// --------------------------------------------------------------------------
extern ILVCHTEXPORTED const IlUInt IlvLastPositionIndex;
extern ILVCHTEXPORTED const IlUInt IlvNoCountLimit;
// --------------------------------------------------------------------------

IlDeclareExpPoolOf(IlDouble,  IlDouble, ILVCHTEXPORTED);
// --------------------------------------------------------------------------

struct ILVCHTEXPORTED IlvProjectorArea
{
//public:
    IlvProjectorArea() : _area(), _offset(0), _length(0) {}
    IlvProjectorArea(const IlvRect& area) 
	: _area(area), _offset(0), _length(0) {}

    inline void		set(const IlvRect& area,
			    IlDouble offset = 0,
			    IlDouble length = 0)
			{
			    _area = area; 
			    _offset = offset;
			    _length = length;
			}

    inline IlDouble	getOffset() const { return _offset; }
    inline IlDouble	getLength() const { return _length; }
    inline
    const IlvRect&	getGlobalRect() const { return _area; }
    inline IlvDim	getMinAreaSize() const 
			{
			    return IlMin(_area.w(), _area.h());
			}

    inline IlBoolean	isTranslated(const IlvProjectorArea& area) const
			{
			    return (_offset == area.getOffset()) &&
				(_length == area.getLength()) &&
				(_area.w() == area.getGlobalRect().w()) &&
				(_area.h() == area.getGlobalRect().h());
			}

    inline void		applyTransform(const IlvTransformer& t)
			{
			    t.apply(_area);
			}

//private:
    IlvRect		_area;
    IlDouble		_offset;
    IlDouble		_length;
};

enum IlvDrawOrder {
    IlvDrawAbove,
    IlvDrawBelow
};

enum IlvCoordinateType {
    IlvAbscissaCoordinate,
    IlvOrdinateCoordinate
};

enum IlvAxisPosition {
    IlvMinDataPosition,
    IlvMaxDataPosition
};

class IlvAbstractScaleDisplayer;
class IlvRectangularScaleDisplayer;
class IlvMultiRectangularScaleDisplayer;
class IlvCoordinateInfo;

// --------------------------------------------------------------------------
// Class IlvCoordInterval
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCoordInterval
{
public:

    ILVEXPLICIT IlvCoordInterval(IlDouble min = 0.0, IlDouble max = 0.0) 
	: _min(min), _max(max) {}

    inline IlDouble	getMin() const { return _min; }

    inline IlDouble	getMax() const { return _max; }

    inline void		setMin(IlDouble val) { _min = val; }

    inline void		setMax(IlDouble val) { _max = val; }

    inline void		set(IlDouble min, IlDouble max)
			{
			    _min = min;
			    _max = max;
			}


    inline IlBoolean	isBefore(IlDouble val) const { return val <= _min; }

    inline IlBoolean	isStrictlyBefore(IlDouble val) const
			{
			    return val < _min - IlvCHTItvPrecision;
			}

    inline IlBoolean	isAfter(IlDouble val) const
			{
			    return val >= _max;
			}

    inline IlBoolean	isStrictlyAfter(IlDouble val) const
			{
			    return val > _max + IlvCHTItvPrecision;
			}

    inline IlBoolean	isInside(IlDouble val) const
			{
			    return !(isStrictlyBefore(val) ||
				     isStrictlyAfter(val));
			}

    inline IlBoolean	isStrictlyInside(IlDouble val) const
			{
			    return !(isBefore(val) || isAfter(val));
			}

    inline IlBoolean	isOutside(IlDouble val) const
			{
			    return isBefore(val) || isAfter(val);
			}

    inline IlBoolean	isStrictlyOutside(IlDouble val) const
			{
			    return isStrictlyBefore(val)
				|| isStrictlyAfter(val);
			}

    inline void		translate(IlDouble delta)
			{
			    _min += delta;
			    _max += delta;
			}

    inline IlBoolean	intersects(const IlvCoordInterval& itv) const
			{
			    return !(isStrictlyBefore(itv.getMax())
				     || isStrictlyAfter(itv.getMin()));
			}

    inline IlBoolean	contains(const IlvCoordInterval& itv) const
			{
			    return isInside(itv.getMin())
				&& isInside(itv.getMax());
			}

    inline IlvCoordInterval&	intersection(const IlvCoordInterval& itv)
				{
				    if (intersects(itv)) {
					if (itv.isStrictlyBefore(getMin()))
					    setMin(itv.getMin());
					if (itv.isStrictlyAfter(getMax()))
					    setMax(itv.getMax());
				    }
				    else setMax(getMin());
				    return *this;
				}

    inline IlDouble	getLength() const { return _max - _min; }
    inline IlDouble	length() const { return getLength(); }

    inline IlDouble	getMiddle() const { return getMin() + getLength()/2; }


    inline IlDouble	stepToValue(IlDouble nSteps, IlDouble iStep) const
			{
			    return length()/(nSteps-1)*iStep + getMin();
			}
    inline void		operator+=(IlDouble val)
			{
			    if (isStrictlyBefore(val))
				setMin(val);
			    else if (isStrictlyAfter(val))
				setMax(val);    
			}

    inline void		operator+=(const IlvCoordInterval& itv)
			{
			    *this += itv.getMin();
			    *this += itv.getMax();
			}

    inline int		operator==(const IlvCoordInterval& itv) const
			{
			    return (_min==itv.getMin())
				&& (_max==itv.getMax());
			}
    inline int		operator!=(const IlvCoordInterval& itv) const
			{
			    return (_min!=itv.getMin())
				|| (_max!=itv.getMax());
			}
private:
    IlDouble		_min;
    IlDouble		_max;
};


ILVCHTEXPORTEDFUNCTION(ILVSTDPREF istream&)
operator>>(ILVSTDPREF istream& o, IlvCoordInterval& );

ILVCHTEXPORTEDFUNCTION(ILVSTDPREF ostream&)
operator<<(ILVSTDPREF ostream& o, const IlvCoordInterval& );

// --------------------------------------------------------------------------
// IlvCoordinateTransformer persistence
// --------------------------------------------------------------------------
class IlvCoordinateTransformer;
typedef IlvCoordinateTransformer* 
(* IlvCoordinateTransformerConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvCoordinateTransformerClassInfo 
    : public IlvValuedClassInfo
{
public:
    static IlvCoordinateTransformerClassInfo*
             Create(const char* className,
		    IlvClassInfo** superClass,
		    IlvCoordinateTransformerConstructor ctor);

    inline
    IlvCoordinateTransformerClassInfo* 
		getCoordinateTransformerSuperClass() const
		{ return ILVDYNAMICCAST(IlvCoordinateTransformerClassInfo*, 
					getSuperClass());
		}
    inline
    IlvCoordinateTransformerConstructor getConstructor() const
					{
					    return _constructor;
					}
protected:
    IlvCoordinateTransformerConstructor	_constructor;

    IlvCoordinateTransformerClassInfo(const char* className,
				      IlvClassInfo** superClass,
				      IlvCoordinateTransformerConstructor ctor)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(ctor)
    {}

};

#define IlvRegisterCoordinateTransformerClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,				\
		IlvCoordinateTransformerClassInfo::Create(	\
		#classname,					\
		ILVSUPERCLASSINFO(superclass),			\
		(IlvCoordinateTransformerConstructor)classname::Read))

#define IlvPreRegisterCoordinateTransformerClass(classname)	\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvPostRegisterCoordinateTransformerClass(classname, superclass)\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
		IlvCoordinateTransformerClassInfo::Create(	\
		#classname,					\
		ILVSUPERCLASSINFO(superclass),			\
		(IlvCoordinateTransformerConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvCoordinateTransformer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCoordinateTransformer : public IlvValueInterface
{
public:

    virtual ~IlvCoordinateTransformer();

    // Accessors
    inline
    const IlvCoordinateInfo*	getOwner() const { return _owner; }
    inline IlvCoordinateInfo*	getOwner() { return _owner; }

    // Apply a transformation to points.

    virtual IlBoolean	transformPoints(IlUInt pointsCount,
					IlvDoublePoint* points) const;

    // Apply a transformation to values.

    virtual IlBoolean	transformValues(IlUInt valuesCount,
					IlDouble* values) const;

    // Apply a transformation to a value.

    virtual IlBoolean	transformValue(IlDouble& value) const = 0;

    // Apply the inverse transformation to points.
    virtual IlBoolean	inverseTransformPoints(IlUInt pointsCount,
					       IlvDoublePoint* points) const;

    // Apply the inverse transformation to values.

    virtual IlBoolean	inverseTransformValues(IlUInt valuesCount,
					       IlDouble* values) const;

    // Apply the inverse transformation to a value.

    virtual IlBoolean	inverseTransformValue(IlDouble& val) const = 0;

    virtual IlBoolean	transformInterval(IlvCoordInterval& itvl) const;

    virtual IlBoolean	inverseTransformInterval(IlvCoordInterval& itvl) const;

    virtual IlBoolean	validateInterval(IlvCoordInterval& interval) const;

    virtual IlvCoordinateTransformer*	copy() const = 0;

    // Should be not used directly by the user.
    inline void		setOwner(IlvCoordinateInfo* coordInfo)
			{
			    _owner = coordInfo;
			}

    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvCoordinateTransformer*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropRootClassInfo();

protected:
    IlvCoordinateInfo*	_owner;

    IlvCoordinateTransformer();

    IlvCoordinateTransformer(const IlvCoordinateTransformer& transfo); 

    IlvCoordinateTransformer(IlvInputFile& file);
};

// --------------------------------------------------------------------------
// Class IlvChartCoordinateTransformer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartCoordinateTransformer
    : public IlvCoordinateTransformer
{
public:

    virtual ~IlvChartCoordinateTransformer();

    inline IlUInt	getLogBase() const { return _logBase; }

    void		setLogBase(IlUInt base);

    // Apply a transformation to points:
    // transform the data into another system of coordinates.
    // First apply an elementary transformation (depending on the 
    // transformer considered), and then apply a logarithmic 
    // transformation if _logBase > 1.

    virtual IlBoolean	transformPoints(IlUInt pointsCount,
					IlvDoublePoint* points) const;

    // Apply a transformation to values.

    virtual IlBoolean	transformValues(IlUInt valuesCount,
					IlDouble* values) const;

    // Apply a transformation to a value.

    virtual IlBoolean	transformValue(IlDouble& val) const;

    // Apply the inverse transformation to points.

    virtual IlBoolean	inverseTransformPoints(IlUInt pointsCount,
					       IlvDoublePoint* points) const;

    // Apply the inverse transformation to values.

    virtual IlBoolean	inverseTransformValues(IlUInt valuesCount,
					       IlDouble* values) const;

    // Apply the inverse transformation to a value.

    virtual IlBoolean	inverseTransformValue(IlDouble& val) const;

    // Specific methods.
    // Define the condition that is needed to be able to apply the
    // elementary transformation.

    virtual IlBoolean	condToApplyElementaryTransfo() const = 0;

    virtual IlBoolean	condToApplyInverseElementaryTransfo() const = 0;

    // Apply the elementary transformation (depending on the transformer
    // considered).

    virtual void	applyElementaryTransfo(IlDouble& val) const = 0;

    virtual void	applyInverseElementaryTransfo(IlDouble& val) const = 0;

    // Apply the logarithmic transformation depending on _logBase.

    void		applyLogTransfo(IlDouble& val) const;

    void		applyInverseLogTransfo(IlDouble& val) const;


    virtual IlBoolean	validateInterval(IlvCoordInterval& interval) const;

    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropClassInfo();

protected:
    IlUInt		_logBase;    // integer >= 0
    IlDouble		_logLogBase; // log(_logBase);

    inline IlDouble	getLogLogBase() const { return _logLogBase; }

    IlvChartCoordinateTransformer(IlUInt logBase);

    IlvChartCoordinateTransformer(const IlvChartCoordinateTransformer& t); 

    IlvChartCoordinateTransformer(IlvInputFile& file);
};

// --------------------------------------------------------------------------
// Class IlvSimpleChartTransformer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvSimpleChartTransformer
    : public IlvChartCoordinateTransformer
{
public:

    IlvSimpleChartTransformer(IlUInt logBase = 0);

    virtual ~IlvSimpleChartTransformer();

    // Specific methods.
    // Define the condition that is needed to be able to apply the
    // elementary transformation.
    virtual IlBoolean	condToApplyElementaryTransfo() const;

    virtual IlBoolean	condToApplyInverseElementaryTransfo() const;

    // Apply the elementary transformation: 
    // In the case of IlvSimpleChartTransformer, nothing is done.

    virtual void	applyElementaryTransfo(IlDouble& val) const;

    virtual void	applyInverseElementaryTransfo(IlDouble& val) const;

    DeclareCoordinateTransformerTypeInfoRO(IlvSimpleChartTransformer);
};

// --------------------------------------------------------------------------
// Class IlvAffineChartTransformer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAffineChartTransformer
    : public IlvChartCoordinateTransformer
{
public:

    IlvAffineChartTransformer(IlDouble multCoeff,
			      IlDouble constCoeff,
			      IlUInt logBase = 0);

    virtual ~IlvAffineChartTransformer();

    inline IlDouble	getMultCoeff() const { return _multCoeff; }

    inline void		setMultCoeff(IlDouble d) { _multCoeff = d; }

    inline IlDouble	getConstCoeff() const { return _constCoeff; }

    inline void		setConstCoeff(IlDouble d) { _constCoeff = d; }

    // Specific methods.
    // Define the condition that is needed to be able to apply the
    // elementary transformation.

    virtual IlBoolean	condToApplyElementaryTransfo() const;

    virtual IlBoolean	condToApplyInverseElementaryTransfo() const;

    // Apply the elementary transformation: 
    // In the case of IlvAffineChartTransformer, apply the affine 
    // transformation defined by _multCoeff and _constCoeff.

    virtual void	applyElementaryTransfo(IlDouble& val) const;

    virtual void	applyInverseElementaryTransfo(IlDouble& val) const;

    DeclareCoordinateTransformerTypeInfo(IlvAffineChartTransformer);

protected:
    IlDouble		_multCoeff;    // double != 0
    IlDouble		_constCoeff;
};

// --------------------------------------------------------------------------
// IlvCoordinateInfo persistence
// --------------------------------------------------------------------------
class IlvCoordinateInfo;
typedef IlvCoordinateInfo* (* IlvCoordinateInfoConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvCoordinateInfoClassInfo : public IlvValuedClassInfo
{
public:
    static IlvCoordinateInfoClassInfo* Create(const char*,
					      IlvClassInfo**,
					      IlvCoordinateInfoConstructor);

    inline
    IlvCoordinateInfoClassInfo*	getCoordinateInfoSuperClass() const
			{
			    return ILVDYNAMICCAST(IlvCoordinateInfoClassInfo*,
						  getSuperClass());
			}
    inline
    IlvCoordinateInfoConstructor	getConstructor() const
					{
					    return _constructor;
					}

protected:
    IlvCoordinateInfoClassInfo(const char* className,
			       IlvClassInfo** superClass,
			       IlvCoordinateInfoConstructor ctor)
    : IlvValuedClassInfo(className, superClass),
      _constructor(ctor)
    {}

    IlvCoordinateInfoConstructor _constructor;
};
#define IlvRegisterCoordinateInfoClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,			\
		IlvCoordinateInfoClassInfo::Create(	\
			#classname,			\
			ILVSUPERCLASSINFO(superclass),	\
			(IlvCoordinateInfoConstructor)classname::Read))

#define IlvPreRegisterCoordinateInfoClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvPostRegisterCoordinateInfoClass(classname, superclass) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname,		\
		IlvCoordinateInfoClassInfo::Create(	\
			#classname,			\
			ILVSUPERCLASSINFO(superclass),	\
			(IlvCoordinateInfoConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvCoordinateInfoStreamer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCoordinateInfoStreamer : public IlvReferenceStreamer
{
public:
    IlvCoordinateInfoStreamer();

    virtual void	writeReference(IlvOutputFile& os, IlAny coordInfoArg);
    virtual IlAny	readReference(IlvInputFile& is);
};

// --------------------------------------------------------------------------
// Class IlvCoordinateInfo
// --------------------------------------------------------------------------
class IlvCoordinateInfoListener;
class ILVCHTEXPORTED IlvCoordinateInfo : public IlvValueInterface
{
public:

    IlvCoordinateInfo(IlvCoordinateType coordinateType,
		      IlvCoordinateTransformer* transfo = 0);

    IlvCoordinateInfo(IlvCoordinateType coordinateType,
		      IlDouble dataMin,
		      IlDouble dataMax,
		      IlvCoordinateTransformer* transfo = 0);

    IlvCoordinateInfo(const IlvCoordinateInfo& coordinateInfo); 

    IlvCoordinateInfo(IlvInputFile& file);

    virtual ~IlvCoordinateInfo();

    // Accessors ============

    inline IlBoolean	isOnAbscissa() const 
			{
			    return _coordinateType == IlvAbscissaCoordinate;
			}

    inline IlBoolean	isOnOrdinate() const
			{
			    return _coordinateType == IlvOrdinateCoordinate;
			}

    inline
    IlvCoordinateType	getCoordinateType() const
			{
			    return _coordinateType;
			}

    inline void		setCoordinateType(IlvCoordinateType coordinateType)
			{
			    _coordinateType = coordinateType;
			}

    inline const	IlvCoordInterval& getAutoDataRange() const
			{
			    return _autoDataRange;
			}

    inline IlDouble	getAutoDataMin() const
			{
			    return getAutoDataRange().getMin();
			}

    inline IlDouble	getAutoDataMax() const
			{
			    return getAutoDataRange().getMax();
			}

    inline IlBoolean	isUsingAutoDataRange() const
			{
			    return _useAutoDataRange;
			}


    void		useAutoDataRange(IlBoolean b);

    inline
    const IlvCoordInterval&	getUserDataRange() const
				{
				    return _userDataRange;
				}

    inline IlDouble	getUserDataMin() const
			{
			    return getUserDataRange().getMin();
			}

    inline IlDouble	getUserDataMax() const
			{
			    return getUserDataRange().getMax();
			}

    virtual void	setUserDataRange(const IlvCoordInterval& range);

    void		setUserDataMin(IlDouble value);

    void		setUserDataMax(IlDouble value);

    inline const	IlvCoordInterval& getDataRange() const
			{
			    return _dataRange;
			}

    inline IlDouble	getDataMin() const { return getDataRange().getMin(); }

    inline IlDouble	getDataMax() const { return getDataRange().getMax(); }

    inline IlDouble	getMinPosData() const  { return _minPosData; }

    inline IlDouble	getMaxPosData() const  { return _maxPosData; }

    inline
    IlvCoordinateTransformer*	getTransformer() const { return _transfo; }

    void		setTransformer(IlvCoordinateTransformer* transfo);

    inline void		lock() { _refCount++; }

    void		unLock();

    IlBoolean		isInShiftMode() const;

    IlBoolean		isInCyclicMode() const;

    void		getFirstCycleRange(IlvCoordInterval& range) const;

    void		getSecondCycleRange(IlvCoordInterval& range) const;

    // Reset the used min and max to the automatically computed 
    // min and max data values.

    void		resetDataRangeToAuto();

    // Reset the used min and max to the values set by the user.

    void		resetDataRangeToUser();

    inline void		updateDueToTransformer(){}

    virtual IlvCoordinateInfo*	copy() const;

    // Persistence

    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvCoordinateInfo*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    static IlvCoordinateInfo*	Read(IlvInputFile& file);

    IlvDeclarePropRootClassInfo();

    // Internal use.
    // Should not be used directly by the user.

    virtual void	setDataRange(const IlvCoordInterval& range);

    void		setDataMin(IlDouble value);

    void		setDataMax(IlDouble value);

    void		updateAutoDataRange(const IlvCoordInterval& range);

    void		setAutoDataRange(const IlvCoordInterval& range);

    inline void		resetAutoDataRange() { _autoDataRange.set(0.0,0.0); }

    virtual void	setMinPosData(IlDouble value);

    virtual void	setMaxPosData(IlDouble value);

    void		addListener(IlvCoordinateInfoListener* listener);

    IlvCoordinateInfoListener*	removeListener(IlvCoordinateInfoListener* l);

    void		removeListeners();

    IlvCoordinateInfoListener* const*	getListeners(IlUInt& count) const;

    void		transformerChanged(const IlvCoordinateTransformer* old);

protected:
    IlUInt			_refCount;

    IlvCoordinateType           _coordinateType;
    IlvCoordInterval    	_autoDataRange;
    IlBoolean			_useAutoDataRange;
    IlvCoordInterval	        _userDataRange;
    IlvCoordInterval	        _dataRange;
    IlDouble			_minPosData;
    IlDouble			_maxPosData;

    IlvCoordinateTransformer*	_transfo;

    IlArray			_listeners;
    IlUInt			_lstLock;

    //== Does not perform notification
    inline void		_setDataRange(const IlvCoordInterval& range)
			{
			    IlBoolean cyclic = isInCyclicMode();
			    _dataRange = range;
			    if (!cyclic) {
				_minPosData = range.getMin();
				_maxPosData = range.getMax();
			    }
			}
};

// --------------------------------------------------------------------------
// Class IlvCoordinateInfoListener
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCoordinateInfoListener
{
public:
    IlvCoordinateInfoListener() {}
    virtual ~IlvCoordinateInfoListener();

    virtual IlBoolean	rangeChanged(IlvCoordinateInfo* coordInfo,
				     const IlvCoordInterval& oldRange);

    virtual void	transformerChanged(IlvCoordinateInfo* coordInfo,
					   const IlvCoordinateTransformer* old);
};

class ILVCHTEXPORTED IlvCoordInfoLstMap
{
public:
    IlvCoordInfoLstMap();
    IlvCoordInfoLstMap(const IlvCoordInfoLstMap& src);
    ~IlvCoordInfoLstMap();

    void		addListener(IlvCoordinateInfo* ds,
				    IlvCoordinateInfoListener* lst);
    void		removeListeners(IlvCoordinateInfo* ds,
					IlBoolean destroy = IlTrue);
private:
    IlAList*		_listeners;
};


class ILVCHTEXPORTED IlvCoordinateGroup 
{
public:
    IlvCoordinateGroup(IlUInt count, 
		       const IlvCoordinateInfo* const* coords,
		       IlDouble offsetRatio = 0.1);

    IlvCoordinateGroup(IlvInputFile& file);
    IlvCoordinateGroup(const IlvCoordinateGroup&);
    void		write(IlvOutputFile& file) const;

    void		getProjectorArea(const IlvRect& globalArea, 
					 const IlvCoordinateInfo* coordInfo,
					 IlvProjectorArea& projArea) const;
    void		removeCoordinate(const IlvCoordinateInfo* coord);
    void		insertCoordinate(const IlvCoordinateInfo* coord, 
					 IlUInt rank = IlvLastPositionIndex);
    void		replaceCoordinate(const IlvCoordinateInfo* oldCoord,
					  const IlvCoordinateInfo* newCoord);
    IlUInt		getCoordinateIndex(const IlvCoordinateInfo* c) const;

protected:
    IlList		_coordinates;
    IlDouble		_offsetRatio;
};

// --------------------------------------------------------------------------
// IlvAbstractProjector persistence
// --------------------------------------------------------------------------
class IlvAbstractProjector;
typedef IlvAbstractProjector* 
(* IlvProjectorConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvProjectorClassInfo : public IlvPropClassInfo
{
public:
    static IlvProjectorClassInfo* Create(const char*,
					 IlvClassInfo**,
					 IlvProjectorConstructor);

    inline
    IlvProjectorClassInfo*	getProjectorSuperClass() const
			{
			    return ILVDYNAMICCAST(IlvProjectorClassInfo*,
						  getSuperClass());
			}
    inline
    IlvProjectorConstructor	getConstructor() const { return _constructor; }
protected:
    IlvProjectorClassInfo(const char* className,
			  IlvClassInfo** superClass,
			  IlvProjectorConstructor ctor)
    : IlvPropClassInfo(className, superClass),
      _constructor(ctor)
    {}
    IlvProjectorConstructor _constructor;
};
#define IlvRegisterProjectorClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,				\
			  IlvProjectorClassInfo::Create(	\
			    #classname,				\
			    ILVSUPERCLASSINFO(superclass),	\
			    (IlvProjectorConstructor)classname::Read))

#define IlvPreRegisterProjectorClass(classname)			\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvPostRegisterProjectorClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
			      IlvProjectorClassInfo::Create(	\
				#classname,			\
				ILVSUPERCLASSINFO(superclass),	\
				(IlvProjectorConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvAbstractProjector
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAbstractProjector
{
public:

    // Not documented since it does nothing special.
    virtual ~IlvAbstractProjector();

    inline void		lock() { ++_refCount; }

    void		unLock();

    virtual void	getDataDisplayArea(const IlvProjectorArea& projArea,
					   IlvRect& dataArea) const = 0;

    // -------------------------------------------------------------
    // Methods to project the data into screen coordinates and 
    // inversely.
    // -------------------------------------------------------------

    // Project data points into positions.
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	dataPointsToDisplay(IlUInt pointCount,
				    const IlvDoublePoint* dataPoints,
				    IlvPoint* points,
				    const IlvProjectorArea& projArea,
				    const IlvCoordinateInfo* absInfo,
				    const IlvCoordinateInfo* ordInfo,
				    IlBoolean shiftOfCycleLength) const;

    // Inversely project the positions into the corresponding data 
    // points.
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	displayToDataPoints(IlUInt pointCount,
				    const IlvPoint* points,
				    IlvDoublePoint* dataPoints,	   
				    const IlvProjectorArea& projArea,
				    const IlvCoordinateInfo* absInfo,
				    const IlvCoordinateInfo* ordInfo,
				    IlBoolean shiftOfCycleLength) const;

    // Compute the clipping rectangle (clipRect) that contains the values
    // delimited by the specified bounding valuess (absRange, 
    // ordRange)
    // The clipRect is defined in the display system of coordinates.
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	boundingValuesToRect(const IlvProjectorArea& projArea,
				     const IlvCoordInterval& absRange,
				     const IlvCoordInterval& ordRange,
				     const IlvCoordinateInfo* absInfo,
				     const IlvCoordinateInfo* ordInfo,
				     IlvRect& clipRect) const = 0;

    // Compute from a clipping rectangle (clipRect), the bounding values 
    // of the values contained in this rectangle.
    // The clipRect is defined in the display system of coordinates.
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	rectToBoundingValues(const IlvProjectorArea& projArea,
				     const IlvRect& clipRect,
				     const IlvCoordinateInfo* absInfo,
				     const IlvCoordinateInfo* ordInfo,
				     IlvCoordInterval& absRange,
				     IlvCoordInterval& ordRange) const = 0;

    virtual
    IlBoolean	getGranularity(const IlvProjectorArea& projArea,
			       const IlvPoint& point,
			       const IlvCoordinateInfo* absInfo,
			       const IlvCoordinateInfo* ordInfo,
			       IlvDoublePoint& granularity) const;

    // Method to project axis values into screen coordinates
    // (coordinates in the display system of coordinates).
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	axisValuesToDisplay(IlvCoordinateType type,
				    IlUInt valuesCount,
				    const IlDouble* values,
				    IlvPoint* points,
				    const IlvProjectorArea& projArea,
				    IlDouble position,
				    const IlvCoordinateInfo* positionInfo,
				    const IlvCoordinateInfo* valueInfo) const;

#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	axisValuesToDisplay(IlvCoordinateType type,
				    IlUInt valuesCount,
				    const IlDouble* values,
				    IlvPoint* points,
				    const IlvProjectorArea& projArea,
				    IlvPos globalPosition,
				    const IlvCoordinateInfo* valueInfo) const;

#if DOCUMENTED_LATER
#endif
    virtual
    void	axisPositionsToDisplay(const IlvRect& dataDisplayArea,
				       IlvPos absAxisGlobalPosition,
				       IlvPos ordAxisGlobalPosition,
				       IlvPoint& crossingPoint) const;

    // ------------------------------------------------------------
    // Specific methods for drawing
    // ------------------------------------------------------------

    // Methods to treat the case of points that are before or after
    // the limits of the abscissa.

    // Project the point (named point) on the limit which is a line
    // passing through pointOnLimit. If nextPoint is defined the 
    // projected point corresponds to the intersection of the limit
    // and the line passing through point and nextPoint.
    // The result is returned in point. 
#if DOCUMENTED_LATER
#endif
    virtual
    void	projectPointOnAbscissaLimit(const IlvRect& dataDisplayArea,
					    const IlvPoint& pointOnLimit,
					    IlvPoint* point,
					    const IlvPoint* nextPt) const = 0;

    // Test if point is before pointOnLimit (which is a 
    // point on the abscissa limit).
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	isPointBeforeAbscissaLimit(const IlvRect& dataDisplayArea,
					   const IlvPoint& pointOnLimit,
					   const IlvPoint& point) const = 0;

    // Test if point is after pointOnLimit (which is a
    // point on the abscissa limit).
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	isPointAfterAbscissaLimit(const IlvRect& dataDisplayArea,
					  const IlvPoint& pointOnLimit,
					  const IlvPoint& point) const = 0;

#if DOCUMENTED_LATER
#endif
   virtual void	getMainOrdinateOrigin(const IlvRect& dataDisplayArea,
				      const IlvPoint& mainCrossingPoint,
				      IlvPoint& mainOrdinateOrigin) const = 0; 

#if DOCUMENTED_LATER
#endif
    virtual
    void	getOrigin(const IlvRect& ddArea, IlvPoint& origin) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    IlvDim	getAxisLength(const IlvRect& ddArea,
			      IlvCoordinateType type) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    void	getAxisGlobalPosition(const IlvRect& dataDisplayArea,
				      IlvAxisPosition relativePosition,
				      IlvPos offset,
				      IlvCoordinateType coordType,
				      IlvPos& globalPosition) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	getAngleInDegrees(IlDouble value,
				  const IlvCoordinateInfo* coordInfoForValue,
				  IlDouble& angleInDegrees) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    void	shiftAlongAxis(IlvCoordinateType type,
			       const IlvRect& dataDisplayArea,
			       IlvPoint& point,
			       IlvPos d) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    void	shiftAlongAxis(IlvCoordinateType type,
			       const IlvRect& dataDisplayArea,
			       IlvPoint& point,
			       const IlvPoint& pointTowardShift) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    void	expandAlongAxis(IlvCoordinateType type,
				IlvRect& rect,
				IlvPos delta) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    void	shiftInDirectionOfAxis(IlvCoordinateType type,
				       IlvPoint& p,
				       IlvPos delta,
				       IlDouble shiftAngle) const = 0;

    virtual IlvAbstractProjector*	copy() const = 0;

    // Persistence
    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvAbstractProjector*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const = 0;

    IlvDeclarePropRootClassInfo();

protected:
    IlUInt		_refCount;

    // Constructor
    IlvAbstractProjector();

    IlvAbstractProjector(const IlvAbstractProjector& projector);

    IlvAbstractProjector(IlvInputFile& file);

    // Internal methods
#if DOCUMENTED_LATER
#endif
    virtual
    void	projectPoints(IlUInt pointCount,
			      const IlvDoublePoint* dataPoints,
			      IlvPoint* points,
			      const IlvRect& dataDisplayArea,
			      IlDouble abscissaScaling,
			      IlDouble abscissaConstant,
			      IlDouble ordinateScaling,
			      IlDouble ordinateConstant,
			      IlDouble shiftLength) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    void	inverseProjectPoints(IlUInt pointCount,
				     const IlvPoint* points,
				     IlvDoublePoint* dataPoints,
				     const IlvRect& dataDisplayArea,
				     IlDouble invAbscissaScaling,
				     IlDouble invAbscissaConstant,
				     IlDouble invOrdinateScaling,
				     IlDouble invOrdinateConstant,
				     IlDouble shiftLength) const = 0;

    // Methods used inside the previous internal methods.
#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	computeMinMaxPos(const IlvProjectorArea& projArea,
				 const IlvCoordinateInfo* coordInfo,
				 IlDouble& coordMinPos,
				 IlDouble& coordMaxPos) const = 0;

#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	computeCoeff(const IlvCoordinateInfo* coordInfo,
			     IlDouble coordMinPos,
			     IlDouble coordMaxPos,
			     IlDouble& scaling,
			     IlDouble& constant,
			     const IlvProjectorArea& projArea) const;

#if DOCUMENTED_LATER
#endif
    virtual
    IlBoolean	computeInverseCoeff(const IlvCoordinateInfo* coordInfo,
				    IlDouble coordMinPos,
				    IlDouble coordMaxPos,
				    IlDouble& invScaling,
				    IlDouble& invConstant,
				    const IlvProjectorArea& projArea) const;

#if DOCUMENTED_LATER
#endif
    virtual
    void	convertToCartesian(const IlvRect& dataDisplayArea,
				   IlvDoublePoint& point) const;

#if DOCUMENTED_LATER
#endif
    virtual
    void	convertFromCartesian(const IlvRect& dataDisplayArea,
				     IlvDoublePoint& point) const;

    // Non virtual methods.
    void	internalComputeCoeff(IlDouble& scaling, 
				     IlDouble& constant,
				     IlDouble minValue,
				     IlDouble maxValue,
				     IlDouble minPos,
				     IlDouble maxPos) const;
    void	internalComputeInvCoeff(IlDouble& invScaling, 
					IlDouble& invConstant,
					IlDouble minValue,
					IlDouble maxValue,
					IlDouble minPos,
					IlDouble maxPos) const;
    void	applyCoeffToPoint(IlDouble abscissaScaling, 
				  IlDouble abscissaConstant,
				  IlDouble ordinateScaling,
				  IlDouble ordinateConstant,
				  IlvDoublePoint& point) const;
    IlBoolean	getMinMaxPosDataTransformed(const IlvCoordinateInfo* coordInfo,
					    IlDouble& minTransformed,
					    IlDouble& maxTransformed) const;
    IlBoolean	getDataRangeTransformed(const IlvCoordinateInfo* coordInfo,
					IlvCoordInterval& range) const;

    IlBoolean	getUserDataRangeTransformed(const IlvCoordinateInfo* coordInfo,
					    IlvCoordInterval& range) const;

    IlBoolean	getCycleValuesTransformed(const IlvCoordinateInfo* coordInfo,
					  IlDouble& minCycleTransformed,
					  IlDouble& maxCycleTransformed) const;

    void	internalProjectPoints(IlUInt pointCount,
				      const IlvDoublePoint* dataPoints,
				      IlvPoint* points,
				      const IlvRect& dataDisplayArea,
				      IlDouble abscissaScaling,
				      IlDouble abscissaConstant,
				      IlDouble ordinateScaling,
				      IlDouble ordinateConstant,
				      IlDouble shiftLength,
				      IlBoolean invertCoord) const;

    void	internalInvProjectPoints(IlUInt pointCount,
					 const IlvPoint* points,
					 IlvDoublePoint* dataPoints,
					 const IlvRect& dataDisplayArea,
					 IlDouble invAbscissaScaling,
					 IlDouble invAbscissaConstant,
					 IlDouble invOrdinateScaling,
					 IlDouble invOrdinateConstant,
					 IlDouble shiftLength,
					 IlBoolean invertCoord) const;
};

// --------------------------------------------------------------------------
// Class IlvCartesianProjector
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCartesianProjector : public IlvAbstractProjector
{
public:
    enum Orientation {
	IlvXRightYTop = 0,
	IlvXRightYBottom,
	IlvXTopYRight,
	IlvXBottomYRight,
	IlvXLeftYTop,
	IlvXLeftYBottom,
	IlvXTopYLeft,
	IlvXBottomYLeft
    };

    IlvCartesianProjector(Orientation orientation = IlvXRightYTop);

    // Not documented since it does nothing.
    virtual ~IlvCartesianProjector();

    // Accessors
    inline Orientation	getOrientation() const { return _orientation; }
    inline void		setOrientation(Orientation orientation) 
			{
			    _orientation = orientation;
			}

    virtual void	getDataDisplayArea(const IlvProjectorArea& projArea,
					   IlvRect& dataArea) const;

    // -------------------------------------------------------------
    // Methods to project the data into screen coordinates and
    // inversely.
    // -------------------------------------------------------------

    // Compute the clipping rectangle that contains the values 
    // delimited by the specified bounding values (abscissaMin, 
    // abscissaMax, ordinateMin and ordinateMax).
    // The clipRect is defined in the display system of coordinates.

    virtual
    IlBoolean	boundingValuesToRect(const IlvProjectorArea& projArea,
				     const IlvCoordInterval& absRange,
				     const IlvCoordInterval& ordRange,
				     const IlvCoordinateInfo* absInfo,
				     const IlvCoordinateInfo* ordInfo,
				     IlvRect& clipRect) const;
    // Compute from a clipping rectangle, the bounding values of the 
    // values contained in this rectangle.
    // The clipRect is defined in the display system of coordinates.

    virtual
    IlBoolean	rectToBoundingValues(const IlvProjectorArea& projArea,
				     const IlvRect& clipRect,
				     const IlvCoordinateInfo* absInfo,
				     const IlvCoordinateInfo* ordInfo,
				     IlvCoordInterval& absRange,
				     IlvCoordInterval& ordRange) const;

    // Methods to treat the case of points that are before or after
    // limits of the abscissa.

    // Project the point (named point) on the abscissa limit which 
    // is a line passing through pointOnLimit.
    // If nextPoint is defined the projected point corresponds to 
    // the intersection of the limit and the line passing through
    // point and nextPoint. 
    // The result is returned in point. 

    virtual
    void	projectPointOnAbscissaLimit(const IlvRect& dataDisplayArea,
					    const IlvPoint& pointOnLimit,
					    IlvPoint* point,
					    const IlvPoint* nextPoint) const;

    // Test if point is before pointOnLimit (which is a 
    // point on the abscissa limit).

    virtual
    IlBoolean	isPointBeforeAbscissaLimit(const IlvRect& dataDisplayArea,
					   const IlvPoint& pointOnLimit,
					   const IlvPoint& point) const;

    // Test if point is after pointOnLimit (which is a
    // point on the abscissa limit).

    virtual
    IlBoolean	isPointAfterAbscissaLimit(const IlvRect& dataDisplayArea,
					  const IlvPoint& pointOnLimit,
					  const IlvPoint& point) const;

    virtual
    void	getMainOrdinateOrigin(const IlvRect& dataDisplayArea,
				      const IlvPoint& mainCrossingPoint,
				      IlvPoint& mainOrdinateOrigin) const;

    virtual
    void	getOrigin(const IlvRect& ddArea, IlvPoint& origin) const;

    virtual
    IlvDim	getAxisLength(const IlvRect& ddArea,
			      IlvCoordinateType type) const;

    virtual
    void	getAxisGlobalPosition(const IlvRect& dataDisplayArea,
				      IlvAxisPosition relativePosition,
				      IlvPos offset,
				      IlvCoordinateType coordType,
				      IlvPos& globalPosition) const;

    virtual
    IlBoolean	getAngleInDegrees(IlDouble value,
				  const IlvCoordinateInfo* coordInfoForValue,
				  IlDouble& angleInDegrees) const;

    virtual
    void	shiftAlongAxis(IlvCoordinateType type,
			       const IlvRect& dataDisplayArea,
			       IlvPoint& point,
			       IlvPos d) const;

    virtual
    void	shiftAlongAxis(IlvCoordinateType type,
			       const IlvRect& dataDisplayArea,
			       IlvPoint& point,
			       const IlvPoint& pointTowardShift) const;

    virtual
    void	expandAlongAxis(IlvCoordinateType type,
				IlvRect& rect,
				IlvPos delta) const;

    virtual
    void	shiftInDirectionOfAxis(IlvCoordinateType type,
				       IlvPoint& p,
				       IlvPos delta,
				       IlDouble shiftAngle) const;

    DeclareProjectorTypeInfo(IlvCartesianProjector);

protected:
    Orientation		_orientation;

    // Internal methods

    virtual
    void	projectPoints(IlUInt pointCount,
			      const IlvDoublePoint* dataPoints,
			      IlvPoint* points,
			      const IlvRect& dataDisplayArea,
			      IlDouble abscissaScaling,
			      IlDouble abscissaConstant,
			      IlDouble ordinateScaling,
			      IlDouble ordinateConstant,		  
			      IlDouble shiftLength) const;

    virtual
    void	inverseProjectPoints(IlUInt pointCount,
				     const IlvPoint* points,
				     IlvDoublePoint* dataPoints,
				     const IlvRect& dataDisplayArea,
				     IlDouble invAbscissaScaling,
				     IlDouble invAbscissaConstant,
				     IlDouble invOrdinateScaling,
				     IlDouble invOrdinateConstant,
				     IlDouble shiftLength) const;

    // Methods used inside the previous internal methods.

    virtual
    IlBoolean	computeMinMaxPos(const IlvProjectorArea& projArea,
				 const IlvCoordinateInfo* coordInfo,
				 IlDouble& coordMinPos,
				 IlDouble& coordMaxPos) const;
};

// --------------------------------------------------------------------------
// Class IlvPolarProjector
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPolarProjector : public IlvAbstractProjector
{
public:
    IlvPolarProjector(IlDouble startingAngle = 0.0,
		      IlBoolean orientedClockwise = IlFalse);

    IlvPolarProjector(IlDouble startingAngle,
		      IlDouble range,
		      IlBoolean orientedClockwise);

    // Not documented since it does nothing special.
    virtual ~IlvPolarProjector();

    // Accessors
    inline IlDouble	getStartingAngle() const { return _startingAngle; }
    inline void		setStartingAngle (IlDouble angle)
			{
			    _startingAngle = angle;
			}

    inline IlDouble	getRange() const { return _range; }

    inline void		setRange(IlDouble range) { _range = range; }

    inline IlBoolean	getOrientedClockwise() const
			{
			    return _orientedClockwise;
			}

    inline void		setOrientedClockwise(IlBoolean b)
			{
			    _orientedClockwise = b;
			}


    virtual void	getDataDisplayArea(const IlvProjectorArea& projArea,
					   IlvRect& dataArea) const;

    // -------------------------------------------------------------
    // Methods to project data into screen coordinates and 
    // inversely.
    // -------------------------------------------------------------

    // Compute the clipping rectangle that contains the values 
    // delimited by the  specified bounding values (abscissaMin,
    // abscissaMax, ordinateMin and ordinateMax).
    // The clipRect is defined in the display system of coordinates.

    virtual
    IlBoolean	boundingValuesToRect(const IlvProjectorArea& projArea,
				     const IlvCoordInterval& absRange,
				     const IlvCoordInterval& ordRange,
				     const IlvCoordinateInfo* absInfo,
				     const IlvCoordinateInfo* ordInfo,
				     IlvRect& clipRect) const;
    // Compute from a clipping rectangle, the bounding values of the 
    // values contained in this rectangle.
    // The clipRect is defined in the display system of coordinates.

    virtual
    IlBoolean	rectToBoundingValues(const IlvProjectorArea& projArea,
				     const IlvRect& clipRect,
				     const IlvCoordinateInfo* absInfo,
				     const IlvCoordinateInfo* ordInfo,
				     IlvCoordInterval& absRange,
				     IlvCoordInterval& ordRange) const;

    // Methods to treat the case of points that are before or after
    // limits of the abscissa.

    // Project the point (named point) on the abscissa limit which
    // is a line passing through pointOnLimit.
    // If nextPoint is defined the projected point corresponds to
    // the intersection of the limit and the line passing through
    // point and nextPoint.
    // The result is returned in point.

    virtual
    void	projectPointOnAbscissaLimit(const IlvRect& dataDisplayArea,
					    const IlvPoint& pointOnLimit,
					    IlvPoint* point,
					    const IlvPoint* nextPoint) const;

    // Test if point is before pointOnLimit (which is a
    // point on the abscissa limit).

    virtual
    IlBoolean	isPointBeforeAbscissaLimit(const IlvRect& dataDisplayArea,
					   const IlvPoint& pointOnLimit,
					   const IlvPoint& point) const;

    // Test if point is after pointOnLimit (which is a
    // point on the abscissa limit).

    virtual
    IlBoolean	isPointAfterAbscissaLimit(const IlvRect& dataDisplayArea,
					  const IlvPoint& pointOnLimit,
					  const IlvPoint& point) const;

    virtual
    void	getMainOrdinateOrigin(const IlvRect& dataDisplayArea,
				      const IlvPoint& mainCrossingPoint,
				      IlvPoint& mainOrdinateOrigin) const;

    virtual
    void	getOrigin(const IlvRect& ddArea, IlvPoint& origin) const;

    virtual
    IlvDim	getAxisLength(const IlvRect& ddArea,
			      IlvCoordinateType type) const;

    virtual
    void	getAxisGlobalPosition(const IlvRect& dataDisplayArea,
				      IlvAxisPosition relativePosition,
				      IlvPos offset,
				      IlvCoordinateType coordType,
				      IlvPos& globalPosition) const;

    virtual
    IlBoolean	getAngleInDegrees(IlDouble value,
				  const IlvCoordinateInfo* coordInfoForValue,
				  IlDouble& angleInDegrees) const;

    virtual
    void	shiftAlongAxis(IlvCoordinateType type,
			       const IlvRect& dataDisplayArea,
			       IlvPoint& point,
			       IlvPos d) const;

    virtual
    void	shiftAlongAxis(IlvCoordinateType type,
			       const IlvRect& dataDisplayArea,
			       IlvPoint& point,
			       const IlvPoint& pointTowardShift) const;

    virtual
    void	expandAlongAxis(IlvCoordinateType type,
				IlvRect& rect,
				IlvPos delta) const;

    virtual
    void	shiftInDirectionOfAxis(IlvCoordinateType type,
				       IlvPoint& p,
				       IlvPos delta,
				       IlDouble shiftAngle) const;

    inline IlBoolean	isSymmetric() const {return _symmetric; }
    inline void		setSymmetric(IlBoolean b) {_symmetric = b; }

    DeclareProjectorTypeInfo(IlvPolarProjector);

protected:
    IlDouble	_startingAngle;
    IlDouble	_range;
    IlBoolean	_orientedClockwise;
    IlBoolean	_symmetric;

    // Internal methods

    virtual
    void	projectPoints(IlUInt pointCount,
			      const IlvDoublePoint* dataPoints,
			      IlvPoint* points,
			      const IlvRect& dataDisplayArea,
			      IlDouble abscissaScaling,
			      IlDouble abscissaConstant,
			      IlDouble ordinateScaling,
			      IlDouble ordinateConstant,		  
			      IlDouble shiftLength) const;

    virtual
    void	inverseProjectPoints(IlUInt pointCount,
				     const IlvPoint* points,
				     IlvDoublePoint* dataPoints,
				     const IlvRect& dataDisplayArea,
				     IlDouble invAbscissaScaling,
				     IlDouble invAbscissaConstant,
				     IlDouble invOrdinateScaling,
				     IlDouble invOrdinateConstant,
				     IlDouble shiftLength) const;

    // Methods used by the previous internal methods.
    virtual
    IlBoolean	computeMinMaxPos(const IlvProjectorArea& projArea,
				 const IlvCoordinateInfo* coordInfo,
				 IlDouble& coordMinPos,
				 IlDouble& coordMaxPos) const;

    virtual
    IlBoolean	computeCoeff(const IlvCoordinateInfo* coordInfo,
			     IlDouble coordMinPos,
			     IlDouble coordMaxPos,
			     IlDouble& scaling,
			     IlDouble& constant,
			     const IlvProjectorArea& projArea) const;
    virtual
    IlBoolean	computeInverseCoeff(const IlvCoordinateInfo* coordInfo,
				    IlDouble coordMinPos,
				    IlDouble coordMaxPos,
				    IlDouble& invScaling,
				    IlDouble& invConstant,
				    const IlvProjectorArea& projArea) const;
    virtual
    void	convertToCartesian(const IlvRect& dataDisplayArea,
				   IlvDoublePoint& point) const;
    virtual
    void	convertFromCartesian(const IlvRect& dataDisplayArea,
				     IlvDoublePoint& point) const;
};


ILVCHTMODULEINIT(common);

#endif /* !__Ilv_Charts_Common_H */
