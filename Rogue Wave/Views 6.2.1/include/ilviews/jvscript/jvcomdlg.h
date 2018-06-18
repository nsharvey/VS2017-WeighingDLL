// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/jvscript/jvcomdlg.h
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
// Declaration of the IlvJSCommonDialog class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Jvscript_Jvcomdlg_H
#define __Ilv_Jvscript_Jvcomdlg_H

#if !defined(__Ilv_Jvscript_Macros_H)
#include <ilviews/jvscript/macros.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Util_Dialogs_H)
#include <ilviews/util/dialogs.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#include <ilviews/gadgets/stdialog.h>
#endif

// --------------------------------------------------------------------------
class ILVJSLEXPORTED IlvJSCommonDialog
    : public IlvValueInterface
{
public:
    IlvJSCommonDialog(IlvDisplay* display, IlSymbol* def=0)
	: _refCount(0),
	  _display(display),
	  _defMethod(def)
    {}
    virtual ~IlvJSCommonDialog();

    virtual void	lock();
    virtual void	unLock();
    virtual IlInt	messageBox(const char*     msg,
				   IlvIDialogType  type = IlvDialogOkCancel,
				   const char*     title = 0,
				   IlvSystemView   transientFor = 0);
    virtual const char*	getFile(const char*	    directory = 0,
				const char*         filter = 0,
				const char*         message = 0,
				IlvFileSelectorType type =
				IlvFileSelectorLoad,
				IlvSystemView       transientFor = 0);

    IlvDisplay*		getDisplay() const { return _display; }
    virtual void	setDefaultMethod(IlSymbol* def);

    DeclareGraphicAccessors();
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_messageBoxMethod;
    static IlSymbol*	_getFileMethod;
    IlvDeclareClassInfo();

protected:
    IlInt		_refCount;
    IlvDisplay*		_display;
    IlSymbol*		_defMethod;
};

#endif /* !__Ilv_Jvscript_Jvcomdlg_H */
