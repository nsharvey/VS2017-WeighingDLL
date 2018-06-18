// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/look.h
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
// Declaration of the IlvLookFeelHandler classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Look_H
#define __Ilv_Base_Look_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif

#if !defined(WINDOWS)
#  define COLOR_SCROLLBAR		0
#  define COLOR_BACKGROUND		1 // unused
#  define COLOR_ACTIVECAPTION		2
#  define COLOR_INACTIVECAPTION		3
#  define COLOR_MENU			4
#  define COLOR_WINDOW			5
#  define COLOR_WINDOWFRAME		6
#  define COLOR_MENUTEXT		7
#  define COLOR_WINDOWTEXT		8
#  define COLOR_CAPTIONTEXT		9
#  define COLOR_ACTIVEBORDER		10 // unused
#  define COLOR_INACTIVEBORDER		11 // unused
#  define COLOR_APPWORKSPACE		12 // unused
#  define COLOR_HIGHLIGHT		13
#  define COLOR_HIGHLIGHTTEXT		14
#  define COLOR_BTNFACE			15
#  define COLOR_BTNSHADOW		16
#  define COLOR_GRAYTEXT		17
#  define COLOR_BTNTEXT			18
#  define COLOR_INACTIVECAPTIONTEXT	19
#  define COLOR_BTNHIGHLIGHT		20
#  define COLOR_3DDKSHADOW		21
#  define COLOR_3DLIGHT			22
#  define COLOR_INFOTEXT		23
#  define COLOR_INFOBK			24
#else  /* WINDOWS */
// For versions previous to MSVC4.0.
#  if !defined(COLOR_3DDKSHADOW)
#    define COLOR_3DDKSHADOW		21
#  endif
#  if !defined(COLOR_3DLIGHT)
#    define COLOR_3DLIGHT		22
#  endif
#  if !defined(COLOR_INFOTEXT)
#    define COLOR_INFOTEXT		23
#  endif
#  if !defined(COLOR_INFOBK)
#    define COLOR_INFOBK    		24
#  endif
#endif /* WINDOWS */
#define COLOR_GADGETCNT			1024

#define FONT_BUTTON  			0
#define FONT_MENU    			1
#define FONT_TOOLTIP 			2
#define FONT_CAPTION 			3
#define FONT_INACTIVECAPTION 		4

#define BITMAP_INFO 			0
#define BITMAP_QUESTION 		1
#define BITMAP_ERROR 			2
#define BITMAP_WARNING 			3
#define BITMAP_MDIMIN 			4
#define BITMAP_MDIMAX 			5
#define BITMAP_MDIRST 			6
#define BITMAP_MDICLOSE 		7
#define BITMAP_MDITITLE 		8
#define BITMAP_SMALLCLOSE 		9
#define BITMAP_GADGETCNT 		10

#define PALETTE_TOOLTIP			0
#define PALETTE_CAPTION			1
#define PALETTE_INACTIVECAPTION		2

class IlvBidiInterface;
class IlvLookFeelHandler;
class IlvObjectLFHandler;
class IlvObjectLFClassInfo;

// --------------------------------------------------------------------------
typedef void (*IlvBackgroundPainter)(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*,
				     IlAny);

// --------------------------------------------------------------------------
typedef IlvLookFeelHandler* (*IlvLookFeelConstructor)(IlvDisplay*);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvLookFeelClassInfo
    : public IlvPropClassInfo
{
public:
    virtual ~IlvLookFeelClassInfo();

    inline IlSymbol*		  getLookName() const
	{ return _lookName; }
    inline IlvLookFeelClassInfo*  getLookFeelSuperClass() const
	{ return IL_CAST(IlvLookFeelClassInfo*, getSuperClass()); }
    inline IlvLookFeelConstructor getConstructor() const
	{ return _constructor; }
    inline static IlvLookFeelClassInfo*	GetFirst()
	{ return _first; }
    inline IlvLookFeelClassInfo*	getNext() const
	{ return _next; }
    static IlvLookFeelClassInfo*	Create(const char*,
					       IlvClassInfo**,
					       IlvLookFeelConstructor,
					       IlSymbol* = 0);
    static IlvLookFeelHandler*		Create(IlSymbol*,
					       IlvDisplay*);

protected:
    IlvLookFeelClassInfo(const char*, IlvClassInfo**,
			 IlvLookFeelConstructor, IlSymbol*);

    IlvLookFeelConstructor		_constructor;
    IlSymbol*				_lookName;
    IlvLookFeelClassInfo*		_next;
    static IlvLookFeelClassInfo*	_first;
    static void				Chain(IlvLookFeelClassInfo*);
    static void				UnChain(IlvLookFeelClassInfo*);
};

#define IlvPredefinedLookFeelMembers(classname, lookname)		\
IlvLookFeelHandler* classname::Create(IlvDisplay* display)		\
{classname* lf = new classname(display); lf->initialize(); return lf;}	\
IlSymbol* classname::GetLookName() { return IlGetSymbol(lookname); }	\
const char* classname::getLookName() const { return GetLookName()->name(); }


#define IlvRegisterLookFeelClass(classname, superclass)			\
ILVDEFINECLASSINFOMEMBERS(classname,					\
IlvLookFeelClassInfo::Create(#classname,				\
			     superclass::ClassPtr(),			\
			     (IlvLookFeelConstructor)classname::Create,	\
			     classname::GetLookName()))

#define IlvPreRegisterLookFeelClass(classname)	\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvPostRegisterLookFeelClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
IlvLookFeelClassInfo::Create(#classname,				\
			     superclass::ClassPtr(),			\
			     (IlvLookFeelConstructor)classname::Create,	\
			     classname::GetLookName()))


#define DeclareLookFeelTypeInfo_()			\
static IlvLookFeelClassInfo* LookFeelClassInfo()	\
{ return IL_CAST(IlvLookFeelClassInfo*, ClassInfo()); }	\
static IlvLookFeelHandler* Create(IlvDisplay*);		\
static IlSymbol* GetLookName();				\
virtual const char* getLookName() const;

#define DeclareLookFeelTypeInfo()					\
	DeclareLookFeelTypeInfo_()					\
	IlvDeclarePropClassInfo()

#define DeclareLazyLookFeelTypeInfo()					\
	DeclareLookFeelTypeInfo_()					\
	IlvDeclareLazyPropClassInfo()

// --------------------------------------------------------------------------
typedef IlvObjectLFHandler* (* IlvCreateObjectLFH)(IlvLookFeelHandler*);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvObjectLFClassInfo
    : public IlvClassInfo
{
public:
    static
    IlvObjectLFClassInfo*	Create(const char*,
				       IlvLookFeelClassInfo*,
				       IlvClassInfo*,
				       IlvCreateObjectLFH);
    IlvObjectLFHandler*		create(const IlvLookFeelHandler*) const;
    virtual void		classInfoDeleted();
    static
    IlvObjectLFClassInfo*	Get(const IlvLookFeelClassInfo*,
				    const IlvClassInfo*);

protected:
    IlvObjectLFClassInfo(const char*,
			 IlvLookFeelClassInfo*,
			 IlvClassInfo*,
			 IlvCreateObjectLFH);
    virtual ~IlvObjectLFClassInfo();

private:
    IlvLookFeelClassInfo* 	_look;
    IlvCreateObjectLFH   	_constructor;
    IlvClassInfo*      		_classInfo;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvLookFeelHandler
{
    friend class IlvDisplay;
public:
    // ____________________________________________________________
    inline IlvDisplay*	getDisplay()	 const { return _display; }

    // Object L&F Handler management
    IlvObjectLFHandler*	getObjectLFHandler(const IlvClassInfo* ci) const;
    void		addObjectLFHandler(IlvObjectLFHandler* olfh);
    void		removeObjectLFHandler(const IlvClassInfo* classinfo);
    void		removeObjectLFHandler(IlvObjectLFHandler*);
    void		removeObjectLFHandlers();

    // Resources management
    const char*		getColorResourceName(int) const;
    const char*		getFontResourceName(int) const;
    const char*		getBitmapResourceName(int) const;
    const char*		getPaletteResourceName(int) const;
    virtual IlvColor*	getColorResource(int) const;
    virtual IlvFont*	getFontResource(int) const;
    virtual IlvBitmap*	getBitmapResource(int) const;
    virtual IlvPalette*	getPaletteResource(int) const;
    IlvColor*		getColor(int) const;
    IlvFont*		getFont(int) const;
    IlvBitmap*		getBitmap(int) const;
    IlvPalette*		getPalette(int) const;
    void		setColor(int, IlvColor*);
    void		setFont(int, IlvFont*);
    void		setBitmap(int, IlvBitmap*);
    void		setPalette(int, IlvPalette*);
    virtual void	reset();

    // Static Methods
    static const IlSymbol* const* GetDynamicLooks(IlUInt& count,
						  IlBoolean sort = IlTrue);
    static const IlSymbol* const* GetAvailableLooks(IlUInt& count,
						    IlBoolean sort = IlTrue);

    static const IlSymbol* const* GetRegisteredLooks(IlUInt& count,
						     IlBoolean sort =IlTrue);
    static IlvLookFeelHandler*	Create(IlSymbol* lookname,
				       IlvDisplay* display);
    static
    IlvLookFeelHandler*	GetDefaultLookFeelHandler(IlvDisplay* display,
						  IlBoolean   warn = IlTrue);
    static IlSymbol*	GetDefaultLookFeelName();
    virtual IlvObjectLFHandler*
			createObjectLFHandler(const IlvClassInfo* ci) const;
    static IlvObjectLFClassInfo*
			RegisterObjectLFHandler(IlvLookFeelClassInfo*,
						IlvClassInfo*,
						IlvCreateObjectLFH);

    // For compatibility...
    virtual IlvFont*	getButtonFont() const;
    virtual IlvFont*	getMenuFont() const;
    virtual IlvPalette*	getToolTipPalette() const;
    virtual IlvColor*	getGadgetContainerBackground() const;
    virtual IlvBitmap*	getGadgetContainerBackgroundBitmap() const;
    virtual IlvPalette*	getActiveCaptionPalette() const;
    virtual IlvPalette*	getInactiveCaptionPalette() const;

    // Misc
    virtual IlvBackgroundPainter getGadgetContainerBackgroundPainter() const;
    virtual IlBoolean 	hasSystemFileBrowser() const;

    // Need to be defined
    virtual const char*	getLookName() const = 0;
    virtual IlvColor*	getDefaultColor(int) const = 0;
    virtual IlvFont*	getDefaultFont(int) const = 0;
    virtual IlvBitmap*	getDefaultBitmap(int) const = 0;
    virtual IlvPalette*	getDefaultPalette(int) const = 0;
    virtual IlvDim	getMnemonicDescent(IlvFont*) const = 0;
    virtual void	drawSeparator(IlvPort*,
				      const IlvRect&,
				      IlvDirection,
				      const IlvPalette*,
				      const IlvPalette*,
				      const IlvRegion*) const = 0;
    virtual void	drawHighlight(IlvPort*,
				      const IlvRect&,
				      IlvPalette*,
				      const IlvRegion*,
				      IlBoolean) const = 0;
    virtual void	drawSelection(IlvPort*,
				      const IlvRect&,
				      IlvPalette*,
				      const IlvRegion*) const = 0;
    virtual void	computeLabelSize(const char*,
					 const IlvPalette*,
					 IlvDim&, IlvDim&,
					 IlvOrientation,
					 const IlvBidiInterface*) const = 0;
    virtual void	drawLabel(IlvPort*,
				  const char*,
				  const IlvRect&,
				  IlvPosition,
				  IlvOrientation,
				  IlBoolean,
				  IlvPalette*,
				  const IlvRegion*,
				  const IlvBidiInterface*) const = 0;
    virtual void	drawInsensitiveLabel(IlvPort*,
					     const char*,
					     const IlvRect&,
					     IlvPosition,
					     IlvOrientation,
					     IlBoolean,
					     IlvPalette*,
					     IlvPalette*,
					     const IlvRegion*,
					     const IlvBidiInterface*)const=0;
    void drawCarvedLabel(IlvPort*, const char*, IlvColor*, IlvColor*,
			 const IlvRect&, IlvPosition, IlvOrientation,
			 IlBoolean, IlvPalette*, const IlvRegion*,
			 const IlvBidiInterface*) const;

    virtual IlBoolean	selectTextToEnd() const = 0;
    virtual IlBoolean	autoSelectWhenFocused() const = 0;
    virtual IlBoolean	autoCopyToClipboardWhenSelected() const = 0;
    virtual IlBoolean	isAPasteFromClipboardEvent(const IlvEvent&) const=0;
    virtual IlBoolean	isACopyToClipboardEvent(const IlvEvent&) const = 0;
    virtual IlBoolean	isACutToClipboardEvent(const IlvEvent&) const = 0;
    virtual IlBoolean	showTextSelectionOnlyWhenFocused() const = 0;

    IlvDeclareLazyPropClassInfo();

protected:
    IlvDisplay*			_display;
    IL_MUTABLE IlHashTable	_objectLFHandlers;
    IL_MUTABLE IlHashTable	_colors;
    IL_MUTABLE IlHashTable	_fonts;
    IL_MUTABLE IlHashTable	_bitmaps;
    IL_MUTABLE IlHashTable	_palettes;

    // Constructor / Destructor
    IlvLookFeelHandler(IlvDisplay*);
    virtual ~IlvLookFeelHandler();

    // Initialization of resources
    virtual void	initialize() = 0;
    virtual void	releaseResources() = 0;

    // Cache for resources
    void		resetResourceCaches();
    IlvColor*		getCachedColor(int) const;
    IlvFont*		getCachedFont(int) const;
    IlvBitmap*		getCachedBitmap(int) const;
    IlvPalette*		getCachedPalette(int) const;
    void		setCachedColor(int, IlvColor*);
    void		setCachedFont(int, IlvFont*);
    void		setCachedBitmap(int, IlvBitmap*);
    void		setCachedPalette(int, IlvPalette*);
};

// --------------------------------------------------------------------------
inline IlvObjectLFClassInfo*
IlvAddLFObjectHandler(IlvClassInfo* classinfo,
		      IlvLookFeelClassInfo* look,
		      IlvCreateObjectLFH constructor)
{
    return IlvLookFeelHandler::RegisterObjectLFHandler(look,
						       classinfo,
						       constructor);
}

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvObjectLFHandler
{
public:
    IlvObjectLFHandler(IlvClassInfo* classInfo, IlvLookFeelHandler* lf)
        : _classInfo(classInfo),
	  _lfhandler(lf)
    {}
    virtual ~IlvObjectLFHandler();

    inline IlvClassInfo* getClassInfo() const
	{ return _classInfo; }
    inline
    IlvDisplay*		getDisplay()   const
	{ return _lfhandler ? _lfhandler->getDisplay() : 0; }
    inline IlvLookFeelHandler*	getLookFeelHandler() const
	{ return _lfhandler; }
    inline IlvLookFeelHandler*	getLFHandler() const
	{ return _lfhandler; }
    inline static IlvClassInfo** ClassPtr()
	{ return &_baseClassInfo; }
    static
    IlvClassInfo*	_baseClassInfo;

protected:
    IlvClassInfo*	_classInfo;
    IlvLookFeelHandler*	_lfhandler;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBasicLFHandler
    : public IlvLookFeelHandler
{
public:
    // ____________________________________________________________
    virtual IlvColor*	getDefaultColor(int) const;
    virtual IlvFont*	getDefaultFont(int) const;
    virtual IlvBitmap*	getDefaultBitmap(int) const;
    virtual IlvPalette*	getDefaultPalette(int) const;
    void		setMnemonicDescent(IlvDim);
    virtual IlvDim	getMnemonicDescent(IlvFont*) const;
    virtual void	computeLabelSize(const char*,
					 const IlvPalette*,
					 IlvDim&, IlvDim&,
					 IlvOrientation,
					 const IlvBidiInterface*) const;
    virtual void	drawLabel(IlvPort*,
				  const char*,
				  const IlvRect&,
				  IlvPosition,
				  IlvOrientation,
				  IlBoolean,
				  IlvPalette*,
				  const IlvRegion*,
				  const IlvBidiInterface*) const;
    virtual void	drawSelection(IlvPort*,
				      const IlvRect&,
				      IlvPalette*,
				      const IlvRegion*) const;
    virtual void	drawSeparator(IlvPort*,
				      const IlvRect&,
				      IlvDirection,
				      const IlvPalette*,
				      const IlvPalette*,
				      const IlvRegion*) const;
    virtual void	drawHighlight(IlvPort*,
				      const IlvRect&,
				      IlvPalette*,
				      const IlvRegion*,
				      IlBoolean) const;
    virtual IlBoolean	isAPasteFromClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	isACopyToClipboardEvent(const IlvEvent&) const;
    virtual IlBoolean	isACutToClipboardEvent(const IlvEvent&) const;

    DeclareLazyLookFeelTypeInfo();

protected:
    IlvBasicLFHandler(IlvDisplay*);

    virtual void	initialize();
    virtual void	releaseResources();
    IlvDim		_mnemonicDescent;
};

#define IlvPreRegisterObjectLFHandler(classname) \
static IlvObjectLFHandler* IlvCreator##classname(IlvLookFeelHandler* lf) \
{ return new classname(lf); }

#define IlvPostRegisterObjectLFHandler(lfh, object, classname) \
IlvObjectLFClassInfo* obj##classname = \
IlvLookFeelHandler::RegisterObjectLFHandler(lfh::LookFeelClassInfo(), \
					    object::ClassInfo(), \
					    IlvCreator##classname)

#define IlvRegisterObjectLFHandler(lfh, object, classname) \
IlvPreRegisterObjectLFHandler(classname) \
IlvPostRegisterObjectLFHandler(lfh, object, classname)

#define ILV_MOTIF_LFNAME	"motif"
#define ILV_WINDOWS_LFNAME	"windows"
#define ILV_WIN95_LFNAME	"win95"
#define ILV_WINXP_LFNAME	"winxp"
#define ILV_VX_LFNAME		"vx"

#if defined(ILVWINDOWSXPLOOK)
#  if !defined(ILVWINDOWS95LOOK)
#    define ILVWINDOWS95LOOK
#  endif
#endif
#if defined(ILVWINDOWS95LOOK)
#  if !defined(ILVWINDOWSLOOK)
#    define ILVWINDOWSLOOK
#  endif
#endif
#if defined(ILVVXLOOK)
#  if !defined(ILVWINDOWSLOOK)
#    define ILVWINDOWSLOOK
#  endif
#endif

// --------------------------------------------------------------------------
ILVDSPMODULEINIT(b0look);
#endif /* !__Ilv_Base_Look_H */
