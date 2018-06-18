// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/seleclst.h
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
// Declaration of the IlvDvListSelectorDialog class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Seleclst_H)
#define __Ilv_Appframe_Seleclst_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Appframe_Dialog_Msgdlg_H)
#include <ilviews/appframe/dialog/msgdlg.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif

class IlvStringList;

// --------------------------------------------------------------------------
// IlvDvListSelectorDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvListSelectorDialog : public IlvDvAutoFitDialog
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvListSelectorDialog(IlvDisplay*,
			    const char* name,
			    const char* title,
			    const IlvPoint& position,
			    IlUInt choicesCount = 0,
			    const char* const* choices = 0,
			    IlvSystemView transientFor = 0);
    virtual ~IlvDvListSelectorDialog();

    // ----------------------------------------------------------------------
    // Fitting methods
    void		fitToChoices();
    // ----------------------------------------------------------------------
    // Adding /removing choices
    void		setChoices(const char* const*,
				   IlUInt count,
				   IlBoolean updateList = IlTrue);
    void		addChoice(const char*,
				  IlUInt = (IlUInt)-1,
				  IlBoolean updateList = IlFalse);
    void		removeChoices(IlBoolean updateList = IlTrue);
    const char*		getChoice(IlUInt) const;
    IlUInt		getChoiceIndex(const char*) const;

    // ----------------------------------------------------------------------
    // String list managment
    void		updateStringList(IlBoolean bRedraw = IlTrue);
    // ----------------------------------------------------------------------
    // Setting a choice
    void		selectChoice(IlUInt);
    void		selectChoice(const char*);
    inline IlUInt	getSelectedChoiceIndex() const
			{
			    return _selectedChoice;
			}
    const char*		getSelectedChoice() const;
    void		applyChoice();

protected:
    IlvDvStringArray	_choices;
    IlUInt		_selectedChoice;
    IlvStringList*	_stringList;

    virtual IlBoolean	getRequieredGraphicSize(IlvDim& w, IlvDim& h);
    virtual IlvGraphic*	createGraphic(const IlvRect& defaultRect);
    void		choiceChanged();

public:
    static void		SelectChoiceCallback(IlvGraphic* g, IlAny param);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(seleclst);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Seleclst_H */
