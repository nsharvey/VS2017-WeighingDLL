// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/textfd.h
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
// Declaration of the IlvTextField class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Textfd_H
#define __Ilv_Gadgets_Textfd_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#  include <ilviews/graphics/holder.h>
#endif

#define ILVTEXTFIELD_EDITABLEFLAG    0
#define ILVTEXTFIELD_READALIGNFLAG   1
#define ILVTEXTFIELD_READMAXCHARFLAG 2
#define ILVTEXTFIELD_MOVEFOCUSFLAG   3
#define ILVTEXTFIELD_DISALLOWTOOLTIP 4

class IlvTextField;
class IlvTextFieldBidiExt;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvTextFieldLFHandler : public IlvObjectLFHandler
{
public:
    IlvTextFieldLFHandler(IlvLookFeelHandler* lfh);

    virtual void	getTextArea(const IlvTextField* tfd,
				    IlvRect& rect,
				    const IlvTransformer* t) const = 0;
    virtual IlvPalette*	getTextPalette(const IlvTextField*) const = 0;
    virtual void	drawContents(const IlvTextField* tfd,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawBackground(const IlvTextField* tfd,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvTextField* tfd,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawCursor(const IlvTextField* tfd,
				   IlvPoint& point,
				   IlvPort* dst,
				   const IlvTransformer* t,
				   const IlvRegion* clip) const = 0;
    virtual void	drawFocus(const IlvTextField*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeFocusRegion(const IlvTextField*,
					   IlvRegion&,
					   const IlvTransformer*) const = 0;
    virtual void	setMode(IlvTextField*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvTextField*, IlBoolean) const = 0;
    virtual void	getPreferredSize(const IlvTextField*,
					 IlvDim&,
					 IlvDim&) const = 0;
    virtual IlBoolean	handleEvent(IlvTextField* tfd,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultTextFieldLFHandler
    : public IlvTextFieldLFHandler
{
public:
    IlvDefaultTextFieldLFHandler(IlvLookFeelHandler* lf)
	: IlvTextFieldLFHandler(lf)
    {}

    virtual void	getTextArea(const IlvTextField*,
				    IlvRect&,
				    const IlvTransformer*) const;
    virtual void	getPreferredSize(const IlvTextField*,
					 IlvDim&,
					 IlvDim&) const;
    virtual IlBoolean	handleEvent(IlvTextField*, IlvEvent&) const;
    virtual void	drawContents(const IlvTextField*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvTextField : public IlvGadget
{
public:
    friend class IlvTextFieldBidiExt;
    friend class IlvDefaultTextFieldLFHandler;

    IlvTextField(IlvDisplay*    display,
		 const char*    label,
		 const IlvRect& rect,
		 IlUShort       thickness = IlvDefaultGadgetThickness,
		 IlvPalette*    palette   = 0);

    IlvTextField(IlvDisplay*     display,
		 const IlvPoint& point,
		 const char*     label,
		 IlUShort        thickness = IlvDefaultGadgetThickness,
		 IlvPalette*     palette   = 0);

    virtual ~IlvTextField();
    // ____________________________________________________________
    virtual void	drawText(IlvPort*,
				 const IlvTransformer*,
				 const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawCursor(IlvPoint&,
				   IlvPort*,
				   const IlvTransformer*,
				   const IlvRegion*) const;
    virtual void	drawFocus(IlvPort*, const IlvPalette* ,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual const char*	getDefaultInteractor() const;
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setFont(IlvFont*);
    virtual void	setPalette(IlvPalette*);

    inline IlShort	getCursorPosition() const { return _cursorPosition; }

    void		setCursorPosition(IlShort position);

    inline IlShort	getTextPosition() const { return _textPosition; }

    void		setTextPosition(IlShort position);

    inline IlBoolean	isCursorShown() const { return _showCursor; }

    void		showCursor(IlBoolean value,
				   IlBoolean redraw = IlFalse);

    IlShort		pointToPosition(const IlvPoint& point,
					const IlvTransformer* t = 0) const;

    inline const char*	getLabel() const { return _label; }

    virtual void	setLabel(const char* label,
				 IlBoolean redraw = IlFalse);

    void		setValue(IlInt value, IlBoolean redraw = IlFalse);

    void		setValue(IlFloat value,
				 const char* format = 0,
				 IlBoolean redraw = IlFalse);

    IlInt		getIntValue() const;

    IlFloat		getFloatValue() const;

    virtual const char*	getMessage() const;

    void		locateWord(IlShort pos,
				   IlShort& form,
				   IlShort& to) const;
    inline IlShort	getStartSelection() const { return _selectionFrom; }

    inline IlShort	getEndSelection() const { return _selectionTo; }

    inline void		setStartSelection(IlShort position)
			{
			    setSelection(position, _selectionTo);
			}

    inline void		setEndSelection(IlShort position)
			{
			    setSelection(_selectionFrom, position);
			}

    void		setSelection(IlShort start, IlShort end);

    virtual void	removeSelection();

    void		ensureVisible(IlShort position,
				      const IlvTransformer* t = 0);

    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual void	fitToContents(IlvDirection = (IlvDirection)
				      (IlvHorizontal|IlvVertical));

    void		fitToLabel();

    IlBoolean		isEditable() const;

    void		setEditable(IlBoolean value);

    inline IlvPosition	getAlignment() const { return _alignment; }

    inline void		setAlignment(IlvPosition alignment)
			{
			    _alignment = alignment;
			}

    inline IlShort	getMaxChar() const { return _maxChar; }

    inline void		setMaxChar(IlShort count) { _maxChar = count; }

    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	changeLanguage(const IlSymbol*);

    // Multi-byte handling
    inline const char*	getValue() const { return _value; }
    inline
    const IlvWChar*	getWcValue() const { return _wcValue; }
    inline IlShort	getValueLength() const { return _valueLength; }
    inline IlUShort	getMaxCharSize() const { return _maxCharSize; }

    // Specific callback
    virtual void	labelChanged();

    inline static
    IlSymbol*		ChangeSymbol() { return SCallbackSymbol(); }

    IlvDefineCallback(Change);


    // event handling methods
    virtual IlBoolean	handleEvent(IlvEvent& event);

    virtual const char*	check(IlUShort character);
    virtual const char*	mbCheck(const char* text);

    virtual void	validate();

    virtual IlBoolean	handleControl(IlUShort character);

    IlBoolean		getChangeFocusOnValidation() const;

    void		setChangeFocusOnValidation(IlBoolean value);

    virtual IlBoolean	allowToolTip() const;

     // Input Method interaction
    virtual IlBoolean	needsInputContext() const;
    virtual void	setNeedsInputContext(IlBoolean val);

    DeclareGraphicAccessors();

    static IlSymbol*	_labelValue;
    static IlSymbol*	_cursorPositionValue;
    static IlSymbol*	_selectionStartValue;
    static IlSymbol*	_selectionEndValue;
    static IlSymbol*	_alignmentValue;
    static IlSymbol*	_maxCharValue;
    static IlSymbol*	_editableValue;
    static IlSymbol*	_changeFocusValue;

    DeclareLazyTypeInfo();

    IlvTextField(const IlvTextField&);
    IlvTextField(IlvInputFile&, IlvPalette*, IlUShort from = 0);

    // ------------------------------------------------------------
    // Cursor commands
    virtual void	cursorMoveTo(IlUShort pos);
    virtual void	cursorBeginningOfLine();
    virtual void	cursorEndOfLine();
    virtual void	cursorLeft();
    virtual void	cursorRight();
    virtual void	cursorEnsureVisible();
    virtual void	cursorKillLine();
    virtual void	cursorYank();
    virtual void	cursorDeleteChar();
    virtual void	cursorBackSpace();
    virtual void	cursorInsertChar(IlUShort ch);

    // ------------------------------------------------------------
    // Bidi interface
    virtual
    IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual
    IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean	setBidiContext(IlvBidiContext*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    inline
    IlvTextFieldBidiExt* bidiExt() const { return _bidiExt; }
    void		bidiSwitch(IlBoolean RtoL,
				   IlBoolean force = IlTrue) const;
    void		bidiFix();
    void		logicalKillOneChar(IlBoolean forward);
    IlShort		visualFromLogical(IlShort visPos) const;
    IlShort		logicalFromVisual(IlShort logPos) const;
    void		internalSetSelection(IlShort from,
					     IlShort to,
					     IlBoolean logical);

protected:
    char*		_label;
    IlShort		_cursorPosition;
    IlShort		_textPosition;
    IlBoolean		_showCursor;
    IlShort		_selectionFrom;
    IlShort		_selectionTo;
    IlvPosition		_alignment;
    IlShort		_maxChar;

    IlBoolean		iHandleEvent(IlvEvent& event);
    virtual IlBoolean	classFocusable() const;
    virtual void	getTextBBox(IlvRect&) const;
    virtual void	getTextArea(IlvRect&, const IlvTransformer*) const;
    virtual void	internalSetLabel(const char*);

    // Event handling
    const char*		iCallCheck(IlUShort ch);
    const char*		iCallMbCheck(const char* text);
    void		iCallValidate();
    IlBoolean		iCallHandleControl(IlUShort ch);
    virtual void	killLeft();
    virtual void	killRight();
    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual IlBoolean	handleButtonDown(IlvEvent&);
    virtual IlBoolean	handleButtonDragged(IlvEvent&);
    virtual IlBoolean	handleButtonUp(IlvEvent&);
    virtual IlBoolean	handleDoubleClick(IlvEvent&);
    virtual IlBoolean	handleTripleClick(IlvEvent&);
    void		handleSelectionKey(IlvEvent&);

    IlShort		_initialDragPos;
    // Clipboard
    virtual void	copyToClipboard();
    virtual void	pasteFromClipboard(IlBoolean redraw = IlTrue);

    // Multi-byte handling
    char*		_value;       // TextField value stored as char*.
    IlvWChar*		_wcValue;     // TextField value stored as wchar_t*.
    IlShort		_valueLength; // Number of char in the TextField value.
    IlUShort		_maxCharSize; // Max bytes per char in current locale.

    IlvTextFieldBidiExt*	_bidiExt;


    IlBoolean		replaceText(IlShort from,
				    IlShort to,
				    const char* insert = 0,
				    IlShort insertLength = -1);
    IlUShort		countCharacters(const char* text,
					IlShort textLength = -1) const;

     // Input Method interaction
    IlvPoint		positionToPoint(IlShort pos) const;

    // static variables
    static IlBoolean	IsSelectingWord;
    static IlShort	WordStart;
    static IlShort	WordEnd;

    static IlvTextField*	_blinkingField;
    static IlvTextField*	_watchDelete;

    friend class IlvBlinkTimer;

private:
    IlBoolean		_needsIC;

    void		makeLabel(const char* label);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvHTextFieldInteractor : public IlvHGadgetInteractor
{
public:
    virtual const char*	check(IlvTextField*, IlUShort) = 0;
    virtual const char*	mbCheck(IlvTextField*, const char*) = 0;
    virtual void	validate(IlvTextField*) = 0;
    virtual IlBoolean	handleControl(IlvTextField*, IlUShort) = 0;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(textfd);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/textfd.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/textfd.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/textfd.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/textfd.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/textfd.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Textfd_H */
