// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/graphmod.h
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
// Declaration of the IlvGraphModel class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Graphmod_H
#define __Ilv_Layout_Graphmod_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Base_Link_H)
#include <ilviews/base/link.h>
#endif /* __Ilv_Base_Link_H */

#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif /* __Ilv_Base_Hash_H */

#if !defined(__Ilv_Base_Geometry_H)
#include <ilviews/base/geometry.h>
#endif /* __Ilv_Base_Geometry_H */

#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif /* __Ilv_Base_String_H */

#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif /* __Ilv_Base_Clssinfo_H */

class IlvGraphLayout;
class IlvGraphLayoutReport;
class IlvGraphModelEvent;
class IlvGraphModelListener;
class IlvGraphModelEvent;

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphModel : public IlvLayoutValueInterface
{
public:
    IlvGraphModel();
    virtual ~IlvGraphModel();

    const char*		getUniqueName(const char* = 0);

    virtual void	beforeLayoutInternal(IlvGraphLayout* layout,
					     IlBoolean redraw);
    virtual void	beforeLayout(IlvGraphLayout* layout,
				     IlBoolean redraw);
    virtual void	afterLayoutInternal(IlvGraphLayout* layout,
					    IlvGraphLayoutReport* report,
					    IlBoolean redraw);
    virtual void	afterLayout(IlvGraphLayout* layout,
				    IlvGraphLayoutReport* report,
				    IlBoolean redraw);
    virtual void	beforeAnimationStep();
    virtual void	afterAnimationStep();

    virtual IlList*	getNodesAndLinks();
    virtual IlList*	getNodes() = 0;
    virtual IlUInt	getNodesCount();
    virtual IlList*	getLinks() = 0;
    virtual IlUInt	getLinksCount();
    virtual IlList*	getLinksFrom(IlAny node) = 0;
    virtual IlUInt	getLinksFromCount(IlAny node);
    virtual IlList*	getLinksTo(IlAny node) = 0;
    virtual IlUInt	getLinksToCount(IlAny node);
    virtual IlList*	getLinks(IlAny node);
    virtual IlUInt	getLinksCountOf(IlAny node);
    virtual IlList*	getNeighbors(IlAny node);

    virtual IlUInt	getNodeDegree(IlAny node);
    virtual IlAny	getOpposite(IlAny link, IlAny node);
    virtual IlAny	getFrom(IlAny link) = 0;
    virtual IlAny	getTo(IlAny link) = 0;
    virtual IlBoolean	isNode(IlAny node) = 0;
    virtual IlBoolean	isLink(IlAny link) = 0;
    virtual IlBoolean	isLinkBetween(IlAny node1, IlAny node2);

    virtual void	setProperty(IlAny nodeOrLink,
				    const char* key,
				    IlAny value);
    virtual IlAny	getProperty(IlAny nodeOrLink, const char* key);
    virtual IlBoolean	hasProperty(IlAny nodeOrLink, const char* key);

    void		addGraphModelListener(const IlvGraphModelListener*);
    void		removeGraphModelListener(const IlvGraphModelListener*);

    void		structureChanged(IlBoolean);
    void		geometryChanged(IlBoolean);
    void		adjustmentEnd();

protected:
    void		fireGraphModelEvent(const IlvGraphModelEvent&);

public:
    virtual void	moveNode(IlAny node,
				 IlInt x,
				 IlInt y,
				 IlBoolean redraw) = 0;
    virtual void	boundingBox(IlAny nodeOrLink, IlvRect& rect) = 0;

    virtual IlInt	getLinkPointsCount(IlAny link) = 0;
    virtual IlvPoint*	getLinkPoints(IlAny link, IlUInt& count) = 0;
    virtual IlvPoint	getLinkPointAt(IlAny link, IlUInt index);

    virtual void	ensureStraightLineLinks(IlvGraphLayout* layout);
    virtual void	ensureReshapeableLinks(IlvGraphLayout* layout);
    virtual void	reshapeLink(IlAny link,
				    IlvPoint fromPoint,
				    IlvPoint* points,
				    IlUInt startIndex,
				    IlUInt length,
				    IlvPoint toPoint,
				    IlBoolean redraw) = 0;

    virtual IlUInt	getLinkWidth(IlAny);

    virtual const char*	getMessage(const char* key) const = 0;

    IlBoolean		isEmpty();

    IlvDeclareLazyClassInfo();

private:
    void		initPropertiesNames();

    static IlInt	_uniqueIdCounter;
    IlInt		_uniqueId;
    IlHashTable*	_properties;
    IlList		_listenerList;
    IlvGraphModelEvent*	_event;
};

ILVGRLMODULEINIT(l_graphmod)
#endif /* !__Ilv_Layout_Graphmod_H */
