// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/mypan.cpp
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
// Implementation of the MyPanelHandler class
// --------------------------------------------------------------------------

#include <ivstudio/studio.h>
#include <mypan.h>
#include <myutil.h>

#define DATAFILE "mypanel.ilv"

// --------------------------------------------------------------------------
MyPanelHandler::MyPanelHandler(IlvStudio* ed,
			       const char* name,
			       IlvDialog*)
    : IlvStDialog(ed, name, DATAFILE, IlvRect(0, 0, 254, 71))
{
    IlvTextField* tf = (IlvTextField*)getDialog()->getObject("filename");
    tf->setLabel("", IlTrue);
    resetOnMessage("ObjectSelected");
}

// --------------------------------------------------------------------------
void
MyPanelHandler::apply()
{
   IlvGraphic* obj = getEditor()->getSelection();
   if (obj) {
       const char* name =
	   ((IlvTextField*)getDialog()->getObject("filename"))->getLabel();
       if (name && name[0]) {
	   MySetParameter(obj, IlvGetSymbol(name));
	   obj->setCallbackName(IlvGetSymbol("loadilv"));
       }
   }
}
    
// --------------------------------------------------------------------------
void 
MyPanelHandler::reset()
{
    IlvTextField* tf = (IlvTextField*)getDialog()->getObject("filename");
    IlvGraphic* obj = getEditor()->getSelection();
    IlvSymbol* fi = 0;
    if (obj) 
	fi = MyGetParameter(obj);
    tf->setLabel(fi ? fi->name() : "", IlvTrue);
}
