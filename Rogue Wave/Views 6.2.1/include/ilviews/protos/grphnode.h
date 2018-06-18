// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/grphnode.h
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
// Declaration of the graphic group node classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Grphnode_H
#define __Ilv_Protos_Grphnode_H

#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#  include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Protos_Group_H)
#  include <ilviews/protos/group.h>
#endif
#if !defined(__Ilv_Graphics_Handle_H)
#  include <ilviews/graphics/handle.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#  include <ilviews/grapher/grapher.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#  include <ilviews/graphics/holder.h>
#endif

// --------------------------------------------------------------------------
// IlvGraphicNode		A group node holding an IlvGraphic.
// --------------------------------------------------------------------------
#define IlvManagerValue			"manager"
#define IlvContainerValue		"container"
#define IlvProtoGraphicValue		"protoGraphic"
#define IlvLayerValue			"layer"
#define IlvBaseLayerValue		"baseLayer"
#define IlvVisibleValue			"visible"
#define IlvHiddenValue			"hidden"
#define IlvIsNodeValue			"isNode"
#define IlvInteractorValue		"interactor"
#define IlvZoomThresholdValue		"zoomThreshold"
#define IlvMaximumLayerValue		"maximumLayer"
#define IlvSelectedValue		"selected"
#define IlvTransformationValue		"transformation"
#define IlvMovableValue			"movable"
#define IlvScalableValue		"scalable"
#define IlvTransformedValue		"transformed"
#define IlvEditModeValue		"editMode"
#define IlvGraphicNodeXValue		"x"
#define IlvGraphicNodeYValue		"y"
#define IlvGraphicNodeWidthValue	"width"
#define IlvGraphicNodeHeightValue	"height"
#define IlvGraphicNodeScaleXValue	"scaleX"
#define IlvGraphicNodeScaleYValue	"scaleY"
#define IlvGraphicNodeCenterXValue	"centerX"
#define IlvGraphicNodeCenterYValue	"centerY"
#if 0
#define IlvGraphicNodeOriginXValue	"originX"
#define IlvGraphicNodeOriginYValue	"originY"
#endif
#define IlvGraphicNodeFixedSizeValue	"fixedSize"
#define IlvGraphicNodeMinZoomValue	"minZoom"
#define IlvGraphicNodeMaxZoomValue	"maxZoom"

typedef void (*IlvGraphicNodeApplyFunc)(IlvGraphic* obj,
					IlAny arg,
					IlvGraphic* transformedObj);

class ILVPROEXPORTED IlvGraphicNode : public IlvGroupNode
{
public:
    IlvGraphicNode(IlvGraphic* graphic,
		   const char* name = 0,
		   IlBoolean transformed = IlFalse);
    virtual ~IlvGraphicNode();

    virtual
    IlvGroupNode*	copy(IlBoolean shared) const;
    virtual IlBoolean	update(const IlvGroupNode&);

    void		clearGraphic();
    virtual void	clear();

    virtual const char*	getName() const;
    virtual void	setName(const char* name);

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual IlBoolean	changeValues(const IlvValue* values, IlUShort count);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
    IlvGroup*		getSubGroup() const;
    IlvGraphic*		getManagedGraphic() const;
    virtual IlvGraphic*	getGraphic() const;

    IlvGraphicHolder*	getHolder() const;
    IlBoolean		isTransformed() const;
    void		setTransformed(IlBoolean transformed,
				       IlBoolean editModeChanged = IlFalse);

    IlBoolean		isEditMode() const;
    void		setEditMode(IlBoolean editMode);
    IlvManager*		getManager() const;
    void		setManager(IlvManager* manager,
				   int layer = -1,
				   IlBoolean redraw = IlFalse);
    IlvContainer*	getContainer() const;
    /*
      Undocumented method: should not be used directly, but only through 
      changeValue calls.

      Sets the container that handles the graphic object associated with
      the node. The graphic object is added to the container. If
      \a redraw is \c IlTrue, the container redraws
      the area that contains the graphic object of the node.
     */
    void		setContainer(IlvContainer* container,
				     IlBoolean redraw = IlFalse);
    IlvGraphic*		getProtoGraphic() const;
    /*
      Undocumented method: should not be used directly, but only through 
      changeValue calls.
      \short Adds the node to the specified \c IlvProtoGraphic
      object.
     */
    void		setProtoGraphic(IlvGraphic* protoGraphic);

    int			getLayer() const;
    void		setLayer(int layer);
    int			getBaseLayer() const;
    void		setBaseLayer(int layer);
    IlBoolean		isVisible() const;
    void		setVisible(IlBoolean visible);
    IlBoolean		isHidden() const;
    void		setHidden(IlBoolean hidden);
    IlBoolean		isNode() const;
    void		isNode(IlBoolean isit);

    IlBoolean		isReference() const;
    void		setReference(IlBoolean reference);
    const char*		getInteractor() const;
    void		setInteractor(const char* name);
    IlFloat		getZoomThreshold() const;
    void		setZoomThreshold(IlFloat zoomThreshold);

    IlBoolean		hasMinZoom() const;
    IlFloat		getMinZoom() const;
    void		setMinZoom(IlFloat zoom);

    IlBoolean		hasMaxZoom() const;
    IlFloat		getMaxZoom() const;
    void		setMaxZoom(IlFloat zoom);
    IlBoolean		isFixedSize() const;
    void		setFixedSize(IlBoolean fixed);

    IlBoolean		isMovable() const;
    void		setMovable(IlBoolean isit);

    IlBoolean		isScalable() const;
    void		setScalable(IlBoolean isit);
    void		reDraw();
    void		apply(IlvGraphicNodeApplyFunc func,
			      IlAny arg,
			      IlBoolean redraw = IlTrue,
			      IlBoolean local = IlFalse);

    void		invalidate();

    inline IlvGraphic*	managedObject() { return(getManagedGraphic()); }
     /* </a></pre>Returns the graphic node associated with a graphic object,
     * or \c 0 if the object is not contained in a graphic
     */
    static
    IlvGraphicNode*	GetNode(IlvGraphic* obj);
    static void		CleanNode(IlvGraphic* obj);

    static IlBoolean	IsInEditor();
    static void		IsInEditor(IlBoolean inEditor);

    static IlBoolean	IsAutoRedrawEnabled();
    static void		SetAutoRedrawEnabled(IlBoolean enabled);

    static IlSymbol*	GroupNodeProperty;

    static IlSymbol*	ManagerValue;
    static IlSymbol*	ContainerValue;
    static IlSymbol*	ProtoGraphicValue;
    static IlSymbol*	LayerValue;
    static IlSymbol*	BaseLayerValue;
    static IlSymbol*	MaximumLayerValue;
    static IlSymbol*	VisibleValue;
    static IlSymbol*	HiddenValue;
    static IlSymbol*	MovableValue;
    static IlSymbol*	ScalableValue;
    static IlSymbol*	FixedSizeValue;
    static IlSymbol*	IsNodeValue;
    static IlSymbol*	InteractorValue;
    static IlSymbol*	ZoomThresholdValue;
    static IlSymbol*	MinZoomValue;
    static IlSymbol*	MaxZoomValue;
    static IlSymbol*	SelectedValue;
    static IlSymbol*	TransformationValue;
    static IlSymbol*	TransformerValue;
    static IlSymbol*	TransformedValue;
    static IlSymbol*	EditModeValue;
    static IlSymbol*	XValue;
    static IlSymbol*	YValue;
    static IlSymbol*	WidthValue;
    static IlSymbol*	HeightValue;
    static IlSymbol*	ScaleXValue;
    static IlSymbol*	ScaleYValue;
    static IlSymbol*	CenterXValue;
    static IlSymbol*	CenterYValue;

    DeclareGroupNodeInfo();

//  inline IlvPoint	getOrigin() const { return _origin; }

protected:
    static int		AddObject(IlvGroupOutputFile& file,
				  const IlvGraphicNode* node);

    static
    IlvGraphicNode*	GetObject(IlvGroupInputFile& file,
				  IlvDisplay* display,
				  int index,
				  const char* name);

    static void		WriteObjects(IlvGroupFile& file,
				     IlvGroupFileHookType type,
				     IlvGroup* group,
				     IlvGroupNode* node,
				     IlAny arg);

    static void		DeleteObjects(IlvGroupFile& file,
				      IlvGroupFileHookType type,
				      IlvGroup* group,
				      IlvGroupNode* node,
				      IlAny arg);

    IlvGraphic*		_graphic;
    IlUShort		_flags;
//  IlvPoint		_origin;
};

IlvDECLAREINITPROCLASS(grphnode)

#endif /* __Ilv_Protos_Grphnode_H */
