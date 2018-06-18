// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/printing/include/windcfac.h
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
// IlvWindowsPrinterDCFactory subclass
// --------------------------------------------------------------------------

#include <ilviews/windows/dump.h>

// --------------------------------------------------------------------------
class MyWindowsPrinterDCFactory : public IlvWindowsPrinterDCFactory
{
public:
    // The default constructor.
    MyWindowsPrinterDCFactory();

    // Inherited functions.
    virtual HDC		getHDC() const;
    virtual IlBoolean	initializeSettings();
    virtual void	resetSettings();
    virtual short	getOrientation() const;
    virtual void	setOrientation(short newOrientation, IlvDisplay& dpy);
    virtual short	getPaperSize() const;
    virtual void	setPaperSize(short paperSize, IlvDisplay& dpy);
    virtual short	getPaperLength() const;
    virtual void	setPaperLength(short length, IlvDisplay& dpy);
    virtual short	getPaperWidth() const;
    virtual void	setPaperWidth(short width, IlvDisplay& dpy);
    virtual IlBoolean	getMinMaxPageRange(IlUShort& min, IlUShort& max) const;
    virtual void	setMinMaxPageRange(IlUShort minPage, IlUShort maxPage);
    virtual IlBoolean	getFirstLastPages(IlUShort& first,
					  IlUShort& last) const;
    virtual void	setFirstLastPages(IlUShort first, IlUShort last);
    virtual IlBoolean	isVisible() const;
    virtual void	setVisibility(IlBoolean isVisible);
    virtual IlBoolean	hasPageSettingDialog() const;
    virtual void	usePageSettingDialog(IlBoolean use);

private:
    // Intentionally not defined.
    MyWindowsPrinterDCFactory(MyWindowsPrinterDCFactory const&);
    // Intentionally not defined.
    MyWindowsPrinterDCFactory&
    operator=(MyWindowsPrinterDCFactory const& other);

    PRINTDLG _printdlg;
};
