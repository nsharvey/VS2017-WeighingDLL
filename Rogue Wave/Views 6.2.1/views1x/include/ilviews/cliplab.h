// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/cliplab.h
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
// Declaration of the IlvClippedLabel class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Cliplab_H
#define __Ilv1X_Cliplab_H

#include <ilviews/graphics/rectangl.h>
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvClippedLabel
: public IlvFilledRectangle {
public:
    IlvClippedLabel(IlvDisplay*    display,
		    const IlvRect& clip,
		    const char*    label,
		    IlvBoolean     fillLabel = IlvFalse,
		    IlvPalette*     palette = 0);
    IlvClippedLabel(IlvDisplay*     display,
		    const IlvPoint& p,
		    const char*     label,
		    IlvBoolean      fillLabel = IlvFalse,
		    IlvPalette*     palette = 0);
    // ____________________________________________________________
    virtual void draw(IlvPort*, const IlvTransformer* t = 0,
		      const IlvRegion* = 0) const;
    void fillLabel(IlvBoolean value) { _fillLabel = value; }
    IlvBoolean isLabelFilled() const { return _fillLabel; }
    const char* getLabel() const { return _label; }
    void setLabel(const char*);
    DeclareTypeInfo();
protected:
    char*      _label;
    IlvBoolean _fillLabel;
};

ILV1XVWSMODULEINIT(cliplab);

#endif /* !__Ilv1X_Cliplab_H */
