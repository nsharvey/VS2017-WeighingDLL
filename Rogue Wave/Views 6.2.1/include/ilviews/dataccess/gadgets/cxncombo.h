// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/cxncombo.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliSQLConnectionComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Cxncombo_H
#define __Ili_Cxncombo_H

#ifndef __Ili_Session_H
#  include <ilviews/dataccess/dbms/session.h>
#endif

#ifndef __Ili_Dlgcombo_H
#  include <ilviews/dataccess/gadgets/dlgcombo.h>
#endif

#ifndef __Ili_Cxndlg_H
#  include <ilviews/dataccess/dialogs/cxndlg.h>
#endif

class ILV_DBSQLG_EXPORTED IliSQLConnectionComboBox
    : public IliDialogComboBox
{
public:
    IliSQLConnectionComboBox(IlvDisplay* display,
			     const char* dialogTitle,
			     const IlvRect& rect,
			     IlUShort thickness = IlvDefaultGadgetThickness,
			     IlvPalette* palette = 0);
    ~IliSQLConnectionComboBox();

    const IliSQLSession* getSessionParams() const;
    void		setSessionParams(const IliSQLSession* session);

    IlBoolean		isShowingName() const;
    void		showName(IlBoolean f);

    IlBoolean		isBoundToValue() const;
    void		bindToValue(IlBoolean);

    // -- overrides IliEntryField

    virtual IlBoolean	f_setValue(const IliValue&,
				   IlBoolean internalP = IlFalse);
    virtual IlBoolean	f_externalToInternal();

    // -- overrides IlvGadget

    DeclareTypeInfo();
    DeclareIOConstructors(IliSQLConnectionComboBox);


protected:
    IliSQLSession*	_session;
    IliString		_dialogTitle;
    IlBoolean		_showName;
    IlBoolean		_boundToValue;

    virtual void	onInitDialog();
    virtual void	onApply();
    virtual void	showDialog(IlBoolean grab);
};

class ILV_DBSQLG_EXPORTED IliSessionTypeClass : public IliPointerTypeClass
{
public:
    IliSessionTypeClass();

    virtual IlAny	lockAny(IlAny a) const;
    virtual void	unLockAny(IlAny a) const;
    virtual void	format(const IliValue&,
			       IliString& dest,
			       const IliFormat&) const;

    IliSQLSession*	getSession(const IliValue&) const;
    IlBoolean		setSession(IliValue&, IliSQLSession*) const;

    static void		AtInit();
};

extern ILV_DBSQLG_EXPORTEDVAR(const IliSessionTypeClass*)
    IliSessionType;


IliModuleDECL_exp(ILV_DBSQLG_EXPORTED, IliSQLConnectionComboBox);

#endif
