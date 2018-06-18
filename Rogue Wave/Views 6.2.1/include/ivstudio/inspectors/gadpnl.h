// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/gadpnl.h
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
// Declaration of the IlvStIGadgetInspectorPanel class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Gadpnl_H
#define __IlvSt_Inspectors_Gadpnl_H

#if !defined(__IlvSt_Inspectors_Insppnl_H)
#  include <ivstudio/inspectors/insppnl.h>
#endif
#if !defined(__IlvSt_Inspectors_Inspvali_H)
#  include <ivstudio/inspectors/inspvali.h>
#endif
#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif

class IlvManager;
class IlvStINameChecker;
class IlvStIGraphicInteractorsInfos;
class IlvStICallbackInfos;
class IlvStINameInfos;

// --------------------------------------------------------------------------
// Inspection of IlvGraphic objects
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// IlvStIGraphicNameValidator
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGraphicNameValidator
    : public IlvStIValidator
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGraphicNameValidator(IlvStINameChecker* = 0,
			     IlvStIPropertyAccessor* = 0,
			     const char* = "GraphicNameValidator");
    virtual ~IlvStIGraphicNameValidator();

    IlvStIError*		check(const IlvStIProperty*) const;
    IlvGraphic*			getGraphic() const;

protected:
    IlvStINameChecker*		_nameChecker;
    IlvStIPropertyAccessor*	_accessor;
};

// --------------------------------------------------------------------------
// IlvStICombinedGraphicAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICombinedGraphicAccessor
    : public IlvStICombinedValueInterAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStICombinedGraphicAccessor(IlvStIPropertyAccessor* = 0,
				  const char* = 0,
				  IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStICombinedGraphicAccessor();

    IlvGraphic*		getGraphic() const;
    IlvManager*		getManager() const;
};

// --------------------------------------------------------------------------
// IlvStIGraphicNameAccessor class
// --------------------------------------------------------------------------
class IlvStIGraphicNameAccessor
    : public IlvStICombinedGraphicAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGraphicNameAccessor(IlvStIPropertyAccessor* = 0,
			      IlvStINameInfos* = 0,
			      const char* = 0,
			      IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIGraphicNameAccessor();

protected:
    IlvStINameInfos* _nameInfos;

    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIGraphicTooltipAccessor class
// --------------------------------------------------------------------------
class IlvStIGraphicTooltipAccessor
    : public IlvStICombinedGraphicAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGraphicTooltipAccessor(IlvStIPropertyAccessor* = 0,
			         const char* = 0,
			         IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIGraphicStateAccessor class
// --------------------------------------------------------------------------
class IlvStIGraphicStateAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGraphicStateAccessor(IlvStIPropertyAccessor* = 0,
			       UpdateMode = NoUpdate,
			       BuildMode = None,
			       const char* = 0);

    IlvGraphic*			getGraphic() const;
    IlvGadget*			getGadget() const;

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIGraphicLayerAccessor class
// --------------------------------------------------------------------------
class IlvStIGraphicLayerAccessor
    : public IlvStICombinedGraphicAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGraphicLayerAccessor(IlvStIPropertyAccessor* = 0,
			       const char* = 0,
			       IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIGraphicInteractorAccessor class
// --------------------------------------------------------------------------
class IlvStIGraphicInteractorAccessor
    : public IlvStICombinedGraphicAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGraphicInteractorAccessor(IlvStIPropertyAccessor* = 0,
				    IlvStINameChecker* = 0,
				    IlvStIGraphicInteractorsInfos* = 0,
				    const char* = 0,
				    IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIGraphicInteractorAccessor();

    void	setInteractorsInfos(IlvStIGraphicInteractorsInfos*);
    IlvStIGraphicInteractorsInfos*	getInteractorsInfos() const
	{ return _graphInter; }

protected:
    virtual IlvStIProperty*		getOriginalValue();
    virtual void			applyValue(IlvStIProperty*);

    IlvStINameChecker*			_nameChecker;
    IlvStIGraphicInteractorsInfos*	_graphInter;

};

// --------------------------------------------------------------------------
// IlvStIGraphicInspectorPanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGraphicInspectorPanel
    : public IlvStInspectorPanel
{
public:
    IlvStIGraphicInspectorPanel(IlvDisplay* display,
				const char*   title,
				const char*   filename = 0,
				IlvSystemView transientFor = 0,
				IlvStIAccessor::UpdateMode
				mode = IlvStIAccessor::OnApply);
    virtual ~IlvStIGraphicInspectorPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void		initializeEditors();
    virtual void		applyChange(IlvGraphic*);
    virtual void		initFrom(IlvGraphic*);

    // ----------------------------------------------------------------------
    // Getting some inspected graphic's infos
    void		setInteractorsInfos(IlvStIGraphicInteractorsInfos*);
    void		setNameChecker(IlvStINameChecker*);
    void		setCallbackInfos(IlvStICallbackInfos*);
    void		setNameInfos(IlvStINameInfos*);

    // ----------------------------------------------------------------------
    // Editor / accessor names
    static const char*	_NameAccessorName;
    static const char*	_NameEditorName;
    static const char*	 _TooltipAccessorName;
    static const char*	_TooltipEditorName;
    static const char*	_StateEditorName;
    static const char*	_LayerAccessorName;
    static const char*	_LayerEditorName;
    static const char*	_InteractorAccessorName;
    static const char*	_InteractorEditorName;
    static const char*	_CallbackEditorName;
    static const char*	_ThicknessEditorName;
    static const char*	_ActiveEditorName;
    static const char*	_TransparentEditorName;
    static const char*	_FocusEditorName;
    static const char*	_ShowFrameEditorName;

protected:
    void initializeGraphicPage();

    IlvStIGraphicInteractorsInfos* _interactorsInfos;
    IlvStINameChecker*		   _nameChecker;
    IlvStINameInfos*               _nameInfos;
    IlvStICallbackInfos*           _callbackInfos;
};

IlvStDefineInspectorPanelBuilder(IlvStIGraphicInspectorPanel,
				 IlvStIGraphicInspectorPanelBuilder);

// --------------------------------------------------------------------------
// Inspection of IlvGadget objects
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// IlvStICombinedGadgetAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICombinedGadgetAccessor
    : public IlvStICombinedGraphicAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStICombinedGadgetAccessor(IlvStIPropertyAccessor* = 0,
				 const IlSymbol* = 0,
				 IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStICombinedGadgetAccessor();

    IlvGadget*			getGadget() const;

protected:
    virtual IlvValueInterface*	getValueInterface() const;
};

// --------------------------------------------------------------------------
// IlvStIGadgetInspectorPanel
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGadgetInspectorPanel
    : public IlvStIGraphicInspectorPanel
{
public:
    IlvStIGadgetInspectorPanel(IlvDisplay*	display,
			       const char*	title,
			       const char*	filename = 0,
			       IlvSystemView	transientFor = 0,
			       IlvStIAccessor::UpdateMode mode =
			       IlvStIAccessor::OnApply);
    virtual ~IlvStIGadgetInspectorPanel();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	initializeEditors();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*);

protected:
    void		initializeGadgetPage();
};

IlvStDefineInspectorPanelBuilder(IlvStIGadgetInspectorPanel,
				 IlvStIGadgetInspectorPanelBuilder);

// --------------------------------------------------------------------------
ILVINSPEXPORTEDFUNC(IlBoolean)
TranslatorTextValueCallback(IlvStIProperty*, IlvValue&, IlBoolean, IlAny);

ILVINSPEXPORTEDFUNC(IlBoolean)
IlvStIDirectionsTranslator(IlvStIProperty*, IlvStIProxyListGadget*,
			   IlBoolean, IlAny);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_gadpnl)
#endif /* !__IlvSt_Inspectors_Gadpnl_H */
