// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vrgadcon.h
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
// Declaration of the IlvVariableGadgetContainer class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vrgadcon_H
#define __Ilv31_Vrgadcon_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv31_Variable_H)
#include <ilviews/variable.h>
#endif
#if !defined(__Ilv31_Itf_Attrcont_H)
#include <ilviews/intrface/attrcont.h>
#endif
#if !defined(__Ilv31_Itf_Varcont_H)
#include <ilviews/intrface/varcont.h>
#endif
#if !defined(__Ilv31_Itf_Vario_H)
#include <ilviews/intrface/vario.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableGadgetContainer
: public IlvGadgetContainer, public IlvACItf, public IlvVCItf {
public:
    IlvVariableGadgetContainer(IlvAbstractView* parent,
			       const IlvRect&   size,
			       IlBoolean        useacc  = IlFalse,
			       IlBoolean        visible = IlTrue)
    : IlvGadgetContainer(parent, size, useacc, visible), _parser(0) {}
    IlvVariableGadgetContainer(IlvDisplay*    d,
			       IlvSystemView  parent,
			       const IlvRect& size,
			       IlBoolean      useacc  = IlFalse,
			       IlBoolean      visible = IlTrue)
    : IlvGadgetContainer(d, parent, size, useacc, visible), _parser(0) {}
    IlvVariableGadgetContainer(IlvDisplay*   d,
			       IlvSystemView w,
			       IlBoolean    useacc = IlFalse)
    : IlvGadgetContainer(d, w, useacc), _parser(0) {}
    IlvVariableGadgetContainer(IlvDisplay*    d,
			       const char*    name,
			       const char*    title,
			       const IlvRect& dims,
			       IlBoolean      useacc  = IlFalse,
			       IlBoolean      visible = IlTrue)
    : IlvGadgetContainer(d, name, title, dims, useacc, visible), _parser(0) {}
    IlvVariableGadgetContainer(IlvDisplay*    d,
			       const char*    name,
			       const char*    title,
			       const IlvRect& dims,
			       IlUInt         properties,
			       IlBoolean      useacc       = IlFalse,
			       IlBoolean      visible      = IlTrue,
			       IlvSystemView  transientFor = 0)
    : IlvGadgetContainer(d, name, title, dims, properties,
			 useacc, visible, transientFor),
      _attributes(),
      _parser(0) {}
    // ____________________________________________________________
    virtual IlvParser* getParser() const;
    void    setParser(IlvParser* parser) { _parser = parser; }
    virtual IlvViewInputFile* createInputFile(IL_STDPREF istream&);
    virtual IlvVariable* connect(IlvGraphic* g,
				 const char* attClass,
				 const char* varName);
    virtual IlvVariable* connect(IlvGraphicAttribute* attr,
				 const char*	      varName);
protected:
    virtual IlList* getAttributeList() const;
    virtual IlvContainer* getTheContainer();

    IlList	_attributes;
    IlvParser*	_parser;
    virtual void cleanObj(IlvGraphic* obj);
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableGadgetContainerInputFile
: public IlvGadgetViewInputFile, public IlvVIItf {
public:
    IlvVariableGadgetContainerInputFile(IL_STDPREF istream& stream,
					IlvVariableGadgetContainer* cont = 0)
    : IlvGadgetViewInputFile(stream, cont) {}
    // ____________________________________________________________
    IlvVariableGadgetContainer* getVariableGadgetContainer() const
	{ return ILVDYNAMICCAST(IlvVariableGadgetContainer*, _container); }
    virtual IlBoolean   parseBlock(const char* blockName);
    virtual const char*  typeOf() const;
};

#endif /* !__Ilv31_Vrgadcon_H */
