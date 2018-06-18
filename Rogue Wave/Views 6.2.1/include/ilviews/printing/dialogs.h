// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/dialogs.h
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
// Definition of various dialog classes.
// --------------------------------------------------------------------------

#ifndef __Ilv_Printing_Dialogs_H
#define __Ilv_Printing_Dialogs_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Printing_Macros_H)
#include <ilviews/printing/macros.h>
#endif
#if !defined(__Ilv_Printing_DialogMacros_H)
#include <ilviews/printing/dlgmacros.h>
#endif
#if !defined(__Ilv_Printing_Printer_H)
#include <ilviews/printing/printer.h>
#endif
#if !defined(__Ilv_Printing_PaperFormat_H)
#include <ilviews/printing/pformat.h>
#endif
#if !defined(__Ilv_Printing_Units_H)
#include <ilviews/printing/units.h>
#endif
#if !defined(__Il_String_H)
#include <ilog/string.h>
#endif
#include <ilviews/graphics/selector.h>
#include <ilviews/graphics/icon.h>

#if !defined(__Ilv_Gadgets_Frame_H)
#include <ilviews/gadgets/frame.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif
#if !defined(__Ilv_Gadgets_Scombo_H)
#include <ilviews/gadgets/scombo.h>
#endif
#if !defined(__Ilv_Gadgets_Fbrowser_H)
#include <ilviews/gadgets/fbrowser.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Spinbox_H)
#include <ilviews/gadgets/spinbox.h>
#endif
#if !defined(__Ilv_Graphics_Shadrect_H)
#include <ilviews/graphics/shadrect.h>
#endif

class ILVPRTDLGEXPORTED IlvPostScriptPrinterDialog : public IlvDialog
{
 public:
    IlvPostScriptPrinterDialog(IlvDisplay* display, 
			       IlvSystemView transientFor = 0);
    virtual ~IlvPostScriptPrinterDialog();

    void		setPaperFormat(IlString const& format,
				       IlBoolean redraw = IlFalse);
    inline
    IlvPaperFormat const& getPaperFormat() const { return *_paperFormat; }
    void		setOrientation(IlvPrinter::Orientation orientation, 
				       IlBoolean redraw = IlFalse);
    inline
    IlvPrinter::Orientation getOrientation() const
			{
			    return _orientation;
			}
    void		setColorMode(IlBoolean useColor,
				     IlBoolean redraw = IlFalse);
    inline IlBoolean	isColorModeOn() const { return _color; }
    void		setCollate(IlBoolean collate,
				   IlBoolean redraw = IlFalse);
    IlBoolean		isCollateOn() const; 
    void		setCopiesNumber(IlUInt copies,
					IlBoolean redraw = IlFalse);
    inline IlUInt	getCopiesNumber() const { return _numcopies; }
    void		setFilename(IlString const& name,
				    IlBoolean redraw = IlFalse);
    inline IlString	getFilename() const { return _filename; }
    void		updateFormatInfo(IlBoolean redraw = IlFalse);
    void		setUnit(IlvPrintUnit& unit,
				IlBoolean redraw = IlFalse);
    void		setMargins(IlvDim left,
				   IlvDim right, 
				   IlvDim top,
				   IlvDim bottom);
    void		getMargins(IlvDim& left,
				   IlvDim& right, 
				   IlvDim& top,
				   IlvDim& bottom) const;
    IlBoolean		get(IlBoolean grab = IlFalse, IlvCursor* cursor = 0);
    void		selectMargins();

protected:
    void		initPaperFormats();

private:
    IlBoolean			_collate;
    IlBoolean			_color;
    IlvPrinter::Orientation	_orientation;
    IlvPaperFormat*		_paperFormat;
    IlString			_filename;
    IlUInt			_numcopies;
    IlvBitmap*			_onepage;
    IlvDim			_leftMargin;
    IlvDim			_rightMargin;
    IlvDim			_topMargin;
    IlvDim			_bottomMargin;
};

class ILVPRTDLGEXPORTED IlvPageMarginDialog 
    : public IlvDialog
{
public:
    IlvPageMarginDialog(IlvDisplay* display, 
			  IlvSystemView transientFor = 0);

    ~IlvPageMarginDialog();

    void		setMargins(IlFloat left,
				   IlFloat right, 
				   IlFloat top,
				   IlFloat bottom);
    void		getMargins(IlFloat& left,
				   IlFloat& right, 
				   IlFloat& top,
				   IlFloat& bottom) const;
    IlBoolean		get(IlBoolean grab = IlFalse, IlvCursor* cursor = 0);
    void		setIncrement(IlBoolean floatmode, IlFloat increment);
    inline void		setLeft(IlFloat value) { _left = value; }
    inline void		setRight(IlFloat value) { _right = value; }
    inline void		setTop(IlFloat value) { _top = value; }
    inline void		setBottom(IlFloat value) { _bottom = value; }
    inline IlFloat	getTop() const { return _top; }
    inline IlBoolean	isSymetric() const { return _symetric; }
    inline void		setSymetric(IlBoolean value) { _symetric = value; }
    void		hideAllBorders();
    void		showHideBorders(IlBoolean,
					IlBoolean,
					IlBoolean,
					IlBoolean);

protected:
    virtual void	init();
    void		updateSpinBoxes();

private:
    IlFloat		_left;
    IlFloat		_right;
    IlFloat		_top;
    IlFloat		_bottom;
    IlBoolean		_symetric;
    IlvSpinBox*		_leftspin;
    IlvSpinBox*		_rightspin;
    IlvSpinBox*		_topspin;
    IlvSpinBox*		_bottomspin;
    IlvNumberField*	_leftnum;
    IlvNumberField*	_rightnum;
    IlvNumberField*	_topnum;
    IlvNumberField*	_bottomnum;
};


ILVPRTDLGMODULEINIT(p2dialogs);

#endif /* __Ilv_Printing_Dialogs_H */
