// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/TextView.cpp
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
// IlogViews 4 generated source file
// File generated Thu Aug 26 15:58:41 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <TextView.h>
#include <docsynt.h>
#include <synode.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// TextView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(TextView)
    Method1(SelectClass, selectClass, IlAny, node)
IlvDvEndInterface1(IlvDvTextView)

// --------------------------------------------------------------------------
// Constructor / destructor
TextView::TextView(IlvDisplay* display):
    IlvDvTextView(display)
{
}

// --------------------------------------------------------------------------
TextView::~TextView()
{
}

// --------------------------------------------------------------------------
// Overridables
void
TextView::initializeView()
{
    IlvDvTextView::initializeView();
}

// --------------------------------------------------------------------------
// Basic properties
TreeDocument*
TextView::getSyneditDocument() const
{
    return (TreeDocument*)getDocument();
}

// --------------------------------------------------------------------------
void
TextView::selectClass(IlAny param)
{
    SynNode* node = (SynNode*)param;
    if (!node)
	return;
    setSelection(node->getBeginPosition(), node->getEndPosition());
    ensureVisible(node->getBeginPosition());
    getHolder()->setFocus(this);
    reDraw();
}

// --------------------------------------------------------------------------
IlBoolean
TextView::handleControl(IlUShort c)
{
    if (IlvText::handleControl(c)) {
	cursorMoved();
	return IlvTrue;
    }
    return IlvFalse;
}

// --------------------------------------------------------------------------
void
TextView::selectionChanged()
{
    IlvDvTextView::selectionChanged();
    cursorMoved();
}

// --------------------------------------------------------------------------
void
TextView::cursorMoved()
{
    IlvTextLocation from = getCursorLocation();
    SynNode* node =
	((TreeDocument*)getDocument())->getNodeAtLocation(from);
    notifyDocument(IlvGetSymbol("SelectClass"), (IlAny)node);
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterGadgetViewClass(TextView, IlvDvTextView);

IL_BEGINMODULEINITDEF(TextView)
    IlvDvPostRegisterGadgetViewClass(TextView, IlvDvTextView);
IL_ENDMODULEINITDEF(TextView)

#if !defined(ILVBUILDLIBS)
static int TextView_ini = (IL_MODINIT(TextView)(), 0);
#endif

