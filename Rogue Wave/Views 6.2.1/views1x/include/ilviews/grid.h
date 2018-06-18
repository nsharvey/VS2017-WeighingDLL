// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/grid.h
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
// Declaration of the IlvGridObj class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Grid_H
#define __Ilv1X_Grid_H

#if !defined(__Ilv_Graphics_Relfrect_H)
#include <ilviews/graphics/relfrect.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

class  IlvView;
class  IlvGridObj;

typedef void (* IlvGridObjectCallback)(IlvView*, IlvGridObj*, IlvGraphic*,
				       IlvBoolean, IlvAny);
typedef enum IlvGridSelectionType {
    IlvGridExclusiveSelection,
    IlvGridMultipleSelection,
    IlvGridNoSelection
} _IlvGridSelectionType;


// --------------------------------------------------------------------------
// The GridElement class stores information for Grid
// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvGridElement
{
    friend class IlvGridObj;
public:
    IlvGridElement(IlvUShort             column,
		   IlvUShort             row,
		   IlvGridObjectCallback callback = 0,
		   IlvAny                userarg  = 0,
		   IlvBoolean            readonly = IlvFalse,
		   IlvDim                width    = 1,
		   IlvDim                height   = 1)
    : 
      _callback(callback),
      _readonly(readonly),
      _selected(IlvFalse),
      _userarg(userarg),
      _marked(IlvFalse),
      _column(column),
      _row(row),
      _width(width),
      _height(height){}
    IlvGridElement()
	{ reset(); }
    // ____________________________________________________________
    IlvBoolean readOnly() const              { return _readonly;     }
    void       readOnly(IlvBoolean readonly) { _readonly = readonly; }
    IlvAny userArg() const         { return _userarg;    }
    void   userArg(IlvAny userarg) { _userarg = userarg; }
    IlvBoolean selected() const              { return _selected;   }
    void       selected(IlvBoolean selected) { _selected=selected; }
    IlvGridObjectCallback callback() const        { return _callback;     }
    void callback(IlvGridObjectCallback callback) { _callback = callback; }
    IlvBoolean marked() const            { return _marked;  }
    void       marked(IlvBoolean marked) { _marked = marked; }
    IlvUShort column() const { return _column; }
    IlvUShort row()    const { return _row;    }
    IlvDim width()  const { return _width;  }
    IlvDim height() const { return _height; }
protected:
    IlvGridObjectCallback _callback;
    IlvBoolean            _readonly;
    IlvBoolean            _selected;
    IlvAny                _userarg;
    IlvBoolean            _marked;
    IlvUShort             _column;
    IlvUShort             _row;
    IlvDim                _width;
    IlvDim                _height;
    void reset() {
	_callback = 0;
	_readonly = IlvFalse;
	_selected = IlvFalse;
	_userarg  = 0;
	_marked   = IlvFalse;
	_width    = _height = 1;
    }
};

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvGridObj
: public IlvReliefRectangle {
public:
    IlvGridObj(IlvDisplay*          display,
	       const IlvRect&       rect,
	       IlvUShort            nbcol,
	       IlvUShort            nbrow,
	       IlvGridSelectionType sel     = IlvGridMultipleSelection,
	       IlvPalette*          palette = 0);
    ~IlvGridObj();
    // ____________________________________________________________
    static IlvSymbol*  _objectGridElement;
    void setSelectionType(IlvGridSelectionType selectiontype)
	{ _selectiontype = selectiontype; }
    IlvGridSelectionType getSelectionType() const
	{ return _selectiontype;          }
    void     setSpacing(IlvUShort spacing) { _spacing = spacing; }
    IlvUShort getSpacing()           const { return _spacing;    }
    void  useShadow(IlvBoolean use)  { _reliefshadow = use;  }
    void deSelect(IlvPort* dst = 0, const IlvTransformer* t = 0);
    void resizeColumn(IlvUShort column, IlvDim newsize);
    void resizeRow(IlvUShort row, IlvDim newsize);
    void add(IlvUShort posx, IlvUShort posy,
	     IlvGraphic* obj,
	     IlvBoolean readonly = IlvFalse,
	     IlvGridObjectCallback c = 0,
	     IlvAny u = 0,
	     IlvDim w = 1, IlvDim h = 1);
    void add(IlvGraphic* obj,    //Add at first valid position
	     IlvBoolean readonly = IlvFalse,
	     IlvGridObjectCallback c = 0,
	     IlvAny u = 0,
	     IlvDim w = 1, IlvDim h = 1);
    void remove(IlvGraphic* obj,IlvBoolean destroyIt=IlvTrue);
    IlvBoolean objectBBox(const IlvGraphic* obj, IlvRect& bbox) const;
    IlvBoolean objectPosition(const IlvGraphic* obj,
			      IlvUShort& col, IlvUShort& row,
			      IlvDim& width,  IlvDim& height) const;
    void makeSelected(IlvGraphic* obj);
    void makeUnSelected(IlvGraphic* obj);
    void swapSelection(IlvGraphic* obj);
    void showGrid(IlvBoolean onoff = IlvTrue) { _showgrid = onoff; }
    IlvUShort columns() const { return _columns; }
    IlvUShort rows()    const { return _rows;    }
    //---------    Graphic Part --------------------------------
    IlvDim getCardinal() const;
    virtual void apply(IlvApplyObject, IlvAny);
    virtual void draw(IlvPort* dst, const IlvTransformer* t =0,
		      const IlvRegion* clip = 0) const;
    virtual void applyTransform(const IlvTransformer* t);
    virtual void invert(IlvBoolean);
    virtual void setMode(IlvDrawMode);
    DeclareTypeInfo();

    IlvGraphic* getObject(IlvUShort posx, IlvUShort posy) const;
    void drawObj(const IlvGraphic*, IlvPort* dst, const IlvTransformer* t = 0,
		 const IlvRegion* rect = 0) const;
    void eraseObj(const IlvGraphic*, IlvPort* dst,
		  const IlvTransformer* t = 0) const;
    void reDrawObj(const IlvGraphic* obj, IlvPort* dst,
		   const IlvTransformer* t = 0, const IlvRegion* clip = 0)
	{ eraseObj(obj, dst, t); drawObj(obj, dst, t, clip); }
    IlvBoolean pointToPosition(const IlvPoint& p,
			       IlvUShort& icol, IlvUShort& irow) const;
    IlvGraphic* getObject(IlvDim pos) const
	{ return (pos < (IlvDim)(_rows*_columns)) ? _objects[pos] : 0; }
    IlvGraphic* getSelection() const
	{ return (_selections->length()) ?
	  (IlvGraphic*)_selections->getValue(0) : 0; }
    IlvList* getSelections() const { return _selections; }
    IlvUInt numberOfSelections() const { return _selections->length(); }
    void callCallback(IlvGraphic* obj, IlvView* view);
    IlvBoolean isSelected(const IlvGraphic* obj) const;
    IlvBoolean isReadOnly(const IlvGraphic* obj) const;
    IlvGridObjectCallback getCallback(const IlvGraphic* obj) const;
    IlvAny                getObjectArg(const IlvGraphic* obj) const;
    IlvInt getPosition(const IlvGraphic*) const;
    void setCallback(IlvGraphic*,
		     IlvGridObjectCallback c = 0, IlvAny arg = 0);
    void setReadOnly(IlvGraphic*,
		     IlvBoolean value = IlvTrue);
 protected:
    IlvGridSelectionType _selectiontype;
    IlvGraphic**         _objects;
    IlvUShort            _columns;             // Number of columns
    IlvUShort            _rows;                // Number of rows
    IlvDim*              _colsize;
    IlvDim*              _rowsize;
    IlvBoolean           _showgrid;
    IlvBoolean           _sameWidth;
    IlvBoolean           _sameHeight;
    IlvUShort            _spacing;           // Spacing between grid and object
    IlvBoolean           _reliefshadow;      // Show relief effect or not
    IlvList*             _selections;

    void reshape(IlvGraphic* obj);
    void computePalettes();
    IlvBoolean checkPosition(IlvUShort, IlvUShort) const;
    void drawGrid(IlvPort* dst,
		  IlvUShort fromx, IlvUShort tox,
		  IlvUShort fromy, IlvUShort toy,
		  const IlvTransformer* t    = 0,
		  const IlvRegion*      clip = 0) const;
};

ILV1XVWSMODULEINIT(grid);

#endif /* !__Ilv1X_Grid_H */
