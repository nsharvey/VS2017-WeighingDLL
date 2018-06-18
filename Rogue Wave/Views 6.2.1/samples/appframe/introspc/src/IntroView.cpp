// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/src/IntroView.cpp
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
// File generated Thu Mar 09 20:08:53 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <IntroView.h>
#include <IntroDocument.h>
#include <ilviews/appframe/command.h>

#include <introcmd.h>
#include <execdlg.h>
#include <ilviews/appframe/command.h>
#include <ilviews/appframe/interf.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/toggle.h>

#define DEFAULT_ROW_HEIGHT 12

// --------------------------------------------------------------------------
// ValueEditorFactory methods
// --------------------------------------------------------------------------
IlvAbstractMatrixItem*
ValueEditorFactory::CreateMatrixItem(IlvDisplay* display,
				     const IlvValueTypeClass* type)
{
    IlvAbstractMatrixItem* matItem;
    if (type == IlvValueIntType)
	matItem = new IlvIntMatrixItem(0);
    else if (type == IlvValueUIntType)
	matItem = new IlvIntMatrixItem(0);
    else if (type == IlvValueBooleanType) {
	IlvToggle* toggle =
			new IlvToggle(display,
				      (const char*)"false",
				      IlvRect(0, 0, 100, 23));
	toggle->setRadio(IlvFalse);
	matItem = new IlvGadgetMatrixItem(toggle);
    }
    else if (type == IlvValueStringType)
	matItem = new IlvLabelMatrixItem("");
    else if (type == IlvValueFloatType)
	matItem = new IlvFloatMatrixItem((IlvFloat)0.0);
    else if (type == IlvValueAnyType)
	matItem = new IlvLabelMatrixItem((const char*)"");
    else if (type == IlvValueDoubleType)
	matItem = new IlvDoubleMatrixItem((IlvDouble)0.0);
    else {
	IlvFatalError("Unknow parameter type %s", type->name());
	matItem = 0;
    }
    return matItem;
}

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------
void
IntroView::ItemSelectedCallback(IlvGraphic*,
				IlAny param)
{
    ((IntroView*)param)->memberSelected();
}

// --------------------------------------------------------------------------
void
IntroView::ItemActivatedCallback(IlvGraphic*,
				 IlAny param)
{
    ((IntroView*)param)->memberActivated();
}

// --------------------------------------------------------------------------
void
IntroView::FieldToggled(IlvGraphic* g,
			IlAny param)
{
    ((IntroView*)param)->
	    fieldToggled((IlvDvFieldMember*)g->getClientData(),
			 ((IlvToggle*)g)->getState());
}

// --------------------------------------------------------------------------
void
IntroView::MatrixItemCallback(IlvMatrix* matrix,
			      IlUShort col,
			      IlUShort row,
			      IlAny param)
{
    IlvAbstractMatrixItem* matItem = matrix->getItem(col, row);
    ((IntroView*)param)->changeFieldValue(
			(IlvDvFieldMember*)matrix->getItemData(0, row),
			matItem->getLabel());
}

// --------------------------------------------------------------------------
// IntroView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(IntroView)
    Method(RefreshValues, refreshValues)
    Action(ExecMethod, execSelectedMethod)
    RefreshAction(ExecMethod, execSelectedMethodUI)
IlvDvEndInterface1(IlvDvHierarchicalSheetView)

// --------------------------------------------------------------------------
// Constructor / destructor
IntroView::IntroView(IlvDisplay* display)
: IlvDvHierarchicalSheetView(display)
{
    _classBmp  = IlvDvLoadBitmap(display, "propert.gif");
    _fieldBmp  = IlvDvLoadBitmap(display, "field.gif");
    _methodBmp = IlvDvLoadBitmap(display, "method.gif");

    hideScrollBar(IlvHorizontal);
    setYgrid(DEFAULT_ROW_HEIGHT);
    setSpacing(0);
    // Some metrics
    adjustLast(IlTrue);
    setBrowseMode(IlFalse);
    setAutoLineSelect(IlTrue);
    setExclusive(IlTrue);
    showGrid(IlTrue);

    // Set callbacks
    setCallback(ItemSelectedCallback, (IlAny)this);
    setCallback(IlvMatrix::ActivateMatrixItemCallbackType(),
		ItemActivatedCallback,
		(IlAny)this);
}

// --------------------------------------------------------------------------
IntroView::~IntroView()
{
}

// --------------------------------------------------------------------------
const IlvString&
GetValueTypeName(const IlvValueTypeClass* type,
		 IlvString& name)
{
    if (!type || (type == IlvValueNoType) || (type == IlvValueNullType))
	name = "void";
    else
	name = type->name();
    return name;
}

// --------------------------------------------------------------------------
// Overridables
void
IntroView::initializeView()
{
    IlvDvHierarchicalSheetView::initializeView();
    
    IntroDocument* document = getIntroDocument();
    
    // Set Column titles
    IlvTreeGadgetItem* parent = new IlvTreeGadgetItem("Document", _classBmp);
    addItem(getRoot(), parent);
    set((IlUShort)1, 0, new IlvLabelMatrixItem((const char*)""));
    set(0, 0, new IlvFilledLabelMatrixItem(
		    getPalette(),
		    (const char*)IlvGetMessage(getDisplay(), "&Fields")));
    setItemRelief(0, 0);
    set(1, 0, new IlvFilledLabelMatrixItem(
		    getPalette(),
		    (const char*)IlvGetMessage(getDisplay(), "&Values")));
    setItemRelief(1, 0);
    setRowSize(0, 23);
    setColumnSize(0, 250);

    // Fill rows according to document's members
    IlvArray members;
    document->getAPIInfos(members);
    IlvString itemName;
    for(IlUInt i = 0; i < members.getLength(); i++) {
	IlvDvMember* member = (IlvDvMember*)members[i];
	IlvBitmap* bmp = 0;

	// Add field or method name in the first column
	if (member->isField()) {
	    IlvDvFieldMember* fieldMember = (IlvDvFieldMember*)member;
	    GetValueTypeName(fieldMember->getType(), itemName);
	    itemName+= " ";
	    itemName+= fieldMember->getName();
	    bmp = _fieldBmp;
	}
	else {
	    IlvDvMethodMember* method = (IlvDvMethodMember*)member;
	    GetValueTypeName(method->getType(), itemName);
	    itemName+= " ";
	    itemName+= method->getName();
	    itemName+= "(";
	    const IlvDvValueArray& parameters = method->getParameters();
	    for(IlUInt iParam = 0; iParam < parameters.getLength(); iParam++){
		if (iParam)
		    itemName+= ", ";
		IlvValue* value = parameters.getValue(iParam);
		IlvString tmp;
		itemName+= GetValueTypeName(value->getType(), tmp);
		itemName+= " ";
		itemName+= value->getName()->name();
	    }
	    itemName+= ");";
	    bmp = _methodBmp;
	}

	IlvTreeGadgetItem* item = 
	    new IlvTreeGadgetItem((const char*)itemName, bmp);
	addItem(parent, item);
	IlUShort row = getItemRow(item);
	setItemData(0, row, (IlAny)member);
	setItemReadOnly((IlUShort)0, row, IlTrue);

	// Add current value of the field in the second column
	IlvAbstractMatrixItem* matItem = 0;
	if (member->isField()) {
	    IlvDvFieldMember* field = (IlvDvFieldMember*)member;
	    const IlvValueTypeClass* type = field->getType();
	    matItem = ValueEditorFactory::CreateMatrixItem(getDisplay(), type);
	    if (type == IlvValueBooleanType) {
		IlvToggle* toggle =
		    (IlvToggle*)((IlvGadgetMatrixItem*)matItem)->getGadget();
		toggle->setCallback(FieldToggled, (IlAny)this);
		toggle->setClientData((IlAny)field);
	    }
	}
	if (matItem) {
	    set((IlUShort)1, row, matItem);
	    setItemAlignment((IlUShort)1, row, IlvLeft);
	    if (member->isField())
		setItemCallback(1, row, MatrixItemCallback, (IlAny)this);
	    else
		setItemReadOnly((IlUShort)1, row, IlTrue);
	}
	setRowSize(row, 23);
    }

    refreshValues();
}

// --------------------------------------------------------------------------
void
IntroView::changeFieldValue(IlvDvFieldMember* field,
			    const char* strValue)
{
    IlvDvValue value(strValue);
    getIntroDocument()->doCommand(
	    new ChangeFieldValueCommand(getIntroDocument(),
					IlvGetSymbol(field->getName()),
					value));
}

// --------------------------------------------------------------------------
void
IntroView::fieldToggled(IlvDvFieldMember* field,
			IlBoolean state)
{
    IlvDvValue value(state);
    getIntroDocument()->doCommand(
	    new ChangeFieldValueCommand(getIntroDocument(),
					IlvGetSymbol(field->getName()),
					value));
}

// --------------------------------------------------------------------------
void
IntroView::refreshValues()
{
    for(IlUShort row = 2; row < rows(); row++) {
	IlvDvMember* member = (IlvDvMember*)getItemData(0, row);
	if (member && member->isField()) {
	    IlvDvValue value;
	    getDocument()->
		    getFieldValue(IlvGetSymbol(member->getName()), value);
	    IlvAbstractMatrixItem* matItem = getItem(1, row);
	    IlvDvFieldMember* field = (IlvDvFieldMember*)member;
	    if (field->getType() == IlvValueBooleanType) {
		IlvToggle* toggle =
		    (IlvToggle*)((IlvGadgetMatrixItem*)matItem)->getGadget();
		toggle->setState((IlBoolean)value);
	    }
	    else
		matItem->setLabel((const char*)value);
	}
    }
    reDraw();
}

// --------------------------------------------------------------------------
void
IntroView::execSelectedMethod()
{
    IlvDvMember* member = getSelectedMember();
    if (!member)
	return;
    if (member->isField())
	return;
    executeMethod((IlvDvMethodMember*)member);
}

// --------------------------------------------------------------------------
void
IntroView::execSelectedMethodUI(IlvDvActionDescriptor* desc)
{
    IlvDvMember* member = getSelectedMember();
    desc->setValid(member && !member->isField());
}

// --------------------------------------------------------------------------
IlvDvMember*
IntroView::getSelectedMember() const
{
    IlUShort col, row;
    getLastSelectedItem(col, row);
    if (row < 2)
	return 0;
    if (col == (IlvUShort)-1)
	return 0;
    return (IlvDvMember*)getItemData((IlUShort)0, row);
}

// --------------------------------------------------------------------------
void
IntroView::executeMethod(IlvDvMethodMember* member)
{
    ExecuteMethodDlg dlg(getDisplay(), getDocument(), member);
    dlg.initialize();
    dlg.wait();
}

// --------------------------------------------------------------------------
void
IntroView::memberSelected()
{
    getDvApplication()->refreshAction(IlvGetSymbol("ExecMethod"));
}

// --------------------------------------------------------------------------
void
IntroView::memberActivated()
{
    execSelectedMethod();
}
    
// --------------------------------------------------------------------------
// Basic properties
IntroDocument*
IntroView::getIntroDocument() const
{
    return (IntroDocument*)getDocument();
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterGadgetViewClass(IntroView, IlvDvHierarchicalSheetView);

IL_BEGINMODULEINITDEF(IntroView)
    IlvDvPostRegisterGadgetViewClass(IntroView, IlvDvHierarchicalSheetView);
IL_ENDMODULEINITDEF(IntroView)

#if !defined(ILVBUILDLIBS)
static int IntroView_ini = (IL_MODINIT(IntroView)(), 0);
#endif

