// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/cellint.h
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
// Definition of the IlvCellManagerInteractor class and some predefined
// subtypes
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Cellint_H
#define __Ilv31_Cellint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Cellmgr_H)
#include <ilviews/cellmgr.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractor
{
public:
    IlvCellManagerInteractor(IlvCellManager* cm, IlvView* view)
    {
	_cellview   = cm->getCellView(view);
    }
    virtual ~IlvCellManagerInteractor();
    // ____________________________________________________________
    IlvCellManager* getCellManager()   const {
	return _cellview->cellManager();
    }
    IlvView*        getView() const     { return _cellview->view(); }
    IlvCellView*    getCellView() const { return _cellview;}

    virtual void handleEvent(IlvEvent&) =0;
    virtual void handleExpose(IlvRegion* clip = 0);
    virtual void drawGhost();
    virtual void abort();
    virtual void init();
    void ensureVisible(IlvPos, IlvPos);
    void ensureVisible(const IlvRect&);
protected:
    IlvCellView*  _cellview;
    IlvCellManagerInteractor() {}
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorSelect
: public IlvCellManagerInteractor {
public:
    IlvCellManagerInteractorSelect(IlvCellManager* cm, IlvView* view)
	: IlvCellManagerInteractor(cm, view)
	{ _xor_rectangle.w(0); }
    // ____________________________________________________________
    virtual void handleExpose(IlvRegion* clip = 0);
    virtual void drawGhost();
    virtual void handleEvent(IlvEvent&);
    virtual void doIt(const IlvRect&);
    virtual void abort();
protected:
    IlvRect _xor_rectangle;
    IlvPos  _firstx;
    IlvPos  _firsty;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorMakeCell
: public IlvCellManagerInteractor{
public:
    IlvCellManagerInteractorMakeCell(IlvCellManager* cm,IlvView* view,
				     IlUShort w=1,IlUShort h=1)
	: IlvCellManagerInteractor(cm,view),_width(w),_height(h) {}
    // ____________________________________________________________
    void setWidth(IlUShort w)  {_width=w;}
    void setHeight(IlUShort h) {_height=h;}
    IlUShort getWidth() const {return _width;}
    IlUShort getHeight() const {return _height;}
    void handleEvent(IlvEvent& event);
    virtual void doIt(IlUShort, IlUShort);
protected:
    IlUShort _width;
    IlUShort _height;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorMakeReliefCell
: public IlvCellManagerInteractorMakeCell {
public:
    IlvCellManagerInteractorMakeReliefCell(IlvCellManager* cm, IlvView* view,
					   IlUShort w=1,IlUShort h=1)
	: IlvCellManagerInteractorMakeCell(cm, view,w,h) {}
    // ____________________________________________________________
    virtual void doIt(IlUShort, IlUShort);
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorMove
: public IlvCellManagerInteractor {
public:
    IlvCellManagerInteractorMove(IlvCellManager* cm, IlvView* view)
	: IlvCellManagerInteractor(cm,view) {}
    // ____________________________________________________________
    void handleEvent(IlvEvent& event);
    virtual void drawGhost();
    virtual void doIt(IlvPos,IlvPos);
};


// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorSwapCell
: public IlvCellManagerInteractor {
public:
    IlvCellManagerInteractorSwapCell(IlvCellManager* cm,IlvView* view)
	: IlvCellManagerInteractor(cm,view)
	{ _from.move(0,0); _to.move(0,0); }
    // ____________________________________________________________
    virtual void drawGhost();
    virtual void handleExpose(IlvRegion* region =0);
    virtual void handleEvent(IlvEvent&);
    virtual void doIt(IlUShort , IlUShort ,IlUShort , IlUShort );
protected:
    IlvPoint _from;
    IlvPoint _to;
    virtual void validate();
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorSwapColumn
: public IlvCellManagerInteractorSwapCell {
public:
    IlvCellManagerInteractorSwapColumn(IlvCellManager* cm,IlvView* view)
	: IlvCellManagerInteractorSwapCell(cm, view) {}
    // ____________________________________________________________
    virtual void doIt(IlUShort , IlUShort ,IlUShort , IlUShort );
protected:
    virtual void validate();
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorSwapRow
: public IlvCellManagerInteractorSwapCell {
public:
    IlvCellManagerInteractorSwapRow(IlvCellManager* cm,IlvView* view)
	: IlvCellManagerInteractorSwapCell(cm, view) {}
    // ____________________________________________________________
    virtual void doIt(IlUShort, IlUShort, IlUShort, IlUShort );
protected:
    virtual void validate();
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerInteractorResize
: public IlvCellManagerInteractor {
public:
    IlvCellManagerInteractorResize(IlvCellManager* cm, IlvView* view)
	: IlvCellManagerInteractor(cm, view), _which(0) {}
    // ____________________________________________________________
    virtual void handleExpose(IlvRegion* clip = 0);
    virtual void drawGhost();
    virtual void handleEvent(IlvEvent&);
    virtual void resizeColumn(IlUShort column, IlvDim newsize);
    virtual void resizeRow(IlUShort row, IlvDim newsize);
protected:
    IlUInt   _which;
    IlUShort _rowColumn;
    IlvPoint  _current;
    void check();
};

#endif /* !__Ilv31_Cellint_H */
