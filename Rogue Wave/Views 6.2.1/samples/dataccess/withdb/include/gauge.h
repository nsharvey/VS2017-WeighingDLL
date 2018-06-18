// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/include/gauge.h
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
// How to use a gauge within a form
// --------------------------------------------------------------------------
#ifndef __Sample_Gauge_H__
#define __Sample_Gauge_H__

#include <app.h>

#include <ildblink/dblink.h>
#include <ilviews/dataccess/gadgets/dbfield.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/dataccess/gadgets/dbnavig.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/dataccess/gadgets/sqldtsrc.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/base/gadget.h>
#include <ilviews/graphics/cirscale.h>
#include <ilviews/graphics/cirgauge.h>

// --------------------------------------------------------------------------
// Panel class for sample Gauge
// --------------------------------------------------------------------------
class Gauge
: public PageNoteBook
{
public:
    Gauge(IlvAbstractView* view, const char* filename);
    ~Gauge();

    void initGauge();

    IliSQLDataSource* getEMP_DS() const
	{ return (IliSQLDataSource*)getObject("EMP_DS"); }
    IliDbNavigator* getDBNavigator() const
	{ return (IliDbNavigator*)getObject("DBNavigator"); }
    IlvCircularGauge* getGRCircGauge() const
	{ return (IlvCircularGauge*)getObject("GRCircGauge"); }
    IlvCircularScale* getGRCircScale() const
	{ return (IlvCircularScale*)getObject("GRCircScale"); }
    IliDbField* getEDTSalary() const
	{ return (IliDbField*)getObject("EDTSalary"); }
};


#endif /* !__Sample_Gauge_H__*/
