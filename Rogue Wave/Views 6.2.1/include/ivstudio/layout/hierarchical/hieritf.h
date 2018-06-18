// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/hierarchical/hieritf.h
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
// Declaration of the IlvHierarchicalLayoutInterface class and accessors
// related to that interface.
// Defined in library ilvsthierarchical
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Hierarchical_Hierarchicalitf_H
#define __IlvSt_Layout_Hierarchical_Hierarchicalitf_H

#ifndef __Ilv_Layout_Hierarchical_H
#include <ilviews/layout/hierarchical.h>
#endif /* __Ilv_Layout_Hierarchical_H */

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Layout_Inspitf_H)
#include <ivstudio/layout/inspitf.h>
#endif /* __IlvSt_Layout_Inspitf_H */

#if defined(ILVSTHIERLIB)
#define ILVSTHIERLAYEXPORTED ILVBASEEXPORTED
#define ILVSTHIERLAYEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVSTHIERLAYEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVSTHIERLIB */
#define ILVSTHIERLAYEXPORTED ILVBASEIMPORTED
#define ILVSTHIERLAYEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVSTHIERLAYEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVSTHIERLIB */

#define IlvDECLAREINITSTHIERLAYCLASS(m)	IL_MODULEINIT(m, ILVSTHIERLAYEXPORTED);
#define ILVSTHIERLAYMODULEINIT(m)	IL_MODULEINIT(m, ILVSTHIERLAYEXPORTED);

class ILVSTHIERLAYEXPORTED IlvHierarchicalLayoutInterface
    : public IlvLayoutInspectorInterface
{
public:
    IlvHierarchicalLayoutInterface(IlvGraphLayout*, const char* = 0);
    virtual ~IlvHierarchicalLayoutInterface();

    virtual IlBoolean	buildPage(IlvLayoutInspectorPanel*);
    virtual IlBoolean	createAccessors(IlvLayoutInspectorPanel*);

    virtual IlBoolean	selectLayout(IlvLayoutInspectorPanel*);
    virtual void        objectSelected(const IlvGraphic*);

    IlvDeclarePropClassInfo();

protected:

private:
    IlvLayoutInspectorPanel* _panel;
};

// --------------------------------------------------------------------------
typedef const char* (IlvHierLayoutObjectGetFn)(IlvHierarchicalLayout*,IlAny);
typedef void (IlvHierLayoutObjectSetFn)(IlvHierarchicalLayout*, IlAny, const char*);

// --------------------------------------------------------------------------
class ILVSTHIERLAYEXPORTED IlvStHierLayoutNodeAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStHierLayoutNodeAccessor(IlvStIPropertyAccessor*,
                  IlvHierLayoutObjectGetFn* getFn,
                  IlvHierLayoutObjectSetFn* setFn,
                  const char* name = 0,
                  UpdateMode = NoUpdate,
                  BuildMode = None);
protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty*);
private:
    IlvHierLayoutObjectGetFn* _getFn;
    IlvHierLayoutObjectSetFn* _setFn;
};

// --------------------------------------------------------------------------
class ILVSTHIERLAYEXPORTED IlvStHierLayoutLinkAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStHierLayoutLinkAccessor(IlvStIPropertyAccessor*,
                  IlvHierLayoutObjectGetFn* getFn,
                  IlvHierLayoutObjectSetFn* setFn,
                  const char* name = 0,
                  UpdateMode = NoUpdate,
                  BuildMode = None);
protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty*);
private:
    IlvHierLayoutObjectGetFn* _getFn;
    IlvHierLayoutObjectSetFn* _setFn;
};


ILVSTHIERLAYMODULEINIT(lh_hieritf)

// --------------------------------------------------------------------------
#endif /* !__IlvSt_Layout_Hierarchical_Hieritf_H */
