// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/piframe.h
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
// Declaration of IlvStPanelInstanceFrame class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Piframe_H
#define __IlvSt_Piframe_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

#ifndef __Ilv_Vframe_H
#include <ilviews/gadgets/vframe.h>
#endif

#ifndef __IlvSt_Stddrop_H
#include <ivstudio/stddrop.h>
#endif

// --------------------------------------------------------------------------
class IlvStPanelInstance;
class IlvStPanelInstanceFrame;
class IlvStudio;
class IlvStPanelInstanceObjectInteractor;

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAppObjectDragDropData;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAppPanelDragDropData;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStPanelInstanceFrame
    : public IlvViewFrame {
public:
    IlvStPanelInstanceFrame(IlvView* parent,
			    IlvStPanelInstance* pinst,
			    IlvStudio* editor);

    IlvStPanelInstance* getPanelInstance() const { return _pinstance; }
    IlvContainer*	getPanelInstanceContainer() const {
	return (getClient()
		   && getClient()->isSubtypeOf(IlvContainer::ClassInfo()))
	    ? (IlvContainer*)getClient()
	    : (IlvContainer*)0;
    }
    IlvStudio*		getEditor() const { return _editor; }
    virtual void	frameSelected();

protected:
    virtual void	initializePanelInstanceObjects(IlvStPanelInstance*);
    virtual IlBoolean	readPanelInstanceData(IlvStPanelInstance*);
    virtual void	moved(const IlvRect&, const IlvRect&);
    virtual void	resized(const IlvRect&, const IlvRect&);
    virtual IlBoolean	handleTitleBarEvent(IlvEvent& event);

private:
    void initPanelInstanceFrame();

public:
    ~IlvStPanelInstanceFrame();
    void		resetPanelInstanceContainer(IlvStPanelInstance*,
						    IlBoolean = IlTrue);
    virtual IlvContainer* createPanelInstanceContainer();
    virtual void	addSubPanelInstance(IlvStPanelInstance* child);
    IlvStPanelInstanceObjectInteractor* getPanelInstanceObjectInteractor()
	const { return _inter; }

    IlvStDdData*	getDragData() const { return _dragData; }
    void		setDragData(IlvStDdData* data) { _dragData = data; }
    IlUShort		getDragCount() const { return _dragCount; }
    void		setDragCount(IlUShort count) { _dragCount = count; }

protected:
    DeclareViewProperties();

    IlvStPanelInstance* _pinstance;
    IlvStudio*		_editor;
    IlvStDdData*	_dragData;
    IlUShort		_dragCount;
    IlvStPanelInstanceObjectInteractor* _inter;

}; // class IlvStPanelInstanceFrame

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStPanelInstanceObjectInteractor
    : public IlvViewObjectInteractor {
public:
    IlvStPanelInstanceObjectInteractor(IlvStPanelInstanceFrame* frame);
    IlvStPanelInstanceFrame* getFrame() const { return _frame; }
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic*     obj,
				   IlvEvent&       event,
                                   IlvContainer*   cont,
                                   IlvTransformer* t);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual const char* className() const;
protected:
    IlvStPanelInstanceFrame*	_frame;
}; // class IlvStPanelInstanceObjectInteractor

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStDddAppPanel
: public IlvStDdData {
public:
    IlvStDddAppPanel(IlvStPanelInstanceFrame* frame, const char* = 0);
    IlvStPanelInstanceFrame* getPanelInstanceFrame() const { return _frame; }
protected:
    IlvStPanelInstanceFrame* _frame;
}; // class IlvStDddAppPanel

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStDddAppObject
: public IlvStDddAppPanel {
public:
    IlvStDddAppObject(IlvStPanelInstanceFrame* frame,
		      IlvGraphic* obj);
    IlvGraphic* getObject() const { return _object; }
protected:
    IlvGraphic* _object;
}; // class IlvStDddAppObject

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTAPPLICLASS(st_piframe)
#endif /* IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
#endif /* __IlvSt_Piframe_H */
