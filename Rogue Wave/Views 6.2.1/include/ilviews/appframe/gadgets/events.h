// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/gadgets/events.h
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
#ifndef __Ilv_Appframe_Gadgets_Events_H
#define __Ilv_Appframe_Gadgets_Events_H

#if !defined(__Ilv_Appframe_Interf_H)
#  include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Gadgets_Scombo_H)
#  include <ilviews/gadgets/scombo.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#  include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#  include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#  include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#  include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Gadgets_Matrix_H)
#  include <ilviews/gadgets/matrix.h>
#endif
#if !defined(__Ilv_Gadgets_Sheet_H)
#  include <ilviews/gadgets/sheet.h>
#endif
#if !defined(__Ilv_Gadgets_Hsheet_H)
#  include <ilviews/gadgets/hsheet.h>
#endif

// --------------------------------------------------------------------------
// IlvDvGadgetEvent
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvGadgetEvent
{
public:
    static IlSymbol*	_Callback;
    static IlSymbol*	_Initialize;
};

// --------------------------------------------------------------------------
// Initializing a gadget
// --------------------------------------------------------------------------
#define InitializeGadget(name, method, gadgetType) \
switch(action) { \
case ILVDV_CALL_METHOD: \
    if (arg._method._name == IlvDvGadgetEvent::_Initialize) { \
    	IlString gdtName=(const char*)*arg._method._paramValue->getValue(0);\
	if (!gdtName.equals(name)) { break; } \
	method((gadgetType*)(IlAny)*arg._method._paramValue->getValue(1)); \
	return IlTrue; \
    } \
    break; \
case ILVDV_PROCESS_GADGETEVENTS: \
    if (arg._method._name == IlvDvGadgetEvent::_Initialize) { \
	IlString gdtName=(const char*)*arg._method._paramValue->getValue(0);\
	if (gdtName.equals(name)) { return IlTrue; } \
    } \
    break; \
}

#define InitializeComboBox(name, method) \
    InitializeGadget(name, method, IlvScrolledComboBox)
#define InitializeTextField(name, method) \
    InitializeGadget(name, method, IlvTextField)
#define InitializeToggle(name, method) \
    InitializeGadget(name, method, IlvToggle)
#define InitializeStringList(name, method) \
    InitializeGadget(name, method, IlvStringList)
#define InitializeTree(name, method) \
    InitializeGadget(name, method, IlvTreeGadget)
#define InitializeMatrix(name, method) \
    InitializeGadget(name, method, IlvMatrix)
#define InitializeSheet(name, method) \
    InitializeGadget(name, method, IlvSheet)
#define InitializeHSheet(name, method) \
    InitializeGadget(name, method, IlvHierarchicalSheet)

#define GadgetNotification(name, callbackName, method, gadgetType) \
switch(action) { \
case ILVDV_CALL_METHOD: \
if (arg._method._name == IlvDvGadgetEvent::_Callback) { \
	IlString gadgetName = (const char*)*arg._method._paramValue->getValue(0); \
	if (!gadgetName.equals(name)) \
	    break; \
	if (callbackName != (IlAny)*arg._method._paramValue->getValue(1)) \
	    break; \
	method((gadgetType*)(IlAny)*arg._method._paramValue->getValue(2)); \
	return IlTrue; \
    } \
    break; \
case ILVDV_PROCESS_GADGETEVENTS: \
    if (arg._method._name == IlvDvGadgetEvent::_Initialize) { \
	IlString gadgetName = (const char*)*arg._method._paramValue->getValue(0); \
	if (gadgetName.equals(name)) \
	    return IlTrue; \
    } \
    break; \
}


#define CallbackNotification(name, method) \
switch(action) { \
case ILVDV_CALL_METHOD: \
if (arg._method._name == IlvDvGadgetEvent::_Callback) { \
	IlString cbName = \
	    (const char*)*arg._method._paramValue->getValue(1); \
	if (!cbName.equals(name)) \
	    break; \
	method(); \
	return IlTrue; \
    } \
    break; \
case ILVDV_PROCESS_GADGETEVENTS: \
    if (arg._method._name == IlvDvGadgetEvent::_Initialize) { \
	IlString cbName=(const char*)*arg._method._paramValue->getValue(1); \
	if (cbName.equals(name)) \
	    return IlTrue; \
    } \
    break; \
}

IlvDECLAREINITDVCLASS(events);
#endif /* !__Ilv_Appframe_Gadgets_Events_H */
