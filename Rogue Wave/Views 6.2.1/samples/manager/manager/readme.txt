
                             Rogue Wave Views 6.2
                               Manager Package

                              Samples 'manager'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'draw'
--------------
  Example of a basic graphic editor.

  This simple application allows you to create graphic objects and modify them.
  The application is composed of a drawing area and a toolbar that enables to
  switch between several editing modes. In the drawing area, the default
  manager accelerators are available:

    * 'Z': zoom in

    * 'U': zoom out

    * 'i': set transformer to 'identity'

    * 'f': fit to size

    * 'R': rotate drawing

    * arrows: pan in a given direction

  Additional accelerators provided by the IlvSelectInteractor in selection
  mode:

    * '<Ctrl>+A': select all objects

    * 'Del': remove all selected objects

    * '<Ctrl>+G': group the selected objects

    * '<Ctrl>+U': ungroup the selected objects

    * 'p': raise the selected objects

    * (uppercase) 'P': lower the selected objects

  For demonstration purposes, this sample code uses portable GUI elements from
  the Gadgets package of the Rogue Wave Views suite. Feel free to use these
  elements in your application if you have a license for Rogue Wave Views or
  for Rogue Wave Views Controls. This information applies to the classes
  located in the library ilvgadgt, listed in the README file that you can find
  in the installation directory.

  Classes involved:
    - IlvManager
    - IlvManagerViewHook
    - IlvSelectInteractor
    - IlvResourcePanel

  Source files:
    - include/dragsq.h
    - src/dragsq.cpp
    - src/draw.cpp

