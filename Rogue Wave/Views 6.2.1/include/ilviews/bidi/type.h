// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bidi/type.h
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
// Type definitions needed for Bidi support
// --------------------------------------------------------------------------
#ifndef __Ilv_Bidi_Type_H
#define __Ilv_Bidi_Type_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
typedef enum IlvNumerals {
    IlvNumeralsNominal,
    IlvNumeralsNational,
    IlvNumeralsContextual
} _IlvNumerals;

typedef enum IlvSwapping {
    IlvSwappingOff,
    IlvSwappingOn
} _IlvSwapping;

typedef enum IlvWordBreak {
    IlvWordBreakOff,
    IlvWordBreakOn
} _IlvWordBreak;

typedef enum IlvShaping {
    IlvShapingOff,
    IlvShapingOn
} _IlvShaping;

typedef enum IlvLayoutDirection {
    IlvLayoutDirectionLeftToRight,
    IlvLayoutDirectionRightToLeft,
    IlvLayoutDirectionContextual
} _IlvLayoutDirection;

class IlvBidiContext;
#if defined(WINDOWS)
class IlvWinBidiContext;
#endif /* WINDOWS */

class ILVDSPEXPORTED IlvBidiString
{
public:
    IlvBidiString();
    IlvBidiString(const IlvBidiString&);
    ~IlvBidiString();
    const char*		getString()		const	{ return _string;     }
    IlvBidiContext*	getContext()		const	{ return _context;    }
    void		setString(const char* str)	{ _string = str;      }
    void		setString(const char*, IlBoolean);
    void		setContext(IlvBidiContext*);
#if defined(WINDOWS)
    IlvWinBidiContext*	getWinContext()		const	{ return _winContext; }
    void setWinContext(IlvWinBidiContext*);
#endif /* WINDOWS */
protected:
    const char*		_string;
    IlvBidiContext*	_context;
#if defined(WINDOWS)
    IlvWinBidiContext*	_winContext;
#else  /* !WINDOWS */
    IlBoolean		_owner;
#endif /* !WINDOWS */
};
#endif /* __Ilv_Bidi_Type_H */
