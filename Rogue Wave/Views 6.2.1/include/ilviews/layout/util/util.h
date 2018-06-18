// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/util/util.h
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
// Declaration of general utilities functions and classes
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Util_Util_H
#define __Ilv_Layout_Util_Util_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Layout_Gphadapt_H)
#include <ilviews/layout/gphadapt.h>
#endif

class ILVGRLEXPORTED IlvRandom
{
public:
    IlvRandom();
    IlvRandom(IlUShort);
    virtual ~IlvRandom();

    virtual IlFloat	nextFloat();
protected:
private:
    IlShort	_seedValue;
};

ILVGRLEXPORTEDFUNCTION(const char*) IlvLayoutCreateUniqueName(const char*);
ILVGRLEXPORTEDFUNCTION(IlBoolean) IlvLayoutUtilIntersects(const IlvPoint&,
							  const IlvPoint&,
							  const IlvPoint&,
							  const IlvPoint&);
ILVGRLEXPORTEDFUNCTION(IlBoolean) IlvLayoutUtilIntersects(IlFloat, IlFloat,
							  IlFloat, IlFloat,
							  IlFloat, IlFloat,
							  IlFloat, IlFloat);
ILVGRLEXPORTEDFUNCTION(void)
IlvLayoutDeleteIntermediatePointsOnLinks(IlvGraphModel* model,
					 IlvGraphLayout* layout,
					 IlBoolean redraw);
ILVGRLEXPORTEDFUNCTION(void)
IlvLayoutUtilBoundingBox(IlAny obj,
			 IlvRect& rect,
			 IlvTransformer* transformer);
#endif /* !__Ilv_Layout_Util_Util_H */
