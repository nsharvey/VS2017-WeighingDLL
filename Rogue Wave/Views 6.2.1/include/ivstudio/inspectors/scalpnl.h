// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/scalpnl.h
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
// Declaration of the IlvStISliderPanel class
// Defined in studio inspectors library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Scalpnl_H)
#define __IlvSt_Inspectors_Scalpnl_H

#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#  include <ivstudio/inspectors/gadpnl.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif

class IlvRectangularScale;
class IlvScale;

// --------------------------------------------------------------------------
// IlvStIScaleLabelsAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIScaleLabelsAccessor
    : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIScaleLabelsAccessor(IlvStIPropertyAccessor* = 0,
		              IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			      const char* = 0);
    virtual ~IlvStIScaleLabelsAccessor();

    // ----------------------------------------------------------------------
    IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;

protected:
    IlvScale* getScale() const;
    virtual IlBoolean applyNodes(IlUInt selection);
    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual IlvStIProperty*  createDefaultProperty() const;
};

// --------------------------------------------------------------------------
// IlvStIScaleDivisionsAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIScaleDivisionsAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvStIScaleDivisionsAccessor(IlvStIPropertyAccessor* = 0,
			         IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			         const char* = 0);

protected:
    IlvScale* getScale() { return (IlvScale*)getInspectedObject(); }
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIRectangularScalePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIScalePanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIScalePanel(IlvDisplay*,
		     const char*,
		     const char* = 0,
		     IlvSystemView = 0,
		     IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
    virtual ~IlvStIScalePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeScalePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIScalePanel,
				 IlvStIScalePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStIRcScalePositionAccessor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRcScalePositionAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIRcScalePositionAccessor(IlvStIPropertyAccessor*,
				  IlvStIPropertyAccessor*,
			          UpdateMode = NoUpdate,
			          BuildMode = None,
			          const char* = 0);
    virtual ~IlvStIRcScalePositionAccessor();

    // ----------------------------------------------------------------------
protected:
    IlvStIPropertyAccessor* _dirAccessor;
    IlvRectangularScale* getRectangularScale() const;
    IlvDirection getAccessorDirection() const;

    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIRectangularScalePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRectangularScalePanel
    : public IlvStIScalePanel
{
public:
    IlvStIRectangularScalePanel(IlvDisplay*,
		                const char*,
		                const char* = 0,
		                IlvSystemView = 0,
		                IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStIRectangularScalePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeRectangularScalePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIRectangularScalePanel,
				 IlvStIRectangularScalePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStICircularScalePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICircularScalePanel
    : public IlvStIScalePanel
{
public:
    IlvStICircularScalePanel(IlvDisplay*,
		             const char*,
		             const char* = 0,
		             IlvSystemView = 0,
		             IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);
    virtual ~IlvStICircularScalePanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);

protected:
    void initializeCircularScalePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStICircularScalePanel,
				 IlvStICircularScalePanelBuilder);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_scalpnl)
#endif /* !__IlvSt_Inspectors_Scalpnl_H */
