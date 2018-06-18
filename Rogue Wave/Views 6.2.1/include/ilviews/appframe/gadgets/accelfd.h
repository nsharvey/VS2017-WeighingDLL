// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/gadgets/accelfd.h
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
// Declaration of the IlvDvAcceleratorTextField class

#if !defined(__Ilv_Appframe_Gadgets_Accelfd_H)
#define __Ilv_Appframe_Gadgets_Accelfd_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Fbrowser_H)
#include <ilviews/gadgets/fbrowser.h>
#endif

// --------------------------------------------------------------------------
// IlvDvAcceleratorTextField class
// --------------------------------------------------------------------------
class IlvDvAcceleratorTextField : public IlvFileSelectorField
{
public:
    IlvDvAcceleratorTextField(IlvDisplay* display,
			     const char* label,
			     const IlvRect& rect,
			     IlUShort thickness = IlvDefaultGadgetThickness,
			     IlvPalette* palette = 0);
    IlvDvAcceleratorTextField(IlvDisplay* display,
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
    DeclareIOConstructors(IlvDvAcceleratorTextField);

    static IlSymbol*	_AcceleratorValue;

protected:
    IlBoolean		_decodeKeyEvents;
    IlUShort		_key;
    IlUShort		_modifiers;

    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual void	buttonPressed();
    virtual IlvBitmap*	createBitmap()const;

public:
    static void		GetAccelerator(const IlvValue&,
				       IlUShort& key,
				       IlUShort& modifier);
    static void		SetAccelerator(IlvValue&,
				       IlUShort key,
				       IlUShort modifier);
};

// --------------------------------------------------------------------------
ILVDVEXPORTEDFUNCTION(IlBoolean)
IlvDvStringToKeyEvent(const char* text, IlUShort& key, IlUShort& modifiers);

ILVDVEXPORTEDFUNCTION(const char*)
IlvDvKeyEventToMenuString(IlUShort  key,
			  IlUShort  modifiers,
			  IlString& result);

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(accelfd)
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Gadgets_Accelfd_H */
