// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/strinter.h
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
// Declaration of predefined text-related interactors classes
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Strinter_H
#define __Ilv1X_Strinter_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Graphics_Lablist_H)
#include <ilviews/graphics/lablist.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif
// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvTextFieldInteractor
: public IlvManagerViewInteractor {
public:
    IlvTextFieldInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager,view)
	    {_window=0;_buffer[0]=0;}
    IlvTextFieldInteractor()
	: IlvManagerViewInteractor()
	    {_window=0;_buffer[0]=0;}
    ~IlvTextFieldInteractor() ;
    // ____________________________________________________________
    IlBoolean    handleEvent(IlvEvent& event);
    virtual void drawGhost();
    virtual void doIt(char* )=0;
    virtual void abort();

    virtual IlvBoolean accept(IlvPoint& p);
    void setLabel(const char* s);
protected:
    IlvSystemView _window;
    IlvPos        _x;
    IlvPos        _y;
    char         _buffer[256];
    void makeWindow(IlvPos,IlvPos);
};

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvMakeLabelInteractor
: public IlvTextFieldInteractor {
public:
    IlvMakeLabelInteractor(IlvManager* manager, IlvView* eview)
	:IlvTextFieldInteractor(manager,eview),_label(0){}
    IlvMakeLabelInteractor()
	:IlvTextFieldInteractor(),_label(0){}
    // ____________________________________________________________
    IlvBoolean accept(IlvPoint& p);
    virtual void doIt(char* );
protected:
    IlvLabel* _label;
};

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvMakeFilledLabelInteractor
: public IlvTextFieldInteractor {
public:
    IlvMakeFilledLabelInteractor(IlvManager* manager, IlvView* eview)
	:IlvTextFieldInteractor(manager,eview){}
    IlvMakeFilledLabelInteractor()
	:IlvTextFieldInteractor(){}
    // ____________________________________________________________
    IlvBoolean accept(IlvPoint& p);
    virtual void doIt(char* );
protected:
    IlvLabel* _label;
};

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvTextInteractor
: public IlvManagerViewInteractor {
public:
    IlvTextInteractor(IlvManager* manager, IlvView* mgrview)
	:IlvManagerViewInteractor(manager, mgrview)
	    {_window=0;}
    IlvTextInteractor()
	:IlvManagerViewInteractor()
	    {_window=0;}
    ~IlvTextInteractor() ;
    // ____________________________________________________________
    IlBoolean handleEvent(IlvEvent& event);
    void drawGhost() {}
    void abort();

    virtual IlvBoolean accept(IlvPoint& p);
    virtual void doIt(char* buffer)=0;
    virtual void setText(const char* text);
protected:
    IlvSystemView _window;
    IlvPoint      _p;
    void makeWindow(IlvPos,IlvPos);
    void getText();
};

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvMakeListLabelInteractor
: public IlvTextInteractor {
public:
    IlvMakeListLabelInteractor(IlvManager* manager, IlvView* eview)
	:IlvTextInteractor(manager,eview), _listlabel(0){}
    IlvMakeListLabelInteractor()
	:IlvTextInteractor(),_listlabel(0){}
    // ____________________________________________________________
    virtual void doIt(char* buffer);
protected:
    IlvBoolean accept(IlvPoint& p);
    IlvListLabel* _listlabel;
};

#endif /* !__Ilv1X_Strinter_H */
