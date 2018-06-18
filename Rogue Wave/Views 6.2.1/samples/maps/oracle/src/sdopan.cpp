// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/oracle/src/sdopan.cpp
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
#include <sdopan.h>
#define FILENAME "sdopan.ilv"

IL_STDUSE

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------
static void
ConnectCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->connectCB(g);
    }
}


// --------------------------------------------------------------------------
static void
DbSaveCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->dbSaveCB(g);
    }
}

// --------------------------------------------------------------------------
static void
LodCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->lodCB(g);
    }
}

// --------------------------------------------------------------------------
static void
EraseCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->eraseCB(g);
    }
}

// --------------------------------------------------------------------------
static void
ExitCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->exitCB(g);
    }
}

// --------------------------------------------------------------------------
static void
DbLoadCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->dbLoadCB(g);
    }
}

// --------------------------------------------------------------------------
static void
SelectCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->selectCB(g);
    }
}

// --------------------------------------------------------------------------
static void
LoadCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->loadCB(g);
    }
}

// --------------------------------------------------------------------------
static void
SaveCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->saveCB(g);
    }
}

// --------------------------------------------------------------------------
static void
TracesCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->tracesCB(g);
    }
}


// --------------------------------------------------------------------------
static void
NewCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->newCB(g);
    }
}

// --------------------------------------------------------------------------
static void
ResetCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->resetCB(g);
    }
}

// --------------------------------------------------------------------------
static void
PanCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->panCB(g);
    }
}

// --------------------------------------------------------------------------
static void
ZoomInCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->zoomInCB(g);
    }
}

// --------------------------------------------------------------------------
static void
ZoomCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->zoomCB(g);
    }
}

// --------------------------------------------------------------------------
static void
UnzoomCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->unzoomCB(g);
    }
}

// --------------------------------------------------------------------------
static void
FitToSizeCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->fitToSizeCB(g);
    }
}

// --------------------------------------------------------------------------
static void
OpenCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->openCB(g);
    }
}

// --------------------------------------------------------------------------
static void
ColarrayCB(IlvGraphic* g, IlvAny)
{
    Sdopan* o = (Sdopan*)
	IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) {
	o->colarrayCB(g);
    }
}

// --------------------------------------------------------------------------
// Sdopan
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
void
Sdopan::initialize()
{
    readFile(FILENAME);

    registerCallback("connectCB", ConnectCB);
    registerCallback("dbSaveCB", DbSaveCB);
    registerCallback("lodCB", LodCB);
    registerCallback("eraseCB", EraseCB);
    registerCallback("exitCB", ExitCB);
    registerCallback("dbLoadCB", DbLoadCB);
    registerCallback("selectCB", SelectCB);
    registerCallback("loadCB", LoadCB);
    registerCallback("saveCB", SaveCB);
    registerCallback("tracesCB", TracesCB);
    registerCallback("newCB", NewCB);
    registerCallback("resetCB", ResetCB);
    registerCallback("panCB", PanCB);
    registerCallback("zoomInCB", ZoomInCB);
    registerCallback("zoomCB", ZoomCB);
    registerCallback("unzoomCB", UnzoomCB);
    registerCallback("fitCB", FitToSizeCB);
    registerCallback("openCB", OpenCB);
    registerCallback("colarrayCB", ColarrayCB);
}

// --------------------------------------------------------------------------
void
Sdopan::connectCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::dbSaveCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::lodCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::eraseCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::exitCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::dbLoadCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::selectCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::loadCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::saveCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::tracesCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::newCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::resetCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::panCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::zoomInCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::zoomCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::unzoomCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::fitToSizeCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::openCB(IlvGraphic* g)
{
}

// --------------------------------------------------------------------------
void
Sdopan::colarrayCB(IlvGraphic* g)
{
}
