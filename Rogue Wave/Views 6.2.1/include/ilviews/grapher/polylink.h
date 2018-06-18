// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/polylink.h
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
// Declaration of the IlvPolylineLinkImage and IlvPolyRelLinkImage classes
// and their creation interactors.
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Polylink_H
#define __Ilv_Grapher_Polylink_H

#if !defined(__Ilv_Manager_Mkpolyin_H)
#include <ilviews/manager/mkpolyin.h>
#endif
#if !defined(__Ilv_Grapher_Links_H)
#include <ilviews/grapher/links.h>
#endif
#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif

class ILVGRAPHEXPORTED IlvGrapherPin;

// --------------------------------------------------------------------------
// IlvLinkImage extension that creates polypoints links.
// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvPolylineLinkImage : public IlvLinkImage
{
public:
    IlvPolylineLinkImage(IlvDisplay*	display,
                         IlBoolean	oriented,
                         IlUInt		count,
                         IlvPoint*	points,
                         IlvGraphic*	from,
			 IlvGraphic*	to,
                         IlvPalette*	palette = 0);

    IlvPolylineLinkImage(IlvDisplay*	display,
                         IlBoolean	oriented,
			 IlDouble	flatness,
                         IlUInt		count,
                         IlvPoint*	points,
                         IlvGraphic*	from,
			 IlvGraphic*	to,
                         IlvPalette*	palette = 0);

    virtual ~IlvPolylineLinkImage();

    virtual IlvPoint*	getLinkPoints(IlUInt& nPoints,
				      const IlvTransformer* t = 0) const;
    virtual void	computePoints(IlvPoint& src,
				      IlvPoint& dst,
				      const IlvTransformer* t = 0) const;


    inline IlUInt	getPointsCount() const
			{
			    return _points ? _points->getLength() : 0;
			}


    inline
    const IlvPoint*	getPoints(IlUInt& count) const
			{
			    count = getPointsCount();
			    return count ? _points->getArray() : 0;
			}

    inline IlvPoint*	getPoints(IlUInt& count)
			{
			    count = getPointsCount();
			    return count ? _points->getArray() : 0;
			}


    inline
    const IlvPoint*	getPoint(IlUInt idx) const
			{
			    return (idx<getPointsCount())
				? _points->getArray() + idx
				: 0;
			}

    void		setPoints(IlUInt count, const IlvPoint* points);


    void		movePoint(IlUInt index,IlvPos x, IlvPos y);

    void		addPoints(IlUInt          count,
				  const IlvPoint* points,
				  IlUInt          where);

    void		removePoints(IlUInt start, IlUInt count);

    void		setFlatness(IlDouble flatness);

    IlDouble		getFlatness() const;

    void		drawSpline(IlBoolean b);

    IlBoolean		isDrawingSpline() const;

    inline IlBoolean	isUsingRelativePoints() const { return _relIdx > 0; }

    void		setRelativeIndex(IlUInt idx);

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    DeclareInterface(Selection);
    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvPolylineLinkImage);

    static IlSymbol*	_flatnessValue;
    static IlSymbol*	_drawSplineValue;
    static IlSymbol*	_relIdxValue;

protected:
    virtual IlvPoint*	computeAllPoints(IlUInt&,
					 const IlvTransformer* t = 0) const;

    IlvPoint*		computeBezierPoints(IlUInt&,
					    const IlvTransformer* t = 0)const;

    void		updateRelativePoints();
    void		computeRelativePoints(IlUInt    count,
					      IlvPoint* pts,
					      IlUInt    relIdx);
    void		_setPoints(IlUInt count, const IlvPoint* points);

    IlvArrayOfPoints*	_points;
    IlDouble		_flatness;
    IlUInt		_relIdx;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvPolyRelLinkImage : public IlvPolylineLinkImage
{
public:
    IlvPolyRelLinkImage(IlvDisplay* display,
                        IlBoolean   oriented,
                        IlUInt      count,
                        IlvPoint*   points,
                        IlvGraphic* from,
			IlvGraphic* to,
                        IlvPalette* palette = 0)
	: IlvPolylineLinkImage(display,
			       oriented,
			       count,
			       points,
			       from,
			       to,
			       palette)
    {}

    DeclareTypeInfoRO();

protected:
    virtual IlvPoint*	computeAllPoints(IlUInt&,
					 const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGrapher;
class ILVGRAPHEXPORTED IlvMakePolyLinkInteractor
    : public IlvMakePolyPointsInteractor
{
public:
    IlvMakePolyLinkInteractor(IlvManager*   manager,
			      IlvView*	    view,
                              IlBoolean	    oriented = IlFalse)
	: IlvMakePolyPointsInteractor(manager, view),
	  _oriented(oriented)
    {
	init();
    }

    IlvMakePolyLinkInteractor(IlBoolean  oriented = IlFalse)
	: IlvMakePolyPointsInteractor(),
	  _oriented(oriented)
    {
	init();
    }

    // ____________________________________________________________
    inline IlvGrapher*	getGrapher() const
			{
			    return IL_REINTERPRETCAST(IlvGrapher*,
						      getManager());
			}
    virtual void	init();
    virtual void	abort();
    virtual IlBoolean	accept(IlvPoint& point);
    virtual void	react(IlvPoint& point, IlUShort modifiers = 0);
    virtual void	doIt(IlUInt count, IlvPoint* allPoints);
    virtual void	drawGhost();

    inline IlBoolean	isOriented() const { return _oriented; }
    virtual IlBoolean	acceptEnd(IlUInt count, IlvPoint* allPoints);
    inline IlvGraphic*	getStartNode() const { return _start;  }
    inline void		setStartNode(IlvGraphic* start) { _start = start; }
    inline IlvGraphic*	getEndNode() const { return _end;  }
    inline void		setEndNode(IlvGraphic* end) { _end = end; }

    inline
    IlvGrapherPin*	getStartPin() const { return _startPin; }
    inline IlUInt	getStartPinIndex() const { return _startPinIdx; }
    inline
    IlvGrapherPin*	getEndPin() const { return _endPin;   }
    inline IlUInt	getEndPinIndex() const { return _endPinIdx; }

    IlvMakePolyLinkInteractor(IlvInputFile&);

    IlvDeclareLazyClassInfo();

protected:
    void		drawPinGhosts();
    void		endOperation();
    virtual
    IlvLinkImage*	makeLink(IlUInt count, IlvPoint* points) = 0;

    virtual void	storeLink(IlvLinkImage* link);

    virtual void	highlight(IlvGraphic* node, IlBoolean highlight);

    IlvGraphic*		_start;
    IlvGraphic*		_end;
    IlBoolean		_oriented;
    IlvGrapherPin*	_startPin;
    IlUInt		_startPinIdx;
    IlvGrapherPin*	_endPin;
    IlUInt		_endPinIdx;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakePolylineLinkInteractor
    : public IlvMakePolyLinkInteractor
{
public:
    IlvMakePolylineLinkInteractor(IlvManager*	manager,
                                  IlvView*	view,
                                  IlBoolean	oriented = IlFalse)
	: IlvMakePolyLinkInteractor(manager, view, oriented)
    {}

    IlvMakePolylineLinkInteractor(IlBoolean  oriented = IlFalse)
	: IlvMakePolyLinkInteractor(oriented)
    {}

    IlvMakePolylineLinkInteractor(IlvInputFile&);

    DeclareLazyManagerViewInteractorInfoRO();

protected :
    virtual
    IlvLinkImage*	makeLink(IlUInt count, IlvPoint* points);
};


// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakePolyRelLinkInteractor
    : public IlvMakePolylineLinkInteractor
{
public:
    IlvMakePolyRelLinkInteractor(IlvManager*	manager,
                                 IlvView*	view,
                                 IlBoolean	oriented = IlFalse)
	: IlvMakePolylineLinkInteractor(manager, view, oriented)
    {}

    IlvMakePolyRelLinkInteractor(IlBoolean oriented = IlFalse)
	: IlvMakePolylineLinkInteractor(oriented)
    {}

protected:
    virtual
    IlvLinkImage*	makeLink(IlUInt count, IlvPoint* points);
};

ILVGRAPHMODULEINIT(plylink);
#endif /* __Ilv_Grapher_Polylink_H */
