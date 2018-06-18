// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/scrdlg.h
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
// Declaration of the IlvScriptCommonDialog class
// Defined in library ilvadvgdgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Scrdlg_H
#define __Ilv_Gadgets_Scrdlg_H

#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#include <ilviews/gadgets/stdialog.h>
#endif
#if !defined(__Ilv_Gadgets_Colorch_H)
#include <ilviews/gadgets/colorch.h>
#endif
#if !defined(__Ilv_Gadgets_Fontsel_H)
#include <ilviews/gadgets/fontsel.h>
#endif
#if !defined(__Ilv_Util_Dialogs_H)
#include <ilviews/util/dialogs.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvScriptCommonDialog : public IlvValueInterface
{
public:
    IlvScriptCommonDialog(IlSymbol* def);
    virtual ~IlvScriptCommonDialog();
    // ____________________________________________________________
    virtual void	lock();
    virtual void	unLock();
    virtual IlInt	messageBox(const char*     msg,
				   IlvIDialogType  type = IlvDialogOkCancel,
				   const char*     title = 0,
				   IlvSystemView   transientFor = 0) const;
    virtual const char*	getFile(const char*	    directory = 0,
				const char*         filter = 0,
				const char*         message = 0,
				IlvFileSelectorType type = IlvFileSelectorLoad,
				IlvSystemView       transientFor = 0) const;
    virtual IlvColor*	getColor(IlvSystemView transientFor = 0) const;
    virtual IlvFont*	getFont(IlvSystemView transientFor = 0) const;
    // ____________________________________________________________
    virtual void	setDefaultMethod(IlSymbol* def);
    // --- Other accessors ---
    DeclareGraphicAccessors();
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_messageBoxMethod;
    static IlSymbol*	_getFileMethod;
    static IlSymbol*	_getColorMethod;
    static IlSymbol*	_getFontMethod;
    IlvDeclareClassInfo();

protected:
    IlInt		_refCount;
    IlSymbol*		_defMethod;
};

ILVADVGDTMODULEINIT(scrdlg);

#endif /* !__Ilv_Gadgets_Scrdlg_H */
