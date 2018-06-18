// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/listener.h
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
// Declaration of the IlvGraphModelEvent class
// Declaration of the IlvGraphModelListener class
// Declaration of the IlvGraphLayoutEvent class
// Declaration of the IlvGraphLayoutListener class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Listener_H
#define __Ilv_Layout_Listener_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif /* __Ilv_Base_Clssinfo_H */

class IlvGraphModel;
class IlvGraphLayout;
class IlvGraphLayoutReport;

// --------------------------------------------------------------------------
enum IlvGraphModelEventType {
    IlvGraphModelNoTypeEvent = 0,
    IlvGraphModelStructureChangedEvent = 1,
    IlvGraphModelGeometryChangedEvent = 2,
    IlvGraphModelAdjustmentEndEvent = 32
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphModelEvent
: public IlvLayoutValueInterface
{
public:
    IlvGraphModelEvent(IlvGraphModel*);
    virtual ~IlvGraphModelEvent();

    IlvGraphModel*	getGraphModel() const;

    IlvGraphModelEventType	getType() const;
    void			setType(IlvGraphModelEventType);    

    void		setAdjusting(IlBoolean set);
    IlBoolean		isAdjusting() const;

    IlvDeclareLazyClassInfo();

protected:
private:
    IlvGraphModel*		_graphModel;
    IlBoolean			_adjusting;
    IlvGraphModelEventType	_type;
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphModelListener
: public IlvLayoutValueInterface
{ 
public:
    IlvGraphModelListener();
    virtual ~IlvGraphModelListener();
    virtual void contentsChanged(const IlvGraphModelEvent& event) = 0;

    IlvDeclareLazyClassInfo();
};

// --------------------------------------------------------------------------
enum IlvGraphLayoutEventType {
    IlvGraphLayoutNoTypeEvent = 0,
    IlvGraphLayoutStructureChangedEvent = 1,
    IlvGraphLayoutGeometryChangedEvent = 2,
    IlvGraphLayoutStructureGeometryChangedEvent = 3,
    IlvGraphLayoutAdjustmentEndEvent = 32
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphLayoutEvent
: public IlvLayoutValueInterface
{
public:
    IlvGraphLayoutEvent(const IlvGraphLayout* layout);
    virtual ~IlvGraphLayoutEvent();

    IlvGraphLayoutReport*	getLayoutReport() const;
    const IlvGraphLayout*	getLayout() const;

    IlvDeclareLazyClassInfo();

protected:
    const IlvGraphLayout*	_layout;
private:
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphLayoutListener
: public IlvLayoutValueInterface
{
public:
    IlvGraphLayoutListener();
    virtual ~IlvGraphLayoutListener();

    virtual void layoutStepPerformed(const IlvGraphLayoutEvent& event) = 0;

    IlvDeclareLazyClassInfo();

protected:
private:
};

ILVGRLMODULEINIT(l_listener)
#endif /* !__Ilv_Layout_Listener_H */
