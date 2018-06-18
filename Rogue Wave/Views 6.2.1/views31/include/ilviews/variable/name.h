// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/name.h
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
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Name_H
#define __Ilv31_Variable_Name_H

#if !defined(__Ilv31_Variable_List_H)
#include <ilviews/variable/list.h>
#endif

ILVV_LIST_DEF3(IlvvBaseNameList, char*, char*)
class ILV31VAREXPORTED IlvvNameList
: public IlvvBaseNameList
{
public:
    IlvvNameList(){}
    ~IlvvNameList();
};

typedef ILVV_LIST_LINK(IlvvBaseNameList) IlvvPath;

extern "C" {
char*     IlvvCopyName(const char*);
IlvvPath* IlvvCharP2Path(const char*);
char*     IlvvPath2CharP(IlvvPath*);
IlvvPath* IlvvCopyPath(IlvvPath*);
void      IlvvDeletePath(IlvvPath*);
// does not free the argument
IlvvPath* IlvvInvertPath(IlvvPath* path2invert, IlvvPath* inverted=0);
}

#endif
