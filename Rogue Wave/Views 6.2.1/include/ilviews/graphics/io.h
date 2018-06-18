// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/io.h
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
// Declaration of the IlvOutputFile and IlvInputFile classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Io_H
#define __Ilv_Graphics_Io_H

#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Util_Util_H)
#  include <ilviews/util/util.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif

class IlvGraphic;
class IlvGraphicHolder;
class IlHashTable;
class IlvClassInfo;
class IlvReferenceStreamer;

// --------------------------------------------------------------------------
//    Object to/from File I/O classes and methods :
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvOutputFile
{
public:
    IlvOutputFile(ILVSTDPREF ostream&);
    virtual ~IlvOutputFile();

    void		writeHeader(IlUInt count, IlvGraphic* const* objs);
    IlUInt		getPaletteIndex(IlvPalette* palette);
    IlvOutputFile&	operator<<(const IlvGraphic* obj);
    virtual const char* typeOf() const;

    inline
    ILVSTDPREF ostream&	getStream() const { return *_ostream; }
    inline void		setStream(ILVSTDPREF ostream& stream)
			{
			    _ostream = &stream;
			}
    IlvOutputFile&	writeReference(const IlvGraphic* object);
    IlBoolean		writeReference(IlvReferenceStreamer&, IlAny);
    IlBoolean		writeReference31(IlvReferenceStreamer&, IlAny);

    virtual
    IlvGraphic* const*	saveObjects(IlUInt		count,
				    IlvGraphic* const*	objects,
				    IlUInt&		totalCount);
    void		writePalettes() const;
    virtual void	saveMoreInfo(IlUInt count, IlvGraphic* const* objects);
    virtual void	writeObject(const IlvGraphic* obj);
    void		writeObjectBlock(const IlvGraphic* obj);
    inline
    operator ILVSTDPREF ostream&() { return *_ostream; }
    inline IlBoolean	isCompressed() const { return _compressed; }
    inline void		setCompressed(IlBoolean compressed)
			{
			    _compressed = compressed;
			}

    void		countObjects(IlvGraphic*);
    inline IlBoolean	isSavingScripts() const { return _saveScripts; }
    inline void		saveScripts(IlBoolean s) { _saveScripts = s; }
    inline IlBoolean	hasReference(IlAny ref) const
			{
			    return _references && _references->contains(ref);
			}
protected:
    ILVSTDPREF ostream*	_ostream;	// Output stream
    IlHashTable*	_palettes;	// Palette indexes
    IlArray		_classes;	// Graphic classes
    IlBoolean		_compressed;	// Is this output file compressed?
    IlHashTable*	_references;
    IlUInt		_referenceCount;

    void		searchPalettes(const IlvGraphic*);
    inline
    IlvGraphicHolder*	getHolder() const { return _holder; }
    inline void		setHolder(IlvGraphicHolder* holder)
			{
			    _holder = holder;
			}
private:
    IlUInt		_nGraphics;
    IlUInt		_nGraphicsHeap;
    IlvGraphic**	_graphics;
    IlvGraphicHolder*	_holder;
    IlBoolean		_saveScripts;
};

// --------------------------------------------------------------------------
// Error code for reading .ilv files (or data)
#define ILV_NO_OBJECTS			0x00000001
#define ILV_BAD_HEADER			0x00000002
#define ILV_BAD_VERSION			0x00000004
#define ILV_UNKNOWN_OBJECT_CLASS	0x00000008
#define ILV_UNKNOWN_PROPERTY_CLASS	0x00000010
#define ILV_UNEXPECTED_EOF		0x00000020
#define ILV_NULL_OBJECT			0x00000040
#define ILV_UNKNOWN_SCRIPT_LANGUAGE	0x00000080
#define ILV_UNKNOWN_OBJECT_INTERACTOR	0x00000100
#define ILV_UNKNOWN_SMARTSET_CLASS	0x00000200
#define ILV_INVALID_SCRIPT_FILE		0x00000400
#define ILV_FILE_NOT_FOUND		0x00000800
#define ILV_UNKNOWN_LAYER_CLASS		0x00001000


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvInputFile : public IlvBaseInputFile
{
public:
    IlvInputFile(ILVSTDPREF istream&);
    virtual ~IlvInputFile();

    inline IlvPalette*	getPalette(IlUInt num) const
			{
			    return _palettes[(int)num];
			}
    int			readHeader(IlvDisplay* d = 0 /* 2.1 compat. */);
    IlvGraphic*		readNext();
    IlAny		readReference(IlvReferenceStreamer&);
    IlvGraphic*		readReference(IlvDisplay*); // Pre-3.1
    IlAny		readReference31(IlvReferenceStreamer&);
    void		saveReference(IlAny);
    virtual
    IlvGraphic* const*	readObjects(IlvDisplay* display, IlUInt& count);
    virtual IlvGraphic*	readObject();
    IlvGraphic*		readObjectBlock(IlInt& number);

    // Reader phases
    static IlvGraphic*	ReadObject(IlvDisplay* display, const char* filename);
    IlBoolean		readBlock();
    virtual IlBoolean	parseBlock(const char* blockName);
    virtual
    IlvClassInfo*	readGraphicClass();

    // Reader notifications
    virtual void	headerRead(double      fileVersion, // creator version
				   const char* creationDate,
				   const char* fileBuilder);
    virtual void	palettesRead(IlUInt nPalettes);
    virtual void	graphicClassesRead(IlUInt nGraphicClasses);
    virtual void	graphicObjectsRead(IlUInt nGraphicObjects);
    virtual void	commentRead(const char* commentString);
    virtual void	unknownLineRead(const char* string);

    inline IlBoolean	isCompressed()   const { return _compressed; }
    inline const char*	getFileCreator() const { return _fileCreator; }
    inline IlDouble	getFileVersion() const { return _fileVersion; }

    inline IlBoolean	overwritePath() const { return _overwritePath; }
    inline void		setOverwritePath(IlBoolean overwritePath)
			{
			    _overwritePath = overwritePath;
			}
    virtual const char* typeOf() const;

protected:
    inline
    IlvGraphicHolder*	getHolder() const { return _holder; }
    inline void		setHolder(IlvGraphicHolder* holder)
			{
			    _holder = holder;
			}

    int			_lineno;
    IlUInt		_nPalettes;
    IlvPalette**	_palettes;
    IlUInt		_nObjects;
    IlvGraphic**	_objects;
    IlArray		_classes;     // Graphic classes
    IlBoolean		_compressed;  // Is this input file compressed?
    char*		_fileCreator; // The class that created this file
    IlDouble		_fileVersion;
    IlAny*		_references;
    IlUInt		_referenceCount;

private:
    IlvGraphicHolder*	_holder;
    IlBoolean		_overwritePath;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReferenceStreamer
{
public:
    IlvReferenceStreamer() {}
    virtual ~IlvReferenceStreamer();

    virtual void	writeReference(IlvOutputFile& os, IlAny object) = 0;
    virtual IlAny	readReference(IlvInputFile& is) = 0;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvIOStrings
{
public:
    static const char* GraphicClassesString;
    static const char* PalettesString;
    static const char* OldGraphicObjectsString;
    static const char* GraphicObjectsString;
    static const char* ViewsString;
    static const char* LayersString;
    static const char* ScriptString;
    static const char* SmartSetsString;
    static const char* SizeString;
    static const char* BackgroundString;
    static const char* BackgroundBitmapString;
    static const char* GeometryHandlersString;
    static const char* PropertiesString;
};

ILVVWSMODULEINIT(graphio);
#endif /* !__Ilv_Graphics_Io_H */
