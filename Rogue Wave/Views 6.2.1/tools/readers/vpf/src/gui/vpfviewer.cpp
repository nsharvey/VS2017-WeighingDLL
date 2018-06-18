// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/vpfviewer.cpp
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
// Rogue Wave Views interface for VPF reader
// --------------------------------------------------------------------------

#include <ilviews/base/view.h>
#include <vpf/gui/reader.h>
#include <vpf/table.h>
#include <vpf/query.h>
#include <vpf/thematicindex.h>

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("IlvVPFReader", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create IlvDisplay...");
	delete display;
	return 1;
    }
    IlvVpfReader* reader = new IlvVpfReader(display);
    IlvMainLoop();
    return 0;
}
