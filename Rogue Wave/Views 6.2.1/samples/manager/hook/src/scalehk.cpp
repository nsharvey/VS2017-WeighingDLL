// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/hook/src/scalehk.cpp
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
// Definition of the classes Ilv1ScaleHook and Ilv4ScaleHook
// Needed for the scalemgr sample.
// --------------------------------------------------------------------------

#include "scalehk.h"

// --------------------------------------------------------------------------
// Margin between the scales and the window they are tied to.
#define S_MARGIN 5

// Scale format
#define S_FORMAT "%g"

// Small dimension of the scales (width if vertical, height if horizontal).
#define S_DIM 50

// space between 2 major ticks (initial value);
#define S_STEP 100

// default value for the number of steps in a scale (= nb of ticks -1)
#define S_NSTEPS 5

// default value for the number of substeps in a scale
#define S_NSUBSTEPS 10

#define TOP_S		(getTopSHook()->getScale())
#define TOP_V		(getTopSHook()->getView())
#define BOTTOM_S	(getBottomSHook()->getScale())
#define BOTTOM_V	(getBottomSHook()->getView())
#define LEFT_S		(getLeftSHook()->getScale())
#define LEFT_V		(getLeftSHook()->getView())
#define RIGHT_S		(getRightSHook()->getScale())
#define RIGHT_V		(getRightSHook()->getView())

// --------------------------------------------------------------------------
static IlvPos
computeScales(IlvRectangularScale*	scale1,
	      IlvRectangularScale*	scale2,
	      IlvDim			view_size,
	      IlDouble			initial_step,
	      IlDouble			translation,
	      IlDouble			ratio)
{
    // returns the position that the scale should take, relative to
    // the window it is drawn in.
    IlDouble gradratio = 1.;
    if (ratio > 1.)
	gradratio = 1. / ILVCAST(IlInt, ratio + 0.5);    // zoom in;
    else if ((0. < ratio) && (ratio < 1.))
	gradratio = ((IlInt)(0.5 + 1. / ratio));    // zoom out

    IlDouble new_step =
	(ratio == 1.) ? initial_step : initial_step * ratio * gradratio;

    // index of the major tick <= window origin
    IlInt iMin = ILVCAST(IlInt, -translation / new_step);
    --iMin; // just to make sure...
    // index of the major tick >= window origin + width
    IlInt iMax = ILVCAST(IlInt, (view_size - translation) / new_step) + 1;

    IlDouble new_min = iMin * ILVCAST(IlInt, new_step);
    IlDouble new_max = iMax * ILVCAST(IlInt, new_step);

    if (ratio != 1.) {
	new_min *= gradratio;
	new_max *= gradratio;
    }

    scale1->setLabels(ILVCAST(IlUShort, iMax - iMin + 1),
		      ILVCAST(IlFloat, new_min),
		      ILVCAST(IlFloat, new_max),
		      S_FORMAT);
    scale2->setLabels(ILVCAST(IlUShort, iMax - iMin + 1),
		      ILVCAST(IlFloat, new_min),
		      ILVCAST(IlFloat, new_max),
		      S_FORMAT);
    scale1->setSize(ILVCAST(IlvDim, (iMax - iMin) * ILVCAST(IlInt, new_step)));
    scale2->setSize(ILVCAST(IlvDim, (iMax - iMin) * ILVCAST(IlInt, new_step)));
    return ILVCAST(IlvPos, (iMin * new_step) + translation);
}

// --------------------------------------------------------------------------
void
Ilv1ScaleHook::beforeDraw(IlvPort*		dst,
			  const IlvTransformer* /*t*/,
			  const IlvRegion*	/*region*/,
			  const IlvRegion*	clip)
{
    // scales are drawn without transformer;
    // they are recomputed to simulate zooming and translation.
    drawScale(dst, 0, clip);
}

// --------------------------------------------------------------------------
void
Ilv1ScaleHook::drawScale(IlvPort*		dst,
			 const IlvTransformer*	t,
			 const IlvRegion*	clip)
{
    getScale()->draw(dst ? dst : getView(), t, clip);
}

// --------------------------------------------------------------------------
static void
redrawExtraPieces(IlvView* /*parentView*/,
		  IlvEvent& event,
		  IlAny arg)
{
    // work area expose callback;
    // must refresh the parts of the scale drawn out of the
    // of the scale view boundaries.

    IlvRect rect(event.x(), event.y(), event.w(), event.h());
    Ilv4ScaleHook* hook = (Ilv4ScaleHook*)arg;

    IlvRect rect1, rect2;

    hook->getTopRects(rect1, rect2);
    if (rect.intersects(rect1) || rect.intersects(rect2))
	hook->drawTopScaleRects();

    hook->getBottomRects(rect1, rect2);
    if (rect.intersects(rect1) || rect.intersects(rect2))
	hook->drawBottomScaleRects();

    hook->getLeftRects(rect1, rect2);
    if (rect.intersects(rect1) || rect.intersects(rect2))
	hook->drawLeftScaleRects();

    hook->getRightRects(rect1, rect2);
    if (rect.intersects(rect1) || rect.intersects(rect2))
	hook->drawRightScaleRects();
}

// --------------------------------------------------------------------------
Ilv4ScaleHook::~Ilv4ScaleHook()
{
    delete _sManager;
    delete _topSHook;
    delete _bottomSHook;
    delete _leftSHook;
    delete _rightSHook;
}

// --------------------------------------------------------------------------
Ilv4ScaleHook::Ilv4ScaleHook(IlvManager* mgr,
			     IlvView*	 view,
			     IlvView*	 parentView)
    : IlvManagerViewHook(mgr, view)
{
    _parentView = parentView;
    IlvRect vRect;
    view->boundingBox(vRect);

    IlvDisplay* dpy = parentView->getDisplay();
    // make the scale views visible
    IlvColor* bgColor = dpy->getColor("palegreen");
    if (bgColor)
	bgColor->lock();
    _sManager = new IlvManager(dpy, 2, IlFalse);

    // -------------------------------
    // create views, scales and hooks
    // -------------------------------
    // top scale
    IlvRect svRect(vRect.x(), vRect.y() - S_MARGIN - S_DIM, vRect.w(), S_DIM);
    IlvView* sview = new IlvView(parentView, svRect, IlTrue);
    if (bgColor)
	sview->setBackground(bgColor);
    getSManager()->addView(sview);
    IlvPoint orig(0, sview->height() - 1);
    IlvRectangularScale* scale =
	new IlvRectangularScale(dpy,
				orig,
				S_STEP * S_NSTEPS,
				S_FORMAT,
				(IlFloat)0,
				(IlFloat)(S_STEP * S_NSTEPS),
				IlvLeft,
				IlvTop,
				S_NSTEPS + 1,
				S_NSUBSTEPS);
    _topSHook = new Ilv1ScaleHook(getSManager(), sview, scale);
    getSManager()->installViewHook(getTopSHook());

    // bottom scale
    svRect.move(vRect.x(), vRect.y() + vRect.h() + S_MARGIN);
    sview = new IlvView(parentView, svRect, IlTrue);
    if (bgColor)
	sview->setBackground(bgColor);
    getSManager()->addView(sview);
    orig.move(0, 0);
    scale = new IlvRectangularScale(dpy,
				    orig,
				    S_STEP * S_NSTEPS,
				    S_FORMAT,
				    (IlFloat)0,
				    (IlFloat)(S_STEP * S_NSTEPS),
				    IlvLeft,
				    IlvBottom,
				    S_NSTEPS,
				    S_NSUBSTEPS);

    _bottomSHook = new Ilv1ScaleHook(getSManager(), sview, scale);
    getSManager()->installViewHook(getBottomSHook());

    // left scale
    svRect.moveResize(vRect.x() - S_MARGIN - S_DIM, vRect.y(),
		      S_DIM, vRect.h());
    sview = new IlvView(parentView, svRect, IlTrue);
    if (bgColor)
	sview->setBackground(bgColor);
    getSManager()->addView(sview);
    orig.move(sview->width() - 1, 0);
    scale = new IlvRectangularScale(dpy,
				    orig,
				    S_STEP * S_NSTEPS,
				    S_FORMAT,
				    (IlFloat)0,
				    (IlFloat)(S_STEP * S_NSTEPS),
				    IlvTop,
				    IlvLeft,
				    S_NSTEPS,
				    S_NSUBSTEPS);
    _leftSHook = new Ilv1ScaleHook(getSManager(), sview, scale);
    getSManager()->installViewHook(getLeftSHook());

    // right scale
    svRect.move(vRect.x() + vRect.h() + S_MARGIN, vRect.y());
    sview = new IlvView(parentView, svRect, IlTrue);
    if (bgColor)
	sview->setBackground(bgColor);
    getSManager()->addView(sview);
    orig.move(0, 0);
    scale = new IlvRectangularScale(dpy,
				    orig,
				    S_STEP * S_NSTEPS,
				    S_FORMAT,
				    (IlFloat)0,
				    (IlFloat)(S_STEP * S_NSTEPS),
				    IlvTop,
				    IlvRight,
				    S_NSTEPS,
				    S_NSUBSTEPS);
    _rightSHook = new Ilv1ScaleHook(getSManager(), sview, scale);
    getSManager()->installViewHook(getRightSHook());

    // set an expose callback on the parent view to redraw
    // the little pieces of junk that we draw around the scale views;
    parentView->setExposeCallback(redrawExtraPieces, this);

    if (bgColor)
	bgColor->unLock();
}


// --------------------------------------------------------------------------
void
Ilv4ScaleHook::transformerChanged(const IlvTransformer* current,
				  const IlvTransformer* /*old*/)
{
    // Only handle scaling and translation;
    IlvTransfoParam xI, yI, xJ, yJ, xO, yO;
    current->getValues(xI, yI, xJ, yJ, xO, yO);
    // make sure there is no rotation;
    if ((xI == 0) || (yI != 0) || (xJ != 0) || (yJ == 0)) {
	IlvWarning("Ilv4ScaleHook::transformerChanged : Illegal transformer");
	return;
    }

    // for horizontal scales, translate&zoom only in x direction
    IlvTransformer transf(xI, 0., 0., 1., xO, 0.);
    IlvTransfoParam cxI, cyI, cxJ, cyJ, cxO, cyO;
    IlvTransformer* ctransf = getSManager()->getTransformer(TOP_V);
    if (ctransf)
	ctransf->getValues(cxI, cyI, cxJ, cyJ, cxO, cyO);
    else {
	cxI = 1.;
	cxO = 0.;
    }
    if ((xI != cxI) || (xO != cxO)) {
	getSManager()->setTransformer(TOP_V, &transf);
	getSManager()->setTransformer(BOTTOM_V, &transf);
	computeHScales(xO, xI);
    }
    // for vertical scales, translate&zoom only in y direction
    transf.setValues(1., 0., 0., yJ, 0., yO);
    ctransf = getSManager()->getTransformer(LEFT_V);
    if (ctransf)
	ctransf->getValues(cxI, cyI, cxJ, cyJ, cxO, cyO);
    else {
	cyJ = 1.;
	cyO = 0.;
    }
    if ((yJ != cyJ) || (yO != cyO)) {
	computeVScales(yO, yJ);
	getSManager()->setTransformer(LEFT_V, &transf);
	getSManager()->setTransformer(RIGHT_V, &transf);
    }
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::viewResized()
{
    IlvTransfoParam xO = 0.;
    IlvTransfoParam yO = 0.;
    IlvTransfoParam xI = 1.;
    IlvTransfoParam yJ = 1.;
    IlvTransfoParam yI, xJ;
    IlvTransformer* t = getManager()->getTransformer(getView());
    if (t) {
	t->getValues(xI, yI, xJ, yJ, xO, yO);
	if ((yI != 0.) || (xJ != 0.))
	    return;
    }
    computeHScales(xO, xI);
    computeVScales(yO, yJ);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::computeHScales(IlvTransfoParam xTranslate,
			      IlvTransfoParam xZoom)
{
    IlvRectangularScale* top_s = TOP_S;
    IlvRectangularScale* bot_s = BOTTOM_S;
    IlvView*             top_v = TOP_V;
    IlvView*             bot_v = BOTTOM_V;

    IlvPos x =
	computeScales(top_s, bot_s, top_v->width(), S_STEP, xTranslate, xZoom);
    top_s->setOrigin(IlvPoint(x, top_v->height() - 1));
    bot_s->setOrigin(IlvPoint(x, 0));

    drawTopScaleRects();
    drawBottomScaleRects();
    top_v->erase(IlTrue);
    bot_v->erase(IlTrue);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::computeVScales(IlvTransfoParam yTranslate,
			      IlvTransfoParam yZoom)
{
    IlvRectangularScale* left_s  = LEFT_S;
    IlvRectangularScale* right_s = RIGHT_S;
    IlvView*             left_v  = LEFT_V;
    IlvView*             right_v = RIGHT_V;

    IlvPos y = computeScales(left_s,
			     right_s,
			     left_v->height(),
			     S_STEP,
			     yTranslate,
			     yZoom);
    left_s->setOrigin(IlvPoint(left_v->width() - 1, y));
    right_s->setOrigin(IlvPoint(0, y));

    drawLeftScaleRects();
    drawRightScaleRects();
    left_v->erase(IlTrue);
    right_v->erase(IlTrue);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::getTopRects(IlvRect& leftRect,
			   IlvRect& rightRect) const
{
    IlvRect vbox;
    TOP_V->boundingBox(vbox);
    IlvDim w = 5 * TOP_S->getFont()->maxWidth();
    IlvDim h = vbox.h() - TOP_S->getStepSize() - 1;
    leftRect.moveResize(vbox.x() - w, vbox.y(), w, h);
    rightRect.moveResize(vbox.x() + vbox.w(), leftRect.y(), w, h);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::getBottomRects(IlvRect& leftRect,
			      IlvRect& rightRect) const
{
    IlvRect vbox;
    BOTTOM_V->boundingBox(vbox);
    IlvDim w = 5 * BOTTOM_S->getFont()->maxWidth();
    IlvDim h = vbox.h() - BOTTOM_S->getStepSize() - 1;
    leftRect.moveResize(vbox.x() - w, vbox.y() + vbox.h() - h, w, h);
    rightRect.moveResize(vbox.x() + vbox.w(), leftRect.y(), w, h);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::getLeftRects(IlvRect& topRect,
			    IlvRect& bottomRect) const
{
    IlvRect vbox;
    LEFT_V->boundingBox(vbox);
    IlvDim w = vbox.w() - LEFT_S->getStepSize() - 1;
    IlvDim h = LEFT_S->getFont()->height();
    topRect.moveResize(vbox.x(), vbox.y() - h, w, h);
    bottomRect.moveResize(topRect.x(), vbox.y() + vbox.h(), w, h);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::getRightRects(IlvRect& topRect,
			     IlvRect& bottomRect) const
{
    IlvRect vbox;
    RIGHT_V->boundingBox(vbox);
    IlvDim w = vbox.w() - RIGHT_S->getStepSize() - 1;
    IlvDim h = RIGHT_S->getFont()->height();
    topRect.moveResize(vbox.x() + vbox.w() - w, vbox.y() - h, w, h);
    bottomRect.moveResize(topRect.x(), vbox.y() + vbox.h(), w, h);
}

// --------------------------------------------------------------------------
// Draw a piece of the scale in the parent window
// so that labels do not appear clipped.
// Let us hope that nothing else is drawn at
// this location in the parent window !!
// --------------------------------------------------------------------------
void
Ilv4ScaleHook::drawTopScaleRects()
{
    IlvRect leftClip, rightClip;
    getTopRects(leftClip, rightClip);

    IlvRegion clipRegion(leftClip);
    clipRegion.add(rightClip);

    // compute the transformer needed to draw the scale in the parent window
    IlvTransformer  scaleTransf;
    IlvPoint pos;
    TOP_V->position(pos);
    scaleTransf.translate((IlFloat)pos.x(), (IlFloat)pos.y());

    getParentView()->erase(leftClip);
    getParentView()->erase(rightClip);
    getTopSHook()->drawScale(getParentView(), &scaleTransf, &clipRegion);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::drawBottomScaleRects()
{
    IlvRect leftClip, rightClip;
    getBottomRects(leftClip, rightClip);

    IlvRegion clipRegion(leftClip);
    clipRegion.add(rightClip);

    // compute the transformer needed to draw the scale in the parent window
    IlvTransformer  scaleTransf;
    IlvPoint pos;
    BOTTOM_V->position(pos);
    scaleTransf.translate((IlFloat)pos.x(), (IlFloat)pos.y());

    getParentView()->erase(leftClip);
    getParentView()->erase(rightClip);
    getBottomSHook()->drawScale(getParentView(), &scaleTransf, &clipRegion);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::drawLeftScaleRects()
{
    IlvRect topClip, bottomClip;
    getLeftRects(topClip, bottomClip);

    IlvRegion clipRegion(topClip);
    clipRegion.add(bottomClip);

    // compute the transformer needed to draw the scale in the parent window
    IlvTransformer scaleTransf;
    IlvPoint pos;
    LEFT_V->position(pos);
    scaleTransf.translate((IlFloat)pos.x(), (IlFloat)pos.y());

    getParentView()->erase(topClip);
    getParentView()->erase(bottomClip);
    getLeftSHook()->drawScale(getParentView(), &scaleTransf, &clipRegion);
}

// --------------------------------------------------------------------------
void
Ilv4ScaleHook::drawRightScaleRects()
{
    IlvRect topClip, bottomClip;
    getRightRects(topClip, bottomClip);

    IlvRegion clipRegion(topClip);
    clipRegion.add(bottomClip);

    // compute the transformer needed to draw the scale in the parent window
    IlvTransformer scaleTransf;
    IlvPoint pos;
    RIGHT_V->position(pos);
    scaleTransf.translate((IlFloat)pos.x(), (IlFloat)pos.y());

    getParentView()->erase(topClip);
    getParentView()->erase(bottomClip);
    getRightSHook()->drawScale(getParentView(), &scaleTransf, &clipRegion);
}
