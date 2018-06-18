// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/cbrowser.h
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
// Definition of the ActiveX control browser.
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Cbrowser_H
#define __Ilv_Windows_Cbrowser_H

#if !defined(__Ilv_Windows_Macros_H)
#include <ilviews/windows/macros.h>
#endif
#if !defined(__Ilv_Base_String_h)
#include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Base_View_h)
#include <ilviews/base/view.h>
#endif
#if defined(ILVSTD)
#include <cstdlib>
#else  /* !ILVSTD */
#include <stdlib.h>
#endif /* !ILVSTD */
#include <oledlg.h>

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvControlBrowser
{
public:
    IlvControlBrowser(IlvSystemView parent, const char* title = 0);
    ~IlvControlBrowser();
    void setTitle(const char* title);
    const char* show();
    const char* show(IlvPos x, IlvPos y);
    const char* showToView(const IlvView*	view,
			   IlvDirection		justification  = IlvCenter,
			   IlvPos		dx = 0,
			   IlvPos		dy = 0,
			   IlBoolean		ensureInScreen = IlTrue);
    const char* showToMouse(IlvDisplay*		display,
			    IlvDirection	justification  = IlvCenter,
			    IlvPos		dx = 0,
			    IlvPos		dy = 0,
			    IlBoolean		ensureInScreen = IlTrue);
    const char* showToScreen(IlvDisplay*	display,
			     IlvDirection	justification  = IlvCenter,
			     IlvPos		dx = 0,
			     IlvPos		dy = 0,
			     IlBoolean		ensureInScreen = IlTrue);

private:
    // These two functions are intentionally not defined.
    IlvControlBrowser(const IlvControlBrowser&);
    IlvControlBrowser& operator=(const IlvControlBrowser&);

    OLEUIINSERTOBJECT	_io;
    TCHAR		_szFile[_MAX_PATH];
    char*		_title;
};

#endif /* !__Ilv_Windows_Cbrowser_H */
