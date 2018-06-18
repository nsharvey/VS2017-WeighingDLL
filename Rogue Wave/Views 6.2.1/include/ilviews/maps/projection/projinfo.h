// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/projinfo.h
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
// The Projection Class Information
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_ProjectionClassInfo_H
#define __Ilv_Maps_ProjectionClassInfo_H


#include <ilviews/maps/macros.h>
#include <ilviews/intrface/value.h>
#include <ilviews/base/value.h>

class ILVDSPEXPORTED IlvInputFile;
class ILVDSPEXPORTED IlvOutputFile;
class ILVMAPSEXPORTED IlvProjection;

typedef IlvProjection* (* IlvProjectionConstructor)();
ILVMAPSEXPORTED IlvProjection* IlvNullProjectionConstructor();

typedef IlvProjection* (* IlvProjectionReader)(IlvInputFile&);
ILVMAPSEXPORTED IlvProjection* IlvNullProjectionReader(IlvInputFile&);

typedef IlvProjection* (* _ilvPROJ4Parser) (IlStringHashTable* );
ILVMAPSEXPORTED IlvProjection* _ilvNullPROJ4Parser(IlStringHashTable* );

typedef IlBoolean (*IlvProjectionInterfaceSetter)(IlvProjection* projection,
						    const IlvValue& value);
ILVMAPSEXPORTED IlBoolean 
IlvNullProjectionInterfaceSetter(IlvProjection*, const IlvValue&);

typedef void (*IlvProjectionInterfaceGetter)(const IlvProjection* projection,
					     IlvValue& value);
ILVMAPSEXPORTED void 
IlvNullProjectionInterfaceGetter(const IlvProjection*, IlvValue&);

typedef void (* IlvAccessorInitializer)();
ILVMAPSEXPORTED void IlvNullAccessorInitializer();


ILVMAPSMODULETERM(projinfo);


class ILVMAPSEXPORTED IlvProjectionClassInfo
: public IlvValuedClassInfo
{
protected:
    // Constructor for common projections
    IlvProjectionClassInfo(const char* className,
			   IlvClassInfo** superClass,
			   IlvProjectionReader reader,
			   IlvProjectionConstructor constructor,
			   const char* projectionName);

    // Constructor for projections providing PROJ4
    // compatibility - Not documented
    IlvProjectionClassInfo(const char* className,
			   IlvClassInfo** superClass,
			   IlvProjectionReader reader,
			   _ilvPROJ4Parser parser,
			   IlvProjectionConstructor constructor,
			   IlvAccessorInitializer accessorInitalizer,
			   const char* projectionName,
			   const char* PROJ4Name);
public:
    // Create common projection
    static IlvProjectionClassInfo* Create(const char* className,
					  IlvClassInfo** superClass,
					  IlvProjectionReader reader,
					  IlvProjectionConstructor constructor,
					  const char* projectionName);
    // Create projection providing PROJ4
    // compatibility - Not documented
    static IlvProjectionClassInfo* Create(const char* className,
					  IlvClassInfo** superClass,
					  IlvProjectionReader reader,
					  _ilvPROJ4Parser parser,
					  IlvProjectionConstructor constructor,
					  IlvAccessorInitializer accessorInitalizer,
					  const char* projectionName,
					  const char* PROJ4Name);
    ~IlvProjectionClassInfo();

    const char* getProjectionName() const {return _projectionName;}
    IlBoolean isAbstract() {return _abstract;}
    IlvProjection* createProjection() const;

    // Interface oriented functions
    void addAccessor(const IlvSymbol* name,
		     IlvValueTypeClass* type,
		     IlvProjectionInterfaceGetter,
		     IlvProjectionInterfaceSetter);
    IlBoolean applyValue(IlvProjection*, const IlvValue&) const;
    IlvValue& queryValue(const IlvProjection*, IlvValue& value) const;
    IlBoolean isValueReadOnly(const IlvSymbol* name) const;
    void getAccessors(const IlvSymbol* const** accessors,
		      const IlvValueTypeClass* const** types,
		      IlUInt& count) const;
    void getClassAccessors(const IlvSymbol* const**,
			   const IlvValueTypeClass* const**,
			   IlUInt&,
			   IlBoolean expandBaseClasses = IlTrue) const;
    IlvValueTypeClass* getValueType(const IlvSymbol*) const;

    // for internal use in the library
    // not documented
    IlvProjectionReader getReader() const {return _reader;}
    IlBoolean isClassPersistent() const {return _persistant;}
    _ilvPROJ4Parser getParser() const {return _parser;}
    const char* getPROJ4Name() const {return _proj4Name;}
    IlBoolean isPROJ4Compatible() const {return _proj4Compatible;}

    void setPROJ4Compatible() {_proj4Compatible = IlTrue;}

    static IlList*  GetAllProjections();


private:
    void initAccessors();
private:
    static void Finalize();
    static void Register(IlvProjectionClassInfo*);

private:
    IlvProjectionConstructor _constructor;
    IlvProjectionReader _reader;
    _ilvPROJ4Parser _parser;
    IlvAccessorInitializer _accessorInitializer;
    IlBoolean _persistant;
    IlBoolean _proj4Compatible;
    IlBoolean _abstract;
    const char* _projectionName;
    const char* _proj4Name;
    IlBoolean _accessorInitialized;

    // interface oriented members
    IlHashTable*  _getters;
    IlHashTable*  _setters;
    IlHashTable*  _types;
    const IlvSymbol** _allAccessors;
    const IlvValueTypeClass** _allTypes;
    IlUInt _allCount;
    const IlvSymbol** _locAccessors;
    const IlvValueTypeClass** _locTypes;
    IlUInt _locCount;

    IlvMapsIcFriend(projinfo, ILVMAPSEXPORTED);
};

#endif
