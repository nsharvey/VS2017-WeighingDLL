// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/database.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the VpfDatabase class
// --------------------------------------------------------------------------
#ifndef VPF_DATABASE_H
#define VPF_DATABASE_H

#include <vpf/string.h>

class VpfLibrary;
class VpfDate;

// --------------------------------------------------------------------------
class VpfDatabase {
public:
    VpfDatabase(const char* path);
    virtual ~VpfDatabase();
    // ____________________________________________________________
    int isBad() const { return ((const char*)_path == 0); }
    void setBad() { _path = 0; }
    const char* getPath() const { return _path; }
    const char* getDir() const { return _dir; }
    VpfUInt        getNLibraries() const { return _nLibraries; }
    VpfLibrary*    getLibrary(VpfUInt i) const { return _libraries[i]; }
    VpfLibrary*    getLibrary(const char*) const;
    const char*    getVersion() const { return _version; }
    const char*    getName() const { return _name; }
    const char*    getDescription() const { return _description; }
    const char*    getMediaStandard() const { return _mediaStandard; }
    const char*    getOriginator() const { return _originator; }
    const char*    getAddressee() const { return _addressee; }
    const char*    getMediaVolumes() const { return _mediaVolumes; }
    const char*    getSequenceNumbers() const { return _sequenceNumbers; }
    const char*    getNumberOfDataSets() const { return _numberOfDataSets; }
    char           getSecurityClass() const { return _securityClass; }
    const char*    getDowngrading() const { return _downgrading; }
    const VpfDate* getDowngradeDate() const { return _downgradeDate; }
    const char*    getReleasability() const { return _releasability; }
    const char*    getOtherStandardName() const { return _otherStandardName; }
    const VpfDate* getOtherStandardDate() const { return _otherStandardDate; }
    const char*    getOtherStandardVersion() const { return _otherStandardVersion; }
    const char*    getTransmittalID() const { return _transmittalID; }
    const char*    getEditionNumber() const { return _editionNumber; }
    const VpfDate* getEditionDate() const { return _editionDate; }
protected:
    VpfString		_dir;
    VpfString		_path;
    char*		_version;
    char*		_name;
    char*		_description;
    char*		_mediaStandard;
    char*		_originator;
    char*		_addressee;
    char*		_mediaVolumes;
    char*		_sequenceNumbers;
    char*		_numberOfDataSets;
    char		_securityClass;
    char*		_downgrading;
    VpfDate*		_downgradeDate;
    char*		_releasability;
    char*		_otherStandardName;
    VpfDate*		_otherStandardDate;
    char*		_otherStandardVersion;
    char*		_transmittalID;
    char*		_editionNumber;
    VpfDate*		_editionDate;
    VpfUInt		_nLibraries;
    VpfLibrary**	_libraries;
};

#endif /* VPF_DATABASE_H */
