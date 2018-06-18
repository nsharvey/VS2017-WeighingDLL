// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/link.h
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
// Encapsulation of the IlLink and related classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Link_H
#define __Ilv_Base_Link_H

#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif
#if !defined(IlLink)
#define IlLink IlList::Cell
#endif
#define IlvLink IlList::Cell
#define IlvAListItem IlAList::Cell
#define IlvMapLink IlMapListCell

#endif /* !__Ilv_Base_Link_H */
