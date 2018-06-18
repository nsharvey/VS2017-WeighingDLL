// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/coverage.h
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
// Declaration of the coverages-related classes
// --------------------------------------------------------------------------
#ifndef VPF_COVERAGE_H
#define VPF_COVERAGE_H

#include <vpf/string.h>

class VpfLibrary;
class VpfFeatureClass;
class VpfTheme;

// --------------------------------------------------------------------------
class VpfCoverage
{
public:
    VpfCoverage(VpfLibrary*, char*, char*, VpfInt);
    ~VpfCoverage();
    // ____________________________________________________________
    inline int		isBad() const { return (_library == 0); }
    inline void		setBad() { _library = 0; }

    inline VpfLibrary*	getLibrary() const { return _library; }

    inline const char*	getPath() const { return _path; }
    inline const char*	getDir() const { return _dir; }
    inline const char*	getName() const { return _name; }
    inline const char*	getDescription() const { return _description; }
    inline VpfInt	getTopologyLevel() const { return _topologyLevel; }

    inline VpfUInt	getNFeatureClasses() const { return _nFeatureClasses; }
    inline VpfFeatureClass*	getFeatureClass(VpfUInt i) const
				{
				    return _featureClasses[i];
				}
    VpfFeatureClass*	getFeatureClass(const char*) const;

    inline VpfUInt	getNThemes() const { return _nThemes; }
    inline VpfTheme*	getTheme(VpfUInt i) const { return _themes[i]; }

    int			isTiled() const;

protected:
    int initFeatureClasses();
    int initThemes();
    VpfLibrary*		_library;
    VpfString		_name;
    VpfString		_path;
    VpfString		_dir;
    VpfString		_description;
    VpfInt		_topologyLevel;
    VpfUInt		_nFeatureClasses;
    VpfFeatureClass**	_featureClasses;
    VpfUInt		_nThemes;
    VpfTheme**		_themes;
};

#endif /* _COVERAGE_H */
