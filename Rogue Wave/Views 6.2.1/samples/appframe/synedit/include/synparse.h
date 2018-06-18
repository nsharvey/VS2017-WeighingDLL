// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/synparse.h
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
// Declaration of the syntaxic parsing classes
// --------------------------------------------------------------------------
#if !defined(__Syn_Synparse_H)
#define __Syn_Synparse_H

#if !defined(__Ilv_Docview_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

#ifndef ILVSYN_TEXTPOS
#define ILVSYN_TEXTPOS
typedef unsigned long IlvTextPos;
#endif

class SynNode;
class TokenArray;
class SynNodes;
// --------------------------------------------------------------------------
// SynParser
// --------------------------------------------------------------------------

class SynParser
: public IlvDvSerializable
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynParser();
    virtual ~SynParser();

    // ----------------------------------------------------------------------
    void                parseAll(const char* buffer, SynNodes&) const;
    virtual SynNode* parse(const char* buffer,
			   IlvTextPos& currentPosition) const = 0;
    virtual const char* getDelimiters() const = 0;

    // ----------------------------------------------------------------------
    const char* goToStrings(const char* buf,
			    const char** strings,
			    int stringsCount,
			    TokenArray* tokens,
			    int& nFound,
			    IlBoolean skipEOL = IlTrue) const;
    const char* goNextLine(const char*) const;
    const char* skipWhites(const char*,
			   IlBoolean skipEOL = IlTrue) const;
    const char* skipLiteralCharacter(const char*) const;
    const char* skipLiteralString(const char*) const;
    const char* skipToken(const char*,
			  TokenArray* tokens = 0) const;
    const char* skipLineComment(const char*) const;
    const char* skipBlock(const char*,
			  TokenArray* tokens = 0) const;
    const char* skipMultiLineComment(const char*) const;
};

// --------------------------------------------------------------------------
// SynCppParser
// --------------------------------------------------------------------------
#define PUBLIC_DECL	0
#define PROTECTED_DECL	1
#define PRIVATE_DECL	2

class SynCppParser
: public SynParser
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynCppParser(const char* buffer = 0);
    ~SynCppParser();

    // ----------------------------------------------------------------------
    virtual SynNode* parse(const char* buf,
			   IlvTextPos& currentPosition) const;
    virtual const char* getDelimiters() const;

    virtual SynNode* parseClass(const char*& buf,
				IlvTextPos currentPosition) const;
    // ----------------------------------------------------------------------
    // Statics
    static const char* Delimiters;
protected:
    const char* _buffer;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(syn_synparse, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !__Syn_Synparse_H */
