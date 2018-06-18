// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/gcontext.h
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
// Declaration of the IlGlobalContext class
// --------------------------------------------------------------------------
#ifndef __Il_Gcontext_H
#define __Il_Gcontext_H

#if !defined(__Il_Pathlist_H)
#  include <ilog/pathlist.h>
#endif
#if !defined(__Il_List_H)
#  include <ilog/list.h>
#endif
#if !defined(__Il_Pathname_H)
#  include <ilog/pathname.h>
#endif

class IlLocaleExtension;
class IlStringHashTable;
class IlSymbol;

typedef void (*IlExitCallback)();
IL_DEFINEFPTRTOANYCAST(IlExitCallback);
typedef void (*IlFreeCallback)();
IL_DEFINEFPTRTOANYCAST(IlFreeCallback);

// --------------------------------------------------------------------------
// IlGlobalContext class
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlGlobalContext
{
public:
    // Member function to have a Singleton.
    static IlGlobalContext& GetInstance();

    enum Error {
	IlGlobalContextErrorNoError,
	IlGlobalContextErrorKeyAlreadyDefined,
	IlGlobalContextErrorWrongScope,
	IlGlobalContextErrorWrongKey,
	IlGlobalContextErrorWrongKeyOrValue
    };
    // Accessors.
    // ----------
    // Finds a symbol from a C string.
    IlSymbol*		findSymbol(const char*) const;
    // Gets the values associated to a scope and a key.
    IlBoolean		getValue(IlAny&, IlAny, IlAny = 0) const;
    inline IlBoolean	hasLocale() const
			{
			    return _locale ? IlTrue : IlFalse;
			}
    // Gets the default locale.
    IlLocaleExtension*	getLocale() const;

    // CPU bit order
    static IlBoolean	IsCPULsb();

    inline const IlPathName&	getHome() const { return _homePath; }

    // MODIFIERS
    // Adds a key and its value, associated to a scope.
    IlBoolean		addValue(IlAny, IlAny, IlAny = 0);
    // Removes a key and its value associated to a scope.
    IlBoolean		removeValue(IlAny, IlAny, IlAny = 0);
    // Replaces a value associated to a scope and a key by a new one.
    IlBoolean		replaceValue(IlAny, IlAny, IlAny = 0);

    // The difference between exit and free callbacks is that the
    // exit callbacks are called at the beginning of the destructor
    // of IlGlobalContext whereas the free callbacks are called
    // at the end of the destructor. The latter ones are typically
    // used to free the resources (memory for example) that are used
    // by low level objects such as hash table, list...
    // Adds an exit callback.
    void		addExitCallback(IlExitCallback);
    // Removes a exit callback.
    void		removeExitCallback(IlExitCallback);
    // Adds a new free callback.
    void		addFreeCallback(IlFreeCallback);
    // Removes a free callback.
    void		removeFreeCallback(IlFreeCallback);
    // Sets the default locale of the application.
    void		setLocale(IlLocaleExtension*);

    inline const IlPathList&	getModulePath() const { return _modulePath; }

    void		addInModulePathList(IlPathName const&);
    void		addInModulePathPostList(IlPathName const&);
    void		addInModulePathPrevList(IlPathName const&);

    static Error	GetError();

protected:
    friend class	IlSymbol;

    // MODIFIERS
    // Adds a new symbol (should be called only by IlSymbol).
    void		addSymbol(IlSymbol*);
    // Removes a symbol (should be called only by IlSymbol).
    void		removeSymbol(IlSymbol*);
    // Gets the compatibility flags.
    inline IlBoolean	getCompatibilityFlag(IlUShort fl) const
	{
	    return ((_compatibilityFlags & ((IlUInt)(1)<<fl))
		    ? IlTrue : IlFalse);
	}
    // Sets a compatibility flag given as a index.
    inline void		setCompatibilityFlag(IlUShort fl)
	{ _compatibilityFlags |= (IlUInt(1) << fl); }
    // Sets a compatibility flag given as a index to a value.
    inline void		setCompatibilityFlag(IlUShort fl, IlBoolean v)
	{
	    IlUInt f = IlUInt(1) << fl;
	    if (v)
		_compatibilityFlags |=  f;
	    else
		_compatibilityFlags &= ~f;
	}
    // Unsets a compatibility flag given as a index.
    inline void		unSetCompatibilityFlag(IlUShort fl)
	{ _compatibilityFlags &= ~(IlUInt(1) << fl); }
    // Inverts a compatibility flag given as a index.
    inline void		invertCompatibilityFlag(IlUShort fl)
	{
	    IlUInt f = IlUInt(1) << fl;
	    if (_compatibilityFlags & f)
		_compatibilityFlags &= ~f;
	    else
		_compatibilityFlags |=  f;
	}
    // The standard constructor. It should be called only the static
    // member function GetInstance.
    IlGlobalContext();
#if defined(_AIX) || (defined(__alpha) && !defined(WIN32)) || \
    defined(_MSC_VER) || defined(__BORLANDC__) || defined(__GNUC__)
public:
#endif /* _AIX || Alpha OSF || Microsoft C++ || Borland || __GNUC__ */
    // Destructor.
     virtual ~IlGlobalContext();
private:
    // The two following functions must not be defined, because only
    // one instance is allowed. These declarations prevent the compiler
    // to generate them by default.
    IlGlobalContext(const IlGlobalContext&);
    IlGlobalContext& operator=(const IlGlobalContext&);

    // This function initializes the homePath member.
    void		initializeHomePath();
    // This function initializes the modulePath member.
    void		initializeModulePath();

    // Data Members.
    IlLocaleExtension*	_locale;
    IlUInt		_compatibilityFlags;
    IlUInt		_behaviourFlags;
    IlSymbol*		_defaultLanguage;
    IlStringHashTable*	_symbols;
    IlAList*		_values;
    IlList*		_exitCallbacks;
    IlList*		_freeCallbacks;
    IlPathName		_homePath;
    IlPathList		_modulePath;
    static Error	_Error;
};

#define IL_GLOBALCONTEXT IlGlobalContext::GetInstance()

#endif /* !__Il_Gcontext_H */
