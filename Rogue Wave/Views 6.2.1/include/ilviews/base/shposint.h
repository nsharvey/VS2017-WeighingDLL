// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/shposint.h
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
// Declaration of the IlvShapePositionEditor
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Shposint_H
#define __Ilv_Base_Shposint_H

#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif

#if !defined(__Ilv_Itf_Shape_H)
#include <ilviews/intrface/shape.h>
#endif


class ILVVWSEXPORTED IlvShapePositionEditor 
    : public IlvInteractor
{
public:
    typedef void (*Action)(IlvGraphic*,
			   const IlvShapePosition& shpPos);

    IlvShapePositionEditor(Action action = 0);

    virtual IlvGraphic* getHandledObject(IlvGraphic* g) const;
    virtual IlBoolean handleEvent(IlvGraphic* g, 
				  IlvEvent& event,
				  const IlvTransformer* t = 0);

    virtual void endOperation();

    DeclareInteractorTypeInfoRO(IlvShapePositionEditor);    

protected:
    Action		_action;
    IlvShapePosition	_oldPos;
    IlvShapePosition	_newPos;
    IlvPoint		_lastPoint;

    virtual void startGhost(IlvPort* dst,
			    IlvGraphic* g,
			    const IlvPoint& p,
			    const IlvTransformer* t);

    virtual void drawGhost(IlvPort* dst,
			   IlvGraphic* g,
			   const IlvPoint& p,
			   const IlvTransformer* t);

    virtual void endGhost(IlvPort* dst,
			  IlvGraphic* g,
			  const IlvPoint& p,
			  const IlvTransformer* t);

    virtual void doIt(IlvGraphic* g,
		      const IlvShapePosition& shpPos,
		      const IlvPoint& p,
		      const IlvTransformer* t);

    virtual void anchorMoved(IlvShapePosition& shpPos,
			     IlvPoint& p);

};

ILVVWSMODULEINIT(anchorint);
#endif /* !__Ilv_Base_Anchorint_H */
