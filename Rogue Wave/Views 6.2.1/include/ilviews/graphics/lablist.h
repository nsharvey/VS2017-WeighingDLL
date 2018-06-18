// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/lablist.h
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
// Declaration of the IlvListLabel class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Lablist_H
#define __Ilv_Graphics_Lablist_H

#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvListLabel : public IlvSimpleGraphic
{
public:
    IlvListLabel(IlvDisplay*        display,
		 const IlvPoint&    position,
		 IlUInt             count,
		 const char* const* labels,
		 IlvPalette*        palette = 0);
    IlvListLabel(IlvDisplay*     display,
		 IlUInt          count,
		 const IlvPoint& position ...);
    virtual ~IlvListLabel();

    inline IlvPosition	align(IlvPosition align)
	{
	    _align = align;
	    return align;
	}
    inline IlvPosition	align() const { return _align;}
    void		setText(const char* text);
    const char*		getText() const;
    inline IlUInt	getCardinal() const { return _count;  }
    inline IlUInt	count() const { return getCardinal();  }
    virtual IlBoolean	zoomable() const;
    void		setLabel(const char* label, IlUInt index);
    inline const char*	getLabel(IlUInt index) const
	{ return _labels[index]; }
    const char* const*	getLabels(IlUInt& count) const;
    void		setSpacing(IlvDeltaPos spacing);
    inline IlvDeltaPos	getSpacing() const { return _spacing; }
    void		setLabels(const char* const* labels,
				  IlUInt             count,
				  IlBoolean          copy = IlTrue);
    void		removeLabel(IlUInt index);
    void		addLabel(const char* label);
    virtual void	setFont(IlvFont*);
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    IlInt		whichContains(const IlvPoint&       p,
				      const IlvTransformer* t = 0) const;
    IlBoolean		contains(const IlvPoint&, const IlvPoint&,
				 const IlvTransformer* = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion*      = 0) const;
    IlBoolean		intersects(const IlvRegion&,
				   const IlvTransformer* = 0) const;
    IlBoolean		inside(const IlvRegion&,
			       const IlvTransformer* = 0) const;
    virtual void	print(ILVSTDPREF ostream&, int = 0) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvListLabel);

protected:
    IlvPoint		_position;
    char**		_labels;
    IlUInt		_count;
    IlvDeltaPos		_spacing;
    IlvDim		_width;
    IlvDim		_height;
    IlvPosition		_align;

    void		computeSize();
};

ILVVWSMODULEINIT(g0lablist);
#endif /* !__Ilv_Graphics_Lablist_H */
