// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/sheet.h
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
// Declaration of the IlvSheet class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Sheet_H
#define __Ilv_Gadgets_Sheet_H

#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif

class IlvSheet;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSheetLFHandler : public IlvObjectLFHandler
{
public:
    IlvSheetLFHandler(IlvLookFeelHandler* lf);

    virtual void	drawFrame(const IlvSheet*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeRects(const IlvSheet*,
				     IlvRect& titleRect,
				     IlvRect& rowRect,
				     IlvRect& colRect,
				     IlvRect& matRect,
				     const IlvTransformer* t) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSheet : public IlvMatrix
{
public:

    IlvSheet(IlvDisplay*    display,
	     const IlvRect& rect,
	     IlUShort       nbcol,
	     IlUShort       nbrow,
	     IlvDim         xgrid =     IlvDefaultMatrixWidth,
	     IlvDim         ygrid =     IlvDefaultMatrixHeight,
	     IlvDim         thickness = IlvDefaultGadgetThickness,
	     IlBoolean      showVSB =   IlTrue,
	     IlBoolean      showHSB =   IlTrue,
	     IlvPalette*    palette =   0);

    IlvSheet(IlvInputFile& is, IlvPalette* palette);
    IlvSheet(const IlvSheet&);

    virtual void	drawFrame(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	drawGadgetContents(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* clip=0) const;
    virtual void	drawItem(IlvPort* dst,
				 IlUShort colno,
				 IlUShort rowno,
				 const IlvRect& itembbox,
				 const IlvRect& clip) const;
    virtual void	scrollTo(IlUShort, IlUShort);
    void		computeBBox(IlvRect& rect,
				    IlvRect& v,
				    IlvRect& h,
				    const IlvTransformer* t = 0) const;
    virtual void	itemBBox(IlUShort col,
				 IlUShort row,
				 IlvRect& bbox,
				 const IlvTransformer* t = 0) const;
    virtual void	borderBBox(IlUShort,
				   IlUShort,
				   IlvRect& bbox,
				   const IlvTransformer* t = 0) const;
    void		computeRects(IlvRect& titleRect,
				     IlvRect& fromRect,
				     IlvRect& colRect,
				     IlvRect& matRect,
				     const IlvTransformer* t) const;
    const char*		getDefaultInteractor() const;
    virtual void	computeVerticalScrollbarRect(IlvRect&,
						     const IlvTransformer*) const;
    virtual void	computeHorizontalScrollbarRect(IlvRect&,
						       const IlvTransformer*) const;
    // event handling methods
    virtual IlBoolean	handleMatrixEvent(IlvEvent&);

    virtual IlBoolean	handleResizeColumn(IlvEvent& event);

    virtual IlBoolean	handleResizeRow(IlvEvent& event);
    virtual IlBoolean	handleMatrix(IlvEvent&);

    DeclareLazyTypeInfo();

protected:
    IlBoolean		_inFirstColumn;
    IlBoolean		_inFirstRow;
    IlvPosition		_dragged;
    IlvPoint		_origin;
    IlvPoint		_previous;
    IlUShort		_clickedCol;
    IlUShort		_clickedRow;

    IlBoolean		iCallHandleResizeColumn(IlvEvent& event);
    IlBoolean		iCallHandleResizeRow(IlvEvent& event);
    IlBoolean		iCallHandleMatrix(IlvEvent& event);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHSheetInteractor : public IlvHMatrixInteractor
{
public:
    virtual IlBoolean	handleResizeColumn(IlvSheet*, IlvEvent&) = 0;
    virtual IlBoolean	handleResizeRow(IlvSheet*, IlvEvent& ) = 0;
    virtual IlBoolean	handleMatrix(IlvSheet*, IlvEvent& ) = 0;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(sheet);
#if defined(ILVMOTIFLOOK)
#include <ilviews/gadgets/motif/sheet.h>
#endif
#if defined(ILVWINDOWSLOOK)
#include <ilviews/gadgets/windows/sheet.h>
#endif
#endif /* !__Ilv_Gadgets_Sheet_H */
