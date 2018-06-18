// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/jpgcomp.cpp
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
// Using the JPEG streamer. 
// --------------------------------------------------------------------------
#include <jpgcomp.h>

#if defined(IL_STD)
#include <strstream>
IL_STDUSE
#else /* !IL_STD */
#include <strstream.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// Callback
// --------------------------------------------------------------------------
static void
QualityCB(IlvGraphic* g, IlAny arg)
{
    IL_CAST(JpgComp*, arg)->qualityChanged();
}

// --------------------------------------------------------------------------
// Panel class for sample Jpgcomp
// --------------------------------------------------------------------------
JpgComp::JpgComp(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _srcdata(0),
      _dsticon(0),
      _slider(0)
{
    initJpgComp();
}

// --------------------------------------------------------------------------
JpgComp::~JpgComp()
{
    _srcdata->unLock();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
JpgComp::initJpgComp()
{
    const char* JPEGBITMAPNAME = "colors.png";

    IlvDisplay* display = getDisplay();
    _srcdata = (IlvRGBBitmapData*)display->readBitmapData(JPEGBITMAPNAME);
    _srcdata->lock();
    IlUInt width = _srcdata->getWidth();
    IlUInt height = _srcdata->getHeight();
    IlvIcon* srcicon = new IlvIcon(display, 
				   IlvPoint(10, 25), 
				   new IlvBitmap(display, _srcdata));
    
    ostrstream tooltipstr;
    tooltipstr << "Original size in memory : "
	       << (int)(width * height * 4)
	       << " bytes"
	       << ends;
    delete srcicon->setNamedProperty(new IlvToolTip(tooltipstr.str()));
    tooltipstr.rdbuf()->freeze(0);
    addObject(srcicon);
    addObject(_dsticon = new IlvIcon(display, 
				     IlvPoint(width + 45, 25), 
				     new IlvBitmap(display, 
						   width, 
						   height, 
						   display->screenDepth())));
    _slider = (IlvSlider*)getObject("slider");
    _slider->setFocusable(IlFalse);
    _slider->setValues(0, 100, 0);
    _slider->setPageIncrement(1);
    _slider->setCallback(QualityCB, this);
    //    resize(width * 2 + 60, height + 20);
    qualityChanged();
}

// --------------------------------------------------------------------------
// Called when the quality changed
// --------------------------------------------------------------------------
void 
JpgComp::qualityChanged()
{
    IlvUInt quality = IL_CAST(IlvUInt, _slider->getValue());
    IlvValue value("quality", 100 - quality);
    IlvBitmapStreamer* jpgstreamer = IlvBitmapStreamer::Get("IlvJPGStreamer");
    jpgstreamer->changeValue(value);
    ostrstream outstream;
    ostrstream tooltipstr;
    jpgstreamer->write(_srcdata, outstream);
    char* dataptr = outstream.str();
    int numbytes = (int) outstream.pcount();
    tooltipstr << "Quality : "
	       << (int)(100 - quality) 
	       << ", Size : "
	       << numbytes
	       << " bytes"
	       << ends;
    delete _dsticon->setNamedProperty(new IlvToolTip(tooltipstr.str()));
    istrstream instream(dataptr, numbytes);
    IlvRGBBitmapData* dstdata = (IlvRGBBitmapData*)
	jpgstreamer->read(instream);
    outstream.rdbuf()->freeze(0);
    tooltipstr.rdbuf()->freeze(0);
    _dsticon->setBitmap(new IlvBitmap(getDisplay(), dstdata));
    delete dstdata;
    initReDraw();
    invalidateRegion(_dsticon);
    reDrawView(IlFalse,IlTrue);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageJpgComp(Pan* mainPanel)
{
    JpgComp* panel = new JpgComp(mainPanel, "jpgcomp.ilv");
    mainPanel->addPageNoteBook(panel, "Jpeg", "jpgcomp.txt");
}
