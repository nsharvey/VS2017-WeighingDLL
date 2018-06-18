// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/cyclicdata.h
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
// Declaration of chart interactor classes
// --------------------------------------------------------------------------

#ifndef __CyclicData_H
#define __CyclicData_H

#include <ilviews/charts/data.h>

// --------------------------------------------------------------------------
// IlvPointInfoCyclicArray
// --------------------------------------------------------------------------
class IlvChartCyclicPointSet;

class ILVCHTEXPORTED IlvPointInfoCyclicArray : public IlvPointInfoArray
{
public:
    IlvPointInfoCyclicArray();

    virtual IlvChartDataPointInfo* getInfoForPoint(IlUInt pointIndex) const;
    virtual IlvChartDataPointInfo* getPointInfo(IlUInt idx) const;

    virtual void	setPointInfo(IlUInt pointIndex,
				     IlvChartDataPointInfo* ptInfo,
				     IlBoolean copy = IlFalse);

    virtual IlBoolean	removePointInfo(IlUInt pointIndex);

    void		setAssociatedPointSet(IlvChartCyclicPointSet* s)
			{
			    _associatedPointSet = s;
			}

    DeclarePointInfoCollectionTypeInfo(IlvPointInfoCyclicArray);

protected:
    IlvChartCyclicPointSet* _associatedPointSet;
};


// --------------------------------------------------------------------------
// Class IlvChartCyclicPointSet
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartCyclicPointSet : public IlvChartPointSet
{
public:
     friend class IlvPointInfoCyclicArray;

    IlvChartCyclicPointSet(const char* name = 0,
			   IlvPointInfoCyclicArray* pointInfoCollection = 0);

    virtual ~IlvChartCyclicPointSet();


    virtual void	getPoint(IlUInt i,IlvDoublePoint& point) const;

    virtual
    IlvDoublePoint*	getPointsBetween(IlUInt  indexMin,
					 IlUInt  indexMax,
					 IlUInt& count) const;

    virtual IlBoolean	setPoint(IlUInt pointIndex,
				 const IlvDoublePoint& point);


    virtual IlBoolean	insertPoint(const IlvDoublePoint& point,
				    IlUInt pointIndex,
				    IlvChartDataPointInfo* pointInfo = 0,
				    IlBoolean copyPointInfo = IlFalse);

    virtual void	dataPointAdded(IlUInt position);
    virtual void	removePointsAndInfo();

    DeclareChartDataSetTypeInfo(IlvChartCyclicPointSet);

protected:
    unsigned int	getArrayIdx(unsigned int idx) const;

    unsigned int	_startIdx;

};

ILVCHTMODULEINIT(cyclicdata);

#endif
