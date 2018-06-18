// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/matrix.h
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
// Declaration of the IlvMatrix class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Matrix_H
#define __Ilv_Gadgets_Matrix_H

#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Gadgets_Amatrix_H)
#  include <ilviews/gadgets/amatrix.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#  include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Base_Alloc_H)
#  include <ilviews/base/alloc.h>
#endif
#if !defined(__Ilv_Base_View_H)
#  include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Gadgets_Itemgdt_H)
#  include <ilviews/gadgets/itemgdt.h>
#endif

class IlvMatrix;
class IlHashTable;
typedef IlUInt IlvMatrixProperty;

#define DeclareMatrixItemInfoRO_()					\
    static IlvAbstractMatrixItem* readItem(IlvInputFile&, IlvDisplay*);	\
    virtual IlvAbstractMatrixItem* copy() const

// --------------------------------------------------------------------------
#define DeclareMatrixItemInfoRO() IlvDeclarePropClassInfo();		\
	DeclareMatrixItemInfoRO_()
#define DeclareLazyMatrixItemInfoRO() IlvDeclareLazyPropClassInfo();	\
	DeclareMatrixItemInfoRO_()

#define DeclareMatrixItemInfo() DeclareMatrixItemInfoRO();		\
    virtual void write(IlvOutputFile&) const

#define DeclareLazyMatrixItemInfo() DeclareLazyMatrixItemInfoRO();	\
    virtual void write(IlvOutputFile&) const

#define DeclareMatrixItemIOConstructors(classname) public:		\
    classname(IlvDisplay* display, IlvInputFile& file);			\
    classname(const classname& source)

#define DeclareMItemClass_(classname)					\
ILV_MLK_DECL();								\
DeclareMatrixItemIOConstructors(classname);				\
virtual void setLabel(const char*, IlBoolean copy = IlTrue);		\
virtual const char* getLabel() const;					\
inline static const char* ClassName()					\
{ return classname::ClassInfo()->getClassName(); }			\
static IlUShort _classIdx;						\
inline static IlUShort ClassIdx()  { return _classIdx; }		\
virtual IlUShort classIdx() const

#define DeclareMItemClass(classname) DeclareMatrixItemInfo();		\
DeclareMItemClass_(classname)
#define DeclareLazyMItemClass(classname) DeclareLazyMatrixItemInfo();	\
DeclareMItemClass_(classname)

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvAbstractMatrixItem
    : public IlvValueInterface
{
    friend class IlvMatrix;
public:
    virtual ~IlvAbstractMatrixItem();

    virtual
    IlvAbstractMatrixItem*	copy() const;
    static
    IlvAbstractMatrixItem*	readItem(IlvInputFile& file,
					 IlvDisplay* display);
    virtual void	write(IlvOutputFile& file) const;
    virtual IlUShort	classIdx() const;
    virtual
    const char*		getLabel() const;
    virtual void	setLabel(const char* label, IlBoolean copy = IlTrue);
    virtual void	draw(const IlvMatrix*	matrix,
			     IlUShort		col,
			     IlUShort		row,
			     IlvPort*		dst,
			     const IlvRect&	bbox,
			     const IlvRect*	clip) const;
    void		drawLabel(const char*		label,
				  const IlvMatrix*	matrix,
				  IlUShort		col,
				  IlUShort		row,
				  IlvPort*		dst,
				  const IlvRect&	bbox,
				  const IlvRect*	clip = 0) const;
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setForeground(IlvColor* color);
    virtual void	setBackground(IlvColor* color);
    virtual void	setFont(IlvFont* font);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	minimumSize(const IlvMatrix*	matrix,
				    IlvDim&		width,
				    IlvDim&		height) const;
    virtual IlBoolean	handleSelectionDrawing() const;
    virtual IlvPalette*	getTextPalette(const IlvMatrix*) const;
    virtual IlvPalette*	getTextSelectedPalette(const IlvMatrix*) const;
    // I/O
    static
    IlvAbstractMatrixItem*	Read(IlvInputFile&,
				     IlvDisplay*,
				     IlvMatrixProperty&);
    static void		Write(IlvOutputFile&,
			      IlvAbstractMatrixItem*,
			      IlvMatrixProperty);
    // --- Value accessors ---
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_labelValue;
    static IlSymbol*	_paletteValue;
    static IlSymbol*	_foregroundValue;
    static IlSymbol*	_backgroundValue;
    static IlSymbol*	_fontValue;
    static IlSymbol*	_valueValue;
    static IlSymbol*	_formatValue;
    static IlSymbol*	_copyMethod;

    IlvDeclareLazyPropRootClassInfo();
    DeclareMatrixItemIOConstructors(IlvAbstractMatrixItem);

protected:
    IlvAbstractMatrixItem() {}
    static IlvPalette*	GetTextPalette(const IlvMatrix*);
    static IlvPalette*	GetTextSelectedPalette(const IlvMatrix*);
    virtual void	init(const IlvMatrix*, IlUShort, IlUShort);
    static void		computePalettesFromBG(IlvColor*,
					      IlvPalette*&,
					      IlvPalette*&);
    static void		computePalettesFromFG(IlvColor*,
					      IlvPalette*&,
					      IlvPalette*&);
    static void		computeInvertedPalette(const IlvPalette*,
					       IlvPalette*&);
    static void		computePaletteFromFont(IlvFont*,
					       IlvPalette*&,
					       IlvPalette*&);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvLabelMatrixItem
    : public IlvAbstractMatrixItem
{
public:
    IlvLabelMatrixItem(const char* label, IlBoolean copy = IlTrue);
    virtual ~IlvLabelMatrixItem();

    DeclareLazyMItemClass(IlvLabelMatrixItem);
    DeclareGraphicAccessors();

protected:
    char*		_label;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFilledLabelMatrixItem
    : public IlvLabelMatrixItem
{
public:
    IlvFilledLabelMatrixItem(IlvPalette*	palette,
			     const char*	label,
			     IlBoolean		copy = IlTrue);
    IlvFilledLabelMatrixItem(IlvMatrix*		matrix,
			     const char*	label,
			     IlBoolean		copy = IlTrue);
    IlvFilledLabelMatrixItem(const char*	label,
			     IlvPalette*	palette,
			     IlvPalette*	invpal,
			     IlBoolean		copy = IlTrue);
    ~IlvFilledLabelMatrixItem();

    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim&, IlvDim&) const;
    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    inline IlvPalette*	getPalette() const { return _palette; }
    inline IlvPalette*	getInvertedPalette() const { return _invertedPalette; }
    virtual IlvPalette*	getTextPalette(const IlvMatrix* m) const;
    virtual IlvPalette*	getTextSelectedPalette(const IlvMatrix* m) const;

    DeclareLazyMItemClass(IlvFilledLabelMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlvPalette*		_palette;
    IlvPalette*		_invertedPalette;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvBitmapMatrixItem
    : public IlvAbstractMatrixItem
{
public:
    IlvBitmapMatrixItem(IlvBitmap*	bitmap,
			IlBoolean	transparent = IlFalse,
			IlvPalette*	palette = 0);
    virtual ~IlvBitmapMatrixItem();

    inline IlvBitmap*	getBitmap() const { return _bitmap; }
    virtual void	setBitmap(IlvBitmap* bitmap);
    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    inline IlvPalette*	getPalette() const { return _palette; }
    inline IlBoolean	isTransparent() const { return _transparent; }
    inline void		setTransparent(IlBoolean val) { _transparent = val; }
    virtual void	minimumSize(const IlvMatrix*, IlvDim&, IlvDim&) const;

    DeclareLazyMItemClass(IlvBitmapMatrixItem);
    DeclareGraphicAccessors();

    static IlSymbol*	_bitmapValue;
    static IlSymbol*	_transparentValue;

protected:
    IlvPalette*		_palette;
    IlvBitmap*		_bitmap;
    IlBoolean		_transparent;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvIntMatrixItem
    : public IlvAbstractMatrixItem
{
public:
    inline IlvIntMatrixItem(IlInt value) { _int = value; }

    inline IlInt	getInt() const { return _int; }
    inline void		setInt(IlInt value) { _int = value; }

    DeclareLazyMItemClass(IlvIntMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlInt		_int;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFilledIntMatrixItem
    : public IlvIntMatrixItem
{
public:
    IlvFilledIntMatrixItem(IlvPalette* palette, IlInt value);
    IlvFilledIntMatrixItem(IlvMatrix* matrix,  IlInt value);
    IlvFilledIntMatrixItem(IlInt value,
			   IlvPalette* palette,
			   IlvPalette* invpal);
    ~IlvFilledIntMatrixItem();

    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim&, IlvDim&) const;

    inline IlvPalette*	getPalette() const { return _palette; }
    inline IlvPalette*	getInvertedPalette() const { return _invertedPalette; }
    virtual IlvPalette*	getTextPalette(const IlvMatrix*) const;
    virtual IlvPalette*	getTextSelectedPalette(const IlvMatrix*) const;

    DeclareLazyMItemClass(IlvFilledIntMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlvPalette*		_palette;
    IlvPalette*		_invertedPalette;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFloatMatrixItem
    : public IlvAbstractMatrixItem
{
public:
    inline IlvFloatMatrixItem(IlFloat value) { _float = value; }

    inline IlFloat	getFloat() const { return _float; }
    inline void		setFloat(IlFloat value) { _float = value; }
    virtual const char*	getFormat() const;

    DeclareLazyMItemClass(IlvFloatMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlFloat		_float;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDoubleMatrixItem
    : public IlvAbstractMatrixItem
{
public:
    inline IlvDoubleMatrixItem(IlDouble value) { _double = value; }

    inline IlDouble	getDouble() const { return _double; }
    inline void		setDouble(IlDouble value) { _double = value; }
    virtual const char*	getFormat() const;

    DeclareLazyMItemClass(IlvDoubleMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlDouble		_double;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFilledFloatMatrixItem
    : public IlvFloatMatrixItem
{
public:
    IlvFilledFloatMatrixItem(IlvPalette* palette, IlFloat value);
    IlvFilledFloatMatrixItem(IlvMatrix* matrix, IlFloat value);
    IlvFilledFloatMatrixItem(IlFloat		value,
			     IlvPalette*	palette,
			     IlvPalette*	invpal);
    ~IlvFilledFloatMatrixItem();

    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim&, IlvDim&) const;
    inline IlvPalette*	getPalette() const { return _palette; }
    inline IlvPalette*	getInvertedPalette() const { return _invertedPalette; }
    virtual IlvPalette*	getTextPalette(const IlvMatrix*) const;
    virtual IlvPalette*	getTextSelectedPalette(const IlvMatrix*) const;

    DeclareLazyMItemClass(IlvFilledFloatMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlvPalette*		_palette;
    IlvPalette*		_invertedPalette;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFilledDoubleMatrixItem
    : public IlvDoubleMatrixItem
{
public:
    IlvFilledDoubleMatrixItem(IlvPalette* palette, IlDouble value);
    IlvFilledDoubleMatrixItem(IlvMatrix* matrix, IlDouble value);
    IlvFilledDoubleMatrixItem(IlDouble		value,
			      IlvPalette*	palette,
			      IlvPalette*	invpal);
    ~IlvFilledDoubleMatrixItem();

    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim&, IlvDim&) const;
    inline IlvPalette*	getPalette() const { return _palette; }
    inline IlvPalette*	getInvertedPalette() const { return _invertedPalette; }
    virtual IlvPalette*	getTextPalette(const IlvMatrix*) const;
    virtual IlvPalette*	getTextSelectedPalette(const IlvMatrix*) const;

    DeclareLazyMItemClass(IlvFilledDoubleMatrixItem);
    DeclareGraphicAccessors();

protected:
    IlvPalette*		_palette;
    IlvPalette*		_invertedPalette;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvGraphicMatrixItem
    : public IlvAbstractMatrixItem
{
public:
    IlvGraphicMatrixItem(IlvGraphic* graphic)
	: IlvAbstractMatrixItem(), _graphic(graphic)
    {}
    virtual ~IlvGraphicMatrixItem();

    inline IlvGraphic*	getGraphic() const { return _graphic; }
    void		setGraphic(IlvGraphic* graphic);
    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim&, IlvDim&) const;
    virtual IlBoolean	handleSelectionDrawing() const;

    DeclareLazyMItemClass(IlvGraphicMatrixItem);
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_graphicValue;

protected:
    IlvGraphic*		_graphic;

    virtual void	init(const IlvMatrix*, IlUShort, IlUShort);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvGadgetMatrixItem
    : public IlvGraphicMatrixItem
{
public:
    IlvGadgetMatrixItem(IlvGadget* gadget);

    inline IlvGadget*	getGadget() const { return (IlvGadget*)_graphic; }
    void		setGadget(IlvGadget* gadget);
    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    inline IlBoolean	isInteractive() const { return _interactive; }
    inline void		setInteractive(IlBoolean val) { _interactive = val; }
    inline IlBoolean	hasFocus() const { return _hasFocus; }
    inline void		setFocus(IlBoolean i) { _hasFocus = i; }
    inline IlUShort	focusRow() { return _focusRow; }
    inline IlUShort	focusColumn() { return _focusColumn; }
    inline void		focusRow(IlUShort row) { _focusRow = row; }
    inline void		focusColumn(IlUShort col) { _focusColumn = col; }
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim& w,
				    IlvDim& h) const;

    DeclareLazyMItemClass(IlvGadgetMatrixItem);
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_interactiveValue;
    static IlSymbol*	_hasFocusValue;
    static IlSymbol*	_focusRowValue;
    static IlSymbol*	_focusColumnValue;

protected:
    IlUShort		_focusRow;
    IlUShort		_focusColumn;
    IlBoolean		_interactive;
    IlBoolean		_hasFocus;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvGadgetItemMatrixItem
    : public IlvAbstractMatrixItem
{
    friend class IlvMatrix;
public:
    IlvGadgetItemMatrixItem(IlvGadgetItem* item);
    virtual ~IlvGadgetItemMatrixItem();

    virtual void	draw(const IlvMatrix*,
			     IlUShort, IlUShort,
			     IlvPort*,
			     const IlvRect&,
			     const IlvRect*) const;
    inline
    IlvGadgetItem*	getItem() const { return _item; }
    virtual void	setPalette(IlvPalette*);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    void		getLocation(IlUShort&, IlUShort&) const;
    static void		GetLocation(IlvGadgetItem*,
				    IlUShort&, IlUShort&);
    virtual void	gadgetItemBBox(IlvRect&,
				       const IlvMatrix*,
				       const IlvRect&) const;
    virtual void	minimumSize(const IlvMatrix*,
				    IlvDim&, IlvDim&) const;
    virtual IlvPalette*	getTextPalette(const IlvMatrix*) const;
    virtual IlvPalette*	getTextSelectedPalette(const IlvMatrix*) const;

    DeclareLazyMItemClass(IlvGadgetItemMatrixItem);
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_locationSymbol;

protected:
    IlvGadgetItem*	_item;

    static void		SetLocation(IlvGadgetItem*,
				    IlUShort&,
				    IlUShort&);
    virtual IlBoolean	handleSelectionDrawing() const;
    virtual void	init(const IlvMatrix*, IlUShort, IlUShort);
};

// --------------------------------------------------------------------------
class IlvMatrixColumn
{
public:
    ILV_MLK_DECL();
    IlvMatrixColumn(IlUShort count)
    {
	_items = new IlvAbstractMatrixItem*[count];
	_properties = new IlvMatrixProperty[count];
    }
    IlvMatrixColumn()
    {
	_items = 0;
	_properties = 0;
    }
    ~IlvMatrixColumn()
    {
	delete [] _items;
	delete [] _properties;
    }

    void		init(IlUShort count);
    inline
    IlvAbstractMatrixItem** getItems() const { return _items; }
    inline
    IlvMatrixProperty*	getProperties() const { return _properties; }
    inline void		setItems(IlvAbstractMatrixItem** items)
			{
			    _items = items;
			}
    inline void		setProperties(IlvMatrixProperty* p)
			{
			    _properties = p;
			}

protected:
    IlvAbstractMatrixItem**	_items;
    IlvMatrixProperty*		_properties;

private:
    IlvMatrixColumn(const IlvMatrixColumn&); // No copy constructor
};

// --------------------------------------------------------------------------
typedef void (*IlvMatrixItemCallback)(IlvMatrix*, IlUShort, IlUShort, IlAny);

class ILVADVGDTEXPORTED IlvMatrixCallback
{
public:
    ILV_MLK_DECL();

    IlvMatrixCallback(IlvMatrixItemCallback c, IlAny a = 0)
	: _callback(c),
	  _clientData(a)
    {}

    inline 
    IlvMatrixItemCallback callback() const { return _callback; }
    inline IlAny	clientData() const { return _clientData; }
    inline void		set(IlvMatrixItemCallback c, IlAny a)
			{
			    _callback = c;
			    _clientData = a;
			}

protected:
    IlvMatrixItemCallback	_callback;
    IlAny			_clientData;
};

#define IlvDefaultMatrixWidth	60

#define IlvDefaultMatrixHeight	30

typedef void (*IlvMatrixChange)(IlvMatrix*);
IL_DEFINEFPTRTOANYCAST(IlvMatrixChange);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixItemEditor
{
public:
    IlvMatrixItemEditor(IlvMatrix* matrix, IlUShort col, IlUShort row);
    virtual ~IlvMatrixItemEditor();

    inline IlUShort	getColumn() const { return _col; }
    inline IlUShort	getRow() const { return _row; }
    inline IlvMatrix*	getMatrix() const { return _matrix; }
    virtual void	validate();
    virtual void	cancel();
    inline IlvGraphic*	getEditorField() const { return _editor; }
    virtual void	initFrom() const = 0;
    virtual void	applyTo() const = 0;
    virtual IlBoolean	handleEvent(IlvEvent& event);

protected:
    IlvGraphic*		_editor;
    IlUShort		_col;
    IlUShort		_row;
    IlvMatrix*		_matrix;
    inline void		setEditorField(IlvGraphic* g)
			{
			    delete _editor;
			    _editor = g;
			}
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultMatrixItemEditor
    : public IlvMatrixItemEditor
{
public:
    IlvDefaultMatrixItemEditor(IlvMatrix*	matrix,
			       IlUShort		col,
			       IlUShort		row,
			       IlvTextField*	tfd = 0);

    virtual void	initFrom() const;
    virtual void	applyTo() const;
    inline
    IlvTextField*	getTextField() const
			{
			    return (IlvTextField*)_editor;
			}
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixItemEditorFactory
    : public IlvNamedProperty
{
public:
    IlvMatrixItemEditorFactory();
    virtual ~IlvMatrixItemEditorFactory();

    static IlvMatrixItemEditorFactory*	Get(const IlvMatrix* matrix);
    static
    IlvMatrixItemEditorFactory*	Set(IlvMatrix*			matrix,
				    IlvMatrixItemEditorFactory*	factory);
    virtual
    IlvMatrixItemEditor*	createEditor(IlvMatrix* matrix,
					     IlUShort	col,
					     IlUShort	row) const;

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvMatrixItemEditorFactory);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvMatrixLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawFocus(const IlvMatrix*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeFocusRegion(const IlvMatrix*,
					   IlvRegion&,
					   const IlvTransformer*) const = 0;
    virtual IlvPalette*	getWindowBackground(const IlvMatrix* matrix) const=0;
    virtual void	drawBackground(const IlvMatrix* matrix,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvMatrix*	matrix,
				  IlvPort*		dst,
				  const IlvTransformer* t,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawRelief(const IlvMatrix*	matrix,
				   IlUShort		colno,
				   IlUShort		rowno,
				   IlvPort*		dst,
				   const IlvRect&	rect,
				   const IlvRect*	clip) const = 0;
    virtual void	drawSelection(const IlvMatrix*	matrix,
				      IlvPort*		dst,
				      const IlvRect&	rect,
				      const IlvRect*	clip) const = 0;
    virtual void	drawItem(const IlvMatrix*	matrix,
				 IlvPort*		dst,
				 IlUShort		colno,
				 IlUShort		rowno,
				 const IlvRect&		itembbox,
				 const IlvRect&		clip) const = 0;
    virtual void	internalBBox(const IlvMatrix*,
				     IlvRect&,
				     const IlvTransformer*) const = 0;
    virtual IlvDim	getReliefThickness(const IlvMatrix*) const = 0;
    virtual IlvPalette*	getSelectionPalette(const IlvMatrix* matrix) const=0;
    virtual IlvPalette*	getTextPalette(const IlvMatrix*) const = 0;
    virtual void	setMode(IlvMatrix*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvMatrix*, IlBoolean) const = 0;
    virtual IlBoolean	handleMatrixEvent(IlvMatrix*	matrix,
					  IlvEvent&	event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultMatrixLFHandler
    : public IlvMatrixLFHandler
{
public:
    IlvDefaultMatrixLFHandler(IlvLookFeelHandler* lf)
	: IlvMatrixLFHandler(lf)
    {}

    virtual void	drawFocus(const IlvMatrix*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeFocusRegion(const IlvMatrix*,
					   IlvRegion&,
					   const IlvTransformer*) const;
    virtual IlvPalette*	getWindowBackground(const IlvMatrix*) const;
    virtual void	drawBackground(const IlvMatrix*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvMatrix*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawItem(const IlvMatrix*,
				 IlvPort*,
				 IlUShort, IlUShort,
				 const IlvRect&,
				 const IlvRect&) const;
    virtual void	internalBBox(const IlvMatrix*,
				     IlvRect&,
				     const IlvTransformer*) const;
    virtual IlBoolean	handleMatrixEvent(IlvMatrix*, IlvEvent&) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrix
    : public IlvAbstractMatrix,
      public IlvGadgetItemHolder
{
    friend class IlvDefaultMatrixLFHandler;
public:
    IlvMatrix(IlvDisplay*	display,
	      const IlvRect&	rect,
	      IlUShort		nbcol,
	      IlUShort		nbrow,
	      IlvDim		xgrid     = IlvDefaultMatrixWidth,
	      IlvDim		ygrid     = IlvDefaultMatrixHeight,
	      IlvDim		thickness = IlvDefaultGadgetThickness,
	      IlvPalette*	palette   = 0);
    ~IlvMatrix();

    virtual
    IlvGadgetItem*	applyToItems(IlvApplyGadgetItem, IlAny);
    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;
    virtual IlBoolean	usesDefaultButtonKeys() const;
    // Palettes
    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    IlBoolean		rowSameHeight() const;
    IlBoolean		columnSameWidth() const;
    IlvDim		getRowHeight(IlUShort) const;
    IlvDim		getColumnWidth(IlUShort) const;
    IlvDim		getRowPosition(IlUShort) const;
    IlvDim		getColumnPosition(IlUShort) const;
    IlvDim		getColumnsDistance(IlUShort,
					   IlUShort) const;
    IlvDim		getRowsDistance(IlUShort,
					IlUShort) const;
    inline IlUShort	columns() const { return _columns; }
    inline IlUShort	rows() const    { return _rows; }
    inline IlvDim	getCardinal() const { return _columns*_rows; }
    inline IlBoolean	isAutoFittingToSize() const { return _autoFitToSize; }
     inline IlBoolean	autoFitToSize(IlBoolean value)
			{
			    _autoFitToSize = value;
			    return value;
			}
    inline IlUShort	getSpacing() const { return _spacing; }
    inline void		setSpacing(IlUShort spacing) { _spacing = spacing; }
    inline IlvDim	getXgrid() const { return _xgrid; }
    virtual void	setXgrid(IlvDim x);
    inline IlvDim	getYgrid() const { return _ygrid; }
    virtual void	setYgrid(IlvDim y);
    inline void		sameWidth(IlBoolean value) { _sameWidth = value; }
    inline void		sameHeight(IlBoolean value) { _sameHeight = value; }
    inline IlBoolean	isExclusive() const { return _exclusive; }
    inline void		setExclusive(IlBoolean value) { _exclusive = value; }
    virtual void	set(IlUShort			col,
			    IlUShort			row,
			    IlvAbstractMatrixItem*	item);
    virtual void	add(IlvAbstractMatrixItem* item);
    virtual IlBoolean	remove(IlUShort		col,
			       IlUShort		row,
			       IlBoolean	destroy = IlTrue);
    virtual void	itemBBox(IlUShort		col,
				 IlUShort		row,
				 IlvRect&		bbox,
				 const IlvTransformer*	t = 0) const;
    virtual void	borderBBox(IlUShort, IlUShort,
				   IlvRect&,
				   const IlvTransformer* t = 0) const;
    virtual void	itemsBBox(IlUShort, IlUShort,
				  IlUShort, IlUShort,
				  IlvRect&,
				  const IlvTransformer* = 0) const;
    inline IlBoolean	isAdjustingLast() const { return _adjustLast; }
    IlBoolean		adjustLast(IlBoolean value);
    void		setGridPalette(IlvPalette* palette);
    IlvPalette*		getGridPalette() const;
    virtual void	drawItem(IlvPort*,
				 IlUShort, IlUShort,
				 const IlvRect&,
				 const IlvRect&) const;

    void		reDrawItem(IlUShort,
				   IlUShort,
				   IlvPort*,  // 2.21 compatibility
				   const IlvTransformer* = 0) const;
    void		reDrawItem(IlUShort col, IlUShort row) const;
    virtual IlvAbstractMatrixItem*
			pointToItem(const IlvPoint&		point,
				    IlUShort&			col,
				    IlUShort&			row,
				    const IlvTransformer*	t = 0) const;
    virtual void	deSelect();
    virtual void	setColumnSize(IlUShort, IlvDim);
    virtual void	setRowSize(IlUShort, IlvDim);
    inline IlvDim	columnSize(IlUShort i) const // 2.1 compatibility
			{
			    return (IlvDim)(_colsize[i + 1] - _colsize[i]);
			}
    inline IlvDim	rowSize(IlUShort i) const // 2.1 compatibility
			{
			    return (IlvDim)(_rowsize[i + 1] - _rowsize[i]);
			}
    inline IlvDim	columnPosition(IlUShort i) const // 2.1 compatibility
			{
			    return _colsize[i];
			}
    inline IlvDim	rowPosition(IlUShort i) const // 2.1 compatibility
			{
			    return _rowsize[i];
			}
    virtual void	setRowSelected(IlUShort		row,
				       IlBoolean	selected = IlTrue);
    virtual void	setColumnSelected(IlUShort	col,
					  IlBoolean	selected = IlTrue);
    IlvAbstractMatrixItem*	getItem(IlUShort col, IlUShort row) const;
    IlvAbstractMatrixItem*	getItem(IlvDim pos) const;
    IlBoolean		isItemSelected(IlUShort col, IlUShort row) const;
    virtual void	setItemSelected(IlUShort	col,
					IlUShort	row,
					IlBoolean	selected = IlTrue);
    IlvPosition		getItemAlignment(IlUShort col, IlUShort row) const;
    void		setItemAlignment(IlUShort	col,
					 IlUShort	row,
					 IlvPosition	alignment);
    IlBoolean		isItemSensitive(IlUShort col, IlUShort row) const;
    void		setItemSensitive(IlUShort	col,
					 IlUShort	row,
					 IlBoolean	value = IlTrue);
    IlBoolean		isItemGrayed(IlUShort col, IlUShort row) const;
    void		setItemGrayed(IlUShort	col,
				      IlUShort	row,
				      IlBoolean	value = IlTrue);
    IlBoolean		isItemFillingBackground(IlUShort col,
						IlUShort row) const;
    void		setItemFillingBackground(IlUShort  col,
						 IlUShort  row,
						 IlBoolean value = IlTrue);
    IlBoolean		isItemReadOnly(IlUShort col, IlUShort row) const;
    void		setItemReadOnly(IlUShort	col,
					IlUShort	row,
					IlBoolean	value = IlTrue);
    IlBoolean		isItemRelief(IlUShort col, IlUShort row) const;
    void		setItemRelief(IlUShort	col,
				      IlUShort	row,
				      IlBoolean	value = IlTrue);
    IlAny		getItemData(IlUShort col, IlUShort row) const;
    void		setItemData(IlUShort col, IlUShort row, IlAny data);
    IlvMatrixCallback*	getItemCallback(IlUShort, IlUShort) const;
    void		setItemCallback(IlUShort		col,
					IlUShort		row,
					IlvMatrixItemCallback	callback = 0,
					IlAny			data = 0);
    IlBoolean		getFirstSelected(IlUShort& col, IlUShort& row) const;
    inline void		fitToSize()
			{
			    fitWidthToSize();
			    fitHeightToSize();
			}
    virtual void	fitWidthToSize(IlUShort col = 0);
    virtual void	fitHeightToSize(IlUShort row = 0);
    virtual void	insertColumn(IlUShort col = 0, IlUShort count = 1);
    virtual void	insertRow(IlUShort row = 0, IlUShort count = 1);
    virtual void	removeColumn(IlUShort	col,
				     IlBoolean	destroy = IlTrue);
    virtual void	removeRow(IlUShort row, IlBoolean destroy = IlTrue);
    virtual void	reinitialize(IlUShort cols, IlUShort rows);
    inline void		reinitialise(IlUShort col, IlUShort row)
			{
			    reinitialize(col, row);
			}
    inline void		visible(IlUShort&		fromcol,
				IlUShort&		tocolr,
				IlUShort&		fromrow,
				IlUShort&		torow,
				const IlvTransformer*	t = 0) // 2.0 compat.
			{
			    getVisibleItems(fromcol,
					    tocolr,
					    fromrow,
					    torow,
					    t);
			}
    virtual void	drawRelief(IlUShort		col,
				   IlUShort		row,
				   IlvPort*		dst,
				   const IlvRect&	bbox,
				   const IlvRect*	clip) const;
    virtual void	drawSelection(IlUShort		col,
				      IlUShort		row,
				      IlvPort*		dst,
				      const IlvRect&	bbox,
				      const IlvRect*	clip) const;
    inline void		getLastSelectedItem(IlUShort& col,
					    IlUShort& row) const
			{
			    col = _lastSelectedColumn;
			    row = _lastSelectedRow;
			}
    void		setLastSelectedItem(IlUShort, IlUShort);
    inline
    IlvTextField*	getEditedItem(IlUShort& col, IlUShort& row) const
			{
			    col = _editedColumn;
			    row = _editedRow;
			    return getTextField();
			}
    inline
    IlBoolean		editedWithMouse() const { return _editedWithMouse; }
    inline void		setEditedItem(IlUShort col, IlUShort row)
			{
			    _editedColumn = col;
			    _editedRow = row;
			}
    virtual
    IlvTextField*	createEditionField(IlUShort col, IlUShort row);
    inline
    static IlSymbol*	ActivateMatrixItemCallbackType()
			{
			    return _activateMatrixItemSymbol;
			}
    virtual void	activateMatrixItem(IlUShort col, IlUShort row);
    virtual
    IlvMatrixItemEditor* createEditor(IlUShort col, IlUShort row);
    void		showEditorField();
    void		hideEditorField();
    inline IlvGraphic*	getEditorField() const
			{
			    return _editor ? _editor->getEditorField() : 0;
			}
    inline IlvMatrixItemEditor*	getEditor() const { return _editor; }
    inline void		showTextField() { showEditorField(); }
    inline void		hideTextField() { hideEditorField(); }
    inline
    IlvTextField*	getTextField() const 
			{
			    IlvGraphic* editor = getEditorField();
			    return editor && editor->
				isSubtypeOf(IlvTextField::ClassInfo())
				? (IlvTextField*)editor
				: 0;
			}
    IlBoolean		hasToolTips() const;
    void		useToolTips(IlBoolean value = IlTrue);
    IlBoolean		allowDragDrop() const;
    void		allowDragDrop(IlBoolean value);
    IlBoolean		allowEditOnDoubleClick() const;
    void		allowEditOnDoubleClick(IlBoolean value);
    inline IlBoolean	isEditAllowed() const { return _allowEdit; }
    virtual IlBoolean	isEditable() const;
    inline IlBoolean	allowEdit(IlBoolean value)
			{
			    _allowEdit = value;
			    return value;
			}
    virtual IlBoolean	isShowingLabel() const;
    void		showLabel(IlBoolean value = IlTrue,
				  IlBoolean redraw = IlTrue);
    virtual IlBoolean	isShowingPicture() const;
    void		showPicture(IlBoolean value = IlTrue,
				    IlBoolean redraw = IlTrue);
    virtual IlvPosition	getLabelPosition() const;
    void		setLabelPosition(IlvPosition position,
					 IlBoolean redraw = IlTrue);
    virtual void	getLabelOrientation(IlvOrientation&	orientation,
					    IlBoolean&		flip) const;
    void		setLabelOrientation(IlvOrientation orientation,
					    IlBoolean flip = IlFalse,
					    IlBoolean redraw = IlTrue);
    IlvDim		getColumnFittingSize(IlUShort col) const;
    IlvDim		getRowFittingSize(IlUShort row) const;
    virtual const char*	getDefaultInteractor() const;
    virtual void	setHolder(IlvGraphicHolder*);

    // Event handling methods
    virtual IlBoolean	handleMatrixEvent(IlvEvent&);
    virtual void	validate();
    virtual void	editItem(IlUShort col, IlUShort row);
    virtual void	doIt();
    IlBoolean		isBrowseMode() const;
    void		setBrowseMode(IlBoolean value);
    IlBoolean		isDirectEditionMode() const;
    void		setDirectEditionMode(IlBoolean value);
    inline IlvDirection	getEditDirection() const { return _editDirection; }
    inline void		setEditDirection(IlvDirection direction)
			{
			    _editDirection = direction;
			}
    IlBoolean		isAutoLineSelect() const;
    void		setAutoLineSelect(IlBoolean value);
    IlBoolean		isAutoColumnSelect() const;
    void		setAutoColumnSelect(IlBoolean value);
    inline
    IlvOrientation	getExtendedSelectionOrientation() const
			{
			    return _extendedSelOrientation;
			}
    inline void		setExtendedSelectionOrientation(IlvOrientation dir)
			{
			    _extendedSelOrientation  = dir;
			}
    virtual void	resizeColumn(IlUShort col, IlvDim size);
    virtual void	resizeRow(IlUShort row, IlvDim size);
    // *** The following functions are obsolete ***
    inline void		addCallback(IlvMatrixChange cb)
			{
			    _callbacks.append((IlAny)
					      IL_FPTRTOANYCAST(IlvMatrixChange)
					      (cb));
			}
    inline void		removeCallback(IlvMatrixChange cb)
			{
			    _callbacks.remove((IlAny)
					      IL_FPTRTOANYCAST(IlvMatrixChange)
					      (cb));
			}
    inline
    IlvMatrixColumn*	matrixColumns() { return _matrixColumns;}
    virtual void	apply(IlvApplyObject, IlAny);
    virtual void	drawGadgetContents(IlvPort*,
					   const IlvTransformer* = 0,
					   const IlvRegion* = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual void	scrollBarVisibilityChanged(IlvDirection);
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	invert(IlBoolean);
    virtual void	setPalette(IlvPalette*);
    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    inline IlvDim	columnPosition(IlUShort i, IlvDim v)
			{
			    _colsize[i] = v;
			    return v;
			}
    inline IlvDim	rowPosition(IlUShort i, IlvDim v)
			{
			    _rowsize[i] = v;
			    return v;
			}
    IlvAbstractMatrixItem**	getItemLocation(IlUShort, IlUShort) const;
    IlvMatrixProperty*	getItemProperty(IlUShort, IlUShort) const;
    IlvAbstractMatrixItem*	getSelection(IlUShort&, IlUShort&) const;
    inline
    IlvGraphicHolder*	getInternalHolder() const { return _matrixHolder; }
    inline
    IlvGadgetMatrixItem*	getFocusItem() const { return _focusItem; }
    inline void		setFocusItem(IlvGadgetMatrixItem* item)
			{
			    _focusItem = item;
			}
    void		setFocus(IlUShort col, IlUShort row);
    void		setFocus(IlvGadgetMatrixItem*,
				 IlUShort,
				 IlUShort);

    virtual IlvPalette*	getWindowBackground() const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	internalBBox(IlvRect&,
				     const IlvTransformer*) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer*) const;
    void		focusIn();
    void		focusOut();
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    //palettes
    IlvPalette*		getTextPalette(IlvMatrix*);
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;
    void		selectNextItem();
    void		selectNextItem(IlvDirection);
    void		selectItem(IlUShort, IlUShort, IlBoolean = IlTrue);
    virtual void	deSelectAll();
    virtual void	changeSelectionTo(IlUShort col, IlUShort row);
    inline void		setSelectionAnchor(IlUShort col, IlUShort row)
			{
			    _startSelectionColumn = col;
			    _startSelectionRow = row;
			}
    virtual void	extendSelection(IlUShort col, IlUShort row);

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_itemsValue;
    static IlSymbol*	_selectedItemsValue;
    static IlSymbol*	_adjustLastValue;
    static IlSymbol*	_columnSizesValue;
    static IlSymbol*	_rowSizesValue;
    static IlSymbol*	_spacingValue;
    static IlSymbol*	_exclusiveValue;
    static IlSymbol*	_autoFitToSizeValue;
    static IlSymbol*	_allowEditionValue;
    static IlSymbol*	_editedColumnValue;
    static IlSymbol*	_editedRowValue;
    static IlSymbol*	_browseSelectValue;
    static IlSymbol*	_editDirectionValue;
    static IlSymbol*	_extendedSelOrientationValue;
    static IlSymbol*	_autoLineSelectValue;
    static IlSymbol*	_autoColumnSelectValue;
    static IlSymbol*	_gridColorValue;
    static IlSymbol*	_directEditModeValue;
    static IlSymbol*	_editOnDoubleClickValue;
    static IlSymbol*	_XgridValue;
    static IlSymbol*	_YgridValue;
    static IlSymbol*	_editorFieldValue;
    static IlSymbol*	_textFieldValue;
    static IlSymbol*	_setMethod;
    static IlSymbol*	_addMethod;
    static IlSymbol*	_removeMethod;
    static IlSymbol*	_itemBBoxMethod;
    static IlSymbol*	_deSelectMethod;
    static IlSymbol*	_columnPositionMethod;
    static IlSymbol*	_rowPositionMethod;
    static IlSymbol*	_columnSizeMethod;
    static IlSymbol*	_rowSizeMethod;
    static IlSymbol*	_resizeColumnMethod;
    static IlSymbol*	_resizeRowMethod;
    static IlSymbol*	_selectColumnMethod;
    static IlSymbol*	_selectRowMethod;
    static IlSymbol*	_selectItemMethod;
    static IlSymbol*	_isItemSelectedMethod;
    static IlSymbol*	_getItemMethod;
    static IlSymbol*	_getItemAlignmentMethod;
    static IlSymbol*	_setItemAlignmentMethod;
    static IlSymbol*	_isItemSensitiveMethod;
    static IlSymbol*	_setItemSensitiveMethod;
    static IlSymbol*	_isItemGrayedMethod;
    static IlSymbol*	_setItemGrayedMethod;
    static IlSymbol*	_isItemFillingBackgroundMethod;
    static IlSymbol*	_setItemFillingBackgroundMethod;
    static IlSymbol*	_isItemReadOnlyMethod;
    static IlSymbol*	_setItemReadOnlyMethod;
    static IlSymbol*	_isItemReliefMethod;
    static IlSymbol*	_setItemReliefMethod;
    static IlSymbol*	_fitToSizeMethod;
    static IlSymbol*	_insertColumnMethod;
    static IlSymbol*	_insertRowMethod;
    static IlSymbol*	_removeColumnMethod;
    static IlSymbol*	_removeRowMethod;
    static IlSymbol*	_reinitializeMethod;
    static IlSymbol*	_getEditedItemMethod;
    static IlSymbol*	_setEditedItemMethod;
    static IlSymbol*	_showEditorFieldMethod;
    static IlSymbol*	_hideEditorFieldMethod;
    static IlSymbol*	_showTextFieldMethod;
    static IlSymbol*	_hideTextFieldMethod;
    static IlSymbol*	_setFocusMethod;
    static IlSymbol*	_activateMatrixItemSymbol;

    DeclareLazyTypeInfo();

    IlvMatrix(const IlvMatrix&);
    IlvMatrix(IlvInputFile&, IlvPalette*, IlBoolean = IlFalse);
protected:
    IlvMatrixColumn*		_matrixColumns;
    IlUShort			_columns;
    IlUShort			_rows;
    IlvDim*			_colsize;
    IlvDim*			_rowsize;
    IlBoolean			_sameWidth;
    IlBoolean			_sameHeight;
    IlUShort			_spacing;
    IlHashTable*		_clientdata;
    IlvDim			_xgrid;
    IlvDim			_ygrid;
    IlBoolean			_exclusive;
    IlBoolean			_autoFitToSize;
    IlList			_callbacks;
    IlUShort			_editedColumn;
    IlUShort			_editedRow;
    IlvMatrixItemEditor*	_editor;
    IlBoolean			_allowEdit;
    IlBoolean			_adjustLast;
    IlvGadgetMatrixItem*	_focusItem;
    IlvAbstractMatrixItem*	_lastItemIn;
    IlvAbstractMatrixItem*	_lastClickedItem;
    IlUShort			_lastSelectedColumn;
    IlUShort			_lastSelectedRow;
    IlUShort			_startSelectionColumn;
    IlUShort			_startSelectionRow;
    IlvDirection		_editDirection;
    IlvPalette*			_gridPalette;
    IlvOrientation		_extendedSelOrientation;
    IlBoolean			_editedWithMouse;
    IlBoolean			_allowEditOnButtonUp;
    IlBoolean			_sendToGadget;
    IlBoolean			_adjustEnabled;
    IlBoolean			_callSelect;
    IlvPosition			_labelPosition;
    IlvPosition			_labelOrientation;
    IlBoolean			_flipLabel;
    IlvPoint			_pointDragged;
    IlvPoint			_deltaDrag;
    IlBoolean			_beginDrag;
    IlvGraphicHolder*		_matrixHolder;

    IlBoolean		iHandleMatrixEvent(IlvEvent&);
    void		clean();
    void		init(IlUShort,IlUShort);
    // event handlng methods
    void		removeToolTipHandler();
    void		restoreToolTipHandler();
    void		iCallValidate();
    void		iCallEditItem(IlUShort, IlUShort);
    void		endEdit(IlvGadgetItem*);
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);
    inline void		allowInvalidateItem(IlBoolean allow)
			{
			    _adjustEnabled = allow;
			}
    IlBoolean		allowInvalidateItem() const;
    virtual void	itemActivated(IlvGadgetItem*);
    virtual void	prepareItemEdition(IlvGadgetItem*,
					   IlvView*&,
					   IlvRect&,
					   IlvRect&,
					   IlvPalette*&);
    virtual void	prepareToolTip(IlvGadgetItem*,
				       IlvView*&,
				       IlvRect&,
				       IlvPalette*&);
    virtual void	drawSelection(IlvPort*,
				      const IlvRect&,
				      const IlvGadgetItem*,
				      const IlvTransformer* = 0,
				      const IlvRegion* = 0) const;
private:
    IlvTimer*		_matrixEditTimer;

    void		requestEditMatrixItem(IlUShort, IlUShort);
    void		cancelEditMatrixItem();
};

// --------------------------------------------------------------------------
extern ILVADVGDTEXPORTEDVAR(IlvValueTypeClass*)
IlvValueMatrixItemArrayType;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvValueMatrixItemArrayTypeClass
    : public IlvValueTypeClass
{
public:
    IlvValueMatrixItemArrayTypeClass();

    virtual const char*	name() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual void	deleteValue(IlvValue&) const;
    virtual void	copy(IlvValue&, const IlvValue&) const;
    static IlvAbstractMatrixItem**	MatrixItemArray(const IlvValue&,
							IlUShort&,
							IlUShort&);
    static void		SetValue(IlvValue&,
				 IlUShort, IlUShort,
				 IlvAbstractMatrixItem**);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvValueMatrixItemArrayValue
{
    IlvValueMatrixItemArrayValue(IlUShort, IlUShort,
				 IlvAbstractMatrixItem**);
    ~IlvValueMatrixItemArrayValue();

    friend class IlvValueMatrixItemArrayTypeClass;

    IlvAbstractMatrixItem**	_array;
    IlUShort			_columns;
    IlUShort			_rows;
};

// --------------------------------------------------------------------------
typedef IlvAbstractMatrixItem* (* IlvMatrixItemConstructor)(IlvInputFile&,
							    IlvDisplay*);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixItemClassInfo
    : public IlvValuedClassInfo
{
public:
    inline IlvMatrixItemConstructor getConstructor() const
	{ return _constructor; }
    static IlvMatrixItemClassInfo*  Create(const char*, IlvClassInfo**,
					   IlvMatrixItemConstructor,
					   IlvGetAccessorsFunction = 0);
protected:
    IlvMatrixItemClassInfo(const char*			className,
			   IlvClassInfo**		superClass,
			   IlvMatrixItemConstructor	constructor,
			   IlvGetAccessorsFunction	getAccessors = 0)
	: IlvValuedClassInfo(className, superClass, getAccessors),
	  _constructor(constructor)
    {}
    IlvMatrixItemConstructor	_constructor;
};

#define IlvRegisterMatrixItemClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
        IlvMatrixItemClassInfo::Create(#classname,			\
                                   superclass::ClassPtr(),		\
                                   (IlvMatrixItemConstructor)		\
                                   classname::readItem,			\
                                   classname::GetAccessors))

#define IlvPostRegisterMatrixItemClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
        IlvMatrixItemClassInfo::Create(#classname,			\
                                   superclass::ClassPtr(),		\
                                   (IlvMatrixItemConstructor)		\
                                   classname::readItem,			\
                                   classname::GetAccessors))

#define IlvPredefinedMatrixItemIOMembers(classname)			\
IlvAbstractMatrixItem*							\
classname::copy() const							\
{ return new classname(*this); }					\
IlvAbstractMatrixItem*							\
classname::readItem(IlvInputFile& i, IlvDisplay* display)		\
{ return new classname(display, i); }

#define IlvPredefinedMItemIOMembers(classname)				\
IlvPredefinedMatrixItemIOMembers(classname);				\
IlUShort classname::classIdx() const { return _classIdx; }		\
IlUShort classname::_classIdx;						\
ILV_MLK_DEF(classname)

#define IlvPreRegisterMatrixItemClass(classname)			\
	ILVPREDEFINECLASSINFOMEMBERS(classname)

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixSelectorInteractor
    : public IlvInteractor
{
public:
    IlvMatrixSelectorInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*,
				    IlvEvent&,
				    const IlvTransformer*);
    virtual IlBoolean	accept(const IlvGraphic*) const;

    DeclareInteractorTypeInfoRO(IlvMatrixSelectorInteractor);
protected:
    IlUShort			_downcol;
    IlUShort			_downrow;
    IlUShort			_prevcol;
    IlUShort			_prevrow;
    IlvAbstractMatrixItem*	_downimage;
    IlvAbstractMatrixItem*	_prevsel;

    virtual void	callCallback(IlvMatrix*	matrix,
				     IlUShort	col,
				     IlUShort	row);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHMatrixInteractor
    : public IlvHGadgetInteractor
{
public:
    virtual void	validate(IlvMatrix*) = 0;
    virtual void	editItem(IlvMatrix*, IlUShort, IlUShort) = 0;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(matrix);
ILVADVGDTMODULEINIT(matxitem);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/matrix.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/matrix.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/matrix.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/matrix.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Matrix_H */
