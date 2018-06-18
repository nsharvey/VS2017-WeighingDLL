// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/colorch.h
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
// Declaration of the IlvColorSelector class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Colorch_H
#define __Ilv_Gadgets_Colorch_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Slider_H)
#include <ilviews/gadgets/slider.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif
#if !defined(__Ilv_Graphics_Inter_H)
#include <ilviews/graphics/inter.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif

class IlvColorSelectorPage;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvColorSelector : public IlvDialog
{
public:

    IlvColorSelector(IlvDisplay* display,
		     IlvSystemView transientFor = 0);

    IlvColor*		getResult() const;

    IlvColor*		get(IlBoolean grab = IlFalse,
			    IlvCursor* cursor = 0);

    void		set(IlvColor* color);

 protected:
    IlvColor*			_originColor;
    IlvColorSelectorPage*	_diskPage;
    IlvColorSelectorPage*	_namedPage;
    IlvNotebook*		_notebook;
    IlInt			_pagesCount;
};

// --------------------------------------------------------------------------
// Page for Color dialog
// --------------------------------------------------------------------------
class IlvColorSelectorPage : public IlvGadgetContainer
{
public:
    IlvColorSelectorPage(IlvAbstractView*	view,
			 const char*		filename,
			 IlvColorSelector*	dialog,
			 IlvNotebook*		nb);

    virtual void	initialize(const char* filename);

    virtual void	setColor(IlvColor* color);
    virtual IlvColor*	getColor() const;
    virtual void	setOriginColor(IlvColor* color);

    void		propagateColor(IlvColor* color);
protected:
    IlvColorSelector*	_dialog;
    IlvNotebook*	_notebook;
    IlBoolean		_inPropagate;
};

#endif /* !__Ilv_Gadgets_Colorch_H */
