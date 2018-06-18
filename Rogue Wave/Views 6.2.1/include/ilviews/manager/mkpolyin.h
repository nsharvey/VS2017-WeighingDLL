// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mkpolyin.h
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
// Declaration of the IlvMakePolyPointsInteractor class and its subtypes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mkpolyin_H
#define __Ilv_Manager_Mkpolyin_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Polyline_H)
#include <ilviews/graphics/polyline.h>
#endif
#if !defined(__Ilv_Graphics_Outpoly_H)
#include <ilviews/graphics/outpoly.h>
#endif
#if !defined(__Ilv_Graphics_Relfpoly_H)
#include <ilviews/graphics/relfpoly.h>
#endif
#if !defined(__Ilv_Graphics_Spline_H)
#include <ilviews/graphics/spline.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakePolyPointsInteractor
: public IlvManagerViewInteractor
{
public:
    IlvMakePolyPointsInteractor(IlvManager* manager, IlvView* view)
    : IlvManagerViewInteractor(manager, view),
      _dragging(IlFalse),
      _count(0),
      _points(0),
      _buffercount(0),
      _threshold(10) {}
    IlvMakePolyPointsInteractor()
    : IlvManagerViewInteractor(),
      _dragging(IlFalse),
      _count(0),
      _points(0),
      _buffercount(0),
      _threshold(10) {}
    virtual ~IlvMakePolyPointsInteractor();
    // ____________________________________________________________
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	drawGhost() = 0;

    virtual void 	drawHull();
    virtual void	doIt(IlUInt count, IlvPoint* points) = 0;
    void		abort();
    void		init();
    inline IlvPoint*	points() { return _points; }
    inline IlUInt	count()  { return _count;  }
    virtual IlBoolean	accept(IlvPoint& p);
    virtual void	react(IlvPoint& p, IlUShort modifier = 0);
    void		addPolyPoints(IlvGraphic* object);
    inline void		setThreshold(IlUShort val) { _threshold = val; }
    inline IlUShort	getThreshold() const { return _threshold; }

    IlvMakePolyPointsInteractor(IlvInputFile&);
    IlvDeclareLazyClassInfo();

protected:
    IlvPoint*		transformPoints() const;
    IlvPoint*		makePoints(IlUInt count);

    virtual IlBoolean	addPoint(const IlvPoint& p);

    IlBoolean		_dragging;
    IlUInt		_count;

    virtual void 	commit(IlBoolean removeExtraPoints);

private:
    IlvPoint*		_points;
    IlUInt		_buffercount;
    IlUShort		_threshold;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakePolylineInteractor
: public IlvMakePolyPointsInteractor
{
public:
    IlvMakePolylineInteractor(IlvManager* manager,
			      IlvView*    view)
	: IlvMakePolyPointsInteractor(manager, view) {}
    IlvMakePolylineInteractor()
	: IlvMakePolyPointsInteractor() {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakePolylineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeReliefPolylineInteractor
: public IlvMakePolylineInteractor
{
public:
    IlvMakeReliefPolylineInteractor(IlvManager* manager, IlvView* view)
	: IlvMakePolylineInteractor(manager, view) {}
    IlvMakeReliefPolylineInteractor()
	: IlvMakePolylineInteractor() {}
    // ____________________________________________________________
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort thickness)
			{
			    _thickness = thickness;
			}
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakeReliefPolylineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlUShort		_thickness;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeArrowPolylineInteractor
: public IlvMakePolylineInteractor
{
public:
    IlvMakeArrowPolylineInteractor(IlvManager* manager,
				   IlvView*    view,
				   IlBoolean  alllines = IlFalse,
				   IlFloat    atpos    = 1.0)
    : IlvMakePolylineInteractor(manager, view),
      _alllines(alllines),
      _atpos(atpos) {}
    IlvMakeArrowPolylineInteractor(IlBoolean  alllines = IlFalse,
				   IlFloat    atpos    = 1.0)
    : IlvMakePolylineInteractor(),
      _alllines(alllines),
      _atpos(atpos) {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakeArrowPolylineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

private:
    IlBoolean		_alllines;
    IlFloat		_atpos;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakePolygonInteractor
: public IlvMakePolylineInteractor
{
public:
    IlvMakePolygonInteractor(IlvManager* manager, IlvView* view)
    : IlvMakePolylineInteractor(manager, view) {}
    IlvMakePolygonInteractor()
    : IlvMakePolylineInteractor() {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakePolygonInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeReliefPolygonInteractor
: public IlvMakePolygonInteractor
{
public:
    IlvMakeReliefPolygonInteractor(IlvManager* manager,
				   IlvView*    view,
				   IlUShort   thickness = 4)
    : IlvMakePolygonInteractor(manager, view),
      _thickness(thickness) {}
    IlvMakeReliefPolygonInteractor(IlUShort   thickness = 4)
    : IlvMakePolygonInteractor(),
      _thickness(thickness) {}
    // ____________________________________________________________
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort thickness)
			{
			    _thickness = thickness;
			}
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakeReliefPolygonInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

private:
    IlUShort		_thickness;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeOutlinePolygonInteractor
: public IlvMakePolygonInteractor
{
public:
    IlvMakeOutlinePolygonInteractor(IlvManager* manager,
				    IlvView*    view)
    : IlvMakePolygonInteractor(manager, view) {}
    IlvMakeOutlinePolygonInteractor()
    : IlvMakePolygonInteractor() {}
    // ____________________________________________________________
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakeOutlinePolygonInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeSplineInteractor
: public IlvMakePolyPointsInteractor
{
public:
    IlvMakeSplineInteractor(IlvManager* manager, IlvView* view)
    : IlvMakePolyPointsInteractor(manager, view),
      _displayIntermediatePoints(IlFalse)
    {}
    IlvMakeSplineInteractor()
    : IlvMakePolyPointsInteractor(),
      _displayIntermediatePoints(IlFalse)
    {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void 	drawHull();
    virtual void	doIt(IlUInt count, IlvPoint* points);

    inline IlBoolean 	displayIntermediatePoints()
			{
			    return _displayIntermediatePoints;
			}

    inline void 	displayIntermediatePoints(IlBoolean d)
			{
			    _displayIntermediatePoints = d;
			}

    void		react(IlvPoint& p, IlUShort modifier = 0);
    virtual void	commit(IlBoolean removeExtraPoints);
    IlBoolean		accept(IlvPoint& p);
    IlvMakeSplineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlBoolean		addPoint(const IlvPoint& p);
    IlBoolean		_displayIntermediatePoints;
    IlBoolean		_detachCalled;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeFilledSplineInteractor
: public IlvMakeSplineInteractor
{
public:
    IlvMakeFilledSplineInteractor(IlvManager* manager, IlvView* view)
    : IlvMakeSplineInteractor(manager, view) {}
    IlvMakeFilledSplineInteractor()
    : IlvMakeSplineInteractor() {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlUInt count, IlvPoint* points);

    void		react(IlvPoint& p, IlUShort modifier = 0);

    void		commit(IlBoolean removeExtraPoints);

    IlvMakeFilledSplineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlBoolean		addPoint(const IlvPoint& p);
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeClosedSplineInteractor
: public IlvMakeFilledSplineInteractor
{
public:
    IlvMakeClosedSplineInteractor(IlvManager* manager, IlvView* view)
    : IlvMakeFilledSplineInteractor(manager, view) {}
    IlvMakeClosedSplineInteractor()
    : IlvMakeFilledSplineInteractor() {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlUInt count, IlvPoint* points);

    IlvMakeClosedSplineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

ILVMGRMODULEINIT(m0_mkpolyin);

#endif /* !_Ilv__Manager_Mkpolyin_H */
