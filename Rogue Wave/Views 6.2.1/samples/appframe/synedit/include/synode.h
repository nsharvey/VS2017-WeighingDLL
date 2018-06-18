// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/synode.h
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
// Declaration of the syntaxic parsing classes
// --------------------------------------------------------------------------
#if !defined(__Syn_Synode_H)
#define __Syn_Synode_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

#if !defined(__Ilv_Text_H)
#include <ilviews/gadgets/text.h>
#endif

#ifndef ILVSYN_TEXTPOS
#define ILVSYN_TEXTPOS
typedef unsigned long IlvTextPos;
#endif

enum SyntaxicNodeType {
    SynNone = -1,
    SynClassDefinition = 0,
    SynMember = 1,
    SynMethodDeclaration = 2
};

// --------------------------------------------------------------------------
// SynNode class
// --------------------------------------------------------------------------

class SynNode
: public IlvDvSerializable
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynNode(const char* name = 0);
    virtual ~SynNode();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual SyntaxicNodeType getSyntaxicType() const;
    const char* getName() const { return _name; }
    void        setName(const IlvString& name) { _name = name; }

    void setTextPositions(IlvTextLocation begin,
			  IlvTextLocation end)
    {	_begin = begin;
	_end   = end; }
    IlvTextLocation getBeginPosition() const { return _begin; }
    IlvTextLocation getEndPosition() const { return _end; }
    
    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);
    
protected:
    IlvString _name;
    IlvTextLocation _begin;
    IlvTextLocation _end;
};

// --------------------------------------------------------------------------
// SynType class
// --------------------------------------------------------------------------

class SynType
: public SynNode
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynType(const char* type = 0);
};

// --------------------------------------------------------------------------
// SynVarDecl class
// --------------------------------------------------------------------------

class SynVarDecl
: public SynNode
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynVarDecl(const char* name = 0);
    ~SynVarDecl();

    // ----------------------------------------------------------------------
    // Basic properties
    void setType(SynType* type);
    const SynType* getType() const { return _type; }

    void setDefaultValue(const IlvString& defaultValue)
    {	_defaultValue = defaultValue; }
    const IlvString& getDefaultValue() const { return _defaultValue; }

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

protected:
    SynType* _type;
    IlvString   _defaultValue;
};


// --------------------------------------------------------------------------
// SynMethodDecl class
// --------------------------------------------------------------------------

class SynMethodDecl
: public SynNode
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynMethodDecl(const char* name = 0);
    ~SynMethodDecl();

    // ----------------------------------------------------------------------
    // Basic properties
    void setType(SynType* type);
    const SynType* getType() const { return _type; }

    IlBoolean isConst() const { return _isConst; }
    void       setConst(IlBoolean isConst) { _isConst = isConst; }

    // ----------------------------------------------------------------------
    // Parameters
    void addParameter(SynVarDecl*);
    IlUInt getParametersCount() const
    {	return _parameters.getLength(); }
    SynVarDecl* getParameter(IlUInt iParameter) const
    {	return (SynVarDecl*)_parameters[iParameter]; }
    void razParameters();

    enum VirtualMode { NO_VIRTUAL, VIRTUAL, PURE_VIRTUAL };
    VirtualMode getVirtualMode() const { return _virtualMode; }
    void        setVirtualMode(VirtualMode mode) { _virtualMode = mode; }

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

protected:
    SynType* _type;
    IlBoolean  _isConst;
    IlBoolean  _isVirtual;
    VirtualMode _virtualMode;
    IlvArray    _parameters;
};

// --------------------------------------------------------------------------
// SynClassDecl class
// --------------------------------------------------------------------------

class SynClassDecl
: public SynNode
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynClassDecl(const char* name = 0);
    ~SynClassDecl();

    // ----------------------------------------------------------------------
    virtual SyntaxicNodeType getSyntaxicType() const;
    // ----------------------------------------------------------------------
    // Inheritance
    void addInheritance(const char* classname,
			int mode);
    IlUInt getInheritancesCount() const
    {	return _inheritances.getLength(); }
    int getInheritanceMode(IlUInt iHiner) const;
    const char* getInheritance(IlUInt iHiner) const;
    void razInheritances();
    
    // ----------------------------------------------------------------------
    // methods
    void addMethod(SynMethodDecl*);
    IlUInt getMethodsCount() const
    {	return _methods.getLength(); }
    SynMethodDecl* getMethod(IlUInt iMethod) const
    {	return (SynMethodDecl*)_methods[iMethod]; }
    void razMethods();

    // ----------------------------------------------------------------------
    // Fields
    void addField(SynVarDecl*);
    IlUInt getFieldsCount() const
    {	return _fields.getLength(); }
    SynVarDecl* getField(IlUInt iField) const
    {	return (SynVarDecl*)_fields[iField]; }
    void razFields();

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

protected:
    IlvArray    _inheritances;
    IlvArray    _methods;
    IlvArray    _fields;
};

// --------------------------------------------------------------------------
// SynNodes class
// --------------------------------------------------------------------------

class SynNodes
: public IlvArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    SynNodes();
    ~SynNodes();

    // ----------------------------------------------------------------------
    void addNode(SynNode* node)
    {	add((IlAny)node); }
    SynNode* getNode(IlUInt nNode) const
    {	return (SynNode*)(*this)[nNode]; }
    void emptyNodes();
};

// --------------------------------------------------------------------------
IL_MODULEINIT(syn_synode, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !__Syn_Synode_H */
