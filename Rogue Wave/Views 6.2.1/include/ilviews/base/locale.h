// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/locale.h
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
// Encapsulation of the IlLocale and related classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Locale_H
#define __Ilv_Base_Locale_H

#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Il_Locale_H)
#include <ilog/locale.h>
#endif

#define ILOG_VIEWS_PRODUCT 1
// TO CHANGE
#define IlvEncoding IlEncoding
#define IlvNoEncoding IlNoEncoding
#define IlvFullCompat IlFullCompat
#define IlvLooseCompat IlLooseCompat

class IlvGlobalContext;

// --------------------------------------------------------------------------
// IlvLocale class
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvLocaleExtension : public IlLocaleExtension
{
    friend class IlvGlobalContext;

public:
    IlvLocaleExtension(IlLocale*);

    inline IlBoolean		isLangSet() const { return _langSet; }
    inline const IlSymbol*	getCurrentDisplayLang() const
				{
				    return _currentDisplayLang;
				}
    void			setCurrentDisplayLang(const IlSymbol* lang);
    inline const IlSymbol*	getCurrentLangDB() const
				{
				    return _currentLangDB;
				}
    void			setCurrentLangDB(const IlSymbol* lang);
    IlBoolean			init();
#if 0
    static inline IlvLocaleExtension* Get(const char* localeName = 0) {
	return (IlvLocaleExtension*)(IlLocale::Get(localeName)
				     ->getExtension(ILOG_VIEWS_PRODUCT));
    }
#endif

protected:
    ~IlvLocaleExtension();

private:
    IlBoolean		_langSet;		// Was IlvSetLanguage() called?
    const IlSymbol*	_currentDisplayLang;	// getCurrentLanguage() without
						// the encoding.
    const IlSymbol*	_currentLangDB;		// current language read or
						// written in message database
						// without the encoding.
};


#endif /* !__Ilv_Base_Locale_H */
