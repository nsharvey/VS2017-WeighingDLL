// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/spinbox.h
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
// Declaration of the IlvSpinBox class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Spinbox_H
#define __Ilv_Gadgets_Spinbox_H

#ifndef __Ilv_Base_Gadget_H
#  include <ilviews/base/gadget.h>
#endif
#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif
#ifndef __Ilv_Gadgets_Numfield_H
#  include <ilviews/gadgets/numfield.h>
#endif
#ifndef __Ilv_Gadgets_Arrowb_H
#  include <ilviews/gadgets/arrowb.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

class IlvSpinBox;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSpinBoxLFHandler
: public IlvObjectLFHandler
{
public:
    IlvSpinBoxLFHandler(IlvLookFeelHandler* lfh);
    // ____________________________________________________________
    virtual void	drawArrow(const IlvSpinBox* spin, 
				  const IlvArrowButton* arrow,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawBackground(const IlvSpinBox* spin,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvSpinBox* spin,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvSpinBox* spin,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawFocus(const IlvSpinBox*,
				  IlvPort*              dst,
				  const IlvPalette*     palette,
				  const IlvTransformer* t,
				  const IlvRegion*      clip) const = 0;
    virtual void	computeFocusRegion(const IlvSpinBox*,
					   IlvRegion&,
					   const IlvTransformer* t) const = 0;
    virtual IlvDim	getArrowSpacing(const IlvSpinBox* spin) const = 0;
    virtual IlvDim	getFieldSpacing() const = 0;
    virtual IlvDim	getArrowWidth(const IlvSpinBox* spin) const = 0;
    virtual IlBoolean	propagateColors() const = 0;
    virtual void	computeArrowRects(const IlvSpinBox* spin,
					  IlvRect& decrArrow,
					  IlvRect& incrArrow,
					  IlvRect& internal,
					  const IlvTransformer* t) const = 0;
    virtual void	getPreferredSize(const IlvSpinBox*,
					 IlvDim&,
					 IlvDim&) const = 0;
    virtual IlBoolean	handleEvent(IlvSpinBox* spin,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultSpinBoxLFHandler
: public IlvSpinBoxLFHandler
{
public:
    IlvDefaultSpinBoxLFHandler(IlvLookFeelHandler* lf)
    : IlvSpinBoxLFHandler(lf)
    {}

    virtual void	drawBackground(const IlvSpinBox*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawContents(const IlvSpinBox*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	getPreferredSize(const IlvSpinBox*,
					 IlvDim&,
					 IlvDim&) const;
    virtual IlBoolean	handleEvent(IlvSpinBox*, IlvEvent&) const;
    virtual void	drawFocus(const IlvSpinBox*,
				  IlvPort*              dst,
				  const IlvPalette*     palette,
				  const IlvTransformer* t,
				  const IlvRegion*      clip) const;
    virtual void	computeFocusRegion(const IlvSpinBox*,
					   IlvRegion&,
					   const IlvTransformer* t) const;
    virtual void	drawArrow(const IlvSpinBox*,
				  const IlvArrowButton*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSpinBox
: public IlvGadget
{
    friend class IlvDefaultSpinBoxLFHandler;
public:

    IlvSpinBox(IlvDisplay*	display,
	       const IlvRect&	rect,
	       IlvOrientation	arrowOrientation = IlvVertical,
	       IlUShort		thickness        = IlvDefaultGadgetThickness,
	       IlvPalette*	palette          = 0);

    IlvSpinBox(IlvDisplay*	display,
	       const IlvPoint&	point,
	       IlvOrientation	arrowOrientation = IlvVertical,
	       IlUShort		thickness        = IlvDefaultGadgetThickness,
	       IlvPalette*	palette          = 0);

    virtual ~IlvSpinBox();

    virtual void	getPreferredSize(IlvDim&, IlvDim&) const;

    void		addField(IlvTextField*	field,
				 const char**	values,
				 IlUShort	count,
				 IlUShort	pos,
				 IlBoolean	loop,
				 IlUShort	at     = 0,
				 IlBoolean	redraw = IlFalse);
    void		addField(IlvNumberField*	field,
				 IlDouble		value,
				 IlDouble		increment,
				 IlBoolean		loop,
				 IlUShort		at     = 0,
				 IlBoolean		redraw = IlFalse);
    IlBoolean		isField(IlvGraphic* object) const;

    void		addObject(IlvGraphic*	object,
				  IlUShort	at = 0,
				  IlBoolean	redraw = IlFalse);
    void		removeObject(IlvGraphic* object,
				     IlBoolean redraw = IlFalse);
    inline IlUShort	objectCount() const
	{ return (IlUShort)_list.getLength(); }
    IlvGraphic*		getObject(IlUShort index) const;
    IlUShort		getObjectPosition(IlvGraphic* object) const;

    IlBoolean		isLoop(IlvTextField* field) const;
    void		setLoop(IlvTextField* field, IlBoolean loop);

    // numeric field
    IlDouble		getIncrement(IlvNumberField* field) const;
    void		setIncrement(IlvNumberField* field, IlDouble value);
    IlDouble		getValue(IlvNumberField* field,
				 IlBoolean& error) const;
    IlBoolean		setValue(IlvNumberField* field,
				 IlDouble value,
				 IlBoolean redraw = IlFalse);

    // strings field
    void		setLabel(IlvTextField* field,
				 const char* label,
				 IlBoolean  redraw = IlFalse);
    void		setLabel(IlvTextField* field,
				 IlUShort index,
				 IlBoolean redraw = IlFalse);
    const char*		getLabel(IlvTextField* field) const;
    const char**	getLabels(IlvTextField* field) const;
    IlUShort		getLabelsCount(IlvTextField* field) const;
    IlUShort		getPosition(IlvTextField* field,
				    IlBoolean& error) const;
    void		removeLabel(IlvTextField* field, IlShort index);
    void		addLabel(IlvTextField* field, const char* label);
    inline IlvOrientation getArrowOrientation() const
	{ return _arrowOrientation; }
    void		setArrowOrientation(IlvOrientation orientation,
					    IlBoolean redraw = IlFalse);
    inline
    IlvOrientation	getArrowLayout() const { return _arrowLayout; }
    void		setArrowLayout(IlvOrientation orientation,
				       IlBoolean redraw = IlFalse);
    IlUInt		getPeriod() const;
    void		setPeriod(IlUInt period);

    IlvGraphic*		pointToObject(const IlvPoint&,
				      const IlvTransformer*) const;

    inline IlvArrowButton* getIncrementButton() const
	{ return _incrButton; }
    inline IlvArrowButton* getDecrementButton() const
	{ return _decrButton; }

    IlBoolean		isIncrementSensitive() const;
    void		setIncrementSensitive(IlBoolean value,
					      IlBoolean redraw = IlFalse);
    IlBoolean		isDecrementSensitive() const;
    void		setDecrementSensitive(IlBoolean value,
					      IlBoolean redraw = IlFalse);

    void		checkArrowsSensitivity(IlBoolean);

    virtual void	computeArrowRects(IlvRect& decrArrow,
					  IlvRect& incrArrow,
					  IlvRect& internal,
					  const IlvTransformer* t) const;
    inline IlvTextField*	getActiveField() const
	{ return (IlvTextField*)_lastFieldFocus; }

    virtual IlUInt	getCallbackTypes(const char*     const**,
					 const IlSymbol* const**) const;

    inline static IlSymbol*		IncrementCallbackType()
	{ return  _incrementSymbol; }
    inline static IlSymbol*		IncrementSymbol()
	{ return  IncrementCallbackType(); }

    IlvDefineCallback(Increment);

    inline static IlSymbol*		DecrementCallbackType()
	{ return  _decrementSymbol; }
    inline static IlSymbol*		DecrementSymbol()
	{ return  DecrementCallbackType(); }
    IlvDefineCallback(Decrement);

    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawArrow(const IlvArrowButton*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    void		setHolder(IlvGraphicHolder*);
    virtual void	setSensitive(IlBoolean);
    virtual void	showFrame(IlBoolean);
    virtual void	setTransparent(IlBoolean);
    virtual void	apply(IlvApplyObject, IlAny);
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setPalette(IlvPalette*);
    virtual void	setThickness(IlUShort);
    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    static IlSymbol*	_infoSymbol;
    static IlSymbol*	_incrementSymbol;
    static IlSymbol*	_decrementSymbol;

    DeclareGraphicAccessors();

    static IlSymbol*	_valueValue;
    static IlSymbol*	_arrowDirectionValue;
    static IlSymbol*	_arrowLayoutValue;
    static IlSymbol*	_repeatPeriodValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvSpinBox);

protected:
    IlBoolean		iHandleEvent(IlvEvent&);
    void		layout();
    void		updateLook();
    void		setFocus(IlvGadget*);
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* = 0) const;
    virtual IlBoolean	classFocusable() const;
    IlvGraphic*		getFirstObject() const;
    IlvGraphic*		getNextObject(IlvGraphic*) const;
    IlvGraphic*		getPreviousObject(IlvGraphic*) const;
    IlvDim		getArrowSpacing() const;
    IlvDim		getFieldSpacing() const;
    IlvDim		getArrowWidth() const;
    IlUInt		_spinflags;
    IlvArrowButton*	_decrButton;
    IlvArrowButton*	_incrButton;
    IlvGadget*		_focusGadget;
    IlvTextField*	_lastFieldFocus;
    IlvOrientation	_arrowOrientation;
    IlvOrientation	_arrowLayout;
    IlList		_list;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(spinbox);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/spinbox.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/spinbox.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/spinbox.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/spinbox.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/spinbox.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Spinbox_H */
