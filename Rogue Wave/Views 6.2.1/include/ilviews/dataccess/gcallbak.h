// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gcallbak.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliCallbackManager class
// Defined in library dbgadget
// --------------------------------------------------------------------------

#ifndef __Ili_Gcallbak_H
#define __Ili_Gcallbak_H

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ilv_Base_Graphic_H
#  include <ilviews/base/graphic.h>
#endif

#ifndef __Ili_Module_H
#  include <ilviews/dataccess/module.h>
#endif

typedef void (* IliGlobalGraphicCallback) (IlvGraphic* g,IlAny arg,
					   IlInt paramsCount,
					   const char* const* params);
IL_DEFINEFPTRTOANYCAST(IliGlobalGraphicCallback);

class ILV_DBG_EXPORTED IliCallbackManager
{
public:
    virtual IlBoolean	callGlobalCallback(IlvGraphicHolder* holder,
					   IlvGraphic* obj,
					   const char* macro,
					   IlAny arg) const;
    virtual IlBoolean	callHolderCallback(IlvGraphicHolder* holder,
					   IlvGraphic* obj,
					   const IlvSymbol* callbackName,
					   IlAny arg) const;
    virtual IlBoolean	callCallback(IlvGraphicHolder* holder,
				     IlvGraphic* obj,
				     const IlvSymbol* callbackName,
				     IlAny arg) const;
    void		registerCallback(const IlvSymbol* callbackName,
					 IliGlobalGraphicCallback cb);

    void		unregisterCallback(const IlvSymbol* callbackName);

    IliGlobalGraphicCallback getCallback(const IlvSymbol* callbackName) const;

    const IlvSymbol**	getCallbackNames(IlUInt& count) const;

    IlBoolean		isQuitCallbackEnabled() const;
    void		enableQuitCallback(IlBoolean);

    static void		AtInit();
    static void		AtExit();

protected:
    IlvHashTable	_globalCallbacks;
    IlBoolean		_allowQuitCallback;

    IliCallbackManager();
    virtual ~IliCallbackManager();

    void		registerSystemCallbacks();

    friend class IliModuleCLASS(IliCallbackManager);
};

#ifdef DOXYGEN_GENERATION
IliCallbackManager& IliGetCallbackManager();
#else
ILV_DBG_EXPORTEDFN(IliCallbackManager&)
IliGetCallbackManager();
#endif

IliModuleDECL_exp(ILV_DBG_EXPORTED,IliCallbackManager);

#endif
