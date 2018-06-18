// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/viewfile/include/viewerw.h
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
// --------------------------------------------------------------------------
// Declares the FileViewerWindow class, a window that displays a tree and a 
// a sheet separated by a splitter
// --------------------------------------------------------------------------

#include <ilviews/gadgets/tree.h>
#include <ilviews/gadgets/sheet.h>
#include <ilviews/gadgets/panecont.h>

// --------------------------------------------------------------------------
class FileViewerWindow : public IlvPanedContainer
{
public:
    FileViewerWindow(IlvAbstractView* parent,
			 const IlvRect&   dims,
			 IlBoolean        visible = IlTrue);
    FileViewerWindow(IlvDisplay*    d,
			 const char*    name,
			 const char*    title,
			 const IlvRect& dims,
			 IlBoolean      visible = IlTrue);

    IlvTreeGadget*           getDirectoryHierarchy() const;
    IlvSheet*                getFileList() const;

protected:
    void                     initLayout(const IlvRect& size);
};
