// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/stream.h
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
// Declaration of the IlvDvStream class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Stream_H)
#define __Ilv_Appframe_Stream_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

class IlvDvDynClassInfo;
class IlvBitmap;
class IlvDvStringArray;

// --------------------------------------------------------------------------
// IlvDvStream class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvStream
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvStream(ILVSTDPREF ostream& os);
    IlvDvStream(ILVSTDPREF istream& is);
    virtual ~IlvDvStream();

    // ----------------------------------------------------------------------
    // Main operations
    virtual void		close();

    // Storing operators
    IlvDvStream& operator	<<(IlInt i);

    IlvDvStream& operator	<<(IlUShort w);

    IlvDvStream&operator	<<(IlShort ch);

    IlvDvStream& operator	<<(IlUInt u);

#if !((defined(__alpha) && !defined(WIN32)) || \
      (defined(__hpux) && defined(__LP64__)) || \
      defined(__sparcv9) || \
      (defined(__sun) && defined(__x86_64__)) || \
      (defined(_AIX) && defined(__64BIT__)))
    IlvDvStream& operator	<<(IlBoolean b);
#endif /* ! (alphaosf || hp64 || ultrasparc64 || x64solaris || AIX_64) */

    IlvDvStream& operator	<<(IlFloat f);

    IlvDvStream& operator	<<(IlDouble d);

    IlvDvStream& operator	<<(const IlvString& s);
			// String do not contains whites

    inline
    IlvDvStream& operator	<<(const char* s)
				{
				    IlString t(s); return *this << t;
				}

    // Reading operators
    IlvDvStream& operator	>>(IlInt& i);

    IlvDvStream& operator	>>(IlUShort& w);

    IlvDvStream& operator	>>(IlShort& ch);

    IlvDvStream& operator	>>(IlUInt& u);

#if !((defined(__alpha) && !defined(WIN32)) || \
      (defined(__hpux) && defined(__LP64__)) || \
      defined(__sparcv9) || \
      (defined(__sun) && defined(__x86_64__)) || \
      (defined(_AIX) && defined(__64BIT__)))
    IlvDvStream& operator	>>(IlBoolean& b);
#endif /* ! (alphaosf || hp64 || ultrasparc64 || x64solaris || AIX_64) */

    IlvDvStream& operator	>>(IlFloat& f);

    IlvDvStream& operator	>>(IlDouble& d);

    IlvDvStream& operator	>>(IlvString& s);

    inline void		serialize(IlvString& s,
				  IlBoolean  betweenQuotes = IlTrue)
			{
			    if (_saving) {
				if (betweenQuotes)
				    s.writeQuoted(*_stream._out);
				else
				    (*this) << s;
			    }
			    else {
				if (betweenQuotes)
				    s.readQuoted(*_stream._in);
				else
				    (*this) >> s;
			    }
			}

    void		serialize(const IlSymbol*& s,
				  IlBoolean betweenQuotes = IlTrue);

    void		serializeBitmap(IlvBitmap*& b,
					IlBoolean   lock = IlTrue);

    void		serializeObjects(IlvArray& objs);

    void		writeObject(const IlvDvSerializable* o);

    IlvDvSerializable*	readObject();
    void		writeDynClassInfo(const IlvDvDynClassInfo* classInfo);
    IlvDvDynClassInfo*	readDynClassInfo();

    unsigned long	readBlock(char*, unsigned long size);
    void		writeBlock(const char*, unsigned long size);
    // ----------------------------------------------------------------------
    // Basic properties
    inline IlBoolean	isSaving() const { return _saving; }
    virtual IlBoolean	operator !() const;
    virtual IlvDisplay* getDisplay() const;
    inline
    ILVSTDPREF istream*	getInStream() const
			{
			    return _saving? 0 : _stream._in;
			}

    inline
    ILVSTDPREF ostream*	getOutStream() const
			{
			    return _saving? _stream._out : 0;
			}

protected:
    IlBoolean		_saving;
    IlvString		_BlanckString; // Do not now how to make it static

    union {
	ILVSTDPREF ostream* _out;
	ILVSTDPREF istream* _in;
    } _stream;

    IlvDvStream();
    void		setIStream(ILVSTDPREF istream&);
    void		setOStream(ILVSTDPREF ostream&);
};

// --------------------------------------------------------------------------
// IlvDvTextStream class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvTextStream : public IlvDvStream
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTextStream(ILVSTDPREF ostream& os);
    IlvDvTextStream(ILVSTDPREF istream& is);
    IlvDvTextStream(const char* pathname, IlBoolean saving);
    IlvDvTextStream(const IlvDvStream& stream);
    virtual ~IlvDvTextStream();

    // ----------------------------------------------------------------------
    // Main operation
    void		skipWhites();
    IlBoolean		skipSeparator(const char*);
    IlBoolean		eof() const;
    IlBoolean		readToken(IlvString&, const char* separators = 0);
    IlBoolean		isSeparator(int c) const;

    void		incTabulation(IlBoolean bNewLine = IlFalse);
    void		decTabulation(IlBoolean bNewLine = IlFalse);
    inline int		getTabulation() const { return _tabs; }
    inline void		setTabulation(int tabs) { _tabs = tabs; }
    void		newLine();
    void		readLine(IlvString&);
    IlBoolean		goTo(const char*, IlvString* buf = 0);
    IlUInt		goToFirstKey(const IlvDvStringArray& keys,
				     IlvString*              buf = 0);
    static const char*	Separators;

protected:
    int			_tabs;
    IlBoolean		_isOpenFile;
};

// --------------------------------------------------------------------------
// IlvDvFileStream class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvFileStream : public IlvDvStream
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvFileStream(const IlvPathName& pathName,
		    IlBoolean          saving,
		    IlvDisplay*        display = 0);
    virtual ~IlvDvFileStream();

    // ----------------------------------------------------------------------
    virtual void		close();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvDisplay*		getDisplay() const;
    virtual IlBoolean		isEmpty() const;
    virtual unsigned long	getLength() const;
    virtual IlvPathName		getPathName() const;

protected:
    IlvPathName			_pathName;
    IlvDisplay*			_display;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(stream);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Stream_H */
