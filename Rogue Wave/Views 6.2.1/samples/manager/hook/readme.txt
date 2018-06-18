
                             Rogue Wave Views 6.2
                               Manager Package

                                Samples 'hook'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'scalemgr'
------------------
  Displays scales around a map and synchronizes them with the transformer of
  the map.

  Shows the connection of location scales around a map.
  The usual accelerators are available to zoom and pan the map:

    * 'Z': zoom in

    * 'U': zoom out

    * 'i': set transformer to 'identity'

    * arrows: pan in a given direction

    * 'f': fit to size

  The map is very large: try to zoom out or 'fit-to-size'.
  The surrounding scales will automatically be updated to match the current
  coordinates system. The tick marks and the labels are recomputed to show
  reasonable scales.
  Note that two square markers are stored in the map (at [0,0] and [200,200]).
  The scales also contain markers to indicate the position of the markers on
  the map.
  There is also a little trick to avoid clipping the scale labels when they are
  too close from the edge of the scale. This trick needs some tuning to get rid
  of some redraw bugs but the goal is just to give an idea on how to solve this
  kind of problems.

  Classes involved:
    - IlvManager
    - IlvManagerViewHook
    - IlvRectangularScale

  Source files:
    - include/scalehk.h
    - src/scalehk.cpp
    - src/scalemgr.cpp


Sample: 'magnify'
-----------------
  Displays a map in a global view and a magnified view.

  Illustrates a possible use of the multiview capabilities of a manager.
  Two views display the same map. The main view allows you to show the map in
  detail. The small view is intended to provide a global view of the map; it
  also contains a specialized object representing the rectangular region of the
  map shown in the main view. This object is called the magnifier and is
  controlled by a manager view hook.
  Zooming or moving in the main view changes the magnifier position and size.
  Clicking the global view moves the magnifier and changes the area seen in the
  main view.

  For demonstration purposes, this sample code uses portable GUI elements from
  the Gadgets package of the Rogue Wave Views suite. Feel free to use these
  elements in your application if you have a license for Rogue Wave Views or
  for Rogue Wave Views Controls. This information applies to the classes
  located in the library ilvgadgt, listed in the README file that you can find
  in the installation directory.

  Classes involved:
    - IlvManager
    - IlvManagerViewHook
    - IlvManagerMagViewInteractor

  Source files:
    - src/magnify.cpp

