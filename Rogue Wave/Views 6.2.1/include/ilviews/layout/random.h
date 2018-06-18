// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/random.h
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
// Declaration of the IlvRandomLayout class
// Defined in library ilvrandom
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Random_H
#define __Ilv_Layout_Random_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvrandom.lib")
#endif

#if !defined(__Ilv_Layout_Gphlayout_H)
#include <ilviews/layout/gphlayout.h>
#endif /* __Ilv_Layout_Gphlayout_H */

#if defined(ILVRANDLIB)
#define ILVRANDEXPORTED ILVBASEEXPORTED
#define ILVRANDEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVRANDEXPORTEDVAR(type)	ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVRANDLIB */
#define ILVRANDEXPORTED ILVBASEIMPORTED
#define ILVRANDEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVRANDEXPORTEDVAR(type)	ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVRANDLIB */

#define ILVRANDMODULEINIT(m)	IL_MODULEINIT(m, ILVRANDEXPORTED);

class ILVRANDEXPORTED IlvRandomLayout
: public IlvGraphLayout
{
public:
    IlvRandomLayout();
    ~IlvRandomLayout();

protected:
    void	layout();

public:
    IlBoolean	supportsPreserveFixedNodes() const;
    IlBoolean	supportsLayoutRegion() const;
    IlBoolean	supportsRandomGenerator() const;

    void			setLinkStyle(IlvLayoutLinkStyle linkStyle);
    IlvLayoutLinkStyle		getLinkStyle() const;



    // ------------------- Accessors ----------------------------
    DeclareLayoutAccessors();
    IlvDeclareLazyClassInfo();

private:
    IlvLayoutLinkStyle	_linksStyle;
    static const IlvLayoutLinkStyle	DefaultLinkStyle;
};

ILVRANDMODULEINIT(lr_random)
#endif /* !__Ilv_Layout_Random_H */
