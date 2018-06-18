// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/classpal.h
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
// Declaration of panel class palette classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Classpal_H
#define __IlvSt_Classpal_H

#ifndef __Ilv_Gadgets_Tree_H
#include <ilviews/gadgets/tree.h>
#endif
#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmShowClassPalette;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmNewApplicationFolder;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmRemoveApplicationFolder;

class IlvStudio;
class IlvStPanelClass;
class IlvStError;
class IlvStPanelInstanceFrame;
class IlvStDdData;
class IlvStFolderVisual;
class IlvStPanelClassVisual;
class IlvStApplicationVisual;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStPaletteTree
: public IlvTreeGadget
{
public:
    IlvStPaletteTree(IlvDisplay* display,
		     const IlvRect& bbox,
		     IlUShort thickness = IlvDefaultGadgetThickness,
		     IlvPalette* palette = 0);
    void		    clear();
    virtual IlBoolean	    handleEvent(IlvEvent&);
    virtual void 	    startDragItem(IlvGadgetItem* item);
    virtual void 	    abortDragItem();
    virtual void 	    endDragItem(const IlvPoint& point);
    virtual void 	    itemDragged(const IlvPoint& point);
    IlvStudio*		    getEditor() const { return _editor; }
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStPaletteTree);
protected:
    virtual IlvStDdData*    makeDdData(IlvEvent&);

    IlvStudio*		    _editor;
    IlvStDdData*	    _dragData;
    IlvEvent		    _lastEvent;
}; // class IlvStPaletteTree

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStClassPalette
: public IlvStPaletteTree
{
public:
    IlvStClassPalette(IlvDisplay* display,
		      const IlvRect& bbox,
		      IlUShort thickness = IlvDefaultGadgetThickness,
		      IlvPalette* palette = 0);
    ~IlvStClassPalette();
    void		    selectPanelClass(IlvStPanelClass*);
    void		    selectApplication();

protected:
    void		    initClassPalette();
    virtual void 	    select(IlvTreeGadgetItem* item);
    virtual void 	    deSelect(IlvTreeGadgetItem* item);
    virtual void 	    activate(IlvTreeGadgetItem* item);
    virtual IlBoolean 	    handleTreeEvent(IlvEvent& event);
    virtual IlvStDdData*    makeDdData(IlvEvent&);

public:
    IlvStError*		    addFolder(IlvStFolderVisual* folder,
				      const IlString& folderName);
    IlvStError*		    removeFolder(IlvStFolderVisual* folder);
    void		    updateFolder(IlvStPanelClass* pclass);
    IlvTreeGadgetItem*      findFolder(IlvStFolderVisual* parent,
				       const IlString& path,
				       IlBoolean create = IlTrue) const;
    void		    addPanelClass(IlvStPanelClass*);
    void		    updatePanelClass(IlvStPanelClass*);
    void		    updatePanelClassFolders();
    void		    updateApplication();
    void		    removePanelClass(IlvStPanelClass*);
    IlvStPanelClassVisual*  findPanelClass(const IlvStPanelClass*) const;
    IlvStApplicationVisual* findApplication() const;
    void		    connect(IlvStudio*);
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStClassPalette);
}; // class IlvStClassPalette

// --------------------------------------------------------------------------
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmPanelClassDragDropData;

#ifndef __IlvSt_Stddrop_H
#include <ivstudio/stddrop.h>
#endif

class ILVSTAPPLICLASS IlvStDdPanelClass
: public IlvStDdData {
public:
    IlvStDdPanelClass(IlvStPanelClass* pclass, const char* type = 0);
    IlvStPanelClass* getPanelClass() const { return _pclass; }
    void setPanelClass(IlvStPanelClass* pclass) { _pclass = pclass; }
protected:
    IlvStPanelClass* _pclass;
};

// --------------------------------------------------------------------------
#ifndef __IlvSt_Panel_H
#include <ivstudio/panel.h>
#endif

class ILVSTAPPLICLASS IlvStClassPalettePanel
: public IlvStPanelHandler
{
public:
    IlvStClassPalettePanel(IlvStudio*);
    virtual void	    connect();
    void		    updateToolBars();
    virtual void	    setUpContainer(IlvGadgetContainer*);
    IlvStClassPalette*	    getClassPalette() const { return _cpalette; }
protected:
    IlvStClassPalette*	    _cpalette;
};

// --------------------------------------------------------------------------
IlvDECLAREINITSTAPPLICLASS(st_classpal);

#endif /* __IlvSt_Classpal_H */
