// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/protos/chartacc.h
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
// Declaration of predefined user accessors for accessing values of Chart
// objects in groups.
// --------------------------------------------------------------------------
/**
 * \file
 * [library ilvproto ilviews/protos/chartacc.h]
 * Declaration of the <code>IlvXYChartAccessor</code> class (deprecated).
 */
#ifndef __Ilv31_Protos_Chartacc_H
#define __Ilv31_Protos_Chartacc_H

#if !defined(__Ilv_Protos_Macros31_H)
#include <ilviews/protos/macros31.h>
#endif
#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif
#if !defined(__Ilv31_Chart_H)
#include <ilviews/chart.h>
#endif

// ---------------------------------------------------------------------------
// IlvXYChartAccessor
// ---------------------------------------------------------------------------
/**
 * @class IlvXYChartAccessor ilviews/protos/chartacc.h ilviews/protos/chartacc.h
 * @library ilvgdpro
 * @short Specialized accessor that adds a point to an <code>IlvChart</code> contained in a group.
 * 
 * Since the <code>IlvChart</code> class is now deprecated, and has been replaced 
 * by the <code>IlvChartGraphic</code> class, this accessor is also deprecated. The
 * <code>IlvChartGraphic</code> class already defines its own accessors that lets
 * the chart be edited much more completely.
 * It responds to changes and queries on two values (one for X and one for
 * Y) in a single \a changeValues or \a queryValues call.
 */
class ILV31PROEXPORTED IlvXYChartAccessor
: public IlvMultipleUserAccessor {
public:
    /**
     * @short Creates a chart accessor. 
     * 
     * <code>IlvXYChartAccessor</code> always adds the new point
     * at the end of the chart. If the new point is greater than the maximum
     * X value of the horizontal scale, the chart automatically scrolls to
     * the left by 50% of the X scale width. If the new X value is less than
     * the X value of the last point, no point is added. If the new point is
     * equal to the last point, no point is added.
     * When the \a xname and \a yname values are
     * queried, they return the coordinates of the last point of the chart.
     * If only the Y value is specified in a call to
     * \a changeValue, a new point will be added with an X value
     * equal to the previous X value plus 1.
     * 
     * @param name Name of the attribute.
     * @param nodename Name of the node that contains the <code>IlvChart</code> object.
     * @param xscalename The name of the node that contains the horizontal scale of the chart. This node will 
     * typically be a graphic node containing an instance of the <code>IlvRectangularScale</code> class.
     * @param yscalename The name of the node that contains the vertical scale of the chart. This node will
     * typically be a graphic node containing an instance of the <code>IlvRectangularScale</code> class.
     * @param xname Specifies the name of the
     * value used to add a new point to the chart (see example provided with yname parameter). 
     * @param yname Specifies the name of the
     * value used to add a new point to the chart. For example, if
     * \a xname is \a valueX and \a yname is
     * \a valueY, a new point is added as follows:
     * \code
     * IlvValue xy[] = { "valueX", "valueY" };
     * xy[0] = 10.0;
     * xy[0] = 20.0;
     * obj-&gt;changeValues(xv, 2);
     * \endcode
     */
    IlvXYChartAccessor(const char* name,
		       const char* nodename,
		       const char* xscalename,
		       const char* yscalename,
		       const char* xname,
		       const char* yname);
    virtual ~IlvXYChartAccessor();
    // ____________________________________________________________
    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvXYChartAccessor);
protected:
    IlvSymbol* _nodename;
    IlvSymbol* _xscalename;
    IlvSymbol* _yscalename;
    IlvFloatPoint* _points;
    IlUInt _npoints;
    IlUInt _max;
    IlvChartDataPoints* _data;

    virtual void initialize(const IlvAccessorHolder* object);

    virtual IlvValue& queryValue(const IlvAccessorHolder* object,
				 IlvValue& val) const;
    virtual IlBoolean changeValues(IlvAccessorHolder* object,
				   const IlvValue* vals,
				   IlUShort count);

    void adjust(IlvAccessorHolder* object, IlvGroupNode* chartNode);

    void setData(IlvGroupNode* chartNode,
		 IlvChartDataPoints* data,
		 IlvPoint& origin,
		 IlFloat sx,
		 IlFloat sy,
		 IlvRect* rect = 0);

    static IlUInt PointsIncrement;
};

IlvDECLAREINIT31PROCLASS(chartacc)

#endif  /* __Ilv31_Protos_Chartacc_H */
