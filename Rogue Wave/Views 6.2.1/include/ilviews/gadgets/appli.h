// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/appli.h
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
// Declaration of the IlvApplication class
// Defined in library ilvadvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Appli_H
#define __Ilv_Gadgets_Appli_H

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

#if defined(ILVSTD)
#include <ctime>
#else
#include <time.h>
#endif

// --------------------------------------------------------------------------
class IlvStateManager;
class IlvGadgetContainer;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvApplication : public IlvValueInterface
{
public:
    IlvApplication(const char*	name,
		   const char*	displayName,
		   int		argc = 0,
		   char**	argv = 0);
    IlvApplication(IlvDisplay*	display,
		   const char*	name,
		   IlBoolean	owner = IlFalse);
    virtual ~IlvApplication();

    virtual void 	run();
    void		realize();
    inline const char*	getName() const { return _name; }
    virtual void	mainLoop();
    // --- Empty methods, to be redefined in subclasses ---
    virtual void	makePanels();
    virtual void 	beforeRunning();
    // --- Basic properties ---
    inline IlvDisplay*	getDisplay() const { return _display; }

    // --- Other accessors ---
    inline IlBoolean 	isRealized() const { return _realized; }
    inline IlBoolean	isDisplayOwner() const { return _displayOwner; }
    inline void		setDisplayOwner(IlBoolean own) { _displayOwner = own; }

    // --- Panel accessors ---
    IlvContainer*	getPanel(const char* name) const;
    void		addPanel(IlvContainer* panel);
    void		removePanel(IlvContainer*	panel,
				    IlBoolean		destroyIt = IlTrue);
    inline
    const IlArray&	getPanels() const { return _panels; }
    inline IlUInt	getNumberOfPanels() const
			{
			    return _panels.getLength();
			}
    inline
    IlvContainer*	getPanel(IlUInt ndx) const
			{
			    return (IlvContainer*)_panels[ndx];
			}
    void		showPanel(const char* name);
    void		hidePanel(const char* name);
    void		raisePanel(const char* name);
    IlBoolean		isViewable(const char* name) const;

    // --- States ---
    virtual
    IlvStateManager*	getRootState() const;
    virtual IlBoolean	setState(const char* stateName);

    // --- Utilities ---
    virtual
    IlvGadgetContainer*	makeExitPanel();
    void		hideWhenDestroyed(const char*, IlBoolean = IlTrue);
    void		exitWhenDestroyed(const char*, IlBoolean = IlTrue);
    inline IlBoolean	isUsingExitPanel() const { return _exitPanel; }
    inline void		setUsingExitPanel(IlBoolean val) { _exitPanel = val; }
    virtual IlvBitmap*	getBitmap(const char* name) const;
    static
    IlvApplication*	GetApplication(const IlvContainer* container);
    void		setApplication(IlvContainer* cont);

    // --- Value accessors ---
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    static IlSymbol*	_getPanelMethod;
    static IlSymbol*	_addPanelMethod;
    static IlSymbol* 	_removePanelMethod;
    static IlSymbol* 	_quitMethod;
    static IlSymbol* 	_setStateMethod;
    static IlSymbol* 	_rootStateValue;

    IlvDeclareClassInfo();

    static void		HidePanel(IlvView*, IlAny);
    static void		Exit(IlvView*, IlAny);

    virtual void	quit();

protected:
    char*		_name;
    IlvDisplay* 	_display;
    IlArray		_panels;
    IlBoolean		_displayOwner;
    IlBoolean		_realized;
    IlBoolean		_exitPanel;

private:
    void		init(IlvDisplay*, const char*);
    static IlSymbol*	GetApplicationSymbol();
    static IlSymbol*	_appliSymbol;

public:
    static IlBoolean	AttachContainer(IlvContainer*	parent,
				        IlvContainer*	child,
					const char*	ref);
    static IlBoolean	AttachNotebookPage(IlvContainer*	parent,
					   IlvContainer*	child,
					   const char*		ref,
					   IlInt		pndx,
					   IlBoolean		newPage,
					   const char*		label);
};

// --------------------------------------------------------------------------
inline void
IlvAppHidePanel(IlvView* v, IlAny a)
{
    IlvApplication::HidePanel(v, a);
}

// --------------------------------------------------------------------------
inline void
IlvAppExit(IlvView* v, IlAny a)
{
    IlvApplication::Exit(v, a);
}

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvPanelObjectReference : public IlvNamedProperty
{
public:
    IlvPanelObjectReference();
    virtual ~IlvPanelObjectReference();

    inline const char*	getString() const { return _string; }

protected:
    void		makeReferenceString();

    char*		_string;
    static
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
			  std::
#endif /* Borland C++ Builder 3.0 */
    time_t	_LastTime;
    static int		_Counter;

public:
    void		setString(const char* str);

    inline static
    IlSymbol*		GetSymbol() { return _Symbol; }
    static IlvGraphic*	GetObject(const IlvContainer*, const char* refstr);

    static IlvPanelObjectReference*	Get(const IlvGraphic*);
    static IlvPanelObjectReference*	Make(IlvGraphic*);

    static IlSymbol*	_Symbol;

    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvPanelObjectReference);
};

ILVADVGDTMODULEINIT(appli);
#endif /* !__Ilv_Gadgets_Appli_H */
