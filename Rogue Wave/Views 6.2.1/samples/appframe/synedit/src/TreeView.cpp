// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/TreeView.cpp
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
// IlogViews 4 generated source file
// File generated Thu Aug 26 15:58:41 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <TreeView.h>
#include <docsynt.h>
#include <synode.h>
#include <ilviews/appframe/command.h>

#include <ilviews/gadgets/splitgad.h>

// --------------------------------------------------------------------------
// TreeView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(TreeView)
    Method1(SelectClass, selectClass, IlAny, node)
IlvDvEndInterface1(IlvDvTreeView)

// --------------------------------------------------------------------------
// Constructor / destructor
TreeView::TreeView(IlvDisplay* display):
    IlvDvTreeView(display)
{
}

// --------------------------------------------------------------------------
TreeView::~TreeView()
{
}

// --------------------------------------------------------------------------
// createNodeItem
IlvTreeGadgetItem*
TreeView::createNodeItem(SynNode* node) const
{
    const char* bmpPath = 0;
    switch(node->getSyntaxicType()) {
    case SynClassDefinition: bmpPath = "class.xpm"; break;
    case SynMember: bmpPath = "member.xpm"; break;
    case SynMethodDeclaration: bmpPath = "method.xpm"; break;
    }
    IlvBitmap* bitmap = 0;
    if (bmpPath)
	bitmap = IlvDvLoadBitmap(getDisplay(), bmpPath);

    IlvTreeGadgetItem* treeGadgetItem =
	    new IlvTreeGadgetItem(node->getName(), bitmap);
    treeGadgetItem->setData((IlAny)node);
    return treeGadgetItem;
}

// --------------------------------------------------------------------------
// Overridables
void
TreeView::initializeView()
{
    IlvDvTreeView::initializeView();
    
    TreeDocument* document = getSyneditDocument();
    IlvGadgetContainer* container = getViewContainer()->getClientContainer();
    IlvMakeSplitterGadget(container, IlvHorizontal, 1);

    SynNodes* synNodes = document->getSynNodes();
    for(IlUInt iNode = 0; iNode < synNodes->getLength(); iNode++) {
	IlvTreeGadgetItem* item = createNodeItem(synNodes->getNode(iNode));
	if (item)
	    addItem(getRoot(), item);
    }
    container->reDraw();
}

// --------------------------------------------------------------------------
// Basic properties
TreeDocument*
TreeView::getSyneditDocument() const
{
    return (TreeDocument*)getDocument();
}

// --------------------------------------------------------------------------
IlvTreeGadgetItem*
TreeView::findNodeItem(IlAny node) const
{
    for(IlvTreeGadgetItem* item = getRoot()->getFirstChild();
			   item;
			   item = item->getNextSibling()) {
	if (item->getData() == node)
	    return item;
    }
    return 0;
}

// --------------------------------------------------------------------------
void
TreeView::selectClass(IlAny node)
{
    IlvTreeGadgetItem* treeItem = findNodeItem(node);
    if (treeItem) {
	if (getFirstSelectedItem() != treeItem) {
	    deSelectAll(IlFalse);
	    setItemSelected(treeItem);
	    reDraw();
	}
    }
    else {
	if (getFirstSelectedItem())
	    deSelectAll(IlTrue);
    }
}

// --------------------------------------------------------------------------
void
TreeView::activate(IlvTreeGadgetItem* item)
{
    notifyDocument(IlvGetSymbol("SelectClass"), item->getData());
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterGadgetViewClass(TreeView, IlvDvTreeView);

IL_BEGINMODULEINITDEF(TreeView)
    IlvDvPostRegisterGadgetViewClass(TreeView, IlvDvTreeView);
IL_ENDMODULEINITDEF(TreeView)

#if !defined(ILVBUILDLIBS)
static int TreeView_ini = (IL_MODINIT(TreeView)(), 0);
#endif

