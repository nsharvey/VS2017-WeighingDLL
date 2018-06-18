// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/synode.cpp
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
// Definition of syntaxing parsing classes
// --------------------------------------------------------------------------
#include "synode.h"
#include <ilviews/appframe/clssinfo.h>

#if defined(IL_STD)
#include <fstream>
#include <string>
IL_STDUSE
#else  /* !IL_STD */
#include <fstream.h>
#include <string.h>
#endif /* IL_STD */

// -------------------------------------------------------------------------
// strnicmp for Unix and x86_.net2005_8.0 port or higher 
#if !defined(WINDOWS)
int
strnicmp(const char* s1,
	 const char* s2,
	 int len)
{
  IlString str1 = s1;
  return str1.caseCompare(s2, 0, len, 0, len);
}
#elif defined(_MSC_VER) && (_MSC_VER >= 1400) /* x86_.net2005_8.0 or higher */
# define strnicmp _strnicmp
#endif
// --------------------------------------------------------------------------
// stristr
static char const*
stristr(char const*	szName,
	char const*	szExp,
	int		nLenName = -1,
	int		nLenExp = -1)
{
    if (nLenName == -1)
	nLenName = IL_CAST(int, strlen(szName));
    if (nLenExp == -1)
	nLenExp = IL_CAST(int, strlen(szExp));
    if (nLenExp > nLenName) return 0;
    while (nLenName >= nLenExp) {
	if (strnicmp(szName, szExp, nLenExp) == 0)
	    return szName;
	++szName;
	--nLenName;
    }
    return 0;
}

// --------------------------------------------------------------------------
// FindFirstChar
inline int
FindFirstChar(char const* szName,
	      int c1,
	      int c2)
{
    char const* szResult = strchr(szName, c1);
    if (szResult) {
	char const* szTmp = strchr(szName, c2);
	if (szTmp){
	    return ((szTmp < szResult)
		    ? (int)(szTmp - szName)
		    : (int)(szResult - szName));
	} else
	    return (int)(szResult - szName);
    } else {
	szResult = strchr(szName, c2);
	return (szResult ? (int)(szResult - szName) : -1);
    }
}

// --------------------------------------------------------------------------
// MetaCompareName
int
MetaCompareName(const char* szName,
		const char* szExp)
{
    int nCmp;
    int nLenName = IL_CAST(int, strlen(szName));
    IlvBoolean bNeedOne;
    const char* szResult;
    if (*szExp == '*')
	if (szExp[1] == '\0')
	    return 0;
    while (*szName && *szExp) {
	if ((*szExp == '*') || (*szExp == '?')){
	    bNeedOne = IlvFalse;
	    while ((*szExp == '*') || (*szExp == '?')){
		    if (*szExp == '?')
			bNeedOne = IlvTrue;
		    szExp++;
	    }
	    if (*szExp == '\0')
		    return (bNeedOne? (nLenName ? 0 : -1) : 0);
	    nCmp = FindFirstChar(szExp, '*', '?');
	    if (nCmp == -1)
		    nCmp = IL_CAST(int, strlen(szExp));
	    if (nCmp > nLenName)
		    return ((strnicmp(szName, szExp, nLenName) >= 0) ? 1 : -1);
	    szResult = stristr(szName, szExp, nLenName, nCmp);
	    if (szResult){
		if (szResult == szName){
		    if (bNeedOne)
			return -1;
		    szName+= nCmp;
		    nLenName-= nCmp;
		} else {
		    szName = szResult + nCmp;
		    nLenName-= (int)(szResult - szName) + nCmp;
		}
	    } else {
		return strnicmp(szName, szExp, nCmp);
	    }
	} else {
	    nCmp = FindFirstChar(szExp, '*', '?');
	    if (nCmp == -1)
		nCmp = IL_CAST(int, strlen(szExp));
	    if (nCmp > nLenName)
		return ((strnicmp(szName, szExp, nLenName) >= 0)? 1 : -1);
	    switch(strnicmp(szName, szExp, nCmp)){
		case -1 : return -1;
		case 1  : return 1;
	    }
	    szName+= nCmp;
	    nLenName-= nCmp;
	}
	szExp+= nCmp;
    }
    if (*szName)
	return 1;
    if(*szExp)
	return -1;
    return 0;
}

// --------------------------------------------------------------------------
// SynNode methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynNode::SynNode(const char* name):
    _name(name)
{
}

// --------------------------------------------------------------------------
SynNode::~SynNode()
{
}

// --------------------------------------------------------------------------
SyntaxicNodeType
SynNode::getSyntaxicType() const
{
    return SynNone;
}

// --------------------------------------------------------------------------
void
SynNode::serialize(IlvDvStream& stream)
{
}

// --------------------------------------------------------------------------
// SynType methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynType::SynType(const char* type):
    SynNode(type)
{
}

// --------------------------------------------------------------------------
// SynVarDecl methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynVarDecl::SynVarDecl(const char* name):
    SynNode(name)
{
}

// --------------------------------------------------------------------------
SynVarDecl::~SynVarDecl()
{
    setType(0);
}

// --------------------------------------------------------------------------
// Basic properties
void
SynVarDecl::setType(SynType* type)
{
    if (_type)
	delete _type;
    _type = type;
}

// --------------------------------------------------------------------------
void
SynVarDecl::serialize(IlvDvStream&)
{
}

// --------------------------------------------------------------------------
// SynMethodDecl methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynMethodDecl::SynMethodDecl(const char* name):
    SynNode(name),
    _type(0),
    _isConst(IlFalse),
    _virtualMode(NO_VIRTUAL)
{
}

// --------------------------------------------------------------------------
SynMethodDecl::~SynMethodDecl()
{
    setType(0);
    razParameters();
}

// --------------------------------------------------------------------------
// Basic properties
void
SynMethodDecl::setType(SynType* type)
{
    if (_type)
	delete _type;
    _type = type;
}

// --------------------------------------------------------------------------
// Parameters
void
SynMethodDecl::addParameter(SynVarDecl* typeDecl)
{
    _parameters.add((IlvAny)typeDecl);
}

// --------------------------------------------------------------------------
void
SynMethodDecl::razParameters()
{
    for(IlvUInt iParameter = 0;
		iParameter < _parameters.getLength();
		iParameter++) {
	delete getParameter(iParameter);
    }
    _parameters.empty();
}

// --------------------------------------------------------------------------
void
SynMethodDecl::serialize(IlvDvStream&)
{
}

// --------------------------------------------------------------------------
// SynClassDecl methods
// --------------------------------------------------------------------------
// Constructor / destructor
SynClassDecl::SynClassDecl(const char* name):
    SynNode(name)
{
}

// --------------------------------------------------------------------------
SynClassDecl::~SynClassDecl()
{
    razInheritances();
    razMethods();
    razFields();
}

// --------------------------------------------------------------------------
// Inheritance

typedef struct InheritanceTag {
    InheritanceTag(const char* classname, int mode):
	_classname(classname), _mode(mode) {}

    IlvString _classname;
    int       _mode;
} InheritanceNode;

// --------------------------------------------------------------------------
void
SynClassDecl::addInheritance(const char* classname,
			     int         hinMode)
{
    _inheritances.add((IlAny)new InheritanceNode(classname, hinMode));
}

// --------------------------------------------------------------------------
const char*
SynClassDecl::getInheritance(IlUInt iHiner) const
{
    InheritanceNode* hinerNode = (InheritanceNode*)_inheritances[iHiner];
    return (hinerNode? (const char*)hinerNode->_classname : 0);
}

// --------------------------------------------------------------------------
int
SynClassDecl::getInheritanceMode(IlUInt iHiner) const
{
    InheritanceNode* hinerNode = (InheritanceNode*)_inheritances[iHiner];
    return (hinerNode? hinerNode->_mode : 0);
}

// --------------------------------------------------------------------------
void
SynClassDecl::razInheritances()
{
    for(IlUInt iHiner = 0; iHiner < _inheritances.getLength(); iHiner++) {
	InheritanceNode* hinerNode = (InheritanceNode*)_inheritances[iHiner];
	delete hinerNode;
    }
    _inheritances.empty();
}

// --------------------------------------------------------------------------
// Methods
void
SynClassDecl::addMethod(SynMethodDecl* method)
{
    _methods.add((IlAny)method);
}

// --------------------------------------------------------------------------
void
SynClassDecl::razMethods()
{
    for(IlUInt iMethod = 0; iMethod < _methods.getLength(); iMethod++)
	delete (SynMethodDecl*)_methods[iMethod];
    _methods.empty();
}

// --------------------------------------------------------------------------
// Fields
void
SynClassDecl::addField(SynVarDecl* field)
{
    _fields.add((IlvAny)field);
}

// --------------------------------------------------------------------------
void
SynClassDecl::razFields()
{
    for(IlUInt iField = 0; iField < _fields.getLength(); iField++)
	delete (SynVarDecl*)_fields[iField];
    _fields.empty();
}

// --------------------------------------------------------------------------
// Inheritance

void
SynClassDecl::serialize(IlvDvStream&)
{
}

// --------------------------------------------------------------------------
SyntaxicNodeType
SynClassDecl::getSyntaxicType() const
{
    return SynClassDefinition;
}

// --------------------------------------------------------------------------
// SynNodes methods
// --------------------------------------------------------------------------
// Constructor / destructor

SynNodes::SynNodes()
{
}

// --------------------------------------------------------------------------
SynNodes::~SynNodes()
{
    emptyNodes();
}

// --------------------------------------------------------------------------
void
SynNodes::emptyNodes()
{
    for(IlUInt i = 0; i < getLength(); i++)
	delete getNode(i);
    empty();
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterDynClass(SynNode, IlvDvSerializable);
IlvDvPreRegisterDynClass(SynType, SynNode);
IlvDvPreRegisterDynClass(SynVarDecl, SynNode);
IlvDvPreRegisterDynClass(SynMethodDecl, SynNode);
IlvDvPreRegisterDynClass(SynClassDecl, SynNode);

IL_BEGINMODULEINITDEF(syn_synode)
    IlvDvPostRegisterDynClass(SynNode, IlvDvSerializable); \
    IlvDvPostRegisterDynClass(SynType, SynNode); \
    IlvDvPostRegisterDynClass(SynVarDecl, SynNode); \
    IlvDvPostRegisterDynClass(SynMethodDecl, SynNode); \
    IlvDvPostRegisterDynClass(SynClassDecl, SynNode); \
IL_ENDMODULEINITDEF(syn_synode)

#if !defined(ILVBUILDLIBS)
static int syn_synode_ini = (IL_MODINIT(syn_synode)(), 0);
#endif
