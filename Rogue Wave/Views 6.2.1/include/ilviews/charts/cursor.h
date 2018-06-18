// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/cursor.h
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
// Declaration of the classes that define cursors.
// Contains:
//  - IlvAbstractChartCursor: the abstract class that allows you to define
//    a cursor that can be added to a given scale
//  - IlvRectangularChartCursor: a subclass of IlvAbstractChartCursor
//    which allows you to define a rectangular cursor that can be used with a
//    cartesian chart.
//  - IlvCircularChartCursor: a subclass of IlvAbstractChartCursor
//    which allows you to define a circular cursor that can be used with a
//    polar chart.
//  - IlvRadialChartCursor: a subclass of IlvAbstractChartCursor
//    which allows you to define a radial cursor that can be used with a
//    polar chart.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Cursor_H
#define __Ilv_Charts_Cursor_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Common_H)
#include <ilviews/charts/common.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif

class IlvSingleScaleDisplayer;
class IlvCircularScaleDisplayer;
class IlvRadialChartCursor;
class IlvCircularChartCursor;
// --------------------------------------------------------------------------
// IlvAbstractChartCursor persistence
// --------------------------------------------------------------------------

class IlvAbstractChartCursor;

typedef IlvAbstractChartCursor* (*IlvChartCursorConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvChartCursorClassInfo : public IlvValuedClassInfo
{
public:
    inline
    IlvChartCursorClassInfo* getChartCursorSuperClass() const
			{
			    return ILVDYNAMICCAST(IlvChartCursorClassInfo*,
						  getSuperClass());
			}
    inline
    IlvChartCursorConstructor getConstructor() const
			{
			    return _constructor;
			}
    static
    IlvChartCursorClassInfo* Create(const char*,
				    IlvClassInfo**,
				    IlvChartCursorConstructor);

protected:
    IlvChartCursorClassInfo(const char* className,
			    IlvClassInfo** superClass,
			    IlvChartCursorConstructor c)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(c)
	{}
    IlvChartCursorConstructor _constructor;
};

#define IlvRegisterChartCursorClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,				\
		IlvChartCursorClassInfo::Create(#classname,	\
		ILVSUPERCLASSINFO(superclass),		\
		(IlvChartCursorConstructor)classname::Read))
#define IlvPreRegisterChartCursorClass(classname) \
  ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterChartCursorClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
		IlvChartCursorClassInfo::Create(#classname,	\
		ILVSUPERCLASSINFO(superclass),		\
		(IlvChartCursorConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvAbstractChartCursor
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAbstractChartCursor : public IlvValueInterface
{
private:
    enum { 
	DrawGhost	= 0x0001,
	DrawAxisMark	= 0x0002,
	DrawDelimiter	= 0x0004
    };
public:
    virtual ~IlvAbstractChartCursor();

    // Accessors ================
    inline IlBoolean	isVisible() const { return _visible; }

    void		setVisible(IlBoolean visible) { _visible = visible; }

    inline const char*	getName() const 
			{
			    return _name.isEmpty()
				? (const char*)0
				: (const char*)_name;
			}
    inline void		setName(const char* name) { _name = name; }

    void		setPalette(IlvPalette* palette);

    IlvPalette*		getPalette() const;

    void		setDrawOrder(IlvDrawOrder drawOrder)
			{
			    _drawOrder = drawOrder;
			}
    IlvDrawOrder	getDrawOrder() const { return _drawOrder; }

    inline IlBoolean	isDrawingGhost() const 
			{
			    return (_drawMode & DrawGhost) ? IlTrue : IlFalse;
			}
    inline void		drawGhost(IlBoolean ghost)
			{
			    if (ghost)
				_drawMode |= DrawGhost;
			    else
				_drawMode &= ~DrawGhost;
			}

    inline IlBoolean	isDrawingAxisMark() const 
			{
			    return (_drawMode & DrawAxisMark)
				? IlTrue
				: IlFalse;
			}
    inline void		drawAxisMark(IlBoolean draw)
			{	
			    if (draw)
				_drawMode |= DrawAxisMark;
			    else
				_drawMode &= ~DrawAxisMark;
			}

    inline IlBoolean	isDrawingDelimiter() const
			{
			    return (_drawMode & DrawDelimiter)
				? IlTrue
				: IlFalse;
			}
    inline void		drawDelimiter(IlBoolean draw)
			{
			    if (draw)
				_drawMode |= DrawDelimiter;
			    else
				_drawMode &= ~DrawDelimiter;
			}

    inline void		setValue(IlDouble value) { _value = value; }
    inline IlDouble	getValue() const { return _value; }
    void		setLabel(const char* label) { _label = label;}

    const char*		getLabel() const { return _label; }


    // Drawing
    virtual void	draw(const IlvSingleScaleDisplayer* scale,
			     const IlvPoint&	cursorPoint,
			     IlDouble		cursorAngle,
			     const IlvRect&	scaleDataDisplayArea,
			     IlvPort*		dst,
			     const IlvRegion*	clip) const;

    virtual void	boundingBox(const IlvSingleScaleDisplayer* scale,
				    const IlvPoint&	cursorPoint,
				    IlDouble		cursorAngle,
				    const IlvRect&	scaleDataDisplayArea,
				    IlvRect&		bbox) const;

    virtual void	drawDelimiter(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvPort*		dst,
				      const IlvRegion*	clip) const = 0;

    virtual void	delimiterBBox(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvRect&		bbox) const = 0;

    virtual void	drawAxisMark(const IlvSingleScaleDisplayer* scale,
				     const IlvPoint&	cursorPoint,
				     IlDouble		cursorAngle,
				     IlvPort*		dst,
				     const IlvRegion*	clip) const;

    virtual void	axisMarkBBox(const IlvSingleScaleDisplayer* scale,
				     const IlvPoint&	cursorPoint,
				     IlDouble		cursorAngle,
				     IlvRect&		bbox) const;

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode mode);

    virtual IlvAbstractChartCursor* copy() const = 0;

    // Persistence
    IlvOutputFile&	save(IlvOutputFile&) const;
    static IlvAbstractChartCursor* Load(IlvInputFile&);
    virtual void	write(IlvOutputFile&) const;

    IlvDeclarePropRootClassInfo();

protected:
    IlBoolean		_visible;
    IlString		_name;
    IlvPalette*		_palette;
    IlvDrawOrder	_drawOrder;
    IlDouble		_value;
    IlString		_label;
    int			_drawMode;

    // Constructors
    IlvAbstractChartCursor(IlDouble value, IlvPalette* palette=0);
    IlvAbstractChartCursor(const IlvAbstractChartCursor& cursor);
    IlvAbstractChartCursor(IlvInputFile& file);
};

// --------------------------------------------------------------------------
// Class IlvRectangularChartCursor
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvRectangularChartCursor : public IlvAbstractChartCursor
{
public:
    IlvRectangularChartCursor(IlDouble value, IlvPalette* palette=0);

    virtual ~IlvRectangularChartCursor();

    virtual void	drawDelimiter(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvPort*		dst,
				      const IlvRegion*	clip) const;

    virtual void	delimiterBBox(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvRect&		bbox) const;

    DeclareChartCursorTypeInfoRO(IlvRectangularChartCursor);
};

// --------------------------------------------------------------------------
// Class IlvCircularChartCursor
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCircularChartCursor : public IlvAbstractChartCursor
{
public:
    IlvCircularChartCursor(IlDouble value,
			   IlvCircularScaleDisplayer* ref,
			   IlvPalette* palette = 0);

    virtual ~IlvCircularChartCursor();

    // Accessors
    const IlvCircularScaleDisplayer* getReferenceScale() const
			{
			    return _referenceScale;
			}
    void		setReferenceScale(const IlvCircularScaleDisplayer* s)
			{
			    _referenceScale = s;
			}


    virtual void	drawDelimiter(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvPort*		dst,
				      const IlvRegion*	clip) const;

    virtual void	delimiterBBox(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvRect&		bbox) const;

    DeclareChartCursorTypeInfoRO(IlvCircularChartCursor);

protected:
    const IlvCircularScaleDisplayer* _referenceScale;

};

// --------------------------------------------------------------------------
// Class IlvRadialChartCursor
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvRadialChartCursor : public IlvAbstractChartCursor
{
public:
    IlvRadialChartCursor(IlDouble value, IlvPalette* palette = 0);

    virtual ~IlvRadialChartCursor();

    virtual void	drawDelimiter(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvPort*		dst,
				      const IlvRegion*	clip) const;

    virtual void	delimiterBBox(const IlvSingleScaleDisplayer* scale,
				      const IlvPoint&	cursorPoint,
				      IlDouble		cursorAngle,
				      const IlvRect&	scaleDataDisplayArea,
				      IlvRect&		bbox) const;

    DeclareChartCursorTypeInfoRO(IlvRadialChartCursor);
};

ILVCHTMODULEINIT(cursor);

#endif /* !__Ilv_Charts_Cursor_H */
