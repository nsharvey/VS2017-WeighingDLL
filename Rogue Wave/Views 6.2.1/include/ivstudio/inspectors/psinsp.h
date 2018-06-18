// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/psinsp.h
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
// Declaration of the IlvStpsPropertyInspector class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Psinsp_H
#define __IlvSt_Inspectors_Psinsp_H

#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif
#if !defined(__IlvSt_Inspectors_Insppnl_H)
#  include <ivstudio/inspectors/insppnl.h>
#endif
#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif

class IlvHierarchicalSheet;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsPropertyInspector
    : public IlvStIExternalEditor
{
public:
    IlvStpsPropertyInspector(IlvStIPropertyAccessor*, const char* = 0,
			     NotificationMode = AsOwner);

    virtual IlBoolean initialize();
    virtual IlBoolean apply();

    virtual IlBoolean connectHolder(IlvGraphicHolder*);

    void propertiesModified();

protected:
    IlvGraphic* getGraphic() const;
    IlvHierarchicalSheet* _hsheet;
};


// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsPropertyInspectorPanel
    : public IlvStInspectorPanel
{
 public:
  IlvStpsPropertyInspectorPanel(IlvDisplay*,
				const char*,
				const char* = 0,
				IlvSystemView = 0,
				IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
  // ----------------------------------------------------------------------
  virtual void initializeEditors();
};

IlvStDefineInspectorPanelBuilder(IlvStpsPropertyInspectorPanel,
				 IlvStpsPropertyInspectorPanelBuilder);

#endif /* !__IlvSt_Inspectors_Psinsp_H */
