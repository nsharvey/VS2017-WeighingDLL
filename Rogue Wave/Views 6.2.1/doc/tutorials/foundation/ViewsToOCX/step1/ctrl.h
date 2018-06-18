// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ViewsToOCX/step1/ctrl.h
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
#if !defined(Ctrl_H)
#define Ctrl_H

#if !defined(__Ilv_Gadgets_Gadcont_H)
#  include <ilviews/gadgets/gadcont.h>
#endif

class IlvManagerRectangle;
class IlvManager;

// --------------------------------------------------------------------------
class Ctrl
    : public IlvGadgetContainer
{
public:
    // Creates a top view.
    Ctrl(IlvDisplay* display, const IlvRect& size, const char* filename = 0);
    // Creates a child view.
    Ctrl(IlvDisplay*	display,
	 IlvSystemView	parent,
	 const IlvRect& size,
	 const char*	filename = 0);
    // Creates from a system view.
    Ctrl(IlvDisplay* display, IlvSystemView parent,
	 const char* filename = 0);

    // Gets the IlvManagerRectangle object.
    IlvManagerRectangle* getManagerRectangle() const
	{ return _managerRectangle; }
    // Gets the view of the IlvManagerRectangle object.
    IlvView* getManagerView() const
	{ return _managerView; }
    // Gets the IlvManager of the IlvManagerRectangle object.
    IlvManager* getManager() const
	{ return _manager; }
private:
    // Initialization.
    void init(const char* filename);
    IlvManagerRectangle* _managerRectangle;
    IlvView*		 _managerView;
    IlvManager*		 _manager;
};
#endif /* !Ctrl_H */
