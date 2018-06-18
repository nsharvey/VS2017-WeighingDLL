// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/readctrl.h
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
// Declaration of the ReadController class
// -------------------------------------------------------------------------
#ifndef _ReaderController_h_
#define _ReaderController_h_

#include <ilviews/ilv.h>
#include <ilviews/manager/manager.h>
#include <ilviews/gadgets/notebook.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/idialog.h>

#include <ilviews/graphics/selector.h>
#include <ilviews/graphics/label.h>

#include <ilviews/maps/maps.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/scalefilter.h>

#include <ilviews/maps/projection/project.h>


#include "desktop.h"
#include "prjselector.h"
#include "adpselect.h"
#include "paleditor.h"
#include "scalecombo.h"

class IldDbms;

// -------------------------------------------------------------------------
class ReaderController
{
public:
    ReaderController(IlvDisplay* ,
		     IlvSystemView transientFor = 0);
    ReaderController(IlvDisplay*,
		     PaletteEditor*,
		     IlvClassInfo*);
    virtual ~ReaderController();

    // Shows this readercontroller
    IlBoolean getParameters();
    // Shows this readercontroller
    void show();
    // Hides this reader controller
    void hide();

    // Specific inits based on readers
    void initReaderSpecific(IlvMapFeatureIterator*, const char* fileName);
    void initShapeParameters(IlvMapFeatureIterator*, const char* fileName);
    void initCADRGParameters(IlvMapFeatureIterator* reader);
    void initDTEDParameters(IlvMapFeatureIterator* reader);
    void initGeoTIFFParameters(IlvMapFeatureIterator* reader);

    // Requesting parameters
    void addRendererEditorPage(IlvClassInfo* geomclass);
    IlvPalette* getFillPalette() const;
    IlvPalette* getLinePalette() const;
    IlvFeatureRenderer* getRenderer();
    void setPaletteEditor(PaletteEditor* pe)
	{ paletteEditor = pe; }

    void setRequestingForSourceProjection(IlBoolean set);
    IlBoolean isRequestingForSourceProjection() const;
    void addSourceProjectionRequestPage();

    void setRequestingForDestProjection(IlBoolean set);
    IlBoolean isRequestingForDestProjection() const;
    IlvProjection* getDestProjection() const;
    void addDestProjectionRequestPage();

    void setRequestingForDestAdapter(IlBoolean set);
    IlBoolean isRequestingForDestAdapter() const;
    IlvMapAdapter* getDestAdapter(const IlvProjection* p) const;
    void addDestAdapterRequestPage();

    void setRequestingForLOD(IlBoolean set);
    IlBoolean isRequestingForLOD() const;
    IlBoolean isLOD() const;
    void addLODRequestPage();

    void setRequestingForLODTileSize(IlBoolean set);
    IlBoolean isRequestingForLODTileSize() const;

    void setRequestingForVisibilityFilter(IlBoolean set);
    IlBoolean isRequestingForVisibilityFilter() const;
    void addVisibilityFilterPage();
    IlvScaleVisibilityFilter* getVisibilityFilter();

    // Returns the size of a tile, converted to the specified destUnit.
    // In case destUnit is 0, the returned value is in km.
    void getLODTileSize(IlvCoordinate& result,
			const IlvUnitConverter* destUnit = 0);

    // Request for an area of interest
    void setRequestingForAOI(IlBoolean set);
    IlBoolean isRequestingForAOI() const;
    void getAOI(IlvCoordinate &UL,
		IlvCoordinate &LR);

#if defined(HAS_SDO_SUPPORT)
    void setRequestingForSDOLayer(IldDbms* dbms);
    IlBoolean isRequestingForSDOLayer() const;
    void addSDOLayerPage();
    char* getSDOLayerTableName();
    char* getSDOLayerGeometryName();
#endif

    void setRequestingForAttributes(IlBoolean set);
    IlBoolean isRequestingForAttributes() const;
    IlBoolean isAttachingAttributes() const;
    void addAttributeRequestPage();

    IlBoolean isAutoHidding() const { return autohide; }

    virtual void cancelClicked();
    virtual void okClicked();

    IlvGadgetContainer* getContainer() const
	{ return container; }
    PaletteEditor* getPaletteEditor() const
	{ return paletteEditor; }
    IlvProjection* getSourceProjection() const
	{ return sourceProjection; }
    void setSourceProjection(IlvProjection* projection)
	{ sourceProjection = projection; }
    IlvToggle* getPreviewToggle() const
	{ return previewToggle; }
    IlvGadgetContainerRectangle* getLodParams() const
	{ return lodParams; }
    IlvGadgetContainerRectangle* getAoiParams() const
	{ return aoiParams; }
    IlvNotebookPage* getDestProjectionRequestPage() const
	{ return destProjectionRequestPage; }
    IlBoolean setRequestForDestProjection(IlBoolean request)
	{ return requestForDestProjection = request; }
    
protected:
    IlvFeatureRenderer* getEditedCurveRenderer();
    IlvFeatureRenderer* getEditedAreaRenderer();
    IlvFeatureRenderer* getEditedPointRenderer();

    IlvGadgetContainer* container;
    // the notebook and its pages
    IlvNotebook* notebook;
    IlvButton* okButton;
    IlvButton* cancelButton;

    PaletteEditor* paletteEditor;
private:
    // for internal use
    void setStatus(IlBoolean s) { status = s; }
    void createPages();

    IlvDisplay* display;

    IlvNotebookPage* rendererEditorPage;
    IlvNotebookPage* sourceProjectionRequestPage;
    IlvNotebookPage* destProjectionRequestPage;
    IlvNotebookPage* destAdapterRequestPage;
    IlvNotebookPage* lodRequestPage;
#if defined(HAS_SDO_SUPPORT)
    IlvNotebookPage* sdoLayerRequestPage;
#endif
    IlvNotebookPage* visibilityFilterPage;
    IlvNotebookPage* attributeRequestPage;

    IlBoolean status;
    IlBoolean autohide;

    IlBoolean requestForSourceProjection;
    IlvProjection* sourceProjection;
    ProjectionSelector* sourceProjectionPanel;

    IlBoolean requestForDestProjection;
    IlvProjection* destinationProjection;
    ProjectionSelector* destProjectionPanel;

    IlBoolean requestForDestAdapter;
    AdapterSelector* destAdapterPanel;

    IlBoolean requestForVisibilityFilter;
    ScaleCombo* largeScaleCombo;
    ScaleCombo* smallScaleCombo;

    IlBoolean requestForLOD;
    IlvSelector* lodSelector;
    IlvToggle*   previewToggle;
    IlvToggle*   lodToggle;
    IlvGadgetContainerRectangle* lodParams;
    IlvNumberField* tileWidthTF;
    IlvNumberField* tileHeightTF;

    IlBoolean requestForLODTileSize;

    IlvGadgetContainerRectangle* aoiParams;
    IlvNumberField* aoiULxTF;
    IlvNumberField* aoiULyTF;
    IlvNumberField* aoiLRxTF;
    IlvNumberField* aoiLRyTF;
    IlBoolean requestForAOI;

    IlvClassInfo* geometry;

    IlvToggle* loadAttributeToggle;
    IlBoolean requestForAttributes;

    IlBoolean pagesCreated;

#if defined(HAS_SDO_SUPPORT)
    IldDbms* sdoDbms;
    IlvStringList *sdoLayerList;
    IlUShort sdoLayerNameCount;
    char** sdoLayerNames;
#endif
};



#endif /* _ReaderController_h_ */
