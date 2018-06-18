// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/sdotypes.h
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
// Declaration of the IlvSDOTypes class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_SDOTYPES_H
#define __Ilv_Maps_Format_Oracle_SDOTYPES_H

#include <ilviews/maps/format/oracle/macros.h>

typedef enum IlvSDOTypes {
    IlvSDOGeometryUNKNOWN = 0,
    IlvSDOGeometryPOINT = 1,
    IlvSDOGeometryLINESTRING = 2,
    IlvSDOGeometryPOLYGON = 3,
    IlvSDOGeometryCOLLECTION = 4,
    IlvSDOGeometryMULTIPOINT = 5,
    IlvSDOGeometryMULTILINESTRING = 6,
    IlvSDOGeometryMULTIPOLYGON = 7,

    IlvSDOGeometryUNKNOWN816 = 2000,
    IlvSDOGeometryPOINT816 = 2001,
    IlvSDOGeometryLINESTRING816 = 2002,
    IlvSDOGeometryPOLYGON816 = 2003,
    IlvSDOGeometryCOLLECTION816 = 2004,
    IlvSDOGeometryMULTIPOINT816 = 2005,
    IlvSDOGeometryMULTILINESTRING816 = 2006,
    IlvSDOGeometryMULTIPOLYGON816 = 2007
} _IlvSDOTypes;

#endif  /* __Ilv_Maps_Format_Oracle_SDOTYPES_H */
