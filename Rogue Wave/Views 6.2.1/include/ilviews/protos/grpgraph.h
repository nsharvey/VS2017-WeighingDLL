// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/grpgraph.h
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
// Encapsulation of IlvGroups into IlvGraphics.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Grpgraph_H
#define __Ilv_Protos_Grpgraph_H

#if !defined(__Ilv_Protos_Group_H)
#include <ilviews/protos/group.h>
#endif
#if !defined(__Ilv_Protos_Grphnode_H)
#include <ilviews/protos/grphnode.h>
#endif

// ---------------------------------------------------------------------------
// IlvGroupGraphic
// ---------------------------------------------------------------------------
class IlvGroupGraphicObserver;
class ILVPROEXPORTED IlvGroupGraphic : public IlvSimpleGraphic
{
    friend class IlvGroupGraphicObserver;

public:
    IlvGroupGraphic(IlvDisplay* display,
		    IlvGroup* group,
		    IlBoolean owner = IlTrue,
		    IlvPalette* palette = 0);

    ~IlvGroupGraphic();

    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	applyTransform(const IlvTransformer*	t);
    void		apply(IlvApplyObject, IlAny);
    void		applyReferences(IlvApplyObject, IlAny);
    virtual
    IlvGraphic* const*	getChildren(IlUInt& count) const;
    virtual IlUInt	getChildCount() const;
    virtual IlvGraphic* getChildAt(IlUInt index) const;
    virtual IlvGraphic* getChildByName(const char* name) const;
    virtual IlInt	getChildIndex(const IlvGraphic* object) const;

    virtual void	boundingBox(IlvRect&			bbox,
				    const IlvTransformer*	t = 0) const;
    virtual IlBoolean	zoomable() const;

    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setPattern(IlvPattern*);
    virtual void	setGradientPattern(IlvGradientPattern* b);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setPlaneMask(unsigned int);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual void	queryValues(IlvValue* values, IlUShort count) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual IlBoolean	changeValues(const IlvValue* values, IlUShort count);
    virtual IlBoolean	applyValue(const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    virtual void	setName(const char* name);

    static IlSymbol*	DeleteCallback;
    inline IlvGroup*	getGroup() const { return(_group); }
    void		clearGroup();
    void		clearOwner();

    void		deleteGroup();

    void		invalidateBBox();

    void		setRedrawNeeded(IlBoolean redraw);
    IlBoolean		isRedrawNeeded() const;
    IlBoolean		isOwner() const;
    void		setOwner(IlBoolean owner);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvGroupGraphic);

protected:
    void		setGroup(IlvGroup* group, IlBoolean owner = IlTrue);

    IlBoolean		isBBoxValid() const;
    void		setBBoxValid(IlBoolean bboxValid);

    IlBoolean		isZoomable() const;

    virtual void	nodesChanged();
    void		updateZoomable();

    IlvGroup*			_group;
    IlUShort			_flags;
    IlvGroupGraphicObserver*	_observer;
    IlvRect			_bbox;

private:
    void		setZoomable(IlBoolean zoomable);
};

// ---------------------------------------------------------------------------
// IlvGroupGraphicObserver
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupGraphicObserver : public IlvGroupObserver
{
public:
    IlvGroupGraphicObserver(IlvGroupGraphic* groupGraphic)
	: IlvGroupObserver(),
	  _groupGraphic(groupGraphic) {}

    virtual void	valuesChanged(IlvGroup* group,
				      const IlvValue* vals,
				      IlUInt count);
    virtual void	nodesChanged(IlvGroup* group);
    virtual void	groupDeleted(IlvGroup* group);

protected:
    IlvGroupGraphic*	_groupGraphic;
};

IlvDECLAREINITPROCLASS(grpgraph)

#endif /* __Ilv_Protos_Grpgraph_H */
