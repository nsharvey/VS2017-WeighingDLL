// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/expr.h
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
// Declaration of the IlvExpression class.
// This an internal class used to evaluate expressions
// in accessor parameters.
// --------------------------------------------------------------------------

#ifndef __Ilv_Protos_Expr_H
#define __Ilv_Protos_Expr_H

#include <ilviews/base/value.h>
#include <ilviews/intrface/value.h>

class IlvExpressionNode;

class IlvExpression {
public:
    IlvExpression(const char* s);
    ~IlvExpression();

    IlBoolean		parse();

    IlBoolean		eval(const IlvValueInterface* obj,
			     IlvValue& result,
			     const IlvValue* arg = 0);

    char*		print(char* buf);

    static IlBoolean	IsAnExpression(const char* s);

protected:
    const char*		_s;
    int			_end;
    IlvExpressionNode*	_tree;

private:
    IlBoolean		parse(int begin, IlvExpressionNode*& result);
    IlBoolean		binary1(int begin, IlvExpressionNode*& result);
    IlBoolean		binary2(int begin, IlvExpressionNode*& result);
    IlBoolean		binary3(int begin, IlvExpressionNode*& result);
    IlBoolean		binary4(int begin, IlvExpressionNode*& result);
    IlBoolean		binary5(int begin, IlvExpressionNode*& result);
    IlBoolean		unary(int begin, IlvExpressionNode*& result);
    IlBoolean		term(int begin, IlvExpressionNode*& result);

    inline int		next(int i) { return(_s[i]); }

    int			skipBlanks(int i);
};

#endif /* __Ilv_Protos_Expr_H */
