// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/string.h
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
// Declaration of the string class
// --------------------------------------------------------------------------
#ifndef __Il_String_H
#define __Il_String_H

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif /* !__Il_Macros_H */
#if !defined(__Il_Iostream_H)
#  include <ilog/iostream.h>
#endif
#if defined(IL_STD)
#  include <cstddef>
#else  /* IL_STD */
#  include <stddef.h>
#endif /* IL_STD */

class IlInternalString;

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlString
{
    friend ILOG_EXPORTEDFUNCTION(IL_STDPREF istream&)
	operator>>(IL_STDPREF istream&, IlString&);
public:
    // Static data
    // Default formats.
    static const char* DefaultIntegerFormat;
    static const char* DefaultUnsignedIntegerFormat;
    static const char* DefaultShortFormat;
    static const char* DefaultUnsignedShortFormat;
    static const char* DefaultLongFormat;
    static const char* DefaultUnsignedLongFormat;
    static const char* DefaultFloatFormat;
    static const char* DefaultDoubleFormat;

    static const char* EmptyCString;

    // *****************************************************************
    // Constructors.
    // *****************************************************************
    IlString(const char* cstring = 0, int length = -1);
    IlString(const IlString& string);
    //
    // Conversion constructors.
    //
    IL_EXPLICIT IlString(int, const char* = DefaultIntegerFormat);
    IL_EXPLICIT IlString(unsigned int,
			 const char* = DefaultUnsignedIntegerFormat);
    IL_EXPLICIT IlString(short, const char* = DefaultShortFormat);
    IL_EXPLICIT IlString(unsigned short,
			 const char* = DefaultUnsignedShortFormat);
    IL_EXPLICIT IlString(long, const char* = DefaultLongFormat);
    IL_EXPLICIT IlString(unsigned long,
			 const char* = DefaultUnsignedLongFormat);
    IL_EXPLICIT IlString(float, const char* = DefaultFloatFormat);
    IL_EXPLICIT IlString(double, const char* = DefaultDoubleFormat);
    ~IlString();

    //
    // Operators.
    //
    inline IlBoolean	operator==(const IlString& string) const
	{ return equals(string); }
    inline IlBoolean	operator!=(const IlString& string) const
	{ return !equals(string); }
    inline IlBoolean	operator!() const { return isEmpty(); }
    inline IlBoolean	operator<(const IlString& string) const
	{ return (compare(string) < 0) ? IlTrue : IlFalse; }
    inline IlBoolean	operator<=(const IlString& string) const
	{ return (compare(string) <= 0) ? IlTrue : IlFalse; }
    inline IlBoolean	operator>(const IlString& string) const
	{ return (compare(string) > 0) ? IlTrue : IlFalse; }
    inline IlBoolean	operator>=(const IlString& string) const
	{ return (compare(string) >= 0) ? IlTrue : IlFalse; }
    inline		operator const char*() const { return getValue(); }

    //
    // Member functions.
    //
    const char*		getValue() const;
    char*		copyValue() const;
    size_t		getSize() const;
    size_t		getLength() const;
    IlString		getSubString(int start = 0, int end = -1) const;
    int			getIndexOf(const IlString&	subString,
				   int			start = 0,
				   int			subStart = 0,
				   int			subEnd = -1) const;
    int			getLastIndexOf(const IlString&	subString,
				       int		end = -1,
				       int		subStart = 0,
				       int		subEnd = -1) const;
    IlBoolean		startsWith(const IlString& prefix,
				   int             start = 0,
				   int             end = -1) const;
    IlBoolean		endsWith(const IlString& suffix,
				 int start = 0,
				 int end   = -1) const;
    IlBoolean		isEmpty() const;
    IlBoolean		isBlank() const;
    IlBoolean		equals(const IlString&	string,
			       int		start1 = 0,
			       int		end1 = -1,
			       int		start2 = 0,
			       int		end2 = -1) const;
    int			compare(const IlString&	string,
				int		start1 = 0,
				int		end1 = -1,
				int		start2 = 0,
				int		end2 = -1) const;
    int			caseCompare(const IlString&	string,
				    int			start1 = 0,
				    int			end1 = -1,
				    int			start2 = 0,
				    int			end2 = -1) const;
    IlBoolean		matches(const IlString&	pattern,
				int		stringStart  = 0,
				int		stringEnd    = -1,
				int		patternStart = 0,
				int		patternEnd   = -1) const;
    void		writeQuoted(IL_STDPREF ostream& ostr) const;
	// Retuns a pointer to the internal class.
	// This function is intentionally not documented.
    inline IlInternalString*	getInternalString() const
	{ return _internal; }

    // *****************************************************************
    //
    // MODIFIERS.
    //
    // *****************************************************************

    //
    // Operators.
    //
    IlString&		operator=(const IlString& string);
    inline IlString&	operator+=(const IlString& string)
	{ return catenate(string); }

    //
    // Member functions.
    //
    IlString&		catenate(const IlString& string,
				 int start = 0,
				 int end = -1);
    IlString&		prepend(const IlString& string,
				int start = 0,
				int end = -1);
    IlString&		insert(const IlString&	string,
			       int		position = 0,
			       int		start = 0,
			       int		end = -1);
    IlString&		remove(int start = 0, int end = -1);
    IlString&		remove(const IlString&	removed,
			       int		start = 0,
			       int		end = -1);
    IlString&		replace(const IlString&	replacement,
				int		start = 0,
				int		end = -1,
				int		subStart = 0,
				int		subEnd = -1);
    IlString&		substitute(const IlString& target,
				   const IlString& replacement,
				   int		 start = 0,
				   int		 end = -1,
				   int		 targetStart = 0,
				   int		 targetEnd = -1,
				   int		 replacementStart = 0,
				   int		 replacementEnd = -1);
    IlString&		toLower();
    IlString&		toUpper();

    void		readQuoted(IL_STDPREF istream& istr);
private:
    // Constructor from an internal object.
    IlString(IlInternalString*);

    //
    // Modifiers.
    //
    // Reserves an amount of memory for _string (used to be printed).
    // This is reserved for IO operations.
    void		reserve(int);

    IlInternalString*	_internal;
};

// *****************************************************************
//
// Helper functions and operators.
//
// *****************************************************************

#if !defined(__BORLANDC__)
inline IlString
operator+(const IlString& string1, const IlString& string2)
{
    return (IlString(string1) += string2);
}
#else  /* __BORLANDC__ */
extern IlString
operator+(const IlString& string1, const IlString& string2);
#endif /* __BORLANDC__ */

// Other ways to concatenate strings.
inline IlString&
operator<<(IlString& string1, const IlString& string2)
	{ return string1.catenate(string2); }

inline IlString&
operator<<(IlString& string, const char* cstring)
{
    return string.catenate(IlString(cstring));
}

ILOG_EXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream& ostr, const IlString& string);

ILOG_EXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream& istr, IlString& string);

#endif /* !__Il_String_H */
