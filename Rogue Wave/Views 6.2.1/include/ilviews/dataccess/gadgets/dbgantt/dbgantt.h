// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbgantt/dbgantt.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliDbGantt class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbgantt_H
#define __Ili_Dbgantt_H

#if !defined(__Ilv_Graphics_Scale_H)
#  include <ilviews/graphics/scale.h>
#endif
#if !defined(__Ilv_Ganttfrm_H)
#  include <ilviews/gantt/ganttfrm.h>
#endif
#if !defined(__Ilv_Ganttint_H)
#  include <ilviews/gantt/ganttint.h>
#endif
#if !defined(__Ilv_Graphics_Gauge_H)
#  include <ilviews/graphics/gauge.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#  include <ilviews/graphics/rectangl.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#  include <ilviews/grapher/grapher.h>
#endif
#if !defined(__Ilv_Graphics_Polyline_H)
#  include <ilviews/graphics/polyline.h>
#endif
#if !defined(__Ili_Reposit_H)
#  include <ilviews/dataccess/reposit.h>
#endif
#if !defined(__Ili_String_H)
#  include <ilviews/dataccess/string.h>
#endif
#if !defined(__Ili_Tblhook_H)
#  include <ilviews/dataccess/tblhook.h>
#endif
#if !defined(__Ili_Mdatasrc_H)
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif
#if !defined(__Ili_Dsusage_H)
#  include <ilviews/dataccess/gadgets/dsusage.h>
#endif
#if !defined(__Ili_Gdtmodel_H)
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

#define ILIDBGANTTW 24

// --------------------------------------------------------------------------
enum IliDbGanttWhichDs {
    IliDbGanttResDs = 0,
    IliDbGanttActDs,
    IliDbGanttCntDs,
    IliDbGanttPreDs,
    IliDbGanttBrkDs,
    IliDbGanttLoaDs,
    IliDbGanttDsCount
};

// --------------------------------------------------------------------------
enum IliDbGanttResCols {
    IliDbGanttResIdentifier = 0,
    IliDbGanttResHeight,
    IliDbGanttResColCount
};

// --------------------------------------------------------------------------
enum IliDbGanttActCols {
    IliDbGanttActStartMin = 0,
    IliDbGanttActStartMax,
    IliDbGanttActEndMin,
    IliDbGanttActEndMax,
    IliDbGanttActIdentifier,
    IliDbGanttActLabel,
    IliDbGanttActColCount
};

// --------------------------------------------------------------------------
enum IliDbGanttCntCols {
    IliDbGanttCntIdentifier = 0,
    IliDbGanttCntResIdentifier,
    IliDbGanttCntActIdentifier,
    IliDbGanttCntCapacity,
    IliDbGanttCntForeground,
    IliDbGanttCntBackground,
    IliDbGanttCntStart,
    IliDbGanttCntEnd,
    IliDbGanttCntColCount
};

// --------------------------------------------------------------------------
enum IliDbGanttPreCols {
    IliDbGanttPreFrom = 0,
    IliDbGanttPreTo,
    IliDbGanttPreType,
    IliDbGanttPreDelay,
    IliDbGanttPreColor,
    IliDbGanttPreColCount
};

// --------------------------------------------------------------------------
enum IliDbGanttBrkCols {
    IliDbGanttBrkIdentifier = 0,
    IliDbGanttBrkResIdentifier,
    IliDbGanttBrkFrom,
    IliDbGanttBrkTo,
    IliDbGanttBrkColCount
};

// --------------------------------------------------------------------------
enum IliDbGanttLoaCols {
    IliDbGanttLoaResIdentifier = 0,
    IliDbGanttLoaFrom,
    IliDbGanttLoaTo,
    IliDbGanttLoaCapacity,
    IliDbGanttLoaColCount
};

// --------------------------------------------------------------------------
enum IliDbGanttColor {
    IliDbGanttActivePeriodColor = 0,
    IliDbGanttInactivePeriodColor,
    IliDbGanttBreakColor,
    IliDbGanttLoadColor,
    IliDbGanttPrecedenceColor,
    IliDbGanttDelimiterColor,
    IliDbGanttColorCount
};

// --------------------------------------------------------------------------
enum IliDbGanttStringInfo {
    IliDbGanttStrResIdentifier = 0,
    IliDbGanttStrActIdentifier,
    IliDbGanttStrCntIdentifier,
    IliDbGanttStrBrkIdentifier,
    IliDbGanttStrLabel,
    IliDbGanttStrBackground,
    IliDbGanttStrForeground,
    IliDbGanttStrFromName,
    IliDbGanttStrToName,
    IliDbGanttStrInfoCount
};

// --------------------------------------------------------------------------
enum IliDbGanttIntegerInfo {
    IliDbGanttIntStartMin = 0,
    IliDbGanttIntStartMax,
    IliDbGanttIntEndMin,
    IliDbGanttIntEndMax,
    IliDbGanttIntCapacity,
    IliDbGanttIntDelay,
    IliDbGanttIntFrom,
    IliDbGanttIntTo,
    IliDbGanttIntType,
    IliDbGanttIntMaxLoad,
    IliDbGanttIntInfoCount
};

// --------------------------------------------------------------------------
enum IliDbGanttCallbackName {
    IliDbGanttCBCreateConstraint = 0,
    IliDbGanttCBCreatePrecedence,
    IliDbGanttCBCreateBreak,
    IliDbGanttCBCreateLoad,
    IliDbGanttCBReplaceConstraint,
    IliDbGanttCBReplacePrecedence,
    IliDbGanttCBReplaceBreak,
    IliDbGanttCBReplaceLoad,
    IliDbGanttCBDeleteConstraint,
    IliDbGanttCBDeletePrecedence,
    IliDbGanttCBDeleteBreak,
    IliDbGanttCBDeleteLoad,
    IliDbGanttCallbackCount
};

// --------------------------------------------------------------------------
enum IliDbGanttRefresh {
    IliDbGanttRefreshResHeader = 0,
    IliDbGanttRefreshRes,
    IliDbGanttRefreshAct,
    IliDbGanttRefreshCnt,
    IliDbGanttRefreshPre,
    IliDbGanttRefreshBrk,
    IliDbGanttRefreshLoa,
    IliDbGanttRefreshGrid,
    IliDbGanttRefreshCount
};

class IliDbGantt;

// --------------------------------------------------------------------------
typedef IlvGraphic* (*IliDbGanttCallback)(IliDbGantt* gantt,
					  IlvGraphic* old,
					  IlAny arg);

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttPeriod
{
public:
    IliDbGanttPeriod();
    ~IliDbGanttPeriod() {}

    IliDbGanttPeriod& operator	=(const IliDbGanttPeriod& o);

    IlBoolean			isActive(const IliDate&);
    void			setUnit(IliDbGanttPeriodUnit);
    IliDbGanttPeriodUnit	getUnit() const;
    void			setTest(IliDbGanttPeriodTest);
    IliDbGanttPeriodTest	getTest() const;
    void			setValue(IlInt, IlInt);
    IlInt			getValue(IlInt) const;

protected:
    IlInt			_unit;
    IlInt			_test;
    IlInt			_value[4];
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScale
{
public:
    IliDbGanttScale(IliDbGantt*, IlInt = 1);
    virtual ~IliDbGanttScale();

    virtual IliDbScaleType	getType() const;
    virtual void	computeLastValues(IlInt count);
    virtual
    IlvGraphicSet*	createScales();
    virtual
    IlvGraphicSet*	createBackground(IlInt);
    virtual
    IlvGraphicSet*	createGrid(IlInt);
    virtual void	initializeDateInfo(IliDate&);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;

    IlInt		convertDay(IlInt, IliScaleUnit, IlBoolean) const;
    IlInt		convertHour(IlInt, IliScaleUnit, IlBoolean) const;
    IlInt		convertMinute(IlInt, IliScaleUnit, IlBoolean) const;

    // Calendar
    const char*		getMonthName(IlInt, IlBoolean = IlTrue);
    const char*		getWeekDayName(IlInt,
				       IlBoolean = IlTrue,
				       IlInt = 3);
    const char*		getDateName(const IliDate&);

    // Rectangle scales
    void		resetScales();
    void		allocScales(IlInt);
    void		addRectScale(IlvGraphicSet*, IlvRectangularScale*);
    IlvRectangularScale* newRectScale(IlInt, IlInt,
				      const char*,
				      IlInt, IlInt, IlInt);

    // Grid
    virtual void	createDefaultGrid(IlInt);

    // Other
    IlInt		getCount() const;

protected:
    IliDbGantt*		_gantt;
    IliDate		_ref;
    IliDate		_last;

    // Rectangle scales
    IlInt		_pas;
    IlvRectangularScale** _rScales;
    IlInt		_rScalesCount;
    IlInt		_rScalesAlloc;
    IlInt		_stepCount;

    // Grid
    IlvRectangle**	_rGrids;
    IlInt		_rGridCount;
    IlvLine*		_rLine;

    // Others
    IliString		_buffer;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleNumeric
: public IliDbGanttScale
{
public:
    IliDbGanttScaleNumeric(IliDbGantt*);

    virtual
    IliDbScaleType	getType() const;
    virtual void	computeLastValues(IlInt);
    virtual IlvGraphicSet*	createScales();
    virtual void	initializeDateInfo(IliDate&);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleDate
: public IliDbGanttScale
{
public:
    IliDbGanttScaleDate(IliDbGantt*, IlBoolean);

    virtual IliDbScaleType	getType() const;
    virtual void		computeLastValues(IlInt);
    virtual IlvGraphicSet*	createScales();
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;

protected:
    IlBoolean		_dispWeekDay;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleDateHour
: public IliDbGanttScale
{
public:
    IliDbGanttScaleDateHour(IliDbGantt*, IlInt);

    virtual IliDbScaleType	getType() const;
    virtual IlvGraphicSet*	createScales();
    virtual void	computeLastValues(IlInt);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleDateMinute
    : public IliDbGanttScaleDateHour
{
public:
    IliDbGanttScaleDateMinute(IliDbGantt*,IlInt);

    virtual
    IliDbScaleType	getType() const;
    virtual
    IlvGraphicSet*	createScales();
    virtual void	computeLastValues(IlInt);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleMinutes
: public IliDbGanttScale
{
public:
    IliDbGanttScaleMinutes(IliDbGantt*);

    virtual IliDbScaleType	getType() const;
    virtual IlvGraphicSet*	createScales();
    virtual void	computeLastValues(IlInt);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleSecondes
: public IliDbGanttScale
{
public:
    IliDbGanttScaleSecondes(IliDbGantt*, IlInt);

    virtual
    IliDbScaleType	getType() const; 
    virtual
    IlvGraphicSet*	createScales();
    virtual void	computeLastValues(IlInt);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttScaleWeek
: public IliDbGanttScale
{
public:
    IliDbGanttScaleWeek(IliDbGantt*,IlInt pas);

    virtual IliDbScaleType	getType() const;
    virtual IlvGraphicSet*	createScales();
    virtual void	computeLastValues(IlInt);
    virtual void	getNextDate(IliDate&, IlInt = 1);
    virtual IlInt	convertValue(IlInt, IliScaleUnit, IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttInfo
{
public:
    IliDbGanttInfo(IliDbGantt* gantt = 0);
    ~IliDbGanttInfo();

    void		setDbGantt(IliDbGantt*);
    void		reset();

    // Operators
    IliDbGanttInfo& operator=(const IliDbGanttInfo&);
    IlInt operator==(const IliDbGanttInfo&) const;
    IlInt operator!=(const IliDbGanttInfo&) const;

    // Resources
    void		setResIdentifier(const char*);
    const char*		getResIdentifier() const;

    void		setResExtIdentifier(const char*);
    const char*		getResExtIdentifier() const;

    void		setLine(IlvGanttLine*);
    IlvGanttLine*	getLine() const;
    void		computeLine();

    // Activity
    void		setStartMin(IlInt);
    IlInt		getStartMin() const;
    IlInt		getStartMinDraw() const;
    void		setStartMax(IlInt);
    IlInt		getStartMax() const;
    IlInt		getStartMaxDraw() const;
    void		setEndMin(IlInt);
    IlInt		getEndMin() const;
    IlInt		getEndMinDraw() const;
    void		setEndMax(IlInt);
    IlInt		getEndMax() const;
    IlInt		getEndMaxDraw() const;

    void		setActIdentifier(const char*);
    const char*		getActIdentifier() const;

    void		setActExtIdentifier(const char*);
    const char*		getActExtIdentifier() const;

    // Constraint
    void		setCntIdentifier(const char*);
    const char*		getCntIdentifier() const;

    void		setCntExtIdentifier(const char*);
    const char*		getCntExtIdentifier() const;

    void		setBackground(const char*);
    const char*		getBackground() const;
    IlvColor*		getBackground(IlvDisplay*) const;

    void		setForeground(const char*);
    const char*		getForeground() const;
    IlvColor*		getForeground(IlvDisplay*) const;

    // Precedence
    void		setPreIdentifier(const char*);
    const char*		getPreIdentifier() const;

    void		setFromName(const char*);
    const char*		getFromName() const;
    void		setFromExtName(const char*);
    const char*		getFromExtName() const;
    IlvGanttNode*	getNodeFrom() const;

    void		setToName(const char*);
    const char*		getToName() const;
    void		setToExtName(const char*);
    const char*		getToExtName() const;
    IlvGanttNode*	getNodeTo() const;

    void		setType(IlInt);
    IlInt		getType() const;

    void		setDelay(IlInt);
    IlInt		getDelay() const;

    void		computeFromTo();
    IlBoolean		isValidPrecedence() const;

    // Breaks
    void		setBrkIdentifier(const char*);
    const char*		getBrkIdentifier() const;

    void		setBrkExtIdentifier(const char*);
    const char*		getBrkExtIdentifier() const;

    // Load
    void		setLoaIdentifier(const char*);
    const char*		getLoaIdentifier() const;
    void		computeLoaIdentifier();
    IlInt		getMaxLoad() const;

    // Common
    void		setCapacity(IlInt);
    IlInt		getCapacity() const;

    void		setLabel(const char*, IlInt = 0);
    const char*		getLabel(IlInt = 0) const;
    void		setLabelCount(IlInt);
    IlInt		getLabelCount() const;

    void		setFrom(IlInt);
    IlInt		getFrom() const;
    IlInt		getFromDraw() const;

    void		setTo(IlInt);
    IlInt		getTo() const;
    IlInt		getToDraw() const;

protected:
    IliDbGantt*		_gantt;

    // Resources
    IliString		_resId;
    IliString		_resExtId;
    IlvGanttLine*	_line;

    // Activity
    IliString		_actId;
    IliString		_actExtId;
    IlInt		_startMin;
    IlInt		_startMinDraw;
    IlInt		_startMax;
    IlInt		_startMaxDraw;
    IlInt		_endMin;
    IlInt		_endMinDraw;
    IlInt		_endMax;
    IlInt		_endMaxDraw;

    // Constraint
    IliString		_cntId;
    IliString		_cntExtId;
    IliString		_background;
    IliString		_foreground;

    // Precedence
    IliString		_preId;
    IliString		_fromName;
    IliString		_fromExtName;
    IliString		_toName;
    IliString		_toExtName;
    IlInt		_type;
    IlInt		_delay;
    IlvGanttNode*	_fromNode;
    IlvGanttNode*	_toNode;

    // Break
    IliString		_brkId;
    IliString		_brkExtId;

    // Load
    IliString		_loaId;

    // Common
    IlInt		_capacity;
    IlInt		_fromDraw;
    IlInt		_from;
    IlInt		_to;
    IlInt		_toDraw;
    IliString*		_labels;
    IlInt		_labelCount;

    // Convert
    IlInt		convert(IlInt);
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttInteractor
    : public IlvGanttSelectInteractor
{
public:
    IliDbGanttInteractor(IlvGanttChart*,IlvManager*,IlvView*);

    virtual IlBoolean	handleEvent(IlvEvent& event);
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttNodeHook
: public IlvGanttSubNodeHook
{
public:
    IliDbGanttNodeHook(IlvGanttChart* gantt)
    : IlvGanttSubNodeHook(gantt)
    {}
    virtual IlBoolean	beforeReshape(IlvGanttNode*,
				      IlUShort,
				      IlvGanttSubNode*);
    virtual IlBoolean	beforeMove(IlvGanttNode*,
				   IlUShort,
				   IlvGanttSubNode*);
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttLink
: public IlvNDoubleLinkImage
{
public:
    IliDbGanttLink(IlvDisplay* display,
		   IlBoolean oriented,
		   IlInt type,
		   IlvGraphic* from,
		   IlvGraphic* to,
		   IlvPalette* palette = 0)
	: IlvNDoubleLinkImage(display, oriented, from, to, palette)
    {
	_type = type;
    };

    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual IlvPoint*	getLinkPoints(IlUInt&,
				      const IlvTransformer* = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    DeclareTypeInfoRO();

protected:
    virtual IlBoolean	isDirect(const IlvTransformer* = 0) const;

    IlInt		_type;
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttModel : public IliGadgetModel
{
public:
    IliDbGanttModel();
    virtual ~IliDbGanttModel();

    // Basic methods
    virtual const char*	getName() const;
    virtual IlBoolean	isSubtypeOf(const IliString&) const;

    // Gantt
    void		setDbGantt(IliDbGantt*);
    IliDbGantt*		getDbGantt() const;

    // Read / Write
    void		write(IL_STDPREF ostream &to);
    void		read(IL_STDPREF istream &from);

    // Unit
    virtual IlInt	externalToInternalUnit(const IliValue& value,
					       IliDbGanttWhichDs which) const;
    virtual IliValue	internalToExternalUnit(IlInt value,
					       IliDbGanttWhichDs which) const;

    // Data sources
    virtual IlBoolean	hasDataSource(IliDbGanttWhichDs) const;
    virtual IlInt	getColumnCount(IliDbGanttWhichDs) const;
    virtual const char*	getColumnLabel(IliDbGanttWhichDs,IlInt) const;
    virtual IlBoolean	isColumnNameNullable(IliDbGanttWhichDs,IlInt) const;
    virtual const char* getDataSourceLabel(IliDbGanttWhichDs) const;

    // Parse
    virtual IlBoolean	parseResource(IliTableBuffer*, IliDbGanttInfo&);
    virtual IlBoolean	parseActivity(IliTableBuffer*, IliDbGanttInfo&);
    virtual IlBoolean	parseConstraint(IliTableBuffer*, IliDbGanttInfo&,
					IlBoolean = IlFalse);
    virtual IlBoolean	parsePrecedence(IliTableBuffer*, IliDbGanttInfo&);
    virtual IlBoolean	parseBreak(IliTableBuffer*, IliDbGanttInfo&);
    virtual IlBoolean	parseLoad(IliTableBuffer*, IliDbGanttInfo&);

    // Computing
    virtual void	computeMinMaxForScale(IlInt&, IlInt&);

    // Identifier
    IlBoolean		isAllUniqueIdentifiers() const;
    void		setAllUniqueIdentifiers(IlBoolean flag);
    void		computeInternalIdentifier(const char*,
						  IliString&,
						  IliDbGanttWhichDs) const;
    void		computeExternalIdentifier(const char*,
						  IliString&) const;

    // Events from Gantt
    virtual void	constraintHasBeenChanged(const IliDbGanttInfo&);

    // Resource events
    virtual void	resTableDeleted(const IliModelHookInfo&);
    virtual void	resTableChanged(const IliModelHookInfo&);

    virtual void	resColumnInserted(const IliModelHookInfo&);
    virtual void	resColumnChanged(const IliModelHookInfo&);
    virtual void	resColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	resColumnDeleted(const IliModelHookInfo&);
    virtual void	resColumnMoved(const IliModelHookInfo&);

    virtual void	resAllRowsDeleted(const IliModelHookInfo&);
    virtual void	resRowsInserted(const IliModelHookInfo&);
    virtual void	resRowInserted(const IliModelHookInfo&);
    virtual void	resRowToBeChanged(const IliModelHookInfo&);
    virtual void	resRowChanged(const IliModelHookInfo&);
    virtual void	resRowToBeDeleted(const IliModelHookInfo&);
    virtual void	resRowDeleted(const IliModelHookInfo&);
    virtual void	resRowMoved(const IliModelHookInfo&);
    virtual void	resRowsExchanged(const IliModelHookInfo&);
    virtual void	resRowsFetched(const IliModelHookInfo&);
    virtual void	resRowFetched(const IliModelHookInfo&);

    virtual void	resColumnCellsChanged(const IliModelHookInfo&);
    virtual void	resCellChanged(const IliModelHookInfo&);

    // Activity events
    virtual void	actTableDeleted(const IliModelHookInfo&);
    virtual void	actTableChanged(const IliModelHookInfo&);

    virtual void	actColumnInserted(const IliModelHookInfo&);
    virtual void	actColumnChanged(const IliModelHookInfo&);
    virtual void	actColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	actColumnDeleted(const IliModelHookInfo&);
    virtual void	actColumnMoved(const IliModelHookInfo&);

    virtual void	actAllRowsDeleted(const IliModelHookInfo&);
    virtual void	actRowsInserted(const IliModelHookInfo&);
    virtual void	actRowInserted(const IliModelHookInfo&);
    virtual void	actRowToBeChanged(const IliModelHookInfo&);
    virtual void	actRowChanged(const IliModelHookInfo&);
    virtual void	actRowToBeDeleted(const IliModelHookInfo&);
    virtual void	actRowDeleted(const IliModelHookInfo&);
    virtual void	actRowMoved(const IliModelHookInfo&);
    virtual void	actRowsExchanged(const IliModelHookInfo&);
    virtual void	actRowsFetched(const IliModelHookInfo&);
    virtual void	actRowFetched(const IliModelHookInfo&);

    virtual void	actColumnCellsChanged(const IliModelHookInfo&);
    virtual void	actCellChanged(const IliModelHookInfo&);

    // Constraint events
    virtual void	cntTableDeleted(const IliModelHookInfo&);
    virtual void	cntTableChanged(const IliModelHookInfo&);

    virtual void	cntColumnInserted(const IliModelHookInfo&);
    virtual void	cntColumnChanged(const IliModelHookInfo&);
    virtual void	cntColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	cntColumnDeleted(const IliModelHookInfo&);
    virtual void	cntColumnMoved(const IliModelHookInfo&);

    virtual void	cntAllRowsDeleted(const IliModelHookInfo&);
    virtual void	cntRowsInserted(const IliModelHookInfo&);
    virtual void	cntRowInserted(const IliModelHookInfo&);
    virtual void	cntRowToBeChanged(const IliModelHookInfo&);
    virtual void	cntRowChanged(const IliModelHookInfo&);
    virtual void	cntRowToBeDeleted(const IliModelHookInfo&);
    virtual void	cntRowDeleted(const IliModelHookInfo&);
    virtual void	cntRowMoved(const IliModelHookInfo&);
    virtual void	cntRowsExchanged(const IliModelHookInfo&);
    virtual void	cntRowsFetched(const IliModelHookInfo&);
    virtual void	cntRowFetched(const IliModelHookInfo&);

    virtual void	cntColumnCellsChanged(const IliModelHookInfo&);
    virtual void	cntCellChanged(const IliModelHookInfo&);

    // Precedence events
    virtual void	preTableDeleted(const IliModelHookInfo&);
    virtual void	preTableChanged(const IliModelHookInfo&);

    virtual void	preColumnInserted(const IliModelHookInfo&);
    virtual void	preColumnChanged(const IliModelHookInfo&);
    virtual void	preColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	preColumnDeleted(const IliModelHookInfo&);
    virtual void	preColumnMoved(const IliModelHookInfo&);

    virtual void	preAllRowsDeleted(const IliModelHookInfo&);
    virtual void	preRowsInserted(const IliModelHookInfo&);
    virtual void	preRowInserted(const IliModelHookInfo&);
    virtual void	preRowToBeChanged(const IliModelHookInfo&);
    virtual void	preRowChanged(const IliModelHookInfo&);
    virtual void	preRowToBeDeleted(const IliModelHookInfo&);
    virtual void	preRowDeleted(const IliModelHookInfo&);
    virtual void	preRowMoved(const IliModelHookInfo&);
    virtual void	preRowsExchanged(const IliModelHookInfo&);
    virtual void	preRowsFetched(const IliModelHookInfo&);
    virtual void	preRowFetched(const IliModelHookInfo&);

    virtual void	preColumnCellsChanged(const IliModelHookInfo&);
    virtual void	preCellChanged(const IliModelHookInfo&);

    // Break events
    virtual void	brkTableDeleted(const IliModelHookInfo&);
    virtual void	brkTableChanged(const IliModelHookInfo&);

    virtual void	brkColumnInserted(const IliModelHookInfo&);
    virtual void	brkColumnChanged(const IliModelHookInfo&);
    virtual void	brkColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	brkColumnDeleted(const IliModelHookInfo&);
    virtual void	brkColumnMoved(const IliModelHookInfo&);

    virtual void	brkAllRowsDeleted(const IliModelHookInfo&);
    virtual void	brkRowsInserted(const IliModelHookInfo&);
    virtual void	brkRowInserted(const IliModelHookInfo&);
    virtual void	brkRowToBeChanged(const IliModelHookInfo&);
    virtual void	brkRowChanged(const IliModelHookInfo&);
    virtual void	brkRowToBeDeleted(const IliModelHookInfo&);
    virtual void	brkRowDeleted(const IliModelHookInfo&);
    virtual void	brkRowMoved(const IliModelHookInfo&);
    virtual void	brkRowsExchanged(const IliModelHookInfo&);
    virtual void	brkRowsFetched(const IliModelHookInfo&);
    virtual void	brkRowFetched(const IliModelHookInfo&);

    virtual void	brkColumnCellsChanged(const IliModelHookInfo&);
    virtual void	brkCellChanged(const IliModelHookInfo&);

    // Load events
    virtual void	loaTableDeleted(const IliModelHookInfo&);
    virtual void	loaTableChanged(const IliModelHookInfo&);

    virtual void	loaColumnInserted(const IliModelHookInfo&);
    virtual void	loaColumnChanged(const IliModelHookInfo&);
    virtual void	loaColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	loaColumnDeleted(const IliModelHookInfo&);
    virtual void	loaColumnMoved(const IliModelHookInfo&);

    virtual void	loaAllRowsDeleted(const IliModelHookInfo&);
    virtual void	loaRowsInserted(const IliModelHookInfo&);
    virtual void	loaRowInserted(const IliModelHookInfo&);
    virtual void	loaRowToBeChanged(const IliModelHookInfo&);
    virtual void	loaRowChanged(const IliModelHookInfo&);
    virtual void	loaRowToBeDeleted(const IliModelHookInfo&);
    virtual void	loaRowDeleted(const IliModelHookInfo&);
    virtual void	loaRowMoved(const IliModelHookInfo&);
    virtual void	loaRowsExchanged(const IliModelHookInfo&);
    virtual void	loaRowsFetched(const IliModelHookInfo&);
    virtual void	loaRowFetched(const IliModelHookInfo&);

    virtual void	loaColumnCellsChanged(const IliModelHookInfo&);
    virtual void	loaCellChanged(const IliModelHookInfo&);

    // Tools
    IlBoolean		isSameString(const char*, const char*) const;
    IlBoolean		isUpdateEventPropagated() const;
    IlBoolean		isDeletionEventPropagated() const;

    // Resources
    IliTable*		getResTable() const;
    IliTableBuffer*	getResBuffer() const;
    IliTableBuffer*	getResBufferInfo() const;
    void		releaseResBuffer(IliTableBuffer*) const;
    IlInt		getResColumnIndex(IlInt) const;

    void		execInsertResource(const IliDbGanttInfo&,
					   IlInt);
    void		execRemoveResource(const IliDbGanttInfo&);
    void		execRenameResource(const char*, const char*);
    void		execRefreshResources();
    void		execDsChangeResIdentifier(const char*, const char*);
    void		execChangeHeightResource(const IliDbGanttInfo&);
    void		execChangeDisplayValueResource(const IliDbGanttInfo&);

    // Activities
    IliTable*		getActTable() const;
    IliTableBuffer*	getActBuffer() const;
    IliTableBuffer*	getActBufferInfo() const;
    void		releaseActBuffer(IliTableBuffer*) const;
    IlInt		getActColumnIndex(IlInt) const;

    void		execDsChangeActIdentifier(const IliDbGanttInfo&,
						  const IliDbGanttInfo&);
    void		execRefreshActivities();

    // Constraints
    IliTable*		getCntTable() const;
    IliTableBuffer*	getCntBuffer() const;
    IliTableBuffer*	getCntBufferInfo() const;
    void		releaseCntBuffer(IliTableBuffer*) const;
    IlInt		getCntColumnIndex(IlInt) const;

    void		execRefreshConstraints();
    void		execAddConstraint(const IliDbGanttInfo&,
					  IlBoolean = IlTrue);
    void		execReplaceConstraint(const IliDbGanttInfo&,
					      const IliDbGanttInfo&);
    void		execRemoveConstraint(const IliDbGanttInfo&,
					     IlBoolean);
    void		execRemoveConstraintsFor(IlInt,
						 const char*);
    void		execDsRemoveConstraintsFor(IlInt,
						   const char*);
    void		execRefreshConstraints(const IliDbGanttInfo&);
    void		execDsChangeCntIdentifier(const char*,
						  const char*);

    // Precedences
    IliTable*		getPreTable() const;
    IliTableBuffer*	getPreBuffer() const;
    IliTableBuffer*	getPreBufferInfo() const;
    void		releasePreBuffer(IliTableBuffer*) const;
    IlInt		getPreColumnIndex(IlInt) const;

    void		execRefreshPrecedences();
    void		execAddPrecedence(const IliDbGanttInfo&,
					  IlBoolean = IlTrue);
    void		execRemovePrecedence(const IliDbGanttInfo&, IlBoolean);
    void		execRemovePrecedencesFor(const char*);
    void		execDsRemovePrecedencesFor(IlInt, const char*);

    // Breaks
    IliTable*		getBrkTable() const;
    IliTableBuffer*	getBrkBuffer() const;
    IliTableBuffer*	getBrkBufferInfo() const;
    void		releaseBrkBuffer(IliTableBuffer*) const;
    IlInt		getBrkColumnIndex(IlInt) const;

    void		execRefreshBreaks();
    void		execAddBreak(const IliDbGanttInfo&,
				     IlBoolean = IlTrue);
    void		execReplaceBreak(const char*, const IliDbGanttInfo&);
    void		execRemoveBreak(const IliDbGanttInfo&);
    void		execRemoveBreaksFor(IlInt, const char*);
    void		execDsRemoveBreaksFor(IlInt, const char*);
    void		execRemoveAllBreaks();

    // Load
    IliTable*		getLoaTable() const;
    IliTableBuffer*	getLoaBuffer() const;
    IliTableBuffer*	getLoaBufferInfo() const;
    void		releaseLoaBuffer(IliTableBuffer*) const;
    IlInt		getLoaColumnIndex(IlInt) const;

    void		execAddLoad(const IliDbGanttInfo&,
				    IlBoolean = IlTrue);
    void		execRemoveLoad(const IliDbGanttInfo&);
    void		execReplaceLoad(const IliDbGanttInfo&,
					const IliDbGanttInfo&);
    void		execRefreshLoads(IlBoolean = IlFalse);
    void		execRemoveAllLoads();
    IlvGanttLine*	execGetLoadLine() const;

    // Grid
    void		execRefreshGrid();

    // Others
    IlBoolean		adjustRowLoad(IlBoolean = IlFalse);
    void		compactRow(const IliDbGanttInfo&);
    IlBoolean		hasValidResourceHeader() const;
    void		computeMinMaxConstraint(const IliDbGanttInfo&,
						IlInt&, IlInt&);
    void		checkScaleValue(const IliDbGanttInfo&,
					IlBoolean = IlTrue,
					IlInt = -1, IlInt = -1);

    IliTableBuffer*	getConstraintActivityBuffer(IliTableBuffer*,
						    IlInt) const;
protected:
    IliDbGantt*		_gantt;
    IlBoolean		_uniqueIdentifier;
};

// --------------------------------------------------------------------------
// Macro for IliDbGanttModel
// --------------------------------------------------------------------------
#if defined(DOXYGEN_GENERATION)
void IliRegisterDbGanttModel(cl);
#else
#define IliRegisterDbGanttModel(cl) \
  IliDbGantt::RegisterModel(new cl)
#endif

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttFullModel
: public IliDbGanttModel
{
public:
    IliDbGanttFullModel();
    virtual ~IliDbGanttFullModel();

    // Computing
    virtual void	computeMinMaxForScale(IlInt&,IlInt&);

    // Basic methods
    IliDeclareModel();
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGanttLightModel
: public IliDbGanttModel
{
public:
    IliDbGanttLightModel();
    virtual ~IliDbGanttLightModel();

    // Basic methods
    IliDeclareModel();

    // Parse
    virtual IlBoolean	parseActivity(IliTableBuffer*,
				      IliDbGanttInfo&);
    virtual IlBoolean	parseConstraint(IliTableBuffer*,
					IliDbGanttInfo&,
					IlBoolean = IlFalse);

    // Computing
    virtual void	computeMinMaxForScale(IlInt&,IlInt&);

    // Data sources
    virtual IlBoolean	hasDataSource(IliDbGanttWhichDs) const;
    virtual IlInt	getColumnCount(IliDbGanttWhichDs) const;
    virtual const char* getColumnLabel(IliDbGanttWhichDs,IlInt) const;

    // Events from gantt
    virtual void	constraintHasBeenChanged(const IliDbGanttInfo&);

    // Activities events
    virtual void	actTableDeleted(const IliModelHookInfo&);
    virtual void	actTableChanged(const IliModelHookInfo&);

    virtual void	actColumnInserted(const IliModelHookInfo&);
    virtual void	actColumnChanged(const IliModelHookInfo&);
    virtual void	actColumnToBeDeleted(const IliModelHookInfo&);
    virtual void	actColumnDeleted(const IliModelHookInfo&);
    virtual void	actColumnMoved(const IliModelHookInfo&);

    virtual void	actRowsInserted(const IliModelHookInfo&);
    virtual void	actRowInserted(const IliModelHookInfo&);
    virtual void	actRowToBeChanged(const IliModelHookInfo&);
    virtual void	actRowChanged(const IliModelHookInfo&);
    virtual void	actRowToBeDeleted(const IliModelHookInfo&);
    virtual void	actRowDeleted(const IliModelHookInfo&);
    virtual void	actRowMoved(const IliModelHookInfo&);
    virtual void	actRowsExchanged(const IliModelHookInfo&);
    virtual void	actRowsFetched(const IliModelHookInfo&);
    virtual void	actRowFetched(const IliModelHookInfo&);

    virtual void	actColumnCellsChanged(const IliModelHookInfo&);
    virtual void	actCellChanged(const IliModelHookInfo&);
};

// -------------------------------------------------------------------------
class ILV_DBGANTT_EXPORTED IliDbGantt
: public IlvGanttChartForm
{
public:
    IliDbGantt(IlvDisplay* display, const IlvRect& rect);
    ~IliDbGantt();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbGantt);

    void		initReDraws();
    void		reDrawViews();

    //  models 
    void		setModelName(const char* name);
    const char*		getModelName() const;
    IliDbGanttModel*	getModel() const;

    IliDeclareDataAccessorForModel(IliDbGanttModel);
    IliDeclareAccessorForModel(IliDbGanttModel);

    //  Holders -
    virtual void	setHolder(IlvGraphicHolder*);

    //  Error reporting 
    void		addErrorSink(IliErrorSink* sink,
				     IliDbGanttWhichDs dsi);
    void		removeErrorSink(IliErrorSink* sink,
					IliDbGanttWhichDs dsi);
    void		setErrorReporter(IliErrorReporter* reporter);
    IliErrorReporter*	getErrorReporter() const;
    void		reportErrors(const IliErrorList& list) const;

    //  Data Sources 
    inline void		setResDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getResDataSource() const;
    inline void		setResDataSourceName(const char* name);
    inline const char*	getResDataSourceName() const;

    inline void		setActDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getActDataSource() const;
    inline void		setActDataSourceName(const char* name);
    inline const char*	getActDataSourceName() const;

    inline void		setCntDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getCntDataSource() const;
    inline void		setCntDataSourceName(const char* name);
    inline const char*	getCntDataSourceName() const;

    inline void		setPreDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getPreDataSource() const;
    inline void		setPreDataSourceName(const char* name);
    inline const char*	getPreDataSourceName() const;

    inline void		setBrkDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getBrkDataSource() const;
    inline void		setBrkDataSourceName(const char* name);
    inline const char*	getBrkDataSourceName() const;

    inline void		setLoaDataSource(IliDataSource* ds);
    inline IliDataSource*	getLoaDataSource() const;
    inline void		setLoaDataSourceName(const char* name);
    inline const char*	getLoaDataSourceName() const;

    void		setInteractionDataSourceToGantt(IlBoolean flag);
    IlBoolean		isInteractionDataSourceToGantt() const;

    //  Event from data source 
    IliDsUsageDeclareFctConnect(res);
    IliDsUsageDeclareFctConnect(act);
    IliDsUsageDeclareFctConnect(cnt);
    IliDsUsageDeclareFctConnect(pre);
    IliDsUsageDeclareFctConnect(brk);
    IliDsUsageDeclareFctConnect(loa);

    // Resources
    void		setResColumnName(IliDbGanttResCols typ,
					 const char* name);
    const char*		getResColumnName(IliDbGanttResCols typ) const;
    IlInt		getResColumnIndex(IliDbGanttResCols typ) const;

    void		removeAllDisplayColumns();
    void		addDisplayColumnName(const char* name);
    const char*		getDisplayColumnName(IlInt pos) const;
    IlInt		getDisplayColumnIndex(IlInt pos) const;
    IlInt		getDisplayColumnCount() const;

    // Activities
    void		setActColumnName(IliDbGanttActCols typ,
					 const char* name);
    const char*		getActColumnName(IliDbGanttActCols typ) const;
    IlInt		getActColumnIndex(IliDbGanttActCols typ) const;

    // Constraints
    void		setCntColumnName(IliDbGanttCntCols typ,
					 const char* name);
    const char*		getCntColumnName(IliDbGanttCntCols typ) const;
    IlInt		getCntColumnIndex(IliDbGanttCntCols typ) const;

    // Precedences
    void		setPreColumnName(IliDbGanttPreCols typ,
					 const char* name);
    const char*		getPreColumnName(IliDbGanttPreCols typ) const;
    IlInt		getPreColumnIndex(IliDbGanttPreCols typ) const;

    // Breaks
    void		setBrkColumnName(IliDbGanttBrkCols typ,
					 const char* name);
    const char*		getBrkColumnName(IliDbGanttBrkCols typ) const;
    IlInt		getBrkColumnIndex(IliDbGanttBrkCols typ) const;

    // Loads
    void		setLoaColumnName(IliDbGanttLoaCols typ,
					 const char* name);
    const char*		getLoaColumnName(IliDbGanttLoaCols typ) const;
    IlInt		getLoaColumnIndex(IliDbGanttLoaCols typ) const;

    // Scale
    void		setScaleType(IliDbScaleType typ);
    IliDbScaleType	getScaleType() const;
    void		setScaleUnit(IliScaleUnit unit);
    IliScaleUnit	getScaleUnit() const;
    IliDbGanttScale*	getScale() const;
    IlInt		convertScaleValue(IlInt, IlBoolean) const;
    void		enableDisplayFullName(IlBoolean flag);
    IlBoolean		isDisplayFullNameEnabled() const;
    void		setReferenceYear(IlInt y);
    IlInt		getReferenceYear() const;
    void		setReferenceMonth(IlInt m);
    IlInt		getReferenceMonth() const;

    virtual const char*	getScaleNumericLabel(IlInt val);
    IlInt		getScaleNumericValue() const;
    void		setScaleNumericLabel(const char* label);
    static IlSymbol*	ScaleNumericLabelSymbol();

    // Callbacks
    void		setGanttCallback(IliDbGanttCallbackName name,
					 IliDbGanttCallback cb,
					 IlAny arg = 0);
    IliDbGanttCallback	getGanttCallback(IliDbGanttCallbackName name) const;
    IlAny	getGanttCallbackData(IliDbGanttCallbackName name) const;
    const IliDbGanttInfo& getCallbackInformation() const;

    virtual IlUInt	getCallbackTypes(const char* const **,
					 const IlSymbol* const**) const;
    virtual void	onConstraintDoubleClicked();
    virtual void	onPrecedenceDoubleClicked();

    static IlSymbol*	ConstraintDoubleClickedSymbol();
    static IlSymbol*	PrecedenceDoubleClickedSymbol();

    const char*		getObjectNameDoubleClicked() const;

    // Hook
    void		setupHook();

    // Resources
    virtual IlvGraphic*	createResourcesModel();

    // Constraints
    IlvGraphic*		createDefaultConstraint();
    virtual IlvGraphic*	onCreateConstraint();
    virtual IlvGraphic*	onReplaceConstraint(IlvGraphic* old);
    virtual void	onDeleteConstraint();

    // Precedences
    void		constraintHasBeenChanged(const IliDbGanttInfo&);
    IlvGraphic*		createDefaultPrecedence();
    virtual IlvGraphic*	onCreatePrecedence();
    virtual IlvGraphic*	onReplacePrecedence(IlvGraphic* old);
    virtual void	onDeletePrecedence();

    // Breaks
    IlvGraphic*		createDefaultBreak();
    virtual IlvGraphic*	onCreateBreak();
    virtual IlvGraphic*	onReplaceBreak(IlvGraphic* old);
    virtual void	onDeleteBreak();

    // Load
    IlvGraphic*		createDefaultLoad();
    virtual IlvGraphic*	onCreateLoad();
    virtual IlvGraphic*	onReplaceLoad(IlvGraphic* old);
    virtual void	onDeleteLoad();

    IlInt		computeMaxLoad();
    void		manageLoadRow();
    virtual void	comboLoadHasChanged();

    // Period
    virtual IlBoolean	isActivePeriod(const IliDate& info);
    static IlvSymbol*	IsActivePeriodSymbol();
    IlInt		getActivePeriodInfo(IliDateInfo info) const;
    void		setInactivePeriod();
    IlBoolean		isActivePeriodWithRules(const IliDate& info);

    // Color
    void		setActivePeriodColor(IlvColor* color);
    void		setInactivePeriodColor(IlvColor* color);
    void		setBreakColor(IlvColor* color);
    void		setLoadColor(IlvColor* color);
    void		setPrecedenceColor(IlvColor* color);
    void		setDelimiterColor(IlvColor* color);
    IlvColor*		getActivePeriodColor() const;
    IlvColor*		getInactivePeriodColor() const;
    IlvColor*		getBreakColor() const;
    IlvColor*		getLoadColor() const;
    IlvColor*		getPrecedenceColor() const;
    IlvColor*		getDelimiterColor() const;
    IlvPalette*		getActivePeriodPalette() const;
    IlvPalette*		getInactivePeriodPalette() const;
    IlvPalette*		getBreakPalette() const;
    IlvPalette*		getLoadPalette() const;
    IlvPalette*		getPrecedencePalette() const;
    IlvPalette*		getDelimiterPalette() const;

    // Periods
    IlInt		getPeriodCount() const;
    void		removeAllPeriods();
    void		addPeriod(const IliDbGanttPeriod&);
    void		addPeriod(IliDbGanttPeriodUnit,
				  IliDbGanttPeriodTest,
				  IlInt,
				  IlInt = -1,
				  IlInt = -1,
				  IlInt = -1);
    IliDbGanttPeriod*	getPeriod(IlInt) const;

    // Refresh
    IliDsUsageDeclareBatchDirect();
    IliDsUsageDeclareBatch(res);
    IliDsUsageDeclareBatch(act);
    IliDsUsageDeclareBatch(cnt);
    IliDsUsageDeclareBatch(pre);
    IliDsUsageDeclareBatch(brk);
    IliDsUsageDeclareBatch(loa);

    IlInt		getBatchCount() const;
    IlBoolean		isBatchMode() const;
    IlBoolean		isRefreshNeeded(IliDbGanttRefresh =
					IliDbGanttRefreshCount) const;
    void		refreshAll();
    void		refreshResourcesHeader();
    void		refreshResources();
    void		refreshActivities();
    void		refreshConstraints();
    void		refreshPrecedences();
    void		refreshBreaks();
    void		refreshLoad();
    void		refreshScales();
    void		refreshGrid();
    void		refreshBack();
    void		refreshSplitters();

    // Computing
    void		computeMinMaxScale();
    IlInt		getMaxLoad() const { return _maxLoad; }
    // Get information
    void		propagateDeletionEvent(IlBoolean flag);
    IlBoolean		isDeletionEventPropagated() const;
    void		propagateUpdateEvent(IlBoolean flag);
    IlBoolean		isUpdateEventPropagated() const;
    void		setReadOnly(IlBoolean flag);
    IlBoolean		isReadOnly() const;

    // Other
    virtual void	makeView(IlvPort*, const IlvTransformer*);
    void		noView() { _noView = IlTrue; }

    // Accessors
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlvValue&	queryValueDataSources(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual IlBoolean	applyValueDataSources(const IlvValue&);
    static  void	GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);

    // Internal
    void		setGanttColor(IliDbGanttColor, const char*);
    void		computeColumnIndex(IliDbGanttWhichDs);
    void		eventKeyUp(IlvEvent&);
    void		eventDoubleClick(IlvEvent&, IlvView*);

    IlBoolean		isValidEventHook();

protected:
    // Initialize
    void		initializeGantt();
    virtual void	initializeViewFirstTime();

    // Refresh
    IlBoolean		_needRefresh[IliDbGanttRefreshCount];
    IlBoolean		_inEndOfBatch;
    IlInt		_batchCount;

    // Data source
    IliSingleDataSourceUsage*	_dsAct;
    IliSingleDataSourceUsage*	_dsRes;
    IliSingleDataSourceUsage*	_dsCnt;
    IliSingleDataSourceUsage*	_dsPre;
    IliSingleDataSourceUsage*	_dsBrk;
    IliSingleDataSourceUsage*	_dsLoa;
    IlBoolean		_coherenceId;
    IlBoolean		_propagateDeletion;
    IlBoolean		_propagateUpdate;
    IlBoolean		_readOnly;
    IlBoolean		_interDsToGantt;

    // Information
    IliDbGanttInfo	_objInfo;

    // Resources
    IliString*		_resColumns;
    IlInt		_resDisplayColumnCount;

    // Load
    IlInt		_maxLoad;
    IliString		_resLoad;

    // Scales
    IlInt		_minScale;
    IlInt		_maxScale;
    IlInt		_yearRef;
    IlInt		_monthRef;
    IliDbGanttScale*	_gtScale;
    IliScaleUnit	_scaleUnit;
    IlvGraphicSet*	_grScales;
    IlBoolean		_dispFullName;

    IliString		_numericLabel;
    IlInt		_numericValue;

    // Grid
    IliString		_gridColor[IliDbGanttColorCount];
    IlvPalette*		_gridPalette[IliDbGanttColorCount];
    IlvGraphicSet*	_grGrid;
    IlvGraphicSet*	_grBack;

    // Period
    IlBoolean		_isActivePeriod;
    IliDate		_periodInfo;
    IliDbGanttPeriod*	_periods;
    IlInt		_periodCount;

    // Callback
    IliDbGanttCallback	_cbList[IliDbGanttCallbackCount];
    IlAny		_cbData[IliDbGanttCallbackCount];
    IliString		_objectDoubleClicked;

    // Others
    IlBoolean		_noView;
    IlBoolean		_firstTime;

    IlInt		getBackgroundLayer() const
	{ return _backgroundLayer; }
    IlvGraphicSet*	setCompositeBackground(IlvGraphicSet*,
					       IlBoolean = IlTrue);
    IlvGraphicSet*	getCompositeBackground() const;
    IlvGanttResourceHeader* getValidResourceHeader() const;

private:
    IlInt		_backgroundLayer;
    IlvGraphicSet*	_compoBack;

    friend class IliDbGanttModel;
};

IliSingleDsUsageCodeDSAccess(IliDbGantt,Res,_dsRes)
IliSingleDsUsageCodeDSAccess(IliDbGantt,Act,_dsAct)
IliSingleDsUsageCodeDSAccess(IliDbGantt,Cnt,_dsCnt)
IliSingleDsUsageCodeDSAccess(IliDbGantt,Pre,_dsPre)
IliSingleDsUsageCodeDSAccess(IliDbGantt,Brk,_dsBrk)
IliSingleDsUsageCodeDSAccess(IliDbGantt,Loa,_dsLoa)

IlvDeclareEnumTypeClass(ILV_DBGANTT_EXPORTED,ScaleUnit);
IlvDeclareEnumTypeClass(ILV_DBGANTT_EXPORTED,DbScaleType);

IliModuleDECL_exp(ILV_DBGANTT_EXPORTED,ScaleUnit);
IliModuleDECL_exp(ILV_DBGANTT_EXPORTED,DbScaleType);
IliModuleDECL_exp(ILV_DBGANTT_EXPORTED,IliDbGantt);

#endif /* !__Ili_Dbgantt_H */
