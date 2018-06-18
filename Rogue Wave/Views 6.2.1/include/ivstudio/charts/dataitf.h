// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/dataitf.h
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
// Declaration of the IlvStIDataSetInterface class
// Defined in studio charts library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Charts_Dataitf_H)
#define __IlvSt_Charts_Dataitf_H

#if !defined(__IlvSt_Genselpg_H)
#include <ivstudio/inspectors/genselpg.h>
#endif

#if !defined(__IlvSt_Charts_Stchart_H)
#include <ivstudio/charts/stchart.h>
#endif

#if !defined(__Ilv_Charts_Data_H)
#include <ilviews/charts/data.h>
#endif

class ILVSTCHARTCLASS IlvStIChartPanel;
class ILVSTCHARTCLASS IlvStIDataSetAccessor;

// --------------------------------------------------------------------------
// Class IlvStIDataSetInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDataSetInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIDataSetInterface(const char* name,
			   const char* label,
			   const char* fileName);
    virtual ~IlvStIDataSetInterface();

    // ----------------------------------------------------------------------
    // Set / get
    const char* getFileName() const { return _fileName; }
    IlSymbol* getSymbol() const { return _symbol; }
    const char* getLabel() const { return _label; } 

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvChartDataSet* createDataSet(const char* name = 0,
					   IlvGraphicHolder* holder = 0) = 0;
    virtual const IlvClassInfo* getDataSetClassInfo() = 0;

    virtual void createPanel(IlvStIChartPanel* panel,
			     IlvStIListPageSelector* selector,
			     const char* dataSetRectangleName,
			     IlUShort itemIndex) = 0;
    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDataSetAccessor* dataSetAcc) = 0;

protected:
    IlSymbol*  _symbol;
    const char* _label;
    const char* _fileName;
};

// --------------------------------------------------------------------------
// Class IlvStIPointSetInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIPointSetInterface
: public IlvStIDataSetInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPointSetInterface(const char* name,
			    const char* label,
			    const char* fileName);
    virtual ~IlvStIPointSetInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvChartDataSet* createDataSet(const char* name = 0,
					   IlvGraphicHolder* holder = 0);
    virtual const IlvClassInfo* getDataSetClassInfo();

    virtual void createPanel(IlvStIChartPanel* panel,
			     IlvStIListPageSelector* selector,
			     const char* dataSetRectangleName,
			     IlUShort itemIndex);
    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDataSetAccessor* dataSetAcc);
};

// --------------------------------------------------------------------------
// Class IlvStIYValueSetInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIYValueSetInterface
: public IlvStIDataSetInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIYValueSetInterface(const char* name,
			     const char* label,
			     const char* fileName);
    virtual ~IlvStIYValueSetInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvChartDataSet* createDataSet(const char* name = 0,
					   IlvGraphicHolder* holder = 0);
    virtual const IlvClassInfo* getDataSetClassInfo();

    virtual void createPanel(IlvStIChartPanel* panel,
			     IlvStIListPageSelector* selector,
			     const char* dataSetRectangleName,
			     IlUShort itemIndex);
    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDataSetAccessor* dataSetAcc);
};

// --------------------------------------------------------------------------
// Class IlvStIFunctionInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIFunctionInterface
: public IlvStIDataSetInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIFunctionInterface(const char* name,
			    const char* label,
			    const char* fileName);
    virtual ~IlvStIFunctionInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvChartDataSet* createDataSet(const char* name = 0,
					   IlvGraphicHolder* holder = 0);
    virtual const IlvClassInfo* getDataSetClassInfo();

    virtual void createPanel(IlvStIChartPanel* panel,
			     IlvStIListPageSelector* selector,
			     const char* dataSetRectangleName,
			     IlUShort itemIndex);
    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDataSetAccessor* dataSetAcc);
};

// --------------------------------------------------------------------------
IlvDECLAREINITSTCHARTCLASS(sti_cht_dataitf)
// --------------------------------------------------------------------------
#endif /* !__IlvSt_Charts_Dataitf_H */
