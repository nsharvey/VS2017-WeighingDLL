// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/iconpnl.h
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
// Declaration of the IlvStIIconPanel class
// Defined in studio inspectors library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Iconpnl_H)
#define __IlvSt_Inspectors_Iconpnl_H

#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#  include <ivstudio/inspectors/gadpnl.h>
#endif
#if !defined(__IlvSt_Inspectors_Inspvali_H)
#  include <ivstudio/inspectors/inspvali.h>
#endif
#if !defined(__Ilv_Bitmaps_Filters_All_H)
#include <ilviews/bitmaps/filters/all.h>
#endif

class IlvIcon;

// --------------------------------------------------------------------------
// class IlvStIIconPanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIIconPanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIIconPanel(IlvDisplay*,
		    const char*,
		    const char* = 0,
		    IlvSystemView = 0,
		    IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStIIconPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void initializeIconPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIIconPanel,
				 IlvStIIconPanelBuilder);

// --------------------------------------------------------------------------
// IlvStIIconPathValidator class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIIconPathValidator
    : public IlvStIPathValidator
{
    IlvDeclareInspClassInfo();
public:
    IlvStIIconPathValidator(IlvDisplay*,
			    IlBoolean  = IlFalse,
			    const char* = "&invalidFileName",
		            IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
protected:
    virtual IlvStIError*	checkPath(const char*) const;
};

// --------------------------------------------------------------------------
// class IlvStIFilteredGraphicPanel
// --------------------------------------------------------------------------
class IlvFileBrowser;
class IlvTreeGadgetItem;

class ILVINSPCLASS IlvStIFilteredGraphicPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStIFilteredGraphicPanel(IlvDisplay*,
			       const char*,
			       const char* = 0,
			       IlvSystemView = 0,
			       IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIFilteredGraphicPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

    void		setModified();
    IlBoolean		addFilterLibrary(const char*);
protected:
    IlvTreeGadgetItem*	findFilter(IlvGadgetItem*, const IlString&);
    void		initializeFilteredGraphicPanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIFilteredGraphicPanel,
				 IlvStIFilteredGraphicPanelBuilder);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_iconpnl)
#endif /* !__IlvSt_Inspectors_Iconpnl_H */
