// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/date.h
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
// Declaration of the IlvTimeScaleStepsUpdater class
// Defined in library charts
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Date_H
#define __Ilv_Charts_Date_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#  include <ilviews/charts/macros.h>
#  include <ilviews/charts/scaledis.h>

#ifdef IL_STD
#include <ctime>
#include <iostream>
#else
#include <time.h>
#include <iostream.h>
#endif

#include <ilog/calendar.h>

// --------------------------------------------------------------------------

class IlTimeUnit;
class IlGregorianCalendar;

class ILVCHTEXPORTED IlvTimeScaleStepsUpdater : public IlvScaleStepsUpdater
{
    friend class IlvSingleScaleDisplayer;

protected:
    enum {
        FirstStepData  = 0x0001,
        LastStepData   = 0x0002,
        //    StepUnit       = 0x0004,
        //    StepNumber     = 0x0008,
        Invalidated      = 0x0010,
        NoTransformer    = 0x0020,
        AutoComputeUnit  = 0x0040
    };

public:
    IlvTimeScaleStepsUpdater(IlvSingleScaleDisplayer* scale);

    //   IlvTimeScaleStepsUpdater(IlTimeUnit *u = 0);

    virtual ~IlvTimeScaleStepsUpdater();

    virtual IlDouble nextStep        (IlDouble v) const;

    virtual IlDouble nextSubStep     (IlDouble v) const;

    virtual IlDouble incrementStep   (IlDouble v) const;

    virtual IlDouble incrementSubStep(IlDouble v) const;

    virtual IlDouble previousStep    (IlDouble v) const;

    virtual IlDouble previousSubStep (IlDouble v) const;

    virtual IlBoolean hasSubStep() const;

    virtual void getStepSubStepValues(const IlvProjectorArea& area,
                                      IlUInt&		stepsCount,
                                      IlDouble*&	stepValues,
                                      IlUInt&		subStepsCount,
                                      IlDouble*&	subStepValues) const;

    const IlTimeUnit* getTimeUnit() const;

    void setTimeUnit(IlTimeUnit* unit);

    inline IlBoolean isUsingTransformer() const {
        return (_flags & NoTransformer) ? IlFalse : IlTrue;
    }

    inline void useTransformer(IlBoolean b) {
        if (b)
            _flags &= ~NoTransformer;
        else
            _flags |= NoTransformer;
    }

    inline IlBoolean isAutoUnit() const {
        return (_flags & AutoComputeUnit) ? IlTrue : IlFalse;
    }

    inline void setAutoUnit(IlBoolean b) {
        if (b)
            _flags |= AutoComputeUnit;
        else
            _flags &= ~AutoComputeUnit;
    }

    //== First and last steps values
    void setFirstStepData(IlDouble value);

    inline IlDouble getFirstStepData() const { return _firstStepData; }

    inline IlBoolean isFirstStepDataDefined() const
    { return (_flags & FirstStepData) ? IlTrue : IlFalse; }
    inline void unsetFirstStepData() { _flags &= ~FirstStepData; }

    void setLastStepData(IlDouble value);

    inline IlDouble getLastStepData() const { return _lastStepData; }

    inline IlBoolean isLastStepDataDefined() const
    { return (_flags & LastStepData) ? IlTrue : IlFalse; }

    IlDouble getStepDataMin() const;

    IlDouble getStepDataMax() const;

    virtual char* computeStepLabel(IlDouble value) const;

    virtual char* computeStepLabel(IlDouble value, IlTimeUnit *unit) const;

    IlvDim getStepsSpacing() const { return _stepsSpacing; }

    void setStepsSpacing(IlvDim stepsSpacing) { _stepsSpacing = stepsSpacing; }


protected:

    void autoComputeUnit(const IlvProjectorArea& area);

    char* iComputeStepLabel(IlDouble value, IlTimeUnit *unit) const;

    int				_flags;
    IlUInt			_stepsCount;

    //== First and last steps values
    IlDouble			_firstStepData;
    IlDouble			_lastStepData;

    IlvDim			_stepsSpacing;

    IlTimeUnit *_unit;
    IlGregorianCalendar *_utilCal;

};

#endif
