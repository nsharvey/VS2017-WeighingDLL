
                             Rogue Wave Views 6.2
                                 Maps Package

                                Samples 's57'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 's57viewer'
-------------------
  This sample shows how to load S57 data.

  Data are read from the .000 file.


  [IMAGE] : Activates the tooltip interactor allowing you to show the
  attributes of a geometry (if any) by clicking it.
  [IMAGE] : Empties the manager.
  [IMAGE] : Loads an .000 S57 file.

  Classes involved:
    - IlvS57Reader
    - IlvS57Loader

  Source files:
    - include/s57viewer.h
    - include/gui.h
    - src/s57viewer.cpp
    - src/gui.cpp

