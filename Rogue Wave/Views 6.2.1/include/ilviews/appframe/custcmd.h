// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/custcmd.h
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
// Declaration of the commands inspectors class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Custcmd_H)
#define __Ilv_Appframe_Custcmd_H

#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif
#if !defined(__Ilv_Appframe_Dialog_H)
#include <ilviews/appframe/dialog/dialog.h>
#endif
#if !defined(__Ilv_Appframe_Inspect_H)
#include <ilviews/appframe/dialog/inspect.h>
#endif
#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif

class IlvDvCommandInspector;
class IlvDvApplication;
class IlvDvMenuOptionsReader;
// --------------------------------------------------------------------------
// IlvDvCmdCategInterface class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvCmdCategInterface
{
public:
    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	canEditCommandName(const IlvDvNodeValue*) const = 0; 
    virtual void	selectCommandCategory(const IlvDvNodeValue* cmdName,
					      const char* = 0) = 0;
    virtual
    const IlSymbol*	getSelectedCategory() const = 0;
    virtual IlBoolean	alwaysUpdateCmdCategories() const = 0;

    IlBoolean		findAccelerator(const char* accel,
					IlvString& foundMsg) const;
    virtual
    IlvDvNodeValue*	getSelectedCommandValue() const = 0;
    virtual
    IlvDvNodeValue*	getCommandValue(const IlSymbol*) const = 0;
    virtual void	updateSelectedCmdItem() = 0;
    virtual
    IlvDvNodeValue*	makeCategsValues(IlBoolean) const = 0;
    virtual
    IlvDvDialogAssoc*	getSelectedCommandAssoc() const;
    virtual
    const IlvDvNodeValueArray*
			getCommandsArray(IlBoolean all = IlTrue) const = 0;
    virtual
    IlvDvNodeValue*	getCommandsDataValue() const = 0;
    virtual void	changeCommandName(IlvDvNodeValue* var,
					  const char* newName) = 0;

protected:
    virtual const char* getAccelAlreadyUsedMsg(IlvString&,
					       const char* accel,
					       const IlvDvNodeValue*) const=0;
};

// --------------------------------------------------------------------------
// IlvDvSortedCommandsInspector class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvSortedCommandsInspector : public IlvDvInspector
{
public:
    // ----------------------------------------------------------------------
    IlvDvSortedCommandsInspector(IlvDvApplication* app,
				 const IlSymbol*,
			         IlvDvDialogAssoc* optionsAssoc,
			         IlvPalette*);
    ~IlvDvSortedCommandsInspector();

    // ----------------------------------------------------------------------
    // Basic properties
    void		setCommandInspector(IlvDvCommandInspector*);
    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_AllCategoriesSymbol;
    static void		AddCmdCategories(IlvDvNodeValue* cmdVar,
					 IlvDvNodeValue* allCategsVar);

protected:
    IlvDvApplication*		_application;
    IlvDvDialogAssoc*		_optionsAssoc;
    IlvDvDialogAssoc*		_categoryAssoc;
    IlvDvCommandInspector*	_cmdInspector;
    IlvPalette*			_userDefinedPalette;

    IlvDvOptions*		getCurrentOptions() const;
    IlvDvMenuOptionsReader*	getMenuOptionsReader() const;

    friend class ILVDVCLASS IlvDvCustomizeDialog;

    IlBoolean		addCmdItem(const IlSymbol* dataKey,
				   IlvListGadgetItemHolder* holder,
				   const IlSymbol* selectedCateg,
				   IlvDvNodeValue* cmdVar,
				   IlvDvNodeValue* dataCmd,
				   IlvDvListGadgetAssoc& assoc,
				   IlUInt& index) const;
    void		fillCmdItems(IlvDvGenericGadget& gadget,
				     IlvDvListGadgetAssoc& assoc,
				     const IlSymbol* category) const;
    virtual void	fillOtherCmdItems(IlvDvGenericGadget& gadget,
					  IlvDvListGadgetAssoc& assoc,
					  const IlSymbol* category,
					  IlUInt index) const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	addListItems(const IlSymbol*,
				     IlvDvGenericGadget&,
				     IlAny clientData,
				     IlvDvListGadgetAssoc&) const;
    virtual void	initGadgetItem(const IlSymbol*,
				       IlvGadgetItem*,
				       const IlvDvAbstractListAssoc&) const;
    virtual
    IlvDvNodeValue*	createFieldVariable(const IlSymbol* name,
					    const IlvDvNodeValue* varParent,
					    IlUInt index,
					    const IlvDvClass* itemClass,
					    IlAny param = 0);
    virtual IlBoolean	isListActionEnabled(const IlSymbol*,
					    IlUInt iItem,
					    IlShort nAction,
					    const IlvDvListGadgetAssoc&,
					    IlAny param = 0) const;
    virtual IlBoolean	getGadgetSensitivity(const IlSymbol*,
					     const IlvDvGadgetAssoc&) const;

    virtual
    IlvDvGadgetAssoc*	getCategoryAssoc() const = 0;
    virtual
    IlvDvListGadgetAssoc*	getCmdsListAssoc() const = 0;

    // ----------------------------------------------------------------------
    const IlSymbol*	getCurrentSelectedCategory() const;
    virtual
    const IlvDvCmdCategInterface*	getCmdInterface() const = 0;
};

// --------------------------------------------------------------------------
// IlvDvCommandInspector class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvCommandInspector : public IlvDvInspector
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvCommandInspector(const IlSymbol* name,
			  IlvDvDialogAssoc* optionsAssoc,
			  IlvDvCmdCategInterface* cmdInterface,
			  IlvDvOptions* allOptions);

    // ----------------------------------------------------------------------
    // Basic properties
    inline
    IlvDvListGadgetAssoc*	getCmdSelectedCategAssoc() const
				{
				    return _cmdSelectedCategAssoc;
				}
    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_CmdBitmapListSymbol;
    static IlSymbol*		_CmdSelectedBitmapSymbol;
    static IlSymbol*		_CmdSelectedListDescSymbol;
    static IlSymbol*		_CmdNameDescSymbol;
    static IlSymbol*		_CmdNameValidatorSymbol;
    static IlSymbol*		_CmdAccelValidatorSymbol;
    static IlSymbol*		_CmdAllCategsEditSymbol;

protected:
    IlvDvDialogAssoc*		_selCmdAssoc;
    IlvDvDialogAssoc*		_optionsAssoc;
    IlvDvListGadgetAssoc*	_cmdCategsListAssoc;
    IlvDvListGadgetAssoc*	_cmdSelectedCategAssoc;
    IlvDvCmdCategInterface*	_cmdInterface;
    IlvDvOptions*		_allOptions;

    IlvDvOptions*	getCurrentOptions() const;
    void		ensureGoodSelectedCategory(const char*);
    // ----------------------------------------------------------------------
    // Overridables
    virtual void	createAssocs();
    virtual void	addListItems(const IlSymbol*,
				     IlvDvGenericGadget&,
				     IlAny clientData,
				     IlvDvListGadgetAssoc&) const;
    virtual IlUShort	getInitialSelectedItem(const IlSymbol*,
					       const IlvDvNodeValue*,
					       IlUShort selection,
					       IlvDvListGadgetAssoc&) const;
    virtual IlUInt	addItem(const IlSymbol*,
				IlvDvNodeValue*,
				IlvDvListGadgetAssoc&,
				IlUInt = (IlUInt)-1,
				IlAny clientData = 0,
				IlBoolean selectIt = IlTrue);
    virtual void	removeItem(const IlSymbol*,
				   IlUInt index,
				   IlvDvNodeValue* varField,
				   IlvDvListGadgetAssoc&);
    virtual void	setNodeValue(const IlSymbol*,
				     IlvDvNodeValue* var,
				     const IlvDvNodeValue*,
				     const IlvDvDialogAssoc&);
    virtual void	setDataVariableValue(const IlSymbol*,
					     IlvDvNodeValue* var,
					     const IlvDvNodeValue*,
					     const IlvDvDialogAssoc&);
    virtual
    IlvDvNodeValue*	getListItemVariable(const IlSymbol*,
					    IlvDvNodeValue*,
					    IlUInt,
					    IlvGadgetItem*,
					    const IlvDvListGadgetAssoc&) const;
    virtual void	setGadgetValue(const IlSymbol*,
				IlvDvGenericGadget&,
				const IlvValue*,
				const IlvDvGadgetAssoc&);
    virtual
    IlvDvNodeValue*	createFieldVariable(const IlSymbol* name,
					    const IlvDvNodeValue* varParent,
					    IlUInt index,
					    const IlvDvClass* itemClass,
					    IlAny param = 0);
    virtual void	connectHolder(IlvGraphicHolder* holder);
    virtual void	modified(const IlSymbol*, const IlvDvDialogAssoc&);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(custcmd);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Custcmd_H */
