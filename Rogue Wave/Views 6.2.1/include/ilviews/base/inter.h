// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/inter.h
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
// Declaration of interactor base classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Inter_H
#define __Ilv_Base_Inter_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#  include <ilviews/util/proplist.h>
#endif

// --------------------------------------------------------------------------
class IlvInteractor;

typedef IlvInteractor* (*IlvInteractorConstructor)(IlvInputFile&);

class  ILVVWSEXPORTED IlvInteractorClassInfo
    : public IlvPropClassInfo
{
public:
    virtual ~IlvInteractorClassInfo();

    inline
    IlvInteractorClassInfo*	getInteractorSuperClass() const
				{
				    return ILVCAST(IlvInteractorClassInfo*,
				    getSuperClass());
				}
    inline
    IlvInteractorConstructor	getConstructor() const
				{
				    return _constructor;
				}
    inline
    IlvInteractorClassInfo*	getNext() const { return _next; }
    inline IlvInteractor*	getSharedInstance() const
				{
				    return _sharedInstance;
				}
    inline IlSymbol*		getSharedInstanceName() const
				{
				    return _sharedName;
				}

    static IlvInteractor*	GetSharedInstance(const char* name);
    inline static 
    IlvInteractorClassInfo*	GetFirst() { return _first; }
    static
    IlvInteractorClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvInteractorConstructor,
				       IlSymbol* = 0,
				       IlvInteractor* = 0);

protected:
    IlvInteractorClassInfo(const char*			className,
			   IlvClassInfo**		superClass,
			   IlvInteractorConstructor	c,
			   IlSymbol*			sharedName = 0,
			   IlvInteractor*		sharedInstance = 0);

    IlvInteractorConstructor	_constructor;
    IlSymbol*			_sharedName;
    IlvInteractor*		_sharedInstance;
    IlvInteractorClassInfo*	_next;

    static 
    IlvInteractorClassInfo*	_first;

    static void			Chain(IlvInteractorClassInfo* ic);
    static int			InitFirst();
};

#define IlvRegisterInteractorClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
     IlvInteractorClassInfo::Create(#classname,				\
				    superclass::ClassPtr(),		\
				  (IlvInteractorConstructor)classname::Read))

#define IlvRegisterSharedInteractorClass(classname, superclass, sharedName)  \
ILVDEFINECLASSINFOMEMBERS(classname,					     \
    IlvInteractorClassInfo::Create(#classname,				     \
				   superclass::ClassPtr(),		     \
				   (IlvInteractorConstructor)classname::Read,\
				   IlGetSymbol(sharedName), new classname()))

#define IlvPreRegisterInteractorClass(classname)			\
  ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvPostRegisterInteractorClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
 IlvInteractorClassInfo::Create(#classname,				\
				superclass::ClassPtr(),			\
				(IlvInteractorConstructor)classname::Read))

#define IlvPostRegisterSharedInteractorClass(classname, sclass, sharedName) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				    \
 IlvInteractorClassInfo::Create(#classname,				    \
				sclass::ClassPtr(),			    \
				(IlvInteractorConstructor)classname::Read,  \
				IlGetSymbol(sharedName), new classname()))


#define DeclareInteractorTypeInfoRO_(classname) public:			\
    classname(IlvInputFile& file);					\
    classname(const classname& source);					\
    inline IlvInteractorClassInfo* getInteractorClassInfo() const	\
	{ return (IlvInteractorClassInfo*)getClassInfo(); }		\
    static IlvInteractor* Read(IlvInputFile&);				\
    virtual IlvInteractor* copy() const
#define DeclareInteractorTypeInfoRO(classname) public:			\
    DeclareInteractorTypeInfoRO_(classname);				\
    IlvDeclarePropClassInfo()

#define DeclareLazyInteractorTypeInfoRO(classname) public:		\
    DeclareInteractorTypeInfoRO_(classname);				\
    IlvDeclareLazyPropClassInfo()

#define DeclareInteractorTypeInfo(classname)				\
DeclareInteractorTypeInfoRO(classname);					\
virtual void write(IlvOutputFile&) const

#define DeclareLazyInteractorTypeInfo(classname)			\
DeclareLazyInteractorTypeInfoRO(classname);				\
virtual void write(IlvOutputFile&) const

#define IlvPredefinedInteractorIOMembers(classname)			\
IlvInteractor* classname::copy() const					\
{ return new classname(*this); }					\
IlvInteractor* classname::Read(IlvInputFile& i)				\
{ return new classname(i); }

// --------------------------------------------------------------------------
class IlvGraphic;
class IlvInteractor;
class ILVVWSEXPORTED IlvStackInteractorInterface
{
public:
    virtual
    IlvInteractor*	getCurrent() const = 0;
    virtual void	push(IlvInteractor*) = 0;
    virtual void	pop() = 0;
    virtual 
    IlvStackInteractorInterface*	getParent() const = 0;
    virtual void	setParent(IlvStackInteractorInterface* parent)  = 0;
    IlBoolean		removeFromParent() const;
    void		flush();
    virtual		~IlvStackInteractorInterface();

protected:
    IlvStackInteractorInterface() {}
};

#define ILVDECLAREINTERACTOR(name, classname)				\
    static IlvInteractor* name () {					\
	  static IlvInteractor* inter = 0;				\
	  if (!inter) { inter = new classname(); }			\
	  return inter;							\
    }

#define IlvInteractorAborted		((IlUInt)(1UL <<  1))
#define IlvInteractorInOperation	((IlUInt)(1UL <<  2))
#define IlvInteractorOpaque		((IlUInt)(1UL <<  3))

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvInteractor
    : public IlvStackInteractorInterface
{
public:
    virtual ~IlvInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*			g,
				    IlvEvent&			event,
				    const IlvTransformer*	t = 0) = 0;

    virtual void	handleExpose(IlvView*, 
				     const IlvTransformer*,
				     IlvRegion*);

    virtual void	startOperation();
    virtual void	endOperation();


    virtual void	abort(IlvGraphic* obj);

    virtual IlBoolean	accept(const IlvGraphic* obj) const;

    inline IlBoolean	isShared() const { return (_refCount != 0); }
    inline void		lock() { ++_refCount; }

    inline void		unLock() { if (!--_refCount) delete this; }

    //== Registering ========    
    const char*		getRegisteredName() const;

    static IlvInteractor*	Get(const char* name, IlBoolean = IlTrue);

    static const char* const* 
		GetRegisteredInteractors(IlUInt&	count,
					 IlBoolean	sortStrings = IlTrue,
					 IlBoolean	createArray = IlFalse);

    inline IlBoolean	isAborted() const
			{
			    return (_flags & IlvInteractorAborted)
				? IlTrue
				: IlFalse;
			}

    inline IlBoolean	isInOperation() const
			{
			    return (_flags & IlvInteractorInOperation)
				? IlTrue
				: IlFalse;
			}

    virtual void	getCallbackTypes(IlUInt&		count,
					 const char* const**	names,
					 const IlSymbol* const** types) const;

    void		setOpaque(IlBoolean opaque);
    inline IlBoolean	isOpaque() const
			{
			    return (_flags & IlvInteractorOpaque)
				? IlTrue
				: IlFalse;
			}

    virtual
    IlvInteractor*	copy() const;

    //== Persistence
    IlvOutputFile&	save(IlvOutputFile&) const;
    virtual void	write(IlvOutputFile&) const;
    static IlvInteractor*	Load(IlvInputFile&);
    IlvDeclareLazyPropRootClassInfo();

    //== From IlvStackInteractorInterface
    virtual
    IlvInteractor*	getCurrent() const;
    virtual void	push(IlvInteractor*);
    virtual void	pop();
    virtual
    IlvStackInteractorInterface*	getParent() const;
    virtual void	setParent(IlvStackInteractorInterface* parent);

protected:
    IlvInteractor();
    IlvInteractor(const IlvInteractor&);
    IlvInteractor(IlvInputFile&);
    IlUInt				_flags;
    IlUInt				_refCount;
    IlvStackInteractorInterface*	_parent;

    inline void		setAborted(IlBoolean b)
			{
			    if (b)
				_flags |= IlvInteractorAborted;
			    else
				_flags &= ~IlvInteractorAborted;
			}

    inline void		setInOperation(IlBoolean b)
			{
			    if (b)
				_flags |= IlvInteractorInOperation;
			    else
				_flags &= ~IlvInteractorInOperation;
			}
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvInteractorProperty
    : public IlvNamedProperty
{
public:   
    IlvInteractorProperty(IlvInteractor* inter = 0);
    virtual ~IlvInteractorProperty();

    static IlSymbol*		GetSymbol();
    static
    IlvInteractorProperty*	Get(const IlvGraphic* obj);
    static
    IlvInteractorProperty*	Remove(IlvGraphic* obj);

    inline IlvInteractor*	getInteractor() const { return _interactor; }
    void			setInteractor(IlvInteractor* inter);

    virtual IlBoolean		isPersistent() const;
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvInteractorProperty);

protected:
    IlvInteractor*		_interactor;
};

ILVVWSMODULEINIT(b0inter);
#endif /* !__Ilv_Base_Inter_H */
