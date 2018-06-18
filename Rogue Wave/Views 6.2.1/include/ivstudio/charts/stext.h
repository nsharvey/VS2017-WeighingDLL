// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/stext.h
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
// Declarations for IlvStChartExtension class
// --------------------------------------------------------------------------

#ifndef __IlvSt_Charts_Stext_H
#define __IlvSt_Charts_Stext_H

#if !defined(__IlvSt_Studio_H)
#include <ivstudio/studio.h>
#endif

#if !defined(__IlvSt_Inspect_H)
#include <ivstudio/inspect.h>
#endif

#if !defined(__IlvSt_Studext_H)
#include <ivstudio/studext.h>
#endif

#if !defined(__IlvSt_Charts_Chartpnl_H)
#include <ivstudio/charts/chartpnl.h>
#endif

#if !defined(__IlvSt_Charts_Cht_legd_H)
#include <ivstudio/charts/cht_legd.h>
#endif

#if !defined(__IlvSt_Charts_Dispedt_H)
#include <ivstudio/charts/dispedt.h>
#endif

#if !defined(__IlvSt_Charts_Scaledt_H)
#include <ivstudio/charts/scaledt.h>
#endif

#if !defined(__Ilv_Charts_Chartinc_H)
#include <ilviews/charts/chartinc.h>
#endif

// ---------------------------------------------------------------------------
// IlvStChartsExtension
// ---------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStChartsExtension
: public IlvStExtension {
public:
    IlvStChartsExtension(IlvStudio* editor);
    virtual ~IlvStChartsExtension();
    // ____________________________________________________________
    IlList* getDataSetInterfaces() const { return _dataSetInterfaces; }
    IlList* getDisplayerInterfaces() const { return _displayerInterfaces; }

    virtual IlBoolean	initializeInspectors();
    virtual IlBoolean	preInitialize();

    void registerDataSetInterface(IlvStIDataSetInterface* dataSetItf);
    void registerDisplayerInterface(IlvStIDisplayerInterface* displayerItf);

    static IlvStChartsExtension* Get(IlvStudio*);
    static IlvStChartsExtension* Make(IlvStudio*);


protected:
    IlList*   _dataSetInterfaces;
    IlList*   _displayerInterfaces;

    virtual void registerDefaultDataSetInterfaces();
    virtual void registerDefaultDisplayerInterfaces();
};

#endif /* __IlvSt_Charts_Stext_H */
