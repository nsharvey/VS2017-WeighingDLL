// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/i18n.h
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
// Declaration of the IlI18N class that contains several I18N-related
// routines.
// Defined in library ilog
// --------------------------------------------------------------------------
#ifndef __Il_I18n_H
#define __Il_I18n_H

#include <ilog/macros.h>

typedef IlUChar  IlUTF8;
typedef IlUShort IlUTF16;
typedef IlUInt   IlUTF32;

// --------------------------------------------------------------------------
class IlI18n
{
public:
    static IlUTF16* Utf8ToUtf16(IlUInt& outputSize,
				IlUInt  inputSize,
				const IlUTF8* input);
    static IlUTF8* Utf16ToUtf8(IlUInt& outputSize,
			       IlUInt  inputSize,
			       const IlUTF16* input);
};

#endif /* !__Ilv_I18n_H */
