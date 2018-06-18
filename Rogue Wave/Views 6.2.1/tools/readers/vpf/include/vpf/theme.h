// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/theme.h
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
// Declaration of the VpfTheme class
// --------------------------------------------------------------------------
#ifndef VPF_THEME_H
#define VPF_THEME_H

class VpfFeatureClass;
class VpfValue;

// --------------------------------------------------------------------------
class VpfTheme
{
public:
    VpfTheme(VpfFeatureClass*, const char*, VpfValue*);
    ~VpfTheme();
    // ____________________________________________________________
    VpfFeatureClass*	getFeatureClass() const { return _feature; }
    const char*		getAttribute() const	{ return _attribute; }
    VpfValue*		getValue() const        { return _value;   }
    int  isLoaded()      const { return _loaded; }
    void setLoaded(int flag=1) { _loaded = flag; }
private:
    VpfFeatureClass*	_feature;
    char*		_attribute;
    VpfValue*		_value;
    int			_loaded;      // Is is loaded, or not ?
};

#endif /* VPF_THEME_H */
