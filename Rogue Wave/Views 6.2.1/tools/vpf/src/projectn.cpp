// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/projectn.cpp
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
// Definition of the VpfProjection classes and some subclasses
// --------------------------------------------------------------------------

#include <vpf/projectn.h>
#include <math.h>
#if defined(Lynx) || defined(WINDOWS) || defined(_WIN32)
#include <limits.h>
#else  /* !Lynx */
#if !defined(__hpux) || !(__cplusplus >= 199707L)
#include <values.h>
#endif /* !hp_10_1.0 */
#endif /* !Lynx */
#if !defined(FLT_MAX)
#define FLT_MAX 3.402823466E+38
#endif

#define PI  3.14159265358979323846

#define DEGREES(x)  ((x)*(180.0/PI))
#define RADIANS(x)  ((x)*(PI/180.0))
#define cot(x) cos(x)/sin(x)


double VpfProjection::_cm     = 0.;
double VpfProjection::_origin = 0.;
double VpfProjection::_r      = 1.;

static double R[2] = { 3958.754, 6370.997 };
// --------------------------------------------------------------------------
float
distance(double lat1, double lon1, double lat2, double lon2, int units)
{
    if ((units<0) || (units>1)) units = 0;

    if (lat1 > 90.0) lat1 -= 180.0;
    if (lat2 > 90.0) lat2 -= 180.0;

    double a = RADIANS(lat1),
           b = RADIANS(lat2),
           p = RADIANS(fabs(lon1-lon2)),
           dtheta = (sin(a)*sin(b)) + (cos(a)*cos(b)*cos(p));
    return (float)(DEGREES(acos(dtheta))*PI*R[units]/180.0); /* Distance in miles/km */
}

// --------------------------------------------------------------------------
double
VpfCentralMeridian(double xmin, double xmax)
{
    double delta;
    if (xmin > xmax) delta = 360.0 - xmin + xmax;
    else             delta = xmax - xmin;
    double cm = xmin + delta/2.0;
    if (cm > 180.0) cm -= 360.0;
    return cm;
}

// --------------------------------------------------------------------------
void
VpfProjection_tm::xy(double& x, double& y)
{
    double cm, lat, lon;
    double b, rlat, rlon, rcm, rorigin;
    double min_range, max_range, temp_lon, radian_angle;

    cm = _cm;
    min_range = cm - 90.0;
    max_range = cm + 90.0;
    LONGITUDE(min_range);
    LONGITUDE(max_range);
    if ((cm == 90.0) && (x == -180.0)) x = 180.0;
    else
	if ((cm == -90.0) && (x == 180.0)) x = -180.0;
    lat = y;
    lon = x;
    rlat = lat * PI/180.0;
    rlon = lon * PI/180.0;
    rcm = cm * PI/180.0;
    rorigin = _origin * PI/180.0;
    radian_angle = rlon-rcm;
    if (radian_angle < -PI) radian_angle += 2*PI;
    if (radian_angle > PI)  radian_angle -= 2*PI;
    b = cos(rlat)*sin(radian_angle);
    if (fabs(b) == 1.0) {
	temp_lon = cm - 90.0;
	LONGITUDE(temp_lon);
	if (lon == temp_lon) x = FLT_MAX;
	else                 x = FLT_MAX;
    } else
	x =.5 * _r * log((1+b)/(1-b));
    temp_lon = lon-cm; LONGITUDE(temp_lon);
    if ( (fabs(temp_lon) == 90.0) || (fabs(lat) == 90.0)) {
	if (lat >= 0.0) y = ( PI/2) * _r;
	else            y = (-PI/2) * _r;
    }
    else
	y = _r * (atan(tan(rlat)/cos(radian_angle))) - rorigin;
    if (min_range < max_range) {
	if ((lon < min_range) || (lon > max_range)) y = FLT_MAX;
    } else
	if ((lon < min_range) && (lon > max_range)) y = FLT_MAX;
}

// --------------------------------------------------------------------------
void
VpfProjection_tm::latlon(double& x, double& y)
{
    double cm, lat,lon;
    double d,rorigin;

    cm = _cm;
    if (y > FLT_MAX-1) return;

    rorigin = _origin * PI/180.0;
    d = (y)/_r + rorigin;
    if (fabs(x) == PI * _r) {
	lat = 0.0;
	if (x == -PI * _r) lon = cm - 90.0;
	else               lon = cm + 90.0;
	LONGITUDE(lon);
    } else {
	lat = asin(sin(d)/cosh((x)/_r))*180.0/PI;
	if ((cos(d) > -0.00001) && (cos(d) < 0.00001)) {
	    if (x < -0.01) {
		lon = cm - 90.0;
		LONGITUDE(lon);
	    } else
		if (x > 0.01) {
		    lon = cm + 90.0;
		    LONGITUDE(lon);
		} else
		    lon = cm;
	} else
	    lon = cm + atan(sinh((x)/_r)/cos(d))*180.0/PI;
    }
    LONGITUDE(lon);
    LATITUDE(lat);
    x = lon;
    y = lat;
}

// --------------------------------------------------------------------------
void
VpfProjection_lambert::xy(double& x, double& y)
{
    double cm, lat,lon,denom,min_range,max_range;
    double k,rlat,rlon,rcm,rorigin;

    cm = _cm;

    min_range = cm - 90.0;
    LONGITUDE(min_range);
    max_range = cm + 90.0;
    LONGITUDE(max_range);

    if (min_range < max_range) {
	if ((x < min_range) || (x > max_range)) {
	    x = FLT_MAX;
	    y = FLT_MAX;
	    return;
	}
    } else    {
	if ((x < min_range) && (x > max_range)) {
	    x = FLT_MAX;
	    y = FLT_MAX;
	    return;
	}
    }

    lat = y;
    lon = x;
    rlat = lat * PI/180.0;
    rlon = lon * PI/180.0;
    rcm = cm * PI/180.0;
    rorigin = _origin * PI/180.0;

    denom = (1+sin(rorigin)*sin(rlat)+cos(rorigin)*cos(rlat)*cos(rlon-rcm));
    if (denom == 0.0)
	denom = 0.0000001;
    k=sqrt(2/denom);
    x = _r * k*cos(rlat)*sin(rlon-rcm);
    y = _r * k*(cos(rorigin)*sin(rlat)-sin(rorigin)*cos(rlat)*
			cos(rlon-rcm));
}

// --------------------------------------------------------------------------
void
VpfProjection_lambert::latlon(double& x, double& y)
{
    if ((x > FLT_MAX-1) && (y > FLT_MAX-1))
	return;
    double cm = _cm;
    double rho = sqrt( ((x)*(x)) + ((y)*(y)) );
    if (rho == 0.0) {
	x = cm;
	y = _origin;
	return;
    } else {
	double rorigin = _origin * PI/180.0;
	double c = 2*asin( rho / (2.0 * _r) );
	double lat = asin(cos(c) * sin(rorigin) +
			  (y) * sin(c) * cos(rorigin)/rho)*(180.0/PI);
	double den = rho*cos(rorigin)*cos(c)-(y)*sin(rorigin)*sin(c);
	double lon;
	if (den == 0.0) {
	    lon = 180.0;
	} else {
	    lon = cm+atan((x)*sin(c)/den)*(180.0/PI);
	    if (den < 0.0)
		lon = lon + 180.0;
	    LONGITUDE(lon);
	}
	LATITUDE(lat);

	x = lon;
	y = lat;
    }
}

// --------------------------------------------------------------------------
void
VpfProjection_gnomonic::xy(double& x, double& y)
{
    float dist = distance(_origin, _cm, y, x, 0);  /* in miles */
    if (dist > 4145.597656) { // distance of 60 degrees @ equator
	x = FLT_MAX;
	y = FLT_MAX;
	return;
    }
    double cos_c = ((sin(RADIANS(_origin))*sin(RADIANS(y)))+
		    (cos(RADIANS(_origin))*cos(RADIANS(y))*
		     cos(RADIANS(x-_cm))));
    double k_prime = (cos_c != 0.0)
	? (1 / cos_c)
	: 0;
    double out_x = 0,
	   out_y = 0;
    if (((_origin < 90) || (_origin > -90)) && (_origin != 0)) {
	out_x = _r * k_prime * cos(RADIANS(y))
	    * sin(RADIANS(x - _cm));
	out_y = _r * k_prime * ((cos(RADIANS(_origin)) * sin(RADIANS(y))) -
				(sin(RADIANS(_origin)) * cos(RADIANS(y)) *
				 cos(RADIANS(x-_cm))));
    } else
    if (_origin == 0) {     /* Equator */
	out_x = _r * tan(RADIANS(x-_cm));
	out_y = _r * tan(RADIANS(y))/cos(RADIANS(x-_cm));
    } else
    if (_origin == 90) {   /* North Pole */
	out_x =  _r * cot(RADIANS(y)) * sin(RADIANS(x-_cm));
	out_y = -_r * cot(RADIANS(y)) * cos(RADIANS(x-_cm));
    } else
    if (_origin == -90) {  /* South Pole */
	out_x = -_r * cot(RADIANS(y)) * sin(RADIANS(x - _cm));
	out_y = -_r * cot(RADIANS(y)) * cos(RADIANS(x - _cm));
    }
    x = out_x;
    y = out_y;
}

// --------------------------------------------------------------------------
void
VpfProjection_gnomonic::latlon(double& x, double& y)
{
    if ((x > FLT_MAX-1) && (y > FLT_MAX-1))
	return;

    double p = sqrt((x * x) + (y * y));

    if (p == 0.0) {
	y = _origin;
	x = _cm;
    } else {
	double c = DEGREES(atan((p/_r)));
	double theta = DEGREES(asin((cos(RADIANS(c)) * sin(RADIANS(_origin)) +
				     (y * sin(RADIANS(c)) *
				      (cos(RADIANS(_origin)))/p))));
	double lambda = 0;
	if ((_origin < 90) && (_origin > -90)) {
	    double denom = (p * cos(RADIANS(_origin)) * cos(RADIANS(c)) -
			    y * sin(RADIANS(_origin)) * sin(RADIANS(c)));
	    if (denom == 0.0)
		lambda = FLT_MAX;
	    else {
		double arctan = DEGREES(atan( ( x * sin( RADIANS (c))/ denom)));
		lambda = _cm + arctan;
	    }
	} else
	if (_origin == 90) { /* North Pole */
	    if (y == 0.0)
		lambda = _cm;
	    else {
		lambda = _cm + DEGREES(atan( (x / (-y))));
		if ((x > 0.0) && (y > 0.0)) lambda += 180.0;
		if ((x < 0.0) && (y > 0.0)) lambda -= 180.0;
	    }
	} else
	if (_origin == -90) { /* South Pole */
	    if (y == 0.0) lambda = _cm;
	    else {
		lambda = _cm + DEGREES(atan( (x / (y)) ));
		if (y < 0.0) lambda += 180.0;
	    }
	}
	LONGITUDE(lambda);
	LATITUDE(theta);
	y = theta;
	x = lambda;
    }
}

// --------------------------------------------------------------------------
void
VpfProjection_pcarree::xy(double& x, double& y)
{
    double k;

    k = (x-_cm);
    if (k < -180.0) k += 360.0;
    if (k >  180.0) k -= 360.0;
    x = _r * RADIANS(k);
    y = _r * RADIANS(y);
}

// --------------------------------------------------------------------------
void
VpfProjection_pcarree::latlon(double& x, double& y)
{
    y = DEGREES(y) / _r;
    x = _cm + (DEGREES(x) / _r);
    if (x >  180.0) x -= 360.0;
    if (x < -180.0) x += 360.0;
}
