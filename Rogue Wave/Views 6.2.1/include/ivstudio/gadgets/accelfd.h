// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/accelfd.h
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
// Declaration of the IlvStIMenuBarPanel class
// Defined in studio gadgets library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Accelfd_H)
#define __IlvSt_Accelfd_H

#if !defined(__IlvSt_Genbase_H)
#include <ivstudio/inspectors/genbase.h>
#endif

#if !defined(__IlvSt_Genedt_H)
#include <ivstudio/inspectors/genedt.h>
#endif

#if !defined(__Ilv_Fbrowser_H)
#include <ilviews/gadgets/fbrowser.h>
#endif

#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

// --------------------------------------------------------------------------
// IlvStIAcceleratorTextField class
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStIAcceleratorTextField : public IlvFileSelectorField
{
public:
    IlvStIAcceleratorTextField(IlvDisplay* display,
			       const char* label,
			       const IlvRect& rect,
			       IlUShort thickness = IlvDefaultGadgetThickness,
			       IlvPalette* palette = 0);
    IlvStIAcceleratorTextField(IlvDisplay* display,
			       const IlvPoint& at,
			       const char* label,
			       IlUShort thickness = IlvDefaultGadgetThickness,
			       IlvPalette* palette = 0);

    void		setAccelerator(IlUShort key, IlUShort modifiers);
    void		getAccelerator(IlUShort& key,
				       IlUShort& modifiers) const;

    // Statics
    DeclareGraphicAccessors();
    DeclareTypeInfo();

    DeclareIOConstructors(IlvStIAcceleratorTextField);
    static IlSymbol*	_AcceleratorValue;

protected:
    IlBoolean		_decodeKeyEvents;
    IlUShort		_key, _modifiers;

    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual void	buttonPressed();
    virtual IlvBitmap*	createBitmap() const;

public:
    static const char*	KeyEventToString(IlUShort key,
					 IlUShort modifiers, IlString&);
    static const char*	KeyEventToMenuString(IlUShort key,
					     IlUShort modifiers,
					     IlString& result);
    static void		GetAccelerator(const IlvValue&,
				       IlUShort& key,
				       IlUShort& modifier);
    static void		SetAccelerator(IlvValue&,
				       IlUShort key,
				       IlUShort modifier);
};

// --------------------------------------------------------------------------
// class IlvStIAcceleratorEditor
// --------------------------------------------------------------------------

class ILVSTGADGETCLASS IlvStIAcceleratorEditor
    : public IlvStIPropertyTextEditor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIAcceleratorEditor(const char* name = 0,
			    IlvStIPropertyAccessor* accessor = 0,
			    NotificationMode = AsOwner);
    ~IlvStIAcceleratorEditor();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() { return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridable
    virtual const char*	getGraphicClassName() const;

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
    virtual void	setGraphic(IlvGraphic*, IlvGraphicHolder* = 0);
};


// --------------------------------------------------------------------------
IlvDECLAREINITSTGADGETCLASS(sti_accelfd)
// --------------------------------------------------------------------------
#endif /* !__IlvSt_Accelfd_H */
