// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/proto.h
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
// Declaration of the IlvPrototype class
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Proto_H
#define __Ilv_Protos_Proto_H

#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Protos_Group_H)
#include <ilviews/protos/group.h>
#endif

// ---------------------------------------------------------------------------
// Aliases for compatibility.
//
// NOTE: the names "IlvModel" and "IlvInstance" must still be changed
//	 in ".ivp" and ".ilv" files.
// ---------------------------------------------------------------------------

#define IlvModel		IlvPrototype
#define IlvInstance		IlvProtoInstance
#define IlvAbstractModelLibrary	IlvAbstractProtoLibrary
#define IlvModelLibrary		IlvProtoLibrary
#define createInstance		clone

// ---------------------------------------------------------------------------
// IlvPrototype		A prototype 8^)
// ---------------------------------------------------------------------------
class IlvProtoInstance;
class IlvPrototype;
class IlvAbstractProtoLibrary;

typedef void (*IlvPrototypeFunction)(IlvPrototype* prototype, IlAny arg);

class ILVPROEXPORTED IlvPrototype : public IlvGroup
{
    friend class IlvProtoInstance;
    friend class IlvAbstractProtoLibrary;
    friend class IlvProtoLibrary;

public:
    IlvPrototype(const char* name);
    IlvPrototype(IlvGroup& group);
    IlvPrototype(const IlvPrototype& prototype);
    virtual ~IlvPrototype();

    IlBoolean		update(const IlvGroup& group);

    virtual IlvGroup*	copy(IlBoolean shared) const;

    virtual void	setName(const char* name);

    // Instances: _________________________________________________
    IlvProtoInstance*	clone(const char* name = 0);
    void		deleteInstance(IlvProtoInstance* instance);
    IlvProtoInstance*	nextInstance(IlAny& link) const;
    IlvProtoInstance*	getInstance(const char* name) const;

    // Default values: ____________________________________________
    void		addValues(IlvValueArray* values);
    void		setValues(IlvValueArray* values);
    inline
    IlvValueArray*	getValues() { return(_values); }

    // Prototype updating: ________________________________________
    void		saveInstanceValues(IlvValueArray*& values);

    void		updateInstances(IlvValueArray* vals);

    virtual
    ILVSTDPREF istream* getNodesInputStream(const char* suffix,
					    IlvDisplay* display,
					    const char* path = 0);
    virtual
    ILVSTDPREF ostream* getNodesOutputStream(const char* suffix,
					     const char* path = 0);

    const char*		getFileName();

    IlvAbstractProtoLibrary*	getLibrary();

    static
    IlvPrototype*	GetPrototype(const char* name);

    static void		ApplyToPrototypes(IlvPrototypeFunction f,
					  IlAny arg = 0);

    DeclareGroupInfo();
protected:
    IlvList			_instances;
    IlUInt			_index;
    IlvValueArray*		_values;
    IlvAbstractProtoLibrary*	_library;

    // Undocumented methods: ______________________________________
    void		addInstance(IlvProtoInstance* instance);

    virtual void	readValues(IlvValueArray*&    values,
				   IlvGroupInputFile& f,
				   IlvDisplay*        display);
    virtual void	writeValues(IlvGroupOutputFile& f) const;

    void		setLibrary(IlvAbstractProtoLibrary* library);

    static void		SetLibraryHook(IlvGroupFile&        file,
				       IlvGroupFileHookType type,
				       IlvGroup*            group,
				       IlvGroupNode*        node,
				       IlAny                arg);

    virtual IlBoolean	deleteWhenEmpty();

    static void		AddPrototype(IlvPrototype* prototype,
				     const char*   name);

    static IlvAList	PrototypesByName;

    virtual IlAny	getAccessorCache() const;
    virtual void	setAccessorCache(IlAny);
};

extern ILVPROEXPORTEDFUNCTION(IlvPrototype*)
    IlvGetPrototype(const char* name);

extern ILVPROEXPORTEDFUNCTION(IlvPrototype*)
    IlvLoadPrototype(const char* name,
		     IlvDisplay* display,
		     IlBoolean reload = IlFalse);

#define IlvChangePrototype(prototype, recreate, exp) \
	{ \
	      IlvValueArray* valuesp; \
	      prototype->saveInstanceValues(valuesp); \
	      exp \
	      prototype->updateInstances(valuesp, recreate); \
	}

// ---------------------------------------------------------------------------
// IlvProtoInstance	  A group that is an instance of an IlvPrototype.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvProtoInstance : public IlvGroup
{
    friend class IlvPrototype;

public:
    IlvProtoInstance(const IlvProtoInstance& source);
    virtual ~IlvProtoInstance();

    virtual IlvGroup*	copy(IlBoolean shared) const;
    inline IlvPrototype* getPrototype() const { return _prototype; }
    IlUInt		getModifiedValues(IlvValueArray& diffs,
					  IlBoolean      any = IlFalse) const;

    virtual IlBoolean	deleteWhenEmpty();

    IlBoolean		update(const IlvGroup&);

    DeclareGroupInfo();

protected:
    IlvPrototype*	_prototype;

    IlvProtoInstance(IlvPrototype* prototype, const char*   name);

    virtual void	writeValues(IlvGroupOutputFile& f) const;
    virtual void	writeNodes(IlvGroupOutputFile& f) const;
    virtual void	writeAccessors(IlvGroupOutputFile& f) const;

    virtual IlAny	getAccessorCache() const;
    virtual void	setAccessorCache(IlAny);
    virtual void	refreshAccessorCache();
};

// Accessor names
//
#define IlvPrototypeValue "prototype"

// ---------------------------------------------------------------------------
// IlvAbstractProtoLibrary	Package a set of prototypes together.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvAbstractProtoLibrary
{
    friend class IlvGroup;
    friend class IlvPrototype;
    friend class IlvProtoInstance;

public:
    IlvAbstractProtoLibrary(IlvDisplay* display, const char* name = 0);
    virtual ~IlvAbstractProtoLibrary();
    inline const char*	getName() const { return(_name ? _name : "Unnamed"); }
    void		setName(const char* name);

    static IlBoolean	LoadAll;
    virtual IlBoolean	load(ILVSTDPREF istream* stream = 0,
			     IlBoolean           loadPrototypes =
			     IlvAbstractProtoLibrary::LoadAll) = 0;
    virtual IlBoolean	save(ILVSTDPREF ostream* stream = 0,
			     IlBoolean           savePrototypes =
			     IlvAbstractProtoLibrary::LoadAll) = 0;

    IlBoolean		loadAllPrototypes();
    IlBoolean		saveAllPrototypes();

    void		addPrototype(const char* name);
    void		addPrototype(IlvPrototype* prototype);
    IlBoolean		replacePrototype(IlvPrototype* oldPrototype,
					 IlvPrototype* newPrototype);
    IlBoolean		renamePrototype(IlvPrototype* prototype,
					const char*   newName);
    virtual void	movePrototypeBefore(IlvPrototype*, IlvPrototype*);
    void		removePrototype(IlvPrototype* prototype);
    IlUInt		getPrototypeCount();
    IlvPrototype*	getPrototype(const char* name,
				     IlBoolean   reload = IlFalse);
    IlvPrototype**	getPrototypes(IlUInt& count);

    IlvPrototype*	findPrototype(const char* name);

    virtual IlBoolean	savePrototype(IlvPrototype* prototype) = 0;

    virtual
    const char*		getBitmapFileName(IlvPrototype* prototype) = 0;

    static
    IlvAbstractProtoLibrary*	GetLibrary(const char* name);
    static
    IlvAbstractProtoLibrary**	GetAllLibraries(IlUInt& count); 
    static void		SetAutoLoadMode(IlBoolean loadAll);

protected:
    IlvDisplay*		_display;
    char*		_name;
    IlvAList		_prototypes;

    virtual
    ILVSTDPREF istream* getNodesInputStream(const char* name,
					    const char* suffix);
    virtual
    ILVSTDPREF ostream* getNodesOutputStream(const char* name,
					     const char* suffix);
    virtual const char* getPrototypeFileName(IlvPrototype* prototype) = 0;
    virtual void	prototypeDeleted(IlvPrototype* prototype);
    virtual
    IlvPrototype*	loadPrototype(const char* name) = 0;
    void		setString(char*&      curString,
				  const char* newString,
				  char**      pString = 0);
    void		addLibrary();
    void		removeLibrary();
};

extern ILVPROEXPORTEDFUNCTION(IlvAbstractProtoLibrary*)
    IlvGetProtoLibrary(const char* name);

typedef void (*IlvProtoLibraryLoadCallback)(IlvAbstractProtoLibrary* lib,
					    IlAny arg);

extern ILVPROEXPORTEDFUNCTION(void)
    IlvSetProtoLibraryLoadCallback(IlvProtoLibraryLoadCallback cb, IlAny arg);

// ---------------------------------------------------------------------------
// IlvProtoLibrary	Prototype library which stores/loads prototypes
//			to/from standard files, using the IlvDisplay's path.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvProtoLibrary : public IlvAbstractProtoLibrary
{
    friend class IlvGroup;
    friend class IlvPrototype;
    friend class IlvProtoInstance;

public:
    IlvProtoLibrary(IlvDisplay* display,
		    const char* name = 0,
		    const char* path = 0);
    ~IlvProtoLibrary();
    inline const char*	getPath() { return(_path); }
    void		setPath(const char* path);

    virtual IlBoolean	load(ILVSTDPREF istream* stream = 0,
			     IlBoolean           loadPrototypes = IlTrue);
    virtual IlBoolean	save(ILVSTDPREF ostream* stream = 0,
			     IlBoolean           savePrototypes = IlTrue);
    virtual IlBoolean	savePrototype(IlvPrototype* prototype);

    virtual const char* getBitmapFileName(IlvPrototype* prototype);
    static IlBoolean	GetSingleFileMode();
    static void		SetSingleFileMode(IlBoolean singleFile);

protected:
    static IlBoolean	SingleFileMode;

    virtual
    IlvPrototype*	loadPrototype(const char* name);

    virtual
    ILVSTDPREF istream* getNodesInputStream(const char* name,
					    const char* suffix);
    virtual
    ILVSTDPREF ostream*	getNodesOutputStream(const char* name,
					     const char* suffix);
    virtual void	removeStream(const char*, const char*);

    virtual const char* getPrototypeFileName(IlvPrototype* prototype);
    void		prototypeDeleted(IlvPrototype* prototype);

    ILVSTDPREF ostream* addFileBlock(const char* name);
    ILVSTDPREF istream* getFileBlock(const char* name);
    void		removeFileBlock(const char*);

    void		readFileBlocks(ILVSTDPREF istream* istr);
    void		writeFileBlocks(ILVSTDPREF ostream* ostr);
    void		deleteFileBlocks();

    char*		_path;
    IlBoolean		_singleFile;
    IlvAList		_fileBlocks;
    IlBoolean		_savingAll;
};

extern ILVPROEXPORTEDFUNCTION(void)
    IlvInitProtoPath(IlvDisplay* display);

// ---------------------------------------------------------------------------
// Static initialization of module.
IlvDECLAREINITPROCLASS(proto)

#endif /* __Ilv_Protos_Proto_H */
