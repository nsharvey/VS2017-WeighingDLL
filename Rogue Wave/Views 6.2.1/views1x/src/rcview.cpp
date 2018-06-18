// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/rcview.cpp
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
// Definition of the IlvRowColumnView class
// --------------------------------------------------------------------------

#include <ilviews/rcview.h>

// --------------------------------------------------------------------------
static void
BoundingBox(IlvList& list, IlvRect& rect)
{
    IlvRect bbox;
    IlvGraphic* obj;
    rect.resize(0,0);
    IlvMapList(&list,  IlvGraphic*, obj,
	       obj->boundingBox(bbox);
	       rect.add(bbox);
	       );
}

// --------------------------------------------------------------------------
void
IlvRowColumnView::addObject(const char* name,
			    IlvGraphic* obj, IlvBoolean redraw)
{
    // Some compilers are confused by the 2 versions of addObject.
    // Redefine this one only to please them.
    IlvContainer::addObject(name, obj, redraw);
}

// --------------------------------------------------------------------------
void
IlvRowColumnView::addObject(IlvGraphic* obj, IlvBoolean redraw)
{
    IlvRect rect;
    IlvDim w, h;
    if (_list.length()) {
	visibleBBox(rect);
	if (_column)
	    obj->move(_wmargin, rect.bottom() + _hmargin);
	else
	    obj->move(rect.right() + _wmargin, _hmargin);
    }
    else
	obj->move(_wmargin, _hmargin);
    size(w, h);
    _list.append(obj);
    BoundingBox(_list, rect);
    if (redraw) reDrawObj(obj);
    if (_column) {
	IlvDim totalh=(IlvDim)(rect.bottom()+ 2*_hmargin);
	if ((h < totalh )  && _autoResize)
	    IlvAbstractView::resize(w, totalh);
    } else {
	IlvDim totalw=(IlvDim)(rect.right()+ 2*_wmargin);
	if ((w < totalw )  && _autoResize)
	    IlvAbstractView::resize(totalw, h);
    }
}

// --------------------------------------------------------------------------
void
IlvRowColumnView::insertObject(IlvGraphic* obj, IlvBoolean redraw)
{
    addObject(obj, redraw);
}

// --------------------------------------------------------------------------
IlvBoolean
IlvRowColumnView::removeObject(IlvGraphic* obj, IlvBoolean)
{
    if (!_list.find(obj)) return IlvFalse;
    _list.remove(obj);
    IlvRect bbox;
    obj->boundingBox(bbox);
    IlvGraphic* other;
    IlvRect rect;
    if (_column){
	IlvMapList(&_list, IlvGraphic*, other,
		   other->boundingBox(rect);
		   if (rect.y() > bbox.y())
		   other->translate(0, -(IlvPos)bbox.h()-(IlvPos)_hmargin);
		   );
    } else {
	IlvMapList(&_list, IlvGraphic*, other,
		   other->boundingBox(rect);
		   if (rect.x() > bbox.x())
		   other->translate(-(IlvDeltaPos)bbox.w()
				    -(IlvDeltaPos)_wmargin, 0);
		  );
    }
    return IlvTrue;
}

// --------------------------------------------------------------------------
void
IlvRowColumnView::align(IlvGraphic* obj, IlvPosition align)
{
    IlvDim w, h;
    size(w, h);
    IlvRect bbox;
    obj->boundingBox(bbox);
    if (_column) {
	switch(align) {
	case IlvLeft:
	    obj->move(_wmargin, bbox.y());
	break;
	case IlvRight:
	    obj->move(w-bbox.w()-_wmargin, bbox.y());
	    break;
	case IlvCenter:
	    obj->move((IlvPos)(w-bbox.w())/2, bbox.y());
	    break;
	}
    } else {
	switch(align) {
	case IlvTop:
	    obj->move(bbox.x(), _hmargin);
	break;
	case IlvBottom:
	    obj->move(bbox.x(), h-bbox.h()-_hmargin);
	    break;
	case IlvCenter:
	    obj->move(bbox.x(), (IlvPos)(h-bbox.h())/2);
	    break;
	}
    }
}

// --------------------------------------------------------------------------
void
IlvRowColumnView::setVisible(IlvGraphic* obj, IlvBoolean visible,
			     IlvBoolean redraw)
{
    if (_column) columnVisible(obj, visible, redraw);
    else rowVisible(obj, visible, redraw);
}

// --------------------------------------------------------------------------
static void
ChangeVisibility(IlvGraphic* obj, IlvBoolean visible)
{
    IlvObjectProperty* objProp = obj->getObjectProperty();
    if (objProp)
	objProp->setVisible(visible);
}

// --------------------------------------------------------------------------
void
IlvRowColumnView::columnVisible(IlvGraphic* obj, IlvBoolean visible,
				IlvBoolean redraw)
{
    IlvRect bbox;
    obj->boundingBox(bbox);
    IlvDim w, h;
    size(w, h);
    IlvDisplay* display=getDisplay();
    IlvPalette* palette=display->defaultPalette();
    if (!visible) {
	if (!isVisible(obj)) return;
	ChangeVisibility(obj, IlvFalse);
	IlvGraphic* other;
	IlvRect rect;
	IlvRect oldrect;
	visibleBBox(oldrect);
	IlvMapList(&_list, IlvGraphic*, other,
		   other->boundingBox(rect);
		   if (rect.y() > bbox.y())
		   other->translate(0, -(IlvDeltaPos)bbox.h()
				       -(IlvDeltaPos)_hmargin);
		   );
	if (redraw){
	    if (bbox.bottom() < oldrect.bottom()) {
#if defined(WINDOWS)
		sizeVisible(oldrect);
		IlvRect fromrect(0, bbox.bottom()+_hmargin,
				 w, (IlvDim)(oldrect.h()-bbox.bottom()
					                -_hmargin));
#else  /* !WINDOWS */
		IlvRect fromrect(0, bbox.bottom()+_hmargin, w,
				 (IlvDim)(h-bbox.bottom()-_hmargin));
#endif /* !WINDOWS */
		IlvPoint topoint(0, bbox.y());
		display->copyArea(this, palette, this, fromrect, topoint);
#if defined(WINDOWS)
		fromrect.move(0, bbox.y() + fromrect.h());
		fromrect.h(oldrect.h()-fromrect.y());
		IlvRegion clip(fromrect);
		reDraw(&clip);
#endif /* WINDOWS */
	    } else
		erase(bbox);
	}
    } else {
	if (isVisible(obj)) return;
	ChangeVisibility(obj, IlvTrue);
	//Found Position then Translate others ....
	IlvRect rect;
	IlvLink* link=_list.getFirst();
	while (link && (link->getNext()->getValue() != obj))
	    link = link->getNext();
	if (!link) return; //parano
	IlvGraphic* found = (IlvGraphic*)link->getValue();
	found->boundingBox(rect);
	IlvPos y=rect.bottom()+_hmargin;
	obj->move(bbox.x(), y); bbox.y(y); ////////
	link=link->getNext()->getNext();
	while (link) {
	    found=(IlvGraphic*)link->getValue();
	    found->translate(0, (IlvDeltaPos)bbox.h()+(IlvDeltaPos)_hmargin);
	    link=link->getNext();
	}
	if (redraw) {
	    y = rect.bottom()+_hmargin;
	    IlvRect fromrect(0, y, w, (IlvDim)(h-y-bbox.h()-_hmargin));
	    IlvPoint topoint(0, y+bbox.h()+_hmargin);
	    display->copyArea(this, palette, this, fromrect, topoint);
	    bbox.x(0);
	    bbox.resize(w, bbox.h()+_hmargin);
	    erase(bbox);
	    obj->draw(this);
	}
    }
    visibleBBox(bbox);
    if(_autoResize) IlvAbstractView::resize(w, bbox.h()+2*_hmargin);
}

//----------------------------------------------------------------------
void
IlvRowColumnView::rowVisible(IlvGraphic* obj, IlvBoolean visible,
			     IlvBoolean redraw)
{
    IlvRect bbox;
    obj->boundingBox(bbox);
    IlvDim w, h;
    size(w, h);
    IlvDisplay* display=getDisplay();
    IlvPalette* palette=display->defaultPalette();
    if (!visible) {
	if (!isVisible(obj)) return;
	ChangeVisibility(obj, IlvFalse);
	IlvGraphic* other;
	IlvRect rect;
	IlvRect oldrect;
	visibleBBox(oldrect);
	IlvMapList(&_list, IlvGraphic*, other,
		   other->boundingBox(rect);
		   if (rect.x() > bbox.x())
		   other->translate(-(IlvDeltaPos)bbox.w()
				    -(IlvDeltaPos)_wmargin, 0);
		  );
	if (redraw){
	    if (bbox.right() < oldrect.right()) {
#if defined(WINDOWS)
		sizeVisible(oldrect);
		IlvRect fromrect(bbox.right()+_wmargin, 0,
				 (IlvDim)(oldrect.w()-bbox.right()
					             -_wmargin), h);
#else  /* !WINDOWS */
		IlvRect fromrect(bbox.right()+_wmargin, 0,
				 (IlvDim)(w-bbox.right()-_wmargin), h);
#endif /* !WINDOWS */
		IlvPoint topoint(bbox.x(), 0);
		display->copyArea(this, palette, this, fromrect, topoint);
#if defined(WINDOWS)
		fromrect.move(bbox.x() + fromrect.w(), 0);
		fromrect.h(oldrect.w()-fromrect.x());
		IlvRegion clip(fromrect);
		reDraw(&clip);
#endif /* WINDOWS */
	    } else
		erase(bbox);
	}
    } else {
	if (isVisible(obj)) return;
	ChangeVisibility(obj, IlvTrue);
	//Found Position then  Translate others ....
	IlvRect rect;
	IlvLink* link = _list.getFirst();
	while (link && (link->getNext()->getValue() != obj))
	    link = link->getNext();
	if (!link) return; //parano
	IlvGraphic* found = (IlvGraphic*)link->getValue();
	found->boundingBox(rect);
	IlvPos x = rect.right()+_wmargin;
	obj->move(x, bbox.y()); bbox.x(x);
	link=link->getNext()->getNext();
	while (link) {
	    found=(IlvGraphic*)link->getValue();
	    found->translate((IlvDeltaPos)bbox.w()+(IlvDeltaPos)_wmargin, 0);
	    link = link->getNext();
	}
	if (redraw) {
	    x = rect.right()+_wmargin;
	    IlvRect fromrect(x, 0,(IlvDim)(w-x-bbox.w()-_wmargin), h);
	    IlvPoint topoint(x+bbox.w()+_wmargin, 0);
	    display->copyArea(this, palette, this, fromrect, topoint);
	    bbox.y(0);
	    bbox.resize(bbox.w()+_wmargin, h);
	    erase(bbox);
	    obj->draw(this);
	}
    }
    visibleBBox(bbox);
    if (_autoResize) IlvAbstractView::resize(bbox.w()+2*_wmargin, h);
}
