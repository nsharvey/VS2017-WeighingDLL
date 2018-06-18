	               Rogue Wave Views version 6.2.1

			tools/vpf README File

This directory contains the needed source files to read VPF (DCW/VMAP0) data
and convert it to Rogue Wave Views 2D objects
		
The 'Gadgets' package must be installed to be able to build this sample.

		VPF reader documentation
		------------------------

This document describes the VPF databases reader module for
Rogue Wave Views. It is made of two parts:

	* The description of the main classes that are used by the
	  reader;
	* The documentation of the 'readvpf' binary.

This document requires that the reader already knows the basic notions
involved in the VPF format.

1 - VPF specific classes
~~~~~~~~~~~~~~~~~~~~~~~~~

Specific classes have been implemented to create the VPF reader. The
main class, called VpfReader, does the actual reading of a Vpf database.
We will start by a description of this class, then other classes will be
described so you can perform lower level operations.

1-1: The reader
- - - - - - - -

Loading part of or all a VPF database is made by an instance of the
VpfReader class, that must be subclassed to apply to different
situations. Its synopsis follows:

    class VpfReader                              [vpf/reader.h]
    {
    public:
        VpfReader(const char* databasepathname);
        virtual ~VpfReader();

        int isBad();
        VpfDatabase* getDatabase() const;
        VpfLibrary* getLibrary() const;
        void        setLibrary(const char* libraryname);
        void        setLibrary(VpfLibrary* library);
        const VpfExtent& getExtent() const;
        void  setExtent(const VpfExtent& extent);
        VpfProjection* getProjector() const;
        void           setProjector(VpfProjection* projector);
	void loadFeatures(VpfCoverage* coverage,
			  VpfSet* features = 0,
			  void** userArgs = 0);
	void loadThemes(VpfCoverage* coverage,
			VpfUInt nthemes, VpfTheme** themes,
			void** userArgs = 0);
        virtual VpfCoordinate& whereIs(double x, double y) const;
protected:
        virtual void createNode(const VpfCoordinate& coords, void*) = 0;
        virtual void createEdge(long count, VpfCoordinate* coords, void*) = 0;
        virtual void createFace(long count, VpfCoordinate* coords, void*) = 0;
        virtual void createText(const VpfCoordinate& where,
                                const char* text, void*)=0;
    };


As you can see, this is an abstract class, and its subtypes will
actually perform the graphic part of the loading process. An instance
of the VpfReader class is able to read, from a given library of a
given database, a set of themes or features, in a given coverage.

You use the reading capabilities of the VpfReader class by installing
a "current" library, from which reading operation will be performed.

 = Constructor/Destructor
	VpfReader(const char* databasepath=0);
	virtual ~VpfReader();

   The constructor initializes a new instance of a VPF reader, that will
   read the information from the database specified by the pathname
   <databasepath>.

   The destructor also deletes the database that was loaded, as well
   as all the related structures (libraries, coverages themes and
   features).

 = int isBad();
   The isBad member function will return a non-null value if the
   initialization of this reader couldn't be successful. Error
   messages are printed out.

 = VpfDatabase* getDatabase() const;
   The getDatabase member function returns a pointer to the instance
   of the database that is used by the reader, or NULL if there are
   none.
   The VpfDatabase class is described in section 1-2.

 = VpfLibrary* getLibrary() const;
   The getLibrary member function returns a pointer to the instance of
   the current library in the reader, or NULL if none has been
   installed.
   The VpfLibrary class is described in section 1-3. 

 = void setLibrary(const char* libraryname);
   void setLibrary(VpfLibrary* library);
   The setLibrary member functions set the current library to the one
   that is called <libraryname>, or the <library> object. An instance
   of the VpfReader class can only read from one library at a time.

 = const VpfExtent& getExtent() const;
   The getExtent member function returns the bounding rectangle (in
   latitude-longitude) from which we will read. The default is the
   current library's bounding rectangle (that contains every tile of
   the library).

   The VpfExtent class synopsis follows:

        class VpfExtent                              [vpf/extent.h]
        {
        public:
	    VpfExtent(const VpfCoordinate& c1, const VpfCoordinate& c2);
	    VpfExtent(const VpfExtent& source);

	    double getMinLongitude() const { return _c1.getLongitude(); }
	    double getMaxLongitude() const { return _c2.getLongitude(); }
	    double getMinLatitude() const  { return _c1.getLatitude(); }
	    double getMaxLatitude() const  { return _c2.getLatitude(); }
        };

   This class is used to store rectangles, in a coordinate system
   defined by doubles, in longitude-latitude. Longitudes will
   therefore always be greater that -180, and smaller than 180, and
   latitude will range from -90 (south pole) to 90 (north pole).

 = void setExtent(const VpfExtent& extent);
   The setExtent member function sets a new set of tiles as the source
   rectangle.

 = VpfProjection* getProjector() const;
   The getProjector member function returns the current projector, or
   NULL if none has been set.

 = void setProjector(VpfProjection* projector) const;
   The setProjector member function sets the current projector to
   <projector>.

 = void loadFeatures(VpfCoverage* coverage, VpfSet* features = 0,
                     void** userArgs = 0);
   The loadFeatures member function actually reads a set of features
   from the indicated coverage.
   The class VpfSet is a bit array that indicates which features indexes
   are to be selected (see vpf/set.h for details).
   The userArgs array is an array of user parameters (one per feature)
   that will be provided to the "createXXX" function calls described later
   in this section. The size of the array must be at least as big as the number
   of features to be loaded.
   
 = void loadThemes(VpfCoverage* coverage,
                   VpfUInt nthemes, VpfTheme** themes,
                   void** userArgs = 0);
   The loadThemes member function actually reads a set of themes
   from the indicated coverage.
   'themes' is an array of 'nthemes' pointers to VpfThemes.
   The 'userArgs' array is an array of user parameters (one per feature)
   that will be provided to the "createXXX" function calls described later
   in this section. The size of the array must be at least as big as the number
   of features to be loaded.

 = virtual VpfCoordinate& whereIs(double x, double y) const;
   The virtual whereIs member function will apply to its parameters
   <x> and <y> the inverse of the current projection, and returns a
   pair of coordinates, in the database coordinate system.

 = virtual void createNode(const VpfCoordinate& coords, void* userArg) = 0;
   The virtual createNode member function is called to create a node
   at the coordinates designated as <coords>.
   The userArg parameter is the parameter that was set in the array when
   calling "loadThemes" or "loadFeatures"

 = virtual void createEdge(long count, VpfCoordinate* coords, void* userArg) = 0;
   The virtual createEdge member function is called to create an edge
   that follows the <count> coordinates place in the array <coords>.
   The userArg parameter is the parameter that was set in the array when
   calling "loadThemes" or "loadFeatures"

 = virtual void createFace(long count, VpfCoordinate* coords, void* userArg) = 0;
   The virtual createFace member function is called to create a face
   that follows the <count> coordinates place in the array <coords>.
   The userArg parameter is the parameter that was set in the array when
   calling "loadThemes" or "loadFeatures"

 = virtual void createText(const VpfCoordinate& where, const char* text, void* userArg) = 0;
   The virtual createText member function is called to create a text
   that contains the <text> strings, located at <where>.
   The userArg parameter is the parameter that was set in the array when
   calling "loadThemes" or "loadFeatures"

1-2: Databases
- - - - - - - -

Opening a database means creating an instance of the VpfDatabase
class. It synopsis summary follows:

    class VpfDatabase                              [vpf/database.h]
    {
    public:
        int isBad();
        const char*  getName()       const;
        const char*  getDescription() const;
        const char*  getPath()       const;
        VpfUInt      getNLibraries() const;
        VpfLibrary*    getLibrary(VpfUInt i) const;
        VpfLibrary*    getLibrary(const char*) const;
    };

 = int isBad();
   The isBad member function returns a non-null value if there has
   been a problem initializing the database.

 = const char*  getName() const;
   The getName member function returns the name of this database.

 = const char*  getDescription() const;
   The getDescription member function returns the description of this database.

 = const char*  getPath() const;
   The getPath member function returns the pathname where this
   database is stored.

 = VpfUInt getNLibraries() const;
   The getNLibraries member function returns the number of libraries
   stored in this database.

 = VpfLibrary* getLibrary(VpfUInt i);
   The getLibrary member function returns the ith library
   of this database.

 = VpfLibrary* getLibrary(const char* libname);
   The getLibrary member function returns the library that has the
   name <libname> in this database.

1-3: Libraries
- - - - - - - -

All VPF libraries are handle by the VpfLibrary class. Its synopsis
summary follows:

    class VpfLibrary                              [vpf/library.h]
    {
    public:
        int  isBad();
        const char*        getName()           const;
        const char*        getDescription()    const;
        const char*        getPath()           const;

        VpfUInt getNCoverages() const;
        VpfCoverage* getCoverage(VpfUInt i) const;
        VpfCoverage* getCoverage(const char*) const;

        const VpfExtent&   getExtent()         const;
        int  hasTiles() const;
    };

 A library stores the coverages it handles.

 = Constructor/Destructor
        VpfLibrary(VpfDatabase* db, const char* name);
        ~VpfLibrary();
   The constructor initializes a new VPF library that is read from the
   <db> VPF database, and has the name <name>.
   The destructor will also remove every contained structures
   (coverages...).

 = int isBad();
   The isBad member function will return a non-null value if the
   initialization of this library couldn't be successful. Error
   messages are printed out.

 = const char* getName() const;
   The getName member function returns the name of this library.

 = const char* getPath() const;
   The getPath member function returns the full pathname where this
   library is stored (such as /usr/local/data/DCW/browse).

        VpfUInt getNCoverages() const;
        VpfCoverage* getCoverage(VpfUInt i) const;
        VpfCoverage* getCoverage(const char*) const;

 = VpfUInt getNCoverages() const;
   The getNCoverages member function returns the number of coverages
   stored in this library.

 = VpfCoverage* getCoverage(VpfUInt index) const;
   The getCoverage member function returns a pointer to the
   <index>th coverage loaded in this library.

 = VpfCoverage* getCoverage(VpfUInt index) const;
   The getCoverage member function returns a pointer to the
   <index>th coverage loaded in this library.

 = VpfCoverage* getCoverage(const char* coveragename);
   The getCoverage member function returns a pointer to the coverage
   that has the name <coveragename> in this library, or NULL if none
   matches this name.

 = long getNTiles() const;
   The getNTiles member function returns the number of VPF tiles
   stored in this library.

 = const VpfExtent& getExtent() const;
   The geExtent member function returns a reference to the bounding
   rectangle of all the objects stored in this library.

 = int hasTiles() const;
   The hasTiles member function returns a non-null value if this
   library actually stores this object it handles into tiles.

1-4: Coverages
- - - - - - - -

Coverages are groups of informations that shared common properties or
that adress the same semantic aspect. A library owns a given number of
coverages. Objects to be loaded are located in coverages, and are
designated by a specific feature class, which is handled by the
VpfFeatureClass class.
Geographic objects are stored with a set of attributes that can
have several values (such as the elevation of a location, for instance).
When an attribute's possible values are taken form a predefined set
(such as the names of countries), then these features may be gathered
in a theme (handled by the calss VpfTheme).
A coverage is an instance of the VpfCoverage class. Here is its
synopsis summary:

    class VpfCoverage                              [vpf/vpf.h]
    {
    public:
        int isBad() const;
        const char* getName()        const;
        const char* getDescription() const;

        VpfUInt getNFeatureClasses() const;
        VpfFeatureClass* getFeatureClass(VpfUInt i) const;
        VpfFeatureClass* getFeatureClass(const char*) const;

        VpfUInt getNThemes() const;
        VpfTheme* getTheme(VpfUInt i) const;
    };

When a library is created, every coverage of this library is also
created and initialized.

 = int isBad()
   The isBad member function will return a non-null value if the
   initialization of this coverage couldn't be successful. Error
   messages are printed out.

 = const char* getName() const;
   The getName member function returns the name of this coverage. This
   name is also the name of the directory this coverage is stored into.

 = const char* getDescription() const;
   The getDescription member function returns a string that briefly
   describes this coverage.

 = long getNThemes() const;
   The getNThemes member function returns the number of themes that
   are stored within this coverage.

 = VpfTheme* getThemes(VpfUInt index) const;
   The getThemes member function returns a pointer to the ith
   theme of this coverage.


1-5: Themes
- - - - - -

Themes precisely define what information is to be loaded, from which
tiles, for a given criteria. They are managed by the VpfTheme class:

    class VpfTheme                              [vpf/vpf.h]
    {
    public:
        const char* getDescription() const;
        long        getValue() const;
        int  isLoaded()      const;
        void setLoaded(int flag = 1);
        int  isBad() const;
    };

When a library is created, every descriptor of every coverage is
also created, as well as every theme of each of these coverages.

 = const char* getDescription() const;
   The getDescription member function returns a string that briefly
   describes this coverage. This string is the one used to
   access a theme from the VpfReader member functions.

 = long getValue() const;
   The getValue member function returns the value associated with
   this theme. It can be useful to distinguish several themes that
   share the same description string.

 = int isLoaded() const;
   The isLoaded member function returns a non-null value if this theme
   has been loaded by a VpfReader instance.

 = void setLoaded(int flag = 1);
   The setLoaded member function modifies this theme's "loaded" state
   to the one specified by the <flag> value.

 = int isBad() const;
   The isBad member function returns a non-null value if this theme
   couldn't be initialized.

2 - Predefined VPF reader for Rogue Wave Views
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A subtype of the VpfReader class is available in the vpf/vpfilv.h
file: the VpfIlvReader class. It implements the necessary code to
create Rogue Wave Views graphic objects (IlvExtPolygon and IlvExtPolylines,
most of the times) depending on what is actually loaded.

    class VpfIlvReader                              [vpf/vpfilv.h]
    : public VpfReader
    {
        VpfIlvReader(IlvManager* manager, VpfProjection* p = 0);
    
        IlvDisplay* getDisplay();
        IlvManager* getManager();
        int  getLayer() const;
        void setLayer(int layer);

        virtual void createNode(const VpfCoordinate& where);
        virtual void createEdge(long count, VpfCoordinate* coords);
        virtual void createFace(long count, VpfCoordinate* coords);
        virtual void createText(const VpfCoordinate& where, const char* text);

        void storeObject(IlvGraphic* object);
    };

This class stores the created objects in an IlvManager, and you have
the opportunity to change the layer in which objects are to be stored.

 = Constructor
	VpfIlvReader(IlvDisplay* display, const char* databasepathname);
   The constructor initializes a new VPF reader, and create a storage
   manager. The <databasepathname> is the directory pathname where the
   database is to be found.

 = IlvDisplay* getDisplay();
   The getDisplay member function returns a pointer to the IlvDisplay
   object that was used to create the manager.

 = IlvManager* getManager();
   The getManager member function returns a pointer to the IlvManager
   object that was created.

 = int getLayer() const;
   The getLayer member function returns current storage layer, the one
   used when loading member fucntions of the VpfReader class are
   called.

 = void setLayer(int layer);
   The setLayer member function lets you modify current insertion
   layer to the one specified as <layer>.

 = virtual void createNode(const VpfCoordinate& where);
   The virtual createNode member function creates an instance of the
   IlvMarker class, and calls storeObject with that object.

 = virtual void createEdge(long count, VpfCoordinate* coords);
   The virtual createEdge member function creates an instance of the
   IlvPolyline class, and calls storeObject with that object.

 = virtual void createFace(long count, VpfCoordinate* coords);
   The virtual createFace member function creates an instance of the
   IlvPolygon class, and calls storeObject with that object.

 = virtual void createText(const VpfCoordinate& where, const char* text);
   The virtual createText member function creates an instance of the
   IlvLabel class, and calls storeObject with that object.

 = virtual void storeObject(IlvGraphic* object);
   The virtual storeObject member function stores the object <object>
   in the manager, in the current layer.

3 - Using the VPF predefined application for Rogue Wave Views
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

With the provided source files, one can compile and execute a
program called "readvpf".

This reads and displays graphically all or part of a VPF database,
creating Rogue Wave Views objects through a 100% Rogue Wave Views graphical
interface.

At launch time, a window is created with a File menu that lets you
specify which database is to be loaded, save Rogue Wave Views files, print,
set loading parameters, as well as quit the program.

You use readvpf by selecting a database (giving its pathname to the
file selector). An instance of the VpfIlvReader class is created. The
list of all the contained libraries is then created, as well
as a "Libraries" menu that lets you select the current library. When you
select a library, the list of the converages it contains is displayed
in a new "Coverages" menu. Selecting a coverage pops a window up, in
which you can select which themes are to be loaded. At any time, you
may change the source library or coverage.

* Loading: the "Open Hierarchy..." option of the File menu pops a file
  selector up. You must choose a VPF hierarchy path;
  A valid path is a directory name (ending with '/' or '\') that
  contains the files 'lat' and 'dht'.
  You can also select one of the 'lat' or 'dht' files.
  The file selector will start in the current directory, or in the
  contents of the environment variable "VPFROOT".
  If your CDROM device is "/cdrom", it will be faster for you to set
  VPFROOT to /cdrom, and run readvpf afterwards. When you request to
  open a VPF hierarchy, the file selector will point to that location.

* Saving: the "Save Rogue Wave Views..." option will save all the visible
  objects to a file that you will be prompted to indicate.

* Reset: resets the reader. Themes are then considered as NOT loaded,
  no matter if they were or not. Note that themes are considered as
  entirely loaded, even if you only selected a tiny area, then changed
  your mind.
  You will be asked if you want to remove the objects from the manager
  at this moment.

* Selection: The "Set Range..." option lets you specify the source tiles
  area from which you want to load the data.

* Printing: The Dump option generates a PostScript dump file, on
  several pages if the scaling factor makes this necessary.

When a database is loaded, another menu appears. These are the
possible projectors. Depending on the source database you are working
on, you may have to change default additionnal growing factors (see
the beginning of the src/vpfilv.cpp file).
The Libraries menu also appears at this moment.

Selectiong a library name makes a two new menus appear, that contain the
list of all the coverages of this library.
You can load a specific theme (that is, a set of features that have predefined
attribute values) by choosing a coverage in the "Coverage Themes" menu.
Or you can load all features of a given coverage by selecting a coverage
in the "Coverage features" menu.

The default behaviour of this sample program is to store each coverage
in a different layer.
These menus indicate whether a coverage (a layer) is visible or not. In
the initialization phase, every coverage is said to be invisible (they
are not loaded, anyway).
Selecting a non-visible coverage makes a selector window appear (where you
can select the themes of features you wish to load).
Selecting a visible coverage makes it disappear.

The selector window lets you mark or unmark the themes or features you
want to load.
In the case of a theme selection, the feature type is indicated by a letter
(F:face, E:edge, T:text, N or C:node) followed by the attribute value.

You may select the All option, marking all themes or features for loading,
or none, deselecting every themes or features.

The Load button will hide the window and start the loading.
If you don't select any theme or feature in this panel, the coverage
is simply made visible.

To speed up the initialization phase, you may run readvpf with
2 optional parameters:

Usage:
   readvpf [database-pathname/ [library-name]]
(the trailing '/' (slash) at the end of the end of the database pathname
 is necessary).

The database-pathname directory is where should be located the files
'lat' and 'dht'.

Exemple:

   readvpf /usr/local/data/DCW/  noamer

will launch readvpf with the immediate loading of the library
"noamer" of the database found in "/usr/local/data/DCW".

All accelerators of the manager are available.
Another accelerator is installed: '?' (question mark key) that
indicates where you pointer device is, both in Rogue Wave Views coordinates,
and in the database coordinate system. These coordinates are displayed
in the terminal that launched the application.
