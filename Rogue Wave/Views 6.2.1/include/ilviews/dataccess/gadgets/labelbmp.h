// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/labelbmp.h
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
// Declaration of the IliLabeledBitmap class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Labelbmp_H
#define __Ili_Labelbmp_H

#ifndef __Ilv_Base_Graphic_H
#  include <ilviews/base/graphic.h>
#endif

#ifndef __Ilv_Base_Port_H
#  include <ilviews/base/port.h>
#endif

#ifndef __Ili_String_H
#include <ilviews/dataccess/string.h>
#endif

#ifndef __Ili_Module_H
#include <ilviews/dataccess/module.h>
#endif

// -------------------------------------------------------------------------
// IliLabeledBitmap
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliLabeledBitmap : public IlvSimpleGraphic
{
public:
    IliLabeledBitmap(IlvDisplay* display,
		     IlvPos x,
		     IlvPos y,
		     const char* name,
		     const char* bmpName,
		     IlvPalette* palette = 0);
    ~IliLabeledBitmap();

    DeclareTypeInfo();
    DeclareIOConstructors(IliLabeledBitmap);

    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint& tp,
				 const IlvTransformer* t) const;
    virtual void	boundingBox(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	setMode(IlvDrawMode m);
    inline const char*	getLabelName() const 
			{
			    return (const char*)_labelName;
			}
    inline void		setLabelName(const char* label) { _labelName = label; }
    inline const char*	getBitmapName() const
			{
			    return (const char*)_bitmapName;
			}
    void		setBitmapName(const char* name);

    //---- Accessors ----
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    static void		GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);

protected:
    IlvRect		_rectBmp;
    IlvBitmap*		_bitmap;
    IlvPoint		_pos;
    IliString		_labelName;
    IliString		_bitmapName;

    void		computeRectBitmap(const IlvTransformer* t) const;
    void		computeBitmap() const;
};


IliModuleDECL_exp(ILV_DBG_EXPORTED, IliLabeledBitmap);

#endif

