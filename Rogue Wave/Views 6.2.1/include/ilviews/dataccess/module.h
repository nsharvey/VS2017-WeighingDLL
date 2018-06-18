// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/module.h
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
// Declaration of the IliModuleDECL and IliModuleDEF macros
// --------------------------------------------------------------------------
#ifndef __Ili_Module_H
#define __Ili_Module_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifndef __Ilv_Base_Gcontext_H
#  include <ilviews/base/gcontext.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

#define ILI_SMART_INIT

#define IliModuleCLASS(classname) ili_module_ ## classname

#if defined(ILI_SMART_INIT) && defined(ILI_BUILDLIBS)
#  define IliModuleINIT(x)
#else
#  define IliModuleINIT(x) x
#endif

#define IliModuleDECL_exp2(class_mode,classname) \
IliModuleINIT(static) class_mode IliModuleCLASS(classname) { \
   static unsigned short _counter; \
public: \
   IliModuleCLASS(classname) ();\
  ~IliModuleCLASS(classname) ();\
  static void Lock (); \
  static void UnLock (); \
protected: \
  static void AtInit ();  \
  static void AtEnd () ;  \
} IliModuleINIT(_ili_module_##classname)

#define IliModuleDECL_exp(mode,classname) \
   IliModuleDECL_exp2(class mode,classname)

#define IliModuleDECL(classname) IliModuleDECL_exp2(class,classname)

#define IliModuleDEF(classname,atinit,atexit) \
  unsigned short  IliModuleCLASS(classname) :: _counter = 0 ; \
  IliModuleCLASS(classname) :: IliModuleCLASS(classname) () { Lock(); } \
  IliModuleCLASS(classname) :: ~IliModuleCLASS(classname) () { UnLock(); } \
  void IliModuleCLASS(classname) :: Lock () { _counter++; \
    if (_counter == 1) { AtInit(); } } \
  void IliModuleCLASS(classname) :: UnLock () { \
   _counter--; if (!_counter) AtEnd(); } \
  void IliModuleCLASS(classname) :: AtInit () { atinit } \
  void IliModuleCLASS(classname) :: AtEnd  () { atexit }

// --------------------------------------------------------------------------
// News modules
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// AtInit
// --------------------------------------------------------------------------
#define IliBeginModuleAtInit(exp,mod) \
static int STModule##mod##Counter = 0; \
ILV_##exp##_EXPORTEDFN(void) IliAtInitModule##mod () { \
STModule##mod##Counter++; \
if (STModule##mod##Counter == 1) { \
IlvGlobalContext::GetInstance(); //

#define IliEndModuleAtInit() }} //

// --------------------------------------------------------------------------
// AtExit
// --------------------------------------------------------------------------
#define IliBeginModuleAtExit(exp,mod) \
ILV_##exp##_EXPORTEDFN(void) IliAtExitModule##mod() { \
STModule##mod##Counter--; \
if (STModule##mod##Counter == 0) { //

#define IliEndModuleAtExit() }} //

// --------------------------------------------------------------------------
// After lock
// --------------------------------------------------------------------------
#define IliBeginModuleAfterLock(exp,mod) \
ILV_##exp##_EXPORTEDFN(void) IliAfterLockModule##mod() { //

#define IliEndModuleAfterLock() } //

#define IliCallModuleFunctionAfterLock(mod) \
IliAfterLockModule##mod()

// --------------------------------------------------------------------------
// Module definition
// --------------------------------------------------------------------------
#define IliModuleDefinition(cl,mod) \
IliModuleDEF(cl,IliAtInitModule##mod();,IliAtExitModule##mod();) //

// --------------------------------------------------------------------------
// Call AtInit or AtExit function
// --------------------------------------------------------------------------
#define IliUseModuleFunctionAtInit(mod) extern void IliAtInitModule##mod()
#define IliCallModuleFunctionAtInit(mod) IliAtInitModule##mod()

#define IliUseModuleFunctionAtExit(mod) extern void IliAtExitModule##mod()
#define IliCallModuleFunctionAtExit(mod) IliAtExitModule##mod()

#endif
