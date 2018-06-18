// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/eventseq.h
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
// Declaration of event sequencer classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Eventseq_H
#define __IlvSt_Eventseq_H

#if !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif
#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if      !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif

// --------------------------------------------------------------------------
void IlvStInitializeEvent(IlvStudio*);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEventSubSequence
: public IlvStNamedObject {
public:
    IlvStEventSubSequence(const char* name);
    virtual ~IlvStEventSubSequence();
    //______________________________________________________________________
    virtual IlBoolean 	read(ILVSTDPREF istream&);
    virtual void 	write(ILVSTDPREF ostream&) const;
    virtual IlvStError*	execute(IlvStudio*);
    virtual IlvStError*	play(IlvStudio*);
    //______________________________________________________________________
    const char*		getEventFile() const { return _eventFile; }
    void		setEventFile(const char* str)
    	{ IlvStSetString(_eventFile, str); }
    const char*		getDataFile() const { return _dataFile; }
    void		setDataFile(const char* str)
    	{ IlvStSetString(_dataFile, str); }
    const char*		getDescription() const { return _description; }
    void		setDescription(const char* str)
    	{ IlvStSetString(_description, str); }
    IlUInt		getSpeed(IlvStudio*) const;
    IlInt		getSpeed() const { return _speed; }
    void		setSpeed(IlInt val) { _speed = val; }
    IlBoolean		getMovePointer() const { return _movePointer; }
    void		setMovePointer(IlBoolean val) { _movePointer = val; }
protected:
    char*		_eventFile;
    char*		_dataFile;
    char*		_description;
    IlInt		_speed;
    IlBoolean		_movePointer;
}; // class ILVSTUDIOCLASS IlvStEventSubSequence

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEventSequencer {
public:
    IlvStEventSequencer(IlvStudio* editor);
    ~IlvStEventSequencer();
    //______________________________________________________________________
    void		empty();
    IlvStError*		read(const char*);
    IlvStError*		read(ILVSTDPREF istream&);
    IlvStError*		write(const char*);
    IlvStError*		write(ILVSTDPREF ostream&);
    IlvStError*		play();
    //______________________________________________________________________
    const char*		getFileName() const            { return _filename; }
    void		setFileName(const char* fname)
    	{ IlvStSetString(_filename, fname); }
    IlvArray&		entries() { return _entries; }
protected:
    IlvStudio* 		_editor;
    IlvArray		_entries;
    char*		_filename;
}; // class ILVSTUDIOCLASS IlvStEventSequencer

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEventSequencerPanel
: public IlvStPanelHandler {
public:
    IlvStEventSequencerPanel(IlvStudio*);
    virtual void 	doReset();
    void		selectEntry(IlUShort);
    void		selectEntry();
    void		insertEntry();
    void		changeEntry();
    void		removeEntry();
    void		loadEntry();
    void		saveEntry();
    void		startRecording();
    void		stopRecording();
    void		playEntry();
    void		clearFields();
    void		applyEntry(IlvStEventSubSequence*);
    IlvStEventSubSequence* getSelectedEventSubSequence();
    void		setRecordingState();
    void		setNormalState();
protected:
    IlBoolean		_recording;
    IlBoolean		_playing;
}; // class ILVSTUDIOCLASS IlvStEventSequencerPanel

// --------------------------------------------------------------------------
#endif /* __IlvSt_Eventseq_H */
