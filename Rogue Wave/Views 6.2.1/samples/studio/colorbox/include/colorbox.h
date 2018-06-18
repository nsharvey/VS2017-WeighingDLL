// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/colorbox/include/colorbox.h
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
// Declaration of the IlvColorComboBox class
// --------------------------------------------------------------------------

#if !defined(__Ilv_SampleColorbox_H)
#define __Ilv_SampleColorbox_H

#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/slist.h>

// --------------------------------------------------------------------------
// IlvColorDrawInfo class
// --------------------------------------------------------------------------
class IlvColorDrawInfo : public IlvValueInterface
{
public:
    IlvColorDrawInfo(IlvDisplay*);
    IlvColorDrawInfo(const IlvColorDrawInfo&);
    ~IlvColorDrawInfo();

    IlvColorDrawInfo& operator = (const IlvColorDrawInfo&);

    IlBoolean  _smallColorRect;
    IlUShort	_colorRoundRectRadius;
    IlUShort   _horizontalRectColorMargin;
    IlUShort   _verticalRectColorMargin;
    IlvDrawMode _drawMode;
    IlvDisplay* _display;

    IlvDeclareClassInfo();
    DeclareGraphicAccessors();
    static IlvSymbol* _SmallColorRectValue;
    static IlvSymbol* _ColorRoundRectRadius;
    static IlvSymbol* _HColorRectMarginValue;
    static IlvSymbol* _VColorRectMarginValue;
    static IlvSymbol* _ColorInfosValue;
    static IlvDim     _DefaultLabelOffset;
};

// --------------------------------------------------------------------------
// IlvColorComboBox class
// --------------------------------------------------------------------------
class IlvColorGadgetItem : public IlvGadgetItem
{
public:
    IlvColorGadgetItem(IlvColor*,
		       const IlvColorDrawInfo* drawInfo,
		       IlvPosition  position = IlvDefaultGadgetItemPosition,
		       IlUShort    spacing  = IlvDefaultGadgetItemSpacing);
    virtual ~IlvColorGadgetItem();
    // ____________________________________________________________
    virtual void draw(IlvPort*              dst,
		      const IlvRect&        rect,
		      const IlvTransformer* t    = 0,
		      const IlvRegion*      clip = 0) const;

    IlvColor* getColor()const;
    void setDrawInfo(const IlvColorDrawInfo* drawInfo);

    // ----------------------------------------------------------------------
    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvColorGadgetItem);

protected:
    const IlvColorDrawInfo* _drawInfo;
};

// --------------------------------------------------------------------------
// IlvColorComboBox class
// --------------------------------------------------------------------------
class IlvColorComboBox : public IlvScrolledComboBox
{
public:
    IlvColorComboBox(IlvDisplay*        display,
		     const IlvPoint&    point,
		     IlUShort           thickness =
			    IlvDefaultGadgetThickness,
		     IlvPalette*        palette   = 0);
    IlvColorComboBox(IlvDisplay*        display,
		     const IlvRect&     rect,
		     IlUShort           thickness =
		     IlvDefaultGadgetThickness,
		     IlvPalette*        palette   = 0);
    virtual ~IlvColorComboBox();
    // ----------------------------------------------------------------------
    // Overriden
/*
    virtual void draw(IlvPort* dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void drawText(IlvPort* dst,
			  const IlvTransformer* t = 0,
			  const IlvRegion* clip = 0) const;
    virtual void getTextBBox(IlvRect&) const;
*/
    virtual IlvGadgetItem* createItem(const char* label,
				      IlvGraphic* g       = 0,
				      IlvBitmap*  bitmap  = 0,
				      IlvBitmap*  sbitmap = 0,
				      IlBoolean  copy     = IlTrue) const;
    virtual void setMode(IlvDrawMode mode);

    // ----------------------------------------------------------------------
    // Specific methods
    IlvColor* getSelectedColor() const;
    virtual IlvUShort insertColor(IlvColor* color,
				  IlShort pos = -1);
    virtual void setColors(IlvColor* const* colors,
			   IlUShort count);

    // ----------------------------------------------------------------------
    // Getting infos
    IlBoolean isShowingColorRect()const;
    void       showColorRect(IlBoolean bShow = IlTrue);

    void       setColorRectMarings(IlInt = -1,
				   IlInt = -1,
				   IlBoolean recomputeItems = IlTrue);
    IlInt     getVColorRectMargin()const;
    IlInt     getHColorRectMargin()const;
    const IlvColorDrawInfo& getColorDrawInfo()const;
    
    // ----------------------------------------------------------------------
    DeclareTypeInfo();
    DeclareIOConstructors(IlvColorComboBox);

protected:
    IlvColorDrawInfo _drawInfo;

    void updateItemsDrawInfo();
    virtual void drawInfoModified();
    
public:
    DeclareGraphicAccessors();
};

// --------------------------------------------------------------------------
// IlvColorStringList class
// --------------------------------------------------------------------------
class IlvColorStringList : public IlvStringList
{
public:
    IlvColorStringList(IlvDisplay*        display,
		       const IlvPoint&    point,
		       IlUShort           thickness =
			    IlvDefaultGadgetThickness,
		       IlvPalette*        palette   = 0);
    IlvColorStringList(IlvDisplay*        display,
		       const IlvRect&     rect,
		       IlUShort           thickness =
		             IlvDefaultGadgetThickness,
		       IlvPalette*        palette   = 0);
    virtual ~IlvColorStringList();
    // ----------------------------------------------------------------------
    // Overriden
    virtual IlvGadgetItem* createItem(const char* label,
				      IlvGraphic* g       = 0,
				      IlvBitmap*  bitmap  = 0,
				      IlvBitmap*  sbitmap = 0,
				      IlBoolean  copy     = IlTrue) const;
    virtual void setMode(IlvDrawMode mode);

    // ----------------------------------------------------------------------
    // Specific methods
    IlvColor* getSelectedColor()const;
    virtual IlUShort insertColor(IlvColor* color,
				 IlShort pos = -1);
    virtual void setColors(IlvColor* const* colors,
			   IlUShort count);

    // ----------------------------------------------------------------------
    // Getting infos
    IlBoolean isShowingColorRect()const;
    void       showColorRect(IlBoolean bShow = IlTrue);

    void       setColorRectMarings(IlInt = -1,
				   IlInt = -1,
				   IlBoolean recomputeItems = IlTrue);
    IlInt     getVColorRectMargin() const;
    IlInt     getHColorRectMargin() const;
    const IlvColorDrawInfo& getColorDrawInfo() const;
    
    // ----------------------------------------------------------------------
    DeclareTypeInfo();
    DeclareIOConstructors(IlvColorStringList);

protected:
    IlvColorDrawInfo _drawInfo;

    void updateItemsDrawInfo();
    virtual void drawInfoModified();
    
public:
    DeclareGraphicAccessors();
};

IL_MODULEINIT(colorbox, IL_EMPTYMACRO);

// --------------------------------------------------------------------------
#endif /* !__Ilv_SampleColorbox_H */
