// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/timeconverter.h
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
// Declaration of the IlvTimeConverter class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Timeconverter_H
#define __Ilv_Graphics_Timeconverter_H

#ifndef __Ilv_Macros_H
#include <ilviews/macros.h>
#endif
#include <ilog/gregocal.h>
#ifndef __Il_Date_H
#include <ilog/date.h>
#endif

typedef IlDouble IlvDuration;

class ILVVWSEXPORTED IlvTimeConverter
{
public:
    IlvTimeConverter(IlDate refTime);

    IlvTimeConverter(const IlvTimeConverter&);

    virtual ~IlvTimeConverter();

    virtual IlDouble	getUnits(IlDate time) = 0;

    virtual IlDate	getTime(IlDouble units) = 0;

    inline IlDate	getReferenceTime() { return _referenceTime; }

    inline void		setReferenceTime(IlDate d) { _referenceTime = d; }

    inline void		lock() { _refcount++; }

    virtual void	unLock();

    inline IlUInt	refCount()    const { return _refcount; }

protected:
    IlDate		_referenceTime;
    IlUInt		_refcount;
};

class ILVVWSEXPORTED IlvLinearTimeConverter : public IlvTimeConverter
{
public:
    IlvLinearTimeConverter(IlDate refTime, IlvDuration unit);

    IlvLinearTimeConverter();

    IlvLinearTimeConverter(const IlvLinearTimeConverter&);

    virtual IlDouble	getUnits(IlDate time);

    virtual IlDate	getTime(IlDouble units);

    inline IlvDuration	getUnitDuration() { return _unitDuration; }

    inline void		setUnitDuration(IlvDuration d) { _unitDuration = d; }

protected:
    IlvDuration		_unitDuration;
};

#endif /* !__Ilv_Graphics_Timeconverter_H */
