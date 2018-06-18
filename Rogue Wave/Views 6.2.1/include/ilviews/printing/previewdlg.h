// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/previewdlg.h
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
// Definition of the IlvPreviewDialog class.
// --------------------------------------------------------------------------

#ifndef __Ilv_Printing_Previewdlg_H
#define __Ilv_Printing_Previewdlg_H

#if !defined(__Ilv_Printing_DialogMacros_H)
#include <ilviews/printing/dlgmacros.h>
#endif
#if !defined(__Ilv_Printing_Document_H)
#include <ilviews/printing/document.h>
#endif
#if !defined(__Ilv_Printing_PreviewDisplayer_H)
#include <ilviews/printing/prevdisplayer.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif
#if !defined(__Ilv_Gadgets_Scombo_H)
#include <ilviews/gadgets/scombo.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Rectscgc_H)
#include <ilviews/gadgets/rectscgc.h>
#endif
#if !defined(__Ilv_Gadgets_Frame_H)
#include <ilviews/gadgets/frame.h>
#endif

// --------------------------------------------------------------------------
// Forward declarations.
class IlvPrinterPreviewPageControler;
class IlvPrinterPreviewDialogDoPrint;

// --------------------------------------------------------------------------
class ILVPRTDLGEXPORTED IlvPrinterPreviewDialog : public IlvDialog
{
    friend class IlvPrinterPreviewPageControler;
public:
    IlvPrinterPreviewDialog(
	IlvDisplay*			 display,
	IlvSystemView			 transientFor = 0,
	IlvPrinterPreviewDisplayer::Mode mode
					= IlvPrinterPreviewDisplayer::OnePage);
    ~IlvPrinterPreviewDialog();
    inline IlInt getResult() const { return _result; }

    IlInt get(
	IlvPrinter&				referencePrinter,
	IlvPrintableDocument const&		document,
	IlvPrintableDocument::Iterator const&	first,
	IlvPrintableDocument::Iterator const&	last,
	int					copyNumber = 1,
	IlBoolean				useAbsolutePageIndex = IlTrue,
	IlBoolean				grab = IlFalse,
	IlvCursor*				cursor = 0);
    IlInt get(IlvPrinter&			referencePrinter,
	      IlvPrintableDocument const&	document,
	      int				first = 0,
	      int				last = -1,
	      int				copyNumber = 1,
	      IlBoolean				useAbsolutePageIndex = IlTrue,
	      IlBoolean				grab = IlFalse,
	      IlvCursor*			cursor = 0);
    inline IlBoolean isBad() const { return _isBad; }
    IlvPrinterPreviewDisplayer::Mode getMode() const;
    inline IlvTransfoParam getZoomFactor() const {  return _zoomFactor; }
    inline IlvPrinter&	getReferencePrinter() const
			{
			    return *_referencePrinter;
			}
    void setMode(IlvPrinterPreviewDisplayer::Mode mode);
    void setZoomFactor(IlvTransfoParam zoomFactor);
    inline IlBoolean	isDialogDisplayForced() const
			{
			    return _forceDialogDisplay;
			}

    inline void		forceDialogDisplay(IlBoolean force)
			{
			    _forceDialogDisplay = force;
			}


    IlvPrinterPreview& getPrinterPreview() const;

private:
    static void ModeCB(IlvGraphic* obj, IlAny userArg);
    static void ZoomCB(IlvGraphic* obj, IlAny userArg);
    static void SettingsCB(IlvGraphic* obj, IlAny userArg);
    static void ResizeCB(IlvView*, IlvRect&, IlAny userArg);
    static void DestroyCB(IlvView*, IlAny);

    void modifySettings();
    void updateSizes();
    void initData(IlvPrinterPreviewDisplayer::Mode mode);
    void initCallbacks();
    void updatePage(IlInt page);
    void updatePageNumber(IlInt page);
    void updateDocumentName(char const* documentName);
    void activate(IlBoolean flag = IlTrue);
    void init();
    void clean();
    IlInt internalGet(IlvPrinter&	referencePrinter,
		      IlBoolean		grab,
		      IlvCursor*	cursor);
    IlvPrinterPreviewDisplayer* getPreviewDisplayer() const;

    IlBoolean					_isBad;
    IlBoolean					_isPrinting;
    IlvPrinter*					_referencePrinter;
    IL_MUTABLE IlvPrinterPreviewDisplayer*	_previewDisplayer;
    IlvTransfoParam				_zoomFactor;
    IlvPrinterPreviewPageControler*		_pageControler;
    IlvScrolledComboBox*			_previewLayoutCombo;
    IlvScrolledComboBox*			_zoomFactorCombo;
    IlvSCGadgetContainerRectangle*		_containerRectangle;
    IlvButton*					_printButton;
    IlvButton*					_cancelButton;
    IlvButton*					_settingsButton;
    IlInt					_result;
    IL_MUTABLE IlvPrinterPreview*		_printerPreview;
    IlvPrinterPreviewDisplayer::Mode		_mode;
    IlvPrinterPreviewDialogDoPrint*		_doPrint;
    IlBoolean					_forceDialogDisplay;
};

#endif /* __Ilv_Printing_Previewdlg_H */
