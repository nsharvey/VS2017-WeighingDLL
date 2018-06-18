// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/flayout.h
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
// Definition of the IlvPrintableLayoutFixedSize class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_LayoutFixedSize_H
#define __Ilv_Printing_LayoutFixedSize_H

#if !defined(__Ilv_Printing_LayoutMultiplePages_H)
#include <ilviews/printing/mlayout.h>
#endif

#if !defined(__Ilv_Printing_Units_H)
#include <ilviews/printing/units.h>
#endif
// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableLayoutFixedSize
: public IlvPrintableLayoutMultiplePages
{
public:
    IlvPrintableLayoutFixedSize(IlvPrintUnit const& width,
				IlvPrintUnit const& height);

    virtual int getPageNumber(IlvPrintableJob& job) const;
    IlvDim getWidth() const;
    IlvDim getHeight() const;
    void setWidth(IlvPrintUnit const& width);
    void setHeight(IlvPrintUnit const& height);

protected:
    virtual void
    updateMainArea(IlvPrintableJob& job, int pageIndex) const;

private:
    IlvDim       _width;
    IlvDim       _height;
};

// --------------------------------------------------------------------------
// Inlined functions.
// --------------------------------------------------------------------------
inline IlvDim
IlvPrintableLayoutFixedSize::getWidth() const
{
    return _width;
}

// --------------------------------------------------------------------------
inline IlvDim
IlvPrintableLayoutFixedSize::getHeight() const
{
    return _height;
}

#endif /* __Ilv_Printing_LayoutFixedSize_H */
