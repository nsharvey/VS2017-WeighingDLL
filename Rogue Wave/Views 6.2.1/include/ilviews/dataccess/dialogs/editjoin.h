// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/editjoin.h
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
// Declaration of the IliJoinDialog class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Editjoin_H
#define __Ili_Editjoin_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ilv_Gadgets_Toggle_H
#  include <ilviews/gadgets/toggle.h>
#endif

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ili_Sqltable_H
#  include <ilviews/dataccess/sqltable.h>
#endif

class ILV_DBSSQL_EXPORTED IliJoinDialog
: public IlvDialog {
public:
    IliJoinDialog (IlvDisplay*, IlvAbstractView*);
    ~IliJoinDialog ();

    IlBoolean inputJoinType (IliSQLJoinType& jt,const char* leftTbl,
			      const char* rightTbl);

    void toggleSelected(IlvToggle*);
protected:
    IlvAbstractView* _view;
    IlvToggle* _toggles[IliJoinTypeCount];
    int _selected;
};

#endif



