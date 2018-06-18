// -------------------------------------------------------------- -*- C++ -*-
//					  Rogue Wave Views sample source file
// File: samples/maps/cadrg/include/covchoose.h
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
// Declaration of cadrg corevage chooser
// --------------------------------------------------------------------------
#ifndef _CovChoose_H
#define _CovChoose_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/maps/format/cadrg/cadrgtoc.h>
#include <ilviews/maps/format/cadrg/cadrgread.h>

#include "viewer.h"

// --------------------------------------------------------------------------
class CovChoose
{
public:
    CovChoose(IlvDisplay* display, class Viewer* viewer);

    static void SmallItemSelected(IlvGraphic* g, IlvAny);
    static void MediumItemSelected(IlvGraphic* g, IlvAny);
    static void LargeItemSelected(IlvGraphic* g, IlvAny);
    const IlvCADRGCoverage* getSmallCoverage();
    const IlvCADRGCoverage* getMediumCoverage();
    const IlvCADRGCoverage* getLargeCoverage();
    static void OkCallback(IlvGraphic* g, IlvAny a);
    void createCombos();
    void empty(int *list);
    void listCoverages();
    static void PixelSize(const IlvCADRGCoverage* coverage,
			  IlvFloatPoint& ps);
    void buildSmall();
    void buildMedium(IlInt index);
    void buildLarge(IlInt index);
    const char* getName(const IlvCADRGCoverage* cov);
    class Viewer* getViewer()
	{ return _viewer; }
    void selectDefault();

    IlvDisplay* _display;        
    IlvGadgetContainer* _gadgetContainer;
    IlvComboBox* _smallComboBox;
    IlvComboBox* _mediumComboBox;
    IlvComboBox* _largeComboBox;

    const IlvCADRGCoverage* const* _coverages;
    IlUShort _numCoverages;

    int* _small;
    int* _medium;
    int* _large;

    class Viewer* _viewer;
};

#endif /* _CovChoose_H */
