
                             Rogue Wave Views 6.2
                             Gantt Chart Package

                              Samples 'calendar'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'calendar'
------------------
  This sample shows how to use IlvGanttChartForms, IlvCalendarScales, and grids
  for the Gantt chart.

  This sample demonstrates how to use the time scales and the grids with the
  Gantt chart form. It shows how to do the following with the IlvGanttChartForm
  and the classes of the time scales:

    * How to use the toolbar defined in samples\gantt\common.

    * How to create an IlvGanttChartForm.

    * How to create an IlvCalendarScale and use it to show dates and times in
      the IlvGanttChartForm.

    * How to create an IlvGanttCalendarGrid and use it in the IlvGanttChartForm.

    * How to use IlvGanttResourceGrid as the grid for resource lines.

    * How to customize graphic models used in IlvGanttChartForm.

    * How to use IlvGanttResourceLine to create the line graphic model. The
      resources in an IlvGanttChartForm are represented by the
      IlvGanttResourceLine class. The line graphic model of an
      IlvGanttChartForm must be an instance of IlvGanttResourceLine. The
      IlvGanttChartForm will create automatically an IlvGanttResourceHeader for
      such a line graphic model. See the function CreateLineGraphicModel().

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
    - IlvGanttChartForm
    - IlvGanttLine
    - IlvGanttNode
    - IlvGanttSubNode
    - IlvShadowLabel
    - IlvGanttResourceLine
    - IlvGanttResourceHeader
    - IlvGanttResourceGrid
    - IlvGanttCalendarScale
    - IlvGanttCalendarGrid

  Source files:
    - src/calendar.cpp

