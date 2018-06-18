// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/codeedit/src/dialogs.cpp
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
// Implementation of the dialog boxes.
// --------------------------------------------------------------------------

#include "dialogs.h"
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/fontsel.h>

void CBCloseDialogBox(IlvView* top, IlAny);

// --------------------------------------------------------------------------
// YesNoCancelBox
// --------------------------------------------------------------------------
static void
NoCBdlg(IlvGraphic* g, IlAny arg)
{
    if (g) {
        ((YesNoCancelBox *)
	 (g->GetCurrentCallbackHolder()->getContainer()))->no();
    }
}
// --------------------------------------------------------------------------
YesNoCancelBox::YesNoCancelBox(IlvDisplay* display, const char* question)
  : IlvDialog(display, "EditorBox", "Editor", "yesnocancel.ilv"),
    _state(Cancel)
{
    setDestroyCallback(CBCloseDialogBox);
    registerCallback("NoCB", NoCBdlg);
    if (question) {
        IlvMessageLabel* TextField = (IlvMessageLabel*)getObject("question");
        TextField->setLabel(question);
    }
}

// --------------------------------------------------------------------------
void
YesNoCancelBox::cancel()
{
    _state = Cancel;
    hide();
}

// --------------------------------------------------------------------------
void
YesNoCancelBox::apply()
{
    _state = Yes;
    hide();
}

// --------------------------------------------------------------------------
void
YesNoCancelBox::no()
{
    _state = No;
    hide();
}

// --------------------------------------------------------------------------
// FindDialogBox
// --------------------------------------------------------------------------
FindDialogBox::FindDialogBox(IlvDisplay* display,
                             IlvCodeEditor* editor,
                             const char* stringInit,
                             IlvSystemView transient,
                             const char* name,
                             const char* title,
                             const char* ilName)
  : IlvDialog(display, name, title, ilName, IlvStandardBorder, 0, transient),
    _editor(editor),
    _sectionStartLine(0),
    _sectionStartColumn(0),
    _sectionEndLine(0),
    _sectionEndColumn(0)
{
    setDestroyCallback(CBCloseDialogBox);
    if (getMatchCaseToggle())
        getMatchCaseToggle()->setState(IlFalse);
    if (getDirSelector())
        getDirSelector()->setSelected(getDirSelector()->getObject(1));
    if (stringInit)
        setPattern(stringInit);
    if (getFindButton())
        setDefaultButton(getFindButton());
}

// --------------------------------------------------------------------------
IlBoolean
FindDialogBox::getForwardDir() const
{
    return (getDirSelector()
            ? getDirSelector()->whichSelected() == 1
	    : IlTrue);
}

// --------------------------------------------------------------------------
void
FindDialogBox::setLimitedToSelection(IlBoolean limitedToSelection)
{
    _sectionStartLine    = _editor->getSelectionStartLine();
    _sectionStartColumn  = _editor->getSelectionStartColumn();
    _sectionEndLine      = _editor->getSelectionEndLine();
    _sectionEndColumn    = _editor->getSelectionEndColumn();
}

// --------------------------------------------------------------------------
IlBoolean
FindDialogBox::getLimitedToSelection() const
{
    return IlFalse;
}

// --------------------------------------------------------------------------
void
FindDialogBox::apply()
{
    if (!find() && _editor) {
        if (getForwardDir())
            _editor->gotoLine(1);
        else
            _editor->gotoEnd();
        find();
    }
}

// --------------------------------------------------------------------------
IlBoolean
FindDialogBox::find()
{
    if (!_editor)
        return IlFalse;
    if (!_editor->find(getForwardDir(),
                       getLimitedToSelection(),
                       getCaseSensitive(),
                       getWholeWord(),
                       getPattern(),
                       getLimitSectionStartLine(),
                       getLimitSectionStartColumn(),
                       getLimitSectionEndLine(),
                       getLimitSectionEndColumn())) {
        getDisplay()->bell();
        return IlFalse;
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
FindDialogBox::findNext()
{
    if (!_editor)
        return IlFalse;
    if (!_editor->find(IlTrue, // Forward Dir
                       IlFalse,
                       getCaseSensitive(),
                       getWholeWord(),
                       getPattern(),
                       getLimitSectionStartLine(),
                       getLimitSectionStartColumn(),
                       getLimitSectionEndLine(),
                       getLimitSectionEndColumn())) {
        getDisplay()->bell();
        return IlFalse;
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
FindDialogBox::findPrevious()
{
    if (!_editor)
        return IlFalse;
    if (!_editor->find(IlFalse, // Backard dir
                       IlFalse,
                       getCaseSensitive(),
                       getWholeWord(),
                       getPattern(),
                       getLimitSectionStartLine(),
                       getLimitSectionStartColumn(),
                       getLimitSectionEndLine(),
                       getLimitSectionEndColumn())) {
        getDisplay()->bell();
        return IlFalse;
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
// ReplaceDialogBox
// --------------------------------------------------------------------------
static void
replaceCBdlg(IlvGraphic* g, IlAny arg)
{
    ReplaceDialogBox* box =
        (ReplaceDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->replaceSelection();
}

// --------------------------------------------------------------------------
static void
replaceAllCBdlg(IlvGraphic* g, IlAny arg)
{
    ReplaceDialogBox* box =
        (ReplaceDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->replaceAll();
}

// --------------------------------------------------------------------------
static void
replaceInSelectionCBdlg(IlvGraphic* g, IlAny arg)
{
    ReplaceDialogBox* box =
        (ReplaceDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->activateFindReplace();
}

// --------------------------------------------------------------------------
ReplaceDialogBox::ReplaceDialogBox(IlvDisplay* display,
                                   IlvCodeEditor* editor,
                                   const char* stringInit,
                                   IlvSystemView transientFor)
    : FindDialogBox(display,
		    editor,
		    stringInit,
		    transientFor,
		    "replace",
		    "Replace Text",
		    "replace.ilv")
{
    getLimitedToSelectionToggle()->setState(IlvFalse);
    registerCallback("replaceCB", replaceCBdlg);
    registerCallback("replaceAllCB", replaceAllCBdlg);
    registerCallback("ReplaceInSelectionCB", replaceInSelectionCBdlg);
}

// --------------------------------------------------------------------------
IlBoolean
ReplaceDialogBox::getLimitedToSelection() const
{
    return getLimitedToSelectionToggle()->getState();
}

// --------------------------------------------------------------------------
void
ReplaceDialogBox::setLimitedToSelection(IlBoolean limited)
{
    FindDialogBox::setLimitedToSelection(limited);
    getLimitedToSelectionToggle()->setState(limited);
}

// --------------------------------------------------------------------------
IlBoolean
ReplaceDialogBox::getForwardDir() const
{
    return IlTrue;
}

// --------------------------------------------------------------------------
void
ReplaceDialogBox::replaceSelection()
{
    if (!_editor)
        return;
    if (!_editor->hasSelection())
        getDisplay()->bell();
    else  {
        _editor->replaceSelection(getReplacePattern(),
				  IlTrue,
                                  getForwardDir());
        _editor->find(getForwardDir(),
                      getLimitedToSelection(),
                      getCaseSensitive(),
                      getWholeWord(),
                      getPattern(),
                      getLimitSectionStartLine(),
                      getLimitSectionStartColumn(),
                      getLimitSectionEndLine(),
                      getLimitSectionEndColumn());
    }
    _editor->consistentReDraw();
}

// --------------------------------------------------------------------------
void
ReplaceDialogBox::replaceAll()
{
    if (!_editor)
        return;
    if (!getLimitedToSelection())
        _editor->gotoLine(1);
    if (!_editor->find(IlTrue, // ForwardDir
                       getLimitedToSelection(),
                       getCaseSensitive(),
                       getWholeWord(),
                       getPattern(),
                       getLimitSectionStartLine(),
                       getLimitSectionStartColumn(),
                       getLimitSectionEndLine(),
                       getLimitSectionEndColumn())) {
        getDisplay()->bell();
        return;
    }
    do {
        _editor->replaceSelection(getReplacePattern(),
				  IlTrue,
                                  getForwardDir());
    } while (_editor->find(IlTrue, // ForwardDir
                           getLimitedToSelection(),
                           getCaseSensitive(),
                           getWholeWord(),
                           getPattern(),
                           getLimitSectionStartLine(),
                           getLimitSectionStartColumn(),
                           getLimitSectionEndLine(),
                           getLimitSectionEndColumn()));
    _editor->consistentReDraw();
}

// --------------------------------------------------------------------------
void
ReplaceDialogBox::activateFindReplace()
{
    if (getFindButton())
        getFindButton()->setActive(getLimitedToSelection());
    if (getReplaceButton())
        getReplaceButton()->setActive(getLimitedToSelection());
}

// --------------------------------------------------------------------------
// GoToDialogBox
// --------------------------------------------------------------------------
GoToDialogBox::GoToDialogBox(IlvDisplay* display, IlvCodeEditor& editor)
    : IlvDialog(display, "goto", "Go To", "goto.ilv"),
      _editor(editor)
{
    setDestroyCallback(CBCloseDialogBox);
}

// --------------------------------------------------------------------------
void
GoToDialogBox::apply()
{
    if (!_editor.gotoLine(getLine()))
        getDisplay()->bell();
    else cancel();
}

// --------------------------------------------------------------------------
// CustomizeDialogBox
// --------------------------------------------------------------------------
CustomizeDialogBox::CustomizeDialogBox(IlvDisplay* display,
                                       IlvCodeEditor* editor,
                                       IlvTextField* miniBuff)
  : IlvDialog(display,
	      "editoroptions",
	      "Editor options",
	      "editoroptions.ilv"),
    _sheet(0),
    _editor(editor)
{
    setDestroyCallback(CBCloseDialogBox);
    _sheet = createStyleSheet(display, miniBuff);
    
    IlBoolean
	syntaxColoring		= _sheet->syntaxHighLight(),
        colorizeErrorLine	= _sheet->colorizeErrorLine(),
        tabAsBlanks		= _sheet->getTabAsBlanks(),
        variableColoring	= _sheet->variableColoring(),
        braceHighLight		= _sheet->braceHighLight(),
        isAutoIndent		= _sheet->isAutoIndent();
    IlInt tabSize = _sheet->getTabSize();
    IlvCodeEditor::Binding::Mode bindingMode = _editor->getBindingMode();
    IlvFont* editorFont = _sheet->getEditorFont();
    IlvColor* edtFgColor = _sheet->getDecorator(IlvCodeEditor::TextToken)
	->getForeground();
    IlvColor* edtBgColor = _sheet->getDecorator(IlvCodeEditor::TextToken)
	->getBackground();
    IlvColor* kwdFgColor = _sheet->getDecorator(IlvCodeEditor::KeywordToken)
	->getForeground();
    IlvColor* kwdBgColor = _sheet->getDecorator(IlvCodeEditor::KeywordToken)
	->getBackground();
    IlvColor* pprFgColor = _sheet->getDecorator(IlvCodeEditor::ScriptToken)
	->getForeground();
    IlvColor* pprBgColor = _sheet->getDecorator(IlvCodeEditor::ScriptToken)
	->getBackground();
    IlvColor* cmtFgColor = _sheet->getDecorator(IlvCodeEditor::CommentToken)
	->getForeground();
    IlvColor* cmtBgColor = _sheet->getDecorator(IlvCodeEditor::CommentToken)
	->getBackground();

    setSyntaxColoring(syntaxColoring);
    setTabulationAsBlanks(tabAsBlanks);
    setColorizeErrorLine(colorizeErrorLine);
    setVariableColoring(variableColoring);
    setBraceHighlighting(braceHighLight);
    setAutoindentation(isAutoIndent);
    setTabSize(tabSize);
    setBindingMode(bindingMode);
    setTabulationAsBlanks(tabAsBlanks);
    if (editorFont)
        setEditorFont(editorFont);
    if (edtFgColor)
        setEdtFgColor(edtFgColor);
    if (edtBgColor)
        setEdtBgColor(edtBgColor);
    if (kwdFgColor)
        setKwdFgColor(kwdFgColor);
    if (kwdBgColor)
        setKwdBgColor(kwdBgColor);
    if (pprFgColor)
        setPprFgColor(pprFgColor);
    if (pprBgColor)
        setPprBgColor(pprBgColor);
    if (cmtFgColor)
        setCmtFgColor(cmtFgColor);
    if (cmtBgColor)
        setCmtBgColor(cmtBgColor);
    registerCB();
}

// --------------------------------------------------------------------------
IlvCodeEditor::StyleSheet*
CustomizeDialogBox::createStyleSheet(IlvDisplay* display,
                                     IlvTextField* miniBuff)
{
    return IlvCodeEditor::StyleSheet::MakeDefault(display, miniBuff);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::okCB()
{
    apply();
    hide();
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::apply()
{
    _sheet->setSyntaxHighlight(getSyntaxColoring());
    _sheet->setTabAsBlanks(getTabulationAsBlanks());
    _sheet->colorizeErrorLine(getColorizeErrorLine());
    _sheet->variableColoring(getVariableColoring());
    _sheet->setBraceHighLight(getBraceHighlighting());
    _sheet->setAutoIndent(getAutoindentation());
    _sheet->setTabSize(getTabSize());
    _editor->setBindingMode(getBindingMode());
    setEditFont(getEditorFont(), getEdtFgColor(), getEdtBgColor());
    setNonOrdinaryColors(getKwdFgColor(),
			 getKwdBgColor(),
			 getPprFgColor(),
                         getPprBgColor(),
			 getCmtFgColor(),
			 getCmtBgColor());
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::setEditFont(IlvFont* fnt, IlvColor* fg, IlvColor* bg)
{
    if (fnt) {
        _sheet->setEditorFont(fnt);
        _sheet->setEditorBackground(bg);
        _sheet->getDecorator(IlvCodeEditor::TextToken)->setForeground(fg);
        _sheet->getDecorator(IlvCodeEditor::TextToken)->setBackground(bg);
        _sheet->stdPalette()->setForeground(fg);
        _sheet->stdPalette()->setBackground(bg);
        _sheet->selPalette()->setForeground(bg);
        _sheet->selPalette()->setBackground(fg);
    }
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::setNonOrdinaryColors(IlvColor* kwdFg,
                                         IlvColor* kwdBg,
                                         IlvColor* pprFg,
                                         IlvColor* pprBg,
                                         IlvColor* cmtFg,
                                         IlvColor* cmtBg)
{
    _sheet->getDecorator(IlvCodeEditor::KeywordToken)->setForeground(kwdFg);
    _sheet->getDecorator(IlvCodeEditor::KeywordToken)->setBackground(kwdBg);
    _sheet->getDecorator(IlvCodeEditor::ScriptToken)->setForeground(pprFg);
    _sheet->getDecorator(IlvCodeEditor::ScriptToken)->setBackground(pprBg);
    _sheet->getDecorator(IlvCodeEditor::CommentToken)->setForeground(cmtFg);
    _sheet->getDecorator(IlvCodeEditor::CommentToken)->setBackground(cmtBg);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::EdtFontCB(IlvGraphic*)
{
    IlvFont* oldFont = getEditorFont();
    IlvFont* newFont = chooseFont(oldFont);
    if (newFont) {
        setEditorFont(newFont);
        getEdtFont()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
OKCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->okCB();
}

// --------------------------------------------------------------------------
static void
EdtFontCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->EdtFontCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::EdtBgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getEdtBgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setEdtBgColor(newColor);
        if (getEdtColor())
            getEdtColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
EdtBgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->EdtBgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::EdtFgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getEdtFgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setEdtFgColor(newColor);
        if (getEdtColor())
            getEdtColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
EdtFgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->EdtFgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::KwdBgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getKwdBgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setKwdBgColor(newColor);
        if (getKeywordsColor())
            getKeywordsColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
static void
KwdBgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->KwdBgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::KwdFgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getKwdFgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setKwdFgColor(newColor);
        if (getKeywordsColor())
            getKeywordsColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
KwdFgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->KwdFgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::PprBgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getPprBgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setPprBgColor(newColor);
        if (getPreprocessorColor())
            getPreprocessorColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
PprBgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->PprBgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::PprFgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getPprFgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setPprFgColor(newColor);
        if (getPreprocessorColor())
            getPreprocessorColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
PprFgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->PprFgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::CmtBgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getCmtBgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setCmtBgColor(newColor);
        if (getCommentColor())
            getCommentColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
CmtBgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->CmtBgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::CmtFgColorCB(IlvGraphic*)
{
    IlvColor* oldColor = getCmtFgColor();
    IlvColor* newColor = chooseColor(oldColor);
    if (newColor) {
        setCmtFgColor(newColor);
        if (getCommentColor())
            getCommentColor()->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
CmtFgColorCB_(IlvGraphic* g, IlAny)
{
    CustomizeDialogBox* box =
        (CustomizeDialogBox*)g->GetCurrentCallbackHolder()->getContainer();
    if (box)
        box->CmtFgColorCB(g);
}

// --------------------------------------------------------------------------
void
CustomizeDialogBox::registerCB()
{
    registerCallback("EdtFontCB",		EdtFontCB_);
    registerCallback("EdtBackColor",		EdtBgColorCB_);
    registerCallback("EdtForeColor",		EdtFgColorCB_);
    registerCallback("CommentBackColor",	CmtBgColorCB_);
    registerCallback("CommentForeColor",	CmtFgColorCB_);
    registerCallback("KeywordsBackColor",	KwdBgColorCB_);
    registerCallback("KeywordsForeColor",	KwdFgColorCB_);
    registerCallback("PreprocessorBackColor",	PprBgColorCB_);
    registerCallback("PreprocessorForeColor",	PprFgColorCB_);
    registerCallback("OKCB",			OKCB_);
}

// --------------------------------------------------------------------------
IlvFont*
CustomizeDialogBox::chooseFont(IlvFont* oldF) const
{
    IlUShort count = 0;
    IlvFontSelector fs(getDisplay(), getSystemView());
    const char* const* names = getDisplay()->getFamilyNames(count);
    for(int i = 0 ; i < count ; i++)
        fs.computeSizes(names[i],
                        (IlvFontStyle)(IlvNormalFontStyle|IlvBoldFontStyle|
                                       IlvUnderlinedFontStyle
                                       |IlvItalicFontStyle));
    IlBoolean okFont = IlTrue;
    IlvFont* ch;
    do {
        fs.moveToMouse();
        ch = fs.get(IlFalse);
        if (ch)
            ch->lock();
        else
            okFont = IlTrue;
    } while (!okFont);
    return ch;
}

// --------------------------------------------------------------------------
IlvColor*
CustomizeDialogBox::chooseColor(IlvColor* oldColor) const
{
    IlvColorSelector colorSelector(getDisplay(), getSystemView());
    if (oldColor)
        colorSelector.set(oldColor);
    IlvColor* newColor = colorSelector.get(IlFalse);
    if (newColor)
        newColor->lock();
    return newColor;
}
