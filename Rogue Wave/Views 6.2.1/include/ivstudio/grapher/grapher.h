// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/grapher/grapher.h
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
// Declaration of grapher editing classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Grapher_H
#define __IlvSt_Grapher_H

#ifndef __IlvSt_Stbuffer_H
#include <ivstudio/stbuffer.h>
#endif

#ifndef __IlvSt_Studext_H
#include <ivstudio/studext.h>
#endif

#ifndef __Ilv_Grapher_All_H
#include <ilviews/grapher/all.h>
#endif

#ifndef __Ilv_Gadgraph_Rectscgr_H
#include <ilviews/gadgraph/rectscgr.h>
#endif

// --------------------------------------------------------------------------
class ILVSTGRAPHERCLASS IlvStGrapherBuffer
: public IlvStBuffer {
public:
    IlvStGrapherBuffer(IlvStudio* editor,
		       const char* name,
		       IlvManager* mgr = 0);
    virtual const char*	getType() const;
    virtual const char* getTypeLabel() const;
    virtual void	setUpPanelClass(IlvStPanelClass*) const;
    virtual IlBoolean	isAGrapherBuffer() const;
    virtual IlBoolean	canBePanelClass() const;
}; // class IlvStGrapherBuffer

// --------------------------------------------------------------------------
class ILVSTGRAPHERCLASS IlvStGrapherExtension
: public IlvStExtension {
public:
    IlvStGrapherExtension(IlvStudio*);
    ~IlvStGrapherExtension();

    virtual IlBoolean initializeBuffers();
    virtual IlBoolean initializeCommandDescriptors();
    virtual IlBoolean initializeModes();

    static IlvStGrapherExtension* Make(IlvStudio*);
};

// --------------------------------------------------------------------------
#endif /* __IlvSt_Grapher_H */
