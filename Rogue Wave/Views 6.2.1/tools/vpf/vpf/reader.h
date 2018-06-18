// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/reader.h
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
// Declaration of the VpfReader class
// --------------------------------------------------------------------------
#ifndef VPF_READER_H
#define VPF_READER_H

#include <vpf/basictypes.h>
#include <vpf/extent.h>
#include <vpf/set.h>

class VpfDatabase;
class VpfLibrary;
class VpfCoverage;
class VpfProjection;
class VpfTable;
class VpfTheme;
class VpfCoordinate;
class VpfExtent;
class VpfSet;
class VpfPoint;
class VpfSegment;
class VpfArea;
class VpfText;
// --------------------------------------------------------------------------
class VpfReader
{
public:
    VpfReader(const char* databasepath);
    virtual ~VpfReader();
    // ____________________________________________________________
    inline VpfDatabase*		getDatabase() const { return _database;   }
    inline VpfLibrary*		getLibrary() const { return _library;    }
    void			setLibrary(const char* libname);
    inline void			setLibrary(VpfLibrary* library)
				{
				    _library = library;
				}
    inline VpfProjection*	getProjector() const { return _projector; }
    inline void			setProjector(VpfProjection* projector)
				{
				    _projector = projector;
				}
    void			project(VpfCoordinate*) const;
    inline const VpfExtent&	getExtent() const { return _extent; }
    inline void			setExtent(const VpfExtent& extent)
				{
				    _extent = extent;
				}
    inline VpfSet*		getFeatures() const { return _features; }
    inline void			setFeatures(VpfSet* f)
				{
				    delete _features; _features = f;
				}
    // ____________________________________________________________
    int				isBad();
    // ____________________________________________________________
    // Reading the primitives:
    void			loadFeatures(VpfCoverage*,
					     VpfSet* features = 0,
					     void**  userArgs = 0);
    void			loadThemes(VpfCoverage*,
					   VpfUInt    nthemes,
					   VpfTheme** themes,
					   void**     userArgs = 0);
    // ____________________________________________________________
    virtual VpfCoordinate&	whereIs(double x, double y) const;

protected:
    VpfDatabase*		_database;
    VpfLibrary*			_library;
    VpfProjection*		_projector;
    VpfExtent			_extent;
    VpfSet*			_features;

    // ____________________________________________________________
    // Creating objects from primitives:
    virtual void		createNode(const VpfCoordinate& coords,
					   void*) = 0;
    virtual void		createEdge(VpfInt         count,
					   VpfCoordinate* coords,
					   void*) = 0;
    virtual void		createFace(VpfInt         count,
					   VpfCoordinate* coords,
					   void*) = 0;
    virtual void		createText(const VpfCoordinate& where,
					   const char*          text,
					   void*) = 0;
    virtual void		loadingFeature(VpfUInt, VpfUInt);
    void			load(VpfPoint*, void*);
    void			load(VpfSegment*, void*);
    void			load(VpfArea*, void*);
    void			load(VpfText*, void*);
};

#endif /* VPF_VPF_H */
