// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/txtpanel.h
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
// Declaration of the IlvStITextPanel class
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Txtpanel_H)
#define __IlvSt_Gadgets_Txtpanel_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif
#if !defined(__Ilv_Gadgets_Text_H)
#  include <ilviews/gadgets/text.h>
#endif

// --------------------------------------------------------------------------
// class IlvStITextPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStITextPanel
    : public IlvStIScrollGadgetInspectorPanel
{
public:
    IlvStITextPanel(IlvDisplay*,
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
    void initializeTextPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStITextPanel,
				    IlvStITextPanelBuilder,
				    ILVSTGADGETCLASS);
#endif /* !__IlvSt_Gadgets_Txtpanel_H */
