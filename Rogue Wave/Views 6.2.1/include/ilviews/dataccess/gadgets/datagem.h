// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/datagem.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliDataGem class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Datagem_H
#define __Ili_Datagem_H

#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#  include <ilviews/base/link.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ili_Module_H)
#  include <ilviews/dataccess/module.h>
#endif
#if !defined(__Ili_String_H)
#  include <ilviews/dataccess/string.h>
#endif

class ILV_INF_EXPORTED IliDataGem;

typedef void (* IliDataGemCallback) (IliDataGem*, IlAny);

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDataGem
: public IlvGadget
{
public:
    virtual ~IliDataGem();
    IlBoolean		hasGlobalScope() const;

    virtual void	setGlobalScope(IlBoolean global);

    IlBoolean		isSystemUsage() const;

    virtual void	usedBySystem(IlBoolean usage);

    DeclareTypeInfo();
    DeclareIOConstructors(IliDataGem);

    virtual void	setHolder(IlvGadgetHolder* holder);
    virtual void	setName(const char*);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t,
			     const IlvRegion* clip) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort* dst,
				    const IlvTransformer* t = 0,
				    const IlvRegion* rect = 0) const;
    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint& tp,
				 const IlvTransformer* t = 0) const;
    virtual IlBoolean	intersects(const IlvRegion&,
				   const IlvTransformer* t = 0) const;
    virtual IlBoolean	inside(const IlvRegion&,
			       const IlvTransformer* t = 0) const;
    virtual void	boundingBox(IlvRect& r,
				    const IlvTransformer* t = 0) const;

    virtual IlBoolean	classFocusable() const;

    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer* = 0) const;

    virtual IlvBitmap*	getBitmap() const;

    static
    IliDataGemCallback	GetAutoShowCallback();
    static IlAny	GetAutoShowClientData();
    static void		SetAutoShowCallback(IliDataGemCallback, IlAny);

    IlBoolean		isAutoShowEnabled() const;
    void		enableAutoShow(IlBoolean);

    IlBoolean		isShowing() const;
    void		show(IlBoolean f);

    virtual void	computeRects(IlvRect& bmpRect,
				     IlvRect& textRect,
				     const IlvTransformer* t) const;
    virtual void	setDefaultResources();
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    static void		GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);

    virtual IlBoolean	isFreeAccess() const;

protected:
    void		drawRelief(IlvPort*,
				   const IlvRect&,
				   const IlvRegion*) const;
    void		drawLabelForName(IlvPort*,
					 const IlvRect&,
					 const IlvRegion*) const;

    void		drawReliefDefaultLook(IlvPort*,
					      const IlvRect&,
					      const IlvRegion*) const;
    void		drawRefiefVxLook(IlvPort*,
					 const IlvRect&,
					 const IlvRegion*) const;  
    void		drawLabelDefaultLook(IlvPort*,
					     const IlvRect&,
					     const IlvRegion*) const;
    void		drawLabelVxLook(IlvPort*,
					const IlvRect&,
					const IlvRegion*) const;

    IlBoolean		_autoShow;
    IlBoolean		_isShowing;
    IlBoolean		_hasGlobalScope;
    IlBoolean		_systemUsage;
    IliDataGem(IlvDisplay* display,
	       const IlvPoint& at,
	       IlUShort thickness = IlvDefaultGadgetThickness,
	       IlvPalette* palette = 0);

    static IliDataGemCallback	_autoShowCallback;
    static IlAny		_autoShowClientData;
};

IliModuleDECL_exp(ILV_INF_EXPORTED, IliDataGem);

#endif /* !__Ili_Datagem_H */
