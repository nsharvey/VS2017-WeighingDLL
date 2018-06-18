// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/matitpa.h
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
// Declaration of the IlvMatrixItemPanel class.
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Matitpa_H
#define __Ilv_Edit_Matitpa_H

#if !defined(__Ilv_Edit_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif
#ifndef __Ilv_Respanel_H
#include <ilviews/edit/respanel.h>
#endif

class ILVGDTEXPORTED IlvResourcePanel;
class ILVGDTEXPORTED IlvMatrix;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvMatrixItemPanel
    : public IlvInspectorPanel
{
public:
    IlvMatrixItemPanel(IlvManager*,
		       IlvSystemView transientFor = 0);
    ~IlvMatrixItemPanel();
    // ____________________________________________________________
    virtual void	applyChange(IlvGraphic*);
    virtual void      	initFrom(IlvGraphic*);
    void              	initFromAll(IlBoolean redraw = IlFalse);
    void              	initFromRow(IlUShort,
				    IlBoolean redraw = IlFalse);
    void              	initFromColumn(IlUShort,
				       IlBoolean = IlFalse);
    void              	initFromItem(IlUShort col,
				     IlUShort row,
				     IlBoolean = IlFalse);
    void		resourcePanelDeleted();
private:
    void applyItemChange(IlvMatrix* matrix,
			 IlUShort col,
			 IlUShort row,
			 const char* label,
			 IlUShort typeNumber,
			 IlBoolean filled,
			 IlBoolean relief,
			 IlBoolean sensitive,
			 IlBoolean readOnly,
			 IlBoolean interactive,
			 IlBoolean fillBg,
			 IlBoolean grayed,
			 IlvPosition alignment,
			 IlvPalette* palette);
    IlvMatrix*        _matrix;
};

#endif /* !__Ilv_Edit_Matitpa_H */
