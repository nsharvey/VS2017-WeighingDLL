// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/protomgr.h
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
// Definition of the macros that are used by Prototypes-enables managers
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Protomgr_H
#define __Ilv_Protos_Protomgr_H

#if !defined(__Ilv_Protos_Macros_H)
#include <ilviews/protos/macros.h>
#endif
#if !defined(__Ilv_Manager_Io_H)
#include <ilviews/manager/io.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif
#if !defined(__Ilv_Grapher_Io_H)
#include <ilviews/grapher/io.h>
#endif
#if !defined(__Ilv_Protos_Grphnode_H)
#include <ilviews/protos/grphnode.h>
#endif
#if !defined(__Ilv_Protos_Grpgraph_H)
#include <ilviews/protos/grpgraph.h>
#endif
#if !defined(__Ilv_Protos_Groupholder_H)
#include <ilviews/protos/groupholder.h>
#endif
#if !defined(__Ilv_Protos_Valuesrc_H)
#include <ilviews/protos/valuesrc.h>
#endif

#if defined(ILVSTD)
#include <cstring>
#else  /* !ILVSTD */
#include <string.h>
#endif /* !ILVSTD */


// ---------------------------------------------------------------------------
// These functions contain the code shared between the various
// Prototype-flavored subclasses of Manager.
// ---------------------------------------------------------------------------

// Holder functions, i.e. functions common to Manager and Container.
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPHDeleteGroups(IlvGraphicHolder* holder);
extern ILVGDPEXPORTEDFUNCTION(IlvGroup*)
    IlvPHGetGroup(IlvGraphicHolder* holder, const char* name);
extern ILVGDPEXPORTEDFUNCTION(IlvGroup**)
    IlvPHGetGroups(IlvGraphicHolder* holder, IlUInt& count);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPHRegisterCallbacks(IlvGraphicHolder* holder);

// Manager versions of holder functions (for compatibility).
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMDeleteGroups(IlvManager* manager);
extern ILVGDPEXPORTEDFUNCTION(IlvGroup*)
    _IlvPMGetGroup(IlvManager* manager, const char* name);
extern ILVGDPEXPORTEDFUNCTION(IlvGroup**)
    _IlvPMGetGroups(IlvManager* manager, IlUInt& count);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMRegisterCallbacks(IlvManager* manager);

// Container functions.
extern ILVGDPEXPORTEDFUNCTION(IlBoolean)
    _IlvPCReadInstances(IlvInputFile& f,
			IlvDisplay* display,
			IlvContainer* container);

// Manager functions.
extern ILVGDPEXPORTEDFUNCTION(IlBoolean)
    _IlvPMReadInstances(IlvInputFile& f,
			IlvDisplay*   display,
			IlvManager*   manager,
			IlBoolean     cutCopy);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMDeleteGroupGraphics(IlvManager*              manager,
			      IlvProtoHolderInterface* protoHolder,
			      IlBoolean                selection,
			      IlBoolean                redraw,
			      IlBoolean                destroyIt,
			      IlInt                    layer = -1);
extern ILVGDPEXPORTEDFUNCTION(IlvGraphic**)
    _IlvPMFilterInstances(IlvGraphic* const* objs,
			  IlUInt&            count,
			  IlvList&           instances,
			  IlvManager*        manager,
			  IlBoolean          cutCopy);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMWriteInstances(IlvOutputFile& f,
			 IlvList&       instances,
			 IlvManager*    manager,
			 IlBoolean      cutCopy);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMPaste(IlvManager*              manager,
		IlvProtoHolderInterface* protoHolder,
		const IlvView*           view,
		const char*              str,
		IlvPoint&                location);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMCheckUniqueNames(IlvManager* manager);
extern ILVGDPEXPORTEDFUNCTION(IlBoolean)
    _IlvPMCheckGraphicSet(IlUInt n, IlvGraphic* const* objects);
extern ILVGDPEXPORTEDFUNCTION(IlBoolean)
    _IlvPMCheckSmartSet(IlvSmartSet* set, IlBoolean redraw);

extern ILVGDPEXPORTEDFUNCTION(IlvGroup**)
    _IlvPMGetSelectedGroups(IlvManager* manager, IlUInt& count);
extern ILVGDPEXPORTEDFUNCTION(IlvGroupGraphic**)
    _IlvPMGetGroupGraphics(IlvManager* manager, IlUInt& count);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMSelectGroup(IlvManager* manager,
		      IlvGroup*   group,
		      IlBoolean   selectIt,
		      IlBoolean   deselectAll);
extern ILVGDPEXPORTEDFUNCTION(IlBoolean)
    _IlvPMIsGroupSelected(IlvManager* manager, IlvGroup* group);
extern ILVGDPEXPORTEDFUNCTION(IlvGroupGraphic*)
    _IlvPMGetGroupGraphic(IlvManager* manager, IlvGroup* group);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMPush(IlvManager*              manager,
	       IlvProtoHolderInterface* protoHolder,
	       IlvGroupGraphic*         gg,
	       IlBoolean                redraw);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMPop(IlvManager*              manager,
	      IlvProtoHolderInterface* protoHolder,
	      IlvGroupGraphic*         gg,
	      IlBoolean                redraw);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMUndo(IlvManager* manager, IlvProtoHolderInterface* protoHolder);
extern ILVGDPEXPORTEDFUNCTION(void)
    _IlvPMRedo(IlvManager* manager, IlvProtoHolderInterface* protoHolder);

// ---------------------------------------------------------------------------
// These macros are used to generate "Prototype" sub-classes of various
// manager subclasses (Manager, Grapher, etc.).
// ---------------------------------------------------------------------------

#ifndef ILVEXPORTPROCLASS
#define ILVEXPORTPROCLASS ILVGDPEXPORTED
#endif

#define ILV_DECLARE_PM_MANAGER_CLASS(clss,superclss,iclss,oclss,ivsclss,ovsclss) \
class ivsclss; \
class ovsclss; \
 \
class ILVEXPORTPROCLASS clss \
:  public superclss, public IlvProtoHolderInterface { \
    friend class iclss; \
    friend class oclss; \
    friend class ivsclss; \
    friend class ovsclss; \
public: \
    clss(IlvDisplay*     display, \
	 int             layers    = 2, \
	 IlBoolean      useacc    = IlTrue, \
	 IlUShort maxInList = IlvMaxObjectsInList, \
	 IlUShort maxInNode = IlvMaxObjectsInList); \
    ~clss(); \
     \
    virtual IlvManagerInputFile*  createInputFile(ILVSTDPREF istream&); \
    virtual IlvManagerOutputFile* createOutputFile(ILVSTDPREF ostream&) const; \
     \
    virtual void deleteAll(IlBoolean destroyIt, \
			   IlBoolean redraw); \
    virtual void deleteAll(int layer, IlBoolean, \
			   IlBoolean redraw); \
    virtual void  deleteSelections(IlBoolean redraw=IlTrue); \
    virtual IlBoolean removeObject(IlvGraphic*, \
				   IlBoolean redraw    = IlTrue, \
				   IlBoolean destroyIt = IlTrue); \
    \
    virtual IlvGraphicSet* group(IlUInt n, IlvGraphic* const* objs); \
    virtual IlBoolean addSmartSet(IlvSmartSet*, IlBoolean redraw = IlTrue); \
    \
    virtual char* cut(IlUInt& count); \
    virtual char* copy(IlUInt& count); \
    virtual void paste(const IlvView*, const char* str, IlvPoint& location); \
    virtual void duplicate(IlvPos dx = 0, IlvPos dy = 0); \
    \
    virtual void push(IlvGraphic* obj, IlBoolean redraw = IlTrue); \
    virtual void pop(IlvGraphic* obj, IlBoolean redraw = IlTrue); \
    \
    virtual void unDo(); \
    virtual void reDo(IlBoolean); \
    \
    virtual void addValueSource(IlvValueSource* source); \
    virtual void removeValueSource(IlvValueSource* source); \
    virtual IlvValueSource* getValueSource(const char* name) const; \
    virtual IlvValueSource** getValueSources(IlUInt& count) const; \
    \
    virtual void addGroup(IlvGroup* group); \
    virtual void removeGroup(IlvGroup* group); \
    virtual IlvGroup* getGroup(const char* name) const; \
    virtual IlvGroup** getGroups(IlUInt& count) const; \
    \
    virtual IlvGroup** getSelectedGroups(IlUInt& count); \
    virtual IlvGroupGraphic** getGroupGraphics(IlUInt& count); \
    virtual void selectGroup(IlvGroup* group, \
			     IlBoolean selectIt = IlTrue, \
			     IlBoolean deselectAll = IlTrue); \
    virtual IlBoolean isGroupSelected(IlvGroup* group); \
    virtual IlvGroupGraphic* getGroupGraphic(IlvGroup* group); \
    \
    virtual IlvAccessible* getValueSourceSubscriber(const char* name); \
    \
    inline IlBoolean inCutCopy() { return(_cutCopy); } \
    \
protected: \
    IlvList _valueSources; \
    IlBoolean _cutCopy; \
    \
    virtual IlBoolean readValueSources(ivsclss& ivsf); \
    virtual void writeValueSources(ovsclss& ovsf); \
    \
    virtual void readSubscriptions(ivsclss& ivsf); \
    virtual void writeSubscriptions(ovsclss& ovsf); \
};

#define ILV_DECLARE_PM_OUTPUT_CLASS(clss,superclss,mgrclss) \
class ILVEXPORTPROCLASS clss : public superclss { \
public: \
    clss(ILVSTDPREF ostream& stream, const mgrclss* mgr = 0); \
    \
    virtual const char* typeOf() const; \
    \
    virtual IlvGraphic* const* saveObjects(IlUInt             count, \
					   IlvGraphic* const* objs, \
					   IlUInt&            totalCount); \
    virtual void saveMoreInfo(IlUInt count, IlvGraphic* const* objs); \
    \
protected: \
    IlvList _instances; \
    IlvList _nodeShadows; \
};

#define ILV_DECLARE_PM_INPUT_CLASS(clss,superclss,mgrclss) \
class ILVEXPORTPROCLASS clss : public superclss { \
public: \
    clss(ILVSTDPREF istream& stream, mgrclss* mgr = 0); \
    \
    virtual const char* typeOf() const; \
    \
    virtual IlBoolean parseBlock(const char* blockName); \
};

#define ILV_DECLARE_PM_VS_INPUT_CLASS(clss,mgrclss) \
class ILVEXPORTPROCLASS clss : public IlvValueSourceInputFile { \
public: \
    clss(ILVSTDPREF istream& stream, mgrclss* mgr) \
	: IlvValueSourceInputFile(stream), \
	  _manager(mgr) {} \
    \
    virtual IlvAccessible* getSubscriber(const char* name) \
	{ return(_manager->getValueSourceSubscriber(name)); } \
    \
protected: \
    mgrclss* _manager; \
};

#define ILV_DECLARE_PM_CLASS(clss,sclss,iclss,isclss,oclss,osclss,ivsclss,ovsclss) \
	    ILV_DECLARE_PM_MANAGER_CLASS(clss,sclss,iclss,oclss,ivsclss,ovsclss)\
	    ILV_DECLARE_PM_INPUT_CLASS(iclss,isclss,clss)\
	    ILV_DECLARE_PM_OUTPUT_CLASS(oclss,osclss,clss)\
	    ILV_DECLARE_PM_VS_INPUT_CLASS(ivsclss,clss)

#define ILV_DEFINE_PM_MANAGER_CLASS(clss,superclss,iclss,oclss,ivsclss,ovsclss) \
clss::clss(IlvDisplay*     display, \
	   int             layers, \
	   IlBoolean       useacc, \
	   IlUShort        maxInList, \
	   IlUShort        maxInNode) \
    : superclss(display, layers, useacc, maxInList, maxInNode), \
      IlvProtoHolderInterface(), \
      _valueSources(), \
      _cutCopy(IlFalse) \
{ \
    addProperty(IlvGetSymbol("IlvProtoHolderInterface"), \
    	(IlvProtoHolderInterface*)this);\
    _IlvPHRegisterCallbacks(getHolder()); \
    \
    removeAccelerator(IlvKeyUp,       IlvCtrlChar('D')); \
    removeAccelerator(IlvKeyUp,       IlvCtrlChar('A')); \
    removeAccelerator(IlvKeyUp,       IlvCtrlChar('S')); \
    removeAccelerator(IlvKeyUp,       IlvCtrlChar('G')); \
    removeAccelerator(IlvKeyUp,       IlvCtrlChar('U')); \
    removeAccelerator(IlvDoubleClick, IlvLeftButton); \
    removeAccelerator(IlvKeyUp,       IlvCtrlChar('T')); \
    removeAccelerator(IlvKeyUp,       'T');  \
} \
 \
clss::~clss() \
{ \
    _IlvPHDeleteGroups(getHolder()); \
    IlvValueSource* source; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       delete source; \
	       ); \
} \
 \
void \
clss::addValueSource(IlvValueSource* source) \
{ \
    _valueSources.append((IlAny)source); \
} \
 \
void \
clss::removeValueSource(IlvValueSource* source) \
{ \
    _valueSources.remove((IlAny)source); \
} \
 \
IlvValueSource* \
clss::getValueSource(const char* name) const \
{ \
    IlvValueSource* source; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       if(strcmp(source->getName(), name) == 0) \
	           return(source); \
	       ); \
    return(0); \
} \
 \
IlvValueSource** \
clss::getValueSources(IlUInt& count) const \
{ \
    count = _valueSources.length(); \
    IlvValueSource** sources = \
		new IlvValueSource*[count]; \
    IlvValueSource* source; \
    IlUInt i = 0; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       sources[i++] = source; \
	       ); \
    return(sources); \
} \
 \
void \
clss::addGroup(IlvGroup* group) \
{ \
    group->changeValue(IlvValue("manager", (IlAny)this)); \
} \
 \
void \
clss::removeGroup(IlvGroup* group) \
{ \
    group->changeValue(IlvValue("manager", (IlAny)0)); \
} \
 \
IlvGroup* \
clss::getGroup(const char* name) const\
{ \
    return(IlvPHGetGroup(getHolder(), name)); \
} \
 \
IlvGroup** \
clss::getGroups(IlUInt& count) const\
{ \
    return(IlvPHGetGroups(getHolder(), count)); \
} \
 \
IlvGroup** \
clss::getSelectedGroups(IlUInt& count) \
{ \
    return(_IlvPMGetSelectedGroups(this, count)); \
} \
 \
IlvGroupGraphic** \
clss::getGroupGraphics(IlUInt& count) \
{ \
    return(_IlvPMGetGroupGraphics(this, count));  \
} \
 \
void \
clss::selectGroup(IlvGroup* group, \
		  IlBoolean selectIt, \
		  IlBoolean deselectAll) \
{ \
    _IlvPMSelectGroup(this, group, selectIt, deselectAll); \
} \
 \
IlBoolean \
clss::isGroupSelected(IlvGroup* group) \
{ \
    return(_IlvPMIsGroupSelected(this, group)); \
} \
 \
IlvGroupGraphic* \
clss::getGroupGraphic(IlvGroup* group) \
{ \
    return(_IlvPMGetGroupGraphic(this, group)); \
} \
 \
IlvAccessible* \
clss::getValueSourceSubscriber(const char* name) \
{ \
    IlvAccessible* accessible = (IlvAccessible*)getGroup(name); \
    if(accessible) \
        return(accessible); \
    return((IlvAccessible*)getValueSource(name)); \
} \
 \
IlBoolean \
clss::readValueSources(ivsclss& ivsf) \
{ \
      IlUInt count; \
      ivsf.getStream() >> count; \
      for(IlUInt i = 0; i < count; i++){ \
          IlvValueSource* source = ivsf.readValueSource(getDisplay()); \
	  if(!source) \
              return(IlFalse); \
	  addValueSource(source); \
      } \
      return(IlTrue); \
} \
 \
void \
clss::writeValueSources(ovsclss& ovsf) \
{ \
    IlUInt count; \
    IlvValueSource** sources = getValueSources(count); \
    ovsf.writeValueSources(sources, count); \
    delete[] sources; \
} \
 \
void \
clss::readSubscriptions(ivsclss& ivsf) \
{ \
      ivsf.readSubscriptions(); \
} \
 \
void \
clss::writeSubscriptions(ovsclss& ovsf) \
{ \
      IlUInt valueSourceCount; \
      IlvValueSource** valueSources = getValueSources(valueSourceCount); \
      if (valueSources) {\
          ovsf.writeSubscriptions((IlvAccessible**)valueSources, valueSourceCount); \
          delete[] valueSources; \
      }\
} \
 \
IlvManagerInputFile*   \
clss::createInputFile(ILVSTDPREF istream& stream) \
{ \
    return(new iclss(stream, this)); \
} \
 \
IlvManagerOutputFile*  \
clss::createOutputFile(ILVSTDPREF ostream& stream) const \
{ \
    return(new oclss(stream, this)); \
} \
 \
void  \
clss::deleteAll(IlBoolean destroyIt, \
		IlBoolean redraw) \
{ \
    _IlvPMDeleteGroupGraphics(this, 0, IlFalse, redraw, destroyIt); \
    \
    IlvValueSource* source; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       delete source; \
	       ); \
    _valueSources.empty(); \
    \
    superclss::deleteAll(destroyIt, redraw); \
} \
 \
void  \
clss::deleteAll(int layer, \
		IlBoolean destroyIt, \
		IlBoolean redraw) \
{ \
    _IlvPMDeleteGroupGraphics(this, \
			      (IlvProtoHolderInterface*)this, \
			      IlFalse, \
			      redraw, \
			      destroyIt, layer); \
    superclss::deleteAll(layer, destroyIt, redraw); \
} \
     \
void \
clss::deleteSelections(IlBoolean redraw) \
{ \
    _IlvPMDeleteGroupGraphics(this, \
			      (IlvProtoHolderInterface*)this, \
			      IlTrue, \
			      redraw, \
			      IlTrue); \
    superclss::deleteSelections(redraw); \
} \
 \
IlBoolean \
clss::removeObject(IlvGraphic* obj, IlBoolean redraw, IlBoolean destroyIt) \
{ \
    IlvGraphicValueSource::CleanSource(obj, this); \
    return(superclss::removeObject(obj, redraw, destroyIt)); \
} \
 \
IlvGraphicSet* \
clss::group(IlUInt n, IlvGraphic* const* objs) \
{ \
    if(!_IlvPMCheckGraphicSet(n, objs)) \
        return(0); \
    return(superclss::group(n, objs)); \
} \
 \
IlBoolean \
clss::addSmartSet(IlvSmartSet* set, IlBoolean redraw) \
{ \
    if(!_IlvPMCheckSmartSet(set, redraw)) \
        return(IlFalse); \
    return(superclss::addSmartSet(set, redraw)); \
} \
 \
char* \
clss::cut(IlUInt& count) \
{ \
    _cutCopy = IlTrue; \
    char* s = superclss::cut(count); \
    _cutCopy = IlFalse; \
    return(s); \
} \
 \
char* \
clss::copy(IlUInt& count) \
{ \
    _cutCopy = IlTrue; \
    char* s = superclss::copy(count); \
    _cutCopy = IlFalse; \
    return(s); \
} \
 \
void \
clss::paste(const IlvView* view, const char* str, IlvPoint& location) \
{ \
    _cutCopy = IlTrue; \
    _IlvPMPaste(this, \
		(IlvProtoHolderInterface*)this, \
		view, str, location); \
    _cutCopy = IlFalse; \
} \
 \
void \
clss::duplicate(IlvPos dx, IlvPos dy) \
{ \
    superclss::duplicate(dx, dy); \
    _IlvPMCheckUniqueNames(this); \
} \
 \
void \
clss::push(IlvGraphic* obj, IlBoolean redraw) \
{ \
    if(obj->getClassInfo() == IlvGroupGraphic::ClassInfo()) \
        _IlvPMPush(this, \
                   (IlvProtoHolderInterface*)this, \
                   (IlvGroupGraphic*)obj, \
                   redraw); \
    else \
        superclss::push(obj, redraw); \
} \
 \
void \
clss::pop(IlvGraphic* obj, IlBoolean redraw) \
{ \
    if(obj->getClassInfo() == IlvGroupGraphic::ClassInfo()) \
        _IlvPMPop(this, \
                  (IlvProtoHolderInterface*)this, \
                  (IlvGroupGraphic*)obj, \
                  redraw); \
    else \
        superclss::pop(obj, redraw); \
} \
 \
void \
clss::unDo() \
{ \
    _IlvPMUndo(this, (IlvProtoHolderInterface*)this); \
} \
 \
void \
clss::reDo(IlBoolean) \
{ \
    _IlvPMRedo(this, (IlvProtoHolderInterface*)this); \
}

#define ILV_DEFINE_PM_OUTPUT_CLASS(clss,superclss,name,mgrclss,ovsclss) \
clss::clss(ILVSTDPREF ostream& stream, const mgrclss* mgr) \
    : superclss(stream, mgr), \
      _instances() \
{ \
} \
 \
const char* \
clss::typeOf() const \
{ \
    return(name); \
} \
 \
IlvGraphic* const* \
clss::saveObjects(IlUInt count,  \
		  IlvGraphic* const* objs, \
		  IlUInt& totalCount) \
{ \
    IlvGraphic** filteredObjs = \
	_IlvPMFilterInstances(objs, count, _instances, \
			      (IlvManager*)getManager(), \
			      ((mgrclss*)getManager())->inCutCopy()); \
    IlvGraphic* const* savedobjs = \
	superclss::saveObjects(count, filteredObjs, totalCount); \
    delete[] filteredObjs; \
    return(savedobjs); \
} \
 \
void \
clss::saveMoreInfo(IlUInt count, IlvGraphic* const* objs) \
{ \
    superclss::saveMoreInfo(count, objs); \
    _IlvPMWriteInstances(*this, _instances, \
			 (IlvManager*)getManager(), \
			 ((mgrclss*)getManager())->inCutCopy()); \
    ovsclss ovsf(getStream()); \
    ovsf.setOutputFile(this); \
    ((mgrclss*)getManager())->writeValueSources(ovsf); \
    ((mgrclss*)getManager())->writeSubscriptions(ovsf); \
}

#define ILV_DEFINE_PM_INPUT_CLASS(clss,superclss,name,oname,mgrclss,ivsclss) \
clss::clss(ILVSTDPREF istream& stream, mgrclss* mgr) \
    : superclss(stream, mgr) \
{ \
} \
 \
const char* \
clss::typeOf() const \
{ \
    return(name); \
} \
 \
IlBoolean \
clss::parseBlock(const char* blockName) \
{ \
    if(strcmp(blockName, "Instances") == 0){ \
        return(_IlvPMReadInstances(*this, getDisplay(), getManager(), \
			           ((mgrclss*)getManager())->inCutCopy())); \
    } else if(strcmp(blockName, "ValueSources") == 0){ \
	ivsclss ivsf(getStream(), (mgrclss*)getManager()); \
	ivsf.setInputFile(this); \
        return(((mgrclss*)getManager())->readValueSources(ivsf)); \
    } else if(strcmp(blockName, "Subscriptions") == 0){ \
	ivsclss ivsf(getStream(), (mgrclss*)getManager()); \
        ((mgrclss*)getManager())->readSubscriptions(ivsf); \
        return(IlTrue); \
    } else { \
        return(superclss::parseBlock(blockName)); \
    } \
}

#define ILV_DEFINE_PM_CLASS(clss,sclss,iclss,isclss,iname,oclss,osclss,oname,ivsclss,ovsclss) \
	   ILV_DEFINE_PM_MANAGER_CLASS(clss,sclss,iclss,oclss,ivsclss,ovsclss)\
	   ILV_DEFINE_PM_INPUT_CLASS(iclss,isclss,iname,oname,clss,ivsclss)\
	   ILV_DEFINE_PM_OUTPUT_CLASS(oclss,osclss,oname,clss,ovsclss)


// ---------------------------------------------------------------------------
// IlvProtoManager	A sub-class of Manager that handles groups and
//			prototype instances properly.
// IlvProtoManagerOutputFile
// IlvProtoManagerInputFile
// ---------------------------------------------------------------------------

ILV_DECLARE_PM_CLASS(IlvProtoManager, IlvManager,\
		     IlvProtoManagerInputFile, IlvManagerInputFile,\
		     IlvProtoManagerOutputFile, IlvManagerOutputFile,\
		     IlvProtoManagerVSInputFile, IlvValueSourceOutputFile)

extern ILVGDPEXPORTEDFUNCTION(IlBoolean)
    IlvPrConvertProtoManager(IlvProtoManager*, IlvManager*);

// ---------------------------------------------------------------------------
// IlvProtoGrapher	Same for Grapher (should be in a separate file ?)
// IlvProtoGraphOutputFile
// IlvProtoGraphInputFile
// ---------------------------------------------------------------------------

ILV_DECLARE_PM_CLASS(IlvProtoGrapher, IlvGrapher,\
		     IlvProtoGraphInputFile, IlvGraphInputFile,\
		     IlvProtoGraphOutputFile, IlvGraphOutputFile,\
		     IlvProtoGraphVSInputFile, IlvValueSourceOutputFile)

// ---------------------------------------------------------------------------
// These macros are used to generate "Prototype" sub-classes of various
// container subclasses (Container, GadgetContainer).
// ---------------------------------------------------------------------------

#define ILV_DECLARE_PC_CONTAINER_CLASS(clss,superclss,iclss,ivsclss) \
class ivsclss; \
class ILVEXPORTPROCLASS clss :  public superclss, public IlvProtoHolderInterface { \
    friend class iclss; \
    friend class ivsclss; \
public: \
    clss(IlvDisplay*    display, \
	 const char*    name, \
	 const char*    title, \
	 const IlvRect& dims, \
	 IlUInt         properties, \
	 IlBoolean      useacc       = IlTrue, \
	 IlBoolean      visible      = IlTrue, \
	 IlvSystemView  transientFor = 0);\
    clss(IlvDisplay*,\
	 IlvSystemView,\
	 const IlvRect&,\
	 IlBoolean useacc  = IlTrue,\
	 IlBoolean visible = IlTrue); \
    clss(IlvAbstractView* parent, \
	 const IlvRect& size, \
	 IlBoolean useacc = IlFalse, \
	 IlBoolean visible = IlTrue); \
    ~clss(); \
     \
    virtual IlvViewInputFile*  createInputFile(ILVSTDPREF istream&); \
    virtual IlBoolean removeObject(IlvGraphic* obj, \
				   IlBoolean redraw = IlFalse); \
     \
    virtual void addValueSource(IlvValueSource* source); \
    virtual void removeValueSource(IlvValueSource* source); \
    virtual IlvValueSource* getValueSource(const char* name) const; \
    virtual IlvValueSource** getValueSources(IlUInt& count) const; \
    \
    virtual void addGroup(IlvGroup* group); \
    virtual void removeGroup(IlvGroup* group); \
    virtual IlvGroup* getGroup(const char* name) const; \
    virtual IlvGroup** getGroups(IlUInt& count) const; \
    \
    virtual IlvGroup** getSelectedGroups(IlUInt& count); \
    virtual IlvGroupGraphic** getGroupGraphics(IlUInt& count); \
    virtual void selectGroup(IlvGroup* group, \
			     IlBoolean selectIt = IlTrue, \
			     IlBoolean deselectAll = IlTrue); \
    virtual IlBoolean isGroupSelected(IlvGroup* group); \
    virtual IlvGroupGraphic* getGroupGraphic(IlvGroup* group); \
    \
    virtual IlvAccessible* getValueSourceSubscriber(const char* name); \
    \
    virtual IlBoolean applyValue(const IlvValue& value); \
    \
protected: \
    IlvList _valueSources; \
    \
    virtual IlBoolean readValueSources(ivsclss& ivsf); \
    virtual void readSubscriptions(ivsclss& ivsf); \
};

#define ILV_DECLARE_PC_INPUT_CLASS(clss,superclss,contclss) \
class ILVEXPORTPROCLASS clss : public superclss { \
public: \
    clss(ILVSTDPREF istream& stream, contclss* cont = 0); \
 \
    virtual const char* typeOf() const; \
     \
    virtual IlBoolean readAll(IlvContainer* container); \
    virtual IlBoolean parseBlock(const char* blockName); \
};

#define ILV_DECLARE_PC_VS_INPUT_CLASS(clss,contclss) \
class ILVEXPORTPROCLASS clss : public IlvValueSourceInputFile { \
public: \
    clss(ILVSTDPREF istream& stream, contclss* cont) \
	: IlvValueSourceInputFile(stream), \
	  _container(cont) {} \
 \
    virtual IlvAccessible* getSubscriber(const char* name) \
     { return(_container->getValueSourceSubscriber(name)); } \
 \
protected: \
    contclss* _container; \
};

#define ILV_DECLARE_PC_CLASS(clss,sclss,iclss,isclss,ivsclss) \
	    ILV_DECLARE_PC_CONTAINER_CLASS(clss,sclss,iclss,ivsclss)\
	    ILV_DECLARE_PC_INPUT_CLASS(iclss,isclss,clss)\
	    ILV_DECLARE_PC_VS_INPUT_CLASS(ivsclss,clss)

#define ILV_DEFINE_PC_CONTAINER_CLASS(clss,superclss,iclss,ivsclss) \
clss::clss(IlvDisplay*     display, \
	    const char*    name, \
	    const char*    title, \
	    const IlvRect& dims, \
	    IlUInt         properties, \
	    IlBoolean      useacc, \
	    IlBoolean      visible, \
	    IlvSystemView  transientFor) \
    : superclss(display, name, title, dims, properties, useacc, visible, transientFor), \
      IlvProtoHolderInterface(), \
      _valueSources() \
{ \
    addProperty(IlvGetSymbol("IlvProtoHolderInterface"), \
    	(IlvProtoHolderInterface*)this);\
    _IlvPHRegisterCallbacks(getHolder()); \
} \
 \
clss::clss(IlvDisplay*    display,\
	   IlvSystemView  view,\
	   const IlvRect& size,\
	   IlBoolean      useacc,\
	   IlBoolean      visible)\
    : superclss(display, view, size, useacc, visible), \
     IlvProtoHolderInterface(), \
     _valueSources() \
{ \
    addProperty(IlvGetSymbol("IlvProtoHolderInterface"), \
    	(IlvProtoHolderInterface*)this);\
    _IlvPHRegisterCallbacks(getHolder()); \
} \
 \
clss::clss(IlvAbstractView* parent, \
	   const IlvRect&   size, \
	   IlBoolean        useacc, \
	   IlBoolean        visible) \
    : superclss(parent, size, useacc, visible), \
      IlvProtoHolderInterface(), \
      _valueSources() \
{ \
    addProperty(IlvGetSymbol("IlvProtoHolderInterface"), \
    	(IlvProtoHolderInterface*)this);\
    _IlvPHRegisterCallbacks(getHolder()); \
} \
 \
clss::~clss() \
{ \
    _IlvPHDeleteGroups(getHolder()); \
    IlvValueSource* source; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       delete source; \
	       ); \
} \
 \
void \
clss::addValueSource(IlvValueSource* source) \
{ \
    _valueSources.append((IlAny)source); \
} \
 \
void \
clss::removeValueSource(IlvValueSource* source) \
{ \
    _valueSources.remove((IlAny)source); \
} \
 \
IlvValueSource* \
clss::getValueSource(const char* name) const \
{ \
    IlvValueSource* source; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       if(strcmp(source->getName(), name) == 0) \
	           return(source); \
	       ); \
    return(0); \
} \
 \
IlvValueSource** \
clss::getValueSources(IlUInt& count) const \
{ \
    count = _valueSources.length(); \
    IlvValueSource** sources = \
		new IlvValueSource*[count]; \
    IlvValueSource* source; \
    IlUInt i = 0; \
    IlvMapList(&_valueSources, IlvValueSource*, source, \
	       sources[i++] = source; \
	       ); \
    return(sources); \
} \
 \
void \
clss::addGroup(IlvGroup* group) \
{ \
    group->changeValue(IlvValue("container", (IlAny)this)); \
} \
 \
void \
clss::removeGroup(IlvGroup* group) \
{ \
    group->changeValue(IlvValue("container", (IlAny)0)); \
} \
 \
IlvGroup* \
clss::getGroup(const char* name) const \
{ \
    return(IlvPHGetGroup(getHolder(), name)); \
} \
 \
IlvGroup** \
clss::getGroups(IlUInt& count) const \
{ \
    return(IlvPHGetGroups(getHolder(), count)); \
} \
 \
IlvGroup** \
clss::getSelectedGroups(IlUInt& count) \
{ \
    count = 0; \
    return(0); \
} \
 \
IlvGroupGraphic** \
clss::getGroupGraphics(IlUInt& count) \
{ \
    count = 0; \
    return(0); \
} \
 \
void \
clss::selectGroup(IlvGroup*, \
		  IlBoolean, \
		  IlBoolean) \
{ \
} \
 \
IlBoolean \
clss::isGroupSelected(IlvGroup*) \
{ \
    return(IlFalse); \
} \
 \
IlvGroupGraphic* \
clss::getGroupGraphic(IlvGroup*) \
{ \
    return(0); \
} \
 \
IlvAccessible* \
clss::getValueSourceSubscriber(const char* name) \
{ \
    IlvAccessible* accessible = (IlvAccessible*)getGroup(name); \
    if(accessible) \
        return(accessible); \
    return((IlvAccessible*)getValueSource(name)); \
} \
 \
IlBoolean \
clss::readValueSources(ivsclss& ivsf) \
{ \
      IlUInt count; \
      ivsf.getStream() >> count; \
      for(IlUInt i = 0; i < count; i++){ \
          IlvValueSource* source = ivsf.readValueSource(getDisplay()); \
	  if(!source) \
              return(IlFalse); \
	  addValueSource(source); \
      } \
      return(IlTrue); \
} \
 \
void \
clss::readSubscriptions(ivsclss& ivsf) \
{ \
      ivsf.readSubscriptions(); \
} \
 \
 \
IlvViewInputFile*   \
clss::createInputFile(ILVSTDPREF istream& stream) \
{ \
    return(new iclss(stream, this)); \
} \
 \
IlBoolean \
clss::applyValue(const IlvValue& value) \
{ \
    if (value.getName() == _getObjectMethod ) { \
        if ( !checkValue(value)) \
            return IlFalse; \
        IlvValue* arg = value._value.values.value; \
        IlvValueInterface* object = getGroup((const char*)arg[1]); \
	if(!object) \
	    object = getObject((const char*)arg[1]); \
        if (object) \
	    arg[0] = object; \
        else \
            arg[0].empty(); \
        return IlTrue; \
    } \
    return superclss::applyValue(value); \
} \
 \
IlBoolean \
clss::removeObject(IlvGraphic* obj, IlBoolean redraw) \
{ \
    IlvGraphicValueSource::CleanSource(obj, this); \
    return(superclss::removeObject(obj, redraw)); \
}

#define ILV_DEFINE_PC_INPUT_CLASS(clss,superclss,name,contclss,ivsclss) \
clss::clss(ILVSTDPREF istream& stream, contclss* cont) \
    : superclss(stream, cont) \
{ \
} \
 \
const char* \
clss::typeOf() const \
{ \
    return(name); \
} \
 \
IlBoolean \
clss::readAll(IlvContainer* container) \
{ \
    superclss::readAll(container); \
    return(IlTrue); \
} \
 \
IlBoolean \
clss::parseBlock(const char* blockName) \
{ \
    if(strcmp(blockName, "Instances") == 0){ \
        return(_IlvPCReadInstances(*this, getDisplay(), getContainer())); \
    } else if(strcmp(blockName, "ValueSources") == 0){ \
	ivsclss ivsf(getStream(), (contclss*)getContainer()); \
	ivsf.setInputFile(this); \
        return(((contclss*)getContainer())->readValueSources(ivsf)); \
    } else if(strcmp(blockName, "Subscriptions") == 0){ \
	ivsclss ivsf(getStream(), (contclss*)getContainer()); \
        ((contclss*)getContainer())->readSubscriptions(ivsf); \
        return(IlTrue); \
    } else { \
        return(superclss::parseBlock(blockName)); \
    } \
}

#define ILV_DEFINE_PC_CLASS(clss,sclss,iclss,isclss,iname,ivsclss) \
	   ILV_DEFINE_PC_CONTAINER_CLASS(clss,sclss,iclss,ivsclss)\
	   ILV_DEFINE_PC_INPUT_CLASS(iclss,isclss,iname,clss,ivsclss)

IlvDECLAREINITGDPCLASS(protomgr)

#endif /* __Ilv_Protos_Protomgr_H */
