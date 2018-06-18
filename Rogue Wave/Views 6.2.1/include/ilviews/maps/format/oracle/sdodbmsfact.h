// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdodbmsfact.h
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
// Rogue Wave Views - Maps add-on.
// Declaration of the IlvSDODbmsFactory and IlvDefaultSDODbmsFactory classes
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Sdodbmsfact_H
#define __Ilv_Maps_Format_Oracle_Sdodbmsfact_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/base/link.h>

class IldDbms;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvSDODbmsFactory
{
    friend class IlvSDOLayer;

public:
    virtual IldDbms*	makeDbms(IlvDisplay* display,
				 const char* userName,
				 const char* password,
				 const char* oracleSidName,
				 const char* dblinkDriverName,
				 IlvMapsError& status);

private:
    static IlList*	_Observers;
};

#endif /* __Ilv_Maps_Format_Oracle_Sdodbmsfact_H */
