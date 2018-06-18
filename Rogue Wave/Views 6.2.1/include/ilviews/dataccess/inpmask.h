// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inpmask.h
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
// Declaration of the IliInputMask class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Inpmask_H
#define __Ili_Inpmask_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#  include <iostream>
#else
#  include <iostream.h>
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

#ifndef __Ili_Alloc_H
#  include <ilviews/dataccess/alloc.h>
#endif

#ifndef __Ili_Value_H
#  include <ilviews/dataccess/value.h>
#endif

#ifndef __Ili_Intl_H
#  include <ilviews/dataccess/intl.h>
#endif

class IliMaskAliasEntry;

enum IliPlaceHolderName {
    IliPlaceHolderMandatoryDigit = 0,
    IliPlaceHolderOptionalDigit,
    IliPlaceHolderMandatoryDigitSign,
    IliPlaceHolderOptionalDigitSign,
    IliPlaceHolderMandatoryLetter,
    IliPlaceHolderOptionalLetter,
    IliPlaceHolderMandatoryUpperCase,
    IliPlaceHolderOptionalUpperCase,
    IliPlaceHolderMandatoryLowerCase,
    IliPlaceHolderOptionalLowerCase,
    IliPlaceHolderMandatoryDigitLetter,
    IliPlaceHolderOptionalDigitLetter,
    IliPlaceHolderMandatoryDigitUpperCase,
    IliPlaceHolderOptionalDigitUpperCase,
    IliPlaceHolderMandatoryDigitLowerCase,
    IliPlaceHolderOptionalDigitLowerCase,
    IliPlaceHolderMandatoryAnyCharacter,
    IliPlaceHolderOptionalAnyCharacter,
    IliPlaceHolderDecimalPoint,
    IliPlaceHolderThousandsSeparator,
    IliPlaceHolderExponentSeparator,
    IliPlaceHolderExponentLowerSeparator,
    IliPlaceHolderMandatoryDigitsInterval,
    IliPlaceHolderMandatoryBeginSet,
    IliPlaceHolderMandatoryEndSet,
    IliPlaceHolderOptionalBeginSet,
    IliPlaceHolderOptionalEndSet,
    IliPlaceHolderMandatoryLettersInterval,
    IliPlaceHolderDateSeparator,
    IliPlaceHolderTimeSeparator,
    IliPlaceHolderForDisplayAndValue,
    IliPlaceHolderRightToLeft,
    IliPlaceHolderOnlyDisplay,
    IliPlaceHolderMandatoryHexadecimal,
    IliPlaceHolderOptionalHexadecimal,
    IliPlaceHolderWaitCharacter,
    IliPlaceHolderCount
};

// --------------------------------------------------------------------------
// IliInputMaskIpl
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliInputMaskIpl : public IliRefCounted
{
public:
    IliInputMaskIpl(const char* definition);
    virtual ~IliInputMaskIpl();

    virtual
    IliInputMaskIpl*	getRedirect();
    const char*		getDefinition() const;
    virtual IlInt	getMaxEntryChar() const;
    IlInt		getMaxCharMask() const;
    void		setMaxCharMask(IlInt v);
    virtual IlBoolean	isValidChar(IlInt pos,
				    wchar_t c,
				    IlBoolean editMode) const;
    IlInt		getFirstEditablePos() const;
    IlInt		getLastEditablePos() const;
    virtual IlInt	getNextEditablePos(IlInt pos) const;
    virtual IlInt	getPreviousEditablePos(IlInt pos) const;
    virtual IlBoolean	format(IliString& dest,
			       const IliValue& src,
			       IlBoolean forEdit) const;
    virtual IlBoolean	unFormat(IliString& dest, const char* src) const;
    virtual void	formatForClipboard(IliString& dest,
					   const char* src,
					   IlInt startPos) const;
    virtual IlBoolean	isFixChar(IlInt pos) const;
    virtual IlBoolean	isConstantChar(IlInt pos) const;
    virtual IlBoolean	isNeededChar(IlInt pos) const;
    virtual wchar_t	filterChar(IlInt pos, wchar_t c);
    virtual wchar_t	killChar(IlInt pos, wchar_t c);
    IlBoolean		checkIndexChar(IlInt pos) const;
    static
    IliInputMaskIpl*	FindMask(const char* definition);
    static
    IliInputMaskIpl*	GetNullMask();

    static void		AddCustomMask(IliInputMaskIpl* msk);
    static void		RemoveCustomMask(IliInputMaskIpl* msk);

    static void		AtInit();
    static void		AtExit();

    ILI_MLK_DECL();

protected:
    IliString		_name;
    IlInt		_maxCharMask;

    virtual void	reset();
    void		intern();
    void		unIntern();

    virtual const char*	getEffectiveDefinition() const;
    virtual
    const IliFormat&	getValueFormat() const;

    static IlvList*		_customMasks;
    static IlvStringHashTable*	_allMasks;
    static IliInputMaskIpl*	_nullMask;
    static IliString*		_buf1;
    static wchar_t*		_buf2;
    static size_t		_buf2Size;
    static wchar_t*		_buf3;
    static size_t		_buf3Size;

    friend class IliInputMask;
};

// --------------------------------------------------------------------------
// IliInputMask
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliInputMask
{
public:
    IliInputMask();
    IliInputMask(const char* definition);
    IliInputMask(const IliInputMask& msk);
    ~IliInputMask();
    IliInputMask& operator=(const IliInputMask& msk);
    int operator	==(const IliInputMask&) const;
    void		read(IL_STDPREF istream& input);
    void		write(IL_STDPREF ostream& output) const;
    const char*		getDefinition() const;
    void		setDefinition(const char* definition);
    IlBoolean		isNull() const;

    IlInt		getMaxChar() const;
    IlBoolean		isValidChar(IlInt pos,
				    wchar_t c,
				    IlBoolean editMode = IlTrue) const;

    IlInt		getFirstEditablePos() const;
    IlInt		getLastEditablePos() const;
    IlInt		getNextEditablePos(IlInt pos) const;
    IlInt		getPreviousEditablePos(IlInt pos) const;
    IlBoolean		format(IliString& dest,
			       const IliValue& src,
			       IlBoolean forEdit) const;
    IlBoolean		unFormat(IliString& dest, const char* src) const;
    void		formatForClipboard(IliString& dest,
					   const char* src,
					   IlInt startPos) const;

    IlBoolean		isFixChar(IlInt pos) const;
    IlBoolean		isConstantChar(IlInt pos) const;
    IlBoolean		isNeededChar(IlInt pos) const;
    IlBoolean		checkIndex(IlInt pos) const;
    wchar_t		filterChar(IlInt pos, wchar_t c);
    wchar_t		killChar(IlInt pos, wchar_t c);
    static wchar_t	GetPlaceHolderChar();
    static IliInputMask& GetDefaultMask();
    static IlInt	GetAliasesCount();
    static const char*	GetAliasName(IlInt aliasIndex);
    static IlInt	GetAliasIndex(const char* aliasName);
    static const char*	GetAliasDefinition(IlInt aliasIndex);
    static const char*	GetAliasDefinition(const char* aliasName);
    static void		AddAlias(const char* aliasName,
				 const char* definition);
    static void		SetAliasName(IlInt aliasIndex, const char* name);
    static void		SetAliasDefinition(IlInt aliasIndex,
					   const char* definition);
    static void		RemoveAlias(IlInt aliasIndex);

    static void		SetPlaceHolderValue(IliPlaceHolderName name,
					    wchar_t value);

    static void		AtInit();
    static void		AtExit();

protected:
    IliInputMaskIpl*	getIpl();
    const IliInputMaskIpl* getIpl() const;

    IliInputMaskIpl*	_ipl;

    static
    IliInputMask*	_defaultMask;
    static
    IlvList*		_aliasesList;
    static
    IlvStringHashTable*	_aliasesTable;
    static IlInt	_aliasesCount;

    static
    IliMaskAliasEntry*	GetAliasEntry(IlInt index);

    friend class IliModuleCLASS(IliInputMask);
};

IliModuleDECL_exp(ILV_INF_EXPORTED,IliInputMask);

#endif
