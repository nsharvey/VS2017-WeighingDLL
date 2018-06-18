// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/views.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the Views class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_VIEWS_H
#define VPF_GUI_VIEWS_H

#include <ilviews/gadgets/gadcont.h>

class IlvButton;
class IlvStringList;
class Manager;

// --------------------------------------------------------------------------
class Views
{
public:
    Views(IlvGadgetContainer*, Manager*);
    virtual ~Views();

    static void AddCB(IlvGraphic*, IlvAny);
    static void RemoveCB(IlvGraphic*, IlvAny);
    static void SelectCB(IlvGraphic*, IlvAny);
    static void ActivateCB(IlvGraphic*, IlvAny);
    
    void add();
    void remove();
    void select();
    void activate();

    static void UpdateCB(IlvView*, IlvAny);
    void update(IlvView*);
protected:
    IlvGadgetContainer*	_container;
    IlvButton*		_remove;
    IlvStringList*	_list;
    Manager*		_manager;
};

#endif /* VPF_GUI_VIEWS_H */
