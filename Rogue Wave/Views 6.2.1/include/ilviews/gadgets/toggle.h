// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/toggle.h
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
// Declaration of the IlvToggle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Toggle_H
#define __Ilv_Gadgets_Toggle_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif

class IlvToggle;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvToggleLFHandler : public IlvObjectLFHandler
{
public:
    IlvToggleLFHandler(IlvLookFeelHandler* lfh);

    virtual IlUShort	getCheckSize() const = 0;
    virtual IlUShort	getXMargin() const = 0;
    virtual void	setMode(IlvToggle*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvToggle*, IlBoolean) const = 0;
    virtual void	drawBackground(const IlvToggle* toggle,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvToggle* toggle,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvToggle* toggle,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;

    virtual void	drawCheckBox(const IlvToggle* toggle,
				     IlvPort* dst,
				     const IlvRect& rect,
				     const IlvRegion* clip) const = 0;
    virtual void	drawText(const IlvToggle* toggle,
				 IlvPort* dst,
				 const IlvRect& rect,
				 const IlvRegion* clip) const = 0;
    virtual void	drawFocus(const IlvToggle*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeFocusRegion(const IlvToggle*,
					   IlvRegion& region,
					   const IlvTransformer* t) const = 0;
    virtual void	computeHighlightRegion(const IlvToggle*,
					       IlvRegion& region,
					       const IlvTransformer*)const = 0;
    virtual IlBoolean	handleEvent(IlvToggle* toggle,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultToggleLFHandler : public IlvToggleLFHandler
{
public:
    IlvDefaultToggleLFHandler(IlvLookFeelHandler* lf)
	: IlvToggleLFHandler(lf) {}

    virtual void	setMode(IlvToggle*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvToggle*, IlBoolean) const;
    virtual void	drawBackground(const IlvToggle*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvToggle*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvToggle : public IlvGadget
{
public:

    IlvToggle(IlvDisplay*    display,
	      const char*    label,
	      const IlvRect& rect,
	      IlUShort       thickness = IlvDefaultGadgetThickness,
	      IlvPalette*    palette   = 0);

    IlvToggle(IlvDisplay*     display,
	      const IlvPoint& point,
	      const char*     label,
	      IlUShort        thickness = IlvDefaultGadgetThickness,
	      IlvPalette*     palette   = 0);

    IlvToggle(IlvDisplay*    display,
	      IlvBitmap*     bitmap,
	      const IlvRect& rect,
	      IlUShort       thickness = IlvDefaultGadgetThickness,
	      IlvPalette*    palette   = 0);

    IlvToggle(IlvDisplay*     display,
	      const IlvPoint& point,
	      IlvBitmap*      bitmap,
	      IlUShort        thickness = IlvDefaultGadgetThickness,
	      IlvPalette*     palette   = 0);

    virtual ~IlvToggle();
    // ____________________________________________________________
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawContents(IlvPort* dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion* clip = 0) const;
    virtual IlvPalette*	getCheckPalette() const;
    virtual void	drawCheckBox(IlvPort* dst,
				     const IlvRect& rect,
				     const IlvRegion* clip = 0) const;
    virtual void	drawText(IlvPort* dst,
				 const IlvRect& rect,
				 const IlvRegion* clip = 0) const;
    virtual void	drawFrame(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	drawFocus(IlvPort* dst,
				  const IlvPalette* palette,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer* t=0)const;
    virtual void	applyTransform(const IlvTransformer* t);

    inline IlvBitmap*	getBitmap() const { return _bitmap; }

    void		setBitmap(IlvBitmap* bitmap);

    virtual void	setFont(IlvFont*);
    virtual void	setPalette(IlvPalette*);
    void		setMode(IlvDrawMode mode);
    void		setOverwrite(IlBoolean mode);

    inline const char*	getLabel() const { return _label; }

    void		setLabel(const char* label);

    inline IlvPosition	getPosition() const { return _position; }

    inline void		setPosition(IlvPosition position)
			{
			    _position = position;
			}

    inline IlvPosition	getTextAlignment() const { return _textAlignment; }

    inline void		setTextAlignment(IlvPosition alignment)
			{
			    _textAlignment=alignment;
			}

    inline IlBoolean	isRadio() const { return _radioLook; }
    inline IlBoolean	isUsingDiamond() const { return isRadio(); }

    inline void		setRadio(IlBoolean value)
			{
			    _radioLook = value;
			    if (value)
				setIndeterminateMode(IlFalse);
			}
    inline void		useDiamond(IlBoolean v) // 2.0.2 Compatibility
			{
			    setRadio(v);
			} 
    IlvDim		getCheckSize(IlBoolean value = IlFalse) const;

    void		setCheckSize(IlvDim size);

    IlBoolean		getState() const;

    void		setState(IlBoolean value);

    IlBoolean		isIndeterminateState() const;

    void		setIndeterminateState(IlBoolean value);

    IlBoolean		isIndeterminateMode() const;

    void		setIndeterminateMode(IlBoolean value);

    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual IlBoolean	handleAccelerator(IlvEvent&) const;

    virtual void	activate();

    virtual const char*	getDefaultInteractor() const;
    char		getMnemonic() const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvToggle);

protected:
    char*		_label;
    IlvBitmap*		_bitmap;
    IlvPosition		_position;
    IlBoolean		_radioLook;
    IlvDim		_checkSize;
    IlvPosition		_textAlignment;

    virtual IlBoolean	classFocusable() const;

public:
    DeclareGraphicAccessors();

    static IlSymbol*	_labelValue;
    static IlSymbol*	_bitmapValue;
    static IlSymbol*	_positionValue;
    static IlSymbol*	_radioValue;
    static IlSymbol*	_checkSizeValue;
    static IlSymbol*	_alignmentValue;
    static IlSymbol*	_stateValue;
    static IlSymbol*	_indeterminateValue;
    static IlSymbol*	_indeterminateModeValue;

    void		nextState();
    void		previousState();
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(toggle);
#if defined(ILVMOTIFLOOK)
#include <ilviews/gadgets/motif/toggle.h>
#endif
#if defined(ILVWINDOWSLOOK)
#include <ilviews/gadgets/windows/toggle.h>
#endif
#if defined(ILVWINDOWS95LOOK)
#include <ilviews/gadgets/win95/toggle.h>
#endif
#if defined(ILVWINDOWSXPLOOK)
#include <ilviews/gadgets/winxp/toggle.h>
#endif
#if defined(ILVVXLOOK)
#include <ilviews/gadgets/vx/toggle.h>
#endif
#endif /* !__Ilv_Gadgets_Toggle_H */
