// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/looks/motif.h
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
//  Declaration of the IlvMotifLFHandler class
// --------------------------------------------------------------------------
#ifndef __Ilv_Looks_Motif_H
#define __Ilv_Looks_Motif_H

#if !defined(__Ilv_Base_Look_H)
#  include <ilviews/base/look.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMotifLFHandler
    : public IlvBasicLFHandler
{
public:

    virtual void	drawInsensitiveLabel(IlvPort*,
					     const char*,
					     const IlvRect&,
					     IlvPosition,
					     IlvOrientation,
					     IlBoolean,
					     IlvPalette*,
					     IlvPalette*,
					     const IlvRegion*,
					     const IlvBidiInterface*) const;

    virtual IlBoolean	hasSystemFileBrowser() const;
    virtual IlvColor* 	getDefaultColor(int) const;
    virtual IlvFont* 	getDefaultFont(int) const;
    virtual IlBoolean	selectTextToEnd() const;
    virtual IlBoolean	autoSelectWhenFocused() const;
    virtual IlBoolean	autoCopyToClipboardWhenSelected() const;
    virtual IlBoolean	isAPasteFromClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	isACopyToClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	showTextSelectionOnlyWhenFocused() const;

    DeclareLazyLookFeelTypeInfo();

protected:
    IlvMotifLFHandler(IlvDisplay*);
};

// --------------------------------------------------------------------------
ILVVWSMODULEINIT(l1motif);

#endif /* !__Ilv_Looks_Motif_H */
