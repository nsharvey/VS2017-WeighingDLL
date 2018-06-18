// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/magview.h
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
// Declaration of the IlvManagerMagViewInteractor class
// Defined in library ilvmgr.
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Magview_H
#define __Ilv_Manager_Magview_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

class _IlvMagViewHook;

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerMagViewInteractor
: public IlvManagerViewInteractor
{
    friend class _IlvMagViewHook;
public:
    IlvManagerMagViewInteractor(IlvManager* manager,
				IlvView*    overview,
				IlvView*    target = 0);
    ~IlvManagerMagViewInteractor();
    // ____________________________________________________________

    void		setTarget(IlvView* view);

    inline IlvView*	getTarget() const { return _target; }

    inline IlvGraphic*	getGraphic() const { return _graphic; }

    void		setGraphic(IlvGraphic* gr);

    void		setDrawSelection(IlvDrawSelection* dr);

    IlvDrawSelection*	getDrawSelection();

    virtual void	computeRectangle();
    virtual void	computeRectangle(IlvRect& rect) const;
    virtual void	invalidateGraphic(IlBoolean erase  = IlFalse);
    virtual void	init();
    virtual void	abort();

    virtual void	adjustView(const IlvRect& rect);

    virtual void	resetOverview();

    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	handleResizing(IlvEvent& event);

    inline void		setAutoZooming(IlBoolean set) { _zoommode = set; }

    inline IlBoolean	isAutoZooming() const { return _zoommode; }

    void		setAutoTranslating(IlBoolean set);

    inline IlBoolean	isAutoTranslating() const { return _translatemode; }

    inline void		setAutoZoomConstrained(IlBoolean set)
			{
			    _autoZoomConstrained = set;
			}

    inline IlBoolean	isAutoZoomConstrained() const
			{
			    return _autoZoomConstrained;
			}

    inline void		setResizingAllowed(IlBoolean allow)
			{
			    _allowResize = allow;
			}

    inline IlBoolean	isResizingAllowed() const { return _allowResize; }
    inline void		enableArrowKeysFiltering(IlBoolean set)
			{
			    _isFilteringArrows = set;
			}

    IlvManagerMagViewInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    void		initHooks();
    void		reconnectHooks();
    void		disconnectHooks();
    void		deleteHooks();

    IlBoolean		_isDragging;
    IlBoolean		_translatemode;
    IlBoolean		_fittedtocontents;
    IlBoolean		_autoZoomConstrained;
    IlBoolean		_zoommode;
    IlBoolean		_previoustranslatemode;
    IlBoolean		_allowResize;
    IlBoolean		_isResizing;
    IlBoolean		_isFilteringArrows;
    IlBoolean		_isErasing;
    IlBoolean		_isAdjusting;
    IlvView*		_target;
    IlvRect		_rect;
    IlvManagerViewHook*	_targetHook;
    IlvManagerViewHook*	_thisHook;
    IlvGraphic*		_graphic;
    IlvDrawSelection*	_selection;
    IlvPos		_startx;
    IlvPos		_starty;
    IlFloat		_translatex;
    IlFloat		_translatey;
    IlvPoint		_center;

private:
    IlBoolean		isTranslation(const IlvTransformer& prev,
				      const IlvTransformer& cur) const;
    IlBoolean		isZoom(const IlvTransformer& prev,
			       const IlvTransformer& cur) const;
    IlBoolean		isTransfoParamEqual(IlvTransfoParam d1,
					    IlvTransfoParam d2) const ;
    virtual IlBoolean	notifyAutoTranslate();
    virtual IlBoolean	notifyAutoZoom();
    virtual void	getAutoTranslationFactors(IlvTransformer* targetTransf,
						  IlvPos&         dx,
						  IlvPos&         dy) const;
    virtual void	getAutoZoomFactors(IlvTransformer* targetTransformer,
					   IlFloat&       sx,
					   IlFloat&       sy) const;
    virtual void	handleFitToBBox(IlvTransfoParam sx,
					IlvTransfoParam sy,
					IlBoolean       redraw);
    virtual IlvTransformer* zoomTransformer(IlvTransformer* initial,
					    IlvPoint        point,
					    IlvTransfoParam sx,
					    IlvTransfoParam sy);
};


ILVMGRMODULEINIT(m0_magview);

#endif /* !__Ilv_Manager_Magview_H */
