// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ViewsToOCX/ATLstep2/democtrl.cpp
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
#include <DemoCtrl.h>

// --------------------------------------------------------------------------
IlvDisplay* DemoCtrl::_Display = 0;

// --------------------------------------------------------------------------
bool
DemoCtrl::InitDisplay(HINSTANCE hInstance) throw ()
{
#if defined(ILVSTD)
    try {
#endif /* ILVSTD */
        _Display = new IlvDisplay(hInstance, "ATL Views Sample");
	if (!_Display || _Display->isBad()) {
	    IlvFatalError("Can't initialize IlvDisplay.");
	    if (_Display) {
		delete _Display;
		_Display = 0;
	    }
	}
#if defined(ILVSTD)
    }
    catch(...) {
	CleanDisplay();
    }
#endif /* ILVSTD */
    return _Display ? true : false;
}

// --------------------------------------------------------------------------
void
DemoCtrl::CleanDisplay()
{
    if (_Display) {
	delete _Display;
	_Display = 0;
    }
}

// --------------------------------------------------------------------------
DemoCtrl::DemoCtrl(HWND hWnd)
   : Ctrl(_Display, reinterpret_cast<IlvSystemView>(hWnd))
{
}

// --------------------------------------------------------------------------
DemoCtrl::~DemoCtrl()
{
}
