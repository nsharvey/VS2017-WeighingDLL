// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/bookpnl.h
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
// Declaration of the IlvStINotebookPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Gadgets_Bookpnl_H)
#define __IlvSt_Gadgets_Bookpnl_H

#if !defined(__IlvSt_Gadgets_Inspscgt_H)
#  include <ivstudio/gadgets/inspscgt.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif

class IlvNotebook;
class IlvNotebookPage;
class IlvStINotebookPanel;

// --------------------------------------------------------------------------
// IlvStINotebookPageAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStINotebookPageAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStINotebookPageAccessor(IlvStIPropertyAccessor* = 0,
			       IlvStIAccessor::UpdateMode =
			                           IlvStIAccessor::Inherited,
			       const char* = 0,
			       IlvStIAccessor::BuildMode =
			                               IlvStIAccessor::None);
protected:
    IlvNotebookPage*	getPage() const;
};

// --------------------------------------------------------------------------
// IlvStIBitmapPageAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIBitmapPageAccessor
    : public IlvStINotebookPageAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIBitmapPageAccessor(IlvStIPropertyAccessor* = 0,
			     IlvStINotebookPanel* = 0,
			     IlvStIAccessor::UpdateMode = Inherited,
			     const char* = 0);
protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);

    IlvDisplay*			getDisplay() const;

    IlvStINotebookPanel*	_panel;
};

// --------------------------------------------------------------------------
// IlvStIBmpPageTranspAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIBmpPageTranspAccessor
    : public IlvStINotebookPageAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIBmpPageTranspAccessor(IlvStIPropertyAccessor* = 0,
			        IlvStIAccessor::UpdateMode = Inherited,
			        const char* = 0);
protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIPageTypeAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIPageTypeAccessor
    : public IlvStINotebookPageAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPageTypeAccessor(IlvStIPropertyAccessor* = 0,
			   IlvStINotebookPanel* = 0,
			   IlvStIAccessor::UpdateMode = Inherited,
			   const char* = 0);
protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);

    IlvStINotebookPanel*	_panel;
};

// --------------------------------------------------------------------------
// IlvStIBackPageAccessor class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIBackPageAccessor
    : public IlvStINotebookPageAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIBackPageAccessor(IlvStIPropertyAccessor*,
			   IlvStIPropertyAccessor*,
			   IlvStIAccessor::UpdateMode = Inherited,
			   const char* = 0);
protected:
    IlvStIPropertyAccessor*	_notebAccessor;
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStINotebookPageAccessor
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStINotebookPageListAccessor
    : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStINotebookPageListAccessor(IlvStIPropertyAccessor* = 0,
		                   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			           IlvStIAccessor::BuildMode =
							IlvStIAccessor::None,
			           const char* = 0);
    virtual ~IlvStINotebookPageListAccessor();

    // ----------------------------------------------------------------------
    // Main overridable
    IlvNotebook*		getNotebook()const;
    virtual IlvGadgetItem*     createGadgetItem(const IlvStIProperty*) const;
protected:
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createDefaultProperty()const;

    // calls property->copy() by default
    virtual IlvStIProperty*	copyProperty(const IlvStIProperty*);
    virtual void		addProperty(IlvStIProperty*, IlUInt);
    virtual void		deleteNewProperty(IlvStIProperty*);
    virtual void		deleteProperty(IlvStIProperty*, IlUInt);
    virtual void		replaceProperty(IlvStIProperty*,
						IlvStIProperty*, IlUInt);
    virtual void		moveProperty(IlvStIProperty*,
					     IlUInt, IlUInt);
    virtual IlvStIError*	check()const;
    virtual IlvStIEditor*	findFirstEditor()const;
    void			addPage(IlvStIProperty*, IlUInt);
};

// --------------------------------------------------------------------------
// class IlvStINotebookPanel
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStINotebookPanel
    : public IlvStIGadgetInspectorPanel
{
public:
    IlvStINotebookPanel(IlvDisplay*,
		        const char*,
		        const char* = 0,
		        IlvSystemView = 0,
		        IlvStIAccessor::UpdateMode =IlvStIAccessor::OnApply);
    ~IlvStINotebookPanel();

    // ----------------------------------------------------------------------
    // Overridable
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

    inline IlvNotebook*	getNotebookCopy()const { return _notebook; }
protected:
    IlvNotebook*	_notebook;

    void		initializeNotebookPanel();
};

IlvStDefineInspectorPanelBuilderExp(IlvStINotebookPanel,
				    IlvStINotebookPanelBuilder,
				    ILVSTGADGETCLASS);

IlvDECLAREINITSTGADGETCLASS(sti_bookpnl)
#endif /* !__IlvSt_Gadgets_Bookpnl_H */
