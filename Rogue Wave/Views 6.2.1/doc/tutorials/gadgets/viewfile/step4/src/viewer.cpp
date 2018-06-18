// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/viewfile/step4/src/viewer.cpp
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
// Implements the FileViewer class
// This class browses a drive and displays its files and folders into a tree
// and a sheet.
// --------------------------------------------------------------------------

#include <viewer.h>
#include <ilviews/bitmaps/png.h>

#if defined(ILVSTD)
#include <fstream>
#include <cstring>
#else  /* !ILVSTD */
#include <fstream.h>
#include <string.h>
#endif /* ILVSTD */

ILVSTDUSE

#define folderBm  "../../data/file.png"
#define sfolderBm "../../data/filesel.png"
#define fileBm    "../../data/txtfile.png"
#define sfileBm   "../../data/stxtfile.png"

// ------------------------------------------------------------------------
FileViewer::FileViewer(IlvTreeGadget* tree, IlvSheet* sheet)
: _tree(tree), _sheet(sheet)
{
    // Initialize the gadgets
    initObjects();
}

// ------------------------------------------------------------------------
FileViewer::~FileViewer()
{
    // Must delete all the IlvPathName instances linked with each tree
    // gadget item
}

// ------------------------------------------------------------------------
void
FileViewer::init(IlvPathName& path)
{
    updateTree(path);
    updateSheet(path);
}
    
// ------------------------------------------------------------------------
void
FileViewer::updateSheet(IlvPathName& path)
{
    _sheet->initReDrawItems();
    // Reset the sheet
    initSheet();
    // Read all the files contained in 'path'
    if (path.openDir()) {
	IlvPathName file;
	while (path.readDir(file)) {
	    if (!file.isDirectory() || 
		(file.getDirectory(IlvFalse) != IlvString(".") &&
		 file.getDirectory(IlvFalse) != IlvString(".."))) {
		if (!file.isDirectory())
		    file.setDirectory(path);
		// Add the file to the sheet
		addFile(file);
	    }
	}
	path.closeDir();
    }
    // Recompute the column sizes
    _sheet->fitWidthToSize();
    // Invalidate the whole sheet
    _sheet->getHolder()->invalidateRegion(_sheet);
    // Finally, redraw 
    _sheet->reDrawItems();
}

// ------------------------------------------------------------------------
void
FileViewer::updateTree(IlvPathName& path, IlvTreeGadgetItem* item)
{
    _tree->initReDrawItems();
    // Reset the tree if needed
    if (!item)
	initTree();
    // Fill it using the 'path' directory
    fillTree(path, item? item : _tree->getRoot());
    // Finally, redraw
    _tree->reDrawItems();
}

// ------------------------------------------------------------------------
IlvBitmap*
FileViewer::getBitmap(const char* name) const
{
    IlvDisplay* display = _tree->getDisplay();
    IlvBitmap* bitmap = display->getBitmap(name);
    if (!bitmap)
	bitmap = display->readBitmap(name);
    return bitmap;
}

// ------------------------------------------------------------------------
IlvBitmap*
FileViewer::getBitmap(const IlvPathName& file,
		      const IlvSymbol* state) const
{
    if (state == IlvGadgetItem::BitmapSymbol())
	return getBitmap(file.isDirectory()
			 ? folderBm
			 : fileBm);
    else
	return getBitmap(file.isDirectory()
			 ? sfolderBm
			 : sfileBm);
}

// ------------------------------------------------------------------------
IlvGadgetItem*
FileViewer::createFileItem(const IlvPathName& file,
			   const IlvGadgetItemHolder* holder) const
{
    // Compute the item's label
    IlvString filename = file.isDirectory()
	? file.getString()
	: file.getBaseName();
    // If file is a directory, remove the trailing '/'
    if (file.isDirectory())
	filename.remove((int)(filename.getLength() - 1));
    return
	holder->createItem(filename,
			   0,
			   getBitmap(file, IlvGadgetItem::BitmapSymbol()),
			   getBitmap(file,
				     IlvGadgetItem::SelectedBitmapSymbol()));
}

// ------------------------------------------------------------------------
void
FileViewer::initObjects()
{
    initTree();
    initSheet();
}

// ------------------------------------------------------------------------
void
FileViewer::initSheet()
{
    // Set up the sheet
    _sheet->scrollBarShowAsNeeded(IlvTrue, IlvFalse);
    _sheet->hideScrollBar(IlvHorizontal, IlvFalse);
    _sheet->adjustLast(IlvTrue);
    _sheet->reinitialize(3, 1);
    _sheet->setNbFixedColumn(0);
    _sheet->scrollToColumn(0);
    _sheet->setExclusive(IlvTrue);
    _sheet->allowEdit(IlvFalse);
    
    // Create the header
    _sheet->set(0, 0, new IlvLabelMatrixItem("Name"));
    _sheet->setItemAlignment(0, 0, IlvLeft);
    _sheet->setItemRelief(0, 0, IlvTrue);
    _sheet->setItemSensitive(0, 0, IlvFalse);
    _sheet->setItemGrayed(0, 0, IlvFalse);
    _sheet->set(1, 0, new IlvLabelMatrixItem("Size"));
    _sheet->setItemRelief(1, 0, IlvTrue);
    _sheet->setItemSensitive(1, 0, IlvFalse);
    _sheet->setItemGrayed(1, 0, IlvFalse);
    _sheet->set(2, 0, new IlvLabelMatrixItem("Type"));
    _sheet->setItemAlignment(2, 0, IlvLeft);
    _sheet->setItemRelief(2, 0, IlvTrue);
    _sheet->setItemSensitive(2, 0, IlvFalse);
    _sheet->setItemGrayed(2, 0, IlvFalse);
}

// ------------------------------------------------------------------------
void
FileViewer::addFile(const IlvPathName& file)
{
    // Create the gadget item that will be inserted into the sheet
    IlvGadgetItem* item = createFileItem(file, _sheet);
    // Encapsulate it with a matrix item
    IlvAbstractMatrixItem* mitem = new IlvGadgetItemMatrixItem(item);
    // Add a new row in the matrix
    _sheet->insertRow((IlvUShort) -1);
    IlvUShort row = (IlvUShort)(_sheet->rows() - 1);

    // Set the item in the first column
    _sheet->set(0, row, mitem);
    _sheet->resizeRow((IlvUShort)(row + 1), item->getHeight() + 1);
    _sheet->setItemAlignment(0, row, _sheet->getItemAlignment(0, 0));

    // File Size in the second column
    _sheet->setItemSensitive(1, row, IlvFalse);
    _sheet->setItemGrayed(1, row, IlvFalse);
    _sheet->setItemAlignment(1, row, _sheet->getItemAlignment(1, 0));
    ifstream ifile(file.getString(), IlvBinaryInputStreamMode);
    if (!(!ifile)) {
	ifile.seekg(0, ios::end);
	streampos length = ifile.tellg();
	mitem = new IlvIntMatrixItem(length);
	_sheet->set(1, row, mitem);
    }

    // File Type in the third column
    mitem = new IlvLabelMatrixItem(file.isDirectory()
				   ? "File Folder"
				   : "File");
    _sheet->setItemSensitive(2, row, IlvFalse);
    _sheet->setItemGrayed(2, row, IlvFalse);
    _sheet->setItemAlignment(2, row, _sheet->getItemAlignment(2, 0));
    _sheet->set(2, row, mitem);
}

// ------------------------------------------------------------------------
static void
TreeItemSelected(IlvGraphic* g, IlvAny arg)
{
    // Retrieve the item that has triggered the callback
    IlvTreeGadgetItem* item = ((IlvTreeGadget*)g)->getCallbackItem();
    // In the case of a selection (this callback is also called when an item
    // is deselected) update the sheet
    if (item->isSelected()) {
	// Retrieve the pathname of the item
	IlvPathName* pathname = (IlvPathName*)item->getClientData();
	// Retrieve the file viewer instance
	FileViewer* viewer = (FileViewer*)arg;
	// update the sheet
	viewer->updateSheet(*pathname);
    }
}

// ------------------------------------------------------------------------
static void
TreeItemExpanded(IlvGraphic* g, IlvAny arg)
{
    IlvTreeGadgetItem* item = ((IlvTreeGadget*)g)->getCallbackItem();
    if (!item->hasChildren()) {
	FileViewer* viewer = (FileViewer*)arg;
	IlvPathName* path = (IlvPathName*)item->getClientData();
	viewer->updateTree(*path, item);
    }
}

// ------------------------------------------------------------------------
void
FileViewer::initTree()
{
    // Set up the tree gadget
    _tree->removeAllItems(IlvFalse);
    _tree->removeCallback(IlvTreeGadget::ExpandCallbackType(),
			  TreeItemExpanded);
    _tree->addCallback(IlvTreeGadget::ExpandCallbackType(),
		       TreeItemExpanded,
		       this);
    _tree->removeCallback(IlvTreeGadget::SelectCallbackType(),
			  TreeItemSelected);
    _tree->addCallback(IlvTreeGadget::SelectCallbackType(),
		       TreeItemSelected,
		       this);
}

// ------------------------------------------------------------------------
void
FileViewer::fillTree(IlvPathName& path, IlvTreeGadgetItem* parent)
{
    // Read the 'path' directory and insert each sub-folder as a child of
    // the item 'parent'
    if (path.openDir()) {
	IlvPathName file;
	while (path.readDir(file)) {
	    if (file.isDirectory() &&
		file.getDirectory(IlvFalse) != IlvString(".") &&
		file.getDirectory(IlvFalse) != IlvString("..")) {
		IlvTreeGadgetItem* item =
		    (IlvTreeGadgetItem*)createFileItem(file, _tree);
		item->setUnknownChildCount(IlvTrue);
		// Insert the directory 'file' into parent
		parent->insertChild(item);
		// Compute the absolute path name
		IlvPathName* absPathName = new IlvPathName(path);
		absPathName->merge(file);
		item->setClientData(absPathName);
	    }
	}
	path.closeDir();
	// Sort the added items
	_tree->sort(parent, 1);
    }
}
