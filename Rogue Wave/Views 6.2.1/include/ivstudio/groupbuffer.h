// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/groupbuffer.h
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

#ifndef __IlvSt_GroupBuffer_H
#define __IlvSt_GroupBuffer_H

#include <ilviews/manager/observer.h>
#include <ilviews/base/iostream.h>
#include <ivstudio/stbuffer.h>
#include <ivstudio/studio.h>
#include <ivstudio/error.h>

class ILVSTUDIOCLASS IlvStGroupEditionBuffer
: public IlvStBuffer
{
public:
    IlvStGroupEditionBuffer(IlvStudio*, IlvGraphic* g);
    ~IlvStGroupEditionBuffer();
    // Overriden virtuals
    //
    virtual const char* getType () const;
    virtual const char* getTypeLabel () const;
    virtual IlvStError* doSaveCommand(IlAny arg);
    virtual IlvStError* doSaveAsCommand(IlAny arg);
    // own methods
    IlvGraphic* getEditedGroup() { return _group; }
    virtual void setEditedGroup(IlvGraphic* g);
    virtual void setGroupName(const char* name = 0);
static IlvStGroupEditionBuffer* Find(IlvStudio*, IlvGraphic*);
protected:
    IlvGraphic* _group;
    IlvManagerObserver* _hook;
    virtual IlBoolean saveGroup();
    virtual IlBoolean loadGroup();
};

#endif /* __IlvSt_GroupBuffer_H */

