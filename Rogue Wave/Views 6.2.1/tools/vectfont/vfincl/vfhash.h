// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/vfincl/vfhash.h
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
// Declaration of the vectorial font hashing-realted class
// --------------------------------------------------------------------------
#ifndef __Ilv_Vectfont_Vfhash_H
#define __Ilv_Vectfont_Vfhash_H

#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

#if defined(WINDOWS)
#  if defined(ILVVFLIB)
#    define ILVVFEXPORTED ILVBASEEXPORTED
#    define ILVVFEXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#  endif /* !ILVVFLIB */

#  if !defined(ILVVFEXPORTED)
#    define ILVVFEXPORTED ILVBASEIMPORTED
#    define ILVVFEXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#  endif /* ILVVFEXPORTED */
#endif /* WINDOWS */

#if !defined(ILVVFEXPORTED)
#  define ILVVFEXPORTED
#  define ILVVFEXPORTEDFUNCTION(type) type
#endif

class ILVVFEXPORTED IlvVectFont;

// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvVectFontHashTable
    : public IlHashTable
{
public:
    IlvVectFontHashTable(IlUInt size) : IlvHashTable(size) {}
    // ____________________________________________________________
    virtual void  insert(const IlAny tag, const IlAny value);
    virtual IlBoolean remove(const IlAny tag);
    virtual IlAny find(const IlAny,
		       IlHashMatchFunction = 0, IlAny = 0) const;
    void insert(const IlvVectFont*);
    IlBoolean remove(const IlvVectFont*);
    IlvVectFont* findVectFont(IlInt   sizex,
			      IlInt   sizy,
			      IlFloat angle,
			      IlFloat slant,
			      IlUInt  style   = 0,
			      IlUInt  quality = 0) const;
protected:
    virtual IlUInt hash(const IlAny tag) const;
    IlInt hashVectFont(IlInt   sizex,
		       IlInt   sizy,
		       IlFloat angle,
		       IlFloat slant,
		       IlUInt  style   = 0,
		       IlUInt  quality = 0) const;
    IlBoolean matchVectFont(const IlvVectFont* vf,
			    IlInt       sizex,
			    IlInt       sizy,
			    IlFloat     angle,
			    IlFloat     slant,
			    IlUInt      style   = 0,
			    IlUInt      quality = 0) const;
};

#endif /* !__Ilv_Vectfont_Vfhash_H */
