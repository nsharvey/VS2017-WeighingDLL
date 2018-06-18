// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/psmodel.h
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
// Declaration of the IlvStpsModel class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Psmodel_H
#define __IlvSt_Inspectors_Psmodel_H

#if !defined(__Il_Hash_H)
#include <ilog/hash.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__IlvSt_Inspectors_Psrules_H)
#  include <ivstudio/inspectors/psrules.h>
#endif
#if !defined(__IlvSt_Inspectors_Psfacto_H)
#  include <ivstudio/inspectors/psfacto.h>
#endif

class IlvStpsPropertySheetItem;
class IlvStpsPropertySheet;
class IlvDisplay;
class IlvTextField;

// --------------------------------------------------------------------------
// IlvStpsModel
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsModel : public IlvStpsRefCount 
{
 public:
  IlvStpsModel();

  virtual IlSymbol* getName() const;
};

// --------------------------------------------------------------------------
// IlvStpsDisplayerModel
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsDisplayerModel : public IlvStpsModel 
{
 public:
  IlvStpsDisplayerModel();

  //---- Properties ----
  virtual IlSymbol* getLabel() const;

  //---- About property sheet ----
  void setPropertySheet(IlvStpsPropertySheet* ps);

  void updateMatrixItem(IlvStpsPropertySheetItem* parent,
			IlvStpsPropertySheetItem* item,
			IlBoolean readOnly);

  void updateMatrixNode(IlvStpsPropertySheetItem* parent,
			IlvStpsPropertySheetItem* item);

  //---- About accessors ----
  virtual IlBoolean isVisibleAccessor(const IlvValueTypeClass* typ,
				      const IlSymbol* name,IlvGraphic* g,
				      IlBoolean propagate = IlTrue) const;
  virtual IlBoolean isReadOnlyAccessor(const IlvValueTypeClass* typ,
				       const IlSymbol* name,IlvGraphic* g,
				       IlBoolean propagate = IlTrue) const;
  virtual IlvMatrixItemEditor* createAccessorEditor(IlvMatrix*,IlUShort col,
						    IlUShort,
						    IlvValueTypeClass* typ,
						    IlSymbol* name,
						    IlvGraphic* g,
					   IlBoolean propagate = IlTrue) const;

  void getAccessors(IlvStpsPropertySheetItem*,const IlSymbol* const**,
		    const IlvValueTypeClass* const**,IlUInt&,IlvGraphic*,
		    IlBoolean expandBaseClasses = IlTrue) const;
  void getAccessors(IlvClassInfo*,const IlSymbol* const**,
		    const IlvValueTypeClass* const**,IlUInt&,IlvGraphic*,
		    IlBoolean expandBaseClasses = IlTrue) const;

  void getAccessors(IlvGraphic*,const IlSymbol* const**,
		    const IlvValueTypeClass* const**,IlUInt&) const;

  //---- From model ----
  virtual IlSymbol* getName() const;

  //---- Visibility rules ----
  void setTypeVisibility(IlvValueTypeClass*,IlBoolean visible);
  void setAccessorVisibility(IlSymbol*,IlBoolean visible);
  void setClassVisibility(IlvClassInfo*,IlSymbol*,IlBoolean visible);
  void addVisilityRule(IlvStpsRule*);
  void setDefaultVisibility(IlBoolean visible);

  //---- Read Only rules ----
  void setTypeReadOnly(IlvValueTypeClass*,IlBoolean only);
  void setAccessorReadOnly(IlSymbol*,IlBoolean only);
  void setClassReadOnly(IlvClassInfo*,IlSymbol*,IlBoolean only);
  void addReadOnlyRule(IlvStpsRule*);
  void setDefaultReadOnly(IlBoolean only);

  //---- Editor factories ----
  void setTypeFactory(IlvValueTypeClass*,IlvStpsEditorFactory* f);
  void setAccessorFactory(IlSymbol*,IlvStpsEditorFactory* f);
  void setClassFactory(IlvClassInfo*,IlSymbol*,IlvStpsEditorFactory* f);

  //---- From DisplayerModel ----
  virtual void buildHierarchy(IlvStpsPropertySheetItem* parent,
			      IlBoolean expand);

 private:
  IlvStpsPropertySheet* _propSheet;
  IlvStpsRuleList _visibilityRules;
  IlvStpsRuleList _readOnlyRules;
  IlvStpsEditorFactoryList _editorFactories;
};

// --------------------------------------------------------------------------
// IlvStpsDisplayerDebugModel
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsDisplayerDebugModel : public IlvStpsDisplayerModel {
 public:
  IlvStpsDisplayerDebugModel();

  //---- From model ----
  virtual IlSymbol* getName() const;

  //---- From DisplayerModel ----
  virtual IlSymbol* getLabel() const;
  virtual void buildHierarchy(IlvStpsPropertySheetItem* parent,
			      IlBoolean expand);
};

// --------------------------------------------------------------------------
// IlvStpsDisplayerDirectModel
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsDisplayerDirectModel : public IlvStpsDisplayerModel {
 public:
  IlvStpsDisplayerDirectModel();

  //---- From model ----
  virtual IlSymbol* getName() const;

  //---- From DisplayerModel ----
  virtual IlSymbol* getLabel() const;
  virtual void buildHierarchy(IlvStpsPropertySheetItem* parent,
			      IlBoolean expand);
};

// --------------------------------------------------------------------------
// IlvStpsDisplayerHierarchicalModel
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsDisplayerHierarchicalModel : public IlvStpsDisplayerModel {
 public:
  IlvStpsDisplayerHierarchicalModel();

  //---- From model ----
  virtual IlSymbol* getName() const;

  //---- From DisplayerModel ----
  virtual IlSymbol* getLabel() const;
  virtual void buildHierarchy(IlvStpsPropertySheetItem* parent,
			      IlBoolean expand);
};

// --------------------------------------------------------------------------
// IlvStpsModelList
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsModelList {
 public:
  IlvStpsModelList();
  ~IlvStpsModelList();

  void add(IlvStpsModel* model);
  IlvStpsModel* get(IlSymbol* name) const;
  IlvStpsModel** getAll(IlUInt& count) const;

 protected:
  IlHashTable _models;
};

// --------------------------------------------------------------------------
// IlvStpsDisplayerModelList
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsDisplayerModelList : public IlvStpsModelList {
 public:
  static IlvStpsDisplayerModelList& GetInstance();

  static void RegisterModel(IlvStpsDisplayerModel* model);
  static IlvStpsDisplayerModel* GetModel(IlSymbol* name);
  static IlvStpsDisplayerModel** GetList(IlUInt& count);
 protected:
  IlvStpsDisplayerModelList();
};

#define IlvStpsRegisterDisplayerModel(cl) \
IlvStpsDisplayerModelList::RegisterModel(new cl)


#endif /* !__IlvSt_Inspectors_Psmodel_H */
