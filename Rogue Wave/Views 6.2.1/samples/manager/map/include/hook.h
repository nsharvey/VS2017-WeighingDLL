// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/map/include/hook.h
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
// Declaration of the Map Hook
// --------------------------------------------------------------------------

#ifndef __ILV_TrackHookH
#define __ILV_TrackHookH

#include <ilviews/manager/manager.h>

// -------------------------------------------------------------------------
class IlvMapHook
    : public IlvManagerViewHook
{
public:
    IlvMapHook(IlvManager* mgr,
	       IlvView*    view,
	       IlUShort    start,
	       IlUShort    endl = 0);
    ~IlvMapHook();

    virtual void	transformerChanged(const IlvTransformer*,
					   const IlvTransformer*);
    virtual void	viewResized();
    virtual void	beforeDraw(IlvPort*              dst,
				   const IlvTransformer* t      = 0,
				   const IlvRegion*      region = 0,
				   const IlvRegion*      clip   = 0);
    void		setBackground(IlvColor*);
    void		adjust();

protected:
    IlvBitmap*		_bitmap;
    IlvPalette*		_palette;
    IlUShort		_startLayer;
    IlUShort		_endLayer;
};

#endif /* !__ILV_TrackHookH */
