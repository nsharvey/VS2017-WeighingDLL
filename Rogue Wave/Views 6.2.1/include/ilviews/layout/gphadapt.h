// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/gphadapt.h
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
// Declaration of the IlvGrapherAdapter class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Gphadapt_H
#define __Ilv_Layout_Gphadapt_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Layout_Graphmod_H)
#include <ilviews/layout/graphmod.h>
#endif /* __Ilv_Layout_Graphmod_H */

#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif /* __Ilv_Grapher_Grapher_H */

#if !defined(__Ilv_Layout_Filter_H)
#include <ilviews/layout/filter.h>
#endif /* __Ilv_Layout_Filter_H */

class IlvGraphLayout;
class IlvGrapherAdapterObserver;

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGrapherAdapter : public IlvGraphModel
{
public:
    IlvGrapherAdapter(IlvGrapher* grapher);
    virtual ~IlvGrapherAdapter();

    IlvGrapher*		getGrapher() const;

private:
    void		beforeLayoutInternal(IlvGraphLayout* layout,
					     IlBoolean reDraw);
protected:
    void		beforeLayout(IlvGraphLayout* layout, IlBoolean redraw);

private:
    void		afterLayoutInternal(IlvGraphLayout* layout,
					    IlvGraphLayoutReport* layoutReport,
					    IlBoolean reDraw);

protected:
    void		afterLayout(IlvGraphLayout* layout,
				    IlvGraphLayoutReport* layoutReport,
				    IlBoolean reDraw);

    void		beforeAnimationStep();
    void		afterAnimationStep();

public:
    IlvDeclareLazyClassInfo();

private:
    void		resetFlags();

public:
    void		contentsChanged();
    void		viewChanged(IlvManagerViewHook* hook,
				    IlvMgrView* view);
    void		transformerChanged();

    void		moveNode(IlAny node,
				 IlInt x,
				 IlInt y,
				 IlBoolean reDraw);

    void		setFilter(IlvLayoutGraphicFilter* filter);
    IlvLayoutGraphicFilter* getFilter() const;

    void		addLayer(IlvManagerLayer* layer);
    IlBoolean		removeLayer(IlvManagerLayer* layer);
    IlBoolean		removeAllLayers();
    const IlArray&	getLayers() const;

    void		setReferenceTransformer(IlvTransformer* t);
    IlvTransformer*	getReferenceTransformer();

    virtual void	setReferenceView(IlvMgrView* view = 0);
    virtual IlvMgrView*	getReferenceView() const;

    IlvMgrView*		getFirstManagerView() const;

    IlList*		getNodesAndLinks();
    virtual IlList*	getNodes();
    IlList*		getLinks();
    IlList*		getLinksFrom(IlAny node);
    IlUInt		getLinksFromCount(IlAny node);
    IlList*		getLinksTo(IlAny node);
    IlUInt		getLinksToCount(IlAny node);
    IlList*		getLinks(IlAny node);
    IlUInt		getLinksCountOf(IlAny node);
    IlList*		getNeighbors(IlAny node);
    IlAny		getOpposite(IlAny link, IlAny node);
    IlAny		getFrom(IlAny link);
    IlAny		getTo(IlAny link);
    IlBoolean		isNode(IlAny obj);
    IlBoolean		isLink(IlAny obj);
    IlBoolean		isLinkBetween(IlAny node1, IlAny node2);

    void		setProperty(IlAny	nodeOrLink,
				    const char*	key,
				    IlAny	value);
    IlAny		getProperty(IlAny	nodeOrLink,
				    const char*	key);
    IlBoolean		hasProperty(IlAny	nodeOrLink,
				    const char*	key);

    void		boundingBox(IlAny nodeOrLink, IlvRect& rect);
    IlUInt		getLinkWidth(IlAny link);
    IlInt		getLinkPointsCount(IlAny link);
    IlvPoint*		getLinkPoints(IlAny link, IlUInt& count);
    IlvPoint		getLinkPointAt(IlAny link, IlUInt index);
    void		reshapeLink(IlAny link,
				    IlvPoint fromPoint,
				    IlvPoint* points,
				    IlUInt startIndex,
				    IlUInt length,
				    IlvPoint toPoint,
				    IlBoolean reDraw);

private:
    void		reshapeLink(IlAny,
				    IlvPoint,
				    IlvPoint*,
				    IlUInt,
				    IlUInt,
				    IlvPoint,
				    IlBoolean,
				    IlBoolean);
public:
    void		ensureStraightLineLinks(IlvGraphLayout* layout);
    void		ensureReshapeableLinks(IlvGraphLayout* layout);

private:
    IlBoolean		replaceLinks(IlBoolean);

    IlBoolean		needsToBeReplaced(IlAny link,
					  IlBoolean toStraightLine);
    void		copyAttributes(IlvLinkImage* source,
				       IlvLinkImage* target);

public:
    IlSymbol*		getLayerToUseProperty() const;
    IlBoolean		isUsingViewCoordinates() const;
    void		setUsingViewCoordinates(IlBoolean);

    virtual const char*	getMessage(const char* msg) const;

private:
    IlvGrapher*			_grapher;
    IlvTransformer*		_identityTransformer;
    IlvTransformer*		_referenceTransformer;
    IlvMgrView*			_referenceView;
    IlvTransformer*		_referenceViewTransformerCache;
    IlvLayoutGraphicFilter*	_filter;

    IlArray			_vectLinks;
    IlArray			_vectViews;
    IlArray			_vectRedrawMode;

    IlArray			_layers;

    IlUInt			_countStart;
    IlBoolean			_isAnimate;

    IlBoolean			_ensureStraightLineLinksUpToDate;
    IlBoolean			_ensureStraightLineLinkConnectorsUpToDate;
    IlBoolean			_ensureReshapeableLinksUpToDate;
    IlBoolean			_ensureReshapeableLinkConnectorsUpToDate;

    IlSymbol*			_layerToUseProperty;
    IlBoolean			_isUsingViewCoodinates;
    IlList*			_transformerHook;
    IlvGrapherAdapterObserver*	_observer;
};

extern ILVGRLEXPORTEDFUNCTION(const char*)
    IlvGetLayoutMessage(const char* id);
extern ILVGRLEXPORTEDFUNCTION(IlBoolean)
    IlvLayoutLoadDatabase(IlvDisplay* display);

ILVGRLMODULEINIT(l_gphadapt)
#endif /* !__Ilv_Layout_Gphadapt_H */
