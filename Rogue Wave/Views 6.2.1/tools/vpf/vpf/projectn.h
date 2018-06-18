// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/projectn.h
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
// Declaration of the projector classes for the IlogViews VPF reader
// --------------------------------------------------------------------------
#ifndef _VPF_PROJECTION_H
#define _VPF_PROJECTION_H

#define VpfPlateCarree        0
#define VpfTransverseMercator 1
#define VpfLambertEqualArea   2
#define VpfGnomonic           3
#define VpfNoProjection       4

#define LONGITUDE(lon) {if(lon<-180.0)lon += 360.0; if(lon>180.0)lon -= 360.0;}
#define LATITUDE(lat)  {if(lat<-90.0) lat += 180.0; if(lat>90.0) lat -= 180.0;}

extern float distance(double lat1, double lon1, double lat2, double lon2,
		      int units);

// --------------------------------------------------------------------------
class VpfProjection
{
protected:
    static double _cm, _origin, _r;

public:
    VpfProjection() {}
    // ____________________________________________________________
    inline void		setParameters(double cm, double origin, double r)
			{
			    _cm = cm;
			    _origin = origin;
			    _r = r;
			}
    inline void		setCM(double cm) { _cm = cm; }
    inline void		setOrigin(double origin) { _origin = origin; }
    inline void		setR(double r) { _r = r; }
    virtual void	xy(double& x, double& y) = 0;
    virtual void	latlon(double& x, double& y) = 0;
    virtual const char*	getName() = 0;
};

// --------------------------------------------------------------------------
class VpfProjection_tm : public VpfProjection
{
public:
    VpfProjection_tm() : VpfProjection() {};
    // ____________________________________________________________
    virtual void	xy(double& x, double& y);
    virtual void	latlon(double& x, double& y);
    virtual const char*	getName() { return "Transverse Mercator"; }
};

// --------------------------------------------------------------------------
class VpfProjection_lambert : public VpfProjection
{
public:
    VpfProjection_lambert() : VpfProjection() {};
    // ____________________________________________________________
    virtual void	xy(double& x, double& y);
    virtual void	latlon(double& x, double& y);
    virtual const char*	getName() { return "Lambert Azimuthal Equal Area"; }
};

// --------------------------------------------------------------------------
class VpfProjection_gnomonic : public VpfProjection
{
public:
    VpfProjection_gnomonic() : VpfProjection() {};
    // ____________________________________________________________
    virtual void	xy(double& x, double& y);
    virtual void	latlon(double& x, double& y);
    virtual const char*	getName() { return "Gnomonic"; }
};

// --------------------------------------------------------------------------
class VpfProjection_pcarree : public VpfProjection
{
public:
    VpfProjection_pcarree() : VpfProjection() {};
    // ____________________________________________________________
    virtual void	xy(double& x, double& y);
    virtual void	latlon(double& x, double& y);
    virtual const char*	getName() { return "Plate Carree"; }
};


extern double		VpfCentralMeridian(double xmin, double xmax);

#endif /* !_VPF_PROJECTION */
