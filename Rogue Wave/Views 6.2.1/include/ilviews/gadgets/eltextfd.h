// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/eltextfd.h
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
// Declaration of the IlvElasticTextField class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Eltextfd_H
#define __Ilv_Gadgets_Eltextfd_H

#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvElasticTextField : public IlvTextField
{
public:
    IlvElasticTextField(IlvDisplay*	display,
			const IlvPoint&	at,
			const char*	label,
			IlvDim		minimumSize,
			IlvDim		maximumSize,
			IlUShort	thick = IlvDefaultGadgetThickness,
			IlvPalette*	pal = 0)
	: IlvTextField(display, at, label, thick, pal),
	  _minimumSize(minimumSize),
	  _maximumSize(maximumSize)
    {
	recomputeSize();
    }

    IlvElasticTextField(IlvDisplay*	display,
			const char*	label,
			const IlvRect&	rect,
			IlvDim		minimumSize,
			IlvDim		maximumSize,
			IlUShort	thick = IlvDefaultGadgetThickness,
			IlvPalette*	pal = 0)
	: IlvTextField(display, label, rect, thick, pal),
	  _minimumSize(minimumSize),
	  _maximumSize(maximumSize)
    {
	recomputeSize();
    }

    ~IlvElasticTextField() {}
    // ____________________________________________________________
    IlBoolean		isElastic() const;
    void		setElastic(IlBoolean b);
    inline IlvDim	getMinimumSize() const { return _minimumSize; }
    inline IlvDim	getMaximumSize() const { return _maximumSize; }
    inline void		setMinimumSize(IlvDim size) { _minimumSize = size; }
    inline void		setMaximumSize(IlvDim size) { _maximumSize = size; }
    virtual void	beforeResize();
    virtual void	afterResize();
    virtual void	labelChanged();
    virtual void	updateSize(IlBoolean = IlFalse);
    virtual IlvDim	computeSize() const;
    void		recomputeSize();

    IlvDefineCallback(BeforeResize);
    IlvDefineCallback(AfterResize);

    IlUInt		getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    inline
    static IlSymbol*	BeforeResizeSymbol() { return _BeforeResizeSymbol; }
    inline
    static IlSymbol*	AfterResizeSymbol() { return _AfterResizeSymbol; }

    static IlSymbol*	_BeforeResizeSymbol;
    static IlSymbol*	_AfterResizeSymbol;
    static IlSymbol*	_setMinimumSizeValue;
    static IlSymbol*	_setMaximumSizeValue;
    static IlSymbol*	_elasticValue;

    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvElasticTextField);

protected:
    IlvDim		_minimumSize;
    IlvDim		_maximumSize;
};

ILVGDTMODULEINIT(eltextfd);
#endif /* !__Ilv_Gadgets_Eltextfd_H */
