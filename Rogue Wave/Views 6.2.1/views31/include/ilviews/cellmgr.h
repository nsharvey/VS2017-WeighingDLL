// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/cellmgr.h
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
// Defintion of the IlvCellManager class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Cellmgr_H
#define __Ilv31_Cellmgr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Util_Accel_H)
#include <ilviews/util/accel.h>
#endif
#if !defined(__Ilv_Util_Drview_H)
#include <ilviews/util/drview.h>
#endif
#if !defined(__Ilv31_Cell_H)
#include <ilviews/cell.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

class IlvCellManagerInteractor;
class IlvCellManager;
class IlvCellManagerTable;

#if !defined(__Ilv31_Tablcell_H)
#include <ilviews/tablcell.h>
#endif

typedef IlvCell* IlvCellRow;
typedef void (* IlvCellApplyFunction)(IlvCellManager*, IlvCell*, IlAny);
typedef void (* IlvCellManagerAction)(IlvCellManager*, IlvView*,
				      IlvEvent&, IlAny);

typedef IlUShort IlvCellProperties;
#define IlvCellSelected    (1 << 0)
#define IlvCellReadOnly    (1 << 1)
#define IlvCellVisible     (1 << 2)
#define IlvCellAlignLeft   (1 << 3)
#define IlvCellAlignRight  (1 << 4)
#define IlvCellSelectable  (1 << 5)
#define IlvCellGrid        (1 << 6)
#define IlvCellMarked      (1 << 7)
#define IlvCellTransparent (1 << 8)

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellInteractor
{
public:
    IlvCellInteractor() {}
    virtual ~IlvCellInteractor();
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvCellManager*, IlvCell*,
				   IlvView*, IlvEvent &)=0;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerAccelerator : public IlvAccelerator
{
public:
    IlvCellManagerAccelerator(IlvCellManagerAction action,
			      IlvEventType         type,
			      IlUShort             data               = 0,
			      IlUShort             modifiers          = 0,
			      IlAny                user_arg           = 0,
			      IlUShort	           modifiersToIgnore  = 0)
    : IlvAccelerator(type, data, modifiers, user_arg, modifiersToIgnore),
      _cellManagerAction(action)
    {}

    virtual void         activate(IlvCellManager*, IlvView*, IlvEvent&) const;
    IlvCellManagerAction getAction() const { return _cellManagerAction; }
    void                 setAction(IlvCellManagerAction action, IlAny userArg)
        { _cellManagerAction = action; _userArg = userArg; }

    // Methods kept for compatibility. Use IlvAccelerator methods instead.
    IlvEventType         getType()      const { return type();      }
    IlUShort             getData()      const { return data();      }
    IlUShort             getModifiers() const { return modifiers(); }
    IlAny                getUserArg()   const { return userArg();   }

protected:
    IlvCellManagerAction _cellManagerAction;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellView
{
public:
    IlvCellView(IlvCellManager* c, IlvView* view,
	        IlUShort column = 0, IlUShort row = 0)
	: _cellmanager(c), _view(view),
          _column(column), _row(row), _interactor(0),_showGrid(IlTrue){}
    ~IlvCellView();
    // ____________________________________________________________
    IlvView*     view()   const  { return _view;   }
    IlUShort     column() const  { return _column; }
    IlUShort     row()    const  { return _row;    }
    void         move(IlUShort c, IlUShort r) { _column = c; _row = r; }
    IlvCellManager* cellManager() const { return _cellmanager; }
    void         setInteractor(IlvCellManagerInteractor* i) { _interactor = i;}
    IlvCellManagerInteractor* getInteractor() const { return _interactor; }
    void         attach();
    void         reset();
    void         sizes(IlUShort& fromcol, IlUShort& tocolr,
		       IlUShort& fromrow, IlUShort& torow) const;
    void         showGrid(IlBoolean value) { _showGrid = value; }
    IlBoolean   isGridOn() const  { return _showGrid; }
protected:
    IlvCellManager*           _cellmanager;
    IlvView*                  _view;
    IlUShort                  _column;
    IlUShort                  _row;
    IlvCellManagerInteractor* _interactor;
    IlBoolean                 _showGrid;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManager
{
public:
    // Public but not documented
    // ____________________________________________________________
    IlvCellView* getCellView(const IlvView*) const;
    IlvPalette*  getPalette() const { return _selectionPalette; }
    IlvPalette*  getGridPalette() const { return _gridPalette; }
    void         setPalette(IlvPalette* palette);
    void         setGridPalette(IlvPalette* palette);
    void         cellBBox(const IlvCellView*, const IlvCell*, IlvRect&) const;
    void         handleResize(IlvCellView*, IlvRect& rect);
    void         handleInput(IlvCellView*, IlvEvent& event);
    void         handleExpose(IlvCellView*, IlvRect* rect = 0);
    void         handleDestroy(IlvCellView*);
    void         draw(IlvCellView*,
		      IlBoolean erase = IlTrue,
		      IlvRect*   clip  = 0) const;
    void         select(IlUShort, IlUShort);
    void         verticalRight(IlUShort);
    void         verticalLeft(IlUShort);
    void         horizontalTop(IlUShort);
    void         horizontalBottom(IlUShort);
    IlBoolean   shortCut(IlvEvent& event, IlvCellView*);

    IlvCellProperties getCellProperties(IlvCell*) const;
    void         setCellProperties(IlvCell*, IlvCellProperties value);
    // Public and Documented ______________________________________
    IlvCellManager(IlvDisplay* display,
		   IlUShort   nbcol,
		   IlUShort   nbrow,
		   IlUShort   xgrid = 0,
		   IlUShort   ygrid = 0,
		   IlBoolean  useAccelerators = IlTrue);
    virtual ~IlvCellManager();
    // ____________________________________________________________
    virtual void setName(const char*);
    const char*  getName()  const {return _name;}
    void         cellBBox(const IlvView* view,
			  const IlvCell* cell,
			  IlvRect&       rect) const
    {
	IlvCellView* cellview = getCellView(view);
	if (cellview)
	    cellBBox(cellview, cell, rect);
    }
    IlBoolean    isSelected(const IlvCell*) const;
    IlBoolean    isMarked(const IlvCell*) const;
    void         setMarked(IlvCell*, IlBoolean value);
    IlBoolean    isVisible(const IlvCell*) const;
    void         setVisible(IlvCell*,  IlBoolean visible);
    IlBoolean    isReadOnly(const IlvCell*) const;
    void         setReadOnly(IlvCell*, IlBoolean readonly);
    IlvDirection getAlignment(const IlvCell*) const;
    void         setAlignment(IlvCell*, IlvDirection);
    IlBoolean    isSelectable(const IlvCell*) const;
    void         setSelectable(IlvCell*, IlBoolean selectable);
    IlBoolean    isTransparent(const IlvCell*) const;
    void         setTransparent(IlvCell*, IlBoolean transparent);
    IlBoolean    isGridOn(IlUShort column,IlUShort row) const;
    void         showGrid(IlUShort column, IlUShort row, IlBoolean onoff);
    // Cell Properties ____________________________________________
    IlUInt      getCardinal() const { return _columns*_rows; }
    IlvDim       columnPosition(IlUShort i) const { return _colsize[i]; }
    IlvDim       rowPosition(IlUShort i)    const { return _rowsize[i]; }
    void         setColumnPosition(IlUShort i, IlvDim s) { _colsize[i] = s; }
    void         setRowPosition(IlUShort i, IlvDim s)    { _rowsize[i] = s; }
    IlvDisplay*  getDisplay() const { return _display; }
    void         addView(IlvView*, IlUShort column = 0, IlUShort row = 0);
    void         removeView(IlvView* view);
    virtual void moveView(IlvView*   view,
			  IlUShort  column,
			  IlUShort  row,
			  IlBoolean redraw = IlTrue,
			  IlBoolean abortInteractor = IlTrue);
    void         ensureVisible(IlvCell*,
			       IlvView*,
			       IlBoolean redraw = IlTrue);
    void         setInteractor(IlvCellManagerInteractor* inter);
    void         removeInteractor(IlvView* view);
    IlvCellManagerInteractor* getInteractor(IlvView* view) const;
    virtual void draw(IlBoolean erase=IlTrue, IlvRect* clip = 0) const;
    virtual void draw(IlvView*   view,
		      IlBoolean erase = IlTrue,
		      IlvRect*   clip = 0) const;
    void         draw(IlvCell*) const;
    void         erase(IlvCell*, IlBoolean redraw = IlTrue) const;
    void         reDraw(IlvCell*) const;
    void         drawItem(IlvPort*       dst,
			  IlUShort      row,
			  IlUShort      column,
			  const IlvRect& itemrect,
			  const IlvRect& clip) const;
    virtual void draw(IlvPort*  dst,
		      IlUShort column,
		      IlUShort row,
		      IlvPos    xmargin = 0,
		      IlvPos    ymargin = 0,
		      IlvRect*  clip    = 0) const;
    virtual void draw(IlvPort*         dstPort,
		      IlUShort        firstColumn,
		      IlUShort        firstRow,
		      const IlvRect&   dstRect,
		      const IlvRegion* clip = 0) const;
    IlBoolean   add(IlvCell*   cell,
		    IlUShort  w,
		    IlUShort  h,
		    IlBoolean draw = IlTrue);
    IlBoolean   add(IlvCell*   cell,       //Add at the first valid position
		    IlBoolean draw = IlTrue);
    IlBoolean   add(const char* label,
		    IlUShort w,
		    IlUShort h,
		    IlBoolean draw = IlTrue,
		    IlUShort width = 1,
		    IlUShort height = 1);
    IlBoolean   add(const char* label,    // Add at the first valid position
		    IlBoolean  draw = IlTrue,
		    IlUShort   width = 1,
		    IlUShort   height = 1);
    virtual void remove(IlvCell*,
			IlBoolean destroyIt = IlTrue,
			IlBoolean draw      = IlTrue);
    void         showGrid(IlvView* view, IlBoolean onoff = IlTrue)
	{ getCellView(view)->showGrid(onoff); }
    IlBoolean   isGridOn(IlvView* view) const
	{ return getCellView(view)->isGridOn(); }
    void         setSelected(IlvCell*,
			     IlBoolean selected = IlTrue,
			     IlBoolean redraw   = IlTrue);
    void         makeSelected(IlvCell*, IlBoolean redraw = IlFalse);
    void         makeUnSelected(IlvCell*, IlBoolean redraw = IlFalse);
    IlvCell*     getCell(IlUShort col,IlUShort row) const;
    IlvCell*     getCell(IlUInt position) const;
    IlBoolean    pointToPosition(const IlvPoint& p,
				 IlUShort&      col,
				 IlUShort&      row) const;
    IlBoolean    pointToPosition(IlvView*,
				 const IlvPoint&,
				 IlUShort&,
				 IlUShort&) const;
    IlUShort     getColumns() const { return _columns; }
    IlUShort     getRows()    const { return _rows;    }
    IlUShort     getSpacing() const { return _spacing; }
    void         setSpacing(IlUShort spacing) { _spacing = spacing; }
    void         deSelectAll(IlBoolean redraw = IlTrue);
    IlBoolean   shortCut(IlvEvent& event, IlvView* view)
	{ return shortCut(event, getCellView(view)); }
    void         setRowSelected(IlUShort  irow,
				IlBoolean selected = IlTrue,
				IlBoolean redraw   = IlTrue);
    void         setColumnSelected(IlUShort  icolumn,
				   IlBoolean selected = IlTrue,
				   IlBoolean redraw   = IlTrue);
    virtual void resizeColumn(IlUShort  column,
			      IlvDim     newsize,
			      IlBoolean redraw = IlTrue);
    virtual void resizeRow(IlUShort  row,
			   IlvDim     newsize,
			   IlBoolean redraw = IlTrue);
    void         select(IlUShort,
			IlUShort,
			IlUShort,
			IlUShort,
			IlBoolean redraw = IlTrue);
    IlvCell*     nextRight(IlvCell*) const;
    IlvCell*     previousLeft(IlvCell*) const;
    IlvCell*     nextBottom(IlvCell*) const;
    IlvCell*     previousTop(IlvCell*) const;
    void         deleteSelections(IlBoolean redraw = IlTrue);
    void         applyToSelections(IlvCellApplyFunction, IlAny arg = 0);
    // Accelerators _______________________________________________
    void         addAccelerator(IlvCellManagerAction action,
				IlvEventType         evtype,
				IlUShort             data              = 0,
				IlUShort             modifiers         = 0,
				IlAny                userarg           = 0,
				IlUShort             modifiersToIgnore = 0);
    IlBoolean   getAccelerator(IlvCellManagerAction* action,
				IlAny*                userArg,
				IlvEventType          evtype,
				IlUShort              data      = 0,
				IlUShort              modifiers = 0) const;
    void         removeAccelerator(IlvEventType evtype,
				   IlUShort     data      = 0,
				   IlUShort     modifiers = 0);
    void         addAccelerator(IlvCellManagerAccelerator*);
    void         removeAccelerator(IlvCellManagerAccelerator*);
    IlvCellManagerAccelerator* getAccelerator(IlvEventType evtype ,
					      IlUShort     data = 0,
					      IlUShort     modifiers = 0)const;
    IlBoolean   viewPosition(IlvView* view,IlUShort& ,IlUShort& ) const;
    IlBoolean   viewSizes(IlvView*   view,
			  IlUShort& fromcol,
			  IlUShort& tocol,
			  IlUShort& fromrow,
			  IlUShort& torow) const;
    void         setCellInteractor(IlvCell*, IlvCellInteractor* interactor);
    IlvCellInteractor*  getCellInteractor(const IlvCell*) const;
    void         swapCells(IlvCell*, IlvCell*, IlBoolean redraw = IlTrue);
    void         swapRows(IlUShort  row1,
			  IlUShort  row2,
			  IlBoolean redraw = IlTrue);
    void         swapColumns(IlUShort  col1,
			     IlUShort  col2,
			     IlBoolean redraw = IlTrue);
    virtual void insertColumn(IlUShort  pos     = 0,
			      IlBoolean redraw  = IlTrue,
			      IlUShort  howMany = 1);
    virtual void insertRow(IlUShort  pos     = 0,
			   IlBoolean redraw  = IlTrue,
			   IlUShort  howMany = 1);
    virtual void removeColumn(IlUShort  pos,
			      IlBoolean destroyIt = IlTrue,
			      IlBoolean redraw    = IlTrue,
			      IlUShort  howMany   = 1);
    virtual void removeRow(IlUShort  pos,
			   IlBoolean destroyIt = IlTrue,
			   IlBoolean redraw    = IlTrue,
			   IlUShort  howMany   = 1);
    virtual void write(IL_STDPREF ostream&) const;
    virtual void read(IL_STDPREF istream&);
    virtual void read(const char*);
    virtual void deleteAll(IlBoolean redraw = IlTrue);
    void         abortInteractors();

    friend class IlvCellManagerTable;
protected:
    IlvDisplay*         _display;
    IlList             _accelerators;
    IlList             _views;
    IlUShort           _rows;    // Number of rows
    IlUShort           _columns; // Number of columns
    IlUShort           _xgrid;
    IlUShort           _ygrid;
    IlUShort           _spacing;
    IlUShort           _allocatedColumns;
    IlvCellRow**        _cells;
    IlvCellProperties** _cellsProperties;
    IlvDim*             _rowsize;
    IlvDim*             _colsize;
    IlBoolean          _stillSameRowSize;
    IlBoolean          _stillSameColumnSize;
    IlvPalette*         _selectionPalette; // Palette for selection
    IlvPalette*         _gridPalette;      // Palette for selection
    IlHashTable        _interactors;
    char*               _name;
    IlBoolean validPosition(IlUShort irow, IlUShort icol) const;
    void fastDrawColumn(IlUShort row, IlInt spacing) const;
    void fastDrawRow(IlUShort col, IlInt spacing) const;
    void installAccelerators();
    IlvCellManagerTable*       _table;
};

#endif /* !__Ilv31_Cellmgr_H */
