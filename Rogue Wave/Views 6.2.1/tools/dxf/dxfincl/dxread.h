// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/dxfincl/dxread.h
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
// Declaration of the IlvDXFInput class
// --------------------------------------------------------------------------
#ifndef __IlvTools_DXREAD_H
#define __IlvTools_DXREAD_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Graphics_Set_H)
#include <ilviews/graphics/set.h>
#endif

IL_STDUSE

// --------------------------------------------------------------------------
class DXFGroup;
class DXFList;
class IlvDXFInput
{
public:
    IlvDXFInput(IL_STDPREF istream& stream);
    virtual ~IlvDXFInput();
    // ____________________________________________________________
    IlBoolean isBad() const;
    IlvGraphic** readObjects(IlUInt& n, IlvDisplay&);
    int    getAngdir() const { return _angdir; }
    double getAngbase() const { return _angbase; }
    void   setViewsExtents(const IlvRect& size, IlBoolean keepRatio = IlTrue);
    const IlvFloatPoint& getExtmin() const { return _extmin; }
    const IlvFloatPoint& getExtmax() const { return _extmax; }
    const IlvTransformer& getTransformer() const { return _transformer; }
    void translate(IlFloat dx, IlFloat dy);
    void  scale(IlFloat fixedx, IlFloat fixedy,
		IlFloat sx, IlFloat sy);
    void rotate(IlFloat centerx, IlFloat centery, IlFloat angle);
protected:
    IL_STDPREF istream&    getStream() const { return _stream; }
    IlvDisplay* getDisplay() const { return _display; }
    virtual int readSection(); // returns 1 on error
    virtual int readHeader(); // returns 1 on error
    virtual int readTables(); // returns 1 on error
    virtual int readTable(const char*); // returns 1 on error
    virtual int readBlocks();   // returns 1 on error
    virtual int readBlock();    // returns 1 on error
    virtual int readEntities(); // returns 1 on error
    virtual int readLtype(); // returns 1 on error
    virtual int readLayer(); // returns 1 on error
    virtual const char*   parseColor(int colorIndex) const;
    virtual IlvColor*     createColor(int colorIndex) const;
    virtual IlvLineStyle* createLineStyle(const char* lineStyleName) const;
    virtual IlvPalette* createPalette(const char* layerName, int color = -1) const;
    virtual IlvGraphic* createGraphicObject(DXFList* entityGroupSet) const;
private:
    IlvPoint scale(const IlvFloatPoint&) const;
    int readGroup(); // return 1 on error
    void addBlock(DXFList*);
    DXFList* getEntitiesOfBlock(const char* blockName) const;
    void cleanUp();
    ILVSTDPREF istream& _stream;
    IlvTransformer	_transformer;
    double		_angbase; // as read in the DXF file
    int			_angdir;  //		//
    IlvFloatPoint	_extmin;  //		//
    IlvFloatPoint	_extmax;  //		//
    IlvDisplay*		_display;
    IlvGraphic**	_objects;
    int			_binaryFormat;
    DXFGroup*		_group;
    IlBoolean		_groupReadAhead;
    IlUInt		_fileOffset; // line number or byte offset
    DXFList*		_ltypes;
    DXFList*		_layers;
    DXFList*		_blocks;
    DXFList*		_entities;
};
#endif /* __IlvTools_DXREAD_H */
