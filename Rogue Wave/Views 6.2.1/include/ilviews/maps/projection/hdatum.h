// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/hdatum.h
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
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __Ilv_Maps_HorizontalDatum_H
#define __Ilv_Maps_HorizontalDatum_H

#include <ilviews/maps/coord.h>
#include <ilviews/maps/clssinfo.h>
#include <ilviews/maps/projection/ellips.h>

ILVMAPSMODULEINIT(hdatum);

class ILVMAPSEXPORTED IlvHorizontalDatumConverterFactory;
class ILVMAPSEXPORTED IlvHorizontalDatumConverter;

class ILVMAPSEXPORTED IlvHorizontalDatum
{
public:
    virtual ~IlvHorizontalDatum();

    IlvMapsError	getInitStatus() const { return _initStatus; }

    void		save(IlvOutputFile &file) const;

    virtual void	write(IlvOutputFile& file) const;

    const IlvEllipsoid*	getEllipsoid() const { return _ellipsoid; }

    virtual IlBoolean	equivalent(const IlvHorizontalDatum* datum) const = 0;

    static const IlvHorizontalDatumConverterFactory* GetConverterFactory();

    static
    IlvHorizontalDatum*	Load(IlvInputFile& inputFile);

    virtual
    IlvMapClassInfo*	getClassInfo() const;
    static
    IlvMapClassInfo*	ClassInfo();
    static
    IlvClassInfo**	ClassInfoRef();

    virtual
    IlvHorizontalDatum*	copy() const = 0;

protected:
    IlvHorizontalDatum(const IlvEllipsoid& ellipsoid);

    IlvHorizontalDatum(const IlvHorizontalDatum& source);

    IlvHorizontalDatum(IlvInputFile& file);

    void		setInitStatus(IlvMapsError status)
			{
			    _initStatus = status;
			}

private:

    IlvEllipsoid*	_ellipsoid;
    IlvMapsError	_initStatus;

    static
    IlvClassInfo*	_classinfo;
    static
    IlvHorizontalDatumConverterFactory* _defaultFactory;
}; /* class IlvHorizontalDatum */


class IlvHorizontalDatumConverterFactory
{
public:
    virtual const IlvHorizontalDatumConverter*
		getConverter(const IlvHorizontalDatum* sourceDatum,
			     const IlvHorizontalDatum* targetDatum) const = 0;
}; /* IlvHorizontalDatumConverterFactory */




class IlvHorizontalDatumConverter
{
public:
    virtual
    IlvMapsError	convert(const IlvHorizontalDatum* sourceDatum,
				const IlvHorizontalDatum* targetDatum,
				IlvCoordinate& ll) const = 0;
}; /* IlvHorizontalDatumConverter */

#endif /* __Ilv_Maps_HorizontalDatum_h */
