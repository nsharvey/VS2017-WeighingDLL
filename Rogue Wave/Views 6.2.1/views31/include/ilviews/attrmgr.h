// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/attrmgr.h
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
// Declaration of the IlvAttributeManager class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Attrmgr_H
#define __Ilv31_Attrmgr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv31_Itf_Attrmgr_H)
#include <ilviews/intrface/attrmgr.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv_Manager_Mgrio_H)
#include <ilviews/manager/io.h>
#endif

class IlvStringHashTable;
// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAttributeManager
    : public IlvManager,
      public IlvAttributeManagerInterface
{
    friend class IlvAttributeManagerOutputFile;

 public:
    IlvAttributeManager(IlvDisplay*	display,
			int		layers    = 2,
			IlBoolean	useacc    = IlTrue,
			IlUShort	maxInList = IlvMaxObjectsInList,
			IlUShort	maxInNode = IlvMaxObjectsInList);
    ~IlvAttributeManager();

    virtual IlBoolean	cleanObj(IlvGraphic* obj,
				 IlBoolean = IlTrue,
				 IlBoolean = IlTrue);
    virtual
    IlvManagerInputFile*  createInputFile(IL_STDPREF istream&);
    virtual
    IlvManagerOutputFile* createOutputFile(IL_STDPREF ostream&) const;

 protected:
    virtual
    IlvStringHashTable* getAttributesTable() const;
    IlvStringHashTable*	_attributes;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAttributeManagerOutputFile
    : public IlvManagerOutputFile
{
 public:
    IlvAttributeManagerOutputFile(IL_STDPREF ostream& stream,
				  const IlvAttributeManager* mgr = 0)
	: IlvManagerOutputFile(stream, mgr)
    {}

    const IlvAttributeManager* getAttributeManager()
	{ return (const IlvAttributeManager*)getManager(); }
    virtual void	saveMoreInfo(IlUInt count = 0,
				     IlvGraphic* const* objs = 0);
    virtual void	saveAttribute(const IlvGraphicAttribute*);
    virtual const char*	typeOf() const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAttributeManagerInputFile
    : public IlvManagerInputFile
{
 public:
    IlvAttributeManagerInputFile(IL_STDPREF istream& stream,
				 IlvAttributeManager* mgr = 0)
	: IlvManagerInputFile(stream, mgr)
    {}
    
    IlvAttributeManager* getAttributeManager() const
	{ return (IlvAttributeManager*)getManager(); }
    virtual void	readAll(IlvManager*);
    virtual IlBoolean	parseBlock(const char* blockName);
    virtual void	readAttribute(IlvAttributeManager*);
    virtual const char*	typeOf() const;
};

#endif /* !__Ilv31_AttributeManagerH */
