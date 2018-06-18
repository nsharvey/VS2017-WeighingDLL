// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspect.h
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
//  Declaration of the IlvStInspector class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspect_H
#define __IlvSt_Inspect_H

#if !defined(__Ilv_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif

#if !defined(__IlvSt_Insppnl_H)
#include <ivstudio/inspectors/insppnl.h>
#endif

#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

#if !defined(__IlvSt_Graphinf_H)
#include <ivstudio/inspectors/graphinf.h>
#endif

#if !defined(__IlvSt_Edtcallb_H)
#include <ivstudio/inspectors/edtcallb.h>
#endif

class IlvStudio;
class IlvStIGraphicInteractorsInfos;
class IlvStINameChecker;
class IlvStICallbackInfos;
class IlvStIGraphicInspectorPanel;
class IlvStIAccessor;
class IlvStInspector;
class IlvStInspectorPanel;
class IlvStIBufferStudioSelectionAccessor;
class IlvStInspectorAccessor;

// --------------------------------------------------------------------------
// IlvStIGraphicInteractorsInfos
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStGraphicInteractorsInfos :
    public IlvStIGraphicInteractorsInfos
{
public:
    IlvStGraphicInteractorsInfos(IlvStudio*, const char* name = 0);
    ~IlvStGraphicInteractorsInfos();

    virtual void	getObjectInteractors(IlArray&, IlvGraphic*);

protected:
    IlvStudio*		_studio;
};

// --------------------------------------------------------------------------
// class IlvStNameChecker
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStNameChecker : public IlvStINameChecker
{
public:
    IlvStNameChecker(IlvStudio*, const char* name = 0);
    ~IlvStNameChecker();

    virtual IlvStIError*	isIdentifierName(const char*) const;
    virtual IlvStIError*	checkGraphicName(const char*,
						 const IlvGraphic*) const;

protected:
    virtual IlBoolean		checkingIdentifierName() const;
    virtual IlvDisplay*		getDisplay() const;

    IlvStudio*			_studio;
};

// --------------------------------------------------------------------------
// class IlvStNameInfos
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStNameInfos : public IlvStINameInfos
{
public:
    IlvStNameInfos(IlvStInspector* inspector, const char* name = 0);
    ~IlvStNameInfos();

    virtual IlvStIError*	setObjectName(IlvGraphic*, const char*);

protected:
    IlvStInspector*		_inspector;
};

// --------------------------------------------------------------------------
// IlvStCallbackInfos class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStCallbackInfos : public IlvStICallbackInfos
{
public:
    IlvStCallbackInfos(IlvStInspector*		inspector,
		       IlvStINameChecker*	nameChecker = 0,
		       const char*		name = 0);
    ~IlvStCallbackInfos();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean		isUsingJScript() const;
    virtual const IlSymbol*	getDefaultCallbackLanguage() const;
    virtual IlvStIError*	checkCallbackName(const char*);
    virtual void		callbacksChanged(IlvGraphic*);
    virtual IlBoolean		editScript(const char*);

    // Deprecated
//    inline IlBoolean isUsingIlogScript() const { return isUsingJScript(); }

protected:
    IlvStudio*			_studio;
    IlvStInspector*		_inspector;
};

class ILVSTUDIOCLASS IlvStInspector : public IlvInspector
{
public:
    IlvStInspector(IlvStudio*);
    ~IlvStInspector();

    void		initialize();
    inline IlvStudio*	getEditor() const { return _editor; }
    IlvDisplay*		getDisplay() const;
    void		hide() const;
    virtual void	inspect(IlvGraphic*);
    virtual void	inspect(IlvStInspectorAccessor*,
				IlBoolean newInspector = IlTrue,
				IlBoolean modalInspector = IlTrue);
    virtual void	use(IlvInspectorPanel*);

    virtual void	registerBuilder(const char* classname,
					IlvStInspectorPanelBuilder* builder);

    virtual
    IlvInspectorPanel*	getPanel(IlvGraphic*) const;
    virtual void	setExclusive(IlBoolean flag);
    inline
    const IlArray&	getInspectors() const { return _panels; }
    inline IlBoolean	isLocked() const { return _locked; }
    inline void		lock(IlBoolean val) { _locked = val; }
    void		objectSelected();
    void		objectNameChanged();
    void		objectCallbackNameChanged();
    void		layersChanged();

    virtual void	getObjectInteractors(IlArray&);

    // ----------------------------------------------------------------------
    // Shared accessor managment
    IlvStIAccessor*	getSharedAccessor(const char*) const;
    void		addSharedAccessor(IlvStIAccessor*);

    // ----------------------------------------------------------------------
    inline
    IlvStGraphicInteractorsInfos*	getInteractorsInfos() const
					{
					    return _interactorsInfos;
					}
    inline
    IlvStNameChecker*	getNameChecker() const { return _nameChecker; }
    inline
    IlvStCallbackInfos*	getCallbackInfos() const
			{
			    return _callbackInfos;
			}
    inline
    IlvStNameInfos*	getNameInfos() const { return _nameInfos; }

    // ----------------------------------------------------------------------
    // Update mode
    inline
    IlvStIAccessor::UpdateMode	getUpdateMode() const { return _updateMode; }
    void		setUpdateMode(IlvStIAccessor::UpdateMode);

protected:
    virtual IlBoolean	checkingIdentifierName() const;

private:
    void		makePanels();
    void		makeCommands();

    IlvStudio*				_editor;
    IlBoolean				_locked	    ILVSTBF;
    IlvStGraphicInteractorsInfos*	_interactorsInfos;
    IlvStNameChecker*			_nameChecker;
    IlvStCallbackInfos*			_callbackInfos;
    IlvStNameInfos*			_nameInfos;
    IlArray				_accessors;
    IlvStIAccessor::UpdateMode		_updateMode;
    IlvStIBufferStudioSelectionAccessor*	_bufferSelectionAccessor;

public:
    // Managing inspector panel infos
    class InspectorPanelInfo
    {
    public:
	InspectorPanelInfo(IlvStInspectorPanelBuilder* builder)
	    : _builder(builder), _inspectorPanel(0)
	{}
	~InspectorPanelInfo() { if (_builder) delete _builder; }

	IlvStInspectorPanelBuilder*	_builder;
	IlvStInspectorPanel*		_inspectorPanel;
    };

    IlvStInspectorPanel* getInspectorPanel(InspectorPanelInfo* panelInfo,
					   const char* classname,
					   IlBoolean newInsp = IlFalse) const;
    InspectorPanelInfo*	getNearestPanelInfo(const char* classname,
					    IlUShort&	depth) const;
    IlvInspectorPanel*	getExactOldInspectorPanel(const char* classname) const;

    IlvHashTable	_inspectorsBuilders;

public:
    // Proxy of inspector panels (IlvInspectorPanel and IlvStInspectorPanel)
    class ProxyInspectorPanel
    {
    public:
	union {
	    IlvInspectorPanel*		_old;
	    IlvStInspectorPanel*	_new;
	} _panel;
	IlBoolean			_isNewPanel;

	ProxyInspectorPanel(IlvInspectorPanel* panel)
	{
	    _panel._old = panel;
	    _isNewPanel = IlFalse;
	}
	ProxyInspectorPanel(IlvStInspectorPanel* panel)
	{
	    _panel._new = panel;
	    _isNewPanel = IlTrue;
	}
	ProxyInspectorPanel(const ProxyInspectorPanel& src)
	{
	    _panel._new = src._panel._new;
	    _isNewPanel = src._isNewPanel;
	}

	inline void	initFrom(IlvGraphic* graphic)
			{
			    if (_isNewPanel)
				_panel._new->initFrom(graphic);
			    else
				_panel._old->initFrom(graphic);
			}
	inline operator	IlvGadgetContainer* () const
			{
			    return (_isNewPanel
				    ? (IlvGadgetContainer*)_panel._new
				    : (IlvGadgetContainer*)_panel._old);
			}
	inline void	ensureLoaded()
			{
			    if (_isNewPanel) {
				if (!_panel._new->isLoaded())
				    _panel._new->load();
			    }
			    else {
				if (!_panel._old->isLoaded())
				    _panel._old->load();
			    }
			}
  };

    ProxyInspectorPanel	getProxyPanel(const char*,
				      IlBoolean newInspector = IlFalse) const;
};

// --------------------------------------------------------------------------
// IlvStInspectorAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStInspectorAccessor : public IlvStIPropertyAccessor
{
public:
    IlvStInspectorAccessor(const char*	name = 0,
			   UpdateMode	= NoUpdate,
			   BuildMode	= None);
    ~IlvStInspectorAccessor();

    virtual IlBoolean		apply();

    virtual IlvGraphic*		getGraphic() const;
    virtual void		setGraphic(IlvGraphic* graphic);
    void			setInspectorPanel(IlvStInspectorPanel* ipanel);
    inline IlvStInspectorPanel*	getInspectorPanel() const
				{
				    return _inspectorPanel;
				}

protected:
    virtual IlvStIProperty*	getOriginalValue();

    IlvGraphic*			_graphic;
    IlvStInspectorPanel*	_inspectorPanel;
};

// --------------------------------------------------------------------------
// IlvStIManagerSelectionAccessor class
// --------------------------------------------------------------------------
class IlvManager;

class ILVINSPCLASS IlvStIManagerSelectionAccessor :
    public IlvStInspectorAccessor
{
public:
    IlvStIManagerSelectionAccessor(IlvManager*,
				   const char*	name = 0,
			           UpdateMode	= NoUpdate,
			           BuildMode	= None);
    ~IlvStIManagerSelectionAccessor();

    virtual IlBoolean	apply();
    void		applyGraphic(IlvGraphic*);

protected:
    virtual IlvManager*	getManager() const;

    IlvManager*		_manager;
};

// --------------------------------------------------------------------------
// IlvStIBufferStudioSelectionAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIBufferStudioSelectionAccessor :
    public IlvStIManagerSelectionAccessor
{
public:
    IlvStIBufferStudioSelectionAccessor(IlvStudio*,
				        const char*	name = 0,
				        UpdateMode	= NoUpdate,
				        BuildMode	= None);
    ~IlvStIBufferStudioSelectionAccessor();

protected:
    virtual IlvManager*	getManager() const;

    IlvStudio*		_studio;
};

// --------------------------------------------------------------------------
// IlvStInspectorGraphicAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStInspectorGraphicAccessor :
    public IlvStInspectorAccessor
{
public:
    IlvStInspectorGraphicAccessor(IlvGraphic*	graphic,
				  const char*	name = 0,
				  UpdateMode	= NoUpdate,
				  BuildMode	= None);

    void	setGraphic(IlvGraphic*);
};

// --------------------------------------------------------------------------
// IlvStInspectorContainerGraphicAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStInspectorContainerGraphicAccessor :
    public IlvStInspectorAccessor
{
public:
    IlvStInspectorContainerGraphicAccessor(IlvGraphicHolder*	holder,
					   const char*		graphicName = 0,
					   const char*		name = 0,
					   UpdateMode		= NoUpdate,
					   BuildMode		= None);


    virtual IlvGraphic*	getGraphic() const;

protected:
    IlvGraphicHolder*	_holder;
    IlString		_graphicName;
};

// --------------------------------------------------------------------------
#endif /* __IlvSt_Inspect_H */
