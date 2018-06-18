// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/cadrg/src/covchoose.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Implementation of the CADRG coverage chooser.
// --------------------------------------------------------------------------
#include <ilviews/manager/rectangl.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/button.h>

#include <covchoose.h>

// --------------------------------------------------------------------------
// coverage chooser
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor: List the coverages using the table of contents. We use combo
// boxes to use only the basic gadget set.
// --------------------------------------------------------------------------
CovChoose::CovChoose(IlvDisplay* display, Viewer* viewer)
    : _display(display),
      _viewer(viewer)
{
    _small = 0;
    _medium = 0;
    _large = 0;
    listCoverages();
    createCombos();
    buildSmall();
}

// --------------------------------------------------------------------------
// Build the medium coverage list when an item in the small coverage list is
// selected
// --------------------------------------------------------------------------
void
CovChoose::SmallItemSelected(IlvGraphic* g, IlvAny)
{
    CovChoose* cc = (CovChoose*)g->getClientData();
    IlvComboBox* cb = (IlvComboBox*)g;
    IlShort which = cb->whichSelected();
    cc->buildMedium(which);
}

// --------------------------------------------------------------------------
// Build the large coverage list when an item in the medium coverage list is 
// setected
// --------------------------------------------------------------------------
void
CovChoose::MediumItemSelected(IlvGraphic* g, IlvAny)
{
    CovChoose* cc = (CovChoose*) g->getClientData();
    IlvComboBox* cb = (IlvComboBox*)g;
    IlShort which = cb->whichSelected();
    cc->buildLarge(which);
}

// --------------------------------------------------------------------------
// Returns the small coverage selected
// --------------------------------------------------------------------------
const IlvCADRGCoverage*
CovChoose::getSmallCoverage()
{
    int which = _smallComboBox->whichSelected();
    if (which < 0) {
	return 0;
    }
    return _coverages[_small[which]];
}

// --------------------------------------------------------------------------
// Returns the medium coverage selected
// --------------------------------------------------------------------------
const IlvCADRGCoverage*
CovChoose::getMediumCoverage()
{
    int which = _mediumComboBox->whichSelected();
    if (which < 0) {
	return 0;
    }
    return _coverages[_medium[which]];
}

// --------------------------------------------------------------------------
// Returns the large coverage selected
// --------------------------------------------------------------------------
const IlvCADRGCoverage*
CovChoose::getLargeCoverage()
{
    int which = _largeComboBox->whichSelected();
    if (which < 0) {
	return 0;
    }
    return _coverages[_large[which]];
}

// --------------------------------------------------------------------------
// Ok button callback : Load the selected coverages
// --------------------------------------------------------------------------
void
CovChoose::OkCallback(IlvGraphic* g, IlvAny a)
{
    const IlvCADRGCoverage* small;
    const IlvCADRGCoverage* medium;
    const IlvCADRGCoverage* large;

    CovChoose* cv = (CovChoose*)a;
    small = cv->getSmallCoverage();
    medium = cv->getMediumCoverage();
    large = cv->getLargeCoverage();

    cv->getViewer()->loadCoverages(small, medium, large);
}

// --------------------------------------------------------------------------
// Create the combo boxes
// --------------------------------------------------------------------------
void
CovChoose::createCombos()
{
    IlvGraphic* label;
    IlvRect r(550, 0, 200, 300);
    _gadgetContainer = new IlvGadgetContainer(_display,
					      "Coverage Chooser",
					      "Coverage Chooser",
					      r,
					      IlFalse,
					      IlFalse);
    IlvGraphicHolder* gh = _gadgetContainer->getHolder();
		 
    IlvPos y = 0;
    IlvComboBox* cb;

    label = new IlvMessageLabel(_display,
				"Small Scale",
				IlvRect(0, y, r.w(), 20),
				IlvCenter);
    _gadgetContainer->addObject(label);
    gh->attach(label, IlvHorizontal, 0, 1, 0);

    y +=  label->h() + 2;
	    
    cb = new IlvComboBox(_display,
			 IlvPoint(0, y),
			 0,
			 0,
			 0);
    cb->setClientData(this);
    cb->setCallback(SmallItemSelected);
    cb->setEditable(IlFalse);
    cb->resize(r.w(), cb->h() + 2);
    _gadgetContainer->addObject(cb);
    gh->attach(cb, IlvHorizontal, 0, 1, 0);
	    
    y +=  cb->h() + 2;
    _smallComboBox = cb;

    label = new IlvMessageLabel(_display,
				"Medium Scale",
				IlvRect(0, y, r.w(), 20),
				IlvCenter);
    _gadgetContainer->addObject(label);
    gh->attach(label, IlvHorizontal, 0, 1, 0);

    y +=  label->h() + 2;
	    
    cb = new IlvComboBox(_display,
			 IlvPoint(0, y),
			 0,
			 0,
			 0);
    cb->setClientData(this);
    cb->setCallback(MediumItemSelected);
    cb->setEditable(IlFalse);
    cb->resize(r.w(), cb->h() + 2);
    _gadgetContainer->addObject(cb);
    gh->attach(cb, IlvHorizontal, 0, 1, 0);

    y +=  cb->h() + 2;
    _mediumComboBox = cb;

    label = new IlvMessageLabel(_display,
				"Large Scale",
				IlvRect(0, y, r.w(), 20),
				IlvCenter);
    _gadgetContainer->addObject(label);
    gh->attach(label, IlvHorizontal, 0, 1, 0);

    y +=  label->h() + 2;
	    
    cb = new IlvComboBox(_display,
			 IlvPoint(0, y),
			 0,
			 0,
			 0);
    cb->setClientData(this);
    cb->setEditable(IlFalse);
    cb->resize(r.w(), cb->h() + 2);
    _gadgetContainer->addObject(cb);
    gh->attach(cb, IlvHorizontal, 0, 1, 0);

    y += cb->h() + 5;
    _largeComboBox = cb;

    IlvButton* btn = new IlvButton(_display,
				   "Ok",
				   IlvRect(r.w()/2 - 30, y,
					   60, 15));
    _gadgetContainer->addObject(btn);
    gh->attach(btn, IlvHorizontal, 0, 1, 0);
    btn->setCallback(OkCallback, (IlvAny)this);
	    
    y += btn->h() + 2;
    _gadgetContainer->resize(r.w(), y);
    _gadgetContainer->show();
}

// --------------------------------------------------------------------------
// Empties the specified list
// --------------------------------------------------------------------------
void
CovChoose::empty(int *list) {
    for(int i = 0; i < _numCoverages; i++)
	list[i] = -1;
}

// --------------------------------------------------------------------------
// Lists all the coverages and empties the lists
// --------------------------------------------------------------------------
void
CovChoose::listCoverages()
{
    IlvCADRGTocReader* tocReader = _viewer->getTocReader();
    _coverages = tocReader->getCoverages(_numCoverages);

    if (_small) {
	delete [] _small;
    }
    _small = new int[_numCoverages+1];
    if (_medium) {
	delete [] _medium;
    }
    _medium = new int[_numCoverages+1];
    if (_large) {
	delete [] _large;
    }
    _large = new int[_numCoverages+1];
    for(int i = 0; i < _numCoverages; i++) {
	_small[i]  = -1;
	_medium[i] = -1;
	_large[i]  = -1;
    }
}

// --------------------------------------------------------------------------
// Returns the pixel size for specfied layer. Size is expressed in units of 
// coverage projection.
// --------------------------------------------------------------------------
void
CovChoose::PixelSize(const IlvCADRGCoverage* coverage, IlvFloatPoint& ps)
{
    IlvFloat widthInPixels = (IlvFloat)coverage->getColumns()
	* 6    // each frame has 6 subframes
	* 256  // each sub-frame has 256 pixels in width
	;
    IlvFloat heightInPixels = (IlvFloat)coverage->getRows() 
	* 6    // each frame has 6 subframes
	* 256  // each sub-frame has 256 pixels in width
	;
    ps.move((IlvFloat)coverage->getFrameWidth() / widthInPixels,
	    (IlvFloat)coverage->getFrameHeight() / heightInPixels);
}

// --------------------------------------------------------------------------
// Build the small coverage list
// --------------------------------------------------------------------------
void
CovChoose::buildSmall()
{
    empty(_small);
    int k = 0;
    for(IlInt i = 0 ; i < _numCoverages; i++) {
	const IlvCADRGCoverage* cov = _coverages[i];
	const char* name = getName(cov);
	if (name) {
	    _small[k ++] = i;
	    _smallComboBox -> insertLabel(1000, name);
	}
    }
}

// --------------------------------------------------------------------------
// Build the medium coverage list
// --------------------------------------------------------------------------
void
CovChoose::buildMedium(IlInt index)
{	
    empty(_medium);
    _mediumComboBox->setLabels(0, 0);
    _mediumComboBox->setLabel(0, IlTrue);
    int c = _small[index];
    const IlvCADRGCoverage* cov = _coverages[c];	   

    IlvFloatPoint small;
    PixelSize(cov, small);

    IlvFloatPoint p;
    int k = 0;
    for(IlInt i = 0; i < _numCoverages; i++) {	    
	cov = _coverages[i];

	if (!cov->getProjection()) {
	    continue;
	}
	    
	PixelSize(cov, p);

	if ((p.x() >= small.x()) ||
	    (p.y() >= small.y())) {
	    continue;
	}

	const char* name = getName(cov);
	    
	if (name) {
	    _medium[k ++] = i;
	    _mediumComboBox->insertLabel(1000, name);
	} 
    }
    IlUShort count;
    _mediumComboBox->getLabels(count);
    if (count) {
	_mediumComboBox->setSelected(0, IlTrue);
    }
}

// --------------------------------------------------------------------------
// Build the large coverage list
// --------------------------------------------------------------------------
void
CovChoose::buildLarge(IlInt index)
{
    empty(_large);
    _largeComboBox->setLabels(0, 0);
    _largeComboBox->setLabel(0, IlTrue);
    int c = _medium[index];
    const IlvCADRGCoverage* cov = _coverages[c];

    IlvFloatPoint medium;
    PixelSize(cov, medium);

    IlvFloatPoint p;
    int k = 0;
    for(IlInt i = 0; i < _numCoverages; i++) {	    
	cov = _coverages[i];

	if (!cov->getProjection()) {
	    continue;
	}
	    
	PixelSize(cov, p);

	if ((p.x() >= medium.x()) ||
	    (p.y() >= medium.y())) {
	    continue;
	}

	const char* name = getName(cov);
	    
	if(name) {
	    _large[k++] = i;
	    _largeComboBox->insertLabel(1000, name);
	} 
    }
    IlUShort count;
    _largeComboBox->getLabels(count);
    if (count) {
	_largeComboBox->setSelected(0, IlTrue);
    }
}

// --------------------------------------------------------------------------
// Retreives the name of the specfied coverage
// --------------------------------------------------------------------------
const char*
CovChoose::getName(const IlvCADRGCoverage* cov)
{
    IlvProjection* proj = cov->getProjection();
    if (!proj) {
	return 0;
    }
    IlInt rows = cov->getRows();
    IlInt columns = cov->getColumns();
    for (IlInt r = 0; r < rows; r++) {
	for (IlInt c = 0; c < columns; c++) {
	    const IlvCADRGFrame* frame =
				      cov->getFrame((IlShort)r, (IlShort)c);
	    if (frame) {
		return frame->getPathName() + 2;
	    }
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
// Selects the default coverages
// --------------------------------------------------------------------------
void
CovChoose::selectDefault()
{
    if (_numCoverages >= 9) {
	int i;
	for (i = 0; i < _numCoverages; i++) {
	    if (_small[i] == 5) {
		_smallComboBox->setSelected(i);
		_smallComboBox->callCallback();
		break;
	    }
	}
	for (i = 0; i < _numCoverages; i++) {
	    if (_medium[i] == 7) {
		_mediumComboBox->setSelected(i);
		_mediumComboBox->callCallback();
		break;
	    }
	}
	for (i = 0; i < _numCoverages; i++) {
	    if (_large[i] == 3) {
		_largeComboBox->setSelected(i);
		_largeComboBox->callCallback();
		break;
	    }
	}
	_viewer->loadCoverages(_coverages[5],
			       _coverages[7],
			       _coverages[3]);
    }
}
