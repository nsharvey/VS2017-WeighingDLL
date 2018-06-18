// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/layer.h
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
// Declaration of the IlvManager class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Layer_H
#define __Ilv_Manager_Layer_H

#if !defined(__Ilv_Manager_Indexgr_H)
#include <ilviews/manager/indexgr.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif

// --------------------------------------------------------------------------
class IlvMgrView;
class IlvManagerLayer;
class ILVMGREXPORTED IlvLayerVisibilityFilter
{
public:
    IlvLayerVisibilityFilter();
    IlvLayerVisibilityFilter(IlvInputFile&);
    IlvDeclareClassInfo();
    virtual ~IlvLayerVisibilityFilter();

    virtual void	write(IlvOutputFile&) const;
    virtual IlBoolean	isVisible(const IlvManagerLayer* mgrlayer,
				  const IlvMgrView*      mgrview) const = 0;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvVisibilityFilterReferenceStreamer
: public IlvReferenceStreamer
{
public:
    IlvVisibilityFilterReferenceStreamer() : IlvReferenceStreamer() {}
    virtual void	writeReference(IlvOutputFile& os, IlAny object);
    virtual IlAny	readReference(IlvInputFile& is);
};

// --------------------------------------------------------------------------
IlDefineExpListOf(IlvLayerVisibilityFilter,
		  IlvLayerVisibilityFilter*,
		  ILVMGREXPORTED);

// --------------------------------------------------------------------------
// IlvManagerLayer
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayer : public IlvIndexedSet
{
    friend class IlvManager;

public:
    IlvManagerLayer(IlUShort maxInList,
		    IlUShort maxInNode = IlvMaxObjectsInList)
	: IlvIndexedSet(maxInList, maxInNode),
	  _manager(0),
	  _visible(IlTrue),
	  _selectable(IlTrue),
	  _index(ILVCAST(IlUShort, -1)),
	  _name(0),
#if defined(X11)
	  _bitPlanesGroup(-1),
#endif /* X11 */
	  _alpha(IlvFullIntensity),
	  _antialias(IlvDefaultAntialiasingMode),
	  _visibilityFilters()
    {}
    virtual ~IlvManagerLayer();

    inline IlvManager*	getManager()	       const { return _manager;	   }
    inline IlUShort	getIndex()	       const { return _index;	   }
    inline IlBoolean	isVisible()	       const { return _visible;	   }
    void		setVisible(IlBoolean v);
    inline IlBoolean	isSelectable()	       const { return _selectable; }
    void		setSelectable(IlBoolean s);
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t      = 0,
			     const IlvRegion*      region = 0,
			     const IlvRegion*      clip   = 0) const;

    virtual void	setName(const char* name);
    const char*		getName() const;
#if defined(X11)
    inline int		getBitPlanesGroup()  const { return _bitPlanesGroup; }
    inline void		setBitPlanesGroup(int bitPlanesGroup)
			{
			    _bitPlanesGroup = bitPlanesGroup;
			}
#endif /* X11 */
    virtual void	write(IlvOutputFile&) const;
    virtual IlBoolean	mustSaveObjects() const;
    void		internalRead(IlvInputFile&);
    void		setAntialiasingMode(IlvAntialiasingMode mode);
    inline
    IlvAntialiasingMode	getAntialiasingMode() const { return _antialias; }
    inline IlvIntensity	getAlpha() const { return _alpha; }
    void 		setAlpha(IlvIntensity alpha);
    inline IlDouble	getTransparency() const
	                {
			    return (IlDouble)(1. - (IlDouble)_alpha/
					      IlvFullIntensity);
			}
    inline void		setTransparency(IlDouble t)
	                {
			    t = (t < 0.) ? 0. : ((t > 1.) ? 1. : t);
			    setAlpha((IlvIntensity)
				     (IlvFullIntensity*(1. - t)));
			} 

    // Visibility filters
    inline IlListOf(IlvLayerVisibilityFilter)&	visibilityFilters()
						{
						    return _visibilityFilters;
						}
    inline void		addVisibilityFilter(IlvLayerVisibilityFilter* filter)
			{
			    _visibilityFilters.append(filter);
			}
    inline IlBoolean	removeVisibilityFilter(IlvLayerVisibilityFilter* filt)
			{
			    return _visibilityFilters.remove(filt);
			}
    IlBoolean		filterVisibility(const IlvMgrView* mgrview) const;

    IlvDeclarePropertyListOwner(IlvGraphic::NamedPropSymbol());

protected:
    IlvManager*		_manager;
    IlBoolean		_visible;
    IlBoolean		_selectable;
    IlUShort		_index;
    char*		_name;
#if defined(X11)      
    int			_bitPlanesGroup;
#endif /* X11 */
    IlvIntensity	_alpha;
    IlvAntialiasingMode _antialias;
    IlListOf(IlvLayerVisibilityFilter) _visibilityFilters;

    virtual void	setManager(IlvManager* manager);

    IlvDeclareClassInfo();
    IlvManagerLayer(IlvInputFile&);

private:
    inline void		setIndex(IlUShort i)	     { _index = i; }
    IlvManagerLayer(const IlvManagerLayer&);
};

// --------------------------------------------------------------------------
// IlvManagerLayerFactory
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayerFactory
{
public:
    IlvManagerLayerFactory() {}
    virtual ~IlvManagerLayerFactory();

    virtual
    IlvManagerLayer*	createLayer(IlUShort maxInList,
				    IlUShort maxInNode) const = 0;
};

// --------------------------------------------------------------------------
// IlvLayerVisibility Class Information
// --------------------------------------------------------------------------
typedef IlvLayerVisibilityFilter* (* IlvLayerVisibilityFilterConstructor)(IlvInputFile&);

class ILVMGREXPORTED IlvLayerVisibilityFilterClassInfo : public IlvClassInfo
{
public:
    inline
    IlvLayerVisibilityFilterConstructor	getConstructor() const
					{
					    return _constructor;
					}
    static
    IlvLayerVisibilityFilterClassInfo* Create(const char*,
					IlvClassInfo**,
					IlvLayerVisibilityFilterConstructor);
protected:
    IlvLayerVisibilityFilterClassInfo(const char*    className,
				      IlvClassInfo** superClass,
				      IlvLayerVisibilityFilterConstructor
				                     constr)
	: IlvClassInfo(className, superClass),
	  _constructor(constr)
    {}
    IlvLayerVisibilityFilterConstructor	_constructor;
};

// --------------------------------------------------------------------------
#define DeclareLayerVisibilityFilterInfoRO() IlvDeclareClassInfo();	\
    static IlvLayerVisibilityFilter* read(IlvInputFile&)

#define DeclareLayerVisibilityFilterInfo() 				\
	DeclareLayerVisibilityFilterInfoRO();				\
	virtual void write(IlvOutputFile&) const

#define DeclareLayerVisibilityFilterIOConstructors(classname) public:	\
    classname(IlvInputFile&)

#define IlvPreRegisterLayerVisibilityFilterClass(classname)		\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterLayerVisibilityFilterClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
		IlvLayerVisibilityFilterClassInfo::Create(#classname,	\
					superclass::ClassPtr(),	\
					(IlvLayerVisibilityFilterConstructor)\
					classname::read))

#define IlvPostRegisterLayerVisibilityFilterClass(classname, superclass)\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
		IlvLayerVisibilityFilterClassInfo::Create(#classname,	\
					superclass::ClassPtr(),	\
					(IlvLayerVisibilityFilterConstructor)\
					classname::read))

// --------------------------------------------------------------------------
// IlvManagerLayer Class Information
// --------------------------------------------------------------------------
typedef IlvManagerLayer* (* IlvManagerLayerConstructor)(IlvInputFile&);

class ILVMGREXPORTED IlvManagerLayerClassInfo : public IlvClassInfo
{
public:
    inline
    IlvManagerLayerConstructor	getConstructor() const
				{
				    return _constructor;
				}
    static
    IlvManagerLayerClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvManagerLayerConstructor);
protected:
    IlvManagerLayerClassInfo(const char*                className,
			     IlvClassInfo**             superClass,
			     IlvManagerLayerConstructor constructor)
	: IlvClassInfo(className, superClass),
	  _constructor(constructor)
    {}
    IlvManagerLayerConstructor	_constructor;
};

// --------------------------------------------------------------------------
#define DeclareManagerLayerInfoRO() IlvDeclareClassInfo();		\
    static IlvManagerLayer* read(IlvInputFile&)

#define DeclareLazyManagerLayerInfoRO() IlvDeclareLazyClassInfo();	\
    static IlvManagerLayer* read(IlvInputFile&)

#define DeclareManagerLayerInfo() DeclareManagerLayerInfoRO();		\
    virtual void write(IlvOutputFile&) const

#define DeclareLazyManagerLayerInfo() DeclareLazyManagerLayerInfoRO();	\
    virtual void write(IlvOutputFile&) const

#define DeclareManagerLayerIOConstructors(classname) public:		\
    classname(IlvInputFile&)

#define IlvPreRegisterManagerLayerClass(classname)			\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterManagerLayerClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
       IlvManagerLayerClassInfo::Create(#classname,			\
					superclass::ClassPtr(),		\
					(IlvManagerLayerConstructor)	\
					classname::read))

#define IlvPostRegisterManagerLayerClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	IlvManagerLayerClassInfo::Create(#classname,			\
					 superclass::ClassPtr(),	\
					 (IlvManagerLayerConstructor)	\
					 classname::read))

ILVMGRMODULEINIT(m0_layer);
#endif /* !__Ilv_Manager_Layer_H */
