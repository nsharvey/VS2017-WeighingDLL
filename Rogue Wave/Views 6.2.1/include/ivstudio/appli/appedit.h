// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/appedit.h
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
// Declaration of the IlvStApplicationEditor and IlvStPanelInspector classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Appedit_H
#define __IlvSt_Appedit_H

#if      !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif

// --------------------------------------------------------------------------
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmInspectPanel;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmPanelInspector;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmApplicationTree;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowApplicationTree;

// --------------------------------------------------------------------------
class IlvNotebook;
class IlvStPanelInstance;
class IlvStPanelClass;
class IlvStudioApplication;

class IlvTreeGadget;
class IlvTreeGadgetItem;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStPanelInspector
: public IlvStPanelHandler {
public:
    IlvStPanelInspector(IlvStudio*);
    virtual IlBoolean	resetBeforeShowing() const;
    virtual void	doReset();
    void		clear();
    virtual void	doApply();
    void		applyInstance(IlvStPanelInstance*);
    void		test();
    IlvNotebook*	getNotebook() const { return _notebook; }

protected:
    void		resetTransientCombo();
    void		initTopPanelNotebook();
    void		initSubPanelNotebook();

    IlvNotebook*	_notebook;
    IlvNotebook*	_topPanelNotebook;
    IlvNotebook*	_subPanelNotebook;
    IlvStudioApplication* _testAppli;
    IlvStPanelInstance*	_lastTop;
    IlvArray		_deletedInstances;

public:
    void setTestApplication(IlvStudioApplication*);
    IlvStudioApplication* getTestApplication() const { return _testAppli; }
    void		resetFromSubPanel(IlvStPanelInstance*);
    void		resetFromTopPanel(IlvStPanelInstance*);
    void		applyToSubPanel(IlvStPanelInstance*);
    void		applyToTopPanel(IlvStPanelInstance*);
    void		resetHierarchyPage(IlvStPanelInstance*);
    void		applyHierarchyPage(IlvStPanelInstance*);
    IlvStPanelInstance* getSelectedPanelInstance() const;
    void		removePanelInstance(IlvStPanelInstance* = 0);
}; // class IlvStPanelInspector

// --------------------------------------------------------------------------

#endif /* __IlvSt_Appedit_H */

