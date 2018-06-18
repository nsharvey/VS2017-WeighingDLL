// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/grphnio.h
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
// Declaration of the Input[/Output] routines for graphic groups.
// --------------------------------------------------------------------------

#ifndef __Ilv_Protos_Grphnio_H
#define __Ilv_Protos_Grphnio_H

#include <ilviews/protos/grphnode.h>
#include <ilviews/protos/groupio.h>
#include <ilviews/graphics/io.h>

// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGraphicGroupInputFile : public IlvGroupInputFile
{
public:
    IlvGraphicGroupInputFile(IlvInputFile& file)
	: IlvGroupInputFile(file.getStream()),
	  _file(file)
    {}
    IlvGraphicGroupInputFile(ILVSTDPREF istream& istr)
	: IlvGroupInputFile(istr),
	  _file(IlvInputFile(istr)) {}

    virtual IlvGroup*	readGroup(IlvDisplay* display);

protected:
    IlvInputFile	_file;
};

#endif /* __Ilv_Protos_Grphnio_H */
