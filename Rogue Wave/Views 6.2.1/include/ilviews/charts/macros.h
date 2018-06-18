// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/macros.h
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
// Definition of the chart library macros.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Macros_H
#define __Ilv_Charts_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVCHTLIB)
#define ILVCHTEXPORTED ILVBASEEXPORTED
#define ILVCHTEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVCHTEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVCHTLIB */
#define ILVCHTEXPORTED ILVBASEIMPORTED
#define ILVCHTEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVCHTEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVCHTLIB */

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvcharts.lib")
#endif

#define ILVCHTMODULEINIT(m) IL_MODULEINIT(c_##m, ILVCHTEXPORTED)
#define ILVSUPERCLASSINFO(s) &s::_classinfo

// --------------------------------------------------------------------------
#define IlvCHTDoublePrecision	0.000000000001
#define IlvCHTItvPrecision	0.000000000001

// --------------------------------------------------------------------------
#define IlvChartsVersion 110

// --------------------------------------------------------------------------
// IlvChartDataPointInfo macros
#define DeclareChartDataPointInfoTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvChartDataPointInfoClassInfo* getChartDataPointInfoClassInfo() const \
	{ return (IlvChartDataPointInfoClassInfo*)getClassInfo(); }\
    static IlvChartDataPointInfo* Read(IlvInputFile&); \
    virtual IlvChartDataPointInfo* copy() const
#define DeclareChartDataPointInfoTypeInfo(classname) \
DeclareChartDataPointInfoTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedChartDataPointInfoIOMembers(classname) \
IlvChartDataPointInfo* classname::copy() const \
{ return new classname(*this); } \
IlvChartDataPointInfo* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvPointInfoCollection macros
#define DeclarePointInfoCollectionTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvPointInfoCollectionClassInfo* getPointInfoCollectionClassInfo() const \
	{ return (IlvPointInfoCollectionClassInfo*)getClassInfo(); }\
    static IlvPointInfoCollection* Read(IlvInputFile&); \
    virtual IlvPointInfoCollection* copy() const
#define DeclarePointInfoCollectionTypeInfo(classname) \
DeclarePointInfoCollectionTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedPointInfoCollectionIOMembers(classname) \
IlvPointInfoCollection* classname::copy() const \
{ return new classname(*this); } \
IlvPointInfoCollection* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvChartDataSet macros
#define DeclareChartDataSetTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvChartDataSetClassInfo* getChartDataSetClassInfo() const \
	{ return (IlvChartDataSetClassInfo*)getClassInfo(); }\
    static IlvChartDataSet* Read(IlvInputFile&); \
    virtual IlvChartDataSet* copy() const
#define DeclareChartDataSetTypeInfo(classname) \
DeclareChartDataSetTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedChartDataSetIOMembers(classname) \
IlvChartDataSet* classname::copy() const \
{ return new classname(*this); } \
IlvChartDataSet* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvAbstractChartData macros
#define DeclareChartDataTypeInfoRO(classname) public:	    \
    classname(IlvInputFile& file);			    \
    classname(const classname& source);			    \
    IlvDeclarePropClassInfo();				    \
    IlvChartDataClassInfo* getChartDataClassInfo() const    \
	{ return (IlvChartDataClassInfo*)getClassInfo(); }  \
    static IlvAbstractChartData* Read(IlvInputFile&);	    \
    virtual IlvAbstractChartData* copy() const

#define DeclareChartDataTypeInfo(classname)		    \
DeclareChartDataTypeInfoRO(classname);			    \
virtual void write(IlvOutputFile&) const

// Added for a problem of compatibility with the old charts
#if defined(IlvPredefinedChartDataIOMembers)
#undef IlvPredefinedChartDataIOMembers
#endif

#define IlvPredefinedChartDataIOMembers(classname)	    \
IlvAbstractChartData* classname::copy() const		    \
{ return new classname(*this); }			    \
IlvAbstractChartData* classname::Read(IlvInputFile& i)	    \
{ return new classname(i); }

//== 3.1 Compat
#define DeclareAbstractChartDataTypeInfoRO(classname)	    \
DeclareChartDataTypeInfoRO(classname)
#define DeclareAbstractChartDataTypeInfo(classname)	    \
DeclareChartDataTypeInfo(classname)
#define IlvPredefinedAbstractChartDataIOMembers(classname) \
IlvPredefinedChartDataIOMembers(classname)

// --------------------------------------------------------------------------
// IlvAbstractChartDisplayer macros
#define DeclareChartDisplayerTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvChartDisplayerClassInfo* \
    getChartDisplayerClassInfo() const \
	{ return (IlvChartDisplayerClassInfo*)getClassInfo(); }\
    static IlvAbstractChartDisplayer* Read(IlvInputFile&); \
    virtual IlvAbstractChartDisplayer* copy() const
#define DeclareChartDisplayerTypeInfo(classname) \
DeclareChartDisplayerTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedChartDisplayerIOMembers(classname) \
IlvAbstractChartDisplayer* classname::copy() const \
{ return new classname(*this); } \
IlvAbstractChartDisplayer* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvAbstractGridDisplayer macros
#define DeclareGridDisplayerTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvGridDisplayerClassInfo* \
    getGridDisplayerClassInfo() const \
	{ return (IlvGridDisplayerClassInfo*)getClassInfo(); }\
    static IlvAbstractGridDisplayer* Read(IlvInputFile&); \
    virtual IlvAbstractGridDisplayer* copy() const
#define DeclareGridDisplayerTypeInfo(classname) \
DeclareGridDisplayerTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedGridDisplayerIOMembers(classname) \
IlvAbstractGridDisplayer* classname::copy() const \
{ return new classname(*this); } \
IlvAbstractGridDisplayer* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvAbstractChartCursor macros
#define DeclareChartCursorTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvChartCursorClassInfo* \
    getChartCursorClassInfo() const \
	{ return (IlvChartCursorClassInfo*)getClassInfo(); }\
    static IlvAbstractChartCursor* Read(IlvInputFile&); \
    virtual IlvAbstractChartCursor* copy() const
#define DeclareChartCursorTypeInfo(classname) \
DeclareChartCursorTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedChartCursorIOMembers(classname) \
IlvAbstractChartCursor* classname::copy() const \
{ return new classname(*this); } \
IlvAbstractChartCursor* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvCoordinateTransformer macros
//#define IlvAbstractCoordinateTransformer IlvCoordinateTransformer
#define DeclareCoordinateTransformerTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvCoordinateTransformerClassInfo* getCoordinateTransformerClassInfo() const \
	{ return (IlvCoordinateTransformerClassInfo*)getClassInfo(); }\
    static IlvCoordinateTransformer* Read(IlvInputFile&); \
    virtual IlvCoordinateTransformer* copy() const
#define DeclareCoordinateTransformerTypeInfo(classname) \
DeclareCoordinateTransformerTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedCoordinateTransformerIOMembers(classname) \
IlvCoordinateTransformer* classname::copy() const \
{ return new classname(*this); } \
IlvCoordinateTransformer* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvCoordinateInfo macros
#define IlvChartCoordinateInfo IlvCoordinateInfo
#define DeclareCoordinateInfoTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvCoordinateInfoClassInfo* getCoordinateInfoClassInfo() const \
	{ return (IlvCoordinateInfoClassInfo*)getClassInfo(); }\
    static IlvCoordinateInfo* Read(IlvInputFile&); \
    virtual IlvCoordinateInfo* copy() const
#define DeclareCoordinateInfoTypeInfo(classname) \
DeclareCoordinateInfoTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedCoordinateInfoIOMembers(classname) \
IlvCoordinateInfo* classname::copy() const \
{ return new classname(*this); } \
IlvCoordinateInfo* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvAbstractProjector macros
#define DeclareProjectorTypeInfoRO(classname) public: \
    classname(IlvInputFile& file); \
    classname(const classname& source); \
    IlvDeclarePropClassInfo();	\
    IlvProjectorClassInfo* getProjectorClassInfo() const \
	{ return (IlvProjectorClassInfo*)getClassInfo(); }\
    static IlvAbstractProjector* Read(IlvInputFile&); \
    virtual IlvAbstractProjector* copy() const
#define DeclareProjectorTypeInfo(classname) \
DeclareProjectorTypeInfoRO(classname); \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedProjectorIOMembers(classname) \
IlvAbstractProjector* classname::copy() const \
{ return new classname(*this); } \
IlvAbstractProjector* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvChartLayout macros
#define DeclareChartLayoutTypeInfoRO(classname) public:	    \
    classname(IlvInputFile& file);			    \
    classname(const classname& source);			    \
    IlvDeclarePropClassInfo();				    \
    IlvChartLayoutClassInfo*				    \
	getChartLayoutClassInfo() const			    \
	{ return (IlvChartLayoutClassInfo*)getClassInfo(); }\
    static IlvChartLayout* Read(IlvInputFile&);		    \
    virtual IlvChartLayout* copy() const
#define DeclareChartLayoutTypeInfo(classname)		    \
DeclareChartLayoutTypeInfoRO(classname);		    \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedChartLayoutIOMembers(classname)	    \
IlvChartLayout* classname::copy() const			    \
{ return new classname(*this); }			    \
IlvChartLayout* classname::Read(IlvInputFile& i)	    \
{ return new classname(i); }

// --------------------------------------------------------------------------
// IlvAbstractScaleDisplayer macros
#define DeclareScaleDisplayerTypeInfoRO(classname) public:  \
    classname(IlvInputFile& file);			    \
    classname(const classname& source);			    \
    IlvDeclarePropClassInfo();				    \
    IlvScaleDisplayerClassInfo*				    \
    getScaleDisplayerClassInfo() const			    \
    { return (IlvScaleDisplayerClassInfo*)getClassInfo(); } \
    static IlvAbstractScaleDisplayer* Read(IlvInputFile&);  \
    virtual IlvAbstractScaleDisplayer* copy() const
#define DeclareScaleDisplayerTypeInfo(classname)	    \
DeclareScaleDisplayerTypeInfoRO(classname);		    \
virtual void write(IlvOutputFile&) const
#define IlvPredefinedScaleDisplayerIOMembers(classname)	    \
IlvAbstractScaleDisplayer* classname::copy() const	    \
{							    \
    IlvAbstractScaleDisplayer* s = new classname(*this);    \
    s->copyProperties(*this); return s;			    \
}							    \
IlvAbstractScaleDisplayer* classname::Read(IlvInputFile& i) \
{ return new classname(i); }

//== 3.1 Compat
#define DeclareAbstractScaleDisplayerTypeInfoRO(classname)  \
DeclareScaleDisplayerTypeInfoRO(classname)
#define DeclareAbstractScaleDisplayerTypeInfo(classname)    \
DeclareScaleDisplayerTypeInfo(classname)
#define IlvPredefinedAbstractScaleIOMembers(classname)	    \
IlvPredefinedScaleIOMembers(classname)

// --------------------------------------------------------------------------
// Debug
#if defined(ILVCHDEBUG)
#define ILVCHASSERT(cond, expr) { if (!(cond)) { expr; } }
#define ILVCHTRACE(expr) { expr; }
#define ILVCHDBG_ARG(A) A
#else  /* !ILVDEBUG */
#define ILVCHASSERT(cond, expr)
#define ILVCHTRACE(expr)
#define ILVCHDBG_ARG(A)
#endif /* !ILVDEBUG */

#endif /* __Ilv_Charts_Macros_H */
