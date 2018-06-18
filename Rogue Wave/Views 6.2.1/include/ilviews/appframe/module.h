// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/module.h
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
// Declaration of IlvDvModule class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Module_H)
#define __Ilv_Appframe_Module_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif

#if !defined(__Ilv_Base_Modules_H)
#include <ilviews/base/modules.h>
#endif

class IlvDvApplication;
class IlvDvModuleInfos;

// --------------------------------------------------------------------------
// IlvDvModuleDllParam class
// --------------------------------------------------------------------------
class IlvDvModuleDllParam
{
public:
    IlvDvModuleDllParam(IlvDvApplication* app, IlvDvModuleInfos* moduleInfos)
	: _app(app), _moduleInfos(moduleInfos) {}

    inline
    IlvDvApplication* getDvApplication() const { return _app; }
    inline
    IlvDvModuleInfos* getModuleInfos() const { return _moduleInfos; }

protected:
    IlvDvApplication* _app;
    IlvDvModuleInfos* _moduleInfos;
};

// --------------------------------------------------------------------------
// IlvDvModule class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvModule : public IlvModule
{
public:
    IlvDvModule(IlAny);
    virtual ~IlvDvModule();

    inline
    IlvDvApplication*	getDvApplication() const { return _app; }
    inline
    IlvDvModuleInfos*	getModuleInfos() const { return _moduleInfos; }

    void		setOptionFilename(const char*);
    void		setDataBaseFilename(const char*);

protected:
    IlvDvApplication*	_app;
    IlvDvModuleInfos*	_moduleInfos;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(module);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Module_H */
