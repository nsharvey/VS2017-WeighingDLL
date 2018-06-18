// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/src/matrix.cpp
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
// Definition of a IlvSampleMatrix subclass.
// Sub class of IlvAstractMatrix, the IlvSampleMatrix is a matrix
// with two column, and the number of rows is not limited.
// Each row shows the number of the row
// an icon is drawn on the second column every 10 item.
// --------------------------------------------------------------------------

#ifdef IL_STD
#include <cstdio>
#include <cmath>
#include <cstring>
#else
#include <stdio.h>
#include <math.h>
#include <string.h>
#endif

#include <ilviews/graphics/io.h>
#include <ilviews/gadgets/amatrix.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/bitmaps/png.h>

IL_STDUSE

#include <matrix.h>

// --------------------------------------------------------------------------
class IlvSampleMatrix : public IlvAbstractMatrix
{
public:
    IlvSampleMatrix(IlvDisplay*        display,
                    const IlvRect&     rect,
                    IlUShort           thickness = IlvDefaultGadgetThickness,
                    IlvPalette*        palette   = 0)
        : IlvAbstractMatrix(display, rect, thickness, palette),
	  _rowCount(400),
	  _bitmap(0)
    {
	setNbFixedRow(1); // The first row is fixed
	_bitmap = display->getBitmap("logo.png");
	if (!_bitmap)
	    _bitmap = display->readBitmap("logo.png");
	if (_bitmap)
	    _bitmap->lock();
    }
    ~IlvSampleMatrix()
    {
	if (_bitmap)
	    _bitmap->unLock();
    }
    // ____________________________________________________________
    // -- properties
    virtual IlUShort	rows ()  const   { return _rowCount; }
    virtual IlUShort	columns () const { return 2; }
    virtual IlvDim	getRowHeight (IlUShort) const { return 50;}
    virtual IlvDim	getColumnWidth (IlUShort) const { return 100;}
    virtual IlBoolean	rowSameHeight() const   { return IlTrue; }
    virtual IlBoolean	columnSameWidth() const { return IlTrue; }

    virtual void	scrollTo(IlUShort colno, IlUShort rowno)
    {
	IlUShort fromcol, tocol, fromrow, torow;
	IlvAbstractMatrix::scrollTo(colno, rowno);
	getVisibleItems(fromcol, tocol, fromrow, torow);
	if (torow >= IlUShort(_rowCount - 10)) {
	    //when scrolling too far, increment the number of row
	    _rowCount += 10;
	    adjustScrollBars();
	    reDraw();
	}
    }

    virtual void	drawItem(IlvPort* dst,
				 IlUShort colno,
				 IlUShort rowno,
				 const IlvRect& bbox,
				 const IlvRect& clip) const
    {
	IlvRect rect = bbox;
	char buffer[16];
	if (rowno)
	    sprintf(buffer, "%d", rowno);
	rect.expand(-1, -1);
	IlvRect clipRect(clip);
	clipRect.intersection(rect);
	IlvRegion clipRegion(clipRect);
	switch (colno) {
	case 0: {
	    dst->drawLabel(getPalette(),
			   rowno ? buffer : "Numbers",
			   -1,
			   rect,
			   &clipRegion);
	    break;
	}
	case 1: {
	    // draw ilog icon every 10
	  if (_bitmap && (rowno != 0) && !(rowno % 10)) {
		dst->drawBitmap(getPalette(),
				_bitmap,
				bbox,
				&clipRegion,
				IlvLeft,
				IlTrue);
	    }
	}
	}
    }
    
    // no IO
private:
    IlUShort		_rowCount;
    IlvBitmap*		_bitmap;
};

// --------------------------------------------------------------------------
// Panel class for sample Matrix
// --------------------------------------------------------------------------
void
Matrix::initMatrix()
{
    IlvDisplay* display = getDisplay();
    IlvSampleMatrix* mat =
	new IlvSampleMatrix(display, IlvRect(15, 30, 230, 570));
    IlvFont* font = display->getFont("Helvetica", 14, IlvNormalFontStyle, "*");
    if (font)
	mat->setFont(font);
    mat->showGrid(IlTrue);
    mat->showScrollBar(IlvVertical);
    addObject(mat);
    IlvSetAttachment(mat, IlvVertical,	IlvElasticAttach,	 0);
    IlvSetAttachment(mat, IlvHorizontal,IlvElasticAttach,	 0);
    IlvSetAttachment(mat, IlvTop,	IlvFixedAttach,		30);
    IlvSetAttachment(mat, IlvBottom,	IlvFixedAttach,		15);
    IlvSetAttachment(mat, IlvRight,	IlvFixedAttach,		15);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageMatrix(Pan* mainPanel)
{
    Matrix* panel = new Matrix(mainPanel,"huge.ilv");
    mainPanel->addPageNoteBook(panel, "Matrix", "matrix.txt");
}
