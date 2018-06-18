// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/mgrpal.cpp
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
// Implementation of the IlvManagerPalette class
// ------------------------------------------------------------------------

#include <ilviews/mgrpal.h>

// ------------------------------------------------------------------------
IlvManagerPalette::IlvManagerPalette(IlvManager*    manager,
				   const IlvRect& size,
				   IlvBoolean     visible)
: IlvPaletteSelector(manager->getDisplay(), size, visible)
{
    _manager = manager;
}

// ------------------------------------------------------------------------
IlvManagerPalette::IlvManagerPalette(IlvManager*    manager,
				     IlvSystemView xany)
: IlvPaletteSelector(manager->getDisplay(), xany)
{
    _manager = manager;
}

// ------------------------------------------------------------------------
IlvManagerPalette::IlvManagerPalette(IlvManager*       manager,
				     IlvRowColumnView* rc)
: IlvPaletteSelector(manager->getDisplay(),rc)
{
    _manager = manager;
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeLineStyle(IlvGraphic* obj, IlvAny style)
{
    obj->setLineStyle((IlvLineStyle*)style);
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeArcMode(IlvGraphic* obj, IlvAny f)
{
    obj->setArcMode((IlvArcMode)IlCastIlAnyToIlInt(f));
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeFillRule(IlvGraphic* obj, IlvAny f)
{
    obj->setFillRule((IlvFillRule)IlCastIlAnyToIlInt(f));
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeFillStyle(IlvGraphic* obj, IlvAny f)
{
    obj->setFillStyle((IlvFillStyle)IlCastIlAnyToIlInt(f));
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeLineWidth( IlvGraphic* obj, IlvAny arg)
{
    obj->setLineWidth(IlCastIlAnyToIlUShort(arg));
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangePattern(IlvGraphic* obj, IlvAny pattern)
{
    obj->setPattern((IlvPattern*)pattern);
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeBackground(IlvGraphic* obj, IlvAny color)
{
    obj->setBackground((IlvColor*)color);
}

// ------------------------------------------------------------------------
static void ILVCALLBACK
ChangeForeground(IlvGraphic* obj, IlvAny color)
{
    obj->setForeground((IlvColor*)color);
}

#define CHANGERESSOURCE(function, ressource) \
     _manager->applyToSelections(function, (IlvAny)ressource);

// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvPattern* bitmap)
{
    CHANGERESSOURCE(ChangePattern, bitmap);
}
// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvLineStyle* sty)
{
    CHANGERESSOURCE(ChangeLineStyle, sty);
}

// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvUShort width)
{
    CHANGERESSOURCE(ChangeLineWidth, IlCastIlUShortToIlAny(width));
}

// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvArcMode am)
{
    CHANGERESSOURCE(ChangeArcMode, IlCastIlIntToIlAny((int)am));
}

// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvFillRule fill)
{
    CHANGERESSOURCE(ChangeFillRule, IlCastIlIntToIlAny((int)fill));
}

// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvFillStyle fillstyle)
{
    CHANGERESSOURCE(ChangeFillStyle, IlCastIlIntToIlAny((int)fillstyle));
}

// ------------------------------------------------------------------------
void
IlvManagerPalette::callCallback(IlvColor* color)
{
    if (_fillbackground) {
	CHANGERESSOURCE(ChangeBackground, color);
    }
    else {
	CHANGERESSOURCE(ChangeForeground, color);
    }
}
#undef CHANGERESSOURCE
