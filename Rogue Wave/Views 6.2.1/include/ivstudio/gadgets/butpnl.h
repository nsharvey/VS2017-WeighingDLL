// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/butpnl.h
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
// Declaration of the IlvStIButtonPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Butpnl_H)
#define __IlvSt_Gadgets_Butpnl_H

#if !defined(__IlvSt_Gadgets_Msgpnl_H)
#  include <ivstudio/gadgets/msgpnl.h>
#endif

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIButtonPanel
: public IlvStIMsgLabelPanel
{
public:
    IlvStIButtonPanel(IlvDisplay*,
		      const char*,
		      const char* = 0,
		      IlvSystemView = 0,
		      IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStIButtonPanel();
    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		intializeButtonPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIButtonPanel,
				    IlvStIButtonPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStITogglePanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITogglePanel
: public IlvStIGadgetInspectorPanel
{
public:
    IlvStITogglePanel(IlvDisplay*,
		      const char*,
		      const char* = 0,
		      IlvSystemView = 0,
		      IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStITogglePanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeTogglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStITogglePanel,
				    IlvStITogglePanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIColoredTogglePanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIColoredTogglePanel
: public IlvStITogglePanel
{
public:
    IlvStIColoredTogglePanel(IlvDisplay*,
			     const char*,
			     const char* = 0,
			     IlvSystemView = 0,
			     IlvStIAccessor::UpdateMode =
			     IlvStIAccessor::OnApply);
    virtual ~IlvStIColoredTogglePanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeColoredTogglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIColoredTogglePanel,
				    IlvStIColoredTogglePanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIFramePanel
: public IlvStIMsgLabelPanel
{
public:
    IlvStIFramePanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    ~IlvStIFramePanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		intializeFramePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIFramePanel,
				    IlvStIFramePanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_butpnl)
#endif /* !__IlvSt_Gadgets_Butpnl_H */
