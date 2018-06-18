// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/genselpg.h
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
// Declaration of generic panel selector
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Genselpg_H
#define __IlvSt_Inspectors_Genselpg_H

#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif

class IlvSelector;
class IlvToggle;
// --------------------------------------------------------------------------
// IlvStIPageSelector class
// --------------------------------------------------------------------------
typedef IlUShort (*FirstSelectedPageCallback)(IlAny);

class ILVINSPCLASS IlvStIPageSelector
    : public IlvStIEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPageSelector(const char* = 0);
    virtual ~IlvStIPageSelector();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean initialize();
    virtual IlBoolean apply() { return IlTrue; }
    virtual IlBoolean connectHolder(IlvGraphicHolder* holder);

    // ----------------------------------------------------------------------
    // Mode managment
    virtual IlBoolean	 isModified() const { return IlFalse; }

    // ----------------------------------------------------------------------
    // Pages managment
    void razPages();
    void showPage(IlUShort, IlBoolean = IlTrue, IlBoolean = IlTrue);

    // Hide previous selected page, before showing the page
    void selectPage(IlUShort);

    // list of strings terminated by 0
    void addToPage(IlUShort nPage, ...);

    // ----------------------------------------------------------------------
    void setFirstSelectedPageCallback(FirstSelectedPageCallback callback,
				      IlAny param)
	{
	    _firstSelectedPagecallback = callback;
	    _firstSelectedPageParam    = param;
	}

    // Callback public because of a bug of sparc compilers
    static void SelectorCallback(IlvGraphic*, IlAny);

protected:
    class GadgetRef
    {
    public:
	GadgetRef(const char* name)
	: _name(name), _object(0), _holder(0)
	{}
	void connectHolder(IlvGraphicHolder*);
	void show(IlBoolean = IlTrue, IlBoolean = IlTrue);

	// All gadget are first refered by their name
	// and, after connectHolder is called, are refered by their
	// gadget pointer
	IlString          _name;
	IlvGraphic*        _object;
	IlvGraphicHolder*  _holder; // Holder of gadget
    };

    // Array of list of strings becoming array of of list of gadgets
    IlArray              _pages;
    IlUShort             _previousSelection;

    IlArray* getPage(IlUInt, IlBoolean = IlFalse);
    void connectSubObjects(IlvGraphicHolder*);

    FirstSelectedPageCallback _firstSelectedPagecallback;
    IlAny                    _firstSelectedPageParam;
    virtual IlUShort getFirstSelectedPage() const;
    virtual IlUShort getCurrentSelectedPage() const { return 0; }

    virtual void onSelectionNotification(){}
    virtual void setGadgetSelected(IlUShort){}
};

// --------------------------------------------------------------------------
// IlvStIListPageSelector class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIListPageSelector
    : public IlvStIPageSelector
{
    IlvDeclareInspClassInfo();
public:
    IlvStIListPageSelector(const char* = 0);
    virtual ~IlvStIListPageSelector();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean connectHolder(IlvGraphicHolder*);
    virtual void       setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void       createEditorObjects(IlvDisplay*,
					   IlArray&,
					   IlArray&);

protected:
    IlvStIProxyListGadget* _list;
    virtual IlUShort getCurrentSelectedPage() const;
    static void SelectorListCallback(IlvGraphic*, IlAny);
    virtual void onSelectionNotification();
    virtual void setGadgetSelected(IlUShort);
};

// --------------------------------------------------------------------------
// IlvStISelectorPageSelector class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISelectorPageSelector
    : public IlvStIPageSelector
{
    IlvDeclareInspClassInfo();
public:
    IlvStISelectorPageSelector(const char* = 0);
    virtual ~IlvStISelectorPageSelector();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean connectHolder(IlvGraphicHolder*);
    virtual void       setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void       createEditorObjects(IlvDisplay*, IlArray&, IlArray&);

protected:
    IlvSelector*        _selector;
    IlvGraphicHolder*   _holder;

    virtual IlUShort getCurrentSelectedPage() const;
    IlUShort getGraphicPosition(IlvGraphic*) const;
    IlvGraphic* getGraphicAtPosition(IlUShort) const;

    virtual void onSelectionNotification();
    virtual void setGadgetSelected(IlUShort);
};

// --------------------------------------------------------------------------
// IlvStITogglePageSelector class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStITogglePageSelector
    : public IlvStIPageSelector
{
    IlvDeclareInspClassInfo();
public:
    IlvStITogglePageSelector(const char* = 0);
    virtual ~IlvStITogglePageSelector();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean connectHolder(IlvGraphicHolder*);
    virtual void       setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void       createEditorObjects(IlvDisplay*, IlArray&, IlArray&);

protected:
    IlvToggle*        _toggle;
    IlvGraphicHolder* _holder;

    virtual IlUShort getCurrentSelectedPage() const;
    virtual void onSelectionNotification();
    virtual void setGadgetSelected(IlUShort);
};

// --------------------------------------------------------------------------
// IlvStITogglePageSelector class
// --------------------------------------------------------------------------
class IlvStIPropertyAccessor;
typedef IlUShort (*IlvStIPropertySelectorCallback)(const IlvStIProperty*,
						   IlAny);

class ILVINSPCLASS IlvStIAccessorPageSelector
    : public IlvStIPageSelector
{
    IlvDeclareInspClassInfo();
public:
    IlvStIAccessorPageSelector(IlvStIPropertyAccessor* = 0, const char* = 0);
    virtual ~IlvStIAccessorPageSelector();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean connectHolder(IlvGraphicHolder*);

    // ----------------------------------------------------------------------
    // Accessor managment
    virtual IlvStIPropertyAccessor* getAccessor() const;
    virtual void	            setAccessor(IlvStIPropertyAccessor*);

    void setPropertySelectorCallback(IlvStIPropertySelectorCallback,
				     IlAny = 0);

protected:
    IlvStIPropertyAccessor*        _accessor;
    IlvStIPropertySelectorCallback _callback;
    IlAny                         _callbackParam;

    virtual IlUShort getCurrentSelectedPage() const;
    virtual IlUShort getIndexFromProperty(const IlvStIProperty*) const;
};

// --------------------------------------------------------------------------
// class IlvStIFilteringAccessor
// --------------------------------------------------------------------------
// Accessor to be used with IlvStIAccessorPageSelector editor
class ILVINSPCLASS IlvStIFilteringAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIFilteringAccessor(IlvStIPropertyAccessor* = 0,
			    IlUShort = 0,
			    UpdateMode = Inherited,
			    const char* = 0);
    virtual ~IlvStIFilteringAccessor();

    virtual IlvStIProperty* get();

    void setPropertySelectorCallback(IlvStIPropertySelectorCallback,
				     IlAny = 0);
protected:
    IlUShort _validIndex;
    IlvStIPropertySelectorCallback _callback;
    IlAny                       _callbackParam;

    virtual IlUShort getIndexFromProperty(const IlvStIProperty*) const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_genselpg)
#endif /* !__IlvSt_Inspectors_Genselpg_H */
