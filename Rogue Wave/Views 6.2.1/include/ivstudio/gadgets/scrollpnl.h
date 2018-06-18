// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/scrollpnl.h
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
// Declaration of the IlvStISliderPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Scrollpnl_H)
#define __IlvSt_Gadgets_Scrollpnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif

class IlvSlider;

// --------------------------------------------------------------------------
// IlvStISliderAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISliderAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStISliderAccessor(IlvStIPropertyAccessor* = 0,
			 IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			 const char* = 0);

protected:
    IlvSlider*		getSlider() const;
};

// --------------------------------------------------------------------------
// class IlvStISliderPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISliderPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStISliderPanel(IlvDisplay*,
		      const char*,
		      const char* = 0,
		      IlvSystemView = 0,
		      IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStISliderPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    IlvStISliderPanel(IlvManager*,
		      const char*,
		      const char*,
		      const char*,
		      const char*,
		      const char* = 0, // overloads data
		      IlvSystemView = 0,
		      IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);

    void		initializeSliderPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStISliderPanel,
				    IlvStISliderPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIScrollBarAccessor class
// --------------------------------------------------------------------------
class IlvScrollBar;

class ILVSTGADGETCLASS IlvStIScrollBarAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScrollBarAccessor(IlvStIPropertyAccessor* = 0,
			    IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			    const char* = 0);

protected:
    IlvScrollBar*	getScrollBar() const;
};

// --------------------------------------------------------------------------
// IlvStIScrollBarDefSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIScrollBarDefSizeAccessor
    : public IlvStIScrollBarAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScrollBarDefSizeAccessor(IlvStIPropertyAccessor* = 0,
			    	   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				   const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIScrollBarPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIScrollBarPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIScrollBarPanel(IlvDisplay*,
		         const char*,
		         const char* = 0,
		         IlvSystemView = 0,
		         IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIScrollBarPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeScrollBarPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIScrollBarPanel,
				    IlvStIScrollBarPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_scrollpnl)
#endif /* !__IlvSt_Gadgets_Scrollpnl_H */
