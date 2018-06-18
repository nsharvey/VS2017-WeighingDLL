
                             Rogue Wave Views 6.2
                             Gantt Chart Package

                                Samples 'load'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'load'
--------------
  A customized Gantt chart shows the load information of the resources.

  This sample shows how to customize the grid of the Gantt chart in order to
  show the load information of the resources.

  This information is a colored line:

    * green means that the resource can still be used for more activities,

    * orange means the resource is just saturated,

    * red means that the resource is overloaded.

  Classes involved:
    - IlvGanttChart
    - IlvGanttLine
    - IlvGanttNode
    - IlvGanttSubNode

  Source files:
    - include/load.h
    - include/loadgantt.h
    - src/load.cpp
    - src/loadgantt.cpp

