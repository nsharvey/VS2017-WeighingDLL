// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/applix.h
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
// Declaration of IlvStApplicationExtension
// --------------------------------------------------------------------------
#ifndef __IlvSt_Applix_H
#define __IlvSt_Applix_H

#if !defined(__IlvSt_Studext_H)
#include <ivstudio/studext.h>
#endif

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmNewApplication;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmOpenApplication;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAppAddCurrentBuffer;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmNewPanelClass;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAppRemoveCurrentBuffer;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmRemovePanelClass;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmTestApplication;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmKillTestPanels;

class IlvStAppCode;
class IlvStStates;
////class IlvStViewsClass;
////class IlvStViewsLibrary;
class IlvStViewsInteractor;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStApplicationExtension
: public IlvStExtension {
public:
    IlvStApplicationExtension(IlvStudio*);
    ~IlvStApplicationExtension();

    virtual IlBoolean preInitialize();
    virtual IlBoolean afterReadingPropertyFiles();
    virtual IlBoolean initializeBuffers();
    virtual IlBoolean initializeCommandDescriptors();
    virtual IlBoolean initializePanels();
    virtual IlBoolean postInitialize();

    static IlvStApplicationExtension* Get(IlvStudio*);
    static IlvStApplicationExtension* Make(IlvStudio*);

    IlvStAppCode&   code()	{ return *_code; }
    IlvStStates&    states()	{ return *_states; }
    IlvStAppCode*   getCode()	{ return _code; }
    IlvStStates*    getStates()	{ return _states; }

    void addViewsInteractor(IlvStViewsInteractor*);
    void removeViewsInteractor(IlvStViewsInteractor*);
    IlvStViewsInteractor* getViewsInteractor(const char*) const;

protected:
    IlvStAppCode*   _code;
    IlvStStates*    _states;
    IlvStHash	    _viewsInteractors;
}; // class IlvStApplicationExtension

// --------------------------------------------------------------------------
#endif /* __IlvSt_Applix_H*/
