// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/wprinter.h
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
// Definition of IlvWindowsPrinter class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Windows_Printer_H
#define __Ilv_Printing_Windows_Printer_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(WINDOWS) || DOXYGEN_GENERATION

#if !defined(__Ilv_Printing_Printer_H)
#include <ilviews/printing/printer.h>
#endif
#if !defined(__Ilv_Windows_Dump_H)
#include <ilviews/windows/dump.h>
#endif

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvWindowsPrinter : public IlvPrinter
{
public:
    IlvWindowsPrinter(IlvDisplay* display);
   ~IlvWindowsPrinter();
    virtual IlvRect getUsableArea() const;
    IlvPort* makePort() const;
    void setPrinterDescription(char const* printerDescription);
    IlvWindowsPrinterDCFactory* getPrinterDCFactory() const;
    void setPrinterDCFactory(IlvWindowsPrinterDCFactory* factory);
     virtual IlBoolean checkErrorStatus() const;
    virtual IlvDim getPaperHeight() const;
    virtual IlvDim getPaperWidth() const;
    virtual IlvRect getPaperSize() const;
    virtual IlBoolean initializeSettings();

protected:
    virtual IlBoolean internalInitialize();
    virtual void internalSetOrientation(Orientation orient);
    virtual void internalSetPaperFormat(IlvPaperFormat const& format);
    virtual void internalSetMargins(IlvDim left,
				    IlvDim right,
				    IlvDim top,
				    IlvDim bottom);
    virtual void internalSetClip(IlvRegion const* newClip);
    virtual void internalInitClip(IlvRect const& newClip);
    virtual void internalSetTransformer(IlvTransformer const& transformer);

private:
    char*			_printerDescription;
    IlvWindowsPrinterDCFactory*	_printerFactory;
};

// --------------------------------------------------------------------------
//
// Inlined functions.
//
// --------------------------------------------------------------------------
inline IlvWindowsPrinterDCFactory*
IlvWindowsPrinter::getPrinterDCFactory() const
{
    return _printerFactory;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsPrinter::setPrinterDCFactory(IlvWindowsPrinterDCFactory* factory)
{
    _printerFactory = factory;
}

#endif /* WINDOWS */

#endif /* __Ilv_Printing_Windows_Printer_H */
