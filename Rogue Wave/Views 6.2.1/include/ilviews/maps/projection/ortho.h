// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/ortho.h
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
// Definition of the IlvOrthographicProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Orthographic_H
#define __Ilv_Maps_Orthographic_H

#include <ilviews/maps/projection/project.h>

ILVMAPSMODULEINIT(IlvOrthographicProjection);

class ILVMAPSEXPORTED IlvOrthographicProjection
    : public IlvProjection
{
public:
    IlvOrthographicProjection();

    virtual void setLLCenter(IlDouble lon, IlDouble lat);

protected:
    virtual IlvMapsError sForward(IlvCoordinate& ll) const;
    virtual IlvMapsError sInverse(IlvCoordinate& xy) const;

    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvOrthographicProjection);
private:
    void computeParameters();
    enum {
	SPole,
	NPole,
	Obliq,
	Equit
    } _mode;
    IlDouble _sinph0;
    IlDouble _cosph0;
};

#endif /* __Ilv_Maps_Orthographic_H */
