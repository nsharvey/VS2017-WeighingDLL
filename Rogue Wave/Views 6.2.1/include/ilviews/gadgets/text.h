// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/text.h
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
// Declaration of the IlvText class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Text_H
#define __Ilv_Gadgets_Text_H

#if !defined(__Ilv_Gadgets_Scgadget_H)
#  include <ilviews/gadgets/scgadget.h>
#endif

#define ILVTEXTNOTEDITABLEFLAG	2
#define ILVTEXTDISALLOWTOOLTIP	6
#define ILVTEXTSAVE30INFO	7

class IlvText;
class IlvTextBidiExt;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTextLFHandler : public IlvObjectLFHandler
{
public:
    IlvTextLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawSelection(const IlvText*	text,
				      IlvPort*		dst,
				      const IlvRect&	rect,
				      const IlvRegion*	clip) const = 0;
    virtual void	drawFrame(const IlvText*	text,
				  IlvPort*		dst,
				  const IlvTransformer*	t,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawBackground(const IlvText* text,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawGadgetContents(const IlvText* text,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const = 0;
    virtual void	setMode(IlvText*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvText*, IlBoolean) const = 0;
    virtual void	drawFocus(const IlvText*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const = 0;
    virtual void	computeFocusRegion(const IlvText*,
					   IlvRegion&,
					   const IlvTransformer* = 0) const=0;
    virtual void	drawCursor(const IlvText* text,
				   IlvPoint& point,
				   IlvPort* dst,
				   const IlvTransformer* t,
				   const IlvRegion* clip) const = 0;
    virtual IlBoolean	handleGadgetEvent(IlvText*	text,
					  IlvEvent&	event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultTextLFHandler : public IlvTextLFHandler
{
public:
    IlvDefaultTextLFHandler(IlvLookFeelHandler* lf)
	: IlvTextLFHandler(lf)
    {}

    virtual void	drawSelection(const IlvText*,
				      IlvPort*,
				      const IlvRect&,
				      const IlvRegion*) const;
    virtual void	drawFrame(const IlvText*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(const IlvText*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetContents(const IlvText*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual IlBoolean	handleGadgetEvent(IlvText*,
					  IlvEvent& event) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTextLocation
{
public:
    IlvTextLocation(IlUShort line = 0, IlUShort column = 0)
        : _line(line),
	  _column(column)
    {}
    IlvTextLocation(const IlvTextLocation& other)
        : _line(other._line),
	  _column(other._column)
    {}

    inline IlUShort	getLine() const { return _line; }

    inline void		setLine(IlUShort line) { _line = line; }

    inline IlUShort	getColumn() const { return _column; }

    inline void		setColumn(IlUShort column) { _column = column; }

    inline void		set(IlUShort line = 0, IlUShort column = 0)
			{
			    _line = line;
			    _column = column;
			}

    inline IlBoolean	isSame(const IlvTextLocation& location) const
			{
			    return ((_line   == location.getLine()) &&
				    (_column == location.getColumn()));
			}

    inline IlBoolean	isBefore(const IlvTextLocation& location) const
			{
			    return ((_line < location.getLine()) ||
				    ((_line   == location.getLine()) &&
				     (_column <= location.getColumn())));
			}

    inline
    IlvTextLocation&	operator=(const IlvTextLocation& other)
			{
			    _line = other._line;
			    _column = other._column;
			    return *this;
			}
    inline IlUShort&	line()   { return _line;   }
    inline IlUShort&	column() { return _column; }

private:
    IlUShort		_line;
    IlUShort		_column;

    friend class IlvText;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvText;
typedef void (*IlvTextChange)(IlvText*);
typedef IlBoolean (* IlvTextCallback)(IlvText*	text,
				       IlUShort	line,
				       IlUShort	column,
				       IlAny	arg);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvText : public IlvScrolledGadget
{
    friend class IlvTextBidiExt;
    friend class IlvDefaultTextLFHandler;

public:
    IlvText(IlvDisplay*		display,
	    const IlvPoint&	point,
            const char* const*	labels		= 0,
            IlUShort		count		= 0,
            IlBoolean		copy		= IlTrue,
            IlUShort		thickness	= IlvDefaultGadgetThickness,
            IlvPalette*		palette		= 0);
    IlvText(IlvDisplay*		display,
            const IlvRect&	rect,
            const char* const*	labels		= 0,
            IlUShort		count		= 0,
            IlBoolean		copy		= IlTrue,
            IlUShort		thickness	= IlvDefaultGadgetThickness,
            IlvPalette*		palette		= 0);
    IlvText(IlvDisplay*		display,
	    const IlvPoint&	point,
            const char*		text,
	    IlUShort		thickness	= IlvDefaultGadgetThickness,
            IlvPalette*		palette		= 0);
    IlvText(IlvDisplay*		display,
	    const IlvRect&	rect,
            const char*		text,
	    IlUShort		thickness	= IlvDefaultGadgetThickness,
            IlvPalette*		palette		= 0);
    virtual ~IlvText();

    inline IlUShort	getFirstLine() const { return _firstLine; }
    void		setFirstLine(IlUShort line);
    inline IlUShort	getNumberOfLines() const { return _count; }
    IlUShort	getNumberOfVisibleLines(const IlvTransformer* t = 0) const;
    IlvDim		getMaxWidth() const;
    IlUShort		getLastLine(const IlvTransformer* t = 0) const;
    IlUShort	   getLastFullVisibleLine(const IlvTransformer* t = 0) const;
    inline IlvDim	getOffset() const { return _xoffset; }
    void		setOffset(IlvDim offset);
    void		changeOffset(IlvDim);
    IlvTextLocation	getEndLocation() const;
    inline
    IlvTextLocation	getCursorLocation() const { return _cursorLocation; }
    void		setCursorLocation(const IlvTextLocation& location);
    const char*		getLine(IlUShort index) const;
    inline IlUShort	getLineLength(IlUShort index) const
	{ return _labelLengths[index]; }
    const char* const*	getLines(IlUShort& count) const;
    void		setLine(IlUShort	line,
				const char*	text,
				IlBoolean	copy = IlTrue);
    void		addLine(const char* text, IlShort line = -1);
    void		removeLine(IlUShort line);
    void		removeLines(IlUShort line, IlUShort count);
    virtual void	setLines(const char* const*	labels,
				 IlUShort		count,
				 IlBoolean		copy = IlTrue);
    virtual void	addLines(const char* const*	labels,
				 IlUShort		count,
				 IlShort		line = -1,
				 IlBoolean		redraw = IlFalse);
    void		insertLabels(const char* const*,
				     IlUShort,
				     IlvTextLocation&,
				     IlBoolean = IlFalse);
    const char*		getText() const;
    virtual void	setText(const char* text);
    void		addText(const char*	text,
				IlShort		line = -1,
				IlBoolean	redraw = IlFalse);
    void		insertText(const char*		text,
				   IlvTextLocation&	location,
				   IlBoolean		redraw = IlFalse);
    void		insertChar(const IlvTextLocation&	location,
				   IlUShort			character);
    void		removeChar(const IlvTextLocation& location);
    void		cutLine(const IlvTextLocation& location);
    inline void		getSelection(IlvTextLocation& from,
				     IlvTextLocation& to) const
			{
			    from = _selectionFrom;
			    to = _selectionTo;
			}
    void		setSelection(const IlvTextLocation& from,
				     const IlvTextLocation& to);
    const char*		getSelectedText() const;
    void		locateWord(const IlvTextLocation&	location,
				   IlvTextLocation&		start,
				   IlvTextLocation&		end) const;

    inline IlBoolean	isCursorShown() const { return _showCursor; }
    inline void		showCursor(IlBoolean value) { _showCursor = value; }
    IlBoolean		isEditable() const;
    void		setEditable(IlBoolean value);

    IlvTextLocation	pointToPosition(const IlvPoint&		point,
					const IlvTransformer*	t = 0) const;

    virtual IlUShort	isValid(IlUShort) const;
    IlBoolean		applyBackward(IlvTextLocation&,
				      IlvTextCallback,
				      IlAny);
    IlBoolean		applyForward(IlvTextLocation&,
				     IlvTextCallback,
				     IlAny);
    void		deSelect(IlBoolean = IlTrue);
    void		removeSelection(IlBoolean = IlTrue);

    virtual void	adjustScrollBars(IlBoolean = IlFalse);
    virtual void	scrollBarVisibilityChanged(IlvDirection);

    inline IlBoolean	isModified() const { return _modified; }
    inline void		setModified(IlBoolean val) { _modified = val; }
    virtual const char*	getDefaultInteractor() const;
    virtual void	scrollBarMoved();
    // Obsolete
    inline IlBoolean	isShadowShown() const { return isShowingFrame(); }
    inline void		showShadow(IlBoolean value)
			{
			    showFrame(value, IlFalse);
			}

    // Margins & bbox
    void		visibleTextBBox(IlvRect&,
					const IlvTransformer* = 0) const;
    IlBoolean		isInTextBBox(IlvPoint,
				     const IlvTransformer* = 0) const;
    void		adjustHeight(IlUShort = 0);
    void		lineBBox(IlUShort,
				 IlvRect&,
				 const IlvTransformer*	t = 0) const;
    void		linesBBox(IlUShort,
				  IlUShort,
				  IlvRect&,
				  const IlvTransformer*	t) const;
    void		lineRegion(IlvRegion&,
				   IlUShort,
				   const IlvTransformer* t = 0) const;
    void		linesRegion(IlvRegion&,
				    IlUShort, IlUShort,
				    const IlvTransformer* = 0) const;

    void		reDrawLine(IlUShort line);

    // File management
    inline const char*	getFileName() const { return _fileName; }
    void		setFileName(const char*);

    IlBoolean		readText(const char*		filename = 0,
				 const IlvTransformer*	t = 0);
    void		readText(ILVSTDPREF istream&	istream,
				 const IlvTransformer*	t = 0);

    IlBoolean		saveText(const char* fileName = 0);
    void		saveText(ILVSTDPREF ostream&);

    // Event hanlding
    virtual IlBoolean	handleGadgetEvent(IlvEvent&);
    virtual IlBoolean	handleSpecialKey(IlvEvent&);
    virtual IlBoolean	handleControl(IlUShort character);
    virtual IlBoolean	handleAltKey(IlUShort character);
    virtual IlBoolean	check(IlUShort character);
    virtual IlBoolean	mbCheck(const char*);

    // Input method interaction
    virtual IlBoolean	needsInputContext() const;
    virtual void	setNeedsInputContext(IlBoolean);

    IlvPoint		locationToPoint(const IlvTextLocation&) const;

    // Scrolling
    void		scrollUp();
    void		scrollDown();
    void		scrollTo(IlUShort);

    // Clipboard
    virtual void	copyToClipboard();
    virtual void	cutToClipboard(IlBoolean = IlTrue);
    virtual void	pasteFromClipboard(IlBoolean = IlTrue);

    // Cursor commands
    void		cursorMoveTo(IlUShort, IlUShort);
    void		cursorBeginningOfLine();
    void		cursorEndOfLine();
    void		cursorDown();
    void		cursorUp();
    void		cursorLeft();
    void		cursorRight();
    void		cursorPageDown();
    void		cursorPageUp();
    void		cursorBeginningOfText();
    void		cursorEndOfText();
    void		cursorEnsureVisible();
    void		cursorKillLine();
    void		cursorYank();
    void		cursorDeleteChar();
    void		cursorBackSpace();
    void		cursorNewLine();
    void		cursorInsertChar(IlUShort);

    void		ensureVisible(const IlvTextLocation&	location,
				      const IlvTransformer*	t = 0);

    virtual IlBoolean	allowToolTip() const;

    // Specific callbacks
    virtual void	cursorMoved();
    virtual void	selectionChanged();
    virtual void	valueChanged();

    IlvDefineCallback(CursorMoved);
    IlvDefineCallback(ScrollerMoved);
    IlvDefineCallback(SelectionChanged);

    inline void		setCursorMovedCallbackName(const IlSymbol* cbName)
			{
			    setCursorMovedCallback((IlSymbol*)cbName);
			}
    inline void		setCursorMovedCallbackName(const IlSymbol* cbName,
						   IlAny arg)
			{
			    setCursorMovedCallback((IlSymbol*)cbName, arg);
			}
    inline void		setScrollerMovedCallbackName(const IlSymbol* cbName)
			{
			    setScrollerMovedCallback((IlSymbol*)cbName);
			}
    inline void		setScrollerMovedCallbackName(const IlSymbol* cbName,
						     IlAny arg)
			{
			    setScrollerMovedCallback((IlSymbol*)cbName, arg);
			}

    // Callbacks
    IlUInt		getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    IlUShort		getDelta() const;
    inline IlUShort	getMaxCharSize() const { return _maxCharSize; }
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetContents(IlvPort*,
					   const IlvTransformer* = 0,
					   const IlvRegion* = 0) const;
    virtual void	drawText(IlvPort*,
				 const IlvTransformer*,
				 const IlvRegion*) const;
    virtual void	drawSelection(IlvPort*,
				      const IlvRect&,
				      const IlvRegion*) const;
    virtual void	drawCursor(IlvPort*,
				   const IlvRect&,
				   const IlvRegion*) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* = 0) const;
    virtual void	getPreferredSize(IlvDim&, IlvDim&) const;
    virtual void	fitToContents(IlvDirection = (IlvDirection)
				      (IlvHorizontal|IlvVertical));
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setPalette(IlvPalette*);

    // Bidi interface
    virtual IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean		setBidiContext(IlvBidiContext*);
    virtual void		changeLayoutAttributes(IlAny, IlAny);
    inline IlvTextBidiExt*	bidiExt() const { return _bidiExt; }
    void		bidiSwitch(IlBoolean, IlBoolean = IlTrue) const;
    void		bidiFix();
    void		logicalKillOneChar(IlBoolean);
    IlShort		visualFromLogical(const IlvTextLocation&) const;
    IlShort		logicalFromVisual(const IlvTextLocation&) const;
    void		internalSetSelection(const IlvTextLocation&,
					     const IlvTextLocation&,
					     IlBoolean);
    void		internalSetCursorLocation(const IlvTextLocation&,
						  IlBoolean);
    inline static IlSymbol*	CursorMovedSymbol() { return _curMovSymbol; }
    inline static IlSymbol*	CurMovSymbol() { return _curMovSymbol; }

    inline static IlSymbol*	SelectionChangedSymbol()
				{
				    return _selChangedSymbol;
				}

    inline
    static IlSymbol*	ValueChangedSymbol() { return _valChangedSymbol; }

    inline
    static IlSymbol*	ScrollerMovedSymbol() { return SBMovSymbol(); }

    static IlSymbol*	_curMovSymbol;
    static IlSymbol*	_selChangedSymbol;
    static IlSymbol*	_valChangedSymbol;

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_textValue;
    static IlSymbol*	_selectedTextValue;
    static IlSymbol*	_editableValue;
    static IlSymbol*	_cursorLocationValue;
    static IlSymbol*	_selectionStartValue;
    static IlSymbol*	_selectionEndValue;
    static IlSymbol*	_valueValue;
    static IlSymbol*	_linesValue;
    static IlSymbol*	_getLineMethod;
    static IlSymbol*	_setLineMethod;
    static IlSymbol*	_addLineMethod;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvText);

protected:
    friend class	_IlvTextBlinkTimer;

    static void		bufferSetLine(const char*);
    static void		bufferNewLine();
    static void		bufferEntry();
    static void		closeBuffer();

    inline IlUShort&	cursorColumn()  { return _cursorLocation._column; }
    inline IlUShort&	cursorLine()	{ return _cursorLocation._line;   }

    IlBoolean		checkCursorLocation();
    IlvDim		getLineW(IlUShort) const;
    IlvDim		getMaxLinesWidth(IlBoolean = IlFalse) const;
    void		computeSize();
    void		internalAddLine(const char*, IlShort i);
    void		internalRemoveLine(IlUShort);
    void		internalRemoveLines(IlUShort, IlUShort);
    void		removeText(const IlvTextLocation&,
				   const IlvTextLocation&);
    virtual IlBoolean	classFocusable() const;

    // Protected event handling
    IlBoolean		iHandleGadgetEvent(IlvEvent&);
    virtual IlBoolean	handleButtonDown(IlvEvent&);
    virtual IlBoolean	handleButtonUp(IlvEvent&);
    virtual IlBoolean	handleButtonDragged(IlvEvent&);
    void		dragText(IlvEvent&);
    void		computeArea(const IlvEvent&);
    void		textButtonDown(IlvEvent&);
    void		textButtonUp(IlvEvent&);
    void		handleSelectionKey(IlvEvent&);

    // Scrollbars
    void		beforeAdjustScrollBarVisibility(const IlvRect &);
    void		afterAdjustScrollBarVisibility(const IlvRect &);
    void		adjustScrollBarValue(IlvScrollBar*, IlvDirection);
    virtual void	scrollBarHasMoved(IlvDirection);
    virtual void	adjustFromScrollBar(const IlvScrollBar*,
					    IlvDirection);

    IlBoolean		iCallCheck(IlUShort);
    IlBoolean		iCallMbCheck(const char*);

    IlBoolean		iCallHandleControl(IlUShort);

    void		ensureVisible(const IlvTextLocation&,
				      IlUShort&,
				      IlvDim&) const;
    IlBoolean		isVisible(const IlvTextLocation&,
				  IlUShort,
				  IlvDim) const;
    void		removeSelection(IlvRegion&,
					IlvBitmap* = 0,
					IlvSystemPort* = 0,
					const IlvTransformer* = 0);
    IlBoolean		ensureVisible(const IlvTextLocation&,
				      IlvRegion&,
				      IlvBitmap* = 0,
				      IlvSystemPort* = 0,
				      const IlvTransformer* = 0);
    void		insertLine(IlvRegion&,
				   IlvBitmap*,
				   const IlvTextLocation&,
				   IlvSystemPort* = 0,
				   const IlvTransformer* = 0);
    void		scrollUp(IlvRegion&,
				 IlvBitmap*,
				 IlvSystemPort* = 0,
				 const IlvTransformer* = 0);
    void		scrollDown(IlvRegion&,
				   IlvBitmap*,
				   IlvSystemPort* = 0,
				   const IlvTransformer* = 0);
    void		scrollTo(IlUShort,
				 IlvRegion&,
				 IlvBitmap*,
				 IlvSystemPort* = 0,
				 const IlvTransformer* = 0);
    void		joinLine(IlvRegion&,
				 IlvBitmap*,
				 IlUShort,
				 IlvSystemPort* = 0,
				 const IlvTransformer* = 0);
    inline IlBoolean	cursorEnsureVisible(IlvRegion& region,
					    IlvBitmap* bitmap = 0,
					    IlvSystemPort* dst = 0,
					    const IlvTransformer* t = 0)
			{
			    return ensureVisible(_cursorLocation,
						 region,
						 bitmap,
						 dst,
						 t);
			}
    void		moveLocationRight(IlvTextLocation&) const;
    void		moveLocationLeft(IlvTextLocation&) const;
    void		moveLocationUp(IlvTextLocation&) const;
    void		moveLocationDown(IlvTextLocation&) const;

    // Multi-byte handling
    IlUShort		countCharacters(const char*, IlShort = -1);
    virtual void	setWcLines(IlUShort,
				   const IlvWChar* const*,
				   const IlUShort*,
				   IlBoolean = IlTrue);

    static IlUShort	_refCount;
    static IlBoolean	_valueChanged;
    // Wipe and yank buffer
    static char**	_buffer;
    static IlUShort	_bufferAllocated;
    static IlUShort	_bufferIndex;
    static IlBoolean	_bufferAdding;

    static IlvText*	_blinkingText;

    IlUShort		_count;
    char**		_labels;
    IlvDim		_xoffset;
    IlUShort		_firstLine;
    IlvTextLocation	_selectionFrom;
    IlvTextLocation	_selectionTo;
    IlBoolean		_showCursor;
    IlvTextLocation	_cursorLocation;
    IlvTextLocation	_initialDragPos;
    char*		_fileName;
    IlBoolean		_modified;

    IlBoolean		_isSelectingWord;
    IlvTextLocation	_wordStart;
    IlvTextLocation	_wordEnd;

    IlvWChar**		_wcLabels;     // Text lines stored as wchar_t*
    IlUShort*		_labelLengths; // Number of characters in text lines
    IlUShort		_maxCharSize;  // Max bytes per char (current locale)

    IlvTextBidiExt*	_bidiExt;

    IlBoolean		_keyDownFlag;

private:
    void		loadFlags();

    IlBoolean		_needsIC;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHTextInteractor : public IlvHGadgetInteractor
{
public:
    virtual IlBoolean	check(IlvText*, IlUShort) = 0;
    virtual IlBoolean	mbCheck(IlvText*, const char*) = 0;
    virtual IlBoolean	handleControl(IlvText*, IlUShort) = 0;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(text);
#if defined(ILVMOTIFLOOK)
#if !defined(__Ilv_Gadgets_Motif_Text_H)
#  include <ilviews/gadgets/motif/text.h>
#endif
#endif
#if defined(ILVWINDOWSLOOK)
#if !defined(__Ilv_Gadgets_Windows_Text_H)
#  include <ilviews/gadgets/windows/text.h>
#endif
#endif
#endif /* !__Ilv_Gadgets_Text_H */
