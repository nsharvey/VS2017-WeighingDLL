// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/vpf.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Definition of general purpose functions
// --------------------------------------------------------------------------

#include <vpf/vpf.h>

Vpf::ByteOrder Vpf::MachineByteOrder = Vpf::CheckByteOrder();

// --------------------------------------------------------------------------
Vpf::ByteOrder
Vpf::CheckByteOrder()
{
    unsigned short test = 0x7F00;
    return (*((char*)&test) == 0x7F) ? MSB : LSB;
}

// --------------------------------------------------------------------------
void
Vpf::SwapTwo(void* value)
{
    char buffer;
    char* in = (char*) value;
    buffer = in[0];
    in[0] = in[1];
    in[1] = buffer;
}

// --------------------------------------------------------------------------
void
Vpf::SwapFour(void* value)
{
    char buffer;
    char* in = (char*) value;

    buffer = in[0];
    in[0] = in[3];
    in[3] = buffer;
    buffer = in[1];
    in[1] = in[2];
    in[2] = buffer;
}

// --------------------------------------------------------------------------
void
Vpf::SwapEight(void* value)
{
    char buffer;
    char* in = (char*) value;

    buffer = in[0];
    in[0] = in[7];
    in[7] = buffer;
    buffer = in[1];
    in[1] = in[6];
    in[6] = buffer;
    buffer = in[2];
    in[2] = in[5];
    in[5] = buffer;
    buffer = in[3];
    in[3] = in[4];
    in[4] = buffer;
}
