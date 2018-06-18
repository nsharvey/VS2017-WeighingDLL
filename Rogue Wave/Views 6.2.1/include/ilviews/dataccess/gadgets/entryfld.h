// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/entryfld.h
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
// Declaration of the IliEntryField class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Entryfld_H
#define __Ili_Entryfld_H

#if !defined(__Ilv_Gadgets_Textfd_H)
#  include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliEntryField
: public IlvTextField, public IliFieldItf
{
public:
    IliEntryField(IlvDisplay* display,
		  const IlvRect& rect,
		  IlUShort thickness = IlvDefaultGadgetThickness,
		  IlvPalette* palette = 0);
    IliEntryField(IlvDisplay* display,
		  const char* label,
		  const IlvRect& rect,
		  IlUShort thickness = IlvDefaultGadgetThickness,
		  IlvPalette* palette = 0);
    IliEntryField(IlvDisplay* display,
		  const IlvPoint& at,
		  const char* label,
		  IlUShort thickness = IlvDefaultGadgetThickness,
		  IlvPalette* palette = 0);
    ~IliEntryField();

    IlBoolean		isBackgroundLookSensitive() const;
    void		setBackgroundLookSensitive(IlBoolean);

    virtual IlBoolean	isMappingEnabled() const;

    // overrides IliFieldItf
    virtual const IliValue&	f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&, IlBoolean = IlFalse);

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual
    IlvAlignment	f_getAlignment() const;
    virtual void	f_setAlignment(IlvAlignment);

    virtual IlShort	f_getMaxLength() const;
    virtual void	f_setMaxLength(IlShort);

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_selectTextForAppend();
    virtual void	f_selectTextForOverwrite();

    virtual
    const IliFormat&	f_getFormat() const;
    virtual void	f_setFormat(const IliFormat&);

    virtual
    const IliInputMask& f_getMask() const;
    virtual void	f_setMask(const IliInputMask&);

    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    virtual
    IliInputPolicy	f_getInputPolicy() const;
    virtual void	f_setInputPolicy(IliInputPolicy);

    virtual void	f_setInputModified(IlBoolean);

    virtual IlBoolean	needsInputContext() const;
    virtual void	setNeedsInputContext(IlBoolean);

    virtual const char* getMessage() const;
    virtual void	validate();

    DeclareTypeInfo();
    DeclareIOConstructors(IliEntryField);

    virtual void	setHolder(IlvGadgetHolder*);

    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual IlBoolean	handleControl(IlUShort);
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	applyReferences(IlvApplyObject, IlAny);
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer* = 0,
				     const IlvRegion* = 0) const;

    virtual const char* mbCheck(const char*);

    virtual IlBoolean	onValidate(IlBoolean = IlTrue, IlBoolean = IlFalse);

    virtual void	copyToClipboard();
    virtual void	pasteFromClipboard(IlBoolean = IlTrue);
    virtual void	removeSelection();

    virtual const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static  IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

protected:
    IliFormat		_format;
    IliInputMask	_mask;
    IlBoolean		_isBackgroundLookSensitive;
    IlBoolean		_inBtnDown;
    IlBoolean		_formatted;
    IlBoolean		_useMask;
    IliValue		_value;
    IlShort		_maxLen;
    IliInputPolicy	_inputPolicy;

    virtual void	internalSetLabel(const char*);

    void		callDrawText(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual IlBoolean	mustBlinkCursor() const;

    virtual IlBoolean	labelToValue(const char*, IliValue&, IlBoolean) const;
    virtual void	valueToLabel(const IliValue& value);
    IlBoolean		fixLabel();
    void		setLabelSilently(const char* label);
    const char*		unFormatLabel(IliString&, const char*) const;
    const char*		formatValue(IliString& dest, const IliValue& val);
    IlBoolean		doHandleEvent(IlvEvent&);

    virtual const char* wcheck(wchar_t);

    void		killChars(IlShort, IlShort);
    virtual void	killLeft();
    virtual void	killRight();

    IlBoolean		charPosToBytePos(IlShort, IlShort&) const;
    IlBoolean		bytePosToCharPos(IlShort, IlShort&) const;
    IlShort		getCursorCharPos() const;
    IlShort		getLastCharPos() const;

    inline IlShort	toCharPos(IlShort bp) const { return bp; }
    inline IlShort	toBytePos(IlShort cp) const { return cp; }
    inline void		setCursorCharPos(IlShort cp)
	{ setCursorPosition(toBytePos(cp)); }
    inline void		setCharSelection(IlShort s, IlShort e)
	{ setSelection(toBytePos(s), toBytePos(e)); }

    wchar_t		getCharAt(IlShort) const;
    IlBoolean		canBeDeleted(IlShort) const;
    IlBoolean		canBeDeleted(IlShort, IlShort) const;

    void		selectCharNoReDraw(IlShort, IlBoolean = IlTrue);
    void		selectChar(IlShort, IlBoolean = IlTrue);
    IlShort		getLastPosition() const;
    void		moveRight();
    void		moveLeft();

    IlInt		getFirstEditablePos() const;
    IlInt		getLastEditablePos() const;
    IlInt		getNextEditablePos() const;
    IlInt		getPreviousEditablePos() const;

    virtual void	reportValueError() const;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliEntryField);

#endif /* !__Ili_Entryfld_H */
