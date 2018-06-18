// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/ilvsock/client.h
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
#ifndef __IlvSOCKETCLIENT_H
#define __IlvSOCKETCLIENT_H

#include <ilvsock/socket.h>

class IlvClientSocket : public IlvSocket
{
public:
    IlvClientSocket(IlUShort, const char* = 0, IlvSocketReader = 0, IlAny = 0);
#if !defined(WINDOWS)
    IlvClientSocket(const char*, IlvSocketReader = 0, IlAny = 0);
#endif /* !WINDOWS */
};

#endif //__IlvSOCKETCLIENT_H
