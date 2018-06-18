// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/dimelem.h
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
// Declaration of the IlvObjectSDOKeyExtractor class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------

#ifndef __Ilv_Maps_Format_Oracle_DIMELEMENT_H
#define __Ilv_Maps_Format_Oracle_DIMELEMENT_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/clssinfo.h>
#include <ilviews/maps/maps.h>

class ILVDBMAPSEXPORTED IlvObjectSDODimElement
{
public:   

    virtual ~IlvObjectSDODimElement();

    IlvObjectSDODimElement(const char* dimName,
			   IlDouble lowerBound,
			   IlDouble upperBound,
			   IlDouble tolerance);

    IlvObjectSDODimElement(IlvInputFile& input);

    inline const char*	getDimName() const { return _dimName.getValue(); }

    inline IlDouble	getLowerBound() const { return _lowerBound; }

    inline IlDouble	getUpperBound() const { return _upperBound; }

    inline IlDouble	getTolerance() const { return _tolerance; }

private:
    IlString		_dimName;
    IlDouble		_lowerBound;
    IlDouble		_upperBound;
    IlDouble		_tolerance;
};

#endif /* __Ilv_Maps_Format_Oracle_DIMELEMENT_H */
