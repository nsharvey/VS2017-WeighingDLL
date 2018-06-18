// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/libdeps/src/libdeps.cpp
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
// Sample showing the Rogue Wave Views libraries dependencies displayed with
// the IlvHierarchicalLayout algorithm
// --------------------------------------------------------------------------

#include <ilviews/layout/hierarchical.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/grapher/links.h>
#include <ilviews/grapher/selinter.h>
#include <ilviews/grapher/polylink.h>
#include <ilviews/layout/linkconnect.h>
#include <ilviews/graphics/label.h>
#include <ilog/pool.h>
#include <ilog/xml.h>
#include <ilviews/util/ps.h>
#include <objsel.h>
#include <dialog.h>

#if defined(IL_STD)
#include <fstream>
#include <string>
#else
#include <fstream.h>
#include <string.h>
#endif
IL_STDUSE

static const char* title = "Rogue Wave Views libraries dependencies";
static const char* SPACE = " ";

// --------------------------------------------------------------------------
IlvDrawSelection*
MakeSelection(IlvManager* manager,
	      IlvGraphic* object)
{
    IlvGrapher* grapher = (IlvGrapher*)manager;
    if (grapher->isNode(object))
	return new GraphLayoutNodeSelection(manager->getDisplay(), object);
    else {
	if (grapher->isLink(object)) {
	    IlvLinkImage* link = (IlvLinkImage*)object;
	    if (grapher->isSelected(link->getFrom()) &&
		grapher->isSelected(link->getTo()))
		return new GraphLayoutLinkSelection(manager->getDisplay(),
						    object);
	    else
	        return new IlvGraphLinkSelection(manager->getDisplay(),
						 object);
	}
    }
    return new IlvReshapeSelection(manager->getDisplay(), object);
}

// --------------------------------------------------------------------------
class GraphLayoutSelectInteractor
    : public IlvGraphSelectInteractor
{
public:
    void doSelect();
};

// --------------------------------------------------------------------------
void
SelectPreviousNode(IlvGrapher* grapher,
		   IlvGraphic* obj)
{
    if (!obj || !grapher->isNode(obj))
	return;
    IlUInt count;
    if (!grapher->isSelected(obj))
	grapher->setSelected(obj, IlTrue);
    IlvLinkImage* const* links = grapher->getLinks(obj, count, IlvLinkTo);
    IlPoolOf(Pointer)::Lock((void**)links);
    IlvGraphic* previousNode;
    for (IlUInt i = 0 ; i < count ; ++i) {
	previousNode = links[i]->getFrom();
	if ((previousNode != obj) &&
	    !grapher->isSelected(previousNode))
	    SelectPreviousNode(grapher, previousNode);
	if (!grapher->isSelected(links[i]))
	    grapher->setSelected(links[i], IlTrue);
	else {
	    grapher->setSelected(links[i], IlFalse);
	    grapher->setSelected(links[i], IlTrue);
	}
    }
    IlPoolOf(Pointer)::UnLock((void**)links);
}

// --------------------------------------------------------------------------
void
GraphLayoutSelectInteractor::doSelect()
{
    IlvGraphSelectInteractor::doSelect();
    IlUInt count;
    IlvGrapher* grapher = (IlvGrapher*)getManager();
    IlvGraphic* const* sel  = grapher->getSelections(count);
    IlPoolOf(Pointer)::Lock((void**)sel);
    grapher->initReDraws();
    for (IlUInt i = 0 ; i < count ; ++i)
	if (grapher->isNode(sel[i]))
	    SelectPreviousNode(grapher, sel[i]);
    grapher->reDrawViews();
    IlPoolOf(Pointer)::UnLock((void**)sel);
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny arg)
{
    IlvHierarchicalLayout* layout = (IlvHierarchicalLayout*)arg;
    IlvGrapher* grapher = layout->getGrapher();
    layout->detach();
    delete layout;
    IlvDisplay* display = view->getDisplay();
    grapher->removeView(view);
    delete grapher;
    delete view;
    delete display;
    IlvExit(0);
}

#define INC 20

#define TRACE
#if defined(TRACE)
#define PRINT(str) cout str
#else
#define PRINT(str)
#endif

// --------------------------------------------------------------------------
void
ReadDataFile(IlvGrapher* grapher)
{
    IlvDisplay* display = grapher->getDisplay();
    IlUInt i = 50 + INC;
    ifstream stream(display->findInPath("libdeps.xml"));
    IlXmlDocument document;
    document.read(stream);
    IlXmlElement* root = document.getRootElement();
    for (IlXmlNodeIteratorI* libs = root->createChildrenIterator();
	 libs->hasMoreNodes(); ) {
	IlXmlNodeI* node = libs->getNextNode();
	if (node->getType() == IlXmlNodeI::Element) {
	    // This should be a <library> element
	    IlXmlElementI* lib = (IlXmlElementI*)node;
	    IlString libName(SPACE);
	    libName << lib->getAttributeValue("name") << SPACE;
	    IlvGraphic* sourceNode = grapher->getObject(libName);
	    if (!sourceNode) {
                // Create the node for that library
		sourceNode = new IlvFilledLabel(display, IlvPoint(i, i), libName);
		PRINT(<< "Adding library node:" << libName << endl);
		grapher->addNode(sourceNode, 1);
		grapher->setObjectName(sourceNode, libName);
		i += INC;
	    }
	    for (IlXmlNodeIteratorI* deps = lib->createChildrenIterator();
		 deps->hasMoreNodes(); ) {
		node = deps->getNextNode();
		// This should be a <dependency> element
		if (node->getType() == IlXmlNodeI::Element) {
		    IlXmlElementI* dep = (IlXmlElementI*)node;
		    IlString depName(SPACE);
		    depName << dep->getAttributeValue("library") << SPACE;
		    IlvGraphic* destNode = grapher->getObject(depName);
		    if (!destNode) {
			// Create the node for that library
			destNode = new IlvFilledLabel(display, IlvPoint(i, i),
						      depName);
			grapher->addNode(destNode, 1);
			grapher->setObjectName(destNode, depName);
			i += INC;
			PRINT(<< "Adding library node:" << depName << endl);
		    }
		    IlvOneLinkImage* link = new IlvOneLinkImage(display,
								IlvHorizontalLink,
								IlTrue,
								destNode,
								sourceNode);
		    grapher->addLink(link);
		    PRINT(<< "Adding link between");
		    PRINT(<< ((IlvFilledLabel*)destNode)->getLabel());
		    PRINT(<< "and");
		    PRINT(<< ((IlvFilledLabel*)sourceNode)->getLabel() << endl);
		}
	    }
	}
    }
}

// --------------------------------------------------------------------------
static void
PerformLayout(IlvManager* manager,
	      IlvView* view,
	      IlvEvent&,
	      IlAny arg)
{
    IlvHierarchicalLayout* layout = (IlvHierarchicalLayout*)arg;
    layout->setParametersUpToDate(IlFalse);
    layout->performLayout();
    manager->fitTransformerToContents(view, false);
    manager->zoomView(view,
		      IlvPoint(view->width()/2, view->height()/2),
		      .95f, .95f);
}

#define DUMPFILE "dump.ps"

// --------------------------------------------------------------------------
IlBoolean
DumpPartInLandscapePagePart(IlvPSDevice* psdevice,
			    const char* filename,
			    const IlvManager* manager,
			    const IlvView* view,
			    const IlvRect& sourceRect,
			    const IlvRect& pageRect)
{
    IlvDisplay* display = manager->getDisplay();
    // Initialize the PSDevice with the BoundingBox info ~~~~~~~~~~~~~
    if (psdevice->init(filename, (IlvRect*)&pageRect)) {
	display->initDump(psdevice);
	// Compute scale factors ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Because we are in landscape orientation, the horizontal ~~~
	// zooming factor is the ratio (pageWidth/areaHeight), and ~~~
	// the vertical zooming factor is the ratio ~~~~~~~~~~~~~~~~~~
	// (pageHeight/areaWidth) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IlFloat sx = (IlFloat)pageRect.w() / sourceRect.h(),
	    sy = (IlFloat)pageRect.h() / sourceRect.w();
	// Compute transformer (manager -> device) ~~~~~~~~~~~~~~~~~~~
	//   The (sourceRect.x(), sourceRect.y()) coordinates must   ~
	// be printed at (pageRect.x(), pageRect+pageRect.height()). ~
	//   The (sourceRect.x(), sourceRect.w(),                    ~
	//        sourceRect.y()+sourceRect.h()) coordinates must    ~
	// be printed at (pageRect.x()+pageRect.w(), pageRect.y()).  ~
	// Therefore:                                                ~
	//     sourceRect.y * sx + Tx = pageRect.x                   ~
	//   - sourceRect.x * sy + Ty = pageRect.bottom              ~
	IlvTransformer t((IlFloat)0, sx, -sy, (IlFloat)0,
			 pageRect.x()      - sx * sourceRect.y(),
			 pageRect.bottom() + sy * sourceRect.x());
	psdevice->setTransformer(t);
	// Draw manager in any port (not clipped) ~~~~~~~~~~~~~~~~~~~~
	manager->draw(display->screenPort(), manager->getTransformer(view));
	display->endDump();
	return IlTrue;
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
// Dump all the manager contents onto a specific area of the output page, in
// landscape mode
// --------------------------------------------------------------------------
IlBoolean
DumpAllInLandscapePagePart(IlvPSDevice* psdevice,
			   const char* filename,
			   IlvManager* manager,
			   const IlvView* view,
			   const IlvRect& pageRect)
{
    // Compute bounding box of the manager objects ~~~~~~~~~~~~~~~~~~~
    IlvRect sourceRect;
    manager->computeBBox(sourceRect, manager->getTransformer(view));
    return DumpPartInLandscapePagePart(psdevice, filename,
				       manager, view,
				       sourceRect, pageRect);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
MakeDump(IlvManager* mgr,
	 IlvView* view,
	 IlvEvent&,
	 IlAny)
{
    // Get container's IlvDisplay instance ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvDisplay* display = mgr->getDisplay();
    // Create a PostScript dump device ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvPSColorDevice psdevice(display);
    IlInt border = 20;
    IlvRect pageRect(border, border,
		     psdevice.getPaperWidth() - 2 * border,
		     psdevice.getPaperHeight() - 2 * border);
    DumpAllInLandscapePagePart(&psdevice, DUMPFILE, mgr, view, pageRect);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
SearchLib(IlvManager* mgr,
	  IlvView* view,
	  IlvEvent&,
	  IlAny)
{
    GraphLayoutDialog dialog(mgr->getDisplay(), "Search for the library:",
			     "SearchView", view->getSystemView());
    if (dialog.get(IlFalse)) {
	IlString objName(SPACE);
	objName << dialog.getLibName() << SPACE;
	IlvGraphic* obj = mgr->getObject(objName);
	if (obj) {
	    mgr->deSelectAll();
	    SelectPreviousNode((IlvGrapher*)mgr, obj);
	}
    }
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay(title, "", argc, argv);
    if (!display || display->isBad()) {
        if (display)
	    delete display;
	IlvFatalError("Cannot open display.");
	return -1;
    }
    IlString dataDir;
    dataDir << display->getEnvOrResource("ILVHOME", "home");
    dataDir << "/samples/layout/libdeps/data";
    display->prependToPath((const char*)dataDir);

    IlvGrapher* grapher = new IlvGrapher(display);
    IlvView* view = new IlvView(display,
				title,
				title,
				IlvRect(0, 0, 600, 400));
    grapher->addView(view);
    grapher->setDoubleBuffering(view, IlTrue);
    grapher->setInteractor(new GraphLayoutSelectInteractor(), view);
    grapher->setMakeSelection(MakeSelection);

    IlvHierarchicalLayout* layout = new IlvHierarchicalLayout();
    layout->attach(grapher);
    layout->setConnectorStyle(IlvLayoutCenteredPins);

    view->setDestroyCallback(Quit, layout);
    view->show();

    ReadDataFile(grapher);

    grapher->addAccelerator(PerformLayout, IlvKeyUp, IlvCtrlChar('l'),
			    0, layout);
    grapher->addAccelerator(PerformLayout, IlvKeyUp, ' ',
			    0, layout);
    grapher->addAccelerator(MakeDump, IlvKeyUp, IlvCtrlChar('p'));
    grapher->addAccelerator(SearchLib, IlvKeyUp, IlvCtrlChar('s'));
    grapher->addAccelerator(SearchLib, IlvKeyUp, IlvCtrlChar('f'));
    IlvMainLoop();
    return 0;
}
