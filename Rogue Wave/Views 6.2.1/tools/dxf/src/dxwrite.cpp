// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/src/dxwrite.cpp
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
// Definition of the IlvDXFOutput class
// --------------------------------------------------------------------------

#include <dxfincl/dxwrite.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/spline.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/ellipse.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/set.h>
#include <ilviews/base/hash.h>
#include <ilviews/base/iostream.h>

#if defined(ILVSTD)
#include <cstring>
#include <cmath>
#include <iostream>
ILVSTDUSE
#else
#include <string.h>
#include <math.h>
#include <iostream.h>
#endif

// --------------------------------------------------------------------------
IlvDXFOutput::IlvDXFOutput(ostream& stream) : _stream(&stream)
{
    _palettes = new IlvHashTable(13);
    _graphicSets = new IlvHashTable(13);
    _lineStyles = new IlvHashTable(13);
}

// --------------------------------------------------------------------------
IlvDXFOutput::~IlvDXFOutput()
{
    delete _lineStyles;
    delete _graphicSets;
    delete _palettes;
}

// --------------------------------------------------------------------------
IlInt
IlvDXFOutput::getLayerNum(IlvPalette* palette) const
{
    static IlInt PaletteNumber = 0;
    IlInt result = IlCastIlAnyToIlInt(_palettes->find(palette));
    if (!result) {
	result = ++PaletteNumber;
	_palettes->insert(palette, IlCastIlIntToIlAny(PaletteNumber));
    }
    return result;
}

// --------------------------------------------------------------------------
IlInt
IlvDXFOutput::getGraphicSetNum(IlvGraphicSet* gs) const
{
    static IlInt GSNumber = 0;
    IlInt result = IlCastIlAnyToIlInt(_graphicSets->find(gs));
    if (!result) {
	result = ++GSNumber;
	_graphicSets->insert(gs, IlCastIlIntToIlAny(GSNumber));
    }
    return result;
}

// --------------------------------------------------------------------------
IlInt
IlvDXFOutput::getLineStyleNum(IlvLineStyle* ls) const
{
    static IlInt LSNumber = 0;
    IlInt  result = IlCastIlAnyToIlInt(_lineStyles->find(ls));
    if (!result) {
	result = ++LSNumber;
	_lineStyles->insert(ls, IlCastIlIntToIlAny(LSNumber));
    }
    return result;
}

// --------------------------------------------------------------------------
void
IlvDXFOutput::prologue()
{
    getStream() << "  0"       << endl
		<< "SECTION"   << endl
		<< " 2"        << endl
		<< "HEADER"    << endl
		<< " 0"        << endl
		<< "ENDSEC"    << endl
		<< "  0"       << endl
		<< "SECTION"   << endl
		<< "2"         << endl
		<< "TABLES"    << endl
		<< " 0"        << endl
		<< "TABLE"     << endl
		<< " 2"        << endl
		<< "APPID"     << endl
		<< " 2"        << endl
		<< "IlogViews" << endl
		<< " 70"       << endl
		<< "0"         << endl
		<< "  0"       << endl
		<< "ENDTAB"    << endl;
}

// --------------------------------------------------------------------------
void
IlvDXFOutput::epilogue()
{
    getStream() << "  0" << endl
		<< "EOF" << endl;
}

// --------------------------------------------------------------------------
#define DXNUMCOLORS 9
// DXF color table
static struct
{
    IlvInt r;
    IlvInt g;
    IlvInt b;
    int     v;
} colors[DXNUMCOLORS] = {
    { 0x000, 0x000, 0x000,  7}, // Black
    { 0xFFF, 0x000, 0x000,  1}, // Red
    { 0xFFF, 0xFFF, 0x000,  2}, // Yellow
    { 0x000, 0xFFF, 0x000,  3}, // Green
    { 0x000, 0xFFF, 0xFFF,  4}, // Cyan
    { 0x000, 0x000, 0xFFF,  5}, // Blue
    { 0xFFF, 0x000, 0xFFF,  6}, // Magenta
    { 0x800, 0x800, 0x800,  8}, // Gray
    { 0xFFF, 0xFFF, 0xFFF, 15}, // White
};

#define DISTANCE(r, g, b, i) \
	((((IlvInt)r)-colors[i].r)*(((IlvInt)r)-colors[i].r)+\
	(((IlvInt)g)-colors[i].g)*(((IlvInt)g)-colors[i].g)+\
	(((IlvInt)b)-colors[i].b)*(((IlvInt)b)-colors[i].b))

// Color matching function
static int
GetColorNum(IlvColor* color)
{
    IlvIntensity r, g, b;
    color->getRGB(r, g, b);
    r >>= 4;
    g >>= 4;
    b >>= 4;
    int idx = 0;
    IlvUInt distance = DISTANCE(r, g, b, 0);
    for (int loop = 1; (distance != 0) && (loop < DXNUMCOLORS); ++loop) {
	IlvUInt dist2 = DISTANCE(r, g, b, loop);
	if (dist2 < distance) {
	    distance = dist2;
	    idx      = loop;
	}
    }
    return colors[idx].v;
}

// --------------------------------------------------------------------------

//DXF identifiers must be uppercase

static char BUFFER[500];

static char*
uppercase(const char* string)
{
    char cn;
    for (size_t n = 0; n < strlen(string); ++n) {
	cn = string[n];
	BUFFER[n] = ((cn < 'a') || (cn > 'z')) ? cn : (char)(cn - 32);
    }
    BUFFER[strlen(string)] = 0;
    return BUFFER;
}

// --------------------------------------------------------------------------
// Saving Line Type table
static void
SaveLType(IlvAny palarg, IlvAny, IlvAny dxfarg)
{
    IlvDXFOutput* dxf		= (IlvDXFOutput*)dxfarg;
    IlvLineStyle* lstyle	= ((IlvPalette*)palarg)->getLineStyle();
    IlvUShort ndashes		= lstyle->count();
    unsigned char * dashlen	= lstyle->dashes();
    IlvUShort	i;
     IlvUShort	patlen		= 0;
    IlvShort j;
    for (i = 0; i < ndashes; ++i) {
	patlen = (IlvUShort)(patlen + dashlen[i]);
    }
    const char* name = ((IlvResource*)lstyle)->getName();
    dxf->getStream() << " 0"    << endl
		     << "LTYPE" << endl
		     << " 2"    << endl;
    if (name) {
	dxf->getStream() << uppercase(name) << endl;
    } else {
	dxf->getStream() << "LT" << dxf->getLineStyleNum(lstyle) << endl;
    }
    dxf->getStream() << "70"    << endl
		     << "64"    << endl
		     << "3"     << endl
		     << "Ilv Line Type"          << endl
		     << "72"    << endl
		     << " 65"   << endl
		     << "73"    << endl
		     << ndashes << endl
		     << "40"    << endl
		     << patlen  << endl;
    for (i = 0, j = 1; i < ndashes; ++i, j = (IlvShort)-j) {
	dxf->getStream() << "49" << endl
			 << (int)(j*dashlen[i]) << endl;
    }
}

// --------------------------------------------------------------------------
// Saving Layer table

static void
SaveLayer(IlvAny palarg, IlvAny, IlvAny dxfarg)
{
    IlvPalette*   pal = (IlvPalette*)palarg;
    IlvDXFOutput* dxf = (IlvDXFOutput*)dxfarg;
    IlvLineStyle* lstyle = pal->getLineStyle();
    const char* name = ((IlvResource*)lstyle)->getName();
    dxf->getStream() << "  0" << endl
		     << "LAYER" << endl
		     << " 70" << endl
		     << "0" << endl
		     << " 2" << endl
		     << "L" << dxf->getLayerNum(pal) << endl
		     << " 62" << endl
		     << GetColorNum(pal->getForeground()) << endl
		     << " 6" << endl;
    if (name) {
	dxf->getStream() << uppercase(name) << endl;
    } else {
	dxf->getStream() << "LT" << dxf->getLineStyleNum(lstyle) << endl;
    }
}

// --------------------------------------------------------------------------
static void
DxfComment(ostream& stream, const char* comment)
{
	stream << " 999" << endl
	       << "********** " << comment << " **********" << endl;
}

// --------------------------------------------------------------------------
// Utilitary functions for saving coordinates
// <Y> coordinate must be inverted
static  ostream&
Coords(ostream& o, const IlvPoint& p)
{
    return o << " 10"  << endl
	     <<  p.x() << endl
	     << " 20"  << endl
	     << -p.y() << endl
	     << " 30"  << endl
	     << "0."   << endl;
}

// --------------------------------------------------------------------------
static void
Vertex(IlvPoint p, ostream& stream, IlInt layernum)
{
    stream << "  0" << endl
	   << "VERTEX" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
    Coords(stream, p);
    return;
}

// --------------------------------------------------------------------------
static void
Vertex1(IlvFloat x, IlvFloat y, ostream& stream, IlInt layernum)
{
    stream << "  0" << endl
	   << "VERTEX" << endl
	   << 8 << endl
	   << "L" << layernum << endl
	   << " 10" << endl
	   << x << endl
	   << " 20" << endl
	   << -y << endl
	   << " 30" << endl
	   << " 0." << endl;
    return;
}

// --------------------------------------------------------------------------
// Saving Polylines

void
IlvDXFOutputPolyline(IlvGraphic*		object,
		     IlvDXFOutput const&	dxf,
		     IlInt			layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Polyline");
    IlvUShort lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    stream << "  0" << endl
	   << "POLYLINE" << endl
	   << " 8" << endl
	   << "L" << layernum << endl
	   << " 66" << endl << "1" << endl;
    // Group 70 1 for closed polylines
    if (object->getClassInfo() == IlvPolygon::ClassInfo()) {
	stream << " 70" << endl << "17" << endl;
    }
    //Setting line width
    stream << " 39" << endl << lw << endl; // Set thickness
    stream << " 40" << endl << lw << endl; // Set begining line width
    stream << " 41" << endl << lw << endl; // Set ending line width
    IlvPolyline* p   = (IlvPolyline*)object;
    IlvUInt   count  = p->numberOfPoints();
    IlvPoint* points = p->points();
    for (IlvUInt loop = 0; loop < count; ++loop, ++points) {
	Vertex(*points, stream, layernum);
    }
    stream << "  0" << endl
	   << "SEQEND" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
    return;
}

// --------------------------------------------------------------------------
void
IlvDXFOutputSpline(IlvGraphic* object, IlvDXFOutput const& dxf, IlInt layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Spline");
    IlvUShort lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    stream << "  0" << endl
	   << "POLYLINE" << endl
	   << " 8"  << endl
	   << "L"   << layernum << endl
	   << " 66" << endl
	   << "1"   << endl;
    if (object->getClassInfo() == IlvFilledSpline::ClassInfo()) {
	stream << " 70" << endl
	       << "17" << endl;
    }
    stream << " 39" << endl
	   << lw    << endl
	   << " 40" << endl
	   << lw    << endl
	   << " 41" << endl
	   << lw    << endl;
    IlvSpline* sp   = (IlvSpline*)object;
    IlvUInt count ;
    IlvPoint* points ;
    if (object->getClassInfo() == IlvFilledSpline::ClassInfo()) {
	points = IlvCreateClosedSpline(sp->numberOfPoints(),
				       sp->points(),
				       count);
    } else {
	points = IlvCreateOpenSpline(sp->numberOfPoints(),
				     sp->points(),
				     count);
    }
    for (IlvUInt loop = 0; loop < count; ++loop, ++points) {
	Vertex(*points, stream, layernum);
    }
    stream << "  0" << endl
	   << "SEQEND" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
}


// --------------------------------------------------------------------------
void
IlvDXFOutputRectangle(IlvGraphic*		object,
		      IlvDXFOutput const&	dxf,
		      IlInt			layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Rectangle");
    IlvUShort lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    stream << "  0" << endl
	   << "POLYLINE" << endl
	   << " 8"  << endl
	   << "L"   << layernum << endl
	   << " 66" << endl
	   << "1"   << endl;
    if (object->getClassInfo() == IlvFilledRectangle::ClassInfo()) {
	stream << "70" << endl
	       << "17" << endl;
    } else {
	stream << " 70" << endl
	       << "1"   << endl;
    }
    stream << " 39" << endl
	   << lw    << endl
	   << " 40" << endl
	   << lw    << endl
	   << " 41" << endl
	   << lw    << endl;
    IlvRectangle* re   = (IlvRectangle*)object;
    static IlvPoint point;
    point.move (re->x(), re->y());
    Vertex(point, stream, layernum);
    point.move (re->x()+re->w(), re->y());
    Vertex(point, stream, layernum);
    point.move (re->x()+re->w(), re->y()+re->h());
    Vertex(point, stream, layernum);
    point.move (re->x(), re->y()+re->h());
    Vertex(point, stream, layernum);
    point.move (re->x(), re->y());
    Vertex(point, stream, layernum);
    stream << "  0" << endl
	   << "SEQEND" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
}

// --------------------------------------------------------------------------
// Saving Ellipses (old version)
void
IlvDXFOutputEllipse0(IlvGraphic*		object,
		     IlvDXFOutput const&	dxf,
		     IlInt			layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Ellipse");
    IlvUShort n;
    IlvUShort lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    stream << "  0" << endl
	   << "POLYLINE" << endl
	   << " 8"  << endl
	   << "L"   << layernum << endl
	   << " 66" << endl
	   << "1"  << endl;
    if (object->getClassInfo() == IlvFilledEllipse::ClassInfo()) {
	stream << " 70" << endl
	       << "17"  << endl;
    } else {
	stream << " 70" << endl
	       << "1"  << endl;
    }
    stream << " 39" << endl
	   << lw    << endl;
    IlvEllipse* el = (IlvEllipse*)object;
    for (n = 0; n < 24; ++n) {
	Vertex1((IlvFloat)(el->x() + (1 + cos(n*2*3.14159/24)) * el->w()/2),
		(IlvFloat)(el->y() + (1 + sin(n*2*3.14159/24)) * el->h()/2),
		stream,
		layernum);
    }
    stream << "  0" << endl
	   << "SEQEND" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
    return;
}

// --------------------------------------------------------------------------
// Saving Ellipse, using splines
void
IlvDXFOutputEllipse(IlvGraphic*		object,
		    IlvDXFOutput const&	dxf,
		    IlInt		layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Ellipse");
    IlvUShort		lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    stream << "  0" << endl
	   << "POLYLINE" << endl
	   << " 8" << endl
	   << "L" << layernum << endl
	   << " 66" << endl
	   << "1" << endl;
    if (object->getClassInfo() == IlvFilledEllipse::ClassInfo()) {
	stream << "70" << endl
	       << "17" << endl;
    } else {
	stream << "70" << endl
	       << "1" << endl;
    }
    stream << " 39" << endl << lw << endl;
    stream << " 40" << endl << lw << endl;
    stream << " 41" << endl << lw << endl;
    IlvEllipse*		el = (IlvEllipse*)object;
    static IlvPoint	cpoints[4];
    IlvUInt		count;
    IlvUInt		loop;
    IlvPoint*		points ;

    cpoints[0].move(el->x(), el->y() + el->h()/2);
    cpoints[1].move(el->x(), el->y() + (IlvPos)(el->h()/2*1.551));
    cpoints[2].move(el->x() + (IlvPos)(el->w()/2*.449), el->y() + el->h());
    cpoints[3].move(el->x() + el->w()/2, el->y() + el->h());
    points = IlvCreateOpenSpline(4, cpoints, count);
    for (loop = 0; loop < count; ++loop, ++points) {
	Vertex(*points, stream, layernum);
    }
    cpoints[3].move(el->x() + el->w(), el->y() + el->h()/2);
    cpoints[2].move(el->x() + el->w(), el->y() + (IlvPos)(el->h()/2*1.551));
    cpoints[1].move(el->x() + (IlvPos)(el->w()/2*1.551), el->y() + el->h());
    cpoints[0].move(el->x() + el->w()/2, el->y() + el->h());
    points = IlvCreateOpenSpline(4, cpoints, count);
    for (loop = 0; loop < count; ++loop, ++points) {
	Vertex(*points, stream, layernum);
    }

    cpoints[0].move(el->x() + el->w(), el->y() + el->h()/2);
    cpoints[1].move(el->x() + el->w(), el->y() + (IlvPos)(el->h()/2*.449));
    cpoints[2].move(el->x() + (IlvPos)(el->w()/2*1.551), el->y());
    cpoints[3].move(el->x() + el->w()/2, el->y());
    points = IlvCreateOpenSpline(4, cpoints, count);
    for (loop = 0; loop < count; ++loop, ++points) {
	Vertex(*points, stream, layernum);
    }

    cpoints[3].move(el->x(), el->y()  +el->h()/2);
    cpoints[2].move(el->x(), el->y() + (IlvPos)(el->h()/2*.449));
    cpoints[1].move(el->x() + (IlvPos)(el->w()/2*.449), el->y());
    cpoints[0].move(el->x() + el->w()/2, el->y());
    points = IlvCreateOpenSpline(4, cpoints, count);
    for (loop = 0; loop < count; ++loop, ++points) {
	Vertex(*points, stream, layernum);
    }
    stream << "  0" << endl
	   << "SEQEND" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
}

// --------------------------------------------------------------------------
// Saving Labels
void
IlvDXFOutputLabel(IlvGraphic* object, IlvDXFOutput const& dxf, IlInt layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Label");
    IlvLabel* la = (IlvLabel*)object;
    static IlvPoint point;
    if (object->getClassInfo() == IlvFilledLabel::ClassInfo()) {
	stream << "  0" << endl
	       << "POLYLINE" << endl
	       << " 8" << endl
	       << "L" << layernum << endl
	       << " 66" << endl << "1" << endl
	       << " 70" << endl
	       << "17"  << endl
	       << " 62" << endl
	       << GetColorNum(la->getBackground()) << endl;
	point.move (la->x(), la->y());
	Vertex(point, stream, layernum);
	point.move (la->x()+la->w(), la->y());
	Vertex(point, stream, layernum);
	point.move (la->x()+la->w(), la->y()+la->h());
	Vertex(point, stream, layernum);
	point.move (la->x(), la->y()+la->h());
	Vertex(point, stream, layernum);
	point.move (la->x(), la->y());
	Vertex(point, stream, layernum);
	stream << "  0" << endl
	       << "SEQEND" << endl
	       << " 8" << endl
	       << "L" << layernum << endl;
    }
    stream << "  0" << endl
	   << "TEXT" << endl
	   << " 8" << endl
	   << "L" << layernum << endl;
    point.move(la->x(), la->y());
    Coords(stream, point);
    stream << " 40" << endl << la->h() << endl
	   << "1" << endl << la->getLabel() << endl;
}

// --------------------------------------------------------------------------
// Saving Lines (old version)
void
IlvDXFOutputLine0(IlvGraphic* object, IlvDXFOutput const& dxf, IlInt layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Line");
    IlvUShort lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    IlvLine* l = (IlvLine*)object;
    stream << "  0"  << endl
	   << "LINE" << endl
	   << " 8"   << endl
	   << "L"    << layernum << endl;
    stream << " 39"  << endl
	   << lw     << endl;
    Coords(stream, l->getFrom())
	<< " 11"     << endl
	<< l->getTo().x() << endl
	<< " 21"     << endl
	<< -l->getTo().y() << endl
	<< " 31"     << endl
	<< "0."      << endl;
}

// --------------------------------------------------------------------------
// Saving Lines, using polylines thus allowing line width
void
IlvDXFOutputLine(IlvGraphic* object, IlvDXFOutput const& dxf, IlInt layernum)
{
    ostream& stream = dxf.getStream();
    DxfComment(stream, "Line");
    IlvUShort lw = ((IlvSimpleGraphic*)object)->getLineWidth();
    IlvLine* l = (IlvLine*)object;
    stream << "  0" << endl
	   << "POLYLINE" << endl
	   << " 8"  << endl
	   << "L"   << layernum << endl
	   << " 66" << endl
	   << "1"   << endl;
    stream << " 39" << endl
	   << lw    << endl;
    stream << " 40" << endl
	   << lw    << endl;
    stream << " 41" << endl
	   << lw    << endl;
    Vertex(l->getFrom(), stream, layernum);
    Vertex(l->getTo(), stream, layernum);
    stream << "  0" << endl
	   << "SEQEND" << endl
	   << " 8"  << endl
	   << "L"   << layernum << endl;
}

// --------------------------------------------------------------------------
// Saving GraphicSets
void
IlvDXFOutputGraphicSet(IlvGraphic*		object,
		       IlvDXFOutput const&	dxf,
		       IlInt			layernum)
{
    DxfComment(dxf.getStream(), "GraphicSet");
    IlvGraphicSet* gs = (IlvGraphicSet*)object;
    dxf.getStream() << " 0" << endl
		    << "INSERT" << endl
		    << " 8" << endl
		    << "L" << layernum << endl
		    // << "67" << endl << "1" << endl
		    << " 2" << endl
		    << "B" << dxf.getGraphicSetNum(gs) << endl;
    static IlvPoint point;
    point.move(0, 0);
    Coords(dxf.getStream(), point);
    dxf.getStream() << " 41" << endl
		    << " 1"  << endl
		    << " 42" << endl
		    << " 1"  << endl
		    << " 50" << endl
		    << " 0"  << endl;
}

// --------------------------------------------------------------------------
// General saving function, new types may be added
void
DXFSaveObject(IlvGraphic* object, IlvDXFOutput const& dxf, IlInt layernum)
{
    const IlvClassInfo* classInfo = object->getClassInfo();
    if ((classInfo == IlvPolyline::ClassInfo()) ||
	(classInfo == IlvPolygon::ClassInfo())) {
	IlvDXFOutputPolyline(object, dxf, layernum);
	return;
    }
    if (classInfo == IlvLine::ClassInfo()) {
	IlvDXFOutputLine(object, dxf, layernum);
	return;
    }
    if ((classInfo == IlvSpline::ClassInfo()) ||
	(classInfo == IlvFilledSpline::ClassInfo())) {
	IlvDXFOutputSpline(object, dxf, layernum);
	return;
    }
    if ((classInfo == IlvRectangle::ClassInfo()) ||
	(classInfo == IlvFilledRectangle::ClassInfo())) {
	IlvDXFOutputRectangle(object, dxf, layernum);
	return;
    }
    if ((classInfo == IlvLabel::ClassInfo()) ||
	    (classInfo == IlvFilledLabel::ClassInfo())) {
	IlvDXFOutputLabel(object, dxf, layernum);
	return;
    }
    if ((classInfo == IlvEllipse::ClassInfo()) ||
	(classInfo == IlvFilledEllipse::ClassInfo())) {
	IlvDXFOutputEllipse(object, dxf, layernum);
	return;
    }
    if (classInfo == IlvGraphicSet::ClassInfo()) {
	IlvDXFOutputGraphicSet(object, dxf, 0);
	return;
    }
    IlvFatalError("Cannot convert instances of the %s class",
		  object->className());
}

// --------------------------------------------------------------------------
void
IlvDXFOutput::saveObject(IlvGraphic* object)
{
    IlInt layernum = 0;
    if (object->isSubtypeOf(IlvSimpleGraphic::ClassInfo()))
	layernum = getLayerNum(IL_CAST(IlvSimpleGraphic*, object)->getPalette());
    DXFSaveObject(object, *this, layernum);
}

// --------------------------------------------------------------------------
// Controlling that each block is save once and only once
// May be fully implemented for sub types of Graphic Sets
static void
BlockIsSaved(IlvGraphic* const)
{
}

// --------------------------------------------------------------------------
static int
IsBlockSaved(IlvGraphic* const)
{
	return 0;
}

// --------------------------------------------------------------------------
// Saving a block (and recursively sub-blocks)
static void
SaveBlock(IlvDXFOutput const& dxf, IlvGraphic* const object)
{
    IlvGraphicSet* gs = (IlvGraphicSet*)object;
    IlvUInt count;
    IlvUInt loop;
    count = gs->getCardinal();
    // First save sub-sets
    for (loop = 0; loop < count; ++loop) {
	if (gs->getObject(loop)->isSubtypeOf(IlvGraphicSet::ClassInfo())
	    && (IsBlockSaved(gs->getObject(loop)) == 0))
	    SaveBlock(dxf, gs->getObject(loop));
    }
    dxf.getStream() << " 0" << endl
		    << "BLOCK" << endl
		    << " 8" << endl
		    << "L0" << endl
		    << " 2" << endl
		    << "B" << dxf.getGraphicSetNum(gs) << endl
		    << " 70" << endl
		    << " 64" << endl
		    << " 10" << endl
		    << " 0." << endl
		    << " 20" << endl
		    << " 0." << endl
		    << " 30" << endl
		    << " 0." << endl
		    << " 3" << endl
		    << "B" << dxf.getGraphicSetNum(gs) << endl ;
    for (loop = 0; loop < count; ++loop) {
	IlvGraphic* obj = gs->getObject(loop);
	DXFSaveObject(obj,
		      dxf,
		      (obj->isSubtypeOf(IlvSimpleGraphic::ClassInfo())
		       ? dxf.getLayerNum(IL_CAST(IlvSimpleGraphic*,
						 obj)->getPalette())
		       : 0));
    }
    dxf.getStream() << " 0" << endl
		    << "ENDBLK" << endl
		    << " 8" << endl
		    << "L0" << endl;
    BlockIsSaved(gs);
}

// --------------------------------------------------------------------------
static void
SaveBlocks(IlvDXFOutput const& dxf, IlvGraphic* const* objects, IlvUInt count)
{
    IlvUInt loop;
    for (loop = 0; loop < count; ++loop) {
	if (objects[loop]->getClassInfo() == IlvGraphicSet::ClassInfo()) {
	    SaveBlock(dxf, objects[loop]);
	}
    }
}

static void StoreGSPalettes(IlvDXFOutput const&	dxf,
			    IlInt&		palnum,
			    IlvGraphic* const	object);

// --------------------------------------------------------------------------
// Saving a palette
static inline void
StorePalette(IlvDXFOutput const& dxf, IlInt& palnum, IlvGraphic* const object)
{
    if (object->isSubtypeOf(IlvSimpleGraphic::ClassInfo())) {
	palnum = dxf.getLayerNum(IL_CAST(IlvSimpleGraphic*,object)->getPalette());
    } else if (object->isSubtypeOf(IlvGraphicSet::ClassInfo())) {
	StoreGSPalettes(dxf, palnum, object);
    }
}

// --------------------------------------------------------------------------
// Saving palettes found in blocks and sub blocks
static void
StoreGSPalettes(IlvDXFOutput const& dxf, IlInt& palnum, IlvGraphic* const object)
{
    IlvGraphicSet* gs = (IlvGraphicSet*)object;
    IlvUInt count = gs->getCardinal();
    for (IlvUInt loop = 0; loop < count; ++loop) {
	StorePalette(dxf, palnum, gs->getObject(loop));
    }
}

// --------------------------------------------------------------------------
// Saving palettes
static void
StorePalettes(IlvDXFOutput const&	dxf,
	      IlInt&			palnum,
	      IlvGraphic* const*	objects,
	      IlvInt			count)
{
    for (IlvInt loop = 0; loop < count; ++loop) {
	StorePalette(dxf, palnum, objects[loop]);
    }
}

// --------------------------------------------------------------------------
// Main saving function
void
IlvDXFOutput::save(IlvManager* manager)
{
    IlvUInt count;
    IlvGraphic* const* objects = (IlvGraphic* const*)manager->getObjects(count);
    if (!count) {
	return;
    }
    IlvRect onebbox;
    objects[0]->boundingBox(_bbox);
    IlvUInt loop;
    for (loop = 0; loop < count; ++loop) {
	objects[loop]->boundingBox(onebbox);
	_bbox.add(onebbox);
    }
    prologue();
    // Getting all palettes
    IlInt palnum = 0;
    StorePalettes(*this, palnum, objects, count);
    // Write out line types descriptions
    getStream() << "  0" << endl
		<< "TABLE" << endl
		<< "  2" << endl
		<< "LTYPE" << endl
		<< " 70" << endl
		<< palnum << endl;
    _palettes->mapHash(SaveLType, this);
    // Write out palettes descriptions
    getStream() << "  0" << endl
		<< "ENDTAB" << endl
		<< "  0" << endl
		<< "TABLE" << endl
		<< "  2" << endl
		<< "LAYER" << endl
		<< " 70" << endl
		<< palnum << endl;
    _palettes->mapHash(SaveLayer, this);
    // Write out blocks descriptions
    getStream() << "  0" << endl
		<< "ENDTAB" << endl
		<< "  0" << endl
		<< "ENDSEC" << endl // End of TABLES section
		<< "  0" << endl
		<< "SECTION" << endl
		<< " 2" << endl
		<< "BLOCKS" << endl;
    SaveBlocks(*this, objects, count);
    // Write out actual objects
    getStream() << "  0" << endl
		<< "ENDSEC" << endl
		<< "  0" << endl
		<< "SECTION" << endl
		<< "  2" << endl
		<< "ENTITIES" << endl;
    for (loop = 0; loop < count; ++loop) {
	saveObject(objects[loop]);
    }
    getStream() << "  0" << endl
		<< "ENDSEC" << endl; // End of ENTITIES section
    epilogue();
}
