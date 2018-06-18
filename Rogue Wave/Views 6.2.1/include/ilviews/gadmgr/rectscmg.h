// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/rectscmg.h
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
// Declaration of the IlvSCManagerRectangle class
// Defined in library ilvgadmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Rectscmg_H
#define __Ilv_Gadmgr_Rectscmg_H

#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
#if !defined(__Ilv_Gadmgr_Macros_H)
#include <ilviews/gadmgr/macros.h>
#endif
#if !defined(__Ilv_Manager_Rectangl_H)
#include <ilviews/manager/rectangl.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif

class IlvSCManagerRectangle;
// --------------------------------------------------------------------------
// Hook class for the SCManagerRectangle
class ILVGDTMGREXPORTED IlvSCMgrRectScrollViewHook : public IlvManagerViewHook
{
public:
    IlvSCMgrRectScrollViewHook(IlvSCManagerRectangle* scmgr);
    ~IlvSCMgrRectScrollViewHook();

    inline
    IlvSCManagerRectangle* getSCManagerRectangle() const
			{
			    return _scmgrrect;
			}
    virtual void	transformerChanged(const IlvTransformer*,
					   const IlvTransformer*);
    virtual void	viewResized();
    virtual void	contentsChanged();
    void		adjustScrollBars();

private:
    IlvSCManagerRectangle*	_scmgrrect;
};

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvSCManagerRectangle
    : public IlvManagerRectangle,
      public IlvScrollableInterface
{
public:
    IlvSCManagerRectangle(IlvDisplay*    display,
			  const IlvRect& rect,
			  IlvPalette*    palette = 0);
    ~IlvSCManagerRectangle();

    IlvScrollBar*	getVerticalScrollBar()   const;
    IlvScrollBar*	getHorizontalScrollBar() const;
    IlvScrollBar*	getScrollBar(IlvOrientation whichSB) const;
    void		showScrollBar(IlvOrientation which);
    void		hideScrollBar(IlvOrientation which);
    void		moveScrollBar(IlvOrientation which,
				      IlvPosition    where);
    void		getScrollBarBBox(IlvRect&       bbox,
					 const IlvRect& rect,
					 IlvOrientation whichSB) const;
    IlvPosition		whereIsScrollBar(IlvOrientation which) const;
    virtual void	boundingBox(IlvRect&              rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    void		computeBBox(IlvRect&              v,
				    IlvRect&              h,
				    const IlvTransformer* t = 0);
    virtual
    IlvSCMgrRectScrollViewHook*	createScrollHook();
    inline
    IlvSCMgrRectScrollViewHook*	getScrollHook() const { return _hook; }
    virtual const char*	getDefaultInteractor() const;
    virtual void	setView(IlvView*);
    virtual void	setManager(IlvManager* mgr, IlBoolean owner = IlTrue);
    void		adjustView();
    virtual void	handleInput(IlvEvent&);
    virtual void	computeContentsBBox(IlvRect& bbox) const;
    virtual void	setHolder(IlvGadgetHolder* holder);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setPalette(IlvPalette*);
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	scrollableSize(IlvDim& w, IlvDim& h) const;
    virtual void	visibleSize(IlvDim& w, IlvDim& h) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvSCManagerRectangle);
    DeclareGraphicAccessors();

    static IlSymbol*	_verticalScrollbarValue;
    static IlSymbol*	_horizontalScrollbarValue;
    static IlSymbol*	_verticalScrollbarPositionValue;
    static IlSymbol*	_horizontalScrollbarPositionValue;

protected:
    void		iShowScrollBar(IlvOrientation whichSB);
    void		iHideScrollBar(IlvOrientation whichSB);
    void		initHook();
    void		removeHook();
    void		recomputeBBoxes();
    virtual
    IlvScrollBar*	createScrollBar(const IlvRect&,
					IlvDirection,
					IlUShort,
					IlvPalette*);
    virtual void	drawScrollBar(IlvPort*              dst,
				      IlvDirection          dir,
				      const IlvTransformer* t = 0,
				      const IlvRegion*      clip=0) const;
    virtual
    IlvScrollableInterfaceStruct&	getScrollBarStruct() const;
    virtual void	adjustScrollBarValue(IlvScrollBar* sb,
					     IlvDirection dir);
    virtual void	adjustFromScrollBar(const IlvScrollBar*sb,
					    IlvDirection dir);

    IlvScrollableInterfaceStruct	_scrollBars;
    IlvSCMgrRectScrollViewHook*		_hook;
    IlvScrollBar*			_vScrollBar;
    IlvScrollBar*			_hScrollBar;
    IlUShort				_sbFlags;
    IlvPos				_previousx;
    IlvPos				_previousy;
};

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvSCManagerInteractor : public IlvInteractor
{
public:
    IlvSCManagerInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic* g, 
				    IlvEvent& event,
				    const IlvTransformer* t = 0);
    virtual IlBoolean	accept(const IlvGraphic*) const;

    DeclareLazyInteractorTypeInfoRO(IlvSCManagerInteractor);

protected:
    IlBoolean		_inHSB;
    IlBoolean		_inVSB;
};

ILVGDTMGRMODULEINIT(rectscmg);
#endif /* __Ilv_Gadmgr_Rectscmg_H */
