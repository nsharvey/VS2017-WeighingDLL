// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/pathlist.h
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
// Declaration of the IlPathList class
// --------------------------------------------------------------------------
#ifndef __Il_Pathlist_H
#define __Il_Pathlist_H

#if !defined(__Il_String_H)
#  include <ilog/string.h>
#endif

class IlPathItem;
class IlPathListIterator;
class IlPathName;

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlPathList
{
    friend class IlPathListIterator;
public:
    // Constructors and destructor.
    IlPathList();
    IlPathList(const IlString& pathList);
    ~IlPathList();

    // Accessors.
    IlBoolean	findInPath(const IlPathName&	relative,
			   IlPathName&		result,
			   IlBoolean		verbose = IlFalse) const;
    IlString	getString() const;
    IlString	getPrevListString() const;
    IlString	getListString() const;
    IlString	getPostListString() const;

    void	addInPrevList(const IlPathName& path);
    void	addInPrevList(const IlString& pathList);
    void	addInPrevList(const IlPathList& pathList);
    void	addInList(const IlPathName& path);
    void	addInList(const IlString& pathList);
    void	addInList(const IlPathList& pathList);
    void	addInPostList(const IlPathName& path);
    void	addInPostList(const IlString& pathList);
    void	addInPostList(const IlPathList& pathList);
    void	insertInPrevList(const IlPathName& path);
    void	insertInPrevList(const IlString& pathList);
    void	insertInPrevList(const IlPathList& pathList);
    void	insertInList(const IlPathName& path);
    void	insertInList(const IlString& pathList);
    void	insertInList(const IlPathList& pathList);
    void	insertInPostList(const IlPathName& path);
    void	insertInPostList(const IlString& pathList);
    void	insertInPostList(const IlPathList& pathList);
    void	setPrevList(const IlPathName& path);
    void	setPrevList(const IlString& pathList);
    void	setPrevList(const IlPathList& pathList);
    void	setList(const IlPathName& path);
    void	setList(const IlString& pathList);
    void	setList(const IlPathList& pathList);
    void	setPostList(const IlPathName& path);
    void	setPostList(const IlString& pathList);
    void	setPostList(const IlPathList& pathList);
    void	removeFromPrevList(const IlPathName& path);
    void	removeFromPrevList(const IlString& pathList);
    void	removeFromList(const IlPathName& path);
    void	removeFromList(const IlString& pathList);
    void	removeFromPostList(const IlPathName& path);
    void	removeFromPostList(const IlString& pathList);
    void	unique();

private:
    // The two following functions are intentionaly not defined.
    IlPathList(const IlPathList& pathList);
    IlPathList& operator=(const IlPathList& pathList);

    inline IlPathItem* getPrevList() const { return _prevList; }
    inline IlPathItem* getList()     const { return _list;     }
    inline IlPathItem* getPostList() const { return _postList; }

    IlPathItem* _prevList;
    IlPathItem* _list;
    IlPathItem* _postList;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlPathListIterator
{
public:
    // Constructor and destructor.
    IlPathListIterator();
    IlPathListIterator(const IlPathList& pathList);
    int operator!() const;
    IlPathListIterator& operator++(int);
    operator const IlPathName&() const;
private:
    const IlPathList*	_list;
    IlPathItem*		_current;
    int			_part;
    void		init();
};

#endif /* __Il_Pathlist_H */
