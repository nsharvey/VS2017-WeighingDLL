// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/common/include/tooltip.h
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
//
// --------------------------------------------------------------------------

#ifndef __gantt_tooltip__header__
#define __gantt_tooltip__header__

#include <ilviews/gantt/gantt.h>
#include <ilviews/graphics/tooltip.h>

class IlvGanttSubNodeToolTip
    : public IlvToolTip
{
public:
    IlvGanttSubNodeToolTip(IlvGanttSubNode* subnode)
        : IlvToolTip(0),
	  _subnode(subnode)
    {}
    void boundingBox(IlvRect& bbox,
		     IlvDisplay* display) const;
protected:
    IlvGanttSubNode* _subnode;
};

#endif /* !__gantt_tooltip__header__*/
