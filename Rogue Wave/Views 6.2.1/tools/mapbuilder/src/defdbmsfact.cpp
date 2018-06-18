// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/defdbmsfact.cpp
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
#if defined(HAS_SDO_SUPPORT)

#include <builder.h>

#include <defdbmsfact.h>
#if defined(HAS_SDO_SUPPORT)
#include <ilviews/maps/format/oracle/sdolayer.h>
#include <ilviews/maps/format/oracle/sdoutil.h>
#include <ildblink/ilddbms.h>
#include <ildblink/ildconn.h>
#endif
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/passwded.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/graphics/label.h>
#include <builder.h>

#if defined(IL_STD)
#  include <strstream>
#else  /* !IL_STD */
#  if defined(WINDOWS)
#    include <strstrea.h>
#  else
#    include <strstream.h>
#  endif
#endif /* !IL_STD */

// --------------------------------------------------------------------------
// Data
// --------------------------------------------------------------------------
static const char _Data1[] =
    "// Ilv Version: 5.2\n// File generated: Tue Mar 17 15:08:41 2009\n// Creator class: IlvGadgetManagerOutput\nFileName \"connpan\"\nPathName \"connpan.ilv\"\nPalettes 2\n1 F \"defaultBg\" \"black\" \"normal\" \"%MS Sans Serif-11-\" 0 solid solid 0 0 0 65535 1\n\"IlvStToolBar\" 0 F \"defaultBg\" \"black\" \"normal\" \"%MS Sans Serif-11-\" 0 solid solid 0 0 0 65535 1\nIlvObjects 10\n1 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 125 40 170 22 F6 2 1 -1 0 \"\" } 32 \"user\"\n0\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 125 100 170 22 F6 2 1 -1 0 \"\" } 32 \"sid\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 10 140 80 23 F13 2 { IlvMessageItem 262145 4 16 4 \"Connect\"  }   } 32 \"connect\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 215 140 80 23 F13 2 { IlvMessageItem 262145 4 16 4 \"Cancel\"  }   } 32 \"cancel\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 10 40 100 22 F268435468 0 { IlvMessageItem 262169 4 16 4 \"User:\"  }   } 0\n";

static const char _Data2[] = "0\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 10 70 100 22 F268435468 0 { IlvMessageItem 262169 4 16 4 \"Password:\"  }   } 0\n0\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 10 100 100 22 F268435468 0 { IlvMessageItem 262169 4 16 4 \"SID:\"  }   } 0\n0\n1 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 10 10 100 22 F268435468 0 { IlvMessageItem 262169 4 16 4 \"DbLink driver:\"  }   } 0\n0\n1 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvPasswordTextField 125 70 170 22 F102 2 1 -1 0 \"\" 42 } 32 \"password\"\n0\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvComboBox 125 10 170 22 F39 2 1 -1 0 \"oracle9\" 3\n{ IlvMenuItem 1 2 4 \"oracle9\"  } \n{ IlvMenuItem 1 2 4 \"oracle10\"  } \n{ IlvMenuItem 1 2 4 \"oracle11\"  }  } 32 \"drivers\"\n0\nSize 305 173\nGeometryHandlers\n1 100 0 305 0 305 0\n6 3 0 0 125  170 0 170 9  0 0 10 0\n 3 0 0 125  170 0 170 0  0 0 10 0\n 3 0 0 125  170 0 170 8  0 0 10 0\n 3 0 0 125  170 0 170 1  0 0 10 0\n 3 215 0 215  0 0 80 3  0 0 10 0\n 3 0 0 10  0 0 80 2  215 0 215 0\n1 100 0 173 0 173 0\n2 3 140 0 140  0 0 23 3  0 0 10 0\n 3 140 0 140  0 0 23 2  0 0 10 0\nEOF\n";

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------

IldDbms* MainDbms = 0;

// --------------------------------------------------------------------------
static void
CancelCB(IlvGraphic* g, IlvAny a)
{
    Connpan* connpan = (Connpan*)a;
    if (MainDbms) {
	delete MainDbms;
	MainDbms = 0;
    }
    connpan->hide();
}

// --------------------------------------------------------------------------
static void
ConnectCB(IlvGraphic* g, IlvAny a)
{
    Connpan* connpan = (Connpan*)a;
    IlString userName = connpan->getuser()->getLabel();
    IlString driver = connpan->getdrivers()->getLabel();
    IlString sid = connpan->getsid()->getLabel();
    IlString password = connpan->getpassword()->getLabel();
    MainDbms = IldNewDbms(driver.getValue(),
			 (userName + "/" + password + "@" + sid).getValue());
    if (MainDbms->isErrorRaised()) {
	// propagate error
	IlvSDOUtil::SetLastDbErrorMessage(MainDbms->getErrorMessage());
	IlvSDOUtil::SetLastDbErrorCode(MainDbms->getErrorCode());
	IlString errMessage(IlString("Data Base Error:\n") +
			    IlString(MainDbms->getErrorMessage()));
	IlvIErrorDialog error(connpan->getDisplay(), errMessage.getValue());
	error.moveToView(GetBuilder()->getMainWindow());
	error.get();
	delete MainDbms;
	MainDbms = 0;
    }
    else {
	// notify the layer
	MainDbms->autoCommitOff();
	IlvSDOLayer::DbmsUpdate(MainDbms,
				userName,
				sid,
				driver);
    }
    if (MainDbms) {
	connpan->hide();
    }
}

// --------------------------------------------------------------------------
// Connpan
// --------------------------------------------------------------------------
void
Connpan::initialize()
{
    // These allocations are made because the static is too large for some
    // compiler
    IlString tmpdata;
    tmpdata += _Data1;
    tmpdata += _Data2;
    ILVSTDPREF istrstream str((const char*)tmpdata);
    read(str);
    getuser()->setCallback(ConnectCB, this);
    getsid()->setCallback(ConnectCB, this);
    getconnect()->setCallback(ConnectCB, this);
    getpassword()->setCallback(ConnectCB, this);
    getcancel()->setCallback(CancelCB, this);
    _userName = IlString();
    _password = IlString();
    _sid = IlString();
    _driver = IlString();
}

// --------------------------------------------------------------------------
IldDbms*
IlvDefaultSDODbmsFactory::makeDbms(IlvDisplay* display,
				   const char* userName,
				   const char* password,
				   const char* oracleSidName,
				   const char* dblinkDriverName,
				   IlvMapsError& status)
{
    status = IlvMaps::NoError();
    //Pop the dialog box
    Connpan* connpan = new Connpan(userName,
				   password,
				   oracleSidName,
				   dblinkDriverName,
				   display,
				   "Default IlvSDOLayer connection Panel",
				   "Default IlvSDOLayer connection Panel");
    connpan->getuser()->setLabel(userName);
    connpan->getsid()->setLabel(oracleSidName);
    IlUShort count;
    connpan->getdrivers()->getLabels(count);
    if (dblinkDriverName) {
	for (IlUShort i = 0; i < count; i++) {
	    if (!strcmp(connpan->getdrivers()->getLabel(i),
			dblinkDriverName)) {
		connpan->getdrivers()->setSelected(i);
	    }
	}
    }
    connpan->moveToView(_builder->getMainWindow());
    connpan->showModal();
    delete connpan;
    return MainDbms;
}

#endif /* HAS_SDO_SUPPORT */
