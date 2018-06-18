
                             Rogue Wave Views 6.2
                               Grapher Package

                               Samples 'design'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'design'
----------------
  This sample shows how to subclass IlvGrapherPin to define connection points
  on fixed-size graphic objects.

  This sample implements a subclass of IlvGrapherPin that enables to define
  connection pins relatively to the bounding box of a graphic object. Such
  connection pins are well suited for fixed-size graphic objects. In the
  context of this sample, we use these connection pins on small electric
  network elements that are represented by instances of the IlvIcon class. The
  GUI of this sample enables to switch between several editing modes:

    * Selection. This mode is implemented by using the IlvGraphSelectInteractor
      class.

    * Link creation. This mode allows you to connect two elements with an
      instance of the IlvOneLinkImage class.

    * Element Creation. Once this mode is selected, you create elements by
      simply clicking the working view.

  Classes involved:
    - IlvGrapher
    - IlvIcon
    - IlvGrapherPin
    - IlvManagerViewInteractor
    - IlvGraphSelectInteractor

  Source files:
    - include/fixedpin.h
    - src/fixedpin.cpp
    - src/design.cpp

