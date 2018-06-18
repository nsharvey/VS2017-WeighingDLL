// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/codesc.h
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
// Declaration of the IlvStCommandDescriptor class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Codesc_H
#define __IlvSt_Codesc_H

#if !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

class IlvStCommandDescriptor;
class IlvStCommand;
class IlvScrolledComboBox;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCommandBuilder
: public IlvStObject
{
public:
    virtual IlvStCommand* build(IlvStudio*) = 0;
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCommandDescriptor
: public IlvStPropertySet {
public:
    IlvStCommandDescriptor(const char*		name,
                           const char*		label,
                           IlvStCommandBuilder* builder);
    IlvStCommandDescriptor(const IlvStCommandDescriptor&);
    IlvStCommandDescriptor(ILVSTDPREF istream&);
    ~IlvStCommandDescriptor();
    virtual IlvStProperty*  copy() const;

    virtual void addedToSet(IlvStPropertySet*);

    virtual IlvStCommand* makeCommand(IlvStudio*);
    const char*		getLabel() const;
    void 		setLabel(const char* label)
	{ setPropertyString(_S_label, label); }
    const char*		getToggleLabel() const
	{ return getPropertyString(_S_toggleLabel); }
    void		setToggleLabel(const char* str)
	{ setPropertyString(_S_toggleLabel, str); }
    const char*		getToolTip() const;
    void		setToolTip(const char* str)
	{ setPropertyString(_S_tooltip, str); }
    const char*		getToggleToolTip() const;
    void		setToggleToolTip(const char* str)
	{ setPropertyString(_S_toggleTooltip, str); }
    const char* 	getBitmapName() const
	{ return getPropertyString(_S_bitmap); }
    void 		setBitmapName(const char* bname)
	{ setPropertyString(_S_bitmap, bname); }
    const char* 	getComboLabels() const
	{ return getPropertyString(_S_comboLabels); }
    void 		setComboLabels(const char* comboLabels)
	{ setPropertyString(_S_comboLabels, comboLabels); }
    const char* 	getWidthString() const
	{ return getPropertyString(_S_width); }
    void 		setWidthString(const char* width)
	{ setPropertyString(_S_width, width); }
    const char*		getPrompt() const;
    void 		setPrompt(const char* prompt)
    	{ setPropertyString(_S_prompt, prompt); }
    const char*		getTogglePrompt() const
	{ return getPropertyString(_S_togglePrompt); }
    void		setTogglePrompt(const char* str)
    	{ setPropertyString(_S_togglePrompt, str); }
    const char*		prompt() const
	{ return getPropertyString(_S_prompt); }
    const char*		getAcceleratorText() const
	{ return getPropertyString(_S_acceleratorText); }
    void  		setAcceleratorText(const char* acc)
    	{ setPropertyString(_S_acceleratorText, acc);}
    const char*		getAcceleratorDefinition() const
	{ return getPropertyString(_S_acceleratorDefinition); }
    void		setAcceleratorDefinition(const char* acc)
    	{ setPropertyString(_S_acceleratorDefinition, acc); }
    IlvStCommandDescriptor();
    void 		clear();
    void 		setMessageNames(const char* const* names,
					IlUShort count);
    const char* const* 	getMessageNames() const;

    IlBoolean		isInteractive() const
	{ return getPropertyBoolean(_S_interactive); }
    void        	setInteractive(IlBoolean val)
	{ setPropertyBoolean(_S_interactive, val); }
    void        	setInteractive(const char* val)
	{ setPropertyString(_S_interactive, val); }

    IlBoolean		hasArguement() const
	{ return getPropertyBoolean(_S_argument); }
    void        	setHasArguement(IlBoolean val)
	{ setPropertyBoolean(_S_argument, val); }
    void        	setHasArguement(const char* val)
	{ setPropertyString(_S_argument, val); }
    // ____________________________________________________________
    IlBoolean 		isRealized() const { return _realized; }
    virtual void 	realize(IlvStudio*);
    IlvStCommandBuilder* getBuilder() const { return _builder; }
    void		setBuilder(IlvStCommandBuilder* builder)
	{ _builder = builder; }
    virtual IlvBitmap* 	getBitmap() const;
    void 		setBitmap(IlvBitmap* bitmap);
    virtual IlvScrolledComboBox* getComboBox() const;
    void 		setComboBox(IlvScrolledComboBox* c);
    void		resetComboBox(IlvDisplay* display);
    virtual IlUInt	getWidth() const;
    void 		setWidth(IlUInt width);
    const IlvStMessage* const* getMessages(IlUShort& count) const {
	count = _messageCount;
	return (const IlvStMessage* const*)_messages; }
    virtual IlBoolean 	isInCategory(IlSymbol* ctg) const;
    void        	addCategory(IlSymbol* ctg);
    void		removeCategory(IlSymbol* ctg);
    virtual IlBoolean 	getState() const;
    virtual void 	setState(IlBoolean val);
    IlBoolean		isInhibited() const { return _inhibited; }
    void		inhibit(IlBoolean value) { _inhibited = value; }
    const IlSymbol*	getSelector() const;
    void		setSelector(const IlSymbol* sel);

    static const IlSymbol* CommandSymbol() { return _S_command; }
    static const IlSymbol* LabelSymbol() { return _S_label; }
    static const IlSymbol* ToggleLabelSymbol() { return _S_toggleLabel; }
    static const IlSymbol* TooltipSymbol() { return _S_tooltip; }
    static const IlSymbol* ToggleTooltipSymbol() { return _S_toggleTooltip; }
    static const IlSymbol* AcceleratorTextSymbol() { return _S_acceleratorText; }
    static const IlSymbol* AcceleratorDefinitionSymbol() { return _S_acceleratorDefinition; }
    static const IlSymbol* CtrlAcceleratorSymbol() { return _S_ctrlAccelerator; }
    static const IlSymbol* PromptSymbol() { return _S_prompt; }
    static const IlSymbol* TogglePromptSymbol() { return _S_togglePrompt; }
    static const IlSymbol* MessagesSymbol() { return _S_messages; }
    static const IlSymbol* BitmapSymbol() { return _S_bitmap; }
    static const IlSymbol* ComboLabelsSymbol() { return _S_comboLabels; }
    static const IlSymbol* WidthSymbol() { return _S_width; }
    static const IlSymbol* CategorySymbol() { return _S_category; }
    static const IlSymbol* SelectorSymbol() { return _S_selector; }
    static const IlSymbol* InteractiveSymbol() { return _S_interactive; }
    static const IlSymbol* ArguementSymbol() { return _S_argument; }

    static int		GlobalInit();
protected:
    void  	initialize();
    static IlBoolean	_Initialized;

    static IlSymbol*	_S_command;
    static IlSymbol* 	_S_label;
    static IlSymbol*	_S_toggleLabel;
    static IlSymbol*	_S_tooltip;
    static IlSymbol*	_S_toggleTooltip;
    static IlSymbol*	_S_acceleratorText;
    static IlSymbol*	_S_acceleratorDefinition;
    static IlSymbol*	_S_ctrlAccelerator;
    static IlSymbol*	_S_prompt;
    static IlSymbol*	_S_togglePrompt;
    static IlSymbol*	_S_messages;
    static IlSymbol*	_S_bitmap;
    static IlSymbol*	_S_comboLabels;
    static IlSymbol*	_S_width;
    static IlSymbol*	_S_category;
    static IlSymbol*	_S_selector;
    static IlSymbol*	_S_interactive;
    static IlSymbol*	_S_argument;
    static IlSymbol*	_S_htmlHelpFile;
    static IlSymbol*	_S_compiledHtmlHelpFile;
    static IlSymbol*	_S_helpDirectory;

    IlUShort 		    _messageCount;
    IlvStMessage** 	    _messages;
    IlvBitmap* 		    _bitmap;
    IlvScrolledComboBox*    _comboBox;
    const char**	    _comboLabels;
    IlUShort		    _comboLabelsCount;
    IlUInt		    _width;
    IlvStCommandBuilder*    _builder;
    IlBoolean 		    _realized	ILVSTBF;
    IlBoolean 		    _state	ILVSTBF;
    IlBoolean		    _inhibited	ILVSTBF;

public:
    const char*	    getHtmlHelpFile() const
	{ return getPropertyString(_S_htmlHelpFile); }
    void	    setHtmlHelpFile(const char* hhf)
	{ setPropertyString(_S_htmlHelpFile, hhf); }
    const char*	    getCompiledHtmlHelpFile() const
	{ return getPropertyString(_S_compiledHtmlHelpFile); }
    void	    setCompiledHtmlHelpFile(const char* str)
	{ setPropertyString(_S_compiledHtmlHelpFile, str); }
    const char*	    getHelpDirectory() const
	{ return getPropertyString(_S_helpDirectory); }
    void	    setHelpDirectory(const char* str)
	{ setPropertyString(_S_helpDirectory, str); }

}; // IlvStCommandDescriptor

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDefaultCommandBuilder
: public IlvStCommandBuilder {
public:
    IlvStDefaultCommandBuilder(IlvStCommandConstructor func);
    virtual IlvStCommand* build(IlvStudio* editor);
private:
    IlvStCommandConstructor _constructor;
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStFunctionCommandBuilder
: public IlvStCommandBuilder {
public:
    IlvStFunctionCommandBuilder(IlvStCommandFunction func);
    virtual IlvStCommand* build(IlvStudio*);
private:
    IlvStCommandFunction _function;
};

// --------------------------------------------------------------------------

#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_codesc)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Codesc_H */
