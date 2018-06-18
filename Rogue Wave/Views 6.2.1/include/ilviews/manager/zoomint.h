// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/zoomint.h
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
// Declaration of the IlvZoomInteractor class
// Defined in library ilvmgr.
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Zoomint_H
#define __Ilv_Manager_Zoomint_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

class ILVMGREXPORTED IlvZoomInteractor : public IlvManagerViewInteractor
{
public:
    IlvZoomInteractor(IlvManager* manager,
		      IlvView*    view,
		      IlUShort    button  = IlvLeftButton,
		      IlUShort    mbutton = IlvMiddleButton | IlvRightButton,
		      IlvCursor*  defaultCursor = 0);
    virtual ~IlvZoomInteractor();

    virtual IlBoolean	handleEvent(IlvEvent& event);

    void		getParams(IlvTransfoParam& cx,
				  IlvTransfoParam& cy,
				  IlvTransfoParam& sx,
				  IlvTransfoParam& sy,
				  IlvTransfoParam& tx,
				  IlvTransfoParam& ty) const;

    IlBoolean		giveTransformer(IlvTransformer& transformer,
					IlBoolean       compute = IlTrue);

    virtual void	doZoom();

    virtual void	abortOperation();

    virtual void	abort();

    virtual void	drawGhost();

    virtual void	decorate();

    inline void		setImmediateMode(IlBoolean set)
			{
			    _immediateMode = set;
			}

    inline IlBoolean	getImmediateMode() { return _immediateMode; }

    inline IlBoolean	isKeepingAspectRatio() { return _kar; }

    void		setZoomCursor(IlvCursor* newCursor);

    void		getRectangle(IlvRect& rect);

    virtual void	attach(IlvManager* manager, IlvView* view);

    IlvZoomInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

private:
    IlUShort		_button;
    IlUShort		_moveButton;

    IlBoolean		_started;
    IlBoolean		_aborted;
    IlBoolean		_immediateMode;

    IlvPos		_startX;
    IlvPos		_startY;
    IlvPos		_lastX;
    IlvPos		_lastY;
    IlvPos		_xOffset;
    IlvPos		_yOffset;
    IlvRect		_oldRect;

    IlvCursor*		_zoomCursor;
    IlvCursor*		_prevCursor;    
    IlvCursor*		_defaultCursor;    
    IlBoolean		_inRect;
    IlBoolean		_kar;

    IlvTransfoParam	_centerX;
    IlvTransfoParam	_centerY;
    IlvTransfoParam	_scaleX;
    IlvTransfoParam	_scaleY;
    IlvTransfoParam	_trX;
    IlvTransfoParam	_trY;

    void		resizeRect(IlvPos&, IlvPos&);
    void		moveRect(IlvPos&, IlvPos&);
    IlBoolean		computeRect(IlvRect& r);
    IlBoolean		inRect(IlvPos, IlvPos);
    void		btnDown(IlvPos, IlvPos);   
    void		handleEnsureVisible(IlvPos&, IlvPos&);
    IlBoolean		transformer(IlvTransformer&);
    void		zoom();
    IlvCursor*		zoomCursor();
    void		computeParams();
    void		createDefaultCursor();
};

ILVMGRMODULEINIT(m0_zoomint);

#endif /* !__Ilv_Manager_Zoomint_H */
