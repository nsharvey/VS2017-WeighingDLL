// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/oracle/src/defdbmsfact.cpp
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
// Implementation of the IlvDefaultSDODbmsFactory class: create a database
// connection to Oracle, using a dedicated dialog box.
// --------------------------------------------------------------------------
#include <ilviews/macros.h>
#include <defdbmsfact.h>
#include <ildblink/dblink.h>
#include <ildblink/ilddbms.h>
#include <ilviews/maps/format/oracle/sdolayer.h>
#include <ilviews/maps/format/oracle/sdoutil.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/passwded.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/graphics/label.h>

#if defined(IL_STD)
#  include <strstream>
#else
#  if defined(WINDOWS)
#    include <strstrea.h>
#  else
#    include <strstream.h>
#  endif
#endif

// --------------------------------------------------------------------------
/////////////////// the default connection dialog box ////////////////////
// --------------------------------------------------------------------------

IldDbms* MainDbms = 0;

// --------------------------------------------------------------------------
// Static and callback functions
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
			  (userName + "/"
			   + password + "@" + sid).getValue());
    if (MainDbms->isErrorRaised()) {
	// propagate error
	IlvSDOUtil::SetLastDbErrorMessage(MainDbms->getErrorMessage());
	IlvSDOUtil::SetLastDbErrorCode(MainDbms->getErrorCode());
	IlString errMessage(IlString("Data Base Error:\n") +
			    IlString(MainDbms->getErrorMessage()));
	IlvIErrorDialog error(connpan->getDisplay(), errMessage.getValue());
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
Connpan::Connpan(const char* userName,
		 const char* password,
		 const char* oracleSidName,
		 const char* dblinkDriverName,
		 IlvDisplay* display,
		 const char* name,
		 const char* title,
		 IlvRect*    size,
		 IlBoolean   useAccelerators,
		 IlBoolean   visible,
		 IlUInt      properties,
		 IlvSystemView transientFor)
    : IlvGadgetContainer(display,
			 name,
			 title,
			 size ? *size : IlvRect(100, 100, 332, 342),
			 properties,
			 useAccelerators,
			 visible,
			 transientFor),
      _userName(userName),
      _password(password),
      _sid(oracleSidName),
      _driver(dblinkDriverName)
{
    initialize();
}

// --------------------------------------------------------------------------
void
Connpan::initialize()
{
    readFile("connpan.ilv");
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
// IlvDefaultSDODbmsFactory
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
    connpan->showModal();
    delete connpan;
    return MainDbms;
}
