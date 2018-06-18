// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/modules.h
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
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Modules_H
#define __Ilv_Base_Modules_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Il_Modules_H)
#include <ilog/modules.h>
#endif
#if !defined(__Il_Modules_H)
#include <ilog/xml.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvModuleClassDescriptor
{
public:
    virtual ~IlvModuleClassDescriptor() {}
    virtual const char*		getClassName() const = 0;
    virtual const IlModuleDescriptor*	getDescriptor() const = 0;
    inline const char*		getName() const
				{
				    return getDescriptor()->getName();
				}
    inline const IlPathName&	getLibPath() const
				{
				    return getDescriptor()->getLibPath();
				}
    inline const IlXmlDocument*	getXmlDescriptor() const
				{
				    return getDescriptor()->getDescriptor();
				}
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvModuleLoader
{
public:
    static IlvModuleLoader&	Get();
    static IlModule*		Load(const char* baseClass,
				     const char* classname);
    static IlModule*		Load(IlvModuleClassDescriptor*);
    static void			ReScan();

private:
    IlvModuleLoader();

#if defined(_AIX) || (defined(__alpha) && !defined(WIN32)) || defined(_MSC_VER) || defined(__BORLANDC__) || defined(__GNUC__)
public:
#endif /* _AIX || Alpha OSF || Microsoft C++ || Borland || __GNUC__ */
    ~IlvModuleLoader();

public:
    static IlvModuleClassDescriptor**	GetClassDescriptors(IlUInt&,
							    const char*);
    static IlBoolean		IsDynamic();
};

#define IlvModule IlModule
#define ILVINITIALIZEMODULE IL_INITIALIZEMODULE

#endif /* __Ilv_Base_Modules_H */
