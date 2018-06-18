// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/chartpnl.h
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
// Declaration of the IlvChartPanel class and some subtypes
// Defined in library ilvedit
// --------------------------------------------------------------------------
#ifndef __Ilv31_Chartpnl_H
#define __Ilv31_Chartpnl_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Edit_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif

class IlvChart;

// --------------------------------------------------------------------------
class ILV31EDTEXPORTED IlvChartPanel
: public IlvInspectorPanel
{
public:
    IlvChartPanel(IlvManager*, IlvSystemView transientFor = 0);
    // ____________________________________________________________
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
    virtual void applyPart(IlvChart*);
    virtual void initPart(IlvChart*);
protected:
    IlvChartPanel(IlvManager*,
		  const char*   className,
		  const char*   title,
		  const char*   icon,
		  const char*   data,
		  const char*   fileName,
		  IlvSystemView transientFor = 0);
private:
    void initializePanel();
    void displayData(IlvChart*);
    void updateData(IlvChart*);
};

// --------------------------------------------------------------------------
class ILV31EDTEXPORTED IlvBarChartPanel
: public IlvChartPanel
{
public:
    IlvBarChartPanel(IlvManager*, IlvSystemView transientFor = 0);
    // ____________________________________________________________
    virtual void applyPart(IlvChart*);
    virtual void initPart(IlvChart*);
};

// --------------------------------------------------------------------------
class ILV31EDTEXPORTED IlvScatterChartPanel
: public IlvChartPanel
{
public:
    IlvScatterChartPanel(IlvManager*, IlvSystemView transientFor = 0);
    // ____________________________________________________________
    virtual void applyPart(IlvChart*);
    virtual void initPart(IlvChart*);
};

// --------------------------------------------------------------------------
class ILV31EDTEXPORTED Ilv3dBarChartPanel
: public IlvChartPanel
{
public:
    Ilv3dBarChartPanel(IlvManager*, IlvSystemView transientFor = 0);
    // ____________________________________________________________
    virtual void applyPart(IlvChart*);
    virtual void initPart(IlvChart*);
};

#endif /*  ! __Ilv31_Chartpnl_H */








