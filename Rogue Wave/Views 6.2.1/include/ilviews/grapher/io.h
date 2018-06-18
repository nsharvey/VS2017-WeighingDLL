// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/io.h
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
// Declaration of the IlvGraphOutputFile and IlvGraphInputFile classes
// Defined in library grapher
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Io_H
#define __Ilv_Grapher_Io_H

#if !defined(__Ilv_Manager_Io_H)
#  include <ilviews/manager/io.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#  include <ilviews/grapher/grapher.h>
#endif

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGraphOutputFile
: public IlvManagerOutputFile {
public:
    IlvGraphOutputFile(ILVSTDPREF ostream& stream,
		       const IlvGrapher* grapher = 0)
    : IlvManagerOutputFile(stream, grapher)
    {}
    // ____________________________________________________________
    inline const IlvGrapher* getGrapher() const
        { return (const IlvGrapher*)getManager(); }
    virtual void writeObject(const IlvGraphic* obj);
    virtual const char* typeOf() const;
};
//end:Graou

// --------------------------------------------------------------------------
//$doc:Grain
class ILVGRAPHEXPORTED IlvGraphInputFile
: public IlvManagerInputFile {
public:
    IlvGraphInputFile(ILVSTDPREF istream& stream, IlvGrapher* grapher = 0)
    : IlvManagerInputFile(stream, grapher),
      _hasGrapherInfo(IlFalse)
    {}
    // ____________________________________________________________
    inline IlvGrapher* getGrapher() const
        { return (IlvGrapher*)getManager(); }
    virtual IlvGraphic* readObject();
    virtual const char* typeOf() const;
protected:
    IlBoolean hasGrapherInfo() const { return _hasGrapherInfo; }
    IlBoolean	_hasGrapherInfo;
};
//end:Grain

#endif /* !__Ilv_Grapher_Io_H */
