// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/src/dxread.cpp
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
// Definition of the IlvDXFInput class
// --------------------------------------------------------------------------
#include <dxfincl/dxread.h>
#include <ilviews/base/memory.h>
#include <ilviews/util/pool.h>
#if defined(ILVSTD)
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>
ILVSTDUSE
#else
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#endif

// Comment the following line to get IlvSpline for ARC and CIRCLE entities,
// instead of IlvArc and IlvEllipse, that cannot rotate properly
// There is a bug in Views 2.3 on the start angle. Do not use this option
// without the patch that fixes it.
// #define ARCSARESPLINES

// Uncomment this line not to use the IlogViews Vectorial Fonts.
// This will speed up the drawing, and let the generated file
// readable by many editors, but texts won't zoom...
// #define NO_VECTFONTS

// Uncomment this line not to use the TrueType Fonts on Windows.
// Although not as nice, the Hershey fonts that will be used are
// both faster and more accurate.
// #define NO_TRUETYPE

// #define DEBUG

typedef IlShort		DXFint16;   // Must be 16 bits!!
typedef IlInt		DXFint32;   // Must be 32 bits!!
typedef IlDouble	DXFfloat64; // Must be 64 bits!!

#define			binaryFormatHeaderLength 22
static const char*	binaryFormatHeader = "AutoCAD Binary DXF\015\012\032";
static char		readAheadBuffer[binaryFormatHeaderLength];
static int		readAheadCount;
static int		readAheadDecount;

// --------------------------------------------------------------------------
// _ltypes is a DXFList(DXFList(_group))
// _layers is a DXFList(DXFList(_group))

// --------------------------------------------------------------------------
static char buffer[512];

class DXFGroup
{
public:
    DXFGroup() : _code(-1), _type(badVal), _next(0) { release(); }
    DXFGroup(const DXFGroup& source)
    : _code(-1), _type(badVal), _next(0)
    {
	release();
	_code = source._code;
	_type = source._type;
	switch (source._type) {
	case int16Val: _value.int16Val = source._value.int16Val; break;
	case int32Val: _value.int32Val = source._value.int32Val; break;
	case floatVal: _value.floatVal = source._value.floatVal; break;
	case stringVal:
	    _value.stringVal =
		strcpy(new char[strlen(source._value.stringVal)+1],
		       source._value.stringVal);
	    break;
	default:
	    _code = -1;
	}
    }
    void	release()
		{
		    _code = -1;
		    if (_type == stringVal)
			delete [] _value.stringVal;
		    _type = badVal;
		    _value.stringVal = 0;
		    _next = 0;
		}
    void	setI16(int code, DXFint16 value)
		{
		    release();
		    _code = code;
		    _type = int16Val;
		    _value.int16Val = value;
		}
    void	setI32(int code, DXFint32 value)
		{
		    release();
		    _code = code;
		    _type = int32Val;
		    _value.int32Val = value;
		}
    void	set(int code, DXFfloat64 value)
		{
		    release();
		    _code = code;
		    _type = floatVal;
		    _value.floatVal = value;
		}
    void	set(int code, const char* value)
		{
		    release();
		    _code = code;
		    _type = stringVal;
		    _value.stringVal =
			strcpy(new char[strlen(value)+1], value);
		}
    int		getCode() const { return _code; }
    DXFint16	getInt16() const { return _value.int16Val; }
    DXFint32	getInt32() const { return _value.int32Val; }
    DXFfloat64	getFloat() const { return _value.floatVal; }
    const char* getString() const { return _value.stringVal; }
    int		getVal(DXFint16&   val) const
		{
		    return (_type == int16Val)
			? (val = _value.int16Val, 1)
			: 0;
		}
    int		getVal(DXFint32&   val) const
		{
		    return (_type == int32Val)
			? (val = _value.int32Val, 1)
			: 0;
		}
    int		getVal(DXFfloat64& val) const
		{
		    return (_type == floatVal)
			? (val = _value.floatVal, 1)
			: 0;
		}
    int		getVal(char*& val) const
		{
		    return (_type == stringVal)
			? (val = _value.stringVal, 1)
			: 0;
		}
    int		match(int code, const char* string)
		{
		    return ((code == _code) &&
			    (_type == stringVal) &&
			    !ILVSTRCASECMP(string, _value.stringVal));
		}
#if defined(DEBUG)
    ostream&	print(ostream& out) const
		{
		    out << "[Code = " << _code << ", Value = ";
		    DXFint16 i;
		    int ok = getVal(i);
		    if (ok)
			out << i << " [i16]";
		    else {
			DXFint32 j;
			ok = getVal(j);
			if (ok)
			    out << j << " [i32]";
			else {
			    DXFfloat64 d;
			    ok = getVal(d);
			    if (ok)
				out << d;
			    else {
				char* s;
				ok = getVal(s);
				if (ok)
				    out << s;
				else
				    out << "(unknown value)";
			    }
			}
		    }
		    return out << "]";
		}
#endif /* DEBUG */
    DXFGroup*	getNext() const { return _next; }
    void	setNext(DXFGroup* next) { _next = next; }

private:
    int		_code;
    enum {
	badVal,
	stringVal,
	int16Val,
	int32Val,
	floatVal
    }		_type;
    union {
	DXFint16      int16Val;
	DXFint32      int32Val;
	DXFfloat64 floatVal;
	char*      stringVal;
    }		_value;
    DXFGroup*	_next;
};

// --------------------------------------------------------------------------
#if defined(DEBUG)
ostream&
operator<<(ostream& o, const DXFGroup& g)
{
    return g.print(o);
}
#endif /* DEBUG */

// --------------------------------------------------------------------------
class DXFList
{
public:
    DXFList(IlAny element)
    : _element(element),
      _data(0),
      _next(0),
      _last(0)
    {}
    IlUInt	getLength() const
		{
		    IlUInt l = 1;
		    for (DXFList* list = (DXFList*)this;
			 list->_next;
			 list = list->_next)
			++l;
		    return l;
		}
    IlAny	getElement() const { return _element; }
    IlAny	getData() const { return _data; }
    void	setData(IlAny data) { _data = data; }
    DXFList*	getNext() const { return _next; }
    void	setNext(DXFList* next) { _next = next; }
    DXFList*	append(IlAny element)
		{
		    if (!_last)
			_last = this;
		    DXFList* newElement = new DXFList(element);
		    _last->_next = newElement;
		    _last = newElement;
		    return newElement;
		}
private:
    IlAny	_element;
    IlAny	_data;
    DXFList*	_next;
    DXFList*	_last;
};

// --------------------------------------------------------------------------
class DXFGroupList : public DXFList
{
public:
    DXFGroupList(DXFGroup* newGroup) : DXFList(newGroup) {}

    DXFGroupList*	getNextGroup() const 
			{
			    return (DXFGroupList*)getNext();
			}
    DXFGroupList*	addGroup(DXFGroup* newGroup)
			{
			    return (DXFGroupList*)
				append(new DXFGroup(*newGroup));
			}
    DXFGroup*		getGroup() const { return (DXFGroup*)getElement(); }
    DXFGroup*		getGroup(int code) const
			{
			    for (DXFGroupList* list = (DXFGroupList*)this;
				 list;
				 list = list->getNextGroup())
				if (list->getGroup()->getCode() == code)
				    return list->getGroup();
			    return 0;
			}
    DXFint16		getInt16(int group)
			{
			    DXFGroup* g = getGroup(group);
			    return g ? g->getInt16() : (DXFint16)0;
			}
    DXFint32		getInt32(int group)
			{
			    DXFGroup* g = getGroup(group);
			    return g ? g->getInt32() : 0;
			}
    DXFfloat64		getFloat(int group)
			{
			    DXFGroup* g = getGroup(group);
			    return (DXFfloat64)(g ? g->getFloat() : 0);
			}
    const char*		getString(int group)
			{
			    DXFGroup* g = getGroup(group);
			    return g ? g->getString() : 0;
			}
#if defined(DEBUG)
    ostream&		print(ostream& out) const
			{
			    out << "length = " << getLength() << endl;
			    for (DXFGroupList* list = (DXFGroupList*)this;
				 list;
				 list = list->getNextGroup())
				out << "  " << *(list->getGroup()) << endl;
			    return out;
			}
#endif /* DEBUG */
};

// --------------------------------------------------------------------------
class DXFGroupListList : public DXFList
{
public:
    DXFGroupListList(DXFGroupList* newGroupList)
    : DXFList(newGroupList) {}
    DXFGroupListList*	getNextGroupList() const
			{
			    return (DXFGroupListList*)getNext();
			}
    DXFGroupList*	getGroupList() const
			{
			    return (DXFGroupList*)getElement();
			}
    void		addGroupList(DXFGroupList* newGroupList)
			{
			    append(newGroupList);
			}
#if defined(DEBUG)
    ostream&		print(ostream& out) const
			{
			    out << "length = " << getLength() << endl;
			    for (DXFGroupListList* list =
				     (DXFGroupListList*)this;
				 list;
				 list = list->getNextGroupList()) {
				out << "  ";
				list->getGroupList()->print(cerr);
			    }
			    return out;
			}
#endif /* DEBUG */
};

// --------------------------------------------------------------------------
IlvDXFInput::IlvDXFInput(istream& stream)
: _stream(stream),
  _transformer((IlvTransfoParam)1,  (IlvTransfoParam)0,
	       (IlvTransfoParam)0, -(IlvTransfoParam)1,
	       (IlvTransfoParam)0,  (IlvTransfoParam)0),
  _angbase((IlFloat)0),
  _angdir(0),
  _extmin((IlFloat)0., (IlFloat)0.),
  _extmax((IlFloat)0., (IlFloat)0.),
  _display(0),
  _objects(0),
  _binaryFormat(0),
  _group(new DXFGroup()),
  _groupReadAhead(IlFalse),
  _fileOffset(0),
  _ltypes(0),
  _layers(0),
  _blocks(0),
  _entities(0)
{
    readAheadCount = 0;
    readAheadDecount = 0;
    int loop;
    for (loop = 0; loop < binaryFormatHeaderLength; ++loop) {
        readAheadBuffer[loop] = (char)stream.get();
	if (binaryFormatHeader[loop] != readAheadBuffer[loop])
	    break;
    }
    if (loop == binaryFormatHeaderLength) {
	_binaryFormat = 1;
	_fileOffset = binaryFormatHeaderLength;
    }
    else
        stream.seekg(0, ios::beg);
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file.");
	    cleanUp();
	    break;
	}
	if (_group->match(0, "EOF"))
	    break;
	if (_group->match(0, "SECTION")) {
	    if (readSection()) {
		cleanUp();
		break;
	    }
	} else {
	    IlvFatalError("Bad group code %d at offset %ld. Should be [0 - SECTION]",
			  _group->getCode(), _fileOffset);
	    cleanUp();
	    break;
	}
    }
}

// --------------------------------------------------------------------------
IlvDXFInput::~IlvDXFInput()
{
    cleanUp();
}

// --------------------------------------------------------------------------
IlBoolean
IlvDXFInput::isBad() const
{
    return _entities ? IlFalse : IlTrue;
}

// --------------------------------------------------------------------------
void
IlvDXFInput::cleanUp()
{
    delete _ltypes;
    _ltypes = 0;
    if (_layers) {
	DXFGroupListList* layer = (DXFGroupListList*)_layers;
	while (layer) {
	    if (layer->getData())
		((IlvPalette*)(layer->getData()))->unLock();
	    layer = layer->getNextGroupList();
	}
	delete _layers;
	_layers = 0;
    }
    delete _entities;
    _entities = 0;
    if (_objects) {
	delete [] _objects;
	_objects = 0;
    }
}

// --------------------------------------------------------------------------
void
IlvDXFInput::translate(IlFloat dx, IlFloat dy)
{
    _transformer.translate(dx, dy);
}

// --------------------------------------------------------------------------
void
IlvDXFInput::scale(IlFloat fixedx, IlFloat fixedy, IlFloat sx, IlFloat sy)
{
    _transformer.scale(fixedx, fixedy, sx, sy);
}

// --------------------------------------------------------------------------
void
IlvDXFInput::rotate(IlFloat centerx, IlFloat centery, IlFloat angle)
{
    _transformer.rotate(centerx, centery, angle);
}

// --------------------------------------------------------------------------
inline int
Get(istream& s)
{
    return ((readAheadDecount < readAheadCount)
	    ? readAheadBuffer[readAheadDecount++]
	    : s.get());
}

// --------------------------------------------------------------------------
#define ISSPACE(c) (((c)==' ')||((c)=='\r')||((c)=='\t')||((c)=='\n'))
int
IlvDXFInput::readGroup()
{
    if (_groupReadAhead) {
	_groupReadAhead = IlFalse;
	return 0;
    }
    _group->release();
    if (_binaryFormat) {
	static int machineIsLSBFirst = -1;
	if (machineIsLSBFirst < 0) {
	    static int LSBtest = 1;
	    machineIsLSBFirst = (((char*)&LSBtest)[0] == 1);
	}
	int code = Get(_stream);
	++_fileOffset;
	if ((code < 0) || _stream.eof())
	    return 1;
	if ((code < 10) ||
	    ((code >= 1000) && (code < 1010))) {
	    int c;
	    char* p = buffer;
	    for (; ((c = Get(_stream)) != 0) && !_stream.eof(); ++p)
		*p = (char)c;
	    *p = 0;
	    for (p--; (p >= buffer) && (*p == '\015'); p--)
		*p = 0;
	    _group->set(code, buffer);
	    _fileOffset += IL_CAST(IlUInt, strlen(buffer+1));
	}
	else if (((code >= 10) && (code < 60)) ||
	    ((code >= 140) && (code < 148)) ||
	    ((code >= 210) && (code < 240) ||
	    ((code >= 1010) && (code < 1060)))) {
	    DXFfloat64 f;
	    _stream.read((char*)&f, 8);
	    if (!machineIsLSBFirst) {
		char* fp = (char*)&f;
		char c = fp[0];
		fp[0] = fp[7];
		fp[7] = c;
		c = fp[1];
		fp[1] = fp[6];
		fp[6] = c;
		c = fp[2];
		fp[2] = fp[5];
		fp[5] = c;
		c = fp[3];
		fp[3] = fp[4];
		fp[4] = c;
	    }
	    _group->set(code, f);
	    _fileOffset += 8;
	}
	else if (((code >= 60) && (code < 80)) ||
	    ((code >= 170) && (code < 176)) ||
	    ((code >= 1060) && (code < 1080))) {
	    DXFint16 i;
	    _stream.read((char*)&i, 2);
	    if (!machineIsLSBFirst) {
		char* ip = (char*)&i;
		char c = ip[0];
		ip[0] = ip[1];
		ip[1] = c;
	    }
	    _group->set(code, i);
	    _fileOffset += 2;
	}
    } else {
	char* p;
	do {
	    _stream.getline(buffer, 512);
	    ++_fileOffset;
	    for (p = buffer; *p && ISSPACE(*p); ++p)
		;
	} while (!*p && !_stream.eof());
	if (_stream.eof())
	    return 1;
	int code = atoi(buffer);
	_stream.getline(buffer, 512);
	++_fileOffset;
	if (_stream.eof())
	    return 1;
	if (code == 999)
	    return readGroup();
	if (code < 0)
	    return 1;
	if ((code < 10) ||
	    ((code >= 1000) && (code < 1010))) {
	    char* p = buffer+strlen(buffer)-1;
	    for (; (p >= buffer) && (*p == '\015'); p--)
		*p = 0;
	    _group->set(code, buffer);
	}
	else if (((code >= 10) && (code < 60)) ||
		   ((code >= 140) && (code < 148)) ||
		   ((code >= 210) && (code < 240) ||
		    ((code >= 1010) && (code < 1060)))) {
	    _group->set(code, atof(buffer));
	}
	else if (((code >= 60) && (code < 80)) ||
		   ((code >= 170) && (code < 176)) ||
		   ((code >= 1060) && (code < 1070))) {
	    _group->setI16(code, (DXFint16)atoi(buffer));
	}
	else if (((code >= 90) && (code < 99)) || (code == 1071)) {
	    _group->setI32(code, (DXFint32)atoi(buffer));
	}
    }
#if defined(DEBUG)
    // This is for debug purposes (displays all groups when they're read)
    cerr << *_group << " " << _fileOffset << endl << flush;
#endif
    return _stream.eof();
}

// --------------------------------------------------------------------------
void
IlvDXFInput::setViewsExtents(const IlvRect& r, IlBoolean keepRatio)
{
    if ((r.w() == 0) || (r.h() == 0) ||
	(_extmin.x() == _extmax.x()) ||
	(_extmin.y() == _extmax.y())) {
	IlvFatalError("Cannot set extents");
	return;
    }
    IlFloat sx = r.w()/(IlFloat)(_extmax.x()-_extmin.x()),
             sy = r.h()/(IlFloat)(_extmax.y()-_extmin.y());
    if (keepRatio) {
	if (sx < sy)
	    sy = sx;
	else
	    sx = sy;
    }
    IlFloat tx = r.x()-sx*_extmin.x(),
	     ty = r.bottom()+sy*_extmin.y();
    _transformer.setValues((IlFloat)sx, (IlFloat)0,
    			   (IlFloat)0, -(IlFloat)sy,
			   tx, ty);
}

// --------------------------------------------------------------------------
IlvPoint
IlvDXFInput::scale(const IlvFloatPoint& p) const
{
    IlvFloatPoint tp(p.x(), p.y());
    _transformer.apply(tp);
    IlvPoint r((IlvPos)tp.x(), (IlvPos)tp.y());
    return r;
}

// --------------------------------------------------------------------------
IlvGraphic**
IlvDXFInput::readObjects(IlUInt& n, IlvDisplay& display)
{
    n  = 0;
    if (!_entities)
	return 0;

    _display = &display;

#if defined(DEBUG)
    // This is for debug purposes
    if (_ltypes) {
	cerr << _ltypes->getLength() << " ltypes read:" << endl;
	DXFGroupListList* ltype = (DXFGroupListList*)_ltypes;
	int loop = 0;
	while (ltype) {
	    DXFGroup* group = ltype->getGroupList()->getGroup(2);
	    cerr << "\t" << loop << " "
		 << (group ? group->getString() : "(no group 2)") << endl;
	    ltype = ltype->getNextGroupList();
	    ++loop;
	}
    }
#endif
#if defined(DEBUG)
    // This is for debug purposes
    if (_layers) {
	cerr << _layers->getLength() << " layers read:" << endl;
	DXFGroupListList* layer = (DXFGroupListList*)_layers;
	int loop = 0;
	while (layer) {
	    DXFGroup* group = layer->getGroupList()->getGroup(2);
	    cerr << "\t" << loop << " "
		 << (group ? group->getString() : "(no group 2)")
		 << endl;
	    group = layer->getGroupList()->getGroup(62);
	    if (group)
		cerr << "\t\tforeground: "
		     << parseColor((int)group->getInt16())
		     << endl;
	    layer = layer->getNextGroupList();
	    ++loop;
	}
    }
#endif
#if defined(DEBUG)
    // This is for debug purposes
    if (_blocks) {
	cerr << _blocks->getLength() << " blocks read:" << endl;
	DXFGroupListList* block = (DXFGroupListList*)_blocks;
	int loop = 0;
	while (block) {
	    DXFGroup* group = block->getGroupList()->getGroup(2);
	    cerr << "\t" << loop << " "
		 << (group ? group->getString() : "(no group 2)")
		 << endl;
	    DXFGroupListList* entity =
		(DXFGroupListList*)(block->getGroupList()->getData());
	    if (entity) {
		int loop = 0;
		while (entity) {
		    DXFGroup* group = entity->getGroupList()->getGroup(0);
		    cerr << "\t\t" << loop << " "
			 << (group ? group->getString() : "(no group 0)")
			 << endl;
		    entity = entity->getNextGroupList();
		    ++loop;
		}
	    }
	    block = block->getNextGroupList();
	    ++loop;
	}
    }
#endif
#if defined(DEBUG)
    // This is for debug purposes
    if (_entities) {
	cerr << "Entities read:" << endl;
	DXFGroupListList* entity = (DXFGroupListList*)_entities;
	int loop = 0;
	while (entity) {
	    DXFGroup* group = entity->getGroupList()->getGroup(0);
	    cerr << "\t" << loop << " "
		 << (group ? group->getString() : "(no group 0)")
		 << endl;
	    entity = entity->getNextGroupList();
	    ++loop;
	}
    }
#endif

    if (_entities) {
	// Build the graphic objects from the entity records
	DXFGroupListList* entity = (DXFGroupListList*)_entities;
	n = 0;
	while (entity) {
	    DXFGroupList* thisEntity = entity->getGroupList();
	    IlvGraphic* g = createGraphicObject(thisEntity);
	    if (g) {
		++n;
		thisEntity->setData(g);
	    }
	    entity = entity->getNextGroupList();
	}
	_objects = new IlvGraphic* [n];
	IlvGraphic** objects = _objects;
	entity = (DXFGroupListList*)_entities;
	while (entity) {
	    DXFGroupList* thisEntity = entity->getGroupList();
	    if (thisEntity->getData()) {
		*objects = (IlvGraphic*)(thisEntity->getData());
		IlvRect bbox;
		(*objects)->boundingBox(bbox);
		++objects;
	    }
	    entity = entity->getNextGroupList();
	}
    }
    return _objects;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readSection()
{
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readSection [%d].", _fileOffset);
	    return 1;
	}
	if (_group->match(0, "ENDSEC"))
	    break;
	if (_group->match(2, "HEADER") && readHeader()) {
	    cleanUp();
	    break;
	}
	if (_group->match(2, "TABLES") && readTables()) {
	    cleanUp();
	    break;
	}
	if (_group->match(2, "BLOCKS") && readBlocks()) {
	    cleanUp();
	    break;
	}
	if (_group->match(2, "ENTITIES") && readEntities()) {
	    cleanUp();
	    break;
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readHeader()
{
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readHeader [%d].", _fileOffset);
	    return 1;
	}
	if (_group->match(9, "$ANGBASE")) {
	    readGroup(); // Should be a 50-group
	    _angbase = (double)_group->getFloat();
	}
	else if (_group->match(9, "$ANGDIR")) {
	    readGroup(); // Should be a 70-group
	    _angdir = (int)_group->getInt16();
	}
	else if (_group->match(9, "$EXTMIN")) {
	    while (1) {
		readGroup();
		if ((_group->getCode() == 9) ||
		    (_group->getCode() == 0)) {
		    _groupReadAhead = IlTrue;
		    break;
		}
		if (_group->getCode() == 10)
		    _extmin.x((IlFloat)_group->getFloat());
		if (_group->getCode() == 20)
		    _extmin.y((IlFloat)_group->getFloat());
	    }
	}
	else if (_group->match(9, "$EXTMAX")) {
	    while (1) {
		readGroup();
		if ((_group->getCode() == 9) ||
		    (_group->getCode() == 0)) {
		    _groupReadAhead = IlTrue;
		    break;
		}
		if (_group->getCode() == 10)
		    _extmax.x((IlFloat)_group->getFloat());
		if (_group->getCode() == 20)
		    _extmax.y((IlFloat)_group->getFloat());
	    }
	}
	if (_group->match(0, "ENDSEC")) {
	    _groupReadAhead = IlTrue;
	    break;
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readTables()
{
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readTables.");
	    return 1;
	}
	if (_group->match(0, "TABLE")) {
	    if (readGroup()) {
		IlvFatalError("Short file in readTables.");
		return 1;
	    }
	    if (_group->getCode() != 2) {
		IlvFatalError("Should be a 2 group at line/byte %ld.",
			      _fileOffset);
		return 1;
	    }
	    if (readTable(_group->getString()))
		return 1;
	}
	if (_group->match(0, "ENDSEC")) {
	    _groupReadAhead = IlTrue;
	    break;
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readTable(const char* /* tableName */)
{
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readTable.");
	    return 1;
	}
	if (_group->match(0, "LTYPE")) {
	    if (readLtype())
		return 1;
	}
	else if (_group->match(0, "LAYER")) {
	    if (readLayer())
		return 1;
	}
	else if (_group->match(0, "ENDTAB")) {
	    _groupReadAhead = IlTrue;
	    break;
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readLtype()
{
    DXFGroupList* newLtype = new DXFGroupList(new DXFGroup(*_group));
    if (!_ltypes)
	_ltypes = new DXFGroupListList(newLtype);
    else
	_ltypes->append(newLtype);
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readLtype.");
	    return 1;
	}
	if (_group->getCode() == 0) {
	    _groupReadAhead = IlTrue;
	    break;
	}
	newLtype->addGroup(_group);
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readLayer()
{
    DXFGroupList* newLayer = new DXFGroupList(new DXFGroup(*_group));
    if (!_layers)
	_layers = new DXFGroupListList(newLayer);
    else
	_layers->append(newLayer);
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readLayer.");
	    return 1;
	}
	if (_group->getCode() == 0) {
	    _groupReadAhead = IlTrue;
	    break;
	}
	newLayer->addGroup(_group);
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readBlocks()
{
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readBlocks [%d].", _fileOffset);
	    return 1;
	}
	if (_group->match(0, "BLOCK")) {
	    if (readGroup() || readBlock())
		break;
	}
	else if (_group->match(0, "ENDSEC"))
	    break;
    }
    return 0;
}

// --------------------------------------------------------------------------
int
IlvDXFInput::readBlock()
{
    DXFGroupList* currentBlock = new DXFGroupList(new DXFGroup(*_group));
    if (!_blocks)
	_blocks = new DXFGroupListList(currentBlock);
    else
	_blocks->append(currentBlock);
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readBlock.");
	    return 1;
	}
	if (_group->match(0, "ENDBLK"))
	    break;
	else if (_group->getCode() == 0) {
	    _groupReadAhead = IlTrue;
	    if (!readEntities()) {
		currentBlock->setData(_entities);
		_entities = 0;
	    }
	}
	else
	    currentBlock->addGroup(_group);
    }
    return 0;
}

// --------------------------------------------------------------------------
// This is called by readBlock and after the ENTITIES marker has been found
// --------------------------------------------------------------------------
int
IlvDXFInput::readEntities()
{
    DXFGroupList* currentEntity = 0;
    while (1) {
	if (readGroup()) {
	    IlvFatalError("Short file in readEntities.");
	    return 1;
	}
	if (_group->getCode() == 0) {
	    if (currentEntity) {
		if (!_entities)
		    _entities = new DXFGroupListList(currentEntity);
		else
		    _entities->append(currentEntity);
	    }
	    if (_group->match(0, "ENDBLK") || _group->match(0, "ENDSEC")) {
		_groupReadAhead = IlTrue;
		break;
	    }
	    currentEntity = new DXFGroupList(new DXFGroup(*_group));
	} else {
	    if (!currentEntity) {
		IlvFatalError("Group 0 in entities expected at line/byte %ld",
			      _fileOffset);
		return 1;
	    }
	    currentEntity->addGroup(_group);
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
const char*
IlvDXFInput::parseColor(int colorIndex) const
{
    switch (colorIndex & 0xF) {
    case  0: return "black";
    case  1: return "red";
    case  2: return "yellow";
    case  3: return "green";
    case  4: return "cyan";
    case  5: return "blue";
    case  6: return "magenta";
    case  7: return "black";
    case  8: return "gray";
    case 15: return "white";
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvColor*
IlvDXFInput::createColor(int colorIndex) const
{
    const char* colorName = parseColor(colorIndex);
    return colorName ? getDisplay()->getColor(colorName) :
	getDisplay()->defaultForeground();
}

// --------------------------------------------------------------------------
IlvLineStyle*
IlvDXFInput::createLineStyle(const char* /* lineStyleName */) const
{
    // LineStyle is not converted (yet)
    return getDisplay()->defaultLineStyle();
}

// --------------------------------------------------------------------------
// The parameter 'color' is optional, and defaults to -1.
// If 'color' is not '-1', then we must use this as the foreground color for
// this new palette
// --------------------------------------------------------------------------
IlvPalette*
IlvDXFInput::createPalette(const char* layerName, int color) const
{
    IlvColor* foreground = (color == -1) ? 0 : createColor(color);
    DXFGroupListList* layerList = (DXFGroupListList*)_layers;
    while (layerList) {
	DXFGroupList* layer = layerList->getGroupList();
	DXFGroup* group = layer->getGroup(2);
	if (group && !ILVSTRCASECMP(group->getString(), layerName)) {
	    if (layer->getData()) {
		IlvPalette* palette = (IlvPalette*)layer->getData();
		if (foreground)
		    return _display->getPalette(palette->getBackground(),
						foreground,
						palette->getPattern(),
						0,
						palette->getFont(),
						palette->getLineStyle(),
						0,
						IlvFillPattern);
		return palette;
	    }
	    if (!foreground) {
		DXFGroup* colorGroup = layer->getGroup(62);
		foreground = colorGroup
		    ? createColor((int)colorGroup->getInt16())
		    : _display->defaultForeground();
	    }
	    DXFGroup* lineStyleGroup = layer->getGroup(6);
	    IlvLineStyle* lineStyle = lineStyleGroup ?
		createLineStyle(lineStyleGroup->getString()) :
		_display->defaultLineStyle();
	    IlvPalette* palette =
		_display->getPalette(_display->defaultBackground(),
				     foreground,
				     _display->solidPattern(),
				     0,
				     _display->defaultFont(),
				     lineStyle,
				     0,
				     IlvFillPattern);
	    layer->setData(palette);
	    palette->lock();
	    return palette;
	}
	layerList = layerList->getNextGroupList();
    }
    return _display->getPalette(0, foreground);
}

// --------------------------------------------------------------------------
static DXFGroupListList*
GetBlock(const char* blockName, DXFGroupListList* blocks)
{
    while (blocks) {
	DXFGroup* group = blocks->getGroupList()->getGroup(2);
	if (group && !ILVSTRCASECMP(group->getString(), blockName))
	    return blocks;
	blocks = blocks->getNextGroupList();
    }
    IlvFatalError("IlvDXFInput::getEntitiesOfBlock::Unknown block %s",
		  blockName);
    return 0;
}

// --------------------------------------------------------------------------
DXFList*
IlvDXFInput::getEntitiesOfBlock(const char* blockName) const
{
    DXFGroupListList* block = GetBlock(blockName, (DXFGroupListList*)_blocks);
    return block ?
	(DXFGroupListList*)(block->getGroupList()->getData()) : 0;
}

// --------------------------------------------------------------------------
static char*
ParseDXFString(const char* inString, IlvFontStyle& flags)
{
    size_t	inLength	= strlen(inString);
    char*	outString	= IlPoolOf(Char)::Alloc(IL_CAST(IlUInt,
								inLength)*2 + 1);
    const char*	in		= inString;
    char*	out		= outString;
    flags = IlvNormalFontStyle;
    for (size_t count = 0; *in; ++in, ++count) {
	if ((count+3 < inLength) && !strncmp(in, "%%u", 3)) {
	    flags  = (IlvFontStyle)(flags | IlvUnderlinedFontStyle);
	    count += 2;
	    in    += 2;
	}
	else
	    *out++ = *in;
    }
    *out = 0;
    return outString;
}

// --------------------------------------------------------------------------
#include <ilviews/graphics/marker.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/polyline.h>
#if defined(ARCSARESPLINES)
#include <ilviews/graphics/spline.h>
#define ARCCLASS IlvSpline
#define CIRCLECLASS IlvClosedSpline
#else  /* !ARCSARESPLINES */
#include <ilviews/graphics/arc.h>
#include <ilviews/graphics/ellipse.h>
#define ARCCLASS IlvArc
#define CIRCLECLASS IlvEllipse
#endif  /* !ARCSARESPLINES */

#if !defined(NO_VECTFONTS)
#include <vfincl/vectlab.h>
#if defined(WINDOWS) && !defined(NO_TRUETYPE)
#include <vfincl/truetype.h>
IlvVirtualTrueTypeFont* vfont = new IlvVirtualTrueTypeFont("Times New Roman");
#else /* !WINDOWS || NO_TRUETYPE */
extern "C" IlvVirtualVectFont* IlvVirtualVectFont_romand();
IlvVirtualVectFont* vfont = IlvVirtualVectFont_romand();
#endif /* WINDOWS || NO_TRUETYPE */
#endif /* !NO_VECTFONTS */

IlvGraphic*
IlvDXFInput::createGraphicObject(DXFList* entityList) const
{
    static IlUInt     nPolylinePoints = 0;
    static IlvPoint*   polylinePoints  = 0;
    static IlvPalette* currentPolylinePalette = 0;
    static DXFint16       currentPolylineFlags = 0;
    static DXFGroupListList* insertAttribEntities = 0;

    DXFGroupList* entity = (DXFGroupList*)entityList;
    DXFGroup* typeGroup  = entity->getGroup(0);
    if (!typeGroup)
	return 0;
    const char* type = typeGroup->getString();
    DXFGroup* lineTypeGroup = entity->getGroup(6);
    DXFGroup* colorGroup =
	(lineTypeGroup && !ILVSTRCASECMP(lineTypeGroup->getString(),
					 "bylayer"))
	? 0 : entity->getGroup(62);
    DXFGroup* layerGroup = entity->getGroup(8);
    const char* layer = layerGroup ? layerGroup->getString() : 0;
    IlvPalette* palette = layer ?
	(colorGroup
	 ? createPalette(layer, colorGroup->getInt16())
	 : createPalette(layer)) : 0;
    IlvGraphic* graphic = 0;

    if (!ILVSTRCASECMP(type, "POINT"))
	graphic =
	    new IlvMarker(getDisplay(),
			  scale(IlvFloatPoint((IlFloat)entity->getFloat(10),
					      (IlFloat)entity->getFloat(20))),
			  IlvMarkerPlus, 4,
			  palette);
    else if (!ILVSTRCASECMP(type, "LINE"))
	graphic =
	    new IlvLine(getDisplay(),
			scale(IlvFloatPoint((IlFloat)entity->getFloat(10),
					    (IlFloat)entity->getFloat(20))),
			scale(IlvFloatPoint((IlFloat)entity->getFloat(11),
					    (IlFloat)entity->getFloat(21))),
			palette);
    else if (!ILVSTRCASECMP(type, "ARC")) {
	DXFfloat64 cx = entity->getFloat(10);
	DXFfloat64 cy = entity->getFloat(20);
	DXFfloat64 radius = entity->getFloat(40);
	IlvPoint ul = scale(IlvFloatPoint((IlFloat)(cx-radius),
					  (IlFloat)(cy-radius)));
	IlvPoint lr = scale(IlvFloatPoint((IlFloat)(cx+radius),
					  (IlFloat)(cy+radius)));
	DXFfloat64 startAngle = entity->getFloat(50);
	DXFfloat64 endAngle   = entity->getFloat(51);
	if (_angdir) {
	    startAngle = -startAngle;
	    endAngle   = -endAngle;
	}
	if (startAngle >  180)
	    startAngle -= (DXFfloat64)360.;
	if (startAngle < -180)
	    startAngle += (DXFfloat64)360.;
	DXFfloat64 angleRange = entity->getFloat(51)-startAngle;
	if (angleRange >  180.05)
	    angleRange -= 360;
	if (angleRange < -180)
	    angleRange += 360;
	graphic = new ARCCLASS(getDisplay(),
			       IlvRect(IlMin(ul.x(), lr.x()),
				       IlMin(ul.y(), lr.y()),
				       (IlvDim)(IlvAbs(ul.x()-lr.x())),
				       (IlvDim)(IlvAbs(ul.y()-lr.y()))),
			       (IlFloat)startAngle, (IlFloat)angleRange,
			       palette);
    }
    else if (!ILVSTRCASECMP(type, "CIRCLE")) { // CIRCLE entity
	DXFfloat64 cx = entity->getFloat(10);
	DXFfloat64 cy = entity->getFloat(20);
	DXFfloat64 radius = entity->getFloat(40);
	IlvPoint ul = scale(IlvFloatPoint((IlFloat)(cx-radius),
					  (IlFloat)(cy-radius)));
	IlvPoint lr = scale(IlvFloatPoint((IlFloat)(cx+radius),
					  (IlFloat)(cy+radius)));
	graphic = new CIRCLECLASS(getDisplay(),
				  IlvRect(IlMin(ul.x(), lr.x()),
					  IlMin(ul.y(), lr.y()),
					  (IlvDim)(IlvAbs(ul.x()-lr.x())+1),
					  (IlvDim)(IlvAbs(ul.y()-lr.y())+1)),
				  palette);
    }
    else if (!ILVSTRCASECMP(type, "POLYLINE")) { // POLYLINE entity
	currentPolylinePalette = palette;
	currentPolylineFlags   = entity->getInt16(70);
    }
    else if (!ILVSTRCASECMP(type, "VERTEX")) {
	DXFint16 flags = entity->getInt16(70);
	if (currentPolylinePalette &&
	    (!(flags & 128) || (flags & 64))) {
	    polylinePoints = IlvAllocPoints(nPolylinePoints+1);
	    polylinePoints[nPolylinePoints] =
		scale(IlvFloatPoint((IlFloat)entity->getFloat(10),
				    (IlFloat)entity->getFloat(20)));
	    ++nPolylinePoints;
	}
    }
    else if (!ILVSTRCASECMP(type, "SEQEND")) {
	if (currentPolylinePalette) {
	    if (currentPolylineFlags & 16)
		graphic = new IlvPolygon(getDisplay(),
					 nPolylinePoints,
					 polylinePoints,
					 currentPolylinePalette);
	    else {
		if (currentPolylineFlags & 1) {
		    polylinePoints = IlvAllocPoints(nPolylinePoints+1);
		    polylinePoints[nPolylinePoints] = polylinePoints[0];
		    ++nPolylinePoints;
		}
		graphic = new IlvPolyline(getDisplay(),
					  nPolylinePoints,
					  polylinePoints,
					  currentPolylinePalette);
	    }
	    nPolylinePoints = 0;
	    polylinePoints = 0;
	    currentPolylinePalette = 0;
	}
	else if (insertAttribEntities) {
	    insertAttribEntities = 0;
	    return 0;
	}
	else
	    IlvWarning("Unexpected SEQEND entity");
    }
    else if (!ILVSTRCASECMP(type, "LWPOLYLINE")) { // LWPOLYLINE entity
	DXFint32 nPoints = entity->getInt32(90);
	if (nPoints) {
	    polylinePoints = IlvAllocPoints(nPoints+1);
	    DXFint32 currentPoint = 0;
	    int xRead = 0;
	    int yRead = 0;
	    IlvFloatPoint p;
#if defined(linux) && (__GNUC__ >= 3)
	    // Bug in gcc3.02 parser
	    IlvFloat dummy = (IlFloat)entity->getFloat(10);
	    IlvFloatPoint(dummy,
			  (IlFloat)entity->getFloat(20));
#else /* !(linux && gnu3) */
	    IlvFloatPoint((IlFloat)entity->getFloat(10),
			  (IlFloat)entity->getFloat(20));
#endif /* !(linux && gnu3) */
	    for (DXFGroupList* cur = entity; (currentPoint < nPoints) && cur;
		 cur = cur->getNextGroup()) {
		if (cur->getGroup()->getCode() == 10) {
		    p.x((IlFloat)cur->getGroup()->getFloat());
		    xRead = 1;
		}
		else if (cur->getGroup()->getCode() == 20) {
		    p.y((IlFloat)cur->getGroup()->getFloat());
		    yRead = 1;
		}
		if (xRead && yRead) {
		    polylinePoints[currentPoint++] = scale(p);
		    xRead = 0;
		    yRead = 0;
		}
	    }
	    if (palette) {
		DXFint16 flags = entity->getInt16(70);
		if (flags & 16)
		    graphic = new IlvPolygon(getDisplay(),
					     nPoints,
					     polylinePoints,
					     palette);
		else {
		    if (currentPolylineFlags & 1) {
			polylinePoints[nPoints] = polylinePoints[0];
			++nPoints;
		    }
		    graphic = new IlvPolyline(getDisplay(),
					      nPoints,
					      polylinePoints,
					      palette);
		}
		nPolylinePoints = 0;
		polylinePoints = 0;
	    }
	}
    }
    else if (!ILVSTRCASECMP(type, "TEXT")) {
#if 1
	int hAlign = entity->getInt16(72);
	// This is not used, since Views doesn't have VAlignement on labels
	// int vAlign = entity->getInt16(73);
	IlvFontStyle flags;
	char* string = ParseDXFString(entity->getString(1), flags);
	double height = entity->getFloat(40);
	double xRatio = 0;
	if (entity->getGroup(41))
	    xRatio = entity->getFloat(41);
	IlvPoint hp = scale(IlvFloatPoint((IlFloat)0, (IlFloat)height));
	IlvPoint op = scale(IlvFloatPoint((IlFloat)0, (IlFloat)0));
	op.translate(-hp.x(), -hp.y());
	IlvPoint location(scale(IlvFloatPoint((IlFloat)
					      (entity->getGroup(11)
					       ? entity->getFloat(11)
					       : entity->getFloat(10)),
					      (IlFloat)
					      (entity->getGroup(21)
					       ? entity->getFloat(21)
					       : entity->getFloat(20)))));
#if !defined(NO_VECTFONTS)
	double angle = -entity->getFloat(50);
#if !defined(WINDOWS) || defined(NO_TRUETYPE)
	double slant = -entity->getFloat(51);
#endif /* !WINDOWS || NO_TRUETYPE */
	IlvVectLabel* label
	    = new IlvVectLabel(getDisplay(),
#if defined(WINDOWS) && !defined(NO_TRUETYPE)
			       new IlvTrueTypeFont(vfont,
						   (IlInt)op.y(), 0,
						   (IlFloat)0),
#else /* !WINDOWS || NO_TRUETYPE */
			       new IlvVectFont(vfont,
					       (IlInt)op.y(), (IlInt)op.y(),
					       (IlFloat)0,
					       (IlFloat)slant),
#endif /* WINDOWS || NO_TRUETYPE */
			       location,
			       string,
			       palette);
	if (xRatio != 0)
	    label->scale((IlFloat)xRatio, (IlFloat)1.);
	IlvRect bbox;
	label->boundingBox(bbox);
	if ((hAlign == 1) || (hAlign == 4)) {
	    label->translate(-(IlvPos)bbox.w()/2, 0);
	    if (hAlign == 4)
		label->translate(0, (IlvPos)bbox.h()/2);
	}
	else if (hAlign == 2)
	    label->translate(-(IlvPos)bbox.w(), 0);
	if (angle != 0)
	    label->rotate(location, (IlFloat)angle);
#else  /* NO_VECTFONTS */
	IlvLabel* label =
	    new IlvLabel(getDisplay(),
			 location,
			 ParseDXFString(entity->getString(1), flags),
			 palette);
	IlvFont* font = getDisplay()->getFont("helvetica", 24, flags);
	if (font)
	    label->setFont(font);
	IlvRect bbox;
	label->boundingBox(bbox);
	if ((hAlign == 1) || (hAlign == 4)) {
	    label->translate(-(IlvPos)bbox.w()/2, 0);
	    if (hAlign == 4)
		label->translate(0, -(IlvPos)bbox.h()/2);
	}
	else if (hAlign == 2)
	    label->translate(-(IlvPos)bbox.w(), 0);
#endif /* NO_VECTFONTS */
	graphic = label;
#else
	graphic =
	    new IlvLabel(getDisplay(),
			 scale(IlvFloatPoint((IlFloat)entity->getFloat(10),
					     (IlFloat)entity->getFloat(20))),
			 entity->getString(1));
#endif
    }
    else if (!ILVSTRCASECMP(type, "TRACE") ||
	!ILVSTRCASECMP(type, "SOLID") ||
	!ILVSTRCASECMP(type, "3DFACE")) {
	IlvPoint points[5];
	points[0] = scale(IlvFloatPoint((IlFloat)entity->getFloat(10),
					(IlFloat)entity->getFloat(20)));
	points[1] = scale(IlvFloatPoint((IlFloat)entity->getFloat(11),
					(IlFloat)entity->getFloat(21)));
	points[2] = scale(IlvFloatPoint((IlFloat)entity->getFloat(12),
					(IlFloat)entity->getFloat(22)));
	points[3] = scale(IlvFloatPoint((IlFloat)entity->getFloat(13),
					(IlFloat)entity->getFloat(23)));
	if (!ILVSTRCASECMP(type, "SOLID")) {
	    IlvPoint p(points[3]);
	    points[3] = points[2];
	    points[2] = p;
	    graphic = new IlvPolygon(getDisplay(), 4, points, palette);
	} else {
	    points[4] = points[0];
	    graphic = new IlvPolyline(getDisplay(), 5, points, palette);
	}
    }
    else if (!ILVSTRCASECMP(type, "INSERT")) {
	DXFGroupListList* entitiesList =
	    (DXFGroupListList*)getEntitiesOfBlock(entity->getString(2));
	if (entitiesList) {
	    DXFGroupListList* block =
		GetBlock(entity->getString(2), (DXFGroupListList*)_blocks);
	    DXFGroup* group;
	    group = entity->getGroup(41);
	    DXFfloat64 sx = group ? group->getFloat() : (DXFfloat64)1.;
	    group = entity->getGroup(42);
	    DXFfloat64 sy = group ? group->getFloat() : (DXFfloat64)1.;
	    if (((group = entity->getGroup(70)) != 0) &&
		(group->getInt16() != 1))
		IlvWarning("Column count %d for INSERT not supported",
			   group->getInt16());
	    if (((group = entity->getGroup(71)) != 0) &&
		(group->getInt16() != 1))
		IlvWarning("Row count %d for INSERT not supported",
			   group->getInt16());
	    if (((group = entity->getGroup(44)) != 0) &&
		(group->getFloat() != 0))
		IlvWarning("Column spacing %.2f for INSERT not supported",
			   group->getFloat());
	    if (((group = entity->getGroup(45)) != 0) &&
		(group->getFloat() != 0))
		IlvWarning("Row spacing %.2f for INSERT not supported",
			   group->getFloat());
#define PUBLICT (((IlvDXFInput*)this)->_transformer)
	    DXFGroup* attribGroup = entity->getGroup(66);
	    if (attribGroup && (attribGroup->getInt16() & 1))
		insertAttribEntities = entitiesList;
	    IlvTransformer saved(PUBLICT);
	    IlvTransformer localT;
	    localT.translate(-(IlFloat)block->getGroupList()->getFloat(10),
			     -(IlFloat)block->getGroupList()->getFloat(20));
	    localT.scale((IlFloat)0, (IlFloat)0, (IlFloat)sx, (IlFloat)sy);
	    group = entity->getGroup(50);
	    if (group)
		localT.rotate((IlFloat)0,
			      (IlFloat)0,
			      (IlFloat)group->getFloat());
	    localT.translate((IlFloat)entity->getFloat(10),
			     (IlFloat)entity->getFloat(20));
	    localT.compose(PUBLICT);
	    PUBLICT = localT;
	    IlvGraphicSet* graphicSet  = 0;
	    IlvGraphic*    firstGraphic = 0;
	    while (entitiesList) {
		DXFGroupList* thisEntity = entitiesList->getGroupList();
		IlvGraphic* graphic = createGraphicObject(thisEntity);
		if (graphic) {
		    if (graphicSet)
			graphicSet->addObject(graphic);
		    else if (firstGraphic) {
			graphicSet = new IlvGraphicSet();
			graphicSet->addObject(firstGraphic);
			graphicSet->addObject(graphic);
		    }
		    else
			firstGraphic = graphic;
		}
		entitiesList = entitiesList->getNextGroupList();
	    }
	    PUBLICT = saved;
#undef PUBLICT
	    graphic = graphicSet ? graphicSet : firstGraphic;
	    if (graphic)
		graphic->setPalette(palette);
	}
    }
    else if (!ILVSTRCASECMP(type, "ATTRIB")) {
	if (insertAttribEntities)
	    return 0;
	else
	    IlvWarning("Unexpected ATTRIB entity");
    }
    else if (!ILVSTRCASECMP(type, "ATTDEF"))
	return 0;
    else
	cerr << "Entity type " << type << " is not implemented" << endl;
    return graphic;
}
