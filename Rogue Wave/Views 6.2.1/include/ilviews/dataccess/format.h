// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/format.h
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
// Declaration of the IliFormat class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Format_H
#define __Ili_Format_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef __Ilv_Base_Link_H
#  include <ilviews/base/link.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ili_Module_H
#  include <ilviews/dataccess/module.h>
#endif

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

#ifndef __Ili_Decimal_H
#  include <ilviews/dataccess/decimal.h>
#endif

#ifndef __Ili_Date_H
#  include <ilviews/dataccess/date.h>
#endif

enum IliFormatType {
    IliNullFormatType,
    IliStringFormatType,
    IliNumberFormatType,
    IliDateFormatType
};

enum IliCurrencyPosition {
    IliCP_AtLeft_NoSpace,
    IliCP_AtLeft_Space,
    IliCP_AtRight_NoSpace,
    IliCP_AtRight_Space
};

enum IliFormatCategory {
    IliSystemFormat,
    IliApplicationFormat,
    IliUserFormat
};

class ILVVWSEXPORTED IlvDisplay;
class IliFormatAliasEntry;

// --------------------------------------------------------------------------
// IliFormatIpl
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliFormatIpl : public IliRefCounted
{
public:
    IliFormatIpl(const char* name);

    const char*		getDefinition() const;
    virtual
    IliFormatType	getType() const;

    virtual void	formatString(IliString& dest, const char* val) const;
    virtual void	formatBoolean(IliString& dest, IlBoolean val) const;
    virtual void	formatInteger(IliString& dest, IlInt val) const;
    virtual void	formatFloat(IliString& dest, IlFloat val) const;
    virtual void	formatDouble(IliString& dest, IlDouble val) const;
    virtual void	formatDecimal(IliString& dest, IliDecimal val) const;
    virtual void	formatDate(IliString& dest, const IliDate& val) const;
    virtual void	formatTime(IliString& dest, const IliTime& val) const;

    virtual IlBoolean	parseDate(const char*,
				  IlUInt len,
				  IliDate&,
				  IlBoolean& isNull) const;
    IlBoolean		isEditModeOn() const;
    void		setEditModeOn();
    void		setEditModeOff();

    virtual IlBoolean	isPasswordFormat() const;
    virtual IlBoolean	isUserDefinedFormat() const;

    static
    IliFormatIpl*	GetNullFormat();
    static
    IliFormatIpl*	FindFormat(const char* definition);
    static void		AddCustomFormat(IliFormatIpl* ipl);
    static void		RemoveCustomFormat(IliFormatIpl* ipl);

    static void		AtInit();
    static void		AtExit();

protected:
    IliString			_definition;
    IlBoolean			_editModeOn;

    static IlvStringHashTable*	_allFormats;
    static IlvList*		_customFormats;
    static IliFormatIpl*	_nullFormat;
    static IliFormatIpl*	_numberFormat;
    static IliFormatIpl*	_fixedNumberFormat;
    static IliFormatIpl*	_expNumberFormat;
    static IliString*		_tempBuf;
    static IliString*		_bigBuf;

    void		intern();
    void		unIntern();

    virtual ~IliFormatIpl();
    virtual void	reset();

    friend class IliFormat;
};


class IliFormatLangSettings;

// --------------------------------------------------------------------------
// IliFormat
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliFormat
{
public:
    IliFormat();
    IliFormat(const char* definition);
    IliFormat(const IliFormat&);
    ~IliFormat();

    void		read(IL_STDPREF istream& input);
    void		write(IL_STDPREF ostream& output) const;
    IliFormat& operator =(const IliFormat& fmt);
    int operator	==(const IliFormat& fmt) const;

    const char*		getDefinition() const;
    void		setDefinition(const char* definition);
    IlBoolean		isNull() const;
    IliFormatType	getType() const;
    void		format(IliString& dest, const char* val) const;

#if !defined(__alpha) || defined(WIN32)
    void		format(IliString& dest, IlBoolean val) const;
#endif
    void		format(IliString& dest, IlInt val) const;
    void		format(IliString& dest, IlFloat val) const;
    void		format(IliString& dest, IlDouble val) const;
    void		format(IliString& dest, IliDecimal val) const;
    void		format(IliString& dest, const IliDate& val) const;
    void		format(IliString&, const IliTime&) const;

    IlBoolean		isEditModeOn() const;
    void		setEditModeOn();
    void		setEditModeOff();
    IlBoolean		isPasswordFormat() const;
    IlBoolean		isUserDefinedFormat() const;
    static
    const IliFormat&	GetDefaultFormat();
    static IlInt	GetAliasesCount();
    static const char*	GetAliasName(IlInt aliasIndex);
    static IlInt	GetAliasIndex(const char* aliasName);
    static
    IliFormatType	GetAliasFormatType(IlInt aliasIndex);
    static
    IliFormatCategory	GetAliasFormatCategory(IlInt aliasIndex);
    static const char*	GetAliasDefinition(IlInt aliasIndex);
    static const char*	GetAliasDefinition(const char* aliasName);
    static void		AddAlias(const char* aliasName,
				 const char* definition,
				 IliFormatType type,
				 IliFormatCategory category = IliUserFormat);
    static void		SetAliasName(IlInt aliasIndex, const char* name);
    static void		SetAliasDefinition(IlInt aliasIndex,
					   const char* definition);
    static void		SetAliasFormatType(IlInt aliasIndex,
					   IliFormatType type);
    static void		SetAliasFormatCategory(IlInt aliasIndex,
					       IliFormatCategory c);
    static void		RemoveAlias(IlInt aliasIndex);
    static char		GetDecimalPoint();
    static void		SetDecimalPoint(char c);
    static char		GetThousandsSeparator();
    static void		SetThousandsSeparator(char c);
    static const char*	GetCurrencySymbol();
    static void		SetCurrencySymbol(const char* c);
    static
    IliCurrencyPosition	GetCurrencyPosition();
    static void		SetCurrencyPosition(IliCurrencyPosition pos);
    static char		GetDateSeparator();
    static void		SetDateSeparator(char c);
    static char		GetTimeSeparator();
    static void		SetTimeSeparator(char c);

    static const char*	GetPMString();
    static void		SetPMString(const char*);

    static const char*	GetAMString();
    static void		SetAMString(const char*);

    static const char*	GetDecimalPointEx();
    static void		SetDecimalPointEx(const char*);

    static const char*	GetThousandsSeparatorEx();
    static void		SetThousandsSeparatorEx(const char*);

    static const char*	GetDateSeparatorEx();
    static void		SetDateSeparatorEx(const char*);

    static const char*	GetTimeSeparatorEx();
    static void		SetTimeSeparatorEx(const char*);

    static IlBoolean	IsMonthBeforeDay();
    static void		SetMonthBeforeDay(IlBoolean before);

    static IlBoolean	ReadMessageDatabase(IlvDisplay* disp,
					    const char* file);
    static void		MessageDatabaseToLabels(IlvDisplay*);
    static void		ConnectToMessageDatabase(IlvDisplay* display);
    static const char*	GetShortWeekDayLabel(IlInt weekDay);
    static void		SetShortWeekDayLabel(IlInt weekDay, const char* str);
    static const char*	GetLongWeekDayLabel(IlInt weekDay);
    static void		SetLongWeekDayLabel(IlInt weekDay, const char* label);
    static const char*	GetShortMonthLabel(IlInt month);
    static void		SetShortMonthLabel(IlInt month, const char* label);
    static const char*	GetLongMonthLabel(IlInt month);
    static void		SetLongMonthLabel(IlInt month, const char* label);
    static IlInt	GetMonthByName(const char* name);

    enum SettingsTag {
	DbmsSettings,
	UserSettings
    };
    static SettingsTag	GetCurrentSettings();
    static SettingsTag	SetCurrentSettings(SettingsTag);
    static SettingsTag	SelectDbmsSettings();
    static SettingsTag	SelectUserSettings();

    static IlBoolean	ParseInt(const char*,
				 IlUInt len,
				 IlInt&,
				 IlBoolean& isNull);
    static IlBoolean	ParseFloat(const char*,
				   IlUInt len,
				   IlFloat&,
				   IlBoolean& isNull);
    static IlBoolean	ParseDouble(const char*,
				    IlUInt len,
				    IlDouble&,
				    IlBoolean& isNull);
    static IlBoolean	ParseDecimal(const char*,
				     IlUInt len,
				     IliDecimal&,
				     IlBoolean& isNull);
    static IlBoolean	ParseDate(const char*,
				  IlUInt len,
				  IliDate&,
				  IlBoolean& isNull);
    static IlBoolean	ParseTime(const char*,
				  IlUInt len,
				  IliTime&,
				  IlBoolean& isNull);
    IlBoolean		parseFormattedDate(const char*,
					   IlUInt len,
					   IliDate&,
					   IlBoolean& isNull) const;


    static IlBoolean	IsDefaultStringLtoR();
    static void		SetDefaultStringLtoR(IlBoolean direction);

    static void		AtInit();
    static void		AtExit();

protected:
    IliFormatIpl* _ipl;

    static IliFormatLangSettings* _dbmsSettings;
    static IliFormatLangSettings* _userSettings;
    static IliFormatLangSettings* _currentSettings;

    static IliFormat*	_defaultFormat;

    static IlvList*	_aliasesList;
    static
    IlvStringHashTable*	_aliasesTable;
    static IlInt	_aliasesCount;

    static
    IliFormatAliasEntry* GetAliasEntry(IlInt index);

    static IlBoolean	_defaultStringLtoR;

    friend class IliModuleCLASS(IliFormat);
};

IliModuleDECL_exp(ILV_INF_EXPORTED,IliFormat);

#endif
