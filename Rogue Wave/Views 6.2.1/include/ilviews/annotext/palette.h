// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/palette.h
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
// Declaration of the IlvATPalette class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Palette_H
#define __Ilv_Annotext_Palette_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif

typedef enum IlvATWrap {
    IlvCharWrap,
    IlvWordWrap,
    IlvNoWrap
} _IlvATWrap;

typedef enum IlvATAlignment {
    IlvATBaseBottom,
    IlvATBaseMiddle,
    IlvATBaseTop,
    IlvATTextBottom,
    IlvATTextMiddle,
    IlvATTextTop,
    IlvATLineBottom,
    IlvATLineMiddle,
    IlvATLineTop
} _IlvATAlignment;

class ILVATEXPORTED IlvAnnoText;
class ILVATEXPORTED IlvATRope;
class ILVATEXPORTED IlvATZone;
class ILVATEXPORTED IlvATInteractor;

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATPalette
{
 public:
    IlvATPalette(IlvDisplay*	display,
		 IlvPalette*	palette		= 0,
		 IlvDim		linespacing	= 0,
		 IlvDim		rightmargin	= 0,
		 IlvDim		leftmargin	= 1,
		 IlvDim		firstlineoffset	= 0,
		 IlvDim		spaceafter	= 0,
		 IlvDim		spacebefore	= 0,
		 IlvDim		vertoffset	= 0,
		 IlBoolean	visible		= IlTrue,
		 IlBoolean	drawbackground	= IlFalse,
		 IlvATWrap	wrap		= IlvWordWrap,
		 IlvATAlignment	align		= IlvATBaseBottom);

    IlvATPalette(const IlvATPalette& atPalette);
    ~IlvATPalette();

    inline IlvPalette*	getPalette() const { return _palette; }
    void		setPalette(IlvPalette* palette);
    IlBoolean		isDrawingBackground() const
    {
	return _drawingBackground;
    }
    inline void		setDrawingBackground(IlBoolean b)
			{
			    _drawingBackground = b;
			}
    IlBoolean		isVisible() const { return _visible; }
    inline void		setVisible(IlBoolean visible) { _visible = visible; }
    inline IlvDim	getVertOffset() const { return _vertOffset; }
    inline void		setVertOffset(IlvDim val) { _vertOffset = val; }
    inline IlvDim	getFirstLineOffset() const
	{ return _firstLineOffset; }
    inline void		setFirstLineOffset(IlvDim val)
			{
			    _firstLineOffset = val;
			}
    inline IlvDim	getSpaceAfter() const { return _spaceAfter; }
    inline void		setSpaceAfter(IlvDim val) { _spaceAfter = val; }
    inline IlvDim	getSpaceBefore() const { return _spaceBefore; }
    inline void		setSpaceBefore(IlvDim val) { _spaceBefore = val; }
    inline IlvDim	getRightMargin() const { return _rightMargin; }
    inline void		setRightMargin(IlvDim val) { _rightMargin = val; }
    inline IlvDim	getLeftMargin() const { return _leftMargin; }
    inline void		setLeftMargin(IlvDim val) { _leftMargin = val; }
    inline IlvDim	getLineSpacing() const { return _lineSpacing; }
    inline void		setLineSpacing(IlvDim val) { _lineSpacing = val; }
    inline IlvATWrap	getWrap() const { return _wrap; }
    inline void		setWrap(IlvATWrap wrap) { _wrap = wrap; }

    inline
    IlvATAlignment	getGraphicAlignment() const
			{
			    return _graphicAlignment;
			}
    inline void		setGraphicAlignment(IlvATAlignment a)
			{
			    _graphicAlignment = a;
			}

    // Zone management
    inline IlList*	getZones() const { return _zones; }
    void		addZone(IlvATZone* zone);
    void		removeZone(IlvATZone* zone);

    inline IlAny	getUserData() const { return _userData; }
    inline void		setUserData(IlAny userData) { _userData = userData; }
    inline 
    IlvATInteractor*	getInteractor() const { return _inter; }
    inline void		setInteractor(IlvATInteractor* inter)
			{
			    _inter = inter;
			}

    // TabulationMarks
    IlvDim		getPreviousTabulationMark(IlvDim x) const;
    IlvDim		getNextTabulationMark(IlvDim x) const;
    IlBoolean		removeTabulationMark(IlvDim x);
    IlBoolean		removeTabulationMarks(IlvDim start, IlvDim end);
    IlBoolean		insertTabulationMark(IlvDim x);
    void		insertRegularTabulationMarks(IlvDim start,
						     IlvDim end,
						     IlvDim spacing);
    void	       copyPaletteTabulationMarks(const IlvATPalette* atPal);

    // No more documented (replaced by getWrap and setWrap)
    inline IlBoolean	isWordWrap() const
	{ return _wrap ? IlTrue : IlFalse; }
    inline void		setWordWrap(IlvATWrap wrap) { _wrap = wrap; }
    // Not documented
    IlvLink*		getPreviousTabulationMarkLink(IlvDim x) const;
private:
    IlvPalette*		_palette;
    IlvDim		_lineSpacing;
    IlvDim		_rightMargin;
    IlvDim		_leftMargin;
    IlvDim		_firstLineOffset;
    IlvDim		_spaceAfter;
    IlvDim		_spaceBefore;
    IlvDim		_vertOffset;
    IlBoolean		_visible;
    IlBoolean		_drawingBackground;
    IlvATWrap		_wrap;
    IlList*		_zones;
    IlAny		_userData;
    IlvATInteractor*	_inter;
    IlList*		_tabulations;
    IlvATAlignment	_graphicAlignment;
};

#endif /* !__Ilv_Annotext_Palette_H */
