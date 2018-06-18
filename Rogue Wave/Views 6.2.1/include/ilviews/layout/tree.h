// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/tree.h
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
// Declaration of the IlvTreeLayout class
// Defined in library ilvtree
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Tree_H
#define __Ilv_Layout_Tree_H

#if !defined(__Ilv_Layout_Gphlayout_H)
#include <ilviews/layout/gphlayout.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvtree.lib")
#endif

#if defined(ILVTREELIB)
#define ILVTREEEXPORTED ILVBASEEXPORTED
#define ILVTREEEXPORTEDFUNCTION(type)   ILVBASEEXPORTEDFUNCTION(type)
#define ILVTREEEXPORTEDVAR(type)        ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVTREELIB */
#define ILVTREEEXPORTED ILVBASEIMPORTED
#define ILVTREEEXPORTEDFUNCTION(type)   ILVBASEIMPORTEDFUNCTION(type)
#define ILVTREEEXPORTEDVAR(type)        ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVTREELIB */

#define ILVTREEMODULEINIT(m)    IL_MODULEINIT(m, ILVTREEEXPORTED);

// Forward declaration

class IlvTGraph;

// --------------------------------------------------------------------------
// Enumeration types
// --------------------------------------------------------------------------

enum IlvLayoutAlignment {
    IlvLayoutEastAlignment = 0,
    IlvLayoutWestAlignment = 1,
    IlvLayoutNorthAlignment = 2,
    IlvLayoutSouthAlignment = 3,
    IlvLayoutCenterAlignment = 4,
    IlvLayoutBorderCenterAlignment = 5,
    IlvLayoutTipOverAlignment = 6,
    IlvLayoutMixedAlignment = 7
};


enum IlvTreeLayoutMode {
    IlvTreeLayoutFreeMode = 0,
    IlvTreeLayoutLevelMode = 1,
    IlvTreeLayoutRadialMode = 2,
    IlvTreeLayoutAlternatingRadialMode = 3,
    IlvTreeLayoutTipOverMode = 4,
    IlvTreeLayoutTipLeavesOverMode = 5,
    IlvTreeLayoutTipRootsOverMode = 6,
    IlvTreeLayoutTipRootsAndLeavesOverMode = 7
};


// --------------------------------------------------------------------------
// Class IlvTreeLayout
// --------------------------------------------------------------------------


class ILVTREEEXPORTED IlvTreeLayout : public IlvGraphLayout
{
private:

    // ----------------------------------------------------------------------
    // Properties

    char*		_rootNodePreferenceProperty;
    char*		_alignmentProperty;
    char*		_linkStyleProperty;
    char*		_eastAttachProperty;
    char*		_westAttachProperty;

    // ----------------------------------------------------------------------
    // Storage for the layout options

    static const IlvLayoutLinkStyle	_defaultGlobalLinkStyle;
    static const IlvLayoutAlignment	_defaultGlobalAlignment;
    static const IlvTreeLayoutMode	_defaultLayoutMode;
    static const IlvDirection		_defaultFlowDirection;
    static const IlvLayoutAlignment	_defaultLevelJustification;
    static const IlvPos			_defaultSiblingOffset;
    static const IlvPos			_defaultParentChildOffset;
    static const IlvPos			_defaultBranchOffset;
    static const IlvPos			_defaultTipOverBranchOffset;
    static const IlDouble		_defaultAspectRatio;
    static const IlInt			_defaultOverlapPercentage;
    static const IlInt			_defaultOrthForkPercentage;
    static const IlInt			_defaultMaxChildrenAngle;

    IlvLayoutLinkStyle	_globalLinkStyle;
    IlvLayoutAlignment	_globalAlignment;
    IlvTreeLayoutMode	_layoutMode;
    IlvDirection	_flowDirection;
    IlvLayoutAlignment	_levelJustification;
    IlvPos		_siblingOffset;
    IlvPos		_parentChildOffset;
    IlvPos		_branchOffset;
    IlvPos		_tipOverBranchOffset;
    IlDouble		_aspectRatio;
    IlInt		_overlapPercentage;
    IlInt		_orthForkPercentage;
    IlInt		_maxChildrenAngle;
    IlvPoint*		_position;
    IlBoolean		_isRootPosition;

    // timer to avoid that layoutStepPerformed is called too often
    IlvRunTimeType	_lastLayoutStepPerformedTime;

    // flag to indicate that we run out of time
    IlBoolean		_preliminaryStopped;

    // the percentage complete controller
    // PercCompleteController* _percCompleteControler;

    // container for specified roots
    IlList		_specRoots;

    // container for calculated roots
    IlList		_calcRoots;

    // container for calculated tree links
    IlList*		_calcForwardTreeLinks;
    IlList*		_calcBackwardTreeLinks;
    IlList*		_calcNonTreeLinks;

public:

    // ----------------------------------------------------------------------

    IlvTreeLayout();

    virtual ~IlvTreeLayout();

    // This is Views specific
    IlvDeclareClassInfo();

protected:

    virtual void	layout();

public:

    virtual void	detach();

    virtual void	cleanObjectProperties(IlAny nodeOrLink);

    // ----------------------------------------------------------------------
    // The supports-features

    IlBoolean		supportsPreserveFixedNodes() const;

    IlBoolean		supportsPreserveFixedLinks() const;

    IlBoolean		supportsAllowedTime() const;

    // IlBoolean supportsPercentageComplete() const;

    // ----------------------------------------------------------------------
    // The layout parameters

    void		setGlobalLinkStyle(IlvLayoutLinkStyle style);

    IlvLayoutLinkStyle	getGlobalLinkStyle() const;

    void		setFlowDirection(IlvDirection flowDirection);

    IlvDirection	getFlowDirection() const;

    void		setLayoutMode(IlvTreeLayoutMode mode);

    IlvTreeLayoutMode	getLayoutMode() const;

    void		setLevelJustification(IlvLayoutAlignment justif);

    IlvLayoutAlignment	getLevelJustification() const;

    void		setGlobalAlignment(IlvLayoutAlignment alignment);

    IlvLayoutAlignment	getGlobalAlignment() const;

    void		setSiblingOffset(IlvPos offset);

    IlvPos		getSiblingOffset() const;

    void		setParentChildOffset(IlvPos offset);

    IlvPos		getParentChildOffset() const;

    void		setBranchOffset(IlvPos offset);

    IlvPos		getBranchOffset() const;

    void		setTipOverBranchOffset(IlvPos offset);

    IlvPos		getTipOverBranchOffset() const;

    void		setAspectRatio(IlDouble aspectRatio);

    void		setAspectRatio(const IlvRect& rect);

    void		setAspectRatio(const IlvAbstractView* view);

    IlDouble		getAspectRatio() const;

    void		setOverlapPercentage(IlInt percentage);

    IlInt		getOverlapPercentage() const;

    void		setMaxChildrenAngle(IlInt angle);

    IlInt		getMaxChildrenAngle() const;

    void		setOrthForkPercentage(IlInt percentage);

    IlInt		getOrthForkPercentage() const;

    void		setLinkStyle(IlAny link, IlvLayoutLinkStyle style);

    IlvLayoutLinkStyle	getLinkStyle(IlAny link) const;

    void		setEastWestNeighboring(IlAny eastNode,
					       IlAny westNode);

    void		setWestEastNeighboring(IlAny westNode,
					       IlAny eastNode);

    IlAny		getEastNeighbor(IlAny node) const;

    IlAny		getWestNeighbor(IlAny node) const;

    void		setRoot(IlAny node);

    const IlList*	getSpecRoots() const;


    // Adds a new calculated root to the vector of roots.
    // For internal usage only.

    void		addCalcRoot(IlAny node);

    const IlList*	getCalcRoots() const;

    void		setRootPreference(IlAny node, IlInt preference);

    IlInt		getRootPreference(IlAny node) const;

    void		setPosition(const IlvPoint& point,
				    IlBoolean isRootPosition);

    const IlvPoint*	getPosition() const;

    IlBoolean		isRootPosition() const;

    void		setCategorizingLinks(IlBoolean flag);

    IlBoolean		isCategorizingLinks() const;

    // Adds a new link to the vector of calculated forward tree links.
    // For internal usage only.

    void		addCalcForwardTreeLink(IlAny link);

    const IlList*	getCalcForwardTreeLinks() const;

    // Adds a new link to the vector of calculated backward tree links.
    // For internal usage only.

    void		addCalcBackwardTreeLink(IlAny link);

    const IlList*	getCalcBackwardTreeLinks() const;

    // Adds a new link to the vector of calculated non-tree links.
    // For internal usage only.

    void		addCalcNonTreeLink(IlAny link);

    const IlList*	getCalcNonTreeLinks() const;

    void		setAlignment(IlAny node,
				     IlvLayoutAlignment alignment);

    IlvLayoutAlignment	getAlignment(IlAny node) const;


private:

    // ----------------------------------------------------------------------
    // Remaining methods

    // Transfers the layout parameters into the graph.

    void		transferLayoutOptions(IlvTGraph* graph);

public:

    // Informs the layout instance that a step of the layout algorithm has
    // been performed. The method notified the listeners of the layout events.
    // In order to automatically avoid that notification is done too often, it
    // notifies only if there was a delay of at least 50 ms since the last
    // notification.
    void		callLayoutStepPerformed();

    // Returns \c IlTrue if the layout can continue.
    IlBoolean		mayContinue() const;

    // Accessors

    DeclareLayoutAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_layoutModeValue;
    static IlSymbol*	_globalLinkStyleValue;
    static IlSymbol*	_globalAlignmentValue;
    static IlSymbol*	_flowDirectionValue;
    static IlSymbol*	_levelJustificationValue;
    static IlSymbol*	_siblingOffsetValue;
    static IlSymbol*	_branchOffsetValue;
    static IlSymbol*	_parentChildOffsetValue;
    static IlSymbol*	_tipOverBranchOffsetValue;
    static IlSymbol*	_aspectRatioValue;
    static IlSymbol*	_overlapPercentageValue;
    static IlSymbol*	_orthForkPercentageValue;
    static IlSymbol*	_maxChildrenAngleValue;
};

ILVTREEMODULEINIT(lt_tree)

// --------------------------------------------------------------------------
#endif /* !__Ilv_Layout_Tree_H */

