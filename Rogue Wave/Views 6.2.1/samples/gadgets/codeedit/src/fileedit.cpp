// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/codeedit/src/fileedit.cpp
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
// Implementation of the FileEditorDesktop class.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/codeedit.h>
#include <ilviews/graphics/selector.h>
#if defined(IL_STD)
#include <cstdio>
#include <cmath>
IL_STDUSE
#else  /* !IL_STD */
#include <stdio.h>
#include <math.h>
#endif /* !IL_STD */
#include <sys/stat.h>

#include "dialogs.h"
#include "fileedit.h"
#include "mainwin.h"

// --------------------------------------------------------------------------
static void
DestroyFrame(IlvView* view, IlAny)
{
    EditorFrame* editorFrame = (EditorFrame*)view;
    if (editorFrame)
	editorFrame->suicide();
}

// --------------------------------------------------------------------------
FileEditorDesktop::FileEditorDesktop(IlvView* view,
				     SaveAllTrigger* saveAll,
				     OpenTrigger* open, 
				     KillBufferTrigger* killBuffer,
				     QuitTrigger* quit,
				     FindTrigger* find,
				     ReplaceTrigger* replace,
				     GotoTrigger* gotoT)
  : IlvDesktopManager(view),
    _newFrameLocation(0, 0),
    _frameCount(0),
    _saveAllTrigger(saveAll),
    _openTrigger(open),
    _killBufferTrigger(killBuffer),
    _quitTrigger(quit),
    _findTrigger(find),
    _replaceTrigger(replace),
    _gotoTrigger(gotoT)
{
    // Get ready for any recognized file
    IlvCodeEditor::Parser* parser = IlvCodeEditor::Parser::CreateCPPParser();
    parser->associate("cpp");
    parser->associate("c");
    parser->associate("cc");
    parser->associate("cxx");
    parser->associate("C");
    parser->associate("h");
    parser->associate("hh");
    parser->associate("hxx");
    parser = IlvCodeEditor::Parser::CreateHTMLParser();
    parser->associate("htm");
    parser->associate("html");
    IlvCodeEditor::Parser::CreateJavaParser()->associate("java");
    IlvCodeEditor::Parser::CreateJavaScriptParser()->associate("js");
    IlvCodeEditor::Parser::CreateDefaultParser()->associate("txt");
    IlvCodeEditor::Parser::CreateMakefileParser()->associate("mak");
}

// --------------------------------------------------------------------------
FileEditorDesktop::~FileEditorDesktop() {}

// --------------------------------------------------------------------------
void
FileEditorDesktop::tileFrames(IlBoolean vertically)
{
    if (getCardinal() == 0)
	return;
    if (isMaximizing())
	restoreFrames();
    IlvRect bbox;
    getView()->boundingBox(bbox);
    IlUInt nbOfMinimizedFrames = 0;
    getMinimizedFrames(nbOfMinimizedFrames);
    IlUInt nbOfFramesToTile = getCardinal() - nbOfMinimizedFrames;
    IlUInt nbTiles = (IlUInt)floor(sqrt((double)nbOfFramesToTile));
    IlUInt nbRows  = nbTiles;
    IlUInt nbCols  = nbTiles;
    IlUInt even	   = 1;
    while (nbRows * nbCols < nbOfFramesToTile) {
	if (vertically) {
	    if (even)
		nbCols++;
	    else
		nbRows++;
	} else {
	    if (even)
		nbRows++;
	    else
		nbCols++;
	}
	even = !even;
    }
    IlUInt tileH   = bbox.h() / nbRows;
    IlUInt tileW   = bbox.w() / nbCols;
    for(IlUInt k = 0, i = 0 ; k < getCardinal() ; k++) {
	if (getFrame(k)->getCurrentState()
	    != IlvViewFrame::IlvFrameMinimizedState) {
	    IlUInt row = 0, col = 0;
	    if (vertically) {
		row = i	 / nbCols;
		col = i % nbCols;
	    } else {
		col = i / nbRows;
		row = i % nbRows;
	    }
	    IlUInt x   = col * tileW, y	  = row * tileH;
	    getFrame(k)->moveResize(IlvRect(x, y, tileW, tileH));
	    getFrame(k)->adjustClientSize();
	    ++i;
	}
    }
}

// --------------------------------------------------------------------------
void
FileEditorDesktop::updateTitle()
{
    IlString title("RW Code Editor");
    IlvViewFrame* cFrame = getCurrentFrame();
    if (cFrame && isMaximizing()) {
	title.catenate(" - [");
	title.catenate(cFrame->getTitle());
	title.catenate("]");
    }
    EditorMainWindow::Instance()->setTitle(title);
}

// --------------------------------------------------------------------------
EditorFrame*
FileEditorDesktop::buildNewFrame(const char* title,
				 const IlvRect& rect,
				 IlvCodeEditor::StyleSheet* sheet,
				 IlvMenuItem* cutItem,
				 IlvMenuItem* cutButton,
				 IlvMenuItem* pasteItem,
				 IlvMenuItem* pasteButton)
{
    char tmpTitle[255];
    const char* extension = 0;
    static const char defaultCppExt[] = ".cpp";
    static const char defaultJavaExt[] = ".java";
    if (!title) {
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
	    // Save compiler warnings
#pragma warning(push)
	    // Remove warning on using sprintf
#pragma warning(disable : 4996)
#endif
	sprintf(tmpTitle, "Frame %lu", (unsigned long int) _frameCount++);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
	    // Restore compiler warnings
#pragma warning(pop)
#endif
	title = tmpTitle;
	extension = (EditorMainWindow::Cpp ? defaultCppExt : defaultJavaExt);
    } else {
	struct stat buf;
	int rv = stat(title, &buf);
	if (rv != 0) {
	    IlvPrint("Impossible to find %s\n", title);
	    return 0;
	} else {
	    for (IlUInt k = 0, i = 0; k < getCardinal() ; k++) {
		EditorFrame* editorFrame = (EditorFrame*)getFrame(k);
		if (editorFrame->equals(buf.st_ino)) {
		    IlvPrint("%s is already loaded\n", title);
		    return 0;
		}
	    }
	}
	// Find out file name extension
	extension = &title[strlen(title) - 1];
	while (title != extension && *extension-- != '.');
	extension++;
	if (*extension == '.') extension++;
    }
    IlvCodeEditor::Parser* parser =
	IlvCodeEditor::Parser::CreateParser(extension);
    EditorFrame* frame =
	new  EditorFrame(parser, getView(), title,
			 IlvRect(_newFrameLocation.x(),
				 _newFrameLocation.y(),
				 rect.w(), rect.h()),
			 new IlvCodeEditor::StyleSheet(*sheet),
			 cutItem,   cutButton,
			 pasteItem, pasteButton,
			 IlTrue);
    if (frame) {
	frame->getEditor()->setSaveAllTrigger(_saveAllTrigger);
	frame->getEditor()->setOpenTrigger(_openTrigger);
	frame->getEditor()->setQuitTrigger(_quitTrigger);
	frame->getEditor()->setKillBufferTrigger(_killBufferTrigger);
	frame->getEditor()->setFindTrigger(_findTrigger);
	frame->getEditor()->setReplaceTrigger(_replaceTrigger);
	frame->getEditor()->setGotoTrigger(_gotoTrigger);
	frame->setDestroyCallback(DestroyFrame);
	_newFrameLocation.translate(IlvPoint(20, 20));
	setCurrentFrame(frame);
	frame->maximizeFrame();
	updateTitle();
    }
    return frame;
}
