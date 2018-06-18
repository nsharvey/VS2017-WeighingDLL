// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/project/prjview.h
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
// Declaration of the IlvDvProjectView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Project_Prjview_H)
#define __Ilv_Appframe_Project_Prjview_H

#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif

class IlvDvProjectItem;
class IlvDvProjectDocument;
class IlvDvDocumentProjectItem;
// --------------------------------------------------------------------------
// IlvDvProjectView class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvProjectView : public IlvDvTreeView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvProjectView(IlvDisplay* display);
    virtual ~IlvDvProjectView();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void	initializeView(); // called first time after construct

    virtual void	activate(IlvTreeGadgetItem* item);

    // ----------------------------------------------------------------------
    // Basic properties
    IlvDvProjectDocument*	getProjectDocument() const;
    IlBoolean		removeProjectItem(IlAny item);
    IlBoolean		addProjectItem(IlAny item);

    // ----------------------------------------------------------------------
    // Query / apply values
    IlvDvDeclareAccessors();
    IlvDvDeclareInterface();

protected:
    IlvTreeGadgetItem*	fill(IlvTreeGadgetItem* parent,
			     const IlvDvProjectItem* treeItem);
    IlvTreeGadgetItem*	findItem(const IlvTreeGadgetItem* dataItem,
				 IlvTreeGadgetItem* root = 0);
    IlvTreeGadgetItem*	getSelectedItems(IlArray& items) const;
    virtual void	activateSelection();

    void		insert();
    virtual void	insertFile();
    virtual IlBoolean	canInsertFile() const;
    virtual void	insertFolder();

    virtual void	insertFileUI(IlvDvActionDescriptor* desc);
    virtual void	insertFolderUI(IlvDvActionDescriptor* desc);
    virtual IlBoolean	canInsertFolder() const;
    virtual void	deleteSelection();

    void		getSelections(IlArray&,
				      IlBoolean getAll = IlFalse,
				      IlvTreeGadgetItem* parent = 0) const;
    IlUInt		getDeletableItems(IlArray& selections) const;
    virtual IlBoolean	canDeleteItem(const IlvDvProjectItem*) const;
    void		selectionChanged();

    // ----------------------------------------------------------------------
    // Popup menus management
    virtual const IlSymbol*	
		getPopupMenuResourceId(const IlvTreeGadgetItem* item) const;
    IlvDvProjectItem*	getProjectItem(const IlvTreeGadgetItem* item) const;
    IlvDvProjectItem*	getSelectedProjectItem() const;

public:
    static void		ItemSelected(IlvGraphic*, IlAny);
    static void		AddItemCallback(IlvGraphic* g, IlAny param);
    static void		RemoveItemCallback(IlvGraphic* g, IlAny param);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(prjview);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Prjview_H */
