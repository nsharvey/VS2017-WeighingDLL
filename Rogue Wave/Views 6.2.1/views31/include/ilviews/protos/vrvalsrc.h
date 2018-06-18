// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/protos/vrvalsrc.h
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
// Declaration of value sources subclasses that are using variables
// --------------------------------------------------------------------------

#ifndef __Ilv31_Protos_Vrvalsrc_H
#define __Ilv31_Protos_Vrvalsrc_H

#include <ilviews/protos/macros31.h>

#include <ilviews/protos/valuesrc.h>
#include <ilviews/variable.h>

// ---------------------------------------------------------------------------
// IlvVariableValueSource
// ---------------------------------------------------------------------------

class ILV31VRPEXPORTED IlvVariableValueSource : public IlvValueSource
{
 public:
    IlvVariableValueSource(const char* name = 0,
			   IlvParser* parser = 0,
			   IlBoolean owner = IlTrue);
    virtual ~IlvVariableValueSource();
    // ____________________________________________________________
    void setParser(IlvParser* parser, IlBoolean owner = IlTrue);
    IlvParser* getParser() { return(_parser); }

    IlvVariable* addVariable(const char* name,
			     const char* formula = 0);
    void removeVariable(const char* name);

    virtual IlvValue& queryValue(IlvValue& val) const;
    virtual IlBoolean changeValue(const IlvValue& val);

    virtual void getAccessors(const IlSymbol* const** accessors,
			      const IlvValueTypeClass* const** types,
			      IlUInt& count) const;

    DeclareValueSourceInfo();
    DeclareValueSourceIOConstructors(IlvVariableValueSource);
 protected:
    IlvParser* _parser;
    IlBoolean _owner;
};

// ---------------------------------------------------------------------------
// Static initialization of module.
// ---------------------------------------------------------------------------

#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINIT31VRPCLASS(vrvalsrc)
#endif /* IlvDECLAREINITCLASS */

#endif /* __Ilv31_Protos_Vrvalsrc_H */
