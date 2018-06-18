// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/orthlink.h
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
// Declaration of the IlvOrthogonalLinkLayout class
// Declaration of the IlvNodeSideFilter class
// Defined in library ilvorthlink
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Orthlink_H
#define __Ilv_Layout_Orthlink_H

#if !defined(__Ilv_Layout_Gphlayout_H)
#include <ilviews/layout/gphlayout.h>
#endif /* __Ilv_Layout_Gphlayout_H */

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvorthlink.lib")
#endif

#if defined(ILVORTHLNKLIB)
#define ILVORTHLNKEXPORTED ILVBASEEXPORTED
#define ILVORTHLNKEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVORTHLNKEXPORTEDVAR(type)	ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVORTHLNKLIB */
#define ILVORTHLNKEXPORTED ILVBASEIMPORTED
#define ILVORTHLNKEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVORTHLNKEXPORTEDVAR(type)	ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVORTHLNKLIB */

#define ILVORTHLNKMODULEINIT(m)	IL_MODULEINIT(m, ILVORTHLNKEXPORTED);

class IlvGenericIndexedSet;
class IlvIncidentLinksSorter;
class IlvNodeSideFilter;
class IlvNodeSide;
class IlvTopSide;
class IlvBottomSide;
class IlvLeftSide;
class IlvRightSide;
class IlvNodeBoxInterface;
class IlvIntersectApplyObject;
class IlvLinkShapeProducer;
class IlvNodeData;
class IlvLinkData;
class IlvLinkShape;
class IlvLinkShapeType;

enum IlvOrthogonalLinkBundleMode {
    IlvOrthogonalLinkNoBundle = 1,
    IlvOrthogonalLinkFirstLastSegment = 2,
    IlvOrthogonalLinkImprovedFirstLastSegment = 3
};

class ILVORTHLNKEXPORTED IlvOrthogonalLinkLayout : public IlvGraphLayout
{
public:
    IlvOrthogonalLinkLayout();
    ~IlvOrthogonalLinkLayout();

    void		detach();

    void		cleanObjectProperties(IlAny nodeOrLink);

    IlvIncidentLinksSorter* getLinkSorter() const;

private:
    IlvIncidentLinksSorter*	_linkSorter;
    IlvNodeSideFilter*		_nodeSideFilter;
    IlvNodeBoxInterface*	_connectionRect;

    IlArray		_vectNodes;
    IlArray		_vectLinks;
    IlArray		_vectOtherLinks;

    IlvRect		_tempRect;

    IlString		_nodeProperty;
    IlString		_linkProperty;

    IlvGenericIndexedSet* _quadTree;
    IlvIntersectApplyObject* _intersectApplyObject;

    IlvLayoutLinkStyle	_linkStyle;
    IlvOrthogonalLinkBundleMode	_linkBundlesMode;
    IlUInt		_minFinalSegment;
    IlUInt		_linkOffset;
    IlUInt		_linkNodePenalty;
    IlUInt		_linkLinkPenalty;
    IlUInt		_numberOfIterations;
    IlBoolean		_sameShapeForMultipleLinks;
    IlBoolean		_autoLayout;

    // temporary storage. Don't directly use _linkOffset, _minFinalSegment
    // and _bundleMode, because we need to pass via getLinkOffset() etc.
    IlUInt		_linkOffsetVal;
    IlUInt		_minFinalSegmentVal;
    IlvOrthogonalLinkBundleMode	_bundleModeVal;

    IlBoolean		_linkConnectorsUpToDate;

    // the link shape producer
    IlvLinkShapeProducer* _shapeProducer;

    IlvTopSide*		_topSide;
    IlvBottomSide*	_bottomSide;
    IlvLeftSide*	_leftSide;
    IlvRightSide*	_rightSide;

    IlBoolean		_isAnimate;

    // a flag that tells us if we discoverd multiple links
    IlBoolean		_multipleLinksFound;

protected:
    virtual void	layout();

public:
    void		 setLinkConnectionRectangle(IlvNodeBoxInterface*);
    IlvNodeBoxInterface* getLinkConnectionRectangle() const;

    void		setNodeSideFilter(IlvNodeSideFilter*);
    IlvNodeSideFilter*	getNodeSideFilter() const;

    IlBoolean		isLayoutTimeElapsedPackage() const;

private:
    IlvLinkShapeProducer* makeLinkShapeProducer();

    IlvIncidentLinksSorter* makeIncidentLinksSorter();

    IlBoolean		initializeData(IlvGraphModel* graphModel);

    void		searchMultipleLinks(IlvGraphModel* graphModel,
					    IlvLinkData* linkData);
    void		searchMultipleLinks(IlvGraphModel* graphModel,
					    IlList* links,
					    IlvLinkData* linkData,
					    IlBoolean reversed);

    IlvLinkData*	initializeLinkShape(IlvGraphModel* graphModel,
					    IlAny link,
					    IlBoolean fixed);
    IlArray*		computeIntersectingObjects(IlvGraphModel* graphModel,
						   IlvLinkData* linkData);
    IlBoolean		initialShapeLink(IlvGraphModel* graphModel,
					 IlvLinkData* linkData);

public:
    // package because called in IlvLinkLayoutBestNeighborsOptimization
    IlBoolean		reshapeLink(IlvGraphModel* graphModel,
				    IlvLinkData* linkData,
				    IlvLinkShapeType* shapeType,
				    IlBoolean isLinkBundlesRequired);

public:
    IlUInt		getAllowedLinkShapeTypesCount(IlvGraphModel* model,
						      IlvLinkData* linkData);
    IlvLinkShape*	getLinkShape(IlvGraphModel*,
				     IlvLinkData*);
    IlvLinkShapeType*	getLinkShapeType(IlvGraphModel* graphModel,
					 IlvLinkData* prop,
					 IlUInt index);

private:
    IlBoolean		finalShapeLink(IlvGraphModel* graphModel,
				       IlBoolean removeProperties,
				       IlBoolean slaveExpansion,
				       IlBoolean redraw);

public:
    void		finalShapeLink(IlvGraphModel* graphModel,
				       IlvLinkData* linkData,
				       IlBoolean slaveExpansion,
				       IlBoolean redraw);

    IlFloat		getLinkCost(IlvGraphModel* graphModel,
				    IlvLinkData* linkData,
				    IlBoolean global);
private:
    IlFloat		getLinkNodeCost(IlvGraphModel* graphModel,
					IlvLinkData* linkData,
					IlvNodeData* nodeData);
    IlFloat		getLinkCost(IlvGraphModel* graphModel,
				    IlvLinkData* linkData1,
				    IlvLinkData* linkData2);

    IlBoolean		isOverlap(const IlvRect& rect1,
				  const IlvRect& rect2) const;

public:
    IlFloat		getSegmentRectCost(const IlvPoint& from,
					   const IlvPoint& to,
					   const IlvRect& rect) const;

private:
    void	computeConnectionPoints(IlvGraphModel* graphModel,
					IlBoolean reshapeLinks,
					IlBoolean withSlaveLinks,
					IlBoolean redraw);
    void	computeNodeConnectionPoints(IlvGraphModel* graphModel,
					    IlvNodeData* nodeData,
					    IlBoolean withSlaveLinks,
					    IlBoolean isGlobalComputation);
    void	computeLinkConnectionPoints(IlvGraphModel* graphModel,
					    IlvLinkData* linkData,
					    IlvNodeSide* oldFromSide,
					    IlvNodeSide* newFromSide,
					    IlvNodeSide* oldToSide,
					    IlvNodeSide* newToSide);
    void	computeLinkNodeConnectionPoints(IlvGraphModel* graphModel,
						IlvLinkData* changedLinkData,
						IlvNodeData* nodeData,
						IlvNodeSide* oldNodeSide,
						IlvNodeSide* newNodeSide);

public:
    virtual void	setLinkStyle(IlvLayoutLinkStyle style);
    virtual
    IlvLayoutLinkStyle	getLinkStyle() const;

    void		setLinkBundlesMode(IlvOrthogonalLinkBundleMode mode);
    IlvOrthogonalLinkBundleMode getLinkBundlesMode() const;

#if CONTENTSCHANGED
    void		contentsChanged(GraphModelEvent event) ;
#endif
    void		setAutoLayout(IlBoolean enable);
    IlBoolean		isAutoLayout() const;

    void		setSameShapeForMultipleLinks(IlBoolean);
    IlBoolean		isSameShapeForMultipleLinks() const;

    void		setLinkToNodeCrossingPenalty(IlUInt);
    IlUInt		getLinkToNodeCrossingPenalty() const;
    void		setLinkToLinkCrossingPenalty(IlUInt);
    IlUInt		getLinkToLinkCrossingPenalty() const;

    virtual void	setMinFinalSegmentLength(IlUInt);
    virtual IlUInt	getMinFinalSegmentLength() const;

    virtual void	setLinkOffset(IlUInt offset);
    virtual IlUInt	getLinkOffset() const;

    virtual IlUInt	getAllowedNumberOfIterations() const;
    void		setAllowedNumberOfIterations(IlUInt);

    IlBoolean		supportsPreserveFixedLinks() const;
    IlBoolean		supportsAllowedTime() const;
    IlBoolean		supportsAnimation() const;

public:
    IlString		getLinkProperty() const;
    IlString		getNodeProperty() const;

    // ------------------- Default Values -----------------------
    static const IlvLayoutLinkStyle	DefaultLinkStyle;
    static const IlvOrthogonalLinkBundleMode		DefaultLinkBundlesMode;
    static const IlUInt			DefaultMinFinalSegment;
    static const IlUInt			DefaultLinkOffset;
    static const IlUInt			DefaultLinkNodePenalty;
    static const IlUInt			DefaultLinkLinkPenalty;
    //static const IlBoolean		DefaultOptimizationEnabled;
    static const IlUInt			DefaultNumberOfIterations;
    static const IlBoolean		DefaultSameShapeForMultipleLinks;
    static const IlBoolean		DefaultAutoLayout;

    // ------------------- Accessors ----------------------------
    DeclareLayoutAccessors();
    static IlSymbol*	_linkStyleValue;
    static IlSymbol*	_linkBundleModeValue;
    static IlSymbol*	_minFinalSegmentValue;
    static IlSymbol*	_linkOffsetValue;
    static IlSymbol*	_linkNodePenaltyValue;
    static IlSymbol*	_linkLinkPenaltyValue;
    static IlSymbol*	_numberOfIterationsValue;
    static IlSymbol*	_sameShapeForMultipleLinksValue;
    static IlSymbol*	_autoLayoutValue;
    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
class ILVORTHLNKEXPORTED IlvNodeSideFilter
{
public:
    IlvNodeSideFilter();
    virtual ~IlvNodeSideFilter();

    virtual IlBoolean	accept(IlvGraphModel* graphModel,
			       IlAny link,
			       IlBoolean origin,
			       IlAny node,
			       IlUInt side) = 0;

protected:
private:
};

ILVORTHLNKMODULEINIT(lo_orthlink)
#endif /* !__Ilv_Layout_Orthlink_H */
