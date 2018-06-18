// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/valuereq.h
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
// Declaration of IlvGraphicStateRequirement
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Valuesreq_H
#define __Ilv_States_Valuesreq_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_States_Reset_H)
#  include <ilviews/states/reset.h>
#endif

class ILVSTATESEXPORTED IlvGraphicStateRequirement;
class ILVVWSEXPORTED IlvContainer;
class ILVGDTEXPORTED IlvAbstractMenu;
class ILVGDTEXPORTED IlvMenuItem;

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvValueStateRequirement
: public IlvStateRequirement
{
public:
    IlvValueStateRequirement(IlAny,
			     const char*,
			     const char*);

    virtual void   applyValue(const IlvValue&) = 0;
    virtual void   storeValue(IlvValue&) = 0;
    virtual IlInt  getInt();
    virtual IlInt  isDifferentOf(IlvStateRequirement*);

    virtual void apply();
    virtual void restore();
    virtual void copyStoredFrom(IlvStateRequirement*);
    virtual void copyRequiredFrom(IlvStateRequirement*);
    virtual void storeObjectData();
    virtual IlAny getType() { return _required.getName(); }

    IlAny		getTarget()    const { return _target; }
    const IlvValue&	getRequired()  const { return _required; }
    IlvValue&		getRequired()        { return _required; }
    const IlvValue&	getStored()    const { return _stored; }
    IlvValue&		getStored()          { return _stored; }
protected:
    IlAny	    _target;
    IlvValue	    _required;
    IlvValue	    _stored;
}; // class IlvValueStateRequirement

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvGraphicStateRequirement
: public IlvValueStateRequirement
{
public:
    IlvGraphicStateRequirement(IlvValueInterface*,
			       const char*,
			       const char*);
    virtual void    applyValue(const IlvValue&);
    virtual void    storeValue(IlvValue&);
    IlvValueInterface* getObject() const { return (IlvValueInterface*)_target;}
    static IlvGraphicStateRequirement* Make(IlvValueInterface*,
					    const char*,
					    const char*);
}; // class IlvGraphicStateRequirement

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvContainerStateRequirement
: public IlvValueStateRequirement
{
public:
    IlvContainerStateRequirement(IlvContainer*,
				 const char*,
				 const char*);
    virtual void    applyValue(const IlvValue&);
    virtual void    storeValue(IlvValue&);
    IlvContainer*   getContainer() const { return (IlvContainer*)_target; }
    static IlvContainerStateRequirement* Make(IlvContainer*,
					      const char*,
					      const char*);
}; // class IlvContainerStateRequirement

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvMenuItemStateRequirement
: public IlvValueStateRequirement
{
public:
    IlvMenuItemStateRequirement(IlvMenuItem*,
				IlvAbstractMenu*,
				const char*,
				const char*);
    virtual void	applyValue(const IlvValue&);
    virtual void	storeValue(IlvValue&);
    IlvMenuItem*	getMenuItem() const { return (IlvMenuItem*)_target; }
    IlvAbstractMenu*	getMenu() const { return _menu; }
    static IlvMenuItemStateRequirement* Make(IlvMenuItem*,
					     IlvAbstractMenu*,
					     const char*,
					     const char*);
protected:
    IlvAbstractMenu*	_menu;
}; // class IlvMenuItemStateRequirement

#endif /* __Ilv_States_Valuesreq_H */
