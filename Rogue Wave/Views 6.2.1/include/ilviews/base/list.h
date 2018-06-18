// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/list.h
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
// Encapsulation of the IlListOf and related macros
// Definition of IlvList
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_List_H
#define __Ilv_Base_List_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Il_List_H)
#include <ilog/list.h>
#endif

#define IlvListOf IlListOf
#define IlvAListOf IlAListOf
#define IlvListIteratorOf IlListIteratorOf
#define IlvAListIteratorOf IlAListIteratorOf
#define IlvSafeListIteratorOf IlSafeListIteratorOf
#define IlvSafeAListIteratorOf IlSafeAListIteratorOf

#define IlvList          IlList
#define IlvLink          IlList::Cell
#define IlLink           IlList::Cell
#define IlvAList         IlAList
#define IlvAListItem     IlAList::Cell
#define IlvMapList       IlMapList
#define IlvMapListCell   IlMapListCell
#define IlvMapAList      IlMapAList
#define IlvMapAListKey   IlMapAListKey
#define IlvMapAListValue IlMapAListValue
#endif /* !__Ilv_Base_List_H */
