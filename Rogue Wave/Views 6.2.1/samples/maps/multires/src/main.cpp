// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/multires/src/main.cpp
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
#include <viewer.h>

// --------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------
int
main(int argc , char** argv)
{
    IlPathName raster = IlPathName();// = 0;
    IlPathName shape  = IlPathName();// = 0;
    IlvDisplay* d = new IlvDisplay(argv[0], "", argc, argv);
    if (d->isBad()) {
	IlvPrint("Can't open display");
	delete d;
	return -1;
    }
    IlPathName localPath(d->getHomePath());
    d->prependToPath(localPath);
    localPath.addDirectory("samples/maps/multires/data");
    d->prependToPath(localPath);
    if (argc == 2) {
	/** attempt to interpret arg as datacd root */
	IlString a(argv[1]);
	if (!Viewer::IsDataCDRoot(a, raster, shape)) {
	    raster = IlPathName(argv[1]);
	    raster.forceDirectory();
	    if (!RasterLayerFactory::IsMultiRasterDirectory(raster, 9)) {
		shape = IlPathName(argv[1]);
		shape.forceDirectory();
		IlBoolean isShape = ShapeLayerFactory::IsMultiShapeDirectory(shape);
		if (isShape) {
		    raster = 0;
		} else {
		    IlvPrint("Usage %s [ <datacd root dir> | <multiraster dir> | <multishape dir> ]", argv[0]);
		    return -1;
		}
	    }
	    else {
		shape = 0;
	    }
	}
    }
    else if (argc > 2) {
	IlvPrint("Usage %s [ <datacd root dir> | <multiraster dir> | <multishape dir> ]", argv[0]);
	return -1;
    }
    raster.forceDirectory();
    shape.forceDirectory();
    Viewer v(d, raster, shape);
    v.show();

    return 0;
}
