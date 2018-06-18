// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/include/samputil.h
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
#include <ilviews/ilv.h>
#include <ilviews/charts/chartinc.h>

IlvPalette* GetPalette(IlvDisplay* dpy, const char* bg, const char* fg);

IlvPalette* GetFontPalette(IlvDisplay* dpy, const char* fontName);

IlvPalette** GetPalettes(IlvDisplay* dpy, IlUInt count);

// Attaches <g> on the borders pf <cont>.
void Attach(IlvContainer* cont, IlvGraphic*   g);

// Create a dataset filled with random y values between min and max
IlvChartYValueSet* CreateYDataSet(IlUInt count, IlUInt min, IlUInt max);

// Create a dataset filled with random y values
IlvChartYValueSet* CreateSmoothDataSet(IlUInt count, IlUInt amplitude);

// Callback to quit the application
void Quit(IlvView* view, IlAny);
void Quit(IlvContainer* cont, IlvEvent&, IlAny);
