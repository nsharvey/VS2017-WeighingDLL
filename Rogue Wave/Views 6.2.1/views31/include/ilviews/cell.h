// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/cell.h
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
// Declaration of the IlvCell class and some predefined subclasses.
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Cell_H
#define __Ilv31_Cell_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Alloc_H)
#include <ilviews/base/alloc.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#include <ilviews/base/link.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

class IlvCell;
class IlvCellManager;
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCell
{
protected:
    IlvPalette* _palette;
    IlvPalette* _invpalette;
    IlUShort   _column;
    IlUShort   _row;
    IlAList*   _properties;
    IlUShort   _width;
    IlUShort   _height;
    union {
	char*    _string;
	IlFloat _float;
	IlInt   _long;
    }_value;
    void internalDraw(const char* s, IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect=0) const;
public:
    IlvCell(IlvDisplay* display,const char* s,IlvPalette* pal=0,
	    IlvPalette* invpal=0);
    IlvCell(IlvDisplay* display,IlvPalette* pal=0,
	    IlvPalette* invpal=0);
    virtual ~IlvCell();
    IL_MLK_DECL();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual void write(ILVSTDPREF ostream&) const;
    virtual void read(ILVSTDPREF istream&);
    // ____________________________________________________________
    inline void       addProperty(IlSymbol* key, IlAny value);
    inline IlBoolean removeProperty(IlSymbol* key);
    inline IlBoolean replaceProperty(IlSymbol* key, IlAny value);
    inline IlAny     getProperty(IlSymbol* key) const;
    inline IlBoolean hasProperty(IlSymbol* key) const;
    // ____________________________________________________________
    IlUShort getColumn()  const { return _column; }
    IlUShort getRow()     const { return _row;    }
    void      setPosition(IlUShort col,IlUShort row)
	{ _column = col; _row = row; }
    IlUShort getWidth()  const { return _width;  }
    void      setWidth(IlUShort w)  { _width  = w; }
    IlUShort getHeight() const { return _height; }
    void      setHeight(IlUShort h) { _height = h; }
    virtual void getFittingSizes(IlvDim& width, IlvDim& height) const;
    virtual const char* getLabel() const;
    virtual void        setLabel(const char* s);
    IlvDisplay*  getDisplay()  const { return _palette->getDisplay(); }
    IlvPalette*  getPalette()  const { return _palette;}
    virtual void setPalette(IlvPalette* palette);
    IlvPalette* getInvertedPalette()  const { return _invpalette;}
    virtual void draw(IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect=0) const;
    virtual void setFont(IlvFont*);
    virtual void setBackground(IlvColor*);
    virtual void setForeground(IlvColor*);
    virtual void setPattern(IlvPattern*);
    virtual void setColorPattern(IlvColorPattern*);
    virtual void setFillStyle(IlvFillStyle);
    virtual void setMode(IlvDrawMode);
    virtual void invert();
    IlvFont*         getFont() const  { return _palette->getFont();       }
    IlvColor*   getBackground() const { return _palette->getBackground(); }
    IlvColor*   getForeground() const    { return _palette->getForeground(); }
    IlvPattern*      getPattern() const  { return _palette->getPattern();    }
    IlvColorPattern* getColorPattern() const{ return _palette->getColorPattern();}
    IlvFillStyle     getFillStyle() const { return _palette->getFillStyle();  }
    IlvDrawMode      getMode() const  { return _palette->getMode();       }
    virtual void setValue(IlInt);
    virtual void setValue(IlFloat);
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvCell::addProperty(IlSymbol* key , IlAny value)
{
    if(!_properties) _properties=new IlAList();
    _properties->insert((IlAny)key,value);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline IlBoolean
IlvCell::removeProperty(IlSymbol* key)
{
    return (_properties)
	? _properties->remove((IlAny)key), IlTrue
	    : IlFalse;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline IlBoolean
IlvCell::replaceProperty(IlSymbol* key , IlAny value)
{
    return (IlBoolean)
	((_properties) ? _properties->replace((IlAny)key, value) : IlFalse);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline IlAny
IlvCell::getProperty(IlSymbol* key) const
{
    return (_properties) ? _properties->get((IlAny)key) : 0;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline IlBoolean
IlvCell::hasProperty(IlSymbol* key) const
{
    return (IlBoolean)
	((_properties) ? _properties->find((IlAny)key) : IlFalse);
}

#define IlvCellDelta 2
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvReliefCell
: public IlvCell {
protected:
    IlUShort      _thickness;
    IlvPalette*    _topshadow;
    IlvPalette*    _bottomshadow;
    IlvPalette*    _selpalette;
    void computePalettes();
    void decrPalettes() {
	_topshadow->unLock();
	_bottomshadow->unLock();
	_selpalette->unLock();
    }
public:
    IlvReliefCell(IlvDisplay* display,
		  const char* s,
		  IlUShort   thickness = 2,
		  IlvPalette* palette   = 0);
    IlvReliefCell(IlvDisplay* display,
		  IlUShort   thickness = 2,
		  IlvPalette* palette   = 0);
    IlvReliefCell(IlvDisplay* display,
		  const char* s,
		  IlvPalette* palette,
		  IlvPalette* invpalette,
		  IlvPalette* toppalette,
		  IlvPalette* shadowpalette,
		  IlvPalette* selpalette);
    IlvReliefCell(IlvReliefCell* model,
		  const char* s);
    virtual ~IlvReliefCell();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual void write(IL_STDPREF ostream&) const;
    virtual void draw(IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect=0) const;
    virtual void setPalette(IlvPalette* palette);
    virtual void setBackground(IlvColor*);
    virtual void setForeground(IlvColor*);
    virtual void setPattern(IlvPattern*);
    virtual void setMode(IlvDrawMode);
    virtual void invert();
    virtual void setFillStyle(IlvFillStyle);
    virtual void getFittingSizes(IlvDim& width, IlvDim& height) const;
    IlUShort getThickness() const            { return _thickness;    }
    void      setThickness(IlUShort thickness) { _thickness=thickness; }
    IlvPalette* getTopShadowPalette() const  {return _topshadow;}
    IlvPalette* getBottomShadowPalette() const  {return _bottomshadow;}
    IlvPalette* getSelectionPalette() const  {return _selpalette;}
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvIntCell
: public IlvCell {
public:
    IlvIntCell(IlvDisplay* ,IlInt f, IlvPalette* pal=0,
	       IlvPalette* invpal=0);
    ~IlvIntCell();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual void write(IL_STDPREF ostream&) const;
    virtual void draw(IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect=0) const;
    virtual const char* getLabel() const;
    virtual void        setLabel(const char* s);
    IlInt getValue() const          { return _value._long; }
    virtual void setValue(IlInt);
    virtual void setValue(IlFloat);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvFloatCell
: public IlvCell {
public:
    IlvFloatCell(IlvDisplay* ,IlFloat f, IlvPalette* pal=0,
		 IlvPalette* invpal=0);
    ~IlvFloatCell();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual void write(IL_STDPREF ostream&) const;
    virtual void draw(IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect=0) const;
    virtual const char* getLabel() const;
    virtual void        setLabel(const char* s);
    IlFloat getValue() const  { return _value._float; }
    void    setValue(IlFloat v);
    void    setValue(IlInt v);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvBitmapCell
: public IlvCell {
protected:
    IlvBitmap* _bitmap;
    IlBoolean _transparent;
public:
    IlvBitmapCell(IlvDisplay* ,IlvBitmap* bitmap,char* s,
		  IlBoolean trans=IlFalse,IlvPalette* pal=0,
		  IlvPalette* invpal=0);
    IlvBitmapCell(IlvDisplay* ,IlvBitmap* bitmap,
		  IlBoolean trans=IlFalse,IlvPalette* pal=0,
		  IlvPalette* invpal=0);
    virtual ~IlvBitmapCell();
    virtual const char* className() const;
    virtual void write(IL_STDPREF ostream&) const;
    // ____________________________________________________________
    void setBitmap(IlvBitmap* g);
    IlvBitmap* getBitmap()  const {return _bitmap;}
    virtual void getFittingSizes(IlvDim& width, IlvDim& height) const;
    virtual void draw(IlvCellManager*,
		      IlvPort* dst, IlvRect& bbox, IlvRect* rect=0) const;
};

#endif /* !__Ilv31_Cell_H */
