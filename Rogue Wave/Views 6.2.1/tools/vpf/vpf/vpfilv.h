// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/vpfilv.h
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
// Declaration of the Rogue Wave Views VPF reader
// --------------------------------------------------------------------------
#ifndef _VPFILV_H
#define _VPFILV_H

#include <vpf/reader.h>
#include <vpf/featuretype.h>
#include <vpf/projectn.h>

#include <ilviews/manager/manager.h>
#include <ilviews/gadgets/idialog.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/gadgets/msglabel.h>

// --------------------------------------------------------------------------
class VpfIlvReader : public VpfReader
{
public:
    VpfIlvReader(IlvDisplay* display, const char* databasepathname);
    ~VpfIlvReader();
    // ____________________________________________________________
    // Accessors
    inline IlvDisplay*	getDisplay() { return _manager->getDisplay(); }
    inline IlvManager*	getManager() { return _manager; }
    inline int		getLayer() const { return _layer;  }
    inline void		setLayer(int layer) { _layer = layer; }
    // ____________________________________________________________

    virtual void	storeObject(IlvGraphic* object);

    virtual VpfCoordinate&	whereIs(double x, double y) const;

protected:
    void		loadingFeature(VpfUInt, VpfUInt);
    virtual void	createNode(const VpfCoordinate& where, void*);
    virtual void	createEdge(VpfInt count, VpfCoordinate* coords, void*);
    virtual void	createFace(VpfInt count, VpfCoordinate* coords, void*);
    virtual void	createText(const VpfCoordinate& where,
				   const char*          text,
				   void*);
private:
    IlvManager*		_manager;
    int			_layer;
    int			_percentage;
};

// --------------------------------------------------------------------------
class VpfIlvInfo
{
public:
    VpfIlvInfo(long index, const VpfFeatureType* type)
    : _index(index),
      _type(type),
      _palette(0),
      _markerSize(IlvDefaultMarkerSize),
      _markerType(IlvMarkerSquare)
    {}
    ~VpfIlvInfo();
    // ____________________________________________________________
    inline const VpfFeatureType*	getType() const { return _type; }
    char		getName() const;
    void		drawPreview(IlvPort * dst, const IlvRect & rect) const;
    inline long		getIndex() { return _index; }
    inline IlvPalette*	getPalette() const { return _palette; }
    void		setPalette(IlvPalette * palette);
    inline IlvMarkerType	getMarkerType() const { return _markerType; }
    inline void		setMarkerType(IlvMarkerType type)
			{
			    _markerType = type;
			}
    inline IlUShort	getMarkerSize() const { return _markerSize; }
    inline void		setMarkerSize(IlUShort size) { _markerSize = size; }

protected:
    long			_index;
    const VpfFeatureType*	_type;
    IlvPalette*			_palette;
    IlUShort			_markerSize;
    IlvMarkerType		_markerType;
};

// --------------------------------------------------------------------------
class NodeResourceDialog : public IlvDialog
{
public:
    NodeResourceDialog(IlvView* view, VpfIlvInfo* info);
    void			setMarkerStyle(IlvMarkerType style);
    void			setPaletteForeground(IlvColor* color);
    IlvColor*			getPaletteForeground() const;
    void			apply();
    inline IlvFilledRectangle*	getForegroundRect() const 
				{
				    return _foregroundRect;
				}
    inline IlvMarker*		getMarker() const { return _marker; }

protected:
    VpfIlvInfo*			_info;
    IlvFilledRectangle*		_foregroundRect;
    IlvMarker*			_marker;
};

// --------------------------------------------------------------------------
class EdgeResourceDialog : public IlvDialog
{
public:
    EdgeResourceDialog(IlvView* view, VpfIlvInfo* info);
    void			setPaletteLineWidth(IlUShort width);
    void			setPaletteLineStyle(IlvLineStyle* style);
    void			setPaletteForeground(IlvColor* color);
    IlvColor*			getPaletteForeground() const;
    void			apply();
    inline IlvFilledRectangle*	getForegroundRect() const
				{
				    return _foregroundRect;
				}
    inline IlvLine*		getLineWidth() const { return _lineWidth; }
    inline IlvLine*		getLineStyle() const { return _lineStyle; }

protected:
    VpfIlvInfo*			_info;
    IlvFilledRectangle*		_foregroundRect;
    IlvLine*			_lineWidth;
    IlvLine*			_lineStyle;
};

// --------------------------------------------------------------------------
class FaceResourceDialog : public IlvDialog
{
public:
    FaceResourceDialog(IlvView* view, VpfIlvInfo* info);
    void			setPalettePattern(IlvPattern* pattern);
    void			setPaletteForeground(IlvColor* color);
    IlvColor*			getPaletteForeground() const;
    inline IlvFilledRectangle*	getForegroundRect() const 
				{
				    return _foregroundRect;
				}
    inline IlvFilledRectangle*	getPatternRect() const { return _patternRect; }
    void			apply();

protected:
    VpfIlvInfo*			_info;
    IlvFilledRectangle*		_foregroundRect;
    IlvFilledRectangle*		_patternRect;
};

// --------------------------------------------------------------------------
class TextResourceDialog : public IlvDialog
{
public:
    TextResourceDialog(IlvView* view, VpfIlvInfo* info);
    void			setPaletteFont(IlvFont* font);
    void			setPaletteForeground(IlvColor* color);
    IlvColor*			getPaletteForeground() const;
    inline IlvFilledRectangle*	getForegroundRect() const
				{
				    return _foregroundRect;
				}
    inline IlvMessageLabel*	getText() const { return _text; }
    void			apply();

protected:
    VpfIlvInfo*			_info;
    IlvFilledRectangle*		_foregroundRect;
    IlvMessageLabel*		_text;
};

#endif /* !_VPFILV_H */
