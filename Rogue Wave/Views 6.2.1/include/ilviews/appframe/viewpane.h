// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/viewpane.h
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
// Declaration of the IlvDvViewPane class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_viewpane_H)
#define __Ilv_Appframe_viewpane_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Viewcont_H)
#include <ilviews/appframe/viewcont.h>
#endif
#if !defined(__Ilv_Appframe_Dockcfg_H)
#include <ilviews/appframe/dockcfg.h>
#endif

class IlvDvApplication;
class IlvPane;
class IlvDvApplication;
class IlvDvDockableMainWindow;
class IlvDvFrameAndBarHandler;
class IlvDvBarSet;
// --------------------------------------------------------------------------
// IlvDvViewPane class
// --------------------------------------------------------------------------


class ILVDVCLASS IlvDvViewPane : public IlvDvViewContainerInterface
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor

    IlvDvViewPane(IlvDvFrameAndBarHandler* paneHandler, const char* name);
    ~IlvDvViewPane();

    // ----------------------------------------------------------------------
    virtual IlBoolean	isContainerVisible() const;
    virtual void	updateTitle();
    virtual void	activate();

    // ----------------------------------------------------------------------

    inline IlvPane*	getPane() const { return _pane; }
    void		setPaneIndex(IlUInt paneIndex);

    // ----------------------------------------------------------------------
    // Specific methods

    void		hide();
    // ----------------------------------------------------------------------
    virtual IlvGadgetContainer*
			getClientContainer(IlBoolean create = IlFalse);
    virtual IlBoolean	readMask(const char* pathName);
    virtual
    IlvDvDocViewInterface* getActiveDocView() const;
    virtual
    IlvDvApplication*	getDvApplication() const;
    virtual void	setDvApplication(IlvDvApplication* app);
    virtual const char*	getContainerTitle() const;
    virtual IlUInt	getContainerNumber() const;
    virtual void	setContainerNumber(IlUInt n,
					   IlBoolean update = IlFalse);

    virtual
    IlvDvContainerHandler* getContainerHandler() const;

    IlvDvDeclareInterface();

protected:
    IlvDvDockableMainWindow*	_container;
    IlvPane*			_pane;
    const IlSymbol*		_name;
    IlvDvBarSet*		_barSet;
    IlUInt			_paneIndex;
    IlvGadgetContainer*		_clientContainer;
    IlvDvFrameAndBarHandler*	_paneHandler;
    IlvGraphic*			_graphic;

    virtual void	removeView(IlvDvDocViewInterface*,
				   IlBoolean deleteIt);
    virtual IlBoolean	addDocViews(const IlArray& views);
    virtual void	doClose();

    // Title data
    IlvString		_title;
    IlUInt		_containerNumber;
    IlBoolean		_usingMask;
    IlvDvApplication*	_application;

    // View data
    IlvArray		_views;
    IlvDvDocViewInterface* _activeView;

    virtual IlBoolean	isUsingMask() const;
    virtual void	setUsingMask(IlBoolean);
    virtual void	setActiveDocViewMember(IlvDvDocViewInterface*);
    virtual IlvArray&	getViewsArray();
    virtual void	storeActiveDocView(IlvDvDocViewInterface* activeView);
    void		initializePane(IlvPane* pane, const char* name);
    void		dockPane();

    void		toggleFrameBar();
    void		refreshToggleFrameBar(IlvDvActionDescriptor* desc);

public:
    static void		FocusInDocView(IlvGraphic*, IlAny);
    static void		FocusOutDocView(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(viewpane);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_viewpane_H */
