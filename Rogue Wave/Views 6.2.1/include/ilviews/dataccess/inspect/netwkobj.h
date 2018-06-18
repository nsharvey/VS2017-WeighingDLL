// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/netwkobj.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the miscellaneous classes used by the IliSQLNetwork class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Netwkobj_H
#define __Ili_Netwkobj_H

#ifndef __Ilv_Grapher_Grapher_H
#  include <ilviews/grapher/grapher.h>
#endif

#ifndef __Ilv_Base_Gadget_H
#  include <ilviews/base/gadget.h>
#endif

#ifndef __Ilv_Grapher_Links_H
#  include <ilviews/grapher/links.h>
#endif

#ifndef __Ilv_Gadgets_Scrollb_H
#  include <ilviews/gadgets/scrollb.h>
#endif

#ifndef __Ilv_Gadgraph_Rectscgr_H
#  include <ilviews/gadgraph/rectscgr.h>
#endif

#ifndef __Ili_Module_H
#  include <ilviews/dataccess/module.h>
#endif

#ifndef __Ili_Schema_H
#  include <ilviews/dataccess/schema.h>
#endif

#ifndef __Ili_Tblref_H
#  include <ilviews/dataccess/tblref.h>
#endif

class ILV_DBSSQL_EXPORTED IliSQLNetwork;
class IliTableGraphicHook;
class IliTableGraphic;
class IliColumnGraphic;
class IliTableLinkImage;

// --------------------------------------------------------------------------
// IliTableGraphicHook
// --------------------------------------------------------------------------
class IliTableGraphicHook
  : public IliTableHook {
public:
  IliTableGraphicHook () {}
  virtual void columnInserted (IlInt colno);
  virtual void columnChanged (IlInt colno);
  virtual void columnToBeDeleted (IlInt colno);
  virtual void columnMoved (IlInt src, IlInt dest);

  void setTableGraphic (IliTableGraphic* tblg) { _tblg = tblg; }

  IliTableGraphic* _tblg;
};

// --------------------------------------------------------------------------
// IliTableGraphic
// --------------------------------------------------------------------------
class IliTableGraphic : public IlvGadget
{
public:
  IliTableGraphic (IliSQLNetwork* net,IlInt token,IliSchema* schema,
		     const char* name,const IlvRect& bbox,
		     IlvPalette* palette = 0);
  ~IliTableGraphic ();

  IliSQLNetwork* getNetwork () const { return _network; }
  IlvGrapher* getGrapher () const;
  IliSchema* getSchema () const { return _schema; }
  IlInt getToken () const { return _token; }

  IlBoolean isDirty () const { return _dirty; }

  const char* getName () const { return _name; }
  void setName (const char* nm) { _name = nm; }

  IlInt getColumnsCount () const;
  IliColumnGraphic* getColumn (IlInt) const;
  IliColumnGraphic* findColumn (const char* nm) const;
  IliColumnGraphic* findColumn(const IliAttributePath& path) const;

  IliAttributePath getFocusPath() const { return _focusPath; }
  void setFocusPath(IliAttributePath path);

  IlBoolean covers(const IliAttributePath& path,
		    const IliColumnGraphic* column) const;
  IlBoolean isInFocusPath(const IliColumnGraphic* column) const;

  class Iterator {
  public:
    Iterator(const IlvList& columns);
    void reset(const IlvList& columns);

    IlBoolean atEnd() const;
    IliColumnGraphic* next();

    void seeAll() { _all = IlTrue; }

  private:
    IlvArray _array;
    IlBoolean _all;
  };

  Iterator getRecursiveIterator() const;

  void reformat ();
  void build ();
  void buildColumn(IliColumnGraphic*);

  void insertColumn (IlvList& columns,IlInt colno,const char* name,
		     const IliDatatype* type,IlBoolean isKey,
		     IlInt indent = 0,IliColumnGraphic* parent = 0);
  void removeColumn (IlvList& columns,IlInt colno);
  void moveColumn (IlvList& columns,IlInt src,IlInt dest);

  const char* getColumnName (IlInt colno) const;
  void setColumnName (IlInt colno, const char*);

  IlBoolean isColumnPartOfKey (IlInt colno) const;
  void setColumnPartOfKey (IlInt colno, IlBoolean);

  const IliDatatype* getColumnType(IlInt colno) const;
  void setColumnType(IlInt colno, const IliDatatype*);

  void scrollBarValueChanged ();
  void removeAllColumns () {
    removeAllColumns(_columns);
  }
  void removeAllColumns (IlvList& columns);

  IlBoolean isStarShown() const { return _isStarShown; }
  void showStar(IlBoolean b) { _isStarShown = b; }

  IlBoolean isUpdatable() const { return _isUpdatable; }
  void setUpdatable(IlBoolean b);

  IlvScrollBar* getScrollBar () const { return _sb; }

  void moved ();
  void doubleClicked ();
  void newSelection();
  void dropAllColumns(IlvPoint& lastPt);

  IlBoolean isDropAllColumnsRect(const IlvPoint& pt,const IlvTransformer* t);

  void drawStar(IlvPort* dst,const IlvTransformer* t,
		const IlvRegion* clip,IlBoolean inverted) const;
  void invertStar(IlvPort* dst,const IlvTransformer* t = 0,
		  const IlvRegion* clip = 0);

  // -- virtual
  DeclareTypeInfo();
  virtual void applyTransform (const IlvTransformer* t);
  virtual IlBoolean contains(const IlvPoint& p, const IlvPoint& tp,
			      const IlvTransformer* t = 0) const;
  virtual void draw(IlvPort*, const IlvTransformer* t = 0,
		    const IlvRegion* = 0) const;


  void computeRects (IlvRect& labelBBox,IlvRect& symBBox,
		     const IlvTransformer* t) const;
  virtual void setOverwrite(IlBoolean);
  virtual void setMode(IlvDrawMode);
protected:
  IliTableGraphicHook _hook;
  IliSQLNetwork* _network;
  IliString _name;
  IliSchema* _schema;
  IlvList _columns;
  IlvScrollBar* _sb;
  IlvRect _columnsBBox;
  IlvRect _nameBBox;
  IlInt _symbolDim;
  IlInt _firstColumn;
  IlInt _totalCount;
  IlInt _token;
  IlBoolean _dirty;
  IlBoolean _isStarInverted;
  IlBoolean _isStarShown;
  IlBoolean _isUpdatable;
  IliAttributePath _focusPath;

  friend class IliColumnGraphic;
  friend class IliTableGraphicHook;
};

// --------------------------------------------------------------------------
// IliColumnGraphic
// --------------------------------------------------------------------------
class IliColumnGraphic
  : public IlvGadget
{
public:
  IliColumnGraphic (IliTableGraphic*,const char* name,const IliDatatype* type,
		    IlBoolean isKey,IlInt position);
  ~IliColumnGraphic ();

  IliSQLNetwork* getNetwork () const { return _table->getNetwork(); }
  IlvGrapher* getGrapher () const { return _table->getGrapher(); }

  IliTableGraphic* getTable () const { return _table; }

  const char* getName () const { return _name; }
  IlBoolean isNameNull () const { return _name.length() == 0; }
  void setName (const char* nm) { _name = nm; }

  void getFullName(IliString& name) const;
  IliAttributePath getPath() const;

  const IliDatatype* getType() const { return _type; }
  void setType(const IliDatatype* type);

  IliColumnGraphic* getParent() const { return _parent; }
  void setParent(IliColumnGraphic* parent) { _parent = parent; }

  IlInt getIndent() const { return _indent; }
  void setIndent(IlInt i) { _indent = i; }

  IlInt getColumnsCount () const;
  IliColumnGraphic* getColumn (IlInt) const;
  IliColumnGraphic* findColumn (const char* nm) const;

  IlBoolean isStructured() const;
  IlBoolean isOpen() const;
  void open();
  void close();

  IlInt getPosition () const { return _position; }
  void setPosition (IlInt p) { _position = p; }

  IlBoolean isKey () const { return _isKey; }
  void setKey (IlBoolean k);

  void hide ();
  void show ();

  void dropOnColumn (IliColumnGraphic* target);
  void dropOnVoid (const IlvPoint&);

  IlInt getLeftMargin() const;
  IlInt getMarkWidth() const;

  void computeRects(IlvRect& markerRect,IlvRect& textRect,
		    const IlvTransformer* t = 0) const;
  void drawMark(IlvPort* dst,const IlvTransformer* t = 0,
		const IlvRegion* clip = 0) const;

  // -- virtual
  DeclareTypeInfo();
  virtual void draw (IlvPort*,const IlvTransformer* t = 0,
		     const IlvRegion* = 0) const;
  void invert (IlBoolean);

  const IlvList& getColumns() const { return _columns; }
  IlvList& getColumns() { return _columns; }

protected:
  IliTableGraphic* _table;
  IliString _name;
  IlBoolean _isKey;
  IlInt _position;
  IlBoolean _inverted;
  const IliDatatype* _type;
  IlvList _columns;
  IlBoolean _open;
  IlInt _indent;
  IliColumnGraphic* _parent;

  friend class IliTableGraphic;
};

// --------------------------------------------------------------------------
// IliDoubleLinkImage
// --------------------------------------------------------------------------
class IliDoubleLinkImage
  : public IlvLinkImage {
public:
  IliDoubleLinkImage (IlvDisplay* display,IlBoolean oriented,IlvGraphic* from,
		      IlvGraphic* to,IlvPalette* palette = 0)
    : IlvLinkImage(display, oriented, from, to, palette)
  {
    _index = 0;
    _markFrom = IlFalse;
    _markTo = IlFalse;
  }

  IlInt getIndex () const { return _index; }
  void setIndex (IlInt idx) { _index = idx; }

  IlBoolean isFromMarked() const { return _markFrom; }
  void markFrom(IlBoolean f) { _markFrom = f; }

  IlBoolean isToMarked() const { return _markTo; }
  void markTo(IlBoolean f) { _markTo = f; }

  void drawMarker(IlvPort* dst,const IlvPoint& pt1,const IlvPoint& pt2) const;

  IlvPoint* getLinkPoints (IlUInt& nPoints, const IlvTransformer* t) const;
  virtual IlBoolean contains (const IlvPoint& p, const IlvPoint&,
			       const IlvTransformer* t = 0) const;
  virtual void draw (IlvPort* dst, const IlvTransformer* t = 0,
		     const IlvRegion* clip = 0) const;
  virtual void boundingBox (IlvRect&, const IlvTransformer* t = 0) const;
  DeclareTypeInfo();

protected:
  IlInt _index;
  IlBoolean _markFrom;
  IlBoolean _markTo;

  void computeImage (IlvPoint* points,IlvPoint* apoints,
		     const IlvTransformer* t) const;
  virtual IlBoolean isDirect (const IlvTransformer* t = 0) const;
  virtual IlBoolean isNotShown (const IlvTransformer* t = 0) const;

  virtual void nodeBBox (IlvGraphic* g, IlvRect&, const IlvTransformer*) const;
};

// --------------------------------------------------------------------------
// IliLinkSelection
// --------------------------------------------------------------------------
class IliLinkSelection
  : public IlvReshapeSelection {
public:
  IliLinkSelection (IlvDisplay* display,IlvLinkImage* link,
		    IlvDim size = IlvDefaultSelectionSize,
		    IlvPalette* palette = 0);

  virtual IlvDirection direction(const IlvPoint& p,
				 const IlvTransformer* t = 0) const;
  virtual void draw(IlvPort* dst, const IlvTransformer* t,
		    const IlvRegion* clip = 0) const;
  virtual void computeRegion(IlvRegion& r,const IlvTransformer* t = 0) const;
  DeclareTypeInfo();
  DeclareIOConstructors(IliLinkSelection);
};

// --------------------------------------------------------------------------
// IliTableLinkImage
// --------------------------------------------------------------------------
class IliTableLinkImage : public IliDoubleLinkImage 
{
public:
  IliTableLinkImage (IliSQLNetwork* net,IlInt token,IlvGraphic* from, 
		     IlvGraphic* to,IlInt hideCount,IlvPalette* palette = 0);
  ~IliTableLinkImage ();

  IliSQLNetwork* getNetwork () const { return _network; }
  IlvGrapher* getGrapher () const;
  IlInt getToken () const { return _token; }

  IlInt getHideCount () const { return _hideCount; }
  void setHideCount (IlInt);
  void incrHideCount ();
  void decrHideCount ();

  void doubleClicked ();
  void newSelection();

  DeclareTypeInfo();
protected:
  IliSQLNetwork* _network;
  IlInt _hideCount;
  IlInt _token;

  void nodeBBox (IlvGraphic* g,IlvRect& bbox,const IlvTransformer* t) const;
};

// --

IliModuleDECL_exp(ILV_DBSSQL_EXPORTED,IliNetwkobj);

#endif
