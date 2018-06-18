// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/transfer.h
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
// Declaration of base component transfer filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Transfer_H
#define __Ilv_Bitmaps_Transfer_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif


class ILVDSPEXPORTED IlvTransferFunction : public IlvValueInterface
{
public:
    IlvTransferFunction();
    virtual ~IlvTransferFunction();
    static IlvTransferFunction*	Create(const char* name);
    const IlUChar*		getLookUpTable() const;
    void			setLookUpValue(IlUInt index, IlUChar value);
    IlvDeclareClassInfo();

protected:
    IlUChar*			_lutdata;
};

ILVDSPMODULETERM(bitmaps_transfer);

#endif /* __Ilv_Bitmaps_Transfer_H */
