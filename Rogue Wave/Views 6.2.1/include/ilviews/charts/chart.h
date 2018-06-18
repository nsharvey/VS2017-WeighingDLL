// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/chart.h
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
// Definition of geometric functions.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Chart_H
#define __Ilv_Charts_Chart_H

#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif

#if !defined(__Ilv_Base_Geometry_H)
#include <ilviews/base/geometry.h>
#endif /* !__Ilv_Base_Geometry_H */

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif

// Geometry
extern 
IlDouble IlvDistance(const IlvPoint& p1, const IlvPoint& p2);
extern 
IlInt IlvScalarProduct(const IlvPoint& p1, 
		       const IlvPoint& p2,
		       const IlvPoint& p3,
		       const IlvPoint& p4);
extern 
IlInt IlvCrossProduct(const IlvPoint& p1,
		      const IlvPoint& p2,
		      const IlvPoint& p3,
		      const IlvPoint& p4);
extern 
void IlvComputeIntersectionAtGivenY(IlvPoint& point,
				    const IlvPoint& point1,
				    const IlvPoint& point2,
				    IlvPos y);
extern
void IlvComputeIntersectionAtGivenX(IlvPoint& point,
				    const IlvPoint& point1,
				    const IlvPoint& point2,
				    IlvPos x);

// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Array_H
#include <ilviews/base/array.h>
#endif

class ILVCHTEXPORTED IlvDeclareArrayOf(IlAny,IlvChartArray);
class ILVCHTEXPORTED IlvDeclareArrayOf(IlDouble,IlvChartDoubleArray);
class ILVCHTEXPORTED IlvDeclareArrayOf(IlvPoint,IlvChartPointArray);
class ILVCHTEXPORTED IlvDeclareArrayOf(IlvDoublePoint,IlvChartDoublePointArray);
class ILVCHTEXPORTED IlvDeclareArrayWithoutEquality(IlUInt,IlvChartUIntArray);
class ILVCHTEXPORTED IlvDeclareArrayOf(IlUShort,IlvChartUShortArray);

#endif /* !__Ilv_Charts_Chart_H */
