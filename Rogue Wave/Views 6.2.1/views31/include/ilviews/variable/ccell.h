// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/ccell.h
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
//
// Defined in library ilvvar
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Ccell_H
#define __Ilv31_Variable_Ccell_H

#if !defined(__Ilv31_Variable_Name_H)
#include <ilviews/variable/name.h>
#endif

class IlvvCell;

class ILV31VAREXPORTED IlvvCellReferencer
{
public:
    virtual void removeCell(IlvvCell*) = 0;
    virtual void resetCell(IlvvCell*) = 0;
    virtual IlvvPath* computePath() = 0;
};

class ILV31VAREXPORTED IlvvCellContext
{
public:
    virtual IlvvPath* computePath(IlvvPath*) = 0;
    virtual void removeCell(IlvvCell*) = 0;
};

#endif
