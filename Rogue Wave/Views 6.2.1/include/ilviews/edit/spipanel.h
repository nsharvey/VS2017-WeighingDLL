// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/spipanel.h
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
// Declaration of the IlvFramePanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Spipanel_H
#define __Ilv_Edit_Spipanel_H

#if !defined(__Ilv_Edit_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif
#if !defined(__Ilv_Gadgets_Spinbox_H)
#include <ilviews/gadgets/spinbox.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Numfield_H)
#include <ilviews/gadgets/numfield.h>
#endif

class IlvSpinBox;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvSpinBoxPanel
: public IlvInspectorPanel
{
public:
    IlvSpinBoxPanel(IlvManager*, IlvSystemView transientFor = 0);
    ~IlvSpinBoxPanel();
    // ____________________________________________________________
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
    IlvSpinBox* getSpin() const { return _spin; }
    IlvGraphic* getSelectedObject() const;
    IlvStringList* getLabels() const
    { return (IlvStringList*)getObject("labels") ;}
    IlvStringList* getFields() const
    { return (IlvStringList*)getObject("fields") ;}
    IlvOptionMenu* getOrientation() const
    { return (IlvOptionMenu*)getObject("Orientation") ;}
    IlvOptionMenu* getAlignment() const
    { return (IlvOptionMenu*)getObject("arrowAlign") ;}
    IlvToggle* getLoop() const
    { return (IlvToggle*)getObject("loop") ;}
    IlvNumberField* getIncrement() const
    { return (IlvNumberField*)getObject("increment") ;}
    IlvTextField* getEntry() const
    { return (IlvTextField*)getObject("labelEntry") ;}
    IlvSpinBox* getPeriod() const
    { return (IlvSpinBox*)getObject("period") ;}
    IlvButton* getCleanButton() const
    { return (IlvButton*)getObject("labelCleanButton") ;}
    IlvButton* getRemoveButton() const
    { return (IlvButton*)getObject("labelRemoveButton") ;}
    IlvMessageLabel* getILabel() const
    { return (IlvMessageLabel*)getObject("ilabel") ;}
    IlvMessageLabel* getVLabel() const
    { return (IlvMessageLabel*)getObject("vlabel") ;}
protected:
    IlvSpinBoxPanel(IlvManager*,
		    const char*   className,
		    const char*   title,
		    const char*   icon,
		    const char*   data,
		    const char*   filename = 0, // if present, overloads data
		    IlvSystemView transientFor = 0);
private:
    IlvSpinBox* _spin;
};

#endif /*  ! __Ilv_Edit_Spipanel_H */


