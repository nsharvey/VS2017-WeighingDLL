// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geomutils.h
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
// Geometry Package
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#include <ilviews/maps/macros.h>
#include <ilviews/base/view.h>

// class not documented

class ILVMAPSEXPORTED IlvMapGeomUtils
{
private:
    IlvMapGeomUtils(){}
public:

    static IlUInt GetCircleHorizontalIntersection(
					       IlDouble x, IlDouble y,
					       IlDouble ax, IlDouble ay,
					       IlDouble bx, IlDouble by,
					       IlDouble cx, IlDouble cy,
					       IlDouble& x1, IlDouble& x2);

    static IlUInt GetArcHorizontalIntersectionCount(
				       IlDouble x, IlDouble y,
				       IlDouble ax, IlDouble ay,
				       IlDouble bx, IlDouble by,
				       IlDouble cx, IlDouble cy);


    static void GetArcAngles( IlDouble ax, IlDouble ay,
				  IlDouble bx, IlDouble by,
				  IlDouble cx, IlDouble cy,
				  IlDouble ctrx, IlDouble ctry,
				  IlDouble r, IlBoolean clockwise,
				  IlDouble& start, IlDouble& middle,
				  IlDouble& end);


    static IlBoolean MakeCircle(IlDouble ax, IlDouble ay,
				   IlDouble bx, IlDouble by,
				   IlDouble cx, IlDouble cy,
				   IlDouble& xCenter, IlDouble& yCenter,
				   IlDouble& radiusp2, IlBoolean& clockwise);


    static IlBoolean MakeArc(IlDouble ax, IlDouble ay,
			      IlDouble bx, IlDouble by,
			      IlDouble cx, IlDouble cy,
			      IlDouble& xCenter, IlDouble& yCenter,
			      IlDouble& radius,
			      IlDouble& startAngle, IlDouble& endAngle);

    static IlBoolean IntersectHorizontal(IlDouble x, 
					  IlDouble y, 
					  IlDouble fromX, 
					  IlDouble fromY, 
					  IlDouble toX, 
					  IlDouble toY);
};
