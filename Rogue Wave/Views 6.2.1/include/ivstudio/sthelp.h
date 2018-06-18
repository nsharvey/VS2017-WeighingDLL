// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/sthelp.h
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
// Declaration of the Help classes
// --------------------------------------------------------------------------

#ifndef __IlvSt_Sthelp_H
#define __IlvSt_Sthelp_H

#ifndef __IlvSt_Panel_H
#include <ivstudio/panel.h>
#endif

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDVAR(const char*) IlvNmHelp;
class ILOG_EXPORTED IlPathName;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStHelpPanel
: public IlvStPanelHandler {
public:
    IlvStHelpPanel(IlvStudio* editor);
    virtual ~IlvStHelpPanel();
    void		makeHelpFilePath(const char*, IlPathName&);
    IlBoolean		readHelpFile(const char* file, IlBoolean = IlTrue);
    IlBoolean		readProperties(ILVSTDPREF istream&);
    void		setDescription(const char*);
    virtual void	setTitle(const char*);
}; // class IlvStHelpPanel

// --------------------------------------------------------------------------
#ifndef __IlvSt_Command_H
#include <ivstudio/command.h>
#endif

class ILVSTUDIOCLASS IlvStShowHelp
: public IlvStCommand {
public:
    IlvStShowHelp(const char* fname);
    virtual ~IlvStShowHelp();
    virtual IlvStError* doIt(IlvStudio*, IlAny);
protected:
    char*   _helpFile;
}; // class IlvStShowHelp

// --------------------------------------------------------------------------
#endif /* ! __IlvSt_Sthelp_H */
