// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/gui/coordview.h
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
// Rogue Wave Views - Maps add-on.
// Declaration of the IlvMapCoordViewer class
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __IlvMapsCoordViewerBar_H__
#define __IlvMapsCoordViewerBar_H__

#include <ilviews/manager/manager.h>
#include <ilviews/base/graphic.h>
#include <ilviews/maps/macros.h>

ILVMAPSMODULEINIT(mapcoordviewer);


class _IlvCoordViewerInternalHook;
enum IlvMapCoordViewerMode {
    IlvMapCartesianMode,
    IlvMapDMSMode
};

class ILVMAPSEXPORTED IlvMapCoordViewer : public IlvSimpleGraphic
{
public:
    IlvMapCoordViewer(IlvDisplay* display,
		      const IlvRect& rect,
		      IlvPalette* palette = 0); 

    IlvMapCoordViewer(IlvDisplay* display,
		      const IlvPoint& pos,
		      IlvPalette* palette = 0); 

    virtual ~IlvMapCoordViewer();

    virtual void	draw(IlvPort *dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    virtual void	boundingBox(IlvRect& rect,
				    const IlvTransformer* t) const;
    virtual void	applyTransform(const IlvTransformer* t);

    void		setView(IlvView* view);

    void		setEastinglabel(const char* label,
					IlBoolean redraw = IlFalse);

    const char*		getEastinglabel() { return _eastinglabel; }

    void		setNorthinglabel(const char* label,
					 IlBoolean redraw = IlFalse);

    const char*		getNorthinglabel() { return _northinglabel; }

    void		setEastingFormat(const char* format,
					 IlBoolean redraw = IlFalse);

    const char*		getEastingFormat() { return _eastingFormat; }

    void		setNorthingFormat(const char* format,
					  IlBoolean redraw = IlFalse);

    const char*		getNorthingFormat() { return _northingFormat; }

    const char*		getCantComputeErrorString()
			{
			    return _cantComputeErrorString;
			}

    const char*		getNoGeoErrorString() { return _noGeoErrorString; }

    void		setDisplayingNorthing(IlBoolean displayNorthing,
					      IlBoolean redraw = IlFalse);

    IlBoolean		isDisplayingNorthing() { return _displayNorthing; }

    void		setDisplayingEasting(IlBoolean displayEasting,
					     IlBoolean redraw = IlFalse);

    IlBoolean		isDisplayingEasting() { return _displayEasting; }

     void		setVertical(IlBoolean vertical,
				    IlBoolean redraw = IlFalse);

    void		setDisplayMode(IlvMapCoordViewerMode mode,
				       IlBoolean redraw = IlFalse);

    // not documented
    void		show(IlvEvent&);
    void		show();

    DeclareTypeInfo();
    DeclareIOConstructors(IlvMapCoordViewer);

private:
    void		rectangles();
    void		init();

    IlvView*		_view;
    IlvManager*		_manager;
    IlvMapCoordViewerMode _mode;
    IlBoolean		_displayNorthing;
    IlBoolean		_displayEasting;
    IlBoolean		_vertical;

    IlvRect		_box;
    IlvRect		_east;
    IlvRect		_north;
    IlvDim		_margin;

    char*		_northinglabel;
    char*		_eastinglabel;
    char*		_northingFormat;
    char*		_eastingFormat;
    char*		_cantComputeErrorString;
    char*		_noGeoErrorString;
    char*		_eastingBuffer;
    IlUInt		_eastingBufferSize;
    char*		_northingBuffer;
    IlUInt		_northingBufferSize;

    _IlvCoordViewerInternalHook* _hook;
    IlvPos		_x;
    IlvPos		_y;
    IlBoolean		_noGeoRef;
};

#endif /* __IlvMapsCoordViewerBar_H__*/
