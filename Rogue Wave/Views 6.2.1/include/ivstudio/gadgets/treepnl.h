// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/treepnl.h
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
// Declaration of the IlvStItreeGadgetPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Treepnl_H)
#define __IlvSt_Gadgets_Treepnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif
#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif
#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Listedt_H)
#  include <ivstudio/inspectors/listedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Inspgadi_H)
#  include <ivstudio/inspectors/inspgadi.h>
#endif

class IlvTreeGadget;
class IlvTreeGadgetItemHolder;
class IlvTreeGadgetItem;

// --------------------------------------------------------------------------
// IlvStITreeGadgetItemValue class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreeGadgetItemValue
: public IlvStIGadgetItemValue
{
    IlvDeclareInspClassInfo();

public:
    IlvStITreeGadgetItemValue(IlvGadgetItem* gadgetItem = 0);
    IlvStITreeGadgetItemValue(const IlvStIGadgetItemValue&);

    virtual IlvStIProperty*	copy() const;
};

// --------------------------------------------------------------------------
// IlvStITreePropertyAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreePropertyAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStITreePropertyAccessor(IlvStIPropertyAccessor* = 0,
			       IlvStIAccessor::UpdateMode =
			       IlvStIAccessor::Inherited,
			       const char* = 0);

protected:
    IlvTreeGadget*		getTreeGadget() const;
};

// --------------------------------------------------------------------------
// IlvStITreeToolTipAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreeToolTipAccessor
    : public IlvStITreePropertyAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStITreeToolTipAccessor(IlvStIPropertyAccessor* = 0,
			      IlvStIAccessor::UpdateMode =
			      IlvStIAccessor::Inherited,
			      const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStITreeEditabilityAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreeEditabilityAccessor
    : public IlvStITreePropertyAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStITreeEditabilityAccessor(IlvStIPropertyAccessor* = 0,
			          IlvStIAccessor::UpdateMode =
				  IlvStIAccessor::Inherited,
			          const char* = 0);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStITreeGadgetItemHolderAccessor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreeGadgetItemHolderAccessor
    : public IlvStICombinedValueInterAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStITreeGadgetItemHolderAccessor(IlvStIPropertyAccessor* = 0,
				       IlvStIAccessor::UpdateMode =
				       IlvStIAccessor::Inherited,
				       const char* = 0);
    virtual ~IlvStITreeGadgetItemHolderAccessor();

    virtual IlvTreeGadgetItemHolder*	getTreeGadgetItemHolder() const;

protected:
    virtual IlvStIProperty*		getOriginalValue();
};

// --------------------------------------------------------------------------
// IlvStIGadgetItemTreeAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIGadgetItemTreeAccessor
    : public IlvStIPropertyTreeAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGadgetItemTreeAccessor(IlvStIPropertyAccessor* = 0,
			         IlvStIAccessor::UpdateMode =
				 IlvStIAccessor::Inherited,
				 const char* = 0,
				 IlvStIAccessor::BuildMode =
				 IlvStIAccessor::Copy);
    virtual ~IlvStIGadgetItemTreeAccessor();

    // ----------------------------------------------------------------------
    IlvTreeGadgetItemHolder*	getTreeGadgetItemHolder() const;
    IlvTreeGadget*		getTreeGadget() const;

protected:

    IlvTreeGadgetItem*	getGadgetItem(const IlvStIProperty*) const;
    IlvTreeGadgetItem*	getParentGadgetItem(const IlvStIProperty*) const;
    // ----------------------------------------------------------------------
    // Application

    virtual IlUInt	getChildPosition(const IlvStIProperty*,
					 const IlvStIProperty*) const;
    virtual void	addProperty(IlvStIProperty*,
				    const IlvStIProperty*,
				    IlUInt);
    virtual void	replaceProperty(IlvStIProperty*,
					IlvStIProperty*,
					const IlvStIProperty*,
					IlUInt);

    // ----------------------------------------------------------------------
    // Array of properties
    virtual IlvStIProperty**
	getInitialChildrenProperties(IlUInt&,
				     const IlvStIProperty* = 0) const;
    // ----------------------------------------------------------------------
    // Insertion of properties
    virtual IlvStIProperty*	createProperty(const IlvStIProperty*,
					       IlUInt,
					       IlAny = 0) const;

    // ----------------------------------------------------------------------
    // Destruction of properties
    virtual void	deleteNewProperty(IlvStIProperty*);
    virtual void	deleteProperty(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIGadgetItemTreeEditor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIGadgetItemTreeEditor
    : public IlvStIPropertyTreeEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGadgetItemTreeEditor(IlvStIPropertyAccessor* = 0,
			       const char* = 0,
			       IlvStIAccessor::UpdateMode =
			       IlvStIAccessor::Inherited);
    virtual ~IlvStIGadgetItemTreeEditor();

    // ----------------------------------------------------------------------
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;
};

// --------------------------------------------------------------------------
// class IlvStITreeGadgetItemEditor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreeGadgetItemEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();

public:
    IlvStITreeGadgetItemEditor(IlvStIPropertyAccessor* = 0,
			       const char* = 0,
			       IlvStIAccessor::UpdateMode =
			       IlvStIAccessor::Inherited);
    virtual ~IlvStITreeGadgetItemEditor();
};

// --------------------------------------------------------------------------
// IlvStITreeGadgetPanel class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITreeGadgetPanel
    : public IlvStIScrollGadgetInspectorPanel
{
public:
    IlvStITreeGadgetPanel(IlvDisplay*,
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
    IlvStITreeGadgetPanel(IlvManager*,
			  const char*,
			  const char*,
			  const char*,
			  const char*,
			  const char* = 0, // != 0, overloads data
			  IlvSystemView = 0,
			  IlvStIAccessor::UpdateMode
						  = IlvStIAccessor::OnApply);

    void		initializeTreeGadgetPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStITreeGadgetPanel,
				    IlvStITreeGadgetPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_treepnl)
#endif /* !__IlvSt_Gadgets_Treepnl_H */
