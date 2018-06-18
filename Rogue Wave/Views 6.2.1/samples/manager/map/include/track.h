// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/map/include/track.h
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
// Declaring the Track object
// --------------------------------------------------------------------------

#ifndef __ILV_TRACKH
#define __ILV_TRACKH

#include <ilviews/base/graphic.h>
#include <string.h>

// --------------------------------------------------------------------------
// Constants
#define TRACKMAXLASTPOSITION 6
#define TRACKMAXCHARS        30

// --------------------------------------------------------------------------
class Track
    : public IlvSimpleGraphic
{
public:
    Track(IlvDisplay*     display,
	  const IlvPoint& position,
	  const IlvPoint& destination,
	  const char*     label,
	  IlvPalette*     palette          = 0,
	  IlvPalette*     highlightPalette = 0,
	  IlvPalette*     alternatePalette = 0);

    ~Track();

    void		setLabel(const char* s)
			{
			    delete _label;
			    _label = new char[1 + strlen(s)];
			    strcpy(_label, s);
			}
    // ---------------------------------------------------
    // drawing stuff
    IlBoolean 		zoomable() const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&              rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t) const;
    void		newPosition(const IlvPoint&);
    void		translatePosition(const IlvPoint&);

    // ---------------------------------------------------
    // ----> Get
    const IlvPoint&	getPosition()      const { return _position;      }
    const IlvPoint&	getDestination()   const { return _destination;   }
    const IlvPoint&	getSpeedPosition() const { return _speedPosition; }
    const IlvPoint&	getLastPositions(IlUInt pos) const
			{
			    return _lastPositions[pos];
			}
    IlBoolean		showLastPositions() const
			{
			    return _showLastPositions;
			}
    IlBoolean		showSpeed() const { return _showSpeed; }
    IlBoolean		showLabel() const { return _showLabel; }
    IlBoolean		showRoute() const { return _showRoute; }

    IlUInt		getSpeed()  const { return _speed;  }
    IlUInt		getHeight() const { return _height; }
    IlvDim		getWarningDistance() const { return _warningDistance; }
    IlBoolean		hasLanded() const
			{
			    return (_position == _destination)
				? IlTrue
				: IlFalse;
			}
    IlvPalette*         getHighlightPalette() const
			{ return _highlightPalette; }
    IlvPalette*         getAlternatePalette() const
			{ return _alternatePalette; }
    // ----> Set
    void		showLastPositions(IlBoolean value)
			{
			    _showLastPositions = value;
			}
    void		showSpeed(IlBoolean value) { _showSpeed = value; }
    void		showLabel(IlBoolean value) { _showLabel = value; }
    void		showRoute(IlBoolean value) { _showRoute = value; }
    void		init(const IlvPoint& pos, const IlvPoint& dest);
    void		land() { newPosition(_destination); }

    void		setSpeed(IlUInt val);
    void		setHeight(IlUInt val);
    void		setWarningDistance(IlvDim val)
			{ _warningDistance = val; }

    virtual void	setFont(IlvFont*);
    void		setHighlightPalette(IlvPalette* pal)
			{
			    pal->lock();
			    _highlightPalette->unLock();
			    _highlightPalette = pal;
			}
    void		setAlternatePalette(IlvPalette* pal)
			{
			    pal->lock();
			    _alternatePalette->unLock();
			    _alternatePalette = pal;
			}

    DeclareTypeInfo();

protected:
    // visibility flags
    IlBoolean		_showLastPositions;
    IlBoolean		_showSpeed;
    IlBoolean		_showLabel;
    IlBoolean		_showRoute;
    // geometric position
    IlvPoint		_position;
    IlvPoint		_lastPositions[TRACKMAXLASTPOSITION];
    IlvPoint		_speedPosition;
    IlvPoint		_destination;
    IlUInt		_speed;
    IlUInt		_height;
    IlvDim		_warningDistance;
    IlvPalette*		_highlightPalette;
    IlvPalette*		_alternatePalette;
    char*		_label;
    char		_speedStr[16];
    char		_heightStr[16];
    IlUInt		_width1;
    IlUInt		_width2;
    IlUInt		_width3;
};

#endif /* !__ILV_TRACKH */
