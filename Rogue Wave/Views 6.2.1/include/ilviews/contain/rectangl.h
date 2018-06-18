// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/contain/rectangl.h
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
// Definition of the IlvContainerRectangle class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Contain_Rectangl_H
#define __Ilv_Contain_Rectangl_H

#if !defined(__Ilv_Graphics_Rectview_H)
#include <ilviews/graphics/rectview.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvContainerRectangle : public IlvViewRectangle
{
public:
    IlvContainerRectangle(IlvDisplay*     display,
			  const IlvRect&  rect,
			  IlvPalette*     palette = 0);
    virtual ~IlvContainerRectangle();

    virtual void	makeView(IlvPort* dst, const IlvTransformer* t = 0);
    virtual IlvView*	createView(IlvAbstractView* parent,
				   const IlvRect& size);
    virtual void	drawContents(IlvPort* dst,
				     const IlvRect& size,
				     const IlvRegion* clip) const;
    virtual
    IlvContainer*	getContainer() const;
    const char*		getFilename() const { return _filename; }
    void		setFilename(const char* name,
				    IlBoolean redraw = IlFalse);
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvContainerRectangle);

protected:
    void		readFile(IlBoolean redraw = IlFalse);
    char*		_filename;

public:
    DeclareGraphicAccessors();
    static IlSymbol*	_innerContainerValue;
};

ILVVWSMODULEINIT(rectcont);
#endif /* __Ilv_Rectgadc_H */
