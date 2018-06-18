// -------------------------------------------------------------- -*- C++ -*-
// File: BitmapView.cpp
// IlogViews 4 generated source file
// File generated Tue Jun 13 15:11:29 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <BitmapView.h>
#include <BitmapDocument.h>
#include <ilviews/appframe/command.h>

// --------------------------------------------------------------------------
// BitmapView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(BitmapView)
IlvDvEndInterface1(IlvDvFormView)

// --------------------------------------------------------------------------
// Constructor / destructor
BitmapView::BitmapView(IlvDisplay* display)
: IlvDvFormView(display)
{
}

// --------------------------------------------------------------------------
BitmapView::~BitmapView()
{
}

// --------------------------------------------------------------------------
// Overridables
void
BitmapView::initializeView()
{
  IlvDvFormView::initializeView();
    
    BitmapDocument* document = getBitmapDocument();
    // Add here your initialization code
}

// --------------------------------------------------------------------------
// Basic properties
BitmapDocument*
BitmapView::getBitmapDocument() const
{
    return (BitmapDocument*)getDocument();
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterGadgetViewClass(BitmapView, IlvDvFormView);

IL_BEGINMODULEINITDEF(BitmapView)
    IlvDvPostRegisterGadgetViewClass(BitmapView, IlvDvFormView);
IL_ENDMODULEINITDEF(BitmapView)

#if !defined(ILVBUILDLIBS)
static int BitmapView_ini = (IL_MODINIT(BitmapView)(), 0);
#endif

