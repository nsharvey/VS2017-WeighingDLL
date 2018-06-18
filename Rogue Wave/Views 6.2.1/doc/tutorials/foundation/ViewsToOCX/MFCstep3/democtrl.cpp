// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ViewsToOCX/MFCstep3/democtrl.cpp
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
#include "stdafx.h"
#include <DemoCtrl.h>
#include <ilviews/manager/manager.h>

// --------------------------------------------------------------------------
IlvDisplay* DemoCtrl::_Display = 0;

// --------------------------------------------------------------------------
bool
DemoCtrl::InitDisplay(HINSTANCE hInstance) throw ()
{
#if defined(IL_STD)
    try {
#endif /* ILVSTD */
        _Display = new IlvDisplay(hInstance, "MFC Views Sample");
	if (!_Display || _Display->isBad()) {
	    IlvFatalError("Can't initialize IlvDisplay.");
	    if (_Display) {
		delete _Display;
		_Display = 0;
	    }
	}
#if defined(IL_STD)
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

// --------------------------------------------------------------------------
void
DemoCtrl::setFileName(const char* filename)
{
    if (!filename || !*filename) {
	return;
    }
    IlvManager* manager = getManager();
    if (!manager) {
	return;
    }
    manager->initReDraws();
    manager->deleteAll(IlvTrue, IlvFalse);
    manager->read(filename);
    manager->fitTransformerToContents(getManagerView());
    manager->reDrawViews();
}

// --------------------------------------------------------------------------
void
DemoCtrl::setBackground(OLE_COLOR oleColor)
{
    if (oleColor == -1) {
	return;
    }
    IlvManager* manager = getManager();
    if (!manager) {
	return;
    }
    COLORREF colRef;
    HPALETTE hPal = NULL;
    if (getDisplay()->screenDepth() <= 8) {
	hPal = HPALETTE(getDisplay()->getPaletteHandle());
    }
    if (S_OK != OleTranslateColor(oleColor, hPal, &colRef)) {
	return;
    }
    IlvIntensity red, blue, green;
    getDisplay()->pixelToRGB((unsigned long)(colRef), red, blue, green);
    IlvColor* color = getDisplay()->getColor(red, blue, green);
    manager->initReDraws();
    manager->setBackground(getManagerView(), color);
    manager->reDraw();
    manager->reDrawViews();
}
