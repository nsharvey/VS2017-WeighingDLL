// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/labelpnl.h
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
// Declaration of the IlvListPanel class
// Defined in studio inspectors library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Labelpnl_H)
#define __IlvSt_Inspectors_Labelpnl_H

#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#  include <ivstudio/inspectors/gadpnl.h>
#endif

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStILabelPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStILabelPanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStILabelPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void initializeLabelPanel();
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIReliefLabelPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIReliefLabelPanel(IlvDisplay*,
			   const char*,
			   const char* = 0,
			   IlvSystemView = 0,
			   IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIReliefLabelPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeLabelPanel();
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIListLabelPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIListLabelPanel(IlvDisplay*,
			 const char*,
			 const char* = 0,
			 IlvSystemView = 0,
			 IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIListLabelPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeListLabelPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStILabelPanel,
				 IlvStILabelPanelBuilder);

IlvStDefineInspectorPanelBuilder(IlvStIReliefLabelPanel,
				 IlvStIReliefLabelPanelBuilder);

IlvStDefineInspectorPanelBuilder(IlvStIListLabelPanel,
				 IlvStIListLabelPanelBuilder);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_labelpnl)
#endif /* !__IlvSt_Inspectors_Labelpnl_H */
