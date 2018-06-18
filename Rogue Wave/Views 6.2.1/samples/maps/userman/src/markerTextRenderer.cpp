// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/markerTextRenderer.cpp
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

#include <ilviews/graphics/set.h>
#include <ilviews/graphics/label.h>
#include <ilviews/maps/attribute/all.h>

#include "markerTextRenderer.h"

#if defined(IL_STD)
#include <cstring>
IL_STDUSE
#else  /* !IL_STD */
#include <string.h>
#endif /* IL_STD */


// --------------------------------------------------------------------------
MarkerTextRenderer::MarkerTextRenderer(IlvDisplay* display,
				       char* attributeName)
    : IlvDefaultPointRenderer(display),
     _attributeName(strcpy(new char[strlen(attributeName)+1],
			   attributeName))
{
    
}

// --------------------------------------------------------------------------
static const char* 
ToString(const IlvFeatureAttribute* attribute)
{
    static char buf[1024];
    
    const IlvMapClassInfo* clsinfo =
	attribute->getClassInfo();

    if(clsinfo->isSubtypeOf(IlvStringAttribute::ClassInfo())) {
	const char *str = ((IlvStringAttribute*)attribute)->getValue();
	return str;
    } else if(clsinfo->isSubtypeOf(IlvIntegerAttribute::ClassInfo())){
	int in = ((IlvIntegerAttribute*)attribute)->getValue();
	sprintf(buf, "%d", in);
	return buf;
    } else if(clsinfo->isSubtypeOf(IlvDoubleAttribute::ClassInfo())){
	double dbl = ((IlvDoubleAttribute*)attribute)->getValue();
	sprintf(buf, "%g", dbl);
	return buf;
    } else if(clsinfo->isSubtypeOf(IlvBooleanAttribute::ClassInfo())){
	IlBoolean bo = ((IlvBooleanAttribute*)attribute)->getValue();
	sprintf(buf, "%s", bo ? "true" : "false");
	return buf;
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvGraphic*
MarkerTextRenderer::makeGraphic( const IlvMapFeature& feature,
                                 const IlvMapInfo& targetMapInfo,
                                 IlvMapsError& status) const
{
    IlvMarker *marker =
        (IlvMarker *)IlvDefaultPointRenderer::makeGraphic(feature,
                                                          targetMapInfo,
                                                          status);
    if(!marker)
        return 0;
    
    IlvLabel* label = 0;

    const IlvFeatureAttributeProperty* attributeList = 
        feature.getAttributes();

    const IlvFeatureAttribute* attribute = 
        attributeList->getAttribute(_attributeName);
   
    if(attribute)
        label = new  IlvLabel (getDisplay(),
                               marker->getPoint(),
                               ToString(attribute));
    
    if (!label)
        return marker; 

    label->setForeground(marker->getForeground());
    IlvGraphicSet* set = new IlvGraphicSet();
    set->addObject(marker);
    set->addObject(label);
    return set;
}

