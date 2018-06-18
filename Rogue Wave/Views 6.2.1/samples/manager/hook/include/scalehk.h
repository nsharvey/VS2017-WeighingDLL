// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/hook/include/scalehk.h
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
//
// --------------------------------------------------------------------------

#include <ilviews/graphics/scale.h>
#include <ilviews/contain/contain.h>
#include <ilviews/manager/manager.h>

// --------------------------------------------------------------------------
class Ilv1ScaleHook
    : public IlvManagerViewHook
{
protected:

    // IlvManagerViewHook virtual functions
    void			beforeDraw(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* region = 0,
					   const IlvRegion* clip   = 0);

    IlvRectangularScale*	_scale;
public:

    Ilv1ScaleHook(IlvManager* mgr,
		  IlvView* view,
		  IlvRectangularScale* scale)
      : IlvManagerViewHook(mgr, view) { _scale = scale; }
    ~Ilv1ScaleHook() { delete _scale; }
    // ____________________________________________________________
    IlvRectangularScale*	getScale()	const { return _scale; }
    void			drawScale(IlvPort* dst,
					  const IlvTransformer* t,
					  const IlvRegion* clip);
};

// ---------------------------------------------------------------------------
class Ilv4ScaleHook
    : public IlvManagerViewHook
{
public:
    Ilv4ScaleHook(IlvManager* mgr,
		  IlvView* view,
		  IlvView* parentView);
    ~Ilv4ScaleHook();

    // ____________________________________________________________

    IlvView*		getParentView()		const { return _parentView; }
    IlvManager*		getSManager()		const { return _sManager; }
    Ilv1ScaleHook*	getTopSHook()		const { return _topSHook; }
    Ilv1ScaleHook*	getBottomSHook()	const { return _bottomSHook; }
    Ilv1ScaleHook*	getLeftSHook()		const { return _leftSHook; }
    Ilv1ScaleHook*	getRightSHook()		const { return _rightSHook; }

    void		getTopRects(IlvRect& left,
				    IlvRect& right) const;
    void		getBottomRects(IlvRect& left,
				       IlvRect& right) const;
    void		getLeftRects(IlvRect& top,
				     IlvRect& bottom) const;
    void		getRightRects(IlvRect& top,
				      IlvRect& bottom) const;

    void		drawTopScaleRects();
    void		drawBottomScaleRects();
    void		drawLeftScaleRects();
    void		drawRightScaleRects();

    void		computeHScales(IlvTransfoParam xTranslate,
				       IlvTransfoParam xZoom);
    void		computeVScales(IlvTransfoParam yTranslate,
				       IlvTransfoParam yZoom);

protected:
    IlvView*		_parentView;

    // one manager and 4 hooks, each one managing one scale;
    IlvManager*		_sManager;
    Ilv1ScaleHook*	_topSHook;
    Ilv1ScaleHook*	_bottomSHook;
    Ilv1ScaleHook*	_leftSHook;
    Ilv1ScaleHook*	_rightSHook;

    // ManagerViewHook virtual functions;
    void		transformerChanged(const IlvTransformer* current,
					   const IlvTransformer* old);
    void		viewResized();
};
