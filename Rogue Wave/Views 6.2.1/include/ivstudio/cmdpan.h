// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/cmdpan.h
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
//  Declaration of IlvStCommandPanel class
// --------------------------------------------------------------------------

#ifndef __IlvSt_Cmdpan_H
#define __IlvSt_Cmdpan_H

#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif
#if !defined(__IlvSt_Command_H)
#include <ivstudio/command.h>
#endif

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCommandPanel
: public IlvStPanelHandler {
public:
    IlvStCommandPanel(IlvStudio*);
    ~IlvStCommandPanel();
    // ____________________________________________________________
    void commandSelected(const char*);
    // --- Redef. ---
    virtual void cancel();
    virtual void doApply();
    virtual void connect();
    virtual void disconnect();
    virtual void show();
    // -- Messages
    virtual void doReset();
    // --- Component accessors ---
    IlvTextField* getCmdField() const
        { return (IlvTextField*)getObject("cmdField"); }
    IlvStringList* getCmdList() const
        { return (IlvStringList*)getObject("cmdList"); }
    IlSymbol* getCategory() const { return _category; }
    void       setCategory(IlSymbol* ctg) { _category = ctg; }
    void       resetCategories();
protected:
    IlSymbol*			_category;
}; // IlvStCommandPanel

// --------------------------------------------------------------------------
#endif /* __IlvSt_Cmdpan_H */
