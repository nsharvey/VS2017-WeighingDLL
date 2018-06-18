// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/modules.h
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
// Declaration of the dynamic loader related classes
// --------------------------------------------------------------------------
#ifndef __Il_Modules_H
#define __Il_Modules_H

#if !defined(__Il_Macros_H)
#include <ilog/macros.h>
#endif
#if !defined(__Il_Pathname_H)
#include <ilog/pathname.h>
#endif
#if !defined(__Il_Xml_H)
#include <ilog/xml.h>
#endif

// --------------------------------------------------------------------------
class IlModule;
class ILOG_EXPORTED IlModuleDescriptor
{
public:
    virtual const char*	         getName() const = 0;
    virtual int 	         getVersion() const = 0;
    virtual const IlPathName&    getLibPath() const = 0;
    virtual const IlXmlDocument* getDescriptor() const = 0;
    virtual IlModule*		 getModule() const = 0;
protected:
    virtual ~IlModuleDescriptor();
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlModule
{
public:
    enum Error {
	NoError,
	ModuleNotFound,
	EntryPointNotFound,
	DependencyNotResolved
    };
    IlModule();
    virtual ~IlModule();
    // ____________________________________________________________
    static void			ReScan();
    static IlModule*		Load(const char* moduleName,
				     void*	      userArg    = 0);
    static IlModule*		Load(IlModuleDescriptor* descriptor,
				     void* userArg = 0);
    static IlModuleDescriptor*	Find(const char* moduleName);
    inline static IlModule*	IsLoaded(const char* moduleName)
	{
	    IlModuleDescriptor* desc = Find(moduleName);
	    return desc
		? desc->getModule()
		: 0;
	}
    static Error		GetError();
    static void			SetError(Error error);
    static IlModuleDescriptor**	GetDescriptors(IlUInt&);
private:
    IlModuleDescriptor*		_descriptor;
};

#if !defined(IL_INITMODULENAME)
#define IL_INITMODULENAME IlInitModule
#endif /* !IL_INITMODULENAME */
#define IL_INITIALIZEMODULE(className)					\
extern "C" IL_BASEEXPORTEDFUNCTION(IlModule*) IL_INITMODULENAME(void*);	\
IL_BASEEXPORTEDFUNCTION(IlModule*) IL_INITMODULENAME(void* arg)		\
{ return new className(arg); }

#endif /* __Il_Modules_H */
