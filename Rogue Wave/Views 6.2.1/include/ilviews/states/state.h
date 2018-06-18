// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/state.h
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
// Declaration of the IlvState class
// Defined in library ilvstates
// --------------------------------------------------------------------------
#ifndef __Ilv_States_State_H
#define __Ilv_States_State_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_States_List_H)
#  include <ilviews/states/list.h>
#endif
#if !defined(__Ilv_States_Statearr_H)
#  include <ilviews/states/statearr.h>
#endif
#if !defined(__Ilv_States_Reset_H)
#  include <ilviews/states/reset.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Gadgets_Appli_H)
#  include <ilviews/gadgets/appli.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_States_Callback_H)
#  include <ilviews/states/callback.h>
#endif

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvState;

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSiSubset
: public IlvSuStack
{
public:
    IlvSiSubset(IlInt = 5,
		IlInt = 5);
    virtual ~IlvSiSubset();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSiSubsetStack
: public IlvSuStack
{
public:
    IlvSiSubsetStack(IlInt = 5,
		     IlInt = 5);
    virtual ~IlvSiSubsetStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSiStateStack
: public IlvSuStack
{
 public:
    IlvSiStateStack(IlInt = 5,
		    IlInt = 5);
    virtual ~IlvSiStateStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSiRequirementStack
: public IlvSuStack
{
public:
    IlvSiRequirementStack(IlInt = 5,
			  IlInt = 5);
    virtual ~IlvSiRequirementStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSiProcedureStack
: public IlvSuStack
{
public:
    IlvSiProcedureStack(IlInt = 5,
			IlInt = 5);
    virtual ~IlvSiProcedureStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvState
    : public IlvValueInterface
{
    friend class IlvStateManager;
private:
    char* 		   _Name;
    IlvState*		   _Parent;
    IlBoolean		   _IsActive;
    IlInt		   _NumOfSubsetInParent;
    // (the index of the concurrent substate in parent the state belongs too)
    IlvSiSubsetStack*      _Subsets;		// the concurrent substates
    IlvSiStateStack*       _ActiveStates;	// the current state for each
    IlvSiStateStack*       _InitialStates;	// the current state for each
    IlvSiRequirementStack* _StateRequirements;	// the data to set and reset
    IlvSiProcedureStack*   _StateProcedures;	// the entry/exit procedures
public:
    IlInt getNumOfSubsets() const;
private:
    ILVSTATES_WRITEONLY(IlvState*, Parent);
    ILVSTATES_WRITEONLY(char*, Name);
protected:
    ILVSTATES_WRITEONLY(IlBoolean, IsActive);
public:
    //constructors
    IlvState(const char*,
	     IlInt = 0,
	     IlvState* = 0);
    virtual ~IlvState();

    //aspects
public:
    ILVSTATES_READONLY(IlvState*, Parent);
    virtual const char* getName() const;
    ILVSTATES_READONLY(IlInt, NumOfSubsetInParent);
    IlBoolean getIsActive() const { return _IsActive; }
    IlBoolean isActive() const {return getIsActive(); }
protected:
    ILVSTATES_READONLY(IlvSuStack*, StateRequirements);
    ILVSTATES_READONLY(IlvSuStack*, Subsets);
    ILVSTATES_READONLY(IlvSuStack*, ActiveStates);
    ILVSTATES_READONLY(IlvSuStack*, StateProcedures);
    //accessors
public:
    void setInitialState(IlInt,
			 IlvState*);
protected:
    IlvSiSubset* getSubset(IlInt) const;
    IlBoolean    hasSubset(IlInt) const;
    IlvState* 	 getActiveState(IlInt) const;
    IlvState* 	 getInitialState(IlInt) const;
    IlBoolean    isEmpty() const;

    //construction
public:
    void createSubset();
    virtual void addState(IlvState*,
			  IlInt = -1); // s must be allocated by new
    void addState(IlvState&,
		  IlInt = -1); // s must be allocated by new

    //description
public:
    void addProcedure(IlvStateProcedure*); // cp must be allocated
    void addRequirement(IlvStateRequirement*);

    //dynamics
public:
    void set(IlBoolean = IlTrue);
    void leave();

protected:
    void setActiveState(IlInt,
			IlvState* s);
    void enterState(IlvSuApplyAssocTable&);
    void leaveState(IlvSuApplyAssocTable&);
    void leaveAllStates(IlvSuApplyAssocTable&);

public:
    // name space policy
    virtual void addToManagerTable(const IlvStateManager*);
    virtual void addToNamespace(const IlvState*);
    virtual IlvState* getStateUp(const char*);
    virtual IlvStateManager* getManagerUp();
    virtual IlvStateManager* getManager(const char*);
    virtual IlBoolean hasType(const char*) const;

    // --- Value accessors ---
    DeclareGraphicAccessors();
    virtual IlBoolean getValueDescriptor(IlvValue& value) const;
    static IlSymbol* _activeValue;
    static IlSymbol* _managerValue;
    static IlSymbol* _setMethod;
    static IlSymbol* _leaveMethod;
    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStateManager
: public IlvState
{
    IlvSuKeyTable _Table;
    IlvSuStack*   _SubManagers; // the managers below (if any)
 public:
    IlvStateManager(const char*,
		    IlUInt = 5);
    ~IlvStateManager();
    void addToNamespace(const IlvState*);
    void addToManagerTable(const IlvStateManager*);
    IlvState* getState(const char* name); // only inside this namespace
    IlvStateManager* getManager(const char*);
    IlvState* getStateUp(const char*); // recurses up if not found locally
    IlvStateManager* getManagerUp();
    IlBoolean hasType(const char*) const;

    // --- Value accessors ---
    DeclareGraphicAccessors();
    virtual IlBoolean getValueDescriptor(IlvValue& value) const;
    static IlSymbol*	_getStateMethod;
    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSiCallbackParameters
{
public :
    IlvSiCallbackParameters(IlvState*,
			    IlArray*,
			    IlvApplication*);
    ~IlvSiCallbackParameters();
    // ____________________________________________________________
    IlvState* getState() const;
    IlvStateRequirement* getStateRequirement() const;
    IlvApplication* getApplication() const;
    IlInt getNumParams() const;
    IlAny getParam(int) const;
    const char* getStringParam(int) const;
private:
    IlvState*		 _state;
    IlvApplication*	 _application;
    IlvStateRequirement* _stateRequirement;
    IlArray*		 _params;
    friend class IlvStateRequirementGenerator;
};

// --------------------------------------------------------------------------
ILVSTATESMODULEINIT(state);

#endif /* !__Ilv_States_State_H */
