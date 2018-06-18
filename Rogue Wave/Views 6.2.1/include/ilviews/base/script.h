// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/script.h
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
// Declaration of the IlvScript class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Script_H
#define __Ilv_Base_Script_H

#if !defined(__Ilv_Graphics_Holder_H)
#include <ilviews/graphics/holder.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif

#define DeclareScriptAccessors DeclareGraphicAccessors
class IlvScriptContext;
class IlvScript;
class IlvClassInfo;
class IlvScriptLanguage;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScriptBinderList
{
public:
    static void		Add(const IlSymbol*, IlvValueInterface*);
    static void		Remove(const IlSymbol*);
    static void		Bind(IlvScriptLanguage* language);
    static void		UnBind(IlvScriptLanguage* language);

protected:
    static IlAList*	_Binders;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScriptObjectConstructor : public IlvValueInterface
{
public:
    IlvScriptObjectConstructor();

    virtual void	lock();
    virtual void	unLock();
    IlvDisplay*		getDisplay() const;
    virtual
    IlvValueInterface*	makeObject(IlvDisplay* display,
				   IlvValue*   args) const = 0;
    virtual IlBoolean	checkParameters(const IlvValue& val) const;
    virtual IlBoolean	getConstructorValueDescriptor(IlvValue& val) const = 0;

    static void		GetAccessors(const IlSymbol* const**		a,
				     const IlvValueTypeClass* const**	t,
				     IlUInt&				c);
    virtual IlBoolean	applyValue(const IlvValue& val);
    virtual IlBoolean	getValueDescriptor(IlvValue& val) const;

protected:
    IlUInt		_refCount;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScriptLanguage
{
public:
    virtual ~IlvScriptLanguage();
    // ____________________________________________________________
    inline
    const IlSymbol*	getName() const { return _name; }
    static
    IlvScriptLanguage*	Get(const IlSymbol* name);
    inline static
    IlvScriptLanguage*	Get(const char* name)
			{
			    return Get(IlGetSymbol(name));
			}
    static
    IlvScriptLanguage*	GetDefault();
    static void		Initialize(IlvDisplay*, const IlSymbol* name);
    inline
    static IlAList*	GetAll() { return _languages; }
    virtual
    IlvScriptContext*	getGlobalContext();
    virtual
    IlvScriptContext*	createContext(IlvScriptContext*) = 0;
    virtual const char*	getIncludeFileName() const = 0;
    virtual const char*	getDefaultScriptFilesExtension() const = 0;
    virtual void	languageChanged(const IlvDisplay*) const;
    virtual IlBoolean	isDebugging() const = 0;

    // Static initialization // Binding
    static void		Bind(const IlSymbol*, IlvValueInterface*);
    static void		UnBind(const IlSymbol*, IlvValueInterface*);
    void		bind(const IlSymbol*, IlvValueInterface*);
    void		unBind(const IlSymbol*, IlvValueInterface*);
    inline IlBoolean	hasInitializedBinders() const
			{
			    return _isInitialized;
			}
    void		bindAll();
    void		unBindAll();

    // Access to IlvDisplay
    static IlvDisplay*	GetDisplay();
    static void		SetDisplay(IlvDisplay* display,
				   IlBoolean   fallback = IlFalse);

protected:
    IlvScriptLanguage(const IlSymbol* name);
    inline
    IlvScriptContext*	globalContext() const { return _globalContext; }

private:
    IlvScriptLanguage(const IlvScriptLanguage&); // No copy constructor

    const IlSymbol*	_name;
    IlvScriptContext*	_globalContext;
    IlBoolean		_isInitialized;
    static IlAList*	_languages;
    static IlvDisplay*	_callbackDisplay;
    static IlvDisplay*	_fallbackDisplay;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScriptContext
{
public:
    IlvScriptContext(IlvScriptLanguage* language, IlvScriptContext* parent);
    IlvScriptContext(const IlSymbol* languageName, IlvScriptContext* parent);
    virtual ~IlvScriptContext();
    // ____________________________________________________________
    inline
    IlvScriptLanguage*	getLanguage() const { return _language; }
    inline
    const IlSymbol*	getLanguageName() const { return _languageName; }
    inline
    IlvScriptContext*	getGlobal() const
			{
			    return _language
				? _language->getGlobalContext()
				: 0;
			}
    static
    IlvScriptContext*	GetGlobal(const IlSymbol* languageName = 0);
    inline
    IlvScriptContext*	getParent() const { return _parent; }
    static void		CallScriptCallback(IlvGraphicHolder* holder,
					   IlvGraphic*       graphic,
					   const IlSymbol*   callbackName,
					   const IlSymbol*   languageName,
					   const IlvValue*   userValue);
    virtual IlBoolean	bind(IlvValueInterface*	intf, const char* name);
    virtual IlBoolean	unBind(IlvValueInterface* intf);
    virtual IlBoolean	isBound(const char* name) const;
    virtual IlBoolean	callCallback(const IlSymbol*	func,
				     IlvValueInterface*	graphic,
				     const IlvValue*	data);
    virtual IlBoolean	callFunction(const IlvValue& args);
    virtual IlvScript*	read(IlvInputFile& is,
			     const char*   pathName = 0,
			     IlBoolean     compileIt = IlTrue);
    virtual void	write(IlvOutputFile& os) const;
    IlBoolean		loadScript(const char* fileName,
				   const char* name = 0,
				   IlBoolean   compileIt = IlTrue);
    IlBoolean		attach(const IlvScript* script);
    IlBoolean		attach(IlUInt                  nScripts,
			       const IlvScript* const* scripts);
    IlBoolean		add(const IlvScript* script,
			    IlBoolean        compileIt = IlTrue);
    IlBoolean		add(IlUInt nScripts,
			    const IlvScript* const* scripts,
			    IlBoolean compileThem = IlTrue);
    IlBoolean		insert(IlUInt           rank,
			       const IlvScript* script,
			       IlBoolean        compileIt = IlTrue);
    IlBoolean		remove(IlUInt rank);
    IlBoolean		remove(IlUInt                  nScripts,
			       const IlvScript* const* scripts);
    IlUInt		getCardinal() const;
    IlUInt		getIndex(const IlvScript* script) const;
    IlvScript*		getScript(IlUInt rank) const;
    IlvScript*		getScript(const char* name) const;

protected:
    virtual IlBoolean	compile(const IlvScript* script);
    virtual IlBoolean	compileScripts();
    virtual void	setParent(IlvScriptContext*);
    void		deleteScripts();

private:
    void		addChild(IlvScriptContext*);
    void		removeChild(IlvScriptContext*);

    IlArray		_scripts;
    IlvScriptContext*	_parent;
    IlList		_children;
    IlvScriptLanguage*	_language;
    const IlSymbol*	_languageName;
};

// --------------------------------------------------------------------------
enum IlvScriptType {
    IlvEmptyScript,
    IlvLinkedScript,
    IlvInlineScript
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScript
{
public:
    IlvScript(IlvScriptContext*	context);
    IlvScript(IlvScriptContext*	context,
	      ILVSTDPREF istream&,
	      const char*       filename = 0,
	      const char*       name = 0);
    IlvScript(IlvScriptContext*	context,
	      const char* contents,
	      const char* name = 0,
	      const char* path = 0);
    IlvScript(IlvScriptContext*	context,
	      IlUInt nLines,
	      const char* const* lines,
	      const char* name = 0,
	      const char* path = 0);
    virtual ~IlvScript();

    virtual IlBoolean	load();
    virtual IlBoolean	onLoad(IlvValueInterface*);
    virtual void	write(IlvOutputFile& os) const;
    inline
    IlvScriptContext*	getContext() const { return _context; }
    inline
    IlvScriptLanguage*	getLanguage() const
			{
			    return _context->getLanguage();
			}
    inline
    const IlSymbol*	getLanguageName() const
			{
			    return _context->getLanguageName();
			}
    inline
    IlvScriptType	getType() const { return _type; }
    inline const char*	getName() const { return _name; }
    void		setName(const char* name);
    inline const char*	getPathName() const { return _pathName; }
    void		setPathName(const char* pathName);
    const char* const*	getContentsArray(IlUInt& nLines) const;
    void		setContentsArray(IlUInt             nLines,
					 const char* const* lines);
    const char*		getContents() const;
    void		setContents(const char* contents);
    inline IlBoolean	isPersistent() const { return _persistent; }
    inline void		setPersistent(IlBoolean persistent)
			{
			    _persistent = persistent;
			}
protected:
    IlvScriptContext*	_context;
    IlvScriptType	_type;
    char**		_contents;
    char*		_name;
    char*		_pathName;
    IlBoolean		_persistent;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvScriptFunction : public IlvValueInterface
{
public:
    IlvScriptFunction(IlvScriptContext*		context,
		      const char*		functionName,
		      IlvValueTypeClass*	retType,
		      IlInt			nParams,
		      IlInt			reqParams
#if !defined(ILVBUILDLIBS) && defined(__hpux)
		                        = 0
#endif /* !ILVBUILDLIBS && __hpux */
		      ,
		      ...);
    virtual IlBoolean	call(IlvValue&	retVal,
			     IlInt	count,
			     IlvValue*	args) = 0;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    inline void		setArgumentClassInfo(IlInt		index,
					     IlvClassInfo*	clsinfo)
			{
			    ILVSETARGCLASSINFO(_method, index, clsinfo);
			}
    static void		GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual
    IlvClassInfo*	getClassInfo() const;
    virtual void	lock();
    virtual void	unLock();

    static
    IlvClassInfo*	_classinfo;
    static IlSymbol*	_functionCallMethod;

    virtual IlBoolean	applyValue(const IlvValue& val);
    virtual IlvValue&	queryValue(IlvValue& value) const;
private:
    IlUInt		_refCount;
    IlvValue		_method;
};

ILVVWSMODULEINIT(script);

#endif /* !__Ilv_Base_Script_H */
