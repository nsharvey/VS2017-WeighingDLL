// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/oracle/include/sdopan.h
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
//
// --------------------------------------------------------------------------
#ifndef __sdopan__header__
#define __sdopan__header__

#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/gadgets/menubar.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/gauge.h>

// --------------------------------------------------------------------------
class Sdopan
    : public IlvGadgetContainer
{
public:
    Sdopan(IlvDisplay* display,
           const char* name,
           const char* title,
           IlvRect*    size            = 0,
           IlBoolean   useAccelerators = IlFalse,
           IlBoolean   visible         = IlFalse,
           IlUInt      properties      = 0,
           IlvSystemView transientFor  = 0)
        : IlvGadgetContainer(display,
			     name,
			     title,
			     size ? *size : IlvRect(0, 0, 572, 543),
			     properties,
			     useAccelerators,
			     visible,
			     transientFor)
        { initialize(); }
    Sdopan(IlvAbstractView* parent,
           IlvRect* size = 0,
           IlBoolean useacc = IlFalse,
           IlBoolean visible = IlTrue)
        : IlvGadgetContainer(parent,
			     size ? *size : IlvRect(0, 0, 572, 543),
			     useacc,
			     visible)
        { initialize(); }
    // ____________________________________________________________
    virtual void connectCB(IlvGraphic*);
    virtual void dbSaveCB(IlvGraphic*);
    virtual void lodCB(IlvGraphic*);
    virtual void eraseCB(IlvGraphic*);
    virtual void exitCB(IlvGraphic*);
    virtual void dbLoadCB(IlvGraphic*);
    virtual void selectCB(IlvGraphic*);
    virtual void loadCB(IlvGraphic*);
    virtual void saveCB(IlvGraphic*);
    virtual void tracesCB(IlvGraphic*);
    virtual void newCB(IlvGraphic*);
    virtual void resetCB(IlvGraphic*);
    virtual void panCB(IlvGraphic*);
    virtual void zoomInCB(IlvGraphic*);
    virtual void zoomCB(IlvGraphic*);
    virtual void unzoomCB(IlvGraphic*);
    virtual void fitToSizeCB(IlvGraphic*);
    virtual void openCB(IlvGraphic*);
    virtual void colarrayCB(IlvGraphic*);

    IlvToolBar* gettoolbar() const
	{ return (IlvToolBar*)getObject("toolbar"); }
    IlvSCManagerRectangle* getscm() const
	{ return (IlvSCManagerRectangle*)getObject("scm"); }
    IlvMenuBar* getmenubar() const
	{ return (IlvMenuBar*)getObject("menubar"); }
protected:
    void initialize();
};

#endif /* !__sdopan__header__*/
