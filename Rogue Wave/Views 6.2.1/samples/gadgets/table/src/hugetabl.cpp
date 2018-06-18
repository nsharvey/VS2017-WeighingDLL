// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/src/hugetabl.cpp
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
// Demonstrates a logical scroll on 100000 rows.
// SIZE is the number of rows of the data array
// ALLOCATEDSIZE is the number of actual rows in the matrix
// the bigger it is, the best results you'll get, but it must be an IlvUShort
// --------------------------------------------------------------------------

#include <ilviews/graphics/io.h>
#include <ilviews/gadgets/amatrix.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/base/memory.h>

#include <hugetabl.h>

#if defined(IL_STD)
IL_STDUSE
#include <cstring>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdlib>
#else  /* !IL_STD */
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <iostream.h>
#include <stdlib.h>
#endif /* IL_STD */

// Real size of the data array
#define SIZE 100000
static char** elements;

// Actual allocated size
#define ALLOCATEDSIZE 400

// --------------------------------------------------------------------------
class IlvHugeMatrix : public IlvAbstractMatrix
{
public:
    IlvHugeMatrix(IlvDisplay*    display,
		  const IlvRect& rect,
		  IlUShort       thickness = IlvDefaultGadgetThickness,
		  IlvPalette*    palette   = 0)
        : IlvAbstractMatrix(display, rect, thickness, palette),
	  _firstvisible(0)
    {}
    // ____________________________________________________________
    virtual IlUShort	rows()  const   { return ALLOCATEDSIZE; }
    virtual IlUShort	columns() const { return 1; }
    virtual IlvDim	getRowHeight(IlUShort) const { return 40;}
    virtual IlvDim	getColumnWidth(IlUShort) const { return 100;}
    virtual IlBoolean	rowSameHeight() const   { return IlTrue; }
    virtual IlBoolean	columnSameWidth() const { return IlTrue; }

    virtual void	adjustFromScrollBar(const IlvScrollBar* sb,
					    IlvDirection dir)
    {
	if (dir == IlvHorizontal) {
	    IlvAbstractMatrix::adjustFromScrollBar(sb, dir);
	} else {
	    IlUShort fromcol, tocol, fromrow, torow, nbvisible;
	    IlInt realrow = (IlvDim)(sb->getValue() / getRowHeight(0));
	    getVisibleItems(fromcol, tocol, fromrow, torow);
	    if (realrow == (IlInt)(fromrow + (IlUShort)getFirstVisible()))
		return;
	    nbvisible = torow - fromrow +1;
	    if ((realrow >= (IlInt)getFirstVisible()) &&
		(realrow < (IlInt)(getFirstVisible() + rows() - nbvisible)))
		scrollToRow((IlUShort) (realrow - getFirstVisible()));
	    else {
		if (realrow + rows() > SIZE) {
		    setFirstVisible(SIZE - rows());
		    setFirstRow((IlUShort)(realrow - (SIZE - rows())));
		} else {
		    setFirstVisible(realrow);
		    setFirstRow(0);
		}
		reDraw();
	    }
	}
    }
    virtual void	adjustScrollBarValue(IlvScrollBar* sb,
					     IlvDirection dir)
    {
	if (dir == IlvVertical) {
	    IlUShort fromcol, tocol, fromrow, torow;
	    getVisibleItems(fromcol, tocol, fromrow, torow);
	    IlvDim rowPos = (_firstvisible + fromrow) * getRowHeight(0);
	    sb->setValue(rowPos);
	    IlvRect vbox;
	    visibleBBox(vbox, getTransformer());
	    sb->setPageIncrement(vbox.h() + 1);
	    sb->setIncrement(getRowHeight(0));
	    sb->setDecrement(getRowHeight(0));
	}
	else IlvAbstractMatrix::adjustScrollBarValue(sb, dir);
    }
    virtual void	scrollableSize(IlvDim& w, IlvDim& h) const
    {
	IlvAbstractMatrix::scrollableSize(w, h);
	h = SIZE * getRowHeight(0);
    }
    virtual void	limitScrollingValues(IlvDim& w, IlvDim& h) const
    {
	IlvAbstractMatrix::limitScrollingValues(w, h);
	h = (SIZE - 1) * getRowHeight(0);
    }
    virtual void	drawItem(IlvPort* dst,
				 IlUShort colno,
				 IlUShort rowno,
				 const IlvRect& bbox,
				 const IlvRect& clip) const
    {
	IlvRect rect = bbox;
	rect.expand(-1, -1);
	IlvRect clipRect(clip);
	clipRect.intersection(rect);
	IlvRegion clipRegion(clipRect);
	dst->drawLabel(getPalette(),
		       elements[rowno + _firstvisible],
		       -1,
		       rect,
		       &clipRegion);
    }

    void		setFirstRow(IlUShort row) { _firstRow = row; }
    IlUInt		getFirstVisible() const   { return _firstvisible; }
    void		setFirstVisible(IlUInt v) {  _firstvisible = v; }

private:
    IlUInt		_firstvisible;
};

// --------------------------------------------------------------------------
// Panel class for sample Huge
// --------------------------------------------------------------------------
void
Huge::initHuge()
{
    IlvDisplay* display = getDisplay();

    // Create the data array
    elements = (char**)IlvMalloc(sizeof(char*) * SIZE);
    for (IlUInt i = 0; i < SIZE; ++i) {
	elements[i] = new char[16];
	sprintf(elements[i], "no %ld", (long int) i);
    }

    IlvHugeMatrix* mat =
	new IlvHugeMatrix(display, IlvRect(15, 30, 190, 570));
    IlvFont* font = display->getFont("%helvetica-14");
    if (font)
	mat->setFont(font);
    mat->showGrid(IlTrue);
    mat->showScrollBar(IlvVertical);
    addObject(mat);
    IlvSetAttachment(mat, IlvVertical,   IlvElasticAttach);
    IlvSetAttachment(mat, IlvHorizontal, IlvElasticAttach);
    IlvSetAttachment(mat, IlvTop,        IlvFixedAttach, 30);
    IlvSetAttachment(mat, IlvBottom,     IlvFixedAttach, 15);
    IlvSetAttachment(mat, IlvRight,      IlvFixedAttach, 15);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void
DefinePageHuge(Pan* mainPanel)
{
    Huge* panel = new Huge(mainPanel,"huge.ilv");
    mainPanel->addPageNoteBook(panel, "Huge", "huge.txt");
}
