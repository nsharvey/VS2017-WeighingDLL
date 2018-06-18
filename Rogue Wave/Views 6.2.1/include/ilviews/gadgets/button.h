// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/button.h
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
// Declaration of the IlvButton class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Button_H
#define __Ilv_Gadgets_Button_H

#if !defined(__Ilv_Gadgets_Msglabel_H)
#  include <ilviews/gadgets/msglabel.h>
#endif

class IlvButton;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvButtonLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvButtonLFHandler(IlvLookFeelHandler* lfh);

    virtual void	setMode(IlvButton*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvButton*, IlBoolean) const = 0;
    virtual void	draw(const IlvButton*,
			     IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const = 0;
    virtual void	drawGadgetItem(const IlvButton*	     button,
				       const IlvGadgetItem*  item,
				       IlvPort*		     dst,
				       const IlvRect&	     rect,
				       const IlvTransformer* t,
				       const IlvRegion*	     clip) const = 0;
    virtual void	drawContents(const IlvButton*	   button,
				     IlvPort*		   dst,
				     const IlvTransformer* t,
				     const IlvRegion*	   clip) const = 0;
    virtual void	drawBackground(const IlvButton*	     button,
				       IlvPort*		     dst,
				       const IlvTransformer* t,
				       const IlvRegion*	     clip) const = 0;
    virtual void	drawFrame(const IlvButton*	button,
				  IlvPort*		dst,
				  const IlvTransformer* t,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawFocus(const IlvButton*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeFocusRegion(const IlvButton*,
					   IlvRegion&,
					   const IlvTransformer*) const = 0;
    virtual void	invert(const IlvButton*, IlBoolean) const = 0;
    virtual void	drawButtonAsDefault(const IlvButton*	  button,
					    IlvPort*		  dst,
					    const IlvTransformer* t,
					    const IlvRegion* clip) const = 0;
    virtual void computeDefaultButtonRegion(const IlvButton*	button,
					    IlvRegion&		region,
					    const IlvTransformer* t) const=0;
    virtual void	getPreferredSize(const IlvButton*,
					 IlvDim&,
					 IlvDim&) const = 0;
    virtual IlBoolean	handleEvent(IlvButton* button,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultButtonLFHandler
    : public IlvButtonLFHandler
{
public:
    IlvDefaultButtonLFHandler(IlvLookFeelHandler* lf)
	: IlvButtonLFHandler(lf)
    {}

    virtual void	draw(const IlvButton*,
			     IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const;
    virtual void	drawGadgetItem(const IlvButton*,
				       const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	getPreferredSize(const IlvButton*,
					 IlvDim&,
					 IlvDim&) const;
    virtual void	invert(const IlvButton*, IlBoolean) const;
    virtual IlBoolean	handleEvent(IlvButton*, IlvEvent&) const;
    virtual void	setMode(IlvButton*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvButton*, IlBoolean) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvButton
    : public IlvMessageLabel
{
    friend class IlvDefaultButtonLFHandler;
public:
    IlvButton(IlvDisplay*    display,
	      const char*    label,
	      const IlvRect& rect,
	      IlUShort       thickness = IlvDefaultGadgetThickness,
	      IlvPalette*    palette   = 0);
    IlvButton(IlvDisplay*     display,
	      const IlvPoint& point,
	      const char*     label,
	      IlUShort        thickness = IlvDefaultGadgetThickness,
	      IlvPalette*     palette   = 0);
    IlvButton(IlvDisplay*     display,
	      IlvBitmap*      bitmap,
	      const IlvRect&  rect,
	      IlUShort        thickness = IlvDefaultGadgetThickness,
	      IlvPalette*     palette   = 0);
    IlvButton(IlvDisplay*     display,
	      const IlvPoint& point,
	      IlvBitmap*      bitmap,
	      IlUShort        thickness = IlvDefaultGadgetThickness,
	      IlvPalette*     palette   = 0);
    ~IlvButton();

    IlvBitmap*		getHighlightedBitmap() const;
    IlvBitmap*		getSelectedBitmap() const;
    void		setHighlightedBitmap(IlvBitmap* bitmap);
    void		setSelectedBitmap(IlvBitmap* bitmap);
    IlBoolean		isRepeat() const;
    void		setRepeat(IlBoolean value);
    inline IlUInt	getPeriod() const { return _period; }
    inline void		setPeriod(IlUInt period) { _period = period; }
    virtual void	activate();

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvButton);

protected:
    IlBoolean		_isDefault;
    IlUInt		_period;
    IlvTimer*		_autoRepeatTimer;

    inline IlvTimer*	getAutoRepeatTimer() const { return _autoRepeatTimer; }
    virtual IlBoolean	classFocusable() const;
    IlBoolean		iHandleEvent(IlvEvent&);

public:
    DeclareGraphicAccessors();
    static IlSymbol*	_autoRepeatValue;
    static IlSymbol*	_autoRepeatPeriodValue;

    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	setSensitive(IlBoolean);
    virtual const char*	getDefaultInteractor() const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion*      = 0) const;
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer* = 0,
				       const IlvRegion*      = 0) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer* = 0,
				     const IlvRegion*      = 0) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer* = 0,
				       const IlvRegion*      = 0) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer* = 0,
				  const IlvRegion*      = 0) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion*      = 0) const;
    virtual void	drawButtonAsDefault(IlvPort*,
					    const IlvTransformer*,
					    const IlvRegion*) const;
    virtual void     computeDefaultButtonRegion(IlvRegion&,
						const IlvTransformer*) const;
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	invert(IlBoolean = IlFalse);
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* = 0) const;
    inline void		setDefault(IlBoolean set) { _isDefault = set;  }
    inline IlBoolean	getDefault() const { return _isDefault; }
    virtual IlUInt	getBitmapMask() const;
    virtual void	setHighlight(IlBoolean);
    virtual void	getPreferredSize(IlvDim&, IlvDim&) const;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(button);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/button.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/button.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/button.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/button.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/button.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Button_H */
