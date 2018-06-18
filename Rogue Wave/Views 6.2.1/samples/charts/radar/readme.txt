
                             Rogue Wave Views 6.2
                                Charts Package

                               Samples 'radar'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'radar'
---------------
  Shows you how to create a Radar Chart.

  This sample shows you how to use the IlvRadarChart class to create a Radar
  Chart that displays the values of several data sets. These data sets are also
  displayed by a Cartesian chart, which demonstrates the ability to share data
  sets between several graphic representations.

  The following interactions are available on the chart:

    * Radar chart: Clicking on a point selects the corresponding data set.
      Another click selects a specific point in the data set. Once a point is
      selected, it can be dragged to a new value.

    * Cartesian chart: You can directly drag a point to modify its value.

  Three buttons (labeled Standard, Stacked and Stacked100) let you change the
  displayers used to display the data sets. The Radar chart uses filled-area
  displayers (IlvPolygonChartDisplayer and IlvStackedPolygonChartDisplayer)
  whereas the Cartesian chart uses bar displayers (IlvBarChartDisplayer and
  IlvStackedBarChartDisplayer).

  The Simulate button launches a timer that randomly changes values in the data
  sets. Notice that both charts are automatically updated whenever a value
  changes.

  Classes involved:
    - IlvRadarChart
    - IlvChartInteractor
    - IlvPolylineChartDisplayer
    - IlvPolygonChartDisplayer
    - IlvStackedPolygonChartDisplayer
    - IlvBarChartDisplayer
    - IlvStackedBarChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/radar.cpp

