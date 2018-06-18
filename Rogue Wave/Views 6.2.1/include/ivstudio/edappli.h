// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/edappli.h
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
// Declaration of the IlvStApplication class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Appli_H
#define __IlvSt_Appli_H

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif
#if !defined(__IlvSt_Document_H)
#include <ivstudio/document.h>
#endif
#if !defined(__IlvSt_Stdesc_H)
#include <ivstudio/stdesc.h>
#endif

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDVAR(const char*) IlvNmAddPanel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmAfterSavingApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmApplicationModified;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeResettingApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeSavingApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelClassAdded;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelClassNameChanged;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelClassRemoved;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelClassSelectionChanged;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelInstanceSelectionChanged;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelInstanceChanged;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelInstanceAdded;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPanelInstanceRemoved;
extern ILVSTEXPORTEDVAR(const char*) IlvNmRemovePanel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSaveApplication;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSaveApplicationAs;

// --------------------------------------------------------------------------
class IlvContainer;
class IlvGadgetContainer;

class IlvStBuffer;
class IlvStError;
class IlvStApplication;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStApplication
: public IlvStAppDescriptor {
public:
    IlvStApplication(IlvStudio* editor, const char* name);
    virtual ~IlvStApplication();
    // ____________________________________________________________
    virtual void	reset();
    void		localPreset();
    // --- Basic ---
    IlvStudio*		getEditor() const { return _editor; }
    virtual const char* getDefaultBaseClass() const;
    virtual const char* getCreatorName() const;
    virtual void 	setModified(IlBoolean);
    // --- IO ---
    IlvStError*		open(const char* filename);
    IlvStError* 	save(const char* filename);
    void updatePanelDataRelativePaths(const IlPathName& oldref) const;
    void		setDefaultDirectories();
    // --- file extensions ---
    virtual const char* getDataFileExtension() const;
    virtual const char* getApplicationFileExtension() const;
    virtual const char* getHeaderFileExtension() const;
    virtual const char* getSourceFileExtension() const;
    virtual const char* getMakeFileExtension() const;
    // --- PanelClass ---
    IlvStPanelClass*	getPanelClass() const { return _pclass; }
    void		setPanelClass(IlvStPanelClass*, IlAny caller = 0);
    IlvStPanelClass*	getPanelClass(const IlvStBuffer*) const;
    IlvStPanelClass*	getPanelClass(const char* name) const
	{ return IlvStAppDescriptor::getPanelClass(name); }
    IlvStPanelClass*	getPanelClass(const IlvStPanelInstance* pinst) const
	{ return IlvStAppDescriptor::getPanelClass(pinst); }
    void		addPanelClass(IlvStPanelClass*, IlAny caller = 0);
    void		setPanelClassName(IlvStPanelClass*,
					  const char* name,
					  IlAny caller = 0);
    void		removePanelClass(IlvStPanelClass*, IlAny caller = 0);
    IlvStPanelClass*	makePanelClass(const IlvStBuffer*) const;
    // --- panel instances ---
    IlvStPanelInstance*	getPanelInstance() const { return _pinstance; }
    IlvStPanelInstance* getPanelInstance(const char* name,
					 IlBoolean subpanel = IlTrue) const
	{ return IlvStAppDescriptor::getPanelInstance(name, subpanel); }
    void		setPanelInstance(IlvStPanelInstance*,
					 IlAny caller = 0);
    void		addPanelInstance(IlvStPanelInstance*,
					 IlAny caller = 0);
    void		removePanelInstance(IlvStPanelInstance*,
					    IlAny caller = 0);
    const char*		makeInstanceName(const char*) const;
    void		sortTransientPanels();
    void		getPanelNames(IlvArray& names) const;
    // --- tests ---
    void		test();
    void		killTestPanels();
    void		showAllTestPanels();
    IlvContainer*	getTestPanel(const char* name) const;
    IlBoolean		isTesting() const { return _testing; }
    void		setTesting(IlBoolean val) { _testing = val; }
protected:
    IlvStudio*		_editor;
    IlvStPanelClass*	_pclass;
    IlvStPanelInstance*	_pinstance;
    IlBoolean		_testing;
private:
    void clean();

public:
    void		iRemovePanelInstance(IlvStPanelInstance* pinst,
					     IlvStPanelInstance*& curinst,
					     IlAny caller);
}; // class IlvStApplication

// --------------------------------------------------------------------------
void IlvStInitializeApplication(IlvStudio*);

// --------------------------------------------------------------------------
#ifndef ILVSTNO31COMPAT

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmNewApplication;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmOpenApplication;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAppAddCurrentBuffer;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmNewPanelClass;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAppRemoveCurrentBuffer;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmRemovePanelClass;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmTestApplication;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmKillTestPanels;

#endif

// --------------------------------------------------------------------------
#endif /* __IlvSt_Appli_H */
