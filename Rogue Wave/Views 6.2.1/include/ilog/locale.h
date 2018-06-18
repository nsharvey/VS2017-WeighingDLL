// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/locale.h
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
// Declaration of the locale class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Il_Locale_H
#define __Il_Locale_H

#if !defined(__IL_Macros_H)
#include <ilog/macros.h>
#endif /* !__IL_Macros_H */

#if !defined(__Il_Calendar_H)
#include <ilog/calendar.h>
#endif /* !__IL_Calendar_H */

#if defined(IL_STD)
#include <clocale>
#include <cstdlib>
#else  /* !IL_STD */
#include <locale.h>
#include <stdlib.h>
#endif /* IL_STD */

// ---------------------------------------------------------------------------
// The following convention is used internally to represent a locale name:
//	
//	 language_territory.encoding
//
// language
//     Is a 2-letter, lowercase abbreviation for the language name.
//     The abbreviations are specified in ISO 639 Code for the
//     Representation of Names of Languages, for example: en (English),
//     fr (French), de (German, from "Deutsch"), ja (Japanese).
//
// territory
//     Is a 2-letter, uppercase abbreviation for the territory name. The
//     abbreviations are specified in ISO 3166 Codes for the
//     Representation of Names of Countries, for example: US (United
//     States), NL (the Netherlands), FR (France), DE (Germany, from
//     "Deutschland"), JP (Japan).
//
// encoding
//    Is a string that identifies the codeset. Any character encoding that
//    has been registered with IANA. 
//    ftp://ftp.isi.edu/in-notes/iana/assignments/character-sets
//
// For exemple:
//    fr_FR.ISO-8859-1
//    ja_JP.EUC-JP
//
// The IlEncoding enum type contains the supported encodings.
// Here is the list with their corresponding charsets and Windows code
// pages, and the set of languages they support:
//
// IlUsAcii	  US-ASCII
//
// IlIsoLatin1	  ISO-8859-1  &&  subset of windows-1252
//		  Latin1 covers most West European languages such as 
//		  Afrikaans (af), Albanian (sq), Basque (eu), Catalan (ca),
//		  Danish (da), Dutch (nl), English (en), Faroese (fo), 
//		  Finnish (fi), French(fr), Galician (gl), German (de), 
//		  Icelandic (is), Irish (ga), Italian (it), Norwegian (no), 
//		  Portuguese (pt), Scottish (gd), Spanish (es), Swedish (sv).
//		  It was derived from the DEC Multinational Character Set.
//		  The lack of the ligatures Dutch IJ, French OE and ,,German`` 
//		  quotation marks is considered tolerable.
//
// IlIsoLatin2	  ISO-8859-2
//		  Latin2 covers the languages of Central and Eastern Europe: 
//		  Croatian (hr), Czech (cs), Hungarian (hu), Polish (pl),
//		  Romanian (ro), Slovak (sk), Slovenian (sl). 
//		  The German umlauts äöüß are found at exactly the same 
//		  positions in Latin1, Latin2, Latin3, Latin4, Latin5, Latin6. 
//		  Thus you can write German+Polish with Latin2 or 
//		  German+Turkish with Latin5 but there is no 8bit charset to 
//		  properly mix German+Russian, for instance. 
//
// IlIsoLatin3	  ISO-8859-3
//		  Latin3 is popular with authors of Esperanto (eo), 
//		  Maltese (mt), and it covered Turkish before the introduction 
//		  of Latin5.
//
// IlIsoLatin4	  ISO-8859-4
//		  Latin4 introduced letters for Estonian, the Baltic languages
//		  Latvian and Lithuanian, Greenlandic and Lappish. 
//		  It is an incomplete precursor of Latin6. 
// 
// IlIsoLatinCyrillic ISO-8859-5
//		  With these Cyrillic letters you can type Bulgarian (bg), 
//		  Byelorussian (be), Macedonian (mk), Russian (ru), 
//		  Serbian (sr) and Ukrainian (uk). 
//		  The ordering is based on the (incompatibly) revised 
//		  GOST 19768 of 1987 with the Russian letters except for ë 
//		  sorted by Russian alphabet (ABVGDE). 
// 
// IlIsoLatinArabic ISO-8859-6
//		  This is the Arabic (ar) alphabet. 
//
// IlIsoLatinGreeek ISO-8859-7
//		  This is modern Greek (el).
//
// IlIsoLatinHebrew ISO-8859-8
//		  This is Hebrew (iw).
//
// IlIsoLatin5	  ISO-8859-9  and subset of CP-1254
//		  Latin5 replaces the rarely needed Icelandic letters ðýþ in 
//		  Latin1 with the Turkish (tr) ones. 
// 
// IlIsoLatin6    ISO-8859-10
//		  Latin6 rearranged Latin4, added the last missing Inuit 
//		  (Greenlandic Eskimo) and non-Skolt Sami (Lappish) letters 
//		  and reintroduced the Icelandic ðýþ to cover the entire 
//		  Nordic area: Estonian (et), Lapp, Latvian (lv) and
//		  Lithuanian (lt). Skolt Sami still needs a few more accents.
//
// IlEucJP	  EUC-JP
//		  Extended Unix Code for Japanese.
//		  Standardized by OSF, UNIX International, and UNIX Systems
//		  Laboratories Pacific.	 Uses ISO 2022 rules to select
//		  code set 0: JIS Roman (a single 7-bit byte set)
//		  code set 1: JIS X0208-1990 (a double 8-bit byte set)
//			      restricted to A0-FF in both bytes
//		  code set 2: Half Width Katakana (a single 7-bit byte set)
//			      requiring SS2 as the character prefix
//		  code set 3: JIS X0212-1990 (a double 7-bit byte set)
//			      restricted to A0-FF in both bytes
//			      requiring SS3 as the character prefix
//
// IlShiftJIS	  Shift_JIS && CP 932
//		  A Microsoft code that extends csHalfWidthKatakana to include 
//		  kanji by adding a second byte when the value of the first 
//		  byte is in the ranges 81-9F or E0-EF.
//
// IlEucKR	  EUC-KR (KS C 5861-1992)
//		  Extended Unix Code for Korean.
//                The 8-bit characters of Korean EUC, which contains both 
//                ASCII and the Wansung characters from KSC 5601, but does 
//                not contain the full Johab character set from the appendix 
//                in that standard.
//
// IlGb2312	  GB2312 && EUC-SC && CP 936
//		  Multibyte encoding standardized by the People's Republic
//		  of China (Simplified Chinese)
// 
// IlBig5	  Big5 && CP 950
//		  Multibyte encoding standardized by Taiwan (Traditional 
//                Chinese)
//
// IlBig5HKSCS	  Big5 && CP 950 && Hong Kong Supplementary Character Set
//		  Entensions to Big5 encoding by Hong Kong goverment.
//
// IlEucTw	  EUC-TW && CNS11643
//		  Extended Unix Code for Traditional Chinese.
//
// IlHpRoman8	  hp-roman8
//		  HP specific
//
// IlIbm850	  IBM850
//		  IBM specific + CP 850
//
// IlWindows1250  windows-1250
//		  Windows 3.1 eastern europen languages.
//
// IlWindows1251  windows-1251
//		  Windows 3.1 Cyrillic
//
// IlWindows1252  windows-1252
//		  Windows 3.1 US (ANSI)
//
// IlWindows1253  windows-1253
//		  Windows 3.1 Greek
//
// IlWindows1254  windows-1254
//		  Windows 3.1 Turkish
//
// IlWindows1255  windows-1255
//		  Hebrew
//
// IlWindows1256  windows-1256
//		  Arabic
//
// IlWindows1257  windows-1257
//		  Baltic
//
// IlWindows1258  windows-1258
//		  Vietnamese
// 
// IlUtf8         Unicode UTF-8
//
// IlIsoLatinThai ISO-8859-11 (also called LatinThai)
//                Similar to tis620 on Unix.
//
// IlIsoLatin7    ISO-8859-13: Baltic Rim
//                Latin7 is going to cover the Baltic Rim and re-establish 
//                the Latvian (lv) support lost in Latin6 and may introduce 
//                the local quotation marks. It resembles WinBaltic.
//
// IlIsoLatin8    ISO-8859-14: Celtic
//                Latin8 adds the last Gaelic and Welsh (cy) letters to 
//                Latin1 to cover all Celtic languages.
//
// IlIsoLatin9    ISO-8859-15
//                The new Latin9 nicknamed Latin0 aims to update Latin1 by 
//                replacing the less needed symbols ¦¨´¸¼½¾ with forgotten
//                French and Finnish letters and placing the U+20AC Euro sign 
//                in the cell =A4 of the former international currency sign 
//                ¤.Similar to Latin1 with euro and oe ligature.
//
// IlWindows949   windows-949
//                Korean(Wansung) on PC.
//
// IlWindows874   windows-874
//                Thai on PC.
//
// IlGBK          Extension to the GB 2312-80 character set "Kuo Zhan", 
//                defined as a normative annex of GB13000.1-93 for Simplified
//                Chinese.
//
// IlDecKanji     DEC Kanji for Japanese.
//
// IlDecKorean    DEC Korean for Korean.
//
// IlDecHanzi     DEC Hanzi for Simplified Chinese.
//
// IlDecHanyu     DEC Hanyu for Traditional Chinese.
//

typedef enum IlEncoding {
    IlNoEncoding=0,	 // No encoding defined or supported
    IlUsAscii=1,	 // US-ASCII (ISO-646): ASCII
    IlIsoLatin1,	 // ISO-8859-1: western european languages && CP 1252
    IlIsoLatin2,	 // ISO-8859-2: eastern europen languages
    IlIsoLatin3,	 // ISO-8859-3
    IlIsoLatin4,	 // ISO-8859-4
    IlIsoLatinCyrillic,	 // ISO-8859-5: Cyrillic 
    IlIsoLatinArabic,	 // ISO-8859-6: Arabic 
    IlIsoLatinGreek,	 // ISO-8859-7: Greek
    IlIsoLatinHebrew,	 // ISO-8859-8: Hebrew 
    IlIsoLatin5,	 // ISO-8859-9: Turkish && CP 1254
    IlIsoLatin6,	 // ISO-8859-10
    IlEucJP,		 // EUC-JP: Extended Unix Code for Japanese
    IlShiftJIS,	         // Shift_JIS (CP 932) for Japanese
    IlEucKR,		 // EUC-KR: Extended Unix Code for Korean
    IlGb2312,		 // GB2312: Simplified chinese (PRC) (CP 936)
    IlBig5,		 // Big5: Chinese for Taiwan Multi-byte set (CP 950)
    IlBig5HKSCS,         // Big5 + Hong Kong Supplementary Character Set
    IlEucTW,             // EUC-TW (cns11643) Traditional Chinese
    // Hp specific
    IlHpRoman8,	         // hp-roman8
    // IBM specific
    IlIbm850,		 // IBM850 and CP 850 for european languages
    // Windows specific
    IlWindows1250,	 // windows-1250: CP 1250 for easten european languages
    IlWindows1251,	 // windows-1251: CP 1251 for Cyrillic
    IlWindows1252,	 // ISO-8859-1-Windows-3.1-Latin-1 or 
			 // ISO-8859-1-Windows-3.0-Latin-1 : CP 1252 depend 
			 // on the Windows version. We will call it 
			 // windows-1252 as it should become an alias in IANA.
			 // For western european languages.
    IlWindows1253,	 // windows-1253: CP 1253 for Greek
    IlWindows1254,	 // windows-1254: CP 1254 for Turkish (superset of 
			 // ISO-8859-9)
    IlWindows1255,	 // windows-1255: CP 1255 for Hebrew
    IlWindows1256,	 // windows-1256: CP 1256 for Arabic
    IlWindows1257,	 // windows-1257: CP 1257 for Baltic
    IlWindows1258,	 // windows-1258: CP 1258 for Vietnamese
    IlUtf8,              // Unicode UTF-8
    IlIsoLatinThai,      // ISO-8859-11: Thai (= tis 620)
    IlIsoLatin7,         // ISO-8859-13: Baltic Rim
    IlIsoLatin8,         // ISO-8859-14: Celtic
    IlIsoLatin9,         // ISO-8859-15: Latin1 with Euro
    IlWindows949,        // windows-949: CP 949 for Korean (Wansung)
    IlWindows874,        // windows-874: CP 874 for Thai
    IlGBK,               // Extension for Simplified Chinese
    IlDecKanji,          // DEC Kanji for Japanese
    IlDecKorean,         // DEC Korean for Korean
    IlDecHanzi,          // DEC Hanzi for Simplified Chinese
    IlDecHanyu           // DEC Hanyu for Traditional Chinese
} _IlEncoding;


typedef enum IlEncodingCompat {
    IlNotCompat,
    IlFullCompat,
    IlLooseCompat
} _IlEncodingCompat;

class ILOG_EXPORTED IlLocaleExtension;

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlExtensionList
{
public:
    //
    // CONSTRUCTORS.
    //
    IlExtensionList();
    ~IlExtensionList();

    //
    // ACCESSORS.
    //
    IlLocaleExtension* find(int) const;

    //
    // MODIFIERS.
    //
    void		add(IlLocaleExtension*);
    void		remove(IlLocaleExtension*);

protected:

private:
    // The two following functions must not be defined, because only
    // one instance is allowed. These declarations prevent the compiler
    // to generate them by default.
    IlExtensionList(const IlExtensionList&);
    IlExtensionList& operator=(const IlExtensionList&);

    //
    // DATA MEMBERS.
    //
    IlLocaleExtension** _list;
    IlUShort		_count;
    IlUShort		_max;
};

// --------------------------------------------------------------------------
typedef enum IlCategory {
    IlAll		= LC_ALL,
    IlCollate		= LC_COLLATE,
    IlCtype		= LC_CTYPE,
    IlMonetary		= LC_MONETARY,
    IlNumeric		= LC_NUMERIC,
    IlTime		= LC_TIME,
#if defined(WINDOWS)
    IlMessages		= 6
#else /* !WINDOWS */
    IlMessages		= LC_MESSAGES
#endif /* WINDOWS */
} _IlCategory;

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlLocaleCatDescriptor
{
public:
    //
    // CONSTRUCTORS.
    //
    IlLocaleCatDescriptor();

    //
    // ACCESSORS.
    //
    inline const char*	getSystemLocaleName() const
			{
			    return _systemLocaleName;
			}
    inline IlBoolean	isStandard()     const { return _isStd; }
    inline const char*	getStdLangTerr() const { return _stdLangTerr; }
    inline IlEncoding	getEncoding()    const { return _stdEncoding; }

    //
    // MODIFIERS.
    //
    IlBoolean		setSystemLocaleName(const char*);
    // MUST not be called with NULL.

    IlBoolean		standardize();

    // Convenience functions.
    char*		getStdLocaleName();

protected:

private:
    //
    // DATA MEMBERS.
    //
    char*	_systemLocaleName; // System dependent locale category name.
    IlBoolean	_isStd;		   // Can this be standardized?
    char*	_stdLangTerr;	   // POSIX based locale category name
				   // composed of Language et Territory.
    IlEncoding	_stdEncoding;

public:
    // The destructor.
    ~IlLocaleCatDescriptor();

    // MODIFIERS. Use wih caution.
    void		setStdLangTerr(const char*, IlEncoding);
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlLocale
{
public:
    //
    // CONSTRUCTORS.
    //
    IlLocale(const char* = 0);

    //
    // ACCESSORS.
    //
    inline IlBoolean	isBad() const		 { return _bad; }
    inline const char*	getSystemCodeset() const { return _systemCodeset; }
    inline IlEncoding	getEncoding() const	 { return _encoding; }
    inline IlUShort	getMaxCharSize() const	 { return _maxCharSize; }
    IlEncodingCompat	isEncodingCompatible(IlEncoding encoding) const;

    // The following functions are handles to the IlCatDescriptor functions.
    inline const char*	getSystemLocaleName(IlCategory ctg = IlCtype) const
			{
			    return getCategory(ctg)
				? getCategory(ctg)->getSystemLocaleName()
				: 0; 
    }
    inline IlBoolean	isStandardLocale(IlCategory ctg = IlCtype) const
			{
			    return getCategory(ctg)
				? getCategory(ctg)->isStandard()
				: IlFalse;
			}
    inline const char*	getStdLangTerr(IlCategory ctg = IlCtype) const
			{
			    return getCategory(ctg)
				? getCategory(ctg)->getStdLangTerr()
				: 0;
			}
    inline IlEncoding	getEncoding(IlCategory ctg) const
			{
			    return getCategory(ctg)
				? getCategory(ctg)->getEncoding()
				: IlNoEncoding;
			}
    inline char*	getStdLocaleName(IlCategory ctg = IlCtype) const
			{
			    return getCategory(ctg)
				? getCategory(ctg)->getStdLocaleName()
				: 0;
			}

    virtual IlCalendar::EDaysOfWeek	getFirstDayOfWeek() const;
    virtual IlUChar	getMinimalDaysInFirstWeek() const;

    //
    // MODIFIERS.
    //
    IlBoolean		setSystemLocaleName(const char*,
					    IlBoolean = IlFalse,
					    IlCategory = IlAll);
    void		addExtension(IlLocaleExtension*);
    void		removeExtension(IlLocaleExtension*);
    IlBoolean		setEncoding();
    inline void		lock() { ++_refCount; }
    inline void		unlock() { if (!--_refCount) delete this; }

    //
    // STATIC.
    //
    static IlLocale*	Get(IlBoolean = IlFalse, const char* = 0);
    static IlEncoding	GetIlEncoding(const char* encodingName);
    static const char*	GetEncodingName(IlEncoding encoding);
    static char*	GetStdLocaleName(const char* localeName);

protected:

private:
    // The two following functions must not be defined, because only
    // one instance is allowed. These declarations prevent the compiler
    // to generate them by default.
    IlLocale(const IlLocale&);
    IlLocale& operator=(const IlLocale&);

    void		setMaxCharSize();

    //
    // DATA MEMBERS.
    //
    IlBoolean		_bad;
    // LC_CTYPE
    IlLocaleCatDescriptor* _ctype;      // LC_CTYPE description (locale the 
                                        // program runs into).
    char*		_systemCodeset;	// returned by nl_langinfo
    IlEncoding		_encoding;	// IANA registered, used internally
    IlUShort		_maxCharSize;	// Max number of bytes per character.

    // LC_MESSAGES
    IlLocaleCatDescriptor* _messages;	// LC_MESSAGES description

    IlExtensionList	_extensions;	// Locale extensions.
    IlUShort		_refCount;	// Reference counter.
    static IlLocale*	_Locale;	// Current instance.
    static IlLocale**	_LocaleList;	// Array of locales.
    static IlUShort	_LocaleNumber;	// Number of locales.
    static IlUShort	_MaxLocaleNumber; // Size of the array of locales.

public:
    virtual ~IlLocale();

    IlLocaleExtension*	getExtension(int) const;
    IlLocaleCatDescriptor*	getCategory(IlCategory) const;

    // Modifiers
    void		setDefaultLocale();
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlLocaleExtension
{
public:
    //
    // CONSTRUCTORS.
    //
    IlLocaleExtension(IlLocale*);
    virtual ~IlLocaleExtension();

    //
    // ACCESSORS.
    //
    virtual int		getType() const;
    inline IlBoolean	isBad() const	{ return _bad; }
    inline IlLocale*	getLocale() const { return _locale; }
    // The following functions are handles to the IlLocale functions.
    inline const char*	getSystemCodeset() const
			{
			    return _locale->getSystemCodeset();
			}
    inline IlEncoding	getEncoding() const { return _locale->getEncoding(); }
    inline IlUShort	getMaxCharSize() const
			{
			    return _locale->getMaxCharSize();
			}
    inline const char*	getSystemLocaleName(IlCategory ctg = IlCtype) const
			{
			    return _locale->getSystemLocaleName(ctg);
			}
    inline IlBoolean	isStandardLocale(IlCategory ctg = IlCtype) const
			{
			    return _locale->isStandardLocale(ctg);
			}
    inline const char*	getStdLangTerr(IlCategory ctg = IlCtype) const
			{
			    return _locale->getStdLangTerr(ctg);
			}
    inline IlEncoding	getEncoding(IlCategory ctg) const
			{
			    return _locale->getEncoding(ctg);
			}
    inline char*	getStdLocaleName(IlCategory ctg = IlCtype) const
			{
			    return _locale->getStdLocaleName(ctg);
			}
    inline IlEncodingCompat	isEncodingCompatible(IlEncoding enc) const
				{
				    return _locale->isEncodingCompatible(enc);
				}

    //
    // MODIFIERS.
    //
    inline void		lock() { ++_refCount; }
    inline void		unlock() { if (!--_refCount) delete this; }
    // The following functions are handles to the IlLocale functions.
    inline IlBoolean	setSystemLocaleName(const char*	ln,
					    IlBoolean	doIt = IlFalse,
					    IlCategory 	c = IlAll)
			{
			    return _locale->setSystemLocaleName(ln, doIt, c);
			}
    inline IlBoolean	setEncoding() { return _locale->setEncoding(); }

    //
    // STATIC.
    //
    // The following functions are handles to the IlLocale functions.
    inline static IlEncoding	GetIlEncoding(const char* encName)
				{
				    return IlLocale::GetIlEncoding(encName);
				}
    inline static const char*	GetEncodingName(IlEncoding enc)
				{
				    return IlLocale::GetEncodingName(enc);
				}
    inline static char*		GetStdLocaleName(const char* locName)
				{
				    return IlLocale::GetStdLocaleName(locName);
				}

protected:
    //
    // MODIFIERS.
    //
    virtual IlBoolean	init() = 0;
    inline void		setType(IlUShort t) { _type = t; }

    //
    // DATA MEMBERS.
    //
    IlBoolean		_bad;
    IlLocale*		_locale;	// Pointer to the core locale.
    IlUShort		_type;		// Defined in each IlLocaleExtension 
    					// subclass.

private:
    // The two following functions must not be defined, because only
    // one instance is allowed. These declarations prevent the compiler
    // to generate them by default.
    IlLocaleExtension(const IlLocaleExtension&);
    IlLocaleExtension& operator=(const IlLocaleExtension&);

    //
    // DATA MEMBERS.
    //
    IlUShort		_refCount;

};

// --------------------------------------------------------------------------
// locale independant string from/to double conversion functions.
// these functions always assume 

ILOG_EXPORTEDFUNCTION(int)		IlDoubleToString(char*       buf,
							 double      val,
							 const char* fmt = 0);
ILOG_EXPORTEDFUNCTION(IlBoolean)	IlStringToDouble(const char* str,
							 char*&      endptr,
							 double&     res);

// Convenient replacement for atof()
inline double
IlA2D(const char* s)
{
    char* endptr;
    double d;
    IlStringToDouble(s, endptr, d);
    return d;
}

// --------------------------------------------------------------------------
ILOG_EXPORTEDFUNCTION(IlLocale*) IlSetLocale(const char* = 0);

#endif /* !__Il_Locale_H */
