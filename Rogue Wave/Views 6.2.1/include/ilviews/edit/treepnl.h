// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/treepnl.h
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
// Declaration of the IlvTreePanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Treepnl_H
#define __Ilv_Edit_Treepnl_H

#if !defined(__Ilv_Edit_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif
#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Frame_H)
#include <ilviews/gadgets/frame.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Gadgets_Msglabel_H)
#include <ilviews/gadgets/msglabel.h>
#endif
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif
#if !defined(__Ilv_Gadgets_Spinbox_H)
#include <ilviews/gadgets/spinbox.h>
#endif

class IlvFileSelectorField;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvTreePanel
    : public IlvInspectorPanel {
 public:
    IlvTreePanel (IlvManager*   manager,
		  const char*   className,
		  const char*   title,
		  const char*   icon,
		  const char*   data,
		  const char*   filename,
		  IlvSystemView transientFor);
    IlvTreePanel(IlvManager* manager,
		 IlvSystemView transientFor);
    ~IlvTreePanel();

    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

    // ____________________________________________________________
    // Containers accessors
    IlvNotebook* getNotebook() const
    { return (IlvNotebook*)getObject("Notebook"); }
    IlvGadgetContainer* getTreeGadgetView()const
    {   return (IlvGadgetContainer*)(*getNotebook())[0]->getView(); }
    IlvGadgetContainer* getTreeItemsView()const
    {   return (IlvGadgetContainer*)(*getNotebook())[1]->getView(); }

    // ____________________________________________________________
    // Gadget accessors

    // Tree gadget accessors
    IlvTextField* getSelectionCallback() const
    { return (IlvTextField*)getTreeGadgetView()
	    ->getObject("SelectionCallback"); }
    IlvToggle* getShowLines() const
    { return (IlvToggle*)getTreeGadgetView()->getObject("ShowLines"); }
    IlvTreeGadget* getTreeSample() const
    { return (IlvTreeGadget*)getTreeGadgetView()->getObject("TreeSample"); }
    IlvToggle* getLinesAsRoot() const
    { return (IlvToggle*)getTreeGadgetView()->getObject("LinesAsRoot"); }
    IlvToggle* getButtons() const
    { return (IlvToggle*)getTreeGadgetView()->getObject("Buttons"); }
    IlvToggle* getToolTips() const
    { return (IlvToggle*)getTreeGadgetView()->getObject("ToolTips"); }
    IlvOptionMenu* getModeSelection() const
    { return (IlvOptionMenu*)getTreeGadgetView()->getObject("ModeSelection"); }
    IlvSpinBox* getIndent() const
    { return (IlvSpinBox*)getTreeGadgetView()->getObject("Indent"); }
    IlvToggle* getItemsEditable() const
    { return (IlvToggle*)getTreeGadgetView()->getObject("ItemsEditable"); }

    // Tree gadget items accessors
    IlvTreeGadget* getTreeItems() const
    { return (IlvTreeGadget*)getTreeItemsView()->getObject("TreeItems"); }
    IlvButton* getInsertItem() const
    { return (IlvButton*)getTreeItemsView()->getObject("InsertItem"); }
    IlvButton* getAddItem() const
    { return (IlvButton*)getTreeItemsView()->getObject("AddItem"); }
    IlvButton* getRemove() const
    { return (IlvButton*)getTreeItemsView()->getObject("Remove"); }
    IlvTextField* getlabel() const
    { return (IlvTextField*)getTreeItemsView()->getObject("label"); }
    IlvFileSelectorField* getbitmap() const
    { return (IlvFileSelectorField*)(IlAny)
	    getTreeItemsView()->getObject("bitmap"); }
    IlvFileSelectorField* getSelectedBitmap() const
    { return (IlvFileSelectorField*)(IlAny)
	    getTreeItemsView()->getObject("SelectedBitmap"); }
    IlvToggle* getGadgetItemEditable() const
    { return (IlvToggle*)getTreeItemsView()
	    ->getObject("GadgetItemEditable"); }
    IlvButton* getAddChild() const
    { return (IlvButton*)getTreeItemsView()->getObject("AddChild"); }

    // ____________________________________________________________
    // Callbacks
    virtual void itemsEditableCallback(IlvGraphic*);
    virtual void treeSampleCallback(IlvGraphic*);
    virtual void setSelectionCallback(IlvGraphic*);
    virtual void insertItemCallback(IlvGraphic*);
    virtual void linesAsRootCallback(IlvGraphic*);
    virtual void indentCallback(IlvGraphic*);
    virtual void toolTipsCallback(IlvGraphic*);
    virtual void buttonsCallback(IlvGraphic*);
    virtual void modeSelectionCallback(IlvGraphic*);
    virtual void showLinesCallback(IlvGraphic*);

    virtual void setBitmap(IlvGraphic*);
    virtual void setSelectionBitmap(IlvGraphic*);
    virtual void addChildCallback(IlvGraphic*);
    virtual void removeCallback(IlvGraphic*);
    virtual void addItemCallback(IlvGraphic*);
    virtual void treeItemsCallback(IlvGraphic*);
    virtual void setLabel(IlvGraphic*);
    virtual void gadgetItemEditableCallback(IlvGraphic*);
    virtual void treeItemsEndEditCallback(IlvGraphic*);
 protected:
    void initialize();

    // General page

    // Used to initialize default tree item sample
    IlvTreeGadget* _defaultTreeGadget;
    void applyGeneralOptions(IlvTreeGadget*);
    void prepareTreeGadgetSample(IlvTreeGadget*);
    void generalOptionChanged();

    // Tree item page
    IlBoolean _treeItemEditable;
    IlvTreeGadgetItem* _currentSelection;
    void initFromSelectedTreeItem();
    void updateTreeSampleFromEditingTree();
    void enableEditingTreeItem (IlBoolean bEnable);
    void insertNewItem(IlvTreeGadgetItem* parent, IlInt index);
};

#endif /* !__Ilv_Edit_Treepnl_H*/
