// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/vlabel.h
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
// Declaration of the IlvVerticalLabel class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Vlabel_H
#define __Ilv1X_Vlabel_H

#include <math.h>
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvVerticalLabel
: public IlvLabel {
public:
    IlvVerticalLabel(IlvDisplay*     display,
		     const IlvPoint& position,
		     const char*     label,
		     IlvPalette*     palette=0);
    // ____________________________________________________________
    virtual void setLabel(const char*);
    virtual void boundingBox(IlvRect& rect,
			     const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort*, const IlvTransformer* t = 0,
		      const IlvRegion* =0) const;
    DeclareTypeInfo1();
protected:
    IlvUShort _maxWidth;
    void computeMaxWidth();
};

ILV1XVWSMODULEINIT(vlabel);

#endif /* !__Ilv1X_Vlabel_H */
