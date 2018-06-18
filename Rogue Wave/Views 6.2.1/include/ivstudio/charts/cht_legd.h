// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/cht_legd.h
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
// Declaration of the IlvStILegendAccessor class
// Defined in studio charts library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Charts_Cht_legd_H)
#define __IlvSt_Charts_Cht_legd_H

#if !defined(__IlvSt_Charts_Stchart_H)
#  include <ivstudio/charts/stchart.h>
#endif
#if !defined(__IlvSt_Inspectors_Graphpnl_H)
#  include <ivstudio/inspectors/graphpnl.h>
#endif

// --------------------------------------------------------------------------
// class IlvStILegendPanel
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStILegendPanel
    : public IlvStIShadowRectanglePanel
{
public:
    IlvStILegendPanel(IlvDisplay*,
		      const char*,
		      const char* = 0,
		      IlvSystemView = 0,
		      IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStILegendPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeLegendPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStILegendPanel,
				    IlvStILegendPanelBuilder,
				    ILVSTCHARTCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTCHARTCLASS(sti_cht_legd)
#endif /* !__IlvSt_Charts_Cht_legd_H */
