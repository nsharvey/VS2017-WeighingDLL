// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/datfield.h
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
// Declaration of the IlvDateField class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Datfield_H
#define __Ilv_Gadgets_Datfield_H

#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

#if !defined(ILV_TM_PREF)
#  if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
// Borland C++ Builder 3.0 is STD and has a weird tm declaration
#    define ILV_TM_PREF IL_STDPREF
#  else
#    define ILV_TM_PREF
#  endif
#endif /* !ILV_TM_PREF */

#if defined(sinix)
#include <time.h>
#else  /* !sinix */
struct ILV_TM_PREF tm;
#endif /* !sinix */

#define ILVDATEFIELDEDITABLEFLAG  0
#define ILVDATEFIELDREADALIGNFLAG 1
// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDateField : public IlvTextField
{
public:
    IlvDateField(IlvDisplay*	display,
		 const IlvRect&	rect,
		 IlUShort	thickness = IlvDefaultGadgetThickness,
		 IlvPalette*	palette   = 0);
    IlvDateField(IlvDisplay*		display,
		 const IlvPoint&	point,
		 IlUShort		thickness = IlvDefaultGadgetThickness,
		 IlvPalette*		palette   = 0);

    enum IlvDateFieldFormat
    {
	df_day,         // 1
	df_Day,         // 01
	df_month,       // 3
	df_Month,       // 03
	df_month_text,  // March
	df_abbrev_month, // Mar
	df_year,        // 95
	df_Year         // 1996
    };

    virtual const char*	check(IlUShort ch);
    virtual void	validate();
    IlBoolean		getValue(struct ILV_TM_PREF tm*) const;
    void		setValue(struct ILV_TM_PREF tm*,
				 IlBoolean redraw = IlFalse);
    IlBoolean		getValue(IlUShort& day,
				 IlUShort& month,
				 IlUShort& year) const;
    void		setValue(IlUShort	day,
				 IlUShort	month,
				 IlUShort	year,
				 IlBoolean	redraw = IlFalse);
    inline void		getFormat(IlvDateFieldFormat&	first,
				  IlvDateFieldFormat&	middle,
				  IlvDateFieldFormat&	last,
				  char&			separator) const
			{
			    first     = _format.first;
			    middle    = _format.middle;
			    last      = _format.last;
			    separator = _separator;
			}
    IlBoolean		setFormat(IlvDateFieldFormat	first,
				  IlvDateFieldFormat	middle,
				  IlvDateFieldFormat	last,
				  char			separator,
				  IlBoolean		redraw = IlFalse);
    const char*		getFormatString() const;
    IlBoolean		setFormatString(const char* formatStr);

    // Y2K issue
    inline static int	GetBaseCentury() { return _BaseCentury; }
    static void		SetBaseCentury(int century);
    inline static int	GetCenturyThreshold() { return _CenturyThreshold; }
    static void		SetCenturyThreshold(int threshold);

    // Input Method interaction
    virtual IlBoolean	needsInputContext() const;

    DeclareGraphicAccessors();
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_valueValue;
    static IlSymbol*	_separatorValue;
    static IlSymbol*	_formatValue;
    static int		_BaseCentury;		// for years coded on 2 digits
    static int		_CenturyThreshold;	// for years coded on 2 digits

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvDateField);

private:
    struct {
	IlvDateFieldFormat first;
	IlvDateFieldFormat middle;
	IlvDateFieldFormat last;
    } _format;
    char		_separator;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(datfield);

#endif /* !__Ilv_Gadgets_Datfield_H */
