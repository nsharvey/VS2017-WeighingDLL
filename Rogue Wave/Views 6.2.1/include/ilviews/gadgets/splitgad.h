// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/splitgad.h
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
// Declaration of the IlvSplitterGadget class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Splitgad_H
#define __Ilv_Gadgets_Splitgad_H

#if !defined(__Ilv_Base_Gadget_H)
#include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

class IlvSplitterGadget;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSplitterGadgetLFHandler : public IlvObjectLFHandler
{
public:
    IlvSplitterGadgetLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawIntersection(const IlvSplitterGadget*,
					 IlvPort*,
					 const IlvRect&,
					 const IlvRegion*) const = 0;
    virtual void	draw(const IlvSplitterGadget* splitgad,
			     IlvPort* dst,
			     const IlvTransformer* t,
			     const IlvRegion* clip) const = 0;
    virtual IlBoolean	handleEvent(IlvSplitterGadget* splitgad,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultSplitterGadgetLFHandler
    : public IlvSplitterGadgetLFHandler
{
public:
    IlvDefaultSplitterGadgetLFHandler(IlvLookFeelHandler* lf)
	: IlvSplitterGadgetLFHandler(lf) {}

    virtual void	drawIntersection(const IlvSplitterGadget*,
					 IlvPort*,
					 const IlvRect&,
					 const IlvRegion*) const;
    virtual void	draw(const IlvSplitterGadget*,
			     IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const;
    virtual IlBoolean	handleEvent(IlvSplitterGadget*, IlvEvent&) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSplitterGadget : public IlvGadget
{
    friend class IlvDefaultSplitterGadgetLFHandler;
public:

    IlvSplitterGadget(IlvDisplay* display,
		      const IlvRect& rect,
		      IlUShort thickness = IlvDefaultGadgetThickness,
		      IlvPalette* palette = 0);

    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual IlBoolean	handleButtonDown(IlvEvent& event);
    virtual IlBoolean	handleButtonDragged(IlvEvent&);
    virtual IlBoolean	handleButtonUp(IlvEvent&);

    IlvDirection	getDirection() const;

    IlvDirection	getGuideDirection() const;

    virtual void	moveGuide(IlvPos position);

    inline void		addIntersect(IlAny intersect)
			{
			    _intersects.append(intersect);
			}

    IlvSplitterGadget*	findIntSepAt(IlvPoint& location);
    IlvSplitterGadget*	findIntSepAt(IlvEvent& event);

    virtual void	draw(IlvPort*dst ,
			     const IlvTransformer* t,
			     const IlvRegion* clip) const;
    virtual void	drawIntersection(IlvPort*dst ,
					 const IlvTransformer* t,
					 const IlvRegion* clip) const;

    inline void		setCollapsed (IlBoolean collapsed)
			{
			    _collapsed = collapsed;
			}

    inline IlBoolean	isCollapsed() const { return _collapsed; }

    inline void		setResetValues(IlBoolean reset)
			{
			    _resetValues = reset;
			}
    inline IlBoolean	getResetValues() const { return _resetValues; }

    inline IlvPos	getMousePos() const { return _lastPos; }

    inline void		setMousePos(IlvPos pos) {_lastPos = pos;}

    IlvDefineCallback(Expand);
    IlvDefineCallback(Collapse);

    virtual IlUInt	getCallbackTypes(const char*      const**,
					 const IlSymbol* const**) const;

    inline static
    IlSymbol*		ExpandCallbackType() { return _expandSymbol; }
    inline static
    IlSymbol*		ExpandSymbol() { return ExpandCallbackType(); }

    inline static
    IlSymbol*		CollapseCallbackType() { return _collapseSymbol; }
    inline static
    IlSymbol*		CollapseSymbol() { return CollapseCallbackType(); }

    static IlSymbol*	_expandSymbol;
    static IlSymbol*	_collapseSymbol;
    static IlBoolean	_DragGhost;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvSplitterGadget);

protected:
    IlBoolean		iHandleEvent(IlvEvent&);
    virtual void	drawGhost();

    IlList		_intersects;
    IlvSplitterGadget*	_intSep;
    IlBoolean		_collapsed;
    IlvPos		_lastPos;
    IlvPos		_offset;
    IlBoolean		_resetValues;
};

class IlvGadgetContainer;

ILVADVGDTEXPORTEDFUNCTION(IlvSplitterGadget*)
IlvMakeSplitterGadget(IlvGadgetContainer* container,
		      IlvDirection direction,
		      IlUInt index,
		      IlUInt from = 0,
		      IlUInt to   = (IlUInt)-1,
		      IlvDim size = 6);

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(splitgad);

#endif /* !__Ilv_Gadgets_Splitgad_H */
