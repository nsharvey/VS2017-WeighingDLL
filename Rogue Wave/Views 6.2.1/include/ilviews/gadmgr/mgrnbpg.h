// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/mgrnbpg.h
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
// Declaration of the IlvManagerNotebookPage class
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadmgr_Mgrnbpg_H
#define __Ilv_Gadmgr_Mgrnbpg_H

#if !defined(__Ilv_Gadmgr_Macrosadv_H)
#include <ilviews/gadmgr/macrosadv.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTMGREXPORTED IlvManagerNotebookPage
    : public IlvNotebookPage
{
public:
    IlvManagerNotebookPage(IlvNotebook* notebook,
			   const char*  label,
			   IlvBitmap*   bitmap,
			   IlBoolean    transparent,
			   const char*  filename);
    virtual ~IlvManagerNotebookPage();
    // ____________________________________________________________
    virtual void drawContents(IlvPort* dst,
			      const IlvRect& size,
			      const IlvRegion* clip) const;
    virtual IlvView* createView(IlvAbstractView* parent,
				const IlvRect&   size);
    void             setManager(IlvManager*,
				IlBoolean owner);
    IlvManager*      getManager() const { return _manager;}
    virtual void     setFileName(const char*);
    virtual void     setViewBackground(IlvColor*);

    DeclareLazyNotebookPageInfo();
    DeclareNotebookPageIOConstructors(IlvManagerNotebookPage);
    DeclareGraphicAccessors();

private:
    IlvManager*    _manager;
    IlvTransformer _t;
    IlBoolean      _owner;
};

// --------------------------------------------------------------------------
ILVADVGDTMGRMODULEINIT(mgrnbpg);

#endif /* !__Ilv_Gadmgr_Mgrnbpg_H */
