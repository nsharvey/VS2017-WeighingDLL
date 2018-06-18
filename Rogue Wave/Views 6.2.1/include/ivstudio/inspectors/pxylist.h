// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/pxylist.h
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
// Declaration of a list/combo/otpionmenu proxy class
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Pxylist_H)
#define __IlvSt_Inspectors_Pxylist_H

#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif

class IlvGraphicHolder;
class IlvGadget;
class IlvOptionMenu;
class IlvStringList;
class IlvScrolledComboBox;
class IlvComboBox;
class IlvGadgetItem;
class IlvListGadgetItemHolder;

// --------------------------------------------------------------------------
// IlvStIProxyListGadget
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIProxyListGadget
{
public:
    IlvStIProxyListGadget(const char*, IlvGraphicHolder*);
    IlvStIProxyListGadget(IlvGraphic*, IlvGraphicHolder* = 0);
    ~IlvStIProxyListGadget();

    // ----------------------------------------------------------------------
    // Initialization
    IlBoolean operator !() const;
    IlBoolean isBad() const;
    IlBoolean initOnGraphic(IlvGraphic*,
			     IlvGraphicHolder* = 0);
    IlBoolean initOnGadgetName(const char*,
			        IlvGraphicHolder*);
    static IlBoolean IsListGadget(IlvGraphic*);

    // ----------------------------------------------------------------------
    // Labels managment
    void		setLabels(const char**, IlUShort,
				  IlBoolean = IlTrue, IlBoolean = IlTrue);
    IlUShort		getPosition(const char*) const;
    const char*		getLabel(IlUShort) const;
    const char* const*	getLabels(IlUShort&) const;
    IlUShort		getCardinal() const;
    void		empty();
    IlBoolean		setLabel(IlUShort, const char*, IlBoolean = IlTrue);
    IlUShort           insertLabel(IlUShort, const char*,
				   IlBoolean = IlTrue);
    void                prepareFilling();
    void                endFilling();

    // ----------------------------------------------------------------------
    // gadget item managment
    IlBoolean isGadgetItemHolder() const;
    IlvListGadgetItemHolder* getListGadgetItemHolder();
    const IlvListGadgetItemHolder* getListGadgetItemHolder() const;
    IlvGadgetItem* getItem(IlUShort) const;
    IlUShort insertItem(IlvGadgetItem*, IlShort = -1);
    void removeItem(IlUShort, IlBoolean = IlTrue);
    void replaceItem(IlUShort, IlvGadgetItem*);
    // IlvGadgetItem for string lists and IlvMenuItem for menus
    IlvGadgetItem* createGadgetItem(const char*, IlvBitmap* = 0) const;
    IlvGadgetItem* checkGadgetItem(IlvGadgetItem*, IlBoolean = IlTrue) const;
    IlBoolean getAutomaticLabelAlignmentMode() const;
    void       setAutomaticLabelAlignmentMode(IlBoolean, IlBoolean = IlTrue);

    static IlvGadgetItem* CreateGadgetItem(IlvGraphic*, const char*,
					   IlvBitmap*);

    // ----------------------------------------------------------------------
    // Selection managment
    void        setSelectionCallback(IlvGraphicCallback, IlAny);
    void        setSelected(IlUShort,
			    IlBoolean = IlTrue, IlBoolean = IlTrue);
    void        setSelectedText(const char*,
			        IlBoolean = IlTrue, IlBoolean = IlTrue);
    IlUShort   getSelectedItem() const;
    const char* getSelectedText() const;

    // ----------------------------------------------------------------------
    // Misc
    IlvGadget*        getGadget();
    const IlvGadget*  getGadget() const;
    IlvDisplay*       getDisplay() const;
    IlvGraphicHolder* getGraphicHolder() const { return _holder; }
    void setSensitive(IlBoolean = IlTrue, IlBoolean = IlTrue);
    void setFocus(IlBoolean = IlTrue);
    void setVisible(IlBoolean = IlTrue);
    IlBoolean isVisible() const;
    void ensureVisible(IlUShort, IlBoolean = IlTrue, IlBoolean = IlFalse);
    void reDraw();
protected:
    IlvGraphicHolder* _holder;
    union {
	IlvOptionMenu*         _optMenu;
	IlvStringList*         _stringList;
	IlvComboBox*           _combo;
	IlvScrolledComboBox*   _scCombo;
    } _gadget;
    IlBoolean _storedLabelAlignmentMode;
    IlvGadget* _getGadget() const;
    enum { NONE, OPTION_MENU, STRING_LIST, COMBOBOX, SCROLLED_COMBOBOX }
      _type;
};

// --------------------------------------------------------------------------
ILVINSPEXPORTEDFUNC(IlvGraphic*)
IlvStIFindGraphic(IlvGraphicHolder*, const char*, IlvGraphicHolder** = 0);

typedef IlBoolean (*IlvStIHolderCallback)(IlvGraphicHolder*, IlAny);
ILVINSPEXPORTEDFUNC(IlBoolean)
IlvStIForEachGraphicHolder(IlvGraphicHolder*,
			   IlvStIHolderCallback, IlAny = 0);
#endif /* !__IlvSt_Inspectors_Pxylist_H */
