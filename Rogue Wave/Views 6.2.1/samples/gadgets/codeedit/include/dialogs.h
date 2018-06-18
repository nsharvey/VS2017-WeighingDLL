// -------------------------------------------------------------- -*- C++ -*-
//                                                 Rogue Wave Views source file
// File: samples/gadgets/codeedit/include/dialogs.h
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

#ifndef Samples_Gadgets_Codeedit_Dialogs_H
#define Samples_Gadgets_Codeedit_Dialogs_H

#include <ilviews/gadgets/idialog.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/optmenu.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/codeedit.h>
#include <ilviews/graphics/selector.h>

// --------------------------------------------------------------------------
// Specialized IlvDialog for Yes/No/Cancel message box
// --------------------------------------------------------------------------
typedef enum { Yes, No, Cancel } YesNoCancel;

class YesNoCancelBox : public IlvDialog
{
public:
    YesNoCancelBox(IlvDisplay* display, const char* question);

    virtual void	cancel();	// overridden
    virtual void	apply();	// overridden
    virtual void	no();		// new
    // replaces the wasCanceled method with the right semantic
    IlBoolean		wasCancel() const { return _state == Cancel; }
    IlBoolean		wasYes() const { return _state == Yes; }
    IlBoolean		wasNo() const { return _state == No; }
    YesNoCancel		ask()
			{
			    wait();
			    return _state;
			}
private:
    YesNoCancel		_state;
};

// --------------------------------------------------------------------------
// Specialized IlvDialog for editor pattern finding.
// --------------------------------------------------------------------------
class FindDialogBox : public IlvDialog
{
public:
    FindDialogBox(IlvDisplay* display,
		  IlvCodeEditor* editor,
		  const char* stringInit = 0,
		  IlvSystemView transientFor = 0,
		  const char* name = "find",
		  const char* title = "Find Text",
		  const char* ilvName = "find.ilv");

    void		apply();
    IlBoolean		findPrevious();
    IlBoolean		findNext();
    void		selectPattern()
			{
			    IlvTextField* t = getTextField();
			    t->setSelection(t->getStartSelection(),
					    t->getEndSelection());
			    setFocus(t);
			}
    void		setEditor(IlvCodeEditor* editor) { _editor = editor; }
    const char*		getPattern() const
			{
			    return getTextField()->getLabel();
			}
    void		setPattern(const char* pattern)
			{
			    getTextField()->setLabel(pattern);
			}
    virtual void	setLimitedToSelection(IlBoolean limited);

protected:
    IlvCodeEditor*	_editor;

    IlBoolean		find();
    virtual IlBoolean	getForwardDir() const;
    IlBoolean		getCaseSensitive() const
			{
			    return getMatchCaseToggle()->getState();
			}
    IlBoolean		getWholeWord() const
			{
			    return getWholeWordToggle()->getState();
			}
    virtual IlBoolean	getLimitedToSelection() const;
    IlInt		getLimitSectionStartLine() const
			{
			    return _sectionStartLine;
			}
    IlInt		getLimitSectionStartColumn() const
			{
			    return _sectionStartColumn;
			}
    IlInt		getLimitSectionEndLine() const
			{
			    return _sectionEndLine;
			}
    IlInt		getLimitSectionEndColumn() const
			{
			    return _sectionEndColumn;
			}
    // Gadgets accessors
    IlvSelector*	getDirSelector() const
			{
			    return (IlvSelector*)getObject("DirectionS");
			}
private:
    // Gadgets accessors
    IlvTextField*	getTextField() const
			{
			    return (IlvTextField*)getObject("TextF");
			}
    IlvToggle*		getMatchCaseToggle() const
			{
			    return (IlvToggle*)getObject("MatchCaseB");
			}
    IlvToggle*		getWholeWordToggle() const
			{
			    return (IlvToggle*)getObject("MatchWordB");
			}
    IlvButton*		getFindButton() const
			{
			    return (IlvButton*)getObject("apply");
			}
    // Limit search section
    IlInt		_sectionStartLine;
    IlInt		_sectionStartColumn;
    IlInt		_sectionEndLine;
    IlInt		_sectionEndColumn;
};

// --------------------------------------------------------------------------
// Specialized IlvDialog for editor pattern replacement.
// --------------------------------------------------------------------------
class ReplaceDialogBox : public FindDialogBox
{
public:
    ReplaceDialogBox(IlvDisplay* display,
		     IlvCodeEditor* editor,
		     const char* stringInit = 0,
		     IlvSystemView transientFor = 0);

    void		replaceSelection();
    void		replaceAll();
    virtual void	setLimitedToSelection(IlBoolean limited);
    void		activateFindReplace();

protected:
    virtual IlBoolean	getForwardDir() const;
    const char*		getReplacePattern() const
			{
			    return getReplaceTextField()->getLabel();
			}
    virtual IlBoolean	getLimitedToSelection() const;

private:
    // Gadgets accessors
    IlvButton*		getFindButton() const
			{
			    return (IlvButton*)getObject("FindB");
			}
    IlvButton*		getReplaceButton() const
			{
			    return (IlvButton*)getObject("ReplaceB");
			}
    IlvTextField*	getReplaceTextField() const
			{
			    return (IlvTextField*)getObject("ReplaceTextF");
			}
    IlvToggle*		getLimitedToSelectionToggle() const
			{
			    return (IlvToggle*)getObject("LimitedToSelectionB");
			}
};

// --------------------------------------------------------------------------
// Specialized IlvDialog for "Go To Line #"
// --------------------------------------------------------------------------
class GoToDialogBox : public IlvDialog
{
public:
    GoToDialogBox(IlvDisplay* display, IlvCodeEditor& editor);

    void		apply();

protected:
    IlInt		getLine() const
			{
			    IlBoolean b;
			    return (IlInt)getNumberField()->getIntValue(b);
			}

    IlvCodeEditor&	_editor;
private:
    // Gadgets accessors
    IlvNumberField*	getNumberField() const
			{
			    return (IlvNumberField*)getObject("NumberF");
			}
};

// --------------------------------------------------------------------------
// Specialized IlvDialog for editor options handling.
// --------------------------------------------------------------------------
class CustomizeDialogBox : public IlvDialog
{
public:
    CustomizeDialogBox(IlvDisplay* display,
		       IlvCodeEditor* editor,
		       IlvTextField* buff);

    void		apply();
    void		okCB();

    void		EdtFontCB(IlvGraphic*);
    void		EdtBgColorCB(IlvGraphic*);
    void		EdtFgColorCB(IlvGraphic*);
    void		KwdBgColorCB(IlvGraphic*);
    void		KwdFgColorCB(IlvGraphic*);
    void		PprBgColorCB(IlvGraphic*);
    void		PprFgColorCB(IlvGraphic*);
    void		CmtBgColorCB(IlvGraphic*);
    void		CmtFgColorCB(IlvGraphic*);
    IlvCodeEditor::StyleSheet*	getStyleSheet() const {	return _sheet; }
    IlvCodeEditor*	getEditor() const { return _editor; }
    void		setEditor(IlvCodeEditor* ed) { _editor = ed; }
    const char*		getClassPath() const
			{
			    return getClassPathTextField()->getLabel();
			}
    const char*		getDestination() const
			{
			    return getDestinationTextField()->getLabel();
			}
private:
    IlvCodeEditor::StyleSheet*	_sheet;
    IlvCodeEditor*		_editor;

    // Value accessors from/to gadgets
    IlInt		getTabSize() const
			{
			    IlBoolean b;
			    return getTabSizeField()->getIntValue(b);
			}
    void		setTabSize(IlInt tabSize)
			{
			    if (getTabSizeField())
				getTabSizeField()->setValue(tabSize);
			}
    IlBoolean		getSyntaxColoring() const
			{
			    return getSyntaxColoringToggle()->getState();
			}
    void		setSyntaxColoring(IlBoolean b)
			{
			    getSyntaxColoringToggle()->setState(b);
			}
    IlBoolean		getAutoindentation() const
			{
			    return getAutoindentationToggle()->getState();
			}
    void		setAutoindentation(IlBoolean b)
			{
			    getAutoindentationToggle()->setState(b);
			}
    IlBoolean		getBraceHighlighting() const
			{
			    return getBraceHighlightingToggle()->getState();
			}
    void		setBraceHighlighting(IlBoolean b)
			{
			    getBraceHighlightingToggle()->setState(b);
			}
    IlBoolean		getTabulationAsBlanks() const
			{
			    return getTabulationAsBlanksToggle()->getState();
			}
    void		setTabulationAsBlanks(IlBoolean b)
			{
			    getTabulationAsBlanksToggle()->setState(b);
			}
    IlBoolean		getVariableColoring() const
			{
			    return IlFalse;
			}
    void		setVariableColoring(IlBoolean b) {}
    IlBoolean		getColorizeErrorLine() const { return IlTrue; }
    void		setColorizeErrorLine(IlBoolean b) { }
    IlvCodeEditor::Binding::Mode
			getBindingMode() const
			{
			    return (IlvCodeEditor::Binding::Mode)
				getBindingModeComboBox()->whichSelected();
			}
    void		setBindingMode(IlvCodeEditor::Binding::Mode mode)
			{
			    if (getBindingModeComboBox())
				getBindingModeComboBox()->
				    setSelected((IlShort)(mode));
			}
    IlvFont*		getEditorFont() const
			{
			    return getEdtFont()->getFont();
			}
    void		setEditorFont(IlvFont* font)
			{
			    getEdtFont()->setFont(font);
			}
    IlvColor*		getEdtFgColor() const
			{
			    return getEdtColor()->getForeground();
			}
    void		setEdtFgColor(IlvColor* color)
			{
			    getEdtColor()->setForeground(color);
			}
    IlvColor*		getEdtBgColor() const
			{
			    return getEdtColor()->getBackground();
			}
    void		setEdtBgColor(IlvColor* color)
			{
			    getEdtColor()->setBackground(color);
			}
    IlvColor*		getKwdBgColor() const
			{
			    return getKeywordsColor()->getBackground();
			}
    void		setKwdBgColor(IlvColor* color)
			{
			    getKeywordsColor()->setBackground(color);
			}
    IlvColor*		getKwdFgColor() const
			{
			    return getKeywordsColor()->getForeground();
			}
    void		setKwdFgColor(IlvColor* color)
			{
			    getKeywordsColor()->setForeground(color);
			}
    IlvColor*		getPprBgColor() const
			{
			    return getPreprocessorColor()->getBackground();
			}
    void		setPprBgColor(IlvColor* color)
			{
			    getPreprocessorColor()->setBackground(color);
			}
    IlvColor*		getPprFgColor() const
			{
			    return getPreprocessorColor()->getForeground();
			}
    void		setPprFgColor(IlvColor* color)
			{
			    getPreprocessorColor()->setForeground(color);
			}
    IlvColor*		getCmtBgColor() const
			{
			    return getCommentColor()->getBackground();
			}
    void		setCmtBgColor(IlvColor* color)
			{
			    getCommentColor()->setBackground(color);
			}
    IlvColor*		getCmtFgColor() const
			{
			    return getCommentColor()->getForeground();
			}
    void		setCmtFgColor(IlvColor* color)
			{
			    getCommentColor()->setForeground(color);
			}
    void		setClassPath(const char* classpath)
			{
			    getClassPathTextField()->setLabel(classpath);
			}
    void		setDestination(const char* dest)
			{
			    getDestinationTextField()->setLabel(dest);
			}

    // Gadgets accessors
    IlvTextField*	getClassPathTextField() const
			{
			    return ((IlvTextField*)getObject("classpath"));
			}
    IlvNumberField*	getTabSizeField() const
			{
			    return (IlvNumberField*)getObject("tabSizeField");
			}
    IlvToggle*		getSyntaxColoringToggle() const
			{
			    return (IlvToggle*)
				getObject("syntaxColoringToggle");
			}
    IlvToggle*		getAutoindentationToggle() const
			{
			    return (IlvToggle*)
				getObject("autoindentationToggle");
			}
    IlvToggle*		getBraceHighlightingToggle() const
			{
			    return (IlvToggle*)
				getObject("braceHighlightingToggle");
			}
    IlvToggle*		getTabulationAsBlanksToggle() const
			{
			    return (IlvToggle*)
				getObject("tabulationAsBlanksToggle");
			}
    IlvOptionMenu*	getBindingModeComboBox() const
			{
			    return (IlvOptionMenu*)getObject("editorMode");
			}
    IlvTextField*	getEdtFont() const
			{
			    return (IlvTextField*)getObject("edt_font");
			}
    IlvTextField*	getEdtColor() const
			{
			    return (IlvTextField*)getObject("SampleEdt");
			}
    IlvTextField*	getCommentColor() const
			{
			    return (IlvTextField*)getObject("SampleComment");
			}
    IlvTextField*	getKeywordsColor() const
			{
			    return (IlvTextField*)getObject("SampleKeywords");
			}
    IlvTextField*	getPreprocessorColor() const
			{
			    return (IlvTextField*)
				getObject("SamplePreprocessor");
			}
    IlvTextField*	getDestinationTextField() const
			{
			    return (IlvTextField*)getObject("destination");
			}

    IlvFont*		chooseFont(IlvFont* f) const;
    IlvColor*		chooseColor(IlvColor* c) const;
    void		setEditFont(IlvFont* fnt,
				    IlvColor* fore,
				    IlvColor* back);
    void		setNonOrdinaryColors(IlvColor* kwdFg,
					     IlvColor* kwdBg,
					     IlvColor* pprFg,
					     IlvColor* pprBg,
					     IlvColor* cmtFg,
					     IlvColor* cmtBg);

    void		registerCB();

    IlvCodeEditor::StyleSheet*
			createStyleSheet(IlvDisplay* display,
					 IlvTextField* buff);
};

#endif /* !Samples_Gadgets_Codeedit_Dialogs_H */
