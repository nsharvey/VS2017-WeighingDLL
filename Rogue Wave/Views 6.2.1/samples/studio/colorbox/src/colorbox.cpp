// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/colorbox/src/colorbox.cpp
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
// Implementation of the ColorBox classes
// --------------------------------------------------------------------------

#include "colorbox.h"
#include <ilviews/graphics/rectangl.h>

#if defined(IL_STD)
#include <fstream>
IL_STDUSE
#else  /* !IL_STD */
#include <fstream.h>
#endif/* !IL_STD */

// --------------------------------------------------------------------------
// IlvColorDrawInfo methods
// --------------------------------------------------------------------------

IlvDim
IlvColorDrawInfo::_DefaultLabelOffset = 20;

// --------------------------------------------------------------------------
// Constructor / destructor
IlvColorDrawInfo::IlvColorDrawInfo(IlvDisplay* display)
    : _smallColorRect(IlTrue),
      _colorRoundRectRadius(0),
      _horizontalRectColorMargin(2),
      _verticalRectColorMargin(1),
      _drawMode(IlvModeSet),
      _display(display)
{
}

// --------------------------------------------------------------------------
IlvColorDrawInfo::IlvColorDrawInfo(const IlvColorDrawInfo& source)
    : _smallColorRect(source._smallColorRect),
      _colorRoundRectRadius(source._colorRoundRectRadius),
      _horizontalRectColorMargin(source._horizontalRectColorMargin),
      _verticalRectColorMargin(source._verticalRectColorMargin),
      _drawMode(IlvModeSet),
      _display(source._display)
{
}

// --------------------------------------------------------------------------
IlvColorDrawInfo::~IlvColorDrawInfo()
{
}

// --------------------------------------------------------------------------
IlvColorDrawInfo&
IlvColorDrawInfo::operator = (const IlvColorDrawInfo& source)
{
    _smallColorRect = source._smallColorRect;
    _colorRoundRectRadius = source._colorRoundRectRadius;
    _horizontalRectColorMargin = source._horizontalRectColorMargin;
    _verticalRectColorMargin = source._verticalRectColorMargin;
    _drawMode = source._drawMode;
    _display = source._display;
    return *this;
}

// --------------------------------------------------------------------------
IlvValue&
IlvColorDrawInfo::queryValue(IlvValue& arg) const
{
    if (arg.getName() == _SmallColorRectValue) {
	arg = _smallColorRect;
	return arg;
    } else
    if (arg.getName() == _ColorRoundRectRadius) {
	arg = (IlInt)_colorRoundRectRadius;
	return arg;
    } else
    if (arg.getName() == _HColorRectMarginValue) {
	arg = (IlInt)_horizontalRectColorMargin;
	return arg;
    } else
    if (arg.getName() == _VColorRectMarginValue) {
	arg = (IlInt)_verticalRectColorMargin;
	return arg;
    } else
    if (arg.getName() == _ColorInfosValue) {
	arg = (IlAny)this;
	return arg;
    }

    return IlvValueInterface::queryValue(arg);
}

// --------------------------------------------------------------------------
IlBoolean
IlvColorDrawInfo::applyValue(const IlvValue& arg)
{
    if (arg.getName() == _SmallColorRectValue) {
	_smallColorRect = (IlBoolean)arg;
	return IlTrue;
    } else
    if (arg.getName() == _ColorRoundRectRadius) {
	_colorRoundRectRadius = (IlUShort)(IlUInt)arg;
	return IlTrue;
    } else
    if (arg.getName() == _HColorRectMarginValue) {
	_horizontalRectColorMargin = (IlUShort)(IlUInt)arg;
	return IlTrue;
    } else
    if (arg.getName() == _VColorRectMarginValue) {
	_verticalRectColorMargin = (IlUShort)(IlUInt)arg;
	return IlTrue;
    } else
    if (arg.getName() == _ColorInfosValue) {
	*(this) = *(IlvColorDrawInfo*)(IlAny)arg;
	return IlTrue;
    }
    
    return IlvValueInterface::applyValue(arg);
}

// --------------------------------------------------------------------------
void
IlvColorDrawInfo::GetAccessors(const IlvSymbol* const** a,
			       const IlvValueTypeClass* const** t,
			       IlUInt& c)
{
    DeclareAccessor(_SmallColorRectValue,   IlvValueBooleanType,   a, t, c);
    DeclareAccessor(_ColorRoundRectRadius,  IlvValueIntType,	   a, t, c);
    DeclareAccessor(_HColorRectMarginValue, IlvValueIntType,       a, t, c);
    DeclareAccessor(_VColorRectMarginValue, IlvValueIntType,       a, t, c);
    DeclareAccessor(_ColorInfosValue,       IlvValueAnyType,       a, t, c);
}

// --------------------------------------------------------------------------
// IlvColorComboBox methods
// --------------------------------------------------------------------------
IlvColorGadgetItem::IlvColorGadgetItem(IlvColor* color,
				       const IlvColorDrawInfo* drawInfos,
				       IlvPosition  position,
				       IlUShort    spacing)
    : IlvGadgetItem((color? color->getName() : "No name"),
		    (IlvBitmap*)0,
		    position,
		    spacing),
      _drawInfo(drawInfos)
{
}

// ----------------------------------------------------------------------
IlvColorGadgetItem::IlvColorGadgetItem(const IlvColorGadgetItem& source)
    : IlvGadgetItem(source),
      _drawInfo(source._drawInfo)
{
}

// --------------------------------------------------------------------------
IlvColorGadgetItem::~IlvColorGadgetItem()
{
}

// --------------------------------------------------------------------------
void
IlvColorGadgetItem::draw(IlvPort* dst,
		         const IlvRect&        rect,
		         const IlvTransformer* t,
		         const IlvRegion*      clip) const
{
    IlvGadgetItem::draw(dst, rect, t, clip);

    // Get the color of the color rect
    IlvColor* color = getColor();
    if (!color || !_drawInfo)
	return;

    // get the color rect bbox
    IlvRect colorRect(rect);
    if (_drawInfo->_smallColorRect)
	colorRect._w = 
	    ((IlvListGadgetItemHolder*)getHolder())->getLabelOffset();
    colorRect.expand(- _drawInfo->_horizontalRectColorMargin,
		     - _drawInfo->_verticalRectColorMargin);
    if (colorRect._w < 2)
	return;
    
    // Draw the color rectangle
    IlvPalette* palette =
	    _drawInfo->_display->getPalette(
		    _drawInfo->_display->getColor("Black"),
		    color);
    IlvDrawMode oldDrawMode = palette->getMode();
    palette->setMode(_drawInfo->_drawMode);
    {
	IlvPushClip pushClip(*palette, clip);
	if (!_drawInfo->_colorRoundRectRadius && _drawInfo->_smallColorRect)
	    dst->getDisplay()->fillRectangle(dst, palette, colorRect);
	else
	    dst->getDisplay()
	       ->fillRoundRectangle(dst,
				    palette,
				    colorRect,
				    _drawInfo->_colorRoundRectRadius);
    }
    // Restore palette parameters
    palette->setMode(oldDrawMode);

    // Redraw label if mode _smallColorRect  is not set
    if (!_drawInfo->_smallColorRect) {
	// Find label color to be sure text is clearly visible
	IlvIntensity r, g, b;
	color->getRGB(r, g, b);
	IlvColor* textColor;
	// If back has a light color, use black color to draw text
	long middleInt = ((IlvIntensity)-1) / 2;
	if ((long)r + (long)g + (long)b >=
		    middleInt + middleInt + middleInt)
	    textColor = dst->getDisplay()->getColor("Black");
	else
	    textColor = dst->getDisplay()->getColor("White");

	//palette = _drawInfo->_display->getPalette(color, textColor);
	palette = _drawInfo->_display->getPalette(textColor, textColor);

	// Prepares palette to draw
	IlvDrawMode oldDrawMode = palette->getMode();
	palette->setMode(_drawInfo->_drawMode);
	{
	    IlvPushClip pushClip(*palette, clip);
	
	    // Draw the label
	    colorRect = rect;
	    colorRect.translate(((IlvListGadgetItemHolder*)getHolder())
					->getLabelOffset(), 0);
	    colorRect.grow(-(IlInt)((IlvListGadgetItemHolder*)getHolder())
					->getLabelOffset(), 0);
	    drawLabel(dst, palette, colorRect, t, clip);
	}

	// Restore palette parameters
	palette->setMode(oldDrawMode);
    }
}
/*
// --------------------------------------------------------------------------
void
IlvColorGadgetItem::drawLabel(IlvPort* dst,
			      IlvPalette*           palette,
			      const IlvRect&        rect,
			      const IlvTransformer* t,
			      const IlvRegion*       clip) const
{
    IlvRect labelRect(rect);
    IlvRect frameRect(rect);
    labelRect.expand(-getHLabelMargin(), 0);
    IlvGadgetItem::drawLabel(dst, palette, bbox, t, clip);
}
*/
// --------------------------------------------------------------------------
IlvColor*
IlvColorGadgetItem::getColor()const
{
    return (_drawInfo? _drawInfo->_display->getColor(getLabel()) : 0);
}

// --------------------------------------------------------------------------
void
IlvColorGadgetItem::setDrawInfo(const IlvColorDrawInfo* drawInfo)
{
    _drawInfo = drawInfo;
}

// --------------------------------------------------------------------------
// Input / output

void
IlvColorGadgetItem::write(IlvOutputFile& os) const
{
    IlvGadgetItem::write(os);
}

// ----------------------------------------------------------------------
IlvColorGadgetItem::IlvColorGadgetItem(IlvInputFile& file,
				       IlvDisplay* holder)
    : IlvGadgetItem(file, holder),
      _drawInfo(0)
{
}

// --------------------------------------------------------------------------
// IlvColorComboBox methods
// --------------------------------------------------------------------------
// Constructors / destructor

IlvColorComboBox::IlvColorComboBox(IlvDisplay*        display,
				   const IlvPoint&    point,
				   IlUShort           thickness,
				   IlvPalette*        palette)
    : IlvScrolledComboBox(display, point, "", 0, 0,  thickness, palette),
      _drawInfo(display)
{
    getStringList()->setLabelOffset(IlvColorDrawInfo::_DefaultLabelOffset);
    setEditable(IlFalse);
}

// --------------------------------------------------------------------------
IlvColorComboBox::IlvColorComboBox(IlvDisplay*        display,
				   const IlvRect&     rect,
				   IlUShort          thickness,
				   IlvPalette*        palette)
    : IlvScrolledComboBox(display, rect, "", 0, 0, thickness, palette),
      _drawInfo(display)
{
    getStringList()->setLabelOffset(IlvColorDrawInfo::_DefaultLabelOffset);
    setEditable(IlFalse);
}

// --------------------------------------------------------------------------
IlvColorComboBox::IlvColorComboBox(const IlvColorComboBox& source)
    : IlvScrolledComboBox(source),
      _drawInfo(source._drawInfo)
{
    getStringList()->setLabelOffset(source.getStringList()->getLabelOffset());
    updateItemsDrawInfo();
}

// --------------------------------------------------------------------------
IlvColorComboBox::~IlvColorComboBox()
{
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::setMode(IlvDrawMode mode)
{
    _drawInfo._drawMode = mode;
    IlvScrolledComboBox::setMode(mode);
}
/*
// --------------------------------------------------------------------------
const IlvDim tfRightMargin = 3; // internal margins  give place for cursor
const IlvDim tfLeftMargin = 3;

static void
ComputeTextArea(const IlvTextField*   textField,
		const IlvTransformer* t,
		IlvRect& bbox)
{
    if (t)
	t->apply(bbox);
    IlvUShort thickness = textField->getThickness();
    if ((bbox.w() <= tfRightMargin + tfLeftMargin + 2 * thickness) ||
	(bbox.h() <= (IlvDim)(2 * thickness))) {
	bbox.resize(0, 0);
	return;
    }
    bbox.translate(tfLeftMargin + thickness, thickness);
    bbox.grow(-(IlvPos)tfRightMargin - (IlvPos)tfLeftMargin
              - 2 * (IlvPos)thickness, -2 * (IlvPos)thickness);
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::draw(IlvPort* dst,
		       const IlvTransformer* t,
		       const IlvRegion* clip) const
{
    IlvScrolledComboBox::draw(dst, t, clip);

    IlvGadgetItem* gadgetItem =
	    (whichSelected() == (IlvShort)-1? 0 : getItem(whichSelected()));
    IlvColor* color =
	(gadgetItem? getDisplay()->getColor(gadgetItem->getLabel()) : 0);
    if (!color)
	return;

    // Get color rectangle bbox
    IlvRect bbox;
    IlvScrolledComboBox::getTextBBox(bbox);
    IlvStringList* stringList = getStringList();
    IlvDim offset = stringList->getLabelOffset();
    bbox.expand(-_horizontalRectColorMargin, -_verticalRectColorMargin);
    bbox.setW(offset - _horizontalRectColorMargin -
	      _horizontalRectColorMargin);

    // Draw the color rectangle
    IlvPalette* palette =
	    getDisplay()->getPalette(
		    getDisplay()->getColor("Black"),
		    color);
    IlvDrawMode oldDrawMode = palette->getMode();
    palette->setMode(_drawMode);
    getDisplay()->fillRectangle(dst, palette, bbox);
    palette->setMode(oldDrawMode);
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::drawText(IlvPort* dst,
			   const IlvTransformer* t,
		           const IlvRegion* clip) const
{
    IlvScrolledComboBox::drawText(dst, t, clip);
    return;
    // Get selected color
    IlvShort selection = whichSelected();
    IlvGadgetItem* gadgetItem = (selection == (IlvShort)-1? 0 : getItem(selection));
    IlvColor* color = (gadgetItem?getDisplay()->getColor(gadgetItem->getLabel()) : 0);
    if (!color) {
	IlvScrolledComboBox::drawText(dst, t, clip);
	return;
    }

    // Get color rectangle bbox
    IlvRect bbox;
    IlvScrolledComboBox::getTextBBox(bbox);
    ComputeTextArea(this, t, bbox);

    IlvStringList* stringList = getStringList();
    IlvDim offset = stringList->getLabelOffset();
    bbox.expand(-_horizontalRectColorMargin, -_verticalRectColorMargin);
    bbox.setW(offset - _horizontalRectColorMargin -
	      _horizontalRectColorMargin);

    // Draw the color rectangle
    IlvPalette* palette =
	    getDisplay()->getPalette(
		    getDisplay()->getColor("Black"),
		    color);
    IlvDrawMode oldDrawMode = palette->getMode();
    palette->setMode(_drawMode);
    getDisplay()->fillRectangle(dst, palette, bbox);
    palette->setMode(oldDrawMode);
    
    // Draw the text
    IlvScrolledComboBox::drawText(dst, t, clip);
}
*/
// --------------------------------------------------------------------------
IlvGadgetItem*
IlvColorComboBox::createItem(const char* label,
			     IlvGraphic*,
			     IlvBitmap*,
			     IlvBitmap*,
			     IlvBoolean) const
{
    return new IlvColorGadgetItem(getDisplay()->getColor(label), &_drawInfo);
}

// --------------------------------------------------------------------------
/*
void
IlvColorComboBox::getTextBBox(IlvRect& bbox) const
{
    IlvScrolledComboBox::getTextBBox(bbox);
    
    IlvStringList* stringList = getStringList();
    IlvDim offset = stringList->getLabelOffset();
    bbox.translate((IlvPos)offset, 0);
    bbox.setW(bbox.getW() - offset);
}
*/
// --------------------------------------------------------------------------
IlvColor*
IlvColorComboBox::getSelectedColor()const
{
    const char* colorName = getLabel();
    return getDisplay()->getColor(colorName);
}

// --------------------------------------------------------------------------
IlvUShort
IlvColorComboBox::insertColor(IlvColor* color,
			      IlShort pos)
{
    return insertItem(new IlvColorGadgetItem(color, &_drawInfo), pos);
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::setColors(IlvColor* const* colors,
			    IlUShort count)
{
    if (!count) {
	setLabels(0, 0);
	return;
    }
    IlvGadgetItem** items = new IlvGadgetItem*[count];
    for(IlUShort iItem = 0; iItem < count; iItem++) {
	items[iItem] = new IlvColorGadgetItem(colors[iItem], &_drawInfo);
    }
    setItems(items, count);
    delete []items;
}

// --------------------------------------------------------------------------
// Getting infos
IlvBoolean
IlvColorComboBox::isShowingColorRect()const
{
    return isShowingPicture();
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::showColorRect(IlvBoolean bShow)
{
    getStringList()->showPicture(bShow);
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::setColorRectMarings(IlvInt hMargin,
				      IlvInt vMargin,
				      IlBoolean)
{
    _drawInfo._horizontalRectColorMargin =
	    (hMargin == -1? _drawInfo._horizontalRectColorMargin :
			    (IlUShort)hMargin);
    _drawInfo._verticalRectColorMargin =
	    (vMargin == -1? _drawInfo._verticalRectColorMargin :
			    (IlUShort)vMargin);
}

// --------------------------------------------------------------------------
IlInt
IlvColorComboBox::getVColorRectMargin() const
{
    return (IlInt)(IlUInt)_drawInfo._verticalRectColorMargin;
}

// --------------------------------------------------------------------------
IlInt
IlvColorComboBox::getHColorRectMargin() const
{
    return (IlInt)(IlUInt)_drawInfo._horizontalRectColorMargin;
}

// --------------------------------------------------------------------------
const IlvColorDrawInfo&
IlvColorComboBox::getColorDrawInfo() const
{
    return _drawInfo;
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::updateItemsDrawInfo()
{
    for(IlShort iItem = 0, count = getCardinal(); iItem < count; iItem++)
	((IlvColorGadgetItem*)getItem(iItem))->setDrawInfo(&_drawInfo);
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::drawInfoModified()
{
}

// --------------------------------------------------------------------------
IlvValue&
IlvColorComboBox::queryValue(IlvValue& arg) const
{
    if (_drawInfo.queryValue(arg).getType() != IlvValueNoType)
	return arg;
    if (arg.getName() == IlvListGadgetItemHolder::_labelOffsetValue) {
	return getStringList()->queryValue(arg);
    }

    return IlvScrolledComboBox::queryValue(arg);
}

// --------------------------------------------------------------------------
IlBoolean
IlvColorComboBox::applyValue(const IlvValue& arg)
{
    if (_drawInfo.applyValue(arg)) {
	drawInfoModified();
	return IlTrue;
    }
    if (arg.getName() == IlvListGadgetItemHolder::_labelOffsetValue) {
	getStringList()->applyValue(arg);
	drawInfoModified();
	return IlTrue;
    }
    
    return IlvScrolledComboBox::applyValue(arg);
}

// --------------------------------------------------------------------------
void
IlvColorComboBox::GetAccessors(const IlvSymbol* const** a,
			       const IlvValueTypeClass* const** t,
			       IlUInt& c)
{
    IlvColorDrawInfo::GetAccessors(a, t, c);
}

// ----------------------------------------------------------------------
// Input / output

void
IlvColorComboBox::write(IlvOutputFile& os) const
{
    IlvScrolledComboBox::write(os);
    IlvDim offset = getStringList()->getLabelOffset();
    os.getStream() << IlvSpc() << offset
		   << IlvSpc() << _drawInfo._smallColorRect
		   << IlvSpc() << _drawInfo._colorRoundRectRadius
    		   << IlvSpc() << _drawInfo._horizontalRectColorMargin
		   << IlvSpc() << _drawInfo._verticalRectColorMargin
		   << IlvSpc();
}

// ----------------------------------------------------------------------
IlvColorComboBox::IlvColorComboBox(IlvInputFile& is,
				   IlvPalette* palette)
    : IlvScrolledComboBox(is, palette),
      _drawInfo((palette? palette->getDisplay() : 0))
{
    IlvDim offset;
    is.getStream() >> offset;
    is.getStream() >> _drawInfo._smallColorRect;
    is.getStream() >> _drawInfo._colorRoundRectRadius;
    is.getStream() >> _drawInfo._horizontalRectColorMargin;
    is.getStream() >> _drawInfo._verticalRectColorMargin;
    getStringList()->setLabelOffset(offset);
    updateItemsDrawInfo();
}

// --------------------------------------------------------------------------
// IlvColorStringList methods
// --------------------------------------------------------------------------
// Constructors / destructor

IlvColorStringList::IlvColorStringList(IlvDisplay*        display,
				       const IlvPoint&    point,
				       IlUShort          thickness,
				       IlvPalette*        palette)
    : IlvStringList(display, point, 0, 0,  thickness, palette),
      _drawInfo(display)
{
    setLabelOffset(IlvColorDrawInfo::_DefaultLabelOffset);
    setEditable(IlFalse);
}

// --------------------------------------------------------------------------
IlvColorStringList::IlvColorStringList(IlvDisplay*        display,
				       const IlvRect&     rect,
				       IlUShort          thickness,
				       IlvPalette*        palette)
    : IlvStringList(display, rect, 0, 0, thickness, palette),
      _drawInfo(display)
{
    setLabelOffset(IlvColorDrawInfo::_DefaultLabelOffset);
    setEditable(IlFalse);
}

// --------------------------------------------------------------------------
IlvColorStringList::IlvColorStringList(const IlvColorStringList& source)
    : IlvStringList(source),
      _drawInfo(source._drawInfo)
{
    updateItemsDrawInfo();
}

// --------------------------------------------------------------------------
IlvColorStringList::~IlvColorStringList()
{
}

// --------------------------------------------------------------------------
void
IlvColorStringList::setMode(IlvDrawMode mode)
{
    _drawInfo._drawMode = mode;
    IlvStringList::setMode(mode);
}

// --------------------------------------------------------------------------
IlvGadgetItem*
IlvColorStringList::createItem(const char* label,
			       IlvGraphic*,
			       IlvBitmap*,
			       IlvBitmap*,
			       IlBoolean) const
{
    return new IlvColorGadgetItem(getDisplay()->getColor(label), &_drawInfo);
}

// --------------------------------------------------------------------------
IlvColor*
IlvColorStringList::getSelectedColor() const
{
    const char* colorName = getSelection();
    return getDisplay()->getColor(colorName);
}

// --------------------------------------------------------------------------
IlUShort
IlvColorStringList::insertColor(IlvColor* color,
				IlShort pos)
{
    return insertItem(new IlvColorGadgetItem(color, &_drawInfo), pos);
}

// --------------------------------------------------------------------------
void
IlvColorStringList::setColors(IlvColor* const* colors,
			      IlUShort count)
{
    if (!count) {
	setLabels(0, 0);
	return;
    }
    IlvGadgetItem** items = new IlvGadgetItem*[count];
    for(IlUShort iItem = 0; iItem < count; iItem++) {
	items[iItem] = new IlvColorGadgetItem(colors[iItem], &_drawInfo);
    }
    setItems(items, count);
    delete []items;
}

// --------------------------------------------------------------------------
// Getting infos
IlBoolean
IlvColorStringList::isShowingColorRect() const
{
    return isShowingPicture();
}

// --------------------------------------------------------------------------
void
IlvColorStringList::showColorRect(IlBoolean bShow)
{
    showPicture(bShow);
}

// --------------------------------------------------------------------------
void
IlvColorStringList::setColorRectMarings(IlvInt hMargin,
				        IlvInt vMargin,
				        IlBoolean)
{
    _drawInfo._horizontalRectColorMargin =
	    (hMargin == -1? _drawInfo._horizontalRectColorMargin :
			    (IlUShort)hMargin);
    _drawInfo._verticalRectColorMargin =
	    (vMargin == -1? _drawInfo._verticalRectColorMargin :
			    (IlUShort)vMargin);
    drawInfoModified();
}

// --------------------------------------------------------------------------
IlInt
IlvColorStringList::getVColorRectMargin() const
{
    return (IlInt)(IlUInt)_drawInfo._verticalRectColorMargin;
}

// --------------------------------------------------------------------------
IlInt
IlvColorStringList::getHColorRectMargin() const
{
    return (IlInt)(IlUInt)_drawInfo._horizontalRectColorMargin;
}

// --------------------------------------------------------------------------
const IlvColorDrawInfo&
IlvColorStringList::getColorDrawInfo() const
{
    return _drawInfo;
}

// --------------------------------------------------------------------------
void
IlvColorStringList::updateItemsDrawInfo()
{
    for(IlShort iItem = 0, count = getCardinal(); iItem < count; iItem++)
	((IlvColorGadgetItem*)getItem(iItem))->setDrawInfo(&_drawInfo);
}

// --------------------------------------------------------------------------
void
IlvColorStringList::drawInfoModified()
{
    reDraw();
}

// --------------------------------------------------------------------------
IlvValue&
IlvColorStringList::queryValue(IlvValue& arg) const
{
    if (_drawInfo.queryValue(arg).getType() != IlvValueNoType)
	return arg;

    return IlvStringList::queryValue(arg);
}

// --------------------------------------------------------------------------
IlBoolean
IlvColorStringList::applyValue(const IlvValue& arg)
{
    if (_drawInfo.applyValue(arg)) {
	drawInfoModified();
	return IlTrue;
    }
    if (arg.getName() == IlvListGadgetItemHolder::_labelOffsetValue) {
	IlvStringList::applyValue(arg);
	drawInfoModified();
	return IlTrue;
    }
    
    return IlvStringList::applyValue(arg);
}

// --------------------------------------------------------------------------
void
IlvColorStringList::GetAccessors(const IlvSymbol* const** a,
			         const IlvValueTypeClass* const** t,
			         IlUInt& c)
{
    IlvColorDrawInfo::GetAccessors(a, t, c);
}

// ----------------------------------------------------------------------
// Input / output

void
IlvColorStringList::write(IlvOutputFile& os) const
{
    IlvStringList::write(os);
    os.getStream() << IlvSpc() << _drawInfo._smallColorRect
		   << IlvSpc() << _drawInfo._colorRoundRectRadius
		   << IlvSpc() << _drawInfo._horizontalRectColorMargin
		   << IlvSpc() << _drawInfo._verticalRectColorMargin
		   << IlvSpc();
}

// ----------------------------------------------------------------------
IlvColorStringList::IlvColorStringList(IlvInputFile& is,
				       IlvPalette* palette)
    : IlvStringList(is, palette),
      _drawInfo((palette? palette->getDisplay() : 0))
{
    is.getStream() >> _drawInfo._smallColorRect;
    is.getStream() >> _drawInfo._colorRoundRectRadius;
    is.getStream() >> _drawInfo._horizontalRectColorMargin;
    is.getStream() >> _drawInfo._verticalRectColorMargin;
    updateItemsDrawInfo();
}

// ----------------------------------------------------------------------
// Static infos
IlvPredefinedGadgetItemIOMembers(IlvColorGadgetItem)
IlvPredefinedIOMembers(IlvColorComboBox)
IlvPredefinedIOMembers(IlvColorStringList)

// ----------------------------------------------------------------------
IlvSymbol* IlvColorDrawInfo::_SmallColorRectValue;
IlvSymbol* IlvColorDrawInfo::_ColorRoundRectRadius;
IlvSymbol* IlvColorDrawInfo::_HColorRectMarginValue;
IlvSymbol* IlvColorDrawInfo::_VColorRectMarginValue;
IlvSymbol* IlvColorDrawInfo::_ColorInfosValue;

IlvPreRegisterClass(IlvColorDrawInfo);
IlvPreRegisterClass(IlvColorComboBox);
IlvPreRegisterClass(IlvColorStringList);
IlvPreRegisterGadgetItemClass(IlvColorGadgetItem);

IL_BEGINMODULEINITDEF(colorbox)
IlvColorDrawInfo::_SmallColorRectValue = IlvGetSymbol("SmallColorRect");
IlvColorDrawInfo::_ColorRoundRectRadius = IlvGetSymbol("ColorRoundRectRadius");
IlvColorDrawInfo::_HColorRectMarginValue = IlvGetSymbol("HColorMargin");
IlvColorDrawInfo::_VColorRectMarginValue = IlvGetSymbol("VColorMargin");
IlvColorDrawInfo::_ColorInfosValue = IlvGetSymbol("ColorsInfos");
ILVPOSTDEFINECLASSINFOMEMBERS(IlvColorDrawInfo,
			      IlvGraphicClassInfo:: Create("IlvColorDrawInfo",
							   0, 0,
							   IlvColorDrawInfo::GetAccessors));
IlvPostRegisterClassWithAccessors(IlvColorComboBox, IlvScrolledComboBox);
IlvPostRegisterClassWithAccessors(IlvColorStringList, IlvStringList);
IlvPostRegisterGadgetItemClass(IlvColorGadgetItem, IlvGadgetItem);
IlvRegisterClassCodeInformation(IlvColorComboBox,"colorbox.h","");
IlvRegisterClassCodeInformation(IlvColorStringList,"colorbox.h","");
IL_ENDMODULEINITDEF(colorbox)
