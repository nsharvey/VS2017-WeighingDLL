// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/ctoggle.h
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
// Declaration of the IlvColoredToggle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Ctoggle_H
#define __Ilv_Gadgets_Ctoggle_H

#if !defined(__Ilv_Gadgets_Toggle_H)
#  include <ilviews/gadgets/toggle.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvColoredToggle
    : public IlvToggle
{
public:

    IlvColoredToggle(IlvDisplay*    display,
		     const char*    label,
		     const IlvRect& rect,
		     IlUShort       thickness = IlvDefaultGadgetThickness,
		     IlvPalette*    palette   = 0)
	: IlvToggle(display, label, rect, thickness, palette),
	  _checkPalette(0)
    {
	computeCheckPalette();
    }

    IlvColoredToggle(IlvDisplay*     display,
		     const IlvPoint& point,
		     const char*     label,
		     IlUShort        thickness = IlvDefaultGadgetThickness,
		     IlvPalette*     palette   = 0)
	: IlvToggle(display, point, label, thickness, palette),
	  _checkPalette(0)
    {
	computeCheckPalette();
    }

    IlvColoredToggle(IlvDisplay*    display,
		     IlvBitmap*     bitmap,
		     const IlvRect& rect,
		     IlUShort       thickness = IlvDefaultGadgetThickness,
		     IlvPalette*    palette   = 0)
	: IlvToggle(display, bitmap, rect, thickness, palette),
	  _checkPalette(0)
    {
	computeCheckPalette();
    }

    IlvColoredToggle(IlvDisplay*     display,
		     const IlvPoint& point,
		     IlvBitmap*      bitmap,
		     IlUShort        thickness = IlvDefaultGadgetThickness,
		     IlvPalette*     palette   = 0)
	: IlvToggle(display, point, bitmap, thickness, palette),
	  _checkPalette(0)
    {
	computeCheckPalette();
    }
    virtual ~IlvColoredToggle();

    virtual void	drawContents(IlvPort*,
				     const IlvTransformer* = 0,
				     const IlvRegion* = 0) const;

    inline IlvColor*	getCheckColor() const
	{ return _checkPalette->getForeground(); }
    void		setCheckColor(IlvColor* color);
    virtual IlvPalette*	getCheckPalette() const;

    static IlSymbol*	_checkColorValue;

    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvColoredToggle);

protected:
    void		computeCheckPalette(IlvColor* = 0);
    IlvPalette*		_checkPalette;
};

ILVGDTMODULEINIT(ctoggle);
#endif /* !__Ilv_Gadgets_Ctoggle_H */
