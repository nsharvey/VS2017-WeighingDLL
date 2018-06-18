// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/attrmac.h
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
// Macro definitions for the attributes
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Attrmac_H
#define __Ilv31_Attrmac_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif

class IlvGraphic;
class IlvContainer;
class IlvManager;
class IlvGraphicAttribute;

typedef IlvGraphicAttribute*
  (*IlvContainerAttributeCreator)(IlvContainer*, IlvGraphic* obj,
				  const char* name);
typedef IlvGraphicAttribute*
  (*IlvManagerAttributeCreator)(IlvManager*, IlvGraphic* obj,
				const char* name);

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvGraphicAttributeClassInfo
{
public:
    IlvGraphicAttributeClassInfo(const char* className,
				 IlvContainerAttributeCreator c1 = 0,
				 IlvManagerAttributeCreator   c2 = 0);
    // ____________________________________________________________
    const char* getClassName() const { return _className; }
    IlvContainerAttributeCreator getContainerCreator() const
	{ return _containerCreator; }
    IlvManagerAttributeCreator getManagerCreator() const
	{ return _managerCreator; }
protected:
    const char*                  _className;
    IlvContainerAttributeCreator _containerCreator;
    IlvManagerAttributeCreator   _managerCreator;
private:
    IlvGraphicAttributeClassInfo(const IlvClassInfo&) {}
    IlvGraphicAttributeClassInfo&
    operator=(const IlvGraphicAttributeClassInfo&) { return *this; }

};

#define IlvDeclareTypeAttribute() public: \
    static IlvGraphicAttributeClassInfo* _classInfo; \
    static  IlvGraphicAttributeClassInfo* ClassInfo() { return _classInfo; } \
    virtual IlvGraphicAttributeClassInfo* getClassInfo() const; \
    const char* className() const { return getClassInfo()->getClassName(); }

#define IlvDeclareAttribute() IlvDeclareTypeAttribute() \
    IlvGraphicAttribute& operator=(const IlvAttributeValue& value) { \
	set(value); \
	return *this; \
    } \
    static IlvGraphicAttribute* readContainerAttribute(IlvContainer*,\
						       IlvGraphic*,\
						       const char* name); \
    static IlvGraphicAttribute* readManagerAttribute(IlvManager*, \
						     IlvGraphic*,\
						     const char* name)

#define IlvRegisterAttribute(className) \
    IlvGraphicAttributeClassInfo* className::getClassInfo() const \
	{ return _classInfo; } \
    IlvGraphicAttribute* className::readContainerAttribute(IlvContainer* c, \
							   IlvGraphic* obj,\
							   const char* name)\
	{ return new className(c, obj, name);} \
    IlvGraphicAttribute* className::readManagerAttribute(IlvManager* c, \
							 IlvGraphic* obj,\
							 const char* name)\
	{ return new className(c, obj, name);} \
    IlvGraphicAttributeClassInfo* className::_classInfo = \
	new IlvGraphicAttributeClassInfo(ILVSTRING(className), \
    (IlvContainerAttributeCreator) className::readContainerAttribute, \
    (IlvManagerAttributeCreator) className::readManagerAttribute)
#define IlvLoadGraphicAttribute(classname) \
IlvManagerAttributeCreator _##classname = \
    (IlvManagerAttributeCreator)classname::readManagerAttribute
#define IlvPreRegisterAttribute(className) \
    IlvGraphicAttributeClassInfo* className::getClassInfo() const \
	{ return _classInfo; } \
    IlvGraphicAttribute* className::readContainerAttribute(IlvContainer* c, \
							   IlvGraphic*   obj,\
							   const char*   name) \
	{ return new className(c, obj, name); } \
    IlvGraphicAttribute* className::readManagerAttribute(IlvManager* c, \
							 IlvGraphic* obj,\
							 const char* name) \
	{ return new className(c, obj, name); } \
    IlvGraphicAttributeClassInfo* className::_classInfo = 0
#define IlvPostRegisterAttribute(className) \
    className::_classInfo = new IlvGraphicAttributeClassInfo(#className, \
		(IlvContainerAttributeCreator)className::readContainerAttribute, \
		(IlvManagerAttributeCreator)className::readManagerAttribute)


#endif /* __Ilv31_Attrmac_H */

