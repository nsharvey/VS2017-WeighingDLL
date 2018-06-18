// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/arrowb.h
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
// Definition of the IlvArrowButton class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Arrowb_H
#define __Ilv_Gadgets_Arrowb_H

#if !defined(__Ilv_Gadgets_Button_H)
#  include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

class IlvArrowButton;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvArrowButtonLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvArrowButtonLFHandler(IlvLookFeelHandler* lf);

    virtual void	drawFrame(const IlvArrowButton*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	drawContents(const IlvArrowButton*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvArrowButton
    : public IlvButton
{
public:
    IlvArrowButton(IlvDisplay*		display,
		   const IlvRect&	rect,
		   IlvDirection		direction,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0)
	: IlvButton(display, (const char*)0, rect, thickness, palette),
	  _direction(direction),
	  _spinMode(IlFalse)
    {}
    IlvArrowButton(IlvDisplay*		display,
		   const IlvPoint&	at,
		   IlvDirection		direction,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0)
	: IlvButton(display, at, (const char*)0, thickness, palette),
	  _direction(direction),
	  _spinMode(IlFalse)
    {}

    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    void		invert(IlBoolean = IlFalse);

    inline
    IlvOrientation	getDirection() const { return _direction;}

    inline void		setDirection(IlvOrientation direction,
				     IlBoolean      redraw = IlFalse)
			{
			    _direction = direction;
			    if (redraw) {
				reDraw();
			    }
			}

    inline IlBoolean	isSpinMode() const { return _spinMode;}
    inline void		setSpinMode(IlBoolean mode, IlBoolean redraw = IlFalse)
			{
			    _spinMode = mode;
			    if (redraw) {
				reDraw();
			    }
			}

    DeclareGraphicAccessors();
    static IlSymbol*	_directionValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvArrowButton);

protected:
    IlvOrientation	_direction;
    IlBoolean		_spinMode;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(arrowb);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/arrowb.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/arrowb.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/arrowb.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/arrowb.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /*__Ilv_Arrowb_H */
