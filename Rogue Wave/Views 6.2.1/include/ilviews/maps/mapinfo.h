// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/mapinfo.h
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
// This file defines the persistent map information.
// Instances of this class store any information relative to the
// coordinate system
// --------------------------------------------------------------------------

#ifndef __Ilv_Maps_Info_H
#define __Ilv_Maps_Info_H

#include <ilviews/maps/adapter.h>

class ILVDSPEXPORTED IlvEvent;
class ILVDSPEXPORTED IlvPoint;
class ILVDSPEXPORTED IlvManager;
class ILVDSPEXPORTED IlvPoint;
class ILVDSPEXPORTED IlvView;

class ILVMAPSEXPORTED IlvMapInfo;
class ILVMAPSEXPORTED IlvProjection;
class ILVMAPSEXPORTED IlvUnitConverter;

class ILVMAPSEXPORTED IlvMapInfoListener
{
public:
    virtual ~IlvMapInfoListener();
    virtual void	mapInfoChanged(IlvManager* manager,
				       const IlvMapInfo* oldInfo,
				       const IlvMapInfo* newInfo) = 0;

    virtual void	managerDeleted(IlvManager* manager) = 0;
};

class ILVMAPSEXPORTED IlvMapInfo
{
public:
    IlvMapInfo(const IlvProjection* projection,
	       const IlvMapAdapter* adapter = 0,
	       IlBoolean copy = IlTrue);
    ~IlvMapInfo();

    const IlvProjection* getProjection() const { return _projection; }

    const IlvMapAdapter* getAdapter() const { return _adapter; }

    const IlvUnitConverter* getUnitConverter() const;

    IlDouble		getScale(IlvView* view) const;
    void		setScale(IlvView* view,
				 IlDouble scale,
				 IlBoolean redraw = IlTrue) const;

    IlvMapsError	forward(const IlvCoordinate& coord,
				IlvPoint& point) const;

    IlvMapsError	inverse(const IlvPoint& point,
				IlvCoordinate& coord) const;

    IlvMapsError	inverse(const IlvEvent& event,
				const IlvView* view,
				IlvCoordinate& coord) const;

    IlvMapsError	toViews(const IlvCoordinate& data,
				const IlvProjection* sourceProjection,
				IlvPoint& result) const;

    IlvMapInfo*		attach(IlvManager* manager);

    void		detach();

    IlvManager*		getManager() const { return _manager; }

public:
    static IlvMapInfo*	Get(IlvManager* manager);

    static void		AddMapInfoListener(IlvManager* manager,
					   IlvMapInfoListener* listener);

    static void		RemoveMapInfoListener(IlvManager* manager,
					      IlvMapInfoListener* listener);

    static void		SetScreenSize(IlvDisplay* display,
				      IlUInt heightmm,
				      IlUInt widthmm);

    // not documented
    static IlDouble	GetScreenScale(IlvDisplay*);

private:
    static void		NotifyListeners(IlvManager*,
					IlvMapInfo*,
					IlvMapInfo*);

private:
    IlvProjection*	_projection;
    IlvMapAdapter*	_adapter;
    IlvManager*		_manager;
};

ILVMAPSMODULETERM(mapinfo);

#endif /* __Ilv_Maps_Info_H */
