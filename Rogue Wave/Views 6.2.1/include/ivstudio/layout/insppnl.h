// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/insppnl.h
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
// Declaration of the IlvLayoutInspectorPanel class
// Defined in library ilvstlayout
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Insppnl_H
#define __IlvSt_Layout_Insppnl_H

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#include <ivstudio/inspectors/insppnl.h>
#include <ivstudio/inspectors/inspall.h>
#include <ilviews/layout/gphlayout.h>
#include <ilviews/gadgets/notebook.h>
#include <ilviews/gadgets/slist.h>

#if !defined(__Ilv_Gadgets_Scombo_H)
#include <ilviews/gadgets/scombo.h>
#endif

#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif

#if !defined(__Ilv_Gadgets_Spinbox_H)
#include <ilviews/gadgets/spinbox.h>
#endif

#if !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif /* __IlvSt_Panel_H */

class IlvLayoutInspectorInterface;
class IlvLayoutAccessor;
class IlvLayoutGeneralAccessor;

class ILVSTLAYEXPORTED IlvLayoutInspectorPanel
: public IlvStInspectorPanel
{
public:
    IlvLayoutInspectorPanel(IlvDisplay*,
			    const char*,
			    const char* = 0,
			    IlvSystemView = 0,
			    IlvStIAccessor::UpdateMode
			    	= IlvStIAccessor::OnApply);
    ~IlvLayoutInspectorPanel();

    void	initializeEditors();
    void	reinitialize();
    void	apply();

    void	registerLayout(const char*, IlvLayoutInspectorInterface*);
    void	initializeLayout();
    void	selectLayout(IlvGraphic*);

    IlvStringList*	getStringList() const;
    void		setFixed(IlBoolean) const;

    IlvGadgetContainer*	getSpecificPage() const;
    IlvGadgetContainer*	getGeneralPage() const;

    void	setManager(const IlvManager*);

protected:
    void	objectSelected(const IlvManager*,
			       IlvLayoutInspectorInterface*,
			       IlBoolean force = IlFalse);

private:
    IlAList*		_layoutItfList;
    IlvStringList*	_stringList;
    IlBoolean		_initialized;
    IlvLayoutGeneralAccessor* _genAcc;
    IlvGraphic*		_selectedObject;
    IlInt		_nrSelectedObjects;
};

class ILVSTLAYEXPORTED IlvLayoutPanelHandler
: public IlvStPanelHandler
{
public:
    IlvLayoutPanelHandler(IlvStudio*,
			  const char* name,
			  const char* fileordata,
			  const IlvRect& rect,
			  IlUInt properties = 0,
			  IlvStPanelHandler* tfor = 0);
    IlvLayoutPanelHandler(IlvStudio*,
			  const char* name,
			  IlvGadgetContainer* = 0);
    virtual ~IlvLayoutPanelHandler();

    void	doApply();
    void	doReset();
    IlBoolean	resetBeforeShowing() const;

protected:
private:
};

// --------------------------------------------------------------------------
class ILVSTLAYEXPORTED IlvLayoutAccessor
: public IlvStICombinedAccessor
{
public:
    IlvLayoutAccessor(IlvStIPropertyAccessor* accessor,
		      IlvGraphLayout* layout,
		      const char* name = 0,
		      UpdateMode = NoUpdate,
		      BuildMode = None);
protected:
    IlvGraphLayout* _layout;
    virtual IlvStIProperty* getOriginalValue();
    IlBoolean apply();
};

// --------------------------------------------------------------------------
class ILVSTLAYEXPORTED IlvLayoutGeneralAccessor
: public IlvStICombinedAccessor
{
public:
    IlvLayoutGeneralAccessor(IlvStIPropertyAccessor*,
			     IlvLayoutInspectorPanel*,
			     const char* name = 0,
			     UpdateMode = NoUpdate,
			     BuildMode = None);
protected:
    IlvLayoutInspectorPanel* _panel;
    virtual IlvStIProperty* getOriginalValue();
    IlBoolean apply();
};

// --------------------------------------------------------------------------
class ILVSTLAYEXPORTED IlvLayoutOffsetAcc
: public IlvStICombinedValueInterAccessor
{
public:
    IlvLayoutOffsetAcc(IlvStIPropertyAccessor*,
		       const char* name = 0,
		       UpdateMode = NoUpdate);
protected:
    void applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
#endif /* !__IlvSt_Layout_Insppnl_H */
