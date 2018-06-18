
                             Rogue Wave Views 6.2
                             Foundations Package

                               Samples 'table'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'prime'
---------------
  An example of how to extend an IlvTable that can be used in a specialized
  graphic object.

  This sample displays a grid where each filled square indicates a prime
  number. The top left cell corresponds to the value 1.
  There are more visible cells if you enlarge the window.
  The grid is an instance of a new graphic class, called PrimeTable, inheriting
  from IlvFilledRectangle. It uses a subclass of IlvTable that implements its
  drawItem member function by testing whether the indicated cell corresponds to
  a prime number.
  If you click with the left button on a cell, the value of the cell is
  displayed in a small pop-up menu. This is achieved by a specialized
  IlvInteractor set on the PrimeTable instance.

  For demonstration purposes, this sample code uses portable GUI elements from
  the Gadgets package of the Rogue Wave Views suite. Feel free to use these
  elements in your application if you have a license for Rogue Wave Views or
  for Rogue Wave Views Controls. This information applies to the classes
  located in the library ilvgadgt, listed in the README file that you can find
  in the installation directory.

  Classes involved:
    - IlvTable
    - IlvInteractor

  Source files:
    - src/prime.cpp

