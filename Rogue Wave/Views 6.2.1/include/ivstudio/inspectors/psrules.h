// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/psrules.h
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
// Declaration of the IlvStpsRule class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Psrules_H
#define __IlvSt_Inspectors_Psrules_H

#if !defined(__IlvSt_Util_H)
#  include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif

class IlvGraphic;

// --------------------------------------------------------------------------
// IlvStpsRefCount
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsRefCount 
{
 public:
  IlvStpsRefCount();

  void lock();
  void unLock();

 protected:
  virtual ~IlvStpsRefCount();

 private:
  IlInt _refCount;
};

// --------------------------------------------------------------------------
// IlvStpsRule
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsRule : public IlvStpsRefCount
{
 public:
  IlvStpsRule(IlBoolean result = IlFalse);

  virtual IlBoolean isTrue(const IlvValueTypeClass*,const IlSymbol*,
			   IlvGraphic*) const;
  virtual IlBoolean isApplicable(const IlvValueTypeClass*,const IlSymbol*,
				 IlvGraphic*) const;

 protected:
  IlBoolean _result;
};

// --------------------------------------------------------------------------
// IlvStpsRuleByClass
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsRuleByClass : public IlvStpsRule 
{
 public:
  IlvStpsRuleByClass(IlBoolean result = IlFalse);

  void registerRuleByAccessor(IlvClassInfo*,IlvStpsRule*);

  virtual IlBoolean isTrue(const IlvValueTypeClass*,
			   const IlSymbol*,IlvGraphic*) const;
  virtual IlBoolean isApplicable(const IlvValueTypeClass*,
				 const IlSymbol*,IlvGraphic*) const;

  IlvStpsRule* getRule(IlvGraphic*) const;

 protected:
  virtual ~IlvStpsRuleByClass();

  IlHashTable _classes;
};

// --------------------------------------------------------------------------
// IlvStpsRulesList
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsRuleList
{
 public:
  IlvStpsRuleList();
  virtual ~IlvStpsRuleList();

  //---- Default value if no rule found ----
  void setDefaultValue(IlBoolean);
  IlBoolean getDefaultValue() const;

  //---- Rules ----
  IlBoolean isTrue(const IlvValueTypeClass*,const IlSymbol*,
		   IlvGraphic*,IlBoolean&) const;

  //---- Register the rules ----
  void registerRuleByType(IlvValueTypeClass*,IlBoolean result);
  void registerRuleByType(IlvValueTypeClass*,IlvStpsRule*);
  void registerRuleByAccessor(IlSymbol*,IlBoolean result);
  void registerRuleByAccessor(IlSymbol*,IlvStpsRule*);
  void registerRuleByClass(IlvClassInfo*,IlSymbol*,IlBoolean result);
  void registerRuleByClass(IlvClassInfo*,IlSymbol*,IlvStpsRule*);
  void registerRule(IlvStpsRule*);
 private:
  IlHashTable _byType;
  IlHashTable _byAccessor;
  IlHashTable _byClass;
  IlList _byRules;
  IlBoolean _defaultValue;
};

// --------------------------------------------------------------------------
// IlvStpsVisibilityRules
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsVisibilityRules
{
 public:
  static IlvStpsVisibilityRules& GetInstance();

  static void SetTypeVisibility(IlvValueTypeClass*,IlBoolean result);
  static void SetAccessorVisibility(IlSymbol*,IlBoolean result);
  static void SetClassVisibility(IlvClassInfo*,IlSymbol*,IlBoolean result);
  static void AddVisibilityRule(IlvStpsRule*);
  static IlBoolean IsVisible(const IlvValueTypeClass*,const IlSymbol*,
			     IlvGraphic*,IlBoolean&);
 protected:
  IlvStpsVisibilityRules();

  IlvStpsRuleList _rules;
};

// --------------------------------------------------------------------------
// IlvStpsReadOnlyRules
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsReadOnlyRules
{
 public:
  static IlvStpsReadOnlyRules& GetInstance();

  static void SetTypeReadOnly(IlvValueTypeClass*,IlBoolean result);
  static void SetAccessorReadOnly(IlSymbol*,IlBoolean result);
  static void SetClassReadOnly(IlvClassInfo*,IlSymbol*,IlBoolean result);
  static void AddReadOnlyRule(IlvStpsRule*);

  static IlBoolean IsReadOnly(const IlvValueTypeClass*,const IlSymbol*,
			      IlvGraphic*,IlBoolean&);
 protected:
  IlvStpsReadOnlyRules();

  IlvStpsRuleList _roRules;
};

#define IlvStpsSetTypeVisibility(typ,visible) \
IlvStpsVisibilityRules::SetTypeVisibility(typ,visible)

#define IlvStpsSetAccessorVisibility(acc,visible) \
IlvStpsVisibilityRules::SetAccessorVisibility(IlGetSymbol(acc),visible)

#define IlvStpsSetClassAccessorVisibility(cl,acc,visible) \
IlvStpsVisibilityRules::SetClassVisibility(cl::ClassInfo(),IlGetSymbol(acc),visible)

#define IlvStpsAddVisibilityRule(clrule) \
IlvStpsVisibilityRules::AddVisibilityRule(new clrule)

#define IlvStpsHideType(typ) \
IlvStpsVisibilityRules::SetTypeVisibility(typ,IlFalse)

#define IlvStpsHideAccessor(acc) \
IlvStpsVisibilityRules::SetAccessorVisibility(IlGetSymbol(acc),IlFalse)

#define IlvStpsHideClassAccessor(cl,acc) \
IlvStpsVisibilityRules::SetClassVisibility(cl::ClassInfo(),IlGetSymbol(acc),IlFalse)


#define IlvStpsSetTypeReadOnly(typ,only) \
IlvStpsReadOnlyRules::SetTypeReadOnly(typ,only)

#define IlvStpsSetAccessorReadOnly(acc,only) \
IlvStpsReadOnlyRules::SetAccessorReadOnly(IlGetSymbol(acc),only)

#define IlvStpsSetClassAccessorReadOnly(cl,acc,only) \
IlvStpsReadOnlyRules::SetClassReadOnly(cl::ClassInfo(),IlGetSymbol(acc),only)

#define IlvStpsAddReadOnlyRule(clrule) \
IlvStpsReadOnlyRules::AddReadOnlyRule(new clrule)

#endif /* !__IlvSt_Inspectors_Psrules_H */
