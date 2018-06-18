// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/common/src/tooltip.cpp
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
// Provides tooltips to Gantt Charts nodes
// --------------------------------------------------------------------------
#include <tooltip.h>

#if defined(IL_STD)
#  include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#  include <stdio.h>
#endif /* IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
void
IlvGanttSubNodeToolTip::boundingBox(IlvRect& bbox,
				    IlvDisplay* display) const
{
    char buffer[128];
    IlvGanttNode* node = _subnode->getNode();
    sprintf(buffer, "%s\n______________________________\n\n"
	    "Start [min: %d, max: %d]\nEnd [min: %d, max: %d]", 
	    node->getName(),
	    _subnode->getStartMin(),
	    _subnode->getStartMax(),
	    _subnode->getEndMin(),
	    _subnode->getEndMax());
    IL_CONSTCAST(IlvGanttSubNodeToolTip*, this)->setLabel(buffer);
    IlvToolTip::boundingBox(bbox, display);
}
