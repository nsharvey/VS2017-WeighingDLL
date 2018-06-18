// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/studio/object.h
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
// Declaration of Appframe Studio macros
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Studio_Object_H)
#define __Ilv_Appframe_Studio_Object_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Rectgadc_H)
#include <ilviews/gadgets/rectgadc.h>
#endif /* __Ilv_Gadgets_Rectgadc_H */
#if !defined(__Ilv_Gadgets_Rectscgc_H)
#include <ilviews/gadgets/rectscgc.h>
#endif /* __Ilv_Gadgets_Rectscgc_H */
#if !defined(__Ilv_Contain_Rectangl_H)
#include <ilviews/contain/rectangl.h>
#endif /* __Ilv_Contain_Rectangl_H */

// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvStudioObject : public IlvGadgetContainerRectangle
{
public:
    IlvDvStudioObject(IlvDisplay*     display,
		      const IlvRect&  rect,
		      IlvPalette*     palette = 0);
    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvDvStudioObject);

    IlUInt		getClass() const;
    void		setClass(IlUInt);

    IlString		getUserClassname() const;
    void		setUserClassname(const IlString&);

    static IlUInt	GetClassCardinal();
    static IlString	GetClassname(IlUInt = IlvBadIndex);
    static IlString	GetClassFilename(IlUInt);
    static IlUInt	GetClassIndex(IlString);

    static IlSymbol*	_dvClassValue;
    static IlSymbol*	_userClassValue;

    virtual void        makeView(IlvPort* dst, const IlvTransformer* t = 0);
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

protected:

    IlUInt		_dvClass;
    IlString		_userClassName;

    IlBoolean           _needUpdateTransformer;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(object);

#endif /* __Ilv_Appframe_Studio_Object_H */
