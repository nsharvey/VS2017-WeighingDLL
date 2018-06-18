// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/viewfile/step2/include/viewfile.h
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
// Declares the FileViewerApplication class, that is, the application class
// of the sample VIEWFILE
// --------------------------------------------------------------------------

#include <ilviews/gadgets/appli.h>
#include <viewer.h>
#include <viewerw.h>

// ------------------------------------------------------------------------
class FileViewerApplication
: public IlvApplication
{
public:
    FileViewerApplication(const char* name,
			  const char* displayName,
			  int argc,
			  char** argv);
    ~FileViewerApplication();
    // ______________________________________________________________________
    virtual void             makePanels();
    FileViewerWindow*        getMainWindow() const;
    virtual IlvContainer*    createMainWindow(const IlvRect& rect) const;
    virtual FileViewer*      createFileViewer(FileViewerWindow*) const;
    static FileViewer*       GetFileViewer(const FileViewerWindow*);
    static void              SetFileViewer(FileViewerWindow*, FileViewer*);

protected:
    void                     initMainWindow();
    void                     configureApplication();
};




