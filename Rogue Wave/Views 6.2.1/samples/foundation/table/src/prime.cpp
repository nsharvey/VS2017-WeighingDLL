// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/table/src/prime.cpp
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
// Extending the class IlvTable class.
// --------------------------------------------------------------------------
// The class IlvTable is subclassed into an IlvTableDrawer
// to draw a map of Prime Numbers
// The class PrimeTable is a sub class of IlvSimpleGraphic
// that uses a IlvTable to draw itself.
// --------------------------------------------------------------------------

#include <ilviews/graphics/rectangl.h>
#include <ilviews/util/table.h>
#include <ilviews/base/inter.h>
#include <ilviews/contain/contain.h>
#include <ilviews/gadgets/menu.h>

#if defined(IL_STD)
#include <cstdio>
#include <cmath>
IL_STDUSE
#else  /* !IL_STD */
#include <stdio.h>
#include <math.h>
#endif /* !IL_STD */

#define CELLWIDTH 15

static const char* title = "Rogue Wave Views sample: prime";

// --------------------------------------------------------------------------
static IlBoolean
IsAPrimeNumber(IlUInt number) // Tells if number is a prime number
{
    if ((number == 1) || (number == 2) ||
	(number == 3) || (number == 5) || (number == 7))
	return IlTrue;
    if (!(number % 2))
	return IlFalse;
    if (!(number % 3))
	return IlFalse;
    if (!(number % 5))
	return IlFalse;
    if (!(number % 7))
	return IlFalse;
    IlUInt root = (IlUInt)sqrt((double)number);
    for (IlUInt i = 11; i<= root ; i += 2)
	if (!(number % i))
	    return IlFalse;
    return IlTrue;
}

// --------------------------------------------------------------------------
class PrimeTable;

// --------------------------------------------------------------------------
class TableDrawer
    : public IlvTable
{
public:
    TableDrawer(PrimeTable* graphic)
        : IlvTable(),
	  _graphic(graphic)
    {}
    TableDrawer(const TableDrawer&);
    // ____________________________________________________________
    // Drawing properties
    virtual IlBoolean isShowingGrid() const { return IlTrue; }
    virtual IlBoolean rowSameHeight() const { return IlTrue; }
    virtual IlBoolean columnSameWidth() const { return IlTrue; }
    virtual IlvDim getRowHeight(IlUShort) const   { return CELLWIDTH; }
    virtual IlvDim getColumnWidth(IlUShort) const { return CELLWIDTH; }

    // Cell managment
    virtual IlBoolean allowCellMode() const { return IlFalse; }

    // Drawing
    virtual void drawItem(IlvPort* dst,
			  IlUShort rowno,
			  IlUShort colno,
			  const IlvRect& itembbox,
			  const IlvRect& clip) const;
private:
    PrimeTable* _graphic;
};

// --------------------------------------------------------------------------
class PrimeTable
: public IlvFilledRectangle {
public:
    PrimeTable(IlvDisplay*    display,
	       const IlvRect& drawrect,
	       IlvPalette*    palette = 0)
    : IlvFilledRectangle(display, drawrect, palette)
    {
	_table =  new TableDrawer(this);
	_popup  = new IlvPopupMenu(display);
    }
    ~PrimeTable()
    {
	delete _popup;
	delete _table;
    }
    // ____________________________________________________________
    void showNumber(const IlvPoint& p,
		    IlUShort col,
		    IlUShort row) const
    {
	char buffer[10];
	col++;
	sprintf(buffer,	"%ld",
		(long)(row * ((_drawrect.w() - 1) / CELLWIDTH) + col));
	_popup->empty();
	_popup->addItem(IlvMenuItem(buffer));
	_popup->show(p, IlTrue);
    }
    
    IlBoolean pointToPosition(const IlvPoint& p,
			      IlUShort& col,
			      IlUShort& row,
			      const IlvTransformer* t) const
    {
	IlvRect bbox = _drawrect;
	if (t)
	    t->apply(bbox);
	
	// pointToPosition using the 'Table drawer'
	// the number of columns and rows depends
	// of height and width.
	return _table->pointToPosition(bbox,
				       p,
				       0,
				       0,
				       IlUShort((bbox.w() - 1) / CELLWIDTH),
				       IlUShort((bbox.h() - 1) / CELLWIDTH),
				       col, row);
    }
    
    virtual void draw(IlvPort* dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const
    {
	IlvRect bbox = _drawrect;
	if (t)
	    t->apply(bbox);
	
	// call the other draw method for each IlvRect of clip
	if (clip) {
	    IlvRect rect;
	    for (IlUShort i = 0; i < clip->getCardinal(); ++i) {
		rect = clip->getRect(i);
		rect.intersection(bbox);
		draw(rect, dst, t);
	    }
	} else
	    draw(bbox, dst, t);
    }

    virtual void draw(const IlvRect& clip,
		      IlvPort* dst,
		      const IlvTransformer* t) const
    {
	IlvRect newclip = clip;
	IlvRect bbox = _drawrect;
	if (t)
	    t->apply(bbox);
	
	newclip.intersection(bbox);
	if (!newclip.w() || !newclip.h())
	    return;
	
	// draw using the 'Table drawer'
	// the number of columns and rows depends
	// of height and width.
	_table->draw(dst,
		     0,
		     0,
		     IlUShort((bbox.w() - 1) / CELLWIDTH),
		     IlUShort((bbox.h() - 1) / CELLWIDTH),
		     _palette,
		     bbox,
		     newclip);
    }

    virtual void drawItem(IlvPort* dst,
			  IlUShort rowno,
			  IlUShort colno,
			  const IlvRect& itembbox,
			  const IlvRect& clip) const
    {
	// fill the matrix item if it corresponds to a prime number.
	colno++;
	if (IsAPrimeNumber(rowno*((_drawrect.w() - 1) / CELLWIDTH) + colno)) {
	    IlvRegion clipreg(clip);
	    IlvPushClip pushClip(*_palette, &clipreg);
	    dst->fillRectangle(_palette, itembbox);
	}
    }

protected:
    TableDrawer* _table;
    IlvPopupMenu*   _popup;
};

// --------------------------------------------------------------------------
class PrimeInteractor
    : public IlvInteractor
{
public:
    virtual IlBoolean handleEvent(IlvGraphic* obj,
				  IlvEvent& event,
				  const IlvTransformer* t)
    {
	IlUShort col, row;
	PrimeTable * table = (PrimeTable*)obj;
	if (event.type() == IlvButtonDown) {
	    if (table->pointToPosition(IlvPoint(event.x(), event.y()),
				       col,
				       row,
				       t)) {
		table->showNumber(IlvPoint(event.gx(), event.gy()), col, row);
		return IlTrue;
	    }
	}
	return IlFalse;
    }
    virtual IlvInteractor* copy() const { return 0; }
};

// --------------------------------------------------------------------------
// Method of TableDrawer
// --------------------------------------------------------------------------
void
TableDrawer::drawItem(IlvPort* dst,
		      IlUShort rowno,
		      IlUShort colno,
		      const IlvRect& itembbox,
		      const IlvRect& clip) const
{
    _graphic->drawItem(dst, rowno, colno, itembbox, clip);
}

// --------------------------------------------------------------------------
// Destroy callback
// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Resize callback
// --------------------------------------------------------------------------
static void
Resize(IlvView* view,
       IlvRect& size,
       IlAny object)
{
    IlvGraphic* table = (IlvGraphic*)object;
    IlvDim w = 1;
    if (size.w() > 20)
	w = size.w() - 20;
    IlvDim h = 1;
    if (size.h() > 20)
	h = size.h() - 20;
    table->moveResize(IlvRect(10, 10, w, h));
    table->reDraw();
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Prime", 0, argc, argv);
    if (!display || display->isBad()) {
        IlvFatalError("Couldn't create display");
        delete display;
        return -1;
    }
    IlvContainer* container = new IlvContainer(display, title, title,
					       IlvRect(0, 0, 200, 590),
					       IlFalse,
					       IlFalse);
    container->setDestroyCallback(Quit);
    PrimeTable* table = new PrimeTable(display,
				       IlvRect(10, 10, 179, 519));
    container->addObject(table);
    container->setResizeCallback(Resize, table);
    table->setInteractor(new PrimeInteractor());
    container->setDoubleBuffering(IlTrue);
    container->show();
    IlvMainLoop();
    return 0;
}
