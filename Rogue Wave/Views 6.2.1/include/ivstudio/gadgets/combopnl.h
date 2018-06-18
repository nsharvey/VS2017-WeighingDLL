// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/combopnl.h
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
// Declaration of the IlvStIComboPanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Combopnl_H)
#define __IlvSt_Gadgets_Combopnl_H

#if !defined(__IlvSt_Gadgets_InspScGt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif

// --------------------------------------------------------------------------
// IlvStIComboPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIComboPanel
: public IlvStIGadgetInspectorPanel
{
public:
    IlvStIComboPanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStIComboPanel();

    // ----------------------------------------------------------------------
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeComboPanel();
    virtual IlBoolean	isUsingMenuItems() const;
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIComboPanel,
				    IlvStIComboPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIScrolledComboPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIScrolledComboPanel
: public IlvStIComboPanel
{
public:
    IlvStIScrolledComboPanel(IlvDisplay*,
			     const char*,
			     const char* = 0,
			     IlvSystemView = 0,
			     IlvStIAccessor::UpdateMode =
				    IlvStIAccessor::OnApply);
    virtual ~IlvStIScrolledComboPanel();

    // ----------------------------------------------------------------------
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeScrolledComboPanel();
    virtual IlBoolean isUsingMenuItems()const { return IlFalse; }
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIScrolledComboPanel,
				    IlvStIScrolledComboPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIOptionMenuPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIOptionMenuPanel
: public IlvStIGadgetInspectorPanel
{
public:
    IlvStIOptionMenuPanel(IlvDisplay*,
			  const char*,
			  const char* = 0,
			  IlvSystemView = 0,
			  IlvStIAccessor::UpdateMode =
				IlvStIAccessor::OnApply);
    virtual ~IlvStIOptionMenuPanel();

    // ----------------------------------------------------------------------
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeOptionMenuPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIOptionMenuPanel,
				    IlvStIOptionMenuPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_combopnl)
#endif /* !__IlvSt_Gadgets_Combopnl_H */
