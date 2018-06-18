// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/include/pickerbar.h
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
// Declaration of the Selector control.
// --------------------------------------------------------------------------
#ifndef __Ilv_Samples_Pickerbar_H
#define __Ilv_Samples_Pickerbar_H

#include <ilviews/base/gadget.h>

// --------------------------------------------------------------------------
class PickerBar
: public IlvGadget
{
public:
    PickerBar(IlvDisplay* display,
	      IlUInt nLabels, const char* const* labels,
	      const IlvRect& location);
    virtual ~PickerBar();

    // Number of labels
    inline IlUInt getLabelsCount() const
	{ return _nLabels; }
    inline static const IlvPoint* getShapePoints()
	{ return _Points; }
    // (IlUInt)-1: no selection
    inline IlUInt getSelected() const
	{ return _selected; }
    void   setSelected(IlUInt selected);
    inline IlBoolean isDrawingLabels() const
	{ return _drawLabels; }
    inline void      drawLabels(IlBoolean drawLabels)
	{ _drawLabels = drawLabels; }
    // Labels are copied
    void setLabels(IlUInt nLabels, const char* const* labels);
    // 0: Square angles, 100: perfect round
    void setRadiusRatio(IlUShort ratio);
    // How knobs are drawn
    inline IlvPalette* getKnobPalette() const
	{ return _knobPalette; }
    void setKnobPalette(IlvPalette* knobPalette);
    // The palette used to draw the bar background
    void setInvertedPalette(IlvPalette* palette);
    inline IlvPalette* getInvertedPalette() const
	{ return _invertedPalette; }

    // Customizing drawing
    // Default implementation returns the gadget's palette
    virtual IlvPalette* getLabelPalette(IlUInt index) const;
    // Default implementation returns the global knob palette
    virtual IlvPalette* getKnobPalette(IlUInt index) const;
    // Default implementation returns the global knob palette
    // If 0, no label is displayed.
    virtual IlvPalette* getKnobLabelPalette(IlUInt index) const;
    // The default implementation returns 0
    virtual IlvPos getKnobLabelOffset(IlUInt index) const;

    // The horizontal margin used by the picker bar
    inline IlvDim getBarHorizontalMargin() const
	{ return _barHorizontalMargin; }
    inline void   setBarHorizontalMargin(IlvDim horizontalMargin)
	{ _barHorizontalMargin = horizontalMargin; }
    // The vertical margin used by the picker bar
    inline IlvDim getBarVerticalMargin() const
	{ return _barVerticalMargin; }
    inline void   setBarVerticalMargin(IlvDim verticalMargin)
	{ _barVerticalMargin = verticalMargin; }
    // The horizontal margin used by the picker bar.
    // If the value is negative, the knob box is larger than
    // with the default width.
    inline IlvPos getKnobHorizontalMargin() const
	{ return _knobHorizontalMargin; }
    inline void   setKnobHorizontalMargin(IlvPos horizontalMargin)
	{ _knobHorizontalMargin = horizontalMargin; }
    // The vertical margin used by the picker bar
    inline IlvDim getKnobVerticalMargin() const
	{ return _knobVerticalMargin; }
    inline void   setKnobVerticalMargin(IlvDim verticalMargin)
	{ _knobVerticalMargin = verticalMargin; }
    // The margin between the knobs and the whole bounding box
    inline IlvDim getKnobsMargin() const
	{ return _knobsMargin; }
    inline void   setKnobsMargin(IlvDim knobsMargin)
	{ _knobsMargin = knobsMargin; }
    // The x-coordinate of the center of the indicated knob
    IlvPos getKnobPosition(IlUInt index, const IlvTransformer* t = 0) const;

    // IlvGraphic overloads
    virtual void	setBackground(IlvColor* background);
    virtual void        setFont(IlvFont* font);
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);

    // IlvGadget overloads
    virtual void	drawBackground(IlvPort*              dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion*      clip = 0) const;
    virtual void	drawFrame(IlvPort*		dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	drawContents(IlvPort*              dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion*      clip = 0) const;
    virtual void	drawFocus(IlvPort* dst,
				  const IlvPalette* palette,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion & region,
					   const IlvTransformer * t) const;
    virtual IlBoolean	classFocusable() const;
    virtual IlBoolean	handleEvent(IlvEvent& event);

    void selectNext();
    void selectPrevious();
protected:
    // The default implementation calls the main callback
    virtual void callSelectionCallback(IlUInt selected);
    // Draws the knob, based on the provided bbox
    virtual void	drawKnob(IlUInt           index,
				 IlvPort*         dst,
				 const IlvRect&   knobBox,
				 const IlvRegion* clip) const;

    // Returns a Bézier spline that describes the gadget's shape
    IlUInt computeShape(const IlvRect& box) const;
private:
    // Computes the global bounding box and the selected knob geometry.
    //   boundingBox: Set to the gadget's bounding box
    //   t:           The transformer that must be used
    //   knobCenter:  Set to the horizontal location of the knob's center
    //   knobBox:     Set to the knob's bounding box
    // Returns IlFalse if gadget too small to display knobs.
    IlBoolean getKnobGeometry(IlvRect& boundingBox,
			      const IlvTransformer* t,
			      IlvPos&  knobCenter,
			      IlvRect& knobBox) const;
    // Computes the specific geometry parameters of the indicated knob.
    // boundingBox: The golbal control bounding box, in the view
    //              coordinates system
    // knobIndex:   The knob index to query geometry for
    // knobCenter:  Set to the horizontal location of the knob's center
    // knobBox:     Set to the knob's bounding box
    void getKnobGeometry(const IlvRect& boundingBox,
			 IlvUInt        knobIndex,
			 IlvPos&        knobCenter,
			 IlvRect&       knobBox) const;
    IlUInt findKnob(const IlvRect& bBox, IlvPos x) const;
    void deleteLabels();

    IlBoolean handleButtonDown(IlvEvent& event);
    IlBoolean handleButtonDragged(IlvEvent& event);
    IlBoolean handleButtonUp(IlvEvent& event);

private:
    IlUInt    _nLabels;
    char**    _labels;
    IlUShort  _radiusRatio;
    IlUInt    _selected;
    IlBoolean _drawLabels;
    IlvDim   _barHorizontalMargin;
    IlvDim   _barVerticalMargin;
    IlvPos   _knobHorizontalMargin;
    IlvDim   _knobVerticalMargin;
    IlvDim   _knobsMargin;
    IlvPos   _knobLabelOffset;
    IlvPalette* _invertedPalette,
              * _labelsPalette,
              * _knobPalette,
	      * _invertedKnobPalette;
    static IlvPoint _Points[25];
    // Interaction data
    IlUInt _interactiveKnob;
    IlUInt _savedSelected;
};

#endif /* !__Ilv_Samples_Pickerbar_H */
