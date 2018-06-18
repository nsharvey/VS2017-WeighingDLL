// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/libdeps/include/dialog.h
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
// Declaration of new dialog class: GraphLayoutDialog
// --------------------------------------------------------------------------

#include <ilviews/gadgets/idialog.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/graphics/relfline.h>

class GraphLayoutDialog
    : public IlvDialog
{
public:
    GraphLayoutDialog(IlvDisplay*    display,
		      const char*    name,
		      const char*    title,
		      IlvSystemView  transientFor = 0);
    IlBoolean	get(IlBoolean);
    IlBoolean	getResult();

    const char*	getLibName() const;
    void	setLibName(const char*);

protected:
private:
};
