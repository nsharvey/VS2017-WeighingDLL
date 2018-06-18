// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/toolbar.h
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
//  Declaration of the Studio tool bar class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Toolbar_H
#define __IlvSt_Toolbar_H

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Toolbar_H)
#include <ilviews/gadgets/toolbar.h>
#endif

class IlvStudio;
class IlvStCommandDescriptor;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStToolBar
: public IlvToolBar
{
public:
    IlvStToolBar(IlvStudio* editor,
		 IlvDirection dir,
		 const char* const* commandNames = 0,
		 IlUShort count = 0,
		 IlvPalette* palette = 0);
    virtual ~IlvStToolBar();
    void setCommands(const char* const* commandNames, IlUShort count);
    void insertCommand(const char*, IlUShort = (IlUShort)-1);
    IlUShort getCommandIndex(const char*) const;
    IlvStCommandDescriptor* getCommandDescriptor(IlUShort ndx) const;

    IlvStudio* getEditor() const { return _editor; }
    IlvDeclarePropClassInfo();
protected:
    IlvStudio* 	 _editor;
}; // class IlvStToolBar

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_toolbar)
#endif /* IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
#endif /* __IlvSt_Toolbar_H */
