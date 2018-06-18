// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/common/include/toolbar.h
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

#ifndef __gantt_toolbar__header__
#define __gantt_toolbar__header__

#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gantt/gantt.h>

// --------------------------------------------------------------------------
class IlvGanttToolBar
    : public IlvToolBar 
{
public:
    IlvGanttToolBar(IlvDisplay* display,
		    IlvGanttChart* gantt);
    virtual void setHolder(IlvGraphicHolder* holder);
    IlvGanttChart* getGanttChart() const { return _gantt; };

    void setCreateActivity();
    void setCreateBreak();
    virtual void setCreateConstraint();
    void setDragAndDrop();
    void setSelect();
    void setBorder();
    void setPan();
    void createRow();
    void deleteRow();
    void setSubNodeGraphicModel();
    void setColor();
protected:
    void removeAllInteractors();
    IlvGanttChart* _gantt;
};

#endif /* !__gantt_toolbar__header__*/
