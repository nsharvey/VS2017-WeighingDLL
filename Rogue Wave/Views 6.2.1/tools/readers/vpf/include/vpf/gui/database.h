// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/database.h
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
// Declaration of the Database class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_DATABASE_H
#define VPF_GUI_DATABASE_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/optmenu.h>
#include <ilviews/gadgets/tree.h>
#include <ilviews/gadgets/combo.h>

class DatabaseReferencer;
class VpfLibrary;
class VpfCoverage;
class VpfFeatureClass;
class Layers;

// --------------------------------------------------------------------------
class Database {
public:
    Database(IlvGadgetContainer*, Layers*);
    virtual ~Database();
    // ____________________________________________________________
    static void AddDatabaseCB(IlvGraphic*, IlvAny);
    static void CloseDatabaseCB(IlvGraphic*, IlvAny);
    static void InspectDatabaseCB(IlvGraphic*, IlvAny);
    static void SelectItemCB(IlvGraphic*, IlvAny);
    static void MakeLayerCB(IlvGraphic*, IlvAny);
    static void PropertiesCB(IlvGraphic*, IlvAny);

    void show() { _browser->show(); }
    void hide() { _browser->hide(); }
    IlvDisplay* getDisplay() const { return _display; }

    void addDatabase(const char*);
    void updateDatabases();
    void updateLibraries();
    void inspectDatabase(IlUShort i);
    void closeDatabase();
    void selectItem(VpfFeatureClass*);
    void makeLayer();

    void addLibraryTree(VpfLibrary*);
    void addCoverageTree(IlvTreeGadgetItem*, VpfCoverage*);
    void addFeatureClassTree(IlvTreeGadgetItem*, VpfFeatureClass*);

    void setBusy(IlBoolean);
protected:
    IlvDisplay*		_display;
    IlvGadgetContainer*	_browser;
    Layers*		_layers;
    IlvOptionMenu*	_databasesMenu;
    IlvTreeGadget*	_librariesTree;
    IlvButton*		_addDatabaseButton;
    IlvButton*		_closeDatabaseButton;
    IlvButton*		_makeLayerButton;
    IlvButton*		_propertiesButton;
    DatabaseReferencer*	_database;
    VpfFeatureClass*	_featureClass;
};

#endif /* VPF_GUI_DATABASE_H */
