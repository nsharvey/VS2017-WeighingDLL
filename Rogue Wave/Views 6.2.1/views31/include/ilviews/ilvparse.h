// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/ilvparse.h
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
// Declaration of the IlvParser class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Ilvparse_H
#define __Ilv31_Ilvparse_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Variable_Cluster_H)
#include <ilviews/variable/cluster.h>
#endif
#if !defined(__Ilv31_Variable_Sheet_H)
#include <ilviews/variable/sheet.h>
#endif

class IlvVariable;
// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvParser
: public IlvvCluster
{
public:
    IlvParser(const char* name = 0);
    ~IlvParser();
    // ____________________________________________________________
    virtual IlvvCellRef* buildCellRef(IlvvPath*);
    virtual IlvvExpr*    getUndefinedValue(IlvvPath*);

    virtual IlBoolean addVariable(IlvVariable*);
    virtual IlBoolean removeVariable(IlvVariable*);
    virtual IlvVariable* getVariable(const char* varName,
				     IlBoolean createIt = IlTrue);
    virtual IlvVariable* createVariable(const char* varName);
    void    setCurrent() const;
    IlUInt getCardinal() const;
    const char* const * getVariableNames(IlUInt& count);
    IlvVariable** getVariables(IlUInt& count);
    void reevaluate();
    IlBoolean addSubParser(IlvParser*);
    IlBoolean removeSubParser(IlvParser*);
#if defined(__GNUC__)
private:
    IlvParser(const IlvParser&);
#endif
};

extern "C" {
ILV31VAREXPORTEDFUNCTION(IlvParser*) IlvCurrentParser();
ILV31VAREXPORTEDFUNCTION(void)       IlvReevaluate();
}

#endif /* !__Ilv31_Ilvparse_H */
