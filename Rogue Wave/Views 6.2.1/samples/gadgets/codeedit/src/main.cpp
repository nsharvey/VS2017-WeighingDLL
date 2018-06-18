// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/codeedit/src/main.cpp
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
// Application entry point.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/codeedit.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/text.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/bitmaps/png.h>

#if defined(IL_STD)
#include <cstdlib>
#include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#include <stdlib.h>
#include <stdio.h>
#endif /* !IL_STD */

#include "dialogs.h"
#include "frame.h"
#include "mainwin.h"

// ==========================================================================
// Specialized IlvDialog for "About..."
// ==========================================================================
static const char VersionID[] = "Rogue Wave Views ";

// --------------------------------------------------------------------------
void
CBCloseAboutBox(IlvView* top, IlAny)
{
    IlvDialog* dlg = (IlvDialog*)top;
    if (dlg)
	dlg->cancel();
}

class AboutBox : public IlvDialog
{
public:
    AboutBox(IlvDisplay* display)
	: IlvDialog(display, "aboutBox", "About", "about.ilv")
    {
	setDestroyCallback(CBCloseAboutBox);
	IlvMessageLabel* versionLabel =
	    (IlvMessageLabel*)getObject("versionMsgLabel");
	if (versionLabel)
	    versionLabel->setLabel(VersionID);
    }
};

IlBoolean EditorMainWindow::Deca = IlFalse;
IlBoolean EditorMainWindow::Cpp  = IlFalse;

// --------------------------------------------------------------------------
IlBoolean
EditorMainWindow::replaceTextByConsoleEditor(IlvNotebook* notebook,
					     int index,
					     const char* name)
{
    // Replacing IlvText by IlvStylableEditor
    IlBoolean res = IlFalse;
    IlvGadgetContainer* gc =
	(IlvGadgetContainer*)notebook->getPages()[index]->getView();
    if (gc) {
	IlvText* ilvText = (IlvText*)gc->getObject(name);
	if (ilvText) {
	    IlvRect boundingBox =  ilvText->bbox();
	    _console = new IlvCodeEditor(getDisplay(), boundingBox,
					 "Java Console", 1,
					 IlvCodeEditor::StyleSheet
					 ::MakeDefault(getDisplay()),
					 2,
					 IlvCodeEditor::Binding::MSVCMode,
					 0);
	    gc->replace(ilvText, _console);
	    _console->scrollBarShowAsNeeded(IlFalse, IlFalse, IlFalse);
	    _console->showScrollBar(IlvVertical, IlTrue);
	    _console->showScrollBar(IlvHorizontal, IlTrue);
	    _console->setEditable(IlFalse);
	    res = IlTrue;
	}
    }
    return res;
}

// --------------------------------------------------------------------------
IlBoolean
EditorMainWindow::closeAll()
{
    IlUInt count = 0;
    IlvViewFrame* const* frames = _desktop->getFrames(count);
    for (;count > 0; --count) {
	EditorFrame* frame = (EditorFrame*)frames[count - 1];
	if (frame)
	    if (frame->suicide() == Cancel)
		return IlFalse;
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
void
EditorMainWindow::customize()
{
    CustomizeDialogBox* optionsDlg =  getCustomizeDialogBox();
    if (optionsDlg && getDesktop()) {
	EditorFrame* fr = getDesktop()->getCurrentEditorFrame();
	if (fr != 0) {	    
	    optionsDlg->setEditor(fr->getEditor());
	    optionsDlg->wait();
	    getDesktop()->propagateSheet(optionsDlg->getStyleSheet());
	    setAcceleratorsTexts();
	}
    }
}

static EditorMainWindow* Singleton = 0;
static const char Title[] = "RW Text Editor";

// --------------------------------------------------------------------------
EditorMainWindow*
EditorMainWindow::Instance()
{
    if (!Singleton) {
	IlvSetLocale(); // Influences the labels and the input method
	IlvDisplay* display = new IlvDisplay(Title, "");
	if (display->isBad()) {
	    delete display;
	    IlvFatalError("Couldn't create display");
	    exit(-1);
	}
	// Influences only the labels not the input method<
	display->setCurrentLanguage(IlvGetSymbol("en_US"));
	display->prependToPath("data");
	display->prependToPath("../data");
	Singleton = new EditorMainWindow(display,
					 Title,
					 Title,
					 IlvRect(0, 0, 700, 800),
					 IlvVertical);
    }
    return Singleton;
}

// --------------------------------------------------------------------------
EditorMainWindow::~EditorMainWindow()
{
    if (_findDialogBox)
	delete _findDialogBox;
    if (_replaceDialogBox)
	delete _replaceDialogBox;
    if (_customizeDlg)
	delete _customizeDlg;
    if (_cursorMovedObserver)
	delete _cursorMovedObserver;
    if (_selectionChangedObserver)
	delete _selectionChangedObserver;
    if (_commandPerformedObserver)
	delete _commandPerformedObserver;
}

// --------------------------------------------------------------------------
IlBoolean
EditorMainWindow::setCallbackAndClientTo(IlvMenuItem* item,
					 IlvGraphicCallback callback)
{
    if (item) {
	item->setCallback(callback);
	item->setClientData(this);
	return IlTrue;
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
void
EditorMainWindow::installAccelerator(IlvMenuItem* item,
				     IlvContainerAction action,
				     const char* accText,
				     IlvEventType type,
				     IlUShort data,
				     IlUShort modifiers)
{
    if (item) {
	item->setAcceleratorText(accText);
	item->setAcceleratorModifiers(modifiers);
	item->setAcceleratorKey(data);
    }
    removeAccelerator(type, data, modifiers);
    addAccelerator(action, type, data, modifiers);
}

// --------------------------------------------------------------------------
void
EditorMainWindow::clearAccelerator(IlvMenuItem* item)
{
    if (item) {
	item->setAcceleratorText("");
	item->setAcceleratorModifiers(0);
	item->setAcceleratorKey(65535);
    }
}

// --------------------------------------------------------------------------
IlvCodeEditor::Binding*
EditorMainWindow::getCurrentBindings()
{
    return getCustomizeDialogBox()->getEditor()->getCommandBindings();
}

// --------------------------------------------------------------------------
// Values for open file action
// --------------------------------------------------------------------------
#if !defined(WIN32)
static const char* const Patterns[] = {
    "*.cpp",
    "*.h",
    "*.java",
    "*.js",
    "*.mak",
    "*.html",
    "*.xml",
    "*.txt",
    "*.*"
};

static const char* const Messages[] = {
    "C++ source files (*.cpp)",
    "C++ header files (*.h)",
    "Java files (*.java)",
    "JavaScript files (*.js)",
    "Makefiles (*.mak)",
    "HTML files (*.html)",
    "XML files (*.xml)",
    "Text files (*.txt)",
    "Any file (*.*)"
};

static int NbPatterns = 9;
#else
static const char* const Patterns[] = {
    "*.cpp|*.C|*.cxx|*.cc|*.c|*.h|*.hxx|*.H|*.hh",
    "*.java|*.grm",
    "*.js",
    "*.mak",
    "*.html|*.htm|*.xml",
    "*.txt",
    "*.*"
};

static const char* const Messages[] = {
    "C++ files (*.cpp;*.C;*.cxx;*.cc;*.c;*.h;*.hxx;*.H;*.hh)",
    "Java files & JACC files(*.java;*.grm)",
    "JavaScript files (*.js)",
    "Makefiles (*.mak)",
    "HTML & XML files (*.html;*.htm;*.xml)",
    "Text files (*.txt)",
    "Any file (*.*)"
};

static int NbPatterns = 7;
#endif

// --------------------------------------------------------------------------
//                          Callbacks
// --------------------------------------------------------------------------
void
CBCloseDialogBox(IlvView* top, IlAny)
{
    IlvDialog* dlg = (IlvDialog*)top;
    if (dlg)
	dlg->cancel();
}

// --------------------------------------------------------------------------
void
CBQuit(IlvView* top, IlAny)
{
    EditorMainWindow* mwin = (EditorMainWindow*)top;
    if (mwin->closeAll()) {
	IlvDisplay* display = top->getDisplay();
	delete top;
	delete display;
	IlvExit(0);
    }
}

// --------------------------------------------------------------------------
static void
CBExit(IlvGraphic* g, IlAny any)
{
    IlvContainer* mwin = (IlvContainer*)any;
    CBQuit(mwin, 0);
}

// --------------------------------------------------------------------------
static void
CBNew(IlvGraphic* g, IlAny any)
{
    ((EditorMainWindow*)any)->buildNewFrameEditor(0);
}

// --------------------------------------------------------------------------
static void
CBOpen(IlvGraphic* g, IlAny any)
{
    EditorMainWindow* mwin = (EditorMainWindow*)any;
    IlvFileBrowser fb(mwin->getDisplay(), 0, 0,
		      NbPatterns, Patterns, Messages);
    const char* result = fb.get();
    if (result)
	mwin->buildNewFrameEditor(result);
}

// --------------------------------------------------------------------------
static void
CBSave(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->save();
}

// --------------------------------------------------------------------------
static void
CBSaveAll(IlvGraphic* g, IlAny any)
{
    IlUInt count = 0;
    const IlvViewFrame* const* frames =
	((EditorMainWindow*)any)->getDesktop()->getFrames(count);
    for(;count > 0 ; --count)  {
	EditorFrame* f = (EditorFrame*)frames[count - 1 ];
	if (f && f->isSaveNeeded())
	    f->save();
    }
}

// --------------------------------------------------------------------------
static void
CBSaveAs(IlvGraphic* g, IlAny any)
{
    EditorMainWindow* mwin = (EditorMainWindow*)any;
    IlvFileBrowser fb(mwin->getDisplay(), mwin->getSystemView());
    fb.setType(IlvFileSelectorSave);
    const char* result = fb.get();
    if (result) {
	EditorFrame* frame = mwin->getDesktop()->getCurrentEditorFrame();
	if (frame)
	    frame->saveFile(result);
    }
}

// --------------------------------------------------------------------------
static void
CBClose(IlvGraphic* g, IlAny any)
{
    EditorMainWindow* mwin = (EditorMainWindow*)any;
    if (mwin) {
	EditorFrame* frame = mwin->getDesktop()->getCurrentEditorFrame();
	if (frame)
	    frame->suicide();
    }
}

// --------------------------------------------------------------------------
static void
CBUndo(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->undo();
}

// --------------------------------------------------------------------------
static void
CBRedo(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->redo();
}

// --------------------------------------------------------------------------
static void
CBReplace(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame = 
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame && ((EditorMainWindow*)any)->getReplaceDialogBox())
	frame->replaceSelection(*((EditorMainWindow*)any)
				->getReplaceDialogBox());
}

// --------------------------------------------------------------------------
static void
CBGoto(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->gotoLine();
}

// --------------------------------------------------------------------------
static void
CBSelectAll(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->selectAll();
}

// --------------------------------------------------------------------------
static void
CBCut(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->cut();
}

// --------------------------------------------------------------------------
static void
CBCopy(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->copy();
}

// --------------------------------------------------------------------------
static void
CBPaste(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->paste();
}

// --------------------------------------------------------------------------
static void
CBFind(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame && ((EditorMainWindow*)any)->getFindDialogBox())
	frame->find(*((EditorMainWindow*)any)->getFindDialogBox());
}

// --------------------------------------------------------------------------
static void
CBFindNext(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame && ((EditorMainWindow*)any)->getFindDialogBox())
	frame->findNext(*((EditorMainWindow*)any)->getFindDialogBox());
}

// --------------------------------------------------------------------------
static void
CBFindPrevious(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame && ((EditorMainWindow*)any)->getFindDialogBox())
	frame->findPrevious(*((EditorMainWindow*)any)->getFindDialogBox());
}

// --------------------------------------------------------------------------
static void
CBIndent(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->indent();
}

// --------------------------------------------------------------------------
static void
CBOutdent(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->outdent();
}

// --------------------------------------------------------------------------
static void
CBCommentRegion(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->commentRegion();
}

// --------------------------------------------------------------------------
static void
CBKillComment(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->killComment();
}

// --------------------------------------------------------------------------
static void
CBRecenter(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->recenter();
}

// --------------------------------------------------------------------------
static void
CBCompleteWord(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->completeWord();
}

// --------------------------------------------------------------------------
static void
CBAbout(IlvGraphic* g, IlAny any)
{
    AboutBox box(((EditorMainWindow*)any)->getDisplay());
    box.wait();
}

// --------------------------------------------------------------------------
static void
CBCascade(IlvGraphic* g, IlAny any)
{
    ((EditorMainWindow*)any)->getDesktop()->cascadeFrames();
}

// --------------------------------------------------------------------------
static void
CBTileVertically(IlvGraphic* g, IlAny any)
{
    ((EditorMainWindow*)any)->getDesktop()->tileFrames(IlTrue);
}

// --------------------------------------------------------------------------
//static void
//CBViewJavaToolbar(IlvGraphic* g, IlAny any)
//{
//    ((EditorMainWindow*)any)->showDecaToolBar();
//}

// --------------------------------------------------------------------------
static void
CBViewJavaConsole(IlvGraphic* g, IlAny any)
{
    ((EditorMainWindow*)any)->showConsole();
}

// --------------------------------------------------------------------------
static void
CBTileHorizontally(IlvGraphic* g, IlAny any)
{
    ((EditorMainWindow*)any)->getDesktop()->tileFrames(IlFalse);
}

// --------------------------------------------------------------------------
static void
CBCustomize(IlvGraphic* g, IlAny any)
{
    ((EditorMainWindow*)any)->customize();
}

// --------------------------------------------------------------------------
static void
CBUnsetAllErrors(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->unsetAllErrors();
}

// --------------------------------------------------------------------------
static void
CBTest(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->testSymbols();
}

// --------------------------------------------------------------------------
static void
CBBreakPoint(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->breakPoint();
}

// --------------------------------------------------------------------------
static void
CBCompile(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->compile();
}
// --------------------------------------------------------------------------
static void
CBJava(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->execute();
}

// --------------------------------------------------------------------------
static void
CBAppletViewer(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->appletViewer();
}

// --------------------------------------------------------------------------
static void
CBInsertJavaDocComment(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertJavaDocComment();
}
// --------------------------------------------------------------------------
static void
CBInsertCppDocComment(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertCppDocComment();
}
// --------------------------------------------------------------------------
static void
CBGenHTML(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->genHTML();
}
// --------------------------------------------------------------------------
static void
CBInsertBanner(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertBanner();
}
// --------------------------------------------------------------------------
static void
CBInsertTTTag(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertTTTag();
}
// --------------------------------------------------------------------------
static void
CBInsertBoldTag(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertBoldTag();
}
// --------------------------------------------------------------------------
static void
CBInsertItalicTag(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertItalicTag();
}
// --------------------------------------------------------------------------
static void
CBInsertCarriageReturn(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->insertCarriageReturn();
}

// --------------------------------------------------------------------------
static void
CBRemoveAllBreakPoints(IlvGraphic* g, IlAny any)
{
    EditorFrame* frame =
	((EditorMainWindow*)any)->getDesktop()->getCurrentEditorFrame();
    if (frame)
	frame->removeAllBreakPoints();
}

// --------------------------------------------------------------------------
static void
CBChangeCurrentFrame(IlvGraphic* g, IlAny any)
{
    IlvPopupMenu* menu = (IlvPopupMenu*)g;
    if (menu && any) {
	EditorMainWindow* ed = (EditorMainWindow*)any;
	const char* label = menu->getItem(menu->whichSelected())->getLabel();
	for (IlUInt i = 0; i < ed->getDesktop()->getCardinal(); i++) {
	    if (!strcmp(label, ed->getDesktop()->getFrame(i)->getTitle())) {
		ed->getDesktop()
		    ->setCurrentFrame(ed->getDesktop()->getFrame(i));
		return;
	    }
	}
    }
}

// --------------------------------------------------------------------------
static void
CBUpdateWindows(IlvGraphic* g, IlAny any)
{
    EditorMainWindow::Instance()->updateWindows();
}

// --------------------------------------------------------------------------
void
EditorMainWindow::updateWindows()
{
    IlvPopupMenu* menu = getMenuWindow();
    menu->autoLabelAlignment(IlFalse, IlFalse);
    IlvGadgetItem* separator = getStartBufferItem();
    if (!separator)
	return;
    IlUShort index = (IlUShort)(menu->getIndex(separator) + 1);
    // First remove all the items after separator
    while (menu->getCardinal() != index)
	menu->removeItem((IlUShort)(menu->getCardinal() - 1));
    // Then add the new  buffers
    for (IlUInt i = 0; i < getDesktop()->getCardinal(); i++) {
	menu->insertLabel(index, getDesktop()->getFrame(i)->getTitle());
	setCallbackAndClientTo(menu->getItem(index++), CBChangeCurrentFrame);
    }
    menu->autoLabelAlignment(IlTrue, IlFalse);
}

// --------------------------------------------------------------------------
//                          Accelerators
// --------------------------------------------------------------------------
#define CREATEACC(cl) \
static void Acc##cl(IlvContainer* mwin, IlvEvent&, IlAny) \
{ CB##cl(0, mwin); }

CREATEACC(Exit);
CREATEACC(New);
CREATEACC(Open);
CREATEACC(Save);
CREATEACC(SaveAll);
CREATEACC(SaveAs);
CREATEACC(Undo);
CREATEACC(Redo);
CREATEACC(Replace);
CREATEACC(Goto);
CREATEACC(SelectAll);
CREATEACC(Cut);
CREATEACC(Copy);
CREATEACC(Paste);
CREATEACC(Find);
CREATEACC(FindNext);
CREATEACC(FindPrevious);
CREATEACC(Cascade);
CREATEACC(TileVertically);
CREATEACC(Customize);
CREATEACC(UnsetAllErrors);
CREATEACC(Test);
CREATEACC(BreakPoint);
CREATEACC(RemoveAllBreakPoints);
CREATEACC(ChangeCurrentFrame);
CREATEACC(UpdateWindows);

// --------------------------------------------------------------------------
void
EditorMainWindow::buildNewFrameEditor(const char* name)
{
    EditorFrame* frame =
	getDesktop()->buildNewFrame(name, IlvRect(0, 0, 300, 300),
				    getCustomizeDialogBox()->getStyleSheet(),
				    getCutItem(), getCutButton(),
				    getPasteItem(), getPasteButton());
    if (frame) {
	IlvCodeEditor* editor = frame->getEditor();
	editor->setCursorMovedObserver(*_cursorMovedObserver);
	editor->setSelectionChangedObserver(*_selectionChangedObserver);
	editor->setCommandPerformedObserver(*_commandPerformedObserver);
	if (name)
	    frame->loadFile(name);
	getDesktop()->setCurrentFrame(frame);
	frame->reDrawClient();
    }
}

// --------------------------------------------------------------------------
IlvGraphic*
EditorMainWindow::loadILV(IlvDisplay* display, const char* filename) const
{
    const char* fullPath = 0;
    std::istream* inf =
	display->createStreamInPath(filename, IlFalse, IlFalse, &fullPath);
    IlvInputFile ins(*inf);
    IlUInt count = 0;
    IlvGraphic* const* tab = ins.readObjects(display, count);
    delete inf;
    return tab[0];
}

// --------------------------------------------------------------------------
void
EditorMainWindow::setAcceleratorsTexts()
{
    IlvCodeEditor::Binding* bindings = getCurrentBindings();
    if (bindings) {
	char a[32];
	a[0] = '\0';
	IlvEventType t;
	IlUShort d;
	IlUShort m;
	if (bindings->getAccelerator(bindings->UndoAccelerator, a, t, d, m))
	    installAccelerator(getUndoItem(), AccUndo, a, t, d, m);
	else
	    clearAccelerator(getUndoItem());
	if (bindings->getAccelerator(bindings->RedoAccelerator, a, t, d, m))
	    installAccelerator(getRedoItem(), AccRedo, a, t, d, m);
	else
	    clearAccelerator(getRedoItem());
	if (bindings->getAccelerator(bindings->CutAccelerator, a, t, d, m))
	    installAccelerator(getCutItem(), AccCut, a, t, d, m);
	else
	    clearAccelerator(getCutItem());
	if (bindings->getAccelerator(bindings->CopyAccelerator, a, t, d, m))
	    installAccelerator(getCopyItem(), AccCopy, a, t, d, m);
	else
	    clearAccelerator(getCopyItem());
	if (bindings->getAccelerator(bindings->PasteAccelerator, a, t, d, m))
	    installAccelerator(getPasteItem(), AccPaste, a, t, d, m);
	else
	    clearAccelerator(getPasteItem());
	if (bindings->getAccelerator(bindings->SelectAllAccelerator,
				     a, t, d, m))
	    installAccelerator(getSelectAllItem(), AccPaste, a, t, d, m);
	else
	    clearAccelerator(getSelectAllItem());
	if (bindings->getAccelerator(bindings->SearchAccelerator,
				     a, t, d, m))
	    installAccelerator(getFindItem(), AccFind, a, t, d, m);
	else
	    clearAccelerator(getFindItem());
	if (bindings->getAccelerator(bindings->FindNextAccelerator,
				     a, t, d, m))
	    installAccelerator(getFindNextItem(), AccFindNext, a, t, d, m);
	else
	    clearAccelerator(getFindNextItem());
	if (bindings->getAccelerator(bindings->FindPreviousAccelerator,
				     a, t, d, m))
	    installAccelerator(getFindPreviousItem(), AccFindPrevious,
			       a, t, d, m);
	else
	    clearAccelerator(getFindPreviousItem());
	if (bindings->getAccelerator(bindings->ReplaceAccelerator,
				     a, t, d, m))
	    installAccelerator(getReplaceItem(), AccReplace, a, t, d, m);
	else
	    clearAccelerator(getReplaceItem());
	if (bindings->getAccelerator(bindings->GotoAccelerator, a, t, d, m))
	    installAccelerator(getGotoItem(), AccGoto, a, t, d, m);
	else
	    clearAccelerator(getGotoItem());
	if (bindings->getAccelerator(bindings->NewAccelerator, a, t, d, m))
	    installAccelerator(getNewItem(), AccNew, a, t, d, m);
	else
	    clearAccelerator(getNewItem());
	if (bindings->getAccelerator(bindings->OpenAccelerator, a, t, d, m))
	    installAccelerator(getOpenItem(), AccOpen, a, t, d, m);
	else
	    clearAccelerator(getOpenItem());
	if (bindings->getAccelerator(bindings->SaveAccelerator, a, t, d, m))
	    installAccelerator(getSaveItem(), AccSave, a, t, d, m);
	else
	    clearAccelerator(getSaveItem());
	if (bindings->getAccelerator(bindings->QuitAccelerator, a, t, d, m))
	    installAccelerator(getExitItem(), AccExit, a, t, d, m);
	else
	    clearAccelerator(getExitItem());
    }
}

// --------------------------------------------------------------------------
void EditorMainWindow::setCallbacks()
{
    setCallbackAndClientTo(getSaveAsItem(), CBSaveAs);
    setCallbackAndClientTo(getSaveAllItem(), CBSaveAll);
    setCallbackAndClientTo(getOptionsItem(), CBCustomize);
    setCallbackAndClientTo(getCascadeItem(), CBCascade);
    setCallbackAndClientTo(getTileHorizontallyItem(), CBTileHorizontally);
    setCallbackAndClientTo(getTileVerticallyItem(), CBTileVertically);
//    setCallbackAndClientTo(getViewJavaToolbarItem(), CBViewJavaToolbar);
    setCallbackAndClientTo(getViewJavaConsoleItem(), CBViewJavaConsole);
    setCallbackAndClientTo(getNewItem(), CBNew);
    setCallbackAndClientTo(getOpenItem(), CBOpen);
    setCallbackAndClientTo(getCloseItem(), CBClose);
    setCallbackAndClientTo(getSaveItem(), CBSave);
    setCallbackAndClientTo(getSaveAllItem(), CBSaveAll);
    setCallbackAndClientTo(getSaveAsItem(), CBSaveAs);
    setCallbackAndClientTo(getExitItem(), CBExit);
    setCallbackAndClientTo(getUndoItem(), CBUndo);
    setCallbackAndClientTo(getRedoItem(), CBRedo);
    setCallbackAndClientTo(getGotoItem(), CBGoto);
    setCallbackAndClientTo(getReplaceItem(), CBReplace);
    setCallbackAndClientTo(getSelectAllItem(), CBSelectAll);
    setCallbackAndClientTo(getCutItem(), CBCut);
    setCallbackAndClientTo(getCopyItem(), CBCopy);
    setCallbackAndClientTo(getPasteItem(), CBPaste);
    setCallbackAndClientTo(getCascadeItem(), CBCascade);
//    setCallbackAndClientTo(getTestItem(), CBTest);
//    setCallbackAndClientTo(getBreakPointItem(), CBBreakPoint);
//    setCallbackAndClientTo(getRemoveAllBreakPointsItem(),
//			   CBRemoveAllBreakPoints);
    setCallbackAndClientTo(getOptionsItem(), CBCustomize);
//    setCallbackAndClientTo(getUnsetAllErrorsItem(), CBUnsetAllErrors);
    setCallbackAndClientTo(getFindItem(), CBFind);
    setCallbackAndClientTo(getFindNextItem(), CBFindNext);
    setCallbackAndClientTo(getFindPreviousItem(), CBFindPrevious);
    setCallbackAndClientTo(getRecenterItem(), CBRecenter);
    setCallbackAndClientTo(getIndentItem(), CBIndent);
    setCallbackAndClientTo(getOutdentItem(), CBOutdent);
    setCallbackAndClientTo(getCommentItem(), CBCommentRegion);
    setCallbackAndClientTo(getUncommentItem(), CBKillComment);
    setCallbackAndClientTo(getCompleteWordItem(), CBCompleteWord);
    setCallbackAndClientTo(getAboutItem(), CBAbout);

    // Buttons
    setCallbackAndClientTo(getNewButton(), CBNew);
    setCallbackAndClientTo(getOpenButton(), CBOpen);
    setCallbackAndClientTo(getSaveButton(), CBSave);
    setCallbackAndClientTo(getSaveAllButton(), CBSaveAll);
    setCallbackAndClientTo(getUndoButton(), CBUndo);
    setCallbackAndClientTo(getRedoButton(), CBRedo);
    setCallbackAndClientTo(getCutButton(), CBCut);
    setCallbackAndClientTo(getCopyButton(), CBCopy);
    setCallbackAndClientTo(getPasteButton(), CBPaste);
//    setCallbackAndClientTo(getBreakpointButton(), CBBreakPoint);
    setCallbackAndClientTo(getInsertCppDocCommentButton(), 
			   CBInsertCppDocComment);
//    setCallbackAndClientTo(getCompileButton(), CBCompile);
//    setCallbackAndClientTo(getJavaButton(), CBJava);
//    setCallbackAndClientTo(getAppletViewerButton(), CBAppletViewer);
//    setCallbackAndClientTo(getGenHTMLButton(), CBGenHTML);
//    setCallbackAndClientTo(getInsertBannerButton(), CBInsertBanner);
//    setCallbackAndClientTo(getInsertTTTagButton(), CBInsertTTTag);
//    setCallbackAndClientTo(getInsertBoldTagButton(), CBInsertBoldTag);
//    setCallbackAndClientTo(getInsertItalicTagButton(), CBInsertItalicTag);
//    setCallbackAndClientTo(getInsertCarriageReturnButton(),
//			   CBInsertCarriageReturn);
//    setCallbackAndClientTo(getInsertJavaDocCommentButton(),
//			   CBInsertJavaDocComment);
}

// --------------------------------------------------------------------------
class MyCursorMovedObserver : public IlvCodeEditor::CursorMovedObserver
{
public:
    MyCursorMovedObserver(IlvTextField* target)
	: IlvCodeEditor::CursorMovedObserver(),
	  _target(target) {}
    virtual void	update(const IlvCodeEditor& editor,
			       IlBoolean redraw);
private:
    IlvTextField*	_target;
};

// --------------------------------------------------------------------------
void
MyCursorMovedObserver::update(const IlvCodeEditor& editor,
			      IlBoolean redraw)
{
    if (_target) {
	const IlvCodeEditor::Location& cursor = editor.getCursorLocation();
	char lineCol[128];
	if (editor.getBindingMode() == IlvCodeEditor::Binding::EmacsMode) {
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
	    // Save compiler warnings
#pragma warning(push)
	    // Remove warning on using sprintf
#pragma warning(disable : 4996)
#endif
	    sprintf(lineCol,
		    "--Emacs-mode---L%d--C%d----------------------------------------",
		    cursor.getLine()+1, cursor.getColumn()+1);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
	    // Restore compiler warnings
#pragma warning(pop)
#endif
	    IlvPalette* palette =  _target->getPalette();
	    if (palette && (palette->getForeground()->getValue() == 0))
		_target->setPalette(editor.getDisplay()->getInvertedPalette(palette));
	} else {
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
	    // Save compiler warnings
#pragma warning(push)
	    // Remove warning on using sprintf
#pragma warning(disable : 4996)
#endif
	    sprintf(lineCol, "Ln %d, Col %d",
		    cursor.getLine()+1,
		    cursor.getColumn()+1);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
	    // Restore compiler warnings
#pragma warning(pop)
#endif
	    IlvPalette* palette =  _target->getPalette();
	    if (palette && (palette->getForeground()->getValue() != 0))
		_target->setPalette(editor.getDisplay()->
				    getInvertedPalette(palette));
	}
	_target->setLabel(lineCol, IlTrue);
    }
}

// --------------------------------------------------------------------------
class MyCommandPerformedObserver
    : public IlvCodeEditor::CommandPerformedObserver
{
public:
    MyCommandPerformedObserver(IlvMenuItem* undoItem,
			       IlvMenuItem* undoButton,
			       IlvMenuItem* redoItem,
			       IlvMenuItem* redoButton)
    : IlvCodeEditor::CommandPerformedObserver(),
      _undoItem(undoItem),
      _undoButton(undoButton),
      _redoItem(redoItem),
      _redoButton(redoButton) {}

     virtual void	update(const IlvCodeEditor& editor, IlBoolean redraw);

private:
    void		update(IlvMenuItem* item,
			       IlvMenuItem* button,
			       IlBoolean active,
			       IlBoolean redraw);
    void		update(IlvMenuItem* item,
			       IlBoolean active,
			       IlBoolean redraw);
    IlvMenuItem*	_undoItem;
    IlvMenuItem*	_undoButton;
    IlvMenuItem*	_redoItem;
    IlvMenuItem*	_redoButton;
};

// --------------------------------------------------------------------------
void
MyCommandPerformedObserver::update(const IlvCodeEditor& editor,
			           IlBoolean redraw)
{
    update(_undoItem, _undoButton, editor.isUndoable(), redraw);
    update(_redoItem, _redoButton, editor.isRedoable(), redraw);
}

// --------------------------------------------------------------------------
void
MyCommandPerformedObserver::update(IlvMenuItem* item,
				   IlvMenuItem* button,
				   IlBoolean active,
			           IlBoolean redraw)
{
    if (item)
	update(item, active, redraw);
    if (button)
	update(button, active, redraw);
}

// --------------------------------------------------------------------------
void
MyCommandPerformedObserver::update(IlvMenuItem* item,
				   IlBoolean active,
			           IlBoolean redraw)
{
    item->setSensitive(active);
    if (redraw && item->getMenu())
	item->getMenu()->reDraw();
}

// --------------------------------------------------------------------------
// Class MySelectionChangedObserver
// --------------------------------------------------------------------------
class MySelectionChangedObserver
    : public IlvCodeEditor::SelectionChangedObserver
{
public:
    MySelectionChangedObserver(IlvMenuItem* cutItem,
			       IlvMenuItem* cutButton,
			       IlvMenuItem* copyItem,
			       IlvMenuItem* copyButton,
			       IlvMenuItem* pasteItem,
			       IlvMenuItem* pasteButton)
	: IlvCodeEditor::SelectionChangedObserver(),
	  _cutItem(cutItem),
	  _cutButton(cutButton),
	  _copyItem(copyItem),
	  _copyButton(copyButton),
	  _pasteItem(pasteItem),
	  _pasteButton(pasteButton) {}

    virtual void	update(const IlvCodeEditor& editor,
			       IlBoolean redraw);
private:
    void		update(IlvMenuItem* item,
			       IlvMenuItem* button,
			       IlBoolean active,
			       IlBoolean redraw);
    void		update(IlvMenuItem* item,
			       IlBoolean active,
			       IlBoolean redraw);

    IlvMenuItem*	_cutItem;
    IlvMenuItem*	_cutButton;
    IlvMenuItem*	_copyItem;
    IlvMenuItem*	_copyButton;
    IlvMenuItem*	_pasteItem;
    IlvMenuItem*	_pasteButton;
};

// --------------------------------------------------------------------------
void
MySelectionChangedObserver::update(const IlvCodeEditor& editor,
			           IlBoolean redraw)
{
    bool hasSel = editor.hasSelection();
    update(_copyItem, _copyItem, hasSel, redraw);
    update(_cutItem, _cutButton, hasSel && !editor.isReadOnly(), redraw);
}

// --------------------------------------------------------------------------
void
MySelectionChangedObserver::update(IlvMenuItem* item,
				   IlvMenuItem* button,
				   IlBoolean active,
			           IlBoolean redraw)
{
    if (item)
	update(item, active, redraw);
    if (button)
	update(button, active, redraw);
}

// --------------------------------------------------------------------------
void
MySelectionChangedObserver::update(IlvMenuItem* item,
				   IlBoolean active,
			           IlBoolean redraw)
{
    item->setSensitive(active);
    if (redraw && item->getMenu())
	item->getMenu()->reDraw();
}

// --------------------------------------------------------------------------
void
EditorMainWindow::createObservers()
{
    _cursorMovedObserver = new MyCursorMovedObserver(_statusBar);
    _selectionChangedObserver =
	new MySelectionChangedObserver(getCutItem(), getCutButton(),
				       getCopyItem(), getCopyButton(),
				       getPasteItem(), getPasteButton());
    _commandPerformedObserver =
	new MyCommandPerformedObserver(getUndoItem(), getUndoButton(),
				       getRedoItem(), getRedoButton());
}

// --------------------------------------------------------------------------
EditorMainWindow::EditorMainWindow(IlvDisplay* display,
				   const char* name,
				   const char* title,
				   IlvRect rect,
				   IlvDirection dir)
    : IlvDockableContainer(display,
			   name,
			   title,
			   rect,
			   dir,
			   0,		// properties
			   IlFalse),	// visible
    _desktop(0),
    _findDialogBox(0),
    _replaceDialogBox(0),
    _customizeDlg(0)
{
    createOrthogonalDockableContainer(IlTrue);
    setDestroyCallback(CBQuit);

    // Lazy creation for _findDialogBox, _replaceDialogBox, and _customizeDlg

    // Create the menu bar
    _menuBar = (IlvToolBar*)loadILV(display, "mbar.ilv");
    _menuBar->setConstraintMode(IlTrue);

    // Create the tool bar
    _toolBar = (IlvToolBar*)loadILV(display, "tbar.ilv");
    _toolBar->setConstraintMode(IlTrue);

    // Create the deca tool bar
//    _decaToolBar = (IlvToolBar*)loadILV(display, "tbardeca.ilv");
//    _decaToolBar->setConstraintMode(IlTrue);

    // Adding menu bar and tool bar inside panes
    IlvPane* menuBarPane = new IlvAbstractBarPane("MenuBarPane", _menuBar);
    addDockingPane(menuBarPane);
    IlvPane* toolBarPane = new IlvAbstractBarPane("ToolBarPane", _toolBar);
    addDockingPane(toolBarPane);
//    _decaToolBarPane = new IlvAbstractBarPane("ToolBarPane", _decaToolBar);
//    addDockingPane(_decaToolBarPane);

    // Add an horizontal paned Container
    IlvDockableContainer* horContainer =
	new IlvDockableContainer(this,
				 IlvRect(0, 0, 640, 100),
				 IlvHorizontal);
    horContainer->createOrthogonalDockableContainer(IlTrue);
    IlvPane* nestedPane = new  IlvViewPane("Main Area", horContainer);
    nestedPane->setResizeMode(IlvPane::Elastic);
    addPane(nestedPane);

    // Creating the notebook and the console as a read-only IlvEditor
    // replacing an existing IlvText(attached to the notebook with Studio)
    IlvGadgetContainer* nbCont =
	new IlvGadgetContainer(this,
			       IlvRect(0, 0, 800, 120),
			       IlFalse,
			       IlTrue);
    nbCont->readFile("notebook.ilv");
    IlvNotebook* notebook = (IlvNotebook*)nbCont->getObject("LowerNB");
    replaceTextByConsoleEditor (notebook, 0, "Console");
    // Adding the console inside a pane
    _consolePane = new  IlvViewPane("Console", nbCont);
    _consolePane->setResizeMode(IlvPane::Elastic);
    addDockingPane(_consolePane);
    if (!EditorMainWindow::Deca)
	_consolePane->hide();
//    if (EditorMainWindow::Cpp)
//	_decaToolBarPane->hide();

    // Create the status bar
    _statusBar = (IlvTextField*)loadILV(display, "statusbar.ilv");
    _statusBar->setLabel("");
    _statusBar->setEditable(IlFalse);

    // Add the status bar inside a pane
    IlvPane* statusBarPane = new IlvGraphicPane("Status Bar", _statusBar);
    addDockingPane(statusBarPane);
    // Create the minibuffer bar
    _minibufferBar = (IlvTextField*)loadILV(display, "minibuffer.ilv");
    _minibufferBar->setLabel("");
    _minibufferBar->setEditable(IlFalse);

    // Add the minibuffer bar inside a pane
    IlvPane* minibufferBarPane =
	new IlvGraphicPane("Minibuffer", _minibufferBar);
    addDockingPane(minibufferBarPane);
    // Add a view Pane with a gadget container connected (MDI area)
    IlvGadgetContainer* gadCont =
	new IlvGadgetContainer(this, IlvRect(0, 0, 100, 100));
    IlvPane* mainPane = new  IlvViewPane("Main View", gadCont);
    mainPane->setResizeMode(IlvPane::Elastic);
    horContainer->addPane(mainPane);
    // Creating the global listeners
    SaveAllTrigger* saveAll = new SaveAllTrigger(this);
    KillBufferTrigger* killBuffer = new KillBufferTrigger(this);
    OpenTrigger* open = new OpenTrigger(this);
    QuitTrigger* quit = new QuitTrigger(this);
    FindTrigger* find = new FindTrigger(this);
    ReplaceTrigger* replace = new ReplaceTrigger(this);
    GotoTrigger* gotoT = new GotoTrigger(this);
    _desktop = new FileEditorDesktop(gadCont,
				     saveAll,
				     open,
				     killBuffer,
				     quit,
				     find,
				     replace,
				     gotoT);
    _desktop->makeMaximizedStateButtons(_menuBar);
    createObservers();

    IlvPopupMenu* menu = getMenuWindow();
    if (menu)
	menu->setOpenMenuCallback(CBUpdateWindows);
    fitToContents();
    resize(750, 700);

    // Registering the callbacks and the accelerators and updating the menu
    // items.
    // Beware the customize dialog box should exists at this point
    setAcceleratorsTexts(); 
    setCallbacks();
    updatePanes(IlTrue);
}

// --------------------------------------------------------------------------
// Triggers
// --------------------------------------------------------------------------
IlBoolean
SaveTrigger::action()
{
    return _frame->save();
}

// --------------------------------------------------------------------------
IlBoolean
SaveAllTrigger::action()
{
    CBSaveAll(0, _mwin);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
OpenTrigger::action()
{
    CBOpen(0, _mwin);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
QuitTrigger::action()
{
    CBExit(0,_mwin);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
KillBufferTrigger::action()
{
    CBClose(0, _mwin);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
FindTrigger::action()
{
    CBFind(0, _mwin);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
ReplaceTrigger::action()
{
    CBReplace(0, _mwin);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
GotoTrigger::action()
{
    CBGoto(0, _mwin);
    return IlTrue;
}

// **************************************************************************
// Entry Point
// **************************************************************************
int main(int argc, char* argv[])
{
    if (argc > 1) {
	for (int i = argc; i - 1 > 0; i--) {
	    if (strcmp(argv[i - 1], "-deca") == 0)
		EditorMainWindow::Deca = IlTrue;
	    if (strcmp(argv[i - 1], "-cpp") == 0)
		EditorMainWindow::Cpp = IlTrue;
	}
    }
    // Create the Main Window as a Dockable Container
    EditorMainWindow::Instance()->show();
    if (argc > 1) {
	for (int i = argc; i - 1 > 0; i--) {
	    if (0 != strncmp(argv[i - 1], "-", 1))
		EditorMainWindow::Instance()->buildNewFrameEditor(argv[i-1]);
	}
    }
    IlvMainLoop();
    return 0;
}
