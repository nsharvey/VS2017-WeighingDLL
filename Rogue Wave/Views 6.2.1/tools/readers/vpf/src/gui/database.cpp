// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/database.cpp
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
// Definition of the Database class
// --------------------------------------------------------------------------

#include <vpf/gui/database.h>
#include <vpf/gui/manager.h>
#include <vpf/gui/layers.h>
#include <vpf/gui/application.h>
#include <vpf/gui/databaselist.h>
#include <ilviews/gadgets/filesel.h>

#include <vpf/gui/databasereferencer.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <vpf/feature.h>
#include <vpf/area.h>
#include <vpf/attribute.h>
#include <vpf/string.h>
#if defined(ILVSTD)
# include <cstdlib>
ILVSTDUSE
#else
# include <stdlib.h>
#endif

// --------------------------------------------------------------------------
Database::Database(IlvGadgetContainer* browser,
		   Layers* layers)
: _display(browser->getDisplay()),
  _browser(browser),
  _layers(layers),
  _databasesMenu(0),
  _librariesTree(0),
  _addDatabaseButton(0),
  _closeDatabaseButton(0),
  _makeLayerButton(0),
  _propertiesButton(0),
  _database(0),
  _featureClass(0)
{
    _databasesMenu = (IlvOptionMenu*)_browser->getObject("db");
    _librariesTree = (IlvTreeGadget*)_browser->getObject("libraries");
    _addDatabaseButton = (IlvButton*)_browser->getObject("adddb");
    _closeDatabaseButton = (IlvButton*)_browser->getObject("closedb");
    _makeLayerButton = (IlvButton*)_browser->getObject("makelayer");
    _propertiesButton = (IlvButton*)_browser->getObject("properties");
  
    _databasesMenu->setCallback(InspectDatabaseCB, this);
    _librariesTree->setCallback(IlvTreeGadget::SelectCallbackType(),
				SelectItemCB, this);
    _addDatabaseButton->setCallback(AddDatabaseCB, this);
    _closeDatabaseButton->setCallback(CloseDatabaseCB, this);
    _makeLayerButton->setCallback(MakeLayerCB, this);
    _propertiesButton->setCallback(PropertiesCB, this);

    // There are no databases so we can't close any,
    // make layers or get properties
    _closeDatabaseButton->setSensitive(IlFalse);
    _databasesMenu->setSensitive(IlFalse);
    _makeLayerButton->setSensitive(IlFalse);
    _propertiesButton->setSensitive(IlFalse);
}

// --------------------------------------------------------------------------
Database::~Database()
{
}

// --------------------------------------------------------------------------
void
Database::AddDatabaseCB(IlvGraphic* g, IlvAny arg)
{
    static IlvIFileSelector* _selector = 0;
    Database* gdb = (Database*)arg;
    const char* name = 0;

    if (!_selector) {
	const char* topDir = getenv("VPFROOT");
	if (!topDir)
	    topDir = 
#if defined(VPF_STARTDIR)
		VPF_STARTDIR
#else
		"."
#endif
		;
	_selector = new IlvIFileSelector(gdb->getDisplay(),
					 topDir, "dht");
    }
    _selector->setTitle("Select VPF Database DHT file");
    _selector->moveToMouse();
    name = _selector->get();
    if (!name || !name[0])
  	return;

    gdb->addDatabase(name);
}

#if defined(WIN32)
#define DIRSEP '\\'
#else
#define DIRSEP '/'
#endif

// --------------------------------------------------------------------------
void
Database::addDatabase(const char* databaseName)
{
    if (!databaseName)
	return;

    Application::GetApplication()->setBusy(IlTrue);
    Application::GetApplication()->setStatus("Reading database");

    DatabaseReferencer* database = new DatabaseReferencer(databaseName);

    if (database && !database->isBad()) {
	_database = database;
	new DatabaseList(database);
	//updateDatabases(); // done by setBusy!
	updateLibraries();
	// Select the new database in the option menu
	// Assumption: the new DatabaseList item is inserted at
	// the beginning of the list.
	_databasesMenu->setSelected(0);
    }

    Application::GetApplication()->setStatus();
    Application::GetApplication()->setBusy(IlFalse);
    Application::GetApplication()->handleError();
}

// --------------------------------------------------------------------------
void
Database::updateDatabases()
{
    const DatabaseList* ptr = DatabaseList::GetHead();
    unsigned int nDatabases = DatabaseList::GetNDatabases();

    if (nDatabases) {
	const char** databaseNames= new const char*[nDatabases];

	unsigned int i = 0;

	while(ptr) {
	    databaseNames[i] = ptr->getDatabase()->getName();
	    if (!databaseNames[i]) databaseNames[i] = "noname";
	    i++;
	    ptr = ptr->next();
	}

	_databasesMenu->setLabels(databaseNames, i, IlTrue);

	delete [] databaseNames;
    } else
	_databasesMenu->setLabels(0, 0, IlTrue);

    _databasesMenu->reDraw();

    // Can only close a database if there is one!
    _closeDatabaseButton->setSensitive(_database != 0);
    _closeDatabaseButton->reDraw();
    _databasesMenu->setSensitive(_database != 0);
    _databasesMenu->reDraw();
}

// --------------------------------------------------------------------------
void
Database::updateLibraries()
{
    _librariesTree->removeAllItems(IlTrue);
    selectItem(0);
    if (_database)
	for (VpfUInt i = 0; i < _database->getNLibraries(); i++)
	    addLibraryTree(_database->getLibrary(i));
    _librariesTree->reDraw();
}

// --------------------------------------------------------------------------
void
Database::addLibraryTree(VpfLibrary* library)
{
    if (!library)
	return;
    const char* name = library ? library->getName() : "damaged library";
    const char* desc = library ? library->getDescription() : 0;

    if (!name)
	name = "noname";

    char* libraryName = strcpy(new char[strlen(name) +
				        (desc ? strlen(desc) + 3 : 1)],
			       name);

    if (desc) {
	strcat(libraryName, ": ");
	strcat(libraryName, desc);
    }
    IlvTreeGadgetItem* libraryItem = 0;
    libraryItem = _librariesTree->addItem(0,
					  libraryName,
					  -1,
					  0, 0,
					  IlFalse);

    delete [] libraryName;

    if (library) {
	VpfUInt nCoverages = library->getNCoverages();
	for (VpfUInt i = 0; i < nCoverages; i++)
	    addCoverageTree(libraryItem, library->getCoverage(i));
    }

    _librariesTree->shrinkItem(libraryItem, IlFalse);
}

// --------------------------------------------------------------------------
void
Database::addCoverageTree(IlvTreeGadgetItem* libraryItem,
			  VpfCoverage* coverage)
{
    char* coverageName = 0;
  
    if (coverage) {
	coverageName = strcpy(new char[strlen(coverage->getName()) +
				       strlen(coverage->getDescription()) +
				       3],
			      coverage->getName());
	strcat(coverageName, ": ");
	strcat(coverageName, coverage->getDescription());
    } else {
	coverageName = (char*) "Damaged coverage";
    }

    IlvTreeGadgetItem* coverageItem = 0;
    coverageItem = _librariesTree->addItem(libraryItem,
					   coverageName,
					   -1,
					   0, 0,
					   IlFalse);
    if (coverage) {
	delete [] coverageName;
	VpfUInt nFeatureClasses = coverage->getNFeatureClasses();
	for (VpfUInt i = 0; i < nFeatureClasses; i++)
	    addFeatureClassTree(coverageItem, coverage->getFeatureClass(i));
    }
    
    _librariesTree->shrinkItem(coverageItem, IlFalse);
}

// --------------------------------------------------------------------------
void
Database::addFeatureClassTree(IlvTreeGadgetItem* coverageItem,
			      VpfFeatureClass* featureClass)
{
    char* featureClassName = 0;
    const char* featureClassDesc = 0;
    char* attributeName = 0;
    size_t attributeNameLen = 0;
    
    char* valueName = 0;
    size_t valueNameLen = 0;
  
    if (featureClass) {
	featureClassDesc = featureClass->getDescription();
	
	featureClassName =
	    strcpy(new char[strlen(featureClass->getName()) +
			   (featureClassDesc
			    ? strlen(featureClass->getDescription())
			    : 0) +
			   3],
		   featureClass->getName());
	if (featureClassDesc) {
	    strcat(featureClassName, ": ");
	    strcat(featureClassName, featureClassDesc);
	}
    } else 
	featureClassName = (char*) "damaged feature class";

    IlvTreeGadgetItem* classRoot = 0;
    classRoot = _librariesTree->addItem(coverageItem,
					featureClassName,
					-1,
					0, 0,
					IlFalse);
    classRoot->setData(featureClass);

    if (featureClass) {
	delete [] featureClassName;
	VpfUInt nAttributes = featureClass->getNAttributes();
	for (VpfUInt i = 0; i < nAttributes; i++) {
	    VpfAttribute* attribute = featureClass->getAttribute(i);
	    size_t len = strlen(attribute->getName()) +
		strlen(attribute->getDescription()) + 3;
	    if (attributeNameLen < len) {
		if (attributeName) delete [] attributeName;
		attributeName = new char[attributeNameLen = len];
	    }

	    strcpy(attributeName, attribute->getName());
	    strcat(attributeName, ": ");
	    strcat(attributeName, attribute->getDescription());

	    IlvTreeGadgetItem* attributeRoot = 0;
	    attributeRoot = _librariesTree->addItem(classRoot,
						    attributeName,
						    -1,
						    0, 0,
						    IlFalse);
	    attributeRoot->setData(featureClass);

	    VpfUInt nValues = attribute->getNValues();
	    for (VpfUInt k = 0; k < nValues; k++) {
		const VpfValue* value = attribute->getValue(k);
		if (value) {
		    size_t vlen = strlen(value->getValue()) +
			strlen(value->getDescription()) + 3;
		    if (valueNameLen < vlen) {
			if (valueName) delete [] valueName;
			valueName = new char[valueNameLen = vlen];
		    }
		    strcpy(valueName, value->getValue());
		    strcat(valueName, ": ");
		    strcat(valueName, value->getDescription());

		    IlvTreeGadgetItem* item = 0;
		    item = _librariesTree->addItem(attributeRoot,
						   valueName,
						   -1,
						   0, 0,
						   IlFalse);
		    item->setData(featureClass);
		}
	    }
	    _librariesTree->shrinkItem(attributeRoot, IlFalse);
	}
    }

    _librariesTree->shrinkItem(classRoot, IlFalse);

    if (attributeName)
	delete [] attributeName;
    if (valueName)
	delete [] valueName;
}

// --------------------------------------------------------------------------
void
Database::InspectDatabaseCB(IlvGraphic* g, IlvAny arg)
{
    IlvOptionMenu* om = (IlvOptionMenu*) g;
    Database* gdb = (Database*)arg;
    gdb->inspectDatabase(om->whichSelected());
}

// --------------------------------------------------------------------------
void
Database::inspectDatabase(IlUShort i)
{
    const DatabaseList* ptr = DatabaseList::GetHead();
    unsigned int nDatabases = DatabaseList::GetNDatabases();

    if (i >= nDatabases)
	return;

    while (ptr && i--)
	ptr = ptr->next();
    if (!ptr)
	return;

    // Assumption: every database was created with the
    // DatabaseReferencer constructor
    DatabaseReferencer* newDatabase = 0;
    newDatabase = (DatabaseReferencer*)ptr->getDatabase();

    if (newDatabase != _database) {
	_database = newDatabase;
	updateLibraries();
    }
}

/*
void
Database::classSelectCB(IlvGraphic* g, IlvAny arg)
{
    IlvTreeGadget* tree = (IlvTreeGadget*) g;
    Database* gdb = (Database*) arg;
    IlvTreeGadgetItem* item = tree->getCallbackItem();

  if (item)
    gdb->classSelect((VpfFeatureClass*) item->getData());
}
 
void
Database::init() {
}
*/
void
Database::SelectItemCB(IlvGraphic* object, IlvAny arg)
{
    Database* gdb = (Database*)arg;
    IlvTreeGadget* tree = (IlvTreeGadget*) object;
    IlvTreeGadgetItem* item = tree->getFirstSelectedItem();
    if (!item)
	return;

    VpfFeatureClass* featureClass = 0;
    featureClass = (VpfFeatureClass*) item->getData();

    gdb->selectItem(featureClass);
}

// --------------------------------------------------------------------------
void
Database::selectItem(VpfFeatureClass* featureClass)
{
    _featureClass = featureClass;

    IlBoolean oldStatus = _makeLayerButton->isSensitive();
    if (oldStatus != (featureClass != 0)) {
	_makeLayerButton->setSensitive(featureClass != 0);
	_makeLayerButton->reDraw();
    }
}

// --------------------------------------------------------------------------
void
Database::MakeLayerCB(IlvGraphic*, IlvAny arg)
{
    Database* gdb = (Database*) arg;
    gdb->makeLayer();
}

// --------------------------------------------------------------------------
void
Database::makeLayer()
{
    if (_featureClass)
	_layers->addLayer(_featureClass);
}

// --------------------------------------------------------------------------
void
Database::CloseDatabaseCB(IlvGraphic*, IlvAny arg)
{
    Database* gdb = (Database*) arg;
    gdb->closeDatabase();
}

// --------------------------------------------------------------------------
void
Database::closeDatabase()
{
    if (!_database)
	return;

    if (_database->getNReferences() > 1) {
	// The database is referenced elsewhere, this probably means
	// that feature classes of this database are used in layers.
	// We can't close this database.
	IlvPrint("Can't close this database: feature classes are in use.");
	return;
    }

    DatabaseList* list = DatabaseList::FromPointer(_database);
    delete list;

    _database->unreference();

    // Assumption: every database was created with the
    // DatabaseReferencer constructor
    list = DatabaseList::GetHead();
    _database = (DatabaseReferencer*)(list
				      ? list->getDatabase()
				      : 0);

    updateDatabases();

    _databasesMenu->setSelected(0);
    _databasesMenu->reDraw();

    updateLibraries();
}

// --------------------------------------------------------------------------
void
Database::setBusy(IlBoolean busy)
{
    if (busy) {
	_librariesTree->setSensitive(IlFalse);
	_librariesTree->reDraw();
	_databasesMenu->setSensitive(IlFalse);
	_databasesMenu->reDraw();
	_closeDatabaseButton->setSensitive(IlFalse);
	_closeDatabaseButton->reDraw();
	_addDatabaseButton->setSensitive(IlFalse);
	_addDatabaseButton->reDraw();
	_makeLayerButton->setSensitive(IlFalse);
	_makeLayerButton->reDraw();
	_propertiesButton->setSensitive(IlFalse);
	_propertiesButton->reDraw();
    } else {
	_librariesTree->setSensitive(IlTrue);
	_librariesTree->reDraw();
	_addDatabaseButton->setSensitive(IlTrue);
	_addDatabaseButton->reDraw();
	updateDatabases();
	SelectItemCB(_librariesTree, this);
    }
}

// --------------------------------------------------------------------------
void
Database::PropertiesCB(IlvGraphic*, IlvAny) 
{
}

