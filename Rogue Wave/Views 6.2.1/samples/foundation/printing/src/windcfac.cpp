// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/printing/src/windcfac.cpp
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
// IlvWindowsPrinterDCFactory subclass implementation
// --------------------------------------------------------------------------
//
// This file implements MyWindowsPrinterDCFactory. This class implementation 
// has been simplified in order to only allow A6 printing in landscape mode.
// 
// --------------------------------------------------------------------------

#include <windcfac.h>

// --------------------------------------------------------------------------
//
// MyWindowsPrinterDCFactory member functions.
//
// --------------------------------------------------------------------------
MyWindowsPrinterDCFactory::MyWindowsPrinterDCFactory()
: IlvWindowsPrinterDCFactory(),
  _printdlg()
{
    memset(&_printdlg, 0, sizeof(PRINTDLG));
    _printdlg.lStructSize = sizeof(PRINTDLG);
}

// --------------------------------------------------------------------------
HDC
MyWindowsPrinterDCFactory::getHDC() const
{
    if (isInitialized()) 
	return _printdlg.hDC;
    return 0;
}

// --------------------------------------------------------------------------
IlBoolean
MyWindowsPrinterDCFactory::initializeSettings()
{    
    if (_printdlg.hDevMode) {
	GlobalFree(_printdlg.hDevMode);
	_printdlg.hDevMode = 0;
    }
    if (_printdlg.hDevNames) {
	GlobalFree(_printdlg.hDevNames);
	_printdlg.hDevNames = 0;
    }
    if (_printdlg.hDC) {
	DeleteDC(_printdlg.hDC);
	_printdlg.hDC = 0;
    }
	
    _printdlg.Flags = PD_RETURNDEFAULT;    
    _printdlg.Flags |= PD_RETURNDC;

    IlBoolean result = PrintDlg(&_printdlg) ? IlTrue : IlFalse;    
    
    if (!result) {
	DeleteDC(_printdlg.hDC);
        _printdlg.hDC = 0;
        unsetInitialized();
    } else {
	LPDEVMODE devMode = (LPDEVMODE) GlobalLock(_printdlg.hDevMode);
        devMode->dmOrientation = getOrientation();
        devMode->dmPaperSize = getPaperSize();
	devMode->dmFields |= DM_ORIENTATION;
	devMode->dmFields |= DM_PAPERSIZE;
	devMode->dmFields &= ~DM_PAPERLENGTH;
	devMode->dmFields &= ~DM_PAPERWIDTH;
	devMode->dmFields &= ~DM_FORMNAME;
	ResetDC(_printdlg.hDC, devMode);	
	int w = GetDeviceCaps(_printdlg.hDC,HORZSIZE);
	int h = GetDeviceCaps(_printdlg.hDC,VERTSIZE);
        GlobalUnlock(_printdlg.hDevMode);
	setInitialized();
    }
    return result;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::resetSettings()
{
    unsetInitialized();
}

// --------------------------------------------------------------------------
short
MyWindowsPrinterDCFactory::getOrientation() const
{
    return DMORIENT_LANDSCAPE;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setOrientation(short newOrientation,
					  IlvDisplay& display)
{
    // TODO.
}

// --------------------------------------------------------------------------
short
MyWindowsPrinterDCFactory::getPaperSize() const
{
    return DMPAPER_A6;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setPaperSize(short newPaperSize,
					IlvDisplay& display)
{
    // TODO.
}

// --------------------------------------------------------------------------
short
MyWindowsPrinterDCFactory::getPaperLength() const
{
    short length = (getOrientation() == DMORIENT_LANDSCAPE) ? 105 : 148;
    return length;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setPaperLength(short newPaperLength,
					  IlvDisplay& display)
{
    // TODO.
}

// --------------------------------------------------------------------------
short
MyWindowsPrinterDCFactory::getPaperWidth() const
{
    short width = (getOrientation() == DMORIENT_LANDSCAPE) ? 148 : 105;
    return width;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setPaperWidth(short newPaperWidth,
IlvDisplay& display)
{
    // TODO.
}

// --------------------------------------------------------------------------
IlBoolean
MyWindowsPrinterDCFactory::getMinMaxPageRange(IlUShort& minPage,
					      IlUShort& maxPage) const
{
    // TODO.
    return IlFalse;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setMinMaxPageRange(IlUShort minPage,
					      IlUShort maxPage)
{
    // TODO.
}

// --------------------------------------------------------------------------
IlBoolean
MyWindowsPrinterDCFactory::getFirstLastPages(IlUShort& firstPage,
					     IlUShort& lastPage) const
{
    // TODO.
    return IlFalse;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setFirstLastPages(IlUShort firstPage,
					     IlUShort lastPage)
{
    // TODO.
}

// --------------------------------------------------------------------------
IlBoolean
MyWindowsPrinterDCFactory::isVisible() const
{
    return IlFalse;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::setVisibility(IlBoolean isVisible)
{
    // Nothing to do when no dialog.
}

// --------------------------------------------------------------------------
IlBoolean
MyWindowsPrinterDCFactory::hasPageSettingDialog() const
{
    return IlFalse;
}

// --------------------------------------------------------------------------
void
MyWindowsPrinterDCFactory::usePageSettingDialog(IlBoolean use)
{
    // Nothing to do when no dialog.
}
