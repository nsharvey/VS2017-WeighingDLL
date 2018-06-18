// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/util.h
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
// Declaration of general purposes functions
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Util_H
#define __Ilv_Util_Util_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInPolygon(const IlvPoint&	p,
		  IlUInt		count,
		  const IlvPoint*	poly,
		  IlBoolean		windingRule = IlFalse);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInPolyline(const IlvPoint& p, IlUInt count, const IlvPoint* poly);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInLine(const IlvPoint& p, const IlvPoint& from, const IlvPoint& to);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvIntersectHorizontal(const IlvPoint&	point,
		       const IlvPoint&	from,
		       const IlvPoint&	to,
		       IlInt*		dir = 0);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvLinesIntersect(const IlvPoint&	from1,
		  const IlvPoint&	to1,
		  const IlvPoint&	from2,
		  const IlvPoint&	to2,
		  IlvPoint*		result = 0 /* if needed */ );

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInSpline(const IlvPoint&, IlUInt count, const IlvPoint* points);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInClosedSpline(const IlvPoint&	p,
		       IlUInt		count,
		       const IlvPoint*	points);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInFilledSpline(const IlvPoint&	p,
		       IlUInt		count,
		       const IlvPoint*	points,
		       IlBoolean	windingRule = IlFalse);

ILVDSPEXPORTEDFUNCTION(IlDouble)
IlvDistanceToBezier(const IlvPoint&	p,
		    const IlvPoint*	bezier,
		    int			length,
		    IlBoolean		closed,
		    IlDouble*		param,
		    IlInt*		segment);

ILVDSPEXPORTEDFUNCTION(IlDouble)
IlvDistanceToPolyline(const IlvPoint&	p,
		      const IlvPoint*	polyline,
		      int		length,
		      IlBoolean		closed,
		      IlDouble*		param,
		      IlInt*		segment);

ILVDSPEXPORTEDFUNCTION(IlvPoint*)
IlvCreateOpenSpline(IlUInt		count,
		    const IlvPoint*	points,
		    IlUInt&		totalcount);
ILVDSPEXPORTEDFUNCTION(IlvPoint*)
IlvCreateClosedSpline(IlUInt		count,
		      const IlvPoint*	points,
		      IlUInt&		totalcount);

ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInArc(const IlvPoint&, const IlvRect&, IlFloat, IlFloat r);
ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvPointInFilledArc(const IlvPoint&,
		    const IlvRect&,
		    IlFloat,
		    IlFloat r,
		    IlvArcMode arcmode = IlvArcPie);
ILVDSPEXPORTEDFUNCTION(void)
IlvComputeArcBBox(const IlvRect&	rect,
		  IlFloat		start,
		  IlFloat		range,
		  IlvRect&		bbox);

ILVDSPEXPORTEDFUNCTION(void)
IlvSetDeltaLine(IlFloat);
ILVDSPEXPORTEDFUNCTION(IlFloat)
IlvGetDeltaLine();
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDeltaArc(IlFloat);
ILVDSPEXPORTEDFUNCTION(IlFloat)
IlvGetDeltaArc();

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvPoint& p);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvFloatPoint& p);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvDeltaPoint& p);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvRect& rect);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvRegion& region);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvFloatRect& rect);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& o, const IlvTransformer& transf);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvPoint& p);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvFloatPoint& p);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvDeltaPoint& p);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvRect& rect);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvFloatRect& rect);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& i, IlvTransformer& transf);
class IlvSkipSpaces { public: IlvSkipSpaces(){} };
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& is, const IlvSkipSpaces&);
class IlvSkipTo { public: IlvSkipTo(int c) : _c(c) {} int _c; };
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& is, const IlvSkipTo&);

// --------------------------------------------------------------------------
inline IlBoolean
IlvIsSpace(int c)
{
    return ((c == ' ') || (c == '\n') || (c == '\r') || (c == '\t'))
	? IlTrue
	: IlFalse;
}

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBaseInputFile
{
public:
    IlvBaseInputFile(IL_STDPREF istream&);
    virtual ~IlvBaseInputFile();

    inline IlvDisplay*	getDisplay() const { return _display; }
    void		setStream(IL_STDPREF istream& stream) 
			{
			    _istream = &stream;
			}
    inline
    IL_STDPREF istream&	getStream() const { return *_istream; }
    inline
    operator IL_STDPREF	istream&() { return *_istream; }

    // Reading resources __________________________________________
    virtual IlvColor*	createColor(const char* colName, IlBoolean fg);
    virtual IlvColor*	createColor(IlvIntensity,
				    IlvIntensity,
				    IlvIntensity,
				    IlBoolean);
    IlvColor*		readColor(IlBoolean foreground);
    virtual IlvPattern*	createPattern(const char* patternName);
    IlvPattern*		readPattern();
    virtual
    IlvColorPattern*	createColorPattern(const char* patternName);
    IlvColorPattern*	readColorPattern();
    IlvGradientPattern*	readGradientPattern();
    virtual
    IlvLineStyle*	createLineStyle(const char* lineStyleName);
    IlvLineStyle*	readLineStyle();
    virtual IlvFont*	createFont(const char* fontName);
    IlvFont*		readFont(int& fs);
    virtual IlvPalette*	createPalette(const char*		paletteName,
				      IlvColor*			bg,
				      IlvColor*			fg,
				      IlvPattern*		pattern,
				      IlvColorPattern*		pixpattern,
				      IlvFont*			font,
				      IlvLineStyle*		style,
				      IlUShort			width,
				      IlvFillStyle		fs,
				      IlvArcMode		am,
				      IlvFillRule		fr,
				      IlvIntensity		alpha,
				      IlvAntialiasingMode	antialias,
				      IlvGradientPattern*	gradpattern);
    IlvPalette*		readPalette(const char* paletteName = 0);

protected:
    inline void		setDisplay(IlvDisplay* disp) { _display = disp; }

private:
    IlvDisplay*		_display;
    IL_STDPREF istream*	_istream;
};

ILVDSPEXPORTEDFUNCTION(void)
IlvComputeArrow(const IlvPoint&		from,
		const IlvPoint&		to,
		IlFloat			atpos,
		IlvPoint*		points,
		IlvDim			arrowBase   = 4,
		IlvDim			arrowLength = 8);

#define IlvPi 3.141592653589
// --------------------------------------------------------------------------
inline IlDouble
IlvDegreesToRadians(IlDouble angle) { return angle * IlvPi / 180.; }
// --------------------------------------------------------------------------
inline IlDouble
IlvRadiansToDegrees(IlDouble angle) { return angle * 180 / IlvPi; }
// --------------------------------------------------------------------------

ILVDSPEXPORTEDFUNCTION(const char*)
IlvCreateNewName(const char* root);

ILVDSPEXPORTEDFUNCTION(const char*) IlvSpc();
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream&, const IlSymbol*);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream&, const IlvPalette*);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream&, const IlvColor*);

// --------------------------------------------------------------------------
// IO of quoted strings
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvQuotedString
{
public:
    IlvQuotedString(const char* string = 0) : _string(string) {}
    static char*	Buffer;
    inline const char*	getString() const { return _string; }

private:
    const char*		_string;
};
ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& os, const IlvQuotedString&);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& is, const IlvQuotedString&);

ILVDSPEXPORTEDFUNCTION(void)
IlvWriteString(IL_STDPREF ostream& stream, const char* string);
ILVDSPEXPORTEDFUNCTION(char*)
IlvReadString(IL_STDPREF istream& is, char* buffer = 0);

ILVDSPEXPORTEDFUNCTION(const char*)
IlvGetCurrentDate();

// Typed array of IlvPoint
class ILVDSPEXPORTED IlDeclareArrayOf(IlvPoint, IlvArrayOfPoints);

// Old bug on VMS... Seems to be removed since OpenVMS 7
#define IlvPatchStreamOperator(in, buffer) in >> buffer

#endif /* !__Ilv_Util_Util_H */
