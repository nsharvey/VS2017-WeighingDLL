
                             Rogue Wave Views 6.2
                             Foundations Package

                               Samples 'basic'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'ilvread'
-----------------
  Loading and displaying a Rogue Wave Views data file.

  This example shows how to use IlvContainer::readFile to load a Rogue Wave
  Views data file.
  If objects are associated with interactors, they will be interactive as
  expected.

  Classes involved:
    - IlvContainer

  Source files:
    - src/ilvread.cpp


Sample: 'inter'
---------------
  Displaying and interacting with graphic objects.

  Shows the use of graphic objects and behaviors.
  Click the left mouse button to move objects, and the middle mouse button to
  change their size.
  Pressing the [Dump PS] button creates a PostScript dump file of the visible
  area, in a file called "dump.ps".

  Classes involved:
    - IlvGraphic
    - IlvContainer

  Source files:
    - src/inter.cpp


Sample: 'hull'
--------------
  Using IlPool in a recursive algorithm.

  The convex hull of a set of points is computed and dynamically updated.
  Because the algorithm is recursive, we use the Rogue Wave Views Pools
  mechanism to allocate and release the memory blocks that are needed.

  Classes involved:
    - IlPoolOf

  Source files:
    - src/hull.cpp

