// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/lookfeel/src/mylook.cpp
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
// This subclass of the IlvWindows95LFHandler class redefines the look and feel
// of 2 objects :
//
// 1) IlvButton : The class MyButtonLFHandler is the new handler for the
// IlvButton class. This class is dynamically linked with the IlvButton class
// in the createObjectLFHandler method.
//
// 2) IlvTreeGadget : The class MyTreeLFHandler is the new handler for the
// IlvTreeGadget class. This class is statically linked with the IlvTreeGadget
// through the use of macros (IlvRegisterObjectLFHandler).
// --------------------------------------------------------------------------

#include <ilviews/gadgets/button.h>
#include <mylook.h>
#include <mybutton.h>
#include <mytree.h>
#if defined(WINDOWS)
#include <windows.h>
#endif

// --------------------------------------------------------------------------
MyLookFeelHandler::MyLookFeelHandler(IlvDisplay* display)
    : IlvWindows95LFHandler(display)
{
}

// --------------------------------------------------------------------------
MyLookFeelHandler::~MyLookFeelHandler()
{
}

// --------------------------------------------------------------------------
IlvObjectLFHandler*
MyLookFeelHandler::createObjectLFHandler(const IlvClassInfo* ci) const 
{
    if (ci == IlvButton::ClassInfo()) {
	return new MyButtonLFHandler((IlvLookFeelHandler*)this);
    } else
	return IlvWindows95LFHandler::createObjectLFHandler(ci);
}

// --------------------------------------------------------------------------
IlvPredefinedLookFeelMembers(MyLookFeelHandler, "MyLook");
IlvRegisterLookFeelClass(MyLookFeelHandler, IlvWindows95LFHandler);
IlvRegisterObjectLFHandler(MyLookFeelHandler, IlvTreeGadget, MyTreeLFHandler);
