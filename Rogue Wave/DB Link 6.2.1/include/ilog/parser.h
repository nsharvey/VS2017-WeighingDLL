// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/parser.h
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
// Declaration of IlXmlParser, the XML parser
// --------------------------------------------------------------------------
#ifndef __Il_Parser_H
#define __Il_Parser_H

#include <ilog/xml.h>
#include <ilog/i18n.h>
#include <ilog/pool.h>

#if defined(IL_STD)
#include <cctype>
#include <iostream>
#include <cstring>
#else  /* !IL_STD */
#include <ctype.h>
#include <iostream.h>
#include <string.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
class IlXmlParser
{
    class Marker;
public:
    IlXmlParser(IL_STDPREF istream& s, IlXmlDocumentI* document);
    ~IlXmlParser();
    // ____________________________________________________________
    enum Error {
	XML_NO_ERROR,
	INVALID_DOCUMENT,
	EMPTY_DOCUMENT,
	EARLY_END_OF_DOCUMENT,
	END_OF_DOCUMENT_EXPECTED,
	END_OF_DOCUMENT_UNEXPECTED,
	INVALID_VERSION_INFO,
	INVALID_SD_DECLARATION,
	INVALID_EXTERNALID,
	INVALID_DECLARATION_END,
	INVALID_COMMENT_CHARS,
	RESERVED_PI_TARGET_NAME,
	INVALID_CDATA,
	INVALID_ENCODING_NAME,
	INVALID_ENCODING_DECLARATION,
	INVALID_TAG_NAME,
	UNEXPECTED_TAG_SYMBOL,
	END_TAG_EXPECTED,
	END_TAG_NOT_MATCHED,
	INVALID_TAG_END,
	EQUAL_SIGN_EXPECTED,
	INVALID_ATTRIBUTE_VALUE,
	INVALID_REFERENCE_DECLARATION,
	INVALID_CHARREF_DECLARATION,
	INVALID_DOCTYPE_NAME,
	UNRECOGNIZED_TAG
    };
    IlUTF16* getCurrent() const { return _current; }
private:
    void reset();
    IlBoolean	parseS();
    IlBoolean 	parseName(char*& name);
    IlBoolean 	parseAttValue(char*& value);
    IlBoolean 	parseCharData();
    IlBoolean 	parseComment();
    IlBoolean 	parsePI();
    // [18] CDSect ::= '<[CDATA[' data ']]>'
    IlBoolean 	parseCDSect();
    void 	parseProlog();
    // [23] XMLDecl ::= '<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'
    IlBoolean 	parseXMLDecl();
    // [24] VersionInfo ::= S 'version' Eq (' VersionNum ' | " VersionNum ")
    IlBoolean 	parseVersionInfo();
    IlBoolean 	parseEq();
    IlBoolean 	parseVersionNum();
    IlBoolean 	parseMisc();
    IlBoolean 	parseDoctypedecl();
    void 	parseSDDecl();
    void 	parseExternalID();
    IlBoolean 	parseElement(IlXmlElementI*& element);
    IlBoolean 	parseTagStart(IlXmlElementI*& node, IlBoolean& isEmpty);
    IlBoolean 	parseTagEnd(IlXmlElementI* node);
    IlBoolean 	parseAttribute(IlXmlElementI* node);
    IlBoolean 	parseContent();
    IlBoolean 	parseReference(IlXmlCharRefI*& reference);
    IlBoolean 	parseEncodingDecl();
    IlBoolean 	parseChar(int c);
    IlBoolean 	parseString(const char* string);
    IlBoolean 	parseIString(const char* string);
    IlUTF16 	nextChar();
    void	previousChar();
    IlBoolean 	parseAttribute(const char* name);
    IlBoolean 	fillBuffer(IL_STDPREF istream& stream);

    // Management of the elements
    void 	addNode(IlXmlNodeI*);
    void 	addText(Marker&);
    void 	addText(const char*);
    static IlUTF16 GetChar(IlXmlCharRefI*);

    IlXmlDocumentI*	_document;
    IlMemoryPoolBlock*	_bufferBlock;
    IlUTF16*		_buffer;
    IlUInt		_bufferSize;
    IlUTF16*		_current;
    IlXmlElementI*	_currentElement;

    class Marker
    {
    public:
	Marker(const IlXmlParser* parser, IlUTF16* marker)
	: _parser(parser),
	  _marker(marker)
	{
	}
	char* getBlock(const IlUTF16* marker, IlUInt skipAtEnd = 0) const;
	IlBoolean operator!=(const Marker& ref) const
	    { return (_marker != ref._marker); }
	IlUTF16* getCurrent() const { return _marker; }
	void reset(IlUTF16* marker) { _marker = marker; }
    private:
	const IlXmlParser* _parser;
	IlUTF16*	   _marker;
    };
    void 	goTo(const Marker& marker) { _current = marker.getCurrent(); }
};

#endif /* !__Il_Parser_H */
