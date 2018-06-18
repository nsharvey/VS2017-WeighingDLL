// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bmpfilters/src/displace.cpp
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
// Using the displace filter. 
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slider.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/graphics/label.h>
#include <ilviews/bitmaps/data.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/bitmaps/filters/displace.h>
#include <ilviews/bitmaps/filters/turbulence.h>
#include <ilviews/bitmaps/flow.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny arg)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
class DisplaceContainer : public IlvGadgetContainer
{
public: 
    DisplaceContainer(IlvDisplay* display, 
		      const char* name,
		      const char* title,
		      const IlvRect& dims);
    ~DisplaceContainer();

    void		updateDisplace();
    void		updateTurbulence();
    void		applyFilter();

protected:
    IlvFilterFlow*	_flow;
    IlvRGBBitmapData*	_srcdata;
    IlvIcon*		_turbicon;
    IlvIcon*		_dsticon;
    IlUInt		_width;
    IlUInt		_height;
};

// --------------------------------------------------------------------------
static void
ChangeTurbulence(IlvGraphic* g, IlAny arg)
{
    IL_CAST(DisplaceContainer*, arg)->updateTurbulence();
}

// --------------------------------------------------------------------------
static void
ChangeDisplace(IlvGraphic* g, IlAny arg)
{
    IL_CAST(DisplaceContainer*, arg)->updateDisplace();
}

// --------------------------------------------------------------------------
DisplaceContainer::DisplaceContainer(IlvDisplay* display, 
				     const char* name,
				     const char* title,
				     const IlvRect& dims)
    : IlvGadgetContainer(display, name, title, dims, IlFalse, IlFalse),
      _flow(new IlvFilterFlow()),
      _srcdata(0),
      _turbicon(0),
      _dsticon(0),
      _width(0), 
      _height(0)
{
    _srcdata = (IlvRGBBitmapData*)display->readBitmapData("mona_lisa.png");
    _width = _srcdata->getWidth();
    _height = _srcdata->getHeight();
    readFile("displace.ilv");
    addObject(new IlvIcon(display, 
			  IlvPoint(10, 10), 
			  new IlvBitmap(display, _srcdata)));
    
    IlvBitmapFilter* turbulence =
	IlvBitmapFilter::Create("IlvTurbulenceFilter", IlTrue);
    _flow->addFilter(turbulence);
    turbulence->changeValue(IlvValue("name", "turbulence"));
    turbulence->changeValue(IlvValue("width", _width));
    turbulence->changeValue(IlvValue("height", _height));
    turbulence->changeValue(IlvValue("result", "turbulence"));
    
    IlvBitmapFilter* displace =
	IlvBitmapFilter::Create("IlvDisplaceFilter", IlTrue);
    _flow->addFilter(displace);
    displace->changeValue(IlvValue("name", "displace"));
    displace->changeValue(IlvValue("width", _width));
    displace->changeValue(IlvValue("height", _height));
    displace->changeValue(IlvValue("xChannelSelector", "A"));
    displace->changeValue(IlvValue("yChannelSelector", "R"));
    displace->changeValue(IlvValue("result", "ResultGraphic"));
    displace->changeValue(IlvValue("in", "SourceGraphic,turbulence"));
    
    setMinimumSize(_width * 2 + 30, _height* 2 + 30);
    setMaximumSize(_width * 2 + 30, _height * 2 + 30);
    
    getObject("xfreq")->setCallback(ChangeTurbulence, this);
    getObject("yfreq")->setCallback(ChangeTurbulence, this);
    getObject("octaves")->setCallback(ChangeTurbulence, this);
    getObject("turb")->setCallback(ChangeTurbulence, this);
    getObject("scale")->setCallback(ChangeDisplace, this);
    
    initRedraw();
    updateTurbulence();
    reDrawView(IlFalse);
}

// --------------------------------------------------------------------------
DisplaceContainer::~DisplaceContainer()
{
    delete _srcdata;
    delete _flow;
}

// --------------------------------------------------------------------------
void
DisplaceContainer::updateDisplace()
{
    initRedraw();
    IlvSlider* slider = (IlvSlider*)getObject("scale");
    IlFloat scale = (IlFloat)(slider->getValue() - 100);
    IlvNumberField* numfield = (IlvNumberField*)getObject("scnum");
    numfield->setValue(scale);
    IlvBitmapFilter* displace = _flow->getFilter("displace");
    displace->changeValue(IlvValue("scale", scale));
    _flow->invalidate(displace);
    applyFilter();
    invalidateRegion(_dsticon);
    invalidateRegion(getObject("scnum"));
    reDrawView(IlFalse);
}

// --------------------------------------------------------------------------
void
DisplaceContainer::updateTurbulence()
{
    initReDraw();
    IlvSlider* slider = (IlvSlider*)getObject("xfreq");
    IlFloat xfrequency = slider->getValue() / (IlFloat)4000.0;
    slider = (IlvSlider*)getObject("yfreq");
    IlFloat yfrequency = slider->getValue() / (IlFloat)4000.0;
    IlvNumberField* numfield = (IlvNumberField*)getObject("xnum");
    numfield->setValue(xfrequency);
    numfield = (IlvNumberField*)getObject("ynum");
    numfield->setValue(yfrequency);
    slider = (IlvSlider*)getObject("octaves");
    IlUInt octaves = slider->getValue();
    numfield = (IlvNumberField*)getObject("onum");
    numfield->setValue((IlFloat)octaves);
    IlvToggle* turb = (IlvToggle*)getObject("turb");
    IlBoolean isfractal = !turb->getState();
    IlvBitmapFilter* turbulence = _flow->getFilter("turbulence");
    turbulence->changeValue(IlvValue("baseFrequencyX", xfrequency));
    turbulence->changeValue(IlvValue("baseFrequencyY", yfrequency));
    turbulence->changeValue(IlvValue("numOctaves", octaves));
    turbulence->changeValue(IlvValue("noiseMode",
				     isfractal ? "fractal" : "turbulence"));
    _flow->invalidate();
    applyFilter();
    invalidateRegion(_turbicon);
    invalidateRegion(getObject("xnum"));
    invalidateRegion(getObject("ynum"));
    invalidateRegion(getObject("onum"));
    reDrawView(IlFalse);
}

// --------------------------------------------------------------------------
void
DisplaceContainer::applyFilter()
{
    IlvDisplay* display = getDisplay();
    IlvBitmapData* result = _flow->applyUnary(_srcdata);
    if (!_turbicon) {
	_turbicon =
	    new IlvIcon(display,
			IlvPoint(_width + 20, 10),
			new IlvBitmap(display, 
				      _flow->getBitmapData("turbulence")));
	addObject(_turbicon);
    }
    else {
	_turbicon->setBitmap(new IlvBitmap(display, 
					   _flow->getBitmapData("turbulence")));
    }
    if (!_dsticon) {
	_dsticon = new IlvIcon(display,
			       IlvPoint(10, _height + 20),
			       new IlvBitmap(display, result));
	addObject(_dsticon);
    }
    else {
	_dsticon->setBitmap(new IlvBitmap(display, result));
    }
    delete result;
    invalidateRegion(_dsticon);
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    const char* title = "Rogue Wave Views Bitmap filter sample: displace";
    IlvRect dims(0, 0, 500, 500);
    IlvDisplay* display = new IlvDisplay(title, "", argc, argv);
    if (!display || display->isBad()) {
	if (display) {
	    delete display;
	}
	IlvFatalError("Could not open display");
	return -1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/bmpfilters/data");
    display->prependToPath(localPath);
    DisplaceContainer* container =
	new DisplaceContainer(display, title, title, dims);
    container->setDestroyCallback(Quit);
    container->show();
    IlvMainLoop();
    return 0;
}
