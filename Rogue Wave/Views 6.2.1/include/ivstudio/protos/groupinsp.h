// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/protos/groupinsp.h
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
// Declarations for IlvGroupInspector class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Groups_Grouppan_H
#define __IlvSt_Groups_Grouppan_H

#if defined(IL_STD)
#include <cstring>
#else
#include <string.h>
#endif /* !IL_STD */

#include <ilviews/base/array.h>
#include <ilviews/base/clssinfo.h>
#include <ilviews/protos/useracc.h>

#include <ivstudio/panel.h>
#include <ivstudio/vobj.h>
#include <ivstudio/protos/stproto.h>
#include <ivstudio/protos/prgadgets.h>
#include <ilviews/protos/proto.h>
#include <ilviews/gadgets/notebook.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/tree.h>
#include <ilviews/gadgets/hsheet.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/spinbox.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/edit/inspanel.h>

#include <ilviews/annotext/annotext.h>
#include <ilviews/annotext/html.h>

extern ILVSTPREXPORTEDVAR(const char*) IlvNmGroupInspector;

// ----------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupEditorPanel;
class ILVSTPRCLASS IlvGroupInspector;
class ILVSTPRCLASS
IlvDeclareAndImplementArrayOfPointerTo(IlvUserAccessor,IlvGroupAccArray);

// ---------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupValueEditor {
friend class IlvGroupAttributesPane;
friend class IlvGroupBehaviorPane;
friend class IlvGroupEditorPane;
public:
    IlvGroupValueEditor(const IlSymbol*, IlvGroupInspector*);
    virtual ~IlvGroupValueEditor();

    void rename(const char*);
    IlvUserAccessor* replaceAccessor(IlvUserAccessor*, 
    				     IlvUserAccessor*, IlInt = -1, 
				     IlBoolean = IlFalse);
    void addAccessor(IlvUserAccessor*);

inline IlBoolean isPrototype () const { return _prototypes.getLength() != 0; }
inline IlBoolean isPublic() const { return _public; }
inline IlBoolean isPersistent() const { return _persistent; }
inline IlBoolean isNotifying() const { return _notifying; }
inline IlBoolean isInteraction() const {
	   return _events.getLength() + _callbacks.getLength() > 0;
	}
    void setPublic(IlBoolean);
    void setPersistent(IlBoolean);
    void setNotifying(IlBoolean);
    IlBoolean empty() { return _types.getLength()==0 && 
	    		_observers.getLength()==0 && 
	    		_events.getLength()==0 && 
	    		_callbacks.getLength()==0 && 
	    		_actions.getLength()==0 &&
			_prototypes.getLength()==0; }
    void clear() {
	_types.erase(); _observers.erase(); _events.erase();
	_callbacks.erase(); _actions.erase(); _prototypes.erase();
	_public=IlFalse; _persistent=IlFalse; _notifying=IlFalse;
    }
    IlvGroupInspector* getInspector() { return _inspector; }
    IlvAccessorDescriptor* getAccessorDescriptor(IlvUserAccessor* c) const;
    const IlSymbol* getName() const { return _name; }
    IlvValueTypeClass* getType() const;
    IlvAbstractMatrixItem* makeTypeEditor(IlvGroupEditorPane*, 
					  const IlvMatrix*, IlvDim, IlvDim) const; 
protected:
    const IlSymbol* _name;
    IlvGroupInspector* _inspector;
    IlBoolean _public, _persistent, _notifying;
    IlvGroupAccArray _types;
    IlvGroupAccArray _observers;
    IlvGroupAccArray _events;
    IlvGroupAccArray _callbacks;
    IlvGroupAccArray _actions;
    IlvGroupAccArray _prototypes;
};

// ----------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupEditorPane {
friend class IlvGroupInspector;
public:
    IlvGroupEditorPane(IlvGroupInspector*, const char*);
    virtual ~IlvGroupEditorPane();

    void update();
    void activate(IlBoolean);
    IlvGroup* getObject(); // inlined below
    IlvGadgetContainer* getPane(); // inlined below
    const char* getName() { return _name; }
    virtual void load(IlvGadgetContainer*, IlBoolean = IlTrue);
    virtual IlvTextField* createEditionField(IlvMatrix*,IlUShort,IlUShort);
    virtual IlvGroupValueEditor* getSelectedAttribute();
    virtual IlvUserAccessor* getSelectedAccessor();
    virtual IlInt getSelectedParam();
    virtual void removeAttribute();
protected:
static void ChangeNameCB(IlvMatrix*, IlUShort, IlUShort, IlAny);
static void AddAttributeCB(IlvGraphic*, IlAny);
static void RemoveAttributeCB(IlvGraphic*, IlAny);
static void MoveUpCB(IlvGraphic*, IlAny);
static void MoveDownCB(IlvGraphic*, IlAny);
static void DelegatePrototypeCB(IlvGraphic*, IlAny);
static void CutSelectionCB(IlvGraphic*, IlAny);
static void CopySelectionCB(IlvGraphic*, IlAny);
static void PasteSelectionCB(IlvGraphic*, IlAny);

    IlvGroupInspector* _inspector;
    const char* _name;
    IlBoolean _needUpdate, _active;
    virtual void initialize(IlvGroup*);
};

// ----------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupAttributesPane : public IlvGroupEditorPane {
friend class IlvGroupInspector;
public:
    IlvGroupAttributesPane(IlvGroupInspector*);
    virtual ~IlvGroupAttributesPane();
    void load(IlvGadgetContainer*, IlBoolean = IlTrue);
enum DisplayType { interfaceValues, publicValues, allValues, modifiedValues };
    IlvGroupValueEditor* getSelectedAttribute();
    void removeAttribute();
protected:
static void ChangeParamCB(IlvMatrix*, IlUShort, IlUShort, IlAny);
// static void ChangeValueCB(IlvMatrix*, IlUShort, IlUShort, IlAny);
static void SetDisplayTypeCB(IlvGraphic*, IlAny);
static void ChangeAttributeCB(IlvGraphic*, IlAny);
    IlUInt makeProtoItem(const IlvGroupValueEditor&, IlvUserAccessor*, IlUInt row);
    IlUInt makeItem(const IlvGroupValueEditor&, IlUInt row, 
		    IlBoolean selected = IlFalse, IlUShort col = 0);
    void initializeValues(IlvValueArray&, IlBoolean);
    void initializeValueEditor(IlBoolean);
    void prepareMatrix(IlUInt);

    void initialize(IlvGroup*);

    IlvMatrix* _items;
    IlBoolean _editTypes;
    DisplayType _currentDisplay;
};

class ILVSTPRCLASS IlvGroupGraphicsPane : public IlvGroupEditorPane {
friend class IlvGroupInspector;
public:
    IlvGroupGraphicsPane(IlvGroupInspector*);
    virtual ~IlvGroupGraphicsPane();
    void load(IlvGadgetContainer*, IlBoolean = IlTrue); 
    void selectNode();
    IlvGroup* getSelectedSubGroup();
protected:
static void ChangeValueCB(IlvGraphic*, IlAny);
static void ChangeNodeNameCB(IlvMatrix*, IlUShort, IlUShort, IlAny);
static void DeleteNodeCB(IlvGraphic*, IlAny);
static void SelectNodeCB(IlvGraphic*, IlAny);
// *** add an observer on selection
    void initialize(IlvGroup*);
    IlvHierarchicalSheet* _items;
    IlvTreeGadgetItem* addItem(IlvGroup*, IlvGroupNode*, IlvTreeGadgetItem*);
    void makeButtons(IlvGroupNode*, IlvTreeGadgetItem*);
};

class ILVSTPRCLASS IlvGroupBehaviorPane
: public IlvGroupEditorPane {
public:
    IlvGroupBehaviorPane(IlvGroupInspector*, const char* n="displayb");
    virtual ~IlvGroupBehaviorPane();
    void load(IlvGadgetContainer*, IlBoolean = IlTrue); 
    IlvGroupValueEditor* getSelectedAttribute();
    IlvUserAccessor* getSelectedAccessor();
    IlInt getSelectedParam();
    void selectAccessor();
protected:
    virtual void makeAccessorEditor(
		IlvTreeGadgetItem*, const char*, const IlvGroupValueEditor&,
		const IlvGroupAccArray&);
    virtual void makeCompactAccessorEditor(
		IlvTreeGadgetItem*, const char*, const IlvGroupValueEditor&,
		const IlvGroupAccArray&);
    virtual void makeItem(const IlvGroupValueEditor&, IlvTreeGadgetItem* =0);
    void initialize(IlvGroup*);
static void AddAccessorCallback(IlvGraphic*, IlAny);
    IlvHierarchicalSheet* _items;
    IlBoolean _isInteraction;
};

class ILVSTPRCLASS IlvGroupInteractionPane
: public IlvGroupBehaviorPane {
public:
    IlvGroupInteractionPane(IlvGroupInspector*);
    virtual ~IlvGroupInteractionPane();
protected:
//    void initialize(IlvGroup*);
};

// --------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupInspectorObserver: public IlvGroupObserver {
public:
    IlvGroupInspectorObserver(IlvGroupInspector* i)
		:IlvGroupObserver(), _inspector(i) {}
    virtual ~IlvGroupInspectorObserver();
    void valuesChanged(IlvGroup*, const IlvValue*, IlUInt);
    void nodesChanged(IlvGroup*);
    void groupDeleted(IlvGroup*);
protected:
    IlvGroupInspector* _inspector;
};


class ILVSTPRCLASS
IlvDeclareAndImplementArrayOfPointerTo(IlvGroupValueEditor,IlvGroupValues);

// --------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupInspector : public IlvInspectorPanel {
friend class IlvGroupEditorPane;
friend class IlvGroupInspectorObserver;
friend class IlvGroupValueEditor;
friend class IlvGroupBehaviorPane;
friend class IlvGroupAttributesPane;
friend class IlvGroupAccessorCommand;
friend class IlvAccessorRenameCommand;
public:
    IlvGroupInspector(IlvStudio* editor, IlvGroupEditorPanel* panel);
    virtual ~IlvGroupInspector();
// panel API
    void initFrom(IlvGraphic*);
    void reset();
    void update();
    void show();
    void hide();
// own API
    IlvStudio* getEditor() const { return _editor; }
    IlvGroup* getSelectedGroup();
inline IlvGroupInspectorObserver* getObserver() { return _observer; }
    IlvGroup* getSelectedSubGroup();
    void setObject(IlvGroup*);
    void updateValue(const IlSymbol* s);
    void addCommand(IlvCommand*);
inline IlvGroup* getObject() { return _object; }
inline IlvGroupValues& getValues() { return _values; }
inline IlBoolean isProtoInstance() { return _object && _object->isSubtypeOf(IlvProtoInstance::ClassInfo()); }
inline IlvGroupEditorPane* getCurrentPane() { return _currentPane; }
    void setHelp(IlBoolean);
    void setPage(IlvGroupEditorPane*);
    void setHelpPage(const char*);
    inline IlBoolean helpOn() { return _helpPage != 0; }
    IlvGadgetContainer* getPage(const char*);
protected:
    IlvStudio* _editor;
    IlvGroupInspectorObserver* _observer;
    IlvGroupEditorPanel* _panel;
// Gadgets from .ilv
    void setupWizardMode();
    void setupRegularMode();
    IlvATHtmlText* _helpPage;
    IlvATHtmlReader* _pageReader;
    IlvMessageLabel* _title;
    IlvGadgetContainerRectangle* _content;
    IlvNotebook* _notebook;  
    IlList _panes;
    IlvGroupEditorPane* _currentPane;
// internal data for the behavior panes
    IlvGroup* _object;
    IlvGroupValues _values;
// handling lazy refreshes
    IlBoolean _resetCalled, _updateCalled;
    IlBoolean _allValues;
    IlList _symbolsToUpdate;
    IlvUserAccessor* _changedAccessor;
    IlvUserAccessor* _addedAccessor;
    IlInt _changedParam;
public: // some compilers don't accept this as protected
// might want to make those static and reloadable when a module is loaded
// to refresh the list.
    struct AccessorClass {
	IlvUserAccessorClassInfo* _info;
	IlvAccessorDescriptor* _desc;
    };
static AccessorClass* _accessorClasses;
static IlUInt _count;
protected:
static void PageSelected(IlvGraphic*, IlAny);
static void ChangePage(IlvGraphic*, IlAny);
static IlBoolean Update(IlAny arg);
static IlBoolean Reset (IlAny arg);
};

inline IlvGroup* IlvGroupEditorPane::getObject() 
	{ return _inspector->_object; }
inline IlvGadgetContainer* IlvGroupEditorPane::getPane() 
	{ return _inspector->getPage(_name); };

// ---------------------------------------------------------------------------
// IlvGroupEditorPanel	A Studio panel that points to the proto insp.
// ---------------------------------------------------------------------------

class ILVSTPRCLASS IlvGroupEditorPanel
: public IlvStPanelHandler {
    friend class IlvGroupInspector;
public:
    IlvGroupEditorPanel(IlvStudio* editor);
    virtual ~IlvGroupEditorPanel();
    // ____________________________________________________________
    virtual IlBoolean resetBeforeShowing() const;
    virtual void connect();
    virtual void reset();
    IlvGroup* getSelectedSubGroup() { return _inspector->getSelectedSubGroup(); }
    IlvGroupInspector* getInspector() { return _inspector; }
protected:
    IlvGroupInspector* _inspector;
    void setVisible(IlBoolean visible) { _visible = visible; }
};

IlvDECLAREINITSTPRCLASS(stp_groupinsp)

#endif /* __IlvSt_Protos_Protopan_H */
