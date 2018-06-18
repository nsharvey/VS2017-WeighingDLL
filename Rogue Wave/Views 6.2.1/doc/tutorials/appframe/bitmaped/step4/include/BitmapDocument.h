// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapDocument.h
// IlogViews 4 generated header file
// File generated Fri Jun  9 16:23:17 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the BitmapDocument class
// --------------------------------------------------------------------------
#if !defined(BitmapDocument__header__)
#define BitmapDocument__header__

#if !defined(__Ilv_Appframe_Document_H)
#include <ilviews/appframe/document.h>
#endif /* !__Ilv_Appframe_Document_H */

// --------------------------------------------------------------------------
// BitmapDocument class
// --------------------------------------------------------------------------

class DVAPPCLASS BitmapDocument
: public IlvDvDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    BitmapDocument();
    virtual ~BitmapDocument();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvBoolean initializeDocument(IlvAny = 0);
    virtual IlvBoolean readDocument(const IlvPathName&);
    virtual IlvBoolean saveDocument(const IlvPathName&);

    // ----------------------------------------------------------------------
    // Export BitmapDocument fields and methods
    IlvDvDeclareInterface();

    IlvBitmap* getBitmap() const { return _bitmap; }
    void setBitmap(IlvBitmap* bitmap);

    IlvPalette* getPalette() const { return _palette; }
    void setPalette(IlvPalette* palette);

    void colorChooser();

    void refreshViews(const IlvRegion&);
    void refreshViews(const IlvRect&);

    void drawRectangle(const IlvPoint& point, IlvDim size, IlvPalette* = 0);

protected:
    IlvBitmap*  _bitmap;
    IlvPalette* _palette;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(BitmapDocument, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !BitmapDocument__header__ */
