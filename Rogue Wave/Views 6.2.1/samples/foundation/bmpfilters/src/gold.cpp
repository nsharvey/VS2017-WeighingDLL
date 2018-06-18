// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bmpfilters/src/gold.cpp
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
// Using various filters to create a golden effect.
// --------------------------------------------------------------------------

#include <gold.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Panel class for sample Gold
// --------------------------------------------------------------------------
Gold::Gold(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename) 
{
    initGold();
}

// --------------------------------------------------------------------------
Gold::~Gold()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Gold::initGold()
{
    IlvRect dims(0, 0, 500, 500);
    IlvDisplay* display = getDisplay();

    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/bmpfilters/data");
    display->prependToPath(localPath);

    IlvFilterFlow* flow = new IlvFilterFlow();

    IlvRGBBitmapData* srcdata =
	(IlvRGBBitmapData*)display->readBitmapData("Views_white.png");
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

    IlvBitmapFilter* morphology =
	IlvBitmapFilter::Create("IlvMorphologyFilter");
    {
	morphology->changeValue(IlvValue("in", "SourceGraphic"));
	morphology->changeValue(IlvValue("width", width));
	morphology->changeValue(IlvValue("height", height));
	morphology->changeValue(IlvValue("operator", "dilate"));
	morphology->changeValue(IlvValue("radiusX", (IlInt)4));
	morphology->changeValue(IlvValue("radiusY", (IlInt)4));
	morphology->changeValue(IlvValue("result", "alpha"));
    }
    flow->addFilter(morphology);

    IlvBitmapFilter* gaussian =
	IlvBitmapFilter::Create("IlvGaussianBlurFilter");
    {
	gaussian->changeValue(IlvValue("in", "alpha"));
	gaussian->changeValue(IlvValue("width", width));
	gaussian->changeValue(IlvValue("height", height));
	gaussian->changeValue(IlvValue("deviationX", (IlFloat)4.0));
	gaussian->changeValue(IlvValue("deviationY", (IlFloat)4.0));
	gaussian->changeValue(IlvValue("result", "blur0"));
    }
    flow->addFilter(gaussian);

    IlvBitmapFilter* offset = IlvBitmapFilter::Create("IlvOffsetFilter");
    {
	offset->changeValue(IlvValue("in", "blur0"));
	offset->changeValue(IlvValue("width", width));
	offset->changeValue(IlvValue("height", height));
	offset->changeValue(IlvValue("dx", (IlInt)4));
	offset->changeValue(IlvValue("dy", (IlInt)4));
	offset->changeValue(IlvValue("result", "offsetBlurredAlpha"));
    }
    flow->addFilter(offset);

    IlvBitmapFilter* flood = IlvBitmapFilter::Create("IlvFloodFilter");
    {
	flood->changeValue(IlvValue("width", width));
	flood->changeValue(IlvValue("height", height));
	flood->changeValue(IlvValue("R", (IlUInt)0));
	flood->changeValue(IlvValue("G", (IlUInt)0));
	flood->changeValue(IlvValue("B", (IlUInt)0));
	flood->changeValue(IlvValue("A", (IlUInt)128));
	flood->changeValue(IlvValue("result", "color"));
    }
    flow->addFilter(flood);

    IlvBitmapFilter* compose = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose->changeValue(IlvValue("in", "color,offsetBlurredAlpha"));
	compose->changeValue(IlvValue("width", width));
	compose->changeValue(IlvValue("height", height));
	compose->changeValue(IlvValue("operator", "in"));
	compose->changeValue(IlvValue("result", "offsetBlurredAlpha"));
    }
    flow->addFilter(compose);

    IlvBitmapFilter* turbulence =
	IlvBitmapFilter::Create("IlvTurbulenceFilter");
    {
	turbulence->changeValue(IlvValue("width", width));
	turbulence->changeValue(IlvValue("height", height));
	turbulence->changeValue(IlvValue("numOctaves", (IlUInt)1));
	turbulence->changeValue(IlvValue("baseFrequencyX", (IlFloat)0.05));
	turbulence->changeValue(IlvValue("baseFrequencyY", (IlFloat)0.05));
	turbulence->changeValue(IlvValue("isFractalNoise", IlFalse));
	turbulence->changeValue(IlvValue("result", "turb1"));
    }
    flow->addFilter(turbulence);
    
    IlvBitmapFilter* turbulence2 =
	IlvBitmapFilter::Create("IlvTurbulenceFilter");
    {
	turbulence2->changeValue(IlvValue("width", width));
	turbulence2->changeValue(IlvValue("height", height));
	turbulence2->changeValue(IlvValue("baseFrequencyX", (IlFloat)0.4));
	turbulence2->changeValue(IlvValue("baseFrequencyY", (IlFloat)0.4));
	turbulence2->changeValue(IlvValue("result", "turb2"));
    }
    flow->addFilter(turbulence2);

    IlvBitmapFilter* compose2 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose2->changeValue(IlvValue("in", "turb1,turb2"));
	compose2->changeValue(IlvValue("width", width));
	compose2->changeValue(IlvValue("height", height));
	compose2->changeValue(IlvValue("operator", "arithmetic"));
	compose2->changeValue(IlvValue("k1", 1.0));
	compose2->changeValue(IlvValue("result", "turb"));
    }
    flow->addFilter(compose2);

    IlvBitmapFilter* compose3 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose3->changeValue(IlvValue("in", "blur0,turb"));
	compose3->changeValue(IlvValue("width", width));
	compose3->changeValue(IlvValue("height", height));
	compose3->changeValue(IlvValue("result", "blur"));
	compose3->changeValue(IlvValue("operator", "arithmetic"));
	compose3->changeValue(IlvValue("k2", 0.6));
	compose3->changeValue(IlvValue("k3", 0.4));
    }
    flow->addFilter(compose3);

    IlvBitmapFilter* compose4 = IlvBitmapFilter::Create("IlvComposeFilter");
    flow->addFilter(compose4);
    {
	compose4->changeValue(IlvValue("width", width));
	compose4->changeValue(IlvValue("height", height));
	compose4->changeValue(IlvValue("in", "blur,blur0"));
	compose4->changeValue(IlvValue("result", "blur"));
	compose4->changeValue(IlvValue("operator", "in"));
    }

    IlvLightSource* light1 = IlvLightSource::Create("IlvDistantLight");
    {
	light1->changeValue(IlvValue("r", 0.6));
	light1->changeValue(IlvValue("g", 0.6));
	light1->changeValue(IlvValue("b", 0.0));
	light1->changeValue(IlvValue("elevation", (IlFloat)60));
	light1->changeValue(IlvValue("azimuth", (IlFloat)135));
    }
    IlvBitmapFilter* lighting =
	IlvBitmapFilter::Create("IlvDiffuseLightingFilter");
    {
	lighting->changeValue(IlvValue("in", "blur"));
	lighting->changeValue(IlvValue("light", light1));
	lighting->changeValue(IlvValue("width", width));
	lighting->changeValue(IlvValue("height", height));
	lighting->changeValue(IlvValue("surfaceScale", (IlFloat)6.0));
	lighting->changeValue(IlvValue("diffuseConstant", (IlFloat)1.0));
	lighting->changeValue(IlvValue("result", "diffuse"));
    }
    flow->addFilter(lighting);

    IlvLightSource* light2 = IlvLightSource::Create("IlvDistantLight");
    {
	light2->changeValue(IlvValue("elevation", (IlFloat)60));
	light2->changeValue(IlvValue("azimuth", (IlFloat)135));
    }
    IlvBitmapFilter* lighting2 =
	IlvBitmapFilter::Create("IlvSpecularLightingFilter");
    {
	lighting2->changeValue(IlvValue("in", "blur"));
	lighting2->changeValue(IlvValue("light", (IlvValueInterface*)light2));
	lighting2->changeValue(IlvValue("width", width));
	lighting2->changeValue(IlvValue("height", height));
	lighting2->changeValue(IlvValue("surfaceScale", (IlFloat)6.0));
	lighting2->changeValue(IlvValue("specularConstant", (IlFloat)1.0));
	lighting2->changeValue(IlvValue("specularExponent", (IlFloat)10.0));
	lighting2->changeValue(IlvValue("result", "specularOut"));
    }
    flow->addFilter(lighting2);

    IlvBitmapFilter* compose5 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose5->changeValue(IlvValue("in", "specularOut,alpha"));
	compose5->changeValue(IlvValue("width", width));
	compose5->changeValue(IlvValue("height", height));
	compose5->changeValue(IlvValue("operator", "in"));
	compose5->changeValue(IlvValue("result", "specularOut"));
    }
    flow->addFilter(compose5);

    IlvBitmapFilter* compose6 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose6->changeValue(IlvValue("in", "blur,diffuse"));
	compose6->changeValue(IlvValue("width", width));
	compose6->changeValue(IlvValue("height", height));
	compose6->changeValue(IlvValue("operator", "arithmetic"));
	compose6->changeValue(IlvValue("k1", 0.7));
	compose6->changeValue(IlvValue("k2", 0.3));
	compose6->changeValue(IlvValue("result", "litPaint"));
    }
    flow->addFilter(compose6);

    IlvBitmapFilter* compose7 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose7->changeValue(IlvValue("in", "litPaint,specularOut"));
	compose7->changeValue(IlvValue("width", width));
	compose7->changeValue(IlvValue("height", height));
	compose7->changeValue(IlvValue("operator", "arithmetic"));
	compose7->changeValue(IlvValue("k2", 1.0));
	compose7->changeValue(IlvValue("k3", 0.7));
	compose7->changeValue(IlvValue("result", "litPaint"));
    }
    flow->addFilter(compose7);

    IlvBitmapFilter* merge = IlvBitmapFilter::Create("IlvMergeFilter");
    {
	merge->changeValue(IlvValue("in",
				    "tileddata,offsetBlurredAlpha,litPaint"));
	merge->changeValue(IlvValue("width", width));
	merge->changeValue(IlvValue("height", height));
    }
    flow->addFilter(merge);
    
    IlvBitmapData* result = flow->applyUnary(srcdata);
    delete srcdata;

    IlvIcon* icon =
	new IlvIcon(display,
		    IlvPoint(10, 25),
		    new IlvBitmap(display, 
				  flow->getBitmapData("OriginGraphic")));
    addObject(icon);

    delete flow;
    
    icon = new IlvIcon(display,
		       IlvPoint(30 + width, 25), 
		       new IlvBitmap(display, result));
    addObject(icon);

    delete result;

    resize(width * 2 + 60, height + 20);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
CreateGoldPage(Pan* mainPanel)
{
    Gold* panel = new Gold(mainPanel, "emboss.ilv");
    mainPanel->addPageNoteBook(panel, "Gold", "gold.txt");
}
