// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/scalecombo.cpp
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
// The implementation of the ScaleCombo methods.
// --------------------------------------------------------------------------
#include "scalecombo.h"

#if defined(IL_STD)
#  include <cstring>
#  include <cctype>
#  include <cstdio>
#  include <cstdlib>
IL_STDUSE
#else  /* !IL_STD */
#  if !defined(WINDOWS)
#    include <strings.h>
#  endif
#  include <ctype.h>
#  include <stdio.h>
#  include <stdlib.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

static const char* ScaleComboLabels[] = {
    "No limit",
    "5 000",
    "10 000",

    "13 000",
    "25 000",
    "50 000",

    "100 000",
    "250 000",
    "500 000",

    "1 000 000",
    "2 500 000",
    "5 000 000",

    "10 000 000",
    "25 000 000",
    "50 000 000",
    
    "100 000 000",
    "250 000 000",
    "500 000 000"
};
static IlUShort ScaleComboLabelNum = 18;

// --------------------------------------------------------------------------
ScaleCombo::ScaleCombo(IlvDisplay* display,
		       const IlvPoint& point)
: IlvComboBox(display, point, "No limit",
	      ScaleComboLabels, ScaleComboLabelNum)
{
}

// --------------------------------------------------------------------------
const char*
ScaleCombo::check(IlUShort sh)
{
    if (isdigit(sh) || isspace(sh)) {
	if (strcmp(getLabel(), "No limit") == 0) {
	    char buf[20];
	    sprintf(buf,"%c",sh);
	    setLabel(buf);
	    return getLabel();
	}
	else {
	    const char* c = IlvComboBox::check(sh);
	    return c;
	}
    }
    else {
	return getLabel();
    }
}

// --------------------------------------------------------------------------
IlDouble
ScaleCombo::getScale()
{
    const char* text = getLabel();
    if (strcmp(text, "No limit") != 0) {
	size_t len = strlen(text);

	char* buf = new char[len + 1];
	size_t ibuf = 0;
	for (size_t i=0; i < len; i++) {
	    if (isdigit(text[i])) {
		buf[ibuf] = text[i];
		ibuf++;
	    }
	}
	buf[ibuf] = 0;
	double scale = -1;
	if (ibuf != 0) {
	    scale = atof(buf);
	}
	if (buf) {
	    delete [] buf;
	}
	buf = 0;
	return scale;
    }
    return -1;
}
