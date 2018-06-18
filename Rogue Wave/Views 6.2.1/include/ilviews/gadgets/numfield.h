// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/numfield.h
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
// Declaration of the IlvNumberField class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Numfield_H
#define __Ilv_Gadgets_Numfield_H

#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvNumberField : public IlvTextField
{
public:

    IlvNumberField(IlvDisplay*		display,
		   IlInt		value,
		   const IlvRect&	rect,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    IlvNumberField(IlvDisplay*		display,
		   IlDouble		value,
		   const IlvRect&	rect,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    IlvNumberField(IlvDisplay*		display,
		   const IlvPoint&	point,
		   IlInt		value,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    IlvNumberField(IlvDisplay*		display,
		   const IlvPoint&	point,
		   IlDouble		value,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette   = 0);

    enum IlvNumberFieldFormat {
	thousands	=  1,
	scientific	=  2,
	padright	=  4,
	showpoint	=  8,
	floatmode	= 16
    };

    virtual const char*	check(IlUShort ch);
    virtual void	validate();

    inline IlUInt	getFormat() const { return _mode; }

    inline void		setFormat(IlUInt format) { _mode = format; }

    inline IlBoolean	getFloatMode() const
			{
			    return (_mode & floatmode) ? IlTrue : IlFalse;
			}

    void		setFloatMode(IlBoolean val);

    inline IlBoolean	getScientificMode() const
			{
			    return ((_mode & (floatmode | scientific))
				    == (floatmode | scientific))
				? IlTrue
				: IlFalse;
			}

    void		setScientificMode(IlBoolean val);

    inline IlBoolean	getPadRightMode() const
			{
			    return ((_mode & (floatmode | padright))
				    == (floatmode | padright))
				? IlTrue
				: IlFalse;
			}


    void		setPadRightMode(IlBoolean val);
    inline IlBoolean	getShowPointMode() const
			{
			    return ((_mode & (floatmode | showpoint))
				    == (floatmode | showpoint))
				? IlTrue
				: IlFalse;
			}

    void		setShowPointMode(IlBoolean val);

    inline IlBoolean	getShowThousandMode() const
			{
			    return (_mode & thousands) ? IlTrue : IlFalse;
			}


    void		setShowThousandMode(IlBoolean val);

    inline char		getDecimalPointChar() const
			{
			    return _decimalPointChar;
			}

    void		setDecimalPointChar(char separator);

    inline char		getThousandSeparator() const
			{
			    return _thousandSeparator;
			}

    void		setThousandSeparator(char separator);

    inline IlUShort	getPrecision() const { return _precision; }

    inline void		setPrecision(IlUShort precision)
			{
			    _precision = precision;
			}

    IlInt		getIntValue(IlBoolean& error) const;

    IlBoolean		setValue(IlInt value, IlBoolean redraw = IlFalse);

    IlDouble		getFloatValue(IlBoolean& error) const;

    IlBoolean		setValue(IlDouble value, IlBoolean redraw = IlFalse);

    inline IlDouble	getMinFloat() const { return _minFloat; }

    inline void		setMinFloat(IlDouble value) { _minFloat = value; }

    inline IlInt	getMinInt() const{ return _minInt; }

    inline void		setMinInt(IlInt value) { _minInt = value; }

    inline IlDouble	getMaxFloat() const{ return _maxFloat; }

    inline void		setMaxFloat(IlDouble value) { _maxFloat = value; }

    inline IlInt	getMaxInt() const{ return _maxInt; }

    inline void		setMaxInt(IlInt value) { _maxInt = value; }

    // Input Method interaction
    virtual IlBoolean	needsInputContext() const;

    // ------------------------------------------------------------
    // Bidi interface
    virtual
    IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual IlBoolean	setBidiContext(IlvBidiContext*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);


    DeclareGraphicAccessors();

    static IlSymbol*	_floatModeValue;
    static IlSymbol*	_scientificModeValue;
    static IlSymbol*	_padrightValue;
    static IlSymbol*	_showpointValue;
    static IlSymbol*	_decimalPointValue;
    static IlSymbol*	_precisionValue;
    static IlSymbol*	_showThousandValue;
    static IlSymbol*	_thousandSeparatorValue;
    static IlSymbol*	_intValueValue;
    static IlSymbol*	_minIntValue;
    static IlSymbol*	_maxIntValue;
    static IlSymbol*	_floatValueValue;
    static IlSymbol*	_minFloatValue;
    static IlSymbol*	_maxFloatValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvNumberField);

private:
    IlBoolean		readNumber(const char*) const;

    char		_decimalPointChar;
    char		_thousandSeparator;
    IlUShort		_precision;
    IlUInt		_mode;
    IlDouble		_minFloat;
    IlDouble		_maxFloat;
    IlInt		_minInt;
    IlInt		_maxInt;
};

ILVGDTMODULEINIT(numfield);
#endif /* !__Ilv_Gadgets_Numfield_H */
