// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/stlayer.h
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
// Declaration of Layer Panel classes
// --------------------------------------------------------------------------

#ifndef __IlvSt_Stlayer_H
#define __IlvSt_Stlayer_H

#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Gadgets_Msglabel_H)
#include <ilviews/gadgets/msglabel.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif

#if !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif

#if !defined(__IlvSt_Mainedt_H)
#include <ivstudio/inspectors/mainedt.h>
#endif

#if !defined(__IlvSt_Listacc_H)
#include <ivstudio/inspectors/listacc.h>
#endif

#if !defined(__IlvSt_Listedt_H)
#include <ivstudio/inspectors/listedt.h>
#endif

class IlvManager;
class IlvManagerLayer;
class IlvToggle;
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStLayerPanel
: public IlvStPanelHandler {
public:
    IlvStLayerPanel(IlvStudio*);
    virtual void    connect();
    virtual void    show();
    virtual void    apply();
    // ____________________________________________________________
    int		    getSelectedLayer() const;
    void	    unSelectObjects(int i, IlBoolean redraw = IlTrue) const;
    void	    initialize();
    void	    resetList();
    void	    bufferSelected();

protected:
    IlvStIMainEditor _mainEditor;
    IlBoolean       _connected;
}; // IlvStLayerPanel

// --------------------------------------------------------------------------
// class IlvStEditorManagerAccessor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStEditorManagerAccessor :
public IlvStIPropertyAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStEditorManagerAccessor(IlvStudio* studio,
			       IlvStIErrorManager* errorManager,
			       const char* name = 0,
			       UpdateMode updateMode = NoUpdate,
			       BuildMode buildMode = None);
    ~IlvStEditorManagerAccessor();

    // ----------------------------------------------------------------------
protected:
    IlvStudio* _studio;
    IlvStIErrorManager* _errorManager;
    virtual IlvStIErrorManager* getErrorManager()const
    {	return _errorManager; }
    virtual IlvStIProperty* getOriginalValue();
};

// --------------------------------------------------------------------------
// class IlvStManagerLayersAccessor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStManagerLayersAccessor :
public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStManagerLayersAccessor(IlvStIPropertyAccessor* accessor,
			       IlvStudio* studio,
		               IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			       IlvStIAccessor::BuildMode =
					    IlvStIAccessor::None,
			       const char* name = 0);
    ~IlvStManagerLayersAccessor();

    // ----------------------------------------------------------------------
    // Main overridables
    IlvManager* getManager()const;
    void setLayerVisible(IlvToggle*);

protected:
    IlvStudio* _studio;

    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual IlvStIProperty* createDefaultProperty()const;
    virtual IlvStIEditor* findFirstEditor()const;

    virtual IlvStIProperty* copyProperty(const IlvStIProperty* property); // calls property->copy() by default
    virtual void addProperty(IlvStIProperty*, IlUInt);
    virtual IlBoolean canDeleteProperty(IlvStIProperty* prop, IlUInt)const;
    virtual void deleteNewProperty(IlvStIProperty* property);
    virtual void deleteProperty(IlvStIProperty* property, IlUInt);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty, IlUInt);
    virtual void moveProperty(IlvStIProperty*,
			      IlUInt previousIndex, IlUInt newIndex);
    virtual void doApply();
    virtual IlvStIError* check()const;

    void getDefaultLayerName(IlvString&)const;
    IlvManagerLayer* getManagerLayer(const IlvStIProperty*)const;
    const char* getManagerLayerName(const IlvStIProperty*)const;
friend class IlvStLayersListEditor;
};

// --------------------------------------------------------------------------
// class IlvStILayersListEditor
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStLayersListEditor
: public IlvStIPropertyListEditor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStLayersListEditor(IlvStIPropertyListAccessor* accessor = 0,
			  const char* name = 0);

    // ----------------------------------------------------------------------
protected:
    IlvString _layerFmt;
    IlvStManagerLayersAccessor* getManagerLayersAcc()const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty* prop)const;
    virtual void propertyCountChanged(IlUInt count, int flag); // flag = 1: adding, flag = 0: initializing, flag = -1: removing
};

// --------------------------------------------------------------------------
IL_MODULEINIT(st_stlayer, ILVSTUDIOCLASS);
// --------------------------------------------------------------------------
#endif /*  ! __IlvSt_Stlayer_H */
