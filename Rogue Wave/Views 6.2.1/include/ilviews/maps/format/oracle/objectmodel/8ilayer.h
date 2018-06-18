// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/8ilayer.h
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
// Rogue Wave Views - Maps add-on.
// Declaration of the IlvObjectSDOLayer class
// Defined in library ilvdbmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Objectmodel_8ilayer_H
#define __Ilv_Maps_Format_Oracle_Objectmodel_8ilayer_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/format/oracle/sdolayer.h>

class IlvObjectSDOLayerMetaData;
class IlvMapInfo;
class IldDbms;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvObjectSDOLayer
    : public IlvSDOLayer
{
public:
    IlvObjectSDOLayer(const IlvMapAdapter* mapAdapter,
		      IldDbms* dbms,
		      const char* tableName,
		      const char* geometryColumnName,
		      IlDouble tileWidth,
		      IlDouble tileHeight,
		      const char* xCoordinateColumnName = 0,
		      const char* yCoordinateColumnName = 0,
		      const char* keyColumnName = 0,
		      const char* password = 0);

    IlvObjectSDOLayer(IlvSDOTileLoader* sdoTileLoader,
		      IlvTileCache* cache,
		      const char* password = 0);

    void		setAttachingAttributes(IlBoolean attachAttributes);
    IlBoolean		isAttachingAttributes() const
	{ return _attachAttributes; }

    IlvTilingDeclareLayerIO(IlvObjectSDOLayer);

private:
    void		init(const char*);

    IlBoolean		_attachAttributes;
};

ILVDBMAPSMODULEINIT(IlvObjectSDOLayer);

#endif /* __Ilv_Maps_Format_Oracle_Objectmodel_8ilayer_H */
