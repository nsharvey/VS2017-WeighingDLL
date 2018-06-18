// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/smartset.h
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
// Declaration of the IlvSmartSet class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Smartset_H
#define __Ilv_Graphics_Smartset_H

#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSmartSet
{
public:
    IlvSmartSet(const IlvSmartSet& source, const char* name = 0);
    IlvSmartSet(const char* name = 0);
    IlvSmartSet(IlvDisplay* display, IlvInputFile& file);
    virtual ~IlvSmartSet();
    // ____________________________________________________________
    inline const char*	getName() const { return _name; }
    void		setName(const char* newName);
    IlBoolean		addObject(IlvGraphic* object);
    IlBoolean		removeObject(IlvGraphic* object,
				     IlBoolean   destroy = IlFalse);
    IlBoolean		hasObject(IlvGraphic* object) const;
    inline IlUInt	getCardinal() const
			{
			    return _objectNames.getLength();
			}
    virtual IlvGraphic*	getObject(const char*) const;
    IlvGraphic* const*	getObjects(IlUInt& count) const;
    inline const IlAList&	getObjectNames() const
				{
				    return _objectNames;
				}
    virtual const char*		getNamesSeparator() const;
    virtual IlvSmartSet*	copy() const;
    // Not documented:
    virtual void	write(IlvOutputFile& file) const;
    const char*		getName(const IlvGraphic* object);
    void		setName(const IlvGraphic*, const char*);
    void		rename(const IlList&);

private:
    char*		_name;
    IlAList		_objectNames;

    IlvDeclarePropRootClassInfo();
};

// --------------------------------------------------------------------------
// SmartSets IO
// --------------------------------------------------------------------------
typedef IlvSmartSet* (* IlvSmartSetConstructor)(IlvInputFile&, IlvDisplay*);

class ILVVWSEXPORTED IlvSmartSetClassInfo
: public IlvPropClassInfo {
public:
    inline IlvSmartSetConstructor	getConstructor() const
					{
					    return _constructor;
					}
    static IlvSmartSetClassInfo*	Create(const char*,
					       IlvClassInfo**,
					       IlvSmartSetConstructor);
protected:
    IlvSmartSetClassInfo(const char*		className,
			 IlvClassInfo**		superClass,
			 IlvSmartSetConstructor	constructor)
    : IlvPropClassInfo(className, superClass),
      _constructor(constructor) {}
    IlvSmartSetConstructor _constructor;
};

#define DeclareSmartSetInfoRO_()				\
    static IlvSmartSet* read(IlvInputFile&, IlvDisplay*);	\
    virtual IlvSmartSet* copy() const
#define DeclareSmartSetInfoRO() IlvDeclarePropClassInfo()	 \
	DeclareSmartSetInfoRO_()
#define DeclareLazySmartSetInfoRO() IlvDeclareLazyPropClassInfo()\
	DeclareSmartSetInfoRO_()
#define DeclareSmartSetInfo() DeclareSmartSetInfoRO(); \
    virtual void write(IlvOutputFile&) const
#define DeclareLazySmartSetInfo() DeclareLazySmartSetInfoRO(); \
    virtual void write(IlvOutputFile&) const
#define DeclareSmartSetIOConstructors(classname) public: \
    classname(IlvDisplay*, IlvInputFile&); \
    classname(const classname&)
#define IlvPreRegisterSmartSetClass(classname) \
	ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvRegisterSmartSetClass(classname, superclass)			\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	IlvSmartSetClassInfo::Create(#classname,			\
				     superclass::ClassPtr(),		\
				    (IlvSmartSetConstructor)classname::read))
#define IlvPostRegisterSmartSetClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	 IlvSmartSetClassInfo::Create(#classname,			\
				      superclass::ClassPtr(),		\
				    (IlvSmartSetConstructor)classname::read))
#define IlvPredefinedSmartSetIOMembers(classname)			    \
inline IlvSmartSet* classname::copy() const { return new classname(*this); }\
inline IlvSmartSet* classname::read(IlvInputFile& i, IlvDisplay* d)	    \
{ return new classname(d, i); }

ILVVWSMODULEINIT(smartset);
#endif /* !__Ilv_Graphics_Smartset_H */
