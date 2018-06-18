// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/html.h
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
// Declaration of the IlvATHtmlReader class (HTML file format reader)
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Html_H
#define __Ilv_Annotext_Html_H

#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#  include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Graphics_Arc_H)
#  include <ilviews/graphics/arc.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#  include <ilviews/graphics/rectangl.h>
#endif
#if !defined(__Ilv_Graphics_Icon_H)
#  include <ilviews/graphics/icon.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#  include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Passwded_H)
#  include <ilviews/gadgets/passwded.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#  include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#  include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Annotext_Annotext_H)
#  include <ilviews/annotext/annotext.h>
#endif
#if !defined(__Ilv_Annotext_Zone_H)
#  include <ilviews/annotext/zone.h>
#endif

// --------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------
#define ILVATHISTORYSIZE   64
#define ILVATREFSIZE      255
#define ILVATTITLESIZE    255

// --------------------------------------------------------------------------
// Forward references
// --------------------------------------------------------------------------
// For compatibility reasons
#define IlvAnnoTextHTMLReader IlvATHtmlReader

class ILVATEXPORTED IlvAnnoText;
class ILVATEXPORTED IlvATPalette;
class ILVATEXPORTED IlvATZone;
class ILVATEXPORTED IlvATHtmlLinkInteractor;
class ILVATEXPORTED IlvATHtmlCommandInteractor;
class ILVATEXPORTED IlvATHtmlReader;

// --------------------------------------------------------------------------
// Typedef
// --------------------------------------------------------------------------
typedef enum IlvATHtmlInteractorType {
    IlvATHtmlInteractorNone,
    IlvATHtmlInteractorLink,
    IlvATHtmlInteractorCommand
} IlvATHtmlInteractorType;

// --------------------------------------------------------------------------
// Class IlvATHtmlStackElement
//   Instances are elements of the trace back/forward stack of the HTML 
//   reader
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlStackElement
{
public:
    IlvATHtmlStackElement(const char* tag, IlvATZone* zone);
    ~IlvATHtmlStackElement();
    // ____________________________________________________________
    inline IlvATZone*		getZone() const		{ return _zone; }
    inline const char*		getTag() const		{ return _tag;  }
    inline
    IlvATHtmlStackElement*	getNext() const		{ return _next; }
    inline void			setNext(IlvATHtmlStackElement* n)
	{ _next = n; }
    inline 
    IlvATHtmlStackElement*	getPrevious()       const
	{ return _previous; }
    inline void			setPrevious(IlvATHtmlStackElement* p)
	{ _previous = p;    }
private:
    IlvATZone*			_zone;
    char*			_tag;
    IlvATHtmlStackElement*	_next;
    IlvATHtmlStackElement*	_previous;
};

// --------------------------------------------------------------------------
// Class IlvHtmlText
//     An instance is an annotated text container with HTML read capability.
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlText
: public IlvAnnoText {
public:
    IlvATHtmlText(IlvDisplay*		display,
		  const IlvRect&	rect,
		  IlvATPalette*		tpalette,
		  IlUShort		thcknss = IlvDefaultGadgetThickness);
    ~IlvATHtmlText();
    // ____________________________________________________________
    IlvATHtmlReader*	getReader() const { return _reader; }
    void		setReader(IlvATHtmlReader* reader)
			{
			    _reader = reader;
			}
    void		setCurrentPath(const IlPathName& p)
			{
			    _currentPath = p;
			}
    void		setCurrentPath(const char* p)
			{
			    _currentPath.setValue(p);
			}
    virtual IlPathName&	getCurrentPath() { return _currentPath; }

    DeclareTypeInfo();
    DeclareIOConstructors(IlvATHtmlText);

    // for delayed bitmap reading
    void		setDelayedBitmaps(IlBoolean db = IlTrue)
			{
			    _delayedBitmaps = db;
			}
    IlBoolean		getDelayedBitmaps() const { return _delayedBitmaps; }

    void		addToProxyList(IlvATGraphicRope* rope);
    IlUShort		getNumberOfProxies() const { return _nProxy; }
    void		setNumberOfProxies(IlUShort nb) { _nProxy = nb; }
    IlvATGraphicRope*	getProxy(IlUShort i) const { return _proxyList[i]; }
protected:
    IlvATHtmlReader*	_reader;
    IlPathName		_currentPath;
    IlvATGraphicRope**	_proxyList;
    IlUShort		_nProxy;
    IlUShort		_nMaxProxy;
    IlBoolean		_delayedBitmaps;
};

// --------------------------------------------------------------------------
// Class IlvATHtmlProxyInfo
//  Instances are the contents of stack element
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlProxyInfo
{
public:
    IlvATHtmlProxyInfo(const char* path, IlBoolean transparent)
    : _path(IlCopyString(path)),
      _transparent(transparent)
      {}
    ~IlvATHtmlProxyInfo()
	{ if (_path) { delete [] _path; } }
    // ____________________________________________________________
    const char*		getPath() const		{ return _path;        }
    IlBoolean		isTranparent() const	{ return _transparent; }
private:
    char*		_path;
    IlBoolean		_transparent;
};

// --------------------------------------------------------------------------
// Class IlvATHtmlReader
//    Provide the HTML handling (read and follow links) capability
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlReader
{
public:
    IlvATHtmlReader(IlvDisplay* display);
    virtual ~IlvATHtmlReader();

    virtual IlBoolean	read(IlvATHtmlText*,
			     ILVSTDPREF istream&,
			     IlBoolean html = IlTrue);
    virtual IlvATHtmlLinkInteractor*	createLinkInteractor() const;
    virtual IlvATHtmlCommandInteractor*	createCommandInteractor() const;
    virtual IlBoolean	parseTag(IlvATHtmlText*,
				 char*,
				 IlvATCursor*,
				 ILVSTDPREF istream&);

    IlBoolean		readStyles(const char* stylesPathname);
    IlBoolean		readBitmapFile(IlvATHtmlText*,
				       IlPathName& );
    IlvATPalette*	getDefaultStyle();
    IlvATPalette*	getStyle(const char* style);
    int			getStyleIndex(const char* style);

    IlBoolean		getTag(IlvATHtmlText*,
			       char*,
			       IlvATCursor*,
			       ILVSTDPREF istream&);
    void		addAnchor(const char* styleName,
				  IlvATCursor*);
    IlvATCursor*	getAnchorCursor(const char * anchorName) const;
    void		removeAnchors();
    void		resetListNumbering();
    IlBoolean		parsePath(char* path,
				  IlUShort& anchor);
    void		getPathNameFromAddress(IlvATHtmlText* text,
					       const char*    address,
					       IlPathName&    path);
    void		setRootDir(const char* path);
    IlPathName&		getRootDir()		{ return _rootDir;         }
    const char*		getTitle() const	{ return _title;           }
    IlBoolean		isTrueNewLines() const	{ return _trueNewLines;    }
    void		setTrueNewLines(IlBoolean nl) { _trueNewLines = nl; }
    IlBoolean		isVerbose() const	{ return _verbose;         }
    void		setVerbose(IlBoolean v)	{ _verbose = v;            }
    // to maintain the stack of tags opened and not yet closed
    void		insertTag(IlvATHtmlStackElement*  tag);
    void		extractTag(IlvATHtmlStackElement* tag);
    IlvATHtmlStackElement*	getFirstTag() const { return _firstTag;     }

    IlvATHtmlLinkInteractor*	getLinkInteractor();
    IlvATHtmlCommandInteractor*	getCommandInteractor();
    void		setServerAddress(char* sa) { _serverAddress = sa; }
    char*		getServerAddress() const { return _serverAddress; }
    IlPathName&		getHome()		 { return _home;          }
    char*		getDefaultFileName() const
	{ return _defaultFileName; }
    void		setDefaultFileName(char* f) { _defaultFileName = f; }
    //  for delayed bitmap reading
    void		makeProxyImageFromAddress(IlvAnnoText* text,
						  IlvATCursor* insert,
						  char* valueStart,
						  IlBoolean transparent);
    void		getRealImages(IlvATHtmlText* text);
protected:
    // Not documented
    IlvDisplay*		getDisplay() const	{ return _display; }
    void		readStyle(ILVSTDPREF istream&);
    void		addStyle(const char* styleName,
				 IlvATPalette*,
				 IlvATHtmlInteractorType interactor);
    IlBoolean		processTag(IlvATHtmlText*,
				   ILVSTDPREF istream&,
				   IlvATCursor*);
    IlBoolean		processSpecialChar(IlvATHtmlText*,
					   ILVSTDPREF   istream&,
					   IlvATCursor* insert);
    IlBoolean		getSpecialChar(ILVSTDPREF istream&,
				       char&);
    int			findAttribute(char* buff,
				      int lbuff,
				      const char* str);
    IlBoolean		getValue(char*		buff,
				 int&		start,
				 int&		end,
				 const char*	attName = 0);
    IlBoolean		getAttributeValue(char*		tag,
					  int		lbuff,
					  const char*	attName,
					  char*&	valStart,
					  int&		len);
    IlBoolean		readImage(IlvATHtmlText*,
				  IlvATCursor* insert,
				  IlPathName& bitmapPath,
				  IlBoolean = IlTrue);
    IlBoolean		readImageFromAddress(IlvATHtmlText*,
					     IlvATCursor* insert,
					     const char*  filename,
					     IlBoolean = IlTrue);
    void		readGadget(IlvATHtmlText*, IlvATCursor*, char* tag);
    IlUShort		getListDepth() const { return _listDepth;           }
    void		incListDepth()       { _listDepth++;                }
    void		decListDepth()       { if (_listDepth) _listDepth--;}
    IlBoolean		isNumbered (IlUShort i) const ;
    void		ensureListStyle(IlvATHtmlText* text,
					const char*    stylename);
    char*		ensureSpecialStyle(IlvATHtmlText*	text,
					   IlvATPalette*	tpal,
					   char			mark,
					   IlvFontStyle		fontstyle);
    char*		ensureSpecialAlignmentStyle(IlvATHtmlText* text,
						    IlvATPalette*  tpal,
						    char           mark,
						    IlvATAlignment align);
    IlUShort		getStyleIndex(IlvATHtmlText*	text,
				      const char*	stylename);
    void		manageZoneWithStyle(IlvATHtmlText*	text,
					    const char*		stylename,
					    const char*		tag,
					    IlvATCursor*	insert,
					    IlBoolean		close);
    IlvATZone*		makeZoneWithStyle(IlvATHtmlText*	text,
					  const char*		stylename,
					  IlvATCursor*		insert);
    void		setNumbered(IlUShort i, IlBoolean numb);
    IlUShort		incItemNumber(IlUShort i);
    IlBoolean		hasAttribute() const { return _attribute; }
    IlBoolean		streamCompare(const char*		tag,
				      char*			buff,
				      ILVSTDPREF istream&	stream,
				      IlUShort&			off);
    void			ignoreUntil(char*		tag,
					    ILVSTDPREF istream&	stream);
    IlvGraphic*		getBullet() const;
    IlvGraphic*		getProxyImage() const { return _proxy; }
private:
    IlvDisplay*		_display;
    IlUShort		_nStyles;
    char**		_styleNames;
    IlvATPalette**	_styles;
    IlUShort		_listDepth;
    IlUShort		_numbered : 16;
    IlUShort		_itemNumber[16];
    IlBoolean		_attribute;
    IlUShort		_nAnchors;
    IlUShort		_nAnchorsMax;
    char**		_anchorNames;
    IlvATCursor**	_anchors;
    char		_title[ILVATTITLESIZE];
    IlvDim		_tabulationSpacing;
    IlvATHtmlLinkInteractor*	_linkInteractor;
    IlvATHtmlCommandInteractor*	_commandInteractor;
    char*		_serverAddress;
    char*		_defaultFileName;
    IlPathName		_rootDir;
    // stack of tags opened and not yet closed
    IlvATHtmlStackElement*	_firstTag;
    IlBoolean		_trueNewLines;
    IlBoolean		_verbose;
    // Bitmaps for list bullets
    IlvGraphic*		_bullet1;
    IlvGraphic*		_bullet2;
    IlvGraphic*		_bullet3;
    IlvGraphic*		_proxy;
    IlPathName		_home;
};

// --------------------------------------------------------------------------
// Class IlvATHtmlLinkInteractor
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlLinkInteractor
: public IlvATInteractor {
public:
    virtual IlBoolean	handleEvent	(IlvATZone* zone,
					 IlvEvent& event);
    virtual void	followLink	(IlvATHtmlText*,
					 const char* linkPathName);
};

// --------------------------------------------------------------------------
// Class IlvATHtmlCommandInteractor
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlCommandInteractor
: public IlvATInteractor {
public:
    virtual IlBoolean	handleEvent	(IlvATZone* zone,
					 IlvEvent& event);
    virtual void	executeCommand	(IlvATHtmlText*,
					 const char* linkPathName);
};

// --------------------------------------------------------------------------
// Class IlvATHtmlHistory
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATHtmlHistory
{
public:
    IlvATHtmlHistory(const IlPathName& ref);
    // ____________________________________________________________
    void		addPage(const IlPathName& ref);
    IlBoolean		back();
    IlBoolean		forward();
    IlPathName&		getRef() { return _ref[_current]; }
private:
    IlPathName		_ref[ILVATHISTORYSIZE];
    int			_top;
    int			_bottom;
    int			_current;
};

ILVATMODULEINIT(html);

#endif /* !__Ilv_Annotext_Html_H */
