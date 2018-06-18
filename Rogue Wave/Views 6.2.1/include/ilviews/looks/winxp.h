// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/looks/winxp.h
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
//  Declaration of the IlvWindowsXPLFHandler class
// --------------------------------------------------------------------------
#ifndef __Ilv_Looks_Winxp_H
#define __Ilv_Looks_Winxp_H

#if defined(_WIN32)

#if !defined(__Ilv_Looks_Win95_H)
#  include <ilviews/looks/win95.h>
#endif

#include <windows.h>
#include <uxtheme.h>

#if !defined(__Ilv_Gadgets_Winxp_Macros_H)
#  include <ilviews/gadgets/winxp/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVWXPLOOKEXPORTED IlvWindowsXPLFHandler
    : public IlvWindows95LFHandler
{
public:
    // ____________________________________________________________
    DeclareLazyLookFeelTypeInfo();
    virtual void drawThemeBackground(IlvSystemPort*,
				     IlvPalette*,
				     HTHEME,
				     int,
				     int,
				     const IlvRect&,
				     const IlvRegion*) const;
    virtual void drawSeparator(IlvPort*,
			       const IlvRect&,
			       IlvDirection,
			       const IlvPalette*,
			       const IlvPalette*,
			       const IlvRegion*) const;
    virtual void drawGadget(IlvPort*,
			    const IlvPalette*,
			    const IlvPalette*,
			    const IlvPalette*,
			    const IlvPalette*,
			    const IlvRect&,
			    IlUShort,
			    IlBoolean,
			    const IlvRegion*) const;
    virtual void drawThumbBox(IlvPort*,
			      const IlvPalette*,
			      const IlvPalette*,
			      const IlvPalette*,
			      const IlvPalette*,
			      const IlvRect&,
			      IlUShort,
			      IlBoolean,
			      const IlvRegion*) const;
    void drawFrame(IlvPort*,
		   const IlvRect&,
		   const IlvRegion*) const;
protected:
    IlvWindowsXPLFHandler(IlvDisplay*);
    ~IlvWindowsXPLFHandler();
    virtual void initialize();
    virtual void releaseResources();
    IlvPalette* getTransparentPalette();
    void releaseThisResources();
    HTHEME _gadgetTheme;
    IlvPalette* _transpPalette;
};

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && \
    !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "uxtheme.lib")
#endif

// --------------------------------------------------------------------------
ILVWXPLOOKMODULEINIT(w3winxp);

#endif /* _WIN32 */

#endif /* !__Ilv_Looks_Winxp_H */
