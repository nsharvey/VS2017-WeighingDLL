// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/clip.h
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
// Declaration of the clipping routines
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Clip_H
#define __Ilv_Base_Clip_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

extern IlBoolean
IlvClipLine(const IlvPoint& fromin,
	    const IlvPoint& toin,
	    const IlvRect&  clip,
	    IlvPoint&       fromout,
	    IlvPoint&       toout);
extern IlvPoint*
IlvClipPolyline(IlUInt         count,
		IlvPoint*      points,
		const IlvRect& clip,
		IlUInt&        countout);

#endif /* !__Ilv_Base_Clip_H */
