// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/shadlab.h
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
// Declaration of the IlvShadowLabel class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Shadlab_H
#define __Ilv_Graphics_Shadlab_H

#if !defined(__Ilv_Graphics_Shadrect_H)
#include <ilviews/graphics/shadrect.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvShadowLabel : public IlvShadowRectangle
{
public:
    IlvShadowLabel(IlvDisplay*    display,
		   const char*    label,
		   const IlvRect& rect,
		   IlUShort       thickness      = IlvDefaultShadowThickness,
		   IlvPosition    shadowPosition = IlvBottomRight,
		   IlvPalette*    palette        = 0);
    IlvShadowLabel(IlvDisplay*     display,
		   const IlvPoint& at,
		   const char*     label,
		   IlUShort        thickness      = IlvDefaultShadowThickness,
		   IlvPosition     shadowPosition = IlvBottomRight,
		   IlvPalette*     palette        = 0);
    virtual ~IlvShadowLabel();

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    inline const char*	getLabel() const { return _label; }
    void		setLabel(const char* label);
    virtual void	setFont(IlvFont* fnt);
    virtual void	print(ILVSTDPREF ostream&, int detail = 0) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvShadowLabel);

protected:
    char*		_label;
};

ILVVWSMODULEINIT(g0shadlab);
#endif /* !__Ilv_Graphics_Shadlab_H */
