// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapDocument.h
// IlogViews 4 generated header file
// File generated Tue Jun 13 15:11:30 2000
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
    virtual void       clean();

    // ----------------------------------------------------------------------
    // IO
    virtual void serialize(IlvDvStream&);

    // ----------------------------------------------------------------------
    // Export BitmapDocument fields and methods
    IlvDvDeclareInterface();
};

// --------------------------------------------------------------------------
IL_MODULEINIT(BitmapDocument, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !BitmapDocument__header__ */
