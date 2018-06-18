// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/holder.h
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
// Declaration of the IlvManagerGraphicHolder class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Holder_H
#define __Ilv_Manager_Holder_H

#if !defined(__Ilv_Graphics_Holder_H)
#include <ilviews/graphics/holder.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerGraphicHolder
    : public IlvGraphicHolder
{
public:
    IlvManagerGraphicHolder(IlvManager* mgr);
    // ____________________________________________________________
    inline void			setCurrentView(IlvView* view) { _view = view; }
    virtual IlvManager*		getManager() const;
    virtual IlvCommandHistory*	getCommandHistory() const;
    inline void			setView(IlvView* view) { _view = view; }
    //
    virtual IlvDisplay*		getDisplay() const;
    virtual IlvTransformer*	getTransformer() const;
    virtual IlvPalette*		palette() const;
    virtual IlBoolean		isAContainer() const;

    virtual void		moveFocusAfter(IlBoolean redraw = IlTrue);
    virtual void		moveFocusBefore(IlBoolean redraw = IlTrue);
    virtual IlBoolean		allowFocus(IlBoolean flag);
    virtual IlBoolean		isFocusAllowed() const;
    virtual void		removeGrab();
    virtual void		setGrab(IlvGraphic*);
    virtual IlBoolean		grab(IlvCursor* cursor = 0);
    virtual void		unGrab();
    virtual void		handleInput(IlvEvent& event);
    virtual IlvEvent*		getLastEvent() const;
    virtual void		reDraw();
    virtual void		reDraw(const IlvRegion* region);
    virtual void		bufferedDraw(const IlvGraphic*);
    virtual void		bufferedDraw(const IlvRect& rect);
    virtual void		bufferedDraw(const IlvRegion& region);
    virtual void		globalBBox(IlvRect& bbox) const;
    virtual IlvBitmap*		getBitmap() const;
    virtual IlvView*		getView() const;
    virtual void		setPropertyToGraphic(IlvGraphic*) const;
    virtual IlvHGadgetInteractor*
				getHGadgetInteractor(const IlvGraphic*) const;
    virtual IlBoolean		objectHasInteractor(const IlvGraphic*) const;
    virtual IlvGraphic*		getFocus() const;
    virtual void		setFocus(IlvGraphic* g = 0,
					 IlBoolean     = IlTrue) const;
    virtual void		moveFocusFirst();
    virtual void		moveFocusLast();
    virtual void		applyToObject(IlvGraphic*    obj,
					      IlvApplyObject f,
					      IlAny          arg,
					      IlBoolean      redraw = IlTrue);
    virtual void		selectionRequest(const IlvGraphic*);
    virtual void		cleanSelection(const IlvGraphic*);
    virtual IlBoolean		setObjectName(IlvGraphic* obj,
					      const char*);
    virtual const char*		getObjectName(const IlvGraphic* obj) const;
    virtual const char*		getObjectInteractor(const IlvGraphic*) const;
    virtual IlBoolean		setObjectInteractor(IlvGraphic* obj,
						    const char*);
    virtual IlBoolean		isVisible(const IlvGraphic* obj) const;
    virtual void		setVisible(IlvGraphic* obj,
					   IlBoolean visible,
					   IlBoolean redraw);
    virtual IlBoolean		isDisplayed(const IlvGraphic* obj,
					    const IlvPort*    dst) const;
    virtual IlvGraphic* const*	getObjects(IlUInt& count) const;
    virtual IlvGraphic*		getObject(const char*) const;
    virtual void		addObject(IlvGraphic* obj,
					  IlBoolean redraw);
    virtual void		addObject(const char* objectName,
					  IlvGraphic* obj,
					  IlBoolean   redraw);
    virtual IlBoolean		removeObject(IlvGraphic* obj,
					     IlBoolean   redraw);
    virtual void		moveObject(IlvGraphic*,
					   const IlvPoint& p,
					   IlBoolean       redraw);
    virtual void		translateObject(IlvGraphic*,
						IlvPos    dx,
						IlvPos    dy,
						IlBoolean redraw);
    virtual void		reshapeObject(IlvGraphic*,
					      const IlvRect& p,
					      IlBoolean      redraw);
    virtual void		pop(IlvGraphic*,
				    IlBoolean redraw);
    virtual void		push(IlvGraphic*,
				     IlBoolean redraw);
    virtual IlvGraphic*		lastContains(const IlvPoint&,
					     const IlvView*) const;

    virtual void		invalidateRegion(const IlvRect& r);
    virtual void		invalidateRegion(const IlvGraphic* obj);
    virtual void		invalidateRegion(const IlvRegionUpdater&,
						 const IlvGraphic* = 0);
    virtual IlBoolean		isInvalidating() const;
    virtual IlvRegion*		updateRegion() const;
    virtual void		flushRedraw();
    virtual void		initReDraws();
    virtual void		draw(IlvRegion*);
    virtual void		reDrawViews();

    // Look, Language and Bidi callbacks.
    virtual void		changeLook();
    virtual void		changeLanguage();
    virtual void		changeLayoutAttributes(IlAny,
						       IlAny);

    virtual int			read(IL_STDPREF istream& stream);
    virtual int			read(const char* filename);

protected:
    IlvManager*			_manager;
    IlvView*			_view;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerGadgetInteractor
    : public IlvManagerObjectInteractor
{
public:
    IlvManagerGadgetInteractor()
    : IlvManagerObjectInteractor(),
      _hGadgetInteractor(0)
    {}
    ~IlvManagerGadgetInteractor();
    // ____________________________________________________________
    virtual const char*		className() const;
    virtual IlBoolean		handleEvent(IlvManager*,
					    IlvGraphic*,
					    IlvEvent&,
					    IlvView*,
					    IlvTransformer*);
    virtual IlBoolean		accept(const IlvGraphic*) const;
    inline IlvHGadgetInteractor*	getHGadgetInteractor() const
					{
					    return _hGadgetInteractor;
					}

protected:
    IlvHGadgetInteractor*	_hGadgetInteractor;
};

// --------------------------------------------------------------------------
ILVMGRMODULEINIT(m0_holder);

#endif /* __Ilv_Manager_Holder_H */
