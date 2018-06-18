// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/filter.h
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
// Declaration of the IlvLayoutGraphicFilter class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Filter_H
#define __Ilv_Layout_Filter_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif /* __Ilv_Base_Graphic_H */

class IlvGrapherAdapter;

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvLayoutGraphicFilter
: public IlvLayoutValueInterface
{
public:
    IlvLayoutGraphicFilter();

    void		setGrapherAdapter(IlvGrapherAdapter*);
    IlvGrapherAdapter*	getGrapherAdapter() const;

    virtual IlBoolean	accept(IlvGraphic* obj);

    IlvDeclareLazyClassInfo();

protected:
private:
    IlvGrapherAdapter*	_adapter;
};

ILVGRLMODULEINIT(l_filter)
#endif /* !__Ilv_Layout_Filter_H */
