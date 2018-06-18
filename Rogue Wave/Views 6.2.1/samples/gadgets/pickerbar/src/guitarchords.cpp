// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/src/guitarchords.cpp
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
// Definition of the GuitarChord class, representing the application.
// --------------------------------------------------------------------------
#include <guitarchords.h>
#include <ilviews/graphics/label.h>

// --------------------------------------------------------------------------
static void
Quit(IlvView*, IlAny guitarChordsArg)
{
    GuitarChords* guitarChords = IL_CAST(GuitarChords*, guitarChordsArg);
    delete guitarChords;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
SelectionChangedCB(IlvGraphic*, IlAny guitarChordsArg)
{
    IL_CAST(GuitarChords*, guitarChordsArg)->selectionChanged();
}

// --------------------------------------------------------------------------
GuitarChords::GuitarChords(IlvDisplay* display)
{
    _container = new IlvGadgetContainer(display,
	"GuitarChords", "Guitar Chord picker",
	IlvRect(0, 0, 240, 370), IlFalse, IlFalse);
    _container->setDestroyCallback(Quit, this);

    // Set up the UI
    IlvColor* background = display->getColor("snow");

    _container->addObject(new IlvLabel(display, IlvPoint(10, 20),
				       "Root note:"));
    // Root note picker
    _tonePicker = new TonePicker(display, IlvRect(30, 25, 180, 40));
    _tonePicker->setBackground(background);
    _container->addObject(_tonePicker);
    _tonePicker->setCallback(SelectionChangedCB, this);
    _tonePicker->setSelected(2); // The 'C' key is selected at startup

    _container->addObject(new IlvLabel(display, IlvPoint(10, 85),
	"Chord type:"));
    // Root note picker
    const char* chordTypes[] = { "M", "m", "7" };
    _typePicker = new PickerBar(display,
				sizeof(chordTypes)/sizeof(char*), chordTypes,
				IlvRect(50, 90, 140, 40));
    _typePicker->setBackground(background);
    _typePicker->setFont(display->getFont("%Arial-18-B"));
    _typePicker->setAntialiasingMode(IlvUseAntialiasingMode);
    _typePicker->setBarHorizontalMargin(10);
    _typePicker->setBarVerticalMargin(10);
    _typePicker->setKnobHorizontalMargin(5);
    _container->addObject(_typePicker);
    _typePicker->setCallback(SelectionChangedCB, this);
    _typePicker->setSelected(0); // The Major chord is selected at startup

    // Fret board
    _fretBoard = new FretBoard(display, IlvRect(20, 135, 200, 250));
    _fretBoard->setBackground(display->getColor("white"));
    _fretBoard->setAntialiasingMode(IlvUseAntialiasingMode);
    _container->addObject(_fretBoard);

    // Reflect selection on fret board
    SelectionChangedCB(0, this);
}

// --------------------------------------------------------------------------
GuitarChords::~GuitarChords()
{
    IlvDisplay* display = _container->getDisplay();
    delete _container;
    delete display;
}

// --------------------------------------------------------------------------
// The picker has a new selected root note.
// Set the proper chord shape on the fret board.
void
GuitarChords::selectionChanged()
{
    IlUInt chord = _tonePicker->getSelected();
    IlUInt type  = _typePicker->getSelected();
    switch (chord) {
    case 0: // A
	switch(type) {
	case 0: { // M
	    int fingers[] = { 2, 2, 3, 2, 4, 2 };
	    _fretBoard->setChord(3, fingers);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 2, 1, 3, 2, 4, 2 };
	    _fretBoard->setChord(3, fingers);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 2, 2, 4, 2 };
	    _fretBoard->setChord(2, fingers);
	    break;
	}
	}
	break;
    case 1: // B
	switch(type) {
	case 0: { // M
	    int fingers[] = { 2, 4, 3, 4, 4, 4 };
	    int barres[] = { 2, 1, 6 };
	    _fretBoard->setChord(3, fingers, 1, barres);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 2, 3, 3, 4, 4, 4 };
	    int barres[] = { 2, 1, 6 };
	    _fretBoard->setChord(3, fingers, 1, barres);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 2, 4, 4, 4 };
	    int barres[] = { 2, 1, 6 };
	    _fretBoard->setChord(2, fingers, 1, barres);
	    break;
	}
	}
	break;
    case 2: // C
	switch(type) {
	case 0: { // M
	    int fingers[] = { 2, 1, 4, 2, 5, 3 };
	    _fretBoard->setChord(3, fingers);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 2, 4, 3, 5, 4, 5, 6, -1 };
	    int barres[] = { 3, 1, 6 };
	    _fretBoard->setChord(4, fingers, 1, barres, 3);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 2, 1, 3, 3, 4, 2, 5, 3, 6, -1 };
	    _fretBoard->setChord(5, fingers);
	    break;
	}
	}
	break;
    case 3: // D
	switch(type) {
	case 0: { // M
	    int fingers[] = { 1, 2, 2, 3, 3, 2, 6, -1 };
	    _fretBoard->setChord(4, fingers);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 1, 1, 2, 3, 3, 2, 6, -1 };
	    _fretBoard->setChord(4, fingers);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 1, 2, 2, 1, 3, 2, 6, -1 };
	    _fretBoard->setChord(4, fingers);
	    break;
	}
	}
	break;
    case 4: // E
	switch(type) {
	case 0: { // M
	    int fingers[] = { 3, 1, 4, 2, 5, 2 };
	    _fretBoard->setChord(3, fingers);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 4, 2, 5, 2 };
	    _fretBoard->setChord(2, fingers);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 2, 3, 3, 1, 4, 2, 5, 2 };
	    _fretBoard->setChord(4, fingers);
	    break;
	}
	}
	break;
    case 5: // F
	switch(type) {
	case 0: { // M
	    int fingers[] = { 3, 2, 4, 3, 5, 3 };
	    int barres[] = { 1, 1, 6 };
	    _fretBoard->setChord(3, fingers, 1, barres);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 4, 3, 5, 3 };
	    int barres[] = { 1, 1, 6 };
	    _fretBoard->setChord(2, fingers, 1, barres);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 2, 4, 3, 2, 5, 3 };
	    int barres[] = { 1, 1, 6 };
	    _fretBoard->setChord(3, fingers, 1, barres);
	    break;
	}
	}
	break;
    case 6: // G
	switch(type) {
	case 0: { // M
	    int fingers[] = { 1, 3, 5, 2, 6, 3 };
	    _fretBoard->setChord(3, fingers);
	    break;
	}
	case 1: { // m
	    int fingers[] = { 4, 5, 5, 5 };
	    int barres[] = { 3, 1, 6 };
	    _fretBoard->setChord(2, fingers, 1, barres, 3);
	    break;
	}
	case 2: { // 7
	    int fingers[] = { 1, 1, 5, 2, 6, 3 };
	    _fretBoard->setChord(3, fingers);
	    break;
	}
	}
	break;
    }
    _fretBoard->reDraw();
}

// --------------------------------------------------------------------------
void
GuitarChords::run() {
    _container->show();
    IlvMainLoop();
}
