// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/include/colorLineRenderer.h
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


#ifndef _ColorLineRenderer_
#define _ColorLineRenderer_

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/rendering/cmodel.h>

class ColorLineRenderer
   : IlvFeatureRenderer
{
public:
    ColorLineRenderer(IlvDisplay *display,
		      char* attributeName,
		      IlvMapColorModel* _colorModel);
    ColorLineRenderer(const ColorLineRenderer* source);
    virtual ~ColorLineRenderer();
    virtual IlvGraphic* makeGraphic(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const;
    virtual IlBoolean isPersistent();
    
  ILVMAPS_DECLMANDATORYRENDERERMEMBERS(ColorLineRenderer); 
 
private:
    char* _attributeName;
    IlvMapColorModel* _colorModel;
};

#endif
