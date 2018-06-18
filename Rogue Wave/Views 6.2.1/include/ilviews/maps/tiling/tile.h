// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/tiling/tile.h
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
// Definition of the IlvTile class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Tiling_Tile_H
#define __Ilv_Maps_Tiling_Tile_H

#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#  include <ilviews/base/link.h>
#endif
#if !defined(__Ilv_Maps_Featureid_H)
#  include <ilviews/maps/featureid.h>
#endif
#if !defined(__Ilv_Maps_Clssinfo_H)
#  include <ilviews/maps/clssinfo.h>
#endif

class ILVMAPSEXPORTED IlvTileController;

enum IlvTileStatus {
    IlvTileEmpty,
    IlvTileLocked,
    IlvTileCached,
    IlvTileDeleted
};

class ILVMAPSEXPORTED IlvTile
{
public:
    // not documented
    IlvTile(IlInt, IlInt,
	    IlvTileController*);
    virtual ~IlvTile();

    inline IlInt getColumn() const { return _column; }
    inline IlInt getRow() const { return _row; }
    IlvTileStatus getStatus() const { return _status; }
    void boundingBox(IlvRect& rect) const;
    void addObject(IlvGraphic* g, IlvMapFeatureId* id = 0);

    IlvDisplay* getDisplay() const;
    IlvTileController* getController() const {return _controller;}
    void deleteAll();
    IlBoolean isObjectShared(IlvGraphic* graphic)  const;
    IlvGraphic* getObject(IlvMapFeatureId* id) const;
    void reDraw() const;
    void loadComplete();
    inline IlBoolean isLoadComplete() const { return _loadComplete; }

    // Not documented. Intended to be used by the classes of the package
    // only
    void lock(IlAny);
    inline IlBoolean isLocked(IlAny lock) { return _locks.find(lock); }
    IlBoolean unLock(IlAny);
    inline const IlvList& getLocks() const { return _locks; }
private:
    IlInt _column;
    IlInt _row;
    IlvTileController* _controller;
    IlvTileStatus _status;
    IlvList _locks;
    IlBoolean _loadComplete;
};

/////////////////// class info macros for tiling ////////////////
#define IlvTilingDeclareIO(className)				\
public:								\
    static IlvClassInfo** ClassInfoRef() { return &_classinfo; }\
    static IlvMapClassInfo* ClassInfo();			\
    virtual IlvMapClassInfo* getClassInfo() const;		\
    virtual void write(IlvOutputFile&) const;			\
    className(IlvInputFile&);					\
private:							\
    static IlvClassInfo* _classinfo

#define IlvTilingDefineMembers(className)			\
IlvMapClassInfo* 						\
className::getClassInfo() const 				\
{ return ClassInfo(); }						\
IlvClassInfo* className::_classinfo = 0

#define IlvTilingDefineClassInfo(className, superClass)			\
IlAny _IlvReader_##className(IlvInputFile& file, IlAny a)		\
{ return new className(file); }						\
void _IlvWriter_##className(IlAny a,IlvOutputFile& file)		\
{ ((className*)a)->write(file); }					\
IlvMapClassInfo* className::ClassInfo() {				\
    if (!_classinfo) {							\
        _classinfo = IlvMapClassInfo::Create(#className,		\
            superClass::ClassInfoRef(),					\
            _IlvReader_##className,					\
            _IlvWriter_##className);					\
    }									\
    return (IlvMapClassInfo*)_classinfo;				\
}

/////////////////////   tiled layer macros  //////////////////////////////
#define IlvTilingDeclareLayerIO(className)				\
public:									\
    static IlvManagerLayer* read(IlvInputFile&);			\
    virtual void write(IlvOutputFile&) const;				\
    className(IlvInputFile&);						\
    virtual IlvClassInfo* getClassInfo() const;				\
    static IlvClassInfo* ClassInfo();					\
    static IlvClassInfo** ClassInfoRef() { return &_classinfo; }	\
protected:								\
    static IlvClassInfo* _classinfo

#define IlvTilingDefineLayerClassInfo(className, superClass)		\
IlvClassInfo* className::getClassInfo() const { return ClassInfo(); }	\
IlvManagerLayer* _IlvReader_##className(IlvInputFile& file)		\
{ return new className(file); }						\
IlvClassInfo* className::_classinfo = 0;				\
IlvClassInfo* className::ClassInfo() {					\
    if (_classinfo == 0) {						\
       _classinfo = IlvManagerLayerClassInfo::Create(#className,	\
                                 superClass::ClassInfoRef(),		\
                                 _IlvReader_##className);		\
    }									\
    return _classinfo;							\
}

#endif /* !__Ilv_Maps_Tiling_Tile_H */
