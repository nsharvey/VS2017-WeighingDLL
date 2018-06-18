// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/util/quicksort.h
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
// Declaration of the IlvQuickSort class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Util_Quicksort_H
#define __Ilv_Layout_Util_Quicksort_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

class ILVGRLEXPORTED IlvQuickSort
{
public:
    IlvQuickSort(IlInt size = 0);
    virtual ~IlvQuickSort();

    void	sort(IlInt = -1);

protected:
    virtual IlBoolean	compare(IlUInt loc1, IlUInt loc2) = 0;
    virtual void	swap(IlUInt, IlUInt) = 0;
private:
    void	quickSort(IlInt, IlInt);
    IlInt	_lastIndex;
};

#endif /* !__Ilv_Layout_Util_Quicksort_H */
