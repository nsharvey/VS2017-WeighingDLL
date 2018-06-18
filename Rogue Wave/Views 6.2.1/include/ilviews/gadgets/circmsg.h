// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/circmsg.h
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
// Declaration of the IlvCircularMessageLabel class
// --------------------------------------------------------------------------

#ifndef _Ilv_Circmsg_H
#define _Ilv_Circmsg_H

#if !defined(__Ilv_Gadgets_Msglabel_H)
#include <ilviews/gadgets/msglabel.h>
#endif
#if !defined(__Ilv_Graphics_Outpoly_H)
#include <ilviews/graphics/outpoly.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvCircularMessageLabel
    : public IlvMessageLabel
{
public:
    IlvCircularMessageLabel(IlvDisplay*     display,
			    const char*     messageName,
			    IlvBitmap*      b,
			    const IlvPoint& center,
			    IlvPosition     textPosition = IlvTop,
			    IlvDim          radiusIn     = 50,
			    IlvDim          radiusOut    = 150,
			    IlFloat         startAngle   = 0,
			    IlFloat         angleRange   = 90,
			    IlUInt          segments     = 5,
			    IlvAlignment    align        = IlvCenter,
			    IlUShort        thickness    = 0,
			    IlvPalette*     palette      = 0,
			    IlBoolean       copy         = IlTrue);
    ~IlvCircularMessageLabel();

    virtual void draw(IlvPort*              dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion*      clip = 0) const;
    virtual void setBackground(IlvColor* background);
    virtual void setPalette(IlvPalette* palette);
    virtual void boundingBox(IlvRect& bbox,
			     const IlvTransformer* t = 0) const;
    virtual void translate(IlvPos dx,
			   IlvPos dy);

protected:
    IlvPolygon*	_polygon;
};

#endif

