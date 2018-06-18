// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable.h
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
// Declaration of the IlvVariable class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_H
#define __Ilv31_Variable_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#include <ilviews/base/link.h>
#endif
#if !defined(__Ilv31_Ilvparse_H)
#include <ilviews/ilvparse.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv_Base_IlvAttr_H)
#include <ilviews/base/ilvattr.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariable
: public IlvAbstractVariable {
public:
    IlvVariable(const char* name, const char* formula = 0,
		IlvParser* parser = 0);
    // Must delete all representation
    virtual ~IlvVariable();
    // ____________________________________________________________
    IlvvNamedCell* getCell() const { return _cell; }
    IlvvFundamental getValue() const { return _cell->getValue(); }
    void setValue(const IlvvFundamental& v)
    {
	setFormula((const char*)0);
	_cell->setValue(v);
    }
    const char*     getName() const  { return _cell->getName(); }
    virtual void reevaluate();
    virtual const char* getFormula();
    virtual IlBoolean setFormula(const char* formula);
    virtual void setFormula(IlvvExpr*);
    IlvParser* getParser() const { return _parser; }
    virtual IlBoolean setParser(IlvParser* parser,
				IlBoolean force = IlFalse /*undocumented*/);
    virtual void setValue(char value);
    virtual void setValue(unsigned char value);
    virtual void setValue(short value);
    virtual void setValue(unsigned short value);
    virtual void setValue(int value);
    virtual void setValue(unsigned int value);
    virtual void setValue(long value);
    virtual void setValue(unsigned long value);
    virtual void setValue(float value);
    virtual void setValue(double value);
    virtual void setValue(const char* value);

    // representation list management
    virtual void notifyUpdated();
    virtual void notifyInCycle();
    virtual void notifyUndefined();
    virtual IlBoolean add(IlvAttribute*);
    virtual IlBoolean remove(IlvAttribute*);
    IlvAttribute** getAttributes(IlUInt& count) const;
    IlUInt getAttributesCount() const { return _attributes.length(); }
    void apply(IlvApplyAttribute, IlAny arg = 0);
protected:
    IlvvNamedCell* _cell;
    IlList        _attributes;
    char*          _formula;
    IlvParser*     _parser;
private:
    // to prevent from copy
    IlvVariable(const IlvVariable&);
};

#if !defined(__Ilv31_Variable_Cellfun_H)
#include <ilviews/variable/cellfun.h>
#endif
#define IlvRegisterFunction ILVV_REGISTER_NFUNC
typedef IlvvFunArgs IlvFunArgs;

typedef IlBoolean (* IlvFunctionParser)(const char*, IlvvFunArgs& args,
					IlvvFundamental& returnValue,
					IlAny userData);
IL_DEFINEFPTRTOANYCAST(IlvFunctionParser);
ILV31VAREXPORTEDFUNCTION(IlBoolean)
IlvAddFunctionParser(IlvFunctionParser,    IlAny userData = 0);
ILV31VAREXPORTEDFUNCTION(IlBoolean)
IlvRemoveFunctionParser(IlvFunctionParser, IlAny = 0);

ILV31VARMODULEINIT(ilvarith);
#endif /* __Ilv31_Variable_H */
