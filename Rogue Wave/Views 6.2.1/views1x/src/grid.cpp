// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/grid.cpp
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
// Definition of the IlvGridObj class
// --------------------------------------------------------------------------

#include <ilviews/grid.h>
#include <ilviews/base/hash.h>

#if defined(ILVSTD)
#include <iostream>
#else  /* !ILVSTD */
#include <iostream.h>
#endif /* ILVSTD */

ILVSTDUSE

const IlvUShort IlvDefaultGridSpacing = 2;

static IlvDim
PosInArray(IlvDim x, IlvDim* array, IlvDim size);

void IlvGridObj::invert(IlvBoolean) {}

// --------------------------------------------------------------------------
inline IlvGridElement*
getGridElement(const IlvGraphic* object)
{
    return
	(IlvGridElement*)(object->getProperty(IlvGridObj::_objectGridElement));
}

// --------------------------------------------------------------------------
IlvGridObj::IlvGridObj(IlvDisplay*          display,
		       const IlvRect&       rect,
		       IlvUShort            nbcol,
		       IlvUShort            nbrow,
		       IlvGridSelectionType sel,
		       IlvPalette*          palette)
: IlvReliefRectangle(display, rect, 0, palette),
  _selectiontype(sel),
  _columns(nbcol),
  _rows(nbrow),
  _spacing(IlvDefaultGridSpacing)
{
    _selections   = new IlvList();
    _showgrid     = IlvFalse;
    _reliefshadow = IlvTrue;
    if (_columns == 0)
	_columns  = 1;
    if (_rows == 0 )
	_rows     = 1;
    IlvUInt size  = _columns*_rows;
    _objects	  = new IlvGraphic* [size];
    _sameWidth	  = IlvTrue;
    _sameHeight   = IlvTrue;
    _colsize	  = new IlvDim [_columns + 1];
    _rowsize	  = new IlvDim [_rows    + 1];
    IlvDim xgrid  = _drawrect.w() / _columns,
	   ygrid  = _drawrect.h() / _rows;
    _drawrect.resize(xgrid*_columns, ygrid*_rows);
    IlvUShort i;
    for (i = 0; i <= _columns; ++i)
	_colsize[i] = (IlvDim)(i*xgrid);
    for (i = 0; i <= _rows;    ++i)
	_rowsize[i] = (IlvDim)(i*ygrid);
    for (IlvUInt loop = 0; loop <  size; ++loop)
	_objects[loop] = 0;
}

// --------------------------------------------------------------------------
IlvGridObj::~IlvGridObj()
{
    delete _selections;
    for (int i = 0; i < (int)(_columns*_rows); ++i) {
	if (_objects[i] && _objects[i]->hasProperty(_objectGridElement)) {
	    IlvGraphic*     object  = _objects[i];
	    IlvGridElement* element = getGridElement(object);
	    // Erase references to this same object
	    for (IlvDim h = 0; h < element->height(); ++h) {
		IlvDim offset = i + h*_columns;
		for (IlvDim w = 0; w < element->width(); ++w)
		    _objects[offset++] = 0;
	    }
	    delete element;
	    object->removeProperty(_objectGridElement);
	    delete object;
	}
    }
    delete [] _objects;
    delete [] _colsize;
    delete [] _rowsize;
}

// --------------------------------------------------------------------------
IlvDim
IlvGridObj::getCardinal() const
{
    IlvDim count = 0;
    IlvUInt i;
    for (i = 0; i < (IlvUInt)(_columns*_rows); ++i) {
	if (_objects[i]) {
	    if (!getGridElement(_objects[i])->marked()) {
		++count;
		getGridElement(_objects[i])->marked(IlvTrue);
	    }
	}
    }
    for (i = 0; i < (IlvUInt)(_columns*_rows); ++i)
	if (_objects[i])
	    getGridElement(_objects[i])->marked(IlvFalse);
    return count;
}

// --------------------------------------------------------------------------
IlvBoolean
IlvGridObj::checkPosition(IlvUShort x, IlvUShort y) const
{
    return (IlvBoolean)((x < _columns) && (y < _rows));
}

// --------------------------------------------------------------------------
void
IlvGridObj::reshape(IlvGraphic* obj)
{
    IlvUShort posx, posy;
    IlvDim    w, h;
    objectPosition(obj, posx, posy, w, h);
    IlvDim xg = _colsize[posx+w] - _colsize[posx];
    IlvDim yg = _rowsize[posy+h] - _rowsize[posy];

    IlvUShort skipdelta = (IlvUShort)(_thickness+_spacing);
    if (obj->zoomable()) {
	obj->move(_drawrect.x()+_colsize[posx] + skipdelta,
		  _drawrect.y()+_rowsize[posy] + skipdelta);
	obj->resize((xg <= 2*(IlvDim)skipdelta) ? 1 : (xg-2*(IlvDim)skipdelta),
		    (yg <= 2*(IlvDim)skipdelta) ? 1 : (yg-2*(IlvDim)skipdelta));
    } else {
	IlvRect bbox;
	obj->boundingBox(bbox);
	IlvPos x, y;
	x = _colsize[posx] + (IlvPos)(xg - bbox.w()) / 2;
	y = _rowsize[posy] + (IlvPos)(yg - bbox.h()) / 2;
	obj->move(_drawrect.x()+x, _drawrect.y()+y);
    }
}

// --------------------------------------------------------------------------
void
IlvGridObj::add(IlvGraphic* obj,
		IlvBoolean  readonly,
		IlvGridObjectCallback c, IlvAny u,
		IlvDim w, IlvDim h)
{
    // Find first valid position
    IlvUInt pos;
    for (pos = 0; (pos < (IlvUInt)(_columns*_rows)) && _objects[pos]; ++pos)
	;
    if (pos == (IlvUInt)(_columns*_rows))
	return ;
    IlvUShort icol = (IlvUShort)(pos % (int)_columns);
    IlvUShort irow = (IlvUShort)(pos / (int)_columns);

    if (((IlvDim)(icol+w) > (IlvDim)_columns) ||
	((IlvDim)(irow+h) > (IlvDim)_rows))
	return;

    IlvDim  ww, hh;
    IlvUInt newpos;
    // Check room for wide objects.
    if ((w > 1) || (h > 1)) {
	for (ww = 0; ww < w; ++ww) {
	    newpos = pos+ww;
	    for (hh = 0; hh < h; ++hh, newpos += _columns)
		if (_objects[newpos])
		    return;
	}
    }
    // Everything's OK. Store that object.
    for (ww = 0; ww < w; ++ww) {
	newpos = pos+ww;
	for (hh = 0; hh < h; ++hh, newpos += _columns) {
	    _objects[newpos] = obj;
	}
    }
    IlvGridElement* element = new IlvGridElement(icol, irow,
					       c, u, readonly, w, h);
    obj->addProperty(_objectGridElement,(IlvAny)element);
    reshape(obj);
}

// --------------------------------------------------------------------------
void
IlvGridObj::add(IlvUShort posx, IlvUShort posy, IlvGraphic* obj,
		IlvBoolean readonly,
		IlvGridObjectCallback c,
		IlvAny u,
		IlvDim w, IlvDim h)
{
    if (((IlvDim)(posx+w) > (IlvDim)_columns) ||
	((IlvDim)(posy+h) > (IlvDim)_rows))
	return;
    if (!checkPosition(posx, posy)) {
	IlvFatalError("IlvGridObj::add: Invalid position");
	return;
    }
    IlvDim newpos, pos =(posy*_columns) + posx;
    IlvDim ww, hh;
    // There were images at that point. Delete them.
    // Check room for wide objects.
    for (ww = 0; ww < w; ++ww) {
	newpos = pos+ww;
	for (hh = 0; hh < h; ++hh, newpos += _columns)
	    if (_objects[newpos])
		remove(_objects[newpos]);
    }
    // Store that object.
    for (ww = 0; ww < w; ++ww) {
	newpos = pos + ww;
	for (hh = 0; hh < h; ++hh, newpos += _columns)
	    _objects[newpos] = obj;
    }
    IlvGridElement* element = new IlvGridElement(posx, posy,
					       c, u, readonly, w, h);
    obj->addProperty(_objectGridElement, (IlvAny)element);
    reshape(obj);
}

// --------------------------------------------------------------------------
IlvBoolean
IlvGridObj::objectPosition(const IlvGraphic* obj,
			   IlvUShort& icol,  IlvUShort& irow,
			   IlvDim&    width, IlvDim& height) const
{
    IlvGridElement* element = getGridElement(obj);
    if (element) {
	icol   = element->column();
	irow   = element->row();
	width  = element->width();
	height = element->height();
	return IlvTrue;
    } else
	return IlvFalse;
}

// --------------------------------------------------------------------------
IlvBoolean
IlvGridObj::objectBBox(const IlvGraphic* obj, IlvRect& bbox) const
{
    IlvGridElement* element = getGridElement(obj);
    if (element) {
	IlvUShort icol, irow,  width,  height;
	icol   = element->column();
	irow   = element->row();
	width  = (IlvUShort)element->width();
	height = (IlvUShort)element->height();
	IlvUShort skipdelta = (IlvUShort)(_thickness+_spacing);
	IlvDim xg = _colsize[icol+width] - _colsize[icol];
	IlvDim yg = _rowsize[irow+height] - _rowsize[irow];
	bbox.move(_drawrect.x()+_colsize[icol] + skipdelta,
		  _drawrect.y()+_rowsize[irow] + skipdelta);
	bbox.resize((xg <= 2*(IlvDim)skipdelta) ? 1 :
		    (xg - 2*(IlvDim)skipdelta),
		    (yg <= 2*(IlvDim)skipdelta) ? 1 :
		    (yg - 2*(IlvDim)skipdelta));
	return IlvTrue;
    } else
	return IlvFalse;
}

// --------------------------------------------------------------------------
void
IlvGridObj::remove(IlvGraphic* obj, IlvBoolean destroyIt)
{
    IlvUShort irow, icol;
    IlvDim    width, height;
    if (!objectPosition(obj, icol, irow, width, height)) {
	IlvWarning("IlvGridObj::remove: No such object");
	return;
    }
    IlvUInt pos = irow *  _columns + icol;
    if (_objects[pos] != obj) {
	IlvWarning("IlvGridObj::remove: Object not in GridObj");
	return;
    }
    IlvGridElement* element = getGridElement(obj);
    if (element->selected())
	makeUnSelected(obj);
    for (IlvDim i = 0; i < width; ++i) {
	for (IlvDim j = 0; j < height; ++j)
	    _objects[(irow+j)*_columns +(icol+i)] = 0;
    }
    obj->removeProperty(_objectGridElement);
    delete element;
    if (destroyIt)
	delete obj;
}

// --------------------------------------------------------------------------
IlvGridObjectCallback
IlvGridObj::getCallback(const IlvGraphic* obj) const
{
    IlvGridElement* element = getGridElement(obj);
    return element ? element->callback() : 0;
}

// --------------------------------------------------------------------------
IlvAny
IlvGridObj::getObjectArg(const IlvGraphic* obj) const
{
    IlvGridElement* element = getGridElement(obj);
    return element ? element->userArg() : 0;
}

// --------------------------------------------------------------------------
void
IlvGridObj::makeSelected(IlvGraphic* obj)
{
    IlvGridElement* element = getGridElement(obj);
    if (!element)
	return;
    if (_selectiontype == IlvGridExclusiveSelection)
	deSelect();
    element->selected(IlvTrue);
    if (_selectiontype != IlvGridNoSelection)
	_selections->insert(obj);
}

// --------------------------------------------------------------------------
void
IlvGridObj::makeUnSelected(IlvGraphic* obj)
{
    IlvGridElement* element = getGridElement(obj);
    if (!element)
	return;
    element->selected(IlvFalse);
    if (_selectiontype != IlvGridNoSelection)
	_selections->remove(obj);
}

// --------------------------------------------------------------------------
void
IlvGridObj::swapSelection(IlvGraphic* obj)
{
    if (isSelected(obj))
	makeUnSelected(obj);
    else
	makeSelected(obj);
}

// --------------------------------------------------------------------------
void
IlvGridObj::eraseObj(const IlvGraphic* obj, IlvPort* dst,
		     const IlvTransformer* t) const
{
    IlvUShort irow, icol;
    IlvDim    width, height;
    if (!objectPosition(obj, icol, irow, width, height))
	return;
    IlvRect prect(_drawrect.x() + _colsize[icol],
		 _drawrect.y() + _rowsize[irow],
		 _colsize[icol + width]  - _colsize[icol],
		 _rowsize[irow + height] - _rowsize[irow]);
    if (t)
	t->apply(prect);
    getDisplay()->clearArea(dst, prect);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvGridObj::getObject(IlvUShort posx, IlvUShort posy) const
{
    return checkPosition(posx, posy) ? _objects[posy*_columns+posx] : 0;
}

// --------------------------------------------------------------------------
void
IlvGridObj::drawObj(const IlvGraphic* obj, IlvPort* dst,
		    const IlvTransformer* t,
		    const IlvRegion* clip) const
{
    IlvUShort irow, icol;
    IlvDim    width, height;
    if (!objectPosition(obj, icol, irow, width, height))
	return;
    if (_showgrid)
	drawGrid(dst,
		 icol,
		 (IlvUShort)(icol+width),
		 irow,
		 (IlvUShort)(irow+height),
		 t,
		 clip);
    IlvRect prect(_drawrect.x()+_colsize[icol],
		  _drawrect.y()+_rowsize[irow],
		  _colsize[icol+width]-_colsize[icol],
		  _rowsize[irow+height]-_rowsize[irow]);
    if (t)
	t->apply(prect);
    IlvDisplay* display = getDisplay();
    if (_reliefshadow) {
	if (isSelected(obj))
	    display->drawReliefRectangle(dst,
					 _palette,
					 _selpalette,
					 _bottomshadow,
					 _topshadow,
					 prect,
					 _thickness,
					 clip);
	else
	    display->drawReliefRectangle(dst,
					 _palette,
					 _invpalette,
					 _topshadow,
					 _bottomshadow,
					 prect,
					 _thickness,
					 clip);
    } else if (isSelected(obj)) {
	IlvRect r1(prect.x(), prect.y(), prect.w(), _spacing);
	IlvRect r2(prect.x(), prect.y(), _spacing, prect.h());
	IlvRect r3(prect.right()-_spacing, prect.y(), _spacing, prect.h());
	IlvRect r4(prect.x(), prect.bottom()-_spacing, prect.w(), _spacing);
	display->fillRectangle(dst, _palette, r1);
	display->fillRectangle(dst, _palette, r2);
	display->fillRectangle(dst, _palette, r3);
	display->fillRectangle(dst, _palette, r4);
    }
    IlvRect objrect;
    obj->boundingBox(objrect, t);
    IlvUShort sdelta = (IlvUShort)(_spacing+_thickness);
    prect.translate(sdelta, sdelta);
    prect.grow(-(IlvDeltaPos)(2*sdelta), -(IlvDeltaPos)(2*sdelta));
    if (prect.contains(objrect))
	obj->draw(dst, t, clip);
    else {
	if (clip)
	    prect.intersection(clip->boundingBox());
	obj->draw(dst, t, &prect);
    }
}

// --------------------------------------------------------------------------
inline IlvDim
Mid(IlvDim px, IlvDim py)
{
    return (px+py)/2;
}

// --------------------------------------------------------------------------
static IlvDim
PosInArray(IlvDim px, IlvDim* array, IlvDim size)
{
    // Dichotomic search
    IlvDim xx = px;
    if ((xx < array[0]) || (xx > array[size]))
	return size;
    IlvDim mid;
    IlvDim infi = 0;
    IlvDim supi = size;
    while (infi != supi) {
	mid = Mid(infi, supi);
	if ((mid == infi) ||(mid == supi)) {
	    supi = mid;
	    infi = mid;
	} else if (array[mid] <= xx)
	    infi = mid;
	else
	    supi = mid;
    }
    return infi;
}

// --------------------------------------------------------------------------
IlvBoolean
IlvGridObj::pointToPosition(const IlvPoint& p,
			    IlvUShort& icol, IlvUShort& irow) const
{
    icol = _columns;
    irow = _rows;
    if (!contains(p, p))
	return IlvFalse;
    IlvDim xgrid = _drawrect.w() / _columns;
    IlvDim ygrid = _drawrect.h() / _rows;
    icol = (_sameWidth) ?
	(IlvUShort)IlvAbs((IlvPos)((int)(p.x()-_drawrect.x())/xgrid)) :
        (IlvUShort)PosInArray((IlvDim)(p.x()-_drawrect.x()),
			      _colsize, _columns);
    irow = (_sameHeight) ?
	(IlvUShort)IlvAbs((IlvPos)((int)(p.y()-_drawrect.y())/ ygrid)) :
        (IlvUShort)PosInArray((IlvDim)(p.y()-_drawrect.y()), _rowsize, _rows);
    return ((irow >= _rows) || (icol >= _columns)) ? IlvFalse : IlvTrue;
}

// --------------------------------------------------------------------------
void
IlvGridObj::deSelect(IlvPort* dst, const IlvTransformer* t)
{
    if (!_selections)
	return;
    for (IlvLink* l = _selections->getFirst(); l; l = l->getNext()) {
	IlvGraphic*     obj = (IlvGraphic*)l->getValue();
	IlvGridElement* element = getGridElement(obj);
	if (element)
	    element->selected(IlvFalse);
	if (dst)
	    reDrawObj(obj, dst, t);
    }
    delete _selections;
    _selections = new IlvList();
}

// --------------------------------------------------------------------------
void
IlvGridObj::resizeColumn(IlvUShort col, IlvDim newsize)
{
    IlvUShort i, j;
    IlvUInt pos;
    if ((col > 0) &&(col < _columns)) {
	IlvDim oldsize;
	if (col)
	    oldsize = _colsize[col] - _colsize[col-1];
	else
	    oldsize = _colsize[col];
	if (newsize == oldsize)
	    return;
	_sameWidth = IlvFalse;
	IlvPos delta = newsize - oldsize;
	for (i = col; i <= _columns; ++i)
	    _colsize[i] = (IlvDim)((IlvPos)_colsize[i]+delta);
	// Now resize objs
	for (i = (IlvUShort)(col-1); i < _columns; ++i)
	    for (j = 0; j < _rows; ++j) {
		pos = j*_columns + i;
		if (_objects[pos]) {
		    IlvGridElement* element = getGridElement(_objects[pos]);
		    if (!element->marked()) {
			reshape(_objects[pos]);
			element->marked(IlvTrue);
		    }
		}
	    }
	for (i = (IlvUShort)(col-1); i < _columns; ++i)
	    for (j = 0; j < _rows; ++j) {
		pos = j*_columns + i;
		if (_objects[pos])
		    getGridElement(_objects[pos])->marked(IlvFalse);
	    }
    }
}

// --------------------------------------------------------------------------
void
IlvGridObj::resizeRow(IlvUShort rw, IlvDim newsize)
{
    IlvUShort i, j;
    IlvUInt   pos;
    if ((rw > 0) && (rw < _rows)) {
	IlvDim oldsize;
	if (rw)
	    oldsize = _rowsize[rw] - _rowsize[rw-1];
	else
	    oldsize = _rowsize[rw];
	if (newsize == oldsize)
	    return;
	_sameHeight = IlvFalse;
	IlvPos delta = newsize - oldsize;
	for (i = rw; i <= _rows; ++i)
	    _rowsize[i] = (IlvDim)((IlvPos)_rowsize[i]+delta);
	pos = (rw-1)*_columns;
	for (j = (IlvUShort)(rw-1); j < _rows; ++j)
	    for (i = 0; i < _columns; ++i, ++pos)
		if (_objects[pos]) {
		    IlvGridElement* element = getGridElement(_objects[pos]);
		    if (!element->marked()) {
			reshape(_objects[pos]);
			element->marked(IlvTrue);
		    }
		}
	pos = (rw-1)*_columns;
	for (j = (IlvUShort)(rw-1); j < _rows; ++j)
	    for (i = 0; i < _columns; ++i, ++pos)
		if (_objects[pos])
		    getGridElement(_objects[pos])->marked(IlvFalse);
    }
}

// --------------------------------------------------------------------------
void
IlvGridObj::applyTransform(const IlvTransformer* t)
{
    IlvUShort i;
    IlvDim oldW,oldH;
    oldW = _drawrect.w();
    oldH = _drawrect.h();
    t->apply(_drawrect);
    IlvFloat sx = (IlvFloat)_drawrect.w() / (IlvFloat)oldW;
    IlvFloat sy = (IlvFloat)_drawrect.h() / (IlvFloat)oldH;
    if (_sameWidth && _sameHeight) {
	IlvDim xgrid = _drawrect.w()/_columns;
	IlvDim ygrid = _drawrect.h()/_rows;
	_drawrect.resize(xgrid*_columns, ygrid*_rows);
	for (i = 0; i <= _columns; ++i)
	    _colsize[i] = (IlvDim)(i*xgrid);
	for (i = 0; i <= _rows; ++i)
	    _rowsize[i] = (IlvDim)(i*ygrid);
    } else {
	for (i = 0; i <= _columns; ++i)
	    _colsize[i] = (IlvDim)IlvRoundFloat((IlvFloat)_colsize[i]*sx);
	for (i = 0; i <= _rows; ++i)
	    _rowsize[i] = (IlvDim)IlvRoundFloat((IlvFloat)_rowsize[i]*sy);
    }
    IlvUInt loop;
    for (loop = 0; loop < (IlvUInt)(_columns*_rows); ++loop)
	if (_objects[loop]) {
	    IlvGridElement* element = getGridElement(_objects[loop]);
	    if (!element->marked()) {
		reshape(_objects[loop]);
		element->marked(IlvTrue);
	    }
	}
    for (loop = 0; loop < (IlvUInt)(_columns*_rows); ++loop)
	    if (_objects[loop])
		getGridElement(_objects[loop])->marked(IlvFalse);
}

// Write Read Copy
// --------------------------------------------------------------------------
IlvGraphic*
IlvGridObj::copy() const
{
    IlvGridObj* grid = new IlvGridObj(getDisplay(),
				      _drawrect, _columns, _rows,
				      _selectiontype, _palette);
    IlvGridElement* element;
    IlvDim i;
    for (i = 0; i < (IlvDim)(_columns*_rows); ++i)
	if (_objects[i]) {
	    element = getGridElement(_objects[i]);
	    if (!element->marked())
		grid->add(_objects[i]->copy(),
			  element->readOnly(),
			  element->callback(),
			  element->userArg(),
			  element->width(),
			  element->height());
	    element->marked(IlvTrue);
	}
    for (i = 0; i < (IlvDim)(_columns*_rows); ++i)
	if (_objects[i])
	    getGridElement(_objects[i])->marked(IlvFalse);
    return grid;
}

// --------------------------------------------------------------------------
void
IlvGridObj::write(IlvOutputFile& os) const
{
    os.getStream() << _drawrect << " " << _thickness << " ";
    os.getStream() << _spacing << " " << _columns << " " ;
    os.getStream() << _rows << " " << (int) _selectiontype << " " ;
    os.getStream() << (int)_reliefshadow <<  " " << getCardinal() << "\n";
    IlvGridElement* element;
    IlvUInt i;
    for (i = 0; i < (IlvUInt)(_columns*_rows); ++i) {
	if (_objects[i]) {
	    if (!(element  = getGridElement(_objects[i]))->marked()) {
		getGridElement(_objects[i])->marked(IlvTrue);
		os.getStream() << element->column() << " " << element->row();
		os.getStream() << " " << element->width() << " ";
		os.getStream() << element->height() << " ";
		os.getStream() << (int)element->selected() << " ";
		os.getStream() << (int)element->readOnly() << " ";
		os << _objects[i];
		os.getStream() <<  "\n";
	    }
	}
    }
    for (i = 0; i < (IlvUInt)(_columns*_rows); ++i)
	if (_objects[i])
	    getGridElement(_objects[i])->marked(IlvFalse);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvGridObj::read(IlvInputFile& is, IlvPalette* palette)
{
    IlvRect rect;
    int seltype,relief;
    IlvDim count,thickness;
    IlvUShort spacing,columns,rows;
    IlvUShort col,row,width,height;
    int selected,readOnly;
    IlvGraphic* g;
    is.getStream() >> rect >> thickness >> spacing >> columns >> rows >>
	seltype >> relief >> count;
    IlvGridObj* grid = new IlvGridObj(palette->getDisplay(),rect,columns,rows,
				      (IlvGridSelectionType)seltype,palette);
    grid->setSpacing(spacing);
    grid->useShadow(relief? IlTrue : IlFalse);
    grid->setThickness((IlvUShort)thickness);
    for (IlvDim i = 0; i < count; ++i) {
	is.getStream() >> col >> row >> width >> height
		       >> selected >> readOnly;
	g = is.readNext();
	if (g) {
	    grid->add(col, row, g, readOnly? IlTrue : IlFalse,
		      0, 0, width, height);
	    if (selected)
		grid->makeSelected(g);
	} else
	    IlvWarning("IlvGridObj::read bad format ...\n");
    }
    return grid;
}

// --------------------------------------------------------------------------
void
IlvGridObj::drawGrid(IlvPort* dst,
		     IlvUShort fromx, IlvUShort tox,
		     IlvUShort fromy, IlvUShort toy,
		     const IlvTransformer* t, const IlvRegion* clip) const
{
   if (!_showgrid)
       return;
   IlvDim* ix = _colsize+fromx,
        * iy = _rowsize+fromy;
   IlvPoint p1, p2;
   IlvDisplay* display = getDisplay();
   if (clip)
       _palette->setClip(clip);
   if (!t) {
       IlvPos xbegin = _drawrect.x()+_colsize[fromx];
       IlvPos xend   = _drawrect.x()+_colsize[tox];
       IlvPos ybegin = _drawrect.y()+_rowsize[fromy];
       IlvPos yend   = _drawrect.y()+_rowsize[toy];
       p1.move(xbegin, xend);
       IlvPos loop;
       for (loop = fromy; loop <= (IlvPos)toy; loop++, ++iy) {
	   p1.y(_drawrect.y() + *iy);
	   p2.y(p1.y());
	   display->drawLine(dst, _palette, p1, p2);
       }
       p1.y(ybegin);
       p2.y(yend);
       for (loop = fromx; loop <= (IlvPos)tox; ++loop, ++ix) {
	   p1.x(_drawrect.x() + *ix);
	   p2.x(p1.x());
	   display->drawLine(dst, _palette, p1, p2);
       }
   } else {
	IlvPos loop;
	for (loop = fromy; loop <= (IlvPos)_rows; ++loop, ++iy) {
	    p1.move(_drawrect.x()+_colsize[fromx],
		    _drawrect.y()+ *iy);
	    p2.move(_drawrect.x()+_colsize[tox], _drawrect.y()+*iy);
	    t->apply(p1);
	    t->apply(p2);
	    display->drawLine(dst, _palette, p1, p2);
	}
	for (loop = 0; loop <= (IlvPos)_columns; ++loop, ++ix){
	    p1.move(_drawrect.x() + *ix, _drawrect.y()+_rowsize[fromy]);
	    p2.move(_drawrect.x() + *ix, _drawrect.y()+_rowsize[toy]);
	    t->apply(p1);
	    t->apply(p2);
	    display->drawLine(dst, _palette, p1, p2);
	}
    }
    if (clip)
	_palette->setClip();
}

// --------------------------------------------------------------------------
void
IlvGridObj::callCallback(IlvGraphic* obj, IlvView* view)
{
    IlvGridElement* element = getGridElement(obj);
    if (element && element->callback())
	(element->callback())(view,
			      this,
			      obj,
			      element->selected(),
			      element->userArg()
			      );
}

// --------------------------------------------------------------------------
IlvBoolean
IlvGridObj::isSelected(const IlvGraphic* obj) const
{
    IlvGridElement* element = getGridElement(obj);
    return (IlvBoolean)((element) ? element->selected() : IlvFalse);
}

// --------------------------------------------------------------------------
IlvBoolean
IlvGridObj::isReadOnly(const IlvGraphic* obj) const
{
    IlvGridElement* element = getGridElement(obj);
    return (IlvBoolean)((element) ? element->readOnly() : IlvFalse);
}

// --------------------------------------------------------------------------
void
IlvGridObj::draw(IlvPort* dst, const IlvTransformer* t,
		 const IlvRegion* clip) const
{
    // Just draw region inside clip
    IlvDim i, j;
    IlvGridElement* element;
    if (!clip) {
	drawGrid(dst, 0, _columns, 0, _rows, t, clip);
	for (i = 0; i < (IlvDim)(_columns*_rows); ++i)
		if (_objects[i]) {
		    element = getGridElement(_objects[i]);
		    if (!element->marked()) {
			drawObj(_objects[i], dst, t);
			element->marked(IlvTrue);
		    }
		}
	for (i = 0; i < (IlvUInt)(_columns*_rows); ++i)
	    if (_objects[i])
		getGridElement(_objects[i])->marked(IlvFalse);
	return;
    }
    IlvDim xgrid = _drawrect.w() / _columns,
          ygrid = _drawrect.h() / _rows;
    IlvDim fromx, tox, fromy, toy;
    IlvRect newrect = clip->boundingBox();
    if (t)
	t->inverse(newrect);
    newrect.move(IlvMax(newrect.x(), _drawrect.x()),
		 IlvMax(newrect.y(), _drawrect.y()));
    newrect.resize(IlvMin(newrect.w(), _drawrect.w()),
		   IlvMin(newrect.h(), _drawrect.h()));
    if (_sameWidth) {
	fromx = (IlvDim)IlvAbs((IlvPos)(newrect.x()-
					_drawrect.x())/(IlvPos)xgrid);
	tox = (IlvDim)(newrect.x() -_drawrect.x()+ newrect.w())/xgrid;
    } else {
	fromx = PosInArray((IlvDim)(newrect.x()-_drawrect.x()),
			   _colsize, _columns);
	tox = PosInArray((IlvDim)(newrect.x()-_drawrect.x() + newrect.w()),
			 _colsize, _columns);
    }
    if (_sameHeight) {
	fromy = (IlvDim)IlvAbs((IlvPos)(newrect.y()-
					_drawrect.y())/(IlvPos)ygrid);
	toy   = (IlvDim)(newrect.bottom() - _drawrect.y()) / ygrid;
    } else {
	fromy = (IlvDim)PosInArray((IlvDim)(newrect.y() - _drawrect.y()),
				  _rowsize, _rows);
	toy   = (IlvDim)PosInArray((IlvDim)(newrect.bottom() - _drawrect.y()),
				  _rowsize, _rows);
    }
    fromx = IlvMax((IlvDim)0,(IlvDim)fromx);
    tox   = IlvMin((IlvDim)(_columns-1),(IlvDim)tox);
    fromx = IlvMin(fromx, tox);
    fromy = IlvMax((IlvDim)0,(IlvDim)fromy);
    toy   = IlvMin((IlvDim)(_rows-1),(IlvDim)toy);
    fromy = IlvMin(fromy, toy);
    IlvDim pos;
    drawGrid(dst,
	     (IlvUShort)fromx, (IlvUShort)(tox+1),
	     (IlvUShort)fromy, (IlvUShort)(toy+1),
	     t, clip);
    for (j = fromy; j <= toy; ++j)
	for (i = fromx; i <= tox; ++i){
	    pos = j * _columns + i;
	    if (_objects[pos]) {
		element = getGridElement(_objects[pos]);
		if (!element->marked()) {
		    IlvRect bbox;
		    _objects[pos]->boundingBox(bbox);
    // BUG DU PORTAGE WINDOWS A CORRIGER
#if defined(WINDOWS)
	            drawObj(_objects[pos], dst, t);
#else  /* !WINDOWS */
		    if (clip->contains(bbox))
			drawObj(_objects[pos], dst, t);
		    else
			drawObj(_objects[pos], dst, t, clip);
#endif /* !WINDOWS */
		    element->marked(IlvTrue);
		}
	    }
	}
    for (j = fromy; j <= toy; ++j)
	for (i = fromx; i <= tox; ++i){
	    pos = j*_columns+ i;
	    if (_objects[pos])
		getGridElement(_objects[pos])->marked(IlvFalse);
	}
}

// --------------------------------------------------------------------------
IlvInt
IlvGridObj::getPosition(const IlvGraphic* obj) const
{
    IlvGridElement* element = getGridElement(obj);
    return element ?  element->row()*_columns+ element->column(): -1;
}

// --------------------------------------------------------------------------
void
IlvGridObj::setCallback(IlvGraphic* g, IlvGridObjectCallback c, IlvAny arg)
{
    IlvGridElement* element = getGridElement(g);
    if (element) {
	element->callback(c);
	element->userArg(arg);
    }
}

// --------------------------------------------------------------------------
void
IlvGridObj::setReadOnly(IlvGraphic* g, IlvBoolean v)
{
    IlvGridElement* element = getGridElement(g);
    if (element)
	element->readOnly(v);
}


// --------------------------------------------------------------------------
void
IlvGridObj::apply(IlvApplyObject f, IlvAny a)
{
    for (int i = 0; i < (int)(_columns*_rows); ++i)
	if (_objects[i])
	    f(_objects[i],a);
}

// --------------------------------------------------------------------------
void
IlvGridObj::setMode(IlvDrawMode mode)
{
    IlvReliefRectangle::setMode(mode);
    for (int i = 0; i < (int)(_columns*_rows); ++i)
	if (_objects[i]) _objects[i]->setMode(mode);
}

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvPreRegisterClass(IlvGridObj);
IlvSymbol* IlvGridObj::_objectGridElement = 0;
ILVDEFINEINITCLASS(grid, IlvPostRegisterClass(IlvGridObj, IlvReliefRectangle); IlvGridObj::_objectGridElement = IlvGetSymbol("objectGridElement");)
#else  /* !IlvDECLAREINITCLASS */
IlvRegisterClass(IlvGridObj, IlvReliefRectangle);
IlvSymbol* IlvGridObj::_objectGridElement = IlvGetSymbol("objectGridElement");
#endif /* !IlvDECLAREINITCLASS */
