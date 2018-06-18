// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/mgrprint.h
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
// Definition of manager inherited classes of IlvPrintable.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Printables_Manager_H
#define __Ilv_Printing_Printables_Manager_H

#if !defined(__Ilv_Printing_ManagerMacros_H)
#include <ilviews/printing/mgrmacros.h>
#endif

#if !defined(__Ilv_Printing_Printable_H)
#include <ilviews/printing/printable.h>
#endif

class IlvManager;
class IlvMgrView;
class IlvManagerLayer;

// --------------------------------------------------------------------------
class ILVPRTMGREXPORTED IlvPrintableManager : public IlvPrintableScalable
{
public:
    IlvPrintableManager(IlvManager const*	manager,
			IlvRect const*		scalableArea = 0,
			IlvRegion const*	clip = 0,
			IlvTransformer const*	t = 0);
    IlvManager const* getManager() const;

protected:
    virtual IlBoolean internalPrint(IlvPrintableJob const& job) const;

private:
    IlvManager const*	_manager;
};

// --------------------------------------------------------------------------
class ILVPRTMGREXPORTED IlvPrintableMgrView : public IlvPrintableScalable
{
public:
    IlvPrintableMgrView(IlvMgrView const*	mgrView,
			IlvRect const*		scalableArea = 0,
			IlvRegion const*	clip = 0);
    IlvMgrView const* getMgrView() const;

protected:
    virtual IlBoolean internalPrint(IlvPrintableJob const& job) const;

private:
    IlvMgrView const*	_mgrView;
};

// --------------------------------------------------------------------------
class ILVPRTMGREXPORTED IlvPrintableManagerLayer : public IlvPrintableScalable
{
public:
    IlvPrintableManagerLayer(IlvManagerLayer const*	mgrLayer,
			     IlvRect const*		scalableArea = 0,
			     IlvRegion const*		clip = 0,
			     IlvTransformer const*	t = 0);
    IlvManagerLayer const* getManagerLayer() const;

protected:
    virtual IlBoolean internalPrint(IlvPrintableJob const& job) const;

private:
    IlvManagerLayer const*	_mgrLayer;
};

// --------------------------------------------------------------------------
// Inline functions.
// --------------------------------------------------------------------------
inline IlvManager const*
IlvPrintableManager::getManager() const
{
    return _manager;
}

// --------------------------------------------------------------------------
inline IlvMgrView const*
IlvPrintableMgrView::getMgrView() const
{
    return _mgrView;
}

// --------------------------------------------------------------------------
inline IlvManagerLayer const*
IlvPrintableManagerLayer::getManagerLayer() const
{
    return _mgrLayer;
}

#endif /* __Ilv_Printing_Printables_Manager_H */
