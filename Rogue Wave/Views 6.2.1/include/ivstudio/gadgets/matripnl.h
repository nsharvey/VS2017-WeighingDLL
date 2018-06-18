// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/matripnl.h
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
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Matripnl_H)
#define __IlvSt_Gadgets_Matripnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#include <ivstudio/gadgets/inspscgt.h>
#endif

class IlvMatrix;
class IlvStIProxyListGadget;

// --------------------------------------------------------------------------
// IlvStIMatrixAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMatrixAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMatrixAccessor(IlvStIPropertyAccessor* = 0,
			 IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			 const char* = 0);

protected:
    IlvMatrix*		getMatrix()const;
};

// --------------------------------------------------------------------------
// IlvStINumberOfColumnsMatrixAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStINumberOfColumnsMatrixAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStINumberOfColumnsMatrixAccessor(IlvStIPropertyAccessor* = 0,
			    	        IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
					const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStINumberOfRowsMatrixAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStINumberOfRowsMatrixAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStINumberOfRowsMatrixAccessor(IlvStIPropertyAccessor* = 0,
			   	     IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				     const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIFirstColumnMatrixAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIFirstColumnMatrixAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIFirstColumnMatrixAccessor(IlvStIPropertyAccessor* = 0,
				    IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				    const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIFirstRowMatrixAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIFirstRowMatrixAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIFirstRowMatrixAccessor(IlvStIPropertyAccessor* = 0,
				 IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				 const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIXMatrixGridAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIXMatrixGridAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIXMatrixGridAccessor(IlvStIPropertyAccessor* = 0,
			      IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			      const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIYMatrixGridAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIYMatrixGridAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIYMatrixGridAccessor(IlvStIPropertyAccessor* = 0,
			      IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			      const char* = 0);

protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMatrixSelectionModeAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMatrixSelectionModeAccessor
    : public IlvStIMatrixAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIMatrixSelectionModeAccessor(IlvStIPropertyAccessor* = 0,
			              IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			              const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMatrixPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIMatrixPanel
    : public IlvStIScrollGadgetInspectorPanel
{
public:
    IlvStIMatrixPanel(IlvDisplay*,
		      const char*,
		      const char* = 0,
		      IlvSystemView = 0,
		      IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeMatrixPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIMatrixPanel,
				    IlvStIMatrixPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStISheetPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISheetPanel
    : public IlvStIMatrixPanel
{
public:
    IlvStISheetPanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeSheetPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStISheetPanel,
				    IlvStISheetPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIHierarchicalSheetPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIHierarchicalSheetPanel
    : public IlvStISheetPanel
{
public:
    IlvStIHierarchicalSheetPanel(IlvDisplay*,
				 const char*,
				 const char* = 0,
				 IlvSystemView = 0,
				 IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeHierarchicalSheetPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIHierarchicalSheetPanel,
				    IlvStIHierarchicalSheetPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// Exported functions
ILVSTGADGETEXPORTEDFUNC(void)
IlvStIFillDirections(IlvStIProxyListGadget&, IlAny);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_matripnl)
#endif /* !__IlvSt_Gadgets_Matripnl_H */
