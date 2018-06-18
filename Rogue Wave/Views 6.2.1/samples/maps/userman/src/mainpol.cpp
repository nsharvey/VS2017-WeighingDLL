// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/mainpol.cpp
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

#include <ilviews/base/view.h>
#include <ilviews/manager/manager.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/projection/geogproj.h>
#include <ilviews/maps/projection/ortho.h>
#include <ilviews/maps/projection/mercator.h>
#include <ilviews/maps/attribute/stringattr.h>
#include <ilog/pathname.h>

#include <simplePolylineReader.h>

#if defined(ILVSTD)
#include <cstdio>
ILVSTDUSE
#else  /* !ILVSTD */
#include <stdio.h>
#endif /* ILVSTD */

// --------------------------------------------------------------------------
void
processAttributes(const IlvMapFeature* feature)
{
    const IlvFeatureAttributeProperty* attributes = feature->getAttributes();

    if(!attributes)
	return;
    
    const IlvFeatureAttributeInfo* info = attributes->getInfo();

    if(info) {
        IlUInt count;
        char buf[512];
        
        count = info->getAttributesCount();
        for(IlUInt i = 0; i < count; i++) {
            buf[0] = 0;
            const char* name = info->getAttributeName(i);

            const IlvMapClassInfo* clsinfo =
                info->getAttributeClass(i);
            const IlvFeatureAttribute* fa = attributes->getAttribute(i);
	    
            if(clsinfo->isSubtypeOf(IlvStringAttribute::ClassInfo())) {
                const char *str = ((IlvStringAttribute*)fa)->getValue();
                if(str)
                    sprintf(buf, "%s %s", name ? name : "",
                            str ? str : "");
            } else {
		IlvWarning("Unexpected attribute class");
		return;
            }
	    
            if(buf[0])
                IlvPrint(buf);
        }
    }
}
 
// --------------------------------------------------------------------------
static void
Exit(IlvView* view, IlvAny a)
{
    IlvDisplay* display = view->getDisplay();
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay(argv[0], "", argc, argv);
    if(display -> isBad()) {
	IlvPrint("Can't open display\nExiting ...");
	delete display;
	IlvExit(1);
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/userman/data");
    display->prependToPath(localPath);
    
    int width = 800;
    int height = 600;
    
    const char* filename = argc > 1 ? argv[1] : "dcwbrowse.pol";
    
    SimplePolylineReader reader(display, filename);
    if(reader.getInitStatus() != IlvMaps::NoError()) {
	IlvPrint("Bad reader\nExiting ...");
	delete display;
	IlvExit(1);
    }
    const IlvMapFeature* feature;
    const IlvFeatureRenderer* renderer;

    IlvGeographicProjection target;    
    IlvMapAdapter adapter(&target);
    IlvMapInfo mapInfo(&target, &adapter, IlFalse);
    
    IlvGraphic* graphic;
    IlvManager manager(display);
    IlvView* view = new IlvView(display, "World Map", "World Map", IlvRect(0, 0, width, height));    
    manager.addView(view);
    manager.setKeepingAspectRatio(view, IlTrue);
    view->setDestroyCallback(Exit, 0);
    
    IlvMapsError status = IlvMaps::NoError();
    int count = 0;
    renderer = reader.getDefaultFeatureRenderer(display);
    
    while(1) {
	feature = reader.getNextFeature(status);
	
	if(status != IlvMaps::NoError()) {
	    IlvWarning(IlvMaps::GetErrorMessage(status, display));
	    break;
	}

	if(feature == 0)
	    break;

	graphic = renderer->makeGraphic(*feature, mapInfo, status);
	processAttributes(feature);
	
        if(!graphic) {
	    if(status != IlvMaps::NoError()) 
		IlvWarning(IlvMaps::GetErrorMessage(status, display));
	} else 
	    manager.addObject(graphic, IlFalse);
	
	count ++;
    }
    IlvPrint("%d feature(s) read", count);

    manager.fitTransformerToContents(view, IlTrue, IlTrue);
    
    IlvMainLoop();
    IlvExit(0);
    return 0;
}
