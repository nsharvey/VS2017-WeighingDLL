// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/lispanel.h
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
#if !defined(__IlvSt_Gadgets_Lispanel_H)
#define __IlvSt_Gadgets_Lispanel_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif

class IlvStringList;

// --------------------------------------------------------------------------
// IlvStIGraphicStateEditor class
class ILVSTGADGETCLASS IlvStIListSelectionModeEditor
    : public IlvStIListEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIListSelectionModeEditor(IlvStIPropertyAccessor* list,
				  const char* name = 0,
				  IlvStIPropertyAccessor* accessor = 0,
				  IlvStIEditor::NotificationMode mode =
				  IlvStIEditor::AsOwner)
    : IlvStIListEditor(name, accessor, mode)
    { _accOnList = list; }

    IlvStringList*		getStringList() const;

    virtual IlBoolean		apply();

protected:
    virtual void		fillListGadget();
    virtual void		translate(IlvStIProperty*, IlBoolean);

    IlvStIPropertyAccessor*	_accOnList;
};

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIListPanel
    : public IlvStIScrollGadgetInspectorPanel
{
public:
    IlvStIListPanel(IlvDisplay*,
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
    void		initializeListPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIListPanel,
				    IlvStIListPanelBuilder,
				    ILVSTGADGETCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_lispanel)
#endif /* !__IlvSt_Gadgets_Lispanel_H */
