// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vrgadmgr.h
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
// Declaration of the IlvVariableGadgetManager class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vrgadgmgr_H
#define __Ilv31_Vrgadgmgr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadmgr_Gadmgr_H)
#include <ilviews/gadmgr/gadmgr.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv31_Ilvparse_H)
#include <ilviews/ilvparse.h>
#endif
#if !defined(__Ilv31_Itf_Attrmgr_H)
#include <ilviews/intrface/attrmgr.h>
#endif
#if !defined(__Ilv31_Itf_Varmgr_H)
#include <ilviews/intrface/varmgr.h>
#endif
#if !defined(__Ilv31_Itf_Vario_H)
#include <ilviews/intrface/vario.h>
#endif

class IlvStringHashTable;
// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableGadgetManager
    : public IlvGadgetManager,
      public IlvAMItf,
      public IlvVMItf
{
public:
    IlvVariableGadgetManager(IlvDisplay* display,
			     int         layers    = 3,
			     IlBoolean   useacc    = IlTrue,
			     IlUShort    maxInList = IlvMaxObjectsInList,
			     IlUShort    maxInNode = IlvMaxObjectsInList);
    virtual ~IlvVariableGadgetManager();

    virtual IlvParser*	getParser() const;
    void		setParser(IlvParser* parser) { _parser = parser; }
    virtual IlBoolean	cleanObj(IlvGraphic* obj,
				 IlBoolean = IlTrue,
				 IlBoolean = IlTrue);
    virtual
    IlvVariable*	connect(IlvGraphic*g,
				const char* attclass,
				const char* varName);
    virtual
    IlvVariable*	connect(IlvGraphicAttribute*	attr,
				const char*		varName);
    virtual
    IlvManagerInputFile* createInputFile(IL_STDPREF istream&);
    virtual
    IlvManagerOutputFile* createOutputFile(IL_STDPREF ostream&) const;

protected:
    virtual
    IlvStringHashTable*	getAttributesTable() const;
    virtual IlvManager*	getTheManager();

    IlvStringHashTable*	_attributes;
    IlvParser*		_parser;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableGadgetManagerOutputFile
    : public IlvGadgetManagerOutputFile,
      public IlvVOItf
{
public:
    IlvVariableGadgetManagerOutputFile(ILVSTDPREF ostream& stream,
				       const IlvVariableGadgetManager* mgr = 0)
	: IlvGadgetManagerOutputFile(stream, mgr)
    {}

    const IlvVariableGadgetManager* getVariableGadgetManager() const
        { return (const IlvVariableGadgetManager*)getManager(); }
    virtual void	saveMoreInfo(IlUInt count = 0,
				     IlvGraphic* const* objs = 0);
    virtual const char* typeOf() const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableGadgetManagerInputFile
    : public IlvGadgetManagerInputFile,
      public IlvVIItf
{
public:
    IlvVariableGadgetManagerInputFile(ILVSTDPREF istream& stream,
				      IlvVariableGadgetManager* mgr = 0)
	: IlvGadgetManagerInputFile(stream, mgr)
    {}

    IlvVariableGadgetManager* getVariableGadgetManager() const
	{ return (IlvVariableGadgetManager*)getManager(); }
    virtual void	readVariable(IlvVariableGadgetManager*);
    virtual IlBoolean	parseBlock(const char*);
    virtual const char*	typeOf() const;
};

#endif /* !__Ilv31_Vrgadgmgr_H */
