// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/varcont.h
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
// Declaration of the IlvVariableContainer class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Varcont_H
#define __Ilv31_Varcont_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif

#if !defined(__Ilv31_Attrcont_H)
#include <ilviews/attrcont.h>
#endif
#if !defined(__Ilv31_Itf_Varcont_H)
#include <ilviews/intrface/varcont.h>
#endif
#if !defined(__Ilv31_Itf_Vario_H)
#include <ilviews/intrface/vario.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv31_Variable_H)
#include <ilviews/variable.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableContainer
: public IlvAttributeContainer, public IlvVCItf
{
public:
    IlvVariableContainer(IlvAbstractView* parent,
			 const IlvRect&   size,
			 IlBoolean        useacc  = IlTrue,
			 IlBoolean        visible = IlTrue)
    : IlvAttributeContainer(parent, size, useacc, visible),
      _parser(0) {}
    IlvVariableContainer(IlvDisplay*    display,
			 IlvSystemView  parent,
			 const IlvRect& size,
			 IlBoolean      useacc  = IlTrue,
			 IlBoolean      visible = IlTrue)
    : IlvAttributeContainer(display, parent, size, useacc, visible),
      _parser(0) {}
    IlvVariableContainer(IlvDisplay*	display,
			 IlvSystemView	window,
			 IlBoolean	 useacc = IlFalse)
    : IlvAttributeContainer(display, window, useacc),
      _parser(0) {}
    IlvVariableContainer(IlvDisplay*	display,
			 const char*	name,
			 const char*	title,
			 const IlvRect&	dims,
			 IlBoolean	useacc = IlTrue,
			 IlBoolean	visible = IlTrue)
    : IlvAttributeContainer(display, name, title, dims, useacc, visible),
      _parser(0) {}
    IlvVariableContainer(IlvDisplay*	display,
			 const char*	name,
			 const char*	title,
			 const IlvRect&	dims,
			 IlUInt		properties,
			 IlBoolean	useacc       = IlTrue,
			 IlBoolean	visible      = IlTrue,
			 IlvSystemView	transientFor = 0)
    : IlvAttributeContainer(display, name, title, dims, properties, useacc,
			    visible, transientFor),
      _parser(0) {}
    // ------------------------------------------------------------
    virtual IlvParser* getParser() const;
    void setParser(IlvParser* parser) { _parser = parser; }
    virtual IlvViewInputFile* createInputFile(IL_STDPREF istream&);
    virtual IlvVariable* connect(IlvGraphic* g, const char* attClass,
				 const char* varName);
    virtual IlvVariable* connect(IlvGraphicAttribute* attr,
				 const char*	      varName);
protected:
    virtual IlvContainer* getTheContainer();
    virtual void cleanObj(IlvGraphic* obj);
    IlvParser* _parser;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableContainerInputFile
: public IlvViewInputFile, public IlvVIItf {
public:
    IlvVariableContainerInputFile(IL_STDPREF istream& stream,
				  IlvVariableContainer* cont = 0)
    : IlvViewInputFile(stream, cont) {}
    // ____________________________________________________________
    IlvVariableContainer* getVariableContainer() const
	{ return ILVDYNAMICCAST(IlvVariableContainer*, _container); }
    virtual IlBoolean parseBlock(const char* blockName);
    virtual const char* typeOf() const;
};

#endif /* !__Ilv31_VariableContainerH */
