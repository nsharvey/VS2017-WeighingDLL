// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapView.h
// IlogViews 4 generated header file
// File generated Tue Jun 13 18:32:05 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the BitmapView class
// --------------------------------------------------------------------------
#if !defined(BitmapView__header__)
#define BitmapView__header__

#if !defined(__Ilv_Appframe_Dialog_Formvw_H)
#include <ilviews/appframe/dialog/formvw.h>
#endif /* !__Ilv_Appframe_Dialog_Formvw_H */

class BitmapDocument;
class IlvIcon;

// --------------------------------------------------------------------------
// BitmapView class
// --------------------------------------------------------------------------

class DVAPPCLASS BitmapView
: public IlvDvFormView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    BitmapView(IlvDisplay* display);
    virtual ~BitmapView();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    BitmapDocument* getBitmapDocument() const;

    virtual void bitmapHasChanged(IlAny region);

    void zoom(IlFloat factor);
    void zoomIn() { zoom((IlFloat)2.); }
    void zoomOut() { zoom((IlFloat).5); }

    // ----------------------------------------------------------------------
    // Export BitmapView fields and methods
    IlvDvDeclareInterface();

protected:
    IlvIcon* _icon;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(BitmapView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !BitmapView__header__ */
