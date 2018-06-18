// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/graphics/maplabel.h
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
// Rogue Wave Views - Maps add-on.
// Declaration of the half zoomable label
// --------------------------------------------------------------------------

#ifndef IlvMapHZLabel_H
#define IlvMapHZLabel_H

#include <ilviews/macros.h>
#include <ilviews/graphics/label.h>
#include <ilviews/maps/macros.h>

ILVMAPSMODULEINIT(maplabel);

class ILVMAPSEXPORTED IlvMapLabel : public IlvLabel
{
public:
    IlvMapLabel(IlvDisplay* display,
		  const IlvPoint& anchor,
		  const IlvPoint& offset,
		  IlvPosition position,
		  IlvDim maxLabelLength,
		  const char* label,
		  IlvPalette* palette = 0);

    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* r = 0) const;

    virtual void	boundingBox(IlvRect& rect,
				    const IlvTransformer* r = 0) const;
    virtual IlBoolean	zoomable() const;
    virtual void	applyTransform(const IlvTransformer*);
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* = 0) const;


    void		setAttachment(const IlvPoint& anchor,
				      const IlvPoint& offset,
				      IlvPosition position)
			{
			    _anchor = anchor;
			    _delta = offset;
			    _position = position;
			}

    IlvPoint		getAnchor() const { return _anchor; }

    IlvPoint		getOffset() const { return _delta; }

    IlvPosition		getPosition() const { return _position; }

    void		setMaxLabelLength(IlvDim length) { _size = length; }

    IlvDim		getMaxLabelLength() const { return _size; }

    static IlvDim	GetLength(IlvDisplay* display,
				  IlvDim height,
				  const char* label,
				  IlvPalette* palette = 0);

protected:
    virtual void	drawMinimizedRect(IlvPort* dst,
					  const IlvRect& minimizedRect) const;

private:
    void		getStringRect(const IlvRect& bbox,
				      const IlvPoint& tanchor,
				      IlvRect& rect) const;
    void		getMinimizedRect(const IlvRect& trect,
					 const IlvPoint& tanchor,
					 const IlvTransformer* t,
					 IlvRect& mRect) const;


    IlvPoint		_anchor;
    IlvPoint		_delta;
    IlvPosition		_position;
    IlvDim		_size;

 protected:
   IlvMapsIcFriend(maplabel, ILVMAPSEXPORTED);
   DeclareTypeInfo();
   DeclareIOConstructors(IlvMapLabel); 
};

#endif
