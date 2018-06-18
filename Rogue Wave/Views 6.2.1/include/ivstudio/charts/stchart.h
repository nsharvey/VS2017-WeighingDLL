// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/stchart.h
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
// Macro definition for the Studio Charts extension
// --------------------------------------------------------------------------

#ifndef __IlvSt_Charts_Stchart_H
#define __IlvSt_Charts_Stchart_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVSTCHARTLIB)
#define ILVSTCHARTEXPORTEDDEF ILVBASEEXPORTED
#define ILVSTCHARTEXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTCHARTEXPORTEDDEF ILVBASEIMPORTED
#define ILVSTCHARTEXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTCHARTCLASS ILVSTCHARTEXPORTEDDEF
#define ILVSTCHARTEXPORTEDVAR(type) ILVSTCHARTEXPORTEDDEF type
#define IlvDECLAREINITSTCHARTCLASS(m) IL_MODULEINIT(m, ILVSTCHARTCLASS);

#if defined(IlvStDefineInspectorPanelBuilderExp)
#undef IlvStDefineInspectorPanelBuilderExp
#endif

#define IlvStDefineInspectorPanelBuilderExp(inspectorPanelClassname, \
					    inspectorPanelBuilderClassname, \
					    exportMacro ) \
class exportMacro inspectorPanelBuilderClassname: \
public IlvStInspectorPanelBuilder \
{ \
public: \
    virtual IlvStInspectorPanel* create(IlvDisplay* display, \
				        const char* classname, \
					IlvSystemView transientFor = 0, \
					IlvStIAccessor::UpdateMode mode = \
						IlvStIAccessor::OnApply) \
    { \
	return new inspectorPanelClassname(display, classname + 3, \
					   0, transientFor, mode); \
    } \
};

#endif /* !__IlvSt_Charts_Stchart_H */
