// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/indexgr.h
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
// Declaration of the IlvIndexedSet class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Indexgr_H
#define __Ilv_Manager_Indexgr_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

#define IlvMaxObjectsInList 30

class IlvQuadtree;
class IlvManager;
class IlvLastContainsFilter;

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvIndexedSet
{
    friend class IlvManager;

public:
    IlvIndexedSet(IlUShort maxInList = IlvMaxObjectsInList,
		  IlUShort maxInNode = IlvMaxObjectsInList);
    virtual ~IlvIndexedSet();
    // ____________________________________________________________
    inline IlvList*	getList()     const { return _list; }
    inline IlUShort	maxInList()   const { return _maxInList; }
    inline IlUShort	maxInNode()   const { return _maxInNode; }
    inline IlvQuadtree*	getQuadtree() const { return _quadtree; }
    inline void		invalidateBbox()    { _bboxIsInvalid = IlTrue; }
    void		deleteAll(IlBoolean deleteObjects = IlTrue);
    // ____________________________________________________________
    inline IlBoolean	subDivide() const { return _maxInNode != 0xffff; }
    inline void		allowSubdivision(IlBoolean b)
			{
			    if (b)
				setMaxInNode(IlvMaxObjectsInList);
			    else
				setMaxInNode(0xffff);
			}
    void		setMaxInNode(IlUShort m);
    inline IlBoolean	isDivided() const { return _useQuadtree; }
    inline IlUInt	getCardinal() const { return _length;      }
    IlBoolean		removeObject(const IlvGraphic* obj,
				     const IlvRect* = 0);
    void		addObject(const IlvGraphic* obj, const IlvRect* = 0);

    void		quadtreeAdd(const IlvGraphic*,
				    const IlvRect* bbox = 0);
    IlBoolean		quadtreeRemove(const IlvGraphic*,
				       const IlvRect* bbox = 0);
    IlvGraphic*		lastContains(const IlvPoint&       p,
				     const IlvPoint&       tp,
				     const IlvTransformer* t = 0) const;
#if 0
    IlvGraphic*		filteredLastContains(const IlvPoint&  p,
					const IlvPoint&       tp,
					const IlvTransformer* t,
					const IlvLastContainsFilter&) const;
#endif

    void		map(IlvApplyObject f, IlAny arg) const;
    void		map(const IlSymbol* tag,
			    IlvApplyObject  f,
			    IlAny           arg) const;
    void		mapIntersects(const IlvRect&        rect,
				      const IlvRect&        trect,
				      IlvApplyObject        f,
				      IlAny                 arg,
				      const IlvTransformer* t = 0) const;
    inline void		mapIntersects(const IlvRect& rect,
				      IlvApplyObject f,
				      IlAny          arg) const
			{
			    mapIntersects(rect, rect, f, arg);
			}
    void		mapInside(const IlvRect&        rect,
				  const IlvRect&        trect,
				  IlvApplyObject        f,
				  IlAny                 arg,
				  const IlvTransformer* t = 0) const;
    inline void		mapInside(const IlvRect& rect,
				  IlvApplyObject f,
				  IlAny          arg) const
			{
			    mapInside(rect, rect, f, arg);
			}
#if !defined(ILVUSEAPPLYCLASS)
    inline void		apply(IlvApplyObject f, IlAny arg)
			{
			    invalidateBbox(); map(f, arg);
			}
    inline void		apply(const IlSymbol* tag,
			      IlvApplyObject  f,
			      IlAny           arg)
			{
			    invalidateBbox(); map(tag, f, arg);
			}
    inline void		applyIntersects(const IlvRect&        rect,
					const IlvRect&        trect,
					IlvApplyObject        f,
					IlAny                 arg,
					const IlvTransformer* t = 0)
			{
			    invalidateBbox();
			    mapIntersects(rect, trect, f, arg, t);
			}
    inline void		applyIntersects(const IlvRect& rect,
					IlvApplyObject f,
					IlAny          arg)
			{
			    applyIntersects(rect, rect, f, arg);
			}
    inline void		applyInside(const IlvRect&        rect,
				    const IlvRect&        trect,
				    IlvApplyObject        f,
				    IlAny                 arg,
				    const IlvTransformer* t = 0)
			{
			    invalidateBbox();
			    mapInside(rect, trect, f, arg, t);
			}
    inline void		applyInside(const IlvRect& rect,
				    IlvApplyObject f,
				    IlAny          arg)
			{
			    applyInside(rect, rect, f, arg);
			}
#else  /* ILVUSEAPPLYCLASS */
    void		map(IlvApplyHook& hook) const;
    void		map(const IlSymbol* tag, IlvApplyHook& hook) cont;
    void		mapIntersects(const IlvRect&        rect,
				      const IlvRect&        trect,
				      IlvApplyHook&         hook,
				      const IlvTransformer* t = 0) const;
    void		mapInside(const IlvRect&        rect,
				  const IlvRect&        trect,
				  IlvApplyHook&         hook,
				  const IlvTransformer* t = 0) const;
    inline void		apply(IlvApplyHook& hook)
			{
			    invalidateBbox();
			    map(hook);
			}
    inline void		apply(IlvApplyObject f, IlAny arg)
			{
			    IlvApplyObjectHook hook(f, arg);
			    apply(hook);
			}
    inline void		apply(const IlSymbol* tag, IlvApplyHook& hook)
			{
			    invalidateBbox();
			    map(tag, hook);
			}
    inline void		apply(const IlSymbol* tag,
			      IlvApplyObject  f,
			      IlAny           arg)
			{
			    IlvApplyObjectHook hook(f, arg);
			    apply(tag, hook);
			}
    inline void		applyIntersects(const IlvRect&		rect,
					const IlvRect&		trect,
					IlvApplyHook&		hook,
					const IlvTransformer*	t = 0)
			{
			    invalidateBbox();
			    mapIntersects(rect, trect, hook, t);
			}
    inline void		applyIntersects(const IlvRect&        rect,
					const IlvRect&        trect,
					IlvApplyObject        f,
					IlAny                 arg,
					const IlvTransformer* t = 0)
			{
			    IlvApplyObjectHook hook(f, arg);
			    applyIntersects(rect, trect, hook, t);
			}
    inline void		applyIntersects(const IlvRect& rect,
					IlvApplyHook&  hook)
			{
			    applyIntersects(rect, rect, hook);
			}
    inline void		applyIntersects(const IlvRect& rect,
					IlvApplyObject f,
					IlAny          args)
			{
			    applyIntersects(rect, rect, f, args);
			}
    inline void		applyInside(const IlvRect&        rect,
				    const IlvRect&        trect,
				    IlvApplyHook&         hook,
				    const IlvTransformer* t = 0)
			{
			    invalidateBbox();
			    mapInside(rect, trect, hook, t);
			}
    inline void		applyInside(const IlvRect&        rect,
				    const IlvRect&        trect,
				    IlvApplyObject        f,
				    IlAny                 arg,
				    const IlvTransformer* t = 0)
			{
			    IlvApplyObjectHook hook(f, arg);
			    applyInside(rect, trect, hook, t);
			}
    inline void		applyInside(const IlvRect& rect,
				    IlvApplyObject f,
				    IlAny          args)
			{
			    applyInside(rect, rect, f, args);
			}
    inline void		applyInside(const IlvRect& rect, IlvApplyHook& hook)
			{
			    applyInside(rect, rect, hook);
			}
#endif /* ILVUSEAPPLYCLASS */
    IlvGraphic* const*	allIntersects(IlUInt&               count,
				      const IlvRect&        rect,
				      const IlvRect&        trect,
				      const IlvTransformer* t = 0) const;
    IlvGraphic* const*	allInside(IlUInt&               count,
				  const IlvRect&        rect,
				  const IlvRect&        trect,
				  const IlvTransformer* t = 0) const;
    IlvGraphic* const*	allContains(IlUInt&               count,
				    const IlvPoint&       p,
				    const IlvPoint&       tp,
				    const IlvTransformer* t = 0) const;
    IlvGraphic*		firstIntersects(const IlvRegion&      tr,
					const IlvTransformer* t = 0) const;
    void		applyDraw(IlvPort*              dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion*      clip = 0) const;
#if !defined(ILVUSEAPPLYCLASS)
    void		applyToObject(IlvGraphic*    obj,
				      IlvApplyObject f,
				      IlAny          arg);
#else  /* ILVUSEAPPLYCLASS */
    void		applyToObject(IlvGraphic* obj, IlvApplyHook& hook);
    inline void		applyToObject(IlvGraphic*    obj,
				      IlvApplyObject f,
				      IlAny          arg)
			{
			    IlvApplyObjectHook hook(f, arg);
			    applyToObject(obj, hook);
			}
#endif /* ILVUSEAPPLYCLASS */
    virtual void	computeBBox(IlvRect&              rect,
				    const IlvTransformer* t = 0);
    IlvGraphic* const*	getObjects(IlUInt& count) const;

    //== Update the zoomable property of a graphic
    void		setZoomable(const IlvGraphic*, IlBoolean);

    IlvDeclarePropertyListDelegation();

protected:
    void		divide();

    IlvQuadtree*	_quadtree;
    IlvList*		_list;
    IlBoolean		_useQuadtree;
    IlUShort		_maxInList;
    IlUShort		_maxInNode;
    IlUInt		_length;
    IlvRect		_bbox;
    IlBoolean		_bboxIsInvalid;
};

#endif /* !__Ilv_Manager_Indexgr_H */
