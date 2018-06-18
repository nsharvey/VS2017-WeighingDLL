// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/vpfilv.cpp
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
// Definition of the VpfIlvReader class
// --------------------------------------------------------------------------

// Rogue Wave Views default scale factors.
// Because VPF uses floating point values, and Rogue Wave Views works in an
// integer coordinates system, the VPF values will be multiplied by this
// factor.
// The value of 1000 means you will get three precision digits.
#define SX 1000
#define SY 1000

#include <vpf/vpfilv.h>
#include <ilviews/base/memory.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/label.h>
#include <ilviews/gadgets/spinbox.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadgets/fontsel.h>

#if defined(VPFSTD)
VPFSTDUSE
#endif
#include <ilviews/base/sstream.h>

#if defined(Lynx) || defined(WINDOWS) || defined(_WIN32)
#include <limits.h>
#include <math.h>
#else  /* !Lynx */
#include <values.h>
#endif /* !Lynx */
#if !defined(FLT_MAX)
#define FLT_MAX 3.402823466E+38
#endif
#include <stdio.h>

// --------------------------------------------------------------------------
VpfIlvReader::VpfIlvReader(IlvDisplay* display, const char* databasepathname)
: VpfReader(databasepathname),
  _manager(new IlvManager(display)),
  _percentage(0)
{
}

// --------------------------------------------------------------------------
VpfIlvReader::~VpfIlvReader()
{
    delete _manager;
}

// --------------------------------------------------------------------------
static IlvPoint&
Scale(const VpfCoordinate& c)
{
    static IlvPoint p;
    p.move((IlvPos)((c.getLongitude() == FLT_MAX)
		    ?  40000
		    :  ((c.getLongitude() * SX)+.5)),
	   (IlvPos)((c.getLatitude()  == FLT_MAX)
		    ? -40000
		    : -((c.getLatitude() * SY)+.5)));
    return p;
}

// --------------------------------------------------------------------------
VpfCoordinate&
VpfIlvReader::whereIs(double x, double y) const
{
    x /=  (double)SX;
    y /= -(double)SY;
    return VpfReader::whereIs(x, y);
}

// --------------------------------------------------------------------------
void
VpfIlvReader::loadingFeature(VpfUInt n, VpfUInt max)
{
    if (!n) {
	printf("0%%");
	fflush(stdout);
	_percentage = 0;
    } else
    if (n > (max-1) * _percentage / 100) {
	_percentage += 10;
	printf("...%d%%", _percentage);
	fflush(stdout);
    } else
    if (n == max-1)
	printf("\n");

}

// --------------------------------------------------------------------------
void
VpfIlvReader::createNode(const VpfCoordinate& coords, void* arg)
{
    VpfIlvInfo* info = (VpfIlvInfo*)arg;
    storeObject(new IlvMarker(getDisplay(),
			      Scale(coords),
			      (IlvMarkerType)(info
					      ? info->getMarkerType()
					      : IlvMarkerSquare),
			      (IlUShort)(info
					  ? info->getMarkerSize()
					  : IlvDefaultMarkerSize),
			      info
			      ? info->getPalette()
			      : 0));
}


// --------------------------------------------------------------------------
#define MaxPolylineSize 500L
void
VpfIlvReader::createEdge(VpfInt count, VpfCoordinate* coords, void* arg)
{
    if (!count)
	return;
    VpfIlvInfo* info = (VpfIlvInfo*)arg;
    IlvPoint* points = IlvAllocPoints(count);
    for (VpfInt loop = 0; loop < count; loop++)
	points[loop] = Scale(coords[loop]);
    if (count == 2) {
	storeObject(new IlvLine(getDisplay(),
				points[0], points[1],
				info ? info->getPalette() : 0));
	return;
    }
    if (count > MaxPolylineSize) {
	IlInt start = 0;
	do {
	    storeObject(new IlvPolyline(getDisplay(),
					IlMin(MaxPolylineSize,
					       (long)(count-start)),
					points,
					info ? info->getPalette() : 0));
	    points += MaxPolylineSize-1;
	    start += MaxPolylineSize;
	} while (start < count);
    } else
	storeObject(new IlvPolyline(getDisplay(), count, points,
				    info ? info->getPalette() : 0));
}

// --------------------------------------------------------------------------
void
VpfIlvReader::createFace(VpfInt count, VpfCoordinate* coords, void* arg)
{
    if (!count)
	return;
    VpfIlvInfo* info = (VpfIlvInfo*)arg;
    IlvPoint* points = IlvAllocPoints(count);
    for (VpfInt loop=0; loop<count; loop++)
	points[loop] = Scale(coords[loop]);
    storeObject(new IlvPolygon(getDisplay(), count, points,
			       info ? info->getPalette() : 0));
}

// --------------------------------------------------------------------------
void
VpfIlvReader::createText(const VpfCoordinate& where, const char* text,
			 void* arg)
{
    VpfIlvInfo* info = (VpfIlvInfo*)arg;
    storeObject(new IlvLabel(getDisplay(), Scale(where), text,
			     info ? info->getPalette() : 0));
}

// --------------------------------------------------------------------------
void
VpfIlvReader::storeObject(IlvGraphic* object)
{
    _manager->addObject(object, IlFalse, _layer);
}

// --------------------------------------------------------------------------
// Class VpfIlvInfo
// --------------------------------------------------------------------------
VpfIlvInfo::~VpfIlvInfo()
{
    if (_palette)
	_palette->unLock();
}

// --------------------------------------------------------------------------
char
VpfIlvInfo::getName() const
{
    char ret = 0;
    if (_type == VpfFeatureType::Line)
	ret = 'E';
    else
    if (_type == VpfFeatureType::Area)
	ret = 'F';
    else
    if (_type == VpfFeatureType::Text)
	ret = 'T';
    else
    if (_type == VpfFeatureType::Point)
	ret  = 'N';
    return ret;
}

// --------------------------------------------------------------------------
void
VpfIlvInfo::drawPreview(IlvPort* dst, const IlvRect& rect) const
{
    IlvPalette * palette = _palette ?
	_palette : dst->getDisplay()->defaultPalette();
    if (_type == VpfFeatureType::Line)
	dst->drawLine(palette,
		      IlvPoint(rect.x(), rect.centery()),
		      IlvPoint(rect.right(), rect.centery()));
    else
    if (_type == VpfFeatureType::Area)
	dst->fillRectangle(palette, rect);
    else
    if (_type == VpfFeatureType::Text)
	dst->drawLabel(palette, "Aa", 2, rect);
    else
    if (_type == VpfFeatureType::Point)
	dst->drawMarker(palette, rect.center(), _markerType, _markerSize);
}


// --------------------------------------------------------------------------
void
VpfIlvInfo::setPalette(IlvPalette * palette)
{
    palette->lock();
    if (_palette)
	_palette->unLock();
    _palette = palette;
}

// --------------------------------------------------------------------------
static void
DialogClosed(IlvView* v,
	     IlAny)
{
    ((IlvDialog*)v)->cancel();
}

// --------------------------------------------------------------------------
// NodeResourceDialog
// --------------------------------------------------------------------------
static void
NodeColorCB(IlvGraphic*,
	    IlAny arg)
{
    NodeResourceDialog* dialog = (NodeResourceDialog*)arg;
    IlvColorSelector selector(dialog->getDisplay(), dialog->getSystemView());
    selector.set(dialog->getPaletteForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	dialog->setPaletteForeground(color);
    dialog->bufferedDraw(dialog->getForegroundRect());
}

// --------------------------------------------------------------------------
static void
NodeStyleCB(IlvGraphic* g,
	    IlAny arg)
{
    IlvOptionMenu* option = (IlvOptionMenu*) g;
    NodeResourceDialog* dialog = (NodeResourceDialog*)arg;
    dialog->setMarkerStyle((IlvMarkerType)(1<<option->whichSelected()));
    dialog->bufferedDraw(dialog->getMarker());
}

// --------------------------------------------------------------------------
static const char NodeResourceData[] =
"// Ilv Version: 2.5\n\
// File generated: Tue Feb 10 17:35:56 1998\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 4\n\
3  \"defaultBg\" \"defaultFg\" \"%times-12-\" 0 solid solid 0 0 0\n\
2  \"defaultBg\" \"defaultFg\" \"button\" \"%helvetica-12-B\" 0 solid solid 0 0 0\n\
\"IlvStText\" 0 \"defaultBg\" \"defaultFg\" \"normal\" \"%helvetica-12-\" 0 solid solid 0 0 0\n\
1 \"defaultBg\" \"defaultFg\" \"fixed\" 0 solid solid 0 0 0\n\
IlvObjects 11\n\
1 { 0 0 IlvMessageLabel 14 11 106 22 0 \"Foreground\" 1 } 0\n0\n\
1 { 1 1 IlvFilledRectangle 127 11 113 22 } 32 \"ForegroundRect\"\n0\n\
1 { 2 0 IlvMessageLabel 14 42 91 22 0 \"Node Style\" 1 } 0\n0\n\
1 { 3 2 IlvButton 271 10 92 23 F1 2 16 Y \"Select\" } 32 \"SelectButton\"\n0\n1 { 4 2 IlvButton 10 117 73 23 F1 2 16 Y \"Apply\" } 512\n1\n1 \"__ilvCallback\" \"apply\"\n0\n\
1 { 5 2 IlvButton 298 117 73 23 F1 2 16 Y \"Cancel\" } 512\n1\n1 \"__ilvCallback\" \"cancel\"\n0\n\
1 { 6 3 IlvReliefLine 2 105 378 105 2 } 0\n0\n\
1 { 7 0 IlvMessageLabel 14 69 97 22 0 \"Node Size\" 1 } 0\n0\n\
1 { 8 0 IlvSpinBox 269 69 92 22 2 0 200 32 2 1\n0 IlvNumberField 269 69 50 22 F6 2 2 -1 0 \"0\" . , 2 16 -3.40282e+38 3.40282e+38  f 1 1 1 0 } 32 \"SizeSpin\"\n0\n\
1 { 9 1 IlvMarker 179 52 1 10 } 32 \"Marker\"\n0\n\
1 { 10 0 IlvOptionMenu 269 42 92 22 2 8 0\n\"square\"\n\"diamond\"\n\"circle\"\n\"cross\"\n\"plus\"\n\"filledSquare\"\n\"filledCircle\"\n\"filledDiamond\" } 32 \"StyleCombo\"\n0\nSize 383 145\n";

NodeResourceDialog::NodeResourceDialog(IlvView* view, VpfIlvInfo* info)
    :  IlvDialog(view->getDisplay(), "Node Resources", "Node Resources",
		 IlvRect(20, 20, 383, 145),
		 IlvNoResizeBorder,
		 view->getSystemView()),
       _info(info)
{
    {
	istrstream s((char*)NodeResourceData);
	read(s);
    }
    setDestroyCallback(DialogClosed);
    // Init Fields
    IlvPalette* palette = _info->getPalette() ?
	_info->getPalette() : getDisplay()->defaultPalette();
    _foregroundRect = (IlvFilledRectangle*)getObject("ForegroundRect");
    _foregroundRect->setForeground(palette->getForeground());
    _marker = (IlvMarker*)getObject("Marker");
    _marker->setType(_info->getMarkerType());
    IlvOptionMenu* option = (IlvOptionMenu*)getObject("StyleCombo");
    IlUShort pos, type;
    for (pos = 0, type = _info->getMarkerType(); type != 1; pos++, type >>= 1);
    option->setSelected(pos);
    option->setCallback(NodeStyleCB, this);

    IlvSpinBox* spin = (IlvSpinBox*) getObject("SizeSpin");
    spin->setValue((IlvNumberField*)spin->getObject(0),
		   (IlDouble)_info->getMarkerSize());
    getObject("SelectButton")->setCallback(NodeColorCB, this);
}

// --------------------------------------------------------------------------
void
NodeResourceDialog::setMarkerStyle(IlvMarkerType style)
{
    _marker->setType(style);
}

// --------------------------------------------------------------------------
void
NodeResourceDialog::setPaletteForeground(IlvColor* color)
{
    _foregroundRect->setForeground(color);
}

// --------------------------------------------------------------------------
IlvColor*
NodeResourceDialog::getPaletteForeground() const
{
    return _foregroundRect->getForeground();
}

// --------------------------------------------------------------------------
void
NodeResourceDialog::apply()
{
    IlvDialog::apply();
    _info->setPalette(getDisplay()->
		      getPalette(0, _foregroundRect->getForeground()));

    IlvSpinBox* spin = (IlvSpinBox*)getObject("SizeSpin");
    IlBoolean error;
    _info->setMarkerSize((IlUShort)spin->getValue((IlvNumberField*)
						  spin->getObject(0), error));

    IlvOptionMenu* option = (IlvOptionMenu*) getObject("StyleCombo");
    _info->setMarkerType((IlvMarkerType)(1 << option->whichSelected()));
}

// --------------------------------------------------------------------------
// EdgeResourceDialog
// --------------------------------------------------------------------------
static void ILVCALLBACK
EdgeColorCB(IlvGraphic*,
	    IlAny arg)
{
    EdgeResourceDialog* dialog = (EdgeResourceDialog*)arg;
    IlvColorSelector selector(dialog->getDisplay(), dialog->getSystemView());
    selector.set(dialog->getPaletteForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	dialog->setPaletteForeground(color);
    dialog->bufferedDraw(dialog->getForegroundRect());
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
LineStyleCB(IlvGraphic* g,
	    IlAny arg)
{
    IlvScrolledComboBox* combo = (IlvScrolledComboBox*)g;
    EdgeResourceDialog* dialog = (EdgeResourceDialog*)arg;
    dialog->setPaletteLineStyle(dialog->getDisplay()->
				getLineStyle(combo->getSelection()));
    dialog->bufferedDraw(dialog->getLineStyle());
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
LineWidthCB(IlvGraphic* g,
	    IlAny arg)
{
    IlvScrolledComboBox* combo = (IlvScrolledComboBox*) g;
    EdgeResourceDialog* dialog = (EdgeResourceDialog*) arg;
    IlvRect bboxBefore;
    dialog->getLineWidth()->boundingBox(bboxBefore);
    bboxBefore.expand(dialog->getLineWidth()->getLineWidth());
    dialog->setPaletteLineWidth((IlUShort)combo->getIntValue());
    IlvRect bboxAfter;
    dialog->getLineWidth()->boundingBox(bboxAfter);
    bboxAfter.expand(dialog->getLineWidth()->getLineWidth());
    bboxAfter.add(bboxBefore);
    dialog->bufferedDraw(bboxAfter);
}

// --------------------------------------------------------------------------
static const char EdgeResourceData[] =
"// Ilv Version: 2.5\n\
// File generated: Tue Feb 10 17:20:46 1998\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 5\n\
\"default\" 4 \"defaultBg\" \"defaultFg\" \"default\" \"fixed\" 0 solid solid 0 0 0\n\
3  \"defaultBg\" \"defaultFg\" \"%helvetica-12\" 0 solid solid 0 0 0\n\
2  \"defaultBg\" \"defaultFg\" \"button\" \"%helvetica-12-B\" 0 solid solid 0 0 0\n\
\"IlvStText\" 0 \"defaultBg\" \"defaultFg\" \"normal\" \"%helvetica-12-\" 0 solid solid 0 0 0\n\
1 \"defaultBg\" \"defaultFg\" \"fixed\" 0 solid solid 0 0 0\n\
IlvObjects 12\n\
1 { 0 0 IlvMessageLabel 14 11 106 22 0 \"Foreground\" 1 } 0\n0\n\
1 { 1 1 IlvFilledRectangle 127 11 113 22 } 32 \"ForegroundRect\"\n0\n\
1 { 2 0 IlvMessageLabel 14 42 79 22 0 \"Line Style\" 1 } 0\n0\n\
1 { 3 0 IlvScrolledComboBox 269 42 92 22 F7 2 8 \"\"\n\"solid\"\n\"dash\"\n\"dot\"\n\"dashdot\"\n\"dashdoubledot\"\n\"alternate\"\n\"doubledot\"\n\"longdash\" 4 } 32 \"StyleCombo\"\n0\n\
1 { 4 2 IlvButton 271 10 92 23 F1 2 16 Y \"Select\" } 32 \"SelectButton\"\n0\n\
1 { 5 2 IlvButton 10 117 73 23 F1 2 16 Y \"Apply\" } 512\n1\n1 \"__ilvCallback\" \"apply\"\n0\n\
1 { 6 2 IlvButton 298 117 73 23 F1 2 16 Y \"Cancel\" } 512\n1\n1 \"__ilvCallback\" \"cancel\"\n0\n\
1 { 7 3 IlvReliefLine 2 105 378 105 2 } 0\n0\n\
1 { 8 4 IlvLine 127 52 240 52 } 32 \"LineStyle\"\n0\n\
1 { 9 0 IlvMessageLabel 14 69 86 22 0 \"Line Width\" 1 } 0\n0\n\
1 { 10 4 IlvLine 127 79 240 79 } 32 \"LineWidth\"\n0\n\
1 { 11 0 IlvScrolledComboBox 269 69 92 22 F6 2 6 \"0\"\n\"1\"\n\"2\"\n\"3\"\n\"4\"\n\"5\"\n\"6\" 4 } 32 \"WidthCombo\"\n0\n\
Size 383 145\n";

EdgeResourceDialog::EdgeResourceDialog(IlvView* view, VpfIlvInfo* info)
    :  IlvDialog(view->getDisplay(), "Edge Resources", "Edge Resources",
		 IlvRect(20, 20, 383, 145),
		 IlvNoResizeBorder,
		 view->getSystemView()),
       _info(info)
{
    {
	istrstream s((char*)EdgeResourceData);
	read(s);
    }
    setDestroyCallback(DialogClosed);

    // Init Fields
    IlvPalette* palette = _info->getPalette() ?
	_info->getPalette() : getDisplay()->defaultPalette();
    _foregroundRect = (IlvFilledRectangle*)getObject("ForegroundRect");
    _foregroundRect->setForeground(palette->getForeground());
    _lineStyle = (IlvLine*)getObject("LineStyle");
    _lineStyle->setLineStyle(palette->getLineStyle());
    _lineWidth = (IlvLine*)getObject("LineWidth");
    _lineWidth->setLineWidth(palette->getLineWidth());
    IlvScrolledComboBox* combo = (IlvScrolledComboBox*)getObject("StyleCombo");
    combo->setLabel(palette->getLineStyle()->getName());
    combo->setCallback(LineStyleCB, this);
    combo = (IlvScrolledComboBox*) getObject("WidthCombo");
    combo->setValue((IlInt)palette->getLineWidth());
    combo->setCallback(LineWidthCB, this);
    getObject("SelectButton")->setCallback(EdgeColorCB, this);
}

// --------------------------------------------------------------------------
void
EdgeResourceDialog::setPaletteLineWidth(IlUShort width)
{
    _lineWidth->setLineWidth(width);
}

// --------------------------------------------------------------------------
void
EdgeResourceDialog::setPaletteLineStyle(IlvLineStyle* style)
{
    _lineStyle->setLineStyle(style);
}

// --------------------------------------------------------------------------
void
EdgeResourceDialog::setPaletteForeground(IlvColor* color)
{
    _foregroundRect->setForeground(color);
}

// --------------------------------------------------------------------------
IlvColor*
EdgeResourceDialog::getPaletteForeground() const
{
    return _foregroundRect->getForeground();
}

// --------------------------------------------------------------------------
void
EdgeResourceDialog::apply()
{
    IlvDialog::apply();
    _info->setPalette(getDisplay()->
		      getPalette(0,
				 _foregroundRect->getForeground(),
				 0,
				 0,
				 0,
				 _lineStyle->getLineStyle(),
				 _lineWidth->getLineWidth()));
}

// --------------------------------------------------------------------------
// FaceResourceDialog
// --------------------------------------------------------------------------
static void
FaceColorCB(IlvGraphic*,
	    IlAny arg)
{
    FaceResourceDialog* dialog = (FaceResourceDialog*)arg;
    IlvColorSelector selector(dialog->getDisplay(),
			      dialog->getSystemView());
    selector.set(dialog->getPaletteForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	dialog->setPaletteForeground(color);
    dialog->bufferedDraw(dialog->getForegroundRect());
}

// --------------------------------------------------------------------------
static void
FacePatternCB(IlvGraphic* g,
	      IlAny arg)
{
    IlvScrolledComboBox* combo = (IlvScrolledComboBox*)g;
    FaceResourceDialog* dialog = (FaceResourceDialog*)arg;
    dialog->setPalettePattern(dialog->getDisplay()->
			      getPattern(combo->getSelection()));
    dialog->bufferedDraw(dialog->getPatternRect());
}

static const char FaceResourceData[] =
"// Ilv Version: 2.5\n\
// File generated: Tue Feb 10 17:29:32 1998\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 4\n\
3 \"defaultBg\" \"defaultFg\" \"%times-12-\" 0 solid solid 0 0 0\n\
2 \"defaultBg\" \"defaultFg\" \"button\" \"%helvetica-12-B\" 0 solid solid 0 0 0\n\
\"IlvStText\" 0 \"defaultBg\" \"defaultFg\" \"normal\" \"%helvetica-12-\" 0 solid solid 0 0 0\n\
1 \"defaultBg\" \"defaultFg\" \"fixed\" 0 solid solid 0 0 0\n\
IlvObjects 9\n\
1 { 0 0 IlvMessageLabel 14 11 106 22 0 \"Foreground\" 1 } 0\n0\n\
1 { 1 1 IlvFilledRectangle 127 11 113 22 } 32 \"ForegroundRect\"\n0\n\
1 { 2 0 IlvMessageLabel 14 42 95 22 0 \"Pattern\" 1 } 0\n0\n\
1 { 3 1 IlvFilledRectangle 127 42 113 22 } 32 \"PatternRect\"\n0\n\
1 { 4 0 IlvScrolledComboBox 269 42 92 22 F7 2 12 \"clear\"\n\"solid\"\n\"clear\"\n\"gray\"\n\"cross\"\n\"dark1\"\n\"dark2\"\n\"dark3\"\n\"dark4\"\n\"light1\"\n\"light2\"\n\"light3\"\n\"light4\" 4 } 32 \"PatternCombo\"\n0\n\
1 { 5 2 IlvButton 271 10 92 23 F1 2 16 Y \"Select\" } 32 \"SelectButton\"\n0\n\
1 { 6 2 IlvButton 8 90 73 23 F1 2 16 Y \"Apply\" } 512\n1\n1 \"__ilvCallback\" \"apply\"\n0\n\
1 { 7 2 IlvButton 296 90 73 23 F1 2 16 Y \"Cancel\" } 512\n1\n1 \"__ilvCallback\" \"cancel\"\n0\n\
1 { 8 3 IlvReliefLine 0 78 376 78 2 } 0\n0\nSize 381 118\nEOF\n";

FaceResourceDialog::FaceResourceDialog(IlvView* view, VpfIlvInfo* info)
    :  IlvDialog(view->getDisplay(), "Face Resources", "Face Resources",
		 IlvRect(20, 20, 381, 118),
		 IlvNoResizeBorder,
		 view->getSystemView()),
       _info(info)
{
    {
	istrstream s((char*)FaceResourceData);
	read(s);
    }
    setDestroyCallback(DialogClosed);
    // Init Fields
    IlvPalette* palette = _info->getPalette() ?
	_info->getPalette() : getDisplay()->defaultPalette();
    _foregroundRect = (IlvFilledRectangle*)getObject("ForegroundRect");
    _patternRect    = (IlvFilledRectangle*)getObject("PatternRect");
    _foregroundRect->setForeground(palette->getForeground());
    _patternRect->setPattern(palette->getPattern());
    IlvScrolledComboBox* combo = (IlvScrolledComboBox*)
	getObject("PatternCombo");
    combo->setLabel(palette->getPattern()->getName());
    combo->setCallback(FacePatternCB, this);
    getObject("SelectButton")->setCallback(FaceColorCB, this);
}

// --------------------------------------------------------------------------
void
FaceResourceDialog::setPalettePattern(IlvPattern* pattern)
{
    _patternRect->setPattern(pattern);
}

// --------------------------------------------------------------------------
void
FaceResourceDialog::setPaletteForeground(IlvColor* color)
{
    _foregroundRect->setForeground(color);
}

// --------------------------------------------------------------------------
IlvColor*
FaceResourceDialog::getPaletteForeground() const
{
    return _foregroundRect->getForeground();
}

// --------------------------------------------------------------------------
void
FaceResourceDialog::apply()
{
    IlvDialog::apply();
    _info->setPalette(getDisplay()->
		      getPalette(0,
				 _foregroundRect->getForeground(),
				 _patternRect->getPattern()));
}

// --------------------------------------------------------------------------
// TextResourceDialog
// --------------------------------------------------------------------------
static void
TextColorCB(IlvGraphic*,
	    IlAny arg)
{
    TextResourceDialog* dialog = (TextResourceDialog*)arg;
    IlvColorSelector selector(dialog->getDisplay(), dialog->getSystemView());
    selector.set(dialog->getPaletteForeground());
    selector.moveToMouse();
    IlvColor* color = selector.get();
    if (color)
	dialog->setPaletteForeground(color);
    dialog->bufferedDraw(dialog->getForegroundRect());
}

// --------------------------------------------------------------------------
static void
TextFontCB(IlvGraphic*,
	   IlAny arg)
{
    TextResourceDialog* dialog = (TextResourceDialog*)arg;
    IlvFontSelector selector(dialog->getDisplay(), dialog->getSystemView());
    selector.moveToMouse();
    IlvFont* font = selector.get();
    if (font)
	dialog->setPaletteFont(font);
    dialog->bufferedDraw(dialog->getText());
}

static const char TextResourceData[] =
"// Ilv Version: 2.5\n\
// File generated: Tue Feb 10 17:40:54 1998\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 4\n\
3 \"defaultBg\" \"defaultFg\" \"%times-12-\" 0 solid solid 0 0 0\n\
2 \"defaultBg\" \"defaultFg\" \"button\" \"%helvetica-12-B\" 0 solid solid 0 0 0\n\
\"IlvStText\" 0 \"defaultBg\" \"defaultFg\" \"normal\" \"%helvetica-12-\" 0 solid solid 0 0 0\n\
1 \"defaultBg\" \"defaultFg\" \"fixed\" 0 solid solid 0 0 0\n\
IlvObjects 9\n\
1 { 0 0 IlvMessageLabel 14 11 106 22 0 \"Foreground\" 1 } 0\n0\n\
1 { 1 1 IlvFilledRectangle 127 11 113 22 } 32 \"ForegroundRect\"\n0\n\
1 { 2 0 IlvMessageLabel 14 42 92 22 0 \"Font\" 1 } 0\n0\n\
1 { 3 2 IlvButton 271 10 92 23 F1 2 16 Y \"Select\" } 32 \"ForegroundButton\"\n0\n\
1 { 4 2 IlvButton 8 90 73 23 F1 2 16 Y \"Apply\" } 512\n1\n1 \"__ilvCallback\" \"apply\"\n0\n\
1 { 5 2 IlvButton 296 90 73 23 F1 2 16 Y \"Cancel\" } 512\n1\n1 \"__ilvCallback\" \"cancel\"\n0\n\
1 { 6 3 IlvReliefLine 0 78 376 78 2 } 0\n0\n\
1 { 7 0 IlvMessageLabel 127 42 111 22 0 \"A B C D E F G H I\" 1 } 32 \"Text\"\n0\n\
1 { 8 2 IlvButton 271 42 92 23 F1 2 16 Y \"Select\" } 32 \"FontButton\"\n0\nSize 381 118\n";

TextResourceDialog::TextResourceDialog(IlvView* view, VpfIlvInfo* info)
    :  IlvDialog(view->getDisplay(), "Text Resources", "Text Resources",
		 IlvRect(20, 20, 381, 118),
		 IlvNoResizeBorder,
		 view->getSystemView()),
       _info(info)
{
    {
	istrstream s((char*)TextResourceData);
	read(s);
    }
    setDestroyCallback(DialogClosed);

    // Init Fields
    IlvPalette* palette = _info->getPalette() ?
	_info->getPalette() : getDisplay()->defaultPalette();
    _foregroundRect = (IlvFilledRectangle*)getObject("ForegroundRect");
    _foregroundRect->setForeground(palette->getForeground());
    _text = (IlvMessageLabel*)getObject("Text");
    _text->setFont(palette->getFont());
    getObject("ForegroundButton")->setCallback(TextColorCB, this);
    getObject("FontButton")->setCallback(TextFontCB, this);
}

// --------------------------------------------------------------------------
void
TextResourceDialog::setPaletteFont(IlvFont* font)
{
    _text->setFont(font);
}

// --------------------------------------------------------------------------
void
TextResourceDialog::setPaletteForeground(IlvColor* color)
{
    _foregroundRect->setForeground(color);
}

// --------------------------------------------------------------------------
IlvColor*
TextResourceDialog::getPaletteForeground() const
{
    return _foregroundRect->getForeground();
}

// --------------------------------------------------------------------------
void
TextResourceDialog::apply()
{
    IlvDialog::apply();
    _info->setPalette(getDisplay()->
		      getPalette(
				 0,
				 _foregroundRect->getForeground(),
				 0,
				 0,
				 _text->getFont()));
}
