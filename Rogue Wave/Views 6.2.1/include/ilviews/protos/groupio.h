// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/groupio.h
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
// Declaration of the Group Input/Output related classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Groupio_H
#define __Ilv_Protos_Groupio_H

#if !defined(__Ilv_Protos_Value_H)
#include <ilviews/protos/value.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Util_Util_H)
#include <ilviews/util/util.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

class IlvGroup;
class IlvGroupNode;
class IlvGroupFile;
class IlvValueArray;

// ---------------------------------------------------------------------------
// Common I/O string definitions.
// ---------------------------------------------------------------------------
#define IlvGroupEOLString		"\n"
#define IlvGroupEOGString		";"
#define IlvGroupBeginString		"{"
#define IlvGroupEndString		"}"
#define IlvGroupValuesString		"values"
#define IlvGroupAccessorsString		"accessors"
#define IlvGroupNodesString		"nodes"
#define IlvGroupEqualString		"="

// ---------------------------------------------------------------------------
// Type definitions.
// ---------------------------------------------------------------------------
typedef enum IlvGroupFileHookType {
    ILV_GROUP_FILE_PRE_READ,
    ILV_GROUP_FILE_POST_CREATE,
    ILV_GROUP_FILE_POST_READ,
    ILV_GROUP_FILE_PRE_WRITE,
    ILV_GROUP_FILE_POST_WRITE,
    ILV_GROUP_FILE_DELETE
} _IlvGroupFileHookType;

typedef void (*IlvGroupFileHookFunction)(IlvGroupFile& file,
					 IlvGroupFileHookType type,
					 IlvGroup* group,
					 IlvGroupNode* node,
					 IlAny arg);

// ---------------------------------------------------------------------------
// IlvGroupFileHook
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupFileHook
{
public:
    IlvGroupFileHook(IlvGroupFileHookType type,
		     IlvGroupFileHookFunction f,
		     IlAny arg)
    : _type(type),
      _f(f),
      _arg(arg) {}
    // ____________________________________________________________
    IlvGroupFileHookType	_type;
    IlvGroupFileHookFunction	_f;
    IlAny			_arg;
};

// ---------------------------------------------------------------------------
// IlvGroupFile
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupFile
{
    friend class IlvGroup;
    friend class IlvGroupNode;

public:
    IlvGroupFile(const char* path);
    virtual ~IlvGroupFile();

    inline IlAny	getData(IlAny key) { return(_data.get(key)); }
    inline void		setData(IlAny key, IlAny data)
			{
			    _data.append(key, data);
			}
    inline void		clearData(IlAny key, IlAny data)
			{
			    _data.remove(key, data);
			}

    void		addHook(IlvGroupFileHookType type,
				IlvGroupFileHookFunction f,
				IlAny arg = 0);

    IlvGroup*		getCurrentGroup();
    IlvGroup*		getTopGroup();

    inline const char*	getPath() { return _path; }
    void		setPath(const char* path);

    inline IlBoolean	useReferences() { return(_useReferences); }
    inline void		useReferences(IlBoolean useRefs)
			{
			    _useReferences = useRefs;
			}
    inline IlFloat	getVersion() { return _version; }
    // Allows you to write old version files.
    inline void		setVersion(IlFloat v) { _version=v; }

protected:
    IlAList		_data;
    IlList		_hooks;
    IlList		_groups;
    char*		_path;
    IlBoolean		_useReferences;
    IlFloat		_version;

    void		callHooks(IlvGroupFileHookType type,
				  IlvGroup* group = 0,
				  IlvGroupNode* node = 0);

    void		pushGroup(const IlvGroup* group);
    IlvGroup*		popGroup();
};

// ---------------------------------------------------------------------------
// IlvGroupInputFile
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupInputFile : public IlvGroupFile
{
    friend class IlvGroup;
    friend class IlvGroupNode;
    friend class IlvSubGroupNode;

public:
    IlvGroupInputFile(ILVSTDPREF istream& str, const char* path = 0);

    inline
    ILVSTDPREF istream&	getStream() { return *_str; }

    virtual IlvGroup*	readGroup(IlvDisplay* display = 0);

    virtual
    ILVSTDPREF istream*	getNodesInputStream(IlvGroup* group,
					    const char* suffix,
					    IlvDisplay* display);
    virtual
    IlvGroupNode*	readNodeReference();
    IlSymbol*		readValue(IlBoolean allowNull = IlFalse);

protected:
    IlvGroup*		readNext(IlvDisplay* display);
    void		readNodes(IlvGroup* group, IlvDisplay* display);
    void		readSubscriptions(IlvGroup* group);

    ILVSTDPREF istream*	_str;
};

// ---------------------------------------------------------------------------
// IlvGroupOutputFile
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupOutputFile : public IlvGroupFile
{
    friend class IlvGroup;
    friend class IlvGroupNode;
    friend class IlvSubGroupNode;

public:
    IlvGroupOutputFile(ILVSTDPREF ostream& str, const char* path = 0);

    inline
    ILVSTDPREF ostream&	getStream() { return *_str; }
    virtual void	writeGroup(const IlvGroup* group);
    void		writeValues(const IlvValueArray& values);

    inline int		getIndent() const { return(_indent); }
    void		indent();
    void		addIndent(int d);

    virtual
    ILVSTDPREF ostream*	getNodesOutputStream(IlvGroup* group,
					     const char* suffix);
    virtual void	writeNodeReference(const IlvGroupNode* node);
    void		writeValue(const IlSymbol* s);
    void		writeValue(const char* string);

protected:
    void		writeNext(const IlvGroup* group);
    void		writeNodes(const IlvGroup* group);
    void		writeSubscriptions(const IlvGroup* group);

    ILVSTDPREF ostream*	_str;
    int			_indent;
};

#endif /* __Ilv_Protos_Groupio_H */
