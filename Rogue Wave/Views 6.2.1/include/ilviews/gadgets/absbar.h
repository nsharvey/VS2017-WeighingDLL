// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/absbar.h
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
// Declaration of the IlvAbstractBar class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Absbar_H
#define __Ilv_Gadgets_Absbar_H

#if !defined(__Ilv_Gadgets_Amenu_H)
#  include <ilviews/gadgets/amenu.h>
#endif

class IlvAbstractBar;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvAbstractBarLFHandler : public IlvObjectLFHandler
{
public:
    IlvAbstractBarLFHandler(IlvLookFeelHandler* lf);

    virtual void	setMode(IlvAbstractBar*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvAbstractBar*, IlBoolean) const = 0;
    virtual void	drawGadgetItem(const IlvAbstractBar*,
				       const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer*,
				       const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvAbstractBar*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const = 0;
    virtual void	drawBackground(const IlvAbstractBar*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const = 0;
    virtual void	drawFrame(const IlvAbstractBar*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	getInternalBBox(const IlvAbstractBar*,
					IlvRect&) const = 0;
    virtual void	getPreferredSize(const IlvAbstractBar*,
					 IlvDim& w,
					 IlvDim& h) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultAbstractBarLFHandler
    : public IlvAbstractBarLFHandler
{
public:
    IlvDefaultAbstractBarLFHandler(IlvLookFeelHandler* lf)
	: IlvAbstractBarLFHandler(lf)
    {}

    virtual void	drawGadgetItem(const IlvAbstractBar*,
				       const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer*,
				       const IlvRegion* clip) const;
    virtual void	getPreferredSize(const IlvAbstractBar*,
					 IlvDim& w,
					 IlvDim& h) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvAbstractBar : public IlvAbstractMenu
{
public:

    IlvAbstractBar(IlvDisplay*		display,
		   const IlvPoint&	point,
		   const char* const*	labels    = 0,
		   IlUShort		count     = 0,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    IlvAbstractBar(IlvDisplay*		display,
		   const IlvRect&	rect,
		   const char* const*	labels    = 0,
		   IlUShort		count     = 0,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    IlvAbstractBar(IlvDisplay*		display,
		   const IlvPoint&	point,
		   IlvMenuItem*		items,
		   IlUShort		count,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    IlvAbstractBar(IlvDisplay*        display,
		   const IlvRect&     rect,
		   IlvMenuItem*	      items,
		   IlUShort           count,
	           IlUShort           thickness = IlvDefaultGadgetThickness,
		   IlvPalette*        palette   = 0);

    virtual
    IlvDirection	getOrientation() const;

    void		setOrientation(IlvDirection orientation);

    IlvDim		getSpacing() const;

    void		setSpacing(IlvDim spacing);

    IlBoolean		isFlushingRight() const;

    void		setFlushingRight(IlBoolean value);

    IlBoolean		useConstraintMode() const;

    void		setConstraintMode(IlBoolean value);

    void		getDefaultItemSize(IlvDim& width,
					   IlvDim& height) const;

    void		setDefaultItemSize(IlvDim width,
					   IlvDim height,
					   IlBoolean redraw = IlTrue);

    void		setWidth(IlvDim width);

    void		setHeight(IlvDim height);

    virtual void	internalBBox(IlvRect& rect,
				     const IlvTransformer* t = 0) const;

    virtual IlUInt	getCallbackTypes(const char* const** names,
					 const IlSymbol* const** types) const;

    IlvDefineCallback(OrientationChanged);
    IlvDefineCallback(GeometryChanged);

    inline
    static IlSymbol*	OrientationChangedCallbackType()
			{
			    return _orientationChangedSymbol;
			}
    inline
    static IlSymbol*	OrientationChangedSymbol()
			{
			    return OrientationChangedCallbackType();
			}
    virtual void	orientationChanged();
    inline
    static IlSymbol*	GeometryChangedCallbackType()
			{
			    return _geometryChangedSymbol;
			}
    inline
    static IlSymbol*	GeometryChangedSymbol()
			{
			    return GeometryChangedCallbackType();
			}
    virtual void	geometryChanged(const IlvRect& rect);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvAbstractBar);
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_geometryChangedSymbol;
    static IlSymbol*	_orientationChangedSymbol;
    static IlSymbol*	_orientationValue;
    static IlSymbol*	_constraintValue;
    static IlSymbol*	_itemSpacingValue;
    static IlSymbol*	_itemsWidthValue;
    static IlSymbol*	_itemsHeightValue;
    static IlSymbol*	_flushRightValue;

protected:
    IlBoolean		_altKeyPressed;
    IlvDim		_spacing;
    IlvDim		_itemsHeight;
    IlvDim		_itemsWitdh;

    virtual void	iCallSelect(IlUShort pos);
    virtual IlBoolean	classFocusable() const;
    virtual
    IlvAlignment	getGadgetItemAlignment() const;

public:
    // Not Documented
    virtual void	drawFocus(IlvPort* ,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer*) const;
    IlvMenuItem*	matchAccelerator(IlvEvent&,
					 IlvPopupMenu**,
					 IlShort*) const;
    IlBoolean		handleAccelerator(IlvEvent&) const;

    // Event handling methods
    virtual IlBoolean	buttonDown(IlShort);
    virtual IlBoolean	buttonUp();
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	select(IlUShort pos);
    virtual void	unSelect(IlUShort pos);
    virtual IlBoolean	isGrabbed() const;
    virtual IlvDim	getMarginSelection() const;
    virtual void	grab();
    virtual void	unGrab();
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    void		computeMaxSizes(IlvDim& width,
					IlvDim& height,
					IlUShort from = 0,
					IlUShort to = (IlUShort)-1) const;
    void		popDownMenu();
    virtual void	iCallUnSelect(IlUShort pos);
    void		adjustFirstVisible(IlBoolean redraw);
    virtual void	setMode(IlvDrawMode m);
    virtual void	setOverwrite(IlBoolean value);
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawContents(IlvPort* dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion* clip = 0) const;
    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawFrame(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	itemBBox(IlUShort item,
				 IlvRect& rect,
				 const IlvTransformer* t = 0) const;
    void		computeBBox();
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual void	fitToContents(IlvDirection = (IlvDirection)
				      (IlvHorizontal|IlvVertical));
    virtual void	itemSize(IlUShort pos,
				 IlvDim& width,
				 IlvDim& height) const;
    void		changeSelection(IlShort);
    IlUShort		getLargestItem(IlvDirection) const;
    IlvDim		getLargestItemSize(IlvDirection) const;
    virtual IlUShort	getHMargin() const;
    virtual IlUShort	getVMargin() const;
};

// --------------------------------------------------------------------------
inline IlBoolean
IsAnIlvAbstractBar(const IlvGraphic* object)
{
    return object->isSubtypeOf(IlvAbstractBar::ClassInfo());
}

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(absbar);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/absbar.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/absbar.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/absbar.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/absbar.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Absbar_H */
