// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/dockutil.h
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
// Declaration of IlvDockableMainWindow and related classes
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Dockutil_H
#define __Ilv_Gadgets_Dockutil_H

#include <ilviews/gadgets/dockpane.h>
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

// --------------------------------------------------------------------------
// Class IlvDockingPaneFilter
// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingPaneFilter
{
public:
    IlvDockingPaneFilter();
    virtual ~IlvDockingPaneFilter();
    virtual IlvPane*	accept(const IlvPane& refPane,
			       const IlvPane& relPane) const;
};

// --------------------------------------------------------------------------
// Class IlvDockableMainWindow
// ------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockableMainWindow : public IlvDockableContainer
{
public:

    IlvDockableMainWindow(IlvDisplay*      display,
			  const char*      name,
			  const char*      title,
			  const IlvRect&   rect,
			  IlUInt           properties = 0,
			  IlBoolean        visible = IlTrue,
			  IlvSystemView    transientFor = 0);
    IlvDockableMainWindow(IlvAbstractView* parent,
			  const IlvRect&   rect,
			  IlBoolean       visible = IlTrue);

    IlvDockableMainWindow(IlvDisplay*      display,
			  IlvSystemView    parent,
			  const IlvRect&   rect,
			  IlBoolean        visible = IlTrue);

    IlvDockableMainWindow(IlvDisplay*      display,
			  IlvSystemView    window);

    virtual ~IlvDockableMainWindow();


    IlvViewPane*	getMainWorkspaceViewPane() const;

    IlvDockable*	addRelativeDockingPane(IlvPane* pane,
					       const char* relativePaneName,
					       IlvPosition relativePanePosition);

    IlvPane*		getRelativePane(const IlvPane& pane,
					IlvPosition& relativePanePosition,
					const IlvDockingPaneFilter* filter = 0) const;

    IlvDockableContainer* getHorizontalDockableContainer() const;

    static const char*	GetHorizontalDockableContainerName();
    static const char*	GetMainWorkspaceName();

protected:
    DeclareLazyViewProperties();
    void		initLayout();
};

// --------------------------------------------------------------------------
// Class IlvDockingPaneLocation
// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingPaneLocation
{
public:

    enum DockedState {
	UnDocked           = 1,
	DockedHorizontally = 2,
	DockedVertically   = 4,
	Docked             = DockedHorizontally|DockedVertically
    };

    IlvDockingPaneLocation(const char*    paneName,
			   const char*    relativePaneName,
			   IlvPosition    relativePosition,
			   int            dockedState = Docked,
			   IlBoolean      visible = IlTrue,
			   const IlvRect* horDockedRect = 0,
			   const IlvRect* verDockedRect = 0,
			   const IlvRect* unDockedRect = 0);

    IlvDockingPaneLocation(const IlvDockingPaneLocation&);
    virtual ~IlvDockingPaneLocation();

    const char*		getPaneName() const { return _paneName; }
    const char*		getRelativePaneName() const
			{
			    return _relativePaneName;
			}
    IlvPosition		getRelativePosition() const
			{
			    return _relativePosition;
			}
    int			getDockedState() const { return _dockedState; }
    IlBoolean		isVisible() const { return _visible; }
    const IlvRect&	getPaneGeometry() const
			{
			    return getPaneGeometry(_dockedState);
			}
    const IlvRect&	getPaneGeometry(int state) const;

protected:
    char*		_paneName;
    char*		_relativePaneName;
    IlvPosition		_relativePosition;
    int			_dockedState;
    IlBoolean		_visible;
    IlvRect		_horizontalDockedRect;
    IlvRect		_verticalDockedRect;
    IlvRect		_unDockedRect;
};

// --------------------------------------------------------------------------
// Class IlvDockingConfiguration
// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingConfiguration
{
public:
    IlvDockingConfiguration();
    IlvDockingConfiguration(const IlvDockingConfiguration&);
    virtual ~IlvDockingConfiguration();

    IlUInt		getCardinal() const
			{
			    return _paneLocations.getLength();
			}
    const IlvDockingPaneLocation*
			getLocation(const char* name) const;
    const IlvDockingPaneLocation*
			getLocation(IlUInt index) const;
    void		addLocation(const IlvDockingPaneLocation* loc);
    void		clean();

protected:
    IlvArray		_paneLocations;
};

// --------------------------------------------------------------------------
// Class IlvDockingConfigurationHandler
// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingConfigurationHandler
{
public:
    IlvDockingConfigurationHandler();
    virtual ~IlvDockingConfigurationHandler();

    virtual IlUInt	getDockingPanesCount() const = 0;
    virtual IlvPane*	getDockingPane(IlUInt index) const = 0;
    IlvPane*		getDockingPane(const char* name) const;
    virtual IlvDockableMainWindow*
			getMainWindow() const = 0;
    virtual IlvDockable* addRelativeDockingPane(IlvPane* pane,
						const char*,
						IlvPosition) const;
    virtual IlvPane*	getRelativePane(const IlvPane& pane,
					IlvPosition&,
					const
					IlvDockingConfiguration*
					c = 0) const;
    virtual IlvDockable* addUnDockedPane(IlvPane* pane,
					 const IlvRect& rect) const;
    virtual IlvDockingPaneLocation*
			createDockingPaneLocation(const IlvDockable&,
						  const char*,
						  IlvPosition) const;
    void		clearCurrentDockingConfiguration();
    void		clearCurrentDockingConfiguration(IlvPane&);

    void setCurrentDockingConfiguration(const IlvDockingConfiguration& conf,
					IlBoolean update = IlTrue);
    void getCurrentDockingConfiguration(IlvDockingConfiguration& conf) const;
    void updateAllPanes();

protected:
    void getCurrentDockingConfiguration(IlvDockable&,
					IlvDockingConfiguration&) const;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(dockutil);

#endif /* !__Ilv_Gadgets_Dockutil_H */
