// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/metadata.h
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
// Declaration of the IlvObjectSDOKeyExtractor class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------

#ifndef __Ilv_Maps_Format_Oracle_METADATA_H
#define __Ilv_Maps_Format_Oracle_METADATA_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/clssinfo.h>
#include <ilviews/maps/maps.h>

class IlvObjectSDODimElement;

class ILVDBMAPSEXPORTED IlvObjectSDOLayerMetaData
{
    friend class IlvObjectSDOUtil;
public:   

    virtual ~IlvObjectSDOLayerMetaData();

    IlvObjectSDOLayerMetaData(const char* ownerName,
			      const char* tableName,
			      const char* geometryColumn,
			      IlvObjectSDODimElement** dimElements,
			      IlInt dimElementCount);

    inline const char*	getOwnerName() const { return _ownerName.getValue(); }


    inline const char*	getTableName() const { return _tableName.getValue(); }

    inline const char*	getGeometryColumn() const
			{
			    return _geometryColumn.getValue();
			}

    inline IlInt	getDimElementCount() const
			{
			    return _dimElementsCount;
			}

    IlvObjectSDODimElement* getDimElementAt(IlInt index) const;

private:
    IlString			_ownerName;
    IlString			_tableName;
    IlString			_geometryColumn;
    IlvObjectSDODimElement**	_dimElements;
    IlInt			_dimElementsCount;
};

#endif /* __Ilv_Maps_Format_Oracle_METADATA_H */
