// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/boolean.h
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
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Boolean_H
#define __Ilv31_Variable_Boolean_H

// beware not to insert a boolean in a stream
// false would be printed as the null char!
typedef unsigned char IlvvBoolean;

// #defines to allow static initialisations of variables with booleans
// in shared libraries. if they are consts, it does not work.
#define IlvvFalse  ((IlvvBoolean)0)
#define IlvvTrue   ((IlvvBoolean)1)

#endif
