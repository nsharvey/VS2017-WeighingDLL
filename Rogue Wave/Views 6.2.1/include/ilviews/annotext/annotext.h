// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/annotext.h
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
// Declaration of the IlvAnnoText class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Annotext_H
#define __Ilv_Annotext_Annotext_H

#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif
#if !defined(__Ilv_Gadgets_Scgadget_H)
#  include <ilviews/gadgets/scgadget.h>
#endif
#if !defined(__Ilv_Annotext_Line_H)
#  include <ilviews/annotext/line.h>
#endif
#if !defined(__Ilv_Annotext_Palette_H)
#  include <ilviews/annotext/palette.h>
#endif
#if !defined(__Ilv_Annotext_Rope_H)
#  include <ilviews/annotext/rope.h>
#endif
#if !defined(__Ilv_Annotext_Accels_H)
#  include <ilviews/annotext/accels.h>
#endif
#if !defined(__Ilv_Base_Timer_H)
#  include <ilviews/base/timer.h>
#endif

class IlvATRope;
class IlvATBuffer;
class IlvATFlyingCursor;
class IlvATCursor;
class IlvATStartCursor;
class IlvATEndCursor;
class IlvATInsertionCursor;
class IlvATZone;
class IlvATAccelerator;
class IlvATCursorBlinkTimer;
class IlvATAutoScrollTimer;
class IlvATExtension;
class IlvContainer;

typedef enum IlvATPart
{
    IlvATNoWhere,
    IlvATTextPart,
    IlvATVerticalScrollBarPart,
    IlvATHorizontalScrollBarPart
} _IlvATPart;

// scrollbar flags
#define ILVANNO_VSBFLAG 1
#define ILVANNO_HSBFLAG 2
#define ILVANNO_VSBIFNEEDEDFLAG 4
#define ILVANNO_HSBIFNEEDEDFLAG 8
#define ILVANNO_HASVSB (_sbFlags & ILVANNO_VSBFLAG)
#define ILVANNO_HASHSB (_sbFlags & ILVANNO_HSBFLAG)
#define ILVANNO_HIFNEEDED (_sbFlags & ILVANNO_HSBIFNEEDEDFLAG)
#define ILVANNO_VIFNEEDED (_sbFlags & ILVANNO_VSBIFNEEDEDFLAG)

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvAnnoTextLFHandler
: public IlvObjectLFHandler
{
public:
    IlvAnnoTextLFHandler(IlvLookFeelHandler* lf);

    virtual void	drawFrame(const IlvAnnoText*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	drawBackground(const IlvAnnoText*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const = 0;
    virtual void	drawGadgetContents(const IlvAnnoText*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const = 0;
    virtual IlvPalette*	getTextPalette(const IlvAnnoText*,
				       IlvPalette*) const = 0;
    virtual IlvPalette*	makeDefault(const IlvAnnoText*,
				    const IlvPalette*) const = 0;
};

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvDefaultAnnoTextLFHandler
: public IlvAnnoTextLFHandler {
public:
    IlvDefaultAnnoTextLFHandler(IlvLookFeelHandler* lf)
	: IlvAnnoTextLFHandler(lf)  {}

    virtual void	drawFrame(const IlvAnnoText*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(const IlvAnnoText*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetContents(const IlvAnnoText*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual IlvPalette*	getTextPalette(const IlvAnnoText*,
				       IlvPalette*) const;
    virtual IlvPalette*	makeDefault(const IlvAnnoText*,
				    const IlvPalette*) const;
};

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvAnnoText
: public IlvScrolledGadget
{
public:
    IlvAnnoText(IlvDisplay*    display,
		const IlvRect& rect,
		IlvATPalette*  tpalette,
		IlUShort       thickness = IlvDefaultGadgetThickness);
    ~IlvAnnoText();

    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion* = 0) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetContents(IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    IlBoolean		isEditable() const;
    void		setEditable(IlBoolean value);

    // Inserting text, image, carriage return
    void		insertText(IlvATCursor*	where,
				   const char*	text,
				   IlvATPos	len     = 1,
				   IlvPosition	gravity = IlvLeft);
    void		insertGraphic(IlvATCursor*	where,
				      IlvGraphic*	obj,
				      IlBoolean		owner   = IlFalse,
				      IlvPosition	gravity = IlvLeft);
    void		insertParagraph(IlvATCursor*	where,
					IlvPosition	gravity = IlvLeft);
    void		insertBreak(IlvATCursor*	where,
				    IlvPosition		gravity = IlvLeft);
    void		insertTabulation(IlvATCursor*	where,
					 IlvPosition	gravity = IlvLeft);
    void		insertSeparator(IlvATCursor*	where,
					IlvDim		size    = 2,
					IlFloat		width   = 1,
					IlvPosition	gravity = IlvLeft);
    // Inserting a zone between two cursors
    IlvATZone*		insertZone(IlvATCursor* start,
				   IlvATCursor* end = 0);

    // Copying text between cursors in a buffer
    IlBoolean		getText(IlvATCursor*	start,
				IlvATCursor*	end,
				char*		buffer,
				IlUInt		length,
				IlBoolean	stopAtNewLine = IlFalse) const;
    void		setLines(const char* const*	textLines,
				 IlUInt			count,
				 IlBoolean		copy = IlTrue);
    const char* const*	getLines(IlUInt& count);

    // Deleting text and image (returns IlFalse if deletion is not possible)
    void		deleteText(IlvATCursor*	start,
				   IlvATCursor*	end,
				   IlBoolean	deleteZones = IlFalse);

    // Deleting all text and zones
    void		emptyText();

    // Scrolling functions
    IlBoolean		ensureVisible(IlvATCursor* cursor,
				      IlBoolean = IlFalse);
    IlBoolean		scrollUpLines(IlUShort lines);
    IlBoolean		scrollDownLines(IlUShort lines);
    IlBoolean		scrollUp(IlvDim pos);
    IlBoolean		scrollDown(IlvDim pos);
    void		scrollTo(IlvATCursor* cursor);

    // Getting topmost zone at given point
    IlvATZone*		whichZone(const IlvPoint&	point,
				  const IlvTransformer*	t = 0,
				  IlBoolean		inside = IlTrue) const;

    // compute involved lines and redraw
    void		computeDraw(IlvPort*			dst  = 0,
				    const IlvTransformer*	t = 0,
				    const IlvRegion*		clip = 0,
				    IlvATCursor*		from = 0,
				    IlvATCursor*		to   = 0);
    // Redraws zone WITHOUT recomputing
    void		refreshZone(IlvATZone*		zone,
				    IlvPort*		dst  = 0,
				    const IlvTransformer* t  = 0,
				    const IlvRegion*	clip = 0) const;

    // prints
    void		printContents(IlvPort*			dst,
				      const IlvTransformer&	trans,
				      const IlvRect&		printRect);

    // Shows/hides/moves the insertion cursor
    void		showInsertionCursor(IlBoolean drawAround = IlTrue);
    void		hideInsertionCursor(IlBoolean drawAround = IlTrue);
    IlBoolean		moveInsertionCursorToPoint(const IlvPoint&       point,
						   const IlvTransformer* t=0);

    // Accelerators handling
    void		addAccelerator(IlvATAction	action,
				       IlvEventType	type,
				       IlUShort		data = 0,
				       IlUShort		modifiers = 0,
				       IlAny		userArg = 0,
				       IlUShort		modifiersToIgnore = 0);
    void		addAccelerator(IlvATAccelerator* accel);
    void		removeAccelerator(IlvEventType	type,
					  IlUShort	data      = 0,
					  IlUShort	modifiers = 0);
    void		removeAccelerator(IlvATAccelerator* accel);

    // Input handling
    virtual IlBoolean	check(IlUShort c);

    // Selection handling
    IlBoolean		setSelection(IlvATCursor*	c1,
				     IlvATCursor*	c2,
				     IlBoolean		redraw = IlFalse);
    IlBoolean		getSelection(IlvATCursor* start,
				     IlvATCursor* end) const;
    IlBoolean		isSelectionEmpty() const;
    void		emptySelection(IlBoolean redraw) const;
    virtual void	removeSelection();

    // Minimum length before wrapping a line
    // (annotext uses a horizontal scrollbar if smaller)
    inline IlvDim	getMinWrapWidth() const { return _minWrapWidth; }
    inline void		setMinWrapWidth(IlvDim wrapwidth)
			{
			    _minWrapWidth = wrapwidth;
			}

    ////////////////////////////////////
    // Not documented
    ////////////////////////////////////
    inline
    IlvATStartCursor*	getFirstRope()  const { return _start; }
    inline
    IlvATEndCursor*	getLastRope()   const { return _end; }
    inline IlvATBuffer*	getTextBuffer() const { return _textBuffer; }
    inline IlvDim	getWrapWidth()  const { return _wrapWidth; }
    inline void		setWrapWidth(IlvDim wrapW) { _wrapWidth = wrapW; }
    inline IlvDim	getScrollIncrement() const { return _scrollIncrement; }
    inline void		setScrollIncrement(IlvDim l) { _scrollIncrement = l; }
    inline IlvDim	getMaxLineLength() const { return _maxLineLength; }
    inline void		setMaxLineLength(IlvDim l) { _maxLineLength = l; }
    inline IlvDim	getFirstOffset() const { return _firstOffset; }
    inline void		setLastOffset(IlvDim offset) { _lastOffset = offset; }
    inline IlvDim	getLastOffset() const { return _lastOffset; }
    inline void		setFirstOffset(IlvDim val) { _firstOffset = val; }
    inline
    IlvATPalette*	getTextPalette() const { return _tpalette; }
    inline void		setTextPalette(IlvATPalette* p) { _tpalette = p; }
    inline IlvATZone*	getGrabZone() const { return _grabZone;   }
    inline void		setGrabZone(IlvATZone* zone) { _grabZone = zone; }
    inline
    IlvATGraphicRope*	getFocusRope() const { return _focusRope;  }
    inline void		setFocusRope(IlvATGraphicRope* rope)
			{
			    _focusRope = rope;
			}
    inline
    IlvATGraphicRope*	getGrabRope() const { return _grabRope;   }
    inline void		setGrabRope(IlvATGraphicRope* rope)
			{
			    _grabRope = rope;
			}
    inline IlvATInsertionCursor*	getInsertionCursor() const
					{
					    return _insert;
					}

    // inline IlList*	getParList()            const { return _parlist;    }
    inline IlvDim	getTextHeight()         const { return _textHeight; }
    inline void		setTextHeight(IlvDim h)       { _textHeight = h;    }

    // vertical offset when scrolled (non visible height)
    inline IlvDim	getTextPos()            const { return _textPos;    }
    inline void		setTextPos(IlvDim h)          { _textPos = h;       }
    IlvDim		computeScrolledOffset();

    // non visible height of the last drawn line
    IlvDim		computeLastOffset();

    inline IlvDim	getOffset()             const { return _xoffset;    }
    void		adjustOffset();
    void		setOffset(IlvDim, IlBoolean redraw = IlTrue);

    inline IlShort	lmarg() const
			{
			    return (IlShort)(_thickness + _leftMargin);
			}
    inline IlShort	rmarg() const
			{
			    return (IlShort)(_thickness + _rightMargin);
			}
    inline IlShort	tmarg() const
			{
			    return (IlShort)(_thickness + _topMargin);
			}
    inline IlShort	bmarg() const
			{
			    return (IlShort)(_thickness + _bottomMargin);
			}
    IlvDim		getVisibleHeight() const;
    IlvATLine*		getLastDrawnLine() const;
    // inline IlBoolean	isShadowShown()          const { return _showShadow;  }
    // inline void	showShadow(IlBoolean v)        { _showShadow = v;     }
    inline char*	getClipboardBuffer()     const { return _clipboard;   }
    inline void		setClipboardBuffer(char* buff) { _clipboard = buff;   }
    inline IlUInt	getClipboardBufferLength() const
			{
			    return _clipboardLength;
			}
    inline void		setClipboardBufferLength(IlInt len)
			{
			    _clipboardLength = len;
			}

    void		setWordSeparator(IlUShort c);
    void		setWordSeparator(const char* seps);
    void		unsetWordSeparator(IlUShort c);
    IlBoolean		isWordSeparator(IlUShort c) const;
    IlBoolean		locateWord(IlvATCursor*		pos,
				   IlvATFlyingCursor*	start,
				   IlvATFlyingCursor*	end);

    IlBoolean		shortCut(IlvEvent& event);
    const char*		getDefaultInteractor() const;
    virtual IlBoolean	classFocusable() const;

    // Redraw the insertion cursor area
    void		drawInsertionCursor(IlvPort* dst,
					    const IlvTransformer* t    = 0,
					    const IlvRegion* clip = 0) const;

    // Focus management
    void		sendFocusIn(IlvATGraphicRope* );
    void		sendFocusOut(IlvATGraphicRope*);
    void		objectMouseEnter(IlvATGraphicRope*);
    void		objectMouseLeave(IlvATGraphicRope*);
    void		setFocus(IlvATGraphicRope*, IlBoolean redraw);
    virtual void	drawFocus(IlvPort*		dst,
				  const IlvPalette*	palette,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0) const;
    // Graphic standard methods
    void		applyTransform(const IlvTransformer* t);
    void		setPalette(IlvPalette* palette);
    void		setThickness(IlUShort t);

    // Draw from cursor to cursor,
    void		draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvATCursor*	from,
			     IlvATCursor*	to,
			     IlBoolean		scrollBars = IlFalse) const;
    void		drawInBBox(IlvPort*		dst,
				   const IlvTransformer* t,
				   IlvRegion*		clip,
				   IlvATCursor*		from,
				   IlvATCursor*		to,
				   IlvRect		bbox) const;

    // Draw line from cursor to cursor,
    void		drawLine(IlvPort*		dst,
				 IlInt&			height,
				 IlvATLine*		startLine,
				 const IlvTransformer*	t    = 0,
				 const IlvRegion*	clip = 0,
				 IlvATCursor*		from = 0,
				 IlvATCursor*		to   = 0) const;
    // Draw one rope
    void		drawRope(IlvPort*		dst,
				 const IlvTransformer*	t,
				 const IlvRegion*	clip,
				 IlvATRope*		rope) const;

    IlvATTextRope*	mergeTextRope(IlvATTextRope*	first,
				      IlvATTextRope*	second);

    // Getting line at given point
    IlvATLine*		whichLine(const IlvPoint&,
				  const IlvTransformer*	t = 0) const;
    IlvATRope*		whichRope(const IlvPoint&,
				  const IlvTransformer*	t      = 0,
				  IlBoolean		inside = IlTrue) const;

    // Scrollbar management
    void		scrollHorizontal(IlInt value);
    void		adjustWrapWidth(const IlvTransformer* t = 0);
    void		getInternalBBox(IlvRect&		rect,
					const IlvTransformer*	t = 0) const;

    // inserted graphics with rectangle view
    void		hideAllVisibleViewRectangles();
    void		showAllVisibleViewRectangles();

    // Computing line and wrap unit lengths
    void		computeLines();
    void		computeHeight();
    void		computeMaxLineLength(IlvATLine* lmax = 0);

    // Comparing two cursors
    inline IlBoolean	isBefore(const IlvATRope*	rope1,
				 const IlvATRope*	rope2)
			{
			    return rope1->isBefore(rope2);
			}

    // Event handling
    virtual IlBoolean	handleGadgetEvent(IlvEvent&);
    virtual IlBoolean	handleZone(IlvEvent&,
				   IlBoolean positionFocus = IlFalse);
    virtual IlBoolean	handleAnnoEvent(IlvEvent&);
    virtual IlBoolean	zoneDispatchEvent(IlvEvent&);
    virtual IlBoolean	handleSpecialKey(IlvEvent&);
    virtual IlBoolean	handleControl(IlUShort ch, IlvEvent* event = 0);
    virtual IlBoolean	handleAltKey(IlUShort ch);
    void		handleSelectionKey(IlvEvent& event);

    virtual void	killRight(IlvEvent* event = 0);
    virtual void	killLeft(IlvEvent* event = 0);
    IlBoolean		textButtonDown(IlvEvent& event);
    IlBoolean		textButtonUp(IlvEvent& event);
    IlBoolean		textDrag(IlvEvent& event);
    IlBoolean		textKeyDown(IlvEvent& event);

    // Input handling
    IlUShort		isValid(IlUShort ch) const;
    void		cursorAfterInsert(IlvATCursor* from);
    void		cursorInsertChar(IlUShort c);
    void		cursorInsertGraphic(IlvGraphic*,
					    IlBoolean owner = IlFalse);
    void		cursorInsertTabulation();
    void		cursorInsertSeparator(IlvDim	size = 2,
					      IlFloat	width = 1);
    void		cursorInsertParagraph();
    void		cursorInsertBreak();
    void		cursorBackSpace();
    void		cursorDelete();
    void		cursorPageUp();
    void		cursorPageDown();
    IlvATLine*		cursorUp();
    IlvATLine*		cursorDown();
    IlvATLine*		liftInsertionCursor(IlvOrientation towards);
    virtual void	cursorKillLine(IlBoolean deleteZones = IlTrue);

    // cut and paste
    void		copyToClipboard();
    void		pasteFromClipboard(IlBoolean redraw);
    void		cutToClipboard(IlBoolean redraw);
    virtual void	insertClipboardText(IlvATCursor* where,
					    const char*	text,
					    IlvATPos	len     = 1,
					    IlvPosition	gravity = IlvLeft);

    IlBoolean		moveCursorToPoint(const IlvPoint&	point,
					  const IlvTransformer*	t,
					  IlvATFlyingCursor&	fc) const;

    // Specific callbacks
    virtual void	cursorMoved();
    inline 
    IlvGraphicCallback	getCursorMovedCallback() const
			{
			    return getCallback(CurMovSymbol());
			}
    inline IlSymbol*	getCursorMovedCallbackName() const
			{
			    return getCallbackName(CurMovSymbol());
			}
    inline void		setCursorMovedCallback(IlvGraphicCallback cb)
			{
			    setCallback(CurMovSymbol(), cb);
			}
    inline void		setCursorMovedCallback(const IlSymbol* cbName)
			{
			    setCallback(CurMovSymbol(), cbName);
			}
    inline void		setCursorMovedCallbackName(const IlSymbol* cbName)
			{
			    setCursorMovedCallback(cbName);
			}
    inline void		addCursorMovedCallback(IlvGraphicCallback cb)
			{
			    addCallback(CurMovSymbol(), cb);
			}
    inline void		addCursorMovedCallback(const IlSymbol* cbName)
			{
			    addCallback(CurMovSymbol(), cbName);
			}
    inline void		setCursorMovedCallback(IlvGraphicCallback	cb,
					       IlAny			arg)
			{
			    setCallback(CurMovSymbol(), cb, arg);
			}
    inline void		setCursorMovedCallback(const IlSymbol*	cbName,
					       IlAny		arg)
			{
			    setCallback(CurMovSymbol(), cbName, arg);
			}
    inline void		setCursorMovedCallbackName(const IlSymbol*	cbName,
						   IlAny		arg)
			{
			    setCursorMovedCallback(cbName, arg);
			}
    inline void		addCursorMovedCallback(IlvGraphicCallback	cb,
					       IlAny			arg)
			{
			    addCallback(CurMovSymbol(), cb, arg);
			}
    inline void		addCursorMovedCallback(const IlSymbol* cbName,
					       IlAny            arg)
			{
			    addCallback(CurMovSymbol(), cbName, arg);
			}
    inline
    IlvGraphicCallback	getScrollerMovedCallback() const
			{
			    return getCallback(SBMovSymbol());
			}
    inline IlSymbol*	getScrollerMovedCallbackName() const
			{
			    return getCallbackName(SBMovSymbol());
			}
    inline void		setScrollerMovedCallback(IlvGraphicCallback cb)
			{
			    setCallback(SBMovSymbol(), cb);
			}
    inline void		setScrollerMovedCallback(const IlSymbol* cbName)
			{
			    setCallback(SBMovSymbol(), cbName);
			}
    inline void		setScrollerMovedCallbackName(const IlSymbol* cbName)
			{
			    setScrollerMovedCallback(cbName);
			}
    inline void		addScrollerMovedCallback(IlvGraphicCallback cb)
			{
			    addCallback(SBMovSymbol(), cb);
			}
    inline void		addScrollerMovedCallback(const IlSymbol* cbName)
			{
			    addCallback(SBMovSymbol(), cbName);
			}
    inline void		setScrollerMovedCallback(IlvGraphicCallback	cb,
						 IlAny			arg)
			{
			    setCallback(SBMovSymbol(), cb, arg);
			}
    inline void		setScrollerMovedCallback(const IlSymbol*	cbName,
						 IlAny			arg)
			{
			    setCallback(SBMovSymbol(), cbName, arg);
			}
    inline void		setScrollerMovedCallbackName(const IlSymbol*	cbName,
						     IlAny		arg)
			{
			    setScrollerMovedCallback(cbName, arg);
			}
    inline void		addScrollerMovedCallback(IlvGraphicCallback	cb,
						 IlAny			arg)
			{
			    addCallback(SBMovSymbol(), cb, arg);
			}
    inline void		addScrollerMovedCallback(const IlSymbol*	cbName,
						 IlAny			arg)
			{
			    addCallback(SBMovSymbol(), cbName, arg);
			}

    //    static IlvATPart	_area;
    static IlSymbol*	CurMovSymbol() { return _curMovSymbol; }
    static IlSymbol*	_curMovSymbol;

    // Line Table Management
    // accessors
    char*		getLineText(IlvATLine* whichLine, IlUInt& length);
    inline IlUShort	getNbLines()          const { return _nbLines;      }
    inline void		setNbLines(IlUShort num)    { _nbLines = num;       }
    inline IlvATLine*	getFirstLine()        const { return _firstLine;    }
    inline void		setFirstLine(IlvATLine* line) { _firstLine = line;  }
    inline IlvATLine*	getLastLine()         const { return _lastLine;     }
    inline void		setLastLine(IlvATLine* num) { _lastLine = num;      }
    // inline IlvATLine* getFirstPar()         const { return _firstpar; }
    // inline void	setFirstPar(IlvATLine* num) { _firstpar = num;      }
    // inline IlvATLine* getFirstGoodLine()  const { return _firstgoodline; }
    // inline void	setFirstGoodLine(IlvATLine* num)
    //			{
    //			    _firstgoodline = num;
    //			}
    // inline IlvATLine* getLastGoodLine()    const { return _lastgoodline; }
    // inline void	setLastGoodLine(IlvATLine* num)
    //			{
    //			    _lastgoodline = num;
    //			}
    inline IlvATLine*	getFirstDrawnLine() const { return _firstDrawnLine; }
    inline void		setFirstDrawnLine(IlvATLine* line)
    {
	_firstDrawnLine = line;
    }
    inline IlvATLine*	getATLine(const IlvATLine*) const { return 0; }
    // list management
    IlvATLine*		insertLine(IlvATLine* afterline);
    void		removeLine(IlvATLine* line);
    // computing lines geometry
    IlvATLine*		computeLines(IlvATLine*	start,
				     IlBoolean	global,
				     IlvATLine*	end = 0);
    IlvATLine*		garbageUnusedLines(IlvATLine*	end,
					   IlvATLine*	currentLine,
					   IlvATCursor*	cutter,
					   IlvATRope*&	searchrope,
					   IlBoolean&	pastend,
					   IlBoolean&	stopok,
					   IlvDim&	oldHeight);
    IlvATLine*		adjustLineComputing(IlvATCursor*	from,
					    IlvATCursor*	to = 0);
    IlBoolean		adjustFirstDrawnLineAndOffset();

    // selection management
    inline IlBoolean	isSelecting()           const { return _isSelecting;}
    inline void		setSelecting(IlBoolean b)     { _isSelecting = b;   }
    inline IlvATCursor*	getSelectingCursor()    const { return _selBound;   }
    inline IlvATCursor*	getOldSelectingCursor() const { return _selBoundOld;}
    inline void		swapSelectingCursors()
			{
			    IlvATCursor* tmp = _selBound;
			    _selBound        = _selBoundOld;
			    _selBoundOld     = tmp;
			}

    // look management
    IlvPalette*		getCurrentLookPalette() const;
    IlBoolean		useTextDefaultColors(IlvPalette*) const;
    IlvPalette*		getWDefault(IlvPalette* ropePalette = 0) const;

    virtual void	traceRopes(IlvATRope* start = 0, IlvATRope* end = 0);
    virtual const char*	traceRopeType(IlvATRopeType	type,
				      IlvATRope*	rope = 0) const;

    void		setCursorBlink(IlBoolean on);
    inline IlUInt	getCursorBlinkRate() const {return _cursorBlinkRate;}
    inline IlUInt	getAutoScrollRate()  const {return _autoScrollRate; }
    void		setCursorBlinkRate(IlUInt rate);
    void		setAutoScrollRate(IlUInt rate);

    // Accessors
    DeclareGraphicAccessors();

    DeclareTypeInfo();
    DeclareIOConstructors(IlvAnnoText);

    // Input Method interaction
    virtual IlBoolean	needsInputContext() const;
    virtual void	setNeedsInputContext(IlBoolean val);

    inline 
    IlvATExtension*	getExtension() const { return _extension; }
protected:
    void		changeOffset(IlvDim);
    IlBoolean		moveCursorUp();
    IlBoolean		moveCursorDown();
    void		internalInitText();

    // Scrolling
    virtual void	adjustScrollBarValue(IlvScrollBar*	sb,
					     IlvDirection	dir);
    virtual void	adjustFromScrollBar(const IlvScrollBar*	sb,
					    IlvDirection	dir);
    virtual void	beforeAdjustScrollBarVisibility(const IlvRect&);
    virtual void	afterAdjustScrollBarVisibility(const IlvRect&);

    IlvDim		_xoffset;      // h-scroll offset, relative to bbox.
    // IlBoolean	_showShadow;

    IlvATStartCursor*	_start;
    IlvATEndCursor*	_end;
    IlBoolean		_editable;

    IlvDim		_firstOffset;    // h of 1st drawn line hidden part
    IlvDim		_lastOffset;     // h of last drawn line hidden part
    IlvDim		_wrapWidth;
    // The Line Table
    IlUShort		_nbLines;        // total number of lines in table
    IlvATLine*		_firstLine;      // 1st line
    IlvATLine*		_lastLine;       // last line
    // IlvATLine*	_firstpar;       // 1st line of 1st displayed parag
    IlvATLine*		_firstDrawnLine; // 1st line actually displayed
    // IlvATLine*	_firstgoodline;  // 1st line correct in table
    // IlvATLine*	_lastgoodline;   // last line correct in table;

    IlvATBuffer*	_textBuffer;
    IlvATPalette*	_tpalette;
    IlvATInsertionCursor* _insert;
    IlvATZone*		_grabZone;
    IlvATGraphicRope*	_grabRope;
    IlvATGraphicRope*	_focusRope;
    IlvGadget*		_graphicButtonDown;

    // IlList*		_parlist;
    IlvDim		_textHeight;
    IlvDim		_textPos;
    IlList		_accelerators;
    IlvDim		_scrollIncrement;
    IlvDim		_maxLineLength;
    IlvDim		_minWrapWidth;

    IlvPalette*		_wDefault;

    // The selection
    IlvATCursor*	_selStart;
    IlvATCursor*	_selEnd;
    IlvATCursor*	_selBoundOld;    // used for selection interactions
    IlvATCursor*	_selBound;       // used for selection interactions
    IlvATCursor*	_selPin;
    IlBoolean		_isSelecting;
    IlUInt		_clipboardLength;
    char*		_clipboard;      // buffer for external clipboard
    IlBoolean		_separators[256];

    // Incremental selection
    IlInt		_iSelLevel;
    // IlvATCursor*	_iSelStart;
    // IlvATCursor*	_iSelEnd;

    // friend class IlvATCursorBlinkTimer;
    // friend class IlvATAutoScrollTimer;
    // friend class IlvATExtension;

    IlvATCursorBlinkTimer* _cursorBlinkTimer;
    IlUInt		_cursorBlinkRate;  // in milliseconds
    IlUInt		_cursorBlinkState;

    IlvATAutoScrollTimer* _autoScrollTimer;
    IlUInt		_autoScrollRate;   // in milliseconds

    IlBoolean		_needsIC;
    IlvATExtension*	_extension;

    // -- wipe and yank buffer --
    static char**	_buffer;
    static IlUShort	_bufferAllocated;
    static IlUShort	_bufferIndex;
    static IlBoolean	_bufferAdding;
    static void		bufferSetLine(const char*);
    static void		bufferNewLine();
    static void		bufferEntry();
    static void		closeBuffer();

    void		makePalette(IlvPalette* ropePal = 0);
private:
    void		insertTextPiece(IlvATCursor*	cursor,
					const char*	text,
					IlvATPos	len,
					IlvPosition	gravity);
};

// --------------------------------------------------------------------------
class IlvATCursorBlinkTimer
: public IlvTimer {
public:
    IlvATCursorBlinkTimer(IlvAnnoText* atext);
    virtual void	doIt();
    IlvAnnoText*	_atext;
};

// --------------------------------------------------------------------------
class IlvATAutoScrollTimer
: public IlvTimer {
public:
    IlvATAutoScrollTimer(IlvAnnoText* atext);
    virtual void	doIt();
    IlvAnnoText*	_atext;
};

ILVATMODULEINIT(annotext);
#endif /* !__Ilv_Annotext_Annotext_H */
