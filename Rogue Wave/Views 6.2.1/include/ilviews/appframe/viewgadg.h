// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/viewgadg.h
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
// Declaration of the IlvDvTextView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Viewgadg_H)
#define __Ilv_Appframe_Viewgadg_H

#if !defined(__Ilv_Appframe_View_H)
#include <ilviews/appframe/view.h>
#endif
#if !defined(__Ilv_Gadgets_Text_H)
#include <ilviews/gadgets/text.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Appframe_Gadgets_Gadgets_H)
#include <ilviews/appframe/gadgets/gadgets.h>
#endif
#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif

class IlvPopupMenu;

// --------------------------------------------------------------------------
// IlvDvTextView class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvTextView : public IlvText, public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvTextView(IlvDisplay* display);
    virtual ~IlvDvTextView();

    // ----------------------------------------------------------------------
    // Main overridables

    virtual void	initializeView();
    virtual void	cut();
    virtual void	paste();
    virtual void	selectAll();
    virtual void	deleteSelection();
    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvGraphic* getGraphic() { return this; }
    IlUShort		getCursorLine() const;
    IlUShort		getCursorColumn() const;
    void		setCursorPosition(IlUShort line, IlUShort col);
    void		insertTextAt(const char*,
				     IlUShort line,
				     IlUShort col,
				     IlBoolean bRedraw = IlTrue);
    void		setSelectionAt(IlUShort lineBeg,
				       IlUShort colBeg,
				       IlUShort lineEnd,
				       IlUShort colEnd);
    IlUShort		getSelectionBeginLine() const;
    IlUShort		getSelectionBeginColumn() const;
    IlUShort		getSelectionEndLine() const;
    IlUShort		getSelectionEndColumn() const;
    IlUShort		locateWordBeginLine(IlUShort line, IlUShort col);
    IlUShort		locateWordBeginColumn(IlUShort line, IlUShort col);
    IlUShort		locateWordEndLine(IlUShort line, IlUShort col);
    IlUShort		locateWordEndColumn(IlUShort line, IlUShort col);
    void		insertCharAt(IlUShort line, IlUShort col, IlInt c);
    void		removeCharAt(IlUShort line, IlUShort col);
    void		cutLineAt(IlUShort line, IlUShort col);
    void		ensureVisibleAt(IlUShort line, IlUShort col);

    // ----------------------------------------------------------------------
    // Query / apply values
    IlvDvDeclareAccessors();

    static IlSymbol*	_TextSymbol;

    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

    // ----------------------------------------------------------------------
    // Specific callbacks
    virtual void	valueChanged();

protected:
    virtual
    IlvDvDocViewContext* createViewContext();
    virtual
    IlvDvDocViewContext* getViewContext() const;

    void		setCutUI(IlvDvActionDescriptor*) const;
    void		setPasteUI(IlvDvActionDescriptor*) const;
    virtual void	selectionChanged();

    IlvDvDocViewContext* _context;
};

// --------------------------------------------------------------------------
// IlvDvListView class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListView
    : public IlvDvStringList, public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvListView(IlvDisplay* display);
    virtual ~IlvDvListView();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvGraphic*		getGraphic() { return this; }

    // ----------------------------------------------------------------------
    // Query / apply values
    IlvDvDeclareAccessors();

protected:
    IlvDvDocViewContext*	_context;

    virtual
    IlvDvDocViewContext*	createViewContext();
    virtual
    IlvDvDocViewContext*	getViewContext() const;
};

// --------------------------------------------------------------------------
// IlvDvTreeView class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvTreeView
    : public IlvDvTreeGadget, public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvTreeView(IlvDisplay* display);
    virtual ~IlvDvTreeView();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvGraphic*		getGraphic() { return this; }

    // ----------------------------------------------------------------------
    // Query / apply values
    IlvDvDeclareAccessors();

protected:
    IlvDvDocViewContext*	_context;
    virtual
    IlvDvDocViewContext*	createViewContext();
    virtual
    IlvDvDocViewContext*	getViewContext() const;

    virtual void		activateSelection();

    virtual void		rightClickOnItem(IlvTreeGadgetItem* item,
						 const IlvPoint& pt);

    virtual IlvPopupMenu* getPopupMenuForItem(const IlvTreeGadgetItem* item);

    virtual const IlSymbol*
		getPopupMenuResourceId(const IlvTreeGadgetItem* item) const;

    // Popup menus management
    IlvAList			_popupMenus;
    virtual IlvPopupMenu*	createPopupMenu(const IlSymbol* resId) const;

public:
    virtual IlBoolean		handleTreeEvent(IlvEvent&);
};

// --------------------------------------------------------------------------
// IlvDvMatrixView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif

class ILVDVCLASS IlvDvMatrixView
    : public IlvMatrix, public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvMatrixView(IlvDisplay* display);
    virtual ~IlvDvMatrixView();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvGraphic*		getGraphic() { return this; }

    // ----------------------------------------------------------------------
    IlvDvDeclareAccessors();
    IlvDvDeclareInterface();

protected:
    IlvDvDocViewContext*	_context;

    virtual
    IlvDvDocViewContext*	createViewContext();
    virtual
    IlvDvDocViewContext*	getViewContext() const;
};

// --------------------------------------------------------------------------
// IlvDvSheetView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Gadgets_Sheet_H)
#include <ilviews/gadgets/sheet.h>
#endif


class ILVDVCLASS IlvDvSheetView : public IlvSheet, public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvSheetView(IlvDisplay* display);
    virtual ~IlvDvSheetView();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvGraphic*		getGraphic() { return this; }

    // ----------------------------------------------------------------------
    IlvDvDeclareAccessors();
    IlvDvDeclareInterface();

protected:
    IlvDvDocViewContext*	_context;

    virtual
    IlvDvDocViewContext*	createViewContext();
    virtual
    IlvDvDocViewContext*	getViewContext() const;
};

// --------------------------------------------------------------------------
// IlvDvHierarchicalSheetView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Gadgets_Hsheet_H)
#include <ilviews/gadgets/hsheet.h>
#endif


class ILVDVCLASS IlvDvHierarchicalSheetView
: public IlvHierarchicalSheet, public IlvDvDocViewInterface
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvHierarchicalSheetView(IlvDisplay* display);
    virtual ~IlvDvHierarchicalSheetView();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvGraphic*		getGraphic() { return this; }

    // ----------------------------------------------------------------------
    // Query / apply values
    IlvDvDeclareAccessors();

protected:
    IlvDvDocViewContext*	_context;
    virtual
    IlvDvDocViewContext*	createViewContext();
    virtual
    IlvDvDocViewContext*	getViewContext() const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(viewgadg);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Viewgadg_H */
