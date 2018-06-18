// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/rcview.h
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
// Declaration of the IlvRowColumnView class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Rcview_H
#define __Ilv1X_Rcview_H

#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

class IlvColumnView;
// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvRowColumnView
: public IlvContainer {
public:
    IlvRowColumnView(IlvCompositeAbstractView* father,
		     const IlvRect&            size,
		     IlvBoolean                column=IlvTrue,
		     IlvDim                    wmargin=10,
		     IlvDim                    hmargin=10,
		     IlvBoolean                isvisible=IlvTrue)
	: IlvContainer(father, size, IlvFalse,isvisible),
          _wmargin(wmargin), _hmargin(hmargin), _column(column),
	  _autoResize(IlvTrue){}
    IlvRowColumnView(IlvDisplay*    display,
		     IlvSystemView  father,
		     const IlvRect& size,
		     IlvBoolean     column  = IlvTrue,
		     IlvDim         wmargin = 10,
		     IlvDim         hmargin = 10,
		     IlvBoolean isvisible=IlvTrue)
	: IlvContainer(display,father, size, IlvFalse,isvisible),
	  _wmargin(wmargin), _hmargin(hmargin), _column(column),
	  _autoResize(IlvTrue) {}
    IlvRowColumnView(IlvDisplay*   display,
		     IlvSystemView w,
		     IlvBoolean    column  = IlvTrue,
		     IlvDim        wmargin = 10,
		     IlvDim        hmargin = 10)
	: IlvContainer(display,w,IlvFalse),
          _wmargin(wmargin), _hmargin(hmargin), _column(column),
	  _autoResize(IlvTrue) {}
    // ____________________________________________________________
    IlvBoolean getAutoResize() const { return _autoResize; }
    void setAutoResize(IlvBoolean value) { _autoResize = value; }
    virtual void addObject(IlvGraphic* obj, IlvBoolean redraw = IlvFalse);
    virtual void addObject(const char*, IlvGraphic* obj, IlvBoolean redraw = IlvFalse);
    virtual void insertObject(IlvGraphic* obj, IlvBoolean redraw = IlvFalse);
    virtual IlvBoolean removeObject(IlvGraphic* obj,
				    IlvBoolean redraw = IlvFalse);
    void align(IlvGraphic*, IlvPosition align = IlvLeft);
    void setVisible(IlvGraphic* obj,
		    IlvBoolean isvisible, IlvBoolean redraw = IlvFalse);
protected:
    IlvDim      _wmargin;
    IlvDim      _hmargin;
    IlvBoolean  _column;
    IlvBoolean  _autoResize;
    void columnVisible(IlvGraphic* obj,
		       IlvBoolean isvisible, IlvBoolean redraw = IlvTrue);
    void rowVisible(IlvGraphic* obj,
		    IlvBoolean isvisible, IlvBoolean redraw = IlvTrue);
};

#endif /* !__Ilv1X_Rcview_H */
