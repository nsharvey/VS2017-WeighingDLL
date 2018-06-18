// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/inspscgt.h
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
// Declaration of the IlvStIScrollGadgetInspectorPanel class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Gadgets_Inspscgt_H
#define __IlvSt_Gadgets_Inspscgt_H

#if !defined(__IlvSt_Inspectors_Insppnl_H)
#  include <ivstudio/inspectors/insppnl.h>
#endif
#if !defined(__IlvSt_Inspectors_Inspvali_H)
#  include <ivstudio/inspectors/inspvali.h>
#endif
#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#include <ivstudio/inspectors/gadpnl.h>
#endif

class IlvManager;
class IlvScrolledGadget;
class IlvStINameChecker;
class IlvStIGraphicInteractorsInfos;
class IlvStICallbackInfos;
class IlvStINameInfos;

// --------------------------------------------------------------------------
// IlvStIScrollGadgetAccessor class
// --------------------------------------------------------------------------
class IlvStIScrollGadgetAccessor
: public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScrollGadgetAccessor(IlBoolean horizontal = IlFalse,
			       IlvStIPropertyAccessor* accessor = 0,
			       IlvStIAccessor::UpdateMode updateMode =
			       IlvStIAccessor::Inherited,
			       const char* name = 0)
    : IlvStICombinedAccessor(accessor,
			     updateMode,
			     IlvStIAccessor::None,
			     name),
      _horizontal(horizontal)
    {}

    IlvScrolledGadget*		getScrolledGadget();

protected:
    IlBoolean			_horizontal;

    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIScrollGadgetEditor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIScrollGadgetEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();

public:
    IlvStIScrollGadgetEditor(IlvStIPropertyAccessor* gadgetAccessor = 0,
			     IlvStIEditor::NotificationMode mode =
			     IlvStIEditor::AsOwner,
			     const char* name = 0);
    virtual ~IlvStIScrollGadgetEditor();

    // ----------------------------------------------------------------------
    // Editor / accessor names
    static const char*	_VerticalScrollbarEditorName;
    static const char*	_VerticalScrollbarAccessorName;
    static const char*	_VerticalScrollbarPosEditorName;
    static const char*	_HorizontalScrollbarEditorName;
    static const char*	_HorizontalScrollbarAccessorName;
    static const char*	_HorizontalScrollbarPosEditorName;
    static const char*	_LeftMarginEditorName;
    static const char*	_RightMarginEditorName;
    static const char*	_TopMarginEditorName;
    static const char*	_BottomMarginEditorName;
    static const char*	_ShowFrameEditorName;
};

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIScrollGadgetInspectorPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIScrollGadgetInspectorPanel(IlvDisplay*	display,
				     const char*	title,
				     const char*	filename = 0,
				     IlvSystemView	transientFor = 0,
				     IlvStIAccessor::UpdateMode =
				     IlvStIAccessor::OnApply);
    virtual ~IlvStIScrollGadgetInspectorPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

    // ----------------------------------------------------------------------
    // Editor / accessor names
    static const char*	_ScrollbarEditorName;

protected:
    void		initializeScrollGadgetPage();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIScrollGadgetInspectorPanel,
				    IlvStIScrollGadgetInspectorPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
ILVSTGADGETEXPORTEDFUNC(IlBoolean)
IlvStITranslatorScrollPosCallback(IlvStIProperty* property,
				  IlvValue& value,
				  IlBoolean bInput,
				  IlAny bHoriz);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_inspscgt)
#endif /* !__IlvSt_Gadgets_Inspscgt_H */
