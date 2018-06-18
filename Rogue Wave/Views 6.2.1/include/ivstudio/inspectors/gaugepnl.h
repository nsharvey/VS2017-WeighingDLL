// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/gaugepnl.h
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
// Declaration of the IlvStIGaugePanel classes
// Defined in studio inspectors library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Gaugepnl_H)
#define __IlvSt_Inspectors_Gaugepnl_H

#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#  include <ivstudio/inspectors/gadpnl.h>
#endif

class IlvGauge;

// --------------------------------------------------------------------------
// class IlvStIGaugePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGaugePanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIGaugePanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStIGaugePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeGaugePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIGaugePanel,
				 IlvStIGaugePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIRectangularGaugePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRectangularGaugePanel
    : public IlvStIGaugePanel
{
public:
    IlvStIRectangularGaugePanel(IlvDisplay*,
				const char*,
				const char* = 0,
				IlvSystemView = 0,
				IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIRectangularGaugePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeRectangularGaugePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIRectangularGaugePanel,
				 IlvStIRectangularGaugePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIReliefGaugePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIReliefGaugePanel
    : public IlvStIRectangularGaugePanel
{
public:
    IlvStIReliefGaugePanel(IlvDisplay*,
			   const char*,
			   const char* = 0,
			   IlvSystemView = 0,
			   IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIReliefGaugePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeReliefGaugePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIReliefGaugePanel,
				 IlvStIReliefGaugePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStISliderGaugePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISliderGaugePanel
: public IlvStIRectangularGaugePanel
{
public:
    IlvStISliderGaugePanel(IlvDisplay*,
			   const char*,
			   const char* = 0,
			   IlvSystemView = 0,
			   IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStISliderGaugePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeSliderGaugePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStISliderGaugePanel,
				 IlvStISliderGaugePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStICircularGaugePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICircularGaugePanel
    : public IlvStIGaugePanel
{
public:
    IlvStICircularGaugePanel(IlvDisplay*,
			     const char*,
			     const char* = 0,
			     IlvSystemView = 0,
			     IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStICircularGaugePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeCircularGaugePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStICircularGaugePanel,
				 IlvStICircularGaugePanelBuilder);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_gaugepnl)
#endif /* !__IlvSt_Inspectors_Gaugepnl_H */
