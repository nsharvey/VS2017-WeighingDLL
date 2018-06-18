// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/docsynt.h
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
// IlogViews 4 generated header file
// File generated Thu Aug 26 15:58:40 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the TreeDocument class
// --------------------------------------------------------------------------
#if !defined(docsynt__header__)
#define docsynt__header__

#if !defined(__Ilv_Appframe_Document_H)
#include <ilviews/appframe/document.h>
#endif /* !__Ilv_Appframe_Document_H */

class SynNode;
class SynNodes;
class ILVGDTEXPORTED IlvTextLocation;

// --------------------------------------------------------------------------
// TreeDocument class
// --------------------------------------------------------------------------

class TreeDocument
: public IlvDvDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    TreeDocument();
    virtual ~TreeDocument();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean initializeDocument(IlAny = 0);
    virtual void      clean();

    // ----------------------------------------------------------------------
    // Main methods
    const char* getText() const { return _text; }
    void        setText(const IlvString&,
			IlvDvDocViewInterface* = 0);

    SynNode* getNodeAtLocation(const IlvTextLocation&) const;

    SynNodes* getSynNodes() const { return _synNodes; }
    void selectClass(IlAny);
    void selectClassByName(const char* className);
    IlUInt getClassCount() const;
    const char* getClassName(IlUInt index) const;
    IlAny getClassNode(const char*) const;

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

    // ----------------------------------------------------------------------
    // Export TreeDocument fields and methods
    IlvDvDeclareInterface();

    static IlvSymbol* _TextSymbol;

protected:
    IlvString _text;
    SynNodes* _synNodes;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(docsynt, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !docsynt__header__ */
