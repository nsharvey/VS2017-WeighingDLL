// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/mstate.h
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
// Declaration of the state model related classes
// Defined in library ilvstates
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Mstate_H
#define __Ilv_States_Mstate_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
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
#if !defined(__Ilv_States_Callback_H)
#  include <ilviews/states/callback.h>
#endif

#if defined(IL_STD)
#  include <iostream>
#include <cstring>
#else  /* !IL_STD */
#  include <iostream.h>
#  include <string.h>
#endif /* !IL_STD */

class IlvSdManager;

// --------------------------------------------------------------------------
// a parameter base class intended to carry information down the generation
// process. It is used solely by its pointer here
class ILVSTATESEXPORTED IlvSdGenerateContext
{
};

// --------------------------------------------------------------------------
// the base class for the structure built by the ivs compiler
// the implementation field can be set by the
// generate member function if needed (this is so for States)
class ILVSTATESEXPORTED IlvSdModel
{
    void* _Implementation; // a pointer to the future implementation object
public:
    IlvSdModel() : _Implementation(0) {}
    virtual ~IlvSdModel() {}
    ILVSTATES_READWRITE(void*, Implementation);
    virtual void  dump(IL_STDPREF ostream&) const = 0;
    // returns an operational class
    virtual void* generate(IlvSdGenerateContext*) = 0;
    virtual IlBoolean hasType(const char*) const = 0;
};

// --------------------------------------------------------------------------
// an abstract function object
class ILVSTATESEXPORTED IlvSdGenerator
{
public:
    virtual void* generate(IlvSdModel*,
			   IlvSdGenerateContext*) = 0;
};


// --------------------------------------------------------------------------
#define ILVSDGENERATE \
    private: static IlvSdGenerator* _Generator; \
    public: static void setGenerator(IlvSdGenerator* g) { _Generator = g; } \
    public: void* generate(IlvSdGenerateContext* c = 0) { \
	return _Generator->generate(this, c);}

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdRequirement
: public IlvSdModel {
    char* _TypeName;
    char* _Value;
    char* _Panel;
    char* _Object;
public:
    IlvSdRequirement(const char* p = 0,
		     const char * o = 0, 
		     const char* t = 0,
		     const char* v = 0)
    : _TypeName(IlCopyString(t, IlFalse)),
      _Value(IlCopyString(v, IlFalse)),
      _Panel(IlCopyString(p, IlFalse)),
      _Object(IlCopyString(o, IlFalse))
    {}
    ~IlvSdRequirement() {
	delete [] _TypeName;
	delete [] _Value;
	delete [] _Panel;
	delete [] _Object;
    }
    ILVSTATES_READONLY(char*, TypeName);
    void setTypeName(const char*);
    ILVSTATES_READONLY(char*, Value);
    void setValue(const char*);
    ILVSTATES_READONLY(char*, Panel);
    void setPanel(const char*);
    ILVSTATES_READONLY(char*, Object);
    void setObject(const char*);
    // protocol
    void dump(IL_STDPREF ostream&) const;
    IlBoolean hasType(const char* c) const {
	return !strcmp("IlvSdRequirement", c);
    }
    ILVSDGENERATE
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdProcedure
: public IlvSdModel {
public:
    void dump(ILVSTDPREF ostream&) const;
    IlBoolean hasType(const char* c) const {
	return !strcmp("IlvSdProcedure", c);
    }
    ILVSDGENERATE
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdState;

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdSubset
: public IlvSuStack {
    char*	 _name;
    IlvSdState* _initial;
public:
    IlvSdSubset(IlInt = 5,
		IlInt = 5);
    virtual ~IlvSdSubset();
    void setName(const char*);
    void setInitial(IlvSdState*);
    char*getName() const;
    IlvSdState*getInitial() const;
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdSubsetStack
: public IlvSuStack {
public:
    IlvSdSubsetStack(IlInt = 5,
		     IlInt = 5);
    virtual ~IlvSdSubsetStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdProcedureStack
: public IlvSuStack {
public:
    IlvSdProcedureStack(IlInt = 5,
			IlInt = 5);
    virtual ~IlvSdProcedureStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStringStack
: public IlvSuStack {
public:
    IlvStringStack(IlInt = 5,
		   IlInt = 5);
    virtual ~IlvStringStack();
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvSdState
: public IlvSdModel {
    friend class IlvSdManager;
private:
    char*		 _Name;
    IlvSdState*		 _Parent;
    IlInt		 _NumOfSubsetInParent;
    IlBoolean		 _IsInitial;
    // (the index of the concurrent substate in parent the state belongs too)
    IlvSdSubsetStack*	 _Subsets;         // the concurrent substates
    IlvArray*		 _requirements;    // the data to set and reset
    IlvSdProcedureStack* _StateProcedures; // the entry/exit procedures
public:
    //constructors
    IlvSdState(const char*); //name is copied
    virtual ~IlvSdState();   //recursive

    //aspects
public:
    ILVSTATES_READWRITE(IlvSdState*, Parent);
    ILVSTATES_READONLY(char*, Name);
    void setName(const char*);
    ILVSTATES_READWRITE(IlInt, NumOfSubsetInParent);
    ILVSTATES_READWRITE(IlvSdSubsetStack*, Subsets);
    ILVSTATES_READWRITE(IlvSdProcedureStack*, StateProcedures);
    IlvArray* getRequirements() const { return _requirements; }
    void      setRequirements(IlvArray* reqs) { _requirements = reqs; }
public:
    // subset accessors
    IlInt getNumOfSubsets() const;
    IlvSdSubset* getSubset(IlInt) const;
    IlBoolean isEmpty() const;
    IlInt getSubset(const char*) const;
    char* getSubsetName(IlInt) const;
    IlBoolean hasSubset(const char*) const;
    IlBoolean hasSubset(IlInt) const;

public:
    // add / remove elementary states
    // with incremental name policy management
    // for top level state ONLY (argument state below)
    void addState(IlvSdState*,
		  IlInt = -1); // -1 means "top most"
    void removeState(const IlvSdState*);

    // subset construction and destruction
    // WITHOUT incremental name policy management !!
    // one has to use the function freshenNameSpaces below to "repair"
    void createSubset(const char*);
    void setSubsetName(IlInt,
		       const char*);
    void removeSubset(IlInt);
    void removeSubset(const char*);
    void addSubset(IlvSdSubset*);
    void addSubset(IlvSdSubset*,
		   const char*);

    // per subset initial state management
    void setInitial(IlvSdState*);
    IlvSdState* getInitial(IlInt);
    void unsetInitial(const IlvSdState*);
    void unsetInitial(IlInt);

    virtual void freshenNameSpaces(IlvSdManager*, IlvSdManager*);

    //description
public:
    void addProcedure(const IlvSdProcedure*);
    void addRequirement(const IlvSdRequirement*,
			IlUInt = (IlUInt)-1);
    void removeProcedure(const IlvSdProcedure*);
    void removeRequirement(const IlvSdRequirement*);

    // name space policy
public:
    virtual void removeFromNamespace(const IlvSdState*);
    virtual void removeFromManagerTable(const IlvSdManager*);
    virtual void addToManagerTable(const IlvSdManager*);
    virtual void addToNamespace(const IlvSdState*);

    virtual IlvSdState* getStateUp(const char*);

    // model protocol
public:
    void dump(IL_STDPREF ostream&) const;
    IlBoolean hasType(const char*) const;
    ILVSDGENERATE
}; // class IlvSdState

// --------------------------------------------------------------------------
// the class IlvSdManager maintains a dictionary of the states that appear
// in it
class ILVSTATESEXPORTED IlvSdManager
: public IlvSdState {
    IlvSuKeyTable _Table;
    IlvSuStack*   _SubManagers; // the managers below (if any)
public:
    ILVSTATES_READONLY(IlvSuStack*,SubManagers);
    IlvSdManager(const char*,
		 IlUInt = 5);
    virtual ~IlvSdManager();
    void addState(IlvSdState*,
		  IlInt);
    void addToNamespace(const IlvSdState*);
    void addToManagerTable(const IlvSdManager*);
    void removeFromNamespace(const IlvSdState*);
    void removeFromManagerTable(const IlvSdManager*);
    IlvSdState* getState(const char*); // only inside this namespace
    IlvSdState* getStateUp(const char*); // recurses up if not found locally

    void freshenNameSpaces();
    void freshenNameSpaces(IlvSdManager* root,
			   IlvSdManager*nameSpace);

    IlvSdManager* getManager(const char*);
    IlBoolean hasType(const char*) const ;
    ILVSDGENERATE
}; // class IlvSdManager

#undef __CpStr

#endif /* !__Ilv_States_Mstate_H */
