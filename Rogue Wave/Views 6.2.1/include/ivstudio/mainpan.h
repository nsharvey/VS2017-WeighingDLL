// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/mainpan.h
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
// Declaration of the editor main panel class: IlvStMainPanel
// --------------------------------------------------------------------------
#ifndef __IlvSt_Mainpan_H
#define __IlvSt_Mainpan_H

#if !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Dockutil_H)
#include <ilviews/gadgets/dockutil.h>
#endif

// --------------------------------------------------------------------------
class IlvStudio;
class IlvStToolBar;
class IlvStGenericInspector;
class IlvStMode;
class IlvStMainBufferViewHandler;
class IlvStWorkDesktop;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStMainPanel
: public IlvStPanelHandler {
public:
    IlvStMainPanel(IlvStudio* editor);
    ~IlvStMainPanel();

protected:
    IlvGraphicPane*	makeMenuBarPane();
    IlvGraphicPane*	makeBufferToolBarPane();
    IlvViewPane*	makeGenericInspectorPane();
    IlvViewPane*	makeStatusPane();

    IlvStMainBufferViewHandler* _bvhandler;
    IlvAbstractMenu*	        _menubar;
    IlvStGenericInspector*      _ginsp;
    IlvStToolBar*	        _bufferToolBar;
    IlvPopupMenu*	        _windowMenu;
    IlUShort		        _fwmiNdx;
    IlvViewPane*	        _mainPane;
    IlvGraphicPane*	        _bufferToolBarPane;
    IlvViewPane*	        _ginspPane;
    IlvGraphicPane*	        _bufferTypePane;
    IlvViewPane*	        _statusPane;
    const char* const*	        _lastBufferCommands;
    IlBoolean		        _modificationStar;
    IlBoolean		        _ginspViewable;

public:
    virtual IlvAbstractMenu* getMenuBar() const;
    virtual void	     connect();
    virtual void	     show();
    virtual void	     hide();
    void		     finalizeInit();
    IlvPanedContainer*       getPanedContainer() const
	{ return (IlvPanedContainer*)_container; }
    IlvDockableContainer*    getDockableContainer() const
	{ return (IlvDockableContainer*)_container; }
    virtual void	     commandStateChanged(IlvStCommandDescriptor*);
    void		     showGenericInspector(IlBoolean = IlTrue);
    void		     hideGenericInspector(IlBoolean = IlTrue);
    void		     bufferSelected();
    void		     updateTitle();
    void		     updateBufferToolBar();
    void		     initializeWindowMenu();
    void		     updateWindowMenuItems();
    void		     updateRecentFileMenuItems();
    void		     bufferTypeChanged();
    IlvPopupMenu*	     getWindowMenu() const { return _windowMenu; }
    IlvGadgetContainer*	     getWorkContainer() const;
    IlBoolean		     hasModificationStar() const
	{ return _modificationStar; }
    void		     setModificationStar(IlBoolean val)
	{ _modificationStar = val; }
    IlvPane*		     getMainPane() const { return _mainPane; }
    IlvPane*		     getBufferToolBarPane() const
	{ return _bufferToolBarPane; }
    IlvPane*		     getGenericInspectorPane() const
	{ return _ginspPane; }
    IlvPane*		     getBufferTypePane() const
	{ return _bufferTypePane; }
    IlvPane*		     getStatusPane() const { return _statusPane; }
    virtual void 	     addToolBar(IlvGraphic*,
					IlvPosition placement,
					const char* name = 0);
    virtual IlvPane*	     addAfter(IlvStPanelHandler* panel,
				      const IlvPane* ref,
				      IlBoolean elastic = IlTrue,
				      IlvDim minSize = 20);
    virtual IlvDockable*     addPane(IlvPane* pane,
				     const char* relativePaneName,
				     IlvPosition relativePanePosition);
    virtual IlvPane*	     addPanelAsPane(IlvStPanelHandler* pane,
					    const char* relativePaneName,
					    IlvPosition relativePanePosition,
					    IlBoolean elastic = IlTrue,
					    IlvDim minSize = 20);
    virtual IlvPane* 	     createPane(IlvStPanelHandler* pane) const;
    IlBoolean		     isGenericInspectorViewable() const
        { return _ginspViewable; }
    void		     setGenericInspectorViewable(IlBoolean val)
	{ _ginspViewable = val; }
    IlUShort                fwmiNdx() const { return _fwmiNdx; }
    IlvStWorkDesktop*        getDesktopManager() const;

protected:
    IlUShort	    _RFLLength;

public:
    IlUShort	    getRFLLength() { return _RFLLength; }
}; // class IlvStMainPanel

class IlvStSCManagerRectangle;

// --------------------------------------------------------------------------
#endif /* __IlvSt_Mainpan_H */
