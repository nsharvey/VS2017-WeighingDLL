// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/intrface/varhold.h
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
// Declaration of the IlvVariableHolderInterface class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Itf_Varhold_H
#define __Ilv31_Itf_Varhold_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif

class IlvGraphic;
class IlvGraphicAttribute;
class IlvVariable;
class IlvParser;
// --------------------------------------------------------------------------
#define IlvVariableHolderInterface IlvVHItf
class ILV31VAREXPORTED IlvVariableHolderInterface
{
public:
    virtual IlvParser* getParser() const = 0;
    virtual IlvVariable* getVariable(const char*, IlBoolean = IlTrue);
    virtual IlBoolean removeVariable(IlvVariable*);
    virtual IlvGraphicAttribute* createAttribute(const char*, IlvGraphic*) = 0;
    IlvVariable* internalConnect(IlvGraphic* graphic,
				 const char* attClass,
				 const char* varName,
				 const char* holderClass);
    IlvVariable* connect(IlvGraphicAttribute*	graphic,
			 const char*		varName);
    virtual void reevaluate() = 0;
protected:
    void removeVariables(IlvGraphic*, IlBoolean);
};

#endif /* __Ilv31_Itf_Varhold_H */
