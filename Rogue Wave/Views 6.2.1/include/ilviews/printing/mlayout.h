// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/mlayout.h
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
// Definition of the IlvPrintableLayoutMultiplePages class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_LayoutMultiplePages_H
#define __Ilv_Printing_LayoutMultiplePages_H

#if !defined(__Ilv_Printing_Layout_H)
#include <ilviews/printing/layout.h>
#endif

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableLayoutMultiplePages
    : public IlvPrintableLayout
{
public:
    IlvPrintableLayoutMultiplePages(int columns = 2, 
				    int rows = 2);
    virtual int getPageNumber(IlvPrintableJob& job) const;
    virtual int getRows() const;
    virtual int getColumns() const;
    void setRows(int rows);
    void setColumns(int columns);
    virtual void initializeBackgroundArea(IlvPrintableJob& job) const;
    virtual void initializeHeaderArea(IlvPrintableJob& job) const;
    virtual void initializeMainArea(IlvPrintableJob& job) const;
    virtual void initializeFooterArea(IlvPrintableJob& job) const;
    virtual void initializeForegroundArea(IlvPrintableJob& job) const;
    virtual void
    updateBackgroundArea(IlvPrintableJob& job, int pageIndex) const;
    virtual void
    updateHeaderArea(IlvPrintableJob& job, int pageIndex) const;
    virtual void
    updateMainArea(IlvPrintableJob& job, int pageIndex) const;
    virtual void
    updateFooterArea(IlvPrintableJob& job, int pageIndex) const;
    virtual void
    updateForegroundArea(IlvPrintableJob& job, int pageIndex) const;
    virtual void setHeaderAreaHeight(IlvDim height);
    virtual void setFooterAreaHeight(IlvDim height);
    virtual IlvDim getHeaderAreaHeight() const;
    virtual IlvDim getFooterAreaHeight() const;
    IlvRect getPrintableArea(IlvPrinter const& printer) const;

protected:
    IlBoolean getPositionFromIndex(int pageIndex, 
				   int& column, 
				   int& row) const;
private:
    int          _columns;
    int          _rows;
    IlvDim	 _headerAreaHeight;
    IlvDim	 _footerAreaHeight;
};

// --------------------------------------------------------------------------
// Inlined functions.
// --------------------------------------------------------------------------
inline int
IlvPrintableLayoutMultiplePages::getRows() const
{
    return _rows;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableLayoutMultiplePages::getColumns() const
{
    return _columns;
}

#endif /* __Ilv_Printing_LayoutMultiplePages_H */
