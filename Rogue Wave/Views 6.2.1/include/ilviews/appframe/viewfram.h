// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/viewfram.h
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
// Declaration of the IlvDvViewFrame class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Viewfram_H)
#define __Ilv_Appframe_Viewfram_H

#if !defined(__Ilv_Appframe_Viewcont_H)
#include <ilviews/appframe/viewcont.h>
#endif
#if !defined(__Ilv_Gadgets_Vframe_H)
#include <ilviews/gadgets/vframe.h>
#endif

// --------------------------------------------------------------------------
// IlvDvViewFrame class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvViewFrame
    : public IlvViewFrame, public IlvDvViewContainerInterface
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvViewFrame(IlvView* parent,
		   const char* title,
		   const IlvRect& size,
		   IlBoolean visible = IlTrue);
    ~IlvDvViewFrame();

    // ----------------------------------------------------------------------
    virtual IlBoolean	isContainerVisible() const;
    virtual void	updateTitle();
    virtual void	activate();
    virtual void	initializeContainer();

    // ----------------------------------------------------------------------
    virtual
    IlvGadgetContainer*	getClientContainer(IlBoolean create = IlFalse);
    virtual IlvDvDocViewInterface*	getActiveDocView() const;
    virtual IlvDvApplication*		getDvApplication() const;
    virtual void	setDvApplication(IlvDvApplication* app);
    virtual const char*	getContainerTitle() const;
    virtual IlUInt	getContainerNumber() const;
    virtual void	setContainerNumber(IlUInt n,
					   IlBoolean update = IlFalse);
    void		setFrameHandler(IlvDvFrameAndBarHandler* frameHandler);
    virtual
    IlvDvContainerHandler* getContainerHandler() const;

    IlvDvDeclareInterface();

protected:
    virtual void	removeView(IlvDvDocViewInterface*,
				   IlBoolean deleteIt);
    virtual void	doClose();

    IlvDvFrameAndBarHandler*	_frameHandler;
    // Title data
    IlUInt			_containerNumber;
    IlBoolean			_usingMask;
    IlvDvApplication*		_application;
    // View data
    IlvArray			_views;
    IlvDvDocViewInterface*	_activeView;

    virtual IlBoolean	isUsingMask() const;
    virtual void	setUsingMask(IlBoolean);
    virtual void	storeActiveDocView(IlvDvDocViewInterface* activeView);
    virtual IlvArray&	getViewsArray();
    void		toggleFrameBar();
    void		refreshToggleFrameBar(IlvDvActionDescriptor* desc);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(viewfram);
// --------------------------------------------------------------------------
#endif /* __Ilv_Appframe_Viewfram_H */
