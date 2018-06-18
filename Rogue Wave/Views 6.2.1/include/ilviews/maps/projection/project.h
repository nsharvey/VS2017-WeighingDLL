// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/project.h
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
// Projections package
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __Ilv_Maps_Project_H
#define __Ilv_Maps_Project_H

#include <ilviews/maps/coord.h>
#include <ilviews/maps/projection/ellips.h>
#include <ilviews/maps/projection/hdatum.h>
#include <ilviews/maps/unitconv.h>
#include <ilviews/maps/projection/projinfo.h>
#include <ilviews/base/value.h>
#include <ilviews/graphics/io.h>

ILVMAPSMODULEINIT(project);

class ILVVWSEXPORTED IlvInputFile;
class ILVDSPEXPORTED IlvDisplay;
class ILVVWSEXPORTED IlvOutputFile;
class ILVDSPEXPORTED IlvAlist;
class ILVDSPEXPORTED IlvTransformer;

class ILVMAPSEXPORTED IlvProjection;
class ILVMAPSEXPORTED IlvProjectionInterface;

enum IlvProjectionGeometricProperty {
    IlvNoneProjectionGeometricProperty = 0,
    IlvConformalProjectionGeometricProperty = 1,
    IlvEqualAreaProjectionGeometricProperty = 2
};


// --------------------------------------------------------------------------
//
// IlvProjection
//
// --------------------------------------------------------------------------

class ILVMAPSEXPORTED IlvProjection
{
protected:
    // Protected constructor, the class beeing abstract.
    IlvProjection(IlBoolean	ellipsoidEnabled,
		  IlBoolean	inverseEnabled,
		  IlvProjectionGeometricProperty	property,
		  IlStringHashTable*  proj4Params = 0);
    IlvProjection(const IlvProjection&);
    IlvProjection(IlvInputFile&);

public:
    virtual ~IlvProjection();

    // Using the projection
    IlvMapsError	forward(const IlvCoordinate& llIn,
				IlvCoordinate& xyOut) const;
    IlvMapsError	forward(IlvCoordinate& x) const
	{ return forward(x, x); }
    IlvMapsError	inverse(const IlvCoordinate& xyIn,
				IlvCoordinate& llOut) const;
    IlvMapsError	inverse(IlvCoordinate& x) const
	{ return inverse(x, x); }

    // Projection parameters
    const IlvEllipsoid* getEllipsoid() const { return _ellipsoid; }
    virtual IlvMapsError setEllipsoid(const IlvEllipsoid& ellipsoid);

    const IlvHorizontalDatum* getDatum(void) const { return _datum; }
    virtual
    IlvMapsError	setDatum(const IlvHorizontalDatum* datum);

    IlBoolean		isGeocentric() const { return _geoc; }
    void		setGeocentric(IlBoolean geoc) { _geoc = geoc; }

    virtual void	setLLCenter(IlDouble lon, IlDouble lat);
    inline IlvCoordinate getLLCenter(void) const
	{ return IlvCoordinate(_lam0, _phi0); }

    inline IlDouble	getCentralMeridian() const { return _lam0; }
    inline void		setCentralMeridian(IlDouble lon)
	{ setLLCenter(lon, _phi0); }

    inline IlDouble	getCentralParallel() const { return _phi0; }
     inline void	setCentralParallel(IlDouble lat)
	{ setLLCenter(_lam0, lat); }

    void		setXYOffset(IlDouble x0, IlDouble y0)
	{
	    _x0 = x0;
	    _y0 = y0;
	}
    inline IlvCoordinate getXYOffset() const
	{ return IlvCoordinate(_x0, _y0); }

    inline IlDouble	getFalseEasting() const { return _x0; }
    inline void		setFalseEasting(IlDouble falseEasting)
	{ _x0 = falseEasting; }
    inline IlDouble	getFalseNorthing() const { return _y0; }
    inline void		setFalseNorthing(IlDouble falseNorthing)
	{ _y0 = falseNorthing; }

    inline IlBoolean	isUsingLongitudeReduction() const
	{ return !_over; }
    inline void		setUsingLongitudeReduction(IlBoolean use)
	{ _over = !use; }

    inline const IlvUnitConverter* getUnitConverter() const
	{ return _converter; }
    void		setUnitConverter(const IlvUnitConverter& converter);

    // General Information
    inline IlBoolean	isEllipsoidEnabled() const
	{ return _ellipsoidEnabled; }

    inline IlBoolean	isInverseEnabled() const { return _inverseEnabled; }

    inline IlvProjectionGeometricProperty getProperty() const
	{ return _property; }

    // PROJ4 compatibility
    virtual
    IL_STDPREF ostream& printPROJ4Descriptor(IL_STDPREF ostream& ostr,
					     IlvMapsError* status = 0) const;
    static IlvProjection* PROJ4ToIlvProjection(const char* proj4Descriptor,
					       IlvMapsError* status = 0);

    // ClassInfo functions
    virtual IlvProjectionClassInfo* getClassInfo() const;
    static inline IlvProjectionClassInfo* ClassInfo()
	{ return (IlvProjectionClassInfo*) _classinfo; }
    static inline IlvClassInfo** ClassInfoRef()
	{ return &_classinfo; }
    IlvProjectionInterface* getInterface();

    // IO functions
    static IlvProjection*	Load(IlvInputFile& inputFile);
    void		save(IlvOutputFile& outputFile) const;
    virtual void	write(IlvOutputFile& outputFile) const;

    // Error management
    inline IlBoolean	isBad() const
	{ return _error != IlvMaps::NoError(); }
    inline IlvMapsError	getError() const { return _error; }

    // Projection errors
    static IlvMapsError InputError();
    static IlvMapsError UnsupportedFeatureError();
    static IlvMapsError InvalidEllipsoidError();
    static IlvMapsError ToleranceConditionError();
    static IlvMapsError NoPROJ4CompatibilityError();

    // Misc
    virtual IlvProjection* copy() const = 0;
    inline void		setShared() { _isShared = IlTrue; }
    inline IlBoolean	isShared() const { return _isShared; }
    inline void		lock() { _lockCount++; }
    inline void		unLock()
	{
	    _lockCount--;
	    if (_lockCount < 0) {
		IlvWarning("IlvProjection::unLock() : "
			   "wrong lock count %d !",
			   _lockCount);
	    }
	    if (!_lockCount && isShared()) {
		_isShared = IlFalse;
		// or the destructor would print a warning
		delete this;
	    }
	}

    // Undocumented
    inline void		getXYOffset(IlDouble& x0, IlDouble& y0) const
	{
	    x0 = _x0;
	    y0 = _y0;
	}

protected:
    // PROJ4 compatibility
    virtual void	printPROJ4Globals(IL_STDPREF ostream&) const;
    virtual void	printPROJ4Specifics(IL_STDPREF ostream&) const;

    // error management
    inline void		setError(IlvMapsError error) { _error = error; }
    void		addError(IlvMapsError error);

    // Implementing the projection
    virtual IlvMapsError	sForward(IlvCoordinate& ll) const = 0;
    virtual IlvMapsError	eForward(IlvCoordinate& ll) const;
    virtual IlvMapsError	sInverse(IlvCoordinate& xy) const;
    virtual IlvMapsError	eInverse(IlvCoordinate& xy) const;

    static IlDouble	AdjustLongitude(IlDouble lon);

private:
    // class intialization and finalization
    IlvMapsIcFriend(project, ILVMAPSEXPORTED);

    static void		Init();
    static void		InitAccessors();

    // PROJ4 compatibility
    void		parsePROJ4Values(IlStringHashTable* );

private:
    // Projection parameters
    IlvEllipsoid*		_ellipsoid;
    IlBoolean			_geoc;
    IlBoolean			_over;
    IlvUnitConverter*		_converter;
    IlvProjectionGeometricProperty _property;
    IlDouble			_lam0;
    IlDouble			_phi0;
    IlDouble			_x0;
    IlDouble			_y0;
    IlBoolean			_ellipsoidEnabled;
    IlBoolean			_inverseEnabled;
    IlvHorizontalDatum* 	_datum;

    // Error management
    IlvMapsError		_error;

    // Class info
    static IlvClassInfo*	_classinfo;
    IlvProjectionInterface*	_interface;

    // Sharing management
    IlBoolean			_isShared;
    IlInt			_lockCount;
};

#endif /* __Ilv_Maps_Project_H */
