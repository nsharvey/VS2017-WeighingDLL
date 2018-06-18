// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/cellgr.h
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
// Declaration of the IlvGraphicCell class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Cellgr_H
#define __Ilv31_Cellgr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv31_Cell_H)
#include <ilviews/cell.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvGraphicCell
: public IlvCell {
public:
    IlvGraphicCell(IlvDisplay*, IlvGraphic* graphic,
		   const char* s, IlvPalette* pal = 0);
    IlvGraphicCell(IlvDisplay*, IlvGraphic* graphic, IlvPalette* pal = 0);
    virtual ~IlvGraphicCell();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual void write(IL_STDPREF ostream&) const;
    void setGraphic(IlvGraphic* g, IlBoolean deleteIt = IlTrue);
    IlvGraphic* getGraphic()  const { return _graphic; }
    virtual void draw(IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect = 0) const;
    virtual void getFittingSizes(IlvDim& width, IlvDim& height) const;
    virtual void setPalette(IlvPalette*);
    virtual void setBackground(IlvColor*);
    virtual void setForeground(IlvColor*);
    virtual void setPattern(IlvPattern*);
    virtual void setFont(IlvFont*);
    virtual void invert();
    virtual void setFillStyle(IlvFillStyle);
    virtual void setMode(IlvDrawMode mode);
protected:
    IlvGraphic* _graphic;
};

ILV31VWSMODULEINIT(cellgr);
#endif /* !__Ilv31_Cellgr_H */
