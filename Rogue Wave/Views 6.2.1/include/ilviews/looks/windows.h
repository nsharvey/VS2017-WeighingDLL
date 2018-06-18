// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/looks/windows.h
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
//  Declaration of the IlvWindowsLFHandler class
// --------------------------------------------------------------------------
#ifndef __Ilv_Looks_Windows_H
#define __Ilv_Looks_Windows_H

#if !defined(__Ilv_Base_Look_H)
#  include <ilviews/base/look.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvWindowsLFHandler : public IlvBasicLFHandler
{
public:

    IlBoolean		isSmall()             const;
    inline IlUShort	getCxHScroll()	      const { return _cxHScroll; }
    inline IlUShort	getCyHScroll()	      const { return _cyHScroll; }
    inline IlUShort	getCxVScroll()	      const { return _cxVScroll; }
    inline IlUShort	getCyVScroll()	      const { return _cyVScroll; }
    inline IlUShort	getCxHThumb()	      const { return _cxHThumb;  }
    inline IlUShort	getCyVThumb()	      const { return _cyVThumb;  }
    inline IlUShort	getCyMenu()	      const { return _cyMenu;    }

    virtual IlvPalette* getFocusLine()        const;
    virtual IlvPalette* getDotLine()          const;
    virtual IlvPalette* getWindowBackground() const;
    virtual IlvPalette* getWindowForeground() const;
    virtual IlvPalette* getWindowFrame()      const;
    virtual IlvPalette* getButtonFace()       const;
    virtual IlvPalette* getButtonText()       const;
    virtual IlvPalette* getButtonShadow()     const;
    virtual IlvPalette* getButtonHighLight()  const;
    virtual IlvPalette* getHBackground()      const;
    virtual IlvPalette* getHForeground()      const;
    virtual IlvPalette* getScrollbar()        const;
    virtual IlvPalette* getMenu()	      const;
    virtual IlvPalette* getMenuText()	      const;
    virtual IlvPalette* getGrayText()	      const;
    virtual IlvPalette* getDashLine()	      const;
#if defined(WINDOWS)
    virtual IlvFont*	getSystemFont(int index) const;
#endif /* WINDOWS */
    virtual IlBoolean	hasSystemFileBrowser() const;
    virtual IlvColor*	getDefaultColor(int index) const;
    virtual IlvFont*	getDefaultFont(int index) const;
    virtual IlBoolean	usesSystemColors() const;
    virtual IlvDim	getMnemonicDescent(IlvFont*) const;
    virtual void	drawGadget(IlvPort*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvRect&,
				   IlUShort,
				   IlBoolean,
				   const IlvRegion* clip) const;
    virtual void	drawThumbBox(IlvPort*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvRect&,
				     IlUShort,
				     IlBoolean,
				     const IlvRegion* clip) const;
    virtual void	drawArrow(IlvPort*,
				  const IlvRect&,
				  IlvDirection,
				  IlvPalette*,
				  const IlvRegion*);
    virtual void	drawHighlight(IlvPort*,
				      const IlvRect&,
				      IlvPalette*,
				      const IlvRegion*,
				      IlBoolean) const;
    virtual void	drawInsensitiveLabel(IlvPort*		dst,
					     const char*	label,
					     const IlvRect&	rect,
					     IlvPosition	alignment,
					     IlvOrientation	orientation,
					     IlBoolean		flip,
					     IlvPalette*	spalette,
					     IlvPalette*	palette,
					     const IlvRegion*	clip,
					     const IlvBidiInterface*) const;
    virtual IlBoolean	selectTextToEnd() const;
    virtual IlBoolean	autoSelectWhenFocused() const;
    virtual IlBoolean	autoCopyToClipboardWhenSelected() const;
    virtual IlBoolean	isAPasteFromClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	isACopyToClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	isACutToClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	showTextSelectionOnlyWhenFocused() const;

    virtual void	setMode(IlvDrawMode) const;
    virtual void	setOverwrite(IlBoolean) const;

    DeclareLazyLookFeelTypeInfo();

protected:
    IlvWindowsLFHandler(IlvDisplay*);
    virtual ~IlvWindowsLFHandler();

    virtual void	initialize();
    virtual void	releaseResources();
    void		releaseThisResources();
    virtual void	computeDefaultColors();
    virtual void	computeDefaultSizes();

    IlUShort		_cxHScroll;
    IlUShort		_cyHScroll;
    IlUShort		_cxVScroll;
    IlUShort		_cyVScroll;
    IlUShort		_cxHThumb;
    IlUShort		_cyVThumb;
    IlvPalette*		_wDotLine;
    IlvPalette*		_wFocusLine;
    IlvPalette*		_winBackground;
    IlvPalette*		_winForeground;
    IlvPalette*		_winFrame;
    IlvPalette*		_grayText;
    IlvPalette*		_buttonFace;
    IlvPalette*		_buttonText;
    IlvPalette*		_buttonHighLight;
    IlvPalette*		_buttonShadow;
    IlvPalette*		_wHBackground;
    IlvPalette*		_wHForeground;
    IlvPalette*		_wScrollbar;
    IlvPalette*		_wMenu;
    IlvPalette*		_wMenuText;
    IlvPalette*		_wDashLine;
    IlUShort		_cyMenu;
};

// --------------------------------------------------------------------------
ILVVWSMODULEINIT(l1windows);

#endif /* !__Ilv_Looks_Windows_H */
