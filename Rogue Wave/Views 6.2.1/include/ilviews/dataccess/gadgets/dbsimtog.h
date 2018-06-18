// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbsimtog.h
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
// Declaration of the IliSimpleToggle class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbsimtog_H
#define __Ili_Dbsimtog_H

#ifndef __Ili_Palspec_H
#  include <ilviews/dataccess/palspec.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

// --------------------------------------------------------------------------
// IliSimpleToggle
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliSimpleToggle : public IliDbToggle
{
public:
    IliSimpleToggle(IlvDisplay* display, const IlvPoint& at);
    ~IliSimpleToggle();

    DeclareTypeInfo();
    DeclareIOConstructors(IliSimpleToggle);

    virtual void	applyTransform(const IlvTransformer* t);
    virtual IlBoolean	f_isConsistent() const;
    virtual IlBoolean	f_canDrawValue() const;
    virtual IlBoolean	f_opensADialog() const;
    virtual void	f_drawValue(IlvPort* dst,
				    const IlvRect& bbox,
				    const IliValue& value,
				    IlBoolean selected,
				    IlvPalette* fillPalette,
				    IlvPalette* textPalette,
				    const IlvRegion* clip = 0) const;

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t=0,
			     const IlvRegion* clip = 0) const;
    virtual void	drawFocus(IlvPort* dst,
				  const IlvPalette* palette,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
protected:
    IlBoolean		_toggleSelected;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliSimpleToggle);

#endif /* !__Ili_Dbtbltog_H*/
