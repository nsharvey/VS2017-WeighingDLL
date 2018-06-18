// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/gadgets/gengadg.h
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
// Declaration of the IlvDvGenericGadget class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Gadgets_Gengadg_H)
#define __Ilv_Appframe_Gadgets_Gengadg_H

#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif

class ILVGDTEXPORTED IlvListGadgetItemHolder;
class ILVGDTEXPORTED IlvNotebook;
class ILVGDTEXPORTED IlvScrolledComboBox;
class ILVGDTEXPORTED IlvStringList;
class ILVGDTEXPORTED IlvScrolledComboBox;
class ILVDVCLASS IlvCheckedStringList;
class ILVGDTEXPORTED IlvGadgetItem;
class ILVDSPEXPORTED IlvBitmap;
class ILVGDTEXPORTED IlvTextField;
class ILVGDTEXPORTED IlvNumberField;
class ILVGDTEXPORTED IlvFileSelectorField;
class ILVGDTEXPORTED IlvSpinBox;
class ILVGDTEXPORTED IlvButton;
class ILVGDTEXPORTED IlvToggle;
class ILVVWSEXPORTED IlvGadget;
class ILVGDTEXPORTED IlvTreeGadget;
class ILVGDTEXPORTED IlvTreeGadgetItem;
class ILVDVCLASS IlvDvAcceleratorTextField;
class ILVDVCLASS IlvCheckedStringList;
class ILVVWSEXPORTED IlvGraphic;
class ILVGDTEXPORTED IlvTreeGadgetItem;
class ILVDSPEXPORTED IlvBitmap;
class ILVVWSEXPORTED IlvGadget;
class ILVGDTEXPORTED IlvListGadgetItemHolder;
class ILVGDTEXPORTED IlvText;
class ILVGDTEXPORTED IlvMessageLabel;
class ILVVWSEXPORTED IlvIcon;
class ILVDVCLASS IlvCheckedTreeGadget;
class ILVGDTEXPORTED IlvGadgetItemHolder;
class ILVVWSEXPORTED IlvGraphicHolder;

// --------------------------------------------------------------------------
// IlvDvGenericGadget class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvGenericGadget
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvGenericGadget(IlvGraphic* = 0);
    ~IlvDvGenericGadget();

    // ----------------------------------------------------------------------
    void set(IlvGraphic*);
    enum Type { NONE,
	        TEXTFIELD,
	        NUMFIELD,
	        TOGGLE,
	        STRINGLIST,
	        COMBOBOX,
	        CHECKED_STRINGLIST,
	        TREEGADGET,
		CHECKED_TREEGADGET,
	        FILE_SELECTORFIELD,
	        SPINBOX,
		ACCELERATORFIELD,
		MESSAGELABEL,
		TEXT,
		ICON,
	        GRAPHIC };
    Type getType() const { return _type; }
    IlvGadget*			getGadget() const;
    IlvTextField*		getTextField() const;
    IlvNumberField*		getNumberField() const;
    IlvToggle*			getToggle() const;
    IlvStringList*		getStringList() const;
    IlvScrolledComboBox*	getComboBox() const;
    IlvCheckedStringList*	getCheckedStringList() const;
    IlvTreeGadget*		getTreeGadget() const;
    IlvCheckedTreeGadget*	getCheckedTreeGadget() const;
    IlvFileSelectorField*	getFileSelector() const;
    IlvSpinBox*			getSpinBox() const;
    IlvGraphic*			getGraphic() const;
    IlvDvAcceleratorTextField*	getAcceleratorField() const;
    IlvText*			getText() const;
    IlvMessageLabel*		getMessageLabel() const;
    IlvIcon*			getIcon() const;

    inline IlBoolean	isValid() const 
			{
			    return getGraphic()? IlTrue : IlFalse;
			}
    IlvGraphicHolder*	getGraphicHolder() const;

    // Value management
    void		setValue(const IlvValue&);
    void		getValue(IlvValue&) const;

    // Label management
    const char*		getLabel() const;
    void		setLabel(const char*);

    // Abstract list management (StringList and trees)
    IlvGadgetItem*	getLastSelectedItem() const;
    IlvGadgetItem*	getFirstVisibleItem() const;
    IlvGadgetItem*	getLastVisibleItem(IlBoolean entireVis= IlTrue) const;
    IlUInt		getIndex(IlvGadgetItem*) const;
    IlUInt		getLabelIndex(const char*) const;
    void		visibleBBox(IlvRect&) const;
    void		setFirstVisibleIndex(IlUInt);
    IlUInt		getItemsCount() const;
    IlvGadgetItem*	pointToItem(const IlvPoint&) const;
    void		removeAllItems(IlBoolean = IlTrue);

    // List management
    IlvListGadgetItemHolder*	getListHolder() const;
    IlUShort			getSelection() const;
    void			setSelected(IlUShort);
    void			setSelected(const char*);
    IlUShort			findString(const char*) const;
    void			fitToContents();
    IlUShort			getCardinal() const;
    void			ensureVisible(IlUShort,
					      IlBoolean redraw = IlTrue,
					      IlBoolean horizontally = IlFalse);

    // List Drag / drop management
    IlvGadgetItemHolder*	getGadgetItemHolder() const;
    IlvGadgetItem*	getDragDropTarget() const;
    void		setDragDropTarget(IlvGadgetItem*);

    // Sensitivity management
    void		setSensitive(IlBoolean,
				     IlBoolean bReDraw = IlTrue);
    IlBoolean		isSensitive() const;

    // Activity management
    void		setActive(IlBoolean);
    IlBoolean		isActive() const;

    // Editable
    void		setEditable(IlBoolean);
    IlBoolean		isEditable() const;

    // Show / hide
    void		show(IlBoolean bShow = IlTrue,
			     IlBoolean bReDraw = IlTrue);
    void		reDraw();

    const IlSymbol*	getCallbackType() const;
    IlvDisplay*		getDisplay() const;

    // Tree gadget method
    IlvTreeGadgetItem*	getRoot() const;
    IlvTreeGadgetItem*	getFirstChildRoot() const;
    IlvTreeGadgetItem*	getLastSelectedTreeItem() const;

protected:
    Type _type;
    union {
	IlvTextField*			_txtField;
	IlvNumberField*			_numField;
	IlvToggle*			_toggle;
	IlvStringList*			_slist;
	IlvScrolledComboBox*		_combo;
	IlvCheckedStringList*		_checkedList;
	IlvTreeGadget*			_treeGadget;
	IlvCheckedTreeGadget*		_chktree;
	IlvFileSelectorField*		_fileSelector;
	IlvSpinBox*			_spinBox;
	IlvDvAcceleratorTextField*	_accel;
	IlvGraphic*			_graphic;
	IlvText*			_text;
	IlvMessageLabel*		_messageLabel;
	IlvIcon*			_icon;
    } _gadget;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(gengadg);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Gadgets_Gengadg_H */
