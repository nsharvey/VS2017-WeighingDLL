// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/dxfincl/dxwrite.h
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

#include <ilviews/base/iostream.h>
#include <ilviews/manager/manager.h>
#include <ilviews/base/hash.h>

class IlvHashTable;
// --------------------------------------------------------------------------
class IlvDXFOutput
{
public:
    IL_EXPLICIT IlvDXFOutput(ILVSTDPREF ostream& stream);
    ~IlvDXFOutput();
    // ____________________________________________________________
    ILVSTDPREF ostream& getStream() const { return *_stream; }
    void prologue();
    void epilogue();
    void save(IlvManager* manager);
    void saveObject(IlvGraphic* object);
    IlInt getLayerNum(IlvPalette* palette) const;
    IlInt getGraphicSetNum(IlvGraphicSet* gs) const;
    IlInt getLineStyleNum(IlvLineStyle* ls) const;

private:
    IlvRect		_bbox;
    ILVSTDPREF ostream* _stream;
    IlvHashTable*	_palettes;
    IlvHashTable*	_graphicSets;
    IlvHashTable*	_lineStyles;
};
