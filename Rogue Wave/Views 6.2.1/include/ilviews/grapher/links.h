// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/links.h
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
#ifndef __Ilv_Grapher_Links_H
#define __Ilv_Grapher_Links_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvLinkImage : public IlvSimpleGraphic
{
public:
    IlvLinkImage(IlvDisplay* display,
		 IlBoolean  oriented,
		 IlvGraphic* from,
		 IlvGraphic* to,
		 IlvPalette* palette = 0)
    : IlvSimpleGraphic(display, palette),
      _oriented(oriented),
      _from(from),
      _to(to)
    {}

    inline IlvGraphic*	getFrom() const { return _from; }
    void		setFrom(IlvGraphic* f);
    inline IlvGraphic*	getTo() const { return _to; }
    void		setTo(IlvGraphic* t);
    inline IlBoolean	isOriented() const { return _oriented; }
    inline IlBoolean	getOriented() const { return isOriented(); }// Obsolete

    inline void		setOriented(IlBoolean oriented)
			{
			    _oriented = oriented;
			}
    virtual IlvPoint*	getLinkPoints(IlUInt& nPoints,
				      const IlvTransformer* t = 0) const;
    virtual void	computePoints(IlvPoint& src,
				      IlvPoint& dst,
				      const IlvTransformer* t = 0) const;

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	applyReferences(IlvApplyObject f, IlAny a);

    virtual IlBoolean	zoomable() const;


    inline void		_setFrom(IlvGraphic* from) { _from = from; }
    inline void		_setTo(IlvGraphic* to)     { _to = to; }

    DeclareGraphicAccessors();
    DeclareInterface(Shape);
    DeclareInterface(Selection);
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvLinkImage);

    static IlSymbol*	FromValue();
    static IlSymbol*	ToValue();
    static IlSymbol*	OrientedValue();

    static void		ApplySetOriented(IlvGraphic*, IlAny);

protected:
    IlBoolean		_oriented;
    IlvGraphic*		_from;
    IlvGraphic*		_to;

    virtual IlBoolean	isDirect(const IlvTransformer* t = 0) const;
    virtual void	computeArrowPoints(IlUInt count,
					   const IlvPoint* linkPts,
					   IlvPoint* arrowPts,
					   const IlvTransformer* t) const;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvLinkLabel : public IlvLinkImage
{
public:
    IlvLinkLabel(IlvDisplay* display,
		 const char* label,
		 IlBoolean  oriented,
		 IlvGraphic* from,
		 IlvGraphic* to,
		 IlvPalette* palette = 0);
    ~IlvLinkLabel();

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    inline const char*	getLabel() const { return _label; }
    void		setLabel(const char* label);

    virtual IlBoolean	zoomable() const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvLinkLabel);

protected:
    char*		_label;
    void		labelBBox(IlvRect& bbox, IlvPoint&, IlvPoint&) const;
};

// --------------------------------------------------------------------------
typedef IlvPosition IlvLinkOrientation;
#define IlvHorizontalLink IlvHorizontal
#define IlvVerticalLink   IlvVertical

class ILVGRAPHEXPORTED IlvOneLinkImage : public IlvLinkImage
{
public:
    IlvOneLinkImage(IlvDisplay*        display,
		    IlvLinkOrientation orientation,
		    IlBoolean         oriented,
		    IlvGraphic*        from,
		    IlvGraphic*        to,
		    IlvPalette*        palette = 0)
    : IlvLinkImage(display, oriented, from, to, palette),
      _orientation(orientation)
    {}

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    virtual IlvPoint*	getLinkPoints(IlUInt&	           nPoints,
				      const IlvTransformer* t = 0) const;
    virtual void	getPoints(IlvPoint*,
				  int&,
				  const IlvTransformer* = 0) const;
    inline void		setOrientation(IlvLinkOrientation orient)
			{
			    _orientation = orient;
			}
    inline IlvLinkOrientation	getOrientation() const { return _orientation; }

    DeclareInterface(Selection);
    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvOneLinkImage);

    static IlSymbol*	_orientationValue;

protected:
    IlvLinkOrientation	_orientation;

    void		compute3Points(IlvPoint*             points,
				       const IlvTransformer* t = 0) const;

    static void		ApplyChangeOrientation(IlvGraphic*, IlAny arg);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvOneSplineLinkImage : public IlvOneLinkImage
{
public:

    IlvOneSplineLinkImage(IlvDisplay*        display,
			  IlvLinkOrientation orientation,
			  IlBoolean         oriented,
			  IlvGraphic*        from,
			  IlvGraphic*        to,
			  IlvPalette*        palette = 0)
    : IlvOneLinkImage(display, orientation, oriented, from, to, palette),
      _scaleWidth(0),
      _scaleHeight(0)
    {}
    IlvOneSplineLinkImage(IlvDisplay*	     display,
			  IlvLinkOrientation orientation,
			  IlBoolean          oriented,
			  IlFloat            scaleWidth,
			  IlFloat            scaleHeight,
			  IlvGraphic*        from,
			  IlvGraphic*        to,
			  IlvPalette*        palette = 0)
    : IlvOneLinkImage(display, orientation, oriented, from, to, palette),
      _scaleWidth(scaleWidth),
      _scaleHeight(scaleHeight)
    {}

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;

    virtual IlvPoint*	getLinkPoints(IlUInt&              nPoints,
				      const IlvTransformer* t = 0) const;
    void		setControlPoint(const IlvPoint& p,
					const IlvTransformer* t = 0);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvOneSplineLinkImage);

protected:
    IlFloat		_scaleWidth;
    IlFloat		_scaleHeight;
    void		computeSplinePoints(IlvPoint* points,
					    const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvDoubleLinkImage : public IlvLinkImage
{
public:
    IlvDoubleLinkImage(IlvDisplay* display,
		       IlBoolean  oriented,
		       IlvGraphic* from,
		       IlvGraphic* to,
		       IlvPalette* palette = 0)
    : IlvLinkImage(display, oriented, from, to, palette)
    {
	setFixedOrientation(IlFalse);
    }

    IlvDoubleLinkImage(IlvDisplay* display,
		       IlvLinkOrientation orientation,
		       IlBoolean  oriented,
		       IlvGraphic* from,
		       IlvGraphic* to,
		       IlvPalette* palette = 0)
    : IlvLinkImage(display, oriented, from, to, palette)
    {
	setFixedOrientation(IlTrue,orientation);
    }

    /*
    virtual IlBoolean contains(const IlvPoint&,
				const IlvPoint&,
				const IlvTransformer* t = 0) const;
				*/
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;

    virtual IlvPoint*	getLinkPoints(IlUInt&              nPoints,
				      const IlvTransformer* t = 0) const;

    void		setFixedOrientation(IlBoolean fixed,
					    IlvLinkOrientation
						orient = IlvHorizontalLink);


    IlBoolean getFixedOrientation(IlvLinkOrientation& orient) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvDoubleLinkImage);

protected:
    IlvLinkOrientation	_orientation;
    virtual void	computeArrowPoints(IlUInt count,
					   const IlvPoint* linkPts,
					   IlvPoint* arrowPts,
					   const IlvTransformer* t) const;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvNDoubleLinkImage : public IlvLinkImage
{
public:
    IlvNDoubleLinkImage(IlvDisplay* display,
			IlBoolean  oriented,
			IlvGraphic* from,
			IlvGraphic* to,
			IlvPalette* palette = 0)
    : IlvLinkImage(display, oriented, from, to, palette)
    {}

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual IlvPoint*	getLinkPoints(IlUInt&              nPoints,
				      const IlvTransformer* t = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvNDoubleLinkImage);

protected:
    virtual IlBoolean	isDirect(const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvDoubleSplineLinkImage : public IlvDoubleLinkImage
{
public:
    IlvDoubleSplineLinkImage(IlvDisplay* display,
			     IlBoolean  oriented,
			     IlvGraphic* from,
			     IlvGraphic* to,
			     IlvPalette* palette = 0)
    : IlvDoubleLinkImage(display, oriented, from, to, palette)
    {}

    IlvDoubleSplineLinkImage(IlvDisplay* display,
			     IlvLinkOrientation orientation,
			     IlBoolean  oriented,
			     IlvGraphic* from,
			     IlvGraphic* to,			     
			     IlvPalette* palette = 0)
    : IlvDoubleLinkImage(display, orientation, oriented, from, to, palette)
    {}

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvDoubleSplineLinkImage);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvArcLinkImage : public IlvLinkImage
{
public:
    IlvArcLinkImage(IlvDisplay* display,
		    IlBoolean  oriented,
		    IlvGraphic* from, 
		    IlvGraphic* to,
		    IlDouble offsetRatio=.20,
		    IlvPos fixedOffset = 0,
		    IlvPalette* palette=0)
    : IlvLinkImage(display, oriented,from,to,palette) ,
      _offsetRatio(offsetRatio),
      _fixedOffset(fixedOffset) {}


    inline IlBoolean	isOffsetFixed() const { return (_offsetRatio==0); }

    inline void		setFixedOffset(IlvPos offset) 
			{
			    _fixedOffset = offset;
			    setOffsetRatio(0);
			}

    inline IlvPos	getFixedOffSet() const { return _fixedOffset; }

    inline IlDouble	getOffsetRatio() const { return _offsetRatio; }

    inline void		setOffsetRatio(IlDouble ratio)
			{
			    _offsetRatio = ratio;
			}

    virtual IlvPos	getArcOffset(const IlvPoint& from,
				     const IlvPoint& to ) const;

    virtual IlBoolean	contains(const IlvPoint& p, const IlvPoint&,
				 const IlvTransformer* t = 0) const;

    virtual void	draw(IlvPort* dst, const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    virtual void	computePoints(IlvPoint& src,
				      IlvPoint& dst,
				      const IlvTransformer* t = 0) const;

    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;

    virtual IlvPoint*	getLinkPoints(IlUInt& nPoints,
				      const IlvTransformer* t = 0) const;

    DeclareInterface(Selection);
    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvArcLinkImage);

    static IlSymbol*	_fixedOffsetValue;
    static IlSymbol*	_offsetRatioValue;

protected:
    static void		ApplyChangeFixedOffset(IlvGraphic*, IlAny arg);
    static void		ApplyChangeOffsetRatio(IlvGraphic*, IlAny arg);

    IlDouble		_offsetRatio;
    IlvPos		_fixedOffset;

private:
    IlvPoint*		getSplinePoints(const IlvTransformer* t) const;
};

ILVGRAPHMODULEINIT(glink);
ILVGRAPHMODULEINIT(nglink);
ILVGRAPHMODULEINIT(glablink);
ILVGRAPHMODULEINIT(gonelink);
ILVGRAPHMODULEINIT(gtwolink);
ILVGRAPHMODULEINIT(garclink);

#endif /* !__Ilv_Grapher_Links_H */
