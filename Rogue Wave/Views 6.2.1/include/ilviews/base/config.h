// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/config.h
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
// Definition of the IlvDisplayConfiguration class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Config_H
#define __Ilv_Base_Config_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

// ----------------------------------------------------------------------
// IlvDisplayConfig
//     Display connection configuration.
//     This class is only used as a base class for device-dependant
//     configurations, and the subclasses are declared in
//     ilviews/<displaySystem>/config.h
// ----------------------------------------------------------------------
class ILVDSPEXPORTED IlvDisplayConfig
{
public:
    inline IlvDisplay*	getDisplay() const { return _display; }
    inline IlAny	getUserArg() const { return _userArg; }
    void		setDefaultBackground(const char* bgName,
					     IlBoolean   isMutable = IlFalse);
    void		setDefaultBackground(IlvIntensity r,
					     IlvIntensity g,
					     IlvIntensity b,
					     IlBoolean    isMutable);
    void		setDefaultForeground(const char* fgName,
					     IlBoolean   isMutable = IlFalse);
    void		setDefaultForeground(IlvIntensity r,
					     IlvIntensity g,
					     IlvIntensity b,
					     IlBoolean    isMutable);
protected:
    IlvDisplayConfig(IlvDisplay* display, IlAny userArg);
    ~IlvDisplayConfig();

    char*		_bgName;
    IlvIntensity	_bgR;
    IlvIntensity	_bgG;
    IlvIntensity	_bgB;
    IlBoolean		_isBgMutable;
    char*		_fgName;
    IlvIntensity	_fgR;
    IlvIntensity	_fgG;
    IlvIntensity	_fgB;
    IlBoolean		_isFgMutable;

private:
    IlvDisplay*		_display;
    IlAny		_userArg;
    friend class	IlvDisplay;
};

#endif /* __Ilv_Base_Config_H */
