// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filter.h
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
// Declaration of bitmap data filters 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filter_H
#define __Ilv_Bitmaps_Filter_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Bitmaps_Data_H)
#include <ilviews/bitmaps/data.h>
#endif
#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif


class ILVDSPEXPORTED IlvBitmapFilter : public IlvValueInterface
{
public:
    IlvBitmapFilter();
    virtual ~IlvBitmapFilter();
    virtual const char*		getClassName() const;
    static IlvBitmapFilter*	Create(const char* classname, 
				       IlBoolean forceLoad = IlTrue);
    static const char**		GetRegisteredFilters(IlUInt& num);
    virtual IlvBitmapData*	apply(IlUInt count = 0, 
				      const IlvBitmapData** datas = 0);
    IlvBitmapData*		applyUnary(const IlvBitmapData* data);
    inline void			setX(IlInt x) { _x = x; }
    inline void			setY(IlInt y) { _y = y; }
    inline void			setWidth(IlUInt width) { _width = width; }
    inline void			setHeight(IlUInt height) { _height = height; }
    inline IlInt		getX() const { return _x; }
    inline IlInt		getY() const { return _y; }
    inline IlUInt		getWidth() const { return _width; }
    inline IlUInt		getHeight() const { return _height; }
    void			setInputs(IlUInt count,
					  const char* const* name);
    const char* const*		getInputs(IlUInt& count) const;
    void			setResult(const char* name);
    const char*			getResult() const;
    void			setName(const char* id);
    inline const char*		getName() const { return _name; }
    void			lock();
    void			unLock();
    IlUInt			getRefCount() const;

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*		_xValue;
    static IlSymbol*		_yValue;
    static IlSymbol*		_widthValue;
    static IlSymbol*		_heightValue;
    static IlSymbol*		_inputsValue;
    static IlSymbol*		_resultValue;
    static IlSymbol*		_nameValue;

protected:
    static IlBoolean		CheckInModules(const char* name);

    IlInt			_x;
    IlInt			_y;
    IlUInt			_width;
    IlUInt			_height;
    char**			_inputs;
    char*			_result;
    char*			_name;
    IlUInt			_count;
    IlUInt			_refcount;
};

IL_MODULETERM(filter, ILVDSPEXPORTED);
#endif /* __Ilv_Bitmaps_Filter_H */
