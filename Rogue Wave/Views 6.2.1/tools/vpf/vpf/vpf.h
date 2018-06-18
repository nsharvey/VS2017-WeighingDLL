// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/vpf.h
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
// Declaration of global constants of the vpflib
// --------------------------------------------------------------------------
#ifndef VPF_VPF_H
#define VPF_VPF_H

class Vpf
{
public:
  typedef enum { LSB, MSB }	ByteOrder;

  static ByteOrder		MachineByteOrder;
  static ByteOrder		CheckByteOrder();

  static void			SwapTwo(void*);
  static void			SwapFour(void*);
  static void			SwapEight(void*);
};

#endif /* VPF_VPF_H */