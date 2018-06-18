// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/iscript/debug.h
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
// Declaration of IlvStudio Script debugger
// --------------------------------------------------------------------------
#ifndef __IlvSt_Iscript_Debug_H
#define __IlvSt_Iscript_Debug_H

#if !defined(__IlvSt_Object_H)
#  include <ivstudio/object.h>
#endif

class IlvGadgetContainer;
class IlvStJvDebuggerInternal;

// --------------------------------------------------------------------------
class ILVSTJSCLASS IlvStJvDebugger
{
public:
    IlvStJvDebugger();
    ~IlvStJvDebugger();
    // ____________________________________________________________
    IlvGadgetContainer* getPanel(IlvDisplay*, IlvSystemView = 0);
private:
    IlvStJvDebuggerInternal*	_internal;
};

#endif /* !__IlvSt_Iscript_Debug_H */
