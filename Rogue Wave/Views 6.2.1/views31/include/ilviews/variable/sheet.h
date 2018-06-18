// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/sheet.h
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
// Definition of the IlvvSheet class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Sheet_H
#define __Ilv31_Variable_Sheet_H

#if !defined(__Ilv31_Variable_Stack_H)
#include <ilviews/variable/stack.h>
#endif
#if !defined(__Ilv31_Variable_List_H)
#include <ilviews/variable/list.h>
#endif
#if !defined(__Ilv31_Variable_Expr_H)
#include <ilviews/variable/expr.h>
#endif
#if !defined(__Ilv31_Variable_Name_H)
#include <ilviews/variable/name.h>
#endif
#if !defined(__Ilv31_Variable_Magic_H)
#include <ilviews/variable/magic.h>
#endif

extern "C"
{
   int Ilvvyylook(void);
#if  defined(_AIX)
   void Ilvvyyerror(char*);
   int Ilvvyyparse(void);
#else  /* !_AIX */
#if defined(__hpux)
   void Ilvvyyerror(char*);
#endif /* __hpux */
   int Ilvvyyinput(void);
#endif /* !_AIX */
#if !defined(IL_SUNCC2_1)
   int Ilvvyylex();
#endif
}
#if defined(_AIX)
extern int Ilvvyywinput(void);
#endif /* !_AIX */

ILVV_STACK_DEF2(IlvvExprStack,IlvvExpr*)
ILVV_STACK_DEF2(IlvvArgumentsStack,IlvvArguments*)
ILVV_STACK_DEF2(IlvvNameListStack,IlvvNameList*)

#if defined(__GNUC__)
// due to a bug quoted under
int Ilvvyyparse(void);
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvSheet
{
#if !defined(__GNUC__)
    // bug with g++
    friend int Ilvvyyparse();
    friend int Ilvvyylook();
#if defined(_AIX)
    friend int Ilvvyywinput();
#endif /* _AIX */
    friend int Ilvvyylex();
    friend void Ilvvyyerror(
#if !defined(IL_SUNCC2_1) && !defined(__hpux) && !defined(_AIX)
	const
#endif /* !IL_SUNC21 && !IL_HPC30 && !IL_RS6000 */
	char *
	);
#endif /* !__GNUC__ */
    friend int Ilvvyyinput();
public:
    // does not free the input string
    static IlvvExpr* parse(const char* formula);
    static IlvvSheet* getCurrentSheet();
    static void setCurrentSheet(IlvvSheet*);
    // just to accept or not the setCurrentSheet
    virtual IlvvBoolean isInserted() const;
    virtual void unknownFunction(const char*);
    virtual void divisionByZero();
    static char* newCopy(const char*);
    static char  translateChar(const char*);
    static char* translate(char*);
    // stack management functions to maintain a separate stack
    // used to avoid memory leaks in case of syntax error
    static void push(IlvvExpr *ep)      { expr_stack()  << ep; }
    static void push(IlvvArguments *ap) { args_stack()  << ap; }
    static void push(IlvvNameList *nl)  { namel_stack() << nl; }
    static void push(char *s){charp_stack()<<s;}
#if defined(__GNUC__)
    // to avoid the bug with g++ quoted above
public:
#else
protected:
#endif
    virtual void parsingError(const char* msg);
    virtual IlvvCell* findCell(const IlvvPath*);
    // If the returned value is 0, getUndefinedValue is automatically
    // called
    virtual IlvvCellRef* buildCellRef(IlvvPath*);
    virtual IlvvExpr* getUndefinedValue(IlvvPath*);
    virtual IlvvFunCall* buildFunCall(const char* f, IlvvArguments *args);
#if defined(__GNUC__)
    // to avoid the bug with g++ quoted above
public:
#else
private:
#endif
    static void setInput(const char *);
    // empties the stacks, frees the elements
    static void killStacks();
    // empties the expression stack, does not free the elements
    static void killExprStack();
    // idem
    static void killNameListStack();
    static void killCharPStack(IlvvBoolean withdel = IlFalse);
    static void killArgumentsStack();
    /**/
    static char getChar();
    static IlvvExpr *_tree;
    static char *_input;
    static char *_cursor;
    static IlvvSheet *_current_sheet;
    ILVV_MAGIC_DECL(IlvvExprStack,expr_stack);
    ILVV_MAGIC_DECL(IlvvArgumentsStack,args_stack);
    ILVV_MAGIC_DECL(IlvvNameListStack,namel_stack);
    ILVV_MAGIC_DECL(IlvvCharPStack,charp_stack);
};

#endif
