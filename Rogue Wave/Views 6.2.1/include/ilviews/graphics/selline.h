// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/selline.h
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
// Declaration of the IlvLineHandle class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Selline_H
#define __Ilv_Graphics_Selline_H

#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif

#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif

class ILVVWSEXPORTED IlvLine;
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvLineHandle : public IlvDrawSelection
{
public:
    IL_MLK_DECL();
    IlvLineHandle(IlvDisplay* display,
		  IlvGraphic* object,
		  IlvDim      size    = 0,
		  IlvPalette* pal = 0)
    : IlvDrawSelection(display, object, size, pal) {}
    // ____________________________________________________________

    virtual IlUInt	getHandlesCount(const IlvTransformer* t = 0) const;

    virtual IlBoolean	getHandleLocation(IlUInt                idx,
					  IlvPoint&             p,
					  const IlvTransformer* t) const;
    IlvLine*		getLine() const;

    virtual IlvInteractor*	getSelectionInteractor() const;

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvLineHandle);
};

class ILVVWSEXPORTED IlvLineSelectionInteractor : public IlvInteractor
{
public:
    IlvLineSelectionInteractor() {}

    virtual IlBoolean	handleEvent(IlvGraphic*           g, 
				    IlvEvent&             event,
				    const IlvTransformer* t = 0);

    virtual IlBoolean	accept(const IlvGraphic* obj) const;
    virtual void	endOperation();
    DeclareInteractorTypeInfoRO(IlvLineSelectionInteractor);

protected:
    IlUInt		_pointIndex;
    IlvLine*		_ghost;

    void		drawGhost(IlvPort* dst, const IlvTransformer* t);
};

ILVVWSMODULEINIT(selline);
#endif /* !__Ilv_Graphics_Selline_H */
