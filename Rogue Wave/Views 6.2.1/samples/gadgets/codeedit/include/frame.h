// -------------------------------------------------------------- -*- C++ -*-
//                                                 Rogue Wave Views source file
// File: samples/gadgets/codeedit/include/frame.h
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

#ifndef Samples_Gadgets_Codeedit_Frame_H
#define Samples_Gadgets_Codeedit_Frame_H

#if defined(WIN32)
#  include <io.h> // for access method (permissions of files)
#  include <process.h> // for spawn
#endif

#include <ilviews/gadgets/dbgedit.h>
#include <ilviews/gadgets/vframe.h>
#include <ilviews/gadgets/fbrowser.h>
#include "triggers.h"

// --------------------------------------------------------------------------
// Implementation of the MDI window.
// The client view is an IlvDebuggerEditor.
// --------------------------------------------------------------------------
class EditorFrame : public IlvViewFrame
{
public:
    EditorFrame(IlvCodeEditor::Parser* parser,
		IlvView* parent,
		const char* title,
		const IlvRect& size,
		IlvCodeEditor::StyleSheet* sheet,
		IlvMenuItem* cutItem,
		IlvMenuItem* cutButton,
		IlvMenuItem* pasteItem,
		IlvMenuItem* pasteButton,
		IlBoolean visible = IlTrue);
    ~EditorFrame()
    {
	unRegisterClientView(_container);
	if (_fName)
	    delete[] _fName;
	delete [] _lastPattern;
	delete _contentChangedObserver;
    }
    IlBoolean		equals(ino_t inode) const
			{
			    return ((_inode == inode)&&(_inode));
			}
    void		focusInCB();
    IlBoolean		isSaveNeeded() const
			{
			    return _editor->isSaveNeeded();
			}
    void		showScrollBars()
			{
			    _editor->scrollBarShowAsNeeded(IlFalse,
							   IlFalse,
							   IlTrue);
			    _editor->showScrollBar(IlvVertical, IlTrue);
			    _editor->showScrollBar(IlvHorizontal, IlTrue);
			}
    IlvDebuggerEditor*	getEditor() const { return _editor; }
    YesNoCancel		suicide();
    IlBoolean		save();
    void		saveFile(const char* filename)
			{
			    if (filename != _fName) {
				if (_fName)
				    delete [] _fName;
				_fName = new char[strlen(filename) + 1];
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
				// Save compiler warnings
#pragma warning(push)
				// Remove warning on using strcpy
#pragma warning(disable : 4996)
#endif
				strcpy(_fName, filename);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
				// Restore compiler warnings
#pragma warning(pop)
#endif
			    }
			    setTitle(_fName);
			    save();
			}
    void		loadFile(const char* filename)
			{
			    if (filename != _fName) {
				if (_fName)
				    delete [] _fName;
				_fName = new char[strlen(filename) + 1];
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
				// Save compiler warnings
#pragma warning(push)
				// Remove warning on using strcpy
#pragma warning(disable : 4996)
#endif
				strcpy(_fName, filename);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
				// Restore compiler warnings
#pragma warning(pop)
#endif
			    }
			    char* text = readFileOnDisk(_fName);
			    _editor->loadText(text);
			    delete [] text;
			}
    void		reDrawClient() { _editor->consistentReDraw(); }
    void		undo() { _editor->undo(); }
    void		redo() { _editor->redo(); }
    void		indent() { _editor->indentRegion(); }
    void		outdent() { _editor->unindentRegion(); }
    void		commentRegion() { _editor->commentRegion(); }
    void		killComment() { _editor->killComment(); }
    void		recenter() { _editor->centerOnCurrentLine(); }
    void		completeWord() { _editor->completeWord(); }
    void		gotoLine()
			{
			    GoToDialogBox gotoDlg(getDisplay(), *_editor);
			    gotoDlg.wait(IlTrue, 0);
			}
    void		selectAll() { _editor->selectAll(); }
    void		setLastPattern(const char* lastPattern)
			{
			    if (lastPattern && (strlen(lastPattern) > 0)) {
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
				// Save compiler warnings
#pragma warning(push)
				// Remove warning on using strcpy
#pragma warning(disable : 4996)
#endif
				strncpy(_lastPattern,
					lastPattern,
					_maxPatternSize - 1);
#if defined(_MSC_VER) && (_MSC_VER >= 1600) /* VS10 and above */
				// Restore compiler warnings
#pragma warning(pop)
#endif
				_lastPattern[_maxPatternSize - 1] = '\0';
			    }
			}
    void		findNext(FindDialogBox& findDlg)
			{
			    findDlg.setEditor(_editor);
			    if (!findDlg.findNext()) {
				_editor->gotoLine(1);
				findDlg.findNext();
			    }
			}
    void		findPrevious(FindDialogBox& findDlg)
			{
			    findDlg.setEditor(_editor);
			    if (!findDlg.findPrevious()) {
				_editor->gotoEnd();
				findDlg.findPrevious();
			    }
			}
    void		find(FindDialogBox& findDlg)
			{
			    findDlg.setEditor(_editor);
			    if (getLastPattern())
				findDlg.setPattern(getLastPattern());
			    findDlg.selectPattern();
			    findDlg.setLimitedToSelection(_editor->isMultilineSelection());
			    findDlg.wait(IlTrue, 0);
			    setLastPattern(findDlg.getPattern());
			}
    void		replaceSelection(ReplaceDialogBox& replaceDlg)
			{
			    replaceDlg.setEditor(_editor);
			    if (getLastPattern())
				replaceDlg.setPattern(getLastPattern());
			    replaceDlg.selectPattern();
			    if (_editor->isMultilineSelection())
				_editor->setCursorLocation(_editor->getSelectionStart());
			    replaceDlg.setLimitedToSelection(_editor->isMultilineSelection());
			    replaceDlg.wait(IlTrue, 0);
			    setLastPattern(replaceDlg.getPattern());
			}
    void		cut() { _editor->cutToClipBoard(); }
    void		copy() { _editor->copyToClipBoard(); }
    void		paste() { _editor->pasteFromClipBoard(); }
    void		testSymbols()
			{
			    _editor->setErrorLocation(1, 2, 1, 4);
			    _editor->setBreakPoint(1);
			    _editor->setBreakPoint(2);
			    _editor->setBreakPoint(3);
			    _editor->setCurrentLine(2);
			    _editor->setCurrentLine(41);
			}
    void		propagateSheet(const IlvCodeEditor::StyleSheet* mould)
			{
			    _editor->propagateSheet(mould);
			}
    void		unsetAllErrors()
			{
			    _editor->unsetAllErrorLines();
			}
    void		breakPoint()
			{
			    IlInt currentLine = _editor->getCursorLine();
			    if (_editor->hasBreakPoint(currentLine) )
				_editor->removeBreakPoint(currentLine);
			    else
				_editor->setBreakPoint(currentLine);
			}
    void		compile();
    void		execute();
    void		appletViewer();
    void		genHTML();
    void		insertBanner();
    void		insertTTTag();
    void		insertBoldTag();
    void		insertItalicTag();
    void		insertCarriageReturn();
    void		insertJavaDocComment();
    void		insertCppDocComment();
    void		removeAllBreakPoints()
			{
			    _editor->removeAllBreakPoints();
			}
    IlvView*		getManagerView() const { return _container; }
    // overriden virtual IlvViewFrame member
    void		setTitle(const char* title);

private:
    void		fillConsole();
    void		insertTag(const char* beginTag, const char* endTag);
    const char*		getFileName() const { return _fName; }
    char*		getLastPattern() const
			{
			    return _editor->getSelection();
			}
    void		setAttachements(IlvContainer* container,
					IlvGadget* gadget)
			{
			    IlvGraphicHolder* holder = container->getHolder();
			    holder->attach(gadget, IlvHorizontal, 0,1,0,0,0);
			    holder->attach(gadget, IlvVertical,   0,1,0,0);
			}
    IlvDebuggerEditor*	createEditor(IlvDisplay* display,
				     IlvRect bRect,
				     IlvCodeEditor::Parser* parser,
				     IlvCodeEditor::StyleSheet* sheet);
    char*		readFileOnDisk(const char* name);
    void		touchStamp(const char* filename);
    IlBoolean		diskChanged() const;
    void		reloadOnChange();

private:
    IlvGadgetContainer*	_container;
    IlvDebuggerEditor*	_editor;
    char*		_fName;
    time_t		_stamp;
    char*		_lastPattern;
    IlvCodeEditor::ContentChangedObserver*
			_contentChangedObserver;
    SaveTrigger*	_saveTrigger;
    const int		_maxPatternSize;
    ino_t		_inode;
};

#endif /* !Samples_Gadgets_Codeedit_Frame_H */
