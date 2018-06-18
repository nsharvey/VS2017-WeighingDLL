// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/codeedit/src/frame.cpp
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
// Implementation of the EditorFrame class.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/dbgedit.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/gadgets/vframe.h>
#include <ilviews/gadgets/stdialog.h>

#if defined(IL_STD)
#include <cstdlib>
#include <fstream>
IL_STDUSE
#else  /* !IL_STD */
#include <stdlib.h>
#include <fstream.h>
#endif /* !IL_STD */

#include "dialogs.h"
#include "fileedit.h"
#include "frame.h"
#include "mainwin.h"

#if defined(IL_STD)
#define LOADFLAG ios::in
#else
#define LOADFLAG ios::in|ios::nocreate
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
// Save compiler warnings
#pragma warning(push)
// Remove warning on using sprintf
#pragma warning(disable : 4996)
#endif

// --------------------------------------------------------------------------
static void
EditorFocusInCallback(IlvGraphic* g, IlAny mw)
{
    EditorFrame* frame = (EditorFrame*)mw;
    if (frame)
	frame->focusInCB();
}

// --------------------------------------------------------------------------
class MyFrameContentChangedObserver
    : public IlvCodeEditor::ContentChangedObserver
{
public:
    MyFrameContentChangedObserver(IlvViewFrame* frame,
				  IlvMenuItem*  cutItem,
				  IlvMenuItem*  cutButton,
				  IlvMenuItem*  pasteItem,
				  IlvMenuItem*  pasteButton)
    : IlvCodeEditor::ContentChangedObserver(),
      _frame(frame),
      _cutItem(cutItem),
      _cutButton(cutButton),
      _pasteItem(pasteItem),
      _pasteButton(pasteButton) {}

    virtual void	update(const IlvCodeEditor& editor, IlBoolean redraw);

private:
    void		update(IlvMenuItem* item,
			       IlvMenuItem* button,
			       IlBoolean active,
			       IlBoolean redraw);
    void		update(IlvMenuItem* item,
			       IlBoolean active,
			       IlBoolean redraw);
    IlvViewFrame*	_frame;
    IlvMenuItem*	_cutItem;
    IlvMenuItem*	_cutButton;
    IlvMenuItem*	_pasteItem;
    IlvMenuItem*	_pasteButton;
};

// --------------------------------------------------------------------------
void
MyFrameContentChangedObserver::update(const IlvCodeEditor& editor,
				      IlBoolean redraw)
{
    if (_frame) {
	const char* oldTitle = _frame->getTitle();
	int oldLength = (int)strlen(oldTitle);
	IlBoolean wasModified = ('*' == oldTitle[oldLength - 1]);
	IlBoolean isModified = editor.isSaveNeeded();
	if (wasModified != isModified) {
	    // 2 for blank and * + 1 for \0
	    char* newTitle = new char[oldLength + 2 + 1];
	    if (wasModified) {
		// Remove leading " *"
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
		// Save compiler warnings
#pragma warning(push)
		// Remove warning on using strncpy
#pragma warning(disable : 4996)
#endif
		strncpy(newTitle, oldTitle, oldLength - 2);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
		// Restore compiler warnings
#pragma warning(pop)
#endif
		if (oldLength > 2) // security
		    newTitle[oldLength - 2] = '\0';
	    } else {
		// Add " *"
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
		// Save compiler warnings
#pragma warning(push)
		// Remove warning on using sprintf
#pragma warning(disable : 4996)
#endif
		sprintf(newTitle, "%s *", oldTitle);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
		// Restore compiler warnings
#pragma warning(pop)
#endif
	    }
	    _frame->setTitle(newTitle);
	    delete [] newTitle;
	}
    }
    update(_cutItem,
	   _cutButton,
	   editor.hasSelection() && !editor.isReadOnly(),
	   redraw);
    update(_pasteItem, _pasteButton, !editor.isReadOnly(), redraw);
}

// --------------------------------------------------------------------------
void
MyFrameContentChangedObserver::update(IlvMenuItem* item,
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
MyFrameContentChangedObserver::update(IlvMenuItem* item,
				      IlBoolean active,
				      IlBoolean redraw)
{
    item->setSensitive(active);
    if (redraw && item->getMenu())
	item->getMenu()->reDraw();
}

// --------------------------------------------------------------------------
EditorFrame::EditorFrame(IlvCodeEditor::Parser* parser,
			 IlvView* parent,
			 const char* title,
			 const IlvRect& size,
			 IlvCodeEditor::StyleSheet* sheet,
			 IlvMenuItem* cutItem,
			 IlvMenuItem* cutButton,
			 IlvMenuItem* pasteItem,
			 IlvMenuItem* pasteButton,
			 IlBoolean visible)
: IlvViewFrame(parent, title, size, visible),
  _maxPatternSize(1024),
  _stamp(0),
  _contentChangedObserver(0),
  _editor(0)
{
    _saveTrigger = new SaveTrigger(this);
    _editor = createEditor(parent->getDisplay(),
			   IlvRect(0, 0, size.w(), size.h()),
			   parser,
			   sheet);
    _contentChangedObserver =
	new MyFrameContentChangedObserver(this,
					  cutItem,   cutButton,
					  pasteItem, pasteButton);
    _editor->setContentChangedObserver(*_contentChangedObserver);
    _editor->setSaveTrigger(_saveTrigger);

    // Creates the client view of the frame
    _container = new IlvGadgetContainer(this, size, IlFalse, visible);
    _container->addObject(_editor, IlTrue);
    _editor->setNeedsInputContext(IlTrue); // TEST
    setAttachements(_container, _editor);
    showScrollBars();
    _fName = 0;
    _lastPattern = new  char[_maxPatternSize];
    _lastPattern[0] = '\0';
    _editor->addFocusInCallback(EditorFocusInCallback, (IlAny)this);
}

// --------------------------------------------------------------------------
YesNoCancel
EditorFrame::suicide()
{
    YesNoCancel answer = Yes;
    char question[1024];
    if (getFileName())
	sprintf(question, "Save %s before closing ?", getFileName());
    else
	sprintf(question, "Save before closing ?");
    YesNoCancelBox dlg(getDisplay(), question);
    dlg.moveToMouse();
    if (isSaveNeeded()) {
	answer = dlg.ask();
	if (dlg.wasCancel()) // Don't use wasCanceled here
	    return answer;
	if (dlg.wasYes())
	    if (!save())
		return Cancel;
    }
    if (EditorMainWindow::Instance()->getFindDialogBox()
	&& EditorMainWindow::Instance()->getReplaceDialogBox()) {
	EditorMainWindow::Instance()->getFindDialogBox()->setEditor(0);
	EditorMainWindow::Instance()->getReplaceDialogBox()->setEditor(0);
	EditorMainWindow::Instance()->getFindDialogBox()->hide();
	EditorMainWindow::Instance()->getReplaceDialogBox()->hide();
    }
    delete this;
    return answer;
}

// --------------------------------------------------------------------------
#include <sys/stat.h>
char*
EditorFrame::readFileOnDisk(const char* name)
{
    int size = 0;
    struct stat buf; // NOT using stat64 to handle huge files
    int rv = stat(name, &buf);
    if (rv != 0) {
	_inode = 0;
	IlvPrint("Impossible to find %s\n", name);
    } else {
	_inode = buf.st_ino;
	size = buf.st_size;
	std::ifstream streamBuffer(name);
	char* text = new char[size + 1];
	if (streamBuffer && text) {
	    streamBuffer.read(text, size);
	    // This is necessary to take the '\n' translation into account.
	    size = (int)streamBuffer.gcount();  
	    text[size] = '\0';
	    streamBuffer.close();
	    touchStamp(name);
	    return text;
	}
	else IlvPrint("Impossible to read %s\n", name);
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvDebuggerEditor*
EditorFrame::createEditor(IlvDisplay* display,
			  IlvRect bRect,
			  IlvCodeEditor::Parser* parser,
			  IlvCodeEditor::StyleSheet* sheet)
{
    IlvDebuggerEditor* editor =
	new IlvDebuggerEditor(display,
			      bRect,
			      "",
			      IlvDefaultGadgetThickness,
			      sheet,
			      IlvCodeEditor::Binding::MSVCMode,
			      IlvDefaultDebuggerMargin, parser);
    return editor;
}

// --------------------------------------------------------------------------
void
EditorFrame::reloadOnChange()
{
    if (_fName && diskChanged()) {
	IlvIQuestionDialog dlg(getDisplay(),
			       "This file has been modified outside the source editor.\nDo you want to reload it?");
	if (dlg.get()) {
	    loadFile(_fName);
	    // Use of this method ensures consistency
	    _editor->consistentReDraw(); 
	}
	else touchStamp(_fName); // to prevent dialog box reapparition
    }
}

// --------------------------------------------------------------------------
IlBoolean
EditorFrame::diskChanged() const
{
    struct stat statBuf; // NOT using stat64 to handle huge files
    if (stat(_fName, &statBuf) == 0)
	return _stamp < statBuf.st_mtime;
    else
	return IlFalse;
}

// --------------------------------------------------------------------------
void
EditorFrame::touchStamp(const char *filename)
{
    struct stat statBuf; // NOT using stat64 to handle huge files
    if (stat(filename, &statBuf) == 0)
	_stamp = statBuf.st_mtime;
    else
	_stamp = 0;
}

// --------------------------------------------------------------------------
void
EditorFrame::focusInCB()
{
    reloadOnChange();
    _editor->updateObservers();
}

// --------------------------------------------------------------------------
// Overriden virtual IlvViewFrame member
// --------------------------------------------------------------------------
void
EditorFrame::setTitle(const char *title)
{
    IlvViewFrame::setTitle(title);
    FileEditorDesktop* desktop = (FileEditorDesktop*)getDesktopManager();
    if (desktop)
	desktop->updateTitle();
}

// --------------------------------------------------------------------------
#ifdef WINDOWS
# define ACCESS _access
#else
# include <unistd.h>
# define ACCESS access
#endif

IlBoolean
EditorFrame::save()
{
    if (!_fName) {
	EditorMainWindow* mwin = EditorMainWindow::Instance();
	IlvFileBrowser fb(mwin->getDisplay(), mwin->getSystemView());
	fb.setType(IlvFileSelectorSave);
	const char *result = fb.get();
	if (!result)
	    return IlFalse;
	saveFile(result);
	return IlTrue;
    }
    if ((_stamp != 0) && (ACCESS(_fName, 2) == -1)) {
	IlvIWarner warning(getDisplay(),
			   "Cannot save, the file is read-only.",
			   0,
			   IlvDialogOk,
			   getSystemView());
	warning.moveToMouse(IlvTopLeft);
	warning.raise();
	warning.get();
	return IlFalse;
    } else {
	char* text = _editor->getText(IlFalse); // IlFalse = conserve tabs
#if defined(WINDOWS) // To fix the DOS ^M problem
	std::ofstream outf(_fName, std::ios_base::binary|std::ios_base::out);
#else
	std::ofstream outf(_fName);
#endif
	outf << text;
	outf.close();
	touchStamp(_fName);
	delete []text;
	_editor->resetSaveNeeded();
	return IlvTrue;
    }
}

// --------------------------------------------------------------------------
void
EditorFrame::appletViewer()
{
    save();
#if defined(WINDOWS)
    if (_fName ) {
	int nPid = (int)_spawnlp(_P_WAIT,
				 "redirector",
				 "redirector",
				 "appletViewer",
				 _fName,
				 NULL);
	std::ifstream streamBufferOut("freopen.out", std::LOADFLAG);
	EditorMainWindow::Instance()->getConsole()->resetAll();
	char* textOut = new  char[4096];
	if (streamBufferOut && textOut) {
	    streamBufferOut.read(textOut, 4094);
	    int size = (int)streamBufferOut.gcount();
	    textOut[size] = '\n';
	    textOut[size + 1] = '\0';
	    streamBufferOut.close();
	    EditorMainWindow::Instance()->getConsole()->appendText(textOut);
	}
	std::ifstream streamBufferErr("freopen.err", std::LOADFLAG);
	if (streamBufferErr && textOut) {
	    streamBufferErr.read(textOut, 4094);
	    int size = (int)streamBufferErr.gcount();
	    textOut[size] = '\n';
	    textOut[size + 1] = '\0';
	    streamBufferErr.close();
	    EditorMainWindow::Instance()->getConsole()->appendText(textOut);
	}
	EditorMainWindow::Instance()->getConsole()->gotoEnd();
	EditorMainWindow::Instance()->getConsole()->consistentReDraw();
	delete [] textOut;
	getDisplay()->bell();
    }
#endif
}

// --------------------------------------------------------------------------
void
EditorFrame::compile()
{
    save();
#if defined(WINDOWS)
    if (_fName ) {
	char classpath[1024];
	sprintf(classpath, "\"%s\"",
		EditorMainWindow::Instance()
		->getCustomizeDialogBox()->getClassPath());
	char destination[1024];
	sprintf(destination, "\"%s\"",
		EditorMainWindow::Instance()
		->getCustomizeDialogBox()->getDestination());
	// Reassign "stderr" and sdtdout to "freopen.err" and "freopen.out":
	FILE* streamErr = freopen("freopen.err", "w", stderr);
	FILE* streamOut = freopen("freopen.out", "w", stdout);
	if (streamErr == NULL || streamOut == NULL)
	    fprintf(stdout, "error on freopen\n");
	int nPid = (int)_spawnlp(_P_WAIT, "javac", "javac", "-classpath",
				 classpath, "-d", destination, _fName, NULL);
	fclose(streamErr);
	fclose(streamOut);
	fflush(stdout);
	fillConsole();
    }
#endif
}

// --------------------------------------------------------------------------
void
EditorFrame::execute()
{
    save();
#if defined(WINDOWS)
    if (_fName ) {
	char classpath[2048];
	sprintf(classpath,"\"%s;%s\"",
		EditorMainWindow::Instance()
		->getCustomizeDialogBox()->getClassPath(),
		EditorMainWindow::Instance()
		->getCustomizeDialogBox()->getDestination());
    
	char* extension = &_fName[strlen(_fName) -1];
	while (_fName != extension && *extension-- != '.');
	if (_fName == extension)
	    return;
	extension++;

	char baseFileName[512];
	size_t baseNameLength = strlen(_fName) - strlen(extension);
	strncpy(baseFileName, _fName, baseNameLength);
	baseFileName[baseNameLength] = '\0';

	char* className = &baseFileName[strlen(_fName) -1];
	while (className != baseFileName && *className != '\\'
	       && *className != '/')
	    --className;
	if (className != baseFileName)
	    className++;

	// Reassign "stderr" and sdtdout to "freopen.err" and "freopen.out":
	FILE* streamErr = freopen("freopen.err", "w", stderr);
	FILE* streamOut = freopen("freopen.out", "w", stdout);
	if (streamErr == NULL || streamOut == NULL)
	    fprintf(stdout, "error on freopen\n");
	int nPid = (int)_spawnlp(_P_WAIT,
				 "java",
				 "java",
				 "-classpath",
				 classpath,
				 className,
				 NULL);
	fclose(streamErr);
	fclose(streamOut);
	fflush(stdout);
	fillConsole();
    }
#endif
}

// --------------------------------------------------------------------------
void
EditorFrame::fillConsole()
{
#if defined(WINDOWS)
    std::ifstream streamBufferOut("freopen.out", std::LOADFLAG);
    EditorMainWindow::Instance()->getConsole()->resetAll();
    char* textOut = new  char[4096];
    if (streamBufferOut && textOut) {
	streamBufferOut.read(textOut, 4094);
	int size = (int)streamBufferOut.gcount();
	textOut[size] = '\n';
	textOut[size + 1] = '\0';
	streamBufferOut.close();
	EditorMainWindow::Instance()->getConsole()->appendText(textOut);
    }
    std::ifstream streamBufferErr("freopen.err", std::LOADFLAG);
    if (streamBufferErr && textOut) {
	streamBufferErr.read(textOut, 4094);
	int size = (int)streamBufferErr.gcount();
	textOut[size] = '\n';
	textOut[size + 1] = '\0';
	streamBufferErr.close();
	EditorMainWindow::Instance()->getConsole()->appendText(textOut);
    }
    EditorMainWindow::Instance()->getConsole()->gotoEnd();
    EditorMainWindow::Instance()->getConsole()->consistentReDraw();
    delete [] textOut;
    getDisplay()->bell();
#endif
}

// --------------------------------------------------------------------------
void
EditorFrame::genHTML()
{
    save();
#if defined(WINDOWS)
    if (_fName) {
	char* extension = &_fName[strlen(_fName) -1];
	while (_fName != extension && *extension-- != '.');
	if (_fName == extension) return;
	extension++;
	if (strcmp(extension, ".java") == 0) {
	    char htmlFileName[512];
	    size_t baseNameLength = strlen(_fName) - strlen(extension);
	    strncpy(htmlFileName, _fName, baseNameLength);
	    htmlFileName[baseNameLength] = '\0';
	    char* className = &htmlFileName[strlen(htmlFileName) - 1];
	    while ((className != htmlFileName) && (*className != '\\')
		   && (*className != '/'))
		--className;
	    if (className != htmlFileName)
		className++;
	    char className2[512];
	    strcpy(className2, className);
	    strcat(htmlFileName, ".html");
	    std::ofstream fout(htmlFileName);
	    fout     << "<html>" << std::endl
		     << "<head>" << std::endl
		     << "</head>" << std::endl
		     << "<body>" << std::endl
		     << "   <applet code="
		     << className2
		     << " width=300 height=200>" << std::endl
		     << "   <strong>If you see this you don't have a Java-enabled Web brower.</strong>" << std::endl
		     << "   </applet>" << std::endl
		     << "</body>" << std::endl
		     << "</html>" << std::endl;
	    fout.close();
	    EditorMainWindow::Instance()->buildNewFrameEditor(htmlFileName);
	}
    }
#endif
}

// --------------------------------------------------------------------------
void
EditorFrame::insertTag(const char* beginTag,
		       const char* endTag)
{
    if (!_editor->hasSelection())
	return;
    IlInt selectionStartLine    = _editor->getSelectionStartLine();
    IlInt selectionStartColumn  = _editor->getSelectionStartColumn();
    _editor->insertTextReversible(endTag,
				  _editor->getSelectionEndLine(),
				  _editor->getSelectionEndColumn() + 1,
				  IlFalse);
    _editor->insertTextReversible(beginTag,
				  selectionStartLine,
				  selectionStartColumn,
				  IlTrue);
}

// --------------------------------------------------------------------------
#define BANNER_TMPL "// --------------------------------------------------------------------------\n"
static const char* bannerTemplate  = BANNER_TMPL;
static const char* commentTemplate = BANNER_TMPL "// \n" BANNER_TMPL;
// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
static const char*
IlvGetUserName()
{
#if defined(WINDOWS)
    return getenv("USERNAME");
#else
    return getenv("USER");
#endif
}

// --------------------------------------------------------------------------
void
EditorFrame::insertBanner()
{
    IlInt currentLine = _editor->getCursorLine();
    const char* userName = IlvGetUserName();
    char banner[2048];
    sprintf(banner,
	    bannerTemplate,
	    userName ? userName : "",
	    userName ? userName : "");

    _editor->insertTextReversible(banner, currentLine, 0, IlTrue);
    _editor->setCursorLocation(currentLine + 7, 17);
}

// --------------------------------------------------------------------------
void
EditorFrame::insertJavaDocComment()
{
    IlInt currentLine = _editor->getCursorLine();
    _editor->insertTextReversible("/**\n * \n */\n", currentLine, 0, IlTrue);
    _editor->setCursorLocation(currentLine + 1, 2);
}

// --------------------------------------------------------------------------
void
EditorFrame::insertCppDocComment()
{
    IlInt currentLine = _editor->getCursorLine();
    _editor->insertTextReversible(commentTemplate,
				  currentLine,
				  _editor->getCursorColumn(),
				  IlTrue);
    _editor->setCursorLocation(currentLine + 1, 3);
}

// --------------------------------------------------------------------------
void
EditorFrame::insertTTTag()
{
    insertTag("<tt>", "</tt>");
}

// --------------------------------------------------------------------------
void
EditorFrame::insertBoldTag()
{
    insertTag("<B>", "</B>");
}

// --------------------------------------------------------------------------
void
EditorFrame::insertItalicTag()
{
    insertTag("<I>", "</I>");
}

// --------------------------------------------------------------------------
void
EditorFrame::insertCarriageReturn()
{
    _editor->insertTextReversible("<BR>",
				  _editor->getCursorLine(),
				  _editor->getCursorColumn(),
				  IlTrue);
}
