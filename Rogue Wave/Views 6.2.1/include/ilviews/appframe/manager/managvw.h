// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/manager/managvw.h
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
// Declaration of the IlvDvManagerView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Manager_Managvw_H)
#define __Ilv_Appframe_Manager_Managvw_H

#if !defined(__Ilv_Appframe_View_H)
#include <ilviews/appframe/view.h>
#endif

#if !defined(__Ilv_Appframe_Manager_Macros_H)
#include <ilviews/appframe/manager/macros.h>
#endif

class ILVDVCLASS IlvDvManagerDocument;
class IlvManager;
// --------------------------------------------------------------------------
// IlvDvManagerView class
// --------------------------------------------------------------------------
class ILVDVMGREXPORTED IlvDvManagerView : public IlvDvView
{
    IlvDvDeclareViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvManagerView(IlvGadgetContainer* parent);
    virtual ~IlvDvManagerView();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void		initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    IlvDvManagerDocument*	getManagerDocument() const;
    IlvManager*			getManager() const;

    // ----------------------------------------------------------------------
    // Printing
    virtual void		print(IlvPort* dst, const IlvDvPrintInfo&);
    virtual IlBoolean		isPrintable() const;
    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

protected:
    virtual void		pasteFromClipboard();

    IlvGraphic*			_graphicContainer;

    virtual IlBoolean		attachToHolder(IlvGraphicHolder* holder,
					       IlUInt nView,
					       IlvGraphic* oldGraphic = 0);
    virtual IlBoolean		attachGraphicToHolder(IlvGraphicHolder* holder,
						      IlvGraphic* graphic,
						      IlUInt nView,
						      IlvGraphic* oldObj = 0);
    virtual IlvGraphic*		createGraphicContainer(IlvGraphicHolder*,
						       IlvGraphic* refGraphic);
    virtual IlBoolean		showGraphicScrollBars() const;

    // ----------------------------------------------------------------------
    // Printing messages
    virtual IlAny		getDocViewTransformer();
    virtual void		computeDocViewBBox(IlAny);
    virtual void		dragDumpRect(IlAny);
};

// --------------------------------------------------------------------------
ILVDVMGRMODULEINIT(managvw);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Managvw_H */
