// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/preview.h
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
// Definition of the IlvPrinterPreview classe.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Preview_H
#define __Ilv_Printing_Preview_H

#if !defined(__Ilv_Printing_Printer_H)
#include <ilviews/printing/printer.h>
#endif

class IlvPort;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrinterPreview : public IlvPrinter
{
public:
    IlvPrinterPreview(IlvPrinter& referencePrinter);
    virtual IlvRect getUsableArea() const;
    virtual IlvPort* makePort() const;
     virtual IlBoolean checkErrorStatus() const;
    virtual IlvDim getPaperHeight() const;
    virtual IlvDim getPaperWidth() const;
    virtual IlvRect getPaperSize() const;
    IlvPrinter& getReferencePrinter() const;
    IlBoolean drawPage(IlvPort*			port,
		       IlvTransformer const&	transformer,
		       IlvRegion const&		clip,
		       IlInt			page) const;
    IlInt getPageNumber() const;

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
    virtual IlBoolean initializeSettings();

private:
    IlvPrinter&	_referencePrinter;
};

// --------------------------------------------------------------------------
//
// Inlined functions
//
// --------------------------------------------------------------------------
inline IlvPrinter&
IlvPrinterPreview::getReferencePrinter() const
{
    return _referencePrinter;
}

#endif /* __Ilv_Printing_Preview_H */
