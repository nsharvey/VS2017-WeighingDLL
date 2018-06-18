// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/table/src/random.cpp
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
// Definition of a subclass of IlvAstractMatrix.
// The IlvSampleMatrix is a matrix with three columns,
// first row is the index, second row a random value
// third row is a gauge
// --------------------------------------------------------------------------

#include <random.h>

#define NBROWS 1000

static IlInt _STThreshold = 500;

// --------------------------------------------------------------------------
class IlvRandomMatrix : public IlvAbstractMatrix
{
public:
    IlvRandomMatrix(IlvDisplay*        display,
		    const IlvRect&     rect)
        : IlvAbstractMatrix(display, rect, IlvDefaultGadgetThickness)
    {
	_alarmPalette = getDisplay()->getPalette(getDisplay()->getColor("red"),
						 getPalette()->getBackground(),
						 0, 0,
						 getPalette()->getFont());
	_alarmPalette->lock();
    }
    virtual ~IlvRandomMatrix()
    {
	_alarmPalette->unLock();
    }
    // ____________________________________________________________
    // -- properties
    virtual IlUShort	rows () const { return NBROWS; }
    virtual IlUShort	columns () const { return 3; }
    virtual IlvDim	getRowHeight (IlUShort ) const { return 30; }
    virtual IlvDim	getColumnWidth (IlUShort ) const { return 50; }
    virtual IlBoolean	rowSameHeight() const { return IlTrue; }
    virtual IlBoolean	columnSameWidth() const { return IlTrue; }
    virtual void	drawItem(IlvPort* dst,
				 IlUShort colno,
				 IlUShort rowno,
				 const IlvRect& bbox,
				 const IlvRect& clip) const
    {
	IlvRect rect = bbox;
	IlvRect clipRect(clip);
	clipRect.intersection(rect);
	IlvRegion clipRegion(clipRect);
	static IlvRectangularGauge* gauge = 0;
	static char buffer[16];
	
	if (colno == 0) {
	    sprintf(buffer, "%d", rowno);
	    dst->drawLabel(getPalette(), buffer, -1, rect, &clipRegion);
	}
	else if (colno == 2) {
	    // Draws a gauge that shows the value
	    if (!gauge)
		gauge = new IlvRectangularGauge(dst->getDisplay(),
						bbox,
						(IlFloat)0,
						(IlFloat)1000,
						(IlFloat)50,
						IlvHorizontal);
	    
	    IlvRect grect;
	    gauge->setValue((IlFloat)_values[rowno]);
	    gauge->boundingBox(grect);
	    IlvTransformer transfo(grect, bbox);
	    gauge->draw(dst, &transfo, &clipRegion);
	}
	else {
	    sprintf(buffer, "%d", _values[rowno]);
	    rect.expand(-1, -1);
	    // Draws the value inverted if the number is >= threshold.
	    if (_values[rowno] >= _STThreshold)
		dst->drawILabel(_alarmPalette, buffer, -1, rect, &clipRegion);
	    else
		dst->drawLabel(getPalette(), buffer, -1, rect, &clipRegion);
	}
    }
    
    void		setValues()
    {
	for (int i = 0; i < NBROWS; ++i)
	    _values[i] = (int)(rand() % 1000);
	reDraw();
    }
    // no IO

private:
    IlvPalette*		_alarmPalette;
    int			_values[NBROWS];
};


// ----------------------------------------------------------------------
class ValuesTimer : public IlvTimer
{
public:
    ValuesTimer(IlvDisplay* dpy, IlvRandomMatrix* matrix)
        : IlvTimer(dpy), _matrix(matrix)
    {}
    virtual void	doIt() { _matrix->setValues(); }

private:
    IlvRandomMatrix*	_matrix;
};

// --------------------------------------------------------------------------
// Callback to stop/restart the timer
// --------------------------------------------------------------------------
static void
SwitchTimer(IlvGraphic* g, IlAny data)
{
    IlvToggle* toggle = (IlvToggle*)g;
    IlvTimer*  timer  = (IlvTimer*)data;
    if (toggle->getState())
	timer->run(0, 50);
    else
	timer->suspend();
}

// --------------------------------------------------------------------------
// Callback to change the threshold
// --------------------------------------------------------------------------
static void
SetThreshold(IlvGraphic* g, IlAny)
{
    IlvNumberField* field = (IlvNumberField*)g;
    IlBoolean error;
    IlInt value = field->getIntValue(error);
    if (!error)
	_STThreshold = value;
    else
	field->getDisplay()->bell();
}

// --------------------------------------------------------------------------
// Panel class for sample Random
// --------------------------------------------------------------------------
void
Random::initRandom()
{
    IlvDisplay* display = getDisplay();

    IlvFont* font = display->getFont("Helvetica", 14, IlvNormalFontStyle, "*");

    // Create the matrix that will display the numbers
    IlvRandomMatrix* mat =
	new IlvRandomMatrix(display, IlvRect(15, 30, 250, 190));
    mat->showGrid(IlTrue);
    mat->showScrollBar(IlvVertical);
    mat->setFont(font);
    srand((int)time(0));
    mat->setValues();
    addObject(mat);

    // Attach the matrix to the bottom of the container
    IlvSetAttachment(mat, IlvVertical,	IlvElasticAttach,	 0);
    IlvSetAttachment(mat, IlvBottom,	IlvFixedAttach,		15);
    
    // Create the number field that contains the timer period
    IlvNumberField* field  =
	new IlvNumberField(display, _STThreshold, IlvRect(370, 30, 50, 22));
    field->addFocusOutCallback(SetThreshold, (IlAny)mat);
    field->setMinInt(0);
    field->setMaxInt(1000);
    addObject(field);
    
    // Create the label located near the number field
    IlvLabel* label = new IlvLabel(display, IlvPoint(300, 45), "Threshold:");
    label->setFont(font);
    addObject(label);

    // Create the timer that will animate the matrix
    ValuesTimer* timer = new ValuesTimer(display, mat);
    
    // Create the toggle button that controls the timer
    IlvToggle* toggle =
	new IlvToggle(display, "Timer", IlvRect(370, 65, 70, 22));
    toggle->setState(IlTrue);
    toggle->setFont(font);
    toggle->addCallback(SwitchTimer, (IlAny)timer);
    addObject(toggle);
    
    // Starts the animation
    timer->run(0, 50);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageRandom(Pan* mainPanel)
{
    Random* panel = new Random(mainPanel,"huge.ilv");
    mainPanel->addPageNoteBook(panel, "Random", "random.txt");
}
