// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/paledit.cpp
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
// Implementation of the IlvPaletteSelector class
// --------------------------------------------------------------------------
#include <ilviews/paledit.h>
#include <ilviews/rcview.h>

#include <ilviews/graphics/line.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/relflab.h>
#include <ilviews/graphics/arc.h>
#include <ilviews/graphics/polyline.h>

#include <ilviews/grid.h>
#include <ilviews/gridint.h>
#include <ilviews/gview.h>
#include <ilviews/graphics/set.h>

#include <ilviews/contint.h>
#include <ilviews/base/hash.h>

#if defined(ILVSTD)
#include <cstdlib>
#if !defined(_MSC_VER)
using std::qsort;
#endif /* _MSC_VER */
#else  /* !ILVSTD */
#include <stdlib.h>
#endif /* !ILVSTD */

// --------------------------------------------------------------------------
class IlvColumnViewInteractor
: public IlvViewToggleInteractor {
protected:
    IlvRowColumnView* _column;
public:
    IlvColumnViewInteractor(IlvRowColumnView* column)
	: _column(column) {}
    // ____________________________________________________________
    virtual void doIt(IlvGraphic* obj, IlvContainer* view);
};

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
static IlvSymbol* __associatedObject;
static IlvSymbol* __paletteObject;
static IlvViewGridInteractor* gridInteractor;
ILVDEFINEINITCLASS(paledit, __associatedObject = IlvGetSymbol("AssociatedObject"); __paletteObject    = IlvGetSymbol("PaletteObject"); gridInteractor = new IlvViewGridInteractor(); )
#else
static IlvSymbol* __associatedObject = IlvGetSymbol("AssociatedObject");
static IlvSymbol* __paletteObject    = IlvGetSymbol("PaletteObject");
static IlvViewGridInteractor* gridInteractor = new IlvViewGridInteractor();
#endif

// --------------------------------------------------------------------------
void
IlvColumnViewInteractor::doIt(IlvGraphic* o, IlvContainer*)
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
    IlvPaletteSelector* papal=(IlvPaletteSelector*)arg;
    papal->destroy();
}

// --------------------------------------------------------------------------
inline IlvPaletteSelector*
getPaletteSelector(IlvGridObj* grid)
{
    return (IlvPaletteSelector*)grid->getProperty(__paletteObject);
}

// --------------------------------------------------------------------------
static void
ChoosePatternCallback(IlvView*, IlvGridObj* g, IlvGraphic*, IlvBoolean, IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p) p->callCallback((IlvPattern*)arg);
}

// --------------------------------------------------------------------------
static void
ChooseLineStyleCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
			IlvBoolean, IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p) p->callCallback((IlvLineStyle*)arg);
}

// --------------------------------------------------------------------------
static void
ChooseLineWidthCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
			IlvBoolean, IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p)
	p->callCallback(IlCastIlAnyToIlUShort(arg));
}

// --------------------------------------------------------------------------
static void
ChooseColorCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p) p->callCallback((IlvColor*)arg);
}

// --------------------------------------------------------------------------
static void
ChooseArcModeCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p) p->callCallback((IlvArcMode)IlCastIlAnyToIlUInt(arg));
}

// --------------------------------------------------------------------------
static void
ChooseBgFgCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		   IlvBoolean , IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p) p->background(IlCastIlAnyToIlUInt(arg)? IlTrue : IlFalse);
}

// --------------------------------------------------------------------------
static void
ChooseFillRuleCallback(IlvView*, IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
    if (p) p->callCallback((IlvFillRule)IlCastIlAnyToIlUInt(arg));
}

// --------------------------------------------------------------------------
static void
ChooseFillStyleCallback(IlvView*,  IlvGridObj* g, IlvGraphic*,
		      IlvBoolean , IlvAny arg)
{
    IlvPaletteSelector* p = getPaletteSelector((IlvGridObj*)g);
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
	} else
	    return -1;
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
IlvPaletteSelector::IlvPaletteSelector(IlvDisplay*    display,
				     const IlvRect& size,
				     IlvBoolean     visible)
: _fillbackground(IlvFalse),_destroyPaletteCallback(0),_argPaletteCallback(0)
{
    _display = display;
    _topview = new IlvTopView(display,
			     "Palette Editor",
			     "Palette Editor",
			     size, visible);
    _topview->setDestroyCallback(DestroyTopView, this);

    IlvRect scrollsize(0, 0, size.w(), size.h());
    IlvScrollView* scrollview = new IlvScrollView(_topview, scrollsize);
    IlvRect csize(0, 0, WIDTH+20, size.h()*2);
    IlvRowColumnView * column=new IlvRowColumnView(scrollview, csize);
    init(column);
}
// --------------------------------------------------------------------------
IlvPaletteSelector::IlvPaletteSelector(IlvDisplay*    display,
				       IlvSystemView xany)
: _fillbackground(IlvFalse),_destroyPaletteCallback(0),_argPaletteCallback(0)
{
    _display = display;
    _topview = 0;
    IlvRowColumnView * column=new IlvRowColumnView(display,xany);
    init(column);
}
// --------------------------------------------------------------------------
IlvPaletteSelector::IlvPaletteSelector(IlvDisplay*    display,
				       IlvRowColumnView * column)
: _fillbackground(IlvFalse),_destroyPaletteCallback(0),_argPaletteCallback(0)
{
    _display = display;
    _topview = 0;
    init(column);
}

// --------------------------------------------------------------------------
void
IlvPaletteSelector::init(IlvRowColumnView* column)
{
    _interactor =  new IlvColumnViewInteractor(column);
    IlvRect rect(0, 0, 100, 100);
    IlvGraphic* obj;
    IlvPoint p(0, 0);

    //Makes LineStyle
    obj = new IlvReliefLabel(_display, p, "Show LineStyle");
    column->addObject(obj);
    column->setObjectInteractor(obj, _interactor);
    obj->invert();

    IlvList* styles=_display->getLineStyles();
    IlvLineStyle* sty;
    IlvGraphicSet* objset;
    IlvUInt length = styles->length();
    IlvRect prect(0, 0, WIDTH, HEIGHTSTY);
    IlvGridObj*  grid = new IlvGridObj(_display, prect,
				       (IlvUShort)(length/2), 2,
				       IlvGridNoSelection);
    obj->addProperty(__associatedObject, grid);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    IlvMapList(styles, IlvLineStyle*, sty,
	      obj=new IlvLine(_display, IlvPoint(0, 50), IlvPoint(98, 50));
	      obj->setLineStyle(sty);
	      objset = new IlvGraphicSet(2, obj,
					new IlvRectangle(_display, rect));
	      grid->add(objset, IlvFalse, ChooseLineStyleCallback, sty);
	      );
    grid->addProperty(__paletteObject, this);
    // Make LineWidth
    obj = new IlvReliefLabel(_display, p, "Show LineWidth");
    column->addObject(obj);
    column->setObjectInteractor(obj, _interactor);
    obj->invert();

    IlvRect lrect(0, 0, WIDTH, HEIGHTSTY);
    grid = new IlvGridObj(_display, lrect, 4, 2, IlvGridNoSelection);
    obj->addProperty(__associatedObject, grid);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    for (IlvUShort i=0; i<8; i++) {
	obj = new IlvLine(_display, IlvPoint(0, 50), IlvPoint(98, 50));
	obj->setLineWidth(i);
	objset = new IlvGraphicSet(2, obj, new IlvRectangle(_display, rect));
	grid->add(objset, IlvFalse, ChooseLineWidthCallback, IlCastIlUShortToIlAny(i));
    }
    grid->addProperty(__paletteObject, this);

    IlvPoint origin(0, 0);

    // ------------------------------------------------------------
    // Patterns
    // ------------------------------------------------------------
    obj = new IlvReliefLabel(_display, p, "Show Patterns");
    column->addObject(obj);
    column->setObjectInteractor(obj, _interactor);
    obj->invert();

    IlvList* all_patterns=_display->getPatterns();
    IlvUInt l = all_patterns->length();
    IlvRect Prect(0, 0, WIDTH, HEIGHTPAT);
    grid = new IlvGridObj(_display, Prect, 4, (IlvUShort)(l/4),
			 IlvGridNoSelection);
    obj->addProperty(__associatedObject, grid);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    IlvPattern* pattern;
    IlvMapList(all_patterns, IlvPattern*, pattern,
	      obj=new IlvFilledRectangle(_display, rect);
	      obj->setPattern(pattern);
	      grid->add(obj, IlvFalse, ChoosePatternCallback, pattern);
	      );
    grid->addProperty(__paletteObject, this);

    // ------------------------------------------------------------
    // Colors
    // ------------------------------------------------------------
    obj = new IlvReliefLabel(_display, p, "Show Colors");
    column->addObject(obj);
    column->setObjectInteractor(obj, _interactor);
    obj->invert();

    IlvRect Crect(0, 0, WIDTH, HEIGHTPAT);
    int nbcolors = sizeof(__colors)/sizeof(arraychar); //LESS THAN 256 !!!!!
    int gridsize;
    for (gridsize = 3; gridsize*gridsize < nbcolors; gridsize++);
    grid = new IlvGridObj(_display, Crect,
			  (IlvUShort)gridsize, (IlvUShort)gridsize,
			  IlvGridNoSelection);
    obj->addProperty(__associatedObject, grid);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->addProperty(__paletteObject, this);
    IlvColor* fg;
    // First store Black and White, then sort the colors:
    obj=new IlvFilledRectangle(_display, rect);
    fg = _display->getColor("Black");
    obj->setForeground(fg);
    grid->add(obj, IlvFalse, ChooseColorCallback, fg);
    obj=new IlvFilledRectangle(_display, rect);
    fg = _display->getColor("White");
    obj->setForeground(fg);
    grid->add(obj, IlvFalse, ChooseColorCallback, fg);

    IlvColor* allcolors[256];
    int colorloop = 0;
    int loop;
    for (loop = 0; loop < nbcolors; loop++) {
	allcolors[colorloop] = _display->getColor(__colors[loop]);
	if (allcolors[colorloop])
	    colorloop++;
	else
	    IlvWarning("Color %s not found", __colors[loop]);
    }
    qsort((char*)allcolors, colorloop, sizeof(IlvColor*), colorcompare);
    for (loop=0; loop<colorloop; loop++) {
	obj = new IlvFilledRectangle(_display, rect);
	obj->setForeground(allcolors[loop]);
	grid->add(obj, IlvFalse, ChooseColorCallback, allcolors[loop]);
    }
    // Make Bg/Fg switch
    IlvRect Brect(0, 0, WIDTH, HEIGHTSMALL);
    grid = new IlvGridObj(_display, Brect, 2, 1, IlvGridExclusiveSelection);
    grid->add(new IlvLabel(_display, origin, "Background"),
	      IlvFalse, ChooseBgFgCallback,(IlvAny)1);
    grid->add(obj = new IlvLabel(_display, origin, "Foreground"), IlvFalse,
	      ChooseBgFgCallback,(IlvAny)0);
    grid->makeSelected(obj);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->addProperty(__paletteObject, this);

    // Make ArcMode switch
    IlvRect Arect(0, 0, WIDTH, HEIGHTSMALL);
    grid = new IlvGridObj(_display, Arect, 2, 1, IlvGridExclusiveSelection);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    obj = new IlvFilledArc(_display, rect, (IlvFloat)30, (IlvFloat)150);
    obj->setArcMode(IlvArcChord);
    grid->add(obj, IlvFalse, ChooseArcModeCallback, (IlvAny)(int)IlvArcChord);
    grid->addProperty(__paletteObject, this);
    obj = new IlvFilledArc(_display, rect, (IlvFloat)30, (IlvFloat)150);
    grid->add(obj, IlvFalse, ChooseArcModeCallback, (IlvAny)(int)IlvArcPie);
    grid->makeSelected(obj);

    IlvPoint points[5] = {
	IlvPoint(94, 19),
	IlvPoint(19, 17),
	IlvPoint(80, 53),
	IlvPoint(55, -5),
	IlvPoint(37, 53) };

    IlvRect Mrect(0, 0, WIDTH, HEIGHTSMALL);
    grid = new IlvGridObj(_display, Mrect, 2, 1, IlvGridExclusiveSelection);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->add(obj=new IlvPolygon(_display, 5, points), IlvFalse,
	      ChooseFillRuleCallback,(IlvAny)(int)IlvWindingRule);
    obj->setFillRule(IlvWindingRule);
    grid->add(obj=new IlvPolygon(_display, 5, points), IlvFalse,
		 ChooseFillRuleCallback, (IlvAny)(int)IlvEvenOddRule);
    grid->makeSelected(obj);
    grid->addProperty(__paletteObject, this);

    // Make FillStyle chooser
    IlvRect Orect(0, 0, WIDTH, HEIGHTSMALL);
    grid = new IlvGridObj(_display, Orect, 3, 1, IlvGridNoSelection);
    column->addObject(grid);
    column->setObjectInteractor(grid, gridInteractor);
    grid->add(new IlvLabel(_display, origin, "ColorPattern"), IlvFalse,
	      ChooseFillStyleCallback, (IlvAny)(int)IlvFillColorPattern);
    grid->add(obj=new IlvLabel(_display, origin, "MaskPattern"), IlvFalse,
	      ChooseFillStyleCallback, (IlvAny)(int)IlvFillMaskPattern);
    grid->add(obj=new IlvLabel(_display, origin, "Pattern"), IlvFalse,
	      ChooseFillStyleCallback,(IlvAny)(int)IlvFillPattern);
    grid->addProperty(__paletteObject, this);
}

// --------------------------------------------------------------------------
IlvPaletteSelector::~IlvPaletteSelector()
{
    delete _interactor;
    if (_topview) delete _topview;
}

// --------------------------------------------------------------------------
void
IlvPaletteSelector::setDestroyPaletteCallback(IlvDestroyPaletteSelector callb,
					     IlvAny arg)
{
    _destroyPaletteCallback = callb;
    _argPaletteCallback     = arg;
}

// --------------------------------------------------------------------------
void
IlvPaletteSelector::destroy()
{
    // Destroy from WM just prevent users
    // But don't try to call delete on view they are already destroyed
    if (_destroyPaletteCallback) {
	_destroyPaletteCallback(this, _argPaletteCallback);
	delete this;
    }
}

// --------------------------------------------------------------------------
void
IlvPaletteSelector::show()
{
    if (_topview) _topview->show();
}

// --------------------------------------------------------------------------
void
IlvPaletteSelector::hide()
{
    if (_topview) _topview->hide();
}

// --------------------------------------------------------------------------
void
IlvPaletteSelector::show(IlvPos x, IlvPos y)
{
    if (_topview)  {
	_topview->move(IlvPoint(x, y));
	_topview->show();
    }
}
