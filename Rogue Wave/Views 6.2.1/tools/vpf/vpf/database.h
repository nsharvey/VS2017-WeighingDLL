// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/database.h
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
// Declaration of the VpfDatabase class
// --------------------------------------------------------------------------
#ifndef VPF_DATABASE_H
#define VPF_DATABASE_H

#include <vpf/string.h>

class VpfLibrary;
class VpfDate;

// --------------------------------------------------------------------------
class VpfDatabase
{
public:
    VpfDatabase(const char* path);
    virtual ~VpfDatabase();
    // ____________________________________________________________
    inline int		isBad() const { return ((const char*)_path == 0); }
    inline void		setBad() { _path = 0; }
    inline const char*	getPath() const { return _path; }
    inline const char*	getDir() const { return _dir; }
    inline VpfUInt	getNLibraries() const { return _nLibraries; }
    inline VpfLibrary*	getLibrary(VpfUInt i) const { return _libraries[i]; }
    VpfLibrary*	getLibrary(const char*) const;
    inline const char*	getVersion() const { return _version; }
    inline const char*	getName() const { return _name; }
    inline const char*	getDescription() const { return _description; }
    inline const char*	getMediaStandard() const { return _mediaStandard; }
    inline const char*	getOriginator() const { return _originator; }
    inline const char*	getAddressee() const { return _addressee; }
    inline const char*	getMediaVolumes() const { return _mediaVolumes; }
    inline const char*	getSequenceNumbers() const { return _sequenceNumbers; }
    inline const char*	getNumberOfDataSets() const
			{
			    return _numberOfDataSets;
			}
    inline char		getSecurityClass() const { return _securityClass; }
    inline const char*	getDowngrading() const { return _downgrading; }
    inline const VpfDate*	getDowngradeDate() const
				{
				    return _downgradeDate;
				}
    inline const char*	getReleasability() const { return _releasability; }
    inline const char*	getOtherStandardName() const
			{
			    return _otherStandardName;
			}
    inline const VpfDate*	getOtherStandardDate() const
				{
				    return _otherStandardDate;
				}
    inline const char*	getOtherStandardVersion() const
			{
			    return _otherStandardVersion;
			}
    inline const char*	getTransmittalID() const { return _transmittalID; }
    inline const char*	getEditionNumber() const { return _editionNumber; }
    inline const VpfDate*	getEditionDate() const { return _editionDate; }

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
