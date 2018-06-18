// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/objcls.h
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
#ifndef __Ili_Compat_Objcls_H
#define __Ili_Compat_Objcls_H

#include <ilviews/dataccess/objcls.h>

#ifdef ILI_COMPAT_PREFIX
#  define IlvSwClassInfo              IliClassInfo
#  define IlvSwTypeReader             IliTypeReader
#  define IlvSwDTypeReader            IliDTypeReader
#  define IlvSwTypeDuplicator         IliTypeDuplicator
#  define IlvSwDeclareTypeInfo        IliDeclareTypeInfo
#  define IlvSwDeclareDTypeInfo       IliDeclareDTypeInfo
#  define IlvSwDeclareTypeInit_exp    IliDeclareTypeInit_exp
#  define IlvSwDeclareTypeInit        IliDeclareTypeInit
#  define IlvSwRegisterClass          IliRegisterClass
#  define IlvSwRegisterClassCompat    IliRegisterClassCompat
#  define IlvSwRegisterDClass         IliRegisterDClass
#  define IlvSwRegisterDClassCompat   IliRegisterDClass
#  define IlvSwRegisterDClassEx       IliRegisterDClassEx
#  define IlvSwRegisterDClassExCompat IliRegisterDClassExCompat
#endif

#endif


