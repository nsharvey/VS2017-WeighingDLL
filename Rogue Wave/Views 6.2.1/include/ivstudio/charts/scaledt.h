// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/scaledt.h
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
#if !defined(__IlvSt_Charts_Scaledt_H)
#define __IlvSt_Charts_Scaledt_H

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif

#if !defined(__IlvSt_Charts_Stchart_H)
#include <ivstudio/charts/stchart.h>
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
class ILVCHTEXPORTED IlvAbstractScaleDisplayer;
class ILVCHTEXPORTED IlvChartCoordinateInfo;
class ILVGDTEXPORTED IlvTreeGadgetItem;
class ILVINSPCLASS IlvStIPageSelector;
class ILVSTCHARTCLASS IlvStIScalesListEditor;
class ILVSTCHARTCLASS IlvStIProjectorAccessor;
class ILVSTCHARTCLASS IlvStIDisplayersAccessor;

// --------------------------------------------------------------------------
// class IlvStIScalesAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScalesAccessor : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScalesAccessor(IlvStIPropertyAccessor* accessor,
			 IlvStIProjectorAccessor* projAcc,
			 IlvStIAccessor::UpdateMode =
			 IlvStIAccessor::Inherited,
			 const char* name = 0);

    // ----------------------------------------------------------------------
    virtual IlBoolean apply();
    // ----------------------------------------------------------------------
    IlvChartGraphic* getChartGraphic() const;
    void projectionChanged(IlBoolean isPolarProjection);
    IlBoolean isPolarProjection() const { return _isPolarProjection; }
    void setDisplayersAcc(IlvStIDisplayersAccessor* displayersAcc)
	{	_displayersAcc = displayersAcc; }

    virtual void removeProperty(IlUInt, IlBoolean = IlTrue);
    virtual void insertProperty(IlUInt, IlAny = 0);
    void getOrdinateLabel(IlUInt iOrdinate, IlString& result);

protected:
    IlvStIDisplayersAccessor* _displayersAcc;
    IlvStIProjectorAccessor* _projectionAcc;
    IlBoolean _isPolarProjection;
    IlBoolean _projectionChanged;

    IlvAbstractScaleDisplayer*
    ensureScaleDisplayerType(IlvAbstractScaleDisplayer*) const;
    const char* getColorFromPalette(const IlvPalette*) const;
    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual IlvStIProperty*  createDefaultProperty()const;

    virtual void addProperty(IlvStIProperty*, IlUInt);
    virtual void deleteNewProperty(IlvStIProperty* property);
    virtual void deleteProperty(IlvStIProperty* property, IlUInt);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty, IlUInt);

    // calls _lstAccessor->copyProperty() by default
    virtual IlvStIProperty* copyProperty(const IlvStIProperty* property);

    virtual void moveProperty(IlvStIProperty* property,
			      IlUInt previousIndex,
			      IlUInt newIndex);
    void updateOrdinateGridReference(IlvAbstractScaleDisplayer*);
    virtual IlBoolean applyNodes(IlUInt selection);
};

// --------------------------------------------------------------------------
// class IlvStIScalesListEditor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScalesListEditor : public IlvStIIndexedListEditor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIScalesListEditor(IlvStIPropertyListAccessor* accessor,
			   const char* name = 0);

    // ----------------------------------------------------------------------
    void getOrdinateLabel(IlUInt iOrdinate, IlString& result);

protected:
    virtual void getLabel(IlUInt, IlString&) const;

    // flag = 1: adding, flag = 0: initializing, flag = -1: removing
    virtual void propertyCountChanged(IlUInt count, int flag);
    virtual void itemSelected(IlUInt, const IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIScaleSelectorAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScaleSelectorAccessor
: public IlvStIObjectClassAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIScaleSelectorAccessor(IlvStIPropertyAccessor* accessor = 0,
				UpdateMode = NoUpdate,
				BuildMode = None,
				const char* name = 0);
    // ----------------------------------------------------------------------
    static IlSymbol* RectangularSymbol;
    static IlSymbol* CircularSymbol;

protected:
    IlvAbstractScaleDisplayer* getScaleDisplayer(IlAny obj) const;
    virtual const IlSymbol* getObjectType(IlAny) const;
    virtual IlAny createObject(const IlSymbol*) const;
    virtual void   deleteObject(IlAny) const;
    virtual void   setObjectToProperty(IlvStIProperty*, IlAny);
};

// --------------------------------------------------------------------------
// IlvStIScaleAccessor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScaleAccessor : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIScaleAccessor(IlvStIScalesAccessor* accessor,
			IlvStIPropertyAccessor* chartGrapAccessor,
			IlvDisplay* display,
			UpdateMode = NoUpdate,
			BuildMode = None,
			const char* name = 0);
    ~IlvStIScaleAccessor();

    // ----------------------------------------------------------------------
    const char* getMode() const { return _mode; }
    void setMode(const char* mode);
    IlArray& getLabelsArray() { return _labels; }
    IlBoolean isPolarProjection() const
	{	return _scalesAccessor->isPolarProjection(); }

protected:
    IlvDisplay* _display;
    IlString	_mode;
    IlArray	_labels;
    IlvStIPropertyAccessor* _chartGrapAccessor;
    IlvStIScalesAccessor* _scalesAccessor;
    void razLabels();

    const char* getColorFromPalette(const IlvPalette* palette) const;
    IlvAbstractScaleDisplayer* getScaleDisplayer();

    // Need to override in most cases
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
    IlvValue& getFieldValue(IlvStIAgregateProperty*,
			    const char*,
			    IlvValue&) const;
};

// --------------------------------------------------------------------------
// class IlvStIScaleDispLabelsAccessor
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScaleDispLabelsAccessor
: public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScaleDispLabelsAccessor(IlvStIPropertyAccessor* accessor = 0,
				  IlvStIAccessor::UpdateMode =
				  IlvStIAccessor::Inherited,
				  const char* name = 0);
    // ----------------------------------------------------------------------
    IlArray& getLabels() const;

protected:
    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual IlvStIProperty*  createDefaultProperty()const;

    virtual IlBoolean applyNodes(IlUInt);
};

// --------------------------------------------------------------------------
// IlvStIScaleEditor class
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScaleEditor : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScaleEditor(IlvStIScalesAccessor* scalesAccessor,
		      IlvStIPropertyAccessor* chartGrapAccessor,
		      IlvDisplay* display,
		      IlvStIEditor::NotificationMode mode =
		      IlvStIEditor::AsOwner,
		      const char* name = 0);
    ~IlvStIScaleEditor();
};

// --------------------------------------------------------------------------
ILVSTCHARTEXPORTEDFUNCTION(IlvPalette*)
IlvStIGetPalette(IlvDisplay* display,
	         IlvPalette* palette,
	         IlvColor* color,
	         IlBoolean foreground = IlTrue);

// --------------------------------------------------------------------------
IlvDECLAREINITSTCHARTCLASS(sti_cht_scaledt)
// --------------------------------------------------------------------------
#endif /* !__IlvSt_Charts_Scaledt_H */

