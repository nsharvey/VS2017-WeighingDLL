// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/registry.h
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
// Declaration of the IlvDvRegistryKey class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Registry_H)
#define __Ilv_Appframe_Registry_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif

class IlvDvStringArray;
class IlvDvApplication;
class IlvDvValue;
// --------------------------------------------------------------------------
// IlvDvRegistryKey class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvRegistryKey : public IlvDvSerializable
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvRegistryKey(const char* = 0);
    IlvDvRegistryKey(const IlvDvRegistryKey&);
    virtual ~IlvDvRegistryKey();

    // ----------------------------------------------------------------------
    // Main operations
    IlUInt		getKeys(IlvDvStringArray&) const;
    void		setKeys(const char*, ...);
    void		setKeys(const IlvDvStringArray&);
    void		setKey(const char*);

    // ----------------------------------------------------------------------
    // Operators
    IlvDvRegistryKey& operator	+=(const IlvString&);
    IlvDvRegistryKey& operator	=(const IlvDvRegistryKey&);
    IlvDvRegistryKey& operator	=(const IlvString&);

    static const char*	_KeySeparator;

protected:
    IlvDvStringArray	_keys;
};

// --------------------------------------------------------------------------
// IlvDvRegistryProcessor class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvRegistryProcessor
: public IlvDvSerializable {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvRegistryProcessor(const IlvString& root,
			   const char* profileName = 0);

    ~IlvDvRegistryProcessor();

    // ----------------------------------------------------------------------
    // Main operations
    IlBoolean		writeRegistry(const IlvDvRegistryKey&,
				      const char* subKey,
				      const IlvDvValue&) const;
    IlBoolean		readRegistryInt(const IlvDvRegistryKey&,
					const char* subKey,
					int&,
					int defaultValue = 0) const;
    IlBoolean		readRegistryString(const IlvDvRegistryKey&,
					   const char* subKey,
					   IlvString&,
					   const char* defaultValue = 0) const;
    IlBoolean		getRegistryKeys(const IlvDvRegistryKey&,
					const char* subKey,
					IlvDvStringArray&) const;
    IlBoolean		writeRegistryKeys(const IlvDvRegistryKey&,
					  const char* subKey,
					  const IlvDvStringArray&) const;
    IlBoolean		delRegistryTree(const IlvDvRegistryKey&,
					const char* subKey);
    void		unregisterAll();

    // ----------------------------------------------------------------------
    // Basic informations
    inline void		setRootName(const char* name) { _rootName = name; }
    inline
    const IlvString&	getRootName() const { return _rootName; }
    inline void		setProfileName(const char* name)
			{
			    _profileName = name;
			}
    inline
    const IlvString&	getProfileName() const { return _profileName; }

protected:
    IlvString		_rootName;
    IlvString		_profileName;

    IlAny		getSystemRegistryKey(const IlvDvRegistryKey&) const;
    IlAny		geRootSystemRegistryKey() const;
    void		unuseSystemRegistry(IlAny) const;
    IlBoolean		systemRegistryAvaible(IlAny) const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(registry);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Registry_H */
