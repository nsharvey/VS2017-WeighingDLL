// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/grapher.h
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
// Declaration of the IlvGrapher and related classes
// Defined in library grapher
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Grapher_H
#define __Ilv_Grapher_Grapher_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Filter_H)
#include <ilviews/graphics/filter.h>
#endif
#if !defined(__Ilv_Graphics_Ghost_H)
#include <ilviews/graphics/ghost.h> // For free-end links
#endif
#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif

class IlvLinkImage;

#define IlvObjectIsNode    ((IlUInt)(1UL <<  5))
#define IlvObjectIsLink    ((IlUInt)(1UL <<  6))

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED  IlvGrapherObjectProperty
    : public IlvManagerObjectProperty
{
public:
    IlvGrapherObjectProperty(IlvManagerLayer* mgrl)
	: IlvManagerObjectProperty(mgrl)
    {
	_properties &= ~(IlvObjectIsNode|IlvObjectIsLink);
    }

    IL_MLK_DECL();

    inline IlBoolean	isNode() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectIsNode) != 0);
			}
    inline IlBoolean	isNode(IlBoolean v)
			{
			    if (v)
				_properties |=  IlvObjectIsNode;
			    else _properties &= ~IlvObjectIsNode;
			    return v;
			}
    inline IlBoolean	isLink() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectIsLink) != 0);
			}
    inline IlBoolean	isLink(IlBoolean v)
			{
			    if (v)
				_properties |=  IlvObjectIsLink;
			    else _properties &= ~IlvObjectIsLink;
			    return v;
			}
};

// --------------------------------------------------------------------------
enum IlvLinkType {
    IlvLinkFrom = 1,
    IlvLinkTo = 2,
    IlvLinkAny = IlvLinkFrom | IlvLinkTo
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGrapher : public IlvManager
{
public:
    IlvGrapher(IlvDisplay*	display,
	       int		layers    = 2,
	       IlBoolean	useacc    = IlTrue,
	       IlUShort		maxInList = IlvMaxObjectsInList,
	       IlUShort		maxInNode = IlvMaxObjectsInList);
    virtual ~IlvGrapher();

    void		installAccelerators();
    void		bboxAndAddLinks(const IlvGraphic*,
					IlBoolean redraw = IlTrue);
    void		bboxAndRemoveLinks(const IlvGraphic*,
					   IlBoolean redraw = IlTrue);

    // ____________________________________________________________
    // General Purpose Methods

    IlvGraphic* const*	getNodes(int layer, IlUInt& count);

    IlvGraphic* const*	getNodes(IlUInt& count);
    IlvLinkImage* const* getLinks(int layer, IlUInt& count);
    IlvLinkImage* const* getLinks(IlUInt& count);

    // End of General Purpose Methods

    IlvLinkImage* const* getLinks(const IlvGraphic* node,
				  IlUInt& count,
				  IlvLinkType type = IlvLinkAny) const;

    // Obsolete. Use the getLinks method instead.
    inline
    IlvLinkImage* const* linksFrom(const IlvGraphic* node,
				   IlUInt& count) const
			{
			    return getLinks(node, count, IlvLinkFrom);
			}

    // Obsolete. Use the getLinks method instead.
    inline
    IlvLinkImage* const* linksTo(const IlvGraphic* node, IlUInt& count) const
			{
			    return getLinks(node, count, IlvLinkTo);
			}

    IlBoolean		setFromNode(IlvLinkImage* link,
				    IlvGraphic* node,
				    IlvLinkImage* afterFrom = 0,
				    IlBoolean reDraw = IlTrue);

    IlBoolean		setToNode(IlvLinkImage* link,
				  IlvGraphic* node,
				  IlvLinkImage* afterTo = 0,
				  IlBoolean reDraw = IlTrue);

    IlBoolean		nodeHasLinks(const IlvGraphic* node,
				     IlvLinkType type = IlvLinkAny) const;


    // Obsolete. Use the nodeHasLinks method instead.
    inline IlBoolean	nodeHasSons(const IlvGraphic* node) const
			{
			    return nodeHasLinks(node, IlvLinkFrom);
			}

    IlUInt		getLinksCount(const IlvGraphic* node,
				      IlvLinkType type = IlvLinkAny) const;
    virtual void	addNode(IlvGraphic* obj,
				IlBoolean redraw = IlTrue,
				int layer = -1);

    virtual void	addLink(IlvLinkImage* link, 
				IlBoolean redraw = IlTrue,
				int layer = -1,
				IlvLinkImage* afterFrom = 0,
				IlvLinkImage* afterTo   = 0);
    virtual void	removeNode(IlvGraphic* obj, 
				   IlBoolean redraw = IlTrue,
				   IlBoolean destroyIt = IlTrue);
    virtual void	removeLink(IlvLinkImage* link, 
				   IlBoolean redraw = IlTrue,
				   IlBoolean destroyIt = IlTrue);
    virtual void	nodeXPretty(IlvGraphic* node,
				    IlvPos xspacing,
				    IlvPos yspacing,
				    IlBoolean redraw = IlTrue,
				    IlvOrientation orientation = IlvCenter);

    virtual void	nodeYPretty(IlvGraphic* node,
				    IlvPos xspacing,
				    IlvPos yspacing,
				    IlBoolean redraw = IlTrue,
				    IlvOrientation orientation = IlvCenter);

    virtual void	changeNode(IlvGraphic* node,
				   IlvGraphic* newNode,
				   IlBoolean redraw = IlFalse);
    virtual void	changeLink(IlvLinkImage* link,
				   IlvLinkImage* newLink,
				   IlBoolean redraw = IlFalse);
    IlBoolean		isLinkBetween(const IlvGraphic* from,
				      const IlvGraphic* to) const;
    IlBoolean		isNode(const IlvGraphic* obj) const;

    IlBoolean		isLink(const IlvGraphic* obj) const;

    void		mapLinks(IlvGraphic*		node,
				 IlvApplyObject	f,
				 IlAny			arg,
				 IlvLinkType		type);

    void		applyLinks(IlvGraphic*		node,
				   IlvApplyObject	f,
				   IlAny		arg,
				   IlvLinkType		type,
				   IlBoolean		reDraw = IlTrue);

    inline static
    IlvGrapher*		GetGrapher(const IlvGraphic* obj)
			{
			    IlvManager* mgr = getManager(obj);
			    return (mgr &&
				    mgr->isSubtypeOf(IlvGrapher::ClassInfo())) 
				? ILVCAST (IlvGrapher*, mgr)
				: 0;
			}

    virtual IlBoolean	removeObject(IlvGraphic*,
				     IlBoolean redraw = IlTrue,
				     IlBoolean destroyIt = IlTrue);
    virtual
    IlvGraphicSet*	group(IlUInt n, IlvGraphic* const* objs);
    virtual void	unGroup(IlvGraphic* obj, IlBoolean);
    virtual void	duplicate(IlvPos dx = 0, IlvPos dy = 0);
    virtual void	deleteSelections(IlBoolean redraw = IlTrue);

    virtual void	beforeApply(const IlvGraphic*, IlBoolean = IlTrue);
    virtual void	afterApply(const IlvGraphic*, IlBoolean = IlTrue);
    virtual IlBoolean	cleanObj(IlvGraphic* obj,
				 IlBoolean = IlTrue,
				 IlBoolean = IlTrue);
    virtual void	deleteAll(IlBoolean deleteIt, IlBoolean redraw);
    virtual void	deleteAll(int layer,
				  IlBoolean deleteIt,
				  IlBoolean redraw);
    virtual
    IlvManagerInputFile* createInputFile(ILVSTDPREF istream&);
    virtual
    IlvManagerOutputFile* createOutputFile(ILVSTDPREF ostream&) const;
    IlBoolean		isMarked(const IlvGraphic* node) const;
    void		setMarked(IlvGraphic* node, IlBoolean value);
    void		markTree(IlvGraphic*, IlBoolean value = IlTrue);

    virtual
    IlvGrapher*		makeNode(IlvGraphic* obj);

    virtual
    IlvGrapher*		makeLink(IlvGraphic* obj);

    inline void		setLinksEditable(IlBoolean editable)
			{
			    _linksEditable = editable;
			}

    inline IlBoolean	areLinksEditable() const { return _linksEditable; }


    void		moveLinkExtremity(IlvLinkImage* link,
					  IlvLinkType type,
					  const IlvPoint& p,
					  IlBoolean reDraw = IlTrue,
					  IlBoolean addCmd = IlFalse);

    IlvGraphic*		addGhostNode(const IlvPoint& p,
				     int layer = -1,
				     IlBoolean addCmd = IlFalse);

    const char*		getDefaultLinkClass() const
			{
			    return _defaultLinkClass;
			}

    inline void		setDefaultLinkClass(const char* name)
			{
			    _defaultLinkClass = name;
			}
    IlvLinkImage*	createDefaultLink(IlvGraphic* from = 0, 
					  IlvGraphic* to = 0) const;
    inline const char*	getDefaultNodeClass() const
			{
			    return _defaultNodeClass;
			}

    inline void		setDefaultNodeClass(const char* name)
			{
			    _defaultNodeClass = name;
			}
    IlvGraphic*		createDefaultNode() const;

    inline IlvLink*	getLinksFrom(const IlvGraphic* obj) const
			{
			    return (IlvLink*)
				obj->getProperty(LinksFromProperty());
			}
    inline IlvLink*	getLinksTo(const IlvGraphic* obj) const
			{
			    return (IlvLink*)
				obj->getProperty(LinksToProperty());
			}

    // Symbols
    inline
    static IlSymbol*	LinksFromProperty() { return _linksFromProperty; }
    inline
    static IlSymbol*	LinksToProperty()   { return _linksToProperty;   }

    static IlSymbol*	_linksFromProperty;
    static IlSymbol*	_linksToProperty;
    static IlSymbol*	_nodeLinkTag;

    // Accessors
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    static void		GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);

    static IlSymbol*	AddNodeMethod();
    static IlSymbol*	IsNodeMethod();
    static IlSymbol*	AddLinkMethod();
    static IlSymbol*	IsLinkMethod();
    static IlSymbol*	LinksEditableValue();
    static IlSymbol*	DefaultLinkClassValue();
    static IlSymbol*	DefaultNodeClassValue();

    IlvDeclareLazyPropClassInfo();

protected:
    IlBoolean		_linksEditable;
    IlString		_defaultLinkClass;
    IlString		_defaultNodeClass;

    void		nodeInternalXPretty(IlvGraphic* node,
					    IlvPos dx,
					    IlvPos dy,
					    IlvDim height,
					    IlvOrientation orientation);
    void		nodeInternalYPretty(IlvGraphic* node,
					    IlvPos dx,
					    IlvPos dy,
					    IlvDim width,
					    IlvOrientation orientation);
    virtual
    IlvObjectProperty*	makeObjectProperty(int layer = 0);
    void		nodeAddLinkFrom(IlvGraphic* node,
					IlvLinkImage* link,
					IlvLinkImage*);
    void		nodeAddLinkTo(IlvGraphic* node,
				      IlvLinkImage* link,
				      IlvLinkImage*);
    void		nodeRemoveLinkFrom(IlvGraphic* node,
					   IlvLinkImage* link);
    void		nodeRemoveLinkTo(IlvGraphic* node, IlvLinkImage* link);
    IlvDim		nodeHeight(const IlvGraphic* node, IlvPos);
    IlvDim		nodeWidth(const IlvGraphic* node, IlvPos);
    void		nodeBBoxSons(const IlvGraphic* node,
				     IlBoolean erase = IlTrue,
				     IlBoolean marked = IlTrue);
    void		nodeBBoxLinks(const IlvGraphic* node,
				      IlBoolean erase = IlTrue);    
};


// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvSelectNodeFilter : public IlvGraphicFilter
{
public:
    IlvSelectNodeFilter(IlvGrapher* grapher) : _grapher(grapher) {}

    virtual IlBoolean	accept(const IlvGraphic* object) const;

private:
    IlvGrapher*		_grapher;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvSelectLinkFilter : public IlvGraphicFilter
{
public:
    IlvSelectLinkFilter(IlvGrapher* grapher) : _grapher(grapher) {}

    virtual IlBoolean	accept(const IlvGraphic* object) const;

private:
    IlvGrapher*		_grapher;
};

ILVGRAPHMODULEINIT(g2grapher);
#endif /* !__Ilv_Grapher_Grapher_H */
