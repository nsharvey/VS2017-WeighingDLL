// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/edtcallb.h
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
// Declaration of IlvStICallbackEditor
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Edtcallb_H
#define __IlvSt_Inspectors_Edtcallb_H

#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Graphinf_H)
#  include <ivstudio/inspectors/graphinf.h>
#endif

class IlvStIError;
// --------------------------------------------------------------------------
#ifdef __USE_SHEET__
class IlvSheet;
#else
class IlvGadgetContainer;
class IlvTextField;
class IlvMessageLabel;
class IlvToggle;
class IlvButton;
#endif /* ! __USE_SHEET__ */
// --------------------------------------------------------------------------
// IlvStICallbackInfos class
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStICallbackInfos : public IlvStIRefNamedObject
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStICallbackInfos(IlvStINameChecker* nameChecker = 0,
			const char* name = 0);
    ~IlvStICallbackInfos();

    // ----------------------------------------------------------------------
    virtual IlBoolean		isUsingJScript() const;
    virtual const IlSymbol*	getDefaultCallbackLanguage() const;
    virtual IlvStIError*	checkCallbackName(const char*);
    virtual void		callbacksChanged(IlvGraphic*);
    virtual IlBoolean		editScript(const char*);

protected:
    IlvStINameChecker*		_nameChecker;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICallbackEditor : public IlvStIExternalEditor
{
    IlvDeclareInspClassInfo();
public:
    static const char*	DefaultCallbackEditorName;
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStICallbackEditor(IlvStIPropertyAccessor* accessor = 0,
			 const char* name = DefaultCallbackEditorName,
		         IlvStIEditor::NotificationMode mode =
			 IlvStIEditor::AsOwner);
    ~IlvStICallbackEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean		initialize();
    virtual IlBoolean		apply();
    virtual IlBoolean		connectHolder(IlvGraphicHolder* holder);

    // ----------------------------------------------------------------------
    void			cleanUp();
    IlvGraphic*			getGraphic() const;
    virtual IlvDisplay*		getDisplay() const;
    void			callbackNameChanged();

    // ----------------------------------------------------------------------
    void			setCallbackInfos(IlvStICallbackInfos* cbnfos);
    inline IlvStICallbackInfos*	getCallbackInfos() const
				{
				    return _callbackInfos;
				}

    void			scriptChecked(IlvGraphic*);
    void			callbackScriptEdited(IlvGraphic*);
    void			callbackNameEdited(IlUShort);
    void			callbackValueEdited(IlUShort);
#if !defined(__USE_SHEET__)
    void			callbackNameEdited(IlvTextField*);
    void			callbackValueEdited(IlvTextField*);
    inline IlvGadgetContainer*	getGadgetContainer() const
				{
				    return _container;
				}
    void			moveTitles();
#endif /* !__USE_SHEET__ */

protected:

#ifdef __USE_SHEET__
    IlvSheet*			_sheet;
#else
    IlvGraphicHolder*		_holder;
    IlvGadgetContainer*		_container;
    IlArray			_labels;
    IlArray			_nameFields;
    IlArray			_valueFields;
    IlvPos			_nameX;
    IlvPos			_titleMargin;
    IlvMessageLabel*		_descLabel;
    IlvMessageLabel*		_nameLabel;
    IlvMessageLabel*		_valueLabel;
    IlvMessageLabel*		_scriptLabel;

    IlvTextField*		getNameField(IlUInt) const;
    IlvMessageLabel*		getMessageLabel(IlUInt) const;
    IlvTextField*		getValueField(IlUInt ndx) const;
#endif /* ! __USE_SHEET__ */

    IlArray			_types;
    IlArray			_scriptToggles;
    IlArray			_editButtons;

    IlArray			_changes;
    IlvStICallbackInfos*	_callbackInfos;

    void			changed(IlUInt ndx,
					IlShort changeType,
					IlBoolean notifyModif = IlTrue);
    IlBoolean			hasChanged(IlUInt ndx,
					   IlShort changeType) const;
    IlShort			getChange(IlUInt ndx) const;
    const char*			getCallbackName(IlUInt ndx) const;
    const char*			getCallbackValue(IlUInt ndx) const;

    virtual IlBoolean		isUsingJScript() const;
    virtual const IlSymbol*	getDefaultCallbackLanguage() const;
    void			updateOnCallbackNameChange(IlUInt, const char*);
    IlvToggle*			getScriptToggle(IlUInt) const;
    IlvButton*			getEditButton(IlUInt) const;

};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_edtcallb)
#endif /* !__IlvSt_Inspectors_Edtcallb_H */
