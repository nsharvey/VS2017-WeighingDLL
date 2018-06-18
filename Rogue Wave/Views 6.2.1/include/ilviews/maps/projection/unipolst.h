// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/unipolst.h
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
// Definition of the IlvUniversalPolarStereographicProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Unipolst_H
#define __Ilv_Maps_Unipolst_H

#include <ilviews/maps/projection/stereo.h>

ILVMAPSMODULEINIT(IlvUniversalPolarStereographicProjection);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvUniversalPolarStereographicProjection
: public IlvStereographicProjection
{
public:
    IlvUniversalPolarStereographicProjection(IlBoolean south = IlFalse);

    virtual void setLLCenter(IlDouble lon, IlDouble lat);
    virtual void setScaleFactor(IlDouble k0);

    IlBoolean isSouth() const { return _south; }

    void   setSouth(IlBoolean south);

    virtual void write(IlvOutputFile& f) const;

protected:
    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;

private:
    IlBoolean _south;
    void initParameters();

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvUniversalPolarStereographicProjection);
};

#endif /* __Ilv_Maps_Unipolst_H */
