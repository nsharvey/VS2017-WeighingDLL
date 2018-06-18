// -------------------------------------------------------------- -*- C++ -*-
//                                                 Rogue Wave Views source file
// File: samples/gadgets/codeedit/include/triggers.h
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
// Action triggers to connect the CodeEditor to the actual implementation
// --------------------------------------------------------------------------

#ifndef Samples_Gadgets_Codeedit_Triggers_H
#define Samples_Gadgets_Codeedit_Triggers_H

#include <ilviews/gadgets/codeedit.h>

class EditorFrame;
class EditorMainWindow;

// --------------------------------------------------------------------------
class SaveTrigger : public IlvCodeEditor::Trigger
{
public:
    SaveTrigger(EditorFrame* frame)
	: _frame(frame) {}
    virtual IlBoolean	action();

private:
    EditorFrame*	_frame;
};

// --------------------------------------------------------------------------
class SaveAllTrigger : public IlvCodeEditor::Trigger
{
public:
    SaveAllTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

// --------------------------------------------------------------------------
class OpenTrigger : public IlvCodeEditor::Trigger
{
public:
    OpenTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

// --------------------------------------------------------------------------
class QuitTrigger : public IlvCodeEditor::Trigger
{
public:
    QuitTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

// --------------------------------------------------------------------------
class KillBufferTrigger : public IlvCodeEditor::Trigger
{
public:
    KillBufferTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

// --------------------------------------------------------------------------
class FindTrigger : public IlvCodeEditor::Trigger
{
public:
    FindTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

// --------------------------------------------------------------------------
class ReplaceTrigger : public IlvCodeEditor::Trigger
{
public:
    ReplaceTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

// --------------------------------------------------------------------------
class GotoTrigger : public IlvCodeEditor::Trigger
{
public:
    GotoTrigger(EditorMainWindow* mwin)
	: _mwin(mwin) {}
    virtual IlBoolean	action();

private:
    EditorMainWindow*	_mwin;
};

#endif /* !Samples_Gadgets_Codeedit_Triggers_H */
