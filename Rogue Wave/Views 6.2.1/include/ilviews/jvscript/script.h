// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/jvscript/script.h
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
// Definition of the IlvJvScript class
// Defined in library jvscript
// --------------------------------------------------------------------------
#ifndef __Ilv_Jvscript_Script_H
#define __Ilv_Jvscript_Script_H

#if !defined(__Ilv_Base_Script_H)
#include <ilviews/base/script.h>
#endif
#if !defined(__Ilv_Jvscript_Macros_H)
#include <ilviews/jvscript/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class IlvDisplay;
class IlvJvScriptContext;
class IljHValuePtr;

// --------------------------------------------------------------------------
class IlvJvScriptLanguageInternal;

class ILVJSLEXPORTED IlvJvScriptLanguage
    : public IlvScriptLanguage
{
public:
    virtual IlvScriptContext*	createContext(IlvScriptContext*);
    virtual const char*		getIncludeFileName() const;
    virtual const char*		getDefaultScriptFilesExtension() const;
    static IlvJvScriptContext*	GetGlobalContext();
    static IlvJvScriptLanguage*	GetInstance();
    static IlBoolean		InitAuxiliaryLib(IlvDisplay* dsp);
    inline
    IlvJvScriptLanguageInternal* getInternal() const { return _internal; }
    virtual void		languageChanged(const IlvDisplay*) const;
    virtual IlBoolean		isDebugging() const;

protected:
    IlvJvScriptLanguage();

private:
    virtual ~IlvJvScriptLanguage();
    IlvJvScriptLanguageInternal*	_internal;

public:
    static IlvJvScriptLanguage*		_singleton;
    static void Destroy();
    friend class IlvJvScriptLanguageInternal;
};

// --------------------------------------------------------------------------
class IlvJvScriptContextInternal;

class ILVJSLEXPORTED IlvJvScriptContext
    : public IlvScriptContext
{
public:
    IlvJvScriptContext(IlvScriptLanguage*, IlvScriptContext*);
    virtual ~IlvJvScriptContext();

    virtual IlBoolean	bind(IlvValueInterface*, const char* name);
    virtual IlBoolean	isBound(const char*) const;
    virtual IlBoolean	callCallback(const IlSymbol* func,
				     IlvValueInterface* graphic,
				     const IlvValue* data);
    virtual IlBoolean	callFunction(const IlvValue& args);
    inline
    IlvJvScriptContextInternal* getInternal() const { return _internal; }

protected:
    virtual IlBoolean	compile(const IlvScript*);
    virtual IlBoolean	compileScripts();
    IlBoolean		find(const char* name, IljHValuePtr& fun) const;

private:
    IlvJvScriptContextInternal*	_internal;
    IlvArray			_environments;
};

IL_MODULETERM(jvscript, ILVJSLEXPORTED);
#endif /* !__Ilv_Jvscript_Script_H */
