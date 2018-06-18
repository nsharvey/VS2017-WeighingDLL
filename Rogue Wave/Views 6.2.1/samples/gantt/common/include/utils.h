// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/common/include/utils.h
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

#ifndef __gantt_utils__header__
#define __gantt_utils__header__

#include <ilviews/gantt/gantt.h>

// --------------------------------------------------------------------------
void RegisterGanttNameProperty(IlvGraphic* graphic);
void OnGanttObjectNameChanged(IlvGanttAbstractObject* object,
			      IlvGraphic*	      graphic,
			      IlvGanttObjectType      type,
			      IlAny		      index);
void  AppendGanttDataPath(IlvDisplay* display);
void ILVCALLBACK Quit(IlvView* view,
		      IlAny);
void PopulateGanttChart(IlvGanttChart* gantt);
void PopulateGanttChart(IlvGanttChart* gantt,
			IlInt start,
			IlInt end,
			IlInt min);
IlvGraphic* CreateSubNodeGraphicModel(IlvDisplay* display);
IlvGraphic* CreateBreakGraphicModel(IlvDisplay* display);
IlvGraphic* CreateLineGraphicModel(IlvDisplay* display);
IlvGraphic* CreateLinkGraphicModel(IlvDisplay* display);

#endif /* !__gantt_utils__header__*/
