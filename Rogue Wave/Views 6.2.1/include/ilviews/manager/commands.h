// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/commands.h
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
// Declaration of the IlvManagerCommand and related class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Commands_H
#define __Ilv_Manager_Commands_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Base_Command_H)
#include <ilviews/base/command.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif

class IlvManager;
class IlvView;

// ---------------- Compatibility with pre-4.0 commands -----------------------
class ILVMGREXPORTED IlvListOfCommand : public IlvCommandHistory
{
public:
    IlvListOfCommand(int maxcommands = IlvDefaultMaxCommand)
	: IlvCommandHistory((IlUInt) maxcommands)
    {}
    ~IlvListOfCommand() {}
    // old semantics of redo as repeat force us to have redo do a repeat...
    // these functions are here only for comatibility reasons.
    inline IlBoolean	reDo()
			{
			    if (canRepeat()) {
				repeatLast();
				return IlTrue;
			    }
			    else return IlFalse;
			}
    inline IlBoolean	unDo()
			{
			    if (canUndo()) {
				undo();
				return IlTrue;
			    }
			    else return IlFalse;
			}
    inline int		length() { return getLength(); }
};

// --------------------------------------------------------------------------
/*
 * The manager command class allows compatibility with the command class
 * provided in the earlier versions of Rogue Wave Views (before 4.0). 
 * If you want to create commands, you must derive them from
 * <code>IlvCommand</code> directly.
 */

class ILVMGREXPORTED IlvManagerCommand : public IlvCommand
{
    IlvActionDeclareMembers();

public:
    IlvManagerCommand(IlvManager* manager);
    ~IlvManagerCommand() {}
    inline IlvManager*	getManager() const
			{
			    return _manager
				? _manager
				: (_context
				   ? _context->getManager()
				   : (IlvManager*)0);
			}
    inline void		executeIt() { doIt(); }
    inline void		undoIt()    { unDo(); }
    virtual void	doIt()      {}
    virtual void	unDo()      {}
    IlvAction*		duplicate() const;
    IlvString		userName()  const;
    void		setContext(IlvActionHistory* h);
    virtual
    IlvManagerCommand*	copy() const = 0;

protected:
    IlvManager*		_manager; // legacy
};

// ---------------- Interface between Manager and Commands --------------------

class ILVMGREXPORTED IlvManagerModifiedObserver
    : public IlvModifiedFlagObserver
{
friend class IlvManagerSelectionHandler;
friend class IlvManager;

public:
    IlvManagerModifiedObserver(IlvCommandHistory* o)
	: IlvModifiedFlagObserver(o), _markChanged(IlFalse) {}

    void	setModified(IlBoolean);
    void	flagChanged(IlBoolean);

protected:
    IlBoolean	_markChanged;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerSelectionHandler
    : public IlvActionSelectionHandler
{
friend class IlvManager;
public:
    IlvManagerSelectionHandler(IlvManager*);
    ~IlvManagerSelectionHandler() {}
    IlvValueInterface* const*	getSelection(IlUInt& c, IlvActionHistory*);

    // commit reactualizes the selection if needed and calls
    // manager->contentsChanged if the modified flag observer has
    // said that some changes have occured.
    void			commit();
    IlvDisplay*			getDisplay();

protected:
    IlvManager*			_manager;
    IlvManagerModifiedObserver	_modificationObserver;
};

// --------------------------------------------------------------------------
// 		    Commands operating on graphic objects
// --------------------------------------------------------------------------

// ------------------- Creation/Destruction commands ------------------------

class ILVMGREXPORTED IlvAddObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvAddObjectCommand(IlvManager * m, IlvGraphic * o, int layer = 0);
    ~IlvAddObjectCommand();
    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
    IlvString		userName() const;

protected:
    int			_layer;
    IlvGraphic*		_object;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvAddObjectsCommand : public IlvManagerCommand
{
   IlvActionDeclareMembers();

public:
   IlvAddObjectsCommand(IlvManager*        m,
			IlUInt             n,
			IlvGraphic* const* o,
			int*               layers = 0);
    ~IlvAddObjectsCommand();

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;

protected:
    int*		_layers;
    IlvGraphic**	_objects;
    IlUInt		_num;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvDeleteObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvDeleteObjectCommand(IlvManager* m, IlvGraphic* o, int layer = 0);
    ~IlvDeleteObjectCommand();

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
    IlvString		userName() const;

protected:
    int			_layer;
    IlvGraphic*		_object;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvDeleteObjectsCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvDeleteObjectsCommand(IlvManager*        m,
			    IlUInt             n,
			    IlvGraphic* const* o,
			    int*               layers = 0);
    ~IlvDeleteObjectsCommand();
    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;

protected:
    int*		_layers;
    IlvGraphic**	_objects;
    IlUInt		_num;
};

// -------------------- Object editing commands --------------------------
class ILVMGREXPORTED IlvChangeLayerCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvChangeLayerCommand(IlvManager*         m,
			  int                 toLayer    = 0,
			  IlUInt              n          = 0,
			  IlvGraphic* const*  o          = 0,
			  int*                fromLayers = 0,
			  int*                fromOrder  = 0);
    ~IlvChangeLayerCommand();

    void		doIt();
    void		unDo();
    IlvManagerCommand*	copy() const;

protected:
    struct ObjectPos {
	IlvGraphic*	_object;
	int		_layer;
	int		_position;
	ObjectPos(IlvGraphic* o = 0, int l = -1, int p = -1)
	    :_object(o), _layer(l), _position(p)
	{}
    };

    IlUInt		_num;
    ObjectPos*		_objects;
    int			_newLayer;
    IlBoolean		_reversed;

    void		saveLayer(int, IlUInt, IlUInt, int*);
    void		saveState(IlUInt,
				  IlvGraphic* const*,
				  int* = 0,
				  int* = 0);
    void		restoreLayer(int, IlUInt, IlUInt);
    virtual void	positionObject(IlvGraphic*) const;

public:
    static int		LayerCmp(const void*, const void*);
    static int		PositionCmp(const void*, const void*);
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvPushObjectsCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvPushObjectsCommand(IlvManager*        m,
			  IlUInt             n = 0,
			  IlvGraphic* const* o = 0,
			  IlUInt*            p = 0);
    ~IlvPushObjectsCommand();

    void		doIt();
    void		unDo();
    IlUInt		getPosition(IlvGraphic*) const;
    void		storeState(IlUInt             n,
				   IlvGraphic* const* g,
				   IlUInt* = 0);
    void		restoreState();
    static int		PositionCmp(const void*, const void*);
    IlvManagerCommand*	copy() const;

protected:
     struct ObjectPos {
	 IlvGraphic*	_object;
	 IlUInt		_position;
     };
     IlUInt		_num;
     ObjectPos*		_objects;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvPopObjectsCommand : public IlvPushObjectsCommand
{
    IlvActionDeclareMembers();

public:
    IlvPopObjectsCommand(IlvManager*        manager,
			 IlUInt             n   = 0,
			 IlvGraphic* const* objs = 0,
			 IlUInt*            p   = 0);
    void		doIt();
    IlvManagerCommand*	copy() const;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvGroupObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvGroupObjectCommand(IlvManager*, IlvGraphic*);
    ~IlvGroupObjectCommand();
    virtual void	doIt();
    virtual void	unDo();
    virtual void	group();
    virtual void	unGroup();
    IlvManagerCommand*	copy() const;

protected:
    IlvGraphic*		_object;
    IlvGraphic**	_objects;
    IlInt*		_layers;
    IlInt		_layer;
    IlUInt		_numObjects;
};

// --------------------------------------------------------------------------
class IlvGraphicSet;
class ILVMGREXPORTED IlvUnGroupObjectCommand : public IlvGroupObjectCommand
{
    IlvActionDeclareMembers();

public:
    IlvUnGroupObjectCommand(IlvManager*, IlvGraphicSet*, int = 0);
    ~IlvUnGroupObjectCommand();

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
};

// ------------------ Commands for transforming objects -----------------------
class ILVMGREXPORTED IlvTranslateObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvTranslateObjectCommand(IlvManager*, IlvGraphic*, IlvPos, IlvPos);
    IlvTranslateObjectCommand(IlvManager*, IlvGraphic*, const IlvPoint&);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
    IlvString		userName() const;

protected:
    IlvPos		_dx;
    IlvPos		_dy;
    IlvGraphic*		_object;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvReshapeObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvReshapeObjectCommand(IlvManager*,
			    IlvGraphic*,
			    IlvRect&,
			    IlvRect* bbox = 0);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
    IlvString		userName() const;

protected:
    IlvRect		_previous;
    IlvRect		_rect;
    IlvGraphic*		_object;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvRotateObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvRotateObjectCommand(IlvManager*     m,
			   IlvGraphic*     g,
			   const IlvPoint& center,
			   IlFloat         angle);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
    IlvString		userName() const;

protected:
    IlvPoint		_center;
    IlFloat		_angle;
    IlvGraphic*		_object;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvSymmetryObjectCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public: 
    IlvSymmetryObjectCommand(IlvManager*  m,
			     IlvGraphic*  g,
			     IlvDirection direction);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;
    IlvString		userName() const;

protected:
    IlvDirection	_direction;
    IlvGraphic*		_object;
};

// -------------------- Layer manipulation commands --------------------------

// -------------------- View transform pseudo-commands ----------------------

class IlvMgrView;
class ILVMGREXPORTED IlvTranslateViewCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvTranslateViewCommand(IlvManager*, IlvMgrView* mv, IlvPos, IlvPos);
    IlvTranslateViewCommand(IlvManager*, IlvMgrView* mv, const IlvPoint&);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;

protected:
    IlvMgrView*		_mgrview; // view associated to transform
    IlvPos		_dx;
    IlvPos		_dy;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvAddTransformCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvAddTransformCommand(IlvManager*,
			   IlvView*              v,
			   const IlvTransformer* tr);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;

protected:
    IlvView*		_view; // view associated to transform
    IlvTransformer	_t;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvSetTransformCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvSetTransformCommand(IlvManager*, IlvView* v, const IlvTransformer* t);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;

protected:
    IlvView*		_view; // view associated to transform
    IlvTransformer	_t;
    IlvTransformer	_newt;
};

// -------------------- Change View size command ----------------------------
class ILVMGREXPORTED IlvSetViewGeometryCommand : public IlvManagerCommand
{
    IlvActionDeclareMembers();

public:
    IlvSetViewGeometryCommand(IlvManager*,
			      IlvView*        v,
			      const IlvPoint& newr,
			      const IlvPoint* old = 0);

    virtual void	doIt();
    virtual void	unDo();
    IlvManagerCommand*	copy() const;

protected:
    IlvView*		_view;
    IlvPoint		_oldSize;
    IlvPoint		_newSize;
};

#endif /* !__Ilv_Manager_Commands_H */
