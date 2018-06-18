// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/readvpf.cpp
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
// Using the VpfIlvReader class to load Vpf/DCW data
// --------------------------------------------------------------------------
#include <vpf/vpfilv.h>
#include <vpf/error.h>
#include <vpf/database.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/theme.h>
#include <vpf/featureclass.h>
#include <vpf/attribute.h>
#include <vpf/set.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/manager/manager.h>
#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/manager/io.h>
#include <ilviews/gadgets/filesel.h>
#include <ilviews/gadgets/menubar.h>
#include <ilviews/gadgets/optmenu.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/arrowb.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/util/ps.h>
#include <ilviews/base/memory.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/util/runtime.h>

static IlvGadgetContainer* topview = 0;
static IlvView*            workingview = 0;
static IlvManagerViewInteractor* selectInteractor = 0;

static const char* defaultTitle = "Rogue Wave Views VPF Reader";

#if defined(VPFSTD)
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <cctype>
VPFSTDUSE
#else
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#endif
#include <ilviews/base/sstream.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1300) /* msvc7 */
typedef intptr_t VpfIntPtr;
#else  /* !msvc7. */
typedef long VpfIntPtr;
#endif /* !msvc7. */

// --------------------------------------------------------------------------
#include <vpf/xorlists.h>
static VpfProjection* projectors[10];

// --------------------------------------------------------------------------
// Main global variables: The IlvDisplay object, and the reader
static IlvDisplay*   display = 0;
static VpfIlvReader* reader  = 0;

// --------------------------------------------------------------------------
static void
Quit(IlvView* tv, IlAny)
{
    delete tv;
    delete selectInteractor;
    for (int loop = 0; projectors[loop]; loop++)
	delete projectors[loop];
    delete reader;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
QuitCB(IlvGraphic* g, IlAny)
{
    Quit(IlvContainer::getContainer(g), 0);
}

// --------------------------------------------------------------------------
static void
WaitCursor(IlBoolean f)
{
    IlvDisplay* d = topview->getDisplay();
    IlvCursor*  c = f ? d->waitCursor() : d->defaultCursor();
    topview->setCursor(c);
    workingview->setCursor(c);
    while (d->hasEvents())
	d->readAndDispatchEvents();
}

// --------------------------------------------------------------------------
static void
HandleErrors()
{
    VpfError* first = VpfErrorReporter::GetFirst();
    while (first) {
	class VPFSTDPREF strstream& stream = first->getStream();
	stream << '\0';
#ifdef IL_USING_STRINGSTREAM
	IlvFatalError("%s: %s", first->getWhere(), stream.str().c_str());
#else
	IlvFatalError("%s: %s", first->getWhere(), stream.str());
#endif
	first = first->getNext();
    }
    VpfErrorReporter::Clear();
}

// --------------------------------------------------------------------------
static IlvMenuBar*
GetMenuBar()
{
    return (IlvMenuBar*)topview->getObject("MenuBar");
}

// --------------------------------------------------------------------------
static IlvSCManagerRectangle*
GetSCManager()
{
    return (IlvSCManagerRectangle*)topview->getObject("SCManager");
}

// --------------------------------------------------------------------------
static void
PrintCounts(IlvManager* manager,
	    IlvView*,
	    IlvEvent&,
	    IlAny)
{
    IlvPrint("** %d objects in the manager [%d selected]\n",
	     manager->getCardinal(),
	     manager->numberOfSelections());
}

// --------------------------------------------------------------------------
static void
WhereAmI(IlvManager* manager, IlvView* view, IlvEvent& event, IlAny)
{
    if (!reader)
	return;
    IlvPoint p(event.x(), event.y());
    IlvGraphic* g = manager->lastContains(p, view);
    IlvTransformer* t = manager->getTransformer(view);
    if (t) t->inverse(p);
    VpfCoordinate c = reader->whereIs(p.x(), p.y());
    IlvPrint("* Longitude: %.2f, Latitude: %.2f\n  - in IlogViews: %d,%d\n",
	     c.getLongitude(), c.getLatitude(), p.x(), p.y());
    if (g)
	IlvPrint("* Object is an %s\n", g->className());
}

// --------------------------------------------------------------------------
static void
SaveViewsFileCB(IlvGraphic*, IlAny)
{
    if (!reader)
	return;
    static IlvIFileSelector* fileoutselector = 0;
    if (!fileoutselector) {
	fileoutselector = new IlvIFileSelector(display, ".", "*.ilv",
					       0, topview->getSystemView());
	fileoutselector->setTitle("Save Rogue Wave Views file");
    }
    const char* filename = fileoutselector->get();
    if (!filename || !filename[0])
	return;
    ofstream out(filename, IlvBinaryOutputStreamMode);
    if (!out) {
	VpfError* error = new VpfError("Save Rogue Wave Views:");
	error->getStream() << "Couldn't open file " << filename
			   << " for writing";
	VpfErrorReporter::Add(error);
	return;
    }
    IlvRect viewrect;
    workingview->sizeVisible(viewrect);
    IlvManager* manager = reader->getManager();
    IlUInt count;
    IlvGraphic* const* objects =
	manager->allInside(count,
			   viewrect,
			   manager->getTransformer(workingview));
    IlvManagerOutputFile output(out);
    output.saveAll(manager, count, objects);
}

// --------------------------------------------------------------------------
static void
SaveAccelerator(IlvManager*, IlvView*, IlvEvent&, IlAny)
{
    SaveViewsFileCB(0, 0);
}

// --------------------------------------------------------------------------
static void
ResetCB(IlvGraphic*, IlAny)
{
    if (reader && reader->getLibrary()) {
	IlvIQuestionDialog asker(display, "Erase the objects?");
	if (asker.get())
	    reader->getManager()->deleteAll(IlTrue, IlTrue);
	// Reset every theme of each coverage
	for (VpfInt loop = reader->getLibrary()->getNCoverages();
	     loop; --loop) {
	    VpfCoverage* cover = reader->getLibrary()->getCoverage(loop-1);
	    for (VpfInt loop2 = cover->getNThemes(); loop2; --loop2)
		cover->getTheme(loop2-1)->setLoaded(0);
	}
    }
}

// --------------------------------------------------------------------------
static void
SelectProjectionCallback(IlvGraphic* g, IlAny projection)
{
    if (!reader)
	return;
    IlvPopupMenu* popup= (IlvPopupMenu*)g;
    reader->setProjector((VpfProjection*)projection);
    for (IlUShort loop = 0; loop < popup->getCardinal(); loop++) {
	IlvMenuItem* item = popup->getItem(loop);
	item->setChecked(projection == item->getClientData());
    }
}

// --------------------------------------------------------------------------
// Create the projection menu entries:
//     Projection
//             None
//             Transverse Mercator
//             Lambert Azimuthal Equal
//             Gnomonic
//             Plate Carree
// --------------------------------------------------------------------------
static void
CreateProjectionMenu()
{
    IlvPopupMenu popup(display);
    IlvMenuItem item("None");
    item.setChecked(IlTrue);
    item.setRadioToggle(IlTrue);
    item.setCallback(SelectProjectionCallback);
    item.setClientData(0);
    popup.addItem(item);

    item.setChecked(IlFalse);
    item.setLabel("Transverse Mercator");
    projectors[0] = new VpfProjection_tm();
    item.setClientData(projectors[0]);
    popup.addItem(item);

    item.setLabel("Lambert Azimuthal Equal");
    projectors[1] = new VpfProjection_lambert();
    item.setClientData(projectors[1]);
    popup.addItem(item);

    item.setLabel("Gnomonic");
    projectors[2] = new VpfProjection_gnomonic();
    item.setClientData(projectors[2]);
    popup.addItem(item);

    item.setLabel("Plate Carree");
    projectors[3] = new VpfProjection_pcarree();
    item.setClientData(projectors[3]);
    popup.addItem(item);

    // Necessary! Needed for destruction
    projectors[4] = 0;
    popup.setFont(GetMenuBar()->getFont());
    GetMenuBar()->insertItem(1, "^Projection", &popup);
}

// --------------------------------------------------------------------------
static void
DialogClosed(IlvView* v, IlAny)
{
    ((IlvDialog*)v)->cancel();
}

// --------------------------------------------------------------------------
// Load the which'th coverage of the current reader library
// To do this, we create a pop up panel that prompts the user for a
// choice of what he wants lo load in.
// --------------------------------------------------------------------------
static const char* LoadCoverageData =
"// Ilv Version: 5.0\n\
// File generated: Fri Jun 14 16:39:50 2002\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 3\n\
0 F \"defaultBg\" \"defaultFg\" \"button\" \"%helvetica-12-\" 0 solid solid 0 0 0 65535 1\n\
2 F \"defaultBg\" \"defaultFg\" \"default\" \"%helvetica-12-\" 0 solid solid 0 0 0 65535 1\n\
1 F \"defaultBg\" \"defaultFg\" \"%helvetica-12-\" 0 solid solid 0 0 0 65535 1\n\
IlvObjects 9\n\
0 { 0 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
0 IlvButton 10 175 55 23 F13 2 { IlvMessageItem 262145 4 16 4 \"Load\"  }   } 512\n\
1\n\
1 \"__ilvCallback\" \"apply\"\n\
0\n\
0 { 1 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
0 IlvButton 361 175 55 23 F13 2 { IlvMessageItem 262145 4 16 4 \"Cancel\"  }   } 512\n\
1\n\
1 \"__ilvCallback\" \"cancel\"\n\
0\n\
0 { 2 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
0 IlvButton 188 68 50 23 F13 2 { IlvMessageItem 262145 4 16 4 \"All\"  }   } 512\n\
1\n\
1 \"__ilvCallback\" \"w\"\n\
0\n\
0 { 3 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
0 IlvButton 188 96 50 23 F13 2 { IlvMessageItem 262145 4 16 4 \"None\"  }   } 544 \"n\"\n\
1\n\
1 \"__ilvCallback\" \"w\"\n\
0\n\
1 { 4 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
1 IlvArrowButton 201 40 23 23 F13 2 { IlvMessageItem 262145 4 16 4 \"\"  }   1 0 } 32 \"g\"\n\
0\n\
1 { 5 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
1 IlvArrowButton 201 12 23 23 F13 2 { IlvMessageItem 262145 4 16 4 \"\"  }   2 0 } 32 \"s\"\n\
0\n\
1 { 6 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
0 IlvButton 190 126 45 45 F13 2 { IlvMessageItem 262145 4 16 4 \"\"  }   } 32 \"Preview\"\n\
0\n\
1 { 7 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
2 IlvStringList 10 10 170 160 F131 2 A A 0 0 0 0 0 0 0 0 V0 2 0 } 32 \"f\"\n\
0\n\
1 { 8 P 1\n\
[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n\
2 IlvStringList 245 10 170 160 F131 2 A A 0 0 0 0 0 3 0 0 V0 2 0 } 544 \"t\"\n\
1\n\
1 \"__ilvSCallback\" \"SelectCB\"\n\
0\n\
Size 426 208\n\
EOF\n\
";

static void Whole(IlvGraphic* g, IlAny);
static void SelectCB(IlvGraphic* g, IlAny);

// --------------------------------------------------------------------------
class LoadCoverageDialog : public IlvDialog
{
public:
    LoadCoverageDialog(const char* title, long nMaxLabels)
	:  IlvDialog(display, "LoadCoverage", "LoadCoverage",
		     IlvRect(20, 20, 424, 206),
		     IlvNoResizeBorder,
		     topview->getSystemView()),
	   _xorList(nMaxLabels)
    {
	IlvDialog::setTitle(title);
	IL_STDPREF istrstream s((char*)LoadCoverageData);
	read(s);
	setDestroyCallback(DialogClosed);
	_xorList.setGadgets((IlvStringList*)getObject("f"),
			    (IlvStringList*)getObject("t"),
			    (IlvGadget*)getObject("g"),
			    (IlvGadget*)getObject("s"));
	registerCallback("w", Whole);
	registerCallback("SelectCB", SelectCB);
    }
    // ____________________________________________________________
    ~LoadCoverageDialog()
    {
	IlAny* data;
	IlUShort count;
	count = _xorList.getSelectionInFrom(0, &data);
	if (count) {
	    while (count)
		delete IL_REINTERPRETCAST(VpfIlvInfo*, data[--count]);
	    delete [] data;
	}

	count = _xorList.getSelectionInTo(0, &data);
	if (count) {
	    while (count)
		delete IL_REINTERPRETCAST(VpfIlvInfo*, data[--count]);
	    delete [] data;
	}
    }
    void addLabel(const char* label, VpfIlvInfo* data, int fromOrTo)
    {
	_xorList.addLabel(label, (IlAny)data, fromOrTo);
    }
    void rebuildLists() { _xorList.rebuildLists(IlFalse); }
    static LoadCoverageDialog* Get(IlvGraphic* g)
    {
	return (LoadCoverageDialog*)IlvContainer::getContainer(g);
    }
    IlUShort getSelection(IlAny** data)
    {
	return _xorList.getSelectionInTo(0, data);
    }
    void selectAll(int fromOrTo) { _xorList.selectAll(fromOrTo); }

private:
    XorLists _xorList;
};

static void
Whole(IlvGraphic* g, IlAny)
{
    LoadCoverageDialog::Get(g)->selectAll(g->getName() == 0);
}

static void
SelectorCB(IlvGraphic* g, IlAny arg)
{
    VpfIlvInfo* info = (VpfIlvInfo*) arg;
    IlvButton* preview = (IlvButton*) g;
    IlvDialog* dialog = (info->getType() == VpfFeatureType::Line)
	? (IlvDialog*)new EdgeResourceDialog(preview->getView(), info)
	: ((info->getType() == VpfFeatureType::Area)
	   ? (IlvDialog*)new FaceResourceDialog(preview->getView(), info)
	   : ((info->getType() == VpfFeatureType::Text)
	      ? (IlvDialog*)new TextResourceDialog(preview->getView(), info)
	      : ((info->getType() == VpfFeatureType::Point)
		 ? (IlvDialog*)new NodeResourceDialog(preview->getView(), info)
		 : 0)));
    if (dialog) {
	dialog->moveToMouse();
	dialog->wait();
	delete dialog;

	if (preview->getBitmap()) {
	    IlvPalette* palette =
		preview->getBitmap()->getDisplay()->defaultPalette();
	    palette->invert();
	    preview->getBitmap()->fillRectangle(palette, IlvRect(0, 0, 40, 40));
	    palette->invert();
	    info->drawPreview(preview->getBitmap(), IlvRect(0, 0, 40, 40));
	}
	preview->reDraw();
    }
}

// --------------------------------------------------------------------------
static void
SelectCB(IlvGraphic* g, IlAny)
{
    IlvStringList* slist = (IlvStringList*)g;
    LoadCoverageDialog* dialog = LoadCoverageDialog::Get(slist);
    IlvButton* button = (IlvButton*)(dialog->getObject("Preview"));
    IlvBitmap* bitmap = button->getBitmap();
    if (!bitmap) {
	bitmap = new IlvBitmap(slist->getDisplay(),
			       40,
			       40,
			       slist->getDisplay()->screenDepth());
	button->setBitmap(bitmap);
    }

    // Reset the button contents
    IlvPalette* palette = slist->getDisplay()->defaultPalette();
    palette->invert();
    bitmap->fillRectangle(palette,
			  IlvRect(0, 0, 40, 40));
    palette->invert();

    IlAny* data;
    (void)dialog->getSelection(&data);
    IlShort item = slist->getLastSelectedItem();
    if (item != -1) {
	VpfIlvInfo* info = IL_REINTERPRETCAST(VpfIlvInfo*, data[item]);
	info->drawPreview(bitmap, IlvRect(0, 0, 40, 40));
	button->setCallback(SelectorCB, info);
	button->setSensitive(IlTrue);
    } else {
	button->removeCallback(IlvGraphic::CallbackSymbol(), SelectorCB);
	button->setSensitive(IlFalse);
    }
    button->reDraw();
}

// --------------------------------------------------------------------------
static void
LoadCoverage(int which, int byFeatures)
{
    // This line will make the reader load the nth coverage in the nth layer
    reader->setLayer(which);
    // Get coverage name, from its index in the library
    VpfLibrary* library = reader->getLibrary();
    VpfCoverage* coverage = library->getCoverage(which);
    VpfUInt nchoices = 0;
    VpfTheme** themes = 0;
    if (byFeatures)
	nchoices = coverage->getNFeatureClasses();
    else {
	nchoices = coverage->getNThemes();
	if (!nchoices)
	    return;
	themes = new VpfTheme* [nchoices];
	for (VpfUInt loop = 0; loop < nchoices; loop++)
	    themes[loop] = coverage->getTheme(loop);
    }
    if (!nchoices) {
	reader->loadFeatures(coverage); // Load everything
	return;
    }
    char* title = strcpy(new char[23 +
				  strlen(coverage->getDescription())],
			 byFeatures
			 ? "Features selector for "
			 : "Themes selector for ");
    strcat(title, coverage->getDescription());
    LoadCoverageDialog dialog(title, nchoices);
    delete [] title;
    if (byFeatures) {
	for (VpfUInt f = 0; f < nchoices; f++)
	    if (coverage->getFeatureClass(f)->getDescription()) {
		VpfIlvInfo* info =
		    new VpfIlvInfo(f, coverage->getFeatureClass(f)->getType());
		dialog.addLabel(coverage->getFeatureClass(f)->getDescription(),
				info, 1);
	    }
    } else {
	char labelbuf[80];
	for (VpfUInt t = 0; t < nchoices; ++t) {
	    VpfTheme* theme = themes[t];
	    if (theme) {
		VpfIlvInfo* info =
		    new VpfIlvInfo(t,
				   theme->getFeatureClass()->getType());
		sprintf(labelbuf, "(%c/%s) %s",
			info->getName(),
			theme->getValue()->getValue(),
			theme->getValue()->getDescription());
		dialog.addLabel(labelbuf, info, theme->isLoaded() ? 0 : 1);
	    }
	}
    }
    dialog.rebuildLists();
    dialog.wait();
    if (dialog.wasCanceled())
	return;

    IlBoolean contensChangedUpdate = IlvGetContentsChangedUpdate();
    IlvSetContentsChangedUpdate(IlFalse);

    IlAny* selecteddata;
    IlUShort nSelected = dialog.getSelection(&selecteddata);
    if (nSelected) {
	IlUInt nObjectsBefore, nObjectsAfter;
	IlDouble timeBefore, timeAfter;
	VpfIlvInfo** userArgs = new VpfIlvInfo* [nSelected];
	if (byFeatures) {
	    VpfSet choices((int)nchoices);
	    for (IlUShort loop = 0; loop < nSelected; loop++) {
		userArgs[loop] = IL_REINTERPRETCAST(VpfIlvInfo*,
						    selecteddata[loop]);
		choices.set(IL_CAST(int,
				    IL_REINTERPRETCAST(VpfIlvInfo*,
						       selecteddata[loop])
				    ->getIndex()),
			    1);
	    }
	    WaitCursor(IlTrue);
	    nObjectsBefore = reader->getManager()->getCardinal();
	    timeBefore = IlvRunTime();
	    reader->loadFeatures(coverage, &choices, (void**)userArgs);
	    timeAfter  = IlvRunTime();
	    nObjectsAfter = reader->getManager()->getCardinal();
	    WaitCursor(IlFalse);
	} else {
	    VpfTheme** selectedthemes = new VpfTheme*[nSelected];
	    for (IlUShort loop = 0; loop < nSelected; ++loop) {
		userArgs[loop] = IL_REINTERPRETCAST(VpfIlvInfo*,
						    selecteddata[loop]);
		selectedthemes[loop] =
		    themes[IL_REINTERPRETCAST(VpfIlvInfo*,
					      selecteddata[loop])->getIndex()];
	    }
	    WaitCursor(IlTrue);
	    nObjectsBefore = reader->getManager()->getCardinal();
	    timeBefore = IlvRunTime();
	    reader->loadThemes(coverage,
			       nSelected, selectedthemes,
			       (void**)userArgs);
	    timeAfter  = IlvRunTime();
	    nObjectsAfter = reader->getManager()->getCardinal();
	    WaitCursor(IlFalse);
	    delete [] selectedthemes;
	}
	delete [] userArgs;
	delete [] selecteddata;
        IlvPrint("%ld objects loaded in %.2f s.\n",
	         (long)nObjectsAfter-(long)nObjectsBefore,
		 timeAfter-timeBefore);
	reader->getManager()->contentsChanged();
    }
    if (themes)
	delete [] themes;

    IlvSetContentsChangedUpdate(contensChangedUpdate);
    HandleErrors();
}

// --------------------------------------------------------------------------
static void
SelectCoverageByThemesCallback(IlvGraphic* g, IlAny idx)
{
    int coverage = IL_CAST(int, IL_REINTERPRETCAST(VpfIntPtr, idx));
    IlvMenuItem* item = ((IlvPopupMenu*)g)->getItem((IlUShort)coverage);
    IlvManager* manager = GetSCManager()->getManager();
    if (item->isChecked()) {
	manager->setVisible(coverage, IlFalse);
	item->setChecked(IlFalse);
    } else {
	LoadCoverage(coverage, 0);
	manager->setVisible(coverage, IlTrue);
	item->setChecked(IlTrue);
    }
    manager->fitTransformerToContents(workingview, IlFalse);
    manager->reDraw();
}

// --------------------------------------------------------------------------
static void
SelectCoverageByFeaturesCallback(IlvGraphic* g, IlAny idx)
{
    int coverage = IL_CAST(int, IL_REINTERPRETCAST(VpfIntPtr, idx));
    IlvMenuItem* item = ((IlvPopupMenu*)g)->getItem((IlUShort)coverage);
    IlvManager* manager = GetSCManager()->getManager();
    if (item->isChecked()) {
	manager->setVisible(coverage, IlFalse);
	item->setChecked(IlFalse);
    } else {
	LoadCoverage(coverage, 1);
	manager->setVisible(coverage, IlTrue);
	item->setChecked(IlTrue);
    }
    manager->fitTransformerToContents(workingview, IlFalse);
    manager->reDraw();
}

// --------------------------------------------------------------------------
static IlUShort
CreateCoverageMenus()
{
    VpfLibrary* library = reader ? reader->getLibrary() : 0;
    if (!library)
	return 0;
    VpfUInt count = library->getNCoverages();
    if (!count)
	return 0;
    IlvPopupMenu themesPopup(display);
    IlvPopupMenu featuresPopup(display);
    IlUShort cover = 0;
    for (VpfUInt loop = 0; loop < count; loop++) {
	VpfCoverage* cov = library->getCoverage(loop);
	if (cov) {
	    IlvMenuItem item(cov->getDescription());
	    item.setToggle(IlTrue);
	    item.setClientData(IL_REINTERPRETCAST(IlAny,
						  IL_CAST(VpfIntPtr, loop)));
	    item.setCallback(SelectCoverageByThemesCallback);
	    item.setSensitive(cov->getNThemes() != 0);
	    themesPopup.addItem(item);
	    item.setCallback(SelectCoverageByFeaturesCallback);
	    item.setSensitive(IlTrue);
	    featuresPopup.addItem(item);
	}
	cover++;
    }
    themesPopup.setFont(GetMenuBar()->getFont());
    GetMenuBar()->insertItem(3, "Coverages ^Themes",   &themesPopup);
    featuresPopup.setFont(GetMenuBar()->getFont());
    GetMenuBar()->insertItem(4, "Coverages ^Features", &featuresPopup);
    GetMenuBar()->reDraw();
    HandleErrors();
    return cover;
}

// --------------------------------------------------------------------------
static void
ResetTitle()
{
    VpfLibrary* library = reader ? reader->getLibrary() : 0;
    if (library) {
	char title[512];
	sprintf(title, "%s: %s (Lon:[%.2f,%.2f], Lat:[%.2f,%.2f])",
		defaultTitle, library->getName(),
		reader->getExtent().getMinLongitude(),
		reader->getExtent().getMaxLongitude(),
		reader->getExtent().getMinLatitude(),
		reader->getExtent().getMaxLatitude());
	topview->setTitle(title);
    } else
	topview->setTitle(defaultTitle);
}

// --------------------------------------------------------------------------
static void
LoadLibrary(VpfLibrary* library)
{
    reader->setLibrary(library);
    reader->setExtent(library->getExtent());
    if (reader->getProjector())
	reader->getProjector()->
	    setCM(VpfCentralMeridian(library->getExtent().getMinLongitude(),
				     library->getExtent().getMaxLongitude()));
    IlvMenuItem* menu = (GetMenuBar()->getCardinal() > 4)
	? GetMenuBar()->getItem(4)
	: 0;
    if (menu)
	GetMenuBar()->removeItem(4);
    menu = (GetMenuBar()->getCardinal() > 3)
	? GetMenuBar()->getItem(3)
	: 0;
    if (menu)
	GetMenuBar()->removeItem(3);
    WaitCursor(IlTrue);
    IlUShort ncoverages = CreateCoverageMenus();
    WaitCursor(IlFalse);
    if (ncoverages) {
	if (reader->getManager()->getNumLayers() < (int)ncoverages)
	    reader->getManager()->setNumLayers(ncoverages);
    }
    ResetTitle();
}

// --------------------------------------------------------------------------
static void
LoadLibraryCallback(IlvGraphic*, IlAny libIndex)
{
    VpfUInt idx = IL_CAST(VpfUInt, IL_REINTERPRETCAST(VpfIntPtr, libIndex));
    if (reader && reader->getDatabase() &&
	(idx < reader->getDatabase()->getNLibraries()))
	LoadLibrary(reader->getDatabase()->getLibrary(idx));
}

// --------------------------------------------------------------------------
// Create a sub menu that lists every available library, for the current
// database
// --------------------------------------------------------------------------
static void
CreateLibraryMenu()
{
    VpfDatabase* database = reader ? reader->getDatabase() : 0;
    if (!database)
	return;
    VpfUInt count = database->getNLibraries();
    if (!count)
	return;
    IlvPopupMenu popup(display);
    for (VpfUInt loop = 0; loop < count; loop++) {
	VpfLibrary* library = database->getLibrary(loop);
	if (library) {
	    IlvMenuItem item(library->getName());
	    item.setCallback(LoadLibraryCallback);
	    item.setClientData(IL_REINTERPRETCAST(IlAny,
						  IL_CAST(VpfIntPtr, loop)));
	    popup.addItem(item);
	}
    }
    popup.setFont(GetMenuBar()->getFont());
    GetMenuBar()->insertItem(2, "^Libraries", &popup);
    GetMenuBar()->reDraw();
}

// --------------------------------------------------------------------------
static void
LoadHierarchy(const char* path)
{
    VpfIlvReader* oldreader = reader;
    IlPathName dir(path);
    reader = new VpfIlvReader(display, dir.getDirName(IlFalse));
    if (reader->isBad()) {
	VpfError* error = new VpfError("Load Hierarchy:");
	error->getStream() << "Couldn't find LAT in " << path;
	if (oldreader)
	    error->getStream() << "Keeping previous reader";
	VpfErrorReporter::Add(error);
	delete reader;
	reader = oldreader;
    } else {
	if (oldreader) {
	    GetSCManager()->setManager(0, IlFalse);
	    delete oldreader;
	    // Remove previous library and coverage menus
	} else
	    CreateProjectionMenu();
	IlvManager* manager = reader->getManager();
	GetSCManager()->setManager(manager, IlFalse);
	workingview = GetSCManager()->getView();
	topview->setTitle(defaultTitle);
	manager->addAccelerator(PrintCounts, IlvKeyDown, 'N');
	manager->addAccelerator(WhereAmI, IlvKeyDown, '?');
	manager->addAccelerator(SaveAccelerator, IlvKeyDown, 'S');
	selectInteractor = new IlvSelectInteractor(manager, workingview);
	manager->setInteractor(selectInteractor, workingview);
	// Remove Features menu
	IlvMenuItem* menu =
	    (GetMenuBar()->getCardinal() > 4) ?
	    GetMenuBar()->getItem(4) : 0;
	if (menu)
	    GetMenuBar()->removeItem(4);
	// Remove Themes menu
	menu = (GetMenuBar()->getCardinal() > 3) ?
	    GetMenuBar()->getItem(3) : 0;
	if (menu)
	    GetMenuBar()->removeItem(3);
	// Remove Libraries menu
	menu = (GetMenuBar()->getCardinal() > 2) ?
	    GetMenuBar()->getItem(2) : 0;
	if (menu)
	    GetMenuBar()->removeItem(2);
	WaitCursor(IlTrue);
	CreateLibraryMenu();
	WaitCursor(IlFalse);
    }
    HandleErrors();
}

// --------------------------------------------------------------------------
static void
LoadHierarchyCB(IlvGraphic*, IlAny)
{
    static IlvIFileSelector* fileinselector = 0;
    if (!fileinselector) {
	fileinselector = new IlvIFileSelector(display,
					      getenv("VPFROOT")
					      ? getenv("VPFROOT")
					      : ".",
					      "*",
					      0, topview->getSystemView());
	fileinselector->setTitle("Load a VPF hierarchy");
    }
    const char* hierarchy = fileinselector->get();
    if (hierarchy && hierarchy[0])
	LoadHierarchy(hierarchy);
}

// --------------------------------------------------------------------------
static void
ComputeTranslation(IlvTransformer& tr,
		   IlvPos x,
		   IlvPos y,
		   IlvPos w,
		   IlvPos h,
		   IlvTransformer* t = 0)
{
    if (t) tr = *t;
#if (IlvVersion < 300)
    IlFloat
#else  /* IlvVersion >= 300 */
	IlvTransfoParam
#endif /* IlvVersion >= 300 */
	dx, dy;
    tr.getValues(dx, dy);
    dx -= (x + w);
    dy -= (y + h );
    tr.setValues(dx, dy);
}

// --------------------------------------------------------------------------
static void
DumpCB(IlvGraphic*, IlAny)
{
    static IlvIFileSelector* fileselector = 0;
    if (!fileselector) {
	fileselector = new IlvIFileSelector(display, ".", "*.ps",
					    0, topview->getSystemView());
	fileselector->setTitle("PostScript Dump");
    }
    const char* filename = fileselector->get();
    if (!filename || !filename[0])
	return;

    IlvPSDevice psdevice(display);
    if (!psdevice.init(filename)) return;
    display->initDump(&psdevice);
    IlvManager* manager = reader->getManager();
    IlvTransformer* t = manager->getTransformer(workingview);
    IlvRect bbox;
    manager->computeBBox(bbox,t);
    IlvDim PaperWidth  = (IlvDim)(21   * 72 / 2.54),
	PaperHeight = (IlvDim)(29.7 * 72 / 2.54);
    IlvRect pageRect(0, 0, PaperWidth, PaperHeight);
    IlvRegion region(pageRect);
    IlvPos x = bbox.x(),
	y = bbox.y();
    IlvTransformer transformer;
    for (IlvPos w=0; w<(IlvPos)bbox.w(); w += PaperWidth)
	for (IlvPos h=0; h<(IlvPos)bbox.h(); h += PaperHeight) {
	    if (w || h) psdevice.newPage();
	    ComputeTranslation(transformer, x, y, w, h, t);
	    manager->draw(workingview, &transformer, &region, &region);
	}
    display->endDump();
    IlvPrint("Dump file is ready.\n");
}

// --------------------------------------------------------------------------
static const char* RangeData = "// Ilv Version: 2.3\n\
// File generated: Thu Oct 31 17:46:32 1996\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 2\n\
1 \"gray\" \"black\" \"button\" \"%helvetica-12-B\" 0 solid solid 0 0 0\n\
\"IlvStText\" 0 \"gray\" \"black\" \"normal\" \"%helvetica-12-\" 0 solid solid 0 0 0\n\
IlvObjects 10\n\
1 { 0 0 IlvNumberField 111 12 45 22 F6 2 2 -1 0 \"0\" . , 2 16 -180 180 } 32 \"LoMn\" 0\n\
1 { 1 0 IlvNumberField 111 41 45 22 F6 2 2 -1 0 \"0\" . , 2 16 -180 180 } 32 \"LoMx\" 0\n\
1 { 2 0 IlvNumberField 111 70 45 22 F6 2 2 -1 0 \"0\" . , 2 16 -90 90 } 32 \"LaMn\" 0\n\
1 { 3 0 IlvNumberField 111 99 45 22 F6 2 2 -1 0 \"0\" . , 2 16 -90 90 } 32 \"LaMx\" 0\n\
1 { 4 0 IlvLabel 20 30 \"Longitude Min:\" } 0 0\n\
1 { 5 0 IlvLabel 20 59 \"Longitude Max:\" } 0 0\n\
1 { 6 0 IlvLabel 20 88 \"Latitude Min:\" } 0 0\n\
1 { 7 0 IlvLabel 20 117 \"Latitude Max:\" } 0 0\n\
1 { 8 1 IlvButton 5 133 73 23 F1 2 16 Y \"Apply\" } 0 4 \"apply\"\n\
1 { 9 1 IlvButton 95 133 73 23 F1 2 16 Y \"Cancel\" } 0 4 \"cancel\"";

// --------------------------------------------------------------------------
class RangeDialog : public IlvDialog
{
public:
    RangeDialog()
	:  IlvDialog(display, "Range", "Setting Range",
		     IlvRect(20, 20, 172, 162),
		     IlvNoResizeBorder,
		     topview->getSystemView())
    {
	IL_STDPREF istrstream s((char*)RangeData); read(s);
	setDestroyCallback(DialogClosed);
    }
};

static void
SetRangeCB(IlvGraphic*, IlAny)
{
    if (!reader) return;
    VpfExtent extent = reader->getExtent();
    RangeDialog dialog;
#define NF(s) ((IlvNumberField*)dialog.getObject(s))
    NF("LoMn")->setValue(extent.getMinLongitude());
    NF("LoMx")->setValue(extent.getMaxLongitude());
    NF("LaMn")->setValue(extent.getMinLatitude());
    NF("LaMx")->setValue(extent.getMaxLatitude());
    dialog.wait();
    if (!dialog.wasCanceled()) {
	IlBoolean e;
	reader->setExtent(VpfExtent(VpfCoordinate(NF("LoMn")->getFloatValue(e),
						  NF("LaMn")->getFloatValue(e)),
				    VpfCoordinate(NF("LoMx")->getFloatValue(e),
						  NF("LaMx")->getFloatValue(e))));
	ResetTitle();
    }
#undef NF
}

// **************************************************************************
// ReadVpf entry point
// **************************************************************************
static const char* MainPanelData = "// Ilv Version: 2.3\n\
// File generated: Thu Oct 31 12:38:50 1996\n\
// Creator class: IlvGadgetManagerOutput\n\
Palettes 2\n\
\"default\" 1 \"defaultBg\" \"defaultFg\" \"default\" \"fixed\" 0 solid solid 0 0 0\n\
0 \"defaultBg\" \"defaultFg\" \"menu\" \"%helvetica-12-B\" 0 solid solid 0 0 0\n\
IlvObjects 2\n\
1 { 0 0 IlvMenuBar 0 0 600 29 F3 2 1\n\
258 \"^File\" 0 IlvPopupMenu 237 119 136 130 F2 2 9\n\
130 \"^Open hierarchy...\" \"OpenHierarchy\"\n\
130 \"^Save Rogue Wave Views...\" \"SaveViewsFile\"\n\
0 \n\
130 \"^Reset\" \"Reset\"\n\
130 \"S^et range...\" \"SetRange\"\n\
0 \n\
130 \"^Dump\" \"Dump\"\n\
0 \n\
130 \"E^xit\" \"Quit\" } 32 \"MenuBar\" 0\n\
1 { 1 1 IlvSCManagerRectangle 0 30 584 554 YY } 96 \"SCManager\" \"SCManager\" 0\n\
GeometryHandlers\n\
1 100 0 600 0 600 0\n\
2 3 0 0 0 600 0 600 0 0 0 0 0\n\
3 0 0 0 600 0 600 1 0 0 0 0\n\
1 100 0 600 0 600 0\n\
1 3 0 2 30 570 0 570 1 0 0 0 0";

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    display = new IlvDisplay("VPFReader", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create IlvDisplay...");
	delete display;
	return 1;
    }
    topview = new IlvGadgetContainer(display,
				     defaultTitle,
				     defaultTitle,
				     IlvRect(0, 0, 600, 600),
				     IlFalse);
    {
	istrstream dataStream((char*)MainPanelData);
	topview->read(dataStream);
    }
    topview->setDestroyCallback(Quit);
    topview->registerCallback("OpenHierarchy", LoadHierarchyCB);
    topview->registerCallback("SaveViewsFile", SaveViewsFileCB);
    topview->registerCallback("Reset",         ResetCB);
    topview->registerCallback("Dump",          DumpCB);
    topview->registerCallback("SetRange",      SetRangeCB);
    topview->registerCallback("Quit",          QuitCB);

    if (argc >= 2) {
	IlPathName dir(argv[1]);
	LoadHierarchy(dir.getDirName(dir.isDirectory()));
    }
    if ((argc >= 3) && reader && reader->getDatabase()) {
	VpfLibrary* library =
	    reader->getDatabase()->getLibrary(IL_CONSTCAST(const char*,
							   argv[2]));
	if (library)
	    LoadLibrary(library);
    }
#if 0
    if (reader && reader->getLibrary() && (argc >= 4))
	LoadCoverage(atoi(argv[3]));
#endif

    topview->applyResize(1.F, 1.F);
    topview->show();

    IlvMainLoop();
    return 0;
}
