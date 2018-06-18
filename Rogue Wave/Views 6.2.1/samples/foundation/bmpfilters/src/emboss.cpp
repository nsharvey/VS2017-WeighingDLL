// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bmpfilters/src/emboss.cpp
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
// Using various bitmap filters to create an emboss effect.
// --------------------------------------------------------------------------

#include <emboss.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Panel class for sample Emboss
// --------------------------------------------------------------------------
Emboss::Emboss(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename) 
{
    initEmboss();
}

// --------------------------------------------------------------------------
Emboss::~Emboss()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Emboss::initEmboss()
{
    IlvRect dims(0, 0, 500, 500);
    IlvDisplay* display = getDisplay();
    
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/bmpfilters/data");
    display->prependToPath(localPath);
    
    IlvFilterFlow* flow = new IlvFilterFlow();
    
    IlvRGBBitmapData* srcdata = (IlvRGBBitmapData*)
	display->readBitmapData("colors.png");
    IlUInt width = srcdata->getWidth();
    IlUInt height = srcdata->getHeight();
    resize(width * 2 + 60, height + 20);
     

    IlvBitmapFilter* colmatrix =
	IlvBitmapFilter::Create("IlvLuminanceToAlphaFilter");
    {
	colmatrix->changeValue(IlvValue("in", "SourceGraphic"));
	colmatrix->changeValue(IlvValue("width", width));
	colmatrix->changeValue(IlvValue("height", height));
	colmatrix->changeValue(IlvValue("result", "lumalpha"));
    }
    flow->addFilter(colmatrix);

    IlvTransferFunction* tabletransfer =
	IlvTransferFunction::Create("IlvTableTransfer");
    {
	tabletransfer->changeValue(IlvValue("tableValues", "1,0"));
    }

    IlvBitmapFilter* component =
	IlvBitmapFilter::Create("IlvComponentTransferFilter");
    {	
	component->changeValue(IlvValue("in", "lumalpha"));
	component->changeValue(IlvValue("width", width));
	component->changeValue(IlvValue("height", height));
	component->changeValue(IlvValue("alphaFunction", tabletransfer));
	component->changeValue(IlvValue("result", "invertedalpha"));
    }
    flow->addFilter(component);

    IlvLightSource* light = IlvLightSource::Create("IlvDistantLight");
    {
	light->changeValue(IlvValue("azimuth", 135.0));
	light->changeValue(IlvValue("elevation", 60.0));
	light->changeValue(IlvValue("r", 0.6));
	light->changeValue(IlvValue("g", 0.6));
	light->changeValue(IlvValue("b", 0.6));
    }

    IlvBitmapFilter* difflighting =
	IlvBitmapFilter::Create("IlvDiffuseLightingFilter");
    {
	difflighting->changeValue(IlvValue("in", "invertedalpha"));
	difflighting->changeValue(IlvValue("light", light));
	difflighting->changeValue(IlvValue("width", width));
	difflighting->changeValue(IlvValue("height", height));
	difflighting->changeValue(IlvValue("surfaceScale", 5.0));
	difflighting->changeValue(IlvValue("diffuseConstant", 1.0));
	difflighting->changeValue(IlvValue("result", "diffuse"));
    }
    flow->addFilter(difflighting);

    IlvLightSource* light2 = IlvLightSource::Create("IlvDistantLight");
    {
	light2->changeValue(IlvValue("azimuth", 135.0));
	light2->changeValue(IlvValue("elevation", 30.0));
    }

    IlvBitmapFilter* speclighting =
	IlvBitmapFilter::Create("IlvSpecularLightingFilter");
    {	
	speclighting->changeValue(IlvValue("in", "invertedalpha"));
	speclighting->changeValue(IlvValue("light", light2));
	speclighting->changeValue(IlvValue("width", width));
	speclighting->changeValue(IlvValue("height", height));
	speclighting->changeValue(IlvValue("surfaceScale", 5.0));
	speclighting->changeValue(IlvValue("specularConstant", 1.0));
	speclighting->changeValue(IlvValue("specularExponent", 6.0));
	speclighting->changeValue(IlvValue("result", "specular"));
    }
    flow->addFilter(speclighting);

    IlvBitmapFilter* compose2 = IlvBitmapFilter::Create("IlvComposeFilter");
    {
	compose2->changeValue(IlvValue("in", "diffuse,specular"));
	compose2->changeValue(IlvValue("width", width));
	compose2->changeValue(IlvValue("height", height));
	compose2->changeValue(IlvValue("operator", "arithmetic"));
	compose2->changeValue(IlvValue("k2", 1.0));
	compose2->changeValue(IlvValue("k3", 1.0));
	compose2->changeValue(IlvValue("result", "ResultGraphic"));
    }
    flow->addFilter(compose2);

    addObject(new IlvIcon(display,
			  IlvPoint(10, 25), 
			  new IlvBitmap(display, srcdata)));

    IlvBitmapData* result = flow->applyUnary(srcdata);
    delete srcdata;
    delete flow;
    addObject(new IlvIcon(display,
			  IlvPoint(30 + width, 25), 
			  new IlvBitmap(display, result)));
    
    delete result;
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
CreateEmbossPage(Pan* mainPanel)
{
    Emboss* panel = new Emboss(mainPanel, "emboss.ilv");
    mainPanel->addPageNoteBook(panel, "Emboss", "emboss.txt");
}
