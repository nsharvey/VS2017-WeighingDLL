// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/prorect.h
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
// Declarations of the IlvSCProto*Rectangle classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Prorect_h
#define __Ilv_Protos_Prorect_h

#if !defined(__Ilv_Protos_Progdmgr_H)
#include <ilviews/protos/progdmgr.h>
#endif
#if !defined(__Ilv_Protos_Allaccs_H)
#include <ilviews/protos/allaccs.h>
#endif
#if !defined(__Ilv_Gadmgr_Rectscmg_H)
#include <ilviews/gadmgr/rectscmg.h>
#endif

// ---------------------------------------------------------------------------
// IlvSCProtoManagerRectangle
// ---------------------------------------------------------------------------
class ILVGDPEXPORTED IlvSCProtoManagerRectangle : public IlvSCManagerRectangle
{
public:
    IlvSCProtoManagerRectangle(IlvDisplay*    display,
			       const IlvRect& rect,
			       IlvPalette*    palette = 0);
    inline
    IlvProtoManager*	getProtoManager() const
			{
			    return (IlvProtoManager*)getManager();
			}

    DeclareTypeInfo();
    DeclareIOConstructors(IlvSCProtoManagerRectangle);
};

// ---------------------------------------------------------------------------
// IlvSCProtoGadgetManagerRectangle
// ---------------------------------------------------------------------------
class ILVGDPEXPORTED IlvSCProtoGadgetManagerRectangle
    : public IlvSCManagerRectangle
{
public:
    IlvSCProtoGadgetManagerRectangle(IlvDisplay*    display,
				     const IlvRect& rect,
				     IlvPalette*    palette = 0);
    inline
    IlvProtoGadgetManager*	getProtoGadgetManager() const
				{
				    return (IlvProtoGadgetManager*)
					getManager();
				}

    DeclareTypeInfo();
    DeclareIOConstructors(IlvSCProtoGadgetManagerRectangle);
};

// ---------------------------------------------------------------------------
// IlvSCProtoGrapherRectangle
// ---------------------------------------------------------------------------

class ILVGDPEXPORTED IlvSCProtoGrapherRectangle : public IlvSCManagerRectangle
{
public:
    IlvSCProtoGrapherRectangle(IlvDisplay*    display,
			       const IlvRect& rect,
			       IlvPalette*    palette = 0);
    inline
    IlvProtoGrapher*	getProtoGrapher() const
			{
			    return (IlvProtoGrapher*)getManager();
			}

    DeclareTypeInfo();
    DeclareIOConstructors(IlvSCProtoGrapherRectangle);
};

IlvDECLAREINITGDPCLASS(prorect)
#endif /* __Ilv_Protos_Prorect_H */
