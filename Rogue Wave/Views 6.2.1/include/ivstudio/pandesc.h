// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/pandesc.h
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
// Declaration of IlvStPanelDescriptor class
// --------------------------------------------------------------------------

#ifndef __IlvSt_Pandesc_H
#define __IlvSt_Pandesc_H

#ifndef __IlvSt_Stprop_H
#include <ivstudio/stprop.h>
#endif

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPanelDescriptor
: public IlvStPropertySet {
public:
    IlvStPanelDescriptor(const char* name);

    virtual void addedToSet(IlvStPropertySet*);

    // --- Accessors ---
    const char*	    getCommandName() const
	{ return getPropertyString(_S_commandName); }
    void	    setCommandName(const char* str)
	{ setPropertyString(_S_commandName, str); }
    const char*	    getFileName() const
	{ return getPropertyString(_S_filename); }
    void	    setFileName(const char* val)
	{ setPropertyString(_S_filename, val); }
    const char*	    getHelpFile() const
	{ return getPropertyString(_S_helpFile); }
    void	    setHelpFile(const char* val)
	{ setPropertyString(_S_helpFile, val); }
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
    const char*	    getTitle() const { return getPropertyString(_S_title); }
    void	    setTitle(const char* val)
	{ setPropertyString(_S_title, val); }
    IlBoolean	    isVisible() const
	{ return getPropertyBoolean(_S_visible); }
    void	    setVisible(IlBoolean val)
	{ setPropertyBoolean(_S_visible, val); }

    IlvPos	    getX() const { return (IlvPos)getPropertyInt(_S_x); }
    void	    setX(IlvPos val) { setPropertyInt(_S_x, (IlInt)val); }
    IlvPos	    getY() const { return (IlvPos)getPropertyInt(_S_y); }
    void	    setY(IlvPos val) { setPropertyInt(_S_y, (IlInt)val); }
    IlvDim	    getWidth() const
	{ return (IlvDim)getPropertyInt(_S_width); }
    void	    setWidth(IlvDim val)
	{ setPropertyInt(_S_width, (IlInt)val); }
    IlvDim	    getHeight() const
	{ return (IlvDim)getPropertyInt(_S_height); }
    void	    setHeight(IlvDim val)
	{ setPropertyInt(_S_height, (IlInt)val); }

    static IlBoolean	_Initialized;
    static IlSymbol*	_S_commandName;
    static IlSymbol*	_S_filename;
    static IlSymbol*	_S_helpFile;
    static IlSymbol*	_S_htmlHelpFile;
    static IlSymbol*	_S_compiledHtmlHelpFile;
    static IlSymbol*	_S_helpDirectory;
    static IlSymbol*	_S_title;
    static IlSymbol*	_S_visible;
    static IlSymbol*	_S_x;
    static IlSymbol*	_S_y;
    static IlSymbol*	_S_width;
    static IlSymbol*	_S_height;
    static IlSymbol*	_S_command;
    static IlSymbol*	_S_menu;
    static IlSymbol*	_S_menuItem;
    static IlSymbol*	_S_toolbar;

    static int GlobalInit();
}; // class IlvStPanelDescriptor

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_pandesc)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Pandesc_H */
