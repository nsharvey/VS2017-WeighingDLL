// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/graphinf.h
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
// Declaration of classes to be derivated to get informations on IlvGraphic
// objects
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Graphinf_H)
#define __IlvSt_Inspectors_Graphinf_H

#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif

class IlvGraphic;
class IlvStIError;

// --------------------------------------------------------------------------
// IlvStIRefNamedObject
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRefNamedObject
    : public IlvStNamedObject
{
    IlvDeclareInspClassInfo();
public:
    IlvStIRefNamedObject(const char* name = 0)
    : IlvStNamedObject(name),
      _nLocks(0)
    {}

    // ----------------------------------------------------------------------
    // Locking mechanism
    void		lock() { _nLocks++; }
    void		unLock();

protected:
    IlUInt		_nLocks;
};

// --------------------------------------------------------------------------
// class IlvStINameChecker
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStINameChecker
    : public IlvStIRefNamedObject
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStINameChecker(const char* = 0);
    virtual ~IlvStINameChecker();

    // ----------------------------------------------------------------------
    virtual IlvStIError*	isIdentifierName(const char*) const;
    virtual IlvStIError*	checkGraphicName(const char*,
						 const IlvGraphic*) const;

    static IlBoolean	IsBlanckString(const char*);

protected:
    virtual IlBoolean	checkingIdentifierName() const { return IlTrue; }
    virtual IlvDisplay*	getDisplay() const { return 0; }
};

// --------------------------------------------------------------------------
// class IlvStINameInfos
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStINameInfos
    : public IlvStIRefNamedObject
{
    IlvDeclareInspClassInfo();
public:
    IlvStINameInfos(const char* = 0);
    virtual ~IlvStINameInfos();

    // ----------------------------------------------------------------------
    virtual IlvStIError*	setObjectName(IlvGraphic*, const char*);
};

// --------------------------------------------------------------------------
// IlvStIGraphicInteractorsInfos
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGraphicInteractorsInfos
    : public IlvStIRefNamedObject
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGraphicInteractorsInfos(const char* = 0);
    virtual ~IlvStIGraphicInteractorsInfos();

    // ----------------------------------------------------------------------
    virtual void	getObjectInteractors(IlArray&, IlvGraphic*);
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_graphinf)
#endif /* !__IlvSt_Inspectors_Graphinf_H */
