// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/htmlload.h
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
// Declaration of the IlvATHtmlReader class (HTML file format reader)
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Htmlload_H
#define __Ilv_Annotext_Htmlload_H

#if !defined(__Ilv_Annotext_Html_H)
#  include <ilviews/annotext/html.h>
#endif

// --------------------------------------------------------------------------
// Sub-classes dealing with the file loading aspects of the html view demo
// --------------------------------------------------------------------------
class ViewerLinkInteractor
: public IlvATHtmlLinkInteractor {
public:
    virtual void	followLink(IlvATHtmlText*, const char*);
};

// --------------------------------------------------------------------------
class ViewerCommandInteractor
: public IlvATHtmlCommandInteractor {
public:
    virtual void	executeCommand(IlvATHtmlText*, const char*);
};

// --------------------------------------------------------------------------
#define ViewerHTMLReader ViewerHtmlReader
class ViewerHtmlReader
: public IlvATHtmlReader {
public:
    ViewerHTMLReader(IlvDisplay* display)
    : IlvATHtmlReader(display)
    {}

    virtual
    IlvATHtmlLinkInteractor*	createLinkInteractor() const
				{
				    return new ViewerLinkInteractor();
				}
    virtual
    IlvATHtmlCommandInteractor*	createCommandInteractor() const
				{
				    return new ViewerCommandInteractor();
				}
    virtual IlBoolean		parseTag(IlvATHtmlText*,
					 char*,
					 IlvATCursor*,
					 ILVSTDPREF istream&);
    virtual IlBoolean		linkLoad(IlvATHtmlText*, char*, IlBoolean);
};
#endif /* !__Ilv_Annotext_Htmlload_H */
