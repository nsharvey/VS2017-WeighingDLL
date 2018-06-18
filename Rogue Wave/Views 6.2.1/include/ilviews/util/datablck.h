// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/datablck.h
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
// Declaration of the IlvDataBlockDescriptor structure
// Defined in library xviews
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Datablck_H
#define __Ilv_Util_Datablck_H

#if !defined(WINDOWS)

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

// --------------------------------------------------------------------------
typedef struct IlvDataBlockDescriptor
{
public:
    static IlUInt		Register(IlvDataBlockDescriptor*);
    static IL_STDPREF istream*	Get(const char*, const char*,
				    const IlvDisplay* = 0);
    static unsigned long	GetLength(const char*);
    const char*			name;
    const unsigned char*	data;
    IlUInt			length;
} _IlvDataBlockDescriptor;

// --------------------------------------------------------------------------
ILVEXPORTEDDEF(void)
IlvRegisterDataBlocks(IlvDataBlockDescriptor);

#define ILVREGISTERDATABLOCKS(res) \
IlvRegisterDataBlocks(res)

#endif /* !WINDOWS */

#endif /* !__Ilv_Util_Datablck_H */
