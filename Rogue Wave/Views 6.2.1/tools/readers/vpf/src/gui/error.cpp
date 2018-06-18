// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/error.cpp
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
// Definition of the Error class
// --------------------------------------------------------------------------

#include <vpf/gui/error.h>
#include <vpf/error.h>

#include <ilviews/gadgets/text.h>
#include <ilviews/gadgets/button.h>

#include <string.h>
#include <stdio.h>
#include <ilviews/base/pathname.h>
#include <ilog/sstream.h>

static const char* GetResourceFileName(IlvDisplay* display,const char*name)
{
    static char path[2048];
    const char* home=display->getEnvOrResource("ILVMAPSHOME");
    sprintf(path,"%s/%s",home?home:".",name);
    if (IlvFileExists(path)) {
	return path;
    } else {
	home=display->getEnvOrResource("ILVHOME");
	sprintf(path,"%s/%s",home?home:".",name);
	if (IlvFileExists(path)) {
	    return path;
	}
    }
    return name;
}

// --------------------------------------------------------------------------
Error::Error(IlvDisplay* display,
	     const IlvRect& rect,
	     VpfError* first,
	     IlUInt properties,
	     IlvSystemView transientFor)
: IlvDialog(display, "Error", "Error",
	    GetResourceFileName(display,"tools/readers/vpf/data/error.ilv"),
	    properties, &rect, transientFor)
{
    IlvText* text = (IlvText*)getObject("text");
    if (text) {
	VpfError* first = VpfErrorReporter::GetFirst();
	while (first) {
#if 0
	    class strstream& stream = first->getStream();
#else
	    strstream& stream = first->getStream();
#endif
	    stream << '\0';
	    text->addLine(first->getWhere());

#if defined(IL_USING_STRINGSTREAM)
	    char* buffer = new char[stream.str().size()+1];
	    strcpy(buffer, stream.str().data());
	    text->addLine(buffer);
	    //	    delete[] buffer; ?
#else	    
	    text->addLine(stream.str());
#endif
	    first = first->getNext();
	}
    }
}

// --------------------------------------------------------------------------
void
Error::HandleError(IlvDisplay* display, IlvView* view)
{
    VpfError* first = VpfErrorReporter::GetFirst();
    if (first) {
	Error ge(display,
		 IlvRect(0, 0, 320, 160), 
		 first, 0,
		 view ? view->getSystemView() : 0);
	ge.moveToMouse();
	ge.wait(IlFalse, 0);
	VpfErrorReporter::Clear();
    }
}
