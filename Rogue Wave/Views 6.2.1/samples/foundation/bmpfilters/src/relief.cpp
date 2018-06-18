// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bmpfilters/src/relief.cpp
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
// Using various bitmap filters to create a relief effect
// --------------------------------------------------------------------------

#include <relief.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Panel class for sample Relief
// --------------------------------------------------------------------------
Relief::Relief(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename) 
{
    initRelief();
}

// --------------------------------------------------------------------------
Relief::~Relief()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Relief::initRelief()
{
    IlvRect dims(0, 0, 500, 500);
    IlvDisplay* display = getDisplay();

    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/bmpfilters/data");
    display->prependToPath(localPath);

    IlvFilterFlow* flow = new IlvFilterFlow();

    IlvBitmapData* srcdata = display->readBitmapData("Views.png");
    IlUInt width = srcdata->getWidth();
    IlUInt height = srcdata->getHeight();
     
    IlvBitmapFilter* imager = IlvBitmapFilter::Create("IlvImageFilter");
    {	
	localPath.setFileName("background.png");
	imager->changeValue(IlvValue("in", localPath));
	imager->changeValue(IlvValue("result", "background"));
    }
    flow->addFilter(imager);

    IlvBitmapFilter* tiler = IlvBitmapFilter::Create("IlvTileFilter");
    {
	tiler->changeValue(IlvValue("in", "background"));
	tiler->changeValue(IlvValue("width", width));
	tiler->changeValue(IlvValue("height", height));
	tiler->changeValue(IlvValue("result", "tileddata"));
    }
    flow->addFilter(tiler);

    IlvBitmapFilter* blender = IlvBitmapFilter::Create("IlvBlendFilter");
    {
	blender->changeValue(IlvValue("in", "tileddata,SourceGraphic"));
	blender->changeValue(IlvValue("width", width));
	blender->changeValue(IlvValue("height", height));
	blender->changeValue(IlvValue("result", "OriginGraphic"));
    }
    flow->addFilter(blender);    

    // blur sourceAlpha
    IlvBitmapFilter* gaussian =
	IlvBitmapFilter::Create("IlvGaussianBlurFilter");
    {
	gaussian->changeValue(IlvValue("in", "SourceAlpha"));
	gaussian->changeValue(IlvValue("width", width));
	gaussian->changeValue(IlvValue("height", height));
	gaussian->changeValue(IlvValue("deviationX", 4.0));
	gaussian->changeValue(IlvValue("deviationY", 4.0));
	gaussian->changeValue(IlvValue("result", "blur"));
    }
    flow->addFilter(gaussian);    

    // offset the blur
    IlvBitmapFilter* offset = IlvBitmapFilter::Create("IlvOffsetFilter");
    {
	offset->changeValue(IlvValue("width", width));
	offset->changeValue(IlvValue("height", height));
	offset->changeValue(IlvValue("dx", (IlInt)8));
	offset->changeValue(IlvValue("dy", (IlInt)8));
	offset->changeValue(IlvValue("in", "blur"));
	offset->changeValue(IlvValue("result", "offsetBlur"));
    }
    flow->addFilter(offset);    

    // light the blur
    IlvLightSource* light = IlvLightSource::Create("IlvPointLight");
    {
	light->changeValue(IlvValue("x", (IlFloat)-5000));
	light->changeValue(IlvValue("y", (IlFloat)-10000));
	light->changeValue(IlvValue("z", (IlFloat)20000));
    }
    IlvBitmapFilter* lighting =
	IlvBitmapFilter::Create("IlvSpecularLightingFilter");
    {
	lighting->changeValue(IlvValue("in", "blur"));
	lighting->changeValue(IlvValue("light", light));
	lighting->changeValue(IlvValue("width", width));
	lighting->changeValue(IlvValue("height", height));
	lighting->changeValue(IlvValue("surfaceScale", 5.0));
	lighting->changeValue(IlvValue("specularConstant", 1.0));
	lighting->changeValue(IlvValue("specularExponent", 7.0));
	lighting->changeValue(IlvValue("result", "specOut"));
    }
    flow->addFilter(lighting);

    IlvBitmapFilter* compose = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose->changeValue(IlvValue("in", "specOut,SourceAlpha"));
	compose->changeValue(IlvValue("width", width));
	compose->changeValue(IlvValue("height", height));
	compose->changeValue(IlvValue("operator", "in"));
	compose->changeValue(IlvValue("result", "specOut"));
    }
    flow->addFilter(compose);    

    IlvBitmapFilter* compose2 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose2->changeValue(IlvValue("in", "SourceGraphic,specOut"));
	compose2->changeValue(IlvValue("width", width));
	compose2->changeValue(IlvValue("height", height));
	compose2->changeValue(IlvValue("operator", "arithmetic"));
	compose2->changeValue(IlvValue("k2", 1.0));
	compose2->changeValue(IlvValue("k3", 1.0));
	compose2->changeValue(IlvValue("result", "litPaint"));
    }
    flow->addFilter(compose2);    

    IlvBitmapFilter* merge = IlvBitmapFilter::Create("IlvMergeFilter");
    {
	merge->changeValue(IlvValue("in", "tileddata,offsetBlur,litPaint"));
	merge->changeValue(IlvValue("width", width));
	merge->changeValue(IlvValue("height", height));
    }
    flow->addFilter(merge);

    IlvBitmapData* result = flow->applyUnary(srcdata);

    IlvIcon* icon =
	new IlvIcon(display,
		    IlvPoint(10, 25), 
		    new IlvBitmap(display, 
				  flow->getBitmapData("OriginGraphic")));
    addObject(icon);

    icon = new IlvIcon(display,
		       IlvPoint(30 + width, 25), 
		       new IlvBitmap(display, result));
    addObject(icon);

    delete result;    
    delete flow;

    resize(width * 2 + 60, height + 20);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
CreateReliefPage(Pan* mainPanel)
{
    Relief* panel = new Relief(mainPanel, "emboss.ilv");
    mainPanel->addPageNoteBook(panel, "Relief", "relief.txt");
}

