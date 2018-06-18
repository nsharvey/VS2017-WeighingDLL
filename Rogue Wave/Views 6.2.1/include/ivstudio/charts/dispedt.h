// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/dispedt.h
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
// Declaration of the IlvStIChartPanel class
// Defined in studio charts library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Charts_Dispedt_H)
#define __IlvSt_Charts_Dispedt_H

#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif

#if !defined(__IlvSt_Charts_Stchart_H)
#include <ivstudio/charts/stchart.h>
#endif

#if !defined(__IlvSt_Charts_Displayitf_H)
#include <ivstudio/charts/displayitf.h>
#endif

#if !defined(__IlvSt_Listacc_H)
#include <ivstudio/inspectors/listacc.h>
#endif

#if !defined(__IlvSt_Listedt_H)
#include <ivstudio/inspectors/listedt.h>
#endif

#if !defined(__IlvSt_Sheetedt_H)
#include <ivstudio/inspectors/sheetedt.h>
#endif

#if !defined(__IlvSt_Clselec_H)
#include <ivstudio/inspectors/clselec.h>
#endif

class ILVCHTEXPORTED IlvChartGraphic;
class ILVCHTEXPORTED IlvAbstractChartDisplayer;
class ILVCHTEXPORTED IlvChartDisplayerFactory;
class ILVCHTEXPORTED IlvScatterChartDisplayer;
class ILVCHTEXPORTED IlvFixedStepChartDisplayer;
class ILVCHTEXPORTED IlvBarChartDisplayer;
class ILVCHTEXPORTED Ilv3dBarChartDisplayer;
class ILVCHTEXPORTED IlvHiLoChartDisplayer;
class ILVCHTEXPORTED IlvBubbleChartDisplayer;
class ILVCHTEXPORTED IlvStackedChartDisplayer;
class ILVGDTEXPORTED IlvTreeGadgetItem;
class ILVINSPCLASS IlvStIPageSelector;
class ILVSTCHARTCLASS IlvStIDataSetsListEditor;
class ILVSTCHARTCLASS IlvStIDisplayerDataSelector;
class ILVSTCHARTCLASS IlvStIScalesAccessor;
class ILVSTCHARTCLASS IlvStIChartPanel;

// --------------------------------------------------------------------------
// class IlvStIGenericDisplayersAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIGenericDisplayersAccessor 
: public IlvStIPropertyTreeAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGenericDisplayersAccessor(IlvStringList* displayerTypeList,
				    IlvStIPropertyAccessor* accessor = 0,
				    IlvStIAccessor::UpdateMode =
				    IlvStIAccessor::Inherited,
				    const char* name = 0);
    ~IlvStIGenericDisplayersAccessor();
    // ----------------------------------------------------------------------
    IlAny findPropertyNode(const IlvStIProperty*,
			   IlAny* parent = 0,
			   IlUInt* index = 0,
			   IlInt* level = 0);
    void checkOnData(IlUInt nDataIndex);
    void checkDisplayer(IlUInt nDisplayer, IlBoolean = IlTrue);
    void uncheckDisplayers(IlBoolean invalidate = IlTrue);
    void getDataIndexes(IlUInt nDisplayer, IlArray&) const;
    void dataSetRemoved(IlUInt nDataSet, IlUInt nDataCount);
    void dataSetInserted(IlUInt nDataSet, IlUInt nDataCount);
    void dataChecked(IlUInt, IlBoolean);
    void displayerChecked(IlUInt, IlUInt nDataSet, IlBoolean);
    IlBoolean isDisplayerChecked(IlUInt iDisplayer) const;
    void setDisplayerDataSelector(IlvStIDisplayerDataSelector* selector)
	{	_selector = selector; }
    IlBoolean ensureDataSetListCorrect(
				       IlUInt,
				       IlArray* = 0);

    void ordinateAxisInserted(IlUInt nAxis, IlUInt nOAxisCount);
    void ordinateAxisRemoved(IlUInt nAxis, IlUInt nOAxisCount);
    void displayerAxisChanged(IlUInt nAxisIndex,
			      IlUInt nDisplayer = (IlUInt)-1);
    IlUInt getDisplayerAxis(IlUInt nDisplayer = (IlUInt)-1);
    void razDisplayersAxis();
    void razDisplayersData();
    IlArray& getDisplayersData() { return _displayersData; }
    IlArray& getDisplayersAxis() { return _displayersAxis; }
    IlAny getSelectionNode(IlAny& parent,
			   IlUInt& childPosition) const;
    virtual void insertProperty(IlAny parent, IlUInt childIndex, IlAny = 0);
    virtual void removeProperty(IlUInt, IlBoolean = IlTrue);
    void updateEditorLabels(int flag);
    IlBoolean isMultiChildSelected() const;
    void selectionBecomesMulti(IlBoolean multi, IlBoolean wasMulti);

protected:
    IlvStringList* _displayerTypeList;
    IlvStIDisplayerDataSelector* _selector;
    IlArray _displayersData;
    IlArray _displayersAxis;
    IlBoolean _updateOnSelection;

    void updateOnSelection(int flag);
    IlAny findNode(const IlvStIProperty*,
		   IlAny* parent = 0,
		   IlUInt* index = 0,
		   IlInt* level = 0,
		   IlAny parentNode = 0) const;

    IlvAbstractChartDisplayer* getDisplayer(const IlvStIProperty*) const;
    //virtual IlvStIProperty** getInitialChildrenProperties(
    //				IlUInt&,
    //				const IlvStIProperty* = 0) const;
    virtual IlvStIProperty*  createDefaultProperty()const;

    //virtual void moveProperty(IlvStIProperty* property,
    //			      IlUInt previousIndex,
    //			      IlUInt newIndex);
    //virtual void addProperty(IlvStIProperty*,
    //			     const IlvStIProperty* parent,
    //			     IlUInt);
    //virtual void deleteNewProperty(IlvStIProperty* property);
    //virtual void deleteChildrenProperty(IlvStIProperty* property,
    //				        IlvStIProperty* parent);
    //virtual void replaceProperty(IlvStIProperty* origProperty,
    //		      	           IlvStIProperty* newProperty,
    // 		      	           const IlvStIProperty* parent,
    // 		      	           IlUInt childPosition);
    //virtual IlUInt getChildPosition(const IlvStIProperty*,
    //				     const IlvStIProperty*) const;

    // calls _lstAccessor->copyProperty() by default
    virtual IlvStIProperty* copyProperty(const IlvStIProperty* property);
    //virtual IlBoolean applyNodes(IlUInt);
};

// --------------------------------------------------------------------------
// class IlvStIDisplayersAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayersAccessor
: public IlvStIGenericDisplayersAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIDisplayersAccessor(IlvStringList* displayerTypeList,
			     IlvStIPropertyAccessor* accessor = 0,
			     IlvStIAccessor::UpdateMode =
			     IlvStIAccessor::Inherited,
			     const char* name = 0);
    ~IlvStIDisplayersAccessor();

protected:

    IlvChartGraphic* getChartGraphic() const;

    virtual IlvStIProperty** getInitialChildrenProperties(
					IlUInt&,
					const IlvStIProperty* = 0) const;

    virtual void moveProperty(IlvStIProperty* property,
			      IlUInt previousIndex,
			      IlUInt newIndex);
    virtual void addProperty(IlvStIProperty*,
			     const IlvStIProperty* parent,
			     IlUInt);
    virtual void deleteNewProperty(IlvStIProperty* property);
    virtual void deleteChildrenProperty(IlvStIProperty* property,
				        IlvStIProperty* parent);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty,
				 const IlvStIProperty* parent,
				 IlUInt childPosition);
    virtual IlUInt getChildPosition(const IlvStIProperty*,
				    const IlvStIProperty*) const;
    virtual IlBoolean applyNodes(IlUInt);
};

// --------------------------------------------------------------------------
// class IlvStIDisplayersTreeEditor
// --------------------------------------------------------------------------

class ILVSTCHARTCLASS IlvStIDisplayersTreeEditor
: public IlvStIPropertyTreeEditor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIDisplayersTreeEditor(IlvStIPropertyTreeAccessor* accessor,
			       IlBoolean check = IlFalse,
			       IlBoolean bNotifySelection = IlTrue,
			       const char* name = 0);
    ~IlvStIDisplayersTreeEditor();

    // ----------------------------------------------------------------------
    void declareTreeGadgets(const char* treeName,
			    const char* addAfterName = 0,
			    const char* removeName = 0,
			    const char* addChildName = 0,
			    const char* addBeforeName = 0,
			    const char* cleanName = 0,
			    const char* up = 0,
			    const char* down = 0);
    virtual IlBoolean connectHolder(IlvGraphicHolder* holder);
    void checkDisplayer(IlUInt nDisplayer, IlBoolean = IlTrue);
    void uncheckDisplayers(IlBoolean invalidate = IlTrue);

    // flag = 1: adding, flag = 0: initializing, flag = -1: removing
    virtual void propertyCountChanged(IlUInt count, int flag);

protected:
    IlString _DisplayersFmt;
    IlString _upName;
    IlString _downName;
    IlBoolean _check;
    IlBoolean _notifySelection;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty* prop)const;
    virtual IlvTreeGadgetItem* findTreeGadgetItem(
					const IlvStIProperty* prop,
					IlvTreeGadgetItem* parent = 0) const;
    virtual void moveUpDownCallback(IlBoolean up);
    virtual void moveCallback(IlUInt previousIndex, IlUInt newIndex);
    virtual void selectedItemCallback();
    virtual void treeItemSelected(IlvTreeGadgetItem* treeItem,
				  const IlvStIProperty* property,
				  const IlvStIProperty* parent);
    virtual void setItemSelected(IlUInt index);
    virtual void refreshSelection();
    IlBoolean ensureLabels(IlvTreeGadgetItem* parent);
    IlBoolean initDispGadgetItem(IlvGadgetItem* gadItem,
				 const IlvStIProperty* dispProp,
				 IlUInt* index = 0,
				 IlInt* level = 0) const;

public:
    static void MoveUpCallback(IlvGraphic*, IlAny arg);
    static void MoveDownCallback(IlvGraphic*, IlAny arg);
};

// --------------------------------------------------------------------------
// IlvStIDisplayerAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerAccessor
: public IlvStIObjectClassAccessor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIDisplayerAccessor(IlvStIGenericDisplayersAccessor* dispsAcc,
			    IlvStIChartPanel* chartPanel,
			    UpdateMode = NoUpdate,
			    BuildMode = Copy,
			    const char* name = 0);
    ~IlvStIDisplayerAccessor();

protected:
    IlvStIGenericDisplayersAccessor* _dispsAcc;
    IlvStIChartPanel*         _chartPanel;

    IlvAbstractChartDisplayer* getDisplayer(IlAny obj) const;
    virtual const IlSymbol* getObjectType(IlAny) const;
    virtual IlAny createObject(const IlSymbol*) const;
    virtual void objectTypeChanged(const IlSymbol*, const IlSymbol*);
    IlBoolean isMultiType(const IlSymbol*) const;
    virtual void   deleteObject(IlAny) const;
    virtual void   setObjectToProperty(IlvStIProperty*, IlAny);
    virtual IlAny copyObject(IlAny object) const;
};

// --------------------------------------------------------------------------
// IlvStIDisplayerAxisEditor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerAxisEditor : public IlvStIListEditor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIDisplayerAxisEditor(IlvStIGenericDisplayersAccessor* dispsAcc,
			      IlvStIScalesAccessor* scalesAcc,
			      const char* name,
			      NotificationMode = AsOwner);

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean		initialize();

    // ----------------------------------------------------------------------
protected:
    IlvStIGenericDisplayersAccessor* _dispsAcc;
    IlvStIScalesAccessor* _scalesAcc;

    virtual void fillListGadget();
    virtual void onListNotification();
};

// --------------------------------------------------------------------------
// IlvStIScatterDisplayerAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScatterDisplayerAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIScatterDisplayerAccessor(IlvStIPropertyAccessor* accessor,
				   const char* name = 0,
				   UpdateMode updateMode = NoUpdate,
				   BuildMode buildMode = None);

protected:
    IlvScatterChartDisplayer* getInspectedObject();
};

// --------------------------------------------------------------------------
// IlvStIDisplayerMarkerSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerMarkerSizeAccessor
: public IlvStIScatterDisplayerAccessor
{
public:
    IlvStIDisplayerMarkerSizeAccessor(IlvStIPropertyAccessor* accessor,
				      const char* name = 0,
				      UpdateMode updateMode = NoUpdate,
				      BuildMode buildMode = None);

protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIDisplayerMarkerTypeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerMarkerTypeAccessor
: public IlvStIScatterDisplayerAccessor
{
public:
    IlvStIDisplayerMarkerTypeAccessor(IlvStIPropertyAccessor* accessor,
				      const char* name = 0,
				      UpdateMode updateMode = NoUpdate,
				      BuildMode buildMode = None);

protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIDisplayerForeColorAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerForeColorAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIDisplayerForeColorAccessor(IlvStIPropertyAccessor* accessor,
				     IlvDisplay* display,
				     const char* name = 0,
				     UpdateMode updateMode = NoUpdate,
				     BuildMode buildMode = None);

protected:
    IlvDisplay* _display;

    IlvAbstractChartDisplayer* getInspectedObject();

    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIDisplayerFallForeColorAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerFallForeColorAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIDisplayerFallForeColorAccessor(IlvStIPropertyAccessor* accessor,
					 IlvDisplay* display,
					 const char* name = 0,
					 UpdateMode updateMode = NoUpdate,
					 BuildMode buildMode = None);

protected:
    IlvDisplay* _display;

    IlvHiLoChartDisplayer* getInspectedObject();

    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIHiLoSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIHiLoSizeAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIHiLoSizeAccessor(IlvStIPropertyAccessor* accessor = 0,
			   const char* name = 0,
			   UpdateMode updateMode = NoUpdate,
			   BuildMode buildMode = None);

protected:
    IlvHiLoChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIStepSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStepSizeAccessor : public IlvStICombinedAccessor
{
public:
    IlvStIStepSizeAccessor(IlvStIPropertyAccessor* accessor = 0,
			   const char* name = 0,
			   UpdateMode updateMode = NoUpdate,
			   BuildMode buildMode = None);

protected:
    IlvFixedStepChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};


// --------------------------------------------------------------------------
// IlvStIBarSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBarSizeAccessor : public IlvStICombinedAccessor
{
public:
    IlvStIBarSizeAccessor(IlvStIPropertyAccessor* accessor = 0,
			  const char* name = 0,
			  UpdateMode updateMode = NoUpdate,
			  BuildMode buildMode = None);

protected:
    IlvBarChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIBarDepthAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBarDepthAccessor : public IlvStICombinedAccessor
{
public:
    IlvStIBarDepthAccessor(IlvStIPropertyAccessor* accessor = 0,
			   const char* name = 0,
			   UpdateMode updateMode = NoUpdate,
			   BuildMode buildMode = None);

protected:
    Ilv3dBarChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIBubbleGraphicModelAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBubbleGraphicModelAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIBubbleGraphicModelAccessor(IlvStIPropertyAccessor* accessor = 0,
				     const char* name = 0,
				     UpdateMode updateMode = NoUpdate,
				     BuildMode buildMode = None);

protected:
    IlvBubbleChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};


// --------------------------------------------------------------------------
// IlvStIBubbleMaxSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBubbleMaxSizeAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIBubbleMaxSizeAccessor(IlvStIPropertyAccessor* accessor = 0,
				const char* name = 0,
				UpdateMode updateMode = NoUpdate,
				BuildMode buildMode = None);

protected:
    IlvBubbleChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIBubbleMinSizeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBubbleMinSizeAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIBubbleMinSizeAccessor(IlvStIPropertyAccessor* accessor = 0,
				const char* name = 0,
				UpdateMode updateMode = NoUpdate,
				BuildMode buildMode = None);

protected:
    IlvBubbleChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIBubbleSizeModeAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBubbleSizeModeAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIBubbleSizeModeAccessor(IlvStIPropertyAccessor* accessor = 0,
				 const char* name = 0,
				 UpdateMode updateMode = NoUpdate,
				 BuildMode buildMode = None);

protected:
    IlvBubbleChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIBubbleScalingAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBubbleScalingAccessor
: public IlvStICombinedAccessor
{
public:
    IlvStIBubbleScalingAccessor(IlvStIPropertyAccessor* accessor = 0,
				const char* name = 0,
				UpdateMode updateMode = NoUpdate,
				BuildMode buildMode = None);

protected:
    IlvBubbleChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIStacked100Accessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStacked100Accessor
: public IlvStICombinedAccessor
{
public:
    IlvStIStacked100Accessor(IlvStIPropertyAccessor* accessor = 0,
			     const char* name = 0,
			     UpdateMode updateMode = NoUpdate,
			     BuildMode buildMode = None);

protected:
    IlvStackedChartDisplayer* getInspectedObject();
    virtual IlvStIProperty* getOriginalValue();
    virtual void applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIPieSlice class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIPieSlice
{
public:
    IlvStIPieSlice(IlvPalette* palette,
		   IlBoolean tearOff,
		   const char* text):
	_palette(palette),
	_tearOff(tearOff),
	_text(text)
	{}

    IlvPalette* _palette;
    IlBoolean  _tearOff;
    IlString   _text;
};

// --------------------------------------------------------------------------
// IlvStIPieAccessor class
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPieChartDisplayer;

class ILVSTCHARTCLASS IlvStIPieAccessor : public IlvStICombinedAccessor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPieAccessor(IlvStIPropertyAccessor* accessor,
		      IlvDisplay* display,
		      UpdateMode = NoUpdate,
		      BuildMode = None,
		      const char* name = 0);
    ~IlvStIPieAccessor();

    // ----------------------------------------------------------------------
    IlArray& getSlices() { return _slices; }
    const char* getColorFromPalette(const IlvPalette* palette) const;
    IlvDisplay* getDisplay() const { return _display; }

protected:
    IlvDisplay* _display;
    IlArray	_slices;
    void razSlices();

    IlvPieChartDisplayer* getPie();

    // Need to override in most cases
    virtual IlvStIProperty* getOriginalValue();

    virtual void            applyValue(IlvStIProperty*);
    IlvValue& getFieldValue(IlvStIAgregateProperty*,
			    const char*,
			    IlvValue&) const;
    void setFieldValue(IlvStIAgregateProperty*,
		       const char*,
		       const IlvStValue&) const;
};

// --------------------------------------------------------------------------
// class IlvStIPieSlicesAccessor
// --------------------------------------------------------------------------

class ILVSTCHARTCLASS IlvStIPieSlicesAccessor
: public IlvStIPropertyListAccessor
{
public:
    IlvStIPieSlicesAccessor(IlvStIPieAccessor* accessor = 0,
			    IlvStIAccessor::UpdateMode =
			    IlvStIAccessor::Inherited,
			    const char* name = 0);
    // ----------------------------------------------------------------------
    IlArray& getSlices() const;
    IlvDisplay* getDisplay() const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;

protected:
    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual IlvStIProperty*  createDefaultProperty()const;
    void fillPieSlice(IlvStIPieSlice*, const IlvStIProperty*) const;
    IlvValue& getFieldValue(IlvStIAgregateProperty*,
			    const char*,
			    IlvValue&) const;

    virtual void addProperty(IlvStIProperty*, IlUInt);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty,
				 IlUInt);
    virtual void moveProperty(IlvStIProperty*,
			      IlUInt previousIndex,
			      IlUInt newIndex);
    virtual void deleteProperty(IlvStIProperty* prop, IlUInt);
    virtual IlvStIProperty* copyProperty(const IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStIPolylineOrPointsAccessor class
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvMarkedPolylineChartDisplayer;

class ILVSTCHARTCLASS IlvStIPolylineOrPointsAccessor
: public IlvStICombinedAccessor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPolylineOrPointsAccessor(IlvStIPropertyAccessor* accessor,
				   IlvDisplay* display,
				   UpdateMode = NoUpdate,
				   BuildMode = None,
				   const char* name = 0);
    ~IlvStIPolylineOrPointsAccessor();

    // ----------------------------------------------------------------------
    IlvDisplay* getDisplay() const { return _display; }

protected:
    IlvDisplay* _display;

    IlvMarkedPolylineChartDisplayer* getInspectedObject();

    // Need to override in most cases
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
    IlvValue& getFieldValue(IlvStIAgregateProperty*,
			    const char*,
			    IlvValue&) const;
    void setFieldValue(IlvStIAgregateProperty*,
		       const char*,
		       const IlvStValue&) const;
};

// --------------------------------------------------------------------------
// IlvStIDisplayerEditor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStInspectorPanel;

class ILVSTCHARTCLASS IlvStIDisplayerEditor : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIDisplayerEditor(IlvStIGenericDisplayersAccessor* dispsAcc,
			  IlvStIScalesAccessor* scalesAcc,
			  IlvStIChartPanel* panel,
			  IlvGraphicHolder* holder,
			  const char* displayerSelectorName,
			  const char* displayerRectangleName,
			  IlvStIEditor::NotificationMode mode =
			  IlvStIEditor::AsOwner,
			  const char* name = 0);
    ~IlvStIDisplayerEditor();

    // ----------------------------------------------------------------------
    virtual IlBoolean connectHolder(IlvGraphicHolder* holder);
    IlArray* getGeneralPageEditors() { return _generalPageEditors; }
    IlvStIListPageSelector* getDisplayerSelector() const
		{ return _displayerSelector; }
    IlvStIGenericDisplayersAccessor* getDisplayersAccessor() const
		{ return _displayersAccessor; }
    IlvStIScalesAccessor* getScalesAccessor() const { return _scalesAccessor; }

protected:
    IlArray*                  _generalPageEditors;
    IlvStIListPageSelector*    _displayerSelector;
    IlvStIGenericDisplayersAccessor*  _displayersAccessor;
    IlvStIScalesAccessor*      _scalesAccessor;
    IlvGraphicHolder*          _pageHolder;

};

// --------------------------------------------------------------------------
// IlvStIEditorHolder class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIEditorHolder
{
public:
    IlString _holderName;
    IlvStIEditor* _editor;

    IlvStIEditorHolder(const char* holderName, IlvStIEditor* editor):
	_holderName(holderName), _editor(editor) {}
};

// --------------------------------------------------------------------------
IlvDECLAREINITSTCHARTCLASS(sti_cht_dispedt)
// --------------------------------------------------------------------------
#endif /* !__IlvSt_Charts_Dispedt_H */

