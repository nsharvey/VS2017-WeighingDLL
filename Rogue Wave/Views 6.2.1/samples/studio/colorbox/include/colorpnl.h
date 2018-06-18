// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/colorbox/include/colorpnl.h
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
// Declaration of the IlvColorInspectorPanel class
// --------------------------------------------------------------------------

#ifndef __Ilv_ColorComboBoxInspectorH
#define __Ilv_ColorComboBoxInspectorH

#include <ilviews/graphics/rectangl.h>
#include <ivstudio/gadgets/inspscgt.h>

#if !defined(__IlvSt_Listacc_H)
#include <ivstudio/inspectors/listacc.h>
#endif

#if !defined(__IlvSt_Listedt_H)
#include <ivstudio/inspectors/listedt.h>
#endif

// --------------------------------------------------------------------------
// IlvColorInspectorPanel class
// --------------------------------------------------------------------------
class IlvColorInspectorPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvColorInspectorPanel(IlvDisplay* display,
			   const char*   title,
			   const char*   filename = 0,
			   IlvSystemView transientFor = 0,
			   IlvStIAccessor::UpdateMode =
			      IlvStIAccessor::OnApply);
    // ----------------------------------------------------------------------
    virtual void initializeEditors();

protected:
    void initializeColorPanel();
    IlvColorDrawInfo _drawInfo;
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvColorInspectorPanel,
				    IlvColorInspectorPanelBuilder,
				    IL_EMPTYMACRO);

// --------------------------------------------------------------------------
// IlvColorGadgetItemHolderAccessor
// --------------------------------------------------------------------------
class IlvColorGadgetItemHolderAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvColorGadgetItemHolderAccessor(IlvStIPropertyAccessor* accessor = 0,
				     UpdateMode updateMode = NoUpdate,
				     BuildMode buildMode = None,
				     const char* name = 0);

protected:
    virtual IlvStIProperty* getOriginalValue();
};

// --------------------------------------------------------------------------
// IlvColorItemsAccessor class
// --------------------------------------------------------------------------
class IlvColorItemsAccessor
    : public IlvStIPropertyListAccessor
{
public:
    IlvColorItemsAccessor(IlvStIPropertyAccessor* accessor = 0,
		          IlvStIAccessor::UpdateMode =
					IlvStIAccessor::Inherited,
			  const char* name = 0);
    virtual ~IlvColorItemsAccessor();

    // ----------------------------------------------------------------------
    // Main overridables
    IlvListGadgetItemHolder* getListGadgetItemHolder()const;

protected:
    IlvGadgetItem* getGadgetItem(const IlvStIProperty*)const;

    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual IlvStIProperty*  createDefaultProperty()const;

    virtual void addProperty(IlvStIProperty*, IlUInt);
    // Default implementation calls _lstAccessor->copyProperty()
    virtual IlvStIProperty* copyProperty(const IlvStIProperty* property);
    virtual void deleteNewProperty(IlvStIProperty* property);
    virtual void deleteProperty(IlvStIProperty* property, IlUInt index);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty, IlUInt);
    virtual void moveProperty(IlvStIProperty* property,
			      IlUInt previousIndex, IlUInt newIndex);
};

// --------------------------------------------------------------------------
// IlvGadgetItemColorAccessor
// --------------------------------------------------------------------------
class IlvGadgetItemColorAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvGadgetItemColorAccessor(IlvStIPropertyAccessor* accessor = 0,
			       UpdateMode = NoUpdate,
			       BuildMode = None,
			       const char* name = 0);
    virtual ~IlvGadgetItemColorAccessor();

protected:
    IlvGadgetItem* getGadgetItem()const;
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvColorListEditor
// --------------------------------------------------------------------------

class IlvColorListEditor
    : public IlvStIPropertyListEditor
{
public:
    IlvColorListEditor(IlvStIPropertyListAccessor* accessor = 0,
		       const char* name = 0);
    virtual ~IlvColorListEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean  connectHolder(IlvGraphicHolder*);

protected:
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*)const;
};

// --------------------------------------------------------------------------
#endif /* __Ilv_ColorComboBoxInspectorH */
