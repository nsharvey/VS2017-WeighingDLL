// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/transition.cpp
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
// Using IlvBitmapTransition classes.
// --------------------------------------------------------------------------

#include <transition.h>

// --------------------------------------------------------------------------
// A Bitmap transition handler displayed by a graphic object
// --------------------------------------------------------------------------
class IlvGraphicTransitionHandler
    : public IlvBitmapTransitionHandler
{
public:
    IlvGraphicTransitionHandler(IlvBitmapTransition& transition,
				IlvRGBBitmapData& image1,
				IlvRGBBitmapData& image2,
				IlvGraphic& graphic,
				IlvBitmap& bitmap)
	: IlvBitmapTransitionHandler(transition,
				     image1,
				     image2,
				     bitmap),
	  _graphic(graphic)
    {
    }
    virtual void doTransition(IlvTransitionScheduler& scheduler,
			      IlDouble previous,
			      IlDouble current)
    {
	IlvBitmapTransitionHandler::doTransition(scheduler, 
						 previous, 
						 current);
	_graphic.reDraw();
    }

protected:
    IlvGraphic& _graphic;
};

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Speed changed
// --------------------------------------------------------------------------
static void
SpeedCB(IlvGraphic* g, IlAny)
{
    Transition* o = (Transition*)IlvContainer::getContainer(g);
    o->speedChanged();
}

// --------------------------------------------------------------------------
// Transition changed
// --------------------------------------------------------------------------
static void
TransitionCB(IlvGraphic* g, IlAny arg)
{
    Transition* o = (Transition*)IlvContainer::getContainer(g);
    o->transitionChanged();
    o->doIt();
}

// --------------------------------------------------------------------------
// Start animation
// --------------------------------------------------------------------------
static void
DoItCB(IlvGraphic* g, IlAny arg)
{
    Transition* o = (Transition*)IlvContainer::getContainer(g);
    o->doIt();
}

// --------------------------------------------------------------------------
// Panel class for sample Transition
// --------------------------------------------------------------------------
Transition::Transition(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _image(0),
      _image1(0),
      _image2(0),
      _transition(0),
      _scheduler(0),
      _duration(0),
      _first(IlTrue)
{
    initTransition();
}

// --------------------------------------------------------------------------
Transition::~Transition()
{
    if (_image1) {
        _image1->unLock();
    }
    if (_image2) {
        _image2->unLock();
    }
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Transition::initTransition()
{
    //readFile("transition.ilv");
	
    // Retrieve the bitmap data for image 1
    IlvButton* icon1 = (IlvButton*)getObject("Image1");
    if (icon1) {
        _image1 = (IlvRGBBitmapData*)
	  IlvSystemPort::GetBitmapData(icon1->getBitmap());
	_image1->lock();
	_image = icon1;
    }
	
    // Retrieve the bitmap data for image 2
    IlvIcon* icon2 = (IlvIcon*)getObject("Image2");
    if (icon2) {
        _image2 = (IlvRGBBitmapData*)
	  IlvSystemPort::GetBitmapData(icon2->getBitmap());
	_image2->lock();
	removeObject(icon2);
	delete icon2;
    }
	
    if (_image1 &&
	_image2 &&
	(_image1->getWidth() == _image2->getWidth()) &&
	(_image1->getHeight() == _image2->getHeight())) {
        // Get slider info
        speedChanged();
	    
	// Get combo info
	transitionChanged();
	    
	// register the callback on the slider and the combo
	registerCallback("SpeedCB", SpeedCB);
	registerCallback("TransitionCB", TransitionCB);
	registerCallback("DoItCB", DoItCB);
    }
    else {
        IlvFatalError("Data file not loaded or bad data file !");
	IlvExit(1);
    }
}

// --------------------------------------------------------------------------
// Called when speed changed
// --------------------------------------------------------------------------
void 
Transition::speedChanged()
{
    IlvSlider* slider = (IlvSlider*)getObject("Speed");
    _duration = slider->getValue();
}

// --------------------------------------------------------------------------
// Called when transition changed
// --------------------------------------------------------------------------
void 
Transition::transitionChanged()
{
    IlvComboBox* scombo = (IlvComboBox*)getObject("Transition");
    IlvBitmapTransition* transition = 0;
    switch (scombo->whichSelected()) {
    case 0:
        transition = new IlvAlphaBitmapTransition;
	break;
    case 1:
        transition = new IlvDissolveBitmapTransition;
	break;
    case 2:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::WipeLeft);
	break;
    case 3:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::WipeRight);
	break;
    case 4:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::WipeDown);
	break;
    case 5:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::WipeUp);
	break;
    case 6:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::BoxIn);
	break;
    case 7:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::BoxOut);
	break;
    case 8:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::
				    SplitHorizontalIn);
	break;
    case 9:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::
				    SplitHorizontalOut);
	break;
    case 10:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::
				    SplitVerticalIn);
	break;
    case 11:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::
				    SplitVerticalOut);
	break;
    case 12:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::SnailIn);
	break;
    case 13:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::
				    BandHorizontalIn);
	break;
    case 14:
        transition = new
	  IlvSimpleBitmapTransition(IlvSimpleBitmapTransition::
				    BandVerticalIn);
	break;
    default:
        return;
    }
    if (transition) {
        if (_scheduler) {
	    if (_scheduler->isRunning()) {
	        _scheduler->stop();
	    }
	    delete _scheduler;
	    _scheduler = 0;
	}
	delete _transition;
	_transition = transition;
    }
}

// --------------------------------------------------------------------------
// Called to start the transition animation
// --------------------------------------------------------------------------
void 
Transition::doIt()
{
    if (_scheduler) {
        if (_scheduler->isRunning()) {
	    _scheduler->stop();
	}
	delete _scheduler;
	_scheduler = 0;
    }
    IlvGraphicTransitionHandler* handler =
        new IlvGraphicTransitionHandler(*_transition,
					_first ? *_image1 : *_image2,
					_first ? *_image2 : *_image1,
					*_image,
					*_image->getBitmap());
    _first = !_first;
    _scheduler =
	new IlvTransitionScheduler(getDisplay(), *handler, _duration);
    _scheduler->start();
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageTransition(Pan* mainPanel)
{
    Transition* panel = new Transition(mainPanel, "transition.ilv");
    mainPanel->addPageNoteBook(panel, "Transition", "transition.txt");
}
