// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/select.h
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
// Declaration of the IlvReshapeSelection class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Select_H
#define __Ilv_Graphics_Select_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

class IlvInteractor;

#define IlvDefaultSelectionSize 0
class ILVVWSEXPORTED IlvDrawSelection : public IlvSimpleGraphic
{
public:
    IL_MLK_DECL();
    // ____________________________________________________________
    inline IlvGraphic*	getObject() const { return _object; }
    inline void		setObject(IlvGraphic* object) { _object = object; }
    virtual IlvGraphic*	getHandledObject() const;
    inline IlvDim	getSize() const { return _size; }    
    inline void		setSize(IlvDim size) { _size = size; }

    IlBoolean		isVisible(const IlvPort* dst) const;

    virtual
    IlvDirection	direction(const IlvPoint&       p,
				  const IlvTransformer* t = 0) const;

    virtual IlBoolean	contains(const IlvPoint& p, 
				 const IlvPoint& tp,
				 const IlvTransformer* t) const;
    virtual void	draw(IlvPort*              dst, 
			     const IlvTransformer* t,
			     const IlvRegion*      clip = 0) const;
    virtual void	drawHandle(IlvPort*         dst, 
				   IlUInt           idx,
				   const IlvRect&   rect,
				   const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect&              r,
				    const IlvTransformer* t = 0) const;

    virtual void	computeRegion(IlvRegion&            r,
				      const IlvTransformer* t = 0) const;

    virtual void	applyTransform(const IlvTransformer* t);

    virtual IlBoolean	zoomable() const;
    virtual void	apply(IlvApplyObject f, IlAny a);
    virtual void	applyReferences(IlvApplyObject f, IlAny a);

    virtual void	setPalette(IlvPalette* palette);
    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode m);

    virtual IlUInt	getHandlesCount(const IlvTransformer* t = 0) const = 0;

    virtual IlBoolean	getHandleLocation(IlUInt                idx,
					  IlvPoint&             p,
					  const IlvTransformer* t) const = 0;

    IlBoolean		getHandleRect(IlUInt                idx,
				      IlvRect&              rect,
				      const IlvTransformer* t) const;

    virtual IlUInt	whichHandle(const IlvPoint&       p,
				    const IlvTransformer* t = 0) const;

    virtual
    IlvInteractor*	getSelectionInteractor() const;
    virtual void	write(IlvOutputFile&) const;
    virtual IlvCursor*	getCursor(const IlvPoint&       p,
				  const IlvTransformer* t = 0) const;
    inline
    static IlBoolean	IsVisibleWhenObjectIsInvisible()
			{
			    return _IsVisibleWhenObjectIsInvisible;
			}

    inline static void	SetVisibleWhenObjectIsInvisible(IlBoolean f)
			{
			    _IsVisibleWhenObjectIsInvisible = f;
			}


    static void		SetDefaultPalette(IlvPalette* palette);

    static IlvPalette*	GetDefaultPalette(IlvDisplay* display);

    inline
    static IlvDim	GetDefaultSize() { return _defaultSize; }

    inline static void	SetDefaultSize(IlvDim size) { _defaultSize = size; }

    static void		Finalize();

    DeclareIOConstructors(IlvDrawSelection);

protected:
    void		computeInvertedPalette();

    IlvDim		_size;   // Side dimension of the selection handles
    IlvGraphic*		_object;
    IlvPalette*		_invPalette;

    static IlAList*	_defaultPalettes;
    static IlvDim	_defaultSize;

    IlvDrawSelection(IlvDisplay* display,
		     IlvGraphic* object,
		     IlvDim      size    = 0,
		     IlvPalette* palette = 0);

private:
    static IlBoolean	_IsVisibleWhenObjectIsInvisible;

    IlvDeclareLazyPropClassInfo();
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReshapeSelection : public IlvDrawSelection
{
public:
    IlvReshapeSelection(IlvDisplay* display,
			IlvGraphic* object,
			IlvDim      size    = 0,
			IlvPalette* palette = 0);

    IL_MLK_DECL();

    virtual
    IlvDirection	direction(const IlvPoint&       p,
				  const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&              r,
				    const IlvTransformer* t = 0) const;
    virtual void	computeRegion(IlvRegion&            r,
				      const IlvTransformer* t = 0) const;
    virtual IlUInt	getHandlesCount(const IlvTransformer* t = 0) const;
    virtual IlBoolean	getHandleLocation(IlUInt                idx, 
					  IlvPoint&             p,
					  const IlvTransformer* t) const;
    virtual IlUInt	whichHandle(const IlvPoint&       p,
				    const IlvTransformer* t = 0) const;
    inline static void	SetAutoHideHandles(IlBoolean b)
			{
			    _autoHideHandles = b;
			}
    inline
    static IlBoolean	GetAutoHideHandles() { return _autoHideHandles; }

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvReshapeSelection);

protected:
    static IlBoolean	_autoHideHandles;
};

ILVVWSMODULEINIT(select);

#endif /* !__Ilv_Graphics_Select_H */
