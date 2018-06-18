// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/selector.h
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
// Declaration of the IlvSelector class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Selector_H
#define __Ilv_Graphics_Selector_H

#if !defined(__Ilv_Graphics_Set_H)
#include <ilviews/graphics/set.h>
#endif

#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSelector : public IlvGraphicSet
{
public:
    IlvSelector() : IlvGraphicSet(), _whichSelected(-1) {}

    virtual void	removeObject(IlvGraphic* obj);
    virtual void	insertObject(IlvGraphic* obj);
    void		setSelected(IlvGraphic* object);
    void		setSelected(IlShort index);
    IlShort		whichSelected() const { return _whichSelected; }
    IlvGraphic*		whichGraphicSelected() const;
    IlBoolean		isSelected(IlvGraphic* object) const;
    IlBoolean		handleAccelerator(IlvEvent&) const;
    IlvGraphic*		graphicForAccelerator(IlvEvent&) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette* ,
				  const IlvTransformer* t    = 0,
				  const IlvRegion*      clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;

    DeclareTypeInfo();
    DeclareIOConstructors(IlvSelector);
    DeclareGraphicAccessors();

    static IlSymbol*	_SelectionValue;

protected:
    IlShort		_whichSelected;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSelectorInteractor : public IlvInteractor
 {
public:
    IlvSelectorInteractor();
    virtual IlBoolean	handleEvent(IlvGraphic*			obj,
				    IlvEvent&			ev,
				    const IlvTransformer*	t = 0);
    virtual IlBoolean	accept(const IlvGraphic* obj) const;

protected:
    virtual void	doIt(IlvSelector* selector);

    DeclareInteractorTypeInfoRO(IlvSelectorInteractor);
};

ILVVWSMODULEINIT(selector);
#endif /* !__Ilv_Graphics_Selector_H */
