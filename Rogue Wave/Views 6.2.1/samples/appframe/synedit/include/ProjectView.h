// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/ProjectView.h
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
// Declaration of the ProjectView class
// --------------------------------------------------------------------------
#if !defined(ProjectView__header__)
#define ProjectView__header__

#if !defined(__Ilv_Appframe_Prjview_H)
#include <ilviews/appframe/project/prjview.h>
#endif /* !__Ilv_Appframe_Prjview_H */

class ProjectDocument;

// --------------------------------------------------------------------------
// ProjectView class
// --------------------------------------------------------------------------

class ProjectView
: public IlvDvProjectView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ProjectView(IlvDisplay*);
    virtual ~ProjectView();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    ProjectDocument* getProjectDocument() const;

    // ----------------------------------------------------------------------
    // Export ProjectView fields and methods
    IlvDvDeclareInterface();
};

// --------------------------------------------------------------------------
IL_MODULEINIT(ProjectView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !ProjectView__header__ */
