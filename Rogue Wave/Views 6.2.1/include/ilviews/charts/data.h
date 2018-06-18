// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/data.h
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
// Declaration of the classes involved in the management of the data.
// The data that we want to represent with a chart are split into data sets.
// A data set which will be represented with a "curve" is represented
// by a IlvChartDataSet.
// Contains:
//  - IlvChartDataPointInfo: a class used to add specific information to
//    a given data point: specially a palette.
//  - IlvChartDataGraphicInfo: a subclass of IlvChartDataPointInfo which
//    allows you to add a graphic object to a given data point.
//  - IlvChartDataPointLabel: a subclass of IlvChartDataGraphicInfo which
//    allows you to annotate a data point with a label displaying the data
//    point values.
//
//  - IlvPointInfoCollection: an abstract class that manage all the
//    IlvChartDataPointInfo for a IlvChartDataSet.
//  - IlvPointInfoMap: a subclass of IlvPointInfoCollection which stores
//    the IlvChartDataPointInfo objects in an array and also keeps an array of
//    the indexes of the data points with which these objects are associated.
//  - IlvPointInfoArray: a subclass of IlvPointInfoCollection which stores
//    IlvChartDataPointInfo objects for each data point of a data set in an
//    array.
//  - IlvPointInfoSingleton: a subclass of IlvPointInfoCollection which
//    stores a unique IlvChartDataPointInfo instance for all the data
//    points of a data set.
//
//  - IlvChartDataSetListener: a class used to propagate all the
//    modifications made on a data set to all the objects that use it.
//  - IlvChartDSLstMap: a class used to keep a correspondance between a
//    data set and each of its listeners.
//
//  - IlvChartDataSet: an abstract class which manages a set of values
//    which will be represented by a "curve".
//
//  - IlvChartDataSetCollection: a class used to handle a collection of
//    data sets.
//
//  - IlvCombinedChartDataSet: an abstract class which is a subclass of
//    IlvChartDataSet. This class allows you to define a data set which is a
//    combination of other data sets.
//  - IlvAddChartDataSet: a subclass of IlvCombinedChartDataSet which
//    performs the addition of several data sets.
//  - IlvHiLoChartDataSet: a subclass of IlvCombinedChartDataSet which
//    is used by the high low chart displayer.
//  - IlvPieChartDataSet: a subclass of IlvCombinedChartDataSet which is
//    used by a pie chart displayer.
//
//  - IlvChartPointSet: a subclass of IlvChartDataSet which stores an array
//    of IlvDoublePoint.
//  - IlvChartYValueSet: a subclass of IlvChartDataSet which stores an array
//    of IlDouble. The abscissa of the data point is supposed to be
//    the index of the stored data.
//  - IlvAbstractChartFunction: a subclass of IlvChartDataSet which allows
//    to define a set of values with a function of the following type:
//    ordinate = function(abscissa).
//  - IlvCallbackChartFunction: a subclass of IlvAbstractChartFunction
//    which allows you to define a set of values with a function defined by a
//    callback.
//
//  - IlvChartDataListener: a class used to propagate all the
//    modifications made on an IlvAbstractChartData object (or one of its
//    derived objects) to all the objects that use it.
//
//  - IlvAbstractChartData: an abstract class which allows you to manage
//    all the data of a chart. This class manages a set of IlvChartDataSet.
//    Each IlvChartDataSet will be represented by a different "curve".
//  - IlvMemoryChartData: a subclass of IlvAbstractChartData which stores the
//    data in memory (in an array).
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Data_H
#define __Ilv_Charts_Data_H

#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Charts_Common_H)
#include <ilviews/charts/common.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Chart_H)
#include <ilviews/charts/chart.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif

class IlvAbstractChartData;
class IlvChartGraphic;

// --------------------------------------------------------------------------
// IlvChartDataPointInfo persistence
// --------------------------------------------------------------------------
class IlvChartDataPointInfo;
typedef IlvChartDataPointInfo*
    (*IlvChartDataPointInfoConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvChartDataPointInfoClassInfo : public IlvPropClassInfo
{
public:
    static IlvChartDataPointInfoClassInfo*
	Create(const char*, IlvClassInfo**, IlvChartDataPointInfoConstructor);

    inline
    IlvChartDataPointInfoClassInfo*	getChartDataPointInfoSuperClass() const
	{
	    return ILVDYNAMICCAST(IlvChartDataPointInfoClassInfo*,
				  getSuperClass());
	}
    inline
    IlvChartDataPointInfoConstructor	getConstructor() const
					{
					    return _constructor;
					}

protected:
    IlvChartDataPointInfoConstructor _constructor;

    IlvChartDataPointInfoClassInfo(const char* className,
				   IlvClassInfo** superClass,
				   IlvChartDataPointInfoConstructor cstor)
	: IlvPropClassInfo(className, superClass),
	  _constructor(cstor)
	{}
};
#define IlvRegisterChartDataPointInfoClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
    IlvChartDataPointInfoClassInfo::Create(#classname,			\
		    ILVSUPERCLASSINFO(superclass),			\
		    (IlvChartDataPointInfoConstructor)classname::Read))
#define IlvPreRegisterChartDataPointInfoClass(classname)		\
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterChartDataPointInfoClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
    IlvChartDataPointInfoClassInfo::Create(#classname,			\
		    ILVSUPERCLASSINFO(superclass),			\
		    (IlvChartDataPointInfoConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvChartDataPointInfo
// --------------------------------------------------------------------------
class IlvChartDataSet;
class IlvAbstractChartDisplayer;

class ILVCHTEXPORTED IlvChartDataPointInfo
{
public:
    friend class IlvPointInfoCollection;
    friend class IlvPointInfoMap;
    friend class IlvPointInfoArray;

    IlvChartDataPointInfo(IlvPalette* palette = 0);

    IlvChartDataPointInfo(const IlvChartDataPointInfo& pointInfo);

    IlvChartDataPointInfo(IlvInputFile& file);

    virtual ~IlvChartDataPointInfo();

    inline IlvPalette*	getPalette() const { return _palette; }

    virtual IlBoolean	getPalette(const IlvChartDataSet* dataSet,
				   IlUInt idx,
				   const IlvAbstractChartDisplayer* disp,
				   const IlvPalette* defaultPalette,
				   IlvPalette* returnPalette) const;

    void		setPalette(IlvPalette* pal);

    void		setForeground(IlvColor* color);

    inline void		lock() { _refCount++; }

    inline void		unLock() { if (!--_refCount) delete this; }

    virtual void	draw(const IlvPoint&		point,
			     const IlvChartDataSet*	dataSet,
			     IlUInt			ptidx,
			     const IlvChartGraphic*	chart,
			     IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;

    virtual IlBoolean	boundingBox(const IlvPoint&		point,
				    const IlvChartDataSet*	dataSet,
				    IlUInt			ptidx,
				    const IlvChartGraphic*	chart,
				    IlvRect&			bbox,
				    const IlvTransformer*	t = 0) const;

    virtual void	setOverwrite(IlBoolean o);

    virtual void	setMode(IlvDrawMode mode);

    virtual IlvChartDataPointInfo*	copy() const;

    // Persistence

    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvChartDataPointInfo*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    static IlvChartDataPointInfo*	Read(IlvInputFile& file);

    IlvDeclarePropRootClassInfo();

protected:
    IlUInt		_refCount;
    IlvPalette*		_palette;

//     const IlvPointInfoCollection* _collection;

//     void setCollection(const IlvPointInfoCollection* c) { _collection = c; }
//     const IlvPointInfoCollection* getCollection() { return _collection; }

};

class ILVCHTEXPORTED IlvChartDataGraphicInfo : public IlvChartDataPointInfo
{
public:
    IlvChartDataGraphicInfo(IlvGraphic*	graphic,
			    IlvPos	dx = 0,
			    IlvPos	dy = 0,
			    IlvPosition anchorPosition = IlvCenter,
			    IlvPalette* palette = 0);
    virtual ~IlvChartDataGraphicInfo();

    virtual void	draw(const IlvPoint&		point,
			     const IlvChartDataSet*	dataSet,
			     IlUInt			ptidx,
			     const IlvChartGraphic*	chart,
			     IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual IlBoolean	boundingBox(const IlvPoint&		point,
				    const IlvChartDataSet*	dataSet,
				    IlUInt			ptidx,
				    const IlvChartGraphic*	chart,
				    IlvRect&			bbox,
				    const IlvTransformer*	t = 0) const;

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode mode);

    inline IlvGraphic*	getGraphic() const { return _graphic; }

    void		setGraphic(IlvGraphic* graphic);

    inline
    const IlvPoint&	getOffset() const { return _offset; }

    inline void		setOffset(const IlvPoint& offset) { _offset = offset; }

    inline IlvPosition	getAnchorPosition() const { return _position; }

    inline void		setAnchorPosition(IlvPosition position) 
			{
			    _position = position;
			}

    DeclareChartDataPointInfoTypeInfo(IlvChartDataGraphicInfo);

protected:
    IlvGraphic*		_graphic;
    IlvPoint		_offset;
    IlvPosition		_position;

    void	computeGraphicTransformer(const IlvPoint&	point,
					  const IlvChartDataSet* data,
					  IlUInt		ptidx,
					  const IlvChartGraphic* chart,
					  IlvTransformer&	tt,
					  const IlvTransformer*	t = 0) const;
};


class IlvLabel;
class ILVCHTEXPORTED IlvChartDataPointLabel : public IlvChartDataGraphicInfo
{
public:
    enum AnnotationMode {
	YValue = 0,
	XValue,
	XYValues
    };

    IlvChartDataPointLabel(IlvDisplay* display,
			   IlvPos dx = 0,
			   IlvPos dy = 0,
			   IlvPosition position = IlvCenter,
			   AnnotationMode mode=IlvChartDataPointLabel::YValue,
			   const char* format = "%g",
			   IlvPalette* palette = 0);

    AnnotationMode	getAnnotationMode() const { return _mode;}

    void		setAnnotationMode(AnnotationMode mode) { _mode = mode;}

    inline const char*	getAnnotationFormat() const
			{
			    return _format.isEmpty()
				? (const char*)0
				: (const char*)_format;
			}

    inline void		setAnnotationFormat(const char* f) { _format = f; }

    virtual void	draw(const IlvPoint&		point,
			     const IlvChartDataSet*	dataSet,
			     IlUInt			ptidx,
			     const IlvChartGraphic*	chart,
			     IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;

    virtual IlBoolean	boundingBox(const IlvPoint&	point,
				    const IlvChartDataSet* dataSet,
				    IlUInt		ptidx,
				    const IlvChartGraphic* chart,
				    IlvRect&		bbox,
				    const IlvTransformer* t = 0) const;

    DeclareChartDataPointInfoTypeInfo(IlvChartDataPointLabel);

protected:
    AnnotationMode	_mode;
    IlString		_format;

    IlvLabel*		getLabel() const;
    virtual void	computeDataLabel(const IlvChartDataSet* dataSet,
					 IlUInt ptidx) const;
};


// --------------------------------------------------------------------------
// Class IlvChartGradientPointInfo
// --------------------------------------------------------------------------

class ILVCHTEXPORTED IlvChartGradientPointInfo : public IlvChartDataPointInfo
{
public:
    IlvChartGradientPointInfo(IlDouble* values, const IlArray& colors);

    IlvChartGradientPointInfo(const IlvChartGradientPointInfo& pointInfo);

    IlvChartGradientPointInfo(IlvInputFile& file);

    virtual ~IlvChartGradientPointInfo();

    virtual IlBoolean	getPalette(const IlvChartDataSet* dataSet,
				   IlUInt		idx,
				   const IlvAbstractChartDisplayer* disp,
				   const IlvPalette*	defaultPalette,
				   IlvPalette*		returnPalette) const;

protected:
    void		setGradientColors();
    IlvColor*		getColor(const IlvChartDataSet*	dataSet,
				 IlUInt idx,
				 IlvDisplay*) const;

    int			getColorIdxForValue(int lidx,
					    int hidx,
					    double value) const;

    IlDouble*		_values; // IlvChartDoubleArray
    IlArray		_colors;
    IlInt*		_dg;
    IlInt*		_db;
    IlInt*		_dr;
};


// --------------------------------------------------------------------------
// IlvPointInfoCollection persistence
// --------------------------------------------------------------------------
class IlvPointInfoCollection;
typedef IlvPointInfoCollection*
(* IlvPointInfoCollectionConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvPointInfoCollectionClassInfo : public IlvPropClassInfo
{
public:
    static IlvPointInfoCollectionClassInfo*
		Create(const char*,
		       IlvClassInfo**,
		       IlvPointInfoCollectionConstructor);

    inline
    IlvPointInfoCollectionClassInfo* getPointInfoCollectionSuperClass() const
	{
	    return ILVDYNAMICCAST(IlvPointInfoCollectionClassInfo*,
				  getSuperClass());
	}
    inline IlvPointInfoCollectionConstructor	getConstructor() const
						{
						    return _constructor;
						}
protected:
    IlvPointInfoCollectionConstructor		_constructor;

    IlvPointInfoCollectionClassInfo(const char*	    className,
				    IlvClassInfo**  superClass,
				    IlvPointInfoCollectionConstructor c)
	: IlvPropClassInfo(className, superClass),
	  _constructor(c) {}
};
#define IlvRegisterPointInfoCollectionClass(classname, superclass)     	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	    IlvPointInfoCollectionClassInfo::Create(#classname,		\
		    ILVSUPERCLASSINFO(superclass),			\
		    (IlvPointInfoCollectionConstructor)classname::Read))
#define IlvPreRegisterPointInfoCollectionClass(classname)		\
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterPointInfoCollectionClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	    IlvPointInfoCollectionClassInfo::Create(#classname,		\
		    ILVSUPERCLASSINFO(superclass),			\
		    (IlvPointInfoCollectionConstructor)classname::Read))

// --------------------------------------------------------------------------
// IlvPointInfoCollection
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPointInfoCollection
{
public:
    virtual ~IlvPointInfoCollection();

    virtual IlUInt	getPointInfoCount() const = 0;

    // API

    inline void		lock() { _refCount++; }

    void		unLock();

    virtual IlvChartDataPointInfo*	getPointInfo(IlUInt idx) const = 0;

    virtual IlvChartDataPointInfo*	getInfoForPoint(IlUInt pidx) const = 0;

    virtual void	setPointInfo(IlUInt ptidx,
				     IlvChartDataPointInfo* ptInfo,
				     IlBoolean copy = IlFalse) = 0;

    virtual IlBoolean	removePointInfo(IlUInt ptidx) = 0;

    virtual void	removeAllPointInfo() = 0;


    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);

    virtual IlvPointInfoCollection*	copy() const = 0;

    // Persistence
    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvPointInfoCollection*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const = 0;

    IlvDeclarePropRootClassInfo();

protected:
    IlUInt		_refCount;

    // Constructors
    IlvPointInfoCollection();

    IlvPointInfoCollection(const IlvPointInfoCollection& pointInfo);

    IlvPointInfoCollection(IlvInputFile& file);
};

// --------------------------------------------------------------------------
// IlvPointInfoMap
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPointInfoMap : public IlvPointInfoCollection
{
public:
    IlvPointInfoMap();

    virtual ~IlvPointInfoMap();

    virtual IlUInt	getPointInfoCount() const;

    virtual IlvChartDataPointInfo*	getInfoForPoint(IlUInt ptidx) const;
    virtual IlvChartDataPointInfo*	getPointInfo(IlUInt idx) const;
    virtual void	setPointInfo(IlUInt ptidx,
				     IlvChartDataPointInfo* ptInfo,
				     IlBoolean copy = IlFalse);

    virtual IlBoolean	removePointInfo(IlUInt ptidx);
    virtual void	removeAllPointInfo();

    DeclarePointInfoCollectionTypeInfo(IlvPointInfoMap);

protected:
    IlBoolean findPointInfoIndex(IlUInt,IlUInt&) const;

    IlArray		_pointInfoArray;
    IlvChartUIntArray	_ptIndexes;
};

// --------------------------------------------------------------------------
// IlvPointInfoArray
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPointInfoArray : public IlvPointInfoCollection
{
public:
    IlvPointInfoArray();

    virtual ~IlvPointInfoArray();

    virtual IlUInt	getPointInfoCount() const;

    virtual IlvChartDataPointInfo*	getInfoForPoint(IlUInt ptidx) const;
    virtual IlvChartDataPointInfo*	getPointInfo(IlUInt idx) const;

    virtual void	setPointInfo(IlUInt ptidx,
				     IlvChartDataPointInfo* ptInfo,
				     IlBoolean copy = IlFalse);

    virtual IlBoolean	removePointInfo(IlUInt ptidx);
    virtual void	removeAllPointInfo();

    DeclarePointInfoCollectionTypeInfo(IlvPointInfoArray);

protected:
    IlArray		_pointInfoArray;
};


// --------------------------------------------------------------------------
// IlvPointInfoSingleton
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPointInfoSingleton : public IlvPointInfoCollection
{
public:
    IlvPointInfoSingleton(IlvChartDataPointInfo* singleton = 0);

    void		setSingleton(IlvChartDataPointInfo* singleton);

    inline
    IlvChartDataPointInfo*	getSingleton() const
				{
				    return _singleton;
				}

    virtual ~IlvPointInfoSingleton();

    virtual IlUInt	getPointInfoCount() const;


    virtual IlvChartDataPointInfo*	getInfoForPoint(IlUInt ptidx) const;
    virtual IlvChartDataPointInfo*	getPointInfo(IlUInt idx) const;

    virtual void	setPointInfo(IlUInt ptidx,
				     IlvChartDataPointInfo* ptInfo,
				     IlBoolean copy = IlFalse);

    virtual IlBoolean	removePointInfo(IlUInt ptidx);

    virtual void	removeAllPointInfo();

    DeclarePointInfoCollectionTypeInfo(IlvPointInfoSingleton);

protected:
    IlvChartDataPointInfo*	_singleton;
};


// --------------------------------------------------------------------------
// IlvChartDataSet persistence
// --------------------------------------------------------------------------
class IlvChartDataSet;
typedef IlvChartDataSet* (* IlvChartDataSetConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvChartDataSetClassInfo : public IlvValuedClassInfo
{
public:
    static IlvChartDataSetClassInfo*
		Create(const char*,
		       IlvClassInfo**,
		       IlvChartDataSetConstructor);

    inline
    IlvChartDataSetClassInfo* getChartDataSetSuperClass() const
		{
		    return ILVDYNAMICCAST(IlvChartDataSetClassInfo*,
					  getSuperClass());
		}
    inline
    IlvChartDataSetConstructor	getConstructor() const
				{
				    return _constructor;
				}
protected:
    IlvChartDataSetConstructor _constructor;

    IlvChartDataSetClassInfo(const char*    className,
			     IlvClassInfo** superClass,
			     IlvChartDataSetConstructor constructor)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(constructor)
	{}
};
#define IlvRegisterChartDataSetClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,				\
    IlvChartDataSetClassInfo::Create(#classname,		\
		    ILVSUPERCLASSINFO(superclass),		\
		    (IlvChartDataSetConstructor)classname::Read))
#define IlvPreRegisterChartDataSetClass(classname)		\
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterChartDataSetClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
    IlvChartDataSetClassInfo::Create(#classname,		\
		    ILVSUPERCLASSINFO(superclass),		\
		    (IlvChartDataSetConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvChartDataSetListener
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDataSetListener
{
public:
    virtual ~IlvChartDataSetListener();

    virtual void	dataPointRemoved(const IlvChartDataSet* dataSet,
					 IlUInt ptidx);

    virtual void	dataAllPointsRemoved(const IlvChartDataSet* dataSet);

    virtual void	dataPointChanged(const IlvChartDataSet* dataSet,
					 IlUInt ptidx,
					 IlBoolean beforeChange);

    virtual void	dataPointAdded(const IlvChartDataSet* dataSet,
				       IlUInt ptidx);

    virtual void	startBatch(const IlvChartDataSet* dataSet);

    virtual void	endBatch(const IlvChartDataSet* dataSet);


protected:
    IlvChartDataSetListener() {}
};

// Undocumented internal class.
class ILVCHTEXPORTED IlvChartDSLstMap
{
public:
    IlvChartDSLstMap();
    IlvChartDSLstMap(const IlvChartDSLstMap& src);
    ~IlvChartDSLstMap();

    void	addListener(IlvChartDataSet* ds,IlvChartDataSetListener* lst);
    void	removeListeners(IlvChartDataSet* ds,
				IlBoolean destroy = IlTrue);
private:
    IlAList*	_listeners;
};

// --------------------------------------------------------------------------
// Class IlvChartDataSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDataSet : public IlvValueInterface
{
public:

    virtual ~IlvChartDataSet();

    virtual IlUInt	getDataCount() const = 0;

    inline IlUInt	getMaxCount() const { return _maxCount; }

    void		setMaxCount(IlUInt maxCount);

    // == Dataset properties ============

    inline IlBoolean	isLimited() const
			{
			    return (_maxCount != IlvNoCountLimit);
			}

    virtual IlBoolean	isWritable() const;

    virtual IlBoolean	isRemovalAllowed() const;

    virtual IlBoolean	isIncreasingOnX() const;

    // == Data point handling ============
    inline
    IlvPointInfoCollection*	getPointInfoCollection() const
				{
				    return _pointInfoCollection;
				}

    void		setPointInfoCollection(IlvPointInfoCollection* ptic);

    inline IlUInt	getPointInfoCount() const
			{
			    return _pointInfoCollection ?
				_pointInfoCollection->getPointInfoCount() : 0;
			}

    inline
    IlvChartDataPointInfo*	getPointInfo(IlUInt ptidx) const
				{
				    return _pointInfoCollection
					? _pointInfoCollection->
					  getInfoForPoint(ptidx)
					: 0;
				}

    IlBoolean setPointInfo(IlUInt ptidx,
			   IlvChartDataPointInfo* pointInfo,
			   IlBoolean copyPointInfo = IlFalse);
    inline IlBoolean	removePointInfo(IlUInt ptidx)
			{
			    return _pointInfoCollection
				? _pointInfoCollection->removePointInfo(ptidx)
				: IlFalse;
			}

    inline void		removeAllPointInfo()
			{
			    if (_pointInfoCollection)
				_pointInfoCollection->removeAllPointInfo();
			}

    virtual IlvDoublePoint*	getPointsBetween(IlUInt  indexMin,
						 IlUInt  indexMax,
						 IlUInt& count) const;

    virtual IlvDoublePoint* getPointsInRange(IlUInt& count,
					     IlUInt*& dataPointIndexes,
					     const IlvCoordInterval& xRange,
					     const IlvCoordInterval& yRange,
					     IlBoolean needContinuity) const;

    IlvDoublePoint*	getPoints(IlUInt& count) const;

    virtual void	getPoint(IlUInt i,IlvDoublePoint& point) const = 0;

    virtual IlBoolean	setPoint(IlUInt ptidx,const IlvDoublePoint& point);

    inline IlBoolean	addPoint(const IlvDoublePoint& point,
				 IlvChartDataPointInfo* pointInfo = 0,
				 IlBoolean copyPointInfo = IlFalse)
			{
			    return insertPoint(point,
					       IlvLastPositionIndex,
					       pointInfo,
					       copyPointInfo);
			}

    virtual IlBoolean	insertPoint(const IlvDoublePoint& point,
				    IlUInt ptidx,
				    IlvChartDataPointInfo* pointInfo = 0,
				    IlBoolean copyPointInfo = IlFalse);

    virtual IlBoolean	insertPoints(IlUInt count,
				     const IlvDoublePoint* points,
				     IlUInt position = IlvLastPositionIndex,
				     IlvChartDataPointInfo* const* pInfos = 0,
				     IlBoolean copyPointInfo = IlFalse);

    virtual IlBoolean	removePointAndInfo(IlUInt ptidx);

    virtual void	removePointsAndInfo();

    virtual void	removeAllPoints();

    virtual const IlvCoordInterval&	getXRange() const;

    virtual const IlvCoordInterval&	getYRange() const;

    inline void		getBoundingValues(IlvCoordInterval& xRange,
					  IlvCoordInterval& yRange) const
			{
			    xRange = getXRange();
			    yRange = getYRange();
			}

    inline const char*	getName() const
			{
			    return _name.isEmpty()
				? (const char*)0
				: (const char*)_name;
			}

    inline void		setName(const char* name) { _name = name; }

    // == Notification methods & Listeners ==================
    virtual void	dataPointAdded(IlUInt position);

    virtual void	dataPointChanged(IlUInt ptidx,
					 IlBoolean beforeChange);

    virtual void	startBatch();

    virtual void	endBatch();

    inline IlUInt	getAddMinIdx() const { return _addMinIdx;}

    inline IlUInt	getAddMaxIdx() const { return _addMaxIdx;}

    virtual void	dataPointRemoved(IlUInt ptidx);

    virtual void	dataAllPointsRemoved();

    inline IlBoolean	areListenersEnabled() const
			{
			    return _listenersEnabled;
			}

    inline void		enableListeners(IlBoolean b) { _listenersEnabled = b; }

    void		addListener(IlvChartDataSetListener* listener);

    IlvChartDataSetListener*	removeListener(IlvChartDataSetListener* l);

    void		removeListeners();

    IlvChartDataSetListener* const*	getListeners(IlUInt& count) const;

    inline void		lock() { _refCount++; }

    inline void		unLock()
			{
			    if (!--_refCount)
				delete this;
			}

    virtual
    IlvChartDataSet*	copy() const = 0;

    // == Persistence ========
    IlvOutputFile&	save(IlvOutputFile& file) const;

    static
    IlvChartDataSet*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    virtual IlBoolean	useDataSet(const IlvChartDataSet* dataSet) const;

    IlvDeclarePropRootClassInfo();

protected:
    IlUInt			_refCount;
    IlUInt			_maxCount; // user limitation
    IlvPointInfoCollection*	_pointInfoCollection;
    IlvCoordInterval		_xRange;
    IlvCoordInterval		_yRange;
    IlString			_name;

    IlArray			_listeners;
    IlBoolean			_listenersEnabled;

    IlUInt			_batchCount;
    IlUInt			_addMinIdx;
    IlUInt			_addMaxIdx;

    // Constructors

    IlvChartDataSet(const char* name = 0,
	            IlvPointInfoCollection* pointInfoCollection = 0);

    IlvChartDataSet(const IlvChartDataSet& dataSet);

    IlvChartDataSet(IlvInputFile& file);

    // Not documented.
    inline void		setBoundingValues(const IlvCoordInterval& xRange,
					  const IlvCoordInterval& yRange)
			{
			    _xRange = xRange;
			    _yRange = yRange;
			}

    // Internal methods

    void		computeBoundingValues();

    virtual void	computeMinMaxValues(IlvCoordInterval& xRange,
					    IlvCoordInterval& yRange) const;

};

// --------------------------------------------------------------------------
// Class IlvChartDataSetCollection
// Handles a collection of dataSets
// --------------------------------------------------------------------------

// Class not documented.
class ILVCHTEXPORTED IlvChartDataSetCollection
{
public:

    IlvChartDataSetCollection(IlUInt maxCount = IlvNoCountLimit);

    IlvChartDataSetCollection(const IlvChartDataSetCollection& collection);

    ~IlvChartDataSetCollection();

    // Get the maximum data sets count that can be handled.
    inline IlUInt	getMaxDataSetsCount() const
			{
			    return _maxDataSetsCount;
			}

    // Set the maximum data sets count that can be handled.
    inline void		setMaxDataSetsCount(IlUInt maxCount)
			{
			    _maxDataSetsCount = maxCount;
			}

    // Know if the number of data sets handled by the current object is
    // limited or not.
    inline IlBoolean	isLimited() const
			{
			    return _maxDataSetsCount != IlvNoCountLimit;
			}

    // Get the number of defined data sets.
    IlUInt		getDataSetsCount() const;
    // Get a data set in the data sets collection.
    IlvChartDataSet*	getDataSet(IlUInt index = 0) const;
    // Get all the data sets in the data sets collection.
    IlvChartDataSet* const*	getDataSets(IlUInt& count) const;
    // Get the index of a given data set in the data sets collection.
    IlUInt		getDataSetIndex(const IlvChartDataSet* dataSet) const;
    // Know if a data set is part of the data sets collection or not.
    IlBoolean		useDataSet(const IlvChartDataSet* dataSet) const;
    // Set a data set in the data sets collection.
    IlBoolean		setDataSet(IlvChartDataSet* dataSet, IlUInt index = 0);
    void		setDataSets(IlUInt& count,
				    IlvChartDataSet* const* dataSets);
    IlBoolean		replaceDataSet(IlvChartDataSet* oldDataSet,
				       IlvChartDataSet* newDataSet);

    inline IlBoolean	addDataSet(IlvChartDataSet* dataSet)
			{
			    return insertDataSet(dataSet,
						 IlvLastPositionIndex);
			}

    IlBoolean		insertDataSet(IlvChartDataSet* dataSet,
				      IlUInt index = 0);

    IlBoolean		removeDataSet(IlUInt index = 0);
    void		removeDataSets();

    inline void		addListener(IlvChartDataSet* dataSet,
				    IlvChartDataSetListener* lst)
			{
			    _lstMap.addListener(dataSet,lst);
			}
    inline void		removeListeners(IlvChartDataSet* dataSet)
			{
			    _lstMap.removeListeners(dataSet);
			}

    inline
    IlvChartDataSet*	operator[](IlUInt index)
			{
			    return getDataSet(index);
			}
    inline
    const IlvChartDataSet*	operator[](IlUInt index) const
				{
				    return (const IlvChartDataSet*)
					getDataSet(index);
				}
    void		read(IlvInputFile&, IlBoolean);
    void		write(IlvOutputFile&, IlBoolean) const;

private:
    IlArray*		_dataSets;
    IlvChartDataSet*	_dataSet;
    IlUInt		_maxDataSetsCount;
    IlvChartDSLstMap	_lstMap;
};

// --------------------------------------------------------------------------
// Class IlvCombinedChartDataSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCombinedChartDataSet : public IlvChartDataSet
{
public:

    virtual ~IlvCombinedChartDataSet();

    virtual IlBoolean	isIncreasingOnX() const;

    virtual IlUInt	getDataCount() const;

    virtual void	setDataCount(IlUInt count);

    inline IlUInt	getDataSetsCount() const
			{
			    return _dataSetCollection.getDataSetsCount();
			}

    inline
    IlvChartDataSet*	getDataSet(IlUInt index = 0) const
			{
			    return _dataSetCollection.getDataSet(index);
			}

    virtual void	setDataSet(IlvChartDataSet* dataSet,
				   IlUInt index = 0);

    inline void		addDataSet(IlvChartDataSet* dataSet)
			{
			    insertDataSet(dataSet,IlvLastPositionIndex);
			}

    virtual void	insertDataSet(IlvChartDataSet* dataSet,
				      IlUInt index = 0);

    virtual void	removeDataSet(IlUInt index = 0);

    void		removeDataSets();

    virtual IlUInt	getIndexInCombined(const IlvChartDataSet* dataSet,
					   IlUInt indexInDataSet) const;

    virtual IlUInt	getIndexInDataSet(IlvChartDataSet*& dataSet,
					  IlUInt indexInCombined) const;

    virtual IlBoolean	setPoint(IlUInt ptidx, const IlvDoublePoint& point);

    virtual
    IlBoolean	retrieveDataSetPoint(IlvChartDataSet*& dataSet,
				     IlUInt ptidx,
				     const IlvDoublePoint& point,
				     IlUInt& dataSetPointIndex,
				     IlvDoublePoint& dataSetPoint) const = 0;

    inline IlUInt	getDataSetIndex(const IlvChartDataSet* dataSet) const
			{
			    return _dataSetCollection.getDataSetIndex(dataSet);
			}

    virtual IlBoolean	useDataSet(const IlvChartDataSet* dataSet) const;


    // Other methods
    virtual void	updateDataCount();

    virtual const IlvCoordInterval&	getXRange() const;

    virtual const IlvCoordInterval&	getYRange() const;


    // == Notif from child dataSets
    virtual void	_dataPointChanged(const IlvChartDataSet* dataSet,
					  IlUInt ptidx,
					  IlBoolean beforeChange);

    virtual void	_dataPointRemoved(const IlvChartDataSet* dataSet,
					  IlUInt ptidx);

    virtual void	_dataPointAdded(const IlvChartDataSet* dataSet,
					IlUInt position);

    // Persistence
    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropClassInfo();

protected:
    IlUInt			_dataCount;
    IlvChartDataSetCollection	_dataSetCollection;
    IlBoolean			_rangeValid;

    // Internal methods
    // Constructors
    IlvCombinedChartDataSet();

    IlvCombinedChartDataSet(IlvInputFile& file);

    IlvCombinedChartDataSet(const IlvCombinedChartDataSet& dataSet);

    inline void		invalidateBoundingValues() { _rangeValid = IlFalse; }
};

// --------------------------------------------------------------------------
// Class IlvAddChartDataSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAddChartDataSet : public IlvCombinedChartDataSet
{
public:
    IlvAddChartDataSet(IlBoolean addX = IlFalse,
		       IlBoolean addY = IlTrue,
		       IlBoolean positiveCt = IlTrue);

    inline IlBoolean	addX() const { return _addX; }
    inline void		setAddX(IlBoolean b) { _addX = b; }
    inline IlBoolean	addY() const { return _addY; }
    inline void		setAddY(IlBoolean b) { _addY = b; }

    inline IlBoolean	getPositiveCt() const { return _positiveCt; }
    inline void		setPositiveCt(IlBoolean b) { _positiveCt = b; }

    virtual void	getPoint(IlUInt i, IlvDoublePoint& point) const;

    virtual
    IlBoolean		retrieveDataSetPoint(IlvChartDataSet*& dataSet,
					     IlUInt ptidx,
					     const IlvDoublePoint& point,
					     IlUInt& dataSetPtIndex,
					     IlvDoublePoint& dataSetPt) const;

    DeclareChartDataSetTypeInfo(IlvAddChartDataSet);

protected:
    IlBoolean		_addX;
    IlBoolean		_addY;
    IlBoolean		_positiveCt;

};

// --------------------------------------------------------------------------
// Class IlvStacked100ChartDataSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStacked100ChartDataSet : public IlvCombinedChartDataSet
{
public:
    IlvStacked100ChartDataSet(IlUInt dsIdx);

    virtual void	getPoint(IlUInt i, IlvDoublePoint& point) const;

    virtual
    IlBoolean		retrieveDataSetPoint(IlvChartDataSet*& dataSet,
					     IlUInt ptidx,
					     const IlvDoublePoint& point,
					     IlUInt& dataSetPtIndex,
					     IlvDoublePoint& dataSetPt) const;

    DeclareChartDataSetTypeInfo(IlvStacked100ChartDataSet);

protected:
    IlUInt		_dsIdx;
};


// --------------------------------------------------------------------------
// Class IlvHiLoChartDataSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvHiLoChartDataSet : public IlvCombinedChartDataSet
{
public:
    IlvHiLoChartDataSet();
    IlvHiLoChartDataSet(IlvChartDataSet*,IlvChartDataSet*);

    inline
    IlvChartDataSet*	getLoDataSet() const { return getDataSet(0); }
    inline
    IlvChartDataSet*	getHiDataSet() const { return getDataSet(1); }

    inline void		setLoDataSet(IlvChartDataSet* dataSet)
			{
			    setDataSet(dataSet, 0);
			}
    inline void		setHiDataSet(IlvChartDataSet* dataSet)
			{
			    setDataSet(dataSet, 1);
			}

    virtual void	setDataCount(IlUInt count);

    virtual void	getPoint(IlUInt i, IlvDoublePoint& point) const;

    virtual IlUInt	getIndexInCombined(const IlvChartDataSet* dataSet,
					   IlUInt indexInDataSet) const;
    virtual IlUInt	getIndexInDataSet(IlvChartDataSet*& dataSet,
					  IlUInt indexInCombined) const;

    virtual
    IlBoolean		retrieveDataSetPoint(IlvChartDataSet*& dataSet,
					     IlUInt ptidx,
					     const IlvDoublePoint& point,
					     IlUInt& dataSetPtIndex,
					     IlvDoublePoint& dataSetPt) const;

    DeclareChartDataSetTypeInfoRO(IlvHiLoChartDataSet);

protected:
};

// --------------------------------------------------------------------------
// Class IlvPieChartDataSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPieChartDataSet : public IlvCombinedChartDataSet
{
public:
    IlvPieChartDataSet(IlDouble radius,
		       IlDouble startingAngle = 0.0,
		       IlDouble range = 360.0);


    inline IlDouble	getRadius() const { return _radius; }
    void		setRadius(IlDouble radius);
    inline IlDouble	getStartingAngle() const { return _startingAngle; }
    void		setStartingAngle(IlDouble angle);
    inline IlDouble	getRange() const { return _range; }
    void		setRange(IlDouble range);

    virtual void	setDataCount(IlUInt count);


    virtual void	getPoint(IlUInt i, IlvDoublePoint& point) const;

    virtual IlUInt	getIndexInCombined(const IlvChartDataSet* dataSet,
					   IlUInt indexInDataSet) const;

    virtual IlUInt	getIndexInDataSet(IlvChartDataSet*& dataSet,
					  IlUInt indexInCombined) const;

    virtual
    IlBoolean		retrieveDataSetPoint(IlvChartDataSet*& dataSet,
					     IlUInt ptidx,
					     const IlvDoublePoint& point,
					     IlUInt& dataSetPtIndex,
					     IlvDoublePoint& dataSetPt) const;

    DeclareChartDataSetTypeInfo(IlvPieChartDataSet);

protected:
    IlDouble		_radius;
    IlDouble		_startingAngle;
    IlDouble		_range;

    // Internal methods
    virtual void	computeMinMaxValues(IlvCoordInterval& xRange,
					    IlvCoordInterval& yRange) const;
};

// --------------------------------------------------------------------------
// Class IlvChartPointSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartPointSet : public IlvChartDataSet
{
public:

    IlvChartPointSet(const char* name = 0,
		     IlvPointInfoCollection* pointInfoCollection = 0);

    virtual ~IlvChartPointSet();

    virtual IlBoolean	isIncreasingOnX() const;

    virtual IlUInt	getDataCount() const;

    virtual void	getPoint(IlUInt i,IlvDoublePoint& point) const;

    virtual
    IlvDoublePoint*	getPointsBetween(IlUInt  indexMin,
					 IlUInt  indexMax,
					 IlUInt& count) const;

    virtual IlBoolean	setPoint(IlUInt ptidx, const IlvDoublePoint& point);

    virtual IlBoolean	insertPoint(const IlvDoublePoint& point,
				    IlUInt ptidx,
				    IlvChartDataPointInfo* pointInfo = 0,
				    IlBoolean copyPointInfo = IlFalse);

    virtual IlBoolean	insertPoints(IlUInt count,
				     const IlvDoublePoint* points,
				     IlUInt position = IlvLastPositionIndex,
				     IlvChartDataPointInfo* const* pInfos = 0,
				     IlBoolean copyPointInfo = IlFalse);
    virtual void	dataPointAdded(IlUInt position);

    virtual void	dataPointChanged(IlUInt ptidx, IlBoolean beforeChange);

    virtual IlBoolean	removePointAndInfo(IlUInt ptidx);

    virtual void	removePointsAndInfo();

    DeclareChartDataSetTypeInfo(IlvChartPointSet);

protected:
    IlvChartDoublePointArray	_points;
    IlBoolean			_isIncreasingOnX;

    // Internal methods
    virtual void	computeMinMaxValues(IlvCoordInterval& xRange,
					    IlvCoordInterval& yRange) const;

    inline void		updateBoundingValues(const IlvDoublePoint& newPoint)
			{
			    _xRange += newPoint.x();
			    _yRange += newPoint.y();
			}

    // Not documented.
    void		removePoints();
};

// --------------------------------------------------------------------------
// Class IlvChartYValueSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartYValueSet : public IlvChartDataSet
{
public:

    IlvChartYValueSet(const char* name = 0,
		      IlvPointInfoCollection* pointInfoCollection = 0);

    virtual ~IlvChartYValueSet();

    virtual IlBoolean	isIncreasingOnX() const;

    virtual IlUInt	getDataCount() const;

    virtual void	getPoint(IlUInt i,IlvDoublePoint& point) const;

    virtual
    IlvDoublePoint*	getPointsBetween(IlUInt  indexMin,
					 IlUInt  indexMax,
					 IlUInt& count) const;

    virtual IlBoolean	setPoint(IlUInt ptidx, const IlvDoublePoint& point);

    virtual IlBoolean	insertPoint(const IlvDoublePoint& point,
				    IlUInt ptidx,
				    IlvChartDataPointInfo* pointInfo = 0,
				    IlBoolean copyPointInfo = IlFalse);

    virtual IlBoolean	removePointAndInfo(IlUInt ptidx);

    virtual void	removePointsAndInfo();

    void		getValue(IlUInt i, IlDouble& yValue) const;

    IlBoolean		setValue(IlUInt valueIndex, IlDouble yValue);

    inline IlBoolean	addValue(IlDouble yValue,
				 IlvChartDataPointInfo* pointInfo = 0,
				 IlBoolean copyPointInfo = IlFalse)
			{
			    return insertValue(yValue,
					       IlvLastPositionIndex,
					       pointInfo,
					       copyPointInfo);
			}

    IlBoolean		insertValue(IlDouble yValue,
				    IlUInt valueIndex,
				    IlvChartDataPointInfo* pointInfo = 0,
				    IlBoolean copyPointInfo = IlFalse);

    IlBoolean		insertValues(IlUInt count,
				     const IlDouble* yValues,
				     IlUInt position = IlvLastPositionIndex,
				     IlvChartDataPointInfo* const* pInfos = 0,
				     IlBoolean copyPointInfo = IlFalse);


    IlBoolean		removeValueAndInfo(IlUInt valueIndex);

    virtual void	removeValuesAndInfo();

    DeclareChartDataSetTypeInfo(IlvChartYValueSet);

protected:
    IlvChartDoubleArray	_yValues;

    // Internal methods
    virtual void	computeMinMaxValues(IlvCoordInterval& xRange,
					    IlvCoordInterval& yRange) const;

    void		updateBoundingValues(IlDouble newYValue);

    // Not documented.
    void		removeValues();
};

// --------------------------------------------------------------------------
// Class IlvAbstractChartFunction
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAbstractChartFunction : public IlvChartDataSet
{
public:

    virtual IlUInt	getDataCount() const;

    void		setDataCount(IlUInt count);

    inline IlDouble	getXMin() const { return getXRange().getMin(); }

    inline IlDouble	getXMax() const { return getXRange().getMax(); }

    void		setXMin(IlDouble min);

    void		setXMax(IlDouble max);

    inline
    virtual IlBoolean	isFunctionDefined() const { return IlFalse; }
    virtual IlBoolean	isIncreasingOnX() const;

    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropClassInfo();

protected:
    IlUInt		_dataCount;

    // == Constructors ================
    IlvAbstractChartFunction(const char* name = 0,
			     IlvPointInfoCollection* ptInfoCollection = 0);

    IlvAbstractChartFunction(const IlvCoordInterval& xRange,
			     IlUInt count,
			     const char* name = 0,
			     IlvPointInfoCollection* ptInfoCollection = 0);

    IlvAbstractChartFunction(IlvInputFile& file);

    IlvAbstractChartFunction(const IlvAbstractChartFunction& dataSet);
};

// --------------------------------------------------------------------------
// Class IlvCallbackChartFunction
// --------------------------------------------------------------------------
typedef IlDouble (* IlvDoubleFunction)(IlDouble);

class ILVCHTEXPORTED IlvCallbackChartFunction : public IlvAbstractChartFunction
{
public:

    IlvCallbackChartFunction(const char* name = 0,
			     IlvPointInfoCollection* ptInfoCollection = 0);

    IlvCallbackChartFunction(const IlvCoordInterval& xRange,
			     IlUInt count,
			     IlvDoubleFunction f,
			     const char* name = 0,
			     IlvPointInfoCollection* ptInfoCollection = 0);

    inline
    IlvDoubleFunction	getFunction() const { return _function; }
    void		setFunction(IlvDoubleFunction function);

    virtual IlBoolean	isFunctionDefined() const;

    virtual void	getPoint(IlUInt i, IlvDoublePoint& point) const;

    DeclareChartDataSetTypeInfo(IlvCallbackChartFunction);

protected:
    IlvDoubleFunction	_function;
};

// --------------------------------------------------------------------------
// IlvAbstractChartData persistence
// --------------------------------------------------------------------------
// Added for a problem of compatibility with the old charts
#if defined(IlvChartDataConstructor)
#undef IlvChartDataConstructor
#endif
#if defined(IlvChartDataClassInfo)
#undef IlvChartDataClassInfo
#endif

class IlvAbstractChartData;
typedef IlvAbstractChartData* (*IlvChartDataConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvChartDataClassInfo : public IlvValuedClassInfo
{
public:
    static
    IlvChartDataClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvChartDataConstructor);

    inline 
    IlvChartDataClassInfo*	getChartDataSuperClass() const
			{
			    return IL_DYNAMICCAST(IlvChartDataClassInfo*,
						  getSuperClass());
			}
    inline
    IlvChartDataConstructor	getConstructor() const { return _constructor; }

protected:
    IlvChartDataConstructor     _constructor;

    IlvChartDataClassInfo(const char* className,
			  IlvClassInfo** superClass,
			  IlvChartDataConstructor constr)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(constr) {}
};
#define IlvRegisterAbstractChartDataClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
		IlvChartDataClassInfo::Create(#classname,		\
		    ILVSUPERCLASSINFO(superclass),			\
		    (IlvChartDataConstructor)classname::Read))

// Added for a problem of compatibility with the old charts
#if defined(IlvPreRegisterChartDataClass)
#undef IlvPreRegisterChartDataClass
#endif

#define IlvPreRegisterChartDataClass(classname)				\
ILVPREDEFINECLASSINFOMEMBERS(classname)

// Added for a problem of compatibility with the old charts
#if defined(IlvPostRegisterChartDataClass)
#undef IlvPostRegisterChartDataClass
#endif

#define IlvPostRegisterChartDataClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
		IlvChartDataClassInfo::Create(#classname,		\
		    ILVSUPERCLASSINFO(superclass),			\
		    (IlvChartDataConstructor)classname::Read))


// --------------------------------------------------------------------------
// Class IlvChartDataListener
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDataListener
{
public:

    virtual ~IlvChartDataListener();

    virtual void	dataSetRemoved(const IlvAbstractChartData* cData,
				       IlvChartDataSet* dataSet);

    virtual void	dataSetAdded(const IlvAbstractChartData* cData,
				     IlvChartDataSet* dataSet,
				     IlUInt position);

    virtual void	dataSetChanged(const IlvAbstractChartData* cData,
				       IlvChartDataSet* oldSet,
				       IlvChartDataSet* newSet);

    virtual void	dataPointRemoved(const IlvAbstractChartData* cData,
					 const IlvChartDataSet* dataSet,
					 IlUInt ptidx);

    virtual void	dataAllPointsRemoved(const IlvAbstractChartData* cData,
					     const IlvChartDataSet* dataSet);

    virtual void	dataPointChanged(const IlvAbstractChartData* cData,
					 const IlvChartDataSet* dataSet,
					 IlUInt ptidx,
					 IlBoolean beforeChange);

    virtual void	dataPointAdded(const IlvAbstractChartData* cData,
				       const IlvChartDataSet* dataSet,
				       IlUInt position);

    virtual void	startBatch(const IlvAbstractChartData* cData,
				   const IlvChartDataSet* dataSet);

    virtual void	endBatch(const IlvAbstractChartData* cData,
				 const IlvChartDataSet* dataSet);
protected:
    IlvChartDataListener() {};
};

// --------------------------------------------------------------------------
// Class IlvAbstractChartData
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAbstractChartData : public IlvValueInterface
{
 public:

    virtual ~IlvAbstractChartData();

    virtual IlUInt	getDataSetsCount() const = 0;

    inline void		lock() { _refCount++; }

    void		unLock();

    // == Properties ============
    virtual IlBoolean	isLimited() const;

    virtual IlBoolean	isWritable() const;

    virtual IlBoolean	isRemovalAllowed() const;

    virtual IlvChartDataSet* const*	getDataSets(IlUInt& nbDataSets) const;

    virtual IlvChartDataSet*	getDataSet(IlUInt index) const = 0;

    IlvChartDataSet*	getDataSetByName(const char* name) const;

    IlUInt		getDataSetIndex(const IlvChartDataSet* dataSet) const;

    virtual IlBoolean	setDataSets(IlUInt& count,
				    IlvChartDataSet* const* dataSets,
				    IlBoolean copy = IlFalse) = 0;
    virtual IlBoolean	setDataSet(IlUInt dataSetIndex,
				   IlvChartDataSet* dataSet,
				   IlBoolean copy = IlFalse) = 0;
    virtual IlBoolean	addDataSet(IlvChartDataSet* dataSet,
				   IlBoolean copy = IlFalse) = 0;

    virtual IlBoolean	insertDataSet(IlvChartDataSet* dataSet,
				      IlUInt index = IlvLastPositionIndex,
				      IlBoolean copy = IlFalse) = 0;
    virtual IlBoolean	removeDataSet(IlUInt dataSetIndex) = 0;

    IlBoolean		replaceDataSet(IlvChartDataSet* oldDataSet,
				       IlvChartDataSet* newDataSet);

    virtual void	removeDataSets() = 0;

    // == Listeners =========================
    // Add a listener
    void		addListener(IlvChartDataListener* lst);

    // Remove a listener, the listener is returned (or 0 if it was not found)
    // The listener is not deleted (it is the responsability of the caller)
    IlvChartDataListener*	removeListener(IlvChartDataListener* lst);

    // Return all the subscribed listeners
    // The returned array must not be freed
    IlvChartDataListener* const*	getListeners(IlUInt& count) const;

    // Remove and delete all the listeners
    void		removeListeners();


    // == Operators =========================
    inline
    IlvChartDataSet*	operator[](IlUInt index)
			{
			    return getDataSet(index);
			}

    inline
    const IlvChartDataSet*	operator[](IlUInt index) const
				{
				    return (const IlvChartDataSet*)
					getDataSet(index);
				}


    // == Notification methods ====================
    virtual void	dataSetRemoved(IlvChartDataSet* dataSet);

    virtual void	dataSetAdded(IlvChartDataSet* dataSet,
				     IlUInt position);

    virtual void	dataSetChanged(IlvChartDataSet* oldSet,
				       IlvChartDataSet* newSet);

    virtual void	startBatch(const IlvChartDataSet* dataSet) const;

    virtual void	endBatch(const IlvChartDataSet* dataSet) const;

    virtual void	dataPointRemoved(const IlvChartDataSet* dataSet,
					 IlUInt ptidx) const;

    virtual void	dataAllPointsRemoved(const IlvChartDataSet* ds) const;

    virtual void	dataPointChanged(const IlvChartDataSet* dataSet,
					 IlUInt ptidx,
					 IlBoolean beforeChange) const;

    virtual void	dataPointAdded(const IlvChartDataSet* dataSet,
				       IlUInt position) const;

    // == Virtual copy constructor
    virtual IlvAbstractChartData*	copy() const = 0;

    // == Persistence

    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvAbstractChartData*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const = 0;

    IlvDeclarePropRootClassInfo();

 protected:
    IlUInt			_refCount;
    IlvArray			_listeners;
    IlvChartDSLstMap		_lstMap;
    IlvChartDataSetListener*	_dsLst;

    void		addDataSetListener(IlvChartDataSet*,
					   IlvChartDataSetListener*);
    void		removeDataSetListeners(IlvChartDataSet*,
					       IlBoolean = IlTrue);
    //void removeDataSetListeners();

    // Constructors
    IlvAbstractChartData();
    IlvAbstractChartData(const IlvAbstractChartData& cData);
    IlvAbstractChartData(IlvInputFile& file);
};

// --------------------------------------------------------------------------
// Class IlvMemoryChartData
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvMemoryChartData : public IlvAbstractChartData
{
public:

    IlvMemoryChartData();

    virtual ~IlvMemoryChartData();

    virtual IlUInt	getDataSetsCount() const;

    inline IlUInt	getMaxDataSetsCount() const
			{
			    return _dataSetCollection.getMaxDataSetsCount();
			}

    inline void		setMaxDataSetsCount(IlUInt maxCount)
			{
			    _dataSetCollection.setMaxDataSetsCount(maxCount);
			}

    // API
    virtual IlBoolean	isLimited() const;

    virtual IlvChartDataSet*	getDataSet(IlUInt dataSetIndex) const;

    virtual IlBoolean	setDataSets(IlUInt& count,
				    IlvChartDataSet* const* dataSets,
				    IlBoolean copy = IlFalse);

    virtual IlBoolean	setDataSet(IlUInt dataSetIndex,
				   IlvChartDataSet* dataSet,
				   IlBoolean copy = IlFalse);

    virtual IlBoolean	addDataSet(IlvChartDataSet* dataSet,
				   IlBoolean copy = IlFalse);

    virtual IlBoolean	insertDataSet(IlvChartDataSet* dataSet,
				      IlUInt index = IlvLastPositionIndex,
				      IlBoolean copy = IlFalse);

    virtual IlBoolean	removeDataSet(IlUInt dataSetIndex);

    virtual void	removeDataSets();

    DeclareChartDataTypeInfo(IlvMemoryChartData);

protected:
    IlvChartDataSetCollection	_dataSetCollection;
};

// --------------------------------------------------------------------------
// Class IlvChartDataStreamer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDataStreamer : public IlvReferenceStreamer
{
public:
    IlvChartDataStreamer();

    virtual void	writeReference(IlvOutputFile& os, IlAny);
    virtual IlAny	readReference(IlvInputFile& is);
};

// --------------------------------------------------------------------------
// Class IlvChartDataSetStreamer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDataSetStreamer : public IlvReferenceStreamer
{
public:
    IlvChartDataSetStreamer();

    virtual void	writeReference(IlvOutputFile& os, IlAny);
    virtual IlAny	readReference(IlvInputFile& is);
};

// --------------------------------------------------------------------------
// Class IlvChartDataPointInfoStreamer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDataPointInfoStreamer
    : public IlvReferenceStreamer
{
public:
    IlvChartDataPointInfoStreamer();

    virtual void	writeReference(IlvOutputFile& os, IlAny);
    virtual IlAny	readReference(IlvInputFile& is);
};

// --------------------------------------------------------------------------
// Class IlvPointInfoCollectionStreamer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPointInfoCollectionStreamer
    : public IlvReferenceStreamer
{
public:
    IlvPointInfoCollectionStreamer();

    virtual void	writeReference(IlvOutputFile& os, IlAny);
    virtual IlAny	readReference(IlvInputFile& is);
};

ILVCHTMODULEINIT(data);

#endif /* !__Ilv_Charts_Data_H */
