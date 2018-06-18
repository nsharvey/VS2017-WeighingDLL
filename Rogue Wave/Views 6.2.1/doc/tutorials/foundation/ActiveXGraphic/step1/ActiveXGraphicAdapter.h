// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ActiveXGraphic/step1/ActiveXGraphicAdapter.h
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
#ifndef __ActiveXGraphicAdapter__header__
#define __ActiveXGraphicAdapter__header__

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgraph/rectscgr.h>
#include <ilviews/gadgets/fbrowser.h>

// --------------------------------------------------------------------------
class ActiveXGraphicAdapter
: public IlvGadgetContainer {
public:
    ActiveXGraphicAdapter(IlvDisplay* display,
                          const char* name, 
                          const char* title,
                          IlvRect*    size            = 0,
                          IlvBoolean  useAccelerators = IlvFalse,
                          IlvBoolean  visible         = IlvFalse,
                          IlvUInt     properties      = 0,
                          IlvSystemView transientFor  = 0)
    : IlvGadgetContainer(display,
			 name,
			 title,
			 size ? *size : IlvRect(0, 0, 523, 426),
			 properties,
			 useAccelerators,
			 visible,
			 transientFor),
      _selectedInteractorIndex(0),
      _interactors(0),
      _fileBrowser(display, getSystemView()),
      _objectInteractor(0)
    {
	    initialize();
    }
    ActiveXGraphicAdapter(IlvAbstractView* parent,
                          IlvRect* size = 0,
                          IlvBoolean useacc = IlvFalse,
                          IlvBoolean visible = IlvTrue)
    : IlvGadgetContainer(parent,
			 size ? *size : IlvRect(0, 0, 523, 426),
			 useacc,
			 visible),
      _selectedInteractorIndex(0),
      _interactors(0),
      _fileBrowser(parent->getDisplay(), getSystemView()),
      _objectInteractor(0)
    {
	initialize();
    }
    ~ActiveXGraphicAdapter();
    // ____________________________________________________________
    virtual void New(IlvGraphic*);
    virtual void Load(IlvGraphic*);
    virtual void Save(IlvGraphic*);
    virtual void SaveAs(IlvGraphic*);
    virtual void Quit(IlvGraphic*);
    virtual void SetNodeInteractor(IlvGraphic*);
    virtual void SetLinkInteractor(IlvGraphic*);
    virtual void SetSelectInteractor(IlvGraphic*);
    virtual void SetNoViewInteractor(IlvGraphic*);
    virtual void Help(IlvGraphic*);
    IlvSCGrapherRectangle* getGrapherRectangle() const {
	return (IlvSCGrapherRectangle*)getObject("GrapherRectangle");
    }
    IlvGrapher* getGrapher() const {
	return getGrapherRectangle()->getGrapher();
    }
    IlvView* getGrapherView() const {
	return getGrapherRectangle()->getView();
    }
    
protected:
    void initialize();

private:
    void save();
    void setInteractor(IlvGraphic* popup, IlvUShort newSelectedItem);
    void specificInitialization();

    IlvUShort			_interactorCount;
    IlvUShort			_selectedInteractorIndex;
    IlvManagerViewInteractor**	_interactors;
    IlvFileBrowser		_fileBrowser;
    IlvString			_loadedFile;
    IlvInteractor*		_objectInteractor;
};

#endif /* !__ActiveXGraphicAdapter__header__*/
