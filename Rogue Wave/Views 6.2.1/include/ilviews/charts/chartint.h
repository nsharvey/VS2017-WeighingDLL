// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/chartint.h
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
// Declaration of chart interactor classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Chartint_H
#define __Ilv_Charts_Chartint_H

#if !defined(__Ilv_Base_Inter_h)
#include <ilviews/base/inter.h>
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


// Forward decl.
class ILVCHTEXPORTED IlvChartGraphic;
class ILVCHTEXPORTED IlvAbstractChartCursor;
class ILVCHTEXPORTED IlvAbstractChartDisplayer;
class ILVCHTEXPORTED IlvChartDataSet;
class ILVCHTEXPORTED IlvChartDataPointInfo;
class ILVCHTEXPORTED IlvChartInteractor;
class IlvCHTInfoView;

// Macro to declare and define the builder method
#if !defined(ILVDECLARECHARTINTERACTOR)
#define ILVDECLARECHARTINTERACTOR(name, classname) \
    static IlvChartInteractor* name () {	    \
	  static IlvChartInteractor* inter=0;	    \
	  if (!inter) inter= new classname ();	    \
	  return inter;				    \
    }
#endif /* !ILVDECLARECHARTINTERACTOR */

#define ILVINTERBUILDER(name) Make ## name
#define ILVINTERREG(name) name ## Reg_
#define IlvRegisterChartInteractor(classname, superclass, sharedName)	\
    ILVDECLARECHARTINTERACTOR(ILVINTERBUILDER(classname), classname)	\
    static int ILVINTERREG(classname) =					\
	IlvChartInteractor::Register(sharedName,ILVINTERBUILDER(classname));

class ILVCHTEXPORTED IlvChartInteractorManager : public IlvNamedProperty
{
    enum {
	ShowAbscissaCursor	= 0x0001,
	ShowOrdinateCursor	= 0x0002,
	AbscissaCursorVisible	= 0x0004,
	OrdinateCursorVisible	= 0x0008
    };

public:
    IlvChartInteractorManager();

    virtual ~IlvChartInteractorManager();

    inline
    IlvChartInteractorManager* set(IlvChartGraphic* chart)
			{
			    return Set(chart, this);
			}

    static
    IlvChartInteractorManager* Set(IlvChartGraphic* chart,
				   IlvChartInteractorManager* interMgr);

    static IlvChartInteractorManager* Remove(IlvChartGraphic* chart);

    static IlvChartInteractorManager* Get(const IlvChartGraphic* chart);

    static IlSymbol*	GetSymbol();

    IlUInt		getCardinal() const;

    IlvChartInteractor* getInteractor(IlUInt index) const;

    IlBoolean		removeInteractor(IlvChartInteractor* interactor);

    IlBoolean		removeInteractor(const char* name);

    void		removeInteractors();

    void		addInteractor(IlvChartInteractor* interactor,
				      IlUInt position=IlvLastPositionIndex);

    void		addInteractor(const char* name,
				      IlUInt position = IlvLastPositionIndex);

    //== Cursor methods ============
    inline IlBoolean	isShowingAbscissaCursor() const
			{
			    return (_cursorVisibility & ShowAbscissaCursor)
				? IlTrue
				: IlFalse;
			}

    void		showAbscissaCursor(IlBoolean show);

    inline IlBoolean	isShowingOrdinateCursor() const
			{
			    return (_cursorVisibility & ShowOrdinateCursor)
				? IlTrue
				: IlFalse;
			}

    void		showOrdinateCursor(IlBoolean show);

    virtual IlvAbstractChartCursor* getAbscissaCursor();

    virtual IlvAbstractChartCursor* getOrdinateCursor();

    void		removeCursors();

    void		moveCursors(IlBoolean abscissa,
				    IlBoolean ordinate,
				    const IlvPoint& point,
				    const IlvTransformer* t,
				    IlBoolean reDraw = IlTrue);

    void		setCursorsVisible(IlBoolean abscissa,
					  IlBoolean ordinate,
					  IlBoolean visible);

    void		setAbscissaCursorVisible(IlBoolean visible);

    void		setOrdinateCursorVisible(IlBoolean visible);

    void		saveCursorsVisibility();

    void		restoreCursorsVisibility(const IlvPoint& point,
						 const IlvTransformer* t);


    //== Handled Ordinate axis
    IlUInt		getOrdinateAxisIndex() const { return _ordAxisIdx; }

    void		setOrdinateAxisIndex(IlUInt index)
			{
			    _ordAxisIdx = index;
			}

    IlvCoordinateInfo*	getOrdinateInfo() const;

    virtual void	getCallbackTypes(IlUInt& count,
					 const char* const**     names,
					 const IlSymbol* const** types) const;

    // Virtuals from IlvNamedProperty
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();
    //virtual const IlSymbol*  getValueName() const;
    //DeclareValueAccessors();

    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvChartInteractorManager);

protected:
    IlArray			_interactors;
    IlvChartGraphic*		_chart;
    IlvAbstractChartCursor*	_abscissaCursor;
    IlvAbstractChartCursor*	_ordinateCursor;
    int				_cursorVisibility;
    IlUInt			_ordAxisIdx;
};


class ILVCHTEXPORTED IlvChartInteractor : public IlvInteractor
{
public:
    virtual ~IlvChartInteractor();
    typedef IlvChartInteractor* (*IlvChartInteractorBuilder)();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& event,
				    const IlvTransformer* t = 0) = 0;

    virtual IlBoolean	isShowingAbscissaCursor() const;

    virtual IlBoolean	isShowingOrdinateCursor() const;

    virtual void	startSequence(IlvChartGraphic* chart,
				      const IlvEvent& event,
				      const IlvTransformer* t);

    virtual void	endSequence(IlvChartGraphic* chart,
				    const IlvEvent& event,
				    const IlvTransformer* t);

    inline IlBoolean	isShared() const { return (_refCount!=0); }

    virtual IlBoolean	accept(const IlvGraphic* obj) const;

    //== Registering & IO ========
    static int		Register(const char* name,
				 IlvChartInteractorBuilder builder);

    static
    IlvChartInteractor*	Get(const char* name);

    static void		Save(IlvChartInteractor*,ILVSTDPREF ostream&);
    static
    IlvChartInteractor* Read(ILVSTDPREF istream&);

    static const char* const*
	GetRegisteredInteractors(IlUInt& count,
				 IlBoolean sortStrings = IlTrue,
				 IlBoolean createArray = IlFalse);

    static void		FreeRegistry();

    IlvDeclarePropClassInfo();

protected:
    IlvChartInteractor();
    IlvChartInteractor(const IlvChartInteractor&);
    IlvChartInteractor(IlvInputFile&);

    virtual void	write(IlvOutputFile&) const;

protected:
    IlUInt		getFlags() const { return _flags; }
    void		setFlags(IlUInt f) { _flags = f; }

    virtual IlvCursor*	getViewCursor(const IlvEvent&) const;
    static void		PushCursor(IlvView*, IlvCursor*);
    static void		PopCursor(IlvView*);
    static IlSymbol*	GetCursorProperty();
    static IlvCursor*	GetFirstCursor(const IlvView* v);

    static void		CallCallbacks(IlvChartGraphic* chart,
				      IlvInteractor* inter);

    IlUInt _flags;
};

class ILVCHTEXPORTED IlvChartInteractorDispatcher : public IlvChartInteractor
{
public:
    IlvChartInteractorDispatcher();
    virtual ~IlvChartInteractorDispatcher();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& event,
				    const IlvTransformer* t = 0);

    virtual void	abort(IlvGraphic* chart);

    virtual IlBoolean	accept(const IlvGraphic* g) const;

    virtual void	getCallbackTypes(IlUInt& count,
					 const char* const**     names,
					 const IlSymbol* const** types) const;

    DeclareInteractorTypeInfoRO(IlvChartInteractorDispatcher);

protected:
    IlvChartInteractor* _activeInteractor;
};


class ILVCHTEXPORTED IlvChartZoomInteractor : public IlvChartInteractor
{
public:
    enum ZoomState {
	Zooming,
	UnZooming
    };

    IlvChartZoomInteractor(IlUShort whichButton = IlvLeftButton);

    virtual ~IlvChartZoomInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    virtual IlBoolean	isShowingAbscissaCursor() const;
    virtual IlBoolean	isShowingOrdinateCursor() const;

    virtual void	abort(IlvGraphic*);

    IlUShort		getZoomSteps() { return _zoomSteps; }

    void		setZoomSteps(IlUShort count) { _zoomSteps = count; }

    ZoomState		getState() const { return _zoomState; }

    DeclareInteractorTypeInfo(IlvChartZoomInteractor);

protected:
    IlUShort		_whichButton;
    IlvRect		_zoomRect;
    IlvCoordInterval	_abscissaRange;
    IlvCoordInterval	_ordinateRange;
    IlvPoint		_startZoom;
    ZoomState		_zoomState;
    IlUShort		_zoomSteps;

    virtual void	doIt(IlvChartGraphic* chart,
			     const IlvCoordInterval& abscissaRange,
			     const IlvCoordInterval& ordinateRange);

    virtual void	drawGhost(const IlvChartGraphic* chart,
				  const IlvCoordInterval& abscissaRange,
				  const IlvCoordInterval& ordinateRange,
				  const IlvTransformer* t) const;

    virtual void	adjustZoomRange(const IlvChartGraphic* chart,
					IlvCoordInterval& abscissaRange,
					IlvCoordInterval& ordinateRange);

    void		setState(ZoomState state) { _zoomState=state; }

    virtual IlvCursor*	getViewCursor(const IlvEvent&) const;
    IlBoolean		checkButtonEvent(const IlvEvent&);
};


class ILVCHTEXPORTED IlvChartDataInteractor : public IlvChartInteractor
{
public:
    struct ILVCHTEXPORTED ChartDataStruct
    {
	ChartDataStruct() { reset();}
	IlvAbstractChartDisplayer*	_disp;
	IlvChartDataSet*		_dataSet;
	IlUInt				_pointIndex;
	inline void	reset()
			{
			    _disp = 0;
			    _dataSet = 0;
			    _pointIndex = IlvBadIndex;
			}
    };

    enum PickingMode {
        ItemPicking,
        NearestPointPicking
    };

    PickingMode		getPickingMode() const { return _pickingMode; }

    void		setPickingMode(PickingMode m) { _pickingMode = m; }

    virtual void	abort(IlvGraphic*);

    inline
    static IlvDim	GetPrecision() { return _precision; }

    inline static void	SetPrecision(IlvDim dim) {_precision = dim;}

    static inline void	SetPrecicion(IlvDim dim) {SetPrecision(dim);}

    IlvDeclarePropClassInfo();

protected:
    static IlvDim	_precision;

    IlvChartDataInteractor();

    IlvChartDataInteractor(const IlvChartDataInteractor&);
    IlvChartDataInteractor(IlvInputFile& file);

    virtual void	write(IlvOutputFile&) const;

    virtual IlBoolean	queryData(IlvChartGraphic* chart,
				  IlvPoint& evp,
				  const IlvTransformer* t);

    IlBoolean		isHandlingData() const
			{
			    return getHandledDisplayer() != 0;
			}

    IlvAbstractChartDisplayer* getHandledDisplayer() const
			{
			    return getHandledData()._disp;
			}

    IlvChartDataSet*	getHandledDataSet() const
			{
			    return getHandledData()._dataSet;
			}

    IlUInt		getHandledPointIndex() const
			{
			    return getHandledData()._pointIndex;
			}

    const ChartDataStruct& getHandledData() const { return _handledData; }
    ChartDataStruct&	getHandledData() { return _handledData; }

    void		init();

    ChartDataStruct	_handledData;
    PickingMode		_pickingMode;
};


class ILVCHTEXPORTED IlvChartDragPointInteractor
    : public IlvChartDataInteractor
{
public:
    IlvChartDragPointInteractor(IlUShort whichButton = IlvLeftButton);

    virtual ~IlvChartDragPointInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    virtual IlBoolean	isShowingAbscissaCursor() const;
    virtual IlBoolean	isShowingOrdinateCursor() const;

    virtual void	abort(IlvGraphic*);

    DeclareInteractorTypeInfo(IlvChartDragPointInteractor);

protected:
    IlUShort		_whichButton;
    IlvPoint		_dragPoint;

    virtual void	doIt(IlvChartGraphic* chart,
			     const IlvPoint& p,
			     const IlvTransformer* t);

    virtual void	drawGhost(IlvChartGraphic* chart,
				  const IlvPoint& point);

    virtual void	validate(IlvChartGraphic* chart,
				 IlvDoublePoint& dataPoint);

    virtual IlvCursor*	getViewCursor(const IlvEvent&) const;
};


class ILVCHTEXPORTED IlvChartHighlightPointInteractor
    : public IlvChartDataInteractor
{
public:
    typedef void (*Action)(IlvChartGraphic* chart,
			   IlvAbstractChartDisplayer* disp,
			   IlvChartDataSet* dataSet,
			   IlUInt pointIndex,
			   IlBoolean highlight);


    typedef Action HighlightAction; // beta2 compat

    IlvChartHighlightPointInteractor();

    virtual ~IlvChartHighlightPointInteractor();

    void		setAction(Action action) { _action = action; }

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    DeclareInteractorTypeInfo(IlvChartHighlightPointInteractor);

protected:
    virtual void	doIt(IlvChartGraphic* chart,
			     IlvAbstractChartDisplayer* disp,
			     IlvChartDataSet* dataSet,
			     IlUInt pointIndex,
			     IlBoolean highlight,
			     IlvEvent& ev);

    Action		_action;
};


class ILVCHTEXPORTED IlvChartInfoViewInteractor
    : public IlvChartHighlightPointInteractor
{
public:
    IlvChartInfoViewInteractor();

    virtual ~IlvChartInfoViewInteractor();

    void		setFollowingMouse(IlBoolean follow)
			{
			    _followMouse = follow;
			}

    IlBoolean		isFollowingMouse() { return _followMouse; }

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    DeclareInteractorTypeInfo(IlvChartInfoViewInteractor);

protected:
    virtual
    const char*		getHighlightText(IlvChartGraphic* chart,
					 IlvAbstractChartDisplayer* disp,
					 IlvChartDataSet* dataSet,
					 IlUInt pointIndex);
    virtual void	doIt(IlvChartGraphic* chart,
			     IlvAbstractChartDisplayer* disp,
			     IlvChartDataSet* dataSet,
			     IlUInt pointIndex,
			     IlBoolean highlight,
			     IlvEvent& ev);

    virtual IlvPoint	computePosition(IlvDim tooltipW,
					IlvDim tooltipH,
					IlvEvent& ev);

    IlvCHTInfoView*	_infoView;

    IlBoolean		_followMouse;
};

class ILVCHTEXPORTED IlvChartSelectInteractor : public IlvChartDataInteractor
{
public:
    typedef void (*Action)(IlvChartGraphic* chart,
			   IlvAbstractChartDisplayer* disp,
			   IlvChartDataSet* dataSet,
			   IlUInt pointIndex,
			   IlBoolean select);

    IlvChartSelectInteractor(IlUShort whichButton = IlvLeftButton);

    virtual IlBoolean handleEvent(IlvGraphic* chart,
				  IlvEvent& ev,
				  const IlvTransformer* t = 0);

    void		setAction(Action action) { _action = action; }

    DeclareInteractorTypeInfo(IlvChartSelectInteractor);

protected:
    IlUShort		_whichButton;
    Action		_action;

    static
    const ChartDataStruct* GetSelectedData(const IlvChartGraphic* chart);
    static IlSymbol* GetSelectedSymbol();

    void		iSelect(IlvChartGraphic* chart,
				IlvAbstractChartDisplayer* disp,
				IlvChartDataSet* dataSet,
				IlUInt pointIndex,
				IlBoolean select);

    void		markSelected(IlvChartGraphic* chart,
				     IlvAbstractChartDisplayer* disp,
				     IlvChartDataSet* dataSet,
				     IlUInt pointIndex,
				     IlBoolean select) const;

    virtual
    IlvChartDataPointInfo* makeSelectionInfo(const IlvChartGraphic* chart,
					     IlvAbstractChartDisplayer* disp,
					     IlvChartDataSet* dataSet,
					     IlUInt pointIndex) const;

    virtual void	doIt(IlvChartGraphic* chart,
			     IlvAbstractChartDisplayer* disp,
			     IlvChartDataSet* dataSet,
			     IlUInt pointIndex,
			     IlBoolean select);
};


class ILVCHTEXPORTED IlvChartCrossHairInteractor : public IlvChartInteractor
{
public:
    IlvChartCrossHairInteractor();

    virtual ~IlvChartCrossHairInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    virtual IlBoolean	isShowingAbscissaCursor() const;
    virtual IlBoolean	isShowingOrdinateCursor() const;

    DeclareInteractorTypeInfoRO(IlvChartCrossHairInteractor);
};

class ILVCHTEXPORTED IlvChartPanInteractor : public IlvChartInteractor
{
public:
    IlvChartPanInteractor(IlUShort whichButton = IlvRightButton);
    virtual ~IlvChartPanInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    DeclareInteractorTypeInfo(IlvChartPanInteractor);

protected:
    IlUShort		_whichButton;
    IlvPoint		_lastPosition;
    virtual void	doIt(IlvChartGraphic* chart,
			     const IlvPoint& from,
			     const IlvPoint& to);

    virtual IlvCursor*	getViewCursor(const IlvEvent&) const;
};

class ILVCHTEXPORTED IlvChartScrollInteractor : public IlvChartInteractor
{
public:
    IlvChartScrollInteractor();
    virtual ~IlvChartScrollInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic* chart,
				    IlvEvent& ev,
				    const IlvTransformer* t = 0);

    DeclareInteractorTypeInfoRO(IlvChartScrollInteractor);

protected:
    virtual IlDouble	getDeltaCoordinate(const IlvChartGraphic* chart,
					   const IlvCoordinateInfo* coordInfo,
					   IlBoolean positive) const;
    virtual void	doIt(IlvChartGraphic* chart,
			     IlvCoordinateInfo* coordInfo,
			     IlDouble delta);
};


ILVCHTMODULEINIT(chartint);

#endif /* !__Ilv_Charts_Chartint_H */
