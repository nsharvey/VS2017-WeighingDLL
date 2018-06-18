// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/insppnl.h
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
// Declaration of the IlvStInspectorPanel class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Insppnl_H
#define __IlvSt_Inspectors_Insppnl_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#  include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__IlvSt_Inspectors_Mainedt_H)
#  include <ivstudio/inspectors/mainedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif

class IlvStIInspectedObjectAccessor;
class IlvNotebook;
class IlvNotebookPage;
class IlvStInspector;
class IlvStInspectorAccessor;

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStInspectorPanel
    : public IlvDialog
{
public:
    IlvStInspectorPanel(IlvDisplay*			display,
			const char*			title,
			const char*			filename = 0,
			IlvSystemView			transientFor = 0,
			IlvStIAccessor::UpdateMode	mode =
			IlvStIAccessor::OnApply);
    virtual ~IlvStInspectorPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	init();
    virtual void	show();
    virtual void	apply();

    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic* obj);
    virtual void	initFrom(IlvGraphic* obj);

    // ----------------------------------------------------------------------
    // Load informations
    void		load();
    inline IlBoolean	isLoaded() const
	{ return (IlBoolean)(_list.getFirst() != 0); }

    IlvStIEditor*	link(const char* gadgetName,
			     const IlSymbol* valueName,
			     IlvStIEditor::NotificationMode mode =
			     IlvStIEditor::AsOwner);
    IlvStIEditor*	link(const char* gadgetName,
			     IlvStIPropertyAccessor* accessor,
			     IlvStIEditor::NotificationMode mode =
			     IlvStIEditor::AsOwner);

    void		addEditor(IlvStIEditor* editor);
    IlvStIEditor*	findEditor(const char* name);
    const IlvStIEditor*	findEditor(const char* name) const;
    IlBoolean		removeEditor(const char* name);
    IlBoolean		removeEditor(IlvStIEditor* editor);
    IlvStIMainEditor&	getMainEditor();
    const IlvStIMainEditor&	getMainEditor() const;

    IlvStIPropertyAccessor*	buildPropertyAccessor(const char* name);

    IlvStIInspectedObjectAccessor*	getInspectedGraphicAccessor() const;
    IlvStIAccessor*	findAccessor(const char* name);
    const IlvStIAccessor*	findAccessor(const char* name) const;
    IlvStIAccessor**	getInspectedObjectAccessors(IlUInt& count) const;
    void		addAccessor(IlvStIAccessor* acc);
    IlBoolean		removeAccessor(IlvStIAccessor* acc);

    IlvNotebookPage*	addPage(const char*	title,
				const char*	filename,
				IlUShort	idx = (IlUShort)-1,
				IlvBitmap*	bitmap = 0,
				IlBoolean	transparent = IlTrue);
    IlBoolean		removePage(IlUShort idx);

    IlvNotebook*	getGenericNotebook() const;

    // ----------------------------------------------------------------------
    IlvGraphic*		getInspectedObject();

    // Find a gadget throughout notebook, managers,...
    IlvGraphic*		getPanelObject(const char* name) const;

    IlBoolean		setGadgetVisible(const char*, IlBoolean = IlTrue);
    IlvStInspector*	getStInspector() const;

    // ----------------------------------------------------------------------
    // Inspector methods
    IlvStInspector*	getInspector() const;
    void		setInspector(IlvStInspector*);

    // ----------------------------------------------------------------------
    // Inspector accessor methods
    void		setInspectorAccessor(IlvStInspectorAccessor*);
    IlvStInspectorAccessor*	getInspectorAccessor() const;

    // ----------------------------------------------------------------------
    // Background managment
#if defined(WINDOWS)
    static void		setDefaultBackground(IlvColor*);
    static IlvColor*	getDefaultBackground();
#else  /* !WINDOWS */
    static void		setDefaultBackground(IlvColor* color)
	{ _background = color; }
    static IlvColor*	getDefaultBackground() { return _background; }
#endif /* !WINDOWS */

    // ----------------------------------------------------------------------
    // Utilities - kept for compabilities
    const char*		getTextFieldLabel(const char*) const;
    void		setTextFieldLabel(const char*, const char*);
    void		setTextFieldValue(const char*, IlInt);
    void		setTextFieldValue(const char*, IlFloat, const char*);
    void		setNumberFieldValue(const char*, IlFloat);
    void		setNumberFieldValue(const char*, IlInt);
    IlBoolean		getToggleState(const char*) const;
    void		setToggleState(const char*, IlBoolean);

    // ----------------------------------------------------------------------
    // Internal use
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);

    static IlSymbol*	_ObjectNameValue;
    static IlSymbol*	_ObjectCallbackValue;
    static IlSymbol*	_LayersChangedValue;
    static IlvPos	_DefaultNotebookXMargin;
    static IlvPos	_DefaultNotebookYMargin;
    static IlvPos	_DefaultButtonSpacing;
    static IlvPos	_DefaultButtonBottomMargin;
    static IlvPos	_DefaultButtonToLineMargin;
    static IlvPos	_DefaultLineToNotebookMargin;

protected:
    void		resizePanel();

    IlString				_filename;
    IlvStIMainEditor			_mainEditor;
    IlBoolean				_containerConnected;
    IlvGraphic*				_inspectedObject;
    IlvStIInspectedObjectAccessor*	_inspectedGraphicAccessor;
    IlvStInspector*			_inspector;
    static IlvColor*			_background;

    // ----------------------------------------------------------------------
    // Managing pages
    IlvNotebook*			_genericNotebook;

};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIInspectedObjectAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIInspectedObjectAccessor(IlvStInspectorAccessor*,
				  IlvStIErrorManager*,
				  const char* = 0,
				  IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIInspectedObjectAccessor();

    // ----------------------------------------------------------------------
    virtual IlvGraphic*		getInspectedGraphic() const;
    void		       setInspectorAccessor(IlvStInspectorAccessor*);
    IlvStInspectorAccessor*	getInspectorAccessor() const;

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);

    virtual IlvStIErrorManager*	getErrorManager() const
	{ return _errorManager; }

    IlvStInspectorPanel*	_inspectorPanel;
    IlvStIErrorManager*		_errorManager;
};

// --------------------------------------------------------------------------
// class IlvStINotebookPage
// --------------------------------------------------------------------------
#if !defined(__Ilv_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif
class ILVINSPCLASS IlvStINotebookPage
    : public IlvNotebookPage
{
public:
    IlvStINotebookPage(IlvNotebook*, const char*, IlvBitmap*,
		       IlBoolean, const char*);
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStInspectorPanelBuilder
{
public:
    virtual ~IlvStInspectorPanelBuilder(){}

    virtual
    IlvStInspectorPanel*	create(IlvDisplay* display,
				       const char* className,
				       IlvSystemView transientFor = 0,
				       IlvStIAccessor::UpdateMode
				         updateMode =
				       IlvStIAccessor::OnApply) = 0;
};

#if defined(IlvStDefineInspectorPanelBuilderExp)
#undef IlvStDefineInspectorPanelBuilderExp
#endif

#define IlvStDefineInspectorPanelBuilderExp(inspectorPanelClassName,      \
					    inspectorPanelBuilderClassName, \
					    exportMacro )                 \
class exportMacro inspectorPanelBuilderClassName:                         \
public IlvStInspectorPanelBuilder                                         \
{                                                                         \
public:                                                                   \
    virtual IlvStInspectorPanel* create(IlvDisplay* display,              \
				        const char* className,            \
					IlvSystemView transientFor = 0,   \
					IlvStIAccessor::UpdateMode mode = \
						IlvStIAccessor::OnApply)  \
    {                                                                     \
	return new inspectorPanelClassName(display, className,            \
					   0, transientFor, mode);        \
    }                                                                     \
}

#define IlvStDefineInspectorPanelBuilder(className, builderClassName) \
IlvStDefineInspectorPanelBuilderExp(className, builderClassName,      \
                                    ILVSTUDIOCLASS)

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_insppnl)
#endif /*  !__IlvSt_Inspectors_Insppnl_H */
