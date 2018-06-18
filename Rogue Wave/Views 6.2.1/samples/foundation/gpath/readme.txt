
                             Rogue Wave Views 6.2
                             Foundations Package

                               Samples 'gpath'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'gpath'
---------------
  Using the capabilities of the IlvGraphicPath object: disconnected polylines,
  polygons with holes and drawing along a path.

  A data file that contains two instances of the class IlvGraphicPath is read
  into an IlvContainer.

  You can animate the objects by pressing the SPACEBAR, and use the regular
  accelerators of the IlvContainer class:

  Arrow Keys

  Pan

  i

  Initialize transformer to identity

  Z

  Zoom in (x 2)

  U

  Zoom out (/ 2)

  f

  "fit": set zoom factor to display every graphic objects

  R

  Rotate

  The IlvGraphicPath class has additional features that can be turned into
  account:

    * Disconnected polylines: This is often the case when an entity is
      represented as several vectors in the cartographic file. This could be
      when a long road is cut into small pieces, or when the road is actually
      interrupted locally. Then it is convenient to have a graphic object that
      can be built from several disjoint vectors. The IlvGraphicPath enables
      this functionality.

    * Polygons with holes: Some applications need to represent polygons with
      holes. This is easily done with IlvGraphicPath objects, by providing
      several vectors for the inside and the outside polygons.

    * Drawing along a path: Even more attractive, the IlvGraphicPath offers the
      capacity to draw along the polyline or the polygon. It is possible to
      repeat a drawing - without memory allocation - along an object, by
      specifying the drawing method and the spacing between each drawing.

  Classes involved:
    - IlvGraphicPath
    - IlvTransformedGraphic
    - IlvTimer

  Source files:
    - src/gpath.cpp

