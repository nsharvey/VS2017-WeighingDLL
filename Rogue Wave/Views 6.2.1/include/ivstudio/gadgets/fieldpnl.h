// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/fieldpnl.h
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
#if !defined(__IlvSt_Gadgets_Fieldpnl_H)
#define __IlvSt_Gadgets_Fieldpnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif

class IlvDateField;

// --------------------------------------------------------------------------
// IlvStITextFieldPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITextFieldPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStITextFieldPanel(IlvDisplay*,
		         const char*,
		         const char* = 0,
		         IlvSystemView = 0,
		         IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStITextFieldPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeTextFieldPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStITextFieldPanel,
				    IlvStITextFieldPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStINumberFieldPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStINumberFieldPanel
    : public IlvStITextFieldPanel
{
public:
    IlvStINumberFieldPanel(IlvDisplay*,
			   const char*,
			   const char* = 0,
			   IlvSystemView = 0,
			   IlvStIAccessor::UpdateMode =
			   IlvStIAccessor::OnApply);
    virtual ~IlvStINumberFieldPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeNumberPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStINumberFieldPanel,
				    IlvStINumberFieldPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIDateFieldAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIDateFieldAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvStIDateFieldAccessor(IlvStIPropertyAccessor* accessor = 0,
			    IlvStIAccessor::UpdateMode mode =
			    IlvStIAccessor::Inherited,
			    const char* name = 0)
    : IlvStICombinedAccessor(accessor, mode, IlvStIAccessor::None, name)
    {}

protected:
    IlvDateField*	getDateField()const;
};

// --------------------------------------------------------------------------
// IlvStIDateFormatAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIDateFormatAccessor
    : public IlvStIDateFieldAccessor
{
public:
    IlvStIDateFormatAccessor(IlvStIPropertyAccessor* accessor = 0,
			     IlvStIAccessor::UpdateMode mode =
			     IlvStIAccessor::Inherited,
			     const char* name = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIDateValueAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIDateValueAccessor : public IlvStIDateFieldAccessor
{
public:
    IlvStIDateValueAccessor(IlvStIPropertyAccessor* accessor = 0,
			    IlvStIAccessor::UpdateMode mode=
			    IlvStIAccessor::Inherited,
			    const char* name = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIDateFieldPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIDateFieldPanel
    : public IlvStITextFieldPanel
{
public:
    IlvStIDateFieldPanel(IlvDisplay*,
			 const char*,
			 const char* = 0,
			 IlvSystemView = 0,
			 IlvStIAccessor::UpdateMode =
			 IlvStIAccessor::OnApply);
    virtual ~IlvStIDateFieldPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeDatePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIDateFieldPanel,
				    IlvStIDateFieldPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
// IlvStIPasswordFieldPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIPasswordFieldPanel
    : public IlvStITextFieldPanel
{
public:
    IlvStIPasswordFieldPanel(IlvDisplay*,
			     const char*,
			     const char* = 0,
			     IlvSystemView = 0,
			     IlvStIAccessor::UpdateMode =
			     IlvStIAccessor::OnApply);
    virtual ~IlvStIPasswordFieldPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    IlvStIPasswordFieldPanel(IlvManager*,
			     const char*,
			     const char*,
			     const char*,
			     const char*,
			     const char* = 0, // overloads data
			     IlvSystemView = 0,
			     IlvStIAccessor::UpdateMode =
			     IlvStIAccessor::OnApply);

    void		initializePasswordFieldPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIPasswordFieldPanel,
				    IlvStIPasswordFieldPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_fieldpnl)
#endif /* !__IlvSt_Gadgets_Fieldpnl_H */
