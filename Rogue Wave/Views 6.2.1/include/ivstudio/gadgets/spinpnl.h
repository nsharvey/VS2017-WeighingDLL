// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/spinpnl.h
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
// Declaration of the IlvStISpinboxPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Spinpnl_H)
#define __IlvSt_Gadgets_Spinpnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif

class IlvSpinBox;
class IlvTextField;
class IlvStISpinboxPanel;

// --------------------------------------------------------------------------
// class IlvStISpinObjectsAccessor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISpinObjectsAccessor
    : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStISpinObjectsAccessor(IlvStIPropertyAccessor* accessor = 0,
			      IlvStISpinboxPanel* panel = 0,
			      const char* name = 0);
    virtual ~IlvStISpinObjectsAccessor();

    // ----------------------------------------------------------------------
    // Main overridable
    IlvSpinBox* getSpinBox()const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;

protected:
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createProperty(IlUInt, IlAny) const;

    // calls property->copy() by default
    virtual IlvStIProperty*	copyProperty(const IlvStIProperty*);
    virtual void		addProperty(IlvStIProperty*, IlUInt);
    virtual void		deleteNewProperty(IlvStIProperty*);
    virtual void		deleteProperty(IlvStIProperty*, IlUInt);
    virtual void		replaceProperty(IlvStIProperty*,
						IlvStIProperty*, IlUInt);
    virtual void		moveProperty(IlvStIProperty*,
					     IlUInt, IlUInt);

    IlvGraphic*			addSpinGraphic(IlvSpinBox*, IlvSpinBox*,
					       IlvGraphic*,
					       IlUShort = (IlUShort)-1);
    IlvSpinBox*			getSpinBoxCopy() const;
    IlvStISpinboxPanel*		_panel;
};

// --------------------------------------------------------------------------
// IlvStISpinObjectAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISpinObjectAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStISpinObjectAccessor(IlvStIPropertyAccessor* = 0,
			     IlvStISpinboxPanel* = 0,
			     IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			     IlvStIAccessor::BuildMode =
							IlvStIAccessor::None,
			     const char* = 0);

protected:
    IlvStISpinboxPanel*	_panel;

    IlvGraphic*		getGraphic() const;
    IlvSpinBox*		getReferenceSpin() const;
};

// --------------------------------------------------------------------------
// IlvStISpinIncrementAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISpinIncrementAccessor
    : public IlvStISpinObjectAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStISpinIncrementAccessor(IlvStIPropertyAccessor* = 0,
			        IlvStISpinboxPanel* = 0,
			        IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			        const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStISpinLoopAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISpinLoopAccessor
    : public IlvStISpinObjectAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStISpinLoopAccessor(IlvStIPropertyAccessor* = 0,
			   IlvStISpinboxPanel* = 0,
			   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			   const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStISpinLabelsAccessor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISpinLabelsAccessor
    : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStISpinLabelsAccessor(IlvStIPropertyAccessor* = 0,
			     IlvStISpinboxPanel* = 0,
		             IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			     IlvStIAccessor::BuildMode =
							IlvStIAccessor::None,
			     const char* = 0);
    virtual ~IlvStISpinLabelsAccessor();

protected:
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createDefaultProperty() const;
    virtual void		moveProperty(IlvStIProperty*,
					     IlUInt, IlUInt);

    IlBoolean			applyNodes(IlUInt);

    IlvTextField*		getTextField()const;
    IlvSpinBox*			getReferenceSpin()const;
    IlvStISpinboxPanel*		_panel;
};

// --------------------------------------------------------------------------
// class IlvStISpinboxPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStISpinboxPanel
: public IlvStIGadgetInspectorPanel
{
public:
    IlvStISpinboxPanel(IlvDisplay*,
		       const char*,
		       const char* = 0,
		       IlvSystemView = 0,
		       IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStISpinboxPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

    inline IlvSpinBox*	getSpinBoxCopy() const { return _spinboxCopy; }

protected:
    void		initializeSpinBoxPanel();

    IlvSpinBox*		_spinboxCopy;
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStISpinboxPanel,
				    IlvStISpinboxPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_spinpnl)
#endif /* !__IlvSt_Gadgets_Spinpnl_H */
