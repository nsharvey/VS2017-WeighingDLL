// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/conic.h
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
// Definition of the IlvConicProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Conic_H
#define __Ilv_Maps_Conic_H

#if !defined(__Ilv_Maps_Projection_Project_H)
#  include <ilviews/maps/projection/project.h>
#endif

ILVMAPSMODULEINIT(conic);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvConicProjection : public IlvProjection
{
protected:
    IlvConicProjection(IlBoolean			ellipsoidEnabled,
		       IlBoolean			inverseEnabled,
		       IlvProjectionGeometricProperty	property,
		       IlStringHashTable*		proj4Params = 0);

    IlvConicProjection(const IlvConicProjection&);
    IlvConicProjection(IlvInputFile&);

public:
    const IlvCoordinate& getSecantLatitudes() const { return _secant; }

    virtual
    IlvMapsError	setSecantLatitudes(const IlvCoordinate& secant);

    IlDouble		getSecantLatitude1(void) const { return _secant.x(); }

    IlvMapsError	setSecantLatitude1(IlDouble v)
			{
			    return
				setSecantLatitudes(IlvCoordinate(v,
								 _secant.y()));
			}

    IlDouble		getSecantLatitude2(void) const { return _secant.y(); }

    IlvMapsError	setSecantLatitude2(IlDouble v)
			{
			    return
			    setSecantLatitudes(IlvCoordinate(_secant.x(),
							     v)); }

    //IO
    virtual void	write(IlvOutputFile &) const;

    //PROJ4 compatibility
    virtual void	printPROJ4Specifics(IL_STDPREF ostream&) const;

    // ClassInfo functions
    virtual
    IlvProjectionClassInfo* getClassInfo() const;
    inline static
    IlvProjectionClassInfo* ClassInfo()
			{
			    return (IlvProjectionClassInfo*) _classinfo;
			}
    inline static
    IlvClassInfo**	ClassInfoRef() { return &_classinfo; }

protected:
    IlvCoordinate	_secant;

private:
    static void		Init();

    static
    IlvClassInfo*	_classinfo;

    IlvMapsIcFriend(conic, ILVMAPSEXPORTED);
};

#endif /* __Ilv_Maps_Conic _H */
