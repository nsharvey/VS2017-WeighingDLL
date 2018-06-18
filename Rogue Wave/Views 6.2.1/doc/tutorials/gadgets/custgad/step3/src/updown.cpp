// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/custgad/step3/src/updown.cpp
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
// Definition of the UpdownField class
// --------------------------------------------------------------------------

#include <updown.h>

#if defined(ILVSTD)
#include <iostream>
#include <cstring>
#else  /* !ILVSTD */
#include <iostream.h>
#include <string.h>
#endif /* ILVSTD */

ILVSTDUSE

const IlvDim ButtonWidth = 20;
const IlvDim Margin = 4;

// --------------------------------------------------------------------------
UpDownField::UpDownField(IlvDisplay*    display,
                         const IlvRect& rect,
                         const char*    label,
                         IlvUShort      thickness,
                         IlvPalette*    palette)
: IlvGadget(display, rect, thickness, palette),
  _textField(0),
  _rightButton(0),
  _leftButton(0),
  _focusGadget(0)
{
    init(label);
}

// --------------------------------------------------------------------------
UpDownField::UpDownField(IlvInputFile& is, IlvPalette* palette)
: IlvGadget(is, palette),
  _textField(0),
  _rightButton(0),
  _leftButton(0),
  _focusGadget(0)
{
    // Read the label and initialize
    init(IlvReadString(is.getStream()));
}

// --------------------------------------------------------------------------
UpDownField::UpDownField(const UpDownField& source)
: IlvGadget(source),
  _textField(0),
  _rightButton(0),
  _leftButton(0),
  _focusGadget(0)
{
    _leftButton  = (IlvButton*)source._leftButton->copy();
    _textField   = (IlvTextField*)source._textField->copy();
    _rightButton = (IlvButton*)source._rightButton->copy();
    _focusGadget = _textField;
}

// --------------------------------------------------------------------------
UpDownField::~UpDownField()
{
    _textField->setHolder(0);
    delete _textField;
    _rightButton->setHolder(0);
    delete _rightButton;
    _leftButton->setHolder(0);
    delete _leftButton;
}

// --------------------------------------------------------------------------
void
UpDownField::write(IlvOutputFile& os) const
{
    IlvGadget::write(os);
    // Write the label
    os.getStream() << IlvSpc();
    IlvWriteString(os.getStream(), getLabel());
    os.getStream() << IlvSpc();
}

// --------------------------------------------------------------------------
static void
_internal_Up(IlvGraphic* , IlvAny data)
{
    UpDownField * obj = (UpDownField*)data;
    obj->increment();
}

// --------------------------------------------------------------------------
static void
_internal_Down(IlvGraphic* , IlvAny data )
{
    UpDownField * obj = (UpDownField*)data;
    obj->decrement();
}

// --------------------------------------------------------------------------
void
UpDownField::init(const char* label)
{
    // Compute the bounding boxes of each element
    IlvRect r1, r2, r3;
    computeRects(r1, r2, r3);

    // Text field
    _textField   =
	new IlvTextField(getDisplay(),
			 label,
			 r2,
			 getThickness(),
			 getPalette());
    _focusGadget = _textField;

    // Left Button
    _leftButton  =
	new IlvButton(getDisplay(), "-", r1, getThickness(), getPalette());
    _leftButton->setCallback(_internal_Down, this);

    // Right Button
    _rightButton =
	new IlvButton(getDisplay(), "+", r3, getThickness(), getPalette());
    _rightButton->setCallback(_internal_Up, this);
}    

// --------------------------------------------------------------------------
void
UpDownField::computeRects(IlvRect& r1,
			  IlvRect& r2,
			  IlvRect& r3,
			  const IlvTransformer* t) const
{
    IlvRect rect = _drawrect;
    if (t)
	t->apply(rect);
    r1.moveResize(rect.x(), rect.y(), (IlvDim)ButtonWidth, rect.h());
    IlvDim width = rect.w() - (2*(ButtonWidth + Margin));
    r2.moveResize(rect.x() + (IlvPos)(ButtonWidth + Margin),
		  rect.y(),
		  (IlvDim)IlvMax(width, (IlvDim)0),
		  rect.h());
    IlvPos deltaX = (IlvPos)(rect.w() - ButtonWidth);
    r3.moveResize(rect.x() + (IlvPos)IlvMax(deltaX, (IlvPos)0),
		  rect.y(),
		  ButtonWidth,
		  rect.h());
    r1.intersection(rect);
    r2.intersection(rect);
    r3.intersection(rect);
}

// ----------------------------------------------------------------------
IlvBoolean
UpDownField::classFocusable() const
{
    return IlvTrue;
}

// --------------------------------------------------------------------------
void
UpDownField::draw(IlvPort* dst,
		  const IlvTransformer* t,
                  const IlvRegion* clip) const
{
    _textField->draw(dst, t, clip);
    _rightButton->draw(dst, t, clip);
    _leftButton->draw(dst, t, clip);
}

// --------------------------------------------------------------------------
void
UpDownField::drawFocus(IlvPort* dst,
                       const IlvPalette* palette,
                       const IlvTransformer* t,
                       const IlvRegion* clip) const
{
    _focusGadget->drawFocus(dst, palette, t, clip);
}

// --------------------------------------------------------------------------
void
UpDownField::computeFocusRegion(IlvRegion& region,
                                const IlvTransformer* t) const
{
    _focusGadget->computeFocusRegion(region, t);
}

// --------------------------------------------------------------------------
void
UpDownField::setHolder(IlvGraphicHolder* holder)
{
    IlvGadget::setHolder(holder);
    _textField->setHolder(holder);
    _rightButton->setHolder(holder);
    _leftButton->setHolder(holder);
}

// --------------------------------------------------------------------------
void
UpDownField::applyTransform(const IlvTransformer* t)
{
    IlvGadget::applyTransform(t);
    IlvRect r1, r2, r3;
    computeRects(r1, r2, r3);
    _rightButton->moveResize(r3);
    _textField->moveResize(r2);
    _leftButton->moveResize(r1);
}

// --------------------------------------------------------------------------
void
UpDownField::setBackground(IlvColor* color)
{
    IlvGadget::setBackground(color);
    _textField->setBackground(color);
    _rightButton->setBackground(color);
    _leftButton->setBackground(color);
}

// --------------------------------------------------------------------------
void
UpDownField::setForeground(IlvColor* color)
{
    IlvGadget::setForeground(color);
    _textField->setForeground(color);
    _rightButton->setForeground(color);
    _leftButton->setForeground(color);
}

// --------------------------------------------------------------------------
void
UpDownField::setFont(IlvFont* font)
{
    IlvGadget::setFont(font);
    _textField->setFont(font);
    _rightButton->setFont(font);
    _leftButton->setFont(font);
}

// --------------------------------------------------------------------------
void
UpDownField::setMode(IlvDrawMode mode)
{
    IlvGadget::setMode(mode);
    _textField->setMode(mode);
    _rightButton->setMode(mode);
    _leftButton->setMode(mode);
}

// --------------------------------------------------------------------------
void
UpDownField::setPalette(IlvPalette* palette)
{
    IlvGadget::setPalette(palette);
    _textField->setPalette(palette);
    _rightButton->setPalette(palette);
    _leftButton->setPalette(palette);
}

// --------------------------------------------------------------------------
void
UpDownField::setThickness(IlvUShort thickness)
{
    if (thickness != getThickness()) {
	IlvRect r1, r2, r3;
	IlvGadget::setThickness(thickness);
	_textField->setThickness(thickness);
	_rightButton->setThickness(thickness);
	_leftButton->setThickness(thickness);
	computeRects(r1, r2, r3);
	_leftButton->moveResize(r1);
	_textField->moveResize(r2);
	_rightButton->moveResize(r3);
    }
}

// --------------------------------------------------------------------------
void
UpDownField::setFocus(IlvGadget* gadget)
{
    IlvRegion region;
    // Send a focus out event to the gadget that loses the focus
    if (_focusGadget) {
        IlvEvent fo;
        fo._type = IlvKeyboardFocusOut;
        _focusGadget->computeFocusRegion(region, getTransformer());
        _focusGadget->handleEvent(fo);
        _focusGadget = 0;
    }
    _focusGadget = gadget;
    // Send a focus in event to the gadget that receives the focus
    if (_focusGadget) {
        IlvEvent fi;
        fi._type = IlvKeyboardFocusIn;
        _focusGadget->handleEvent(fi);
        _focusGadget->computeFocusRegion(region, getTransformer());
    }
    if (getHolder())
        getHolder()->reDraw(&region);
}

// --------------------------------------------------------------------------
void
UpDownField::increment()
{
    callCallbacks(upCallbackType());
}

// --------------------------------------------------------------------------
void
UpDownField::decrement()
{
    callCallbacks(downCallbackType());
}

// --------------------------------------------------------------------------
IlvBoolean
UpDownField::handleEvent(IlvEvent& event)
{
    IlvBoolean result
#if !defined(__BORLANDC__)
		      = IlvFalse
#endif /* Borland C++ */
		     ;
    switch (event.type()) {
    case IlvButtonDown:
	{
	    // changing focus on click
	    IlvRect r1, r2, r3;
	    IlvPoint evp(event.x(), event.y());
	    computeRects(r1, r2, r3,  getTransformer());
	    if (r2.contains(evp) && _focusGadget != _textField)
		setFocus(_textField);
	    else
	    if (r3.contains(evp) && _focusGadget != _rightButton)
		setFocus(_rightButton);
	    else
	    if (r1.contains(evp) && _focusGadget != _leftButton)
		setFocus(_leftButton);
	    result = _focusGadget->handleEvent(event);
	    break;
      }
    case IlvKeyDown:
	{
	    // moving focus with Tab key
	    if (event.data() == IlvTab &&
		(!(event.modifiers() & IlvShiftModifier)) &&
		(!(event.modifiers() & IlvCtrlModifier))) {
		if (_focusGadget == _textField)
		    setFocus(_rightButton);
		else
		if (_focusGadget == _rightButton)
		    setFocus(_leftButton);
		else
		if (_focusGadget == _leftButton)
		    setFocus(_textField);
		return IlvTrue;
	    }
	    //moving focus with Shift Tab key
	    if (event.data() == IlvTab &&
		((event.modifiers() & IlvShiftModifier)) &&
		(!(event.modifiers() & IlvCtrlModifier))) {
		if (_focusGadget == _leftButton)
		    setFocus(_rightButton);
		else
		if (_focusGadget == _rightButton)
		    setFocus(_textField);
		else
		if (_focusGadget == _textField)
		    setFocus(_leftButton);
		return IlvTrue;
	    }
	}
    default:
	result = _focusGadget->handleEvent(event);
    }
    return result;
}

// ---------------------------------------------------------
IlvUInt
UpDownField::getCallbackTypes(const char* const**      names,
                              const IlvSymbol* const** types) const
{
    IlvUInt count = IlvGadget::getCallbackTypes(names, types);
    AddToCallbackTypeList(count, names, types,
                          "Down", downCallbackType());
    AddToCallbackTypeList(count, names, types,
                          "Up", upCallbackType());
    return count;
}

IlvPredefinedIOMembers(UpDownField);
IlvRegisterClass(UpDownField, IlvGadget);
