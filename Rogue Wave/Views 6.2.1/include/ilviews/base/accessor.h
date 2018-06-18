// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/accessor.h
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
// Declaration of the IlvBaseAccessor class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Accessor_H
#define __Ilv_Base_Accessor_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBaseAccessor
{
public:
    virtual ~IlvBaseAccessor();
    // ____________________________________________________________
    virtual IlBoolean	set(IlvValueInterface*, const IlvValue&);
    virtual IlBoolean	get(const IlvValueInterface*, IlvValue&);
    virtual IlBoolean	call(IlvValueInterface*,
			     IlvValue& returned,
			     IlUInt nParams,
			     const IlvValue* params);
    virtual IlBoolean	checkAndCall(IlvValueInterface*,
				     IlvValue&,
				     IlUInt,
				     const IlvValue*);
    virtual IlBoolean	callStoredParams(IlvValueInterface*, IlvValue&);
    virtual IlBoolean	setParameter(IlvValueInterface*,
				     const IlSymbol*,
				     const IlvValue&);
    enum {
	FullAccess     = 0,
	ReadOnly       = 1,
	WriteOnly      = 2,
	Method         = 3,
	NoVisualImpact = 4
    };
    inline const IlvValueTypeClass*	getType() const { return _type; }
    inline IlBoolean	canRead() const
			{
			    return (_flags & WriteOnly) ? IlFalse : IlTrue;
			}
    inline IlBoolean	canWrite() const
			{
			    return (_flags & ReadOnly) ? IlFalse : IlTrue;
			}
    inline IlBoolean	canExecute() const
			{
			    return ((_flags & Method) == Method)
				? IlTrue : IlFalse;
			}
protected:
    IlvBaseAccessor(const IlvValueTypeClass* type, int flags)
    : _type(type),
      _flags(flags)
    {}
    inline void		removeReadOnlyAccess()  { _flags &= ~ReadOnly;  }
    inline void		removeWriteOnlyAccess() { _flags &= ~WriteOnly; }
private:
    const IlvValueTypeClass* _type;
    int                      _flags;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvMethodBaseAccessor
: public IlvBaseAccessor {
public:
    class Parameter {
    public:
	Parameter() : _name(0), _type(0), _classInfo(0) {}
	inline void	set(const IlSymbol*          name,
			    const IlvValueTypeClass* type,
			    const IlvClassInfo*      clssInfo)
			{
			    _name = name; _type = type;
			}
	inline const IlSymbol*		getName() const { return _name; }
	inline const IlvValueTypeClass*	getType() const { return _type; }
	inline const IlvClassInfo*	getClassInfo() const
					{
					    return _classInfo;
					}
    private:
	const IlSymbol*			_name;
	const IlvValueTypeClass*	_type;
	const IlvClassInfo*		_classInfo;
    };

    IlvMethodBaseAccessor(const IlvValueTypeClass* type,
			  int                      flags,
			  IlUInt                   required)
    : IlvBaseAccessor(type, flags),
      _nParams(0),
      _required(required),
      _signature(0),
      _params(0)
      {}
    ~IlvMethodBaseAccessor();
    // ____________________________________________________________
    const Parameter*	getSignature(IlUInt&, IlUInt&) const;
    const IlvValueTypeClass**	getParamNames(IlUInt&, IlUInt&) const;
    void		add(const IlSymbol*,
			    const IlvValueTypeClass*,
			    const IlvClassInfo* = 0);
    virtual IlBoolean	checkAndCall(IlvValueInterface*,
				     IlvValue&,
				     IlUInt,
				     const IlvValue*);
    virtual IlBoolean	callStoredParams(IlvValueInterface*, IlvValue&);
    virtual IlBoolean	setParameter(IlvValueInterface*,
				     const IlSymbol*,
				     const IlvValue&);
private:
    IlUInt		_nParams;
    IlUInt		_required;
    Parameter*		_signature;
    IlvValue*		_params;

    static IlBoolean	TypeMatch(Parameter&, const IlvValue&);
};

// --------------------------------------------------------------------------
typedef IlvBaseAccessor* (* IlvBaseAccessorFactory)();
typedef IlvAccessorsMap* (* IlvAccessorsMapFactory)();
IL_DEFINEFPTRTOANYCAST(IlvAccessorsMapFactory);
class ILVDSPEXPORTED IlvAccessorsMap
{
public:
    IlvAccessorsMap(int unused ...);
    virtual ~IlvAccessorsMap();
    // ____________________________________________________________
    IlBoolean		get(const IlvValueInterface*, IlvValue&) const;
    IlBoolean		set(IlvValueInterface*, const IlvValue&) const;
    virtual const IlvValueTypeClass* getType(const IlSymbol*,
					     const IlvValueInterface*) const;
    virtual IlBoolean	canRead(const IlSymbol*,
				const IlvValueInterface*) const;
    virtual IlBoolean	canWrite(const IlSymbol*,
				 const IlvValueInterface*) const;
    virtual IlBoolean	canExecute(const IlSymbol*,
				   const IlvValueInterface*) const;
    void		add(const IlSymbol*, IlvBaseAccessorFactory c);
    virtual IlvBaseAccessor*	get(const IlSymbol*,
				    const IlvValueInterface*) const;
    virtual void	getAccessors(IlSymbol const* const** accessors,
				     IlvValueTypeClass const* const** types,
				     IlUInt&                  count,
				     IlvValueInterface const* obj) const;
    static int Register(const IlvValuedClassInfo*, IlvAccessorsMapFactory);

private:
    IlArray _accessors;
};

// --------------------------------------------------------------------------

#define IlvAM_DPA(c, n, t, f)					\
    class c##_##n##PA : public IlvBaseAccessor {			\
public: c##_##n##PA() : IlvBaseAccessor(IlvValue##t##Type, f) {}

#define IlvAM_DG(c, n, t, f, e) IlvAM_DPA(c, n, t, f)			\
virtual IlBoolean get(const IlvValueInterface* o_, IlvValue& value) {	\
const c* object = IL_DYNAMICCAST(const c*, o_); e return IlTrue; }};	\
static IlvBaseAccessor* c##_##n##CA() { static c##_##n##PA p; return &p; }
#define IlvAM_DS(c, n, t, f, expr) IlvAM_DPA(c, n, t, f)		\
virtual IlBoolean set(IlvValueInterface* o_, const IlvValue& value) {	\
c* object = IL_DYNAMICCAST(c*, o_); expr return IlTrue; }};		\
static IlvBaseAccessor* c##_##n##CA() { static c##_##n##PA p; return &p; }
#define IlvAM_DGS(c, n, t, f, G, S) IlvAM_DPA(c, n, t, f)		\
virtual IlBoolean get(const IlvValueInterface* o_, IlvValue& value) {	\
const c* object = IL_DYNAMICCAST(const c*, o_); G return IlTrue; }	\
virtual IlBoolean set(IlvValueInterface* o_, const IlvValue& value) {	\
c* object = IL_DYNAMICCAST(c*, o_); S return IlTrue; }};		\
static IlvBaseAccessor* c##_##n##CA() { static c##_##n##PA p; return &p; }

#define IlvAM_DP(n, t) add(IlGetSymbol(IL_STRING(n)), IlvValue##t##Type);
#define IlvAM_DVP(n, c) add(IlGetSymbol(IL_STRING(n)), \
IlvValueInterfaceType, c::ClassInfo());
#define IlvAM_DPL(A) A
#define IlvAM_DMC(c, n, t, f, r, p, e)					\
class c##_##n##PA : public IlvMethodBaseAccessor {			\
public:c##_##n##PA():IlvMethodBaseAccessor(IlvValue##t##Type,f,r){ p }	\
    virtual IlBoolean call(IlvValueInterface* o_, IlvValue& value,	\
	IlUInt nParams, const IlvValue* params) { c* object =		\
	IL_DYNAMICCAST(c*, o_); e return IlTrue; } };			\
static IlvBaseAccessor* c##_##n##CA(){static c##_##n##PA m; return &m; }

// --------------------------------------------------------------------------
#define IlvAM_DPG(c, n, D1, D2, D3) \
IlGetSymbol(IL_STRING(n)), c##_##n##CA,
#define IlvAM_DPS(c, n, D1, D2, D3) \
IlGetSymbol(IL_STRING(n)), c##_##n##CA,
#define IlvAM_DPGS(c, n, D1, D2, D3, D4) \
IlGetSymbol(IL_STRING(n)), c##_##n##CA,
#define IlvAM_DMR(c, n, D1, D2, D3, D4, D5) \
IlGetSymbol(IL_STRING(n)), c##_##n##CA,

#define IlvAM_E1(A)
#define IlvAM_E2(A, B)
#define IlvAM_E5(A, B, C, D, E)
#define IlvAM_E6(A, B, C, D, E, F)

#define IlvDeclareAccessorsMap(c, MAP)					  \
MAP(c,IlvAM_DG,IlvAM_DS,IlvAM_DGS,IlvAM_DMC,IlvAM_DPL,IlvAM_DP,IlvAM_DVP) \
static IlvAccessorsMap*c##CAM(){ static IlvAccessorsMap m(0,		  \
MAP(c,IlvAM_DPG,IlvAM_DPS,IlvAM_DPGS,IlvAM_DMR,IlvAM_E1,IlvAM_E2,IlvAM_E2)\
(IlAny)0); return &m; }

#define IlvRegisterAccessorsMap(c) static int c##_CAM = \
IlvAccessorsMap::Register(c::ClassInfo()->getValued(), c##CAM)

#endif /* !__Ilv_Base_Accessor_H */
