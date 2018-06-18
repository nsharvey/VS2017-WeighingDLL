// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/rectpnl.h
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
// Declaration of the IlvStIContainerRectanglePanel class
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Rectpnl_H)
#define __IlvSt_Inspectors_Rectpnl_H

#if !defined(__IlvSt_Inspectors_Gadpnl_H)
#  include <ivstudio/inspectors/gadpnl.h>
#endif

class IlvGadgetContainerRectangle;
class IlvSCGadgetContainerRectangle;
class IlvSCManagerRectangle;
class IlvManagerRectangle;

// --------------------------------------------------------------------------
// IlvStIContRectFilenameAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIContainerRectangleAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIContainerRectangleAccessor(IlvStIPropertyAccessor* = 0,
				     IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				     const char* = 0);

protected:
    IlvGadgetContainerRectangle* getRectangle() const;
};

// --------------------------------------------------------------------------
// IlvStIContRectFilenameAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIContRectFilenameAccessor
    : public IlvStIContainerRectangleAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIContRectFilenameAccessor(IlvStIPropertyAccessor* = 0,
				   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				   const char* = 0);

protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStIContainerRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIContainerRectanglePanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIContainerRectanglePanel(IlvDisplay*,
				  const char*,
				  const char* = 0,
				  IlvSystemView = 0,
				  IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
protected:
    void initializeContainerRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIContainerRectanglePanel,
				 IlvStIContainerRectanglePanelBuilder);

// --------------------------------------------------------------------------
// IlvStIContRectScrollAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIContRectScrollAccessor
    : public IlvStIContainerRectangleAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIContRectScrollAccessor(IlvStIPropertyAccessor* = 0,
				 IlvOrientation = IlvHorizontal,
				 IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				 const char* = 0);

protected:
    IlvOrientation _orientation;
    IlvSCGadgetContainerRectangle* getSCRectangle();
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIContRectScrollPosAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIContRectScrollPosAccessor
    : public IlvStIContRectScrollAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIContRectScrollPosAccessor(IlvStIPropertyAccessor* = 0,
				    IlvOrientation = IlvHorizontal,
				    IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				    const char* = 0);

protected:
    IlvDirection getDirection(IlvDirection) const;
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStISCContainerRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISCContainerRectanglePanel
    : public IlvStIContainerRectanglePanel
{
public:
    IlvStISCContainerRectanglePanel(IlvDisplay*,
				    const char*,
				    const char* = 0,
				    IlvSystemView = 0,
				    IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
protected:
    void initializeSCContainerRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStISCContainerRectanglePanel,
				 IlvStISCContainerRectanglePanelBuilder);

// --------------------------------------------------------------------------
// IlvStIManagerRectangleAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIManagerRectangleAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIManagerRectangleAccessor(IlvStIPropertyAccessor* = 0,
				   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				   const char* = 0);

protected:
    IlvManagerRectangle* getMgerRectangle() const;
};

// --------------------------------------------------------------------------
// IlvStIMgerRectFilenameAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIMgerRectFilenameAccessor
    : public IlvStIManagerRectangleAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIMgerRectFilenameAccessor(IlvStIPropertyAccessor* = 0,
				   IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				   const char* = 0);

protected:
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMgerRectScrollAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIMgerRectScrollAccessor
    : public IlvStIManagerRectangleAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMgerRectScrollAccessor(IlvStIPropertyAccessor* = 0,
				 IlvOrientation = IlvHorizontal,
				 IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				 const char* = 0);

protected:
    IlvOrientation _orientation;
    IlvSCGadgetContainerRectangle* getSCRectangle();
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIMgerRectScrollPosAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIMgerRectScrollPosAccessor
    : public IlvStIMgerRectScrollAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMgerRectScrollPosAccessor(IlvStIPropertyAccessor* = 0,
				    IlvOrientation = IlvHorizontal,
				    IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				    const char* = 0);

protected:
    IlvDirection getDirection(IlvDirection) const;
    virtual IlvStIProperty* getOriginalValue();
    virtual void            applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// class IlvStISCManagerRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIManagerRectanglePanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIManagerRectanglePanel(IlvDisplay*,
				const char*,
				const char* = 0,
				IlvSystemView = 0,
				IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
protected:
    void initializeManagerRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStIManagerRectanglePanel,
				 IlvStIManagerRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStISCManagerRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISCManagerRectanglePanel
    : public IlvStIManagerRectanglePanel
{
public:
    IlvStISCManagerRectanglePanel(IlvDisplay*,
				  const char*,
				  const char* = 0,
				  IlvSystemView = 0,
				  IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
protected:
    void initializeSCManagerRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStISCManagerRectanglePanel,
				 IlvStISCManagerRectanglePanelBuilder);

// --------------------------------------------------------------------------
// class IlvStISCGrapherRectanglePanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISCGrapherRectanglePanel
    : public IlvStISCManagerRectanglePanel
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStISCGrapherRectanglePanel(IlvDisplay*,
				  const char*,
				  const char* = 0,
				  IlvSystemView = 0,
				  IlvStIAccessor::UpdateMode =
						    IlvStIAccessor::OnApply);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeEditors();
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
protected:
    void initializeSCGrapherRectanglePanel();
};

// --------------------------------------------------------------------------
IlvStDefineInspectorPanelBuilder(IlvStISCGrapherRectanglePanel,
				 IlvStISCGrapherRectanglePanelBuilder);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_rectpnl)
#endif /* !__IlvSt_Inspectors_Rectpnl_H */
