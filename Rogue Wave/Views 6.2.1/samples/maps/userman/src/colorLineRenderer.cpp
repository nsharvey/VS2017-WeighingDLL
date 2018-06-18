// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/colorLineRenderer.cpp
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
#include <ilviews/maps/geometry/geolinestr.h>
#include <ilviews/maps/graphics/mapgenpath.h>
#include <ilviews/maps/attribute/intattr.h>
#include <ilviews/maps/attribute/doubleattr.h>
#include <ilviews/maps/attrinfo.h>

#include "colorLineRenderer.h"

#if defined(IL_STD)
#include <iostream>
#include <cstring>
IL_STDUSE
#else  /* !IL_STD */
#include <iostream.h>
#include <string.h>
#endif /* IL_STD */


// --------------------------------------------------------------------------
ColorLineRenderer::ColorLineRenderer(IlvDisplay* display,
				     char* attributeName,
				     IlvMapColorModel* cmodel)
    :IlvFeatureRenderer(display),
     _attributeName(attributeName ?
		    strcpy(new char[strlen(attributeName)+1],
			   attributeName) : 0),
     _colorModel(cmodel)
{
}

// --------------------------------------------------------------------------
ColorLineRenderer::~ColorLineRenderer() {
  if (_attributeName) {
    delete [] _attributeName;
    _attributeName = 0;
  }
}

// --------------------------------------------------------------------------
IlvGraphic*
ColorLineRenderer::makeGraphic(const IlvMapFeature& feature,
                               const IlvMapInfo& targetMapInfo,
                               IlvMapsError& status) const {
    
    const IlvMapGeometry* geometry = feature.getGeometry();
    if (!geometry) {
        status = IlvMaps::IllegalArgument();
        return 0;
    }
    if (geometry->getClassInfo() != IlvMapLineString::ClassInfo()) {
        status = IlvMaps::ClassError();
        return 0;
    }

    const IlvMapLineString* lineStr = (const IlvMapLineString*) geometry;

    int segCount = lineStr->getSegmentCount();
    if (segCount == 0)
        return 0;

    IlvMapGeneralPath* genPath = new IlvMapGeneralPath(getDisplay());

    const IlvMapSegment *segment;
    IlvCoordinate c; 
    IlvPoint p;

    segment = lineStr->getSegment(0);
    c = segment -> getStartPoint();
    status = targetMapInfo.toViews(c, feature.getProjection(), p);
    genPath->moveTo(p);

    for (int i = 0; i < segCount ; i++) {
        c = segment -> getEndPoint();
        status = targetMapInfo.toViews(c, feature.getProjection(), p);
        genPath->lineTo(p);
    }



    IlInt colorIndex = 0;

    const IlvFeatureAttributeProperty* attributeList = 
        feature.getAttributes();
                
    const IlvFeatureAttribute* fa = 
        attributeList->getAttribute(_attributeName);
            
    const IlvMapClassInfo* clsinfo =
        fa->getClassInfo();
            
    if(clsinfo->isSubtypeOf(IlvIntegerAttribute::ClassInfo()))
        colorIndex = ((IlvIntegerAttribute*)fa)->getValue();
    else if(clsinfo->isSubtypeOf(IlvDoubleAttribute::ClassInfo()))
        colorIndex = (IlInt)((IlvDoubleAttribute*)fa)->getValue();
           
    IlvColor* color = getDisplay()->
        getColor((IlUShort)_colorModel->getRed(colorIndex),
                 (IlUShort)_colorModel->getGreen(colorIndex),
                 (IlUShort)_colorModel->getBlue(colorIndex));

    genPath->setForeground(color);

    return genPath;
}

// --------------------------------------------------------------------------
IlBoolean
ColorLineRenderer::isPersistent()
{
    return IlTrue;
}

// --------------------------------------------------------------------------
void
ColorLineRenderer::write(IlvOutputFile& output) const
{
    IlvWriteString(output, _attributeName);

    if(_colorModel->isPersistent()) {
        output.getStream() << 1 << IlvSpc();
        _colorModel->write(output);
    } else {
        output.getStream() << 1 << IlvSpc();
        IlvWarning("colormodel not saved");
    }
}

// --------------------------------------------------------------------------
ColorLineRenderer::ColorLineRenderer(IlvInputFile& stream)
    :IlvFeatureRenderer(stream.getDisplay(), IlTrue)
{
    char* s = IlvReadString(stream);
    if(s)
        _attributeName = strcpy(new char[strlen(s)+1], s);

    IlInt hasColorModel;
    stream.getStream() >> hasColorModel;
    if(hasColorModel) {
        _colorModel = (IlvMapColorModel*)
            IlvMapClassInfo::ReadObject(IlvMapColorModel::ClassInfo(),
                                        stream,
                                        0);
    } else {
        _colorModel = IlvIntervalColorModel::MakeElevationColorModel();
    }
}

// --------------------------------------------------------------------------
ILVMAPS_DEFRENDERER(ColorLineRenderer, IlvFeatureRenderer);

