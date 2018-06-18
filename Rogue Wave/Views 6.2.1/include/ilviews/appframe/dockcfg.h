// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dockcfg.h
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
// Declaration of the IlvDvMainContainer class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Dockcfg_H)
#define __Ilv_Appframe_Dockcfg_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Dockpane_H)
#include <ilviews/gadgets/dockpane.h>
#endif
#if !defined(__Ilv_Gadgets_Dockutil_H)
#include <ilviews/gadgets/dockutil.h>
#endif

class IlvDvNodeValue;
class IlvPane;
class IlvToolBar;
class IlvDvOptions;
class IlvDvDockableMainWindow;
class IlvDvApplication;

// --------------------------------------------------------------------------
// IlvDvSortedDockedPositions class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvSortedDockedPositions
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvSortedDockedPositions();
    ~IlvDvSortedDockedPositions();

    // ----------------------------------------------------------------------
    void	addPaneLocation(const IlvDockingPaneLocation* position);

    // get next stored position. First time,
    // direction and index must be initialized to 0
    IlvDockingPaneLocation*	getNextPosition(int& direction,
						IlUInt& index,
						const IlSymbol** = 0) const;
    IlvDockingPaneLocation*	getPosition(int direction,
					    IlUInt index,
					    const IlSymbol** = 0) const;

protected:
    // 0: top, 1: bottom, 2:left, 3:right, 4:others(hidden, floatting)
    IlvArray	_panePositions[5];
    IlvArray	_names[5];

    int		getSortedIndex(const IlvDockingPaneLocation*) const;
};

// --------------------------------------------------------------------------
// IlvDvDockingConfiguration class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDockingConfiguration : public IlvDockingConfiguration
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDockingConfiguration(const IlSymbol* name);
    IlvDvDockingConfiguration(const IlvDvDockingConfiguration& src);
    ~IlvDvDockingConfiguration();

    // ____________________________________________________________
    // Name management
    inline
    const IlSymbol*	getName()const { return _name; }
    inline void		setName(const IlSymbol* name) { _name = name; }

    IlBoolean		removeLocation(const char* locName,
				       IlBoolean deleteIt = IlTrue);
    void		renameLocation(const char* oldName,
				       const char* newName);
    void		mergeConfiguration(IlvDvDockingConfiguration* config,
					   IlBoolean deleteSrc = IlTrue);
    // Sorting configuration
    void		sortLocations(IlvDvSortedDockedPositions& positions);

    // ----------------------------------------------------------------------
    // IO
    void		readOptions(const IlvDvNodeValue* configNode);
    void		updateOptions(IlvDvNodeValue* configNode,
				      IlvDvOptions* options);

    static IlvDockingPaneLocation*
			ReadLocationOptions(const IlvDvNodeValue* node);
    static void		UpdateLocationOptions(const IlvDockingPaneLocation*,
					      IlvDvNodeValue* node);
    static IlvDockingPaneLocation*
			NewPaneLocation(IlvDockingPaneLocation* loc,
					IlBoolean deleteGivenLoc = IlTrue,
					const char* name = 0,
					const char* relativeName = 0,
					IlvPosition = IlvBadPosition,
					int dockedState = -1,
					int visible = -1,
					const IlvRect* hrect = 0,
					const IlvRect* vrect = 0,
					const IlvRect* undockedRect = 0);

protected:
    const IlSymbol*	_name;

    IlBoolean		replaceLocation(IlvDockingPaneLocation* oldLoc,
					IlvDockingPaneLocation* newLoc);
};

// --------------------------------------------------------------------------
// IlvDvBarSet class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvBarSet
{
public:
    // ----------------------------------------------------------------------
    // Constructor
    IlvDvBarSet();
    IlvDvBarSet(const char* name, IlvToolBar* bar);
    IlvDvBarSet(const char* name, IlvPane* pane);
    virtual ~IlvDvBarSet();

    // ----------------------------------------------------------------------
    void		addToolBar(const char* name, IlvToolBar* bar);

    IlvPane*		removeBar(const IlvToolBar* bar);

    IlBoolean		removePane(const IlvPane* pane);
    IlBoolean		removePaneByName(const char* paneName);


    IlvToolBar*		getToolBar(IlUInt index) const;

    IlvToolBar*		getToolBarByName(const char* name) const;

    inline IlUInt	getBarsCount() const { return getPanesCount(); }

    IlUInt		getIndex(const IlvToolBar* bar) const;

    void		addPane(const char* name, IlvPane* pane);

    IlvPane*		getPane(IlUInt index) const;

    void		setPane(IlUInt nPane, IlvPane* pane);
    IlUInt		findPaneIndex(const IlvPane* pane) const;
    IlUInt		getPanesCount() const;

    IlvView*		getContainer(IlUInt nBar) const;
    IlvGraphic*		getGraphic(IlUInt nBar) const;

    // Bar infos
    typedef enum { None, ToolBar, Graphic, Container, Pane } BarType;

    BarType		getBarType(IlUInt nBar) const;
    const char*		getBarName(IlUInt nBar) const;

    IlUInt		getPaneIndexByName(const char* name) const;
    void		rename(const char* oldName, const char* newName);

    void		removePanesInfo();
    inline IlBoolean	containPane(const IlvPane* pane) const
			{
			    return findPaneInfo(pane)? IlTrue : IlFalse;
			}
    inline void		setDeletePanesInfo(IlBoolean bSet)
			{
			    _deletePanesInfo = bSet;
			}
    void		append(const IlvDvBarSet& src);

    // ----------------------------------------------------------------------
    // I/O
    virtual IlBoolean	readOptions(const IlvDvOptions* options,
				    const IlvDvNodeValue* nodesValue,
				    const IlvDvApplication* app);

protected:

    // ----------------------------------------------------------------------
    // Panes info
    class PaneInfo {
    public:
	const IlSymbol*	_name;
	IlvPane*	_pane;

	// Docked object type
	BarType _type;
	union {
	    IlvGraphic*	_graphic;
	    IlvToolBar*	_bar;
	    IlvView*	_view;
	    IlvPane*	_pane;
	} _content;

	// ------------------------------------------------------------------
	// Constructors
	PaneInfo(const IlSymbol* name, IlvGraphic* g)
	    : _name(name), _pane(0), _type(Graphic)
	{   _content._graphic = g; }

	PaneInfo(const IlSymbol* name, IlvToolBar* bar)
	    : _name(name), _pane(0), _type(ToolBar)
	{   _content._bar = bar; }

	PaneInfo(const IlSymbol* name, IlvView* view)
	    : _name(name), _pane(0), _type(Container)
	{   _content._view = view; }

	PaneInfo(const IlSymbol* name, IlvPane* pane)
	    : _name(name), _pane(pane), _type(Pane)
	{   _content._pane = pane; _pane = pane; }
    };
    IlvArray	_panesInfo;
    IlBoolean	_deletePanesInfo;

    inline
    PaneInfo*	getPaneInfo(IlUInt iPane) const
		{
		    return (PaneInfo*)_panesInfo[iPane];
		}

    inline
    PaneInfo*	findPaneInfo(const IlvPane* pane) const
		{
		    for(IlUInt iPane = 0;
			iPane < _panesInfo.getLength();
			iPane++) {
			PaneInfo* paneInfo = getPaneInfo(iPane);
			if (paneInfo->_pane == pane)
			    return paneInfo;
		    }
		    return 0;
		}
    inline
    PaneInfo*	findPaneInfo(const char* name) const
		{
		    const IlSymbol* nameSymb = IlGetSymbol(name);
		    for(IlUInt iPane = 0;
			iPane < _panesInfo.getLength();
			iPane++) {
			PaneInfo* paneInfo = getPaneInfo(iPane);
			if (paneInfo->_name == nameSymb)
			    return paneInfo;
		    }
		    return 0;
		}
    inline
    PaneInfo*	findBarPaneInfo(const IlvToolBar* bar) const
		{
		    for(IlUInt iPane = 0;
			iPane < _panesInfo.getLength();
			iPane++) {
			PaneInfo* paneInfo = getPaneInfo(iPane);
			if ((paneInfo->_type == ToolBar) &&
			    (paneInfo->_content._bar == bar))
			    return paneInfo;
		    }
		    return 0;
		}
};

// --------------------------------------------------------------------------
// IlvDvDockingConfigurationHandler class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvDockingConfigurationHandler
    : public IlvDockingConfigurationHandler
{
public:
    // ----------------------------------------------------------------------
    // Constructor
    IlvDvDockingConfigurationHandler(IlvDvDockableMainWindow* mainWindow,
				     const IlvDvBarSet* barSet,
				     const IlvDvBarSet* relativeBarSet = 0);
    virtual ~IlvDvDockingConfigurationHandler();

    // ----------------------------------------------------------------------
    // IlvDockingConfigurationHandler methods
    virtual IlUInt		getDockingPanesCount() const;
    virtual IlvPane*		getDockingPane(IlUInt index) const;
    virtual
    IlvDockableMainWindow*	getMainWindow() const;
    virtual IlvPane*		getRelativePane(const IlvPane& pane,
						IlvPosition&,
						const
						IlvDockingConfiguration*
						c = 0) const;

    inline IlBoolean		containPane(const IlvPane* pane) const
				{
				    return _barSet
				    ? _barSet->containPane(pane)
					: IlFalse;
				}

protected:
    IlvDvDockableMainWindow*	_mainWindow;
    const IlvDvBarSet*		_barSet;
    const IlvDvBarSet*		_relativeBarSet;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(dockcfg);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dockcfg_H */
