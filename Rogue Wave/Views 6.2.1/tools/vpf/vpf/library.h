// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/library.h
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
// Declaration of the VpfLibrary class
// --------------------------------------------------------------------------
#ifndef VPF_LIBRARY_H
#define VPF_LIBRARY_H

#include <vpf/basictypes.h>
#include <vpf/extent.h>
#include <vpf/string.h>

class VpfTile;
class VpfDatabase;
class VpfCoverage;
class VpfDate;

// --------------------------------------------------------------------------
class VpfLibrary
{
public:
    VpfLibrary(VpfDatabase*, const char*, const VpfExtent&);
    ~VpfLibrary();
    // ------------------------------------------------------------
    inline int		isBad() const { return (_name == 0); }
    inline void		setBad() { _name = 0; }

    inline const char*	getPath() const { return _path; }
    inline const char*	getDir() const { return _dir; }

    inline const VpfExtent& getExtent() const { return _extent; }

    inline const char*	getProductType() const { return _productType; }
    inline const char*	getName() const { return _name; }
    inline const char*	getDescription() const { return _description; }
    inline char		getDataStructCode() const { return _dataStructCode; }
    inline VpfInt	getScale() const { return _scale; }
    inline const char*	getSourceSeries() const { return _sourceSeries; }
    inline const char*	getSourceID() const { return _sourceID; }
    inline const char*	getSourceEdition() const { return _sourceEdition; }
    inline const char*	getSourceName() const { return _sourceName; }
    inline const VpfDate* getSourceDate() const { return _sourceDate; }
    inline char		getSecurityClass() const { return _securityClass; }
    inline const char*	getDowngrading() const { return _downgrading; }
    inline const VpfDate* getDowngradeDate() const { return _downgradeDate; }
    inline const char*	getReleasability() const { return _releasability; }

    inline VpfUInt	getNCoverages() const { return _nCoverages; }
    inline VpfCoverage*	getCoverage(VpfUInt i) const { return _coverages[i]; }
    VpfCoverage*	getCoverage(const char*) const;

    inline int		isTiled() const { return _isTiled; }
    inline VpfUInt	getNTiles() const { return _nTiles; }
    inline VpfTile*	getTile(VpfUInt i) { return _tiles[i]; }
    void		tileSelect(const VpfExtent& extent);

protected:
    int			initTiling();

    VpfString		_dir;
    VpfString		_path;
    VpfExtent		_extent;
    char*		_productType;
    char*		_name;
    char*		_description;
    char		_dataStructCode;
    VpfInt		_scale;
    char*		_sourceSeries;
    char*		_sourceID;
    char*		_sourceEdition;
    char*		_sourceName;
    VpfDate*		_sourceDate;
    char		_securityClass;
    char*		_downgrading;
    VpfDate*		_downgradeDate;
    char*		_releasability;
    int			_isTiled;
    VpfUInt		_nTiles;
    VpfTile**		_tiles;
    VpfUInt		_nCoverages;
    VpfCoverage**	_coverages;
};

#endif /* VPF_LIBRARY_H */
