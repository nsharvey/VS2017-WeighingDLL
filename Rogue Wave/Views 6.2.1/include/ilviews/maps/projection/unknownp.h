// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/unknownp.h
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
// Declaration of the IlvUnknownProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_UnknownProjection_H
#define __Ilv_Maps_UnknownProjection_H

#include <ilviews/maps/projection/project.h>

ILVMAPSMODULEINIT(unknownp);

class ILVMAPSEXPORTED IlvUnknownProjection : public IlvProjection {
public:
    IlvUnknownProjection();

    IlvUnknownProjection(const IlvUnknownProjection&);
    IlvUnknownProjection(IlvInputFile&);
    virtual IlvProjection* copy() const;

protected:
    virtual IlvMapsError sForward(IlvCoordinate& ll) const;
    virtual IlvMapsError sInverse(IlvCoordinate& xy) const;
    virtual IlvMapsError eForward(IlvCoordinate& ll) const;
    virtual IlvMapsError eInverse(IlvCoordinate& xy) const;

public:
    virtual IlvProjectionClassInfo* getClassInfo() const;
    static IlvClassInfo** ClassInfoRef() {return &_classInfo;}
    static IlvProjectionClassInfo* ClassInfo()
    {return (IlvProjectionClassInfo*) _classInfo;}

    IlvMapsIcFriend(unknownp, ILVMAPSEXPORTED);

private:
    static IlvClassInfo* _classInfo;
};

#endif /* __Ilv_Maps_UnknownProjection_H */
