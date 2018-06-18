// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/display.h
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
// Declaration of the classes that allow to display (or represent) the data.
// Contains:
//  - IlvChartDisplayerPoints.
//  - IlvAbstractChartDisplayer: an abstract class which allows you to define
//    a "displayer". A "displayer" allows you to represent the data in a
//    specific way such as for example with markers.
//  - IlvSingleChartDisplayer: a subclass of IlvAbstractChartDisplayer
//    which allows you to display data with a single rendering shape.
//    This class allows you to represent charts such as polyline or bar charts
//  - IlvCompositeChartDisplayer: a subclass of IlvAbstractChartDisplayer
//    which allows you to display data sets using several rendering shapes.
//    This class allows you to represent more complex charts such as stacked
//    bar charts or stock charts
//  - IlvChartDisplayerFactory.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Display_H
#define __Ilv_Charts_Display_H

#if !defined(__Ilv_Itf_Value_H)
#  include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_String_H)
#  include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Base_Memory_H)
#  include <ilviews/base/memory.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Charts_Common_H)
#  include <ilviews/charts/common.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#  include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Chart_H)
#  include <ilviews/charts/chart.h>
#endif
#if !defined(__Ilv_Charts_Data_H)
#  include <ilviews/charts/data.h>
#endif
#if !defined(__Ilv_Charts_Graphic_H)
#  include <ilviews/charts/graphic.h>
#endif


class IlvSingleChartDisplayer;
class IlvCompositeChartDisplayer;
class IlvCoordinateInfo;
class IlvChartDisplayerFactory;
class IlvChartLegend;

#define IlvChartDisplayerWidth 8

#define IlvChartDisplayerDepth 4


#define IlvChartPointProjectedOnLimitsFlag 1

// --------------------------------------------------------------------------
// Class IlvChartDisplayerPoints
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDisplayerPoints
{
public:
    IlvChartDisplayerPoints(const IlvChartGraphic*         chart,
			    const IlvSingleChartDisplayer* displayer,
			    IlBoolean                      outOfRange=IlTrue);

    IlvChartDisplayerPoints(const IlvChartDisplayerPoints& displayerPoints);

    virtual ~IlvChartDisplayerPoints();


    inline 
    const IlvChartGraphic*	getChartGraphic() const
				{
				    return _chart;
				}

    inline
    const IlvSingleChartDisplayer*	getDisplayer() const
					{
					    return _displayer;
					}

    inline IlUInt		getPointsCount() const
				{
				    return _points.getLength();
				}

    IlvPoint*			getPoints(IlUInt& count) const;

    inline const IlvPoint*	getInternalPoints(IlUInt& count) const
				{
				    count = _points.getLength();
				    return _points.getArray();
				}

    inline const IlUInt*	getInternalPointIndexes(IlUInt& count) const
				{
				    count = _dataPointIndexes.getLength();
				    return _dataPointIndexes.getArray();
				}

    void			getPoint(IlUInt    index,
					 IlvPoint& point,
					 IlUInt&   dataPtIdx) const;

    void			getDataPoint(IlUInt          index,
					     IlvDoublePoint& point) const;

    inline void			getPoint(IlUInt index, IlvPoint& point) const
				{
				    point = _points[index];
				}

    IlUInt			getDataPointIndex(IlUInt index) const;

    virtual void		setPoint(IlUInt          index,
					 const IlvPoint& point,
					 IlUInt dataPtIdx = IlvBadIndex);

    void			addPoint(const IlvPoint& point,
					 IlUInt dataPtIdx = IlvBadIndex);

    void			insertPoint(const IlvPoint& point,
					    IlUInt dataPtIdx = IlvBadIndex,
					    IlUInt position = 0);

    virtual void		insertPoints(IlUInt          count,
					     const IlvPoint* points,
					     const IlUInt*   dataPtIdxes = 0,
					     IlUInt          position = 0);

    virtual IlBoolean		removePoint(IlUInt index);

    virtual void		removePoints();

    IlUShort			getPointFlag(IlUInt index) const;

    IlBoolean			isProjectedOnLimits(IlUInt index) const;

    void			setProjectedOnLimits(IlUInt    index,
						     IlBoolean flag);

    void			boundingBoxOfPoints(IlvRect& bbox) const;

    IlDouble			averageSpaceBetweenDataPoints() const;

    inline void			setChartGraphic(const IlvChartGraphic* chart)
				{
				    _chart = chart;
				}

    inline void		setDisplayer(const IlvSingleChartDisplayer* displayer)
			{
			    _displayer = displayer;
			}

    // API
    virtual
    IlBoolean		init(IlUInt		    count,
			     const IlvDoublePoint*  dataPoints,
			     const IlUInt*	    dataPtIdxes,
			     const IlvCoordInterval& abscissaRange,
			     IlBoolean		    shiftOfCycleLength,
			     const IlvTransformer*  t);

    virtual IlvPalette*	getPointPalette(IlUInt index,
                                        IlBoolean usePointInfo = IlTrue,
                                        IlvPalette* defaultPalette = 0) const;

    virtual IlvChartDisplayerPoints*	copy() const;


    inline IlBoolean		isCyclic() const { return _isCyclic; }

    inline IlBoolean		isHandlingOutOfRangePoints() const
				{
				    return _outOfRange;
				}

    inline void			handleOutOfRangePoints(IlBoolean b)
				{
				    _outOfRange = b;
				}

    void	handleOutOfRangePoints(const IlvRect&           ddArea,
				       const IlvCoordInterval&	abscissaRange,
				       IlBoolean		cycleShift,
				       const IlvTransformer*	t);


protected:
    const IlvChartGraphic*		_chart;
    const IlvSingleChartDisplayer*	_displayer;
    IlvChartPointArray			_points;
    IlvChartUIntArray			_dataPointIndexes;
    IlvChartUShortArray			_pointFlags;
    IlvChartDoublePointArray            _dataPoints;
    IlBoolean				_outOfRange;
    IlBoolean				_isCyclic;
    IL_MUTABLE IlvPalette*              _lastValidPalette;
    IL_MUTABLE IlvPalette*              _defaultPalette;
    IL_MUTABLE IlvPalette*              _returnPalette;
    IlDouble                            _averageSpaceBetweenPoints;

    // Internal methods
    IlBoolean		dataPointToDisplay(const IlvDoublePoint& dataPoint,
					   IlvPoint& point,
					   IlBoolean shiftOfCycleLength,
					   const IlvTransformer* t) const;
    IlBoolean		displayToDataPoint(const IlvPoint& point,
					   IlvDoublePoint& dataPoint,
					   IlBoolean shiftOfCycleLength,
					   const IlvTransformer* t) const;

    virtual void	projectOutOfBoundOnLimits(const IlvTransformer* t = 0);

    // The two following methods are used inside the previous method.
    void	projectHorizontallyOnLimits(const IlvTransformer* t = 0);
    void	projectVerticallyOnLimits(const IlvTransformer* t = 0);

};

// --------------------------------------------------------------------------
// IlvChartDisplayerPointsFactory
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDisplayerPointsFactory
{
public:

    virtual ~IlvChartDisplayerPointsFactory();

    virtual IlvChartDisplayerPointsFactory*	copy() const = 0;

    virtual
    IlvChartDisplayerPoints*	create(const IlvChartGraphic* chart,
				       const IlvSingleChartDisplayer* disp)=0;

    virtual void		release(const IlvSingleChartDisplayer* disp,
					IlvChartDisplayerPoints* dispPts);

protected:
    IlvChartDisplayerPointsFactory() {}

    IlvChartDisplayerPointsFactory(const IlvChartDisplayerPointsFactory&) {}
};

// --------------------------------------------------------------------------
// Points filter
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartPointsFilter : public IlvChartDisplayerPoints
{
public:
    IlvChartPointsFilter(const IlvChartGraphic*		chart,
			 const IlvSingleChartDisplayer* displayer,
			 IlvDim				clusterSize = 2)
	: IlvChartDisplayerPoints(chart,displayer)
	{
	    _clusterSize = clusterSize;
	}

    IlvChartPointsFilter(const IlvChartPointsFilter& src)
	: IlvChartDisplayerPoints(src), _clusterSize(src._clusterSize)
	{}

    inline IlvDim	getClusterSize() const { return _clusterSize; }

    void		setClusterSize(IlvDim size) { _clusterSize = size; }

    virtual IlBoolean	init(IlUInt			count,
			     const IlvDoublePoint*	dataPoints,
			     const IlUInt*		dataPtIdxes,
			     const IlvCoordInterval&	abscissaRange,
			     IlBoolean			shiftOfCycleLength,
			     const IlvTransformer*	t);

protected:
    IlvDim		_clusterSize;
};

// --------------------------------------------------------------------------
// IlvChartPointsFilterFactory
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartPointsFilterFactory
    : public IlvChartDisplayerPointsFactory
{
public:
    IlvChartPointsFilterFactory(IlvDim clusterSize)
	: IlvChartDisplayerPointsFactory(),
          _clusterSize(clusterSize)
	{}

    IlvChartPointsFilterFactory(const IlvChartPointsFilterFactory& src)
	: IlvChartDisplayerPointsFactory(src),
          _clusterSize(src._clusterSize)
	{}

    virtual IlvChartDisplayerPointsFactory*	copy() const;

    inline IlvDim	getClusterSize() const { return _clusterSize; }

    void		setClusterSize(IlvDim size) { _clusterSize = size; }

    virtual
    IlvChartDisplayerPoints*	create(const IlvChartGraphic* chart,
				       const IlvSingleChartDisplayer* disp);
protected:
    IlvDim		_clusterSize;
};

// --------------------------------------------------------------------------
// IlvAbstractChartDisplayer persistence
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAbstractChartDisplayer;
typedef IlvAbstractChartDisplayer*
(* IlvChartDisplayerConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvChartDisplayerClassInfo : public IlvValuedClassInfo
{
public:
    inline
    IlvChartDisplayerClassInfo* getChartDisplayerSuperClass() const
		{
		    return ILVDYNAMICCAST(IlvChartDisplayerClassInfo*,
					  getSuperClass());
		}
    inline
    IlvChartDisplayerConstructor	getConstructor() const
					{
					    return _constructor;
					}
    static IlvChartDisplayerClassInfo*	Create(const char*,
					       IlvClassInfo**,
					       IlvChartDisplayerConstructor);

protected:
    IlvChartDisplayerClassInfo(const char*                  className,
			       IlvClassInfo**               superClass,
			       IlvChartDisplayerConstructor c)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(c)
	{}
    IlvChartDisplayerConstructor	_constructor;
};

#define IlvRegisterChartDisplayerClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	     IlvChartDisplayerClassInfo::Create(#classname,\
			    ILVSUPERCLASSINFO(superclass),		\
			    (IlvChartDisplayerConstructor)	\
			    classname::Read))

#define IlvPreRegisterChartDisplayerClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterChartDisplayerClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
		IlvChartDisplayerClassInfo::Create(#classname,		\
			   ILVSUPERCLASSINFO(superclass),		\
			   (IlvChartDisplayerConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvAbstractChartDisplayer
// --------------------------------------------------------------------------
// - Flags
#define IlvCHTDispClosedFlag   0x00000001
#define IlvCHTDisp50FileFormat 0x00000002
enum IlvChartGradientMode {
    IlvChartGradientDefault = 0,
    IlvChartGradientGraphArea,
    IlvChartGradientItem
};
// --------------------------------------------------------------------------

class ILVCHTEXPORTED IlvAbstractChartDisplayer : public IlvValueInterface
{
public:
    //     friend class IlvAxisElement;
    //     friend class IlvAbscissaAxisElement;

    virtual ~IlvAbstractChartDisplayer();

    //== Accessors =======================
    inline IlvChartGraphic*	getChartGraphic() const { return _chart; }

    virtual void		setChartGraphic(IlvChartGraphic* chart);

    inline IlBoolean		isVisible() const { return _visible; }

    inline void			setVisible(IlBoolean visible)
				{
				    _visible = visible;
				}

    inline IlvCoordinateInfo*	getOrdinateInfo() const
				{
				    return _ordinateInfo;
				}

    virtual void	setOrdinateInfo(IlvCoordinateInfo* ordinateInfo);

    inline const char*		getName() const
				{
				    return _name.isEmpty()
					? (const char*)0
					: (const char*)_name;
				}

    inline void			setName(const char* name) { _name = name; }

    //== Displayer properties =======================
    virtual IlBoolean		isFilled() const;

    virtual IlBoolean		isContinuous() const;

    virtual IlBoolean		canBeProjectedIfOutOfBounds() const;

    virtual IlvPalette*		getProjectedPointsPalette() const;

    virtual IlBoolean		graphicalRepresentationByDataPoint() const;

    virtual IlBoolean		isViewable() const;

    virtual IlBoolean		useVirtualDataSets() const;

    virtual IlUInt	getDisplayersCount() const = 0;

    IlUInt		getFlags() const { return _flags; }
    void		setFlags(IlUInt flags) { _flags = flags; }

    //== Data sets methods =======================
    inline
    const IlvChartDataSetCollection& getRealDataSetCollection() const
					{
					    return _dataSetCollection;
					}
    inline
    const IlvChartDataSetCollection& getVirtualDataSetCollection() const
					{
					    return _virtualDataSetCollection;
					}

    IlUInt		getDataSetsCount() const;

    inline IlUInt	getRealDataSetsCount() const
			{
			    return _dataSetCollection.getDataSetsCount();
			}

    inline IlUInt	getMaxDataSetsCount() const
			{
			    return _dataSetCollection.getMaxDataSetsCount();
			}

    IlvChartDataSet*	getDataSet(IlUInt index = 0) const;

    inline
    IlvChartDataSet*	getRealDataSet(IlUInt index = 0) const
			{
			    return _dataSetCollection.getDataSet(index);
			}

    virtual
    IlvCombinedChartDataSet* getVirtualDataSet(const IlvChartDataSet* dataSet,
					       IlUInt& index) const;

    virtual void	setDataSet(IlvChartDataSet* dataSet,
				   IlUInt           index = 0);

    virtual void	setDataSets(IlUInt                  count,
				    IlvChartDataSet* const* dataSets);

    inline void		setDataSet(IlvChartDataSet* dataSet,
				   IlvPalette* palette,
				   IlUInt index = 0)
			{
			    setDataSet(dataSet,index);
			    setPalette(palette,index);
			}

    inline void		addDataSet(IlvChartDataSet* dataSet)
			{
			    insertDataSet(dataSet,IlvLastPositionIndex);
			}

    virtual void	insertDataSet(IlvChartDataSet* dataSet,
				      IlUInt index = IlvLastPositionIndex);

    virtual void	removeDataSet(IlvChartDataSet* dataSet);

    virtual void	removeDataSets();

    virtual IlBoolean	replaceDataSet(IlvChartDataSet* oldDataSet,
				       IlvChartDataSet* newDataSet);

    virtual IlBoolean	displayDataSet(const IlvChartDataSet* dataSet) const;

    void		setVirtualDataSet(IlvCombinedChartDataSet* vDataSet,
					  IlUInt index = 0);

    //== Palette managements =======================
    virtual IlvPalette*	getPalette(IlUInt index = 0) const = 0;

    virtual void	setPalette(IlvPalette* pal, IlUInt index = 0) = 0;

    virtual IlvColor*	getForeground(IlUInt index = 0) const = 0;

    virtual void	setForeground(IlvColor* color, IlUInt index = 0) = 0;

    virtual IlvColor*	getBackground(IlUInt index = 0) const = 0;

    virtual void	setBackground(IlvColor* color, IlUInt index = 0) = 0;

    virtual void	drawFill(IlBoolean b) = 0;

    virtual void	setClosed(IlBoolean b) = 0;
    virtual const char*	getLegendText(IlUInt index = 0) const = 0;

    virtual void	setLegendText(const char* text, IlUInt index = 0) = 0;

    virtual const char*	getInternalLegendText(IlUInt index = 0) const = 0;

    //== Point infos =======================
    virtual void	setPointInfoCollection(const IlvChartDataSet* dataSet,
					       IlvPointInfoCollection* ptInfoCollection) = 0;

    virtual IlvPointInfoCollection*
	getPointInfoCollection(const IlvChartDataSet* dataSet) const = 0;

    inline void removePointInfoCollection(const IlvChartDataSet* dataSet)
		{
		    setPointInfoCollection(dataSet, 0);
		}

    virtual
    IlvChartDataPointInfo*	getPointInfo(IlUInt dataPtIdx,
					     const IlvChartDataSet* dataSet = 0) const;
    inline
    const IlvCompositeChartDisplayer*
		getParentDisplayer() const { return _parentDisplayer; }

    inline void	setParentDisplayer(const IlvCompositeChartDisplayer* displayer)
		{
		    _parentDisplayer = displayer;
		}

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const = 0;

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const = 0;

    virtual IlUInt	getNearestPoint(IlvChartDataSet*& dataSet,
					const IlvPoint& viewPoint,
					IlvDim distance,
					IlvPoint& point,
					const IlvTransformer* t = 0) const = 0;

    virtual IlUInt	getDisplayItem(IlvChartDataSet*& dataSet,
				       const IlvPoint& viewPoint,
				       const IlvTransformer* t) const = 0;

    virtual IlBoolean	boundingBox(IlvRect& bbox,
				    const IlvTransformer* t = 0) const = 0;

    virtual void	drawDataPoint(IlUInt dataPtIdx,
				      IlvPort* dst,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const = 0;

    // Simplified: does not work in cyclic mode!
    virtual void	drawDataPoints(IlUInt iMin,
				       IlUInt iMax,
				       IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const = 0;

    virtual IlBoolean	dataPointBBox(IlUInt dataPtIdx,
				      IlvRect& bbox,
				      IlBoolean takeInfoIntoAccount = IlTrue,
				      const IlvTransformer* t = 0) const = 0;

    virtual void	dataPointsBBox(IlUInt iMin,
				       IlUInt iMax,
				       IlvRect& bbox,
				       IlBoolean takeInfoIntoAccount = IlTrue,
				       const IlvTransformer* t = 0) const = 0;
    virtual
    IlBoolean		getDisplayPoint(const IlvChartDataSet* dataSet,
					IlUInt dataPtIdx,
					IlvPoint& point,
					const IlvTransformer* t = 0) const = 0;

    virtual IlBoolean	setDataPoint(IlvChartDataSet* dataSet,
				     IlUInt dataPtIdx,
				     const IlvPoint& point,
				     const IlvTransformer* t = 0) const = 0;

    IlBoolean		dataPointToDisplay(const IlvDoublePoint& dataPoint,
					   IlvPoint& point,
					   const IlvTransformer* t = 0) const;

    IlBoolean		displayToDataPoint(const IlvPoint&       point,
					   IlvDoublePoint&       dataPoint,
					   const IlvTransformer* t = 0) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const = 0;

    virtual void	setLegendItems(IlvChartLegend* legend) const = 0;

    virtual void	setOverwrite(IlBoolean o) = 0;

    virtual void	setMode(IlvDrawMode mode) = 0;

    virtual IlvAbstractChartDisplayer*	copy() const = 0;

    // Persistence
    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvAbstractChartDisplayer*	Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropRootClassInfo();

    void		refreshVirtualDataSet();

    inline
    IlvChartGradientMode	getGradientMode() const
				{
				    return _gradientMode;
				}
    virtual void		setGradientMode(IlvChartGradientMode m);

protected:
    IlBoolean				_visible;
    IlvCoordinateInfo*		        _ordinateInfo; // how to remove this ?
    IlString				_name;
    IlUInt				_flags;
    IlvChartGraphic*			_chart;
    IlvChartDataSetCollection		_dataSetCollection;
    IlvChartDataSetCollection		_virtualDataSetCollection;
    const IlvCompositeChartDisplayer*	_parentDisplayer;
    IlvChartGradientMode		_gradientMode;

    //     IlvAxisElement*                     _axisElement;
    // How to connect it to an IlvAxisElement ?

    IlBoolean		checkChartGraphic();

    inline void		setMaxDataSetsCount(IlUInt count)
			{
			    _dataSetCollection.setMaxDataSetsCount(count);
			}

    IlvAbstractChartDisplayer();

    IlvAbstractChartDisplayer(const IlvAbstractChartDisplayer& displayer);

    IlvAbstractChartDisplayer(IlvInputFile& file);

    //== Update methods =======================
    virtual void	dataSetRemoved(IlUInt index);

    virtual void	dataSetAdded(IlUInt position = IlvLastPositionIndex);

    virtual void	update();

    virtual void	updateVirtualDataSets();
};

// --------------------------------------------------------------------------
// Class IlvSingleChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvSingleChartDisplayer
    : public IlvAbstractChartDisplayer
{
public:
    virtual ~IlvSingleChartDisplayer();

    virtual IlUInt	getDisplayersCount() const;

    //== Palette managements ======================
    virtual IlvPalette*	getPalette(IlUInt = 0) const;
    virtual void	setPalette(IlvPalette* pal, IlUInt index = 0);
    virtual IlvColor*	getForeground(IlUInt index = 0) const;
    virtual void	setForeground(IlvColor* color, IlUInt index = 0);
    virtual IlvColor*	getBackground(IlUInt index = 0) const;
    virtual void	setBackground(IlvColor* color, IlUInt index = 0);

    virtual void	drawFill(IlBoolean b);

    virtual void	setClosed(IlBoolean b);

    virtual IlBoolean	closePoints(IlvChartDisplayerPoints* dispPts,
				    const IlvTransformer*    t = 0) const;

    inline IlBoolean	isDrawingFill() const {return _drawFill;}

    inline IlBoolean	isClosed() const
			{
			    return (_flags & IlvCHTDispClosedFlag)
				? IlTrue
				: IlFalse;
			}

    inline IlvPos	getShiftOffset() const { return _shiftOffset; }

    inline void		setShiftOffset(IlvPos offset)
			{
			    _shiftOffset = offset;
			}

    virtual IlvDim	getSizeAlongBase() const;

    //== Legend ======================
    virtual const char*	getLegendText(IlUInt index = 0) const;

    virtual void	setLegendText(const char* text, IlUInt index = 0);

    virtual const char*	getInternalLegendText(IlUInt index = 0) const;

    //== Point Infos ======================
    virtual void	setPointInfoCollection(const IlvChartDataSet* dataSet,
					       IlvPointInfoCollection* ptInfoCollection);

    virtual IlvPointInfoCollection*
		getPointInfoCollection(const IlvChartDataSet* dataSet) const;

    virtual IlBoolean	usePointInfo() const;


    //== API ======================

    inline
    IlvChartDisplayerPointsFactory* getDisplayerPointsFactory() const
				{
				    return _displayerPointsFactory;
				}

    IlvChartDisplayerPointsFactory*
	setDisplayerPointsFactory(IlvChartDisplayerPointsFactory* factory);

    virtual IlvChartDisplayerPoints*	allocDisplayerPoints() const;

    virtual
    void	releaseDisplayerPoints(IlvChartDisplayerPoints* dispPts) const;

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;


    virtual IlUInt	getNearestPoint(IlvChartDataSet*& dataSet,
					const IlvPoint& viewPoint,
					IlvDim distance,
					IlvPoint& point,
					const IlvTransformer* t = 0) const;

    virtual IlUInt	getDisplayItem(IlvChartDataSet*& dataSet,
				       const IlvPoint& viewPoint,
				       const IlvTransformer* t) const;

    virtual IlBoolean	boundingBox(IlvRect& bbox,
				    const IlvTransformer* t = 0) const;

    inline void		getDataDisplayArea(IlvRect& dataDisplayArea,
					   const IlvTransformer* t = 0) const
			{
			    getChartGraphic()
				->getDataDisplayArea(getOrdinateInfo(),
						     dataDisplayArea,
						     t);
			}

    virtual void	drawDataPoint(IlUInt dataPtIdx,
				      IlvPort* dst,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;


    virtual void	drawDataPoints(IlUInt iMin,
				       IlUInt iMax,
				       IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;

    virtual IlBoolean	dataPointBBox(IlUInt dataPtIdx,
				      IlvRect& bbox,
				      IlBoolean takeInfoIntoAccount = IlTrue,
				      const IlvTransformer* t = 0) const;

    virtual void	dataPointsBBox(IlUInt iMin,
				       IlUInt iMax,
				       IlvRect& bbox,
				       IlBoolean takeInfoIntoAccount = IlTrue,
				       const IlvTransformer* t = 0) const;


    virtual IlBoolean	getDisplayPoint(const IlvChartDataSet* dataSet,
					IlUInt dataPtIdx,
					IlvPoint& point,
					const IlvTransformer* t = 0) const;



    virtual IlBoolean	setDataPoint(IlvChartDataSet* dataSet,
				     IlUInt dataPtIdx,
				     const IlvPoint& point,
				     const IlvTransformer* t = 0) const;

    virtual void
    treatPointsOutOfAbscissaLimits(const IlvRect& dataDisplayArea,
				   IlvChartDisplayerPoints* displayerPoints,
				   const IlvCoordInterval& abscissaRange,
				   const IlvPoint& minLimit,
				   const IlvPoint& maxLimit) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual void	setLegendItems(IlvChartLegend* legend) const;

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode mode);

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    // Persistence
    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropClassInfo();

protected:
    IlvPalette*				_palette;
    IlvPalette*				_fillPalette;
    IlBoolean				_drawFill;
    IlvPos				_shiftOffset;
    IlString				_legendText;
    IlAList				_pointInfoMap;
    IlvChartDisplayerPointsFactory*	_displayerPointsFactory;


    // Palette used for filling
    inline IlvPalette*	getFillPalette() const { return _fillPalette; }
    virtual void	computeFillPalette();

    // Constructors
    IlvSingleChartDisplayer(IlvPalette* palette = 0);

    IlvSingleChartDisplayer(IlvInputFile& file);

    IlvSingleChartDisplayer(const IlvSingleChartDisplayer& displayer);

    // Internal methods
    void		drawPart(const IlvCoordInterval& abscissaRange,
				 IlBoolean shiftOfCycleLength,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;

    IlUInt getNearestPointInsidePart(const IlvCoordInterval& abscissaRange,
				     IlBoolean shiftOfCycleLength,
				     IlvChartDataSet*& dataSet,
				     const IlvPoint& viewPoint,
				     IlvDim distance,
				     IlvPoint& point,
				     const IlvTransformer* t = 0) const;

    IlBoolean	boundingBoxOfPart(const IlvCoordInterval& abscissaRange,
				  IlBoolean shiftOfCycleLength,
				  IlvRect& partBBox,
				  IlBoolean takeInfoIntoAccount,
				  const IlvTransformer* t = 0) const;

    virtual void	drawPoints(IlvChartDisplayerPoints* displayerPoints,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    // To remove
    virtual void	drawPointInfo(const IlvChartDisplayerPoints* dspPoints,
				      IlUInt ptInfoIndex,
				      const IlvPoint& viewPoint,
				      IlvPort* dst,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;

    virtual void drawPointInfos(const IlvChartDisplayerPoints* displayerPoints,
			        IlvPort* dst,
			        const IlvTransformer* t = 0,
			        const IlvRegion* clip = 0,
				const IlvChartDataSet* dataSet = 0) const;

    virtual void boundingBoxOfPoints(IlvChartDisplayerPoints* displayerPoints,
				     IlvRect& bbox,
				     IlBoolean takeInfoIntoAccount = IlTrue,
				     const IlvTransformer* t = 0) const;

    virtual
    IlvDoublePoint* selectDataPointsForRange(const IlvCoordInterval& abscissaRange,
					     IlUInt& pointCount,
					     IlUInt*& dataPtIdxes,
					     const IlvTransformer* t = 0,
					     const IlvRect* clip = 0) const;

    virtual
    IlvDoublePoint* selectDataPointsForPoint(IlUInt dataPtIdx,
					     IlUInt& count,
					     IlUInt*& dataPtIdxes) const;

    virtual IlBoolean
    computeLimitsForDataSelection(const IlvRect& clipRect,
				  const IlvCoordInterval& abscissaRange,
				  const IlvCoordInterval& ordinateRange,
				  IlvCoordInterval& abscissaSelectionRange,
				  IlvCoordInterval& ordinateSelectionRange,
				  IlBoolean& dataToSelect,
				  const IlvTransformer* t = 0) const;

    virtual void computeItem(const IlvChartDisplayerPoints* displayerPoints,
			     IlUInt pointIndex,
			     IlUInt& usedPointsCount,
			     IlvPoint* points,
			     const IlvTransformer* t = 0) const = 0;

    virtual
    IlUInt getItemPointsCount(const IlvChartDisplayerPoints* displayerPoints) const;

    virtual void drawItem(const IlvChartDisplayerPoints* displayerPoints,
			  IlUInt pointIndex,
			  IlUInt pointsCount,
			  IlvPoint* points,
			  IlvPalette* itemPalette,
			  IlvPort* dst,
			  const IlvTransformer* t = 0,
			  const IlvRegion* clip = 0) const = 0;

    virtual
    void boundingBoxOfItem(const IlvChartDisplayerPoints* displayerPoints,
			   IlUInt pointIndex,
			   IlUInt pointsCount,
			   IlvPoint* points,
			   IlvRect& bbox,
			   IlBoolean takeInfoIntoAccount = IlTrue,
			   const IlvTransformer* t = 0) const;

     virtual
     IlvDoublePoint* selectDataPointsInRect(IlUInt& pointCount,
					    IlUInt*& dataPtIndexes,
					    IlvRect pickRect,
					    const IlvTransformer* t = 0) const;

    virtual IlUInt	pointsContains(const IlvPoint& viewPoint,
				       IlvChartDisplayerPoints*,
				       const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
// Class IlvCompositeChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCompositeChartDisplayer
    : public IlvAbstractChartDisplayer
{
public:
    virtual ~IlvCompositeChartDisplayer();

    //== Properties ======================
    virtual IlBoolean	isFilled() const;
    virtual IlBoolean	isContinuous() const;

    virtual IlBoolean	graphicalRepresentationByDataPoint() const;

    virtual IlBoolean	isViewable() const;

    //== Accessors ======================
    virtual void	setChartGraphic(IlvChartGraphic* chart);
    virtual void	setOrdinateInfo(IlvCoordinateInfo* ordinateInfo);


    //== Palette/Color managements ======================
    virtual IlvPalette*	getPalette(IlUInt index = 0) const;
    virtual void	setPalette(IlvPalette* pal, IlUInt index = 0);
    virtual IlvColor*	getForeground(IlUInt index = 0) const;
    virtual void	setForeground(IlvColor* color, IlUInt index = 0);
    virtual IlvColor*	getBackground(IlUInt index = 0) const;
    virtual void	setBackground(IlvColor* color, IlUInt index = 0);


    virtual void	drawFill(IlBoolean b);

    virtual void	setClosed(IlBoolean b);

    //== Legend ======================
    virtual const char*	getLegendText(IlUInt index = 0) const;
    virtual void	setLegendText(const char* text, IlUInt index = 0);

    virtual const char*	getInternalLegendText(IlUInt index = 0) const;

    //== Child displayers ======================
    virtual IlUInt	getDisplayersCount() const;

    IlvAbstractChartDisplayer*	getDisplayer(IlUInt index) const;

    virtual IlvAbstractChartDisplayer*
	getDisplayerForDataSet(const IlvChartDataSet* dataSet) const;

    IlvAbstractChartDisplayer*	removeDisplayer(IlUInt index);

    void		addDisplayer(IlvAbstractChartDisplayer* displayer,
				     IlUInt position=IlvLastPositionIndex);
    IlvAbstractChartDisplayer*	replaceDisplayer(IlUInt position,
						 IlvAbstractChartDisplayer* displayer);

    //== Point Infos ======================
    virtual
    void setPointInfoCollection(const IlvChartDataSet* dataSet,
				IlvPointInfoCollection* ptInfoCollection);

    virtual
    IlvPointInfoCollection*
	getPointInfoCollection(const IlvChartDataSet* dataSet) const;

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    virtual IlUInt	getNearestPoint(IlvChartDataSet*& dataSet,
					const IlvPoint& viewPoint,
					IlvDim distance,
					IlvPoint& point,
					const IlvTransformer* t = 0) const;

    virtual IlUInt	getDisplayItem(IlvChartDataSet*& dataSet,
				       const IlvPoint& viewPoint,
				       const IlvTransformer* t) const;

    virtual IlBoolean	boundingBox(IlvRect& bbox,
				    const IlvTransformer* t = 0) const;

    virtual void	drawDataPoint(IlUInt dataPtIdx,
				      IlvPort* dst,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;

    virtual void	drawDataPoints(IlUInt iMin,
				       IlUInt iMax,
				       IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;

    virtual IlBoolean	dataPointBBox(IlUInt dataPtIdx,
				      IlvRect& bbox,
				      IlBoolean takeInfoIntoAccount,
				      const IlvTransformer* t = 0) const;

    virtual void	dataPointsBBox(IlUInt iMin,
				       IlUInt iMax,
				       IlvRect& bbox,
				       IlBoolean takeInfoIntoAccount = IlTrue,
				       const IlvTransformer* t = 0) const;

    virtual IlBoolean	getDisplayPoint(const IlvChartDataSet* dataSet,
					IlUInt dataPtIdx,
					IlvPoint& point,
					const IlvTransformer* t = 0) const;

    virtual IlBoolean	setDataPoint(IlvChartDataSet* dataSet,
				     IlUInt dataPtIdx,
				     const IlvPoint& point,
				     const IlvTransformer* t = 0) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual void	setLegendItems(IlvChartLegend* legend) const;

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode mode);

    inline IlvChartDisplayerFactory*	getDisplayerFactory() const
					{
					    return _displayerFactory;
					}

    IlvChartDisplayerFactory*
			setDisplayerFactory(IlvChartDisplayerFactory* factory,
					    IlBoolean reCreate = IlFalse);

    IlvAbstractChartDisplayer* setDisplayerModel(IlvAbstractChartDisplayer* model);


    inline
    IlvAbstractChartDisplayer*	getDisplayerModel() const
				{
				    return _dispModel;
				}

    // Persistence
    virtual void		write(IlvOutputFile& file) const;

    IlvDeclarePropClassInfo();

protected:
    IlArray			_displayers;
    IlvChartDisplayerFactory*	_displayerFactory;
    IlArray			_palettes;
    IlvAbstractChartDisplayer*	_dispModel;


    //== Constructors =======================
    IlvCompositeChartDisplayer(IlvChartDisplayerFactory* factory =0);

    IlvCompositeChartDisplayer(IlvInputFile& file);

    IlvCompositeChartDisplayer(const IlvCompositeChartDisplayer& displayer);

    virtual void	update();

    virtual void	updateDisplayers();

    void		initDisplayers(IlUInt count,
				       IlvPalette* const* palettes = 0);

    virtual
    IlvAbstractChartDisplayer*	makeDisplayer(IlUInt idx,
					      IlvPalette* pal = 0);

    virtual
    IlvAbstractChartDisplayer*	createDisplayer(IlUInt idx,
						IlvPalette* pal = 0);

};

// --------------------------------------------------------------------------
// IlvChartDisplayerFactory
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDisplayerFactory
{
public:

    // Not documented since it does nothing special.
    virtual ~IlvChartDisplayerFactory();

    virtual IlvChartDisplayerFactory*	copy() const = 0;

    virtual IlvAbstractChartDisplayer*
		createDisplayer(IlvCompositeChartDisplayer* parent,
				IlUInt idx,
				IlvPalette* palette=0) = 0;

protected:
    IlvChartDisplayerFactory() {}

    IlvChartDisplayerFactory(const IlvChartDisplayerFactory&) {}
};


// --------------------------------------------------------------------------
// IlvChartDefaultColors
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartDefaultColors
{
    class ILVCHTEXPORTED IlvRGB 
    {
    public:
        IlvRGB() : r(0), g(0), b(0) {}
        IlvRGB(short rr, short gg, short bb) : r(rr), g(gg), b(bb) {}
        short r, g, b;
    };

public:
    IlvChartDefaultColors(IlvDisplay* display);

    IlvColor*		getColor(IlUInt colNb);

    inline IlUInt	getNbColors() const { return 56; }

protected:
    IlvRGB		_colors[60];
    IlvDisplay*		_display;
};


ILVCHTMODULEINIT(display);

#endif /* !__Ilv_Charts_Display_H */
