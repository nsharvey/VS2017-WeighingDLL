// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/src/edit.cpp
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
// Shows how to create a subclass of the IlvAbstractMatrixItem class.
// Shows how to use a specific editor on an IlvMatrix object.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/spinbox.h>
#include <ilviews/gadgets/slider.h>
#include <ilog/pathname.h>
#include <edit.h>

#if defined(IL_STD)
IL_STDUSE
#include <cstring>
#include <iostream>
#include <cstdlib>
#else  /* !IL_STD */
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#endif /* IL_STD */


#define NUMROWS 50

// --------------------------------------------------------------------------
// FormattedFloatItem : A subclass of the IlvFloatMatrixItem where the format
// can be specified.
// --------------------------------------------------------------------------
class FormattedFloatItem : public IlvFloatMatrixItem
{
public:
    FormattedFloatItem(IlFloat value)
	: IlvFloatMatrixItem(value),
	  _format("%.1f")
    {
    }
    FormattedFloatItem(IlFloat value,
		       const IlString& format)
	: IlvFloatMatrixItem(value),
	  _format(format)
    {
    }
    void setFormat(const IlString& format)
    {
	_format = format;
    }
    virtual const char* getFormat() const
    {
	return (const char*)_format;
    }

    DeclareMatrixItemInfo();
    DeclareMatrixItemIOConstructors(FormattedFloatItem);
protected:
    IlString _format;
};

// --------------------------------------------------------------------------
FormattedFloatItem::FormattedFloatItem(const FormattedFloatItem& source)
    : IlvFloatMatrixItem(source),
      _format(source._format)
{
}

// --------------------------------------------------------------------------
FormattedFloatItem::FormattedFloatItem(IlvDisplay* display,
				       IlvInputFile& is)
    : IlvFloatMatrixItem(display, is),
      _format()
{
    _format.readQuoted(is.getStream());
}

// --------------------------------------------------------------------------
void
FormattedFloatItem::write(IlvOutputFile& os) const
{
    IlvFloatMatrixItem::write(os);
    os.getStream() << IlvSpc();
    _format.writeQuoted(os.getStream());
    os.getStream() << IlvSpc();
}

IlvPredefinedMatrixItemIOMembers(FormattedFloatItem);
IlvRegisterMatrixItemClass(FormattedFloatItem, IlvFloatMatrixItem);
// --------------------------------------------------------------------------
// End of the FormattedFloatItem cl43ass definition
// -------------------------------------------------------------------------

// --------------------------------------------------------------------------
// FloatMatrixItemEditor : A subclass of the IlvMatrixItemEditor class that
// uses a spin-box as an editor for an IlvFloatMatrixItem
// --------------------------------------------------------------------------
class FloatMatrixItemEditor : public IlvMatrixItemEditor
{
public:
    FloatMatrixItemEditor(IlvMatrix* matrix,
			  IlUShort col,
			  IlUShort row,
			  IlDouble increment = (IlDouble).1)
	: IlvMatrixItemEditor(matrix, col, row),
	  _increment(increment)
    {
	setEditorField(createSpinBox(matrix->getDisplay()));
    }
    IlvNumberField* createNumberField(IlvDisplay* display) const
    {
	return new IlvNumberField(display, IlvPoint(), (IlDouble)0);
    }
    IlvGraphic* createSpinBox(IlvDisplay* display) const
    {
	IlvSpinBox* spinbox = new IlvSpinBox(display, IlvPoint());
	IlvNumberField* numfield = createNumberField(display);
	spinbox->addField(numfield, 0, _increment, IlTrue);
	return spinbox;
    }
    IlvNumberField* getNumberField() const
    {
	IlvSpinBox* spinbox = (IlvSpinBox*)getEditorField();
	return (IlvNumberField*)spinbox->getObject(0);
    }
    virtual void initFrom() const
    {
	IlvFloatMatrixItem* mitem = (IlvFloatMatrixItem*)
	    getMatrix()->getItem(getColumn(), getRow());
	if (mitem) {
	    IlvNumberField* numfield = getNumberField();
	    numfield->setValue((IlDouble)mitem->getFloat(), IlFalse);
	    IlUShort len = (IlUShort)strlen(numfield->getLabel());
	    numfield->setSelection((IlUShort)0,
				   (numfield->isEditable()
				    ? len
				    : (IlUShort)0));
	    numfield->setCursorPosition(len);
	    numfield->ensureVisible(len);
	    numfield->setAlignment(getMatrix()->getItemAlignment(getColumn(),
								 getRow()));
	    numfield->setTransparent(getMatrix()->isTransparent());
	}
    }
    virtual void applyTo() const
    {
	IlvFloatMatrixItem* mitem = (IlvFloatMatrixItem*)
	    getMatrix()->getItem(getColumn(), getRow());
	if (mitem) {
	    IlvNumberField* numfield = getNumberField();
	    IlBoolean error;
	    IlDouble newValue = numfield->getFloatValue(error);
	    if (!error)
		mitem->setFloat((IlFloat)newValue);
	}
    }
protected:
    IlDouble _increment;
};

// --------------------------------------------------------------------------
// IntMatrixItemEditor : A subclass of the IlvMatrixItemEditor class that
// uses a slider as an editor for an IlvInMatrixItem
// --------------------------------------------------------------------------
class IntMatrixItemEditor : public IlvMatrixItemEditor
{
public:
    IntMatrixItemEditor(IlvMatrix* matrix,
			IlUShort col,
			IlUShort row,
			IlInt min = 0,
			IlInt max = 100)
	: IlvMatrixItemEditor(matrix, col, row),
	  _min(min),
	  _max(max)
    {
	setEditorField(createSlider(matrix->getDisplay()));
    }
    IlvGraphic* createSlider(IlvDisplay* display) const
    {
	IlvSlider* slider = new IlvSlider(display, IlvPoint(), 1);
	slider->setValues(_min, _max, _min);
	return slider;
    }
    IlvSlider* getSliderField() const
    {
	return (IlvSlider*)getEditorField();
    }
    virtual void initFrom() const
    {
	IlvIntMatrixItem* mitem = (IlvIntMatrixItem*)
	    getMatrix()->getItem(getColumn(), getRow());
	if (mitem) {
	    IlvSlider* slider = getSliderField();
	    slider->setValue(mitem->getInt(), IlFalse);
	}
    }
    virtual void applyTo() const
    {
	IlvIntMatrixItem* mitem = (IlvIntMatrixItem*)
	    getMatrix()->getItem(getColumn(), getRow());
	if (mitem) {
	    IlvSlider* slider = getSliderField();
	    mitem->setInt(slider->getValue());
	}
    }
protected:
    IlInt _min;
    IlInt _max;
};

// --------------------------------------------------------------------------
// MatrixItemEditorFactory : A subclass of the IlvMatrixItemEditorFactory class
// that makes the FloatMatrixItemEditor class the editor of IlvFloatMatrixItem
// objects.
// --------------------------------------------------------------------------
class MatrixItemEditorFactory : public IlvMatrixItemEditorFactory
{
public:
    virtual IlvMatrixItemEditor* createEditor(IlvMatrix* matrix,
					      IlUShort col,
					      IlUShort row) const
    {
	IlvAbstractMatrixItem* mitem = matrix->getItem(col, row);
	if (mitem->isSubtypeOf(IlvFloatMatrixItem::ClassInfo()))
	    return new FloatMatrixItemEditor(matrix, col, row);
	else if (mitem->isSubtypeOf(IlvIntMatrixItem::ClassInfo()))
	    return new IntMatrixItemEditor(matrix, col, row);
	else
	    return IlvMatrixItemEditorFactory::createEditor(matrix, col, row);
    }
};

// --------------------------------------------------------------------------
// Panel class for sample Edit
// --------------------------------------------------------------------------
void
Edit::initEdit()
{
    IlvDisplay* display = getDisplay();

    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/gadgets/table/data");
    display->prependToPath(localPath);

    // Fill the matrix
    IlvMatrix* matrix = (IlvMatrix*)getObject("Matrix");
    for (IlUShort i = 0; i < NUMROWS; ++i) {
	// Insert a new row in the matrix
	matrix->insertRow(matrix->rows());
	// For each column add an item
	// Label (column 0)
	IlString label("Row ");
	label += IlString(i + 1);
	matrix->set(0, matrix->rows() - 1, new IlvLabelMatrixItem(label));
	matrix->setItemReadOnly(0, matrix->rows() - 1, IlTrue);
	// Integer (column 1)
	matrix->set(1, matrix->rows() - 1, new IlvIntMatrixItem(i + 1));
	// Float 1/i (column 2)
	matrix->set(2,
		    matrix->rows() - 1,
		    new IlvFloatMatrixItem((IlFloat)(1. / (i + 1))));
	// FormattedFloat 1/i (column 3)
	matrix->set(3,
		    matrix->rows() - 1,
		    new FormattedFloatItem((IlFloat)(1. / (i + 1)), "%.3f"));
    }
	
    // Set the factory for the editors...
    IlvMatrixItemEditorFactory::Set(matrix, new MatrixItemEditorFactory);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageEdit(Pan* mainPanel)
{
    Edit* panel = new Edit(mainPanel, "edit.ilv");
    mainPanel->addPageNoteBook(panel, "Edit", "edit.txt");
}
