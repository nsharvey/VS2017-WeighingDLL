// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/menuread.h
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
// Declaration of the IlvDvMenuOptionsReader class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Menuread_H)
#define __Ilv_Appframe_Menuread_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class IlvDvApplication;
class IlvDvOptions;
class IlvDvNodeValue;
class IlvOptions;
class IlvDvNodeValueArray;
class IlvAbstractMenu;
class IlvMenuItem;
class IlvGadgetItem;
class IlvPopupMenu;
class IlvGraphic;

#define GADITEM_BITMAP_COUNT 4

#ifndef COMMAND_STATE_DEFINED
#define COMMAND_STATE_DEFINED
enum IlvDvCommandState {
    Sensitive = 0,
    Selected = 1,
    Unsensitive = 2,
    Highlighted = 3 };
#endif /* COMMAND_STATE_DEFINED */
// --------------------------------------------------------------------------
// IlvDvMenuOptionsReader class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvMenuOptionsReader
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvMenuOptionsReader(IlvDvApplication* application);
    virtual ~IlvDvMenuOptionsReader();

    // ----------------------------------------------------------------------
    // Loading ressources
    IlBoolean		readBar(const char* menuName,
				IlvAbstractMenu* menu) const;
    IlBoolean		readMenu(const IlvDvNodeValue*,
				 IlvAbstractMenu* menu) const;
    IlBoolean		readPopup(const IlSymbol* menuName,
				  IlvPopupMenu* popup) const;
    IlBoolean		readMenuItems(const IlvDvNodeValue*,
				      IlvAbstractMenu* bar) const;
    IlBoolean		readMenuItems(const IlvDvNodeValue*,
				      IlvAbstractMenu* bar,
				      IlBoolean bigIcons,
				      IlBoolean showTooltips,
				      IlBoolean withShortcuts) const;

    IlvMenuItem*	createMenuItemWithCommand(const IlSymbol* actionName,
						  IlBoolean
						  inPopup = IlFalse) const;
    IlvMenuItem*	createMenuItemWithCommand(const IlSymbol* actionName,
						  IlBoolean bigIcons,
						  IlBoolean showTooltips,
						  IlBoolean withShortcuts,
						  IlBoolean inPopup) const;

    IlBoolean	completeMenuItemWithCommand(IlvMenuItem*,
					    const IlSymbol* actionName,
					    IlBoolean bigIcons = IlFalse,
					    IlBoolean showTooltips = IlTrue,
					    IlBoolean withShortcuts = IlTrue,
					    IlvDvNodeValue* = 0,
					    IlBoolean inPopup = IlFalse) const;

    const char*		getCommandMenuLabel(const IlvDvNodeValue*) const;

    IlvMenuItem*	createMenuItem(const IlvDvNodeValue* node,
				       IlBoolean inPopup = IlFalse) const;
    IlvMenuItem*	createMenuItem(const IlvDvNodeValue*,
				       IlBoolean bigIcons,
				       IlBoolean showTooltips,
				       IlBoolean withShortcuts,
				       IlBoolean inPopup) const;
    IlvDvNodeValue*	getMenuVariableFromPath(const IlvDvNodeValueArray&,
						const IlvString&,
						IlvDvNodeValue** = 0);

    IlBoolean		setActionItemBitmaps(IlvGadgetItem* gadgetItem,
					     const IlvDvNodeValue*,
					     IlBoolean bigIcon=IlFalse) const;

    // ----------------------------------------------------------------------
    // Basic accessors
    inline
    IlvDvApplication*	getDvApplication() const { return _application; }
    IlvDisplay*		getDisplay() const;
    IlvDvOptions*	getOptions() const;
    void		setOptions(IlvDvOptions* options);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_OptionMenuSymbol;
    static IlSymbol*	_PopupSymbol;
    static const char*	_OptionMenuSeparatorName;
    static const char*	_OptionMenuIsPopupField;
    static IlSymbol*	_OptionBarSymbol;
    static IlSymbol*	_OptionIsUserBarSymbol;
    static IlSymbol*	_MenuItemAppPropertySymbol;

    static void		SetGraphicCallbacks(const IlvDvApplication* app,
					    IlvGraphic* g);

    static IlSymbol*	_ActionBitmapsSymbol[GADITEM_BITMAP_COUNT + GADITEM_BITMAP_COUNT];
    static IlSymbol*	_CommandStatesSymbol[GADITEM_BITMAP_COUNT];

protected:
    IlvDvApplication*	_application;
    IlvDvOptions*	_options;

    IlvDvNodeValue*	getNodeValue(const IlSymbol* type,
				     const IlSymbol* name) const;

    const char*		getActionBitmapPath(const IlvDvNodeValue*,
					    IlvDvCommandState = Sensitive,
					    IlBoolean bigIcon = IlFalse) const;
};

// --------------------------------------------------------------------------
ILVDVEXPORTEDFUNCTION(IlvMenuItem*)
IlvDvCopyMenuItem(IlvMenuItem*); // copy the item and its properties

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(menuread);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Menuread_H */
