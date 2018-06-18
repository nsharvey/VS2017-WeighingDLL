// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/polyptsel.h
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
// - IlvPolyPointsSelection
// - IlvPolyPointsEditionInteractor 
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Polyptsel_H
#define __Ilv_Graphics_Polyptsel_H

#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
class ILVVWSEXPORTED IlvPolyPoints;
class ILVVWSEXPORTED IlvSpline;
class ILVVWSEXPORTED IlvChangeValueCommand;
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPolyPointsSelection : public IlvDrawSelection
{
public:
    IL_MLK_DECL();
    IlvPolyPointsSelection(IlvDisplay* display,
			   IlvGraphic* object,
			   IlvDim      size    = IlvDefaultSelectionSize,
			   IlvPalette* palette = 0);
    // ____________________________________________________________
    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t,
			     const IlvRegion*		clip = 0) const;
    void		computeRegion(IlvRegion&	    r,
				      const IlvTransformer* t = 0) const;
    void 		boundingBox(IlvRect&		  bbox,
				    const IlvTransformer* t) const;
    void 		drawGhost(IlvPolyPoints*	object,
				  IlvPort*		dst,
				  const IlvTransformer* t);

    IlUInt		getHandlesCount(const IlvTransformer* t = 0) const;
    IlBoolean		getHandleLocation(IlUInt		idx, 
					  IlvPoint&		p,
					  const IlvTransformer* t) const;
    IlvInteractor*	getSelectionInteractor() const;
    IlvPolyPoints*	getPolyPoints() const;

    virtual void 	startInteraction() const;
    virtual IlDouble 	distanceToCurve(const IlvPoint&		p, 
    					const IlvTransformer*	t, 
    					IlInt*			segment = 0, 
    					IlDouble*		param = 0);

    virtual IlBoolean 	isClosed() const;

    inline IlUInt 	selectedIndex() const { return _selectedNdx; }
    virtual void 	setSelectedIndex(IlUInt ndx);

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvPolyPointsSelection);

    virtual void 	(*removePointCallback())(IlvGraphic* g, IlAny arg);
    virtual void 	(*movePointCallback())(IlvGraphic* g, IlAny arg);
    virtual void 	(*insertPointCallback())(IlvGraphic* g, IlAny arg);

    struct EditPointCallbackStruct
    {
	IlvPolyPoints*	object;
	IlvEvent*	event;
	IlUInt		point;
	IlvPoint	position;
	IlDouble	param;

	EditPointCallbackStruct(IlvPolyPoints*	o,
				IlvEvent*	e,
				IlUInt		p,
				const IlvPoint& pos,
				IlDouble	pa = 0) 
	    : object(o), event(e), point(p), position(pos), param(pa) {}
    };

protected:
    IlUInt		_selectedNdx;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPolyPointsEditionInteractor : public IlvInteractor
{
public:
    IlvPolyPointsEditionInteractor();
    virtual ~IlvPolyPointsEditionInteractor();
    // ____________________________________________________________
    virtual IlBoolean	handleEvent(IlvGraphic*			g,
				    IlvEvent&			event,
				    const IlvTransformer*	t = 0);

    virtual IlBoolean	handleButtonDown(IlvPolyPointsSelection*	sel,
					 IlvEvent&			event,
					 const IlvTransformer*		t = 0);
    virtual IlBoolean	handleButtonUp(IlvPolyPointsSelection*	sel,
				       IlvEvent&		event,
				       const IlvTransformer*	t = 0);
    virtual IlBoolean	handleButtonDragged(IlvPolyPointsSelection*	sel,
					    IlvEvent&			event,
					    const IlvTransformer*	t = 0);

    virtual IlBoolean	accept(const IlvGraphic* obj) const;

    DeclareInteractorTypeInfoRO(IlvPolyPointsEditionInteractor);

protected:
    virtual void 	removePoint(IlvPolyPointsSelection*	sel,
				    IlvEvent&			ev,
				    const IlvTransformer*	t);
    virtual void 	insertPoint(IlvPolyPointsSelection*	sel, 
				    IlvEvent&			ev,
				    const IlvTransformer*	t,
				    IlUInt			seg,
				    IlDouble			param);

    IlvPolyPoints*		_ghostPoly;
    IlvChangeValueCommand*	_command;

};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSplineSelection : public IlvPolyPointsSelection
{
    friend class IlvSplineEditionInteractor;
public:
    IL_MLK_DECL();
    IlvSplineSelection(IlvDisplay*	display,
			   IlvGraphic*	object,
			   IlvDim	size    = IlvDefaultSelectionSize,
			   IlvPalette*	palette = 0);

    // ____________________________________________________________
    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t,
			     const IlvRegion*		clip = 0) const;
    IlBoolean		getHandleLocation(IlUInt		idx, 
					  IlvPoint&		p,
					  const IlvTransformer* t) const;
    IlUInt 		whichHandle(const IlvPoint&		p,
				    const IlvTransformer*	t = 0) const;
    void 		drawGhost(IlvPolyPoints*	obj,
				  IlvPort*		dst,
				  const IlvTransformer* t);
    IlvInteractor*	getSelectionInteractor() const;

    IlDouble		distanceToCurve(const IlvPoint&		p, 
    					const IlvTransformer*	t, 
    					IlInt*			segment = 0,
    					IlDouble*		param = 0);

    void 		(*insertPointCallback())(IlvGraphic* g, IlAny arg);
    void 		(*movePointCallback())(IlvGraphic* g, IlAny arg);
    void 		(*removePointCallback())(IlvGraphic* g, IlAny arg);
    IlvSpline*		getSpline() const;
    IlBoolean 		isClosed() const;

    static int 		handleType(IlvPolyPoints*, IlUInt ndx);
    static int 		handleType(IlUInt cnt, int ndx, IlBoolean closed);    

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvSplineSelection);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSplineEditionInteractor
    : public IlvPolyPointsEditionInteractor
{
public:
    IlvSplineEditionInteractor();
    ~IlvSplineEditionInteractor();
    // ____________________________________________________________
    IlBoolean		accept(const IlvGraphic* obj) const;
    DeclareInteractorTypeInfoRO(IlvSplineEditionInteractor);
};

ILVVWSMODULEINIT(polyptsel);
#endif /* !__Ilv_Graphics_Polyptsel_H */


