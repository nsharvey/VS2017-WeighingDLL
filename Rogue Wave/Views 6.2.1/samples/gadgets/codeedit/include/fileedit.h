// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/codeedit/include/fileedit.h
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

#ifndef Samples_Gadgets_Codeedit_Fileedit_H
#define Samples_Gadgets_Codeedit_Fileedit_H

#include <ilviews/gadgets/desktop.h>

#include "triggers.h"
#include "frame.h"

// --------------------------------------------------------------------------
// The IlvDesktopManager.
// --------------------------------------------------------------------------
class FileEditorDesktop : public IlvDesktopManager
{
public:
    FileEditorDesktop(IlvView* view,
		      SaveAllTrigger* saveAll,
		      OpenTrigger* open,
		      KillBufferTrigger* killBuffer,
		      QuitTrigger* quit,
		      FindTrigger* find,
		      ReplaceTrigger* replace,
		      GotoTrigger* gotoT);
    ~FileEditorDesktop();
    
    EditorFrame*	getCurrentEditorFrame() const
			{
			    return (EditorFrame*)getCurrentFrame();
			}
    void		tileFrames(IlBoolean vertically);
    EditorFrame*	buildNewFrame(const char* title,
				      const IlvRect& rect,
				      IlvCodeEditor::StyleSheet* sheet,
				      IlvMenuItem* cutItem,
				      IlvMenuItem* cutButton,
				      IlvMenuItem* pasteItem,
				      IlvMenuItem* pasteButton);
    void		propagateSheet(const IlvCodeEditor::StyleSheet* mould)
			{
			    for (int count = getCardinal() - 1;
				 count >= 0;
				 count--) {
				EditorFrame* frame = (EditorFrame*)
				    getFrame((IlUInt)count);
				if (frame)
				    frame->propagateSheet(mould);
			    }
			}
    void		frameMaximized(IlvViewFrame*, int) { updateTitle(); }
    void		frameMinimized(IlvViewFrame*, int) { updateTitle(); }
    void		frameRestored(IlvViewFrame*, int)  { updateTitle(); }
    void		frameSelectionChanged(IlvViewFrame* newFrame,
					      IlvViewFrame* oldFrame)
			{
			    IlvDesktopManager::frameSelectionChanged(newFrame,
								     oldFrame);
			    updateTitle();
			}
    void		updateTitle();

private:
    IlvPoint		_newFrameLocation;
    IlUInt		_frameCount;
    SaveAllTrigger*	_saveAllTrigger;
    OpenTrigger*	_openTrigger;
    QuitTrigger*	_quitTrigger;
    KillBufferTrigger*	_killBufferTrigger;
    GotoTrigger*	_gotoTrigger;
    ReplaceTrigger*	_replaceTrigger;
    FindTrigger*	_findTrigger;
};

#endif /* !Samples_Gadgets_Codeedit_H */
