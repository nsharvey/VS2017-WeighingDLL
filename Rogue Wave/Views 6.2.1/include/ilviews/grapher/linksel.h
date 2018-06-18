// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/linksel.h
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
// Declaration of the IlvGraphLinkSelection and IlvLinkInteractor classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Linksel_H
#define __Ilv_Grapher_Linksel_H

#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif
#if !defined(__Ilv_Grapher_Links_H)
#include <ilviews/grapher/links.h>
#endif
#if !defined(__Ilv_Grapher_Polylink_H)
#include <ilviews/grapher/polylink.h>
#endif

class ILVGRAPHEXPORTED IlvLinkImage;

class ILVGRAPHEXPORTED IlvGraphLinkSelection
: public IlvDrawSelection {
public:
    IL_MLK_DECL();
    IlvGraphLinkSelection(IlvDisplay* display,
			  IlvGraphic* object,
			  IlvDim      size    = 0,
			  IlvPalette* palette = 0);

    virtual void draw(IlvPort* dst, const IlvTransformer* t,
		      const IlvRegion* clip = 0) const;

    virtual void boundingBox(IlvRect& r, const IlvTransformer* t = 0) const;
    virtual void computeRegion(IlvRegion& r,
			       const IlvTransformer* t = 0) const;

    virtual IlUInt getHandlesCount(const IlvTransformer* t=0) const;
    virtual IlBoolean getHandleLocation(IlUInt idx, 
					 IlvPoint& p,
					 const IlvTransformer* t) const;

    virtual IlUInt whichHandle(const IlvPoint& p,
				const IlvTransformer* t = 0) const;

    virtual IlvInteractor* getSelectionInteractor() const;
    IlvLinkImage* getLink() const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvGraphLinkSelection);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvLinkGhostHandler
{
public: 
    IlvLinkGhostHandler(IlvLinkType type,
			IlvLinkImage* ghost);

    ~IlvLinkGhostHandler();

    void update(IlvGraphic*,
		IlvGrapherPin*,
		IlUInt);

    void update(const IlvPoint&);

    void draw(IlvPort* dst,const IlvTransformer* t,const IlvRegion* = 0);
    inline IlvLinkImage* getGhost() const { return _linkGhost; }
    IlBoolean isFreeEnd() const;

private:
    IlvLinkType	    _type;
    IlvLinkImage*   _linkGhost;
    IlvGraphic*	    _nodeGhost;
    void cleanPin();
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvLinkInteractor 
: public IlvInteractor {
public:
    IlvLinkInteractor();
    virtual ~IlvLinkInteractor();

    virtual IlBoolean handleEvent(IlvGraphic* g, 
				  IlvEvent& event,
				  const IlvTransformer* t = 0);

    virtual void endOperation();

    virtual IlBoolean handleButtonDown(IlvGraphLinkSelection* sel,
				       IlvEvent& event,
				       const IlvTransformer* t = 0);
    virtual IlBoolean handleButtonUp(IlvGraphLinkSelection* sel,
				     IlvEvent& event,
				     const IlvTransformer* t = 0);
    virtual IlBoolean handleButtonDragged(IlvGraphLinkSelection* sel,
					  IlvEvent& event,
					  const IlvTransformer* t = 0);

    virtual void handleExpose(IlvView*, 
			      const IlvTransformer*,
			      IlvRegion*);

    virtual IlBoolean accept(const IlvGraphic* obj) const;

    virtual IlBoolean canEditPoint(IlvGraphLinkSelection* sel,
				    IlUInt index,
				    const IlvTransformer* t);

    inline IlvLinkImage* getLinkGhost() const
	{
	    return _ghostHandler
		? _ghostHandler->getGhost()
		: 0; 
	}

    inline static IlvMakeSelection
	SetMakeNodeSelection(IlvMakeSelection mksel) 
	{
	    IlvMakeSelection old = _makeNodeSelection;
	    _makeNodeSelection = mksel;
	    return old;
	}

    DeclareLazyInteractorTypeInfoRO(IlvLinkInteractor);
protected:
    IlUInt		    _pointIndex;
    IlvLinkType		    _type;
    IlBoolean		    _wasSelected;
    IlvLinkGhostHandler*    _ghostHandler;
    IlBoolean		    _allowDrawGhost;

    static IlvMakeSelection _makeNodeSelection;

    void highlight(IlvGraphic* g, IlBoolean b);
    // Ghost handling
    void drawGhost(IlvPort* dst,const IlvTransformer* t);
    void initLinkGhost(const IlvGraphLinkSelection* sel);
    void endLinkGhost();

};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvOneLinkInteractor 
: public IlvLinkInteractor {
public:
    IlvOneLinkInteractor() {}

    virtual IlBoolean handleButtonUp(IlvGraphLinkSelection* sel,
				     IlvEvent& event,
				     const IlvTransformer* t = 0);
    virtual IlBoolean handleButtonDragged(IlvGraphLinkSelection* sel,
					  IlvEvent& event,
					  const IlvTransformer* t = 0);

    inline IlvOneLinkImage* getOneLink(const IlvGraphLinkSelection* sel) const
	{ 
	    return sel->getLink()->isSubtypeOf(IlvOneLinkImage::ClassInfo())
		? ILVCAST(IlvOneLinkImage*,sel->getLink())
		: 0;
	}

    inline IlvOneLinkImage* getOneLinkGhost() const 
	{ return ILVCAST(IlvOneLinkImage*,getLinkGhost()); }

    virtual IlBoolean accept(const IlvGraphic* obj) const;

    DeclareLazyInteractorTypeInfoRO(IlvOneLinkInteractor);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvArcLinkInteractor 
: public IlvLinkInteractor {
public:
    IlvArcLinkInteractor() {}

    virtual IlBoolean handleButtonUp(IlvGraphLinkSelection* sel,
				      IlvEvent& event,
				      const IlvTransformer* t = 0);

    virtual IlBoolean handleButtonDragged(IlvGraphLinkSelection* sel,
					   IlvEvent& event,
					   const IlvTransformer* t = 0);

    inline IlvArcLinkImage* getArcLink(const IlvGraphLinkSelection* sel) const
	{ 
	    return sel->getLink()->isSubtypeOf(IlvArcLinkImage::ClassInfo())
		? ILVCAST(IlvArcLinkImage*,sel->getLink())
		: 0;
	}

    inline IlvArcLinkImage* getArcLinkGhost() const 
	{ return ILVCAST(IlvArcLinkImage*,getLinkGhost()); }

    virtual IlBoolean accept(const IlvGraphic* obj) const;

    DeclareLazyInteractorTypeInfoRO(IlvArcLinkInteractor);
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvPolyLinkInteractor 
: public IlvLinkInteractor {
public:
    IlvPolyLinkInteractor();
    virtual ~IlvPolyLinkInteractor();

    virtual IlBoolean handleButtonDragged(IlvGraphLinkSelection* sel,
					   IlvEvent& event,
					   const IlvTransformer* t = 0);
    virtual IlBoolean handleButtonUp(IlvGraphLinkSelection* sel,
				      IlvEvent& event,
				      const IlvTransformer* t = 0);


    IlvPolylineLinkImage* getPolyLink(const IlvGraphLinkSelection* sel) const
	{ 
	    return sel->getLink()->
		isSubtypeOf(IlvPolylineLinkImage::ClassInfo())
		? ILVCAST(IlvPolylineLinkImage*,sel->getLink())
		: 0;
	}

    IlvPolylineLinkImage* getPolyLinkGhost() const 
	{ return ILVCAST(IlvPolylineLinkImage*,getLinkGhost()); }

    virtual IlBoolean accept(const IlvGraphic* obj) const;

    DeclareLazyInteractorTypeInfoRO(IlvPolyLinkInteractor);
};

ILVGRAPHMODULEINIT(glinksel);
#endif /* !__Ilv_Grapher_Linksel_H */
