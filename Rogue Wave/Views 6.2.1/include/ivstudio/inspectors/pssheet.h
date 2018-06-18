// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/pssheet.h
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
// Declaration of the IlvStpsPropertySheet class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Pssheet_H
#define __IlvSt_Inspectors_Pssheet_H

#if !defined(__Ilv_Gadgets_Tree_H)
#  include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Gadgets_Hsheet_H)
#  include <ilviews/gadgets/hsheet.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif
#if !defined(__IlvSt_Inspectors_Psmodel_H)
#  include <ivstudio/inspectors/psmodel.h>
#endif

class ILVSTUDIOCLASS IlvStpsPropertySheetItem : public IlvTreeGadgetItem 
{
 public:
  IlvStpsPropertySheetItem(IlvValueInterface* valItf);
  IlvStpsPropertySheetItem(const char* label,const IlvValueTypeClass* type,
			   IlvClassInfo* classInfo);
  IlvStpsPropertySheetItem(IlvClassInfo* classInfo);

  IlvStpsPropertySheetItem(const IlvStpsPropertySheetItem& source);

  ~IlvStpsPropertySheetItem();

  // ---------------------------------------------------------------------
  void refresh();

  IlvClassInfo* getPropertyClassInfo();
  IlvValueTypeClass* getPropertyType() const;
  void setPropertyType(const IlvValueTypeClass* type);

  IlBoolean isRootInterface() const;
  void setRootInterface(IlBoolean);
  IlvStpsPropertySheetItem* findRootInterface();

  void setValueInterface(IlvValueInterface* valItf);
  IlvValueInterface* getValueInterface();

  void setInspectedGraphic(IlvGraphic* g);
  IlvGraphic* getInspectedGraphic() const;

  void setUpdated(IlBoolean b);
  IlBoolean needUpdate() const;

  void init();

 protected:
  IlvGraphic* _inspGraphic;
  IlvValueInterface* _valItf;
  IlvClassInfo* _classInfo;

  static IlSymbol* _UpdateSymbol;
  static IlSymbol* _RootItfSymbol;
};


// --------------------------------------------------------------------------
// IlvStpsPropertySheet
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsPropertySheet : public IlvHierarchicalSheet 
{
 public:
  IlvStpsPropertySheet(IlvDisplay* display,const IlvRect& rect,
		       IlUShort nbcol,IlUShort nbrow,
		       IlvDim xgrid=IlvDefaultMatrixWidth,
		       IlvDim ygrid=IlvDefaultMatrixWidth,
		       IlvDim      thickness = IlvDefaultGadgetThickness,
		       IlBoolean  showVSB=IlTrue,
		       IlBoolean  showHSB=IlTrue,
		       IlvPalette* palette = 0);

  ~IlvStpsPropertySheet();

  //---- Displayer ----
  void setDisplayerModelName(IlSymbol* name);
  IlSymbol* getDisplayerModelName() const;

  //---- Events ----
  virtual IlBoolean handleMatrixEvent(IlvEvent&);
  virtual void doIt();
  virtual void editItem(IlUShort col, IlUShort row);
  virtual void validate();
  virtual void focusOut();
  virtual IlvMatrixItemEditor* createEditor(IlUShort col,IlUShort row);
  virtual void  expand(IlvTreeGadgetItem* item);
  virtual IlBoolean handleResizeColumn(IlvEvent&);
  virtual IlBoolean handleResizeRow(IlvEvent&);
  virtual void changeLanguage(const IlSymbol*);  

  virtual void drawItem (IlvPort* dst,
			 IlUShort colno,
			 IlUShort rowno,
			 const IlvRect& itembbox,
			 const IlvRect& clip) const;

  void buildHierarchy(IlvStpsPropertySheetItem* parent,
		      IlBoolean expand = IlFalse);

  void inspect(IlvGraphic* object,IlBoolean add=IlTrue,
	       IlBoolean expand=IlTrue);
  IlvValueTypeClass* getPropertyValueType(IlUShort row) const;

  void updateMatrixItem(IlvStpsPropertySheetItem* propItem,
			IlvValueInterface* valItf=0);

  void updateMatrixNode(IlvStpsPropertySheetItem* propItem);

  virtual void onValueModified(IlUShort col,IlUShort row);

  void applyChange(IlvStpsPropertySheetItem* propItem) const;
  void applyChanges();

  void refreshValue(IlvStpsPropertySheetItem* propItem,
		    IlBoolean propagate=IlTrue);
  void refreshLabels(IlvTreeGadgetItem* root);

  void reset();

  IlvStpsPropertySheetItem* getPropertyItem(IlUShort row) const {
    return ILVDYNAMICCAST(IlvStpsPropertySheetItem*,getTreeItem(row));
  }

  IlvStpsPropertySheetItem* findPropertyItem(IlvValueInterface* valItf,
					     IlvTreeGadgetItem* from) const;

  void setInterfaceName(IlvValueInterface*,const char*);

  virtual IlUInt getCallbackTypes(const char* const**      names,
				  const IlSymbol* const** types) const;
  static IlSymbol* ValueChangedCallbackType()
	{ return _ValueChangedCallback ; }

  void removeListener(IlvGraphic*);

  void enableRefresh(IlBoolean);
  IlBoolean isRefreshEnabled() const;

 protected:
  //---- Displayer ----
  IlvStpsDisplayerModel* _displayerModel;
  IlBoolean _enableRefresh;

  //---- Listener ----
  IlHashTable _listeners;

  //---- Others ----
  IlvPalette* _valItfPal;
  IlvPalette* _classPal;
  IlvPalette* _nullItfPal;
  IlvPalette* _roPal;

  IlvBitmap* _valItfBmp;
  IlvBitmap* _classBmp;

  IlvValue _editedValue;
  IlList _modifiedValues;
  IlvValue* createValue(IlUShort col,IlUShort row) const;

  void removeChildren(IlvTreeGadgetItem* item,IlBoolean reDraw=IlFalse);

  static IlSymbol* _ValueChangedCallback;
};

#endif /* !__IlvSt_Inspectors_Pssheet_H */
