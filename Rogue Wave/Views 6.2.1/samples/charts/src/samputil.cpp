// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/src/samputil.cpp
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
// Geeral purpose functions for the samples
// --------------------------------------------------------------------------
#include <samputil.h>
#include <ilviews/util/util.h>
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/attach.h>

#ifdef IL_STD
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
IL_STDUSE
#else
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <math.h>
#endif

// --------------------------------------------------------------------------
static const IlUInt NbColors = 15;
static const char* ColorNames[15] = {
    "red",
    "cornflowerblue",
    "palegreen",
    "gold",
    "salmon",
    "indianred",
    "yellow",
    "green",
    "violet",
    "magenta",
    "blue",
    "wheat",
    "maroon",
    "lightsteelblue"
};

// --------------------------------------------------------------------------
IlvPalette*
GetPalette(IlvDisplay* dpy, const char* bg, const char* fg)
{
    return dpy->getPalette(dpy->getColor(bg), dpy->getColor(fg));
}

// --------------------------------------------------------------------------
IlvPalette*
GetFontPalette(IlvDisplay* dpy, const char* fontName)
{
    return dpy->getPalette(0, 0, 0, 0, dpy->getFont(fontName));
}

// --------------------------------------------------------------------------
IlvPalette**
GetPalettes(IlvDisplay* dpy, IlUInt count)
{
    IlvPalette** palettes = new IlvPalette*[count];
    IlvColor* white = dpy->getColor("white");
    white->lock();
    for (IlUInt i = 0; i < count; ++i) {
	IlvColor* color = dpy->getColor(ColorNames[i % NbColors]);
	color->lock();
	IlvGradientPattern* gradientPattern = 
	    dpy->getRadialGradientPattern(white, color, 10, 10);
	palettes[i] =
	    dpy->getPalette(0,
			    color,
			    0,
			    0,
			    0,
			    0,
			    0,
			    IlvFillGradientPattern,
			    IlvArcPie,
			    IlvEvenOddRule,
			    IlvFullIntensity,
			    IlvDefaultAntialiasingMode,
			    gradientPattern);
	color->unLock();
    }
    white->unLock();
    return palettes;
}

// --------------------------------------------------------------------------
IlvChartYValueSet*
CreateYDataSet(IlUInt count,
	       IlUInt min,
	       IlUInt max)
{	
    IlvChartYValueSet* set = new IlvChartYValueSet();
    IlDouble val;
    while(count--) {
	val = IL_CAST(IlDouble, (rand() % (max - min + 1) + min));
	set->addValue(val);
    }
    return set;
}

// --------------------------------------------------------------------------
IlvChartYValueSet*
CreateSmoothDataSet(IlUInt count, IlUInt amplitude)
{
    int amp = IL_CAST(int, amplitude);
    int twoAmp = IL_CAST(int, amplitude * 2) + 1;
    IlvChartYValueSet* set = new IlvChartYValueSet();
    IlDouble* values = new IlDouble[count];
    values[0] = IL_CAST(IlDouble, rand() % amplitude);
    for (IlUInt i =1 ; i < count; ++i)
	values[i] = values[i - 1] + (rand() % twoAmp) - amp;
    set->insertValues(count, values);
    delete [] values;
    return set;
}

// --------------------------------------------------------------------------
void
Attach(IlvContainer* cont, IlvGraphic* g)
{
    if (!IlvAttachmentsHandler::Get(cont))
	IlvAttachmentsHandler::Set(cont, new IlvAttachmentsHandler());
    IlvSetAttachment(g, IlvLeft,	IlvFixedAttach,		0);
    IlvSetAttachment(g, IlvTop,		IlvFixedAttach,		0);
    IlvSetAttachment(g, IlvRight,	IlvFixedAttach,		0);
    IlvSetAttachment(g, IlvBottom,	IlvFixedAttach,		0);
    IlvSetAttachment(g, IlvHorizontal,	IlvElasticAttach,	0);
    IlvSetAttachment(g, IlvVertical,	IlvElasticAttach,	0);
}

// --------------------------------------------------------------------------
void
Quit(IlvView* view, IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
void
Quit(IlvContainer* cont, IlvEvent&, IlAny)
{
    Quit(cont, 0);
}

