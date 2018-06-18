// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/objprop.h
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
// Declaration of the IlvObjectProperty class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Objprop_H
#define __Ilv_Graphics_Objprop_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#define IlvObjectVisible		((IlUInt)(1UL <<  0))
#define IlvObjectSelectable		((IlUInt)(1UL <<  1))
#define IlvObjectMoveable		((IlUInt)(1UL <<  2))
#define IlvObjectResizable		((IlUInt)(1UL <<  3))
#define IlvObjectIsMarked		((IlUInt)(1UL <<  4))
#define IlvObjectEditable		((IlUInt)(1UL << 28))
#define IlvObjectHasApplyMarker		((IlUInt)(1UL << 29))
#define IlvObjectHasApplyListener	((IlUInt)(1UL << 30))
#define IlvObjectHasNoHolder		((IlUInt)(1UL << 31))
#define IlvObjectAllProperties		((IlUInt)0x00FF)

class ILVVWSEXPORTED IlvGraphicHolder;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvObjectProperty
{
public:
    IlvObjectProperty(IlvGraphicHolder* holder = 0)
    : _properties(IlvObjectVisible  | IlvObjectSelectable |
		  IlvObjectMoveable | IlvObjectResizable  | IlvObjectEditable),
      _holder(holder) {}
    virtual ~IlvObjectProperty();
    // ____________________________________________________________
    inline IlvGraphicHolder*	getHolder() { return _holder; }
    inline IlvGraphicHolder*	getRealHolder()
				{
				    return hasDummyHolder() ? 0 : _holder;
				}
    inline void		setHolder(IlvGraphicHolder* holder)
			{
			    _holder = holder;
			}
    inline IlBoolean	isVisible() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectVisible) != 0);
			}
    inline void		setVisible(IlBoolean v)
			{
			    if (v)
				_properties  |=  IlvObjectVisible;
			    else _properties &= ~IlvObjectVisible;
			}
    inline IlBoolean	isSelectable() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectSelectable) != 0);
			}
    inline void		setSelectable(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectSelectable;
			    else _properties &= ~IlvObjectSelectable;
			}
    inline IlBoolean	isMoveable() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectMoveable) != 0);
			}
    inline void		setMoveable(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectMoveable;
			    else _properties &= ~IlvObjectMoveable;
			}
    inline IlBoolean	isResizeable() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectResizable) != 0);
			}
    inline void		setResizeable(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectResizable;
			    else _properties &= ~IlvObjectResizable;
			}
    inline IlBoolean	isEditable() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectEditable) != 0);
			}
    inline void		setEditable(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectEditable;
			    else _properties &= ~IlvObjectEditable;
			}

    inline IlBoolean	isMarked() const
			{
			    return (IlBoolean)
				((_properties & IlvObjectIsMarked) != 0);
			}
    inline void		setMarked(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectIsMarked;
			    else _properties &= ~IlvObjectIsMarked;
			}
    inline void		setDummyHolder()
			{
			    _properties |= IlvObjectHasNoHolder;
			}
    inline IlBoolean	hasDummyHolder() const
			{
			    return (_properties & IlvObjectHasNoHolder)
				? IlTrue
				: IlFalse;
			}
    inline void		setApplyMarker(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectHasApplyMarker;
			    else _properties &= ~IlvObjectHasApplyMarker;
			}
    inline IlBoolean	hasApplyMarker() const
			{
			    return (_properties & IlvObjectHasApplyMarker)
				? IlTrue
				: IlFalse;
			}
    inline void		setApplyListener(IlBoolean s)
			{
			    if (s)
				_properties  |=  IlvObjectHasApplyListener;
			    else _properties &= ~IlvObjectHasApplyListener;
			}
    inline IlBoolean	hasApplyListener() const
			{
			    return (_properties & IlvObjectHasApplyListener)
				? IlTrue
				: IlFalse;
			}

protected:
    IlUInt		_properties;
    IlvGraphicHolder*	_holder;
};

#endif /* !__Ilv_Graphics_Objprop_H */
