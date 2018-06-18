// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/seltable.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliSelectTableDialog class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Seltable_H
#define __Ili_Seltable_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ilv_Graphics_Relfline_H
#  include <ilviews/graphics/relfline.h>
#endif

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Slist_H
#  include <ilviews/gadgets/slist.h>
#endif

#ifndef __Ili_Session_H
#  include <ilviews/dataccess/dbms/session.h>
#endif

#ifndef __Ili_Sqlrepvw_H
#  include <ilviews/dataccess/gadgets/sqlrepvw.h>
#endif

#ifndef __Ili_Dboptmnu_H
#  include <ilviews/dataccess/gadgets/dboptmnu.h>
#endif

class ILV_DBSQLG_EXPORTED IliSelectTableDialog
  : public IlvDialog {
public:
    IliSelectTableDialog (IlvDisplay*,IlvAbstractView*,IliSQLSession*);
    ~IliSelectTableDialog ();

    IlBoolean inputTableName (IliSQLTableRef& tblRef);
    IlBoolean inputTableNames ();

    IlInt getTablesCount () const;
    IlBoolean getTableRef (IlInt pos, IliSQLTableRef& tblRef) const;

    void onOwner ();
    void bnAdd();
    void bnDel();
protected:
    IliSQLSession* _session;
    IlvAbstractView* _view;
    IlBoolean _supportOwner;
    IlBoolean _exclusive;

    IliDbOptionMenu* _dlgOption;
    IlvStringList* _dlgList;
    IliTreeSQLTablesGadget* _dlgTree;

    void fillOwnerCombo ();
    void clearListTables();
    IlBoolean process (IlBoolean exculsive);
};

#endif




