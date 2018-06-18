// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/defdbmsfact.h
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
#ifndef _DefaultSDODbmsFactory
#define _DefaultSDODbmsFactory

#include <ilviews/maps/format/oracle/sdodbmsfact.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/passwded.h>
#include <ilviews/gadgets/combo.h>

// --------------------------------------------------------------------------
class Connpan
    : public IlvGadgetContainer
{
    friend class IlvDefaultSDODbmsFactory;
public:
    Connpan(const char* userName,
	     const char* password,
	     const char* oracleSidName,
	     const char* dblinkDriverName,
	     IlvDisplay* display,
	     const char* name,
	     const char* title,
	     IlvRect*    size            = 0,
	     IlBoolean   useAccelerators = IlFalse,
	     IlBoolean   visible         = IlFalse,
	     IlUInt      properties      = 0,
	     IlvSystemView transientFor  = 0)
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
    { initialize(); }

    IlvTextField* getuser() const
	{ return (IlvTextField*)getObject("user"); }
    IlvTextField* getsid() const
	{ return (IlvTextField*)getObject("sid"); }
    IlvButton* getconnect() const
	{ return (IlvButton*)getObject("connect"); }
    IlvButton* getcancel() const
	{ return (IlvButton*)getObject("cancel"); }
    IlvPasswordTextField* getpassword() const
	{ return (IlvPasswordTextField*)getObject("password"); }
    IlvComboBox* getdrivers() const
	{ return (IlvComboBox*)getObject("drivers"); }

private:
    void initialize();
    IlString _userName;
    IlString _password;
    IlString _sid;
    IlString _driver;
};

class MapBuilder;

// --------------------------------------------------------------------------
class IlvDefaultSDODbmsFactory
    : public IlvSDODbmsFactory
{
public:
    IlvDefaultSDODbmsFactory(MapBuilder* b):
	IlvSDODbmsFactory(),
	_builder(b) {
    }

    virtual IldDbms* makeDbms(IlvDisplay* display,
			      const char* userName,
			      const char* password,
			      const char* oracleSidName,
			      const char* dblinkDriverName,
			      IlvMapsError& status);
private:
    MapBuilder* _builder;
};

#endif /* _DefaultSDODbmsFactory */
