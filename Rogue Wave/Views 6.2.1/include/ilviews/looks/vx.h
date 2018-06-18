// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/looks/vx.h
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
//  Declaration of the IlvVXLFHandler class
// --------------------------------------------------------------------------
#ifndef __Ilv_Looks_Vx_H
#define __Ilv_Looks_Vx_H

#if !defined(__Ilv_Looks_Windows_H)
#  include <ilviews/looks/windows.h>
#endif


// --------------------------------------------------------------------------
enum IlvVXPaletteName {
    IlvVXBackgroundPalette = 0, 

    IlvVXBorderPalette = 1,
    // Reserve 2, 3 for computing border and 4 for Shadow

    IlvVXBackgroundGadgetPalette = 5,
    // Reserve 6, 7, 8 for gradient

    IlvVXForegroundGadgetPalette = 9,

    IlvVXBackgroundInactiveGadgetPalette = 10,
    // Reserve 11, 12, 13 for gradient

    IlvVXDefaultButtonPalette = 14,

    IlvVXLightEffectPalette = 15,

    IlvVXBackgroundEditionPalette = 16,

    IlvVXForegroundEditionPalette = 17,

    IlvVXBackgroundSelectionPalette = 18,

    IlvVXForegroundSelectionPalette = 19,

    IlvVXGrayTextPalette = 20,

    IlvVXFocusLinePalette = 21,

    IlvVXDotLinePalette = 22,

    IlvVXCaptionPalette = 23,

    IlvVXInactiveCaptionPalette = 24,

    IlvVXGridPalette = 25,

    IlvVXWhiteReliefPalette = 26,

    IlvVXPaletteCount = 27
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvVXLFHandler : public IlvWindowsLFHandler
{
public:

    IlvPalette*		getPublicPalette(IlvVXPaletteName name) const;

    void		setPublicPalette(IlvVXPaletteName name,
					 IlvPalette* pal);

    void		initializeInternalPalettes();
    void		recomputeInternalPalette(IlvVXPaletteName name);

    void		buildGradientPalettes(IlvVXPaletteName);
    void		buildShadowPalette();
    void		buildBorderPalettes();

    void		setDominantUIColor(IlvColor* color);
    void		setPaletteAndPropagate(IlvVXPaletteName name,
					       IlvPalette* pal);

    virtual IlvColor* 	getDefaultColor(int index) const;
    virtual IlvFont* 	getDefaultFont(int index) const;
    virtual IlBoolean   usesSystemColors() const;
    virtual void        drawSeparator(IlvPort*,
				      const IlvRect&,
				      IlvDirection,
				      const IlvPalette*,
				      const IlvPalette*,
				      const IlvRegion*) const;
    virtual void        drawGadget(IlvPort*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvPalette*,
				   const IlvRect&,
				   IlUShort,
				   IlBoolean,
				   const IlvRegion* clip) const;
    virtual void        drawThumbBox(IlvPort*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvPalette*,
				     const IlvRect&,
				     IlUShort,
				     IlBoolean,
				     const IlvRegion* clip) const;
    virtual void        drawFrame(IlvPort*,
				  const IlvRect&,
				  const IlvRegion*) const;
    virtual void        drawArrow(IlvPort* dst,
				  const IlvRect& bbox,
				  IlvDirection dir,
				  IlvPalette* palette,
				  const IlvRegion* clip);

    virtual void        drawInsensitiveLabel(IlvPort*         dst,
					     const char*      label,
					     const IlvRect&   rect,
					     IlvPosition      alignment,
					     IlvOrientation   orientation,
					     IlBoolean        flip,
					     IlvPalette*      spalette,
					     IlvPalette*      palette,
					     const IlvRegion* clip,
					     const IlvBidiInterface*) const;

    virtual void	setMode(IlvDrawMode) const;
    virtual void	setOverwrite(IlBoolean) const;

    virtual void	drawRoundBorder(IlvPort*,
					const IlvRect&,
					const IlvRegion*,
					IlBoolean = IlFalse,
					IlvPalette* = 0) const;
    virtual void	drawSquareBorder(IlvPort*,
					 const IlvRect&,
					 const IlvRegion*,
					 IlBoolean = IlFalse,
					 IlvPalette* = 0,
					 IlBoolean = IlTrue) const;

    virtual void	drawRectangleBorder(IlvPort*,
					    const IlvRect&,
					    const IlvRegion*,
					    IlBoolean = IlFalse,
					    IlvPalette* = 0,
					    IlBoolean = IlTrue) const;

    virtual void	drawMenuBorder(IlvPort*,
				       const IlvRect&,
				       const IlvRegion*) const;

    virtual void	drawGradientFrame(IlvPort*,
					  const IlvRect&,
					  const IlvRegion*,
					  IlvPosition pos = IlvTop) const;
    virtual void	drawGradientButton(IlvPort*,
					   const IlvRect&,
					   const IlvRegion*,
					   IlBoolean = IlFalse,
					   IlvPalette* = 0) const;
    virtual void	drawGradientSquare(IlvPort*,
					   const IlvRect&,
					   const IlvRegion*,
					   IlvPosition pos = IlvTop) const;
    virtual void	drawTopGradient(IlvPort*,
					const IlvRect&,
					const IlvRegion*,
					IlvPosition pos = IlvTop) const;
    virtual void	drawGradient(IlvPort*,
				     const IlvRect&,
				     const IlvRegion*,
				     IlBoolean,
				     IlvPosition pos = IlvTop) const;

    void		setInternalPalette(IlInt name, IlvPalette*);
    IlvPalette*		getInternalPalette(IlInt) const;
    const IlvPalette*	getInternalStylePalette(IlInt) const;

    // Inherits from Default and windows look
    virtual IlvPalette* getFocusLine() const;
    virtual IlvPalette* getDotLine() const;
    virtual IlvPalette* getWindowBackground() const;
    virtual IlvPalette* getWindowForeground() const;
    virtual IlvPalette* getWindowFrame() const;
    virtual IlvPalette* getButtonFace() const;
    virtual IlvPalette* getButtonText() const;
    virtual IlvPalette* getButtonShadow() const;
    virtual IlvPalette* getButtonHighLight() const;
    virtual IlvPalette* getHBackground() const;
    virtual IlvPalette* getHForeground() const;
    virtual IlvPalette* getScrollbar() const;
    virtual IlvPalette* getMenu() const;
    virtual IlvPalette* getMenuText() const;
    virtual IlvPalette* getGrayText() const;
    virtual IlvPalette*	getActiveCaptionPalette() const;
    virtual IlvPalette*	getInactiveCaptionPalette() const;
    virtual IlvColor*	getGadgetContainerBackground() const;

    DeclareLazyLookFeelTypeInfo();

protected:
    IlvVXLFHandler(IlvDisplay*);
    ~IlvVXLFHandler();

    virtual void        computeDefaultColors();
    virtual void        releaseResources();

    IlvPalette**	_vxPalettes;
    IlBoolean		_autoComputeMode;
};

// --------------------------------------------------------------------------
ILVVWSMODULEINIT(l1vx);

#endif /* !__Ilv_Looks_Vx_H */
