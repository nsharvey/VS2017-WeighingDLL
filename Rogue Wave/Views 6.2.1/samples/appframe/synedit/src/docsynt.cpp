// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/src/docsynt.cpp
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
#include <docsynt.h>
#include <ilviews/appframe/stream.h>
#include <ilviews/appframe/command.h>
#include <ilviews/appframe/doctempl.h>
#include <ilviews/appframe/viewgadg.h>
#include <synode.h>
#include <synparse.h>

#if defined(IL_STD)
#include <string>
#else /* ! IL_STD */
#include <string.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// TreeDocument methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(TreeDocument)
    Method1(SelectClass, selectClass, IlAny, ClassNode)
    Method1(SelectClassByName, selectClassByName, const char*, className)
    TypedMethod(GetText, getText, const char*)
    TypedMethod(GetClassCount, getClassCount, IlUInt)
    TypedMethod1(GetClassName, getClassName, IlUInt, index, const char*)
    TypedMethod1(GetClassNode, getClassNode, const char*, className, IlAny)
IlvDvEndInterface1(IlvDvDocument)

// --------------------------------------------------------------------------
// Constructor / destructor
TreeDocument::TreeDocument()
    : IlvDvDocument()
{
    _synNodes = new SynNodes;
}

// --------------------------------------------------------------------------
TreeDocument::~TreeDocument()
{
    delete _synNodes;
}

// --------------------------------------------------------------------------
// Overridables

IlBoolean
TreeDocument::initializeDocument(IlAny data)
{
    if (!IlvDvDocument::initializeDocument(data))
        return IlFalse;

    // This document has been created while executing command New
    // Add your initialization code here
    return IlTrue;
}

// --------------------------------------------------------------------------
void
TreeDocument::clean()
{
    IlvDvDocument::clean();
    // This method is called while destroying the document or
    // before the initializeDocument is called for a SDI document type
    // Free your data here
}

// --------------------------------------------------------------------------
void
TreeDocument::setText(const IlvString& text,
		      IlvDvDocViewInterface* docView)
{
    _text = text;
    applyValueDocViews(IlvDvTextView::_TextSymbol,
		       (const char*)_text,
		       docView);
    setModified(IlTrue);
}

// --------------------------------------------------------------------------
SynNode*
TreeDocument::getNodeAtLocation(const IlvTextLocation& location) const
{
    SynNodes* nodes = getSynNodes();
    for (IlUInt iNode = 0; iNode < nodes->getLength(); ++iNode) {
	SynNode* node = nodes->getNode(iNode);
	if (node->getBeginPosition().isBefore(location) &&
			location.isBefore(node->getEndPosition()))
	    return node;
    }
    return 0;
}

// --------------------------------------------------------------------------
void
TreeDocument::selectClass(IlAny node)
{
    notifyViews(IlvGetSymbol("SelectClass"), getCurrentCallerView(), node);
}

// --------------------------------------------------------------------------
void
TreeDocument::selectClassByName(const char* className)
{
    selectClass(getClassNode(className));
}

// --------------------------------------------------------------------------
IlUInt
TreeDocument::getClassCount() const
{
    return _synNodes->getLength();
}

// --------------------------------------------------------------------------
const char*
TreeDocument::getClassName(IlUInt index) const
{
    return ((SynNode*)(*_synNodes)[index])->getName();
}

// --------------------------------------------------------------------------
IlAny
TreeDocument::getClassNode(const char* className) const
{
    for (IlUInt iNode = 0; iNode < _synNodes->getLength(); ++iNode) {
	SynNode* node = (SynNode*)(*_synNodes)[iNode];
	IlvString name = node->getName();
	if (name.equals(className))
	    return (IlAny)node;
    }
    return 0;
}

// --------------------------------------------------------------------------
// IO

extern unsigned long
IlvDvRemoveDosEOL(char* buf,
		  unsigned long len);

void
TreeDocument::serialize(IlvDvStream& stream)
{
    if (stream.isSaving()) {
	int len = IL_CAST(int, _text.getLength() + 1);
	char* buf = new char[len];
	::memcpy(buf, (const char*)_text, len * sizeof(char));
	len = IlvDvRemoveDosEOL(buf, len);
	stream.writeBlock(buf, (len ? len - 1 : 0));
	delete[] buf;
    } else {
	_text = (const char*)"";
	static unsigned long const DefaultBufReadSize = 16000;
	char buf[DefaultBufReadSize + 1];
	unsigned long memRead;
	do {
	    memRead = stream.readBlock(buf, DefaultBufReadSize);
	    buf[memRead] = '\0';
	    IlvDvRemoveDosEOL(buf, memRead + 1);
	    _text+= buf;
	}
	while (memRead && (memRead == DefaultBufReadSize))
	    ;
	_synNodes->emptyNodes();
	SynCppParser parser((const char*)_text);
	parser.parseAll((const char*)_text, *_synNodes);
    }
}


// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterDynClass(TreeDocument, IlvDvDocument);

IL_BEGINMODULEINITDEF(docsynt)
    IlvDvPostRegisterDynClass(TreeDocument, IlvDvDocument);
IL_ENDMODULEINITDEF(docsynt)

#if !defined(ILVBUILDLIBS)
static int docsynt_ini = (IL_MODINIT(docsynt)(), 0);
#endif


