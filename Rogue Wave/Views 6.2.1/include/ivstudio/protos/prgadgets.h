// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/protos/prgadgets.h
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
// Declarations for Gadgets used by the IlvGroupInspector
// --------------------------------------------------------------------------
#ifndef __IlvSt_Groups_Prgadgets_H
#define __IlvSt_Groups_Prgadgets_H

#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/hsheet.h>
#include <ivstudio/protos/stproto.h>

#include <ivstudio/vobj.h>

class IlvGroupValueEditor;
class IlvGroupEditorPane;
class IlvGroupAccArray;
class IlvUserAccessor;

// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupMatrix : public IlvMatrix 
{
public:
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvGroupMatrix);

    IlvGroupMatrix(IlvDisplay* dpy,
		   const IlvRect& r, 
		   IlUShort row,
		   IlUShort col,
		   IlvDim w,
		   IlvDim h)
	: IlvMatrix(dpy, r, row, col, w, h, 0),
	_pane(0)
	{}

    IlvTextField*	createEditionField(IlUShort, IlUShort);
    inline void		setPane(IlvGroupEditorPane* p) { _pane = p; }

protected:
    IlvGroupEditorPane*		_pane;
};

// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupHierarchicalSheet : public IlvHierarchicalSheet 
{
public:
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvGroupHierarchicalSheet);

    IlvTextField*	createEditionField(IlUShort, IlUShort);
    inline void		setPane(IlvGroupEditorPane* p) { _pane = p; }
    void		cellInfo(IlUShort,
				 IlUShort,
				 IlUShort&,
				 IlUShort&,
				 IlUShort&,
				 IlUShort&) const;
    void		drawItem(IlvPort* dst,
				 IlUShort colno,
				 IlUShort rowno,
				 const IlvRect& itembbox,
				 const IlvRect& clip) const;

protected:
    IlvGroupEditorPane*	_pane;
};

// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvOffsetLabelMatrixItem : public IlvLabelMatrixItem
{
public:
    DeclareMatrixItemInfoRO();
    DeclareMatrixItemIOConstructors(IlvOffsetLabelMatrixItem);

public:    
    IlvOffsetLabelMatrixItem(const char* lbl, IlBoolean cp = IlTrue)
	: IlvLabelMatrixItem(lbl, cp)
	{}

    void		draw(const IlvMatrix* matrix,
			     IlUShort col,
			     IlUShort row,
			     IlvPort* dst,
			     const IlvRect& bbox,
			     const IlvRect* clip) const;
};

// --------------------------------------------------------------------------
class  ILVSTPRCLASS IlvGroupLabelMatrixItem : public IlvOffsetLabelMatrixItem
{
public:
    DeclareMatrixItemInfoRO();
    DeclareMatrixItemIOConstructors(IlvGroupLabelMatrixItem);

public:    
    IlvGroupLabelMatrixItem(const char*			lbl,
			    const IlvGroupAccArray*	a,
			    const IlvGroupValueEditor*	v,
			    const IlvUserAccessor*	acc,
			    IlUInt			p = 0,
			    IlBoolean			cp = IlTrue)
    /* C++ shortcoming: semantically, the objects passed as const *are* const
       in the body of the constructor, which is what const means.
       yet, when the callback will be called, these objects can't be const,
       because they may be modified as a result of the callback.
       hence we have to do this unrecommended cast here, rather than in the
       callback.
    */
	: IlvOffsetLabelMatrixItem(lbl, cp),
	  _array((IlvGroupAccArray*)a),
    	  _value((IlvGroupValueEditor*)v),
	  _acc((IlvUserAccessor*)acc),
	  _param(p),_symbol(0) 
	{ 
	}

    IlvGroupLabelMatrixItem(const char* lbl,
			    const IlSymbol* symb, 
			    IlBoolean cp = IlTrue)
	: IlvOffsetLabelMatrixItem(lbl, cp),
	_array(0),
	_value(0),
	_acc(0),
	_param(0),
    	_symbol(symb)
	{}

public:
    IlvGroupAccArray*		_array;
    IlvGroupValueEditor*	_value;
    IlvUserAccessor*		_acc;
    IlUInt			_param;
    const IlSymbol*		_symbol;
};

// --------------------------------------------------------------------------
ILVSTPREXPORTEDFUNCTION(IlvTextField*) 
IlvGroupMakeValueField(IlvDisplay*,
		       const IlvRect&,
		       const char*,
		       IlvGroup*,
		       const IlSymbol*);

// --------------------------------------------------------------------------
// IlvStPrototypeSelField	A subclass of IlvStSelectionField that calls
//				its select callback on right-button.
// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvStGroupSelField : public IlvStSelectionField
{
public:
    IlvStGroupSelField(IlvDisplay*	display,
		       const IlvPoint&	at,
		       const char*	label,
		       IlUShort		thickness = IlvDefaultGadgetThickness,
		       IlvPalette*	palette   = 0)
	: IlvStSelectionField(display, at, label, thickness, palette)
	{}

    inline IlBoolean	isRightClick() { return(_rightClick); }

    virtual IlBoolean	handleEvent(IlvEvent& event);

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStGroupSelField);

protected:
    inline void		setRightClick(IlBoolean rightClick)
			{
			    _rightClick = rightClick;
			}

    static IlBoolean	_rightClick;
};

// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupFieldEditor: public IlvComboBox
{
public:
    IlvGroupFieldEditor(IlvGroupValueEditor*,
			IlvUserAccessor*,
			IlvMatrix*,
			const IlvRect&);
protected:
    virtual void		valueChanged() = 0;
    virtual void		makeMenu() = 0;
    IlvGroupValueEditor*	_editor;
    IlvUserAccessor*		_accessor;

public:
    static void			ChangedCallback(IlvGraphic*, IlAny);
    static void			MenuCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupTypeFieldEditor: public IlvGroupFieldEditor
{
public:
    IlvGroupTypeFieldEditor(IlvGroupValueEditor*	v,
			    IlvUserAccessor*		a,
			    IlvMatrix*			m,
			    const IlvRect&		r)
	: IlvGroupFieldEditor(v, a, m, r)
	{
	    makeMenu();
	    setEditable(IlFalse);
	}

protected:
    void	valueChanged();
    void	makeMenu();
};

// --------------------------------------------------------------------------
class ILVSTPRCLASS IlvGroupAttributeFieldEditor : public IlvGroupFieldEditor
{
public:
    IlvGroupAttributeFieldEditor(IlvGroupValueEditor*	v,
				 IlvUserAccessor*	a, 
				 IlUInt			param,
				 IlvMatrix*		m,
				 const IlvRect&		r);

   void		setLabel(const char*, IlBoolean redraw = IlFalse);
   void		setLabel(IlUShort pos, const char* label);
   IlBoolean	handleEvent(IlvEvent& event);
   static void	ChooseCallback(IlvGraphic*, IlAny arg);

protected:
    void	makeMenu();
    void	valueChanged();

    IlUInt			_param;
    const IlvValueTypeClass*	_type;
    IlString			_oldlbl;
    static IlBoolean		_matchingTypes;
    static IlBoolean		_immediate;
    static IlSymbol*		PropNoFocusOut;
};

IlvDECLAREINITSTPRCLASS(stp_prgadgets)

#endif
