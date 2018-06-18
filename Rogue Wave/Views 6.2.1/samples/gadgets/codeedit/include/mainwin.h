// -------------------------------------------------------------- -*- C++ -*-
//                                                 Rogue Wave Views source file
// File: samples/gadgets/codeedit/include/mainwin.h
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

#ifndef Samples_Gadgets_Codeedit_Mainwin_H
#define Samples_Gadgets_Codeedit_Mainwin_H

#include <ilviews/gadgets/dockpane.h>
#include <ilviews/gadgets/notebook.h>

#include "dialogs.h"
#include "fileedit.h"

// --------------------------------------------------------------------------
// The application Main Window.
// Is a IlvDockableContainer singleton.
// ==========================================================================
typedef enum {
    TBNew,
    TBSeparator1,
    TBOpen,
    TBSave,
    TBSaveAll,
    TBSeparator2,
    TBUndo,
    TBRedo,
    TBSeparator3,
    TBCut,
    TBCopy,
    TBPaste,
    TBSeparator4,
    TBBreakpoint,
    TBSeparator5,
    TBInsertCppDocComment,
    TBSeparator7
} ToolbarButtons;

typedef enum {
    TBCompile,
    TBJava,
    TBGenHtml,
    TBAppletViewer,
    TBSeparator6,
    TBInsertBanner,
    TBInsertTTTag,
    TBInsertBoldTag,
    TBInsertItalicTag,
    TBInsertCarriageReturn,
    TBInsertJavaDocComment,
    TBSeparator8
} DecaToolbarButtons;

typedef enum {
    MenuFile,
    MenuEdit,
    MenuTool,
    MenuWindow,
    MenuDemo,
    MenuHelp2  // INTERNAL COMPILER ERROR 
} Menus;

typedef enum {
    ITMenuFileNew,
    ITMenuFileOpen,
    ITMenuFileClose,
    ITMenuFileSave,
    ITMenuFileSaveAs,
    ITMenuFileSaveAll,
    ITMenuFileSeparator1,
    ITMenuFileExit
} MenuFileItems;

typedef enum {
    ITMenuEditUndo,
    ITMenuEditRedo,
    ITMenuEditSeparator1,
    ITMenuEditCut,
    ITMenuEditCopy,
    ITMenuEditPaste,
    ITMenuEditSeparator2,
    ITMenuEditSelectAll,
    ITMenuEditSeparator3,
    ITMenuEditFind,
    ITMenuEditFindNext,
    ITMenuEditFindPrevious,
    ITMenuEditReplace,
    ITMenuEditSeparator4,
    ITMenuEditGoto,
    ITMenuEditRecenter,
    ITMenuEditSeparator5,
    ITMenuEditIndent,
    ITMenuEditOutdent,
    ITMenuEditSeparator6,
    ITMenuEditComment,
    ITMenuEditUncomment,
    ITMenuEditSeparator7,
    ITMenuEditCompleteWord
} MenuEditItems;

typedef enum {
    ITMenuToolOptions
} MenuToolItems;

typedef enum {
    ITMenuWindowCascade,
    ITMenuWindowTileHorizontally,
    ITMenuWindowTileVertically,
    ITMenuWindowSeparator1,
    ITMenuWindowViewJavaToolbar,
    ITMenuWindowViewJavaConsole,
    ITMenuWindowSeparator2
} MenuWindowItems;

typedef enum {
    ITMenuDemoMarginSymbolsTest,
    ITMenuDemoInsertRemoveBreakPoints,
    ITMenuDemoRemoveAllBreakPoints,
    ITMenuDemoUnsetAllErrorLines
} MenuDemoItems;

typedef enum {
    ITMenuHelpAbout
} MenuHelpItems;

// --------------------------------------------------------------------------
class EditorMainWindow : public IlvDockableContainer
{
public:
    static IlBoolean	Deca;
    static IlBoolean	Cpp;
    static EditorMainWindow*	Instance();

    void		showConsole()
			{
			    _consolePane->show();
			    updatePanes(IlTrue);
			}
    //    void		showDecaToolBar()
    //			{
    //			    _decaToolBarPane->show();
    //			    updatePanes(IlTrue);
    //			}

    IlvCodeEditor*	getConsole() const { return _console; }
    CustomizeDialogBox*	getCustomizeDialogBox()
			{
			    if (!_customizeDlg)
				_customizeDlg =
				    new CustomizeDialogBox(getDisplay(),
							   _console,
							   _minibufferBar);
			    return _customizeDlg;
			}
    FindDialogBox*	getFindDialogBox()
			{
			    if (!_findDialogBox) {
				_findDialogBox =
				    new FindDialogBox(getDisplay(), 0, 0, 0);
			    }
			    return _findDialogBox;
			}
    ReplaceDialogBox*	getReplaceDialogBox()
			{
			    if (!_replaceDialogBox)
				_replaceDialogBox =
				    new ReplaceDialogBox(getDisplay(), 0, 0, 0);
			    return _replaceDialogBox;
			}
    FileEditorDesktop*	getDesktop() const { return _desktop; }
    void		buildNewFrameEditor(const char* name);
    void		updateWindows();
    void		customize();
    IlBoolean		closeAll();
    
private:
    EditorMainWindow(IlvDisplay* display,
		     const char* name,
		     const char* title,
		     IlvRect rect,
		     IlvDirection dir);
    ~EditorMainWindow();
    IlvGraphic*		loadILV(IlvDisplay* display,
				const char *filename) const;
    IlBoolean		setCallbackAndClientTo(IlvMenuItem* item,
					       IlvGraphicCallback callback);
    void		setCallbacks();
    IlvCodeEditor::Binding*	getCurrentBindings();
    void		installAccelerator(IlvMenuItem* item,
					   IlvContainerAction action,
					   const char* accText,
					   IlvEventType type,
					   IlUShort data,
					   IlUShort modifiers);
    void		clearAccelerator(IlvMenuItem* item);
    void		setAcceleratorsTexts();
    void		createObservers();
    IlvMenuItem*	getNewItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileNew);
			}
    IlvMenuItem*	getOpenItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileOpen);
			}
    IlvMenuItem*	getCloseItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileClose);
			}
    IlvMenuItem*	getSaveItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileSave);
			}
    IlvMenuItem*	getSaveAsItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileSaveAs);
			}
    IlvMenuItem*	getSaveAllItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileSaveAll);
			}
    IlvMenuItem*	getExitItem() const
			{
			    return getMenuFile()->getItem(ITMenuFileExit);
			}
  
    IlvMenuItem*	getUndoItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditUndo);
			}
    IlvMenuItem*	getRedoItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditRedo);
			}
    IlvMenuItem*	getCutItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditCut);
			}
    IlvMenuItem*	getCopyItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditCopy);
			}
    IlvMenuItem*	getPasteItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditPaste);
			}
    IlvMenuItem*	getSelectAllItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditSelectAll);
			}
    IlvMenuItem*	getFindItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditFind);
			}
    IlvMenuItem*	getFindNextItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditFindNext);
			}
    IlvMenuItem*	getFindPreviousItem() const
			{
			    return getMenuEdit()->
				getItem(ITMenuEditFindPrevious);
			}
    IlvMenuItem*	getReplaceItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditReplace);
			}
    IlvMenuItem*	getGotoItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditGoto);
			}
    IlvMenuItem*	getRecenterItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditRecenter);
			}
    IlvMenuItem*	getIndentItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditIndent);
			}
    IlvMenuItem*	getOutdentItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditOutdent);
			}
    IlvMenuItem*	getCommentItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditComment);
			}
    IlvMenuItem*	getUncommentItem() const
			{
			    return getMenuEdit()->getItem(ITMenuEditUncomment);
			}
    IlvMenuItem*	getCompleteWordItem() const
			{
			    return getMenuEdit()->
				getItem(ITMenuEditCompleteWord);
			}
    IlvMenuItem*	getOptionsItem() const
			{
			    return getMenuTool()->getItem(ITMenuToolOptions);
			}
    IlvMenuItem*	getCascadeItem() const
			{
			    return getMenuWindow()->
				getItem(ITMenuWindowCascade);
			}
    IlvMenuItem*	getTileHorizontallyItem() const
			{
			    return getMenuWindow()->
				getItem(ITMenuWindowTileHorizontally);
			}
    IlvMenuItem*	getTileVerticallyItem() const
			{
			    return getMenuWindow()->
				getItem(ITMenuWindowTileVertically);
			}
    IlvMenuItem*	getViewJavaToolbarItem() const
			{
			    return getMenuWindow()->
				getItem(ITMenuWindowViewJavaToolbar);
			}
    IlvMenuItem*	getViewJavaConsoleItem() const
			{
			    return getMenuWindow()->
				getItem(ITMenuWindowViewJavaConsole);
			}
    IlvMenuItem*	getStartBufferItem() const
			{
			    return getMenuWindow()->
				getItem(ITMenuWindowSeparator2);
			}
    IlvMenuItem*	getTestItem() const
			{
			    return getMenuDemo()->
				getItem(ITMenuDemoMarginSymbolsTest);
			}
    IlvMenuItem*	getBreakPointItem() const
			{
			    return getMenuDemo()->
				getItem(ITMenuDemoInsertRemoveBreakPoints);
			}
    IlvMenuItem*	getRemoveAllBreakPointsItem() const
			{
			    return getMenuDemo()->
				getItem(ITMenuDemoRemoveAllBreakPoints);
			}
    IlvMenuItem*	getUnsetAllErrorsItem() const
			{
			    return getMenuDemo()->
				getItem(ITMenuDemoUnsetAllErrorLines);
			}
    IlvMenuItem*	getAboutItem() const
			{
			    return getMenuHelp()->getItem(ITMenuHelpAbout);
			}
    IlvPopupMenu*	getMenuFile() const
			{
			    return ((IlvMenuItem*)
				    (_menuBar->getItemByName("MenuFile")))
				->getMenu();
			}
    IlvPopupMenu*	getMenuEdit() const
			{
			    return ((IlvMenuItem*)
				    (_menuBar->getItemByName("MenuEdit")))
				->getMenu();
			}
    IlvPopupMenu*	getMenuWindow() const
			{
			    return ((IlvMenuItem*)
				    (_menuBar->getItemByName("MenuWindow")))
				->getMenu();
			}
    IlvPopupMenu*	getMenuDemo() const
			{
			    return  ((IlvMenuItem*)
				     (_menuBar->getItemByName("MenuDemo")))
				->getMenu();
			}
    IlvPopupMenu*	getMenuTool() const
			{
			    return ((IlvMenuItem*)
				    (_menuBar->getItemByName("MenuTool")))
				->getMenu();
    }
    IlvPopupMenu*	getMenuHelp() const
			{
			    return ((IlvMenuItem*)
				    (_menuBar->getItemByName("MenuHelp")))
				->getMenu();
			}
    IlvMenuItem*	getNewButton() const
			{
			    return _toolBar->getItem(TBNew);
			}
    IlvMenuItem*	getOpenButton() const
			{
			    return _toolBar->getItem(TBOpen);
			}
    IlvMenuItem*	getSaveButton() const
			{
			    return _toolBar->getItem(TBSave);
			}
    IlvMenuItem*	getSaveAllButton() const
			{
			    return _toolBar->getItem(TBSaveAll);
			}
    IlvMenuItem*	getUndoButton() const
			{
			    return _toolBar->getItem(TBUndo);
			}
    IlvMenuItem*	getRedoButton() const
			{
			    return _toolBar->getItem(TBRedo);
			}
    IlvMenuItem*	getCutButton() const
			{
			    return _toolBar->getItem(TBCut);
			}
    IlvMenuItem*	getCopyButton() const
			{
			    return _toolBar->getItem(TBCopy);
			}
    IlvMenuItem*	getPasteButton() const
			{
			    return _toolBar->getItem(TBPaste);
			}
    IlvMenuItem*	getBreakpointButton() const
			{
			    return _toolBar->getItem(TBBreakpoint);
			}
    IlvMenuItem* getInsertCppDocCommentButton() const
			{
			    return _toolBar->getItem(TBInsertCppDocComment);
			}

    //    IlvMenuItem*	getCompileButton() const
    //			{
    //			    return _decaToolBar->getItem(TBCompile);
    //			}
    //    IlvMenuItem*	getJavaButton() const
    //			{
    //			    return _decaToolBar->getItem(TBJava);
    //			}
    //    IlvMenuItem*	getAppletViewerButton() const
    //			{
    //			    return _decaToolBar->getItem(TBAppletViewer);
    //			}
    //    IlvMenuItem*	getGenHTMLButton() const
    //			{
    //			    return _decaToolBar->getItem(TBGenHtml);
    //			}
    //    IlvMenuItem*	getInsertBannerButton() const
    //			{
    //			    return _decaToolBar->getItem(TBInsertBanner);
    //			}
    //    IlvMenuItem*	getInsertTTTagButton() const
    //			{
    //			    return _decaToolBar->getItem(TBInsertTTTag);
    //			}
    //    IlvMenuItem*	getInsertBoldTagButton() const
    //			{
    //			    return _decaToolBar->getItem(TBInsertBoldTag);
    //			}
    //    IlvMenuItem*	getInsertItalicTagButton() const
    //			{
    //			    return _decaToolBar->getItem(TBInsertItalicTag);
    //			}
    //    IlvMenuItem*	getInsertCarriageReturnButton() const
    //			{
    //			    return _decaToolBar->
    //				getItem(TBInsertCarriageReturn);
    //			}
    //    IlvMenuItem*	getInsertJavaDocCommentButton() const
    //			{
    //			    return _decaToolBar->
    //				getItem(TBInsertJavaDocComment);
    //			}

    IlBoolean		replaceTextByConsoleEditor(IlvNotebook* notebook,
						   int index,
						   const char* name);
private:
    IlvCodeEditor*	_console;
    FindDialogBox*	_findDialogBox;
    ReplaceDialogBox*	_replaceDialogBox;
    CustomizeDialogBox*	_customizeDlg;
    FileEditorDesktop*	_desktop;
    IlvToolBar*		_menuBar;
    IlvToolBar*		_toolBar;
//    IlvToolBar*	_decaToolBar;
    IlvTextField*	_statusBar;
    IlvTextField*	_minibufferBar;
    IlvPane*		_consolePane;
//    IlvPane*		_decaToolBarPane;
    IlvCodeEditor::CursorMovedObserver*		_cursorMovedObserver;
    IlvCodeEditor::SelectionChangedObserver*	_selectionChangedObserver;
    IlvCodeEditor::CommandPerformedObserver*	_commandPerformedObserver;
};

#endif /* !Samples_Gadgets_Codeedit_Mainwin_H */
