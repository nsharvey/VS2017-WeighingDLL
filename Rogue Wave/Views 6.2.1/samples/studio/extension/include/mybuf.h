// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/include/mybuf.h
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
// Declaration of the MyGadgetBuffer class
// --------------------------------------------------------------------------

#ifndef __Mybuf_H
#define __Mybuf_H

#include <ivstudio/buffer.h>

// --------------------------------------------------------------------------
class MyGadgetBuffer : public IlvStGadgetBuffer
{
public:
    MyGadgetBuffer(IlvStudio*,
		   const char* name,
		   IlvManager* = 0);
    virtual const char* getType () const;
    virtual const char* getTypeLabel() const;
    virtual void	setUpPanelClass(IlvStPanelClass*) const;
};

#endif /* __Mybuf_H */
