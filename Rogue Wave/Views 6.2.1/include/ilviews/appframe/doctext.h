// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/doctext.h
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
// Declaration of the IlvDvTextDocument class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Doctext_H)
#define __Ilv_Appframe_Doctext_H

#if !defined(__Ilv_Appframe_Document_H)
#include <ilviews/appframe/document.h>
#endif

// --------------------------------------------------------------------------
// IlvDvTextDocument class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTextDocument : public IlvDvDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTextDocument();
    virtual ~IlvDvTextDocument();

    // ----------------------------------------------------------------------
    // Main methods
    inline const char*	getText() const { return _text; }
    void		setText(const IlvString& text,
				IlvDvDocViewInterface* view = 0);
    void		setEditable(IlBoolean editable);

    // ----------------------------------------------------------------------
    // IO
    virtual void	serialize(IlvDvStream& stream);

    // ----------------------------------------------------------------------
    // Statics
    IlvDvDeclareInterface();

    static IlSymbol*	_SetTextMethod;
    static IlSymbol*	_GetTextMethod;

protected:
    IlvString		_text;

    const char*		readText(IlvString& buf, IlvDvStream&);
    IlUInt		getNextLineOffset(const char* buf, IlUInt index) const;
};

// --------------------------------------------------------------------------
ILVDVEXPORTEDFUNCTION(unsigned long)
IlvDvRemoveDosEOL(char* buf, unsigned long len);

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(doctext);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Doctext_H */
