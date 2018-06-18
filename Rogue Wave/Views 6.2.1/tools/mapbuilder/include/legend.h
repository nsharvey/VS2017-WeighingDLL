// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/legend.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the Legend class
// -------------------------------------------------------------------------
#ifndef _Legend_h_
#define _Legend_h_

#include <ilviews/manager/layer.h>
#include <ilviews/manager/manager.h>
#include <ilviews/manager/observer.h>
#include <ilviews/manager/selinter.h>

#include <ilviews/base/gadget.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/rectgadc.h>

class IlvGadgetContainerRectangle;
class IlvScrolledComboBox;
class IlvViewRectangle;
class IlvToggle;
class IlvTextField;
class IlvLabel;
class IlvSelector;

// -------------------------------------------------------------------------
// Handles contextual menus
// -------------------------------------------------------------------------
class ContextualMenuInteractor
    : public IlvGadgetInteractor
{
public:
    ContextualMenuInteractor() {};
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic* obj,
				  IlvEvent&,
				  const IlvTransformer* t);
    virtual IlBoolean shouldShowMenu(IlvGraphic*,
				     IlvEvent&,
				     const IlvTransformer*) const;
    virtual IlvPopupMenu* getMenu(IlvGraphic*,
				  IlvEvent&,
				  const IlvTransformer*) const = 0;
};

// -------------------------------------------------------------------------
//
// -------------------------------------------------------------------------
class Legend
: public IlvGadgetContainerRectangle
{
    friend class LegendManagerObserver;
    friend class LegendCallbacks;

public:
    Legend(IlvDisplay* display,const IlvRect& rect);
    virtual ~Legend();
    virtual IlvView* createView(IlvAbstractView*, const IlvRect&);

    virtual void setTargetView(IlvView* view);

    // A legend is composed of 3 components:
    //  - a toggle that show/set the visibility status + the name of
    //    the layer
    //  - a graphic object that serves as a preview of objects
    //    corresponding to the layer
    // The following method returns the later + a direction for the place
    // where the label is to be displayed
    virtual IlvGraphic* getLayerRepresentation(IlvManagerLayer* layer);

    // returns the matrix
    IlvMatrix* getMatrix() { return _matrix; }
    IlInt getLastSelectedItem() const { return _lastSelectedItem; }
    void setLastSelectedItem(IlInt i) { _lastSelectedItem = i; }
    IlvView* getCurrentView() { return _currentView; }
    void createAllLegend();
    void createLayerLegend(IlInt layerindex);
    IlvManagerObserver* getObserver() const { return _managerObserver; }

protected:
    IlBoolean updateLayerLegendName(IlInt layerindex);
    IlBoolean updateLayerRepresentation(IlInt layerindex);

private:
    IlvView*  _currentView;   // current view this legend is attached to
    IlvManagerObserver* _managerObserver;
    IlvMatrix* _matrix;
    IlInt _lastSelectedItem;
};

// -------------------------------------------------------------------------
//
// -------------------------------------------------------------------------
class LegendGadgetInteractor
    : public ContextualMenuInteractor
{
    Legend* _legend;
public:
    LegendGadgetInteractor(Legend* legend)
	: _legend(legend)
    {}
    virtual IlvPopupMenu* getMenu(IlvGraphic*,
				  IlvEvent&,
				  const IlvTransformer*) const;

    static void SetSelectedItem(IlvPopupMenu*,
				Legend*,
				IlvAbstractMatrixItem*);

    static IlvAbstractMatrixItem* GetSelectedItem(const IlvPopupMenu*);
};

#endif /* !_Legend_h_ */
