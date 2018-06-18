// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/src/pickerbar.cpp
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
// Definition of the PickerBar control.
// --------------------------------------------------------------------------
#include <pickerbar.h>
#include <palettechanger.h>

IlvPoint PickerBar::_Points[25];

// --------------------------------------------------------------------------
PickerBar::PickerBar(IlvDisplay* display,
		     IlUInt nLabels, const char* const* labels,
		     const IlvRect& location)
: IlvGadget(display, location),
  _nLabels(0),
  _labels(0),
  _radiusRatio(100),
  _selected(-1),
  _drawLabels(IlTrue),
  _barHorizontalMargin(0),
  _barVerticalMargin(0),
  _knobHorizontalMargin(0),
  _knobVerticalMargin(0),
  _knobsMargin(2),
  _invertedPalette(0),
  _labelsPalette(0),
  _knobPalette(0),
  _invertedKnobPalette(0),
  _interactiveKnob((IlUInt)-1),
  _savedSelected((IlUInt)-1)
{
    setLabels(nLabels, labels);
    _invertedPalette = display->getInvertedPalette(getPalette());
    _invertedPalette->lock();
    _labelsPalette = getPalette();
    _labelsPalette->lock();
    _knobPalette = _invertedPalette;
    _knobPalette->lock();
    _invertedKnobPalette = getPalette();
    _invertedKnobPalette->lock();
}

// --------------------------------------------------------------------------
PickerBar::~PickerBar()
{
    deleteLabels();
    _invertedPalette->unLock();
    _labelsPalette->unLock();
    _knobPalette->unLock();
    _invertedKnobPalette->unLock();
}

// --------------------------------------------------------------------------
void
PickerBar::setSelected(IlUInt selected)
{
    if ((selected != (IlUInt)-1) && (selected >= _nLabels)) {
	_selected = _nLabels - 1;
    }
    else {
	_selected = selected;
    }
}

// --------------------------------------------------------------------------
void
PickerBar::setLabels(IlUInt nLabels, const char* const* labels)
{
    deleteLabels();
    if (nLabels > 0) {
	_labels = new char*[nLabels];
	for (IlUInt loop = 0; loop < nLabels; loop++) {
	    // Keep empty labels as is
	    _labels[loop] = IlCopyString(labels[loop], IlFalse);
	}
	// Make sure selection is accurate
	if ((_selected != (IlUInt)-1) && (_selected >= nLabels)) {
	    _selected = nLabels-1;
	}
	_nLabels = nLabels;
    }
    else {
	_selected = (IlUInt)-1;
    }
}

// --------------------------------------------------------------------------
void
PickerBar::setRadiusRatio(IlUShort ratio)
{
    if (ratio > 100) {
	ratio = 100;
    }
    _radiusRatio = ratio;
}

// --------------------------------------------------------------------------
void
PickerBar::setInvertedPalette(IlvPalette* palette)
{
    palette->lock();
    _invertedPalette->unLock();
    _invertedPalette = palette;
}

// --------------------------------------------------------------------------
void
PickerBar::setKnobPalette(IlvPalette* knobPalette)
{
    knobPalette->lock();
    _knobPalette->unLock();
    _knobPalette = knobPalette;
}

// --------------------------------------------------------------------------
IlvPalette*
PickerBar::getLabelPalette(IlUInt index) const
{
    return _labelsPalette;
}

// --------------------------------------------------------------------------
IlvPalette*
PickerBar::getKnobPalette(IlUInt index) const
{
    return _knobPalette;
}

// --------------------------------------------------------------------------
IlvPalette*
PickerBar::getKnobLabelPalette(IlUInt index) const
{
    return _knobPalette;
}

// --------------------------------------------------------------------------
IlvPos
PickerBar::getKnobLabelOffset(IlUInt) const
{
    return 0;
}

// --------------------------------------------------------------------------
IlvPos
PickerBar::getKnobPosition(IlUInt index, const IlvTransformer* t) const
{
    if (index > _nLabels) {
	return 0;
    }
    IlvRect bBox;
    boundingBox(bBox, t);
    if ((_nLabels < 2)        ||
	(index == (IlUInt)-1)) {
	return bBox.centerx();
    }
    IlvPos  knobCenter;
    IlvRect knobBox;
    getKnobGeometry(bBox, index, knobCenter, knobBox);
    return knobCenter;
}

// --------------------------------------------------------------------------
void
PickerBar::setBackground(IlvColor* background)
{
    // Propagate to all known palettes
    IlvGadget::setBackground(background);
    _invertedPalette = PaletteChanger(_invertedPalette)
		       .setForeground(background).replace();
    _labelsPalette = PaletteChanger(_labelsPalette)
		     .setBackground(background).replace();
    _knobPalette = PaletteChanger(_knobPalette)
		   .setForeground(background).replace();
    _invertedKnobPalette = PaletteChanger(_invertedKnobPalette)
			   .setBackground(background).replace();
}

// --------------------------------------------------------------------------
void
PickerBar::setFont(IlvFont* font)
{
    // Propagate to all known palettes
    IlvGadget::setFont(font);
    _invertedPalette = PaletteChanger(_invertedPalette)
		       .setFont(font).replace();
    _labelsPalette = PaletteChanger(_labelsPalette)
		     .setFont(font).replace();
    _knobPalette = PaletteChanger(_knobPalette)
		   .setFont(font).replace();
    _invertedKnobPalette = PaletteChanger(_invertedKnobPalette)
		 	   .setFont(font).replace();
}

// --------------------------------------------------------------------------
void
PickerBar::setAntialiasingMode(IlvAntialiasingMode mode)
{
    // Propagate to all known palettes
    IlvGadget::setAntialiasingMode(mode);
    _invertedPalette = PaletteChanger(_invertedPalette)
		       .setAntialiasingMode(mode).replace();
    _labelsPalette   = PaletteChanger(_labelsPalette)
		       .setAntialiasingMode(mode).replace();
    _knobPalette     = PaletteChanger(_knobPalette)
		       .setAntialiasingMode(mode).replace();
    _invertedKnobPalette = PaletteChanger(_invertedKnobPalette)
			   .setAntialiasingMode(mode).replace();
}

// --------------------------------------------------------------------------
void
PickerBar::drawBackground(IlvPort*              dst,
			  const IlvTransformer* t,
			  const IlvRegion*      clip) const
{
    IlvRect bBox;
    boundingBox(bBox, t);
    if ((bBox.w() > 2*_barHorizontalMargin)
	|| (bBox.h() > 2*_barVerticalMargin)) {
	bBox.expand((bBox.w() > 2*_barHorizontalMargin)
		    ? -(IlvPos)_barHorizontalMargin
		    : 0,
		    (bBox.h() > 2*_barVerticalMargin)
		    ? -(IlvPos)_barVerticalMargin
		    : 0);
    }
    IlUInt nPoints = computeShape(bBox);
    // Bar background
    if (nPoints != 0) {
	dst->fillBezier(_invertedPalette, nPoints, _Points);
	IlvPalette* antialias = PaletteChanger(getPalette())
				.setAntialiasingMode(IlvUseAntialiasingMode)
				.get();
	antialias->lock();
	dst->drawBezier(antialias, nPoints, _Points);
	antialias->unLock();
    }
    else {
	dst->fillRectangle(_invertedPalette, bBox);
	dst->drawRectangle(getPalette(), bBox);
    }
    // Draw labels
    if (!_drawLabels || (_nLabels == 0)      // No labels
	|| (bBox.w() <= 2 * _knobsMargin)) { // Too small to draw the labels?
	return;
    }
    if (_nLabels == 1) {
	if (_labels[0] != 0) {
	    IlvPalette* palette = getLabelPalette(0);
	    IlvPushClip clip(palette, &bBox);
	    IlvDim w, h, d;
	    palette->getFont()->sizes(_labels[0], -1, w, h, d);
	    dst->drawString(palette,
			    IlvPoint(bBox.x() + (bBox.w() - w) / 2,
				     bBox.y() + (bBox.h() - h) / 2 - d),
			    _labels[0], -1);
	}
    }
    else {
	IlvPos  knobCenter;
	IlvRect knobBox;
	for (IlUInt knob = 0; knob < _nLabels; knob++) {
	    const char* label = _labels[knob];
	    if (label != 0) {
		IlvPalette* palette = getLabelPalette(knob);
		getKnobGeometry(bBox, knob, knobCenter, knobBox);
		IlvPushClip clip(palette, &bBox);
		IlvDim w, h, d;
		palette->getFont()->sizes(label, -1, w, h, d);
		dst->drawString(palette,
				IlvPoint(knobCenter - w / 2,
					 bBox.y() + (bBox.h() + h) / 2 - d),
				label, -1);
	    }
	}
    }
}

// --------------------------------------------------------------------------
void
PickerBar::drawFrame(IlvPort*		  dst,
		     const IlvTransformer* t,
		     const IlvRegion*	  clip) const
{
}

// --------------------------------------------------------------------------
void
PickerBar::drawContents(IlvPort*              dst,
		        const IlvTransformer* t,
		        const IlvRegion*      clip) const
{
    if (_nLabels == 0) {
	return;
    }
    IlvRect bBox;
    IlvPos  knobCenter;
    IlvRect knobBox;
    if (!getKnobGeometry(bBox, t, knobCenter, knobBox)
	&& (knobBox.w() > 0)) {
	return;
    }
    // Draw the knob label...
    if (_selected == (IlInt)-1) {
	return;
    }
    drawKnob(_selected, dst, knobBox, clip);
    const char* label = _labels[_selected];
    if (label == 0) { // ... if there is one.
	return;
    }
    IlvPalette* labelPalette = getKnobLabelPalette(_selected);
    if (labelPalette == 0) {
	return;
    }
    IlvPushClip knobClip(labelPalette, &knobBox);
    IlvDim w, h, d;
    labelPalette->getFont()->sizes(label, -1, w, h, d);
    dst->drawString(labelPalette,
		    IlvPoint(knobCenter - w / 2,
			     bBox.y() + (bBox.h() + h) / 2 - d),
		    label, -1);
}

// --------------------------------------------------------------------------
void
PickerBar::computeFocusRegion(IlvRegion&		region,
    const IlvTransformer*	t) const
{
    IlvRect bbox;
    boundingBox(bbox, t);
    bbox.expand(4); // line width + antialiasing
    region.add(bbox);
}

// --------------------------------------------------------------------------
void
PickerBar::drawFocus(IlvPort* dst,
		     const IlvPalette* palette,
		     const IlvTransformer* t,
		     const IlvRegion* clip) const
{
    IlvRect bBox;
    boundingBox(bBox, t);
    bBox.translate(-2, -2);
    bBox.grow(5, 5);
    IlUInt nPoints = computeShape(bBox);
    IlvPalette* pal = PaletteChanger(getPalette())
		      .setLineWidth(2)
		      .setAntialiasingMode(IlvUseAntialiasingMode)
		      .get();
    pal->lock();
    {
	IlvPushClip(*pal, clip);
	if (nPoints != 0) {
	    dst->drawBezier(pal, nPoints, _Points);
	}
	else {
	    dst->drawRectangle(pal, bBox);
	}
    }
    pal->unLock();
}

// --------------------------------------------------------------------------
IlBoolean
PickerBar::classFocusable() const
{
    return isShowingFrame();
}

// --------------------------------------------------------------------------
IlBoolean
PickerBar::handleEvent(IlvEvent& event)
{
    switch (event.getType()) {
    case IlvButtonDown:
	if (event.getKey() == IlvLeftButton) {
	    return handleButtonDown(event);
	}
	break;
    case IlvButtonDragged:
	if (event.getKey() == IlvLeftButton) {
	    return handleButtonDragged(event);
	}
	break;
    case IlvButtonUp:
	if (event.getKey() == IlvLeftButton) {
	    return handleButtonUp(event);
	}
	break;
    case IlvKeyDown:
	if ((event.key() == IlvLeftKey) ||
	    (event.key() == IlvDownKey)) {
	    selectPrevious();
	}
	else if ((event.key() == IlvRightKey) ||
		 (event.key() == IlvUpKey)) {
	    selectNext();
	}
	else if (event.key() == IlvEscape) {
	    if (_interactiveKnob != (IlUInt)-1) {
		_selected = _savedSelected;
		callSelectionCallback(_selected);
		reDraw();
		_interactiveKnob = (IlUInt)-1;
	    }
	}
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
void
PickerBar::selectNext()
{
    if ((_selected != (IlUInt)-1) && (_nLabels > 1)) {
	if (_selected == _nLabels - 1) {
	    _selected = 0;
	}
	else {
	    _selected++;
	}
	callSelectionCallback(_selected);
	reDraw();
    }
}

// --------------------------------------------------------------------------
void
PickerBar::selectPrevious()
{
    if ((_selected != -1) && (_nLabels > 1)) {
	if (_selected == 0) {
	    _selected = _nLabels - 1;
	}
	else {
	    _selected--;
	}
	callSelectionCallback(_selected);
	reDraw();
    }
}

// --------------------------------------------------------------------------
void
PickerBar::callSelectionCallback(IlUInt)
{
    callCallback();
}

// --------------------------------------------------------------------------
void
PickerBar::drawKnob(IlUInt           index,
		    IlvPort*         dst,
		    const IlvRect&   knobBox,
		    const IlvRegion* clip) const
{
    if (index == (IlUInt)-1) {
	return;
    }
    IlUInt nPoints = computeShape(knobBox);
    IlvPalette* palette = getKnobPalette(index);
    IlvPalette* bgPalette = PaletteChanger(palette)
			    .setForeground(palette->getBackground()).get();
    // No outline if foreground == background
    bgPalette->lock();
    if (palette->getForeground() == palette->getBackground()) {
	palette = 0;
    }
    if (nPoints != 0) {
	dst->fillBezier(bgPalette, nPoints, _Points);
	if (palette) {
	    dst->drawBezier(palette, nPoints, _Points);
	}
    }
    else {
	dst->fillRectangle(bgPalette, knobBox);
	if (palette) {
	    dst->drawRectangle(palette, knobBox);
	}
    }
    bgPalette->unLock();
}

// --------------------------------------------------------------------------
// Computes a rounded rectangle shape, that has the indicated dimensions,
// where _radiusRatio is used.
// The shape is stored in the _Points points array, as a series of Bezier
// curve control points.
// This method returns the number of control points, or 0 if the rectangle
// is so small that it would be irrelevant to
IlUInt
PickerBar::computeShape(const IlvRect& box) const
{
    if (!_radiusRatio) {
	return 0;
    }
    /* 1 - ((4 / 3)*tan(PI / 8) = 4 * (sqrt(2) - 1) / 3) */
    static const double bezierCircleWeight = 1 - 0.5523;
    IlInt thickness = getLineWidth() >> 1;
    IlInt l = box.x() + thickness;
    IlInt r = box.right() - thickness - 1;
    IlInt t = box.y() + thickness;
    IlInt b = box.bottom() - thickness - 1;
    IlvDim h = _radiusRatio * (IlvDim)(r - l) / 200;
    if (h == 0) {
	return 0;
    }
    IlvDim v = _radiusRatio * (IlvDim)(b - t) / 200;
    if (v == 0) {
	return 0;
    }
    // Use the smallest corner radius value
    IlvDim cr = (h > v) ? v : h;
    IlvPoint* p = _Points;
    IlUInt nPoints = 0;
    IlInt pos = 0;
    p[0].move(l, t + cr);
    p[1].move(l, t + (IlInt)(cr * bezierCircleWeight));
    p[2].move(l + (IlInt)(cr * bezierCircleWeight), t);
    p += 3;
    nPoints += 3;
    pos = l + cr;
    if ((pos + (IlInt)cr) < r) { // Top side
	p[0].move(pos, t);
	p[1].move(pos, t);
	p[2].move(r - cr, t);
	p += 3;
	nPoints += 3;
    }
    p[0].move(r - cr, t);
    p[1].move(r - (IlInt)(cr * bezierCircleWeight), t);
    p[2].move(r, t + (IlInt)(cr * bezierCircleWeight));
    p += 3;
    nPoints += 3;
    pos = t + cr;

    if ((pos + (IlInt)cr) < b) { // Right side
	p[0].move(r, pos);
	p[1].move(r, pos);
	p[2].move(r, b - cr);
	p += 3;
	nPoints += 3;
    }
    p[0].move(r, b - cr);
    p[1].move(r, b - (IlInt)(cr * bezierCircleWeight));
    p[2].move(r - (IlInt)(cr * bezierCircleWeight), b);
    p += 3;
    nPoints += 3;
    pos = r - cr;
    if (pos > (IlInt)(l + cr)) { // Bottom side
	p[0].move(pos, b);
	p[1].move(pos, b);
	p[2].move(l + cr, b);
	p += 3;
	nPoints += 3;
    }
    p[0].move(l + cr, b);
    p[1].move(l + (IlInt)(cr * bezierCircleWeight), b);
    p[2].move(l, b - (IlInt)(cr * bezierCircleWeight));
    p += 3;
    nPoints += 3;
    p[0].move(l, b - cr);
    p += 1;
    nPoints += 1;
    if (b - cr > t + cr) { // Left side
	p[0].move(l, b - cr);
	p[1].move(l, t + cr);
	p[2].move(l, t + cr);
	nPoints += 3;
    }
    return nPoints;
}

// --------------------------------------------------------------------------
IlBoolean
PickerBar::getKnobGeometry(IlvRect& bBox,
			   const IlvTransformer* t,
			   IlvPos&  knobCenter,
			   IlvRect& knobBox) const
{
    boundingBox(bBox, t);
    // Too small to hold the knobs?
    if (!_nLabels                      || // No labels?
	(bBox.w() <= 2 * _knobsMargin) || // Too narrow to hold the knobs?
	(bBox.h() <= 2 * _knobsMargin) || // Too flat to hold the knobs?
	(bBox.w() < bBox.h())) {          // Too flat to several knobs?
	return IlFalse;
    }
    IlvDim knobSize = bBox.h();
    if ((_selected == (IlInt)-1)       || // No selection?
        ((_knobHorizontalMargin > 0) &&
	 (knobSize < 2 * (IlvDim)_knobHorizontalMargin)) ||
	(knobSize < 2 * _knobVerticalMargin)) {
	knobSize = 0;
	return IlTrue;
    }
    getKnobGeometry(bBox, _selected, knobCenter, knobBox);
    return IlTrue;
}

// --------------------------------------------------------------------------
void
PickerBar::getKnobGeometry(const IlvRect& bBox,
			   IlUInt   knob,
			   IlvPos&  knobCenter,
			   IlvRect& knobBox) const
{
    IlvDim  knobSize = bBox.h();
    if (bBox.w() < knobSize + 2 * _knobsMargin) {
	knobCenter = bBox.centerx();
	knobBox.resize(0, 0);
    }
    IlvDim  knobSpacing = (bBox.w() - knobSize - 2*_knobsMargin) / _nLabels;
    knobCenter = bBox.x() + _knobsMargin +
		 ((_nLabels > 1)
		  ? (knob * ((IlvPos)bBox.w() - knobSize - 2 * _knobsMargin)
		     / (_nLabels-1) + knobSize / 2)
		  : ((IlvPos)bBox.w() - (IlvPos)knobSize) / 2);
    knobBox.set(bBox.x() + _knobsMargin + _knobHorizontalMargin +
		((_nLabels > 1)
		 ? (knob * ((IlvPos)bBox.w() - knobSize - 2 * _knobsMargin)
		    / (_nLabels - 1))
		 : ((IlvPos)bBox.w() - (IlvPos)knobSize) / 2),
		bBox.y() + _knobVerticalMargin,
		knobSize - 2 * _knobHorizontalMargin,
		knobSize - 2 * _knobVerticalMargin);
}

// --------------------------------------------------------------------------
IlUInt
PickerBar::findKnob(const IlvRect& bBox, IlvPos x) const
{
    IlvPos  knobCenter;
    IlvRect knobBox;
    IlUInt  lastKnob = (IlUInt)-1;
    IlvDim  lastDistance;
    IlUInt  knob = (IlUInt)-1;
    for (knob = 0; knob < _nLabels; knob++) {
	getKnobGeometry(bBox, knob, knobCenter, knobBox);
	if (x == knobCenter) {
	    return knob;
	}
	else if (x < knobCenter) {
	    if (lastKnob == (IlUInt)-1) {
		return knob;
	    }
	    IlvDim distance = IL_CAST(IlvDim, knobCenter - x);
	    return (distance < lastDistance) ? knob : lastKnob;
	}
	else {
	    lastKnob = knob;
	    lastDistance = IL_CAST(IlvDim, x - knobCenter);
	}
    }
    return _nLabels-1;
}

// --------------------------------------------------------------------------
void
PickerBar::deleteLabels()
{
    if (_nLabels != 0) {
	for (IlUInt loop = 0; loop < _nLabels; loop++) {
	    if (_labels[loop] != 0) {
		delete [] _labels[loop];
	    }
	}
	delete [] _labels;
	_nLabels = 0;
    }
}

// --------------------------------------------------------------------------
IlBoolean
PickerBar::handleButtonDown(IlvEvent& event)
{
    // Nothing to interact with
    if (_nLabels < 2) {
	return IlFalse;
    }
    IlvRect bBox;
    IlvPos  knobCenter;
    IlvRect knobBox;
    if (!getKnobGeometry(bBox, getTransformer(), knobCenter, knobBox)) {
	return IlFalse;
    }
    IlUInt interactiveKnob = (IlUInt)-1;
    IlvPos evx = event.getLocation().getX();
    IlvPos evy = event.getLocation().getY();
    // In the selected knob?
    if ((_selected != (IlInt)-1) && (knobBox.w() > 0)
	&& knobBox.contains(IlvPoint(evx, evy))) {
	_savedSelected = _selected;
	_interactiveKnob = _selected;
    }
    else {
	IlUInt selected = findKnob(bBox, evx);
	if (_selected != selected) {
	    _selected = selected;
	    _savedSelected = _selected;
	    _interactiveKnob = _selected;
	    callSelectionCallback(_selected);
	    reDraw();
	}
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
PickerBar::handleButtonDragged(IlvEvent& event)
{
    // Nothing to interact with...
    if (_nLabels < 2) {
	return IlFalse;
    }
    // Not interacting
    if (_interactiveKnob == (IlInt)-1) {
	return IlFalse;
    }
    IlvRect bBox;
    boundingBox(bBox, getTransformer());
    IlUInt selected = findKnob(bBox, event.getX());
    if (_selected != selected) {
	_selected = selected;
	callSelectionCallback(_selected);
	reDraw();
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
PickerBar::handleButtonUp(IlvEvent& event)
{
    if (_interactiveKnob != (IlInt)-1) {
        _interactiveKnob = (IlInt)-1;
	return IlTrue;
    }
    return IlFalse;
}
