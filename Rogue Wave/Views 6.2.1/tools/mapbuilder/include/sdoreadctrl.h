// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/sdoreadctrl.h
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
// Declaration of the SdoReaderController class
// -------------------------------------------------------------------------
#ifndef _SdoReaderController_h_
#define _SdoReaderController_h_

#if HAS_SDO_SUPPORT
#include <ilviews/maps/format/oracle/sdoutil.h>
#include <ilviews/maps/format/oracle/objectmodel/8iutil.h>
#include <readctrl.h>

class MapBuilder;

// -------------------------------------------------------------------------
class SdoReaderController
    : public ReaderController
{
public:
    SdoReaderController(IlvDisplay*   display,
			IlvSystemView transientFor,
			MapBuilder*   builder);
    virtual ~SdoReaderController();

    virtual void cancelClicked();
    virtual void okClicked();
    virtual void updateController();
private:
    MapBuilder* _builder;
};
#endif

#endif /* _SdoReaderController_h_ */
