// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/chartpnl.h
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
#if !defined(__IlvSt_Charts_Chartpnl_H)
#define __IlvSt_Charts_Chartpnl_H

#if !defined(__IlvSt_Charts_Stchart_H)
#  include <ivstudio/charts/stchart.h>
#endif
#if !defined(__IlvSt_Charts_Stchart_H)
#  include <ivstudio/charts/stchart.h>
#endif
#if !defined(__IlvSt_Charts_Dataitf_H)
#  include <ivstudio/charts/dataitf.h>
#endif
#if !defined(__IlvSt_Charts_Displayitf_H)
#  include <ivstudio/charts/displayitf.h>
#endif
#if !defined(__IlvSt_Gadpnl_H)
#  include <ivstudio/inspectors/gadpnl.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#  include <ilviews/charts/macros.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif
#if !defined(__IlvSt_Inspectors_Listedt_H)
#  include <ivstudio/inspectors/listedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Sheetedt_H)
#  include <ivstudio/inspectors/sheetedt.h>
#endif
#if !defined(__Ilv_Charts_Chart_H)
#  include <ilviews/charts/chart.h>
#endif
#if !defined(__IlvSt_Inspectors_Clselec_H)
#  include <ivstudio/inspectors/clselec.h>
#endif
#if !defined(__IlvSt_Inspectors_Genselpg_H)
#  include <ivstudio/inspectors/genselpg.h>
#endif

class ILVCHTEXPORTED IlvChartGraphic;
class ILVCHTEXPORTED IlvAbstractProjector;
class ILVCHTEXPORTED IlvAbstractChartData;
class ILVCHTEXPORTED IlvChartPointSet;
class ILVGDTEXPORTED IlvSheet;
class ILVGDTEXPORTED IlvAbstractMatrixItem;
class ILVCHTEXPORTED IlvChartDataSet;
class ILVCHTEXPORTED IlvChartYValueSet;
class ILVGDTEXPORTED IlvStringList;
class ILVGDTEXPORTED IlvTreeGadget;
class ILVGDTEXPORTED IlvChartInteractorManager;
class ILVINSPCLASS IlvStICheckedStringList;
class ILVSTCHARTCLASS IlvStIGenericDisplayersAccessor;
class ILVSTCHARTCLASS IlvStIScalesAccessor;
class ILVSTCHARTCLASS IlvStIDisplayerDataSelector;
class ILVSTCHARTCLASS IlvStIChartPanel;
class ILVVWSEXPORTED IlvScriptContext;

// --------------------------------------------------------------------------
// class IlvStIDataSetsAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDataSetsAccessor
    : public IlvStIPropertyListAccessor
{
public:
    IlvStIDataSetsAccessor(IlvStIPropertyAccessor* = 0,
			   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			   const char* = 0);

    IlvAbstractChartData*	getChartData() const;
    void		checkData(IlUInt, IlBoolean = IlTrue);
    void		checkIndexes(const IlArray&);
    void		uncheckData(IlBoolean = IlFalse);
    virtual void	removeProperty(IlUInt, IlBoolean = IlTrue);
    virtual void	insertProperty(IlUInt, IlAny = 0);
    void      setDisplayerDataSelector(IlvStIDisplayerDataSelector* selector)
	{	_selector = selector; }

protected:
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createDefaultProperty()const;

    virtual void	addProperty(IlvStIProperty*, IlUInt);
    virtual void	deleteNewProperty(IlvStIProperty* property);
    virtual void	deleteProperty(IlvStIProperty* property, IlUInt);
    virtual void	replaceProperty(IlvStIProperty* origProperty,
					IlvStIProperty* newProperty, IlUInt);
    virtual
    IlvStIProperty*	copyProperty(const IlvStIProperty* property);
    // calls _lstAccessor->copyProperty() by default

    IlvStIDisplayerDataSelector* _selector;
};

// --------------------------------------------------------------------------
// class IlvStIDataSetsListEditor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDataSetsListEditor
    : public IlvStIPropertyListEditor
{
public:
    IlvStIDataSetsListEditor(IlvStIPropertyListAccessor*,
			     IlBoolean = IlFalse,
			     IlBoolean = IlTrue,
			     const char* = 0);

    virtual IlBoolean	connectHolder(IlvGraphicHolder*);
    void		checkData(IlUInt, IlBoolean = IlTrue);
    void		uncheckData(IlBoolean = IlFalse);
    void		checkIndexes(const IlArray&);

protected:
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;
    virtual void	propertyCountChanged(IlUInt, int);
    // flag = 1: adding, flag = 0: initializing, flag = -1: removing

    virtual void	selectedItemCallback();
    virtual void	setItemSelected(IlUInt);
    virtual void	refreshSelection();
    void		initDataSetGadgetItem(IlvGadgetItem*,
					      const IlvStIProperty*) const;

    IlBoolean			_check;
    IlBoolean			_notifySelection;
    IlvStICheckedStringList*	_checkedList;
    IlString			_dataSetFmt;
};

// --------------------------------------------------------------------------
// IlvStIDataSetAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDataSetAccessor
    : public IlvStIObjectClassAccessor
{
public:
    IlvStIDataSetAccessor(IlvStIPropertyAccessor*,
			  IlvStIPropertyAccessor*,
			  IlvStIChartPanel*,
			  UpdateMode = NoUpdate,
			  BuildMode = Copy,
			  const char* = 0);
    ~IlvStIDataSetAccessor();

protected:
    IlvChartDataSet*	getDataSet(IlAny) const;
    virtual
    const IlSymbol*	getObjectType(IlAny) const;
    virtual IlAny	createObject(const IlSymbol*) const;
    virtual void	deleteObject(IlAny) const;
    virtual void	setObjectToProperty(IlvStIProperty*, IlAny);
    virtual IlAny	copyObject(IlAny) const;

    IlvStIPropertyAccessor*	_chartAccessor;
    IlvStIChartPanel*		_chartPanel;
};

// --------------------------------------------------------------------------
// class IlvStIChartPointsAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIChartPointsAccessor
    : public IlvStIPropertySheetAccessor
{
public:
    IlvStIChartPointsAccessor(IlvStIPropertyAccessor* = 0,
			      IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			      IlvStIAccessor::BuildMode =
							IlvStIAccessor::Copy,
			      const char* = 0);

    IlvChartPointSet*	getChartPointSet() const;
    static void		GetPropertyPoint(const IlvStIProperty*,
					 IlvDoublePoint&);
    virtual
    IlvAbstractMatrixItem*	createMatrixItem(const IlvStIProperty*,
						 IlUInt, IlUInt) const;

protected:
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createDefaultProperty()const;

    virtual void	addProperty(IlvStIProperty*, IlUInt);
    virtual void	deleteNewProperty(IlvStIProperty*);
    virtual void	deleteProperty(IlvStIProperty*, IlUInt);
    virtual void	replaceProperty(IlvStIProperty*,
					IlvStIProperty*, IlUInt);
    virtual void	propertyFieldChanged(IlvStIProperty*,
					     IlUInt, IlvAbstractMatrixItem*);
};

// --------------------------------------------------------------------------
// class IlvStIYValuesAccessor
// --------------------------------------------------------------------------
 class ILVSTCHARTCLASS IlvStIYValuesAccessor
     : public IlvStIPropertySheetAccessor
{
public:
    IlvStIYValuesAccessor(IlvStIPropertyAccessor* = 0,
			  IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			  IlvStIAccessor::BuildMode = IlvStIAccessor::Copy,
			  const char* = 0);

    IlvChartYValueSet*	getYValuesSet() const;
    static void		GetPropertyPoint(const IlvStIProperty*,
					 IlvDoublePoint&);
    virtual
    IlvAbstractMatrixItem*	createMatrixItem(const IlvStIProperty*,
						 IlUInt, IlUInt) const;

protected:
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createDefaultProperty()const;

    virtual void	addProperty(IlvStIProperty*, IlUInt);
    virtual void	deleteNewProperty(IlvStIProperty*);
    virtual void	deleteProperty(IlvStIProperty*, IlUInt);
    virtual void	replaceProperty(IlvStIProperty*,
					IlvStIProperty*, IlUInt);
    virtual void	propertyFieldChanged(IlvStIProperty*,
					     IlUInt, IlvAbstractMatrixItem*);
};

// --------------------------------------------------------------------------
// IlvStIProjectorAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIProjectorAccessor
    : public IlvStIObjectClassAccessor
{
public:
    IlvStIProjectorAccessor(IlvStIPropertyAccessor*,
			    UpdateMode = NoUpdate,
			    BuildMode = None,
			    const char* = 0);

    void		setScalesAccessor(IlvStIScalesAccessor*);
    virtual void	setType(const IlSymbol*);

    static IlSymbol*	CartesianSymbol;
    static IlSymbol*	PolarSymbol;

protected:
    IlvChartGraphic*	getChartGraphic() const;
    IlvAbstractProjector*	getProjector(IlAny) const;
    virtual IlAny	getObjectFromProperty(const IlvStIProperty*) const;
    virtual
    const IlSymbol*	getObjectType(IlAny) const;
    virtual IlAny	createObject(const IlSymbol*) const;
    virtual void	deleteObject(IlAny) const;
    virtual void	setObjectToProperty(IlvStIProperty*, IlAny);

    IlvStIScalesAccessor*	_scalesAcc;
};

// --------------------------------------------------------------------------
// IlvStIDisplayerDataSelector class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerDataSelector
    : public IlvStIEditorSet
{
public:
    IlvStIDisplayerDataSelector(const char*,
				const char*);
    virtual ~IlvStIDisplayerDataSelector();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean	connectHolder(IlvGraphicHolder*);
    virtual IlBoolean	initialize();
    // ----------------------------------------------------------------------
    void		setSelectors(IlvStIPageSelector*,
				     IlvStIPageSelector*);
    void		setAccessors(IlvStIGenericDisplayersAccessor*,
				     IlvStIDataSetsAccessor*);
    void		dataSetRemoved(IlUInt, IlUInt);
    void		dataSetInserted(IlUInt, IlUInt);
    void		checkData(IlUInt, IlBoolean = IlTrue);
    IlUInt		getSelectedData() const;

    void		dataSelected();
    void		displayerSelected();

protected:
    virtual IlUShort	getCurrentSelectedPage() const;
    void		dataChecked(IlUInt, IlBoolean);
    void		displayerChecked(IlUInt, IlBoolean);

    IlString				_dataListName;
    IlString				_treeDisplayersName;
    IlvStIPageSelector*			_dataTypeSelector;
    IlvStIPageSelector*			_displayerTypeSelector;
    IlvStICheckedStringList*		_checkedDataList;
    IlUShort				_currentSelectedPage;
    IlvStIGenericDisplayersAccessor*	_displayersAcc;
    IlvStIDataSetsAccessor*		_dataSetsAcc;

public:
    static void		SelectDataCallback(IlvGraphic*, IlAny);
    static void		SelectDisplayerCallback(IlvGraphic*, IlAny);
    static void		DataCheckedCallback(IlvGadgetItemHolder*,
					    IlvGadgetItem*,
					    IlBoolean, IlBoolean, IlAny);
    static void		DisplayerCheckedCallback(IlvGadgetItemHolder*,
						 IlvGadgetItem*,
						 IlBoolean, IlBoolean,
						 IlAny);
};

// --------------------------------------------------------------------------
// IlvStIChartLayoutAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIChartLayoutAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvStIChartLayoutAccessor(IlvStIPropertyAccessor*,
			      UpdateMode = NoUpdate,
		 	      BuildMode = None,
			      const char* = 0);

protected:
    IlvValue&		getFieldValue(IlvStIAgregateProperty*,
				      const char*,
				      IlvValue&) const;
    void		setFieldValue(IlvStIAgregateProperty*,
				      const char*,
				      const IlvStValue&) const;
    IlvChartGraphic*	getChartGraphic();
    virtual
    IlvStIProperty*	getOriginalValue();
    virtual void	applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIChartMiscAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIChartMiscAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvStIChartMiscAccessor(IlvStIPropertyAccessor*,
			    IlvDisplay*,
			    UpdateMode = NoUpdate,
		 	    BuildMode = None,
			    const char* = 0);

protected:
    IlvValue&		getFieldValue(IlvStIAgregateProperty*,
				      const char*,
				      IlvValue&) const;
    void		setFieldValue(IlvStIAgregateProperty*,
				      const char*,
				      const IlvStValue&) const;
    IlvChartGraphic*	getChartGraphic();
    const char*		getColorNameFromPalette(const IlvPalette*) const;
    const char*		getColorNameFromColor(const IlvColor*) const;
    virtual IlvStIProperty*	getOriginalValue();
    virtual void	applyValue(IlvStIProperty*);

    IlvDisplay*		_display;
};

// --------------------------------------------------------------------------
// class IlvStILegendListEditor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStILegendListEditor
    : public IlvStIListEditor
{
public:
    IlvStILegendListEditor(const char* = 0,
			   IlvStIPropertyAccessor* = 0,
			   NotificationMode = AsOwner);
    ~IlvStILegendListEditor();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();

    virtual
    IlvStIPropertyAccessor*	getAccessor() const { return 0; }

protected:
    IlvChartGraphic*	getChartGraphic() const;

    virtual void	fillListGadget();
    virtual void	onListNotification();
};

// --------------------------------------------------------------------------
// class IlvStIChartInteractorsAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIChartInteractorsAccessor
    : public IlvStIPropertyListAccessor
{
public:
    IlvStIChartInteractorsAccessor(IlvStIPropertyAccessor* = 0,
				   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				   const char* = 0);

    IlvChartInteractorManager*	getInteractorManager() const;
    virtual IlvGadgetItem*     createGadgetItem(const IlvStIProperty*) const;

protected:
    virtual IlBoolean		applyNodes(IlUInt);
    virtual IlvStIProperty**	getInitialProperties(IlUInt&);
    virtual IlvStIProperty*	createDefaultProperty() const;
};

// --------------------------------------------------------------------------
// class IlvStIChartPanel
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIChartPanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIChartPanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    ~IlvStIChartPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

    inline IlList*	getDataSetInterfaces() const
	{ return _dataSetInterfaces; }
    void		registerDataSetInterface(IlvStIDataSetInterface*);
    inline IlList*	getDisplayerInterfaces() const
	{ return _displayerInterfaces; }
    void	       registerDisplayerInterface(IlvStIDisplayerInterface*);

protected:
    void		initializeChartPanel();

    IlList*		_dataSetInterfaces;
    IlList*		_displayerInterfaces;
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilderExp(IlvStIChartPanel,
				    IlvStIChartPanelBuilder,
				    ILVSTCHARTCLASS);

// --------------------------------------------------------------------------
IlvDECLAREINITSTCHARTCLASS(sti_cht_chartpnl)
#endif /* !__IlvSt_Charts_Chartpnl_H */
