// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/grhash.h
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
// Declaration of the palette hashing-related classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Grhash_H
#define __Ilv_Util_Grhash_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvHashTablePalette : public IlHashTable
{
public:
    IlvHashTablePalette(IlUInt size) : IlHashTable(size) {}

    virtual void	insert(const IlAny tag, const IlAny value);
    virtual IlBoolean	remove(const IlAny tag);
    virtual IlAny	find(const IlAny,
			     IlHashMatchFunction = 0,
			     IlAny userArg = 0) const;
    void		insert(const IlvPalette*);
    IlBoolean		remove(const IlvPalette*) ;
    IlvPalette*		findPalette(IlvColor*		bg,
				    IlvColor*		fg,
				    IlvPattern*		pat,
				    IlvColorPattern*	pixpat,
				    IlvFont*		fnt,
				    IlvLineStyle*	sty,
				    IlUShort		width,
				    IlvFillStyle	fs,
				    IlvArcMode		am,
				    IlvFillRule		fr,
				    IlvIntensity	alpha,
				    IlvAntialiasingMode antialias,
				    IlvGradientPattern*	grad) const;

protected:
    IlUInt		hash(const IlAny tag) const;
    static IlBoolean	matchPal(IlvColor*		bg,
				 IlvColor*		fg,
				 IlvPattern*		pat,
				 IlvColorPattern* 	pixpat,
				 IlvFont*		fnt,
				 IlvLineStyle*		sty,
				 IlUShort		width,
				 IlvFillStyle		fs,
				 IlvArcMode		am,
				 IlvFillRule		fr,
				 IlvIntensity		alpha,
				 IlvAntialiasingMode	antialias,
				 IlvGradientPattern*	grad,
				 IlvPalette*		palette);
    IlUInt		hashPal(IlvColor*,
				IlvColor*,
				IlvPattern*,
				IlvColorPattern*,
				IlvFont*,
				IlvLineStyle*,
				IlUShort width,
				IlvFillStyle,
				IlvArcMode,
				IlvFillRule,
				IlvIntensity alpha,
				IlvAntialiasingMode,
				IlvGradientPattern*) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvColorHashTable : public IlHashTable
{
public:
    IlvColorHashTable(IlUInt size) : IlHashTable(size) {}

    virtual void	insert(const IlAny, const IlAny);
    virtual IlBoolean	remove(const IlAny);
    virtual IlAny	find(const IlAny,
			     IlHashMatchFunction = 0, IlAny = 0) const;
    void		insert(const IlvColor*);
    IlBoolean		remove(const IlvColor*) ;
    IlvColor*		findColor(const char*, const IlAny) const;

protected:
    IlUInt		hash(const IlAny) const;
    IlBoolean		matchColor(const IlvColor*,
				   const char*,
				   const IlAny) const;
    IlUInt		hashColor(const char*, const IlAny) const;
};

#endif /* !__Ilv_Util_Grhash_H */
