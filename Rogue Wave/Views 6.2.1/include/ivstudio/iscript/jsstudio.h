// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/iscript/jsstudio.h
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
// Declaration of IlvStudio Scripting Extension class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Iscript_Jsstudio_H
#define __IlvSt_Iscript_Jsstudio_H

#if !defined(__IlvSt_Object_H)
#  include <ivstudio/object.h>
#endif
IL_NO_UNSECURE_CRT_WARNINGS
#if !defined(__Ilv_Jvscript_Script_H)
#  include <ilviews/jvscript/script.h>
#endif
#if !defined(__Ilv_Gadgets_Scrdlg_H)
#  include <ilviews/gadgets/scrdlg.h>
#endif
#if !defined(__IlvSt_Studext_H)
#  include <ivstudio/studext.h>
#endif

class IlvStudio;
class IlvGadgetContainer;
class IlvStJvDebugger;

extern ILVSTJSEXPORTEDVAR(const char*) IlvNmScriptChanged;

// --------------------------------------------------------------------------
class ILVSTJSCLASS IlvStScriptExtension
: public IlvStExtension
{
public:
    IlvStScriptExtension(IlvStudio*);
    ~IlvStScriptExtension();

    inline IlvStJvDebugger*	getIde() const
	{ return _ide; }
    inline IlvGadgetContainer*	getDebuggerPanel() const
	{ return _debuggerPanel; }

    virtual IlBoolean	initializeCommandDescriptors();
    virtual IlBoolean	initializePanels();
    virtual IlBoolean	postInitialize();

    static IlvStScriptExtension* Get(IlvStudio*);
    static IlvStScriptExtension* Make(IlvStudio*);

protected:
    IlvStJvDebugger*	    _ide;
    IlvGadgetContainer*	    _debuggerPanel;
}; // class IlvStSJExtension

// --------------------------------------------------------------------------
class ILVSTJSCLASS IlvStScripts // obsolete class
: public IlvStObject
{
public:
    IlvStScripts(IlvStudio*);
    virtual ~IlvStScripts();

    void initialize();
    static IlvStScripts*    Get(IlvStudio* editor);

    inline IlvGadgetContainer*	    getDebugPanel()
	{ return _debugPanel; }

protected:
    IlvStudio*		    _editor;
    IlvStJvDebugger*	    _ide;
    IlvGadgetContainer*	    _debugPanel;
    static IlSymbol*	    _S_Scripts;
}; // class IlvStScripts

#endif /* !__IlvSt_Iscript_Jsstudio_H */
