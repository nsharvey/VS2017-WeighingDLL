// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/applylst.h
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
// Declaration of the IlvApplyListener class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Applylst_H
#define __Ilv_Manager_Applylst_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvApplyListener : public IlvNamedProperty
{
public:
    IlvApplyListener();

    virtual
    const IlSymbol*	getValueName() const;
    virtual void	beforeApply(IlvGraphic*, const IlvRect&, IlBoolean);
    virtual void	applied(IlvGraphic*    object,
				const IlvRect& oldBBox,
				const IlvRect& newBBox,
				IlBoolean      reDraw) = 0;
    void		set(IlvGraphic* object);
    static
    IlvApplyListener*	Get(const IlvGraphic* object);

    static
    IlvApplyListener*	Remove(IlvGraphic* object, IlvApplyListener* lst);

    static
    IlvApplyListener*	Remove(IlvGraphic* object);

    
    static IlUInt	GetCardinal(IlvGraphic* object);

    static IlSymbol*	GetSymbol();

    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvApplyListener);
};


// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvApplyListenerList : public IlvApplyListener
{
public:
    IlvApplyListenerList();

    virtual void	beforeApply(IlvGraphic*, const IlvRect&, IlBoolean);
    virtual void	applied(IlvGraphic*    object,
				const IlvRect& oldBBox,
				const IlvRect& newBBox,
				IlBoolean      reDraw);

    virtual IlBoolean	isPersistent() const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    inline IlUInt	getCardinal() const
			{
			    return _listeners.getProperties().getLength();
			}
    inline
    IlvNamedPropertySet& getPropertySet() { return _listeners; }

    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvApplyListenerList);

protected:
    IlvNamedPropertySet _listeners;
};

ILVMGRMODULEINIT(m0_applylst);

#endif /* !__Ilv_Manager_Applylst_H */
