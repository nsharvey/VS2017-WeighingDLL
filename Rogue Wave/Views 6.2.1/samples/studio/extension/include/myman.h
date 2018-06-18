// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/include/myman.h
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
// Declaration of the MyManager class and auxiliaries
// --------------------------------------------------------------------------

#ifndef __Myman
#define __Myman

#include <ilviews/gadmgr/gadmgr.h>

// --------------------------------------------------------------------------
class MyManager : public IlvGadgetManager
{
 public:
    MyManager(IlvDisplay* display, 
	      int         layers    = 3, 
	      IlBoolean   useacc    = IlTrue,
	      IlUShort    maxInList = IlvMaxObjectsInList,
	      IlUShort    maxInNode = IlvMaxObjectsInList)
	: IlvGadgetManager(display, layers, useacc, maxInList, maxInNode)
    {};

    virtual void read(const char* filename);
    virtual void save(ILVSTDPREF ostream&) const;
    virtual void read(ILVSTDPREF istream&);
};

// --------------------------------------------------------------------------
class MyOutputFile : public IlvGadgetManagerOutputFile
{
public:
    MyOutputFile(ILVSTDPREF ostream& stream,
		 const IlvGadgetManager* mgr = 0)
	: IlvGadgetManagerOutputFile(stream,mgr)
    {};
    // ____________________________________________________________
    virtual const char* typeOf() const;
    virtual void writeObject(const IlvGraphic* obj);
};

// --------------------------------------------------------------------------
class MyInputFile : public IlvGadgetManagerInputFile
{
public:
    MyInputFile(ILVSTDPREF istream& stream,
		IlvGadgetManager* mgr = 0)
	: IlvGadgetManagerInputFile(stream,mgr)
    {};
    // ____________________________________________________________
    virtual IlvGraphic* readObject();
};

// --------------------------------------------------------------------------
#endif /* ! __Myman */
