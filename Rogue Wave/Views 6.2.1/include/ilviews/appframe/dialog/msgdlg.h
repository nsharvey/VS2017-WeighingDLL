// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/msgdlg.h
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
// Declaration of the IlvDvMessageDialog class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Dialog_Msgdlg_H)
#define __Ilv_Appframe_Dialog_Msgdlg_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif

class IlvMessageLabel;
class IlvButton;
// --------------------------------------------------------------------------
#define ILVDV_OK                       0x00000000L
#define ILVDV_OKCANCEL                 0x00000001L
#define ILVDV_ABORTRETRYIGNORE         0x00000002L
#define ILVDV_YESNOCANCEL              0x00000003L
#define ILVDV_YESNO                    0x00000004L
#define ILVDV_RETRYCANCEL              0x00000005L

#define ILVDV_ICONHAND                 0x00000010L
#define ILVDV_ICONQUESTION             0x00000020L
#define ILVDV_ICONEXCLAMATION          0x00000030L
#define ILVDV_ICONASTERISK             0x00000040L

#define ILVDV_USERICON                 0x00000080L
#define ILVDV_ICONWARNING              ILVDV_ICONEXCLAMATION
#define ILVDV_ICONERROR                ILVDV_ICONHAND

#define ILVDV_DEFBUTTON1               0x00000000L
#define ILVDV_DEFBUTTON2               0x00000100L
#define ILVDV_DEFBUTTON3               0x00000200L
#define ILVDV_DEFBUTTON4               0x00000300L

#define ILVDV_IDOK                1
#define ILVDV_IDCANCEL            2
#define ILVDV_IDABORT             3
#define ILVDV_IDRETRY             4
#define ILVDV_IDIGNORE            5
#define ILVDV_IDYES               6
#define ILVDV_IDNO                7
#define ILVDV_IDCLOSE		  8
#define ILVDV_IDHELP		  9

// --------------------------------------------------------------------------
// IlvDvAutoFitDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvAutoFitDialog : public IlvDialog
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvAutoFitDialog(IlvDisplay*,
		       const char*   name,
		       const char*   title,
		       IlUInt        style = ILVDV_OK | ILVDV_DEFBUTTON1,
		       IlvSystemView transientFor = 0);
    virtual ~IlvDvAutoFitDialog();

    // ----------------------------------------------------------------------
    IlUInt popup();
    virtual IlBoolean	initializePanel();
    inline IlvButton*	getCancelButton() const { return _cancelButton; }
    inline IlvButton*	getOKButton() const { return _okButton; }

protected:
    IlvGraphic*		_mainGraphic;
    IlBoolean		_panelInitialized;
    IlUInt		_style;
    IlUInt		_answer;
    IlvButton*		_cancelButton;
    IlvButton*		_okButton;

    virtual IlvGraphic*	createGraphic(const IlvRect& defaultRect) = 0;
    virtual IlBoolean	getRequieredGraphicSize(IlvDim& w, IlvDim& h) = 0;
    virtual void	postInitializeGraphic();
    void		fitPanel();
    IlUInt		getButtonCount() const;
    const char*		getButtonTitle(IlUInt) const;
    const char*		getButtonName(IlUInt, IlString& name) const;
    IlBoolean		isCancelButton(IlUInt) const;
    IlBoolean		isOKButton(IlUInt) const;

public:
    static void		NoCallback(IlvGraphic* obj, IlAny);
};

// --------------------------------------------------------------------------
// IlvDvAutoFitILVDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvAutoFitILVDialog : public IlvDvAutoFitDialog
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvAutoFitILVDialog(IlvDisplay*,
			  const char*   name,
			  const char*   title,
			  const char*   ilvPath,
			  IlUInt        style = ILVDV_OK | ILVDV_DEFBUTTON1,
			  IlvSystemView transientFor = 0);
    virtual ~IlvDvAutoFitILVDialog();

    // ----------------------------------------------------------------------

protected:
    IlvDim		_initialILVWidth;
    IlvDim		_initialILVHeight;
    IlString		_ilvPath;

    virtual IlBoolean	getRequieredGraphicSize(IlvDim& w, IlvDim& h);
    virtual IlvGraphic*	createGraphic(const IlvRect& defaultRect);
    virtual void	getRequieredContainerSize(IlvDim& w, IlvDim& h);
};

// --------------------------------------------------------------------------
// IlvDvMessageDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvMessageDialog : public IlvDvAutoFitILVDialog
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvMessageDialog(IlvDisplay*,
		       const char*   title,
		       const char*   msg,
		       const char*   bitmapPath,
		       IlUInt        style = ILVDV_OK | ILVDV_DEFBUTTON1,
		       IlvSystemView transientFor = 0);
    virtual ~IlvDvMessageDialog();

    // ----------------------------------------------------------------------

protected:
    IlvBitmap*		_bitmap;
    IlvMessageLabel*	_msgLabel;

    virtual IlBoolean	getRequieredGraphicSize(IlvDim& w, IlvDim& h);
    virtual IlvGraphic*	createGraphic(const IlvRect& defaultRect);
    virtual void	postInitializeGraphic();
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(msgdlg);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Msgdlg_H */
