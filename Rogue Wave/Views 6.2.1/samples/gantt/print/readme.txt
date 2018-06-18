
                             Rogue Wave Views 6.2
                             Gantt Chart Package

                               Samples 'print'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'print'
---------------
  Multiple Pages Gantt Chart Printing.

  This sample prints a gantt chart using Postcript or Windows printer. It uses
  a class called GanttChartPrintingUtility.
  Multiple pages printing is handled by this class. On each page, the gantt
  lines and scale are printed according to the part of the gantt chart which is
  supposed to be displayed.

  Classes involved:
    - IlvPSDevice
    - IlvWindowsDevice
    - IlvGanttChart

  Source files:
    - src/print.cpp
    - src/ganttprnt.cpp
    - include/ganttprnt.h

