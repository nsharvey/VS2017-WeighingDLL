// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/abscombo.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliAbstractComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Abscombo_H
#define __Ili_Abscombo_H

#if !defined(__Ili_Entryfld_H)
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif
#if !defined(__Ili_Palspec_H)
#  include <ilviews/dataccess/palspec.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliAbstractComboBox
    : public IliEntryField
{
public:
    virtual ~IliAbstractComboBox();

    IlBoolean		isArrowInverted() const;
    void		invertArrow();
    IlBoolean		isEditAllowed() const;

    void		allowEdit(IlBoolean enable);

    IlBoolean		isArrowShown() const;

    void		showArrow(IlBoolean show);

    virtual void	open(IlBoolean grab);

    virtual void	openAt(const IlvPoint&, IlBoolean);

    virtual void	close();

    virtual IlBoolean	isOpen() const;

    // Callbacks

    virtual void	onOpen();
    virtual void	onClose();

    // Symbols

    static IlvSymbol*	OpenSymbol();
    static IlvSymbol*	CloseSymbol();

    // Implements IliFieldItf
    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    // Overrides IlvGadget
    DeclareTypeInfo();
    DeclareIOConstructors(IliAbstractComboBox);

    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlvSymbol* const**) const;
    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    void		invert(IlBoolean = IlFalse);
    virtual void	getTextBBox(IlvRect&) const;
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    void		setBackground(IlvColor*);
    void		setPalette(IlvPalette*);

    IlBoolean		isArrowUsingDefaultColor() const;
    void		useDefaultColorForArrow(IlBoolean);

    virtual void	itemsBBox(IlvRect&,
				  IlvRect&,
				  const IlvTransformer* = 0) const;

    static void		GetOpenShortCut(IlUShort& modifiers, IlUShort& key);

    static void		SetOpenShortCut(IlUShort modifiers, IlUShort key);

protected:
    IlBoolean		_readOnly;
    IlBoolean		_allowEdit;
    IlBoolean		_inBtnDown;
    IlBoolean		_arrowInverted;
    IlBoolean		_openOnBtnUp;
    IlBoolean		_defColorForArrow;
    IlBoolean		_isArrowShown;

    IliReliefPalette	_relfpal;
    static IlUShort	_openShortCutKey;
    static IlUShort	_openShortCutModifiers;
    IliAbstractComboBox(IlvDisplay*	display,
			const IlvRect&	rect,
			IlUShort	thickness = IlvDefaultGadgetThickness,
			IlvPalette*	palette = 0);

    void		setOpenOnBtnUp(IlBoolean);

    virtual IlBoolean	mustInvertArrowRect() const;
    virtual IlBoolean	mustBlinkCursor() const;

    virtual void	drawArrow(IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void	drawWindowsArrow(IlvPort*,
					 const IlvRect&,
					 const IlvRegion*) const;
    virtual void	drawWindows95Arrow(IlvPort*,
					   const IlvRect&,
					   const IlvRegion*) const;
    virtual void	drawVxArrow(IlvPort*,
				    const IlvRect&,
				    const IlvRegion*) const;
    virtual void	drawMotifArrow(IlvPort*,
				       const IlvRect&,
				       const IlvRegion*) const;

    virtual void	drawWindowsFocusBox(IlvPort*, IlvRect,
					    const IlvTransformer*,
					    const IlvRegion*) const;
    virtual void	onUpKey();
    virtual void	onDownKey();
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliAbstractComboBox);

#endif /* !__Ili_Abscombo_H */
