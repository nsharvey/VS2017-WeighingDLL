// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbgraphe.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliDbGrapher class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbgraphe_H
#define __Ili_Dbgraphe_H

#if !defined(__Ilv_Grapher_Links_H)
#  include <ilviews/grapher/links.h>
#endif
#if !defined(__Ilv_ginterac_H)
#  include <ilviews/grapher/inters.h>
#endif
#if !defined(__Ilv_Base_Error_H)
#  include <ilviews/base/error.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgraph_Rectscgr_H)
#  include <ilviews/gadgraph/rectscgr.h>
#endif
#if !defined(__Ili_Dsusage_H)
#  include <ilviews/dataccess/gadgets/dsusage.h>
#endif
#if !defined(__Ili_Reposit_H)
#  include <ilviews/dataccess/reposit.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#  include <ilviews/graphics/label.h>
#endif
#if !defined(__Ili_Labelbmp_H)
#  include <ilviews/dataccess/gadgets/labelbmp.h>
#endif

// --------------------------------------------------------------------------
enum IliGrapherColumn {
    IliGrapherNodeXColumn = 0,
    IliGrapherNodeYColumn,
    IliGrapherNodeIdColumn,
    IliGrapherNodeLabelColumn,
    IliGrapherNodeBitmapColumn,
    IliGrapherNodeForegroundColumn,
    IliGrapherNodeBackgroundColumn,
    IliGrapherLinkFromColumn,
    IliGrapherLinkToColumn,
    IliGrapherLinkColorColumn,
    IliGrapherLinkTypeColumn,
    IliGrapherLinkOrientedColumn,
    IliGrapherColumnNbTag
};

// --------------------------------------------------------------------------
enum IliGrapherColor {
    IliGrapherLinkColor = 0,
    IliGrapherForegroundLabelColor,
    IliGrapherBackgroundLabelColor,
    IliGrapherColorNbTag
};

// --------------------------------------------------------------------------
typedef IlBoolean (*IliDefineObjectCallback)(IliTableBuffer* buff,
					     IlvGraphic* g,
					     IlAny arg);
// --------------------------------------------------------------------------
typedef IlvGraphic* (*IliCreateObjectCallback)(IliTableBuffer* buff,
					       IlAny arg);
// --------------------------------------------------------------------------
typedef IlvGraphic* (*IliUpdateObjectCallback)(IlvGraphic* previous,
					       IliTableBuffer* buff,
					       IlAny arg);

class IliDbGrapher;

// -------------------------------------------------------------------------
class IliGrapher
: public IlvGrapher
{
public:
    IliGrapher(IlvDisplay* display);
    virtual ~IliGrapher();

    virtual void	removeNode(IlvGraphic*,
				   IlBoolean = IlTrue,
				   IlBoolean = IlTrue);
    virtual void	removeLink(IlvLinkImage*,
				   IlBoolean = IlTrue,
				   IlBoolean = IlTrue);
    virtual void	paste(const IlvView*, const char*, IlvPoint&);
    virtual void	addNode(IlvGraphic*, IlBoolean = IlTrue, int = -1);
    virtual void	addLink(IlvLinkImage*,
				IlBoolean = IlTrue,
				int = -1,
				IlvLinkImage* = 0,
				IlvLinkImage* = 0);

    // Internals
    void		eventKeyUp(IlvEvent&);
    void		eventDoubleClick(IlvEvent&);
    void		eventButtonDown(IlvEvent&);
    void		eventButtonDragged(IlvEvent&);
    void		eventButtonUp(IlvEvent&);

    void		setGrapherRectangle(IliDbGrapher*);
    IliDbGrapher*	getGrapherRectangle() const;

protected:
    IliDbGrapher*	_dbGrapher;

    void		addAccel(IlvEventType, IlUShort, IlUShort = 0);
};

// -------------------------------------------------------------------------
class IliDbGrapherInteractor
: public IlvGraphSelectInteractor
{
public:
    IliDbGrapherInteractor(IlvManager*, IlvView*, IliDbGrapher*);

    IlBoolean		handleEvent(IlvEvent&);

    virtual void	doReshape(IlvGraphic*, const IlvRect&);
    virtual void	doTranslate(const IlvPoint&);
    virtual const char* className() const;

protected:
    IliDbGrapher*	_grapherObject;

    virtual IlBoolean	eventButtonDragged(IlvEvent&);
    IlvGraphic*		getSelectedObject(IlInt,
					  IlInt,
					  IlBoolean) const;
};

// -------------------------------------------------------------------------
class ILV_DBGRAPHE_EXPORTED IliDbGrapher
: public IlvSCGrapherRectangle
{
public:
    IliDbGrapher(IlvDisplay* display,
		 const IlvRect& rect,
		 IlvPalette* palette = 0);
    ~IliDbGrapher();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbGrapher);

    // Behaviour
    inline void		propagateNodeDeletion(IlBoolean propagate)
	{ _propagateNodeDeletion = propagate; }
    inline IlBoolean	isNodeDeletetionPropagated() const
    {
	return _propagateNodeDeletion;
    }

    inline void		propagateNodeRename(IlBoolean propagate)
    {
	_propagateNodeRename = propagate;
    }
    inline IlBoolean	isNodeRenamePropagated() const
	{ return _propagateNodeRename; }

    inline void		supportsOutOfOrderEvents(IlBoolean support)
	{ _supportsOutOfOrderEvents = support; }
    inline IlBoolean	areOutOfOrderEventsSupported() const
	{ return _supportsOutOfOrderEvents; }

    // Data Sources
    inline void		setNodeDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getNodeDataSource() const;
    inline void		setNodeDataSourceName(const char* name);
    inline const char*	getNodeDataSourceName() const;
    inline void		setLinkDataSource(IliDataSource* ds);
    inline
    IliDataSource*	getLinkDataSource() const;
    inline void		setLinkDataSourceName(const char* name);
    inline const char*	getLinkDataSourceName() const;

    // Column Name
    inline void		setColumnName(IliGrapherColumn tag, const char* col)
	{
	    if (tag < IliGrapherLinkFromColumn) {
		_dsNode->setColumnName((IlInt)tag, col);
	    }
	    else {
		_dsLink->setColumnName((IlInt)
				       (tag-IliGrapherLinkFromColumn), col);
	    }
	}
    inline const char*	getColumnName(IliGrapherColumn tag) const
	{
	    return (tag < IliGrapherLinkFromColumn)
		   ? _dsNode->getColumnName((IlInt)tag)
		   : _dsLink->getColumnName((IlInt)
					    (tag-IliGrapherLinkFromColumn));
	}
    inline IlInt	getColumnIndex(IliGrapherColumn tag) const
	{
	    return (tag < IliGrapherLinkFromColumn)
		   ? _dsNode->getColumnIndex((IlInt)tag)
		   : _dsLink->getColumnIndex((IlInt)
					     (tag-IliGrapherLinkFromColumn));
	}

    // Refresh
    void		refreshAll();
    void		refreshAllNodes();
    void		refreshAllLinks(IlBoolean del = IlFalse);

    IliDsUsageDeclareBatch(node);
    IliDsUsageDeclareBatch(link);
    IliDsUsageDeclareBatchDirect();

    IlInt		getBatchCount() const;
    IlBoolean		isBatchMode() const;

    // Initialisation
    void		initGrapher();

    //---- Event from data source ----
    IliDsUsageDeclareFctConnect(node);
    IliDsUsageDeclareFctConnect(link);

    // Execute
    IlBoolean		doRemoveNode(IlvGraphic*);
    IlBoolean		doRemoveLink(IlvLinkImage*);
    IlBoolean		doAddLink(IlvLinkImage*);
    IlBoolean		doAddNode(IlvGraphic*);
    IlBoolean		doPaste();
    void		doEventKeyUp(IlvEvent& event);
    void		doEventDoubleClick(IlvEvent& event);
    void		doEventButtonDown(IlvEvent& event);
    void		doEventButtonDragged(IlvEvent& event);
    void		doEventButtonUp(IlvEvent& event);

    inline IlBoolean	isRightButton(IlvEvent& event) const
	{
	    return ((event.button() == IlvRightButton) ||
		     (event.button() == IlvMiddleButton))
		   ? IlTrue
		   : IlFalse;
	}
    IlvGraphic*		getSelectedObject(IlInt, IlInt, IlBoolean) const;
    void		drawGhostLink();
    void		doIt(IlvGraphic*, IlvGraphic*);

    // Holders
    virtual void	setHolder(IlvGraphicHolder*);

    // Look
    void		setColor(IliGrapherColor tag, IlvColor* color);
    inline IlvColor*	getColor(IliGrapherColor tag) const
	{
	    return getDisplay()->getColor((const char*)(_colors[tag]));
	}
    void		setBitmapName(const char* name);
    inline const char*	getBitmapName() { return (const char*)_bitmapName; }
    inline void		setDisplayName(IlBoolean flag)
	{ _displayName = flag; }
    inline IlBoolean	isNameDisplayed() const
	{ return _displayName; }
    inline void		setLinkType(IliGrapherLinkType type,
				    IlBoolean oriented = IlFalse)
	{
	    _linkType = type;
	    _oriented = oriented;
	}
    inline
    IliGrapherLinkType	getLinkType() const
	{
	    return (IliGrapherLinkType)_linkType;
	}
    inline IlBoolean	isLinkOriented() const { return _oriented; }
    void		setBackgroundPictureName(const char* name,
						 IlBoolean reload = IlFalse);
    inline const char*	getBackgroundPictureName() const
	{
	    return (const char*)_bgPictureName;
	}

    // Error reporting
    void		addErrorSink(IliErrorSink* sink, IlBoolean forNode);
    void		removeErrorSink(IliErrorSink* sink,
					IlBoolean forNode);
    void		setErrorReporter(IliErrorReporter* reporter);
    IliErrorReporter*	getErrorReporter() const;
    void		reportErrors(const IliErrorList& list) const;

    // Event
    virtual void	onNodeMoved();
    virtual void	onNodeDoubleClicked();
    virtual void	onLinkDoubleClicked();
    virtual void	onPrepareDeleteObject();
    virtual IlBoolean	onDefineNode(IliTableBuffer* buff, IlvGraphic* g = 0);
    virtual IlvGraphic* onCreateObjectNode(IliTableBuffer* buff);
    virtual IlBoolean	onDefineLink(IliTableBuffer* buff, IlvGraphic* g = 0);
    virtual
    IlvLinkImage*	onCreateObjectLink(IliTableBuffer* buff);
    virtual IlvGraphic* onUpdateObjectNode(IlvGraphic* g,
					   IliTableBuffer* buff);
    virtual IlvGraphic* onUpdateObjectLink(IlvGraphic* g,
					   IliTableBuffer* buff);
    IlvGraphic*		createDefaultObjectNode(IliTableBuffer* buff);
    IlvLinkImage*	createDefaultObjectLink(IliTableBuffer* buff);
    inline const char*	getObjectNameMoved() const
	{ return (const char*)_objectForCallback; }
    inline const char*	getObjectNameDoubleClicked() const
	{ return (const char*)_objectForCallback; }
    inline const char*	getObjectNamePrepareDeleted() const
	{ return (const char*)_objectForCallback; }

    inline void		setCallbackContext(IlvSymbol* sym)
	{ _callbackContext = sym; }
    inline void		setObjectForCallback(const char* obj)
	{ _objectForCallback = obj; }
    inline void		dontDeleteObject() { _dontDelete = IlTrue; }

    // Callbacks
    void		setDefineObjectCallback(IliDefineObjectCallback cb,
						IlAny arg,
						IlBoolean forNode = IlTrue);
    IliDefineObjectCallback
    getDefineObjectCallback(IlBoolean forNode = IlTrue) const;
    IlAny		getDefineObjectData(IlBoolean forNode = IlTrue) const;
    void		setCreateObjectCallback(IliCreateObjectCallback cb,
						IlAny arg,
						IlBoolean forNode = IlTrue);
    IliCreateObjectCallback
    getCreateObjectCallback(IlBoolean forNode = IlTrue) const;
    IlAny		getCreateObjectData(IlBoolean forNode = IlTrue) const;
    void		setUpdateObjectCallback(IliUpdateObjectCallback cb,
						IlAny arg,
						IlBoolean forNode = IlTrue);
    IliUpdateObjectCallback
    getUpdateObjectCallback(IlBoolean forNode = IlTrue) const;
    IlAny		getUpdateObjectData(IlBoolean forNode = IlTrue) const;
    static IlvSymbol*	NodeMovedSymbol();
    static IlvSymbol*	NodeDoubleClickedSymbol();
    static IlvSymbol*	LinkDoubleClickedSymbol();
    static IlvSymbol*	PrepareDeleteObjectSymbol();

    virtual IlUInt	getCallbackTypes(const char* const **,
					 const IlvSymbol* const**) const;

    // Commands for grapher (internal)
    void		cmdMoveNode(const char*, IlInt, IlInt);
    void		cmdRenameNode(const char*, const char*);
    void		cmdDeleteLinksForNode(const char*);
    void		cmdReplaceNode(const char*,
				       IliTableBuffer*);
    void		cmdCheckLinks(const char*);
    void		cmdChangeLink(IliTableBuffer*, IliTableBuffer*);
    void		cmdChangeLinkColor(IliTableBuffer*);
    void		cmdChangeLinkOrientation(IliTableBuffer*);
    void		cmdDeleteSelection();

    // Commands for data source (internal) ----
    void		cmdDsDeleteLink(const char*, const char*);
    void		cmdDsDeleteNode(const char*);
    void		cmdDsDeleteLinksForNode(const char*);
    void		cmdDsAddNode(IlInt, IlInt);
    void		cmdDsAddNode(IlvGraphic*);
    void		cmdDsAddLink(IlvLinkImage*);
    void		cmdDsAddLink(const char*, const char*);
    void		cmdDsRenameLinksForNode(const char*,
						const char*);
    void		cmdDsMoveNode(const char*, IlInt, IlInt);

    // FieldItf
    virtual IlBoolean	isReadOnly() const;
    virtual void	setReadOnly(IlBoolean);

    // Accessors
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    static  void	GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);

    // Others
    IlBoolean		isValidObject(IlvGraphic* g) const;
    IlBoolean		isNode(IlvGraphic* g) const;
    IlBoolean		isLink(IlvGraphic* g) const;
    void		applyFromInspector();

    IlInt		getIntegerValueForColumn(IliTableBuffer*,
						 IlInt,
						 IlInt);
    const char*		getStringValueForColumn(IliTableBuffer*,
						IlInt,
						const char*);
    IlBoolean		getBooleanValueForColumn(IliTableBuffer*,
						 IlInt,
						 IlBoolean);
    IlvColor*		getColorValueForColumn(IliTableBuffer*,
					       IlInt,
					       IlvColor*);

    // Internal
    void		onNodeMovedCallback(const char*);
    void		onNodeDoubleClickedCallback(const char*);
    void		onLinkDoubleClickedCallback(const char*);
    void		onPrepareDeleteObjectCallback(const char*);

protected:
    // Event handling
    IlBoolean			_makeLink;
    IlvGraphic*			_firstNode;
    IlvGraphic*			_secondNode;
    IlvPoint			_prev;
    IlvPoint			_first;
    IlvPoint			_ptBtnDown;

    // Data sources
    IliSingleDataSourceUsage*	_dsNode;
    IliSingleDataSourceUsage*	_dsLink;

    // Refresh
    IlBoolean			_needRefreshNodes;
    IlBoolean			_needRefreshLinks;
    IlBoolean			_inEndOfBatch;
    IlInt			_batchCount;

    // Behaviour
    IlBoolean			_propagateNodeDeletion;
    IlBoolean			_propagateNodeRename;
    IlBoolean			_supportsOutOfOrderEvents;
    IlBoolean			_dontDelete;

    // Other
    IlInt			_linkType;
    IlBoolean			_oriented;
    IlBoolean			_displayName;
    IliString			_colors[IliGrapherColorNbTag];
    IlvPalette*			_objPal;
    IliString			_bgPictureName;
    IliString			_bitmapName;
    IlBoolean			_readOnly;

    // Callbacks
    IliString			_objectForCallback;
    IlvSymbol*			_callbackContext;

    IliDefineObjectCallback	_defineNodeCallback;
    IliDefineObjectCallback	_defineLinkCallback;
    IlAny			_defineNodeData;
    IlAny			_defineLinkData;

    IliCreateObjectCallback	_createNodeCallback;
    IliCreateObjectCallback	_createLinkCallback;
    IlAny			_createNodeData;
    IlAny			_createLinkData;

    IliUpdateObjectCallback	_updateNodeCallback;
    IliUpdateObjectCallback	_updateLinkCallback;
    IlAny			_updateNodeData;
    IlAny			_updateLinkData;

    // Interaction
    IliDbGrapherInteractor*	_grapherInter;

    // Internals
    void		makeLinkName(IliTableBuffer*, IliString&);

    IlBoolean		isColumnData(IlBoolean link, IlInt colno);
    void		computePaletteNodes();

    // ViewRectangle
    virtual void	makeView(IlvPort* dst, const IlvTransformer* t);
    virtual void	makeView(IlvView* v);
};

IliSingleDsUsageCodeDSAccess(IliDbGrapher, Node, _dsNode)
IliSingleDsUsageCodeDSAccess(IliDbGrapher, Link, _dsLink)

IlvDeclareEnumTypeClass(ILV_DBGRAPHE_EXPORTED, LinkType);

IliModuleDECL_exp(ILV_DBGRAPHE_EXPORTED, LinkType);
IliModuleDECL_exp(ILV_DBGRAPHE_EXPORTED, IliDbGrapher);

#endif /* !__Ili_Dbgraphe_H */
