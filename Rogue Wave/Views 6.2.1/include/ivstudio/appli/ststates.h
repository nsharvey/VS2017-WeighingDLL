// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/ststates.h
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
// Declaration of IlvStStates class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Ststates_H
#define __IlvSt_Ststates_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

class IlvStudio;
class IlvStError;

class IlvSdManager;
class IlvSdState;
class IlvSdRequirement;
class IlvStateParser;

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmSetStateManager;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmSetState;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmSetStateRequirement;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmRemoveStateRequirement;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmSetStateSubsetIndex;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmRenameStateSubset;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmRenameState;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmNewStateSubset;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowStateInspector;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowStateTree;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmStateTree;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmStateTreeClosed;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStStates
{
public:
    IlvStStates(IlvStudio*);
    virtual ~IlvStStates();

    void		reset();

    IlvStudio*		getEditor() const { return _editor; }
    IlvSdManager*	getManager() const { return _sdManager; }

    // state
    IlvSdState*		getState() const { return _sdState; }
    void		setState(IlvSdState*,
				 IlUShort subsetIndex = (IlUShort)-1,
				 IlAny caller = 0);
    void		setState(const char* name,
				 IlUShort subsetIndex = (IlUShort)-1,
				 IlAny caller = 0);
    void		selectParentState(IlAny caller = 0);
    void		renameState(const char* = 0, IlAny caller = 0);
    void		newState(const char* name = 0, IlAny caller = 0);
    void		newRootState(const char* name = 0, IlAny caller = 0);
    void		removeState(IlAny caller = 0);
    void		removeRootState(IlAny caller = 0);
    void		updateNameSpace();
    // requirement
    IlvSdRequirement*	getRequirement() const { return _sdReq; }
    void		setRequirement(IlvSdRequirement*, IlAny caller = 0);
    void		removeRequirement(IlAny = 0);
    // subset
    IlUShort		getSubsetIndex() const { return _subsetIndex; }
    void		setSubsetIndex(IlUShort index, IlAny caller = 0);
    void		renameSubset(const char* = 0, IlAny caller = 0);
    void		newSubset(const char* name = 0, IlAny caller = 0);
    void		removeSubset(IlAny caller = 0);
    // IO
    IlvStError*		open(const char* = 0, IlAny = 0);
    IlvStError*		save(const char* = 0, IlAny = 0);
    //
    IlBoolean		checkCurrentState();
    IlBoolean		checkStates();
    IlBoolean		hasRequirements() const;

protected:
    void		setManager(IlvSdManager*, IlAny caller = 0);
    void		broadcast(const char*, IlAny clr = 0, IlAny arg = 0);
    IlvStudio*		_editor;
    IlvStateParser*	_parser;
    IlvSdManager*	_sdManager;
    IlvSdState*		_sdState;
    IlvSdRequirement*	_sdReq;
    IlUShort		_subsetIndex;

public:
    static IlvStStates*	Get(IlvStudio*);
}; // class IlvStStates

// --------------------------------------------------------------------------
#endif /* __IlvSt_Ststates_H */
