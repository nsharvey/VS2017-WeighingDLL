// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/message.h
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
// Declaration of the message data bases-related class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Message_H
#define __Ilv_Base_Message_H

#if !defined(__Ilv_Base_List_H)
#  include <ilviews/base/list.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Base_Locale_H)
#  include <ilviews/base/locale.h>
#endif

class IlvDisplay;
class IlvDBMessage;
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvMessageDatabase
{
public:
    IlvMessageDatabase() : _messages(11), _languages(), _paths() {}
    virtual ~IlvMessageDatabase();

    virtual void	clean();
    IlvDBMessage*	find(const char* message) const;
    virtual IlBoolean	read(ILVSTDPREF istream& istr,
			     const IlvDisplay*   display = 0,
			     const char*         fName   = 0);
    virtual void	write(ILVSTDPREF ostream& ostr,
			      const IlSymbol* language = 0,
			      IlEncoding      encoding = IlNoEncoding) const;
    void		write(const char*     filename,
			      const IlSymbol* language = 0,
			      IlEncoding      encoding = IlNoEncoding) const;
    IlBoolean		read(const char*       filename,
			     const IlvDisplay* display = 0,
			     const char*       fName = 0);
    virtual
    IlvDBMessage*	makeMessage(const char* msgid);
    virtual IlBoolean	removeMessage(const char* msgid);
    void		putMessage(const char* msgid,
				   IlSymbol*   language,
				   const char* value,
				   IlBoolean   copy = IlTrue);
    const char*		getMessage(const char*     msgid,
				   const IlSymbol* language) const;
    virtual void	remove(IlSymbol* language);
    inline
    IlStringHashTable*	getHashTable() { return &_messages; }
    void		add(IlvMessageDatabase* db);
    IlBoolean		addLanguage(const IlSymbol*);
    IlBoolean		hasLanguage(const IlSymbol*) const;
    const IlSymbol**	getLanguages(IlUInt&) const;
    IlUInt		getLanguageCardinal() const;
    inline
    const IlList*	getLanguages() const { return &_languages; }
    inline
    const IlList*	getPaths() const { return &_paths;     }

protected:
    IlStringHashTable	_messages;
    IlList		_languages;
    IlList		_paths;
    void		writeHeader(ILVSTDPREF ostream&,
				    const IlSymbol* language,
				    IlEncoding encoding) const;
    IlBoolean		readHeader(ILVSTDPREF istream&,
				   const IlvDisplay*,
				   const char*);
    void		writeMessage(ILVSTDPREF ostream& stream,
				     const char* message) const;
    IlBoolean		readMessage(ILVSTDPREF istream& stream,
				    const char* message);
};

#endif /* !__Ilv_Base_Message_H */
