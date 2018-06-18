
                             Rogue Wave Views 6.2
                                 Maps Package

                              Samples 'projvect'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'projvect'
------------------
  Projects a vector representation of the earth.

  This sample shows how to project a vector file, the available projections
  being listed in a combo box. The icons in the toolbar allow you to quit the
  application, zoom in and zoom out the projected image, fit the image in the
  view, pan and zoom the view. An interactor is available to center the
  projection and a grid can be displayed on the image.

  Classes involved:
    - IlvProjection

  Source files:
    - include/proj.h
    - include/gui.h
    - include/centeri.h
    - include/pcenter.h
    - src/proj.cpp
    - src/gui.cpp
    - src/centeri.cpp
    - src/pcenter.cpp

