// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/protogr.h
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
#ifndef __Ilv_Protos_Protogr_H
#define __Ilv_Protos_Protogr_H

#if !defined(__Ilv_Protos_Grpgraph_H)
#include <ilviews/protos/grpgraph.h>
#endif
#if !defined(__Ilv_Protos_Proto_H)
#include <ilviews/protos/proto.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
// ---------------------------------------------------------------------------
// IlvProtoGraphic: an IlvGraphic encapsulating an IlvProtoInstance.
// ---------------------------------------------------------------------------

class IlvManagerProtoGraphicInteractor;
class IlvViewProtoGraphicInteractor;
class IlvProtoGraphicInteractor;

class ILVPROEXPORTED IlvProtoGraphic : public IlvGroupGraphic
{
    friend class IlvManagerProtoGraphicInteractor;
    friend class IlvViewProtoGraphicInteractor;
    friend class IlvProtoGraphicInteractor;

public:
    IlvProtoGraphic(IlvDisplay* display,
		    IlvGroup*   group,
		    IlBoolean   owner = IlTrue);

    // only for compatibility reasons.
    IlvProtoGraphic(IlvDisplay*       display,
		    IlvProtoInstance* instance,
		    IlBoolean         owner = IlTrue,
		    IlvPalette*       palette = 0);
    IlvProtoGraphic(IlvDisplay*   display,
		    IlvPrototype* proto,
		    IlvPalette*   palette = 0);
    IlvProtoGraphic(IlvDisplay* display,
		    const char* protoName,
		    IlvPalette* palette = 0);
    ~IlvProtoGraphic();

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*              dst,
				    const IlvTransformer* t    = 0,
				    const IlvRegion*      rect = 0) const;

    virtual void	setMode(IlvDrawMode m);
    virtual void	setOverwrite(IlBoolean o);

    virtual void	setHolder(IlvGraphicHolder* holder);

    IlvGraphicNode*	dispatchToObjects(IlvEvent&             event,
					  const IlvTransformer* t);

    virtual void	drawFocus(IlvPort*,
				  const IlvPalette* ,
				  const IlvTransformer* t = 0,
				  const IlvRegion*      clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual IlBoolean	classFocusable() const;
    const char*		getDefaultInteractor() const;
    inline
    IlvProtoInstance*	getProtoGraphic()
			{
			    IlvGroup* gr = getGroup();
			    if (gr &&
				gr->isSubtypeOf(IlvProtoInstance::ClassInfo()))
				return (IlvProtoInstance*) gr;
			    else return 0;
			}

    DeclareTypeInfo();
    DeclareIOConstructors(IlvProtoGraphic);

protected:
    virtual void	init();
    virtual void	nodesChanged();

    void		setFocus(IlvGraphicNode*       node,
				 const IlvTransformer* t);

    void		setFocusNode(IlvGraphicNode* node);
    IlvGraphicNode*	getFocusNode() const;

    void		initFocusNode();

    void		setMouseDragNode(IlvGraphicNode* node);
    IlvGraphicNode*	getMouseDragNode() const;
};

// ---------------------------------------------------------------------------
// IlvManagerProtoGraphicInteractor	Dispatch events to graphic nodes
//					inside an IlvProtoGraphic
//					(manager version).
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvManagerProtoGraphicInteractor
    : public IlvManagerObjectInteractor
{
public:
    IlvManagerProtoGraphicInteractor() {}

    virtual IlBoolean		handleEvent(IlvManager*,
					    IlvGraphic*     obj,
					    IlvEvent&,
					    IlvView*,
					    IlvTransformer* t);
    virtual IlBoolean		accept(const IlvGraphic*) const;
    virtual const char*		className() const;
};

// ---------------------------------------------------------------------------
// IlvViewProtoGraphicInteractor	Dispatch events to graphic nodes
//					inside an IlvProtoGraphic
//					(container version).
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvViewProtoGraphicInteractor
    : public IlvViewObjectInteractor
{
public:
    IlvViewProtoGraphicInteractor() {}

    virtual IlBoolean	handleEvent(IlvGraphic*     obj,
				    IlvEvent&,
				    IlvContainer*,
				    IlvTransformer* t);
    virtual IlBoolean	accept(const IlvGraphic*) const;
    virtual const char*	className() const;
};

class ILVPROEXPORTED IlvProtoGraphicInteractor : public IlvInteractor
{
public:
    IlvProtoGraphicInteractor() {}

    virtual IlBoolean	handleEvent(IlvGraphic*           obj,
				    IlvEvent&,
				    const IlvTransformer* t);

    virtual IlBoolean	accept(const IlvGraphic*) const;

    DeclareInteractorTypeInfoRO(IlvProtoGraphicInteractor);    
};

IlvDECLAREINITPROCLASS(protogr)
#endif /* __Ilv_Protos_Protogr_H */
