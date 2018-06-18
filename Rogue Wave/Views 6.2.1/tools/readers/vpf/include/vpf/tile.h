// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/tile.h
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
// Declaration of the VpfTile class
// --------------------------------------------------------------------------
#ifndef VPF_TILE_H
#define VPF_TILE_H

#include <vpf/extent.h>

// --------------------------------------------------------------------------
class VpfTile
{
 public:
    VpfTile(char* path, const VpfExtent& extent, int selected = 0);
    ~VpfTile();
    // ____________________________________________________________
    const char* getPath() const { return _path; }
    const VpfExtent& getExtent() const { return _extent; }
    int isSelected() const { return _selected; }
    void setSelected(int selected) { _selected = selected; }
protected:
    char*	_path;
    VpfExtent	_extent;
    int		_selected;
};

#endif /* VPF_TILE_H */
