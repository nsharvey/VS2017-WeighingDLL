// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/framebar.h
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
// Declaration of the IlvDvFrameAndBarHandler class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Framebar_H)
#define __Ilv_Appframe_Framebar_H

#if !defined(__Ilv_Appframe_Viewcont_H)
#include <ilviews/appframe/viewcont.h>
#endif

class IlvDvViewFrame;
class IlvDvDockableMainWindow;
class IlvDvDocTemplate;
class IlvDvNodeValue;
class IlvDockingPaneLocation;
class IlvPane;
class IlvDvTemplatePaneViewer;
class IlvDvBarSet;
class IlvDvViewPane;

// --------------------------------------------------------------------------
// IlvDvFrameAndBarHandler class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvFrameAndBarHandler : public IlvDvContainerHandler
{
public:

    enum ContainerType { NoWindow, Docked, MDIChild, Floating };
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvFrameAndBarHandler(IlvDvDockableMainWindow* mainWindow,
			    IlvDvDocTemplate* docTemplate,
			    ContainerType mode = MDIChild,
			    IlBoolean isMaximizing = IlFalse,
			    IlUInt viewTemplateIndex = 0);

    virtual ~IlvDvFrameAndBarHandler();

    // ----------------------------------------------------------------------
    // Virtuals inherited from IlvDvContainerHandler
    virtual
    IlvDvViewContainerInterface* createContainer();
    void		setDocViewFactory(IlvDvDocumentViewFactory*);
    IlvDvDocumentViewFactory* getDocViewFactory() const;
    virtual IlBoolean	closeDocumentOnClose() const;

    // ----------------------------------------------------------------------
    // Accessors
    virtual IlBoolean	allowMultipleContainers() const;

    // ----------------------------------------------------------------------
    // Basic properties
    virtual
    IlvDvApplication*	getDvApplication() const;
    inline
    IlvDvDockableMainWindow* getMainWindow() const
			{
			    return _mainWindow;
			}
    inline
    ContainerType	getContainerCreationMode() const { return _mode; }
    IlBoolean		allowBarToPane() const;

    // ----------------------------------------------------------------------
    // Methods specific to docking
    void		initializePane(IlvPane* pane, const char* paneName);
    void		dockBarSet(IlvDvBarSet* barSet,
				   IlBoolean update = IlTrue);
    virtual void	removeBarSet(const IlvDvBarSet* barSet,
				     IlBoolean update = IlTrue);

    // ----------------------------------------------------------------------
    // Methods specific to frames
    void		deleteFrame(IlvDvViewFrame* viewFrame);

    // ----------------------------------------------------------------------
    // IO
    inline const char*	getOptionsNodeName() const { return _nodeName; }
    inline void		setOptionsNodeName(const char* name)
			{
			    _nodeName = name;
			}
    virtual void	readOptions(IlvDvOptions* options);
    virtual void	updateOptions(IlvDvOptions* options);

protected:
    IlvDvDockableMainWindow*	_mainWindow;
    IlvDvNodeValue*		_configNode;
    IlvDvDocTemplate*		_docTemplate;
    IlUInt			_viewTemplateIndex;
    IlvString			_nodeName;
    ContainerType		_mode;
    IlvDvTemplatePaneViewer*	_paneViewer;
    IlBoolean			_initialyVisible;
    IlBoolean			_closeDocumentOnClose;
    IlvDvDocumentViewFactory*	_viewFactory;

    // Parameters needed for creation of view frames
    IlBoolean			_isMaximizingFrames;
    IlvString			_ilvMaskPathName;
    IlBoolean			_allowMultipleContainers;

    // Parameters needed for creation of dockable panes
    IlvArray			_openedPaneIndexes;
    IlvDockingPaneLocation*	_defaultPaneLocation;
    IlBoolean			_resizable;
    IlvPoint			_minimumSizes;
    IlvPoint			_initialSizes;

    enum { OnlyHorizontally, OnlyVertically, Everywhere } _dockingContrainst;

    friend class ILVDVCLASS IlvDvViewFrame;
    friend class ILVDVCLASS IlvDvViewPane;

    IlvDvViewFrame*	createFrame();
    void		frameToPane(IlvDvViewFrame* viewFrame);

    IlUInt		getNewPaneIndex();
    void		removePaneIndex(IlUInt);


    IlvDvViewPane*	createPane();
    void		paneToFrame(IlvDvViewPane* viewPane);
    void		togglePaneFrame(IlvDvViewContainerInterface*,
					IlBoolean bCreateFrame);
    void		readOptionsMode(IlvDvNodeValue*);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(framebar);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Framebar_H */
