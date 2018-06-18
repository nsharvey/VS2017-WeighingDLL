// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/paninter.h
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
// Declaration of the IlvPanInteractor class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Paninter_H
#define __Ilv_Manager_Paninter_H

#if !defined(__Ilv_Manager_Macros_H)
#  include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#  include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvPanZoomInteractor
    : public IlvManagerViewInteractor
{
public:
    IlvPanZoomInteractor(IlvManager* manager,
			 IlvView*    view,
			 IlvCursor*  handup   = 0,
			 IlvCursor*  handdown = 0,
			 IlvCursor*  zoomin   = 0,
			 IlvCursor*  zoomout  = 0);
    IlvPanZoomInteractor(IlvCursor*  handup   = 0,
			 IlvCursor*  handdown = 0,
			 IlvCursor*  zoomin   = 0,
			 IlvCursor*  zoomout  = 0);
    virtual ~IlvPanZoomInteractor();
    // ____________________________________________________________
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	attach(IlvManager* manager,
			       IlvView* view);    
    virtual void	init();
    virtual void	abort();

    inline void		setOpaqueMove(IlBoolean set) { _opaquemode = set; }

    inline IlBoolean	isOpaqueMove() const { return _opaquemode; }

    virtual void	setZoomInCursor(IlvCursor* c);

    virtual void	setZoomOutCursor(IlvCursor* c);

    virtual void	setDragCursor(IlvCursor* c);

    virtual void	setDefaultCursor(IlvCursor* c); 

    inline IlvCursor*	getZoomInCursor() const { return _zoomin; }

    inline IlvCursor*	getZoomOutCursor() const { return _zoomout; }

    inline IlvCursor*	getDragCursor() const { return _down; }

    inline IlvCursor*	getDefaultCursor() const  { return _up; }

    inline void		setDrawingBitmap(IlBoolean set)
	{ _drawingBitmap = set; }
    inline IlBoolean	isDrawingBitmap() const
	{ return _drawingBitmap; }

    inline void		setZoomingRatio(IlFloat sx) { _zoomx = sx; }
    inline IlFloat	getZoomingRatio() const { return _zoomx; }

    inline void		setMaxZoomingFactor(IlFloat sx)
	{ _maxzoomx = sx; }
    inline IlFloat	getMaxZoomingFactor() const
	{ return _maxzoomx; }
    inline void		setMinZoomingFactor(IlFloat sx)
	{ _minzoomx = sx; }
    inline IlFloat	getMinZoomingFactor() const { return _minzoomx; }

    virtual void	drawGhost();

    void		allocateBitmap();

    IlvPanZoomInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    virtual void	doTranslate(IlvPos dx,
				    IlvPos dy,
				    IlBoolean reDraw);
    virtual void	doZoom(const IlvPoint& center,
			       IlFloat         scalex,
			       IlBoolean       reDraw);
    virtual void	drawBitmap();

    void		checkZoomTransformer(IlvTransfoParam sx);
private:
    void		createCursors();
    void		cleanBitmap();

    IlvCursor*		_up ;
    IlvCursor*		_down;
    IlvCursor*		_previous;
    IlvCursor*		_zoomin;
    IlvCursor*		_zoomout;
    IlvRect		_bbox;
    IlvPoint		_startp;
    IlvPoint		_previousp;
    IlvPoint		_previouszoomp;
    IlvPalette*		_palette;
    IlBoolean		_opaquemode;
    IlBoolean		_dragging;
    IlBoolean		_drawingBitmap;
    IlBoolean		_initialized;
    IlBoolean		_bitmapCreated;
    IlFloat		_zoomx;
    IlFloat		_maxzoomx;
    IlFloat		_minzoomx;
    IlvTransformer	_zoomtr;
    IlvBitmap*		_bitmap;
    IlvBitmap*		_dblbufBitmap;
};

ILVMGRMODULEINIT(m0_paninter);

#endif /* !__Ilv_Manager_Paninter_H */
