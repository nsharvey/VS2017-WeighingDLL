// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/ProjectDocument.h
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
// File generated Thu Aug 26 15:58:41 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the ProjectDocument class
// --------------------------------------------------------------------------
#if !defined(ProjectDocument__header__)
#define ProjectDocument__header__

#if !defined(__Ilv_Appframe_Prjdoc_H)
#include <ilviews/appframe/project/prjdoc.h>
#endif /* !__Ilv_Appframe_Prjdoc_H */

// --------------------------------------------------------------------------
// ProjectDocument class
// --------------------------------------------------------------------------

class ProjectDocument
: public IlvDvProjectDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ProjectDocument();
    virtual ~ProjectDocument();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean initializeDocument(IlAny = 0);
    virtual void       clean();

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

    // ----------------------------------------------------------------------
    // Export ProjectDocument fields and methods
    IlvDvDeclareInterface();
};

// --------------------------------------------------------------------------
IL_MODULEINIT(ProjectDocument, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !ProjectDocument__header__ */
