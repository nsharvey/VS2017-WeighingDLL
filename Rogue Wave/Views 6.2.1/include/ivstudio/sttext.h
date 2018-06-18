// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/sttext.h
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
//  Declaration of the Studio text editor interface classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Sttext_H
#define __IlvSt_Sttext_H

#if !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStTextPanel
: public IlvStPanelHandler
{
public:
    IlvStTextPanel(IlvStudio*, const char* name = 0);
    virtual ~IlvStTextPanel();
    virtual void	    setUpContainer(IlvGadgetContainer*);
    const char* const*	    getLines(IlUShort&) const;
    void		    setLines(const char* const*, IlUShort);
protected:
    IlvGadget*	    _text;
    IlAny	    _defaultPalette;
}; // class ILVSTUDIOCLASS IlvStTextPanel

ILVSTEXPORTEDFUNC(void)IlvStMakeTextPanel(IlvStudio*);

// --------------------------------------------------------------------------
#endif


