// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/application.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the Application class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_APPLICATION_H
#define VPF_GUI_APPLICATION_H

#include <ilviews/base/view.h>
#include <ilviews/base/resource.h>

// --------------------------------------------------------------------------
class Application
{
public:
    Application(IlvDisplay* display)
	{
	    _display = display;
	    _application = this;
	}
    virtual ~Application() {}
    // ____________________________________________________________
    virtual void setCursor(IlvCursor* cursor)
	{
	    IlUInt count = 0;
	    IlvView* const* views = _display->getViews(count);
	    for (IlUInt i = 0; i < count; i++)
		views[i]->setCursor(cursor);
	}
    virtual void setBusy(IlBoolean busy)
	{
	    IlvCursor* cursor = busy
		? _display->getCursor("wait")
		: _display->defaultCursor();
	    setCursor(cursor);
	}
    virtual void setStatus(const char* = 0) {}
    virtual void handleError() = 0;
    static Application* GetApplication() { return _application; }
    static IlvDisplay* GetDisplay() { return _display; }
protected:
    static IlvDisplay* _display;
    static Application* _application;
};

#endif /* VPF_GUI_APPLICATION_H */
