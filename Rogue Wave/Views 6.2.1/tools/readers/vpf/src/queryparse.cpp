// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/queryparse.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Definition of the query parser
// --------------------------------------------------------------------------

#include <ilviews/macros.h>

#include <vpf/query.h>
#include <vpf/string.h>
#include <vpf/table.h>
#include <vpf/error.h>
#include <vpf/parser.h>

#ifdef ILVSTD
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
ILVSTDUSE
#else
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif

struct VpfSyntaxDelimiter {
  const char*	delimiter;
  unsigned int	length;
  int		type;
  int		isNameEnd;
} delimiters[] = {
    { "&&",  2, AND,  0 },
    { "^^",  2, XOR,  0 },
    { "||",  2, OR,   0 },
    { "<>",  2, NEo,  1 },
    { "<=",  2, LEo,  1 },
    { ">=",  2, GEo,  1 },
    { "==",  2, EQo,  1 },
    { "<",   1, LTo,  1 },
    { ">",   1, GTo,  1 },
    { "(",   1, OPAR, 1 },
    { ")",   1, CPAR, 1 },
    { "*",   1, STAR, 1 }
};

struct ptrlist {
    char*		ptr;
    struct ptrlist*	next;
};

static const unsigned int nDelimiters =
	sizeof(delimiters) / sizeof(delimiters[0]);
static const char* parsetext = 0;
static VpfTable* parsetable = 0;
static VpfExpression* parseresult = 0;
static ptrlist* parseptrlist = 0;

extern int yyparse();

// --------------------------------------------------------------------------
static const char*
AddInList(char* ptr)
{
    ptrlist* elem = new ptrlist;
    if (elem) {
	elem->ptr = ptr;
	elem->next = parseptrlist;
	parseptrlist = elem;
    }
    return ptr;
}

// --------------------------------------------------------------------------
static void
DeleteList()
{
    ptrlist* elem = 0;

    while (parseptrlist) {
	if (parseptrlist->ptr)
	    delete [] parseptrlist->ptr;
	elem = parseptrlist;
	parseptrlist = elem->next;
	delete elem;
    }
}

// --------------------------------------------------------------------------
static int
GetLex(const char*& text, YYSTYPE* token)
{
    // Skip spaces
    while ((*text == ' ') || (*text == '\t'))
	text++;

    // Handle end of string case
    if (*text == '\0')
	return 0;

    // Try the predefined tokens
    for (VpfUInt i = 0; i < nDelimiters; i++) {
	if (!strncmp(text, delimiters[i].delimiter, delimiters[i].length)) {
	    text += delimiters[i].length;
	    return delimiters[i].type;
	}
    } /* for i */

    enum {
	ENDSTATE,
	STARTSTATE,
	STRINGSTATE,
	NAMESTATE,
	NUMSTATE,
	FLOATSTATE
    } state = STARTSTATE;

    enum {
	NONE,
	BUFFEROVERRUN,
	EOFINSTRING
    } error = NONE;

    int type = 0;
    char buffer[128];
    VpfUInt offset = 0;
    VpfUInt bufferSize = 127;

    while (state != ENDSTATE) {
	switch(state) {
	case STARTSTATE:
	    switch(*text) {
	    case '\0':
		state = ENDSTATE;
		break;
	    case '"':
		text++;
		state = STRINGSTATE;
		break;
	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		state = NUMSTATE;
		break;
	    default:
		state = NAMESTATE;
	    }
	    break;

	case STRINGSTATE:
	    switch(*text) {
	    case '\0':
		state = ENDSTATE;
		error = EOFINSTRING;
		type = 0;
		break;
	    case '\"':
		text++;
		state = ENDSTATE;
		type = STRING;
		buffer[offset] = '\0';
		token->textval = AddInList(VpfStrDup(buffer));
		break;
	    default:
		if (offset >= bufferSize) {
		    error = BUFFEROVERRUN;
		    state = ENDSTATE;
		} else
		    buffer[offset++] = *text++;
	    }
	    break;

	case NAMESTATE:
	    {
		for (unsigned int loop = 0; loop < nDelimiters; loop++) {
		    if (delimiters[loop].isNameEnd &&
			(*text == delimiters[loop].delimiter[0])) {
			text += delimiters[loop].length;
			state = ENDSTATE;
			type = NAME;
			buffer[offset] = '\0';
			token->textval = AddInList(VpfStrDup(buffer));
		    }
		}
	    }
	    if (state == NAMESTATE) {
		switch(*text) {
		case '\0':
		case ' ':
		case '\t':
		    state = ENDSTATE;
		    type = NAME;
		    buffer[offset] = '\0';
		    token->textval = AddInList(VpfStrDup(buffer));
		    break;
		default:
		    if (offset >= bufferSize) {
			error = BUFFEROVERRUN;
			state = ENDSTATE;
		    } else
			buffer[offset++] = *text++;
		}
	    }
	    break;

	case NUMSTATE:
	case FLOATSTATE:
	    switch(*text) {
	    case '.':
		state = FLOATSTATE;
	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		if (offset >= bufferSize) {
		    error = BUFFEROVERRUN;
		    state = ENDSTATE;
		} else
		    buffer[offset++] = *text++;
		break;

	    default:
		state = ENDSTATE;
		buffer[offset] = '\0';
		if (state == FLOATSTATE) {
		    type = FLOAT;
		    token->floatval = atof(buffer);
		} else {
		    type = INT;
		    token->intval = atoi(buffer);
		}
	    }
	    break;
	default:;
	}
    }   
    return type;
}

// --------------------------------------------------------------------------
int
yylex(YYSTYPE* token)
{
    if (!parsetext)
	return 0;
    return GetLex(parsetext, token);
}

// --------------------------------------------------------------------------
void
yyerror(const char*)
{
}

// --------------------------------------------------------------------------
VpfTable*
VpfQuery::Table()
{
    return parsetable;
}

// --------------------------------------------------------------------------
VpfInt
VpfQuery::FieldFromName(const char* name)
{
    VpfInt field = parsetable->getFieldPosition(name);
    VpfError* error = 0;
    static const char* Class = "VpfQueryParser::FieldFromName";
    if (field < 0) {
	error = new VpfError(Class);
	error->getStream() << "The field " << name << " does not exist "
			   << "in table " << parsetable->getPath();
	VpfErrorReporter::Add(error);
    }

    return field;
}

// --------------------------------------------------------------------------
void
VpfQuery::SetResult(VpfExpression* expr)
{
    parseresult = expr;
}

// --------------------------------------------------------------------------
VpfExpression*
VpfQuery::Parse(VpfTable* table, const char* filter)
{
    parsetext = filter;
    parsetable = table;
    parseresult = 0;
    parseptrlist = 0;

    if (!parsetext)
	return 0;
    if (!parsetable)
	return 0;

    if (yyparse()) {
	if (parseresult) {
	    delete parseresult;
	    parseresult = 0;
	}
    }

    DeleteList();
    return parseresult;
}
