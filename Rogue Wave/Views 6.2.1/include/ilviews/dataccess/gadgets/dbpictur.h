// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbpictur.h
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
// Declaration of the IliDbPicture class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbpictur_H
#define __Ili_Dbpictur_H

#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbPicture
    : public IlvGadget, public IliFieldItf
{
public:
    IliDbPicture(IlvDisplay* display,
		 const char* bitmapName,
		 const IlvRect& rect,
		 IlUShort thickness = IlvDefaultGadgetThickness,
		 IlvPalette* palette = 0);
    IliDbPicture(IlvDisplay* display,
		 const IlvPoint& at,
		 const char* bitmapName,
		 IlUShort thickness = IlvDefaultGadgetThickness,
		 IlvPalette* palette = 0);
    IliDbPicture(IlvDisplay* display,
		 IlvBitmap* bitmap,
		 const IlvRect& rect,
		 IlUShort thickness = IlvDefaultGadgetThickness,
		 IlvPalette* palette = 0);
    IliDbPicture(IlvDisplay* display,
		 const IlvPoint& at,
		 IlvBitmap* bitmap,
		 IlUShort thickness = IlvDefaultGadgetThickness,
		 IlvPalette* palette = 0);
    virtual ~IliDbPicture();


    virtual void	setHolder(IlvGadgetHolder*);
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	doIt();

    // Implements IliFieldItf
    virtual
    const IliValue&	f_getValue(IlBoolean internalP = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&,
				   IlBoolean internalP = IlFalse);
    virtual void	f_refresh();
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();
    virtual IlBoolean	f_isConsistent() const;

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual void	f_setAlignment(IlvAlignment );
    virtual
    IlvAlignment	f_getAlignment() const;

    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    virtual
    const IlvValueTypeClass* getValueType(const IlvSymbol* name) const;
    static  void	GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

    void		draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    virtual IlBoolean	f_canDrawValue() const;
    virtual void	f_drawValue(IlvPort* dst,
				    const IlvRect& bbox,
				    const IliValue& value,
				    IlBoolean selected,
				    IlvPalette* fillPalette,
				    IlvPalette* textPalette,
				    const IlvRegion* clip = 0) const;

    virtual IlBoolean	f_supportsTableProperties() const;

    void		drawValue(IlvPort* dst,
				  IlvRect& bbox,
				  IlvBitmap*,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    void		setAdjustedBitmap(IlBoolean adj) { _isAdjust = adj; }
    IlBoolean		isAdjustedBitmap() const { return _isAdjust; }
    void		enableTransparentColor(IlBoolean enable);
    IlBoolean		isTransparentColorEnabled() const;
    void		setBitmap(IlvBitmap* bmp);
    inline IlvBitmap*	getBitmap() const { return _bitmap; }

    IlBoolean		setBitmapName(const char* name,
				      IlBoolean readbmp = IlTrue);
    const char*		getBitmapName() const { return _value.asString(); }
    void		setBitmapType(IlBoolean str) { _isStringType = str; }
    IlBoolean		isStringType() { return _isStringType; }
    IlBoolean		isBitmapType() { return !_isStringType; }

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbPicture);

protected:
    IliValue		_value;
    IlvBitmap* 		_bitmap;
    IlBoolean 		_isAdjust;
    IlBoolean 		_isStringType;
    IlBoolean 		_transColor;
    IlvAlignment	_alignment;

    void		computeNewDrawRect(const IlvPoint& at);
    void		loadBitmap(const char* name);
    void		init();

    virtual IlBoolean	classFocusable() const;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbPicture);

#endif /* !__Ili_Dbpictur_H */
