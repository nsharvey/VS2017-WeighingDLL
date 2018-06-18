// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/iprompt.h
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
// Declaration of the IlvIPromptString class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Iprompt_H
#define __Ilv_Gadgets_Iprompt_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvIPromptString : public IlvDialog
{
public:
    IlvIPromptString(IlvDisplay*        display,
                     const char*        string        = 0,
                     const char* const* strings       = 0,
                     IlUShort           count         = 0,
                     IlBoolean          copy          = IlTrue,
                     IlBoolean          showtextf     = IlTrue,
                     const char*        fileordata    = 0,
		     IlvSystemView      transientFor  = 0,
		     IlUInt		properties    = 0);
    // ____________________________________________________________
    void		setString(const char* string);
    const char*		getResult();

    void		setResult(const char* string);
    void		setLabels(const char* const* strings,
				  IlUShort           count,
				  IlBoolean          copy      = IlTrue,
				  IlBoolean          showtextf = IlTrue);
    const char*		get(IlBoolean grab = IlFalse,
			    IlvCursor* cursor = 0);

    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual IlBoolean	handleKeyUp(IlvEvent&);
};

#endif /* !__Ilv_Gadgets_Iprompt_H */
