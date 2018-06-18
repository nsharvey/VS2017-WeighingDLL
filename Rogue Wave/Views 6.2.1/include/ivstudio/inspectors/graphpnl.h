// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/graphpnl.h
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
// Declaration of inspector panels classes of common graphics classes
// Defined in studio inspectors library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Graphpnl_H)
#define __IlvSt_Inspectors_Graphpnl_H

#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#include <ivstudio/inspectors/gadpnl.h>
#endif

// --------------------------------------------------------------------------
// class IlvStIRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRectanglePanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIRectanglePanel(IlvDisplay*,
			 const char*   title,
			 const char*   filename = 0,
			 IlvSystemView transientFor = 0,
			 IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIRectanglePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIRectanglePanel,
				 IlvStIRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIRoundRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRoundRectanglePanel
: public IlvStIRectanglePanel
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIRoundRectanglePanel(IlvDisplay*,
			      const char*   title,
			      const char*   filename = 0,
			      IlvSystemView transientFor = 0,
			      IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::OnApply);
    virtual ~IlvStIRoundRectanglePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeRoundRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIRoundRectanglePanel,
				 IlvStIRoundRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIShadowRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIShadowRectanglePanel
: public IlvStIRectanglePanel
{
public:
    IlvStIShadowRectanglePanel(IlvDisplay*,
			       const char*,
			       const char* = 0,
			       IlvSystemView = 0,
			       IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIShadowRectanglePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeShadowRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIShadowRectanglePanel,
				 IlvStIShadowRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIShadowLabelPanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIShadowLabelPanel
    : public IlvStIRectanglePanel
{
public:
    IlvStIShadowLabelPanel(IlvDisplay*,
			   const char*,
			   const char* = 0,
			   IlvSystemView = 0,
			   IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIShadowLabelPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeShadowLabelPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIShadowLabelPanel,
				 IlvStIShadowLabelPanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIFilledRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIFilledRectanglePanel
    : public IlvStIRectanglePanel
{
public:
    IlvStIFilledRectanglePanel(IlvDisplay*,
			       const char*,
			       const char* = 0,
			       IlvSystemView = 0,
			       IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIFilledRectanglePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeFilledRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIFilledRectanglePanel,
				 IlvStIFilledRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIFilledRoundRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIFilledRoundRectanglePanel
    : public IlvStIFilledRectanglePanel
{
public:
    IlvStIFilledRoundRectanglePanel(IlvDisplay*,
				    const char*,
				    const char* = 0,
				    IlvSystemView = 0,
				    IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIFilledRoundRectanglePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeFilledRoundRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIFilledRoundRectanglePanel,
				 IlvStIFilledRoundRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIEllipsePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIEllipsePanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIEllipsePanel(IlvDisplay*,
		       const char*,
		       const char* = 0,
		       IlvSystemView = 0,
		       IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStIEllipsePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeEllipsePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIEllipsePanel,
				 IlvStIEllipsePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIFilledEllipsePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIFilledEllipsePanel
    : public IlvStIEllipsePanel
{
public:
    IlvStIFilledEllipsePanel(IlvDisplay*,
			     const char*,
			     const char* = 0,
			     IlvSystemView = 0,
			     IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIFilledEllipsePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeFilledEllipsePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIFilledEllipsePanel,
				 IlvStIFilledEllipsePanelBuilder);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_graphpnl)
#endif /* !__IlvSt_Inspectors_Graphpnl_H */
