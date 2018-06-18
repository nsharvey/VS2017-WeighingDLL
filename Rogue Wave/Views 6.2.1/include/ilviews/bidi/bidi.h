// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bidi/bidi.h
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
// Bidi support public API
// --------------------------------------------------------------------------
#ifndef __Ilv_Bidi_Bidi_H
#define __Ilv_Bidi_Bidi_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Bidi_Type_H)
#include <ilviews/bidi/type.h>
#endif

class IlvDisplay;
class IlvFont;
class IlvPort;

ILVDSPEXPORTEDFUNCTION(IlBoolean) IlvUsingBidi(IlvDisplay*);
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDefaultNumerals(IlvDisplay*, IlvNumerals);
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDefaultSwapping(IlvDisplay*, IlvSwapping);
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDefaultLayoutDirection(IlvDisplay*, IlvLayoutDirection);
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDefaultShaping(IlvDisplay*, IlvShaping);
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDefaultWordBreak(IlvDisplay*, IlvWordBreak);
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDefaultBidiValues(IlvDisplay*,
			IlvNumerals,
			IlvSwapping,
			IlvLayoutDirection,
			IlvShaping,
			IlvWordBreak);
ILVDSPEXPORTEDFUNCTION(void)
IlvGetDefaultBidiValues(IlvDisplay*,
			IlvNumerals*,
			IlvSwapping*,
			IlvLayoutDirection*,
			IlvShaping*,
			IlvWordBreak*);

class IlvBidiString;

ILVDSPEXPORTEDFUNCTION(const IlvBidiString*)
IlvGetBidiString(const IlvFont*, const char*, int, const IlvPort* = 0);

ILVDSPEXPORTEDFUNCTION(const IlvBidiString*)
IlvGetBidiString(const IlvFont*,
		 const char*,
		 int,
		 IlvNumerals,
		 IlvSwapping,
		 IlvLayoutDirection,
		 IlvShaping,
		 IlvWordBreak,
		 const IlvPort* = 0);

#if !defined(ILVDSPLIB)

class IlvGraphic;

ILVVWSEXPORTEDFUNCTION(void)
IlvSetBidiValuesToDefault(IlvDisplay*, IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(void)
IlvSetNumerals(IlvDisplay*, IlvGraphic*, IlvNumerals);
ILVVWSEXPORTEDFUNCTION(void)
IlvSetSwapping(IlvDisplay*, IlvGraphic*, IlvSwapping);
ILVVWSEXPORTEDFUNCTION(void)
IlvSetLayoutDirection(IlvDisplay*, IlvGraphic*, IlvLayoutDirection);
ILVVWSEXPORTEDFUNCTION(void)
IlvSetShaping(IlvDisplay*, IlvGraphic*, IlvShaping);
ILVVWSEXPORTEDFUNCTION(void)
IlvSetWordBreak(IlvDisplay*, IlvGraphic*, IlvWordBreak);
ILVVWSEXPORTEDFUNCTION(void)
IlvSetBidiValues(IlvDisplay*,
		 IlvGraphic*,
		 IlvNumerals,
		 IlvSwapping,
		 IlvLayoutDirection,
		 IlvShaping,
		 IlvWordBreak);

ILVVWSEXPORTEDFUNCTION(IlInt)
IlvHasDefaultBidiValues(IlvDisplay*, const IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(IlvNumerals)
IlvGetNumerals(IlvDisplay*, const IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(IlvSwapping)
IlvGetSwapping(IlvDisplay*, const IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(IlvLayoutDirection)
IlvGetLayoutDirection(IlvDisplay*, const IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(IlvShaping)
IlvGetShaping(IlvDisplay*, const IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(IlvWordBreak)
IlvGetWordBreak(IlvDisplay*, const IlvGraphic*);
ILVVWSEXPORTEDFUNCTION(void)
IlvGetBidiValues(IlvDisplay*,
		 const IlvGraphic*,
		 IlvNumerals*,
		 IlvSwapping*,
		 IlvLayoutDirection*,
		 IlvShaping*,
		 IlvWordBreak*);

#if !defined(ILVVWSLIB)
#  if defined(ILVGDTEXPORTEDFUNCTION)
class IlvGadgetContainer;
class IlvGadgetManager;

ILVGDTEXPORTEDFUNCTION(IlvLayoutDirection)
IlvGetLayoutDirection(const IlvGadgetContainer*);
ILVGDTEXPORTEDFUNCTION(IlvLayoutDirection)
IlvGetLayoutDirection(const IlvGadgetManager*);
ILVGDTEXPORTEDFUNCTION(IlBoolean)
IlvSetLayoutDirection(IlvGadgetContainer*, IlvLayoutDirection);
ILVGDTEXPORTEDFUNCTION(IlBoolean)
IlvSetLayoutDirection(IlvGadgetManager*, IlvLayoutDirection);
ILVGDTEXPORTEDFUNCTION(void)
IlvFlipAllViews(IlvDisplay*, IlBoolean);
ILVGDTEXPORTEDFUNCTION(void)
_IlvFlipObjects(IlvGadgetManager* gadmgr);
#  endif /* defined(ILVGDTEXPORTEDFUNCTION) */
#endif  /* ! ILVVWSLIB */

ILVVWSMODULEINIT(bidi);

#endif /* ! ILVDSPLIB */

#endif /* !__Ilv_Bidi_Bidi_H */
