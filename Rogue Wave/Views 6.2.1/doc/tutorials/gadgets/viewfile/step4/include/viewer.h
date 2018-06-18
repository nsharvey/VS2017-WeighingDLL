// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/viewfile/step4/include/viewer.h
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
// Declares the FileViewer class, a component that browses a hard drive 
// thanks to an IlvTreeGadget and an IlvSheet
// --------------------------------------------------------------------------

#include <ilviews/base/pathname.h>
#include <ilviews/gadgets/tree.h>
#include <ilviews/gadgets/sheet.h>

// --------------------------------------------------------------------------
class FileViewer
{
public:
    FileViewer(IlvTreeGadget* tree, IlvSheet* sheet);
    virtual ~FileViewer();
    // ____________________________________________________________
    IlvTreeGadget*           getTreeGadget() const { return _tree; }
    IlvSheet*                getSheet() const { return _sheet; }
    void                     init(IlvPathName& path);
    void                     updateSheet(IlvPathName& path);
    void                     updateTree(IlvPathName& path,
					IlvTreeGadgetItem* item = 0);
    virtual IlvBitmap*       getBitmap(const IlvPathName& file,
				       const IlvSymbol* state) const;
    IlvBitmap*               getBitmap(const char*) const;
    virtual IlvGadgetItem*   createFileItem(const IlvPathName& file,
					    const IlvGadgetItemHolder*) const;
    
protected:
    IlvTreeGadget*           _tree;
    IlvSheet*                _sheet;

    void                     initObjects();
    void                     initSheet();
    void                     initTree();
    void                     addFile(const IlvPathName& file);
    void                     fillTree(IlvPathName& path,
				      IlvTreeGadgetItem* parent);
};

