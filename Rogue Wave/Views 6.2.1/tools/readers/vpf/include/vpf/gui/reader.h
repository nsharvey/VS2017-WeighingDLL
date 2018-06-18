// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/reader.h
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
// Declaration of the IlvVpfReader class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_READER_H
#define VPF_GUI_READER_H

#include <ilviews/gadgets/gadcont.h>
#include <vpf/gui/application.h>

class Layers;
class Manager;
class Database;
class Views;
class IlvLabel;

// --------------------------------------------------------------------------
class IlvVpfReader
: public Application
{
public:
    IlvVpfReader(IlvDisplay* display);
    virtual ~IlvVpfReader();
    // ____________________________________________________________
    virtual void setBusy(IlBoolean);
    virtual void setStatus(const char* = 0);
    virtual void handleError();

    static void destroyCB(IlvView*, IlvAny);
 protected:
    IlvDisplay*		_display;
    IlvGadgetContainer*	_container;
    IlvLabel*		_status;
    Layers*		_layers;
    Database*		_database;
    Views*		_views;
    Manager*		_manager;
};

#endif /* VPF_GUI_READER_H */
