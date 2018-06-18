// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/scriptft.h
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
// Declaration of the IlvScriptChartFunction class.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Scriptft_H
#define __Ilv_Charts_Scriptft_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Script_H)
#include <ilviews/base/script.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#include <ilviews/graphics/holder.h>
#endif
#if !defined(__Ilv_Charts_Data_H)
#include <ilviews/charts/data.h>
#endif

// --------------------------------------------------------------------------
// Class IlvScriptChartFunction
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvScriptChartFunction : public IlvAbstractChartFunction
{
public:

    IlvScriptChartFunction(const char* name = 0,
			   IlvPointInfoCollection* ptInfoCollection = 0);

    IlvScriptChartFunction(const IlvCoordInterval& xRange,
			   IlUInt count,
			   const char* scriptFunctionName,
			   IlvGraphicHolder* holder,
			   const IlSymbol* scriptLanguageName = 0,
			   const char* name = 0,
			   IlvPointInfoCollection* ptInfoCollection = 0);

    virtual ~IlvScriptChartFunction();

    // Accessors
    inline const char*	getScriptFunctionName() const 
			{
			    return _scriptFunctionName;
			}

    void		setScriptFunctionName(const char* name);

    inline
    IlvGraphicHolder*	getHolder() const { return _holder; }

    inline void		setHolder(IlvGraphicHolder* holder)
			{
			    _holder = holder;
			}

    inline
    const IlSymbol*	getScriptLanguageName() const
			{
			    return _scriptLanguageName;
			}

    inline void		setScriptLanguageName(const IlSymbol* name)
			{
			    _scriptLanguageName = name;
			}

    IlvScriptContext*	getScriptContext() const;

    virtual IlBoolean	isFunctionDefined() const;

    virtual void	getPoint(IlUInt i, IlvDoublePoint& point) const;

    // callScriptFunction is capable of calling a (jv)script 
    // function having the following signature:
    // y = f(x)
    // Here, f is the name of the function; x and y are IlDouble.
    // callScriptFunction returns IlTrue if the call is 
    // successfully achieved. Otherwise it returns IlFalse.
    IlBoolean		callScriptFunction(IlDouble x,IlDouble& y) const;

    DeclareChartDataSetTypeInfo(IlvScriptChartFunction);

protected:
    char*		_scriptFunctionName;
    IlvGraphicHolder*	_holder;
    const IlSymbol*	_scriptLanguageName;
};

ILVCHTMODULEINIT(scriptft);

#endif /* !__Ilv_Charts_Scriptft_H */
