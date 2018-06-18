// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/inspect/src/inspect.cpp
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
// Small sample that inspects a .ilv using an IlvHierarchicalSheet
// --------------------------------------------------------------------------

#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/gadgets.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/rectscgc.h>
#include <ilviews/gadgets/fbrowser.h>
#include <ilviews/graphics/geomhan.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/util/pool.h>

#if defined(IL_STD)
#include <fstream>
#include <cstdio>
IL_STDUSE
#else
#include <fstream.h>
#include <stdio.h>
#endif

#define MARGIN 2

// --------------------------------------------------------------------------
// This class is a subclass of IlvTreeGadgetItem that does nothing special.
// It's just here to show how to subclass IlvTreeGadgetItem.
// --------------------------------------------------------------------------
class InspectorTreeGadgetItem
    : public IlvTreeGadgetItem
{
public:
    // ---------------------------------------------------------------------
    InspectorTreeGadgetItem(const char* label)
        : IlvTreeGadgetItem(label)
    {
    }

    // ---------------------------------------------------------------------
    ~InspectorTreeGadgetItem()
    {
    }

    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(InspectorTreeGadgetItem);
};

// ---------------------------------------------------------------------
InspectorTreeGadgetItem::InspectorTreeGadgetItem(IlvInputFile& is,
						 IlvDisplay* display)
    : IlvTreeGadgetItem(is, display)
{
}

// --------------------------------------------------------------------------
InspectorTreeGadgetItem::
InspectorTreeGadgetItem(const InspectorTreeGadgetItem& source)
    : IlvTreeGadgetItem(source)
{
}

// ---------------------------------------------------------------------
void
InspectorTreeGadgetItem::write(IlvOutputFile&) const
{
}

IlvPredefinedGadgetItemIOMembers(InspectorTreeGadgetItem);
IlvRegisterGadgetItemClass(InspectorTreeGadgetItem, IlvTreeGadgetItem);
// --------------------------------------------------------------------------
// End of code related to the InspectorTreeGadgetItem class
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// This class is a subclass of IlvHierarchicalSheet
// It's used to inspect an ilv file by adding a new hierarchy to the
// hierarchical sheet for each ilv file read.
// --------------------------------------------------------------------------
class IlvHierarchicalInspector
    : public IlvHierarchicalSheet
{
public:
    IlvHierarchicalInspector(IlvDisplay*    d,
			     const IlvRect& rect,
			     IlvPalette*    palette = 0)
        : IlvHierarchicalSheet(d,
			       rect,
			       2,
			       1,
			       215,
			       22,
			       2,
			       IlTrue,
			       IlFalse,
			       palette)
    {
	// Set the matrix attributes
	autoFitToSize(IlTrue);
	scrollBarShowAsNeeded(IlFalse, IlFalse);
	showScrollBar(IlvVertical);
	setNbFixedColumn(0);
	scrollToColumn(0);
	setSpacing(0);
	showGrid(IlTrue);
	adjustLast(IlTrue);
	setExclusive(IlTrue);
	setAutoLineSelect(IlTrue);
	fitWidthToSize();

	// Create the first Line items
	set(0, 0, new IlvLabelMatrixItem("Properties"));
	setItemRelief(0, 0, IlTrue);
	setItemSensitive(0, 0, IlFalse);
	setItemGrayed(0, 0, IlFalse);
	set(1, 0, new IlvLabelMatrixItem("Value"));
	setItemRelief(1, 0, IlTrue);
	setItemSensitive(1, 0, IlFalse);
	setItemGrayed(1, 0, IlFalse);

	// Set the callback for edition
	setCallback(SCallbackSymbol(), ValidateCB, this);

	// Palette for accessor nodes :
	// The accessor nodes are drawn with an italic font
	IlvFont* font =
	    getDisplay()->getFont(getFont()->getFamily(),
				  getFont()->getSize(),
				  IlvItalicFontStyle,
				  getFont()->getFoundary());
	_accessorPalette =
	    getDisplay()->getPalette(getNormalTextPalette()->getBackground(),
				     getNormalTextPalette()->getForeground(),
				     0, 0, font);
	_accessorPalette->lock();
	_accessorSPalette =
	   getDisplay()->getPalette(getSelectionTextPalette()->getBackground(),
				    getSelectionTextPalette()->getForeground(),
				    0, 0, font);
	_accessorSPalette->lock();
    }

    // ----------------------------------------------------------------------
    ~IlvHierarchicalInspector()
    {
	_accessorPalette->unLock();
	_accessorSPalette->unLock();
    }

    // ----------------------------------------------------------------------
    // The registerObject methods registers 'object' at the tree location
    // 'item'. In fact, it just add one item (the object name) in the tree.
    // The UnknownChildCount mode is used to allow the children creation when
    // expanding the 'object' node.
    // ----------------------------------------------------------------------
    IlvTreeGadgetItem* registerObject(IlvGraphic* object,
				      IlvTreeGadgetItem* item,
				      const char*        name = 0)
    {
	// If no name is provided, use the object name
	if (!name)
	    name = object->getName();
	// Create the tree item with name as label
	IlvTreeGadgetItem* newItem =
	    createNewTreeItem(name? name : "no name");
	newItem->setUnknownChildCount(IlTrue);
	newItem->setClientData(object);

	// The item is inserted into the tree
	if (item == 0)
	    item = getRoot();
	item->insertChild(newItem);

	// Add the type of the object in the sheet
	(void)createMatrixItem(newItem,
			       object->getClassInfo()->getClassName());
	setItemReadOnly(1, getItemRow(newItem), IlTrue);
	return newItem;
    }

    // ----------------------------------------------------------------------
    // The registerHolder methods registers a whole holder at the tree
    // location 'item'. It adds a tree item for the holder, and calls the
    // registerObjects member function for all its objects.
    // ----------------------------------------------------------------------
    IlvTreeGadgetItem* registerHolder(IlvGraphicHolder*  holder,
				      IlvTreeGadgetItem* item = 0,
				      const char* name = 0)
    {
	if (item == 0)
	    item = getRoot();
	IlvTreeGadgetItem* newItem;
	initReDrawItems();
	// Register the container
	if (holder->isAContainer())
	    item->insertChild(newItem = createNewTreeItem("IlvContainer"));
	else
	    item->insertChild(newItem = createNewTreeItem("IlvManager"));
	setItemReadOnly(1, getItemRow(newItem), IlTrue);
	newItem->setClientData(holder);

	// Add the name of the holder in the sheet
	if (name) {
	    (void)createMatrixItem(newItem, name);
	    setItemReadOnly(1, getItemRow(newItem), IlTrue);
	}

	// For all the objects of the container
	IlUInt count = 0;
	IlvGraphic* const* objects = holder->getObjects(count);
	for (IlUInt i = 0; i < count; i++)
	    registerObject(objects[i], newItem);
	reDrawItems();
	return newItem;
    }

    // ----------------------------------------------------------------------
    // The updateMatrixItem methods updates the matrix item related with the
    // tree item 'item' by calling queryValue on the inspected object.
    // ----------------------------------------------------------------------
    void updateMatrixItem(IlvTreeGadgetItem* item,
			  IlBoolean          redraw = IlFalse)
    {
	// Retrieve the row of the tree item
	IlUShort row = getItemRow(item);
	if (row != (IlUShort)-1) {
	    IlvAbstractMatrixItem* mitem = getItem(1, row);
	    // If no item, create it.
	    if (!mitem)
		mitem = createMatrixItem(item, "");
	    // Retrieve a pointer to the inspected object using the client
	    // data of the tree item.
	    IlvGraphic* object = (IlvGraphic*)
		item->getParent()->getParent()->getClientData();
	    if (object) {
		IlvValue arg(item->getLabel());
		object->queryValue(arg);
		const char* label = (const char*)arg;
		mitem->setLabel(label? label : "");
		if (redraw)
		    reDrawItem(1, row);
	    }
	}
    }

protected:
    IlvPalette* _accessorPalette;
    IlvPalette* _accessorSPalette;

    // ----------------------------------------------------------------------
    // The registerObjectProperties method is called when an item is expanded
    // and has no children. It registers the accessors of the inspected object
    // (the inspected object can be accessed through the client data of the
    // tree item).
    // ----------------------------------------------------------------------
    void registerObjectProperties(IlvTreeGadgetItem* item)
    {
	IlvGraphic* object = (IlvGraphic*)item->getClientData();
	// First Register the object accessors
	registerAccessors(object, item);

	// Then check the type and register sub-objects
	if (object->getClassInfo()->isSubtypeOf(IlvNotebook::ClassInfo())) {
            IlvNotebook* notebook = (IlvNotebook*)object;
	    IlvNotebookPage* page;
            for(IlUShort iPage = 0, iCount = notebook->getPagesCardinal();
		iPage < iCount; iPage++ ) {
		page = (*notebook)[iPage];
                if (!page ||
		    !page->getView() ||
		    !page->getView()->isSubtypeOf(IlvContainer::ClassInfo()))
                    continue;
		IlvContainer* container =
		    (IlvContainer*)page->getView();
		if (container)
		    registerHolder(container->getHolder(), item);
	    }
	} else
	if (object->getClassInfo()->
	    isSubtypeOf(IlvContainerRectangle::ClassInfo())){
	    registerHolder(((IlvContainerRectangle*)object)->
			   getContainer()->getHolder(),
			   item);
	} else
	if (object->getClassInfo()->
	    isSubtypeOf(IlvSpinBox::ClassInfo())) {
	    IlvSpinBox* spin = (IlvSpinBox*)object;
	    IlUShort objectCount = spin->objectCount();
	    for (IlUShort i = 0; i < objectCount; i++)
		registerObject(spin->getObject(i), item);
	}
    }

    // ----------------------------------------------------------------------
    void expand(IlvTreeGadgetItem* item)
    {
	IlvHierarchicalSheet::expand(item);
	if (!item->hasChildren() && item->getClientData())
	    registerObjectProperties(item);
    }

    // ----------------------------------------------------------------------
    IlvAbstractMatrixItem* createMatrixItem(IlvTreeGadgetItem* item,
					    const char* label)
    {
	IlvAbstractMatrixItem* mitem = 0;
	IlUShort row = getItemRow(item);
	if (row != (IlUShort)-1) {
	    mitem = new IlvLabelMatrixItem(label);
	    set(1, row, mitem);
	    setItemAlignment(1, row, IlvLeft);
	}
	return mitem;
    }

    // ----------------------------------------------------------------------
    IlvTreeGadgetItem* createNewTreeItem(const char* label,
					 IlvPalette* pal = 0,
					 IlvPalette* spal = 0)
    {
	IlvTreeGadgetItem* item = new InspectorTreeGadgetItem(label);
	item->setEditable(IlFalse);
	if (pal)
	    item->setNormalTextPalette(pal);
	if (spal)
	    item->setSelectionTextPalette(spal);
	return item;
    }

    // ----------------------------------------------------------------------
    // The registerAccessors() method registers the accessors of the object
    // 'object' at the tree location 'item'. For each registered accessor, it
    // calls updateMatrixItem() to update the inspected value of the accessor.
    // ----------------------------------------------------------------------
    IlvTreeGadgetItem* registerAccessors(IlvGraphic* object,
					 IlvTreeGadgetItem* item)
    {
	IlvTreeGadgetItem* accItem = createNewTreeItem("accessors",
						       _accessorPalette,
						       _accessorSPalette);
	item->insertChild(accItem);
	setItemReadOnly(1, getItemRow(accItem), IlTrue);
	IlUInt count = 0;
	const IlvSymbol* const* accessors = 0;
	const IlvValueTypeClass* const* types = 0;
	object->getAccessors((const IlvSymbol* const**)&accessors,
			     (const IlvValueTypeClass* const**)&types,
			     count);
	if (count) {
	    IlPoolOf(Pointer)::Lock((IlAny*)accessors);
	    IlPoolOf(Pointer)::Lock((IlAny*)types);
	}
	IlvTreeGadgetItem* newItem;
	IlvValue value;
	for (IlUInt i = 0;i < count; i++) {
	    value = IlvValue(accessors[i]->name());
	    object->queryValue(value);
	    if (types[i] != IlvValueMethodType) {
		newItem = createNewTreeItem(accessors[i]->name());
		accItem->insertChild(newItem);
		// Insert the Matrix item associated
		updateMatrixItem(newItem);
	    }
	}
	if (count) {
	    IlPoolOf(Pointer)::UnLock((IlAny*)accessors);
	    IlPoolOf(Pointer)::UnLock((IlAny*)types);
	}
	accItem->shrink();
	return accItem;
    }
    
    // ----------------------------------------------------------------------
    // This callback is called when an accessor's value has been changed.
    // It calls changeValue() on the inspected object.
    // ----------------------------------------------------------------------
    static void ValidateCB(IlvGraphic*,
			   IlAny arg)
    {
	IlvHierarchicalInspector* hsheet = (IlvHierarchicalInspector*)arg;
	IlUShort col, row;
	hsheet->getEditedItem(col, row);
	IlvTreeGadgetItem* item = hsheet->getTreeItem(row);
	if (!item)
	    return;
	IlvAbstractMatrixItem* mitem = hsheet->getItem(col, row);
	IlvValue accessor(item->getLabel(), mitem->getLabel());
	if (item->getParent() && item->getParent()->getParent()) {
	    IlvGraphic* object =
		(IlvGraphic*)item->getParent()->
		getParent()->getClientData();
	    if (!object)
		IlvPrint("Error : object not found !");
	    else {
		object->changeValue(accessor);
		hsheet->updateMatrixItem(item, IlTrue);
	    }
	}
    }

};

// --------------------------------------------------------------------------
// This callback is called when the view associated with an loaded ilv is
// deleted. It removes the associated tree hierarchy from the sheet
// --------------------------------------------------------------------------
static void
DestroyCB(IlvView* view,
	  IlAny arg)
{
    IlvHierarchicalSheet* hsheet = (IlvHierarchicalSheet*)arg;
    // Remove the tree from the hsheet object
    IlvTreeGadgetItem* item = hsheet->getRoot()->getFirstChild();
    while (item) {
	if (((IlvGraphicHolder*)item->getClientData())->getView() == view) {
	    hsheet->removeItem(item);
	    item = 0;
	} else
	    item = item->getNextSibling();
    }
    delete view;
}

const char * filter[] = { "*.ilv" };
const char * msg[] = { "*.ilv" };

// --------------------------------------------------------------------------
// This callback loads an ilv file into the inspector sheet
// --------------------------------------------------------------------------
static void
LoadFileCB(IlvGraphic* g,
	   IlAny arg)
{
    IlvHierarchicalInspector* hsheet = (IlvHierarchicalInspector*)arg;
    IlvButton* button = (IlvButton*)g;
    IlvDisplay* display = button->getDisplay();
    
    const char* home = display->getEnvOrResource("ILVHOME", 0);
    IlPathName dataPath;
    if (home && *home) {
        IlString strHome = home;
        strHome+= "/";
        dataPath= strHome;
        dataPath.addDirectory("samples/gadgets/inspect/data/");
    }
    IlvFileBrowser fb(display->getPalette()->getDisplay(),
		      button->getView()->getSystemView(),
		      dataPath,
		      1,
		      filter,
		      msg);
    const char* result = fb.get();
    if (result) {
	IlvPathName file(result);
	IlvContainer* container = new IlvGadgetContainer(display,
							 file.getBaseName(),
							 file.getBaseName(),
							 IlvRect(0, 0, 1, 1),
							 IlFalse,
							 IlFalse);
	container->setDestroyCallback(DestroyCB, hsheet);
	container->readFile(result);
	container->fitToContents();
	container->show();
	hsheet->initReDrawItems();
	hsheet->registerHolder(container->getHolder(), 0, file.getBaseName());
	hsheet->reDrawItems();
    }
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
QuitCB(IlvGraphic* g,
       IlAny)
{
    delete ((IlvPopupMenu*)g)->getPalette()->getDisplay();
    IlvExit(0);
}

// **************************************************************************
// Entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("HierarchicalSheet", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Can't open display...");
	if (display)
	    delete display;
	return 1;
    }

    // Create the main container
    const char* title = "Hierarchical Inspector";
    IlvRect size(0, 0, 640, 480);
    IlvGadgetContainer* container =
	new IlvGadgetContainer(display,
			       title,
			       title,
			       size,
			       IlFalse,
			       IlFalse);
    container->setDestroyCallback(Quit);

    // Create the sheet
    IlvFont* font = display->getFont("%times-14-");
    IlvHierarchicalInspector* hsheet =
	new IlvHierarchicalInspector(display,
				     IlvRect(MARGIN,
					     MARGIN,
					     size.w() - 2 * MARGIN,
					     size.h() - 50),
				     display->getPalette(0, 0, 0, 0, font));

    // Add it to the container
    container->addObject(hsheet);
    
    // Attach it
    IlvGadgetHolder* holder = container->getHolder();
    holder->attach(hsheet, IlvHorizontal, 0, 1, 0, 0, 0);
    holder->attach(hsheet, IlvVertical,   0, 1, 0, 0);

    // Add the buttons
    IlvButton* button = new IlvButton(display,
				      "Quit",
				      IlvRect(5 * MARGIN,
					      size.h() - 40,
					      70,
					      30));
    button->setCallback(QuitCB);
    container->addObject(button);
    holder->attach(button, IlvHorizontal, 0, 0, 1, 0, 0);
    holder->attach(button, IlvVertical,   1, 0, 0, 0);
    
    button = new IlvButton(display,
			   "Load File",
			   IlvRect(size.w() - 5 * MARGIN - 120,
				   size.h() - 40,
				   120,
				   30));
    button->setCallback(LoadFileCB, hsheet);
    container->addObject(button);
    holder->attach(button, IlvHorizontal, 1, 0, 0, 0,  0);
    holder->attach(button, IlvVertical,   1, 0, 0, 0);
    
    // Show the main window
    container->show();
    IlvMainLoop();
    return 0;
}
