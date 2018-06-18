// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/viewfile/src/viewerw.cpp
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
// Implements the FileViewerWindow class
// This class displays a tree and a sheet separated by a splitter
// --------------------------------------------------------------------------

#include <viewerw.h>

// --------------------------------------------------------------------------
FileViewerWindow::FileViewerWindow(IlvAbstractView* parent,
				   const IlvRect&   dims,
				   IlBoolean        visible)
    : IlvPanedContainer(parent, dims, IlvHorizontal, visible)
{
    initLayout(dims);
}

// --------------------------------------------------------------------------
FileViewerWindow::FileViewerWindow(IlvDisplay*    d,
				   const char*    name,
				   const char*    title,
				   const IlvRect& dims,
				   IlBoolean      visible)
    : IlvPanedContainer(d, name, title, dims, IlvHorizontal, 0, visible)
{
    initLayout(dims);
}

// --------------------------------------------------------------------------
IlvTreeGadget*
FileViewerWindow::getDirectoryHierarchy() const
{
    IlvGraphicPane* pane = (IlvGraphicPane*)getPane("DirectoryHierarchy");
    return (IlvTreeGadget*)pane->getObject();
}

// --------------------------------------------------------------------------
IlvSheet*
FileViewerWindow::getFileList() const
{
    IlvGraphicPane* pane = (IlvGraphicPane*)getPane("FileList");
    return (IlvSheet*)pane->getObject();
}

// --------------------------------------------------------------------------
void
FileViewerWindow::initLayout(const IlvRect& size)
{
    // Create the tree gadget in which the folder hierarchy will be displayed
    IlvTreeGadget* tree =
	new IlvTreeGadget(getDisplay(),
			  IlvRect(0,
				  0,
				  IlMax((IlvDim)100,
					 (IlvDim)(size.w() / 3)),
				  size.h()));
    // Encapsulate it into a graphic pane giving "DirectoryHierarchy" as name
    IlvGraphicPane* treePane = new IlvGraphicPane("DirectoryHierarchy", tree);
    // The pane is set resizable, that is, it will be possible to
    // interactively resize it using a splitter.
    treePane->setResizeMode(IlvPane::Resizable);
    // Set also a minimum size on the horizontal direction
    treePane->setMinimumSize(IlvHorizontal, 100);
    // Add the pane to the container
    addPane(treePane);
    
    // Create the sheet
    IlvSheet* sheet =
	new IlvSheet(getDisplay(),
		     IlvRect(0, 0, size.w(), size.h()),
		     1,
		     1,
		     size.w() / 4,
		     25,
		     2,
		     IlFalse,
		     IlFalse);
    // Disable multi selection
    sheet->setExclusive(IlTrue);
    // Disable edition
    sheet->allowEdit(IlFalse);
    // Encapsulate it into a graphic pane giving "FileList" as name
    IlvGraphicPane* listPane = new IlvGraphicPane("FileList", sheet);
    // The sheet is elastic : When the container will be resized, only the 
    // sheet will be resized (because the tree is only resizable, not elastic)
    listPane->setResizeMode(IlvPane::Elastic);
    // Add the pane to the container
    addPane(listPane);
    // update the container
    updatePanes();
}
