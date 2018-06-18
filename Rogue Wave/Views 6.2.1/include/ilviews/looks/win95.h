// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/looks/win95.h
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
//  Declaration of the IlvWindows95LFHandler class
// --------------------------------------------------------------------------
#ifndef __Ilv_Looks_Win95_H
#define __Ilv_Looks_Win95_H

#if !defined(__Ilv_Looks_Windows_H)
#  include <ilviews/looks/windows.h>
#endif

class IlvGadget;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvWindows95LFHandler
    : public IlvWindowsLFHandler
{
public:

    inline IlvPalette*	getLight()      const { return _buttonHighLight; }
    inline IlvPalette*	get3DLight()    const { return _button3DLight;   }
    inline IlvPalette*	getDarkShadow() const { return _buttonShadow;    }
    IlvPalette*		get3DFace(const IlvGadget*) const;
    virtual IlvColor*	getDefaultColor(int) const;
    virtual IlvFont*	getDefaultFont(int) const;
    virtual IlBoolean	usesSystemColors() const;
    virtual void	drawSeparator(IlvPort*,
				      const IlvRect&,
				      IlvDirection,
				      const IlvPalette*,
				      const IlvPalette*,
				      const IlvRegion*) const;
    virtual void	drawGadget(IlvPort*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvRect&,
				   IlUShort,
				   IlBoolean,
				   const IlvRegion*) const;
    virtual void	drawThumbBox(IlvPort*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvRect&,
				     IlUShort,
				     IlBoolean,
				     const IlvRegion*) const;
    void		drawFrame(IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
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

    DeclareLazyLookFeelTypeInfo();

protected:
    IlvWindows95LFHandler(IlvDisplay*);
    ~IlvWindows95LFHandler();

    virtual void	computeDefaultColors();
    virtual void	releaseResources();
    void		releaseThisResources();

    IlvPalette*		_button3DLight;
};

// --------------------------------------------------------------------------
ILVVWSMODULEINIT(l1win95);

#endif /* !__Ilv_Looks_Win95_H */
