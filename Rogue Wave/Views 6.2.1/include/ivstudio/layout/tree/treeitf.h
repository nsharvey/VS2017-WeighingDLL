// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/tree/treeitf.h
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
// Declaration of the IlvTreeLayoutInterface class and accessors
// related to that interface.
// Defined in library ilvsttree
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Tree_Treeitf_H
#define __IlvSt_Layout_Tree_Treeitf_H

#ifndef __Ilv_Layout_Tree_H
#include <ilviews/layout/tree.h>
#endif /* __Ilv_Layout_Tree_H */

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Layout_Inspitf_H)
#include <ivstudio/layout/inspitf.h>
#endif /* __IlvSt_Layout_Inspitf_H */

#if defined(ILVSTTREELIB)
#define ILVSTTREEEXPORTED ILVBASEEXPORTED
#define ILVSTTREEEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVSTTREEEXPORTEDVAR(type)	ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVSTTREELIB */
#define ILVSTTREEEXPORTED ILVBASEIMPORTED
#define ILVSTTREEEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVSTTREEEXPORTEDVAR(type)	ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVSTTREELIB */

#define IlvDECLAREINITSTTREECLASS(m) IL_MODULEINIT(m, ILVSTTREEEXPORTED);
#define ILVSTTREEMODULEINIT(m)	IL_MODULEINIT(m, ILVSTTREEEXPORTED);

class ILVSTTREEEXPORTED IlvTreeLayoutInterface
    : public IlvLayoutInspectorInterface
{
public:
    IlvTreeLayoutInterface(IlvGraphLayout*, const char* = 0);
    virtual ~IlvTreeLayoutInterface();

    virtual IlBoolean	buildPage(IlvLayoutInspectorPanel*);
    virtual IlBoolean	createAccessors(IlvLayoutInspectorPanel*);

    virtual IlBoolean	selectLayout(IlvLayoutInspectorPanel*);
    virtual void        objectSelected(const IlvGraphic*);

    void addRoot();
    void clearRoot();
    void showSpecRoot();
    void showCalcRoot();

protected:

private:
    IlvLayoutInspectorPanel* _panel;
};

// --------------------------------------------------------------------------
typedef const char* (IlvTreeLayoutObjectGetFn)(IlvTreeLayout*,IlAny);
typedef void (IlvTreeLayoutObjectSetFn)(IlvTreeLayout*, IlAny, const char*);

// --------------------------------------------------------------------------
class ILVSTTREEEXPORTED IlvStTreeLayoutNodeAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStTreeLayoutNodeAccessor(
	IlvStIPropertyAccessor*,
	IlvTreeLayoutObjectGetFn* getFn,
	IlvTreeLayoutObjectSetFn* setFn,
	const char* name = 0,
	UpdateMode = NoUpdate,
	BuildMode = None);
protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty*);
private:
    IlvTreeLayoutObjectGetFn* _getFn;
    IlvTreeLayoutObjectSetFn* _setFn;
};

// --------------------------------------------------------------------------
class ILVSTTREEEXPORTED IlvStTreeLayoutLinkAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStTreeLayoutLinkAccessor(
	IlvStIPropertyAccessor*,
	IlvTreeLayoutObjectGetFn* getFn,
	IlvTreeLayoutObjectSetFn* setFn,
	const char* name = 0,
	UpdateMode = NoUpdate,
	BuildMode = None);
protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty*);
private:
    IlvTreeLayoutObjectGetFn* _getFn;
    IlvTreeLayoutObjectSetFn* _setFn;
};


// --------------------------------------------------------------------------
#endif /* !__IlvSt_Layout_Tree_Treeitf_H */
