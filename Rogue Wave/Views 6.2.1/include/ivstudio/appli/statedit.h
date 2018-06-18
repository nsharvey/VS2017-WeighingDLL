// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/statedit.h
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
// Declaration of the IlvStStateInspector class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Statedit_H
#define __IlvSt_Statedit_H

#ifndef __IlvSt_Panel_H
#include <ivstudio/panel.h>
#endif

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmStateInspector;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmStateInspectorClosed;

// --------------------------------------------------------------------------
class IlvColorSelector;
class IlvFontSelector;
class IlvIBitmapSelector;
class IlvAbstractMatrixItem;
class IlvGadgetMatrixItem;

class IlvSdRequirement;
class IlvStSheet;
class IlvStDdRecipientManager;
class IlvStPanelInstanceFrame;
class IlvStPopupList;
class IlvStTreeItemSelector;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStStateInspector
: public IlvStPanelHandler {
public:
    IlvStStateInspector(IlvStudio*);
    ~IlvStStateInspector();
    virtual void	connect();
    virtual void	doReset();
    virtual IlBoolean	resetBeforeShowing() const;
    virtual void	setUpContainer(IlvGadgetContainer* cont);
    virtual void	hide();
    void		cleanUp();
    void		sheetItemSelected(IlUShort posx, IlUShort posy);
    void		browseSheetItem(IlUShort posx, IlUShort posy);
    void		validateSheetItem(IlUShort posx, IlUShort posy);
    IlBoolean		doubleClickSheetHook(IlUShort posx, IlUShort posy);
    void		checkAndFillRequirement(IlUShort row);
    IlBoolean		fillRequirement(IlUShort row);
    IlUShort		getRow(IlvSdRequirement*) const;
    IlvSdRequirement*	getRequirement(IlUShort row) const;
    void		setRequirement(IlUShort row, IlvSdRequirement*);
    IlvSdRequirement*	makeRequirement(IlUShort row);
    void		removeRequirement(IlvSdRequirement*);
    void		requirementSelected(IlvSdRequirement*);
    IlvStSheet*		getSheet() const { return _sheet; }
    const char* const*  getObjectRequirements(IlvGraphic*, IlUShort& count);
    IlvStPanelInstanceFrame* getPanelInstanceFrame(const char* name) const;
    IlvGraphic*		getPanelObject(const char* panelName,
				       const char* objectName) const;
    const char*		selectTypedValue(const IlvValueTypeClass*);
    const char* const*	getValues(const IlvValueTypeClass*, IlUShort& count);
    const IlvValueTypeClass* getValueType(const char*, IlvGraphic* = 0);
    IlBoolean		checkCurrentRequirement();
    //
    const IlvArray*	getPanelNames();
    const IlvArray*	getObjectNames();
    const IlvArray*	getRequirementNames();
    const IlvArray*	getPredefinedValues(const IlvValueTypeClass*&);
    const IlvArray*	getStateCallbacks();
protected:
    static void		MoveToMouse(IlvView*);
    void		adjustPopupList(IlUShort = (IlUShort)-1,
					IlUShort = (IlUShort)-1);
    enum {
	UnknownTarget = 0,
	GraphicTarget,
	MenuItemTarget
    };
    IlAny		getTarget(const char* panelName,
				  const char* objectName,
				  int& targetType) const;

    IlvStSheet*			_sheet;
    IlvStDdRecipientManager*	_ddRecMgr;
    IlvColorSelector*		_colSelector;
    IlvFontSelector*		_fntSelector;
    IlvIBitmapSelector*		_btmSelector;
    IlvArray			_panelNames;
    IlvArray			_objectNames;
    IlvArray			_requirementNames;
    IlvArray			_predefinedValues;
    const char*			_lastObjectClass;
    IlvArray			_objectRequirements;
    IlvArray			_stateCallbacks;
    IlvStPopupList*		_popupList;
    IlvStTreeItemSelector*	_menuItemSelector;
    IlvGadgetMatrixItem*	_sheetComboItem;
    IlvGadgetMatrixItem*	_sheetSelFldItem;
}; // class IlvStStateInspector

// --------------------------------------------------------------------------
#endif /* __IlvSt_Statedit_H */
