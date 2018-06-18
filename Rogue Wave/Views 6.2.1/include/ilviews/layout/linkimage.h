// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/linkimage.h
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
// Declaration of the IlvLayoutLinkImage class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Linkimage_H
#define __Ilv_Layout_Linkimage_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Grapher_Polylink_H)
#include <ilviews/grapher/polylink.h>
#endif /* __Ilv_Grapher_Polylink_H */

class ILVGRLEXPORTED IlvLayoutLinkImage
: public IlvPolylineLinkImage
{
public:
    IlvLayoutLinkImage(IlvDisplay* display,
		       IlBoolean  oriented,
		       IlUInt     count,
		       IlvPoint*   points,
		       IlvGraphic* from,
		       IlvGraphic* to,
		       IlvPalette* palette = 0);
    ~IlvLayoutLinkImage();

    void	movePoint(IlUInt index, IlInt x, IlInt y,
			  IlvTransformer* t);

    IlvPoint* getLinkPoints(IlUInt&              nPoints,
			    const IlvTransformer* t = 0) const;
    IlvPoint* getPoints(IlUInt& count)
#if (IlvVersion < 400)
 const
#endif
;
    virtual IlUInt getPointsCardinal() const;

    virtual void	setIntermediateLinkPoints(IlvPoint*, IlUInt, IlUInt);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvLayoutLinkImage);
protected:
    IlvPoint* computeAllPoints(IlUInt&,
			       const IlvTransformer* t = 0) const;
private:
    IlvPolyPoints* _plyPoints;
    void	computePoints(IlvPoint& src,
			      IlvPoint& dst,
			      const IlvTransformer* t) const;
};


ILVGRLMODULEINIT(l_linkimage);
#endif /* !__Ilv_Layout_Linkimage_H */
