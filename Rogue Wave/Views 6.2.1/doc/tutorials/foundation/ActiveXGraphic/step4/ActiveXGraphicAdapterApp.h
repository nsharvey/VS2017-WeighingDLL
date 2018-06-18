// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step4/ActiveXGraphicAdapterApp.h
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
#ifndef __ActiveXGraphicAdapterApp__header__
#define __ActiveXGraphicAdapterApp__header__

#include <ilviews/gadgets/appli.h>

#include "ActiveXGraphicAdapter.h"

// --------------------------------------------------------------------------
class Testapp: public IlvApplication {
public:
    Testapp(const char* appName,
	    const char* displayName = 0,
	    int		argc = 0,
	    char**	argv = 0
    );
    Testapp(
        IlvDisplay* display,
        const char* appName
    );
    ~Testapp();
    virtual void makePanels();
    virtual void beforeRunning();
    ActiveXGraphicAdapter* getActiveXGraphicAdapter() const {
	return (ActiveXGraphicAdapter*) getPanel("ActiveXGraphicAdapter");
    }
};

#endif /* !__ActiveXGraphicAdapterApp__header__*/
