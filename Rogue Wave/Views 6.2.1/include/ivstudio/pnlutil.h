// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/pnlutil.h
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
// Declaration of IlvStPanelUtil
// --------------------------------------------------------------------------
#ifndef __IlvSt_Pnlutil_H
#define __IlvSt_Pnlutil_H

#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

#if defined(ILVSTD)
#include <iostream>
#else
#include <iostream.h>
#endif

class IlvStudio;
class IlvStCommandDescriptor;

class IlvContainer;
class IlvGraphic;

class IlvMenuBar;
class IlvAbstractMenu;
class IlvTextField;
class IlvComboBox;
class IlvPopupMenu;
class IlvGadgetItem;
class IlvMenuItem;
class IlvGadgetContainer;
class IlvToggle;
class IlvStringList;
class IlvNotebook;

// --------------------------------------------------------------------------
typedef void (*IlvStMapMenuFunction)(IlvAbstractMenu*, IlAny);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPanelUtil
{
public:
    // Properties
    static IlvStudio* GetEditor(const IlvGraphic*);
    static void SetEditor(IlvGraphic*, IlvStudio*);
    static IlAny GetCaller(const IlvGraphic*);
    static void SetCaller(IlvGraphic*, IlAny caller);
    static IlvStCommandDescriptor* GetCommandDescriptor(const IlvGraphic*);
    static void SetCommandDescriptor(IlvGraphic*, IlvStCommandDescriptor*);
    static void SetCommandDescriptor(IlvGraphic*, const char*);
    static IlvStCommandDescriptor* GetCommandDescriptor(const IlvGadgetItem*);
    static void SetCommandDescriptor(IlvGadgetItem*, IlvStCommandDescriptor*);
    static void SetCommandDescriptor(IlvGadgetItem*, const char*);

    // Containers and objects
    static void Fill(IlvGadgetContainer* cont, const char* fdata);
    static IlvGraphic* GetObject(const IlvNotebook*,
				 const char* objName,
				 const char* contName = 0);
    static IlvTextField* GetTextField(const IlvNotebook* notebook,
				      const char* name,
				      const char* contName = 0);
    static IlvToggle* GetToggle(const IlvNotebook* notebook,
				const char* name,
				const char* contName = 0);
    static void SetToggleState(IlvNotebook*, const char*, IlBoolean);
    static void SetTextFieldLabel(IlvNotebook*, const char*, const char*);
    static void SetTextFieldLabel(const IlvContainer*,
				  const char* name,
				  const char* label);
    static const char* GetTextFieldLabel(const IlvContainer*,
					 const char* name);
    static void SetTextFieldValue(const IlvContainer*,
				  const char* name,
				  IlInt);
    static IlInt GetTextFieldValue(const IlvContainer*, const char* name);
    static void SetToggleState(const IlvContainer*,
			       const char* name,
			       IlBoolean value);
    static IlBoolean GetToggleState(const IlvContainer* cont,
				     const char* name);
    static const char* GetSelectedString(const IlvContainer* cont,
					 const char* name);

    // Menus and tool bars
    static IlvPopupMenu* ReadPopupMenu(IlvStudio* editor, 
                                       IL_STDPREF istream& istrm);
    static IlvPopupMenu* CreatePopupMenu(IlvStudio*,
					 IlUShort count,
					 const char* const*);
    static void MapMenu(IlvStMapMenuFunction, IlvAbstractMenu*, IlAny);
    static void InitializeMenu(IlvAbstractMenu*,
			       IlvStudio*,
			       IlAny caller = 0);
    static void InitializeMenuItem(IlvMenuItem*, IlvStudio*, const char*);
    static void InitializeToolBarItem(IlvMenuItem*, IlvStudio*, const char*);
    static const char* GetToolTipString(IlvStudio*, IlvStCommandDescriptor*);

    // Other objects
    static void InitializeObject(IlvGraphic* obj,
				 IlvStudio* studio,
				 const char* commandName,
				 IlAny = 0);
    static void SetSelectedString(const IlvContainer* cont,
				  const char* name,
				  const char* label);
    // Misc
    static int GlobalInit();
}; // class IlvStPanelUtil

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_pnlutil)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Pnlutil_H */

