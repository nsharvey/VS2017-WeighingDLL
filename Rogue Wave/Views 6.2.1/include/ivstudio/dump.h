// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/dump.h
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
// Declaration of printing classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Dump_H
#define __IlvSt_Dump_H

#if !defined(__IlvSt_Studio_H)
#include <ivstudio/studio.h>
#endif

// --------------------------------------------------------------------------
extern void IlvStInitializePrinterModule(IlvStudio* editor);

#if 0
#if      !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif

class IlvManagerViewInteractor;
class IlvPSDevice;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDumpPanel
: public IlvStPanelHandler {
public:
    IlvStDumpPanel(IlvStudio*);
    virtual ~IlvStDumpPanel();
    virtual void doReset();
    virtual void doApply();
    virtual IlBoolean resetBeforeShowing() const;
    void 	setFilename(const char*);
    IlBoolean 	pageRect(IlvRect& rect);
    IlBoolean 	sourceRect(IlvRect& rect);
    void	dragDumpRect();
    void	dumpRectDragged(const IlvRect&);
    void	updateDumpArea();
    void	pageSize(IlvDim& width, IlvDim& height, IlvPSDevice* = 0);
protected:
    IlBoolean	makeDragInteractor();
    IlvManagerViewInteractor* _draginter;
    IlvManagerViewInteractor* _previnter;
};
#endif

#endif /* __IlvSt_Dump_H */
