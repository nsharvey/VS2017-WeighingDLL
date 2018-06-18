// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/vfincl/vectlab.h
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
// Declaration of the IlvVectLabel class
// --------------------------------------------------------------------------
#ifndef __Ilv_Vectfont_Vectlab_H
#define __Ilv_Vectfont_Vectlab_H

#if !defined(__Ilv_Vectfont_Vect_H)
#include <vfincl/vect.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvVectLabel
: public IlvSimpleGraphic
{
public:
    IlvVectLabel(IlvDisplay*        display,
		 IlvVectFont*       font,
		 const IlvPoint&    position,
		 const char*        label,
		 IlvPalette*        palette=0);
    virtual ~IlvVectLabel();
    // ____________________________________________________________
    void getSizes(IlInt& sizex, IlInt& sizey) const
	{ _font->getSizes(sizex, sizey); }
    IlFloat getAngle() const { return _font->getAngle(); }
    IlFloat getSlant() const { return _font->getSlant(); }
    // ____________________________________________________________
    virtual void boundingBox(IlvRect& rect, const IlvTransformer* t = 0) const;
    virtual void applyTransform(const IlvTransformer* t);
    virtual void scale(IlFloat zoomx, IlFloat zoomy);
    virtual void translate(IlvPos dx, IlvPos dy);
    virtual IlBoolean contains(const IlvPoint& p, const IlvPoint& tp,
			       const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort*, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    // ____________________________________________________________
    const char* getLabel() const { return _label; }
    void setLabel(const char* label);
    DeclareTypeInfo();

protected:
    IlvVectFont*    _font;
    IlvRect         _bbox;
    IlvTransformer* _transformer;
#if defined (WINDOWS)
    IlvRect         _tbbox;
    IlvTransformer  _tt;
#endif /* WINDOWS */
    IlvPoint        _position;
    char*           _label;
    unsigned int    _length;
    void computeBBox();
};

#endif /* !__Ilv_Vectfont_Vectlab_H */
