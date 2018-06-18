// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/ilm.h
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
// The License Manager for the Rogue Wave Views Charts add-on
// Defined in library ilvcharts
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Ilm_H
#define __Ilv_Charts_Ilm_H

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
class ILVCHTEXPORTED IlvChartsLicenseManager
{
public:
    static IlBoolean IsAvailable();

     static IlBoolean RegisterLicense(const char* key,
				     IlInt keySignature);
};

#endif /* __Ilv_Charts_Ilm_H */