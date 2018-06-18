// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/inters.h
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
// Definition of predefined grapher interactor classes
// Defined in library grapher
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Inters_H
#define __Ilv_Grapher_Inters_H

#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Grapher_Links_H)
#include <ilviews/grapher/links.h>
#endif
#if !defined(__Ilv_Grapher_Selinter_H)
#include <ilviews/grapher/selinter.h>
#endif
#if !defined(__Ilv_Grapher_Pinedit_H)
#include <ilviews/grapher/pinedit.h>
#endif

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeNodeInteractorFactory
{
public:
    virtual ~IlvMakeNodeInteractorFactory();

    virtual IlvGraphic*	createNode(IlvManager* mgr,
				   const IlvRect& rect) const = 0;
protected:
    IlvMakeNodeInteractorFactory() {}
};

class ILVGRAPHEXPORTED IlvMakeNodeInteractor
    : public IlvDragRectangleInteractor
{
public:
    IlvMakeNodeInteractor(IlvManager* mgr, IlvView* v)
	: IlvDragRectangleInteractor(mgr, v), _factory(0)
    {}
    IlvMakeNodeInteractor() : IlvDragRectangleInteractor(), _factory(0) {}

    ~IlvMakeNodeInteractor();

    virtual void	doIt(IlvRect& rect);

    IlvMakeNodeInteractorFactory* getFactory() const { return _factory; }

    IlvMakeNodeInteractorFactory*
		setFactory(IlvMakeNodeInteractorFactory* factory);

    IlvMakeNodeInteractor(IlvInputFile&);

    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvMakeNodeInteractorFactory* _factory;

    virtual IlvGraphic*	createNode(const IlvRect& rect);
};


class ILVGRAPHEXPORTED IlvMakeShadowNodeInteractor
    : public IlvMakeNodeInteractor
{
public:
    IlvMakeShadowNodeInteractor(IlvManager* mgr, IlvView* v)
	: IlvMakeNodeInteractor(mgr, v)
    {}
    IlvMakeShadowNodeInteractor() : IlvMakeNodeInteractor() {}

    IlvMakeShadowNodeInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    virtual IlvGraphic* createNode(const IlvRect& rect);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeReliefNodeInteractor
    : public IlvMakeNodeInteractor
{
public:
    IlvMakeReliefNodeInteractor(IlvManager* mgr, IlvView* v)
	: IlvMakeNodeInteractor(mgr, v)
    {}
    IlvMakeReliefNodeInteractor() : IlvMakeNodeInteractor() {}

    IlvMakeReliefNodeInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    virtual IlvGraphic* createNode(const IlvRect& rect);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeLinkInteractorFactory
{
public: 
    virtual ~IlvMakeLinkInteractorFactory();

    virtual
    IlvLinkImage*	createLink(IlvDisplay* dpy,
				   IlvGraphic* from,
				   IlvGraphic* to,
				   IlBoolean  oriented) const = 0;

protected:
    IlvMakeLinkInteractorFactory(){}
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGrapherPin;
class ILVGRAPHEXPORTED IlvLinkGhostHandler;
class ILVGRAPHEXPORTED IlvMakeLinkInteractor : public IlvManagerViewInteractor
{
    friend class IlvMakeLinkFilter;
public:
    IlvMakeLinkInteractor(IlvManager* mgr,
			  IlvView*    v,
			  IlBoolean  oriented = IlTrue);
    IlvMakeLinkInteractor(IlBoolean oriented = IlTrue);

    virtual ~IlvMakeLinkInteractor();

    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	handleExpose(IlvRegion* clip = 0);
    virtual void	abort() ;
    virtual void	init() ;
    virtual void	drawGhost();
    virtual void	doIt(IlvGraphic* from, IlvGraphic* to);
    IlvGraphic*		getFrom() const {return _firstNode; }
    IlvGrapherPin*	getFromPin()      const { return _firstPin; }
    IlUInt		getFromPinIndex() const { return _firstIdx; }
    IlvGraphic*		getTo() const { return _secondNode; }
    IlvGrapherPin*	getToPin() const { return _secondPin; }
    IlUInt		getToPinIndex() const { return _secondIdx; }
    IlBoolean		isOriented() const { return _oriented; }
    void		setOriented(IlBoolean oriented)
			{
			    _oriented = oriented;
			}
    IlvMakeLinkInteractorFactory* getFactory() const { return _factory; }

    IlvMakeLinkInteractorFactory*
		setFactory(IlvMakeLinkInteractorFactory* factory);

    IlvMakeSelection	setMakeNodeSelection(IlvMakeSelection mksel) 
			{
			    IlvMakeSelection old = _makeNodeSelection;
			    _makeNodeSelection = mksel;
			    return old;
			}

    void		useLinkGhost(IlBoolean useLink)
			{
			    _useLinkGhost = useLink;
			}

    IlBoolean		isUsingLinkGhost() const { return _useLinkGhost;}

    void		handlePointerMoved(IlBoolean b)
			{
			    _handlePointerMoved = b;
			}

    IlBoolean		isHandlingPointerMoved() const
			{
			    return _handlePointerMoved ;
			}

    IlvMakeLinkInteractor(IlvInputFile&);

    DeclareLazyManagerViewInteractorInfo();

protected:
    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

     virtual void	storeLink(IlvLinkImage* link);

    virtual IlBoolean	acceptFrom(IlvGraphic* obj);

    virtual IlBoolean	acceptTo(IlvGraphic* obj);
    virtual void	storePinInfo(IlvGraphic* link);
    void		initLinkGhost();
    void		endLinkGhost();


    IlBoolean		findFromNode(const IlvPoint& p);

    IlBoolean		findToNode(const IlvPoint& p);

    virtual void	highlight(IlvGraphic* node, IlBoolean highlight);

    IlBoolean			_oriented;
    IlvGraphic*			_firstNode;
    IlvGrapherPin*		_firstPin;
    IlUInt			_firstIdx;
    IlvGraphic*			_secondNode;
    IlvGrapherPin*		_secondPin;
    IlUInt			_secondIdx;
    IlvPoint			_prev;
    IlvPoint			_first;
    IlvMakeLinkInteractorFactory* _factory;
    IlvLinkGhostHandler*	_ghostHandler;
    IlvMakeSelection		_makeNodeSelection;
    IlBoolean			_useLinkGhost;
    IlBoolean			_handlePointerMoved;

    void initialize();
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeLinkImageInteractor
    : public  IlvMakeLinkInteractor
{
public:
    IlvMakeLinkImageInteractor(IlvManager*  mgr,
			       IlvView*	    v,
			       IlBoolean    oriented = IlTrue)
	: IlvMakeLinkInteractor(mgr, v, oriented)
    {}
    IlvMakeLinkImageInteractor(IlBoolean oriented = IlTrue)
	: IlvMakeLinkInteractor(oriented)
    {}

    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

    IlvMakeLinkImageInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeLabelLinkImageInteractor
    : public IlvMakeLinkInteractor
{
public:
    IlvMakeLabelLinkImageInteractor(IlvManager* mgr,
				    IlvView*    v,
				    IlBoolean	oriented = IlTrue)
	: IlvMakeLinkInteractor(mgr, v, oriented)
    {}
    IlvMakeLabelLinkImageInteractor(IlBoolean oriented = IlTrue)
	: IlvMakeLinkInteractor(oriented)
    {}

    inline const char*	getLabel() const { return _label; }
    inline void		setLabel(const char* label) { _label = label;}

    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

    IlvMakeLabelLinkImageInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

private:
    IlString		_label;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeOneLinkImageInteractor
    : public IlvMakeLinkInteractor
{
public:
    IlvMakeOneLinkImageInteractor(IlvManager*	     mgr,
				  IlvView*	     v,
				  IlBoolean	     oriented = IlTrue,
				  IlvLinkOrientation o = IlvVerticalLink)
	: IlvMakeLinkInteractor(mgr, v, oriented),
	  _orientation(o)
    {}
    IlvMakeOneLinkImageInteractor(IlBoolean          oriented  = IlTrue,
				  IlvLinkOrientation o = IlvVerticalLink)
	: IlvMakeLinkInteractor(oriented),
	  _orientation(o)
    {}

    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

    inline
    IlvLinkOrientation getOrientation() const { return _orientation; }
    inline void		setOrientation(IlvLinkOrientation o)
			{
			    _orientation = o;
			}

    IlvMakeOneLinkImageInteractor(IlvInputFile&);

    DeclareLazyManagerViewInteractorInfo();

protected:
    IlvLinkOrientation	_orientation;
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeOneSplineLinkImageInteractor
    : public  IlvMakeOneLinkImageInteractor
{
public:
    IlvMakeOneSplineLinkImageInteractor(IlvManager* mgr,
					IlvView*    v,
					IlBoolean   oriented  = IlTrue,
					IlvLinkOrientation o = IlvVerticalLink)
	: IlvMakeOneLinkImageInteractor(mgr, v, oriented, o)
    {}
    IlvMakeOneSplineLinkImageInteractor(IlBoolean oriented  = IlTrue,
					IlvLinkOrientation o = IlvVerticalLink)
	: IlvMakeOneLinkImageInteractor(oriented, o)
    {}

    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

    IlvMakeOneSplineLinkImageInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeDoubleLinkImageInteractor
    : public  IlvMakeLinkInteractor
{
public:
    IlvMakeDoubleLinkImageInteractor(IlvManager*    mgr,
				     IlvView*	    v,
				     IlBoolean	    oriented = IlTrue)
	: IlvMakeLinkInteractor(mgr, v, oriented)
    {}
    IlvMakeDoubleLinkImageInteractor(IlBoolean oriented = IlTrue)
	: IlvMakeLinkInteractor(oriented)
    {}

    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

    IlvMakeDoubleLinkImageInteractor(IlvInputFile&);

    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvMakeDoubleSplineLinkImageInteractor
    : public  IlvMakeDoubleLinkImageInteractor
{
public:
    IlvMakeDoubleSplineLinkImageInteractor(IlvManager*	mgr,
					   IlvView*	v,
					   IlBoolean	oriented = IlTrue)
	: IlvMakeDoubleLinkImageInteractor(mgr, v, oriented)
    {}
    IlvMakeDoubleSplineLinkImageInteractor(IlBoolean oriented = IlTrue)
	: IlvMakeDoubleLinkImageInteractor(oriented)
    {}

    virtual
    IlvLinkImage*	createLink(IlvGraphic* from, IlvGraphic* to) const;

    IlvMakeDoubleSplineLinkImageInteractor(IlvInputFile&);

    DeclareLazyManagerViewInteractorInfoRO();
};

ILVGRAPHMODULEINIT(mknode);
ILVGRAPHMODULEINIT(mklink);
ILVGRAPHMODULEINIT(mkonelink);
ILVGRAPHMODULEINIT(mktwolink);
#endif /* !__Ilv_Grapher_Inters_H */
