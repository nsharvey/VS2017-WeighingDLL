// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/colorbox/src/colorpnl.cpp
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
// 
// --------------------------------------------------------------------------

#include <ilviews/manager/manager.h>

#include <colorbox.h>
#include <colorpnl.h>
#include <ivstudio/inspectors/listedt.h>
#include <ivstudio/inspectors/pxylist.h>
#include <ivstudio/inspectors/precond.h>

#include <ilviews/contain/inter.h>
#include <ilviews/graphics/label.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/splitgad.h>
#include <ilviews/base/hash.h>

#define CLASSNAME IlvColorComboBox::ClassInfo()->getClassName()
#define TITLE     CLASSNAME + 3

// --------------------------------------------------------------------------
// IlvColorGadgetItemHolderAccessor methods
// --------------------------------------------------------------------------
IlvColorGadgetItemHolderAccessor::IlvColorGadgetItemHolderAccessor(
				     IlvStIPropertyAccessor* accessor,
				     UpdateMode updateMode,
				     BuildMode buildMode,
				     const char* name)
	: IlvStICombinedAccessor(accessor, updateMode, buildMode,
				 (name? name : "ColorHolderAccessor"))
{}

// --------------------------------------------------------------------------
IlvStIProperty*
IlvColorGadgetItemHolderAccessor::getOriginalValue()
{
    IlvStIProperty* property =
		    (getObjectAccessor()? getObjectAccessor()->get() : 0);
    if (!property)
	return 0;
    IlvColorComboBox* combo = (IlvColorComboBox*)property->getPointer();
    if ((!combo) || (!combo->getStringList()))
	return 0;
    return new IlvStIValueProperty((IlvListGadgetItemHolder*)combo,
				   "ColorHolder");
}

// --------------------------------------------------------------------------
// IlvColorItemsAccessor methods
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor / destructor

IlvColorItemsAccessor::
IlvColorItemsAccessor(IlvStIPropertyAccessor* accessor,
		      IlvStIAccessor::UpdateMode mode,
		      const char* name)
    : IlvStIPropertyListAccessor(accessor,
				 mode,
				 IlvStIAccessor::Copy,
				 name) // Forces Copy style
{
}

// --------------------------------------------------------------------------
IlvColorItemsAccessor::~IlvColorItemsAccessor()
{
}

// --------------------------------------------------------------------------
IlvListGadgetItemHolder*
IlvColorItemsAccessor::getListGadgetItemHolder() const
{
    IlvStIProperty* property = (_accessor? _accessor->get() : 0);
    return (property?
	    (IlvListGadgetItemHolder*)property->getPointer() : 0);
}

// --------------------------------------------------------------------------
IlvStIProperty**
IlvColorItemsAccessor::getInitialProperties(IlUInt& count)
{
    IlvListGadgetItemHolder* listHolder = getListGadgetItemHolder();
    if (!listHolder)
	return 0;

    count = (IlUInt)listHolder->getCardinal();
    if (!count)
	return 0;
    IlvStIProperty** properties = new IlvStIProperty*[count];
    for(IlUInt i = 0; i < count; i++) {
	properties[i] =
	    new IlvStIValueProperty((IlAny)listHolder->getItem((IlUShort)i),
				    "Item");
    }
    return properties;
}

// --------------------------------------------------------------------------
IlvStIProperty*
IlvColorItemsAccessor::createDefaultProperty() const
{
    IlvListGadgetItemHolder* listHolder = getListGadgetItemHolder();
    if (!listHolder)
	return 0;
    IlvValue valueInfo(IlvColorDrawInfo::_ColorInfosValue->name());
    IlvColorDrawInfo* colorInfo = (IlvColorDrawInfo*)(IlAny)
		    listHolder->getGadget()->queryValue(valueInfo);
    return new IlvStIValueProperty(
	    new IlvColorGadgetItem(listHolder->getGadget()->
					getDisplay()->getColor("Black"),
				   colorInfo), "Item");
}

// --------------------------------------------------------------------------
IlvGadgetItem*
IlvColorItemsAccessor::getGadgetItem(const IlvStIProperty* property) const
{
    return (IlvGadgetItem*)(property? property->getPointer() : 0);
}

// --------------------------------------------------------------------------
void
IlvColorItemsAccessor::addProperty(IlvStIProperty* property,
				   IlUInt index)
{
    IlvListGadgetItemHolder* listHolder = getListGadgetItemHolder();
    if (listHolder) {
	listHolder->insertItem(getGadgetItem(property), (IlShort)index);
    }
}

// --------------------------------------------------------------------------
IlvStIProperty*
IlvColorItemsAccessor::copyProperty(const IlvStIProperty* property)
{
    IlvGadgetItem* gadgetItem = getGadgetItem(property);
    return new IlvStIValueProperty((IlAny)gadgetItem->copy(), "Item");
}

// --------------------------------------------------------------------------
void
IlvColorItemsAccessor::replaceProperty(IlvStIProperty* origProperty,
				       IlvStIProperty* newProperty,
				       IlUInt)
{
    IlvListGadgetItemHolder* listHolder = getListGadgetItemHolder();
    if (!listHolder)
	return;
    IlvGadgetItem* origGadgetItem = getGadgetItem(origProperty);
    IlvGadgetItem* newGadgetItem = getGadgetItem(newProperty);
    IlvShort position = listHolder->getIndex(origGadgetItem);
    if (position == -1) {
	ILVST_ASSERT(0);
	return;
    }
    *(origGadgetItem) = *newGadgetItem;
    newProperty->setPointer(origGadgetItem);
}

// --------------------------------------------------------------------------
void
IlvColorItemsAccessor::deleteProperty(IlvStIProperty*,
				      IlUInt index)
{
    IlvListGadgetItemHolder* listHolder = getListGadgetItemHolder();
    if (!listHolder)
	return;
    listHolder->removeItem((IlShort)(IlInt)index);
}

// --------------------------------------------------------------------------
void
IlvColorItemsAccessor::moveProperty(IlvStIProperty* property,
				    IlUInt previousIndex,
				    IlUInt newIndex)
{
    IlvListGadgetItemHolder* listHolder = getListGadgetItemHolder();
    if (!listHolder)
	return;
    listHolder->removeItem((IlUShort)previousIndex, IlFalse);
    listHolder->insertItem(getGadgetItem(property),
			   (IlShort)(IlUShort)(newIndex -
				(newIndex > previousIndex? 1 : 0)));
}

// --------------------------------------------------------------------------
void
IlvColorItemsAccessor::deleteNewProperty(IlvStIProperty* property)
{
    IlvGadgetItem* gadgetItem = getGadgetItem(property);
    if (gadgetItem)
	delete gadgetItem;
}

// --------------------------------------------------------------------------
// IlvGadgetItemColorAccessor methods
// --------------------------------------------------------------------------
IlvGadgetItemColorAccessor::IlvGadgetItemColorAccessor(
				       IlvStIPropertyAccessor* accessor,
				       UpdateMode updateMode,
				       BuildMode buildMode,
				       const char* name)
	: IlvStICombinedAccessor(accessor, updateMode, buildMode,
				 (name? name : "GadgetItemColorAccessor"))
{
}

//----------------------------------------------------------------------------
IlvGadgetItemColorAccessor::~IlvGadgetItemColorAccessor()
{
}

//----------------------------------------------------------------------------
IlvGadgetItem*
IlvGadgetItemColorAccessor::getGadgetItem() const
{
    IlvStIProperty* property =
	    (getObjectAccessor()? getObjectAccessor()->get() : 0);
    return (property? (IlvGadgetItem*)property->getPointer() : 0);
}

//----------------------------------------------------------------------------
IlvStIProperty*
IlvGadgetItemColorAccessor::getOriginalValue()
{
    IlvGadgetItem* gadgetItem = getGadgetItem();
    if (!gadgetItem)
	return 0;
    return new IlvStIValueProperty(gadgetItem->getLabel(), "Color");
}

//----------------------------------------------------------------------------
void
IlvGadgetItemColorAccessor::applyValue(IlvStIProperty* property)
{
    IlvGadgetItem* gadgetItem = getGadgetItem();
    if (!gadgetItem)
	return;
    IlvValue value;
    gadgetItem->setLabel((const char*)property->getValue(value));
}

// --------------------------------------------------------------------------
// IlvColorListEditor methods
// --------------------------------------------------------------------------

IlvColorListEditor::IlvColorListEditor(
			  IlvStIPropertyListAccessor* accessor,
			  const char* name)
    : IlvStIPropertyListEditor(accessor, name)
{
    declareGadgets("ColorItemsList",
		   "AddColorItem",
		   "RemoveColorItem",
		   "InsertColorItem",
		   "CleanColorItems",
		   "UpColorItem",
		   "DownColorItem");
}

// --------------------------------------------------------------------------
IlvColorListEditor::~IlvColorListEditor()
{
}
     
// --------------------------------------------------------------------------
IlvBoolean
IlvColorListEditor::connectHolder(IlvGraphicHolder* holder)
{
    // Replaces string list of colors by an IlvColorStringList
    IlvGraphicHolder* subHolder;
    IlvGadget* oldList =
		(IlvGadget*)IlvStIFindGraphic(holder, getName(), &subHolder);
    if (!oldList)
	return IlvStIPropertyListEditor::connectHolder(holder);
    IlvRect bbox;
    oldList->boundingBox(bbox);
    IlvColorStringList* colorList =
		new IlvColorStringList(oldList->getDisplay(),
				       bbox,
				       oldList->getThickness(),
				       oldList->getPalette());
    colorList->useFullSelection(IlTrue, IlFalse);
    colorList->setSelectionMode(IlvStringListSingleSelection);
    colorList->setExclusive(IlTrue);
    colorList->scrollBarShowAsNeeded(IlTrue, IlTrue, IlFalse);
    subHolder->getContainer()->replace(oldList, colorList, IlTrue);

    return IlvStIPropertyListEditor::connectHolder(holder);
}

//----------------------------------------------------------------------------
IlvGadgetItem*
IlvColorListEditor::createGadgetItem(const IlvStIProperty* property) const
{
    IlvGadgetItem* gadgetItem = (IlvGadgetItem*)property->getPointer();
    if (!gadgetItem)
	return 0;
    IlvValue valueInfo(IlvColorDrawInfo::_ColorInfosValue->name());
    IlvColorDrawInfo* colorInfo = (IlvColorDrawInfo*)(IlvAny)
				    getListGadget()->queryValue(valueInfo);
    IlvGadgetItem* newGadgetItem =
	new IlvColorGadgetItem(getDisplay()->getColor(gadgetItem->getLabel()),
			       colorInfo);
    newGadgetItem->setEditable(IlFalse);
    return newGadgetItem;
}

//----------------------------------------------------------------------------
// IlvColorInspectorPanel methods
//----------------------------------------------------------------------------
// Constructor / destructor
IlvColorInspectorPanel::IlvColorInspectorPanel(IlvDisplay* display,
					       const char* title,
					       const char* filename,
					       IlvSystemView transientFor,
					       IlvStIAccessor::UpdateMode
					          updateMode)
    : IlvStIGadgetInspectorPanel(display, title, filename,
				 transientFor, updateMode),
    _drawInfo(0)
{
}

// --------------------------------------------------------------------------
// initializeEditors
void
IlvColorInspectorPanel::initializeEditors()
{
    // Add pages
    addPage("&Specific", "colorspe.ilv", 1);
    addPage("&items", "coloritm.ilv", 2);

    IlvStIGadgetInspectorPanel::initializeEditors();
    initializeColorPanel();
}

// -------------------------------------------------------------------------
static IlBoolean
IlvTranslatorLargeListCallback(IlvStIProperty* property,
			       IlvStIProxyListGadget* list,
			       IlBoolean bInput,
			       IlAny)
{
    IlvValue value;
    if (bInput) {
	property->getValue(value);
	IlvPosition pos = (IlvPosition)value;
	if (pos & IlvLeft)
	    list->setSelectedText("&Left");
	else if (pos & IlvRight)
	    list->setSelectedText("&Right");
	else
	    list->setSelectedText("&None");
    } else {
	IlvString selectedText = list->getSelectedText();
	if (!selectedText.getLength()) {
	    value = (IlvDirection)IlvBadPosition;
	    property->setValue(value);
	    return IlTrue;
	}
	    
	if (selectedText.equals("&Left"))
	    value = (IlvDirection)IlvLeft;
	else if (selectedText.equals("&Right"))
	    value = (IlvDirection)IlvRight;
	else
	    value = (IlvDirection)IlvBadPosition;
	property->setValue(value);
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
// initializeOptionMenuPanel

void
IlvColorInspectorPanel::initializeColorPanel()
{
    // ----------------------------------------------------------------------
    // Adding notebook pages
    addPage("&Specific", "colorspe.ilv", 1);
    IlvNotebookPage* itemsPage =
	addPage("&items", "coloritm.ilv", 2);
    
    // Adding splitter in pages page
    if (itemsPage)
	IlvMakeSplitterGadget((IlvGadgetContainer*)itemsPage->getView(),
			      IlvHorizontal, 1);
    // ----------------------------------------------------------------------
    // Adding editors
    IlvStIEditor* editor;

    // Color name offset
    editor =
	link("ColorNameOffset", IlvListGadgetItemHolder::_labelOffsetValue);
    editor->setPreviewValueAccessor(
	new IlvStIGraphicContainerAccessor(getHolder(), "ColorItemsList"),
	IlvListGadgetItemHolder::_labelOffsetValue);

    // Horizontal margin
    editor = link("XColorMargin", IlvColorDrawInfo::_HColorRectMarginValue);
    editor->setPreviewValueAccessor(
	new IlvStIGraphicContainerAccessor(getHolder(), "ColorItemsList"),
	IlvColorDrawInfo::_HColorRectMarginValue);

    // Vertical margin
    editor = link("YColorMargin", IlvColorDrawInfo::_VColorRectMarginValue);
    editor->setPreviewValueAccessor(
	new IlvStIGraphicContainerAccessor(getHolder(), "ColorItemsList"),
	IlvColorDrawInfo::_VColorRectMarginValue);

    // Small rect editor
    editor = link("SmallRect", IlvColorDrawInfo::_SmallColorRectValue);
    editor->setPreviewValueAccessor(
	new IlvStIGraphicContainerAccessor(getHolder(), "ColorItemsList"),
	IlvColorDrawInfo::_SmallColorRectValue);
    IlvStIPropertyAccessor* smallRectAcc = editor->getAccessor();

    // Round rect editor
    editor = link("RoundRadius", IlvColorDrawInfo::_ColorRoundRectRadius);
    editor->setPreviewValueAccessor(
	new IlvStIGraphicContainerAccessor(getHolder(), "ColorItemsList"),
	IlvColorDrawInfo::_ColorRoundRectRadius);
    editor->getAccessor()->setPrecondition(
	    new IlvStIPreconditionValue(smallRectAcc, IlFalse, (IlInt)0));

    // Visible items
    link("ComboVisibleItems", IlvScrolledComboBox::_nbVisibleItemsValue);
    
    // Enable Large list option
    IlvStIListEditor* lstEdt = ILVI_NEW IlvStIListEditor("ComboEnableLargeList",
	buildPropertyAccessor(IlvScrolledComboBox::_largeListValue->name()));
    lstEdt->setListTranslator(IlvTranslatorLargeListCallback);
    lstEdt->setFillAlways(IlFalse);
    _mainEditor.addEditor(lstEdt);
    
    // List of colors editor
    IlvColorItemsAccessor* lstAccessor =
	    new IlvColorItemsAccessor(
			new IlvColorGadgetItemHolderAccessor(
				getInspectedGraphicAccessor()));
    addEditor(new IlvColorListEditor(lstAccessor, "ColorItemsList"));
    
    editor = new IlvStIPropertyColorEditor("EditColorItem",
		    new IlvGadgetItemColorAccessor(
				lstAccessor->getSelectionAccessor()));
    addEditor(editor);
}
