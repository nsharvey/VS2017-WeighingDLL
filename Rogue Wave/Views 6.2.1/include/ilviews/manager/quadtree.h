// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/quadtree.h
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
// Declaration of the IlvQuadtree class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Quadtree_H
#define __Ilv_Manager_Quadtree_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Alloc_H)
#include <ilviews/base/alloc.h>
#endif
#if !defined(__Il_Pool_H)
#include <ilog/pool.h>
#endif

#if !defined(ILVUSEAPPLYCLASS)
typedef void (* IlvQuadtreeIntersect)(IlvGraphic*, IlAny arg, IlBoolean);
#endif /* !ILVUSEAPPLYCLASS */

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvQuadtree
{
public:
    IlvQuadtree(IlUInt max, IlvRect* initial = 0);
    ~IlvQuadtree();
    ILV_MLK_DECL();
    // ____________________________________________________________
    inline void		bbox(IlvRect& rect) const { rect = _bbox;       }
    inline IlUInt	objPerNode()        const { return _maxinlist;  }
    inline IlUInt	getCardinal()       const { return _nbelements; }
    inline IlUInt	cardinal()          const { return _nbelements; }
    inline IlBoolean	isDivided()         const { return _divided;    }
    void		add(const IlvGraphic*, const IlvRect* bbox = 0);
    IlBoolean		remove(const IlvGraphic*, const IlvRect* bbox = 0);

#if !defined(ILVUSEAPPLYCLASS)
    void		apply(IlvApplyObject f, IlAny args);
    void		apply(const IlSymbol* tag,
			      IlvApplyObject  f,
			      IlAny            args);
    void		applyInside(const IlvRect&        rect,
				    const IlvRect&        trect,
				    IlvApplyObject        f,
				    IlAny                 args,
				    const IlvTransformer* t = 0);
    void		applyIntersect(const IlvRect&        rect,
				       const IlvRect&        trect,
				       IlvQuadtreeIntersect  f,
				       IlAny                 args,
				       const IlvTransformer* t = 0);
    void		applyInside(const IlvRegion& rect,
				    IlvApplyObject   f,
				    IlAny            args);
    void		applyIntersect(const IlvRegion&      rect,
				       const IlvRegion&      trect,
				       IlvQuadtreeIntersect  f,
				       IlAny                 args,
				       const IlvTransformer* t = 0);
    inline void		applyIntersect(const IlvRegion&     rect,
				       IlvQuadtreeIntersect f,
				       IlAny                args)
			{
			    applyIntersect(rect, rect, f, args);
			}
#else  /* ILVUSEAPPLYCLASS */
    void		apply(IlvApplyHook& hook);
    void		apply(const IlSymbol* tag, IlvApplyHook& hook);
    void		applyInside(const IlvRect&        rect,
				    const IlvRect&        trect,
				    IlvApplyHook&         hook,
				    const IlvTransformer* t = 0);
    void		applyIntersect(const IlvRect&        rect,
				       const IlvRect&        trect,
				       IlvApplyHook&         hook,
				       const IlvTransformer* t = 0);
    void		applyInside(const IlvRegion& rect, IlvApplyHook&);
    void		applyIntersect(const IlvRegion&      rect,
				       const IlvRegion&      trect,
				       IlvApplyHook&         hook,
				       const IlvTransformer* t = 0);
    inline void		applyIntersect(const IlvRegion& rect,
				       IlvApplyHook&    hook)
			{
			    applyIntersect(rect, rect, hook);
			}
#endif /* ILVUSEAPPLYCLASS */
    IlvGraphic*		firstContains(const IlvPoint&       p,
				      const IlvPoint&       tp,
				      const IlvTransformer* t = 0) const;
    inline IlvGraphic*	firstContains(const IlvPoint& p) const
			{
			    return  firstContains(p, p);
			}
    IlvGraphic* const*	allContains(IlUInt&               count,
				    const IlvPoint&       p,
				    const IlvPoint&       tp,
				    const IlvTransformer* t = 0) const;
    inline IlvGraphic* const*	allContains(IlUInt& count, IlvPoint& p) const
				{
				    return allContains(count, p, p);
				}
    IlvGraphic* const*	allInside(const IlvRect&        rect,
				  const IlvRect&        trect,
				  IlUInt&               count,
				  const IlvTransformer* t = 0) const;
    IlvGraphic* const*	allIntersects(const IlvRect&        rect,
				      const IlvRect&        trect,
				      IlUInt&               count,
				      const IlvTransformer* t = 0) const;
    IlvGraphic*		firstIntersects(const IlvRegion&      trect,
					const IlvTransformer* t = 0) const;

    void		deleteAll();
    void		deleteNodes();
    void		allObjects(IlUInt&            count,
				   IlvGraphic* const* objects) const;

private:
    IlvQuadtree*	_topL;
    IlvQuadtree*	_topR;
    IlvQuadtree*	_bottomL;
    IlvQuadtree*	_bottomR;
    IlvLink*		_elements;
    IlvLink*		_last;
    IlUInt		_nbelements;
    IlBoolean		_divided;
    IlUInt		_maxinlist;
    IlvRect		_bbox;

    void		listAppend(const IlvGraphic*);
    IlBoolean		listRemove(const IlvGraphic*);
    void		deleteList(IlvLink*);

    IlvQuadtree()
    : _topL(0),
      _topR(0),
      _bottomL(0),
      _bottomR(0),
      _elements(0),
      _last(0),
      _nbelements(0),
      _divided(IlFalse),
      _maxinlist(30),
      _bbox() {}
    // ____________________________________________________________
    void		nodeAdd(const IlvGraphic*, const IlvRect&);
    IlBoolean		nodeRemove(const IlvGraphic*, const IlvRect&);
    IlUInt		findPos(const IlvRect&) const;
    IlUInt		findPos(const IlvPoint&) const;
    void		growToPoint(const IlvPoint&);
    void		growToRect(const IlvRect&);
    void		nodeAddList(IlvLink*);
    void		rebuildFrom(IlvQuadtree*);
    IlBoolean		nodeInsideP(const IlvGraphic*, const IlvRect&) const;
#if !defined(ILVUSEAPPLYCLASS)
    void		applyIn(IlvQuadtreeIntersect, IlAny);
#else  /* ILVUSEAPPLYCLASS */
    void		applyIn(IlvApplyHook&);
#endif /* ILVUSEAPPLYCLASS */
    void		nodeAllContains(IlMemoryPoolBlock*&,
					const IlvPoint&,
					IlUInt&,
					const IlvPoint&,
					const IlvTransformer* t = 0) const;
    void		nodeAllIntersects(IlMemoryPoolBlock*&,
					  const IlvRect&,
					  const IlvRect&,
					  IlUInt&,
					  const IlvTransformer* t) const;
    void		nodeAllInside(IlMemoryPoolBlock*&,
				      const IlvRect&,
				      const IlvRect&,
				      IlUInt&,
				      const IlvTransformer* t) const;
    void		nodeAllObjects(IlUInt&            count,
				       IlvGraphic* const* objects) const;
};

extern "C" {
ILVMGREXPORTEDFUNCTION(void)       IlvSetOptimizeMode(IlBoolean);
ILVMGREXPORTEDFUNCTION(IlBoolean) IlvGetOptimizeMode();
}

#endif /* !__Ilv_Manager_Quadtree_H */
