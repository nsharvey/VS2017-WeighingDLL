// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/month/include/month.h
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

#ifndef __month__header__
#define __month__header__

#include <toolbar.h>
#include <utils.h>

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/grapher/links.h>
#include <ilviews/gadgets/stdialog.h>

IlvGraphic* CreateDoubleLinkGraphicModel(IlvDisplay* display);

// --------------------------------------------------------------------------
class MonthToolBar
    : public IlvGanttToolBar
{
public:
    MonthToolBar(IlvDisplay* display,
		 IlvGanttChart* gantt);
    ~MonthToolBar();
    IlUShort getLinkType();
    virtual void setCreateConstraint();
protected:
    IlvDialog* _dialog;
};

// ---------------------------------------------------------------------------
class DoubleLink
    : public IlvNDoubleLinkImage
{
public:
    DoubleLink(IlvDisplay* display,
	       IlBoolean  oriented,
	       IlvGraphic* from,
	       IlvGraphic* to,
	       IlvPalette* palette = 0)
	: IlvNDoubleLinkImage(display, oriented, from, to, palette) {};
    // ____________________________________________________________
    virtual void draw(IlvPort* dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual IlvPoint* getLinkPoints(IlvUInt& nPoints,
				    const IlvTransformer* t = 0) const;
    virtual void boundingBox(IlvRect& rect,
			     const IlvTransformer* t = 0) const;
    DeclareTypeInfoRO();
protected:
    virtual IlBoolean isDirect(const IlvTransformer* = 0) const
    { return IlFalse; }
};

// --------------------------------------------------------------------------
class AddLinkInteractor
    : public IlvGanttAddLinkInteractor
{
public:
    AddLinkInteractor(IlvGanttChart* gantt,
		      IlvManager* mgr,
		      IlvView* view,
		      IlvGanttLinkType type = IlvStartsAfterEnd,
		      IlBoolean oriented = IlTrue)
	: IlvGanttAddLinkInteractor(gantt, mgr, view, oriented)
    {_type = type;}
    // ____________________________________
    virtual IlvGanttLink* makeLink(IlvGanttNode* from,
				   IlvGanttNode* to);
protected:
    IlvGanttLinkType _type;
};
#endif /* !__month__header__*/
