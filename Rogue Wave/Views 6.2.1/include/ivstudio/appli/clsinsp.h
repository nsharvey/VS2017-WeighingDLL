// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/clsinsp.h
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
// Declaration of generated classes inspectors
// --------------------------------------------------------------------------
#ifndef __IlvSt_Clsinsp_H
#define __IlvSt_Clsinsp_H

#ifndef __IlvSt_Panel_H
#include <ivstudio/panel.h>
#endif

class IlvStClassDescriptor;
class IlvNotebook;

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowApplicationInspector;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmPanelClassInspector;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowApplicationInspector;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowPanelClassInspector;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStClassInspector
: public IlvStPanelHandler {
public:
    IlvStClassInspector(IlvStudio*, const char* name, const IlvRect&);
    virtual void	connect();
    IlvNotebook*	getNotebook() const;
    virtual void	doReset();
    virtual void	doApply();
    void		clear();
    virtual IlBoolean	isValid() const;
    virtual IlBoolean	resetBeforeShowing() const;
    virtual IlvStClassDescriptor* getDescriptor() const = 0;
protected:
    void		makeUserCodePages();
    void		updateBackground();
}; // IlvStClassInspector

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStApplicationInspector
: public IlvStClassInspector {
public:
    IlvStApplicationInspector(IlvStudio* editor);
    virtual void	doReset();
    virtual void	doApply();
    void		clear();
    virtual IlvStClassDescriptor* getDescriptor() const;
}; // IlvStApplicationInspector

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStPanelClassInspector
: public IlvStClassInspector {
public:
    IlvStPanelClassInspector(IlvStudio* editor);
    virtual void	doReset();
    virtual void	doApply();
    void		clear();
    virtual IlvStClassDescriptor* getDescriptor() const;
};

// --------------------------------------------------------------------------
#endif /* __IlvSt_Clsinsp_H */