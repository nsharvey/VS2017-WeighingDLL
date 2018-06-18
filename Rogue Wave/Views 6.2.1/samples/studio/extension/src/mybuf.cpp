// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/mybuf.cpp
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
// Implementation of the MyStudioExtension class
// --------------------------------------------------------------------------

#include <ivstudio/studio.h>
#include <ivstudio/stdesc.h>

#include <mybuf.h>
#include <myman.h>
#include <mycont.h>

// --------------------------------------------------------------------------
MyGadgetBuffer::MyGadgetBuffer(IlvStudio* editor,
			       const char* name,
			       IlvManager* mgr)
    : IlvStGadgetBuffer(editor,
			name,
			mgr ? mgr : new MyManager(editor->getDisplay()))
{
}

// --------------------------------------------------------------------------
const char* 
MyGadgetBuffer::getType () const
{
    return "MyGadgetBuffer";
}

// --------------------------------------------------------------------------
const char* 
MyGadgetBuffer::getTypeLabel () const
{
    return "Mine";
}

// --------------------------------------------------------------------------
void
MyGadgetBuffer::setUpPanelClass(IlvStPanelClass* pclass) const
{
    IlvStGadgetBuffer::setUpPanelClass(pclass);
    pclass->setBaseClass("MyContainer");
}