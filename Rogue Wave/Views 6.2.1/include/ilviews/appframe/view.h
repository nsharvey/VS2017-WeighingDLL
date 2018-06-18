// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/view.h
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
// Declaration of the IlvDvDocViewInterface class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_View_H)
#define __Ilv_Appframe_View_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Clssinfo_H)
#include <ilviews/appframe/clssinfo.h>
#endif
#if !defined(__Ilv_Appframe_Viewcont_H)
#include <ilviews/appframe/viewcont.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

class IlvDvDocument;
class IlvDvStream;
class IlvAbstractView;
class IlvGadget;
class IlvDvApplication;
class IlvDvDocViewInterface;
class IlvDvPrintInfo;
// --------------------------------------------------------------------------
// IlvDvDocViewContext class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvDocViewContext
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor


    IlvDvDocViewContext(IlvDvDocViewInterface* view);
    ~IlvDvDocViewContext();

    // ----------------------------------------------------------------------
    inline
    IlvDvViewContainerInterface* getContainer() const
				{
				    return _container;
				}
    inline void			setContainer(IlvDvViewContainerInterface* cont)
				{
				    _container = cont;
				}
    inline IlvDvDocument*	getDocument() const { return _document; }
    void			setDocument(IlvDvDocument* doc)
				{
				    _document = doc;
				}

    // ----------------------------------------------------------------------
protected:
    IlvDvViewContainerInterface*	_container;
    IlvDvDocument*			_document;
    IlvDvDocViewInterface*		_view;
};

// --------------------------------------------------------------------------
// IlvDvDocViewInterface class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvDocViewInterface
: public IlvDvSerializable, public IlvDvInterface
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDocViewInterface();
    virtual ~IlvDvDocViewInterface();

    // ----------------------------------------------------------------------
    // Main overridables

    virtual void	initializeView();
    virtual void	update();
    virtual void	setActive(IlBoolean = IlTrue,
				  IlvDvDocViewInterface* activated = 0,
				  IlvDvDocViewInterface* desactivated = 0);

    virtual void	close(IlBoolean deleteView = IlTrue);

    // ----------------------------------------------------------------------
    // Basic properties

    IlvDvDocument*	getDocument() const;
    void		setDocument(IlvDvDocument*, IlBoolean attach = IlTrue);

    IlvDvViewContainerInterface*	getViewContainer() const;
    void		setViewContainer(IlvDvViewContainerInterface* cont);

    IlvDvApplication*	getDvApplication() const;

    virtual IlvAbstractView*	getDvView();

    virtual IlvGraphic*		getGraphic();
    virtual IlvGadget*		getGadget();
    virtual void		reDrawView();

    // ----------------------------------------------------------------------
    // Printing
    virtual void		print(IlvPort* dst, const IlvDvPrintInfo&);
    virtual IlBoolean		isPrintable() const;

    // ----------------------------------------------------------------------
    // IO
    virtual void		serialize(IlvDvStream&);

    // ----------------------------------------------------------------------
    // Query / apply values
    virtual IlvValue&		queryValue(IlvValue&) const;
    virtual IlBoolean		applyValue(const IlvValue&);
    static void			GetAccessors(const IlSymbol* const**,
					     const IlvValueTypeClass* const**,
					     IlUInt&);
    virtual IlBoolean		getValueDescriptor(IlvValue& value) const;

    static IlSymbol*		_DocumentValue;
    static IlSymbol*		_DocModifiedMethod;
    static IlSymbol*		_DocChangedTitleMethod;

    IlvDvDeclareInterface();

protected:
    void		notifyDocument(const IlSymbol* name, ...);
    void		applyDocValue(const IlSymbol* name,
				      const IlvDvValue& param1);
    virtual void	updateViewTitle(const char* title,
					IlBoolean isModified);
    virtual IlBoolean	attachToHolder(IlvGraphicHolder* holder,
				       IlUInt nView,
				       IlvGraphic* oldGraphic = 0);
    virtual IlBoolean	attachGraphicToHolder(IlvGraphicHolder* holder,
					      IlvGraphic* graphic,
					      IlUInt nView,
					      IlvGraphic* oldGraphic = 0);

    virtual IlvDvDocViewContext*	createViewContext() = 0;
    virtual IlvDvDocViewContext*	getViewContext() const = 0;

    friend class ILVDVCLASS IlvDvViewContainerInterface;

protected:
    void		focusInView();
    // ----------------------------------------------------------------------
    //Printing Messages
    virtual IlAny	getDocViewTransformer();
    virtual void	computeDocViewBBox(IlAny);
    virtual void	dragDumpRect(IlAny);

public:
    // Callbacks
    static void		FocusInView(IlvGraphic*, IlAny);
    static void		ParentResizedCallback(IlvView*, IlvRect&,  IlAny arg);
};

// --------------------------------------------------------------------------
// IlvDvGadgetViewClassInfo class
// --------------------------------------------------------------------------
typedef IlvDvDocViewInterface* (*IlvDvGadgetViewBuilder)(IlvDisplay*);

class ILVDVCLASS IlvDvGadgetViewClassInfo : public IlvGraphicClassInfo
{
public:
    inline
    IlvDvDocViewInterface*	createGadgetView(IlvDisplay* dsp) const
				{
				    return _builder
					? _builder(dsp)
					: 0;
				}
    // ----------------------------------------------------------------------
    // Basic properties
    inline
    IlvDvGadgetViewBuilder	getBuilder() const { return _builder; }
    inline void			setBuilder(IlvDvGadgetViewBuilder builder)
				{
				    _builder = builder;
				}
    static
    IlvDvGadgetViewClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvDvGadgetViewBuilder = 0,
				       IlvGetAccessorsFunction = 0);
protected:
    IlvDvGadgetViewClassInfo(const char*	className,
			     IlvClassInfo** superClass,
			     IlvDvGadgetViewBuilder builder = 0,
			     IlvGetAccessorsFunction ga = 0)
    : IlvGraphicClassInfo(className, superClass, 0, ga),
      _builder(builder) {}
    IlvDvGadgetViewBuilder	_builder;
};

#define IlvDvDeclareGadgetViewCreate()				\
    IlvDeclareClassInfo();					\
    static IlvDvGadgetViewClassInfo* GadgetViewClassInfo()	\
    { return (IlvDvGadgetViewClassInfo*)ClassInfo(); }		\
    IlvDvDeclareDownCasting();					\
public: static IlvDvDocViewInterface* Builder(IlvDisplay*)

#if 1 || defined(ILVBUILDLIBS)

#define IlvDvPreRegisterGadgetViewClass(classname, superclass)		\
IlvDvDefineCast(classname, superclass)					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvDocViewInterface* classname::Builder(IlvDisplay* display)		\
{ return new classname(display); }					\
IlvClassInfo* classname::_classinfo = 0

#define IlvDvPostRegisterGadgetViewClass(classname, superclassname)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	   IlvDvGadgetViewClassInfo::Create(#classname,			\
					    &superclassname::_classinfo,\
					    classname::Builder))

#else  /* !ILVBUILDLIBS */

#define IlvDvPreRegisterGadgetViewClass(classname, superclass)		\
IlvDvDefineCast(classname, superclass)					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvDocViewInterface* classname::Builder(IlvDisplay* display)		\
	{ return new classname(display); }				\
IlvClassInfo* classname::_classinfo =					\
	IlvDvGadgetViewClassInfo::Create(#classname,			\
					 &superclass::_classinfo,	\
					 classname::Builder)

#define IlvDvPostRegisterGadgetViewClass(classname, superclassname)

#endif /* !ILVBUILDLIBS */

#define IlvDvRegisterGadgetViewClassWithAccessors(classname, superclassname) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname, \
			      IlvDvGadgetViewClassInfo::Create(#classname, \
					       &superclassname::_classinfo, \
					       classname::Builder,	\
					       classname::GetAccessors)) \

#define IlvDvDeclareAccessors()					\
virtual IlvValue&  queryValue(IlvValue&) const;			\
virtual IlBoolean applyValue(const IlvValue&);			\
static void GetAccessors(const IlSymbol* const**,		\
			 const IlvValueTypeClass* const**,	\
			 IlUInt&);				\
virtual IlBoolean getValueDescriptor(IlvValue& value) const

// --------------------------------------------------------------------------
// IlvDvViewClassInfo class
// --------------------------------------------------------------------------
typedef IlvDvDocViewInterface* (*IlvDvIlvViewBuilder)(IlvGadgetContainer*);

class ILVDVCLASS IlvDvViewClassInfo : public IlvGraphicClassInfo
{
public:
    IlvDvDocViewInterface* createIlvView(IlvGadgetContainer* parent) const;
    // ----------------------------------------------------------------------
    // Basic properties
    inline
    IlvDvIlvViewBuilder getBuilder()const { return _builder; }
    inline void		setBuilder(IlvDvIlvViewBuilder builder)
			{
			    _builder = builder;
			}
    static
    IlvDvViewClassInfo* Create(const char*, IlvClassInfo**,
			       IlvDvIlvViewBuilder = 0,
			       IlvGetAccessorsFunction = 0);
protected:
    IlvDvViewClassInfo(const char*	className,
		       IlvClassInfo** superClass,
		       IlvDvIlvViewBuilder builder = 0,
		       IlvGetAccessorsFunction ga = 0)
	: IlvGraphicClassInfo(className, superClass, 0, ga),
	  _builder(builder) {}

    IlvDvIlvViewBuilder _builder;
};

#define IlvDvDeclareViewCreate()			\
    IlvDeclareClassInfo();				\
    static IlvDvViewClassInfo* ViewClassInfo()		\
    { return (IlvDvViewClassInfo*)ClassInfo(); }	\
    IlvDvDeclareDownCasting();				\
public:							\
    static IlvDvDocViewInterface* Builder(IlvGadgetContainer*)

#define IlvDvPreRegisterViewClass(classname, superclass)		\
IlvDvDefineCast(classname, superclass)					\
IlvClassInfo* classname::getClassInfo() const { return _classinfo; }	\
IlvDvDocViewInterface* classname::Builder(IlvGadgetContainer* parent)	\
	{ return new classname(parent); }				\
IlvClassInfo* classname::_classinfo = 0

#define IlvDvPostRegisterViewClass(classname, superclassname)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
			      IlvDvViewClassInfo::Create(#classname,	\
					   &superclassname::_classinfo, \
					   classname::Builder))

// --------------------------------------------------------------------------
// IlvDvView class
// --------------------------------------------------------------------------
#if !defined (__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif


class ILVDVCLASS IlvDvView : public IlvView, public IlvDvDocViewInterface
{
    IlvDvDeclareViewCreate();

public:
    IlvDvView(IlvGadgetContainer* parent);
    ~IlvDvView();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractView*	getDvView();

protected:
    IlvDvDocViewContext*	_context;

    virtual
    IlvDvDocViewContext*	createViewContext();
    virtual
    IlvDvDocViewContext*	getViewContext() const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(docview);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_View_H */
