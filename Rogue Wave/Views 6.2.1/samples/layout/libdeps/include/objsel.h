// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/libdeps/include/objsel.h
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
// Declaration of new selection objects:
// GraphLayoutNodeSelection and GraphLayoutLinkSelection
// --------------------------------------------------------------------------

#include <ilviews/grapher/nodesel.h>
#include <ilviews/grapher/linksel.h>

// --------------------------------------------------------------------------
class GraphLayoutNodeSelection
    : public IlvGraphNodeSelection
{
public:
    GraphLayoutNodeSelection(IlvDisplay* display,
			     IlvGraphic* object);
    void draw(IlvPort*,
	      const IlvTransformer*,
	      const IlvRegion*) const;
    void boundingBox(IlvRect& r,
		     const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
class GraphLayoutLinkSelection
    : public IlvGraphLinkSelection
{
public:
    GraphLayoutLinkSelection(IlvDisplay* display,
			     IlvGraphic* object);
    ~GraphLayoutLinkSelection();
    void draw(IlvPort*,
	      const IlvTransformer*,
	      const IlvRegion*) const;
    virtual void boundingBox(IlvRect& r,
			     const IlvTransformer* t = 0) const;
    void computeRegion(IlvRegion& region,
		       const IlvTransformer* t) const;
    IlUInt getHandlesCount(const IlvTransformer* t = 0) const;
private:
    IlvPalette* _layoutPalette;
};

// --------------------------------------------------------------------------
