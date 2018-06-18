// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/src/execdlg.cpp
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
#include <execdlg.h>
#include <IntroView.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>
#include <ilviews/gadgets/matrix.h>
// --------------------------------------------------------------------------
// ExecuteMethodDlg methods
// --------------------------------------------------------------------------
// Constructor / destructor
ExecuteMethodDlg::ExecuteMethodDlg(IlvDisplay* display,
				   IlvDvInterface* interf,
				   IlvDvMethodMember* method)
 : IlvDvDialog(display, "ExecuteMethod", "&ExecuteMethod", "execute.ilv"),
   _interf(interf),
   _method(method)
{
    // Set dialog title
    IlvString title = display->getMessage("&ExecuteMethod");
    title+= " ";
    title+= method->getName();
    setTitle(title);

    // Fill Matrix
    IlvMatrix* matrix = (IlvMatrix*)getObject("Parameters");
    matrix->setRowSize(0, 23); // Set title height

    const IlvDvValueArray& parameters = _method->getParameters();
    if (parameters.getLength()) {
	matrix->setSensitive(IlvTrue);
	setFocus(matrix);
	IlUShort row = 1;
	for(IlUInt iParam = 0; iParam < parameters.getLength(); iParam++,
	      row++) {
	    IlvDvValue* param = parameters.getValue(iParam);
	    IlvAbstractMatrixItem* matItem;
	    matItem = new IlvLabelMatrixItem(param->getName()->name());
	    matrix->insertRow(row);
	    matrix->set((IlUShort)0, row, matItem);
	    matrix->setItemReadOnly((IlUShort)0, row, IlvTrue);

	    matItem =
		ValueEditorFactory::CreateMatrixItem(getDisplay(),
						     param->getType());
	    matrix->set((IlUShort)1, row, matItem);
	    matrix->setRowSize(row, 23);
	}
    }
    else {
	matrix->setSensitive(IlFalse);
	setFocus(getObject("Execute"));
    }

    const IlvValueTypeClass* type = _method->getType();
    IlvTextField* returnedValue = (IlvTextField*)getObject("ReturnedValue");
    returnedValue->setLabel("");
    returnedValue->setSensitive(
		(type != IlvValueNoType) && (type != IlvValueNullType));
    registerCallback("ExecuteCB", ExecuteCB);
    getObject("Execute")->setClientData((IlAny)this);
    reDraw();
}

// --------------------------------------------------------------------------
void
ExecuteMethodDlg::ExecuteCB(IlvGraphic* g,
			    IlAny)
{
    ((ExecuteMethodDlg*)g->getClientData())->execute();
}

// --------------------------------------------------------------------------
void
ExecuteMethodDlg::execute()
{
    // Get parameter values
    IlvDvValueArray params;
    IlvMatrix* matrix = (IlvMatrix*)getObject("Parameters");
    IlUInt iParam = 0;
    const IlvDvValueArray& parameters = _method->getParameters();
    for(IlUShort iRow = 1; iRow < matrix->rows(); iRow++, iParam++) {
	IlvDvValue value(*(parameters.getValue(iParam)));
	IlvAbstractMatrixItem* matItem = matrix->getItem(1, iRow);
	((IlvValue&)value) = matItem->getLabel();
	params.addValue(value);
    }

    // Call method
    IlvDvValue returnedValue;
    _interf->callMethod(_method->getNameSymbol(),
			params,
			&returnedValue);

    // Print result if needed
    const IlvValueTypeClass* type = _method->getType();
    if ((type != IlvValueNoType) && (type != IlvValueNullType)) {
	IlvTextField* tf = (IlvTextField*)getObject("ReturnedValue");
	tf->setLabel((const char*)returnedValue);
	tf->reDraw();
    }

    // Refresh values
    _interf->callMethod(IlvGetSymbol("RefreshValues"), params);
}

// --------------------------------------------------------------------------
// Static initializations

ILVPREDEFINECLASSINFOMEMBERS(ExecuteMethodDlg);

IL_BEGINMODULEINITDEF(execdlg)
    ILVPOSTDEFINECLASSINFOMEMBERS(ExecuteMethodDlg, \
			  IlvPropClassInfo::Create("ExecuteMethodDlg", 0));
IL_ENDMODULEINITDEF(execdlg)

