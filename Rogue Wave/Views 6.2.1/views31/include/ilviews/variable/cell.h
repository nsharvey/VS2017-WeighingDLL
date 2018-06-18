// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/cell.h
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
// Definition of the IlvvCell class
// Defined in library ilvvar
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Cell_H
#define __Ilv31_Variable_Cell_H

#if !defined(__Ilv31_Variable_Actval_H)
#include <ilviews/variable/actval.h>
#endif
#if !defined(__Ilv31_Variable_All_H)
#include <ilviews/variable/all.h>
#endif
#if !defined(__Ilv31_Variable_Boolean_H)
#include <ilviews/variable/boolean.h>
#endif
#if !defined(__Ilv31_Variable_Ccell_H)
#include <ilviews/variable/ccell.h>
#endif
#if !defined(__Ilv31_Variable_Cexpr_H)
#include <ilviews/variable/cexpr.h>
#endif
#if !defined(__Ilv31_Variable_Cellxref_H)
#include <ilviews/variable/cellxref.h>
#endif

ILVV_LIST_DEF3(IlvvCellReferencers, IlvvCellReferencer*, IlvvCellReferencer*)

class IlvvExpr;

class ILV31VAREXPORTED IlvvCell
: public IlvvActiveValue, public virtual IlvvExprContext
{
    friend class IlvvCellRef;
public:
    IlvvCell(IlvvExpr* =0);
    virtual ~IlvvCell();
    // ____________________________________________________________
    void setValue(const IlvvFundamental& value);
    IlvvFundamental getValue();
    const IlvvExpr* formula() const { return _formula; }
    virtual void setFormula(IlvvExpr*);
    virtual IlvvOStream& print(IlvvOStream&) const;
    virtual IlvvOStream& printRef(IlvvOStream&) const;
    static IlvvCell* beingEvaluated(){return _being_evaluated;}
    // this one stacks the cell and calls scompute
    COMPUTATION compute();
    IlvvBoolean hasReferencers() const {return _referencers.link()?IlvvTrue:IlvvFalse;}
    void addReferencer(IlvvCellReferencer* r) { _referencers.cons(r); }
    void removeReferencer(IlvvCellReferencer* r) { _referencers.suppress(r); }
    void setContext(IlvvCellContext* c){_context=c;}
    IlvvBoolean removableSmoothly(){return (IlvvBoolean)!!_referencers.link();}
    void remove();
    IlvvCellContext* getContext(){return _context;}
    IlvvBoolean inserted() const {return _context?IlvvTrue:IlvvFalse;}
    IlvvPath* computePath();
    virtual const char* getName() const { return 0; }
    IlvvCellXRefs xrefs();
    // meant for instance for notify_set, to inspect the
    // value of the cell, knowing that it was just computed
    // does not involve the evaluation algorithm
    IlvvFundamental inspectValue() const;
private:
    void resetExprContext();
    // to prevent copying
    IlvvCell(const IlvvCell&);
    static IlvvCell* _being_evaluated;
    // this one is the compute of active values
    COMPUTATION accompute();
    IlvvFundamental evaluate();
    IlvvExpr* _formula;
    IlvvFundamental _value;
    IlvvCellReferencers _referencers;
    IlvvCellContext* _context;
};

IlvvOStream& operator<<(IlvvOStream&, const IlvvCell*);
IlvvOStream& operator<<(IlvvOStream&, const IlvvCell&);

#endif
