// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/xml.h
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
// Set of classes for the XML parser
// --------------------------------------------------------------------------
#ifndef __Il_Xml_H
#define __Il_Xml_H

#if !defined(__Il_List_H)
#include <ilog/list.h>
#endif
#if !defined(__Il_Iostream_H)
#include <ilog/iostream.h>
#endif
class IlArray;

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlError
{
public:
    enum Severity {
	NoError,
	Warning,
	Error
    };
    static IlBoolean	IsSet();
    static void		Set(Severity severity, int code, int line);
    static const char*	Get(Severity& severity, int& code, int& line);
    static void		Reset();
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlSpaces
{
public:
    IlXmlSpaces(int n_) : n(n_) {}
    int n;
};

IL_STDPREF ostream& operator<<(IL_STDPREF ostream&, const IlXmlSpaces&);

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlString
{
public:
    IlXmlString(const char* t_) : t(t_) {}
    const char* t;
};

ILOG_EXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream&, const IlXmlString&);

// --------------------------------------------------------------------------
// Interface for XML nodes
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodeI
{
public:
    virtual ~IlXmlNodeI();
    // ____________________________________________________________
    enum Type {
	Attribute,
	Element,
	Text,
	Comment,
	CData,
	PI,
	CharRef,
	EntityRef
    };
    virtual Type		getType() const = 0;
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream& stream) const = 0;
};

inline IL_STDPREF ostream&
operator<<(IL_STDPREF ostream& os, const IlXmlNodeI& node)
{
    return node.write(os);
}

// --------------------------------------------------------------------------
// Interface for XML node iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodeIteratorI
{
public:
    virtual ~IlXmlNodeIteratorI();
    virtual IlBoolean	hasMoreNodes() const = 0;
    virtual IlXmlNodeI*	getNextNode() = 0;
};

// --------------------------------------------------------------------------
// Actual XML node iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodeIterator : public IlXmlNodeIteratorI
{
public:
    IlXmlNodeIterator(IlXmlNodeIteratorI* iterator)
    : _iterator(iterator) {}
    virtual ~IlXmlNodeIterator();
    // ____________________________________________________________
    virtual IlBoolean	hasMoreNodes() const;
    virtual IlXmlNodeI*	getNextNode();

protected:
    IlXmlNodeIteratorI*	_iterator;
};

// --------------------------------------------------------------------------
// XML node list iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodeListIterator
: public IlXmlNodeIteratorI,
  public Il_LIterator
{
public:
    IlXmlNodeListIterator(const Il_List& list);
    // ____________________________________________________________
    virtual IlBoolean	hasMoreNodes() const;
    virtual IlXmlNodeI*	getNextNode();
};

// --------------------------------------------------------------------------
// XML node array iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodeArrayIterator : public IlXmlNodeIteratorI
{
public:
    IlXmlNodeArrayIterator(const IlArray& objs);
    // ____________________________________________________________
    virtual IlBoolean	hasMoreNodes() const;
    virtual IlXmlNodeI*	getNextNode();

protected:
    const IlArray&	_nodeArray;
    IlUInt		_currentIndex;
};

// --------------------------------------------------------------------------
// XML node pointer array iterator
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodePtrArrayIterator : public IlXmlNodeIteratorI
{
public:
    IlXmlNodePtrArrayIterator(IlUInt count, const IlXmlNodeI** objs);
    // ____________________________________________________________
    virtual IlBoolean	hasMoreNodes() const;
    virtual IlXmlNodeI*	getNextNode();

protected:
    IlUInt		_count;
    const IlXmlNodeI**	_nodes;
    IlUInt		_currentIndex;
};

// --------------------------------------------------------------------------
// Interface for attributes
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlAttributeI : public IlXmlNodeI
{
public:
    virtual ~IlXmlAttributeI();
    // ____________________________________________________________
    virtual const char*		getName() const = 0;
    virtual void		setName(const char* name);
    virtual void		storeName(char* name) = 0;
    virtual const char*		getValue() const = 0;
    virtual void		setValue(const char* value);
    virtual void		storeValue(char* value) = 0;
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream& stream) const;
    virtual Type		getType() const;

    static void			Write(IL_STDPREF ostream& stream,
				      const char*         name,
				      const char*         value);
    static void			Write(IL_STDPREF ostream& stream,
				      const char*         name,
				      IlInt               value);
    static void			Write(IL_STDPREF ostream& stream,
				      const char*         name,
				      IlDouble            value);
};

// --------------------------------------------------------------------------
// Default implementation of an attribute
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlAttribute : public IlXmlAttributeI
{
public:
    IlXmlAttribute(const char* name  = 0,
		   const char* value = 0);
    virtual ~IlXmlAttribute();
    // ____________________________________________________________
    virtual const char*		getName() const;
    virtual void		storeName(char*);
    virtual const char*		getValue() const;
    virtual void		storeValue(char* name);

private:
    char*			_name;
    char*			_value;
};

// --------------------------------------------------------------------------
// Interface for elements.
// --------------------------------------------------------------------------
class IlXmlDocumentI;
class ILOG_EXPORTED IlXmlElementI : public IlXmlNodeI
{
public:
    IlXmlElementI()
    : IlXmlNodeI()
    {}
    virtual ~IlXmlElementI();
    // ____________________________________________________________
    virtual Type		getType() const;
    virtual const char*		getTag() const = 0;
    virtual void		setTag(const char* tag);
    virtual void		storeTag(char* tag);
    virtual void		addChild(IlXmlNodeI* node);
    virtual void		storeAttribute(IlXmlDocumentI* document,
					       char*           name,
					       char*           value);
    virtual IlXmlElementI*	createChildElement(char* tag) const;
    virtual IlXmlAttributeI*	createAttribute(char* name,
						char* value) const;
    virtual void		addAttribute(IlXmlAttributeI* attribute);
    virtual IlXmlAttributeI*	getAttribute(const char* name) const;
    const char*			getAttributeValue(const char* name) const;
    virtual IlBoolean		doesPreserveWhiteSpaces() const;
    virtual void		preserveWhiteSpaces(IlBoolean preserve);
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream& os) const;
    virtual void	writeAttributes(IL_STDPREF ostream& os) const;
    virtual IlBoolean		writeChildren(IL_STDPREF ostream& os) const;
    virtual const char*		getText() const;
    static inline void		ResetIndent()	  { _indent = 0; }
    static inline IlUInt	GetIndentation() { return _indentation; }
    static inline void		SetIndentation(IlUInt i) { _indentation = i; }
    static inline IlUInt	GetIndent() { return _indent; }
    static inline void		IndentMore()	  { _indent += _indentation; }
    static inline void		IndentLess()	  { _indent -= _indentation; }
    virtual IlXmlNodeIteratorI*	createChildrenIterator() const;
    virtual IlXmlNodeIteratorI*	createAttributesIterator() const;

private:
    static IlUInt		_indent;
    static IlUInt		_indentation;
};

//
// --------------------------------------------------------------------------
IlDefineExpListOf(IlXmlAttributeI, IlXmlAttributeI*, ILOG_EXPORTED);
IlDefineExpListOf(IlXmlNodeI,      IlXmlNodeI*,      ILOG_EXPORTED);
class ILOG_EXPORTED IlXmlElement : public IlXmlElementI
{
public:
    IlXmlElement(const char* tag = 0);
    virtual ~IlXmlElement();
    // ____________________________________________________________
    virtual const char*		getTag() const;
    virtual void		storeTag(char*);

    IlUInt			getChildrenCardinal() const;
    virtual void		addChild(IlXmlNodeI*);
    inline
    IlListOf(IlXmlNodeI)&	getChildren() const
				{
				    return IL_CONSTCAST(IlXmlElement*,
							this)->_children;
				}

    IlUInt			getAttributesCardinal() const;
    virtual void		addAttribute(IlXmlAttributeI*);
    inline
    IlListOf(IlXmlAttributeI)&	getAttributes() const
				{
				    return IL_CONSTCAST(IlXmlElement*,
							this)->_attributes;
				}
    virtual IlXmlAttributeI*	getAttribute(const char*) const;
    virtual IlBoolean		doesPreserveWhiteSpaces() const;
    virtual void		preserveWhiteSpaces(IlBoolean preserve);
    IlXmlElement*		getElement(const char* tagName,
					   IlXmlNodeI* skip = 0) const;
    virtual const char*		getText() const;
    virtual IlXmlNodeIteratorI*	createChildrenIterator() const;
    virtual IlXmlNodeIteratorI* createAttributesIterator() const;

private:
    char*			_tag;
    IlListOf(IlXmlNodeI)	_children;
    IlListOf(IlXmlAttributeI)	_attributes;
    IlBoolean			_preserveWS;
};

// --------------------------------------------------------------------------
// Interface for Comment nodes.
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlCommentI : public IlXmlNodeI
{
public:
    virtual ~IlXmlCommentI();
    // ____________________________________________________________
    virtual const char*		getComment() const = 0;
    virtual void		setComment(const char* comment);
    virtual void		storeComment(char* comment) = 0;
    virtual Type		getType() const;
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream&) const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlComment : public IlXmlCommentI
{
public:
    IlXmlComment()
    : IlXmlCommentI(),
      _comment(0)
    {}
    virtual ~IlXmlComment();
    // ____________________________________________________________
    virtual const char*	getComment() const;
    virtual void	storeComment(char*);

private:
    char*		_comment;
};

// --------------------------------------------------------------------------
// Interface for Text nodes.
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlTextI : public IlXmlNodeI
{
public:
    virtual ~IlXmlTextI();
    // ____________________________________________________________
    virtual Type		getType() const;
    virtual const char*		getText() const = 0;
    virtual void		setText(const char* text);
    virtual void		storeText(char* text) = 0;
    virtual void		appendText(const char* text) = 0;
    virtual IL_STDPREF ostream& write(IL_STDPREF ostream&) const;
};

// --------------------------------------------------------------------------
// Default implementation of Text nodes.
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlText : public IlXmlTextI
{
public:
    IlXmlText()
    : IlXmlTextI(),
      _text(0)
    {}
    virtual ~IlXmlText();
    // ____________________________________________________________
    virtual const char*	getText() const;
    virtual void	storeText(char*);
    virtual void	appendText(const char* text);

private:
    char*		_text;
};

// --------------------------------------------------------------------------
// class IlXmlPII
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlPII : public IlXmlNodeI
{
public:
    virtual ~IlXmlPII();
    // ____________________________________________________________
    virtual Type		getType() const;
    virtual const char*		getTarget() const = 0;
    virtual void		setTarget(const char* target);
    virtual void		storeTarget(char* target) = 0;
    virtual const char*		getData() const = 0;
    virtual void		setData(const char* data);
    virtual void		storeData(char* data) = 0;
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream&) const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlPI : public IlXmlPII
{
public:
    IlXmlPI()
    : IlXmlPII(),
      _target(0),
      _data(0)
    {
    }
    virtual ~IlXmlPI();
    // ____________________________________________________________
    virtual const char*	getTarget() const;
    virtual void	storeTarget(char*);
    virtual const char*	getData() const;
    virtual void	storeData(char*);

private:
    char*		_target;
    char*		_data;
};

// --------------------------------------------------------------------------
// class IlXmlCDataI
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlCDataI : public IlXmlNodeI
{
public:
    virtual ~IlXmlCDataI();
    // ____________________________________________________________
    virtual Type		getType() const;
    virtual const char*		getData() const = 0;
    virtual void		setData(const char* data);
    virtual void		storeData(char* data) = 0;
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream&) const;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlCData : public IlXmlCDataI
{
public:
    IlXmlCData()
    : IlXmlCDataI(),
      _data(0)
    {
    }
    virtual ~IlXmlCData();
    // ____________________________________________________________
    virtual const char*	getData() const;
    virtual void	storeData(char*);

private:
    char*		_data;
};

// --------------------------------------------------------------------------
// class IlXmlCharRefI
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlCharRefI : public IlXmlNodeI
{
public:
    ~IlXmlCharRefI();
    // ____________________________________________________________
    virtual Type		getType() const;
    virtual int			getRefCode() const = 0;
    virtual void		setRefCode(int code) = 0;
    virtual const char*		getRefName() const = 0;
    virtual void		setRefName(const char* name);
    virtual void		storeRefName(char* name) = 0;
    virtual IL_STDPREF ostream& write(IL_STDPREF ostream&) const;
};

// --------------------------------------------------------------------------
// class IlXmlCharRefElement
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlCharRef : public IlXmlCharRefI
{
public:
    IlXmlCharRef()
    : IlXmlCharRefI(),
      _refCode(0),
      _refName(0)
    {
    }
    virtual ~IlXmlCharRef();
    // ____________________________________________________________
    virtual int		getRefCode() const;
    virtual void	setRefCode(int code);
    virtual const char*	getRefName() const;
    virtual void	storeRefName(char*);

private:
    int			_refCode;
    char*		_refName;
};

// --------------------------------------------------------------------------
// Element factory for documents
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlNodeFactory
{
public:
    virtual ~IlXmlNodeFactory();
    // ____________________________________________________________
    IlXmlAttributeI*	createAttribute(IlXmlElementI* element,
					char*          name,
					char*          value) const;
    IlXmlElementI*	createElement(char* tag) const;
    IlXmlTextI*		createText() const;
    IlXmlCommentI*	createComment() const;
    IlXmlCharRefI*	createCharRef() const;
    IlXmlPII*		createPI() const;
    IlXmlCDataI*	createCData() const;
};

// --------------------------------------------------------------------------
// Interface for documents
// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlDocumentI
{
public:
    virtual ~IlXmlDocumentI();
    // ____________________________________________________________
    virtual void	addNode(IlXmlNodeI* node) = 0;
    virtual void	startElement(IlXmlElementI* element);
    virtual void	attributeAdded(IlXmlElementI*   element,
				       IlXmlAttributeI* attribute);
    virtual void	endElement(IlXmlElementI* element);
    virtual void	textAdded(IlXmlTextI* text);
    virtual void	commentAdded(IlXmlCommentI* comment);
    virtual void	charRefAdded(IlXmlCharRefI* charRef);
    virtual void	processingInstructionAdded(IlXmlPII* pi);
    virtual void	cDataAdded(IlXmlCDataI* cdata);
    virtual IlXmlAttributeI*	createAttribute(IlXmlElementI* element,
						char*          name,
						char*          value) const;
    virtual IlXmlElementI*	createElement(char* tag) const;
    virtual IlXmlTextI*		createText() const;
    virtual IlXmlCommentI*	createComment() const;
    virtual IlXmlCharRefI*	createCharRef() const;
    virtual IlXmlPII*		createPI() const;
    virtual IlXmlCDataI*	createCData() const;
    virtual IlXmlNodeFactory*	getNodeFactory() const;
    virtual const char*	getVersion() const;
    virtual const char*	getDoctypeName() const;
    virtual const char*	getDoctypeRest() const;
    virtual void	empty();
    void		read(IL_STDPREF istream& stream);
    virtual IL_STDPREF ostream&	write(IL_STDPREF ostream& stream) const;
    virtual void	writeNodes(IL_STDPREF ostream& stream) const;
    virtual IlXmlNodeIteratorI*	createNodesIterator() const;

protected:
    virtual void	storeVersion(char* version);
    virtual void	storeDoctype(char* name, char* rest);

    friend class	IlXmlParser;
};

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlXmlDocument : public IlXmlDocumentI
{
public:
    IlXmlDocument();
    virtual ~IlXmlDocument();
    // ____________________________________________________________
    IlListOf(IlXmlNodeI)& getNodes() const;
    IlXmlElement*		getRootElement() const;
    virtual void		addNode(IlXmlNodeI*);
    virtual const char*		getVersion() const;
    virtual const char*		getDoctypeName() const;
    virtual const char*		getDoctypeRest() const;
    virtual void		empty();
    virtual IlXmlNodeIteratorI*	createNodesIterator() const;

protected:
    virtual void		storeVersion(char* version);
    virtual void		storeDoctype(char* name, char* rest);

private:
    IlListOf(IlXmlNodeI)	_nodes;
    char*			_version;
    char*			_doctypeName;
    char*			_doctypeRest;
};

#endif /* !__Il_Xml_H */
