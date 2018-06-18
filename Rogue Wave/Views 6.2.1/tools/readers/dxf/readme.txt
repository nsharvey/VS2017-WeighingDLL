                             Rogue Wave Views Maps 6.2

                                The DXF Reader



A Reader for the DXF format is provided with the source code in the
Rogue Wave Views Maps add-on.

A DXF Viewer, also provided with the source code, demonstrates how to use
this reader.

The DXF reader is located in the directory <installdir>/tools/readers/dxf.

The default compilation of this reader needs the Rogue Wave Views Gadgets and
Rogue Wave Views Manager packages. However, if you did not install the
Rogue Wave Views Gadgets package, you can compile this program using :
- 'make dxfviewer.nogadgets' on Unix platforms
- 'nmake dxfviewer.nogadgets' on Windows platforms

When the Rogue Wave Views Gadgets package is not available, the file browser
is replaced by a text field.

About the DXF format
--------------------

The DXF format (Drawing Interchange Format) is the interchange format of
AutoCAD. This format supports vector graphics (polygons, arcs, lines,
points...) and layers. The DXF format is often used as an interchange
format for vector maps. The specifications of the DXF format can be found
at the following URL
http://www.autodesk.com/techpubs/autocad/dxf/reference/

The Files
---------

dxfreader.h
dxfreader.cpp

dxfbasic.h
dxfbasic.cpp

dxffactory.h
dxffactory.cpp

dxfviewer.h
dxfviewer.cpp

   * The dxfreader.h and dxfreader.cpp files define the DXF Reader.
   * The dxfbasic.h and dxfbasic.cpp files define the basic entities used
     by the DXF Reader.
   * The dxffactory.h and dxffactory.cpp files define the graphic factory
     used by the DXF Reader to create graphic objects.
   * The dxfviewer.h and dxfviewer.cpp files define a simple Viewer that
     demonstrates how the reader can be used.

Using the DXFReader
-------------------

The class DXFReader can be used in other applications. To read a DXF file,
you should include the dxfreader.h file and add the following line to your
code:

      DXFFrameReader frameReader(fileName,
                                 manager,
                                 factory);


   * fileName is the name of the DXF frame.
   * manager is the instance of IlvManager where the reader will put the
     graphic objects.
   * factory is an instance of DXFGraphicFactory. It willl be used by the
     reader to create the graphic objects from their DXF description.

To create a DXFFactory, you can use the DXFDefaultGraphicFactory class
providied with this reader.

       DXFDefaultGraphicFactory factory(display,
                                        mapInfo,
                                        sourceProjection);


   * display is the Rogue Wave Views display.
   * mapinfo is an optional argument specifying the georeferencement
     information of your manager. If you don't provide a mapinfo, the dxf
     reader will create one with an unknown projection, that can be
     accessed with the DXFReader::getMapInfo function.
   * sourceProjection is an optional argument specifying the projection of
     the data contained in the DXF file. If you pass this argument, the DXF
     reader will reproject the data to the mapinfo's projection.
