// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/vfhash.cpp
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
// Implementation of the hashing routines for vectorial fonts
// --------------------------------------------------------------------------
#include <vfincl/vect.h>
#include <string.h>

// --------------------------------------------------------------------------
IlUInt
IlvVectFontHashTable::hash(const IlAny tag) const
{
    IlvVectFont* v = (IlvVectFont*)tag;
    IlInt sx, sy;
    v->getSizes(sx, sy);
    IlUInt style   = v->getStyle(), quality = v->getQuality();
    return hashVectFont(sx, sy, v->getAngle(), v->getSlant(), style, quality);
}

// --------------------------------------------------------------------------
IlInt
IlvVectFontHashTable::hashVectFont(IlInt	sizex,
				   IlInt	sizey,
				   IlFloat	angle,
				   IlFloat	slant,
				   IlUInt	style,
				   IlUInt	quality) const
{
    IlUInt hashp;
    hashp  = (IlUInt)sizex;
    hashp ^= (IlUInt)sizey;
    hashp ^= *((IlUInt*)&angle);
    hashp ^= *((IlUInt*)&slant);
    hashp ^= style;
    hashp ^= quality;
    return hashp % _nBuckets;
}

// --------------------------------------------------------------------------
IlBoolean
IlvVectFontHashTable::matchVectFont(const IlvVectFont*	vf,
				    IlInt		sizex,
				    IlInt		sizey,
				    IlFloat		angle,
				    IlFloat		slant,
				    IlUInt		style,
				    IlUInt		quality) const
{
    IlInt sx, sy;
    ((IlvVectFont*)vf)->getSizes(sx, sy);
    IlUInt vfstyle   = vf->getStyle(), vfquality = vf->getQuality();
    if ((sizex   == sx)             &&
	(sizey   == sy)             &&
	(IlAbs(angle - vf->getAngle()) < (IlFloat)0.1) &&
	(IlAbs(slant - vf->getSlant()) < (IlFloat)0.1) &&
	(style   == vfstyle)        &&
	(quality == vfquality))
	return IlTrue;
    else
	return IlFalse;
}

// --------------------------------------------------------------------------
void
IlvVectFontHashTable::insert(const IlvVectFont* vf)
{
    IlInt hash = IlvVectFontHashTable::hash((IlAny) vf);
    IlHashTable::insert(hash, (IlAny) vf, (IlAny) vf);
}

// --------------------------------------------------------------------------
IlvVectFont*
IlvVectFontHashTable::findVectFont(IlInt	sizex,
				   IlInt	sizey,
				   IlFloat	angle,
				   IlFloat	slant,
				   IlUInt	style,
				   IlUInt	quality) const
{
    IlInt hash = IlvVectFontHashTable::hashVectFont(sizex,
						    sizey,
						    angle,
						    slant,
						    style,
						    quality);
    for (IlEntry* entry = _buckets[hash].getFirst();
	 entry != (IlEntry*)0;
	 entry = entry->getNext())
	if (IlvVectFontHashTable::matchVectFont((IlvVectFont*)entry->getTag(),
						sizex,
						sizey,
						angle,
						slant,
						style,
						quality))
	    return (IlvVectFont*)entry->getValue();
    return (IlvVectFont*)0;
}

// --------------------------------------------------------------------------
IlBoolean
IlvVectFontHashTable::remove(const IlvVectFont* vf)
{
    IlInt hash = IlvVectFontHashTable::hash((IlAny)vf);
    return IlHashTable::remove(hash, (IlAny)vf);
}

// --------------------------------------------------------------------------
inline void
PrintNotImp(char const* ope, char const* hash)
{
    IlvFatalError("Not Implemented %s for %s", ope, hash);
}

// --------------------------------------------------------------------------
void
IlvVectFontHashTable::insert(const IlAny, const IlAny)
{
    PrintNotImp("Insert", "IlvVectFontHashTable");
}

// --------------------------------------------------------------------------
IlBoolean
IlvVectFontHashTable::remove(const IlAny)
{
    PrintNotImp("Remove", "IlvVectFontHashTable");
    return IlFalse;
}

// --------------------------------------------------------------------------
IlAny
IlvVectFontHashTable::find(const IlAny,
			   IlHashMatchFunction, IlAny) const
{
    PrintNotImp("Find", "IlvVectFontHashTable");
    return 0;
}
