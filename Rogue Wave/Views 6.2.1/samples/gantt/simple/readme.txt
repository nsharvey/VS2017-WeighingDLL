
                             Rogue Wave Views 6.2
                             Gantt Chart Package

                               Samples 'simple'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'simple'
----------------
  This sample shows how to use IlvGanttChart and grids for the Gantt chart.

  This sample demonstrates simply how to use the Gantt chart. It shows how to
  do the following with the IlvGanttChart:

    * How to use the toolbar defined in samples\gantt\common.

    * How to create an IlvGanttChart.

    * How to create an IlvGanttRowGrid and use it in the IlvGanttChart.

    * How to use IlvGanttResourceGrid as the grid for Gantt lines.

    * How to customize graphic models used in IlvGanttChartForm.

    * How to create a break graphic model. The CreateBreakGraphicModel()
      function shows the creation of the break graphic model. Note that this
      graphic model has a nonshared palette and an IlvModeAnd drawing mode.


  How to use the toolbar:
  -----------------------

    1. [IMAGE] Click on this button to select any graphic objects of the Gantt
      chart.

        * Select, move, and resize Gantt subnodes.

        * Select and vertically move the Gantt lines. This is useful for
          resource reorganizing.

    2. [IMAGE] Click on this button to add new rows to the end of the Gantt
      chart.

    3. [IMAGE] Click on this button to delete any selected Gantt lines.

    4. [IMAGE] Click on this button to create Gantt nodes.

    5. [IMAGE] Click on this button to create breaks.

    6. [IMAGE] Click on this button to create Gantt links between Gantt nodes.

    7. [IMAGE] Click on this button to enable/disable the outline borders of
      the grapher views.

    8. [IMAGE] Click on this button to change the background of the grid.

    9. [IMAGE] Click on this button to change the foreground of the grid.

    10. [IMAGE] Click on this button to pan and zoom the Gantt chart.

        * To pan, drag the left mouse button in one of the grapher views.

        * To zoom, drag the middle button or use the mouse wheel in one of the
          grapher views.

    11. [IMAGE] Click on this button to change the current subnode graphic
      model of the Gantt chart. If any subnodes are selected, this action also
      changes their graphics.

  Classes involved:
    - IlvGanttChart
    - IlvGanttLine
    - IlvGanttNode
    - IlvGanttSubNode
    - IlvShadowLabel
    - IlvGanttResourceLine
    - IlvGanttResourceHeader
    - IlvGanttLineReliefGrid
    - IlvGanttRowGrid

  Source files:
    - src/simple.cpp

