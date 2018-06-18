// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/passwded.h
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
// Declaration of the IlvPasswordTextField class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Passwded_H
#define __Ilv_Gadgets_Passwded_H

#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvPasswordTextField : public IlvTextField
{
public:

    IlvPasswordTextField(IlvDisplay*    display,
			 const char*    label,
			 const IlvRect& rect,
			 IlUShort       thickness = IlvDefaultGadgetThickness,
			 IlvPalette*    palette   =0);

    IlvPasswordTextField(IlvDisplay*     display,
			 const IlvPoint& point,
			 const char*     label,
			 IlUShort        thickness = IlvDefaultGadgetThickness,
			 IlvPalette*     palette   = 0);

    ~IlvPasswordTextField();
    // ____________________________________________________________

    virtual const char*	getMessage() const;

    inline char		getMaskChar() const { return _maskChar; }

    inline void		setMaskChar(char character) { _maskChar = character; }

    void		changeMaskChar(char character,
				       IlBoolean redraw = IlTrue);

    // ------------------------------------------------------------
    // Bidi interface
    virtual
    IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual IlBoolean	setBidiContext(IlvBidiContext*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    DeclareLazyTypeInfo();

protected:
    IlvPasswordTextField(IlvInputFile& inf , IlvPalette* p);
    IlvPasswordTextField(const IlvPasswordTextField&);

private:
    char		_maskChar;
    static IlInt	_count;
    static char*	_buffer;
    static IlInt	_bufferSize;

public:
    DeclareGraphicAccessors();

    static IlSymbol*	_maskingCharValue;

    // Input Method interaction
    virtual IlBoolean	needsInputContext() const;
};

ILVGDTMODULEINIT(passwded);
#endif /* !__Ilv_Gadgets_Passwded_H */
