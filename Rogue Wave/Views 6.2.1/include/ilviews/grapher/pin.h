// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/pin.h
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
// Declaration of the IlvGrapherPin class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Pin_H
#define __Ilv_Grapher_Pin_H

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGrapherPin : public IlvNamedProperty
{
public:
    IlvGrapherPin();

    virtual ~IlvGrapherPin();

    virtual
    const IlSymbol*	getValueName() const;

    virtual IlUInt	getCardinal(const IlvGraphic* node,
				    const IlvTransformer* t) const;
    virtual IlBoolean	getClosest(const IlvGraphic* node,
				   const IlvPoint& p,
				   const IlvTransformer* t,
				   IlvPoint& returnPoint,
				   IlUInt& pinIndex) const;
    virtual IlBoolean	getLinkLocation(const IlvGraphic* node,
					const IlvGraphic* link,
					const IlvTransformer* t,
					IlvPoint& returnPoint) const;
    virtual IlBoolean	getLocation(IlUInt pinIndex,
				    const IlvGraphic* node,
				    const IlvTransformer* t,
				    IlvPoint& returnPoint) const;

    virtual IlUInt	getPinIndex(const IlvGraphic* link, IlBoolean from);

    virtual void	setPinIndex(const IlvGraphic* link,
				    IlUInt pinIndex,
				    IlBoolean from);

    void		removePinIndex(const IlvGraphic*,
				       IlUInt,
				       IlBoolean from);
    void		removeLink(const IlvGraphic* node,
				   const IlvGraphic* link,
				   IlBoolean from);

    void		replaceLink(const IlvGraphic* oldLink,
				    const IlvGraphic* newLink,
				    IlBoolean from);

    IlvGraphic* const*	getLinks(const IlvGraphic* node,
				 IlUInt pinIndex,
				 IlBoolean from,
				 IlUInt& count) const;
    virtual void	drawGhost(IlvPort* dst,
				  IlvPalette* palette,
				  const IlvGraphic* node,
				  const IlvTransformer* t) const;

    static IlSymbol*	GetSymbol();
    static IlSymbol*	GrapherPinSymbol() { return GetSymbol(); }


    IlvGrapherPin*	set(IlvGraphic* node) 
			{
			    return IL_CAST(IlvGrapherPin*,
					   node
					   ? node->setNamedProperty(this)
					   : 0);
			}
    static
    IlvGrapherPin*	Get(const IlvGraphic* node);

    static
    IlvGrapherPin*	Remove(IlvGraphic* node);


    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvGrapherPin);

protected:
    class IlvGrapherPinLink
    {
    public:
	IlvGrapherPinLink(const IlvGraphic* link, IlUInt idx,
			  IlvGrapherPinLink* next)
	    : _link(link),
	      _idx(idx),
	      _next(next)
	{}

	inline
	const IlvGraphic*	getLink() const { return _link; }
	inline void		setLink(const IlvGraphic* link)
				{
				    _link = link;
				}
	inline IlUInt		getIdx()  const { return _idx;  }
	inline void		setIdx(IlUInt idx) { _idx = idx; }
	inline
	IlvGrapherPinLink*	getNext() const { return _next; }
	inline void		setNext(IlvGrapherPinLink* n) { _next = n; }

    private:
	const IlvGraphic*	_link;
	IlUInt			_idx;
	IlvGrapherPinLink*	_next;
    };

    IlvGrapherPinLink*	_fromLinks;
    IlvGrapherPinLink*	_toLinks;
};


class ILVVWSEXPORTED IlvShapePosition;

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGenericPin : public IlvGrapherPin 
{
public:
    IlvGenericPin() : _positions() {}
    virtual ~IlvGenericPin();

    IlUInt		addPin(const IlvGraphic* node,
			       const IlvPoint& p,
			       const IlvTransformer* t);

    IlBoolean		movePin(IlUInt pinIndex,
				const IlvGraphic* node,
				const IlvPoint& p,
				const IlvTransformer* t);

    virtual IlUInt	getCardinal(const IlvGraphic*, 
				    const IlvTransformer*) const;

    virtual IlBoolean	getClosest(const IlvGraphic*,
				   const IlvPoint&, 
				   const IlvTransformer* t,
				   IlvPoint&, IlUInt&) const;

    virtual IlBoolean	getLocation(IlUInt, 
				    const IlvGraphic*,
				    const IlvTransformer* t,
				    IlvPoint&) const;

    void		removePin(IlUInt pinIndex);

    const IlvShapePosition* getShapePosition(IlUInt idx) const;

    inline
    const IlvList&	getShapePositions() const { return _positions;}

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvGenericPin);

protected:
    IlList		_positions;
};

ILVGRAPHMODULEINIT(graphpin);
#endif /* !__Ilv_Grapher_Pin_H */
