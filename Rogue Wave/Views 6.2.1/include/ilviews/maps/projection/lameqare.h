// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/lameqare.h
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
// Definition of the IlvLambertEqualAreaConic class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_LambertEqualAreaConic_H
#define __Ilv_Maps_LambertEqualAreaConic_H

#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/projection/alberseq.h>

ILVMAPSMODULEINIT(IlvLambertEqualAreaConicProjection);

class ILVMAPSEXPORTED IlvLambertEqualAreaConicProjection
    : public IlvAlbersEqualAreaProjection
{
private:
    IlBoolean _south;
public:
    IlvLambertEqualAreaConicProjection();

    IlvLambertEqualAreaConicProjection(IlDouble lat1,
				       IlBoolean south = IlFalse);

    IlBoolean isSouth() { return _south; }

    void   setSouth(IlBoolean south);

    virtual IlvMapsError setSecantLatitudes(const IlvCoordinate& secant);

    virtual void write(IlvOutputFile& f) const;

protected:
    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvLambertEqualAreaConicProjection);
};

#endif /* __Ilv_Maps_LambertEqualAreaConic_H */
