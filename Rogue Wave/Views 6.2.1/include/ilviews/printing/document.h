// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/document.h
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
// Definition of IlvPrintableDocument class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Document_H
#define __Ilv_Printing_Document_H

#if !defined(__Ilv_Printing_Macros_H)
#  include <ilviews/printing/macros.h>
#endif

// --------------------------------------------------------------------------
// Forward declarations.
class IlvPrinter;
class IlvPrintable;
class IlvPrintableLayout;
class IlvPrintableDocumentList;
class IlvPrintableDocumentListIterator;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableDocument
{
public:
    class ILVPRINTINGEXPORTED Iterator
    {
	friend class IlvPrintableDocument;

    public:
	Iterator(Iterator const& other);
	~Iterator();

	Iterator& operator	=(Iterator const& other);

	IlBoolean operator	==(Iterator const& other) const;
	inline
	IlBoolean operator	!=(Iterator const& other) const
				{
				    return (*this == other) ? IlFalse : IlTrue;
				}

	Iterator& operator	++();
	Iterator operator	++(int);

	IlvPrintable*		getPrintable() const;
	IlvPrintableLayout*	getPrintableLayout() const;

    private:
	Iterator(IlvPrintableDocumentListIterator const&);
	IlvPrintableDocumentListIterator* getInternal() const;

	IlvPrintableDocumentListIterator* _internal;
    };
    friend class Iterator;

    class ILVPRINTINGEXPORTED ThresholdHook
    {
    public:
	virtual ~ThresholdHook();
	virtual IlBoolean	checks(int pageNumber) const = 0;
    };

    enum PrintingMode {
	WholeDocument,
	Page
    };
    IlvPrintableDocument(IlvPrintableLayout*	layout,
			 PrintingMode		mode = WholeDocument);
    ~IlvPrintableDocument();

    inline
    IlvPrintableLayout*	getDefaultLayout() const { return _defaultLayout; }

    inline PrintingMode getPrintingMode() const { return _mode; }

    inline
    void		setPrintingMode(PrintingMode mode) { _mode = mode; }

    inline Iterator	insert(IlvPrintable* printable, Iterator const& iter)
			{
			    return insert(iter, printable, getDefaultLayout());
			}
    inline Iterator	insert(IlvPrintable* printable,
			       IlvPrintableLayout* layout,
			       Iterator const& iter)
			{
			    return insert(iter,
					  printable,
					  layout ? layout : getDefaultLayout());
			}
    inline Iterator	append(IlvPrintable* printable)
			{
			    return insert(end(),
					  printable,
					  getDefaultLayout());
			}
    inline Iterator	append(IlvPrintable* 	 printable,
			       IlvPrintableLayout* layout)
			{
			    return insert(end(),
					  printable,
					  layout ? layout : getDefaultLayout());
			}

    Iterator		begin() const;
    Iterator		end() const;

    IlBoolean		print(IlvPrinter& printer,
			      Iterator const& first,
			      Iterator const& last,
			      int copyNumber = 1,
			      IlBoolean useAbsolutePageIndex = IlTrue) const;
    IlBoolean		print(IlvPrinter& printer,
			      int first = 0,
			      int last = -1,
			      int copyNumber = 1,
			      IlBoolean useAbsolutePageIndex = IlTrue) const;
    inline void		setThresholdHook(ThresholdHook* newThresholdHook)
			{
			    _thresholdHook = newThresholdHook;
			}

private:
    // Intentionally not defined.
    IlvPrintableDocument(IlvPrintableDocument const& other);

    // Intentionally not defined.
    IlvPrintableDocument& operator=(IlvPrintableDocument const& other);
    Iterator		insert(Iterator const&	iter,
			       IlvPrintable*	printable,
			       IlvPrintableLayout*	layout);

    IlvPrintableDocumentList*	_list;
    IlvPrintableLayout*		_defaultLayout;
    PrintingMode		_mode;
    ThresholdHook*		_thresholdHook;
};

#endif /* __Ilv_Printing_Document_H */
