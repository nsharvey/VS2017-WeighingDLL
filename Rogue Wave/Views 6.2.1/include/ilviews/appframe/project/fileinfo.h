// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/project/fileinfo.h
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
// Declaration of the IlvDvFileInfo class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Project_Fileinfo_H)
#define __Ilv_Appframe_Project_Fileinfo_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif

class IlvDvProjectDocument;

//---------------------------------------------------------------------------
// IlvDvFileInfo class
//---------------------------------------------------------------------------
class ILVDVCLASS IlvDvFileInfo : public IlvDvSerializable
{
    IlvDvDeclareDynCreate();
public:
    //-----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvFileInfo();
    IlvDvFileInfo(const char* pathname, IlvDvProjectDocument* owner = 0);
    ~IlvDvFileInfo();

    //-----------------------------------------------------------------------
    // Main operations
    int			comparePathName(const IlPathName& pathname) const;

    //-----------------------------------------------------------------------
    // Basic properties
    inline const IlPathName&	getPathname() const { return _path; }
    inline const IlString&	getShortName() const { return _shortName; }
    void		setOwner(IlvDvProjectDocument* owner);

    //-----------------------------------------------------------------------
    // Lock / unLock mechanism
    inline void		lock() { ++_nLocks; }
    void		unLock();

    int			getSerializationIndex() const;

    //-----------------------------------------------------------------------
    // Input / output
    virtual void	serialize(IlvDvStream& stream);

protected:
    IlString			_shortName;
    IlPathName			_path;
    IlUInt			_nLocks;
    IlvDvProjectDocument*	_owner;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(fileinfo)
//-----------------------------------------------------------------------////
#endif /* __Ilv_Appframe_Project_Fileinfo_H */
