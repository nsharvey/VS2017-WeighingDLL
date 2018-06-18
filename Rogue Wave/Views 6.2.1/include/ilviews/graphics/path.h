// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/path.h
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
// Declaration of the IlvGraphicPath class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Path_H
#define __Ilv_Graphics_Path_H

#ifndef __Ilv_Base_Graphic_H
#include <ilviews/base/graphic.h>
#endif

enum IlvDrawRule {
    IlvStrokeOnly,
    IlvFillOnly,
    IlvStrokeAndFill
};

class IlvGraphicPath;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPathSteppingData
{
public:
    virtual void	init(const IlvGraphicPath* gp,
			     const IlvPointArray*  transformed,
			     const IlvTransformer* tr);
    virtual void	stepping();
    inline IlUInt	getUserStep() const { return _userStep; }
    inline IlAny	getUserArg() const { return _userArg; }
    inline const IlvGraphicPath*	getGraphicPath() const
					{
					    return _graphicPath;
					}
    inline const IlvTransformer*	getTransformer() const
					{
					    return _trans;
					}
    inline const IlvPointArray*		getTransformedPaths() const
					{
					    return _transfPaths;
					}
    inline IlUInt	getCurPath() const { return _curPath; }
    inline IlUInt	getCurSegment() const { return _curSegment;}
    inline const IlvPoint*	getCurPosition() const { return _curPos; }
    inline IlFloat	getAngle() const { return _angle; }

protected:
    IlvPathSteppingData(IlUInt userStep, IlAny userArg)
    : _userStep(userStep),
      _userArg(userArg)
    {}
    virtual ~IlvPathSteppingData() {}

    virtual IlBoolean	doIt() = 0;
    virtual IlBoolean	acceptPath();
    virtual IlBoolean	beginStepping();
    virtual void	endStepping();

    IlUInt			_userStep;
    IlAny			_userArg;
    const IlvGraphicPath*	_graphicPath;
    const IlvTransformer*	_trans;
    const IlvPointArray*	_transfPaths;
    IlUInt			_curPath;
    IlUInt			_curSegment;
    const IlvPoint*		_curPos;
    IlFloat			_angle;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPathDrawingData : public IlvPathSteppingData
{
public:
    IlvPathDrawingData(IlUInt step, IlvGraphic* object)
    : IlvPathSteppingData(step, (IlAny)object)
    {}
    // ____________________________________________________________
    inline void		initDraw(const IlvGraphicPath*	gp,
				 const IlvPointArray*	transformed,
				 IlvPort* 		port,
				 const IlvTransformer*	tr,
				 const IlvRegion*	reg)
			{
			    _port = port;
			    _clip = reg;
			    init(gp, transformed, tr);
			}
    virtual void	setForeground(IlvColor* foreground);
    virtual void	setBackground(IlvColor* background);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setMode(IlvDrawMode mode);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    inline IlvPort*	getPort() const { return _port; }
    inline const IlvRegion*	getClip() const { return _clip; }
protected:
    IlvPort*		_port;
    const IlvRegion*	_clip;
    virtual IlBoolean	doIt();
};


// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicPath : public IlvSimpleGraphic
{
public:
    IlvGraphicPath(IlvDisplay*		display,
		   IlUInt		count,
		   IlvPoint*		points,
		   IlBoolean		copyPoints = IlTrue,
		   IlvPalette*		palette    = 0);
    IlvGraphicPath(IlvDisplay*		display,
		   IlUInt		count,
		   IlvPointArray*	paths,
		   IlBoolean		copyPoints = IlTrue,
		   IlvPalette*		palette    = 0);
    virtual ~IlvGraphicPath();
    // ____________________________________________________________
    inline void		setDrawRule(IlvDrawRule val) { _drawRule = val; }
    inline IlvDrawRule	getDrawRule() const { return _drawRule; }
    inline IlUInt	getNumPaths() const { return _npaths; }
    inline const IlvPointArray*		getPaths() const { return _paths; }
    inline IlvPalette*	getBackgroundPalette() const { return _bgPal; }
    const IlvRect&	bbox() const;
    inline void		setBBoxExtent(IlUInt extent)
			{
			    _bboxExtent = extent;
			    _bboxReady = IlFalse;
			}
    inline IlUInt	getBBoxExtent() const { return _bboxExtent; }
    inline void		setPathDrawingData(IlvPathDrawingData *data)
			{
			    _stepData = data;
			}
    inline IlvPathDrawingData*	getPathDrawingData() const
				{
				    return _stepData;
				}
    virtual IlDouble	getLocation(IlUInt               count,
				    const IlvPointArray* paths,
				    IlDouble             distance = 0.,
				    IlvPoint*            pos      = 0,
				    IlDouble*            angle    = 0,
				    IlUInt*              path     = 0,
				    IlUInt*              segment  = 0) const;
    IlDouble		getLocation(IlDouble             distance,
				    IlvPoint*            pos      = 0,
				    IlDouble*            angle    = 0,
				    IlUInt*              path     = 0,
				    IlUInt*              segment  = 0,
				    IlvTransformer*      t        = 0) const;
    inline IlDouble	getLength() const
			{
			    return getLocation(_npaths, _paths);
			}
    inline IlDouble	getLength(const IlvPointArray& path) const
			{
			    return getLocation(1, &path);
			}

    // ____________________________________________________________
    virtual void	setForeground(IlvColor* fg);
    virtual void	setBackground(IlvColor* bg);
    virtual void	setPalette(IlvPalette* pal);
    virtual void 	setMode(IlvDrawMode mode);
    virtual void 	setAlpha(IlvIntensity);
    virtual void 	setAntialiasingMode(IlvAntialiasingMode);
    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGraphicPath);

protected:
    IlvGraphicPath(IlvDisplay*, IlvPalette* palette = 0);

    IlvDrawRule		_drawRule;
    IlvPalette*		_bgPal;		// used to fill the surface;
    IlUInt		_npaths;
    IlvPointArray*	_paths;
    IlvRect		_bbox;
    IlBoolean		_bboxReady;
    IlUInt		_bboxExtent;
    IlvPathDrawingData*	_stepData;
};

ILVVWSMODULEINIT(g0path);
#endif /* !__Ilv_Graphics_Path_H */
