// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/intrface/tblitf.h
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
#ifndef __Ili_Compat_Tblitf_H
#define __Ili_Compat_Tblitf_H

#include <ilviews/dataccess/intrface/tblitf.h>

#ifdef ILI_COMPAT_PREFIX
#define IlvSwTableSelectionItf IliTableSelectionItf
#define IlvSwParameterItf IliParameterItf
#define IlvSwTableColumnItf IliTableColumnItf
#define IlvSwTransactionManagerItf IliTransactionManagerItf
#define IlvSwTableItf IliTableItf
#define IlvSwTableBufferItf IliTableBufferItf
#define IlvSwTableBufferValueItf IliTableBufferValueItf
#define IlvSwTablePropertyManagerItf IliTablePropertyManagerItf
#endif

#endif



