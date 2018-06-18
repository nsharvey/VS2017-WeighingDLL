// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/intrface/vario.h
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
// Declaration of the IlvVariableInputInterface and
// IlvVariableOutputInterface interfaces
// Defined in library ilvvar
// --------------------------------------------------------------------------
#ifndef __Ilv31_Itf_Vario_H
#define __Ilv31_Itf_Vario_H

#if !defined(__Ilv31_Itf_Varhold_H)
#include <ilviews/intrface/varhold.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif

class IlvGraphicAttribute;
class IlvVariable;
// --------------------------------------------------------------------------
#define IlvVariableInputInterface IlvVIItf
class ILV31VAREXPORTED IlvVariableInputInterface
{
public:
    virtual void readAVariable(IlvVHItf*, IlvInputFile&,
			       const char* holderClassName);
    virtual IlvVariable* getAVariable(IlvVHItf*,
				      IlvInputFile&);
    IlBoolean parseVariables(IlvVHItf*, IlvInputFile&,
			     const char* blockDescriptor,
			     const char* holderClassName);
};

// --------------------------------------------------------------------------
#define IlvVariableOutputInterface IlvVOItf
class ILV31VAREXPORTED IlvVariableOutputInterface
{
public:
    virtual void saveVariables(const IlvVHItf*, IlvOutputFile&);
    virtual void saveAnAttribute(const IlvVHItf*, IlvOutputFile&,
				 IlvGraphicAttribute*);
    virtual void saveAVariable(const IlvVHItf*, IlvOutputFile&,
			       IlvVariable*);
};

#endif /* !__Ilv31_Itf_Vario_H */
