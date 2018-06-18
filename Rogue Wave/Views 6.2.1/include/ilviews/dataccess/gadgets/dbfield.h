// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbfield.h
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
// Declaration of the IliDbField class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbfield_H
#define __Ili_Dbfield_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Entryfld_H)
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif
#if !defined(__Ili_Tblcombo_H)
#  include <ilviews/dataccess/gadgets/tblcombo.h>
#endif
#if !defined(__Ili_Dbtext_H)
#  include <ilviews/dataccess/gadgets/dbtext.h>
#endif
#if !defined(__Ili_Dboptmnu_H)
#  include <ilviews/dataccess/gadgets/dboptmnu.h>
#endif
#if !defined(__Ili_Dbstrlst_H)
#  include <ilviews/dataccess/gadgets/dbstrlst.h>
#endif
#if !defined(__Ili_Dbtoggle_H)
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif
#if !defined(__Ili_Toggsel_H)
#  include <ilviews/dataccess/gadgets/toggsel.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbField
: public IlvGadget, public IliFieldItf
{
public:
    IliDbField(IlvDisplay* display, const IlvRect& rect,
	       IliDbFieldStyle style = IliEntryFieldStyle,
	       IlUShort thickness = IlvDefaultGadgetThickness,
	       IlvPalette* palette = 0);
    virtual ~IliDbField();

    IliDbFieldStyle	getStyle() const;
    virtual void	setStyle(IliDbFieldStyle style);

    const IlvPoint&	getLabelPosition() const;
    void		setLabelPosition(const IlvPoint& pos);
    void		putLabelAtLeft();
    void		putLabelOnTop();
    IlvColor*		getLabelForeground() const;
    void		setLabelForeground(IlvColor* color);
    IlvFont*		getLabelFont() const;
    void		setLabelFont(IlvFont* font);

    void		computeLabelBBox(IlvRect&,
					 const IlvTransformer* = 0) const;
    void		getPreferredSize(IlvDim&, IlvDim&) const;
    void		getPreferredGadgetSize(IlvDim&, IlvDim&) const;
    void		setGadgetRect(const IlvRect&);

    // Implement IliFieldItf
    virtual const IliValue& f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&, IlBoolean = IlFalse);
    virtual void	f_refresh();

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual IlBoolean	f_complete();

    virtual void	f_selectTextForAppend();
    virtual void	f_selectTextForOverwrite();

    virtual
    IliInputPolicy	f_getInputPolicy() const;
    virtual void	f_setInputPolicy(IliInputPolicy);

    virtual IlBoolean	f_isInputModified() const;
    virtual void	f_setInputModified(IlBoolean);

    virtual
    const IliFormat&	f_getFormat() const;
    virtual void	f_setFormat(const IliFormat&);

    virtual
    const IliInputMask& f_getMask() const;
    virtual void	f_setMask(const IliInputMask&);

    virtual
    IlvAlignment	f_getAlignment() const;
    virtual void	f_setAlignment(IlvAlignment);

    virtual IlShort	f_getMaxLength() const;
    virtual void	f_setMaxLength(IlShort);

    virtual IlBoolean	f_canMapValue() const;
    virtual void	f_mapValue(IliValue&) const;

    virtual IlBoolean	f_opensADialog() const;

    virtual IlBoolean	f_hasLabel() const;
    virtual const char* f_getLabel() const;
    virtual void	f_setLabel(const char*);

    virtual void	f_enableAutoReDraw(IlBoolean);

    virtual void	f_setForeignTable(IliTable*,
					  IlBoolean = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);
    virtual void	f_setConstrained(IlBoolean);
    virtual void	f_enableCompletion(IlBoolean);
    virtual void	f_setVisibleRowsCount(IlInt);

    // Override IlvGraphic

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbField);

    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    virtual void	applyTransform(const IlvTransformer*) ;
    virtual IlBoolean	zoomable() const;
    virtual void	invert(IlBoolean = IlFalse);

    virtual void	apply(IlvApplyObject, IlAny);
    virtual void	applyReferences(IlvApplyObject, IlAny);

    virtual void	setPalette(IlvPalette*);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setPattern(IlvPattern*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setPlaneMask(unsigned int);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);

    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*,
				    const IlvTransformer* = 0,
				    const IlvRegion* = 0) const;

    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer*
					                          = 0)const;

    virtual IlBoolean	handleAccelerator(IlvEvent&) const;

    // Override IlvGadget
    virtual void	setSensitive(IlBoolean);
    virtual void	setThickness(IlUShort);
    virtual void	setHolder(IlvGadgetHolder*);
    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	reDraw() const;
    virtual void	focusIn();
    virtual void	focusOut();
    virtual void	useDefaultSize(IlBoolean);

    // Internals
    void		fieldInputModified();
    inline IlvPalette*  getLabelPalette() const { return _labelPalette; }

    inline const IliFieldItf*	getSubField() const { return _field; }
    inline IliFieldItf*	getSubField() { return _field; }

    // Accessors
    virtual const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

    virtual void	changeLanguage(const IlSymbol*);

protected:
    IlBoolean		_readOnly;
    IlBoolean		_inputModifiedMutex;

    IliFieldItf*	_field;
    IliDbFieldStyle	_style;
    IlvAlignment	_alignment;
    IlShort		_maxLength;
    IliString		_label;
    IlvPoint		_labelPos;
    IlvPalette*		_labelPalette;
    IliFormat		_format;
    IliInputMask	_mask;

    // -- override IlvGadget
    virtual IlBoolean	classFocusable() const;
    virtual void	changeLook(const IlvLookFeelHandler*);

    virtual
    IliFieldItf*	makeField(IliDbFieldStyle);
    virtual void	setField(IliFieldItf*);
};

// --------------------------------------------------------------------------
IlvDeclareEnumTypeClass(ILV_DBG_EXPORTED, DbFieldStyle);

IliModuleDECL_exp(ILV_DBG_EXPORTED, DbFieldStyle);
IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbField);

#endif /* !__Ili_Dbfield_H */
