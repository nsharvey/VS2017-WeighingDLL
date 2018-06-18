// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/pyrrect.h
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
// Declaration of the IlvPyramidRectangle class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Pyrrect_H
#define __Ilv1X_Pyrrect_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvPyramidRectangle
: public IlvSimpleGraphic {
public:
    IlvPyramidRectangle(IlvDisplay*     display,
			const IlvRect&  rect,
			const IlvPoint& point,
			IlvPalette*     palette=0);
    ~IlvPyramidRectangle();
    // ____________________________________________________________
    virtual IlvBoolean contains(const IlvPoint& p,
			       const IlvPoint& tp, const IlvTransformer* t=0) const;
    virtual void symmetry(IlvDirection);
    virtual void draw(IlvPort* dst, const IlvTransformer* t=0,
		      const IlvRegion*  =0) const;
    virtual void boundingBox(IlvRect& rect, const IlvTransformer* t=0)const;
    virtual void setForeground(IlvColor*);
    virtual void setBackground(IlvColor*);
    virtual void setFont(IlvFont*);
    virtual void setMode(IlvDrawMode);
    virtual void setOverwrite(IlvBoolean);
    void applyTransform(const IlvTransformer* t);
    DeclareTypeInfo();
    const IlvPoint& getPoint() const               { return _point;  }
    void            setPoint(const IlvPoint& point) { _point = point; }
#if !defined(sgi)
    const
#endif
          IlvRect getRectangle() const        { return _rect;  }
    void          setRect(const IlvRect& rect) { _rect  = rect; }
protected:
    IlvRect      _rect;
    IlvPoint     _point;
    IlvPalette*  _edgespalette;
    IlvPalette*  _rectpalette;
    void internalDraw(IlvPort* dst, const IlvRegion* rect,
		      const IlvRect&, const IlvPoint&) const;
    void computePalettes();
private:
    IlvPosition locatePoint(const IlvRect&, const IlvPoint&)const;
    int  createPolygon(const IlvRect&, const IlvPoint&)const;
};

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvPyramidLabel
: public IlvPyramidRectangle {
public:
    IlvPyramidLabel(IlvDisplay*     display,
		    const char*     label,
		    const IlvRect&  rect,
		    const IlvPoint& point,
		    IlvPalette*     palette=0);
    ~IlvPyramidLabel() { delete _label; }
    // ____________________________________________________________
    virtual void draw(IlvPort* dst, const IlvTransformer* t=0,const IlvRegion*  =0)const;
    const char* getLabel() const   { return _label; }
    void setLabel(const char* label);
    DeclareTypeInfo();
protected:
    char* _label;
};

ILV1XVWSMODULEINIT(pyrrect);

#endif /* !__Ilv1X_Pyrrect_H */
