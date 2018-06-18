// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/polysel.h
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
// Declaration of the IlvPolySelection class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Polysel_H
#define __Ilv_Graphics_Polysel_H

#if !defined(__Ilv_Graphics_Polypts_H)
#include <ilviews/graphics/polypts.h>
#endif

#define IlvDefaultPolySelectionSize 4

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPolySelection : public IlvSimpleGraphic
{
public:
    IlvPolySelection(IlvPolyPoints*	object,
		     IlUShort		size    = IlvDefaultPolySelectionSize,
		     IlvMarkerType	marker  = IlvMarkerFilledSquare,
		     IlvPalette*	palette = 0);
    virtual ~IlvPolySelection();
    // ____________________________________________________________
    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&              r,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    inline
    IlvPolyPoints*	getObject() const { return _object; }
    inline void		setObject(IlvPolyPoints*  object)
			{
			    delete _object;
			    _object = object;
			}
    inline IlUShort	getSize() const { return _size; }
    inline void		setSize(IlUShort size) { _size = size; }
    virtual IlInt	getPointIndex(const IlvPoint& point,
				      const IlvTransformer* t) const;
    inline void		translatePoint(const IlvPoint& delta, IlUInt index)
			{
			    _object->translatePoint(delta, index);
			}
    inline void		setPoint(const IlvPoint& point, IlUInt index)
			{
			    _object->setPoint(point, index);
			}
    inline void		getPoint(IlvPoint& point, IlUInt index) const
			{
			    _object->getPoint(point, index);
			}
    void		apply(IlvApplyObject f, IlAny arg);
    virtual void	setMode(IlvDrawMode);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvPolySelection);

protected:
    IlUShort		_size;    // size of the selection markers
    IlvPolyPoints*	_object;
    IlvMarkerType	_marker;
};

ILVVWSMODULEINIT(polysel);
#endif /* !__Ilv_Graphics_Polysel_H */
