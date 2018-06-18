// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/include/mgercmd.h
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
// Declaration of the ManagerCommand classes
// --------------------------------------------------------------------------
#if !defined(__Mgercmd_H)
#define __Mgercmd_H

#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif

class ILVVWSEXPORTED IlvManager;
class ManagerView;
// --------------------------------------------------------------------------
// ManagerCommand class
// --------------------------------------------------------------------------

class ManagerCommand
: public IlvDvCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ManagerCommand(IlvManager*,
		   const char* name = 0);
    ManagerCommand(const ManagerCommand&);
    ~ManagerCommand();

    // ----------------------------------------------------------------------
    // Basic properties
    typedef void (ManagerCommand::*CmdGraphicCallback) (IlvGraphic*, IlAny);
    void forEachGraphic(CmdGraphicCallback callback,
			IlAny = 0);
protected:
    IlvManager*  _manager;
    IlvGraphic** _graphics;
    IlUInt       _count;
};

// --------------------------------------------------------------------------
// TranslateSelectionCommand class
// --------------------------------------------------------------------------

class TranslateSelectionCommand
: public ManagerCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    TranslateSelectionCommand(IlvManager*,
			      const IlvPoint&,
			      const IlvTransformer* t = 0,
			      const char* name = 0);
    TranslateSelectionCommand(const TranslateSelectionCommand&);
    virtual IlvDvCommand* copy() const;
    // ----------------------------------------------------------------------
    // Main operations
    virtual void doIt();
    virtual void undo();

    // ----------------------------------------------------------------------
    void translateObject(IlvGraphic*, IlAny);
protected:
    IlvPoint       _offset;
    IlvTransformer _t;
};

// --------------------------------------------------------------------------
// ActiveSelectionCommand class
// --------------------------------------------------------------------------

class ActiveSelectionCommand
: public ManagerCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ActiveSelectionCommand(IlvManager*,
			   const IlvGraphic* activeSelection);
    ActiveSelectionCommand(const ActiveSelectionCommand&);

    // ----------------------------------------------------------------------
    // Main operations
    virtual void doIt();
    virtual void undo();

    // ----------------------------------------------------------------------
protected:
    IlUInt            _activeIndex;
    const IlvGraphic* _activeGraphic;

    void updateActiveIndex(const IlvGraphic* graphic);
    const IlvGraphic* getActiveGraphic() const;
};

// --------------------------------------------------------------------------
// ReshapeCommand class
// --------------------------------------------------------------------------

class ReshapeCommand
: public ActiveSelectionCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ReshapeCommand(IlvManager*,
		   const IlvGraphic* activeSelection,
		   const IlvRect&);
    ReshapeCommand(const ReshapeCommand&);

    virtual IlvDvCommand* copy() const;
    
    // ----------------------------------------------------------------------
    // Main operations
    virtual void doIt();
    virtual void undo();
    
    // ----------------------------------------------------------------------
protected:
    IlvRect _previousRect, _reshapedRect;
    void reshapeObject(IlvGraphic* graphic,
		       IlAny pRect);
};

// --------------------------------------------------------------------------
// ManagerDeleteCommand class
// --------------------------------------------------------------------------

class ManagerDeleteCommand
: public ActiveSelectionCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ManagerDeleteCommand(ManagerView*,
			 const IlvGraphic* activeSelection);
    ManagerDeleteCommand(const ManagerDeleteCommand&);
    ~ManagerDeleteCommand();

    virtual IlvDvCommand* copy() const;
    
    // ----------------------------------------------------------------------
    // Main operations
    virtual void doIt();
    virtual void undo();
    
    // ----------------------------------------------------------------------
    static IlvSymbol* _LayerProperty;
protected:
    ManagerView* _editor;
    IlvGraphic** _graphics;
    IlUInt       _count;

    void deleteGraphics();
    void createCopies();
    IlvGraphic* copyGraphic(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
// ManagerAlignCommand class
// --------------------------------------------------------------------------

class ManagerAlignCommand
: public ActiveSelectionCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ManagerAlignCommand(IlvManager*,
			const IlvGraphic* activeSelection,
			IlvPosition       side);
    ManagerAlignCommand(const ManagerAlignCommand&);
    ~ManagerAlignCommand();

    virtual IlvDvCommand* copy() const;
    
    // ----------------------------------------------------------------------
    // Main operations
    virtual void doIt();
    virtual void undo();

    static IlvPosition CenterVerticaly;
    static IlvPosition CenterHorizontaly;

protected:
    IlvPosition _side;
    IlvRect*    _rects;
    IlUInt      _rectNumbers;

    void createRects();
    void alignObject(IlvGraphic*,
		     IlAny);
    void setObjectBBox(IlvGraphic*,
		       IlAny);
};
// --------------------------------------------------------------------------
IL_MODULEINIT(mgercmd, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !__Mgercmd_H */
