// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/units.h
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
// Definition of classes for the measurement system.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Units_H
#define __Ilv_Printing_Units_H

#if !defined(__Ilv_Printing_Macros_H)
#include <ilviews/printing/macros.h>
#endif

#if !defined(__Il_String_H)
#include <ilog/string.h>
#endif

#if defined(IL_STD)
#include <iostream>
#else  /* !IL_STD */
#include <iostream.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintUnit
{
public:
    virtual ~IlvPrintUnit();

    IlvPrintUnit();
    IlvPrintUnit(double units);

    IlvPrintUnit& operator=(IlvPrintUnit const& other);
    IlvPrintUnit& operator=(double units);
    IlvPrintUnit& operator+=(IlvPrintUnit const& other);
    IlvPrintUnit& operator+=(double units);
    IlvPrintUnit& operator-=(IlvPrintUnit const& other);
    IlvPrintUnit& operator-=(double units);
    IlvPrintUnit& operator*=(double units);
    IlvPrintUnit& operator/=(double units);

    IlBoolean operator==(IlvPrintUnit const& other) const;
    IlBoolean operator!=(IlvPrintUnit const& other) const;

    double getUnits() const;
    void setUnits(double units);

    virtual double getPoints() const = 0;
    virtual void setPoints(double points) = 0;

    virtual IlString getUnitName() const = 0;
    IlString toString() const;

protected:
    virtual IlString getUnitNamePlural() const = 0;
    IlString getPlural(double value) const;

private:
    // Intentionally not defined.
    IlvPrintUnit(IlvPrintUnit const& other);

    double _units;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintCMUnit : public IlvPrintUnit
{
public:
    IlvPrintCMUnit();
    IlvPrintCMUnit(IlvPrintCMUnit const& other);
    IlvPrintCMUnit(IlvPrintUnit const& other);
    IlvPrintCMUnit(double units);

    virtual double getPoints() const;
    virtual void setPoints(double points);

    virtual IlString getUnitName() const;

protected:
    virtual IlString getUnitNamePlural() const;

private:
    static double	_PointsPerUnit;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintInchUnit : public IlvPrintUnit
{
public:
    IlvPrintInchUnit();
    IlvPrintInchUnit(IlvPrintInchUnit const& other);
    IlvPrintInchUnit(IlvPrintUnit const& other);
    IlvPrintInchUnit(double units);

    virtual double getPoints() const;
    virtual void setPoints(double points);

    virtual IlString getUnitName() const;

protected:
    virtual IlString getUnitNamePlural() const;

private:
    static double	_PointsPerUnit;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintPicaUnit : public IlvPrintUnit
{
public:
    IlvPrintPicaUnit();
    IlvPrintPicaUnit(IlvPrintPicaUnit const& other);
    IlvPrintPicaUnit(IlvPrintUnit const& other);
    IlvPrintPicaUnit(double units);

    virtual double getPoints() const;
    virtual void setPoints(double points);

    virtual IlString getUnitName() const;

protected:
    virtual IlString getUnitNamePlural() const;

private:
    static double	_PointsPerUnit;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintPointUnit : public IlvPrintUnit
{
public:
    IlvPrintPointUnit();
    IlvPrintPointUnit(IlvPrintPointUnit const& other);
    IlvPrintPointUnit(IlvPrintUnit const& other);
    IlvPrintPointUnit(double units);

    virtual double getPoints() const;
    virtual void setPoints(double points);

    virtual IlString getUnitName() const;

protected:
    virtual IlString getUnitNamePlural() const;
};

// --------------------------------------------------------------------------
// IO operator.
ILVPRINTINGEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& ostr, IlvPrintUnit const& unit);

// --------------------------------------------------------------------------
// Inline definitions.
// --------------------------------------------------------------------------
inline
IlvPrintUnit::IlvPrintUnit()
: _units(0.0)
{
}

// --------------------------------------------------------------------------
inline
IlvPrintUnit::IlvPrintUnit(double units)
: _units(units)
{
}

// --------------------------------------------------------------------------
inline double
IlvPrintUnit::getUnits() const
{
    return _units;
}

// --------------------------------------------------------------------------
inline void
IlvPrintUnit::setUnits(double units)
{
    _units = units;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator=(IlvPrintUnit const& other)
{
    setPoints(other.getPoints());
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator=(double units)
{
    setUnits(units);
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator+=(IlvPrintUnit const& other)
{
    setPoints(getPoints() + other.getPoints());
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator+=(double units)
{
    setUnits(getUnits() + units);
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator-=(IlvPrintUnit const& other)
{
    setPoints(getPoints() - other.getPoints());
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator-=(double units)
{
    setUnits(getUnits() - units);
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator*=(double units)
{
    setUnits(getUnits() * units);
    return *this;
}

// --------------------------------------------------------------------------
inline IlvPrintUnit&
IlvPrintUnit::operator/=(double units)
{
    setUnits(getUnits() / units);
    return *this;
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvPrintUnit::operator!=(IlvPrintUnit const& other) const
{
    return (*this == other) ? IlFalse : IlTrue;
}

// --------------------------------------------------------------------------
inline IlString
IlvPrintUnit::getPlural(double value) const
{
    IlString result = getUnitName();
    if (value > 1.) {
	result +=  getUnitNamePlural();
    }
    return result;
}

// --------------------------------------------------------------------------
inline IlString
IlvPrintUnit::toString() const
{
    return IlString(getUnits()) + IlString(" ") + getPlural(getUnits());
}

// --------------------------------------------------------------------------
inline
IlvPrintCMUnit::IlvPrintCMUnit()
: IlvPrintUnit()
{
}

// --------------------------------------------------------------------------
inline
IlvPrintCMUnit::IlvPrintCMUnit(IlvPrintCMUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintCMUnit::IlvPrintCMUnit(IlvPrintUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintCMUnit::IlvPrintCMUnit(double units)
: IlvPrintUnit(units)
{
}

// --------------------------------------------------------------------------
inline
IlvPrintInchUnit::IlvPrintInchUnit()
: IlvPrintUnit()
{
}

// --------------------------------------------------------------------------
inline
IlvPrintInchUnit::IlvPrintInchUnit(IlvPrintInchUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintInchUnit::IlvPrintInchUnit(IlvPrintUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintInchUnit::IlvPrintInchUnit(double units)
: IlvPrintUnit(units)
{
}

// --------------------------------------------------------------------------
inline
IlvPrintPicaUnit::IlvPrintPicaUnit()
: IlvPrintUnit()
{
}

// --------------------------------------------------------------------------
inline
IlvPrintPicaUnit::IlvPrintPicaUnit(IlvPrintPicaUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintPicaUnit::IlvPrintPicaUnit(IlvPrintUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintPicaUnit::IlvPrintPicaUnit(double units)
: IlvPrintUnit(units)
{
}

// --------------------------------------------------------------------------
inline
IlvPrintPointUnit::IlvPrintPointUnit()
: IlvPrintUnit()
{
}

// --------------------------------------------------------------------------
inline
IlvPrintPointUnit::IlvPrintPointUnit(IlvPrintPointUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintPointUnit::IlvPrintPointUnit(IlvPrintUnit const& other)
: IlvPrintUnit()
{
    setPoints(other.getPoints());
}

// --------------------------------------------------------------------------
inline
IlvPrintPointUnit::IlvPrintPointUnit(double units)
: IlvPrintUnit(units)
{
}

#endif /* __Ilv_Printing_Units_H */
