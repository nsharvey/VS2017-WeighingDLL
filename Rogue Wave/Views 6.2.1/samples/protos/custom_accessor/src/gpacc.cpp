// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/custom_accessor/src/gpacc.cpp
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
// Definition of the GraphicPath accessor.
// ---------------------------------------------------------------------------

#include <ilviews/protos/grphnode.h>
#include <ilviews/graphics/path.h>
#include <ilviews/graphics/polypts.h>
#include <ilviews/base/ptarray.h>
#include "gpacc.h"

#if defined(IL_STD)
#include <iostream>
#include <cstring>
#include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#include <iostream.h>
#include <string.h>
#include <stdio.h>
#endif /* IL_STD */

// ---------------------------------------------------------------------------
// IlvGraphicPathAccessor
// ---------------------------------------------------------------------------

IlvPredefinedUserAccessorIOMembers(IlvGraphicPathAccessor)

IlvGraphicPathAccessor::IlvGraphicPathAccessor(const char* name,
					       const IlvValueTypeClass* type,
					       IlvDisplay* display,
					       const char* nodeName,
					       IlUInt polyLineCount,
					       const char** polyLineNames)
    : IlvUserAccessor(name, type),
      _display(display),
      _value((IlDouble)0),
      _nodeName(IlvGetSymbol(nodeName)),
      _polyLineCount(polyLineCount),
      _polyLineNames(0)
{
    _polyLineNames = new IlvSymbol*[_polyLineCount];
    for(IlUInt i = 0; i < _polyLineCount; i++)
	_polyLineNames[i] = IlvGetSymbol(polyLineNames[i]);
}

// --------------------------------------------------------------------------
IlvGraphicPathAccessor::IlvGraphicPathAccessor(const IlvGraphicPathAccessor& source)
    : IlvUserAccessor(source),
      _display(source._display),
      _value(source._value),
      _nodeName(source._nodeName),
      _polyLineCount(source._polyLineCount),
      _polyLineNames(0)
{
    _polyLineNames = new IlvSymbol*[_polyLineCount];
    for(IlUInt i = 0; i < _polyLineCount; i++)
	_polyLineNames[i] = source._polyLineNames[i];
}

// --------------------------------------------------------------------------
IlvGraphicPathAccessor::IlvGraphicPathAccessor(IlvDisplay* display,
					       IlvGroupInputFile& f)
    : IlvUserAccessor(display, f),
      _display(display),
      _value((IlDouble)0),
      _nodeName(0),
      _polyLineCount(0),
      _polyLineNames(0)
{
    char buffer[256];
    f.getStream() >> buffer;
    _nodeName = IlvGetSymbol(buffer);
    f.getStream() >> buffer;
    if(strcmp(buffer, "{") != 0){
	IlvFatalError("IlvGraphicPathAccessor: { expected");
	return;
    }

    IlArray names;
    for(; ; ){
	f.getStream() >> buffer;
	if(strcmp(buffer, "}") == 0)
	    break;
	names.add((IlAny)IlvGetSymbol(buffer));
    }

    _polyLineCount = names.getLength();
    _polyLineNames = new IlvSymbol*[_polyLineCount];
    for(IlUInt i = 0; i < _polyLineCount; i++){
	_polyLineNames[i] = (IlvSymbol*)names[i];
    }
}

// --------------------------------------------------------------------------
IlvGraphicPathAccessor::~IlvGraphicPathAccessor()
{
    delete[] _polyLineNames;
}

// --------------------------------------------------------------------------
void
IlvGraphicPathAccessor::write(IlvGroupOutputFile& f) const
{
    IlvUserAccessor::write(f);
    f.getStream() << IlvSpc() << _nodeName->name();
    f.getStream() << IlvSpc() << "{" << endl;
    f.addIndent(1);
    for(IlUInt i = 0; i < _polyLineCount; i++){
	f.indent();
	f.getStream() << _polyLineNames[i]->name() << endl;
    }
    f.addIndent(-1);
    f.indent();
    f.getStream() << "}" << endl;
}

// --------------------------------------------------------------------------
IlBoolean
IlvGraphicPathAccessor::changeValue(IlvAccessorHolder* object,
				    const IlvValue& val)
{
    // Get the moving node.
    //
    IlvGroupNode* movingNode =
	((IlvGroup*)object)->findNode(_nodeName->name());
    if (!movingNode){
	IlvWarning("Could not find moving node %s in group %s",
		   _nodeName,
		   object->getName());
	return(IlFalse);
    }

    // Get (and check) the polylines nodes.
    //
    IlvPointArray* paths = new IlvPointArray[_polyLineCount];
    IlUInt count = 0;
    for (IlUInt i = 0; i < _polyLineCount; i++){
	IlvGroupNode* node =
	    ((IlvGroup*)object)->findNode(_polyLineNames[i]->name());
	if (!node) {
	    IlvWarning("Could not find node %s in group %s",
		       _polyLineNames[i],
		       object->getName());
	    continue;
	}
	if (!node->isSubtypeOf(IlvGraphicNode::ClassInfo())) {
	    IlvWarning("Node %s.%s is not a graphic node",
		       object->getName(),
		       _polyLineNames[i]);
	    continue;
	}
	IlvGraphic* g = ((IlvGraphicNode*)node)->getGraphic();
	if (!g->isSubtypeOf(IlvPolyPoints::ClassInfo())) {
	    IlvWarning("Node %s.%s is not a poly-points",
		       object->getName(),
		       _polyLineNames[i]);
	    continue;
	}
	paths[count++].setPoints(((IlvPolyPoints*)g)->numberOfPoints(),
				 ((IlvPolyPoints*)g)->getPoints());
    }

    // Create a graphic path with the polypoints data
    //
    IlvGraphicPath grpath(_display, count, paths, IlFalse);

    // Get total lenght of path.
    //
    IlDouble length = grpath.getLocation((IlDouble)0);

    // Compute distance given the new value, which is a percentage.
    //
    _value = (IlDouble)val;
    if(_value < (IlDouble)0)
	_value = (IlDouble)0;
    if(_value > (IlDouble)100.0)
	_value = (IlDouble)100.0;
    IlDouble distance = _value * length / (IlDouble)100.0;

    // Get position of point at "distance" from beginning
    // of path.
    //
    IlvPoint p;
    IlDouble angle;

    if (grpath.getLocation(distance, &p, &angle) >= (IlDouble)0.0){
	if(count > 0 &&
	   paths[0].npoints() > 0){
	    p = paths[0].points()[0];
	} else {
	    p.move(0, 0);
	}
	angle = (IlDouble)0;
    }

    // Get moving node's size
    //
    IlvValue sizev[2] = {
	IlvValue("width"),
	IlvValue("height")
    };
    movingNode->queryValues(sizev, 2);

    // Move (and rotate if applicable) the moving node.
    //
    IlvValue newv[4] = {
	IlvValue("x", (IlInt)(p.x() - ((IlInt)sizev[0]) / 2)),
	IlvValue("y", (IlInt)(p.y() - ((IlInt)sizev[1]) / 2)),
	IlvValue("angle", angle),
	IlvValue("rotation", angle)
    };
    movingNode->changeValues(newv, 4);

    // All done !
    //
    return(IlTrue);
}

// -------------------------------------------------------------------------
IlvValue&
IlvGraphicPathAccessor::queryValue(const IlvAccessorHolder*,
				  IlvValue& val) const
{
    val = _value;
    return(val);
}

// ---------------------------------------------------------------------------
class IlvGraphicPathAccessorDescriptorClass : public IlvAccessorDescriptor
{
public:
    IlvGraphicPathAccessorDescriptorClass()
	: IlvAccessorDescriptor("GraphicPath: move a node along a set of polylines", Display,
				"graphic path %s...",
				IlTrue,
				&IlvValueDoubleType,
				2,
				IlTrue,
				"Node to move", &IlvNodeNameParameterType,
				IlvAccessorParameterAllNodesStr,
				"Polyline", &IlvNodeNameParameterType, "") {}
};

// ---------------------------------------------------------------------------
// ClassInfo stuff
// ---------------------------------------------------------------------------

#if defined(IlvDECLAREINITCLASS)
IlvPreRegisterUserAccessorClass(IlvGraphicPathAccessor);
ILVDEFINEINITCLASS(gpacc, \
IlvPostRegisterUserAccessorClass(IlvGraphicPathAccessor, IlvUserAccessor);)
#else  /* !IlvDECLAREINITCLASS */
IlvRegisterUserAccessorClass(IlvGraphicPathAccessor, IlvUserAccessor);
#endif /* !IlvDECLAREINITCLASS */
