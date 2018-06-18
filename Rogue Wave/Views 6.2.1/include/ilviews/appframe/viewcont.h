// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/viewcont.h
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
// Declaration of the IlvDvViewContainerInterface class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Viewcont_H)
#define __Ilv_Appframe_Viewcont_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class IlvDvDocViewInterface;
class IlvDvDocument;
class IlvDvApplication;
class IlvDvContainerHandler;
class IlvDvOptions;
class IlvDvFrameAndBarHandler;
class IlvDvActionDescriptor;
class IlvGraphic;
class IlvGadgetContainer;
class IlvDvDocumentViewFactory;
// --------------------------------------------------------------------------
// IlvDvViewContainerInterface class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvViewContainerInterface : public IlvDvInterface
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvViewContainerInterface();
    virtual ~IlvDvViewContainerInterface();

    // ----------------------------------------------------------------------
    virtual IlBoolean	isContainerVisible() const = 0;

    virtual IlBoolean	readMask(const char* pathName);
    virtual IlBoolean	close(IlBoolean askForSaving = IlTrue);
    virtual IlBoolean	canClose();
    virtual void	activate();
    virtual void	initializeContainer();

    // ----------------------------------------------------------------------
    // Title management
    virtual const char*	getContainerTitle() const = 0;

    virtual void	updateTitle() = 0;

    virtual IlUInt	getContainerNumber() const = 0;

    virtual void	setContainerNumber(IlUInt n,
					   IlBoolean update = IlFalse) = 0;

    // ----------------------------------------------------------------------
    // DocViews management

    virtual
    IlvDvDocViewInterface* getActiveDocView() const;
    virtual void	setActiveDocView(IlvDvDocViewInterface* activeView,
					 IlBoolean notify = IlTrue);

    IlvDvDocViewInterface*  getDocView(IlUInt index) const;

    IlUInt                getDocViewsCount() const;
    IlvDvDocViewInterface** getDocViews(IlUInt&) const;
    IlvDvDocViewInterface*  getDocViewFromGraphic(IlvGraphic*) const;

    virtual IlBoolean	attachDocViews(IlvDvDocViewInterface** views,
				       IlUInt viewsCount);
    virtual void	removeDocViews(IlBoolean deleteViews = IlTrue,
				       IlvDvDocViewInterface** views = 0,
				       IlUInt viewsCount = (IlUInt)0);
    virtual void	initializeDocViews(IlBoolean makeVisible = IlTrue);

    // ----------------------------------------------------------------------
    // Document management
    IlvDvDocument*	getActiveDocument() const;

    // ----------------------------------------------------------------------
    // Basic properties
    virtual
    IlvGadgetContainer*	getClientContainer(IlBoolean create = IlFalse);

    virtual
    IlvDvApplication*  getDvApplication() const = 0;

    virtual
    void               setDvApplication(IlvDvApplication* app) = 0;

    virtual
    IlvDvContainerHandler* getContainerHandler() const = 0;

    // ----------------------------------------------------------------------
    // Accessors
    virtual const char* getObjectName(IlvString&,
				      IlvGraphic*,
				      IlUInt index) const;
    // ----------------------------------------------------------------------
    // Statics
    IlvDvDeclareInterface();
    static IlSymbol* _ViewFmtNameSymbol;

protected:
    virtual IlBoolean	isUsingMask() const = 0;

    virtual void	setUsingMask(IlBoolean useMask) = 0;

    virtual
    const IlvString&	makeTitle(IlvString& title) const;
    virtual void	removeView(IlvDvDocViewInterface*,
				   IlBoolean deleteIt);
    virtual void	doClose();
    virtual IlBoolean	addDocViews(const IlArray& views);

    virtual void	storeActiveDocView(IlvDvDocViewInterface* activeView) = 0;

    virtual IlvArray&	getViewsArray() = 0;
    virtual IlvDvDocViewInterface* const* getViews(IlUInt& count) const;

protected:
    // Interface methodes
    virtual IlUInt	getChildInterfacesCount() const;
    virtual
    IlvDvInterface*	getChildInterface(IlUInt nInterface) const;
};

// --------------------------------------------------------------------------
// IlvDvContainerHandler class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvContainerHandler
{
public:
    virtual ~IlvDvContainerHandler();
    virtual IlvDvViewContainerInterface* createContainer() = 0;

    virtual IlvDvDocViewInterface**
		createDocViews(IlvDvViewContainerInterface* parent,
			       IlUInt& count);

    virtual void	setDocViewFactory(IlvDvDocumentViewFactory* factory) = 0;

    virtual IlvDvDocumentViewFactory* getDocViewFactory() const = 0;

    virtual IlBoolean	isMaximizingFrames() const;
    virtual void	setMaximizingFrames(IlBoolean = IlTrue);
    virtual IlBoolean	allowMultipleContainers() const;
    virtual void	setAllowMultipleContainers(IlBoolean = IlTrue);
    virtual IlBoolean	closeDocumentOnClose() const;

    // ----------------------------------------------------------------------
    // IO
    virtual void	readOptions(IlvDvOptions* options) = 0;

    virtual void	updateOptions(IlvDvOptions* options) = 0;

protected:
    friend class ILVDVCLASS IlvDvDocTemplate;
    virtual IlBoolean	attachDocViews(IlvDvDocViewInterface** views,
				       IlUInt viewsCount,
				       IlvDvViewContainerInterface* container);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(viewcont);
// --------------------------------------------------------------------------
#endif /* __Ilv_Appframe_Viewcont_H */
