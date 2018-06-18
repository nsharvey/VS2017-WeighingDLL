// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/group.h
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
// Declaration of the IlvGroup class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Group_H
#define __Ilv_Protos_Group_H

#if !defined(__Ilv_Protos_Accessor_H)
#include <ilviews/protos/accessor.h>
#endif
#if !defined(__Ilv_Protos_Groupio_H)
#include <ilviews/protos/groupio.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#include <ilviews/util/proplist.h>
#endif

class IlvGroupNode;
class IlvUserAccessor;
class IlvGroupObserver;
class IlvGroupLink;

class IlvGraphicHolder;
class IlvProtoHolderInterface;
class IlvProtoGraphic;

// ---------------------------------------------------------------------------
// IlvGroupFunction		Prototype of a function to apply to all nodes
//				of a group tree.
// ---------------------------------------------------------------------------
typedef void (*IlvGroupFunction)(IlvGroupNode* node, IlAny arg);

// ---------------------------------------------------------------------------
// IlvGroup			The root of a group
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroup : public IlvAccessorHolder
{
    friend class IlvGroupNode;
    friend class IlvUserAccessor;
    friend class IlvGroupObserver;
    friend class IlvGroupInputFile;
    friend class IlvGroupOutputFile;
    friend class IlvSubGroupNode;

public:
    IlvGroup(const char* name = 0);
    IlvGroup(const IlvGroup& source,
	     IlBoolean shared,
	     IlBoolean initAccessors = IlTrue);
    IlvGroup(const IlvGroup& source);
    virtual ~IlvGroup();

    virtual IlBoolean	update(const IlvGroup& source);

    virtual IlvGroup*	copy(IlBoolean shared) const;
    virtual IlvGroup*	copy() const;

    virtual const char*	getName() const;
    virtual void	setName(const char* name);

    void		addNode(IlvGroupNode* node,
				IlBoolean uniqueName = IlFalse);
    void		removeNode(IlvGroupNode* node,
				   IlBoolean deleteIt = IlTrue);
    IlvGroupNode*	findNode(const char* name,
				 IlBoolean actual = IlTrue) const;
    IlUInt		getNodeCount() const;
    IlvGroupNode**	getNodes(IlUInt& count);
    const char**	getNodeNames(IlUInt& count);
    IlBoolean		isEmpty() const;
    IlvGroupNode*	nextNode(IlAny& link) const;
    void		deleteAllNodes();
    void		updateNodes(const IlvGroup&);

    void		addAccessor(IlvUserAccessor* accessor,
				    IlBoolean owner = IlTrue,
				    IlBoolean initialize = IlTrue,
				    IlBoolean sort = IlFalse,
				    IlvUserAccessor* previous = 0);
    void		removeAccessor(IlvAccessor* accessor,
				       IlBoolean deleteIt = IlTrue);

    IlBoolean		replaceAccessor(IlvAccessor* oldAccessor,
					IlvAccessor* newAccessor,
					IlBoolean destroy = IlTrue);
    IlBoolean		moveAccessorUp(IlvAccessor* accessor);
    IlBoolean		moveAccessorDown(IlvAccessor* accessor);
    IlBoolean		hasAccessor(IlvAccessor* accessor);
    virtual
    IlvUserAccessor*	nextUserAccessor(IlAny& link) const;
    IlUInt		getAccessorList(const char**& names,
					const char**& types,
					IlBoolean all = IlFalse,
					IlBoolean output = IlFalse) const;

    void		getAccessorList(const IlSymbol**& names,
					const IlvValueTypeClass**& types,
					IlUInt& n,
					IlBoolean all = IlFalse,
					IlBoolean output = IlFalse) const;
    void		deleteAllAccessors();
    // Subscription interface:
    //
    virtual void	subscribe(IlvAccessible* subscriber,
				  IlSymbol* sourceValue,
				  IlSymbol* subscriberValue,
				  IlvValueTypeClass* type,
				  IlvValueSubscriptionMode mode
				  = IlvValueSubscriptionChange);
    virtual void	subscribeByName(const char* subscriber,
					IlSymbol* sourceValue,
					IlSymbol* subscriberValue,
					IlvValueTypeClass* type,
					IlvValueSubscriptionMode mode
					= IlvValueSubscriptionChange);
    virtual void	unSubscribe(IlvAccessible* subscriber,
				    IlSymbol* sourceValue = 0,
				    IlSymbol* subscriberValue = 0);
    virtual void	unSubscribeByName(const char* subscriber,
					  IlSymbol* sourceValue = 0,
					  IlSymbol* subscriberValue = 0);

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    // Value interface:
    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	queryValues(IlvValue* values, IlUShort count) const;
    virtual IlBoolean	changeValues(const IlvValue* values, IlUShort count);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
    virtual
    const IlvValueTypeClass* getValueType(const IlSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    IlBoolean		beforeChangeValues(const IlvValue*, IlUShort);
    void		afterChangeValues(const IlvValue*, IlUShort);

    // properties
    inline
    static IlSymbol*	NamedPropSymbol() { return _namedPropSymbol; }

    static IlSymbol*	_namedPropSymbol;

    IlvDeclarePropertyListOwner(NamedPropSymbol());

public:
    // Parent group:
    inline
    IlvGroupNode*	getParentNode() const { return(_parentNode); }
    IlvGroup*		getParent() const;
    IlvGroup*		getTopGroup();

    // Graphic API
    void		boundingBox(IlvRect& bbox);
    IlvGraphicHolder*	getHolder() const;
    inline
    IlvProtoGraphic*	getProtoGraphic() const { return _protoGraphic; }
    IlvProtoHolderInterface* getProtoHolder() const;
    void		setProtoGraphic(IlvProtoGraphic*);
    void		setHolder(IlvGraphicHolder*);
    IlBoolean		isFlat() const;
    void		invalidateLocal(const IlvRect&);

    // Loading/saving:
    static IlvGroup*	load(const char* name,
			     IlvDisplay* display,
			     ILVSTDPREF istream* stream = 0,
			     const char* path = 0);
     IlBoolean		save(ILVSTDPREF ostream* stream = 0,
			     const char* path = 0);

    virtual
    ILVSTDPREF istream*	getNodesInputStream(const char* suffix,
					    IlvDisplay* display,
					    const char* path = 0);
    virtual
    ILVSTDPREF ostream*	getNodesOutputStream(const char* suffix,
					     const char* path = 0);

    virtual IlBoolean	deleteWhenEmpty();

    void		addObserver(IlvGroupObserver* observer);
    void		removeObserver(IlvGroupObserver* observer,
				       IlBoolean deleteIt = IlFalse);
    IlBoolean		isObserving (IlvGroupObserver* observer);
    void		replaceNode(IlAny& link, IlvGroupNode* newNode);

    static IlvGroup*	read(IlvGroupInputFile& f, IlvDisplay* display);

    static const char*	DefaultFileName(const char* name,
					const char* path = 0);

    inline
    static IlSymbol*	ClassAccessorsSymbol()
			{
			    return(_classAccessorsSymbol);
			}

    static IlSymbol*	_classAccessorsSymbol;

    IlvDeclarePropRootClassInfo();

    IlList&		getGraphics() { return _nodes; }
    void		nodesUpdated();

public:
    const char*		_name;
    IlList		_accessors;
    IlList		_nodes;
    IlList		_observers;
    IlvGroupNode*	_parentNode;
    IlvGraphicHolder*	_holder;
    IlvProtoGraphic*	_protoGraphic;

    void		copyAccessors(const IlvGroup& source);
    void		copyNodes(const IlvGroup& source, IlBoolean shared);
    virtual IlList*	getAccessorList() const;
    virtual IlList*	getClassAccList(IlAny&) const;

    void		initializeAccessors();

    virtual void	write(IlvGroupOutputFile& f) const;
    virtual void	readNodes(IlvGroupInputFile& f, IlvDisplay* display);
    virtual void	writeNodes(IlvGroupOutputFile& f) const;
    virtual void	readAccessors(IlvGroupInputFile& f,
				      IlvDisplay* display);
    virtual void	writeAccessors(IlvGroupOutputFile& f) const;
    virtual void	readGroupSubscriptions(IlvGroupInputFile& f);
    virtual void	writeGroupSubscriptions(IlvGroupOutputFile& f) const;
    IlvAccessible*	resolveSubscription(const char*) const;
    virtual void	readValues(IlvValueArray*& values,
				   IlvGroupInputFile& f,
				   IlvDisplay* display);
    virtual void	writeValues(IlvGroupOutputFile& f) const;

    void		addAccessor(IlvAccessor* accessor);
    virtual
    IlvAccessor*	nextAccessor(IlAny& link) const;
    void		sortAccessors();

    void		setParentNode(IlvGroupNode* parentNode);

    void		checkUniqueName(IlvGroupNode* node);
};

#define IlvMapGroup(group, node, exp) { \
    IlAny link = 0; \
    while ((node = (group)->nextNode(link)) != 0) { \
	      exp; \
    } \
}

#define IlvMapTwoGroups(group1, group2, node1, node2, exp) { \
    IlAny link1 = 0; \
    IlAny link2 = 0; \
    while ((node1 = (group1)->nextNode(link1)) != 0 \
	   && (node2 = (group2)->nextNode(link2)) != 0) { \
	      exp; \
    } \
}

// ---------------------------------------------------------------------------
// Class info macros for IlvGroup.
// ---------------------------------------------------------------------------
typedef IlvGroup* (* IlvGroupConstructor)(IlvGroupInputFile&, IlvDisplay*);

class ILVPROEXPORTED IlvGroupClassInfo : public IlvPropClassInfo
{
public:
    inline
    IlvGroupConstructor	getConstructor() const { return _constructor; }
    static
    IlvGroupClassInfo*	Create(const char*,
			       IlvClassInfo**,
			       IlvGroupConstructor,
			       IlvAccessor*** = 0,
			       IlUInt = 0);

protected:
    IlvGroupClassInfo(const char*		className,
		      IlvClassInfo**		superClass,
		      IlvGroupConstructor	constructor,
		      IlvAccessor***		classAccessors = 0,
		      IlUInt			classAccessorCount = 0);
    IlvGroupConstructor	_constructor;
};

#define DeclareGroupInfoRO() IlvDeclarePropClassInfo(); \
    static IlvGroup* read(IlvGroupInputFile&, IlvDisplay*); \
    virtual IlvGroup* copy() const
#define DeclareGroupInfo() DeclareGroupInfoRO(); \
    virtual void write(IlvGroupOutputFile&) const
#define DeclareGroupIOConstructors(classname) public: \
    classname(IlvDisplay*, IlvGroupInputFile&); \
    classname(const classname&)
#define IlvPreRegisterGroupClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvRegisterGroupClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,			\
    IlvGroupClassInfo::Create(#classname, \
			      &superclass::_classinfo,\
			     (IlvGroupConstructor)classname::read))
#define IlvPostRegisterGroupClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname, \
    IlvGroupClassInfo::Create(#classname, \
			      &superclass::_classinfo,\
			      (IlvGroupConstructor)classname::read))
#define IlvRegisterGroupClassWithAccessors(classname, superclass, a, c)	\
ILVDEFINECLASSINFOMEMBERS(classname, \
    IlvGroupClassInfo::Create(#classname, \
			      &superclass::_classinfo,\
			      (IlvGroupConstructor)classname::read, a, c))
#define IlvPostRegisterGroupClassWithAccessors(classname, superclass, a, c)\
ILVPOSTDEFINECLASSINFOMEMBERS(classname, \
    IlvGroupClassInfo::Create(#classname, \
			      &superclass::_classinfo,\
			     (IlvGroupConstructor)classname::read, a, c))
#define IlvPredefinedGroupIOMembers(classname) \
IlvGroup* classname::copy() const { return new classname(*this); } \
IlvGroup* classname::read(IlvGroupInputFile& i, IlvDisplay* d) \
{ return new classname(d, i); }

// ---------------------------------------------------------------------------
// IlvGroupNode			A generic node of a group
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupNode : public IlvAccessible
{
    friend class IlvGroup;
public:
    IlvGroupNode(const char* name = 0);
    virtual ~IlvGroupNode();
    // ____________________________________________________________
    static
    IlvGroupNode*	read(IlvGroupInputFile& f, IlvDisplay* display);
    virtual void	write(IlvGroupOutputFile& f) const;
    inline IlvGroup*	getGroup() const { return _group; }
    virtual IlvGroup*	getSubGroup() const;
    virtual const char*	getName() const;
    virtual void	setName(const char* name);
    const char*		getPath();

    virtual
    IlvGroupNode*	copy(IlBoolean shared) const = 0;
    virtual
    IlvGroupNode*	copy() const = 0;

    // Undocumented methods: ______________________________________
    virtual
    IlvGroupNode*	getActualNode();
    virtual void	setActualNode(IlvGroupNode*);
    virtual
    IlvAccessible*	getActualSubscriber();

    virtual void	setGroup(IlvGroup* group);

    virtual void	clear();
    virtual IlBoolean	update(const IlvGroupNode&);

    IlvDeclarePropRootClassInfo();

protected:
    const char*		_name;
    IlvGroup*		_group;
};

// ---------------------------------------------------------------------------
// Class info macros for IlvGroupNode.
// ---------------------------------------------------------------------------
typedef IlvGroupNode* (* IlvGroupNodeConstructor)(IlvGroupInputFile&,
						  IlvDisplay*);
class ILVPROEXPORTED IlvGroupNodeClassInfo : public IlvPropClassInfo
{
public:
    inline
    IlvGroupNodeConstructor getConstructor() const { return _constructor; }
    static
    IlvGroupNodeClassInfo* Create(const char*, IlvClassInfo**,
				  IlvGroupNodeConstructor,
				  IlvAccessor*** = 0,
				  IlUInt = 0,
				  IlvGroupClassInfo* = 0);

protected:
    IlvGroupNodeClassInfo(const char*             className,
			  IlvClassInfo**	  superClass,
			  IlvGroupNodeConstructor constructor,
			  IlvAccessor***	  classAccessors = 0,
			  IlUInt	          classAccessorCount = 0,
			  IlvGroupClassInfo*	  groupClassInfo = 0);
    IlvGroupNodeConstructor _constructor;
};

#define DeclareGroupNodeInfoRO() IlvDeclarePropClassInfo();	\
    static IlvGroupNode* read(IlvGroupInputFile&, IlvDisplay*); \
    virtual IlvGroupNode* copy() const
#define DeclareGroupNodeInfo() DeclareGroupNodeInfoRO(); \
    virtual void write(IlvGroupOutputFile&) const
#define DeclareGroupNodeIOConstructors(classname) public: \
    classname(IlvDisplay*, IlvGroupInputFile&); \
    classname(const classname&)
#define IlvPreRegisterGroupNodeClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvRegisterGroupNodeClass(classname, superclass) \
ILVDEFINECLASSINFOMEMBERS(classname, \
    IlvGroupNodeClassInfo::Create(#classname, \
			          &superclass::_classinfo,\
			          (IlvGroupNodeConstructor)classname::read))
#define IlvPostRegisterGroupNodeClass(classname, superclass) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
    IlvGroupNodeClassInfo::Create(#classname,			\
			          &superclass::_classinfo,	\
			          (IlvGroupNodeConstructor)classname::read))
#define IlvRegisterGroupNodeClassWithAccessors(classname, superclass, \
					       accs, count, groupclass) \
ILVDEFINECLASSINFOMEMBERS(classname, \
    IlvGroupNodeClassInfo::Create(#classname, \
			      &superclass::_classinfo,\
			      (IlvGroupNodeConstructor)classname::read, \
			      accs, count, groupclass))
#define IlvPostRegisterGroupNodeClassWithAccessors(classname, superclass, \
						   accs, count, groupclass) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname, \
    IlvGroupNodeClassInfo::Create(#classname, \
			      &superclass::_classinfo,\
			      (IlvGroupNodeConstructor)\
			      classname::read, accs, count, groupclass))
#define IlvPredefinedGroupNodeIOMembers(classname) \
IlvGroupNode* classname::copy() const { return new classname(*this); } \
IlvGroupNode* classname::read(IlvGroupInputFile& i, IlvDisplay* d) \
{ return new classname(d, i); }

// ---------------------------------------------------------------------------
// IlvGroupAccessorInterface	common code for IlvGroupAccessor and
//				IlvMultipleGroupAccessor (and others?)
// ---------------------------------------------------------------------------

extern IlBoolean _IlvGroupChangeValue(IlvAccessorHolder* object,
				      const IlvValue& val);
extern IlvValue& _IlvGroupQueryValue(const IlvAccessorHolder* object,
				     IlvValue& val);
extern void _IlvGroupFilterValues(const IlvAccessorHolder* object,
				  IlvValue* values,
				  IlUShort& count,
				  IlSymbol* const* const filteredNames,
				  IlUInt filteredCount);
extern IlUInt _IlvGroupCompareValues(const IlvAccessorHolder* object,
				     const IlvAccessible* ref,
				     IlvValue* values,
				     IlUShort count,
				     IlvValueArray& diffs);

// ---------------------------------------------------------------------------
// IlvGroupAccessor	maps a value to all the nodes of a group.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupAccessor : public IlvAccessor
{
    friend class IlvGroup;
    friend class IlvGroupNode;

public:
    IlvGroupAccessor(const char* name,
		     IlvValueTypeClass* type);

    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;

    virtual void	filterValues(const IlvAccessorHolder* object,
				     IlvValue* values,
				     IlUShort& count) const;

    virtual IlUInt	compareValues(const IlvAccessorHolder* object,
				      const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;

};

// ---------------------------------------------------------------------------
// IlvReadOnlyGroupAccessor	Use this group accessor to ignore
//				a node value when comparing values
//				(i.e. if you dont want the value to be
//				saved).
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvRunTimeGroupAccessor : public IlvGroupAccessor
{
public:
    IlvRunTimeGroupAccessor(const char* name,
			     IlvValueTypeClass* type)
	: IlvGroupAccessor(name, type) {}

    virtual IlUInt	compareValues(const IlvAccessorHolder*,
				      const IlvAccessible*,
				      IlvValue*,
				      IlUShort,
				      IlvValueArray&) const;
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
};

// ---------------------------------------------------------------------------
// IlvMultipleGroupAccessor
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvMultipleGroupAccessor : public IlvMultipleAccessor
{
public:
    IlvMultipleGroupAccessor(const char* name,
			     IlUShort count,
			     const char** names,
			     IlvValueTypeClass** types);
    IlvMultipleGroupAccessor(const char* name,
			     IlUShort count,
			     const char** names,
			     IlvValueTypeClass*** types);

    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;

    virtual void	filterValues(const IlvAccessorHolder* object,
				     IlvValue* values,
				     IlUShort& count) const;
    virtual IlUInt	compareValues(const IlvAccessorHolder* object,
				      const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;

    virtual void	queryValues(const IlvAccessorHolder* object,
				    IlvValue* values,
				    IlUShort count) const;
    virtual IlBoolean	changeValues(IlvAccessorHolder* object,
				     const IlvValue* values,
				     IlUShort count);
};

// ---------------------------------------------------------------------------
// IlvSubGroupNode		A group node holding a subgroup.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvSubGroupNode : public IlvGroupNode
{
    friend class IlvGroup;
public:
    IlvSubGroupNode(IlvGroup* subGroup,
		    const char* name = 0,
		    IlBoolean owner = IlTrue);
    virtual ~IlvSubGroupNode();

    virtual const char*	getName() const;
    virtual IlvGroup*	getSubGroup() const;

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	queryValues(IlvValue* values, IlUShort count) const;
    virtual IlBoolean	changeValues(const IlvValue* values, IlUShort count);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlUInt	compareValues(const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;

    // Subscription interface: ____________________________________
    virtual void	subscribe(IlvAccessible* subscriber,
				  IlSymbol* sourceValue,
				  IlSymbol* subscriberValue,
				  IlvValueTypeClass* type,
				  IlvValueSubscriptionMode mode
				  = IlvValueSubscriptionChange);
    virtual void	unSubscribe(IlvAccessible* subscriber,
				    IlSymbol* sourceValue = 0,
				    IlSymbol* subscriberValue = 0);
    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    // Undocumented methods: ______________________________________
    inline void		clearOwner() { _owner = IlFalse; }
    virtual
    IlvGroupNode*	copy(IlBoolean shared) const;
    virtual void	setGroup(IlvGroup* group);
    virtual void	clear();

    IlBoolean		update(const IlvGroupNode&);

    DeclareGroupNodeInfo();

protected:
    IlvGroup*		_subGroup;
    IlBoolean		_owner;
};

// ---------------------------------------------------------------------------
// IlvGroupObserver		Notification of group changes.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupObserver
{
    friend class IlvGroup;
    friend class IlvGroupNode;

public:
    IlvGroupObserver() {}
    virtual ~IlvGroupObserver();

    virtual void	valuesChanged(IlvGroup*,
				      const IlvValue*,
				      IlUInt);
    virtual void	nodesChanged(IlvGroup*);
    virtual void	groupDeleted(IlvGroup*);
};

// ---------------------------------------------------------------------------
extern const char* _IlvCheckSubClassMsg;

#define ILVCHECKSUBCLASS(o, class, errexp) \
if (!o->isSubtypeOf(class::ClassInfo())){ \
    IlvFatalError(ILVPROMSG("&IlvMsg100001", "Bad class: %s (%s expected)"), \
		  o->className(), \
		  class::ClassInfo()->getClassName()); \
		  errexp; \
}

/* 
 * The list of accessors in a IlvGroup is made of instances of the following
 * class. Warning: this is subject to change. Use documented functions
 * to access the list of accessors if you want to ensure compatibility
 * with future versions.
 */
class ILVPROEXPORTED IlvAccessorInfo
{
public:
    IlvAccessorInfo(IlvAccessor* accessor,
		    IlBoolean owner = IlTrue)
	: _accessor(accessor),
	  _owner(owner),
	  _user(IlFalse) {}
    IlvAccessorInfo(IlvUserAccessor* accessor, IlBoolean owner = IlTrue);
    ~IlvAccessorInfo();

    void		setAccessor(IlvUserAccessor* acc);

public:
    IlvAccessor*	_accessor;
    IlBoolean		_owner;
    IlBoolean		_user;
};

IlvDECLAREINITPROCLASS(group)

#endif /* __Ilv_Protos_Group_H */
