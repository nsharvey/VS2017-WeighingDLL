// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/manager.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the Manager class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_MANAGER_H
#define VPF_GUI_MANAGER_H

#include <ilviews/manager/manager.h>
#include <vpf/basictypes.h>
#include <vpf/extent.h>

class VpfArea;
class VpfRing;
class VpfSegment;
class VpfText;
class VpfPoint;
class Palette;
class Layers;
class IlvProjection;
class IlvMapInfo;

// --------------------------------------------------------------------------
class Manager
: public IlvManager {
public:
    Manager(IlvDisplay*, IlvProjection*);
    ~Manager();

    const IlvMapInfo*		getMapInfo();

    void add(VpfSegment*, Palette*, VpfUInt);
    void add(VpfRing*, Palette*, VpfUInt);
    void add(VpfArea*, Palette*, VpfUInt);
    void add(VpfText*, Palette*, VpfUInt);
    void add(VpfPoint*, Palette*, VpfUInt);
    void forward(const IlvCoordinate& degrees, IlvPoint& mgrPoint);

    void startUpdate();
    void endUpdate();

    void setExtent(const VpfExtent& extent) { _extent = extent; }
    const VpfExtent& getExtent() const { return _extent; }

    IlvView* installView(void (*)(IlvView*, IlvAny) = 0, IlvAny = 0);

    void	saveVpf() const;
    void	loadVpf(Layers* layers);
    void	moveToManager(IlvGraphic* g);
protected:
    static void SaveAccelerator(IlvManager*, IlvView*, IlvEvent&, IlvAny arg);
    static void DestroyCB(IlvView*, IlvAny);

    friend class ManagerViewHook;

    IlvMapInfo*		_mapInfo;
    VpfExtent		_extent;
};

#endif /* VPF_GUI_MANAGER_H */
