// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/mycont.cpp
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
// Definition of the MyContainer class
// --------------------------------------------------------------------------

#include <ilviews/ilv.h>

#include <mycont.h>
#include <myutil.h>

#include <ilviews/base/iostream.h>
#if !defined(IL_STD)
#include <iostream.h>
#else  /* !IL_STD */
IL_STDUSE
#endif /* !IL_STD */

// --------------------------------------------------------------------------
static void
LoadIlv(IlvGraphic* g,
	IlAny)
{
    IlvSymbol* name = MyGetParameter(g);
    if (name)
	IlvPrint("File to read: %s", name->name());
    else
	IlvPrint("No associated file");
}

// --------------------------------------------------------------------------
MyContainer::MyContainer(IlvDisplay* d,
			 const char* name,
			 const char* title,
			 const IlvRect& dims,
			 IlUInt properties,
			 IlBoolean useacc,
			 IlBoolean visible,
			 IlvSystemView transiFor)
    : IlvGadgetContainer(d, name, title, dims, properties,
			 useacc, visible, transiFor)
{
    registerCallback("loadilv", LoadIlv);
}

// --------------------------------------------------------------------------
MyContainer::MyContainer(IlvAbstractView* parent,
			 const IlvRect&   size,
			 IlBoolean       useacc,
			 IlBoolean       visible)
    : IlvGadgetContainer(parent, size, useacc, visible)
{
    
    registerCallback("loadilv", LoadIlv);
}

// --------------------------------------------------------------------------
IlBoolean 
MyContainer::read(istream& stream)
{
    MyViewInputFile file(stream);
    file.readAll(this);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlvGraphic* 
MyViewInputFile::readObject()
{
    IlvGraphic* obj = IlvGadgetViewInputFile::readObject();
    if (obj) {
	unsigned short props = 0;
	getStream() >> props;
	if (props & (unsigned short)(1 << 1)) {
	    char* param =IlvReadString(getStream());
	    MySetParameter(obj, IlvGetSymbol(param));
	}
    }
    return obj;
}

// --------------------------------------------------------------------------
IlvPreRegisterViewClass(MyContainer);
IL_BEGINMODULEINITDEF(mycont)
IlvPostRegisterViewClassWithAccessors(MyContainer, IlvGadgetContainer);
IlvRegisterClassCodeInformation(MyContainer,"mycont.h","");
IL_ENDMODULEINITDEF(mycont)
