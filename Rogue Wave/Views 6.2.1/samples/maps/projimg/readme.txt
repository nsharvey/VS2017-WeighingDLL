
                             Rogue Wave Views 6.2
                                 Maps Package

                              Samples 'projimg'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'projimg'
-----------------
  Projects an image of the earth.

  This sample shows a set of projections that can be applied to a raster
  representation of the earth. You can change the projection by selecting an
  item of the projection combo box on the right of the screen.

  The icons in the tool bar allow you to quit the application, zoom in and zoom
  out the projected image, fit the image in the view, pan and zoom the view. An
  interactor is available to center the projection and a grid can be displayed
  on the image.

  Classes involved:
    - IlvProjection

  Source files:
    - include/proj.h
    - include/gui.h
    - include/pcenter.h
    - include/centeri.h
    - src/proj.cpp
    - src/gui.cpp
    - src/pcenter.cpp
    - src/centeri.cpp

