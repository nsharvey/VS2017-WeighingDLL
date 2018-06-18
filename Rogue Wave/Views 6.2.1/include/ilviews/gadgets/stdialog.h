// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/stdialog.h
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
// Declaration of predefined standard dialogs classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Stdialog_H
#define __Ilv_Gadgets_Stdialog_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif
#if !defined(__Ilv_Graphics_Icon_H)
#include <ilviews/graphics/icon.h>
#endif

enum IlvIDialogType {
    IlvDialogOk,
    IlvDialogOkCancel
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvIMessageDialog : public IlvDialog
{
public:
    IlvIMessageDialog(IlvDisplay*    display,
		      const char*    string,
		      const char*    fileordata   = 0,
		      IlvIDialogType type         = IlvDialogOkCancel,
		      IlvSystemView  transientFor = 0);
    IlvIMessageDialog(IlvDisplay*        display,
		      const char* const* strings,
		      IlUShort           count,
		      IlBoolean          copy         = IlTrue,
		      const char*        fileordata   = 0,
		      IlvIDialogType     type         = IlvDialogOkCancel,
		      IlvSystemView      transientFor = 0);

    void		setBitmap(IlvBitmap*);
    void		setString(const char* string);
    void		setString(const char* const* strings,
				  IlUShort count,
				  IlBoolean copy = IlTrue);

    void		fitToString();
    IlBoolean		getResult();
    IlBoolean		get(IlBoolean grab = IlFalse, IlvCursor* cursor = 0);

    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual IlBoolean	handleKeyUp(IlvEvent&);
    virtual void	setBackground(IlvColor* c);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

protected:
    void		initialize(const char* fileordata,
				   IlvIDialogType type);
    virtual void	changeLook();

    IlvDim		_minWidth;
    IlvDim		_minHeight;
    IlvDim		_deltaWidth;
    IlvDim		_deltaHeight;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvIQuestionDialog : public IlvIMessageDialog
{
public:
    IlvIQuestionDialog(IlvDisplay*    display,
                       const char*    title,
                       const char*    fileordata   = 0,
		       IlvIDialogType type         = IlvDialogOkCancel,
		       IlvSystemView  transientFor = 0);
    IlvIQuestionDialog(IlvDisplay*        display,
                       const char* const* strings,
                       IlUShort           count,
                       IlBoolean          copy         = IlTrue,
                       const char*        fileordata   = 0,
		       IlvIDialogType     type         = IlvDialogOkCancel,
		       IlvSystemView      transientFor = 0);

    virtual void	changeLayoutAttributes(IlAny, IlAny);

protected:
    virtual void	changeLook();
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvIInformationDialog : public IlvIMessageDialog
{
public:
    IlvIInformationDialog(IlvDisplay*    display,
			  const char*    title,
			  const char*    fileordata   = 0,
			  IlvIDialogType type         = IlvDialogOk,
			  IlvSystemView  transientFor = 0);
    IlvIInformationDialog(IlvDisplay*        display,
			  const char* const* strings,
			  IlUShort           count,
			  IlBoolean          copy         = IlTrue,
			  const char*        fileordata   = 0,
			  IlvIDialogType     type         = IlvDialogOk,
			  IlvSystemView      transientFor = 0);

    virtual void	changeLayoutAttributes(IlAny, IlAny);

protected:
    virtual void	changeLook();
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvIErrorDialog : public IlvIMessageDialog
{
public:
    IlvIErrorDialog(IlvDisplay*    display,
		    const char*    title,
		    const char*    fileordata   = 0,
		    IlvIDialogType type         = IlvDialogOk,
		    IlvSystemView  transientFor = 0);
    IlvIErrorDialog(IlvDisplay*        display,
		    const char* const* strings,
		    IlUShort           count,
		    IlBoolean          copy         = IlTrue,
		    const char*        fileordata   = 0,
		    IlvIDialogType     type         = IlvDialogOk,
		    IlvSystemView      transientFor = 0);

    virtual void	changeLayoutAttributes(IlAny, IlAny);

protected:
    virtual void	changeLook();
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvIWarner : public IlvIMessageDialog
{
public:
    IlvIWarner(IlvDisplay*    display,
               const char*    title,
               const char*    fileordata   = 0,
	       IlvIDialogType type         = IlvDialogOk,
	       IlvSystemView  transientFor = 0);
    IlvIWarner(IlvDisplay*        display,
               const char* const* strings,
               IlUShort           count,
               IlBoolean          copy         = IlTrue,
               const char*        fileordata   = 0,
	       IlvIDialogType     type         = IlvDialogOk,
	       IlvSystemView      transientFor = 0);

    virtual void	changeLayoutAttributes(IlAny, IlAny);

protected:
    virtual void	changeLook();
};

#endif /* !__Ilv_Gadgets_Stdialog_H */
