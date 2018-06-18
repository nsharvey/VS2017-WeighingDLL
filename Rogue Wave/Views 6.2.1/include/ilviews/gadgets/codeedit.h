// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/codeedit.h
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
// Declaration of the IlvCodeEditor class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Codeedit_H
#define __Ilv_Gadgets_Codeedit_H

#if !defined(__Ilv_Gadgets_Scgadget_H)
#include <ilviews/gadgets/scgadget.h>
#endif
#if !defined(__Il_Pathname_H)
#include <ilog/pathname.h>
#endif
#if !defined(__Il_Shrptr_H)
#include <ilog/shrptr.h>
#endif

class IlvCodeEditor;
class IlvMenuItem;
class IlvTextField;

// Forward declaration of internal classes
class IlvCEdtParser;
class IlvCEdtMarker;
class IlvCEdtLine;
class IlvCEdtText;
class IlvCEdtObserver;
class IlvCEdtCommandFactory;
class IlvCEdtCommandProcessor;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvCodeEditor : public IlvScrolledGadget
{
public:
    typedef IlBoolean (IlvCodeEditor::*Action)(void);

    enum TokenType {
	TextToken = 0,
	CommentToken = 1,
	KeywordToken = 2,
	VariableToken = 3,
	FunctionToken = 4,
	ScriptToken = 5
    };

    class ILVADVGDTEXPORTED Location
    {
    public:
	Location(IlInt line = -1, IlInt column = -1)
	: _line(line),
	  _column(column)
	{}
	inline void	set(IlInt line, IlInt column)
			{
			    _line = (line < 0) ? -1 : line;
			    _column = (column < 0) ? -1 : column;
			}
	inline void	set(const Location& source)
			{
			    _line = source._line;
			    _column = source._column;
			}
	inline IlInt	getLine() const { return _line; }
	inline IlInt	getColumn() const { return _column; }
	inline void	setLine(IlInt line)
			{
			    _line = (line < 0) ? -1 : line;
			}
	inline void	setColumn(IlInt col)
			{
			    _column = (col < 0) ? -1 : col;
			}
	inline
	IlBoolean	isDefault() const
			{
			    return (_line == -1) && (_column == -1);
			}
	inline
	IlBoolean operator>=(const Location& other) const
			{
			    return ((_line > other._line)
				    ? IlTrue
				    : ((_line == other._line) &&
				       (_column >= other._column)));
			}
	inline
	IlBoolean operator<(const Location& other) const
			{
			    return !(*this  >= other);
			}
	inline
	IlBoolean operator<=(const Location& other) const
			{
			    return ((_line < other._line)
				    ? IlvTrue
				    : ((_line == other._line) &&
				       (_column <= other._column)));
			}
	inline
	IlBoolean operator>(const Location& other) const
			{
			    return !(*this <= other);
			}

	inline
	IlBoolean operator==(const Location& source) const
			{
			    return (_line == source._line)
				&& (_column == source._column);
			}
	inline
	IlBoolean operator!=(const Location& source) const
			{
			    return !(*this == source);
			}
    private:
	IlInt	_line;
	IlInt	_column;
    };

    // Internal
    class ILVADVGDTEXPORTED Decorator
    {
    public:
	virtual ~Decorator();

	virtual void		setFont(IlvFont* font) = 0;
	virtual IlvColor*	getBackground() const = 0;
	virtual void		setBackground(IlvColor* col) = 0;
	virtual IlvColor*	getForeground() const = 0;
	virtual void		setForeground(IlvColor* col) = 0;
    };

    class ILVADVGDTEXPORTED Style
    {
    public:
	Style(Decorator* d);
	Style(const Style& style);
	~Style();

	Style&			operator=(const Style& sty);
	Decorator*		getDecorator() const;

    private:
	class			Internal;
	Internal*		_internal;
    };

    class ILVADVGDTEXPORTED StyleSheet
    {
    public:
	StyleSheet(IlvDisplay* display,
		   IlBoolean syntaxHighlight = IlTrue,
		   IlBoolean colorizeErrorLine = IlTrue,
		   IlvTextField* miniBuff = 0);
	StyleSheet(const StyleSheet& original);
	virtual ~StyleSheet();

	static
	StyleSheet*	MakeDefault(IlvDisplay*, IlvTextField* = 0);
	int operator=(const StyleSheet& original);
	void		insertStyle(int id, Style style);
	void		add(int id, const Style& style);
	IlBoolean	exist(int id) const;
	const Style&	get(int id) const;
	Style&		get(int id);
	Decorator*	getDecorator(int id);

	void		stdPalette(IlvPalette* pal);
	void		errPalette(IlvPalette* pal);
	void		selPalette(IlvPalette* pal);
	void		mrgPalette(IlvPalette* pal);
	IlvPalette*	stdPalette() const;
	IlvPalette*	errPalette() const;
	IlvPalette*	selPalette() const;
	IlvPalette*	mrgPalette() const;
	int		getTabSize() const;
	void		setTabSize(IlInt tabSize);
	IlBoolean	getTabAsBlanks() const;
	void		setTabAsBlanks(IlBoolean tabAsBlanks);
	IlvFont*	getEditorFont() const;
	void		setEditorFont(IlvFont* font);
	void		setEditorBackground(IlvColor* back);
	IlBoolean	colorizeErrorLine() const;
	void		colorizeErrorLine(IlBoolean b);
	IlBoolean	tabulationManagement() const;
	void		variableColoring(IlBoolean b);
	IlBoolean	variableColoring() const;
	IlBoolean	braceHighLight() const;
	void		setBraceHighLight(IlBoolean b);
	void		setSyntaxHighlight(IlBoolean on);
	IlBoolean	syntaxHighLight() const;
	void		setAutoIndent(IlBoolean b);
	IlBoolean	isAutoIndent() const;
	IlvTextField*	getBuffer() const;

    private:
	class		Internal;
	Internal*	_internal;

	void		copy(const StyleSheet& orig);
    };

    // Bindings
    class ILVADVGDTEXPORTED Binding
    {
    public:
	enum Mode { MSVCMode, EmacsMode };
	enum Accelerator {
	    UndoAccelerator,
	    RedoAccelerator,
	    KillLineAccelerator,
	    CutAccelerator,
	    CopyAccelerator,
	    PasteAccelerator,
	    GotoAccelerator,
	    SearchAccelerator,
	    ReplaceAccelerator,
	    FindNextAccelerator,
	    FindPreviousAccelerator,
	    RunAccelerator,
	    AbortAccelerator,
	    NextAccelerator,
	    SaveAccelerator,
	    QuitAccelerator,
	    NewAccelerator,
	    OpenAccelerator,
	    SelectAllAccelerator,
	    BreakPointAccelerator,
	    SaveAllAccelerator,
	    KillBufferAccelerator,
	    CompleteWordAccelerator,
	    SaveAsAccelerator,
	    RecenterAccelerator
	};
	virtual ~Binding();
	inline Mode	getMode() const { return _mode; }
	virtual
	IlBoolean	getAccelerator(Accelerator accelerator,
				       char* keyCode,
				       IlvEventType& type,
				       IlUShort& data,
				       IlUShort& mods) const = 0;
    protected:
	Mode		_mode;
    };

    // Triggers
    class ILVADVGDTEXPORTED Trigger
    {
    public:
	virtual ~Trigger();
	virtual IlBoolean	action() = 0;

    protected :
	Trigger() {}
    };

    // Observers
    class ILVADVGDTEXPORTED Observer
    {
    public:
	virtual ~Observer();
	virtual void	update(const IlvCodeEditor& editor,
			       IlBoolean redraw) = 0;

    protected:
	Observer() {}
    };
    class ILVADVGDTEXPORTED ContentChangedObserver : public Observer
    {
    public:
	ContentChangedObserver() : Observer() {}
    };

    class ILVADVGDTEXPORTED CursorMovedObserver : public Observer
    {
    public:
	CursorMovedObserver() : Observer() {}
    };

    class ILVADVGDTEXPORTED SelectionChangedObserver : public Observer
    {
    public:
	SelectionChangedObserver() : Observer() {}
    };

    class ILVADVGDTEXPORTED CommandPerformedObserver : public Observer
    {
    public:
	CommandPerformedObserver() : Observer() {}
    };

    // Parsing 
    class ILVADVGDTEXPORTED Parser
    {
    public:
	virtual ~Parser();
	virtual Parser*	clone() const = 0;
	void		associate(const char* ext);
	static Parser*	CreateParser(const char*);

	static Parser*	CreateDefaultParser();
	static Parser* CreateCPPParser();
	static Parser* CreateJavaParser();
	static Parser* CreateJavaScriptParser();
	static Parser* CreateHTMLParser();
	static Parser* CreateMakefileParser();
    };

public:
    IlvCodeEditor(IlvDisplay* display,
		  const IlvRect& rect,
		  IlUShort thickness = IlvDefaultGadgetThickness,
		  Binding::Mode mode = Binding::MSVCMode,
		  StyleSheet* sheet = 0);
    IlvCodeEditor(IlvDisplay* display,
		  const IlvRect& rect,	// bounding box
		  const char* text,	// whole text to split in lines
		  IlUShort thickness,	// window border size
		  StyleSheet* sheet,	// style sheet for parameters
		  IlvDim marginWidth,	// margin width for symbols
		  Binding::Mode mode,
		  Parser* parser = 0);  // parser for syntax coloring
    virtual ~IlvCodeEditor();

    void		setMarker(IlvCEdtMarker& marker, IlInt line);
    void		removeMarker(IlvCEdtMarker& marker, IlInt line);
    void		removeMarkers(IlInt line = -1);

    // ------------------------------------------------------------
    // Cursor management
    const Location&	getCursorLocation() const;
    void		setCursorLocation(const Location& loc);
    void		setCursorColumn(IlInt column);
    IlBoolean		ensureCursorVisible(IlBoolean reDraw = IlTrue);

    IlBoolean		isCursorVisible() const { return _cursorVisible; }
    IlInt		getCursorLine() const;
    IlInt		getCursorColumn() const;
    void		setCursorLocation(IlInt line, IlInt column);

    // -------------------------------------------------------------
    // Undo/Redo
    IlBoolean		undo();
    IlBoolean		redo();
    void		blockUndoRedo();
    IlBoolean		isUndoable() const;
    IlBoolean		isRedoable() const;
    void		getUndoCommandLabel(IlString& l) const;
    void		getRedoCommandLabel(IlString& l) const;

    // -------------------------------------------------------------
    // Accessors
    void		setEditable(IlBoolean mode);
    IlBoolean		isReadOnly() const;

    // -------------------------------------------------------------
    // Selection
    IlBoolean		hasSelection() const;
    IlBoolean		selectAll();
    IlBoolean		setSelection(IlInt startOffset, IlInt endOffset);
    char*		getSelection() const;
    char*		getSelectedText() const { return getSelection(); }
    IlBoolean		isMultilineSelection() const;
    Location		getSelectionStart() const;
    IlInt		getSelectionStartLine() const;
    IlInt		getSelectionStartColumn() const;
    Location		getSelectionEnd() const;
    IlInt		getSelectionEndLine() const;
    IlInt		getSelectionEndColumn() const;
    void		getSelection(Location& from, Location& to) const;

    // For Emacs mode only
    IlBoolean		setMark();
    // For Emacs mode only on NT with Views 3.1.1 bug
    IlBoolean		setMarkForgetNextBlank();
    // For Emacs mode only
    void		unsetMark();
    IlBoolean		isMark() const;
    Binding::Mode	getBindingMode() const;
    void		setBindingMode(Binding::Mode mode,
				       IlvTextField* b = 0);

    // -------------------------------------------------------------
    // Comment
    IlBoolean		commentRegion();
    IlBoolean		killComment();
    // -------------------------------------------------------------
    // Find/Replace/GoTo
    IlBoolean		gotoLine(IlInt line);
    void		gotoEnd();
    IlBoolean		find(IlBoolean forwardDir,
			     IlBoolean limited,
			     IlBoolean caseSensitive,
			     IlBoolean wholeWord,
			     const char* pattern,
			     Location from,
			     Location to,
			     IlBoolean s = IlTrue);
    // Start and end location reduced by 1 in delegation
    inline IlBoolean	find(IlBoolean forwardDir,
			     IlBoolean limited,
			     IlBoolean caseSens,
			     IlBoolean wholeWord,
			     const char* pattern,
			     IlInt firstLine,
			     IlInt firstCol,
			     IlInt endLine,
			     IlInt endCol)
			{
			    return find(forwardDir,
					limited,
					caseSens,
					wholeWord,
					pattern,
					Location(firstLine - 1, firstCol - 1), 
					Location(endLine - 1, endCol - 1));
			}
    void		replaceSelection(const char* replacement,
					 IlBoolean autoRedraw,
					 IlBoolean forwardDir);
    void		setLine(IlInt line, const char* text);

    // =====================================================================
    //                       Text handling
    // ======================================================================
    void		insertText(const char* text,
				   IlInt line,
				   IlInt column,
				   IlBoolean reDraw = IlFalse);
    void		addText(const char* text,
				IlInt line,
				IlBoolean redraw = IlFalse);
    IlInt		getNumberOfLines() const;
    IlInt		getLineLength(IlInt l) const;
    IlvCEdtLine*	getLine(IlInt l) const;

    void		insertTextReversible(const char* text,
					     IlInt line,
					     IlInt column,
					     IlBoolean reDraw);
    void		loadText(const char* text);
    IlBoolean		loadFile(const IlPathName& filePath,
				 IlBoolean redraw = IlTrue);
    IlBoolean		readText(const char* filename)
			{
			    return loadFile(IlPathName(filename));
			}

    IlBoolean		readText(IL_STDPREF istream& is);
    void		setText(const char* text);
    void		setLines(const char* const* ls, IlInt count);
    void		appendText(const char* text);
    char*		getText(IlBoolean blanks);
    inline
    IlvCEdtText*	getText() const { return _text; };
    inline StyleSheet*	getStyleSheet() { return _sheet; };

    IlBoolean		isEditable() const;
    // Destroy all lines and release string memory pool to system
    void		resetAll();

    // ======================================================================
    // Brace and syntax highlighting
    // ======================================================================
    IlBoolean		syntaxHighLight() const;
    void		stopBraceHighLighting();
    IlBoolean		braceHighLight() const;

    // -------------------------------------------------------------
    // Clipboard Management
    IlBoolean		appendToClipBoard();
    IlBoolean		copyToClipBoard() const;
    IlBoolean		cutToClipBoard();
    IlBoolean		cutLineToClipBoard();
    IlBoolean		pasteFromClipBoard();

    // -------------------------------------------------------------
    // Automatic word completion
    IlBoolean		completeWord();
    void		locateWord(const Location& at,
				   Location& start,
				   Location& end);

    // -------------------------------------------------------------
    // Need for saving management
    IlBoolean		isSaveNeeded() const;

    void		resetSaveNeeded();

    // -------------------------------------------------------------
    // Style sheet
    void		propagateSheet(const StyleSheet* s = 0);

    /*
     *
     */
    inline Binding*	getCommandBindings() const { return _binding; }

    void		setCommandBindings(Binding* binding,
					   IlBoolean destroy = IlFalse);
    void		setCommandBindings(Binding::Mode m,
					   IlBoolean destroy = IlFalse,
					   IlvTextField* miniBuff = 0);

    inline StyleSheet*	getStyleSheet () const { return _sheet; }
    void		setStyleSheet(StyleSheet* sheet,
				      IlBoolean destroy = IlFalse);

    // -------------------------------------------------------------
    // Observer mechanism
    void		clearEditSignal();
    // Observers mechanism
    ContentChangedObserver& getContentChangedObserver() const;
    void		setContentChangedObserver(ContentChangedObserver&);
    CursorMovedObserver& getCursorMovedObserver() const;
    void		setCursorMovedObserver(CursorMovedObserver&);
    SelectionChangedObserver& getSelectionChangedObserver() const;
    void		setSelectionChangedObserver(SelectionChangedObserver&);
    CommandPerformedObserver& getCommandPerformedObserver() const;
    void		setCommandPerformedObserver(CommandPerformedObserver&);

    // -------------------------------------------------------------
    // Triggers
    void		setSaveTrigger(Trigger* trigger);
    void		setSaveAsTrigger(Trigger* trigger);
    void		setSaveAllTrigger(Trigger* trigger);
    void		setOpenTrigger(Trigger* trigger);
    void		setQuitTrigger(Trigger* trigger);
    void		setKillBufferTrigger(Trigger* trigger);
    void		setSwitchBufferTrigger(Trigger* trigger);
    void		setGotoTrigger(Trigger* trigger);
    void		setFindTrigger(Trigger* trigger);
    void		setReplaceTrigger(Trigger* trigger);
    void		setReadOnlyTrigger(Trigger* trigger);

    // Triggers notifications
    IlBoolean		triggerSave();
    IlBoolean		triggerSaveAs();
    IlBoolean		triggerSaveAll();
    IlBoolean		triggerOpen();
    IlBoolean		triggerQuit();
    IlBoolean		triggerKillBuffer();
    IlBoolean		triggerSwitchBuffer();
    IlBoolean		triggerGoto();
    IlBoolean		triggerFind();
    IlBoolean		triggerReplace();
    IlBoolean		triggerReadOnly();

    // -------------------------------------------------------------
    // Overridden IlvGraphic, IlvGadget and IlvScrolledGadget virtual methods
    virtual IlBoolean	classFocusable () const;

    virtual void	drawGadgetContents(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* clip = 0) const;

    virtual IlBoolean	handleGadgetEvent(IlvEvent& event);
    virtual IlBoolean	handleScrollBarsEvent(IlvEvent& event);
    virtual void	scrollableSize(IlvDim& w, IlvDim& h) const;
    virtual void	focusIn();
    virtual void	focusOut();
    virtual void	applyTransform(const IlvTransformer* t);

    //-----------------------------------------------------------------------
    // Undocumented public API

    // Selection management
    void		selectAndScrollDown();
    void		selectAndScrollUp();
    void		selectAndScrollRight();
    void		selectAndScrollLeft();
    void		setSelection(const Location& begin,
				     const Location& end);
    void		releaseSelection();
    void		extendSelectionToXY(IlvPos x, IlvPos y);

    // Scroll management
    void		adjustFromScrollBar(const IlvScrollBar* sb,
					    IlvDirection dir);
    void		adjustScrollBarValue(IlvScrollBar* sb,
					     IlvDirection dir);
    IlBoolean		scrollUp(IlInt nbLines,
				 IlBoolean redraw = IlTrue,
				 IlBoolean optimize = IlTrue);
    IlBoolean		scrollDown(IlInt nbLines,
				   IlBoolean redraw = IlTrue,
				   IlBoolean optimize = IlTrue);
    IlBoolean		scrollRight(IlInt nbColumn,
				    IlBoolean redraw = IlTrue);
    IlBoolean		scrollLeft(IlInt nbColumn,
				   IlBoolean redraw = IlTrue);

    IlBoolean		centerOnCurrentLine();

    // reDraw management.
    void		consistentReDrawLines(IlInt fromLine, IlInt toLine);
    void		consistentReDraw(const IlvRegion* reg = 0);
    void		consistentBufferedDraw(const IlvRegion& reg);

    // Observer mechanism
    void		updateContentChangedObserver() const;
    void		updateCursorMovedObserver() const;
    void		updateSelectionChangedObserver() const;
    void		updateCommandPerformedObserver() const;
    void		updateObservers() const;

    // Need for saving management
    void		incrSaveNeeded();
    void		decrSaveNeeded();

    // Text management
    char*		concatText(const Location& begin,
				   const Location& end,
				   IlBoolean tabAsBlanks) const;

    Location		insertText(const char* text,
				   const Location& at,
				   IlBoolean reDraw = IlFalse);

    char*		removeText(const Location& start,
				   const Location& end,
				   IlBoolean retStr = IlTrue);

    void		cutLine(Location& loc);
    void		removeLine(IlInt l);
    void		removeLines(IlInt line, IlInt count);

    IlInt		insertCharacter(char key,
					IlBoolean bckIndent = IlTrue);

    void		removeOneLogicalCharacter();

    void		removeChar(const Location& loc);
    IlInt		insertTabulation();

    IlBoolean		isTabulation(const Location& l) const;

    IlInt		breakLine(IlBoolean autoIndent);

    // Indentation and auto-indentation mechanism
    IlInt		unindentLine(IlInt line);

    IlInt		indentLine(IlInt line);

    IlBoolean		isBlockCloser(char character) const;

    void		restoreIndentation(IlInt nbOfBlanksToAdd);

    // Misc.
    Location		getEndLocation() const ;
    Location		endOfLine(IlInt line) const;
    Location		prec(const Location& l) const;
    Location		next(const Location& l) const;
    IlBoolean		ensureVisible(const Location& location,
				      IlBoolean reDraw = IlTrue);
    char		characterAt(const Location& l) const;

    // Syntax coloring
    IlBoolean		computeDecorators(IlInt lineNumber,
					  IlBoolean noError);
    IlInt		propagateInfluence(IlInt startLine);

    // Limited Bounding boxes computation
    IlvRect		getLineMarginBBox(int line) const;
    IlvRect		getLineBBox(int line) const;
    IlvRect		getCharBBox(Location loc) const;

    // Blinking cursor
    void		getCursorExtent(IlvPoint* low,
					IlvPoint* up) const;
    void		drawCursor(IlvPort* dst) const;
    void		hideCursor(IlvPort* dst) const;

    // Brace Matching highlighting
    void		drawParen(IlvPort* dst, Location loc);
    void		hideParen(IlvPort* dst) const;
    void		drawParen(IlvPort* dst);

    // Online help management
    void		onlineHelpTemplateMethod() const;

    // Text edition notification
    void		notifyEditTemplateMethod();

    // Internationalization (Redefinition of SimpleGraphic? class)
    virtual IlBoolean	needsInputContext() const;
    virtual void	setNeedsInputContext(IlBoolean val);
    // To be called each time the cursor has moved
    void		moveInputMethodPreEditArea();

    //------------------------------------------------------------------
    // Undocumented public API used by the IlvSEBinding interactors.
    // C-g with Emacs mode
    IlBoolean		keyboardQuit();

    // Navigation
    IlBoolean		moveLeftChar();
    IlBoolean		moveRightChar();
    IlBoolean		moveLeftWord();
    IlBoolean		moveRightWord();
    IlBoolean		moveStartLine();
    IlBoolean		moveEndLine();
    IlBoolean		moveUpLine();
    IlBoolean		moveDownLine();
    IlBoolean		moveUpText();
    IlBoolean		moveDownText();
    IlBoolean		moveUpPage();
    IlBoolean		moveDownPage();
    IlBoolean		moveStartBuffer();
    IlBoolean		moveEndBuffer();

    // Selection management
    void		extendSelection();
    void		setStartSelection();

    // Deletion
    IlBoolean		deleteLeft();
    IlBoolean		deleteRight();
    IlBoolean		deleteSelection();

    // Insertion
    IlBoolean		insertLineFeed();
    void		insertChar(char key);
    // For internationalization Input Method can return more than one char !
    void		insertString(const char* mbs);
    IlBoolean		insertTab();
    IlBoolean		removeTab();

    // Indentation management
    IlBoolean		indentRegion();
    IlBoolean		unindentRegion();

    // ClipBoard mechanism : non-const intentionaly
    IlBoolean		copyToClipBoardBinding();

    void		setMarginWidth(IlvDim mrgW);
    void		setShowLineNumbers(IlBoolean show);

    void		changeParser(Parser* parser);

 protected:
    //-----------------------------------------------------------------------
    // Undocumented protected API

    // Online help management
    // To redefine for online help window displaying.
    virtual void	onlineHelp(const char* word) const; 

    // Text edition notification
    virtual void	notifyEdit();

    // Undo/redo mechanism
    IlvCEdtCommandFactory* getCommandFactory() const;

    // Underlying data-structure protected accessors
    //delta on the y-coordinate
    IlvDim		getDelta() const;
    IlShort		lmarg() const;

    // Pixel/Location conversions
    void		xyToStartLocation(IlInt x, IlInt y,
					  Location& loc) const;
    IlvPos		lineToY(IlInt line) const;
    IlInt		xToColumn(IlvPos x,
				  IlInt line,
				  IlInt from,
				  IlvPos& delta,
				  IlBoolean previous) const;
    IlInt		yToLine(IlvPos y, IlBoolean t = IlFalse) const;

    // Scrolling management
    void		setFirstLine(IlInt lineNumber);
    IlInt		getFirstLine() const;
    IlInt		getLastLine(IlBoolean t = IlFalse) const;
    IlInt		getNbOfVisibleLines(IlBoolean theor = IlFalse) const;
    IlInt		getNbOfVisibleColumns() const;
    void		setFirstColumn(IlInt colNumber);
    IlInt		getFirstColumn() const;
    IlInt		getLastColumn() const;

    // Autoindent
    IlBoolean		isAutoIndent() const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvCodeEditor);
    DeclareGraphicAccessors();

 private:
    void		init(IlvDisplay* display,
			     Binding::Mode mode,
			     StyleSheet* sheet,
			     IlvDim leftMargin = 0);
    // Copy C'tor
    //IlvEditor (const IlvEditor&);
    // Clipboard management
    IlBoolean		getAppendableToClipboard() const;
    void		setAppendableToClipboard(IlBoolean b) const;
    IlBoolean		copyToClipBoardInternal(IlBoolean append) const;

    // Scrolling management
    void		optimizedScroll(IlInt nbLines);
    IlBoolean		isPartiallyVisible(IlInt line) const;
    IlInt		getLastFullVisibleLine() const;
    // Scrolling while dragging outside editing area
    IlBoolean		leaveArea(IlvEvent& event);
    IlBoolean		setMaxWidth(IlvDim newMax);
    IlBoolean		trySetMaxWidth(const IlvCEdtLine* line);
    IlvDim		computeMaxWidth() const;
    IlvDim		getMaxWidth() const;

    // Syntax coloring
    void		decorateComment(IlInt line);
    IlBoolean		findCommentOnLine(IlInt line,
					  IlInt& commentBegCol,
					  IlInt& commentEndCol) const;

    void		hideCursorAndParen();

    // Selection management
    void		extendSelectionToLocation(const Location& loc,
						  IlBoolean endExcl = IlTrue);
    void		manageMultiClick(int nbOfClicks);

    // Text management
    IlBoolean		insertTextReversible(const char* text,
					     const Location& at,
					     IlBoolean reDraw);
    void		loadTextInternal(const char* text);
    void		removeBreakLine(IlInt line);
    IlBoolean		multiInsertAtColumn(const char* text,
					    IlInt beginLine,
					    IlInt endLine,
					    IlInt column);
    IlBoolean		removeComment(const char* commentDelim,
				      IlInt beginLine,
				      IlInt endLine);

    // Internationalization Input Method
    void		notifyInputMethodFocusOut();
    void		notifyInputMethodFocusIn();
    void		initInputMethodParameters(IlvImValue values[],
						  IlUShort count);

    //---- Attributes-----------------------------------------------
    IlvCEdtText*	_text;          // Content
    IlvDim		_delta;		// inter-line
    IlvDim		_marginWidth;	// margin width
    IlBoolean		_showLineNums;  // show line numbers
    IlBoolean		_showMargin;	// show line numbers
    //----Blinking, Scrolling and Match Brace timers
    IlvTimer*		_blinkingTimer;
    IlvTimer*		_scrollingTimer;
    IlvTimer*		_matchBraceTimer;
    IlBoolean		_cursorVisible;
    //----Scrolling management
    IlInt		_firstLine;
    IlInt		_firstColumn;
    IlvDim		_maxLineWidth;	// for hor. scrollbar if prop font

    enum  ButtonState { UpButton, DownButton};

    ButtonState		_buttonState;
    //----Brace matching management
    IlBoolean		_braceHighLighting;
    // ----Bindings
    Binding*		_binding;
    // ----Style Sheet
    StyleSheet*	_sheet;
    //----Undo/Redo facilities
    IlvCEdtCommandProcessor* _cmdProcessor;
    //-----Misc.-------------
    IlBoolean		_editSignal;		// True as soon as edited.
    IlBoolean		_appendableToClipboard; // True if next C-k can append.
    //-----Observers---------
    ContentChangedObserver*   _contentChangedObserver;
    CursorMovedObserver*      _cursorMovedObserver;
    SelectionChangedObserver* _selectionChangedObserver;
    CommandPerformedObserver* _commandPerformedObserver;
    //-----Triggers----------
    Trigger*		_saveTrigger;
    Trigger*		_saveAsTrigger;
    Trigger*		_saveAllTrigger;
    Trigger*		_openTrigger;
    Trigger*		_quitTrigger;
    Trigger*		_killBufferTrigger;
    Trigger*		_switchBufferTrigger;
    Trigger*		_findTrigger;
    Trigger*		_replaceTrigger;
    Trigger*		_gotoTrigger;
    Trigger*		_readOnlyTrigger;
    //-----Internationalization----
    IlBoolean		_needsIC;
};

ILVADVGDTMODULEINIT(editor);

#endif /* !__Ilv_Gadgets_Codeedit_H */
