// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/myman.cpp
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
// Definition of a new manager type.
// --------------------------------------------------------------------------

#include <myman.h>
#include <myutil.h>

#include <ilviews/base/iostream.h>

#if !defined(IL_STD)
#include <iostream.h>
#else  /* !IL_STD */
IL_STDUSE
#endif /* !IL_STD */

// --------------------------------------------------------------------------
void
MyManager::save(ostream& stream) const
{
    IlvGraphic* const* objs;
    IlUInt n;
    objs = getObjects(n);
    if (n) {
	MyOutputFile output(stream, this);
	output.saveAll(this, n, objs);
    }
}

// --------------------------------------------------------------------------
void
MyManager::read(istream& stream)
{
    MyInputFile file(stream, this);
    file.readAll(this);
}

// --------------------------------------------------------------------------
void
MyManager::read(const char* filename)
{
    IlvGadgetManager::read(filename);
}

// --------------------------------------------------------------------------
// Input
// --------------------------------------------------------------------------
IlvGraphic*
MyInputFile::readObject()
{
    IlvGraphic* obj = IlvGadgetManagerInputFile::readObject();
    if (obj) {
	IlInt props;
	getStream() >> props;
	if (props & (int)(1 << 1)) {
	    char* param =IlvReadString(getStream());
	    MySetParameter(obj, IlvGetSymbol(param));
	}
    }
    return obj;
}

// --------------------------------------------------------------------------
// Output
// --------------------------------------------------------------------------
const char*
MyOutputFile::typeOf() const
{
    return "MyGadgetManagerOutput";
}

// --------------------------------------------------------------------------
void
MyOutputFile::writeObject(const IlvGraphic* obj)
{
    IlvGadgetManagerOutputFile::writeObject(obj);
    int props = 0;
    IlvSymbol* param = MyGetParameter(obj);
    if (param)
	props |= (int)(1 << 1);
    getStream() << IlvSpc() << props << IlvSpc();
    if (param) {
	IlvWriteString(getStream(), param->name());
	getStream() << IlvSpc();
    }
}
