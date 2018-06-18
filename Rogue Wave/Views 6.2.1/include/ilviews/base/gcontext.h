// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/gcontext.h
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
// Encapsulation of the IlGlobalContext class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Gcontext_H
#define __Ilv_Base_Gcontext_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Pathlist_H)
#include <ilviews/base/pathlist.h>
#endif
#if !defined(__Il_Gcontext_H)
#include <ilog/gcontext.h>
#endif

class IlvDisplay;
class IlvLocaleExtension;
typedef void (* IlvGlobalContextDisplayCallback)(IlvDisplay*, IlAny);
IL_DEFINEFPTRTOANYCAST(IlvGlobalContextDisplayCallback);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvGlobalContext
{
public:
    // Member function to have a Singleton.
    static IlvGlobalContext&	GetInstance();

    // Gets the displays list.
    const IlAList&	getDisplays() const;
    // Gets the display from an internal.
    IlvDisplay*		getDisplay(IlAny) const;
    IlPathList const&	getModulePath() const;

    inline const IlPathName&	getHome() const { return _home; }

    IlvLocaleExtension*	getLocale() const;
    void		setLocale(IlLocaleExtension* ext);

    // Delegated to IlGlobalContext
    inline IlSymbol*	findSymbol(const char* s) const
			{
			    return _context.findSymbol(s);
			}
    inline IlBoolean	getValue(IlAny& v, IlAny k, IlAny s = 0) const
			{
			    return _context.getValue(v, k, s);
			}
    inline IlBoolean	addValue(IlAny v, IlAny k, IlAny s = 0)
			{
			    return _context.addValue(v, k, s);
			}
    inline IlBoolean	removeValue(IlAny v, IlAny k, IlAny s = 0)
			{
			    return _context.removeValue(v, k, s);
			}
    inline IlBoolean	replaceValue(IlAny v, IlAny k, IlAny s = 0)
			{
			    return _context.replaceValue(v, k, s);
			}
    inline void		addExitCallback(IlExitCallback c)
			{
			    _context.addExitCallback(c);
			}
    inline void		removeExitCallback(IlExitCallback c)
			{
			    _context.removeExitCallback(c);
			}
    inline void		addFreeCallback(IlFreeCallback c)
			{
			    _context.addFreeCallback(c);
			}
    inline void		removeFreeCallback(IlFreeCallback c)
			{
			    _context.removeFreeCallback(c);
			}
    inline static IlGlobalContext::Error GetError()
			{
			    return IlGlobalContext::GetError();
			}

    static const char*	ProductShortName();
    static const char*	LegacyProductShortName();

protected:
    friend class IlvDisplay;
    // Adds a display (should be called only by IlvDisplay).
    void		addDisplay(IlAny, IlvDisplay*);
    // Removes a display (should be called only by IlvDisplay).
    void		removeDisplay(IlvDisplay*);

    void	addDisplayCreationCallback(IlvGlobalContextDisplayCallback,
					   IlAny userArg = 0);
    void	removeDisplayCreationCallback(IlvGlobalContextDisplayCallback,
					      IlAny userArg = 0);
    void	addDisplayDestructionCallback(IlvGlobalContextDisplayCallback,
					      IlAny userArg = 0);
    void removeDisplayDestructionCallback(IlvGlobalContextDisplayCallback,
					  IlAny userArg = 0);
#if defined(_AIX) || (defined(__alpha) && !defined(WIN32)) || defined(_MSC_VER) || defined(__BORLANDC__) || defined(__GNUC__)
public:
#endif /* _AIX || Alpha OSF || Microsoft C++ || Borland || __GNUC__ */
    // The destructor.
    virtual	~IlvGlobalContext();

private:
    IlvGlobalContext();
    // The two following functions must not be defined, because only
    // one instance is allowed. These declarations prevent the compiler
    // to generate them by default.
    IlvGlobalContext(const IlvGlobalContext&);
    IlvGlobalContext& operator=(const IlvGlobalContext&);

    void		initializeHomePath();
    void		initializeModulePath();

    IlGlobalContext&	_context;
    IlAList*		_displays;
    IlAList*		_displayCreationCbs;
    IlAList*		_displayDestructionCbs;
    IlPathName		_home;
};

#define IlvExitCallback IlExitCallback
#define IlvFreeCallback IlFreeCallback

#define ILVGLOBALCONTEXT IlvGlobalContext::GetInstance()

#endif /* !__Ilv_Base_Gcontext_H */
