// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/gadattr.h
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
// Declaration of the main attribut classes for gadgets
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Gadattr_H
#define __Ilv31_Gadattr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Slider_H)
#include <ilviews/gadgets/slider.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Graphics_Selector_H)
#include <ilviews/graphics/selector.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvScrollBarValueAttribute
: public IlvGraphicAttribute {
public:
    IlvScrollBarValueAttribute(IlvContainer* container,
			       IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name)
    {}
    IlvScrollBarValueAttribute(IlvManager* manager,
			       IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name)
    {}
    // ____________________________________________________________
    IlvScrollBar* getScrollBar() const
	{ return (IlvScrollBar*)getGraphic(); }
    virtual void set(const IlvAttributeValue&, IlBoolean = IlTrue);
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvSliderValueAttribute
: public IlvGraphicAttribute {
public:
    IlvSliderValueAttribute(IlvContainer* container,
			   IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name)
    {}
    IlvSliderValueAttribute(IlvManager* manager,
			   IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name)
    {}
    // ____________________________________________________________
    IlvSlider* getSlider() const { return (IlvSlider*)getGraphic(); }
    virtual void set(const IlvAttributeValue&, IlBoolean = IlTrue);
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};


// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvTextFieldValueAttribute
: public IlvGraphicAttribute {
public:
    IlvTextFieldValueAttribute(IlvContainer* container,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvTextFieldValueAttribute(IlvManager* manager,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    IlvTextField* getTextField() const
	{ return (IlvTextField*)getGraphic(); }
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvSensitiveValueAttribute
: public IlvGraphicAttribute {
public:
    IlvSensitiveValueAttribute(IlvContainer* container,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvSensitiveValueAttribute(IlvManager* manager,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvToggleValueAttribute
: public IlvGraphicAttribute {
public:
    IlvToggleValueAttribute(IlvContainer* container,
			    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvToggleValueAttribute(IlvManager* manager,
			    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    IlvToggle* getToggle() const
	{ return (IlvToggle*)getGraphic(); }
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvOptionMenuValueAttribute
: public IlvGraphicAttribute {
public:
    IlvOptionMenuValueAttribute(IlvContainer* container,
				IlvGraphic* obj = 0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name)
    {}
    IlvOptionMenuValueAttribute(IlvManager* manager,
				IlvGraphic* obj = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name)
    {}
    // ____________________________________________________________
    IlvOptionMenu* getOptionMenu() const
	{ return (IlvOptionMenu*)getGraphic(); }
    virtual void set(const IlvAttributeValue&, IlBoolean redraw = IlTrue);
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvSelectorValueAttribute
: public IlvGraphicAttribute {
public:
    IlvSelectorValueAttribute(IlvContainer* container,
			      IlvGraphic* obj = 0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name)
    {}
    IlvSelectorValueAttribute(IlvManager* manager,
			      IlvGraphic* obj = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name)
    {}
    // ____________________________________________________________
    IlvSelector* getSelector() const
	{ return (IlvSelector*)getGraphic(); }
    virtual void set(const IlvAttributeValue&, IlBoolean redraw = IlTrue);
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};

ILV31VARMODULEINIT(gadattr);
#endif /* !__Ilv31__GadgetAttribsH */
