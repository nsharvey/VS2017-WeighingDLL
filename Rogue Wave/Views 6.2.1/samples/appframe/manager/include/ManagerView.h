// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/include/ManagerView.h
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
// IlogViews 4 generated header file
// File generated Wed Mar 08 20:35:33 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the ManagerView class
// --------------------------------------------------------------------------
#if !defined(ManagerView__header__)
#define ManagerView__header__

#if !defined(__Ilv_Appframe_Managvw_H)
#include <ilviews/appframe/manager/managvw.h>
#endif /* !__Ilv_Appframe_Managvw_H */

class ManagerDocument;
class IlvDrawSelection;
// --------------------------------------------------------------------------
// ManagerView class
// --------------------------------------------------------------------------

class ManagerView
: public IlvDvManagerView
{
    IlvDvDeclareViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ManagerView(IlvGadgetContainer*);
    virtual ~ManagerView();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    ManagerDocument* getManagerDocument() const;

    // ----------------------------------------------------------------------
    // Specific methods
    void setActiveSelection(IlvGraphic*);
    void unactiveSelection();
    void removedFromSelection(IlvGraphic* graphic);
    void doTranslate(const IlvPoint& point);
    void doReshape(IlvGraphic* graphic, const IlvRect& rect);
    void selectionChanged();
    void deleteSelectedGraphics();
    void cut();
    void paste();

    // ----------------------------------------------------------------------
    // Export ManagerView fields and methods
    IlvDvDeclareInterface();

protected:
    IlvGraphic* _activeSelection;
    IlvPalette* _activePalette;
    IlvPalette* _unactivePalette;

    void align(IlvPosition side);
    void alignLeft();
    void alignRight();
    void alignTop();
    void alignBottom();
    void sameWidth();
    void sameHeight();
    void centerVerticaly();
    void centerHorizontaly();
    virtual void alignmentUI(IlvDvActionDescriptor*) const;
    void reDrawSelection(IlvDrawSelection*);
    virtual void undo();
    virtual void setUndoUI(IlvDvActionDescriptor*);
    virtual void redo();
    virtual void setRedoUI(IlvDvActionDescriptor*);
    void deleteUI(IlvDvActionDescriptor*);
};

// --------------------------------------------------------------------------
IL_MODULEINIT(ManagerView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !ManagerView__header__ */
