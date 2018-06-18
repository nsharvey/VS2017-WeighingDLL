// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/ddpalet.h
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
// Declaration of
// --------------------------------------------------------------------------
#ifndef __IlvSt_Ddpalet_H
#define __IlvSt_Ddpalet_H

#if !defined(__IlvSt_Panel_H)
#  include <ivstudio/panel.h>
#endif
#if !defined(__IlvSt_Stprop_H)
#  include <ivstudio/stprop.h>
#endif

extern ILVSTEXPORTEDVAR(const char*) IlvNmPalettePanel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmShowPalettePanel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPaletteSelected;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPaletteContainerInitialized;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPaletteDescriptor
: public IlvStPropertySet
{
public:
    IlvStPaletteDescriptor(const char*);
    ~IlvStPaletteDescriptor();

    const char*		getDataFileName() const;
    void		setDataFileName(const char*);
    const char*		getLabel() const;
    void		setLabel(const char*);
    const char*		getBitmapName() const;
    void		setBitmapName(const char*);

    inline IlvContainer*	getContainer() const
	{ return _container; }

private:
    IlvContainer*		_container;

public:
    static int GlobalInit();
    inline void containerDeleted() { _container = 0; }

    friend class IlvStDdPalettePanel;
}; // class IlvStPaletteDescriptor

// --------------------------------------------------------------------------
#if !defined(__Ilv_Graphics_Inter_H)
#  include <ilviews/graphics/inter.h>
#endif
class ILVSTUDIOCLASS IlvStPaletteDragDrop
: public IlvDragDropInteractor
{
public:
    IlvStPaletteDragDrop(IlvStudio*);

    virtual IlBoolean inTarget(const IlvPoint&);
    virtual void doIt(IlvView* target, IlvGraphic*, const IlvPoint&);
    virtual IlBoolean  handleEvent(IlvGraphic*,
				   IlvEvent&,
				   const IlvTransformer*);

private:
    void	addToBuffer(IlvGraphic*, IlvGraphic*);
    IlvStudio*   _editor;
    IlvSmartSet* _smartSetCopy;
    IlvGraphic*	 _targetObject;

public:
    IlBoolean handleButtonDragged(IlvGraphic*,
				   IlvEvent&,
				   const IlvTransformer*);
    virtual void smartSetStartDrop(IlvView*);
    virtual void smartSetEndDrop(IlvView*);

};

// --------------------------------------------------------------------------
class IlvScrolledView;
class IlvTreeGadget;
class IlvTreeGadgetItem;
class ILVSTUDIOCLASS IlvStDdPalettePanel
: public IlvStPanelHandler
{
public:
    IlvStDdPalettePanel(IlvStudio*);
    ~IlvStDdPalettePanel();

    IlvStPaletteDescriptor* getPaletteDescriptor(const char*) const;
    void addPaletteDescriptor(IlvStPaletteDescriptor*);
    void addPaletteDescriptor(IlvStPaletteDescriptor*,
			      const char*,
			      IlUInt = (IlUInt)-1);
    IlBoolean removePaletteDescriptor(const char*);
    void selectPalette(const char*);

    virtual void selectGraphic(IlvGraphic*);
protected:
    IlvTreeGadget*		_tree;
    IlvScrolledView*		_scroller;
    IlvView*			_scrolled;
    IlvContainer*		_currentContainer;
    IlvStPaletteDragDrop*	_ddi;

    IlvGraphic* 		_currentSelected;
    IlvGraphic* 		_selectionFeedback;
private:
    void initPalettePanel();
    IlvTreeGadgetItem* makeParent(IlvStPaletteDescriptor*);
    static void SetPaletteDescriptor(IlvTreeGadgetItem*,
				     IlvStPaletteDescriptor*);
    IlvTreeGadgetItem* createTreeGadgetItem(IlvStPaletteDescriptor*);

public:
    static IlvStPaletteDescriptor* GetPaletteDescriptor(IlvTreeGadgetItem*);
    IlvTreeGadgetItem* getTreeGadgetItem(const char*) const;
    inline IlvTreeGadgetItem*
    getTreeGadgetItem(IlvStPaletteDescriptor* pdesc) const
	{ return getTreeGadgetItem(pdesc->getName()); }
    static IlvTreeGadgetItem* GetTreeGadgetItem(const char*,
						IlvTreeGadgetItem*);
    void removePaletteDescriptors(IlvTreeGadgetItem*);
    void applyOptions();
    inline IlvContainer* makeContainer(IlvStPaletteDescriptor* pdesc)
    {
	return pdesc->getContainer()
	       ? pdesc->getContainer()
	       : createPaletteContainer(pdesc);
    }
    IlvContainer* createPaletteContainer(IlvStPaletteDescriptor*);
    inline IlvTreeGadget* getPaletteTree() const
	{ return _tree; }
    void treeGadgetItemSelected(IlvTreeGadgetItem*);
    void initializePaletteObject(IlvGraphic*, IlvContainer*);
    inline IlvStPaletteDragDrop* getDragDropInteractor() const
	{ return _ddi; }
    virtual void resetModeCache(IlvContainer*);
}; // class IlvStPalettePanel

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_ddpalet)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Ddpalet_H */
