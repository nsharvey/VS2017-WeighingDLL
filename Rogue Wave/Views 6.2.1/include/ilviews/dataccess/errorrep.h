// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/errorrep.h
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
// Declaration of the IliErrorReporter class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Errorrep_H
#define __Ili_Errorrep_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif
#ifndef __Ilv_Gadgets_Text_H
#  include <ilviews/gadgets/text.h>
#endif
#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif
#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif
#ifndef __Ilv_Gadgets_Spinbox_H
#  include <ilviews/gadgets/spinbox.h>
#endif
#ifndef __Ilv_Contain_Contain_H
#  include <ilviews/contain/contain.h>
#endif

#ifndef __Ili_Error_H
#  include <ilviews/dataccess/error.h>
#endif

// --------------------------------------------------------------------------
// IliErrorReporter
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliErrorReporter {
public:
  IliErrorReporter () {}
  virtual ~IliErrorReporter ();

  virtual void reportErrors (IlvDisplay* dpy,IlvAbstractView* anchor,
			     const IliErrorList& list) const;

  static void GetMessage(IlvDisplay* display,const IliErrorMessage& msg,
			 IliString& trans);


  static const IliErrorReporter* GetDefault();
  static void SetDefault(const IliErrorReporter* reporter);
};

IliModuleDECL_exp(ILV_INF_EXPORTED,IliErrorReporter);

#endif
