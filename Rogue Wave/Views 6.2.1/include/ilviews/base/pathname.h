// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/pathname.h
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
// Encapsulation of the IlPathName and related classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Pathname_H
#define __Ilv_Base_Pathname_H

#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif
#if !defined(__Il_Pathname_H)
#include <ilog/pathname.h>
#endif

#define IlvFileExists IlPathName::doesExist
#define IlvIsFileWritable(filename, message, display) \
    (IlPathName::isWritable(filename) ? IlTrue : \
     ((display ? display->bell(), IlFalse : IlFalse), \
      (message ? IlvFatalError("## Cannot open %s for writing", filename), IlFalse : IlFalse)))

#define IlvPathName IlPathName

#endif /* !__Il_Base_PathName_H */
