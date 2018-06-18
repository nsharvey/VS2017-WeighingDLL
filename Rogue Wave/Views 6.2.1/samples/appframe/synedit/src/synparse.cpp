// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/synparse.cpp
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
// IlogViews 4 generated source file
// File generated Thu Aug 26 15:58:41 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Definition of syntaxic parsing classes
// --------------------------------------------------------------------------
#include "synparse.h"
#include "synode.h"
#include <ilviews/appframe/clssinfo.h>

#if defined(IL_STD)
#include <string>
IL_STDUSE
#else  /* !IL_STD */
#include <string.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// TokenArray class
// --------------------------------------------------------------------------
class TokenArray
: public IlvArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    TokenArray() : IlvArray() {}
    ~TokenArray() { emptyTokens(); }

    // ----------------------------------------------------------------------
    const char* getToken(IlvUInt iToken)
    {	return (const char*)(char*)(*this)[iToken]; }
    void addToken(const char* token,
		  int len = -1);
    void emptyTokens();
};

// --------------------------------------------------------------------------
void
TokenArray::addToken(const char* token,
		     int len)
{
    if (len == -1)
	len = IL_CAST(int, strlen(token));
    char* newToken = new char[len + 1];
    ::memcpy(newToken, token, len);
    newToken[len] = '\0';
    add((IlAny)newToken);
}

// --------------------------------------------------------------------------
void
TokenArray::emptyTokens()
{
    for(IlUInt iToken = 0; iToken < getLength(); iToken++)
	delete[] (char*)(*this)[iToken];
    empty();
}

// --------------------------------------------------------------------------
// SynParser methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynParser::SynParser()
{
}

// --------------------------------------------------------------------------
SynParser::~SynParser()
{
}

// --------------------------------------------------------------------------
const char*
SynParser::skipWhites(const char* buf,
		      IlBoolean skipEOL) const
{
    for(;;) {
	switch(*buf) {
	case '\n':
	case '\r':
	    if (!skipEOL)
		return buf;
	case ' ':
	case '\t':
	    ++buf;
	    break;
	case '\0':
	    return buf;
	default:
	    return buf;
	}
    }
    return 0; // Never go there
}

// --------------------------------------------------------------------------
const char*
SynParser::goNextLine(const char* buf) const
{
    while(*buf) {
	if ((*buf == '\r') || (*buf == '\n')) {
	    ++buf;
	    if ((*buf == '\r') || (*buf == '\n'))
		++buf;
	    return buf;
	}
    }
    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::skipLiteralString(const char* buf) const
{
    if (*buf != '"')
	return buf;
    while((++buf != '\0') || (*buf != '"')) {
	if (*buf == '"')
	    break;
	if ((*buf == '\\') && (buf[1] == '"'))
	    buf+= 2;
    }
    if (*buf != '\0')
	return buf + 1;
    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::skipLiteralCharacter(const char* buf) const
{
    if (*buf != '\'')
	return buf;
    ++buf;
    if (*buf == '\\')
	buf+= 3;
    else
	buf+= 2;
    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::skipLineComment(const char* buf) const
{
    if ((*buf == '/') && (buf[1] == '/')) {
	// Comment line
	buf+= 2;
	while((*buf != '\r') && (*buf != '\n') && (*buf != '\0'))
	    ++buf;
	if ((*buf == '\r') || (*buf == '\n'))
	    return buf;
    }
    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::skipMultiLineComment(const char* buf) const
{
    if ((*buf != '/') || (buf[1] != '*'))
	return buf;
    buf+= 2;
    while((*buf != '\0') && ((*buf != '*') || (buf[1] != '/')))
	++buf;
    if (*buf == '*') {
	buf+= 2;
	return buf;
    }
    // Error, no enclosing "*/"
    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::skipToken(const char* buf,
		     TokenArray* tokens) const
{
    const char* delimiters = getDelimiters();
    int nDelimiters = IL_CAST(int, strlen(delimiters));
    const char* startBuf = buf;
    const char* aheadBuf = 0;
    while(*buf) {
	// Is white
	switch(*buf) {
	case ' ':
	case '\t':
	case '\r':
	case '\n':
	    if (buf != startBuf)
		goto TokenFound;
	    buf = startBuf = skipWhites(buf);
	}

	// Literal string caracter
	aheadBuf = skipLiteralString(buf);
	if (buf != aheadBuf)
	    goto TokenFound;

	// Line comment
	aheadBuf = skipLineComment(buf);
	if (buf != aheadBuf)
	    goto TokenFound;
	
	// Multi line comment
	aheadBuf = skipMultiLineComment(buf);
	if (buf != aheadBuf)
	    goto TokenFound;

	aheadBuf = skipLiteralCharacter(buf);
	if (buf != aheadBuf)
	    goto TokenFound;

	// Delimiters
	for(int i = 0; i < nDelimiters; i++) {
	    if (*buf == delimiters[i]) {
		aheadBuf = buf + 1;
		goto TokenFound;
	    }
	}
	++buf;
    }

    return buf;

TokenFound:
    if (startBuf == buf)
	buf = aheadBuf;
    if (tokens)
	tokens->addToken(startBuf, (int)(buf - startBuf));
    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::skipBlock(const char* buf,
		     TokenArray* tokens) const
{
    char enclosingChar;
    switch(*buf) {
    case '[': enclosingChar = ']'; break;
    case '{': enclosingChar = '}'; break;
    case '(': enclosingChar = ')'; break;
    default:
	return buf;
    }
    char blockChar = *buf;
    int nBlockDepth = 1;
    ++buf;
    do {
	const char* aheadBuf = skipToken(buf, tokens);
	if (aheadBuf == buf + 1) {
	    if (*buf == enclosingChar)
		--nBlockDepth;
	    else if (*buf == blockChar)
		++nBlockDepth;
	}
	buf = aheadBuf;
	if (!*buf) {
	    // Error, no enclosing character found
	    return buf;
	}
	buf = skipWhites(buf);
    }
    while(nBlockDepth);

    return buf;
}

// --------------------------------------------------------------------------
const char*
SynParser::goToStrings(const char* buf,
		       const char** strings,
		       int stringsCount,
		       TokenArray* tokens,
		       int& nFound,
		       IlBoolean skipEOL) const
{
    if (tokens)
	tokens->emptyTokens();
    int* lens = new int[stringsCount], i;
    for(i = 0; i < stringsCount; i++)
	lens[i] = IL_CAST(int, strlen(strings[i]));
    
    while(*buf) {
	buf = skipWhites(buf, skipEOL);
	if (!buf || !*buf) {
	    delete[] lens;
	    return 0;
	}
	for(int i = 0; i < stringsCount; i++) {
	    if (strncmp(buf, strings[i], lens[i]) == 0) {
		delete[] lens;
		nFound = i;
		return buf;
	    }
	}
	// Skip current word
	buf = skipToken(buf, tokens);
    }
    delete[] lens;
    return buf;
}

// --------------------------------------------------------------------------
void
SynParser::parseAll(const char* buf,
		    SynNodes& nodes) const
{
    SynNode* node;
    IlvTextPos currentPosition = 0;
    for (;;) {
	node = parse(buf, currentPosition);
	if (node)
	    nodes.addNode(node);
	else
	    break;
    }
}

// --------------------------------------------------------------------------
// SynCppParser methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynCppParser::SynCppParser(const char* buffer):
    SynParser(),
    _buffer(buffer)
{
}

// --------------------------------------------------------------------------
SynCppParser::~SynCppParser()
{
}

// --------------------------------------------------------------------------
IlvTextLocation
GetLocationFromOffset(const char* buf,
		      IlvTextPos offset)
{
    IlvTextLocation textLoca;
    if (offset == (IlvTextPos)-1)
	return textLoca;
    IlUShort column = 0, line = 0;
    while(offset && *buf) {
	if (*buf == '\n') {
	    ++line;
	    column = 0;
	} else
	    ++column;
	++buf;
	--offset;
    }
    textLoca.set(line, column);
    return textLoca;
}

// --------------------------------------------------------------------------
SynNode*
SynCppParser::parseClass(const char*& buf,
			 IlvTextPos currentPosition) const
{
    const char* startBuf = buf;
    // Skip class keyword
    buf = skipToken(buf);
    const char* Keywords[3];
    Keywords[0] = ";"; // Only class declaration
    Keywords[1] = "{"; // class definition, without inheritance
    Keywords[2] = ":"; // class definition, with inheritance
    int nFound = -1;
    TokenArray tokens;
    buf = goToStrings(buf, Keywords, 3, &tokens, nFound);
    if (!nFound)
	return 0; // Class declaration

    SynClassDecl* classDecl =
	    new SynClassDecl(tokens.getToken(tokens.getLength() - 1));
    if (nFound == 2) {
	// Class inheritance
	const char* Delims[2];
	Delims[0] = ",";
	Delims[1] = "{";
	do {
	    buf = goToStrings(buf, Delims, 2, &tokens, nFound);
	    if (tokens.getLength() > 1) {
	    }
	    if (nFound == 0)
		++buf;
	}
	while(nFound == 0); // While enumeration of ineritance
    }

    // Read body of class definition
    buf = skipBlock(buf);
    classDecl->setTextPositions(
	GetLocationFromOffset(_buffer, (IlvTextPos)currentPosition),
	GetLocationFromOffset(_buffer, 
		(IlvTextPos)currentPosition + (IlvTextPos)(buf - startBuf)));
    return classDecl;
}

// --------------------------------------------------------------------------
SynNode*
SynCppParser::parse(const char* buf,
		    IlvTextPos& currentPosition) const
{
#define CLASS_KEYWORD 0
    const char* Keywords = "class ";
    int nFound;
    TokenArray tokens;
    buf+= currentPosition;
    const char* startBuf = buf;
    while(buf && *buf) {
	buf = goToStrings(buf, &Keywords, 1, 0, nFound, IlvTrue);
	if (!buf)
	    return 0;
	switch(nFound) {
	case CLASS_KEYWORD:
	    {
		SynNode* node =
		    parseClass(buf, currentPosition +
					(IlvTextPos)(buf - startBuf));
		if (node) {
		    currentPosition+= (IlvTextPos)(buf - startBuf);
		    return node;
		}
	    }
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
const char*
SynCppParser::Delimiters = " \r\n\t,.;:=<>{}[]()/-*+|&!%";

const char*
SynCppParser::getDelimiters() const
{
    return Delimiters;
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterAbstractClass(SynParser, IlvDvSerializable);
IlvDvPreRegisterDynClass(SynCppParser, SynParser);

IL_BEGINMODULEINITDEF(syn_synparse)
    IlvDvPostRegisterAbstractClass(SynParser, IlvDvSerializable); \
    IlvDvPostRegisterDynClass(SynCppParser, SynParser); \
IL_ENDMODULEINITDEF(syn_synparse)

#if !defined(ILVBUILDLIBS)
static int syn_synparse_ini = (IL_MODINIT(syn_synparse)(), 0);
#endif
