// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/cellpal.cpp
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
// Definition of the Palette selector for cell managers
// ------------------------------------------------------------------------
#include <ilviews/cellpal.h>
#include <ilviews/cell.h>

#include <ilviews/graphics/label.h>
#include <ilviews/graphics/relflab.h>
#include <ilviews/gview.h>
#include <ilviews/rcview.h>

#if defined(ILVSTD)
#include <cstdlib>
#if !defined(_MSC_VER)
using std::qsort;
#endif /* _MSC_VER */
#else  /* !ILVSTD */
#include <stdlib.h>
#endif /* !ILVSTD */

// --------------------------------------------------------------------------
class IlvCellColumnViewInteractor
: public IlvViewToggleInteractor {
protected:
    IlvRowColumnView* _column;
public:
    IlvCellColumnViewInteractor(IlvRowColumnView* column)
	: _column(column) {}
    // ____________________________________________________________
    virtual void doIt(IlvGraphic*, IlvContainer*);
};

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
static IlvSymbol* __associatedObject;
static IlvSymbol* __paletteObject;
static IlvViewGridInteractor* gridInteractor;
ILVDEFINEINITCLASS(cellpal, __associatedObject = IlvGetSymbol("AssociatedObject"); __paletteObject    = IlvGetSymbol("PaletteObject"); gridInteractor = new IlvViewGridInteractor(); )
#else  /* !IlvDECLAREINITCLASS */
static IlvSymbol* __associatedObject = IlvGetSymbol("AssociatedObject");
static IlvSymbol* __paletteObject    = IlvGetSymbol("PaletteObject");
static IlvViewGridInteractor* gridInteractor = new IlvViewGridInteractor();
#endif /* !IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
void
IlvCellColumnViewInteractor::doIt(IlvGraphic* o, IlvContainer*)
{
    IlvGraphic* obj = (IlvGraphic*)o->getProperty(__associatedObject);
    if (_column->isVisible(obj))
	_column->setVisible(obj, IlvFalse, IlvTrue);
    else
	_column->setVisible(obj, IlvTrue, IlvTrue);
}

// --------------------------------------------------------------------------

typedef const char*  arraychar;
static arraychar __colors[] = {
    "Aquamarine",
    "Blue",
    "Blue Violet",
    "Brown",
    "Cadet Blue",
    "Coral",
    "Cornflower Blue",
    "Cyan",
    "Dark Green",
    "Dark Olive Green",
    "Dark Orchid",
    "Dark Slate Blue",
    "Dark Slate Gray",
    "Dark Turquoise",
    "Dim Gray",
    "Firebrick",
    "Forest Green",
    "Gold",
    "Goldenrod",
    "Gray",
    "Green",
    "Green Yellow",
    "Indian Red",
    "Khaki",
    "Light Blue",
    "Light Gray",
    "Light Steel Blue",
    "Lime Green",
    "Magenta",
    "Maroon",
    "Medium Aquamarine",
    "Medium Blue",
    "Medium Orchid",
    "Medium Sea Green",
    "Medium Slate Blue",
    "Medium Spring Green",
    "Medium Turquoise",
    "Medium Violet Red",
    "Midnight Blue",
    "Navy",
    "Navy Blue",
    "Olive Drab",
    "Orange",
    "Orange Red",
    "Orchid",
    "Pale Green",
    "Pink",
    "Plum",
    "Salmon",
    "Sea Green",
    "Sienna",
    "Sky Blue",
    "Slate Blue",
    "Spring Green",
    "Steel Blue",
    "Thistle",
    "Turquoise",
    "Violet",
    "Violet Red",
    "Wheat",
    "Yellow",
    "Yellow Green"
};

// --------------------------------------------------------------------------
static void
DestroyTopView(IlvTopView*, IlvAny arg)
{
    IlvCellPalette* papal=(IlvCellPalette*)arg;
    papal->destroy();
}

// --------------------------------------------------------------------------
inline IlvCellPalette*
getCellPalette(IlvGridObj* grid)
{
    return (IlvCellPalette*)grid->getProperty(__paletteObject);
}

// --------------------------------------------------------------------------
static void
ChoosePatternCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvCellPalette* p = getCellPalette((IlvGridObj*)g);
    if (p) p->callCallback((IlvPattern*)arg);
}

// --------------------------------------------------------------------------
static void
ChooseColorCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvCellPalette* p = getCellPalette((IlvGridObj*)g);
    if (p) p->callCallback((IlvColor*)arg);
}

// --------------------------------------------------------------------------
static void
ChooseBgFgCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		   IlvBoolean , IlvAny arg)
{
    IlvCellPalette* p = getCellPalette((IlvGridObj*)g);
    if (p) p->background(IlCastIlAnyToIlUInt(arg)? IlTrue : IlFalse);
}

// --------------------------------------------------------------------------
static void
ChooseFillStyleCallback(IlvView*,  IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvCellPalette* p = getCellPalette((IlvGridObj*)g);
    if (p) p->callCallback((IlvFillStyle)IlCastIlAnyToIlUInt(arg));
}

// --------------------------------------------------------------------------
#if defined(__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT >= 5)
extern "C" { static int colorcompare(const void*, const void*); }
#endif /* Sun C++ 5.0 */
static int
#if defined(__IBMCPP__)
_Optlink
#endif /* __IBMCPP__ */
colorcompare(const void* col1, const void* col2)
{
    IlvFloat h1, s1, v1;
    (*((IlvColor**)col1))->getHSV(h1, s1, v1);
    IlvFloat h2, s2, v2;
    (*((IlvColor**)col2))->getHSV(h2, s2, v2);

    if (s1 == 0) {
	if (s2 == 0) {
	    if (v1 > v2) return 1;
	    if (v1 < v2) return -1;
	    return 0;
	} else return -1;
    }
    if (s2 == 0) return 1;
    if (h1 > h2) return 1;
    if (h1 < h2) return -1;
    if (v1 > v2) return 1;
    if (v1 < v2) return -1;
    if (s1 > s2) return 1;
    if (s1 < s2) return -1;
    return 0;
}

#define WIDTH      220
#define HEIGHTSTY   60
#define HEIGHTPAT  220
#define HEIGHTSMALL 30
// --------------------------------------------------------------------------
IlvCellPalette::IlvCellPalette(IlvCellManager* manager,
			       const IlvRect&  size,
			       IlvBoolean      visible)
: _fillbackground(IlvFalse),_manager(manager)
{
    IlvDisplay* display=manager->getDisplay();
    _topview = new IlvTopView(display, "Palette Editor", "Palette Editor",
			      size, visible);
    _topview->setDestroyCallback(DestroyTopView, this);
    IlvRect scrollsize(0, 0, size.w(), size.h());
    IlvScrollView* scrollview = new IlvScrollView(_topview, scrollsize);
    IlvRect csize(0, 0, WIDTH+20, size.h()*2);
    IlvRowColumnView * column=new IlvRowColumnView(scrollview, csize);
    _interactor =  new IlvCellColumnViewInteractor(column);

    IlvRect rect(0, 0, 100, 100);
    IlvGraphic* obj;
    IlvPoint p(0, 0);

    //Makes Patterns
    obj = new IlvReliefLabel(display, p, "Show Patterns");
    column->addObject(obj);
    column->setObjectInteractor(obj, _interactor);
    obj->invert();

    IlvList* all_patterns=display->getPatterns();
    IlvUInt l=all_patterns->length();
    IlvRect Prect(0, 0, WIDTH, HEIGHTPAT);
    IlvGridObj* grid = new IlvGridObj(display, Prect, 4, (IlvUShort)(l/4),
				    IlvGridNoSelection);
    obj->addProperty(__associatedObject, grid);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    IlvPattern* pattern;
    IlvMapList(all_patterns, IlvPattern*, pattern,
	       obj=new IlvFilledRectangle(display, rect);
	       obj->setPattern(pattern);
	       grid->add(obj, IlvFalse, ChoosePatternCallback, pattern);
	       );
    grid->addProperty(__paletteObject, this);

    // Create Colors
    obj = new IlvReliefLabel(display, p, "Show Colors");
    column->addObject(obj);
    column->setObjectInteractor(obj, _interactor);
    obj->invert();

    IlvRect Crect(0, 0, WIDTH, HEIGHTPAT);

    grid = new IlvGridObj(display, Crect, 9, 8, IlvGridNoSelection);
    obj->addProperty(__associatedObject, grid);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->addProperty(__paletteObject, this);
    IlvColor* fg;
    int nbcolors=sizeof(__colors)/sizeof(arraychar);
    // First store Black and White, then sort the colors:
    obj=new IlvFilledRectangle(display, rect);
    fg = display->getColor("Black");
    obj->setForeground(fg);
    grid->add(obj, IlvFalse, ChooseColorCallback, fg);
    obj=new IlvFilledRectangle(display, rect);
    fg = display->getColor("White");
    obj->setForeground(fg);
    grid->add(obj, IlvFalse, ChooseColorCallback, fg);

    IlvColor** allcolors = new IlvColor* [nbcolors];
    int colorloop = 0;
    int i;
    for (i = 0; i < nbcolors; i++) {
	allcolors[colorloop] = display->getColor(__colors[i]);
	if (allcolors[colorloop]) colorloop++;
	else
	    IlvWarning("Color %s not found\n", __colors[i]);
    }
    qsort((char*)allcolors, colorloop, sizeof(IlvColor*), colorcompare);
    for (i = 0; i < colorloop; i++) {
	obj=new IlvFilledRectangle(display, rect);
	obj->setForeground(allcolors[i]);
	grid->add(obj, IlvFalse, ChooseColorCallback, allcolors[i]);
    }
    delete [] allcolors;
    //Makes Bg/FG
    IlvRect Brect(0, 0, WIDTH, HEIGHTSMALL);
    grid = new IlvGridObj(display, Brect, 2, 1, IlvGridExclusiveSelection);
    IlvPoint origin(0, 0);
    grid->add(new IlvLabel(display, origin, "Background"),
	      IlvFalse, ChooseBgFgCallback,(IlvAny)1);
    grid->add(obj = new IlvLabel(display, origin, "Foreground"), IlvFalse,
	      ChooseBgFgCallback,(IlvAny)0);
    grid->makeSelected(obj);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->addProperty(__paletteObject, this);
    // Fill mode
    IlvRect Orect(0, 0, WIDTH, HEIGHTSMALL);
    grid = new IlvGridObj(display, Orect, 3, 1, IlvGridNoSelection);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->add(new IlvLabel(display, origin, "ColorPattern"), IlvFalse,
	      ChooseFillStyleCallback,(IlvAny)(long)IlvFillColorPattern);
    grid->add(obj=new IlvLabel(display, origin, "MaskPattern"), IlvFalse,
	      ChooseFillStyleCallback,(IlvAny)(long)IlvFillMaskPattern);
    grid->add(obj=new IlvLabel(display, origin, "Pattern"), IlvFalse,
	      ChooseFillStyleCallback,(IlvAny)(long)IlvFillPattern);
    grid->addProperty(__paletteObject, this);
}

// --------------------------------------------------------------------------
IlvCellPalette::~IlvCellPalette()
{
    delete _interactor;
    if(_topview) delete _topview;
}

// --------------------------------------------------------------------------
void
IlvCellPalette::destroy()
{
    // Destroy from WM just prevent users
    // But don't try to call delete on view they are already detroyed
    //delete this; // expects a destroy callback to prevent user ...
}

// --------------------------------------------------------------------------
void
IlvCellPalette::show()
{
    _topview->show();
}

// --------------------------------------------------------------------------
void
IlvCellPalette::hide()
{
    _topview->hide();
}

// --------------------------------------------------------------------------
void
IlvCellPalette::show(IlvPos x, IlvPos y)
{
    _topview->move(IlvPoint(x, y));
    _topview->show();
}

// --------------------------------------------------------------------------
static void
SetPattern(IlvCellManager* cellmgr,IlvCell* cell, IlvAny arg)
{
    cell->setPattern((IlvPattern*)arg);
    cellmgr->reDraw(cell);
}

// ------------------------------------------------------------------------
void
IlvCellPalette::callCallback(IlvPattern* bitmap)
{
    _manager->applyToSelections(SetPattern,bitmap);
}

// --------------------------------------------------------------------------
static void
SetFillStyle(IlvCellManager* cellmgr,IlvCell* cell, IlvAny arg)
{
    cell->setFillStyle((IlvFillStyle)IlCastIlAnyToIlUInt(arg));
    cellmgr->reDraw(cell);
}

// ------------------------------------------------------------------------
void
IlvCellPalette::callCallback(IlvFillStyle fillstyle)
{
    _manager->applyToSelections(SetFillStyle,IlCastIlUIntToIlAny(fillstyle));
}

// ------------------------------------------------------------------------
static void
SetBackground(IlvCellManager* cellmgr,IlvCell* cell, IlvAny arg)
{
    cell->setBackground((IlvColor*)arg);
    cellmgr->reDraw(cell);
}

// ------------------------------------------------------------------------
static void
SetForeground(IlvCellManager* cellmgr,IlvCell* cell, IlvAny arg)
{
    cell->setForeground((IlvColor*)arg);
    cellmgr->reDraw(cell);
}

// ------------------------------------------------------------------------
void
IlvCellPalette::callCallback(IlvColor* color)
{
    if (_fillbackground)
	_manager->applyToSelections(SetBackground,color);
    else
	_manager->applyToSelections(SetForeground,color);
}
