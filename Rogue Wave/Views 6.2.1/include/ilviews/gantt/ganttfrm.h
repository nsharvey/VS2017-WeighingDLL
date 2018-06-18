// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gantt/ganttfrm.h
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
// Declaration of the classes IlvGanttChartForm and
// --------------------------------------------------------------------------
#ifndef __Ilv_Gantt_Ganttfrm_H
#define __Ilv_Gantt_Ganttfrm_H

#if !defined(__Ilv_Gantt_Gantt_H)
#include <ilviews/gantt/gantt.h>
#endif
#if !defined(__Ilv_Graphics_Set_H)
#include <ilviews/graphics/set.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif
#if !defined(__Ilv_Graphics_Handle_H)
#include <ilviews/graphics/handle.h>
#endif
#if !defined(__Ilv_Gadgets_Splitgad_H)
#include <ilviews/gadgets/splitgad.h>
#endif
#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif
#if !defined(__Ilv_Gadgets_Sheet_H)
#include <ilviews/gadgets/sheet.h>
#endif

class IlvGanttResourceHeader;

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttChartForm : public IlvGanttChart
{
public:
    IlvGanttChartForm(IlvDisplay*	display,
		      const IlvRect&	rect,
		      IlInt		start,
		      IlInt		end,
		      IlInt		shownStart,
		      IlInt		shownEnd,
		      IlUShort		step,
		      IlvDim		rowSize,
		      IlvDim		lineInfoSize	= 0,
		      IlvDim		unitSize	= 20,
		      IlvDim		scaleH		= 32,
		      IlvDim		sbSize		= 16,
		      IlUShort		spacing		= 4,
		      IlUShort		vwSpacing	= 20,
		      IlUShort		margin		= 0,
		      IlvDim		separSize	= 6,
		      IlvPosition	hasScale	= IlvTop,
		      IlvPosition	hasHSB		= IlvBottom,
		      IlvPosition	hasVSB		= IlvRight,
		      int		numLayers	= 5,
		      IlBoolean		useAcc		= IlTrue,
		      IlvPalette*	palette		= 0);

    virtual ~IlvGanttChartForm();

    virtual void	deleteAll(IlBoolean destroy,
				  IlBoolean redraw = IlTrue);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	makeView(IlvPort* dst, const IlvTransformer* t);
    virtual void	updateScale(IlvScale* scale,
				    IlBoolean redraw = IlTrue) const;
    void		updateScale(IlUShort hi,
				    IlBoolean redraw = IlTrue) const;
    virtual void	insertLine(IlvGanttLine*, IlUShort row,
				   IlBoolean redraw=IlTrue, int layer=-1);
    virtual void	drawContents(IlvPort* dst, const IlvRect& size,
				     const IlvRegion* clip) const;
    void		drawScaleViewContents(IlUShort i,
					      IlvPort* dst,
					      const IlvRect& size,
					      const IlvRegion* clip) const;
    void		resetShowInterval(IlUShort hi,
					  IlBoolean redraw = IlTrue);
    IlvGraphic*		setCompositeScale(IlvGraphic* compoScale,
					  IlBoolean redraw = IlTrue,
					  IlBoolean reshape = IlFalse);
    IlvGraphic*		getCompositeScale() const;
    IlvGraphic*		setCompositeGrid(IlvGraphic* compoGrid,
					 IlBoolean redraw = IlTrue);
    IlvGraphic*		getCompositeGrid() const;
    IlvScrollBar*	getResourceScrollBar() const
			{
			    return _resourceScrollBar;
			}
    IlvGanttResourceHeader* getResourceHeader() const
			{
			    return _resourceHeader;
			}
    IlvGanttResourceHeader* createResourceHeader();
    void		resetResourceColumnWidths();

    inline IlvView*	getScaleView(IlUShort viewIndex) const
			{
			    return _scaleView[viewIndex];
			}
    inline
    IlvViewRectangle*	viewRectangle(IlInt i, IlInt j) const
			{
			    return _viewRectangle[i][j];
			}
    inline
    IlvSplitterGadget*	horizontalSplitter(IlInt index) const
			{
			    return _horGuideSep[index];
			}
    inline
    IlvSplitterGadget*	verticalSplitter(IlInt index) const
			{
			    return _verGuideSep[index];
			}

    IlFloat		getScaleThreshold() const { return _scaleThreshold;}
    inline void		setScaleThreshold(IlFloat threshold)
			{
			    _scaleThreshold = threshold;
			}

    inline IlBoolean	isScaleThresholdEnabled() const
			{
			    return _enableThreshold;
			}
    void		enableScaleThreshold(IlBoolean threshold,
					     IlBoolean redraw = IlTrue);

    virtual void	calculateRects();
    virtual void	expandPane(IlvDirection dir, IlvPos pos);
    virtual void	collapsePane(IlvDirection dir);
    virtual void	moveSplitter(IlvDirection dir,
				     IlUInt index,
				     IlvPos pos);
    virtual IlvRect&	getLineArea(IlvRect& area) const;
    virtual void	setDoubleBuffering(IlBoolean doubleBuffer);

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_resourceScrollBarValue;
    static IlSymbol*	_resourceHeaderValue;
    static IlSymbol*	_compositeScaleValue;
    static IlSymbol*	_compositeGridValue;
    static IlSymbol*	_getScaleViewMethod;
    static IlSymbol*	_getHorizontalSplitterMethod;
    static IlSymbol*	_getVerticalSplitterMethod;
    static IlSymbol*	_moveHorizontalSplitterMethod;
    static IlSymbol*	_moveVerticalSplitterMethod;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGanttChartForm);

protected:
    void attachComponents(IlvDirection dir);
    void detachComponents(IlvDirection dir);
    void resizeComponents();

private:
    IlvViewRectangle*	_viewRectangle[3][3];
    IlvScrollBar*	_resourceScrollBar;
    IlvGanttResourceHeader* _resourceHeader;
    IlvRect		_rscBarRect;
    IlvView*		_scaleView[2];
    IlvGraphic*		_compoScale;
    IlvGraphic*		_compoGrid;
    IlvSplitterGadget*	_horGuideSep[2];
    IlvSplitterGadget*	_verGuideSep[2];
    IlFloat		_scaleThreshold;
    IlBoolean		_enableThreshold;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttResourceHeader : public IlvSheet
{
public:
    IlvGanttResourceHeader(IlvDisplay*	dsp,
			   const IlvRect& rect,
			   IlShort	cols,
			   IlShort	rows,
			   IlvDim	xgrid	= IlvDefaultMatrixWidth,
			   IlvDim	ygrid	= IlvDefaultMatrixWidth,
			   IlvDim	thickness = IlvDefaultGadgetThickness,
			   IlBoolean	showVSB = IlFalse,
			   IlBoolean	showHSB = IlFalse,
			   IlvPalette*	pal	= 0,
			   IlvGanttChartForm* gantt = 0)
	: IlvSheet(dsp,
		   rect,
		   cols,
		   rows,
		   xgrid,
		   ygrid,
		   thickness,
		   showVSB,
		   showHSB,
		   pal),
	  _gantt(gantt)
    {}

    virtual void	resizeColumn(IlUShort c, IlvDim size);
    void		adjustHScrollBar(IlvScrollBar*  hsb);
    virtual void	scrollBarsHaveMoved(IlInt firstColumn,
					    IlvPosition position);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	ensureVisible(IlUShort colno,
				      IlUShort rowno,
				      IlBoolean redraw = IlTrue);

    inline
    IlvGanttChartForm*	getGanttForm() const { return _gantt; }
    inline void		setGanttForm(IlvGanttChartForm* gantt)
			{
			    _gantt = gantt;
			}

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvGanttResourceHeader);

private:
    IlvGanttChartForm* _gantt;
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvGanttResourceLine : public IlvMatrix
{
public:
    IlvGanttResourceLine(IlvDisplay*	dsp,
			 const IlvRect& rect,
			 IlShort	cols,
			 IlShort	rows,
			 IlvDim		xgrid = IlvDefaultMatrixWidth,
			 IlvDim		ygrid = IlvDefaultMatrixWidth,
			 IlvDim		thickness = IlvDefaultGadgetThickness,
			 IlBoolean	showVSB = IlFalse,
			 IlBoolean	showHSB = IlFalse,
			 IlvPalette*	pal = 0)
	: IlvMatrix(dsp, rect, cols, rows, xgrid, ygrid, thickness, pal)
    {
	if (showHSB)
	    iShowScrollBar(IlvHorizontal);
	if (showVSB)
	    iShowScrollBar(IlvVertical);
	if (showVSB || showHSB)
	    adjustScrollBars(IlFalse);
    }

    void		draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    IlvGanttChartForm*	getGanttChartForm() const;
    virtual void	ensureVisible(IlUShort colno,
				      IlUShort rowno,
				      IlBoolean redraw = IlTrue);


    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvGanttResourceLine);
};

// --------------------------------------------------------------------------
class ILVGTEXPORTED IlvAttachedGraphicSet : public IlvGraphicSet
{
public:
    IlvAttachedGraphicSet(IlInt minWidth = 4, IlInt minHeight = 4);
    virtual ~IlvAttachedGraphicSet();

    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t=0,
			     const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect& r,
				    const IlvTransformer* t = 0) const;

    inline IlInt	getMinWidth() const     { return _minWidth; }
    inline void		setMinWidth(IlInt val)  { _minWidth = val; }
    inline IlInt	getMinHeight() const    { return _minHeight; }
    inline void		setMinHeight(IlInt val) { _minHeight = val; }

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvAttachedGraphicSet);

protected:
    IlInt		_version;
    IlInt		_minWidth;
    IlInt		_minHeight;
};

ILVGANTTMODULEINIT(ganttfrm);

#endif /* !__Ilv_Gantt_Ganttfrm_H */
