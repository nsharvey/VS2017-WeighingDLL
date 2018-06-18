// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/home.h
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
// Declaration of the IlvGraphic and IlvSimpleGraphic classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Home_H
#define __Ili_Home_H

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif


ILV_INF_EXPORTEDFN(const char*)
IliGetDataAccessHome(IlvDisplay*);

ILV_INF_EXPORTEDFN(const char*)
IliGetDefaultDataAccessHome(IlvDisplay*);

ILV_INF_EXPORTEDFN(const char*)
IliGetDataAccessVariableHome(IlvDisplay*);

ILV_INF_EXPORTEDFN(IlBoolean)
IliAppendDataAccessSubPath(IlvDisplay*,const char* subPath,
		       const char* checkFile = 0);

#ifdef DOXYGEN_GENERATION
IlBoolean IliAppendDataAccessPath(IlvDisplay* display);
#else
ILV_INF_EXPORTEDFN(IlBoolean)
IliAppendDataAccessPath(IlvDisplay*);
#endif

ILV_INF_EXPORTEDFN(IlBoolean)
IliCheckInPath(IlvDisplay*, const char* filename);

#endif

